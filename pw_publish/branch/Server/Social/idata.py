# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *

import tornado.ioloop
import tornado.options
from tornado.options import define, options

from cluster_base import crc_hash

def mongo_callback( query ):
    ## log( "--- mongo_callback: %s" % str(query) )
    pass
    
def mongo_find_callback( query ):
    #~ cursor = query.get("r")
    #~ count = cursor.count() if cursor else 0
    #~ log( "--- mongo_find_callback: %s (reply count %d)" % ( str(query), count ) )
    #~ for i in range(count):
        #~ log( "----- mongo_find_callback[%d]: %s" % (i, cursor[i]) )
    pass

##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class IData:
    """ Виртуальный интерфейс для общения с некой "user database" (возможно, нереляционной: MongoDB, BerkeleyDB, SimpleDB).
        повторяет интерфейс реального общения приложения с [no]sql thread pool (через очередь запросов), 
        поэтому параметры и return могут быть странного вида.
        Поведение: якобы успешно исполняем все запросы, uid возвращаем уникальный для каждого логина.
    """
    def loadAndStampData(self, shard_key, data_key, stamp, callback, params=None): 
        """ достаем пользовательские данные (из некоторого БД-шарда по некоторому ключу); 
            при этом стампим данные неким ключиком stamp (не указав этот ключ, нельзя апдейтить данные)
            ответ: будет вызван callback( reply = { "r":["data":<text>] } )
        """
        # called: только из onUserCachedData
        reply = ClassDict( {"data":"{}"} )
        return callback( {"r": [reply], "p":params} )
        
    def stampData(self, shard_key, data_key, stamp): 
        """ стампим данные неким ключиком stamp (не указав этот ключ, нельзя апдейтить данные).
            сами данные возвращать не надо, мы их, видимо, уже получили из кэша.
        """
        # called: только из onUserCachedData
        pass 
        
    def saveData(self, shard_key, data_key, stamp, data, callback=None, params=None):
        """ срочное сохранение данных (через основную очередь thread-pool).
            данные должны сохраниться только если указан корректный stamp (для указанной записи)
            ответ: будет вызван callback( reply = { "r":[ "ok":0|1 ] }
        """
        # called: только из saveUserData
        if callback:
            reply = ClassDict( {"ok":1} )
            return callback( {"r": [reply], "p":params} )

    def getData(self, shard_key, data_key, callback=mongo_find_callback, params=None):
        """ есть что-нибудь у данного шарда по данному ключу? """
        pass
            
    def setupIndex(self, shard_key, data_key, callback=mongo_callback, params=None):
        """ обеспечиваем/проверяем наличие необходимого индекса """
        pass
        
    def setupData(self, data_key, callback=mongo_callback, params=None):
        """ обеспечиваем/проверяем наличие индекса у всех инстансов mongo.
            также можно использовать в качестве keepAlive.
        """ 
        pass
        
    def fadeoutData(self, syncWait=1.0):
        """ постепенно закрываем лавочку (ждем когда очередь запросов полностью разберут, и тогда прибиваем thread pool) """
        pass

    def isDoneData(self):
        """ прикрыта ли лавочка? """ 
        return True # пустышку можно прибивать в любой момент

    def insert(self, shard_key, collection, dict, callback=None, params=None):
        pass
   
    def ensure_index(self, shard_key, collection, key, callback=None, unique=True, params=None):
        pass

    def find_one(self, shard_key, collection, key, callback=None, params=None):
        pass

    def find(self, shard_key, collection, key, callback=None, params=None):
        pass

    def remove(self, shard_key, collection, key, callback=None, params=None):
        pass

    def update_data(self, shard_key, collection, data_key, data, callback=None, params=None):
        pass

    def update(self, shard_key, collection, query, update, callback=None, params=None):
        pass

    def multi_update(self, shard_key, collection, query, update, callback=None, params=None):
        pass

    def unset(self, shard_key, collection, data_key, data, callback=None, params=None):
        pass

    def group_unset(self, shard_key, collection, data_key, data, callback=None, params=None):
        pass

    def find_and_modify(self, shard_key, collection, query, callback=None, params=None, **kwargs):
        pass

    def increment(self, shard_key, collection, query, amount, callback=None, params=None, **kwargs):
        pass

