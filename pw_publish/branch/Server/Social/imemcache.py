# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *

import tornado.ioloop
import tornado.options
from tornado.options import define, options

#from iwebserver import *

def AsyncMC():
    return tornado.ioloop.IOLoop.instance().mc

# заглушка, на случай когда "не особо нужен callback"
def main_memc_callback( reply ):
    ##log( "- main_memc_callback: reply %s" % str(reply) )
    pass

##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------
class IMemcache:
    """ Виртуальный интерфейс для общения с memcache (он же и dummy-заглушка).
        повторяет интерфейс реального общения приложения с memcache thread pool (через очередь запросов), 
        поэтому параметры и return могут быть странного вида.
        Поведение: по умолчанию якобы "фейлим" все запросы к memcache.
    """
    def checkLogin(self, login_key, callback, params=None): 
        """ проверить, есть ли в memcache указанный логин;
            ответ: будет вызван callback( reply = { "r":(login_data, cas_id) } )
        """
        return callback( {"r": None, "p":params} )
        
    def lockLogin(self, login_key, login_data, cas_id, callback):
        """ попытаться залочить в memcache указанный логин, поставив ему значение login_data (cas_id == возвращен из предыдущего checkLogin)
            ответ: будет вызван callback( reply = { "r":True|False } )
        """
        return callback( {"r": False} )

    def updateLogin(self, login_key, login_data):
        """ апдейтим в memcache указанный логин (ранее залоченный нашим сервером)
        """
        pass
    
    def destroy(self):
        pass
        
    def addQuery(self, op, args_tuple, callback, params=None):
        """ голый запрос к underlying Memcache """
        if op == "gets":
            reply = (None, None)
        else:
            reply = None
        return callback( {"r": reply, "p":params} )

    # после ресета списка серверов требуется разбудить все рабочие потоки, чтобы пореесетили свои коннекты
    def wakeAll(self):
        pass
    
    # имеет ли смысл retry операций?
    def allowsRetries(self):
        pass
        
##---------------------------------------------------------------------------------------------
## В отличие от IMemcache, всегда возвращаем ok/yes на все запросы
class MemcacheMockYes(IMemcache):
    """ Поведение: якобы "успешно" исполняем все запросы, всегда возвращаем ok/yes; генерируем уникальный uid юзера на каждый логин. """
    def __init__(self):
        self._next_uid = 100000 * options.server_id
        
    def checkLogin(self, login_key, callback, params=None): 
        """ проверить, есть ли в memcache указанный логин """
        self._next_uid += 1
        login_data = "0:%d:12345:0" % self._next_uid # да, логин есть и он свободен (server_id=0)
        return callback( {"r": (login_data, 0), "p":params} )
        
    def lockLogin(self, login_key, login_data, cas_id, callback):
        """ попытаться залочить в memcache указанный логин, поставив ему значение login_data (cas_id == возвращен из предыдущего checkLogin)
            ответ: будет вызван callback( reply = { "r":True|False } )
        """
        return callback( {"r": True} )

##---------------------------------------------------------------------------------------------
## В ответ на проверки логина возвращаем "юзер на другом сервере"
class MemcacheMockPeer(IMemcache):
    """ Поведение: возвращаем "юзер на другом сервере"; при этом генерируем уникальный uid юзера на каждый логин. """
    def __init__(self):
        self._next_uid = 100000 * options.server_id
        
    def checkLogin(self, login_key, callback, params=None): 
        """ проверить, есть ли в memcache указанный логин """
        self._next_uid += 1
        login_data = "%d:%d:12345:0" % (DUMMY_PEER_WS_ID, self._next_uid) # да, логин есть, но он занят (на несуществующем server_id==-2)
        return callback( {"r": (login_data, 0), "p":params} )
        
    def lockLogin(self, login_key, login_data, cas_id, callback):
        """ попытаться залочить в memcache указанный логин, поставив ему значение login_data (cas_id == возвращен из предыдущего checkLogin)
            ответ: будет вызван callback( reply = { "r":True|False } )
        """
        return callback( {"r": True} )