##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

WS_MAX_MONGO_THREADS = 2
            
class AsyncMongo( IData ):
    """ Реальный обмен с нереляционной БД MongoDB (запросы странного вида, далеко не SQL).
    """
    def __init__(self, mongo_server_count):
        self.loop = tornado.ioloop.IOLoop.instance()
        self.collection = "pers"
        self.MONGO_SERVER_COUNT = mongo_server_count
        
    def mongoShard(self, shard_key):
        index = ( crc_hash(shard_key) % self.MONGO_SERVER_COUNT ) if self.MONGO_SERVER_COUNT else 0
        return self.loop.mongo[ index ]        
            
    def loadAndStampData(self, shard_key, data_key, stamp, callback, params=None): 
        """ достаем пользовательские данные (из некоторого БД-шарда по некоторому ключу); 
            при этом стампим данные неким ключиком stamp (не указав этот ключ, нельзя апдейтить данные)
            ответ: будет вызван callback( reply = { "r":["data":<text>] } )
        """
        # called: только из onUserCachedData
        self.mongoShard(data_key).addQuery( self.collection, "find_and_modify", ({"key":data_key}, {"$set": {"stamp":stamp}}, True), callback, params, \
            opname="loadAndStampData" ) # upsert=True
        
    def stampData(self, shard_key, data_key, stamp): 
        """ стампим данные неким ключиком stamp (не указав этот ключ, нельзя апдейтить данные).
            сами данные возвращать не надо, мы их, видимо, уже получили из кэша.
        """
        # called: только из onUserCachedData
        args = ({"key":data_key}, {"$set": {"stamp":stamp}}, True, False) # upsert=True, manipulate=False, safe=True
        self.mongoShard(data_key).addQuery( self.collection, "update", args, opname="stampData" ) 
        
    def saveData(self, shard_key, data_key, stamp, data, callback=None, params=None):
        """ срочное сохранение данных (через основную очередь thread-pool).
            данные должны сохраниться только если указан корректный stamp (для указанной записи)
            ответ: будет вызван callback( reply = { "r":[ "ok":0|1 ] }
        """
        # called: только из saveUserData
        args = ({"key":data_key, "stamp":stamp}, {"$set": {"data":data}}, True, False) # upsert=True, manipulate=False, safe=True
        self.mongoShard(data_key).addQuery( self.collection, "update", args, callback, params, opname="saveData" ) 

    def getData(self, shard_key, data_key, callback=mongo_find_callback, params=None):
        """ есть что-нибудь у данного шарда по данному ключу? """
        self.mongoShard(data_key).addQuery( self.collection, "find_one", ({"key":data_key},), callback, params, opname="getData" )
            
    def setupIndex(self, shard_key, data_key, callback=mongo_callback, params=None):
        """ обеспечиваем/проверяем наличие необходимого индекса """
        self.mongoShard(data_key).addQuery( self.collection, "ensure_index", (data_key,), callback, params, opname="setupIndex" )
        
    def setupData(self, callback=mongo_callback, params=None):
        """ обеспечиваем/проверяем наличие индекса у всех инстансов mongo.
            также можно использовать в качестве keepAlive. 
        """ 
        mongo_list = self.loop.mongo
        for db in mongo_list:
            for i in range(WS_MAX_MONGO_THREADS): # надо скормить по команде каждому mongo-thread
                db.addQuery( self.collection, "ensure_index", ("key",), callback, params, opname="setupData" )
                
    def fadeoutData(self, syncWait=1.0):
        """ постепенно закрываем лавочку (ждем когда очередь запросов полностью разберут, и тогда прибиваем thread pool) 
            при syncWait==1 не возвращаем управление, пока полностью не закроемся; syncWait==0 ставит флаг и сразу возвращается (async) """
        for mongo in self.loop.mongo:
            mongo.fadeout( syncWait )

    def isDoneData(self):
        """ прикрыта ли лавочка? """ 
        for mongo in self.loop.mongo:
            if ( not mongo.threadsDone() ) or len(mongo.replies): # остались бегающие threads или неразобранные ответы
                return False
        return True

    def insert(self, shard_key, collection, dict, callback=None, params=None):
        args = ( dict, False, False, True ) # upsert=False
        self.mongoShard(shard_key).addQuery( collection, "insert", args, callback, params, opname="insert" ) 
   
    def ensure_index(self, shard_key, collection, key, callback=None, unique=True, sparse=True, params=None):
        pass