##---------------------------------------------------------------------------------------------
## Интерфейс для общения с реальным memcache через async thread-pool.
class AsyncMemcache(IMemcache):
    def checkLogin(self, login_key, callback, params=None): 
        """ проверить, есть ли в memcache указанный логин; """
        AsyncMC().addQuery( "gets", (login_key,), callback, params )
        
    def lockLogin(self, login_key, login_data, cas_id, callback):
        """ попытаться залочить в memcache указанный логин, поставив ему значение login_data (cas_id == возвращен из предыдущего checkLogin) """
        AsyncMC().addQuery( "cas", (login_key, login_data, cas_id), callback )

    def updateLogin(self, login_key, login_data):
        """ апдейтим в memcache указанный логин (ранее залоченный нашим сервером) """
        AsyncMC().addQuery( "set", (login_key, login_data), main_memc_callback ) # callback в данном случае игнорируем
        
    def destroy(self):
        AsyncMC().destroy()
        
    def addQuery(self, op, args_tuple, callback, params=None):
        """ голый запрос к underlying Memcache """
        AsyncMC().addQuery( op, args_tuple, callback, params )
        
    # после ресета списка серверов требуется разбудить все рабочие потоки, чтобы пореесетили свои коннекты
    def wakeAll(self):
        AsyncMC().wakeAll()

    # retry операций имеет смысл только если у нас вообще есть активные memcache-сервера (при пустом списке серверов будут только вечные обломы)
    def allowsRetries(self):
        return len( AsyncMC().server_list )
        
        
##------------------------------------------------------------------------------------------------------------------------
##------------------------------------------------------------------------------------------------------------------------

##------------------------------------------------------------------------------------------------------------------------
## Обертка, позволяющая "якобы атомарно" выполнять 2 операции: set (изменение данных) и gets (получение нового cas_id)
class SetS:
    def __init__(self, mc, key, data, callback, params=None):
        self.mc = mc
        self.key = key
        self.callback = callback
        self.params = params  
        self.args = (key, data)
        mc.addQuery( "set", (key, data), self.onSet )
        
    def onSet(self, mc_reply):
        if mc_reply and mc_reply.get("r"):
            # set прошел успешно; теперь получаем новый cas_id
            self.mc.addQuery( "gets", (self.key,), self.onGets )
        else:
            self.fail()
            
    def onGets(self, mc_reply):
        if mc_reply and mc_reply.get("r"):
            # что-то ответили. добавляем к запросу исходные параметры и отвечаем
            mc_reply["p"] = self.params
            mc_reply["a1"] = self.args
            self.callback( mc_reply )
        else:
            self.fail()
            
    def fail(self):
        self.callback( {"r":(None, None), "p":self.params, "a1":self.args} )
            
    
##------------------------------------------------------------------------------------------------------------------------
## Обертка, позволяющая "якобы атомарно" выполнять 2 операции: cas (условное изменение данных) и gets (получение нового cas_id)
class CasS( SetS ):
    def __init__(self, mc, key, data, cas_id, callback, params=None):
        self.mc = mc
        self.key = key
        self.callback = callback
        self.params = params        
        self.args = (key, data, cas_id)
        mc.addQuery( "cas", (key, data, cas_id), self.onSet )
    
    ## ... остальные stages совпадают с SetS


##------------------------------------------------------------------------------------------------------------------------
## Обертка, позволяющая "якобы атомарно" выполнять 2 операции: 
##  add (добавление данных, если их еще нет в mc) и gets (получение нового cas_id)
class AddS( SetS ):
    def __init__(self, mc, key, data, callback, params=None):
        self.mc = mc
        self.key = key
        self.callback = callback
        self.params = params        
        self.args = (key, data)
        mc.addQuery( "add", (key, data), self.onSet )
    
    ## ... остальные stages совпадают с SetS

##------------------------------------------------------------------------------------------------------------------------
## Обертка, позволяющая "якобы атомарно" выполнять 2 операции: 
##  append (насильная модификация данных "суффиксом") и gets (получение данных + нового cas_id)
class AppendS( SetS ):
    def __init__(self, mc, key, suffix, callback, params=None):
        self.mc = mc
        self.key = key
        self.callback = callback
        self.params = params        
        self.args = (key, suffix)
        mc.addQuery( "append", (key, suffix), self.onSet )
    
    ## ... остальные stages совпадают с SetS