# Not need because PF-70300
#        self.mongoShard(shard_key).addQuery( collection, "ensure_index", (key, 300, {"unique":unique, "sparse":sparse}), callback, params, opname="ensure_index" ) 

    def find_one(self, shard_key, collection, data_key, callback=None, params=None):
        self.mongoShard(shard_key).addQuery( collection, "find_one", (data_key,), callback, params, opname="find_one" )

    def find(self, shard_key, collection, data_key, callback=None, params=None):
        self.mongoShard(shard_key).addQuery( collection, "find", (data_key,), callback, params, opname="find" )

    def remove(self, shard_key, collection, data_key, callback=None, params=None):
        self.mongoShard(shard_key).addQuery( collection, "remove", (data_key,), callback, params, opname="remove" )

    def update_data(self, shard_key, collection, data_key, data, callback=None, params=None):
        # upsert=True, manipulate=False, safe=True
        debug("AsyncMongo: update_data for collection {2} with key {0} and data {1}".format(str(data_key), str(data), collection))
        self.mongoShard(shard_key).addQuery( collection, "update", ({"key":data_key}, {"$set": {"data":data}}, True, False), callback, params,
            opname="update_data" )

    def increment(self, shard_key, collection, query, amount, callback=None, params=None, upsert=True):
        self.mongoShard(shard_key).addQuery( collection, "update", (query, {"$inc": amount}, upsert, False), callback, params, opname="increment" )

    def pushAll(self, shard_key, collection, query, amount, callback=None, params=None):
        self.mongoShard(shard_key).addQuery( collection, "update", (query, {"$pushAll": amount}, False, False), callback, params, opname="$pushAll" )

    def pullAll(self, shard_key, collection, query, amount, callback=None, params=None):
        self.mongoShard(shard_key).addQuery( collection, "update", (query, {"$pullAll": amount}, False, False), callback, params, opname="$pullAll" )
    
    def update(self, shard_key, collection, query, update, callback=None, params=None):
        # update - словарь вида http://docs.mongodb.org/manual/reference/method/db.collection.update/#update-parameter
        # upsert=True, manipulate=False, safe=True (? default safe=False!)
        debug("AsyncMongo: update for collection {2} with query {0} and data {1}".format(str(query), str(update), collection))
        self.mongoShard(shard_key).addQuery( collection, "update", (query, {"$set": update}, True, False), callback, params, opname="update" )

    def multi_update(self, shard_key, collection, query, update, callback=None, params=None):
        # update - словарь вида http://docs.mongodb.org/manual/reference/method/db.collection.update/#update-parameter
        # upsert=False, manipulate=False, safe=True, multi=True
        debug("AsyncMongo: multi_update for collection {2} with query {0} and data {1}".format(str(query), str(update), collection))
        self.mongoShard(shard_key).addQuery( collection, "update", (query, {"$set": update}, False, False, True, True), callback, params, opname="update" )

    def unset(self, shard_key, collection, data_key, data, callback=None, params=None):
        debug("AsyncMongo: update_data for collection {2} with data_key {0} and data {1}".format(str(data_key), str(data), collection))
        self.mongoShard(shard_key).addQuery( collection, "update", (data_key, {"$unset": data}, True, False), callback, params, opname="update" )

    def group_unset(self, shard_key, collection, data_key, data, callback=None, params=None):
        debug("AsyncMongo: update_data for collection {2} with data_key {0} and data {1}".format(str(data_key), str(data), collection))
        self.mongoShard(shard_key).addQuery( collection, "update", (data_key, {"$unset": data}, False, True), callback, params, opname="update" )

    def find_and_modify(self, shard_key, collection, query, callback=None, params=None, **kwargs):
        debug("AsyncMongo: find_and_modify in collection %s, query %s, kwargs: %s", collection, query, kwargs)
        self.mongoShard(shard_key).addQuery(collection, "find_and_modify", (query,), callback, params, kw=kwargs, opname="find_and_modify")
