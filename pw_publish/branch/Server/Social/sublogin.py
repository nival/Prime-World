# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, json, re, hashlib, urllib, httplib, logging, functools

from base.helpers import *
from subaction import SubAction, action_timing, separate_timing
from handlers import users, PWSOC_VERSION
from ext_main.login import LoginAction, helperCheckSocialNetworkCount

import ibilling
import pwaccount
from enums import *


class SubloginActionBase( SubAction ):
    """ helper-класс для исполнения server sublogin (не имеет своего onStart, только helper-метод subLogin для вызова из класса-наследника) """
    # ----------------------------------------------------------------------------------------------
    def subLogin(self, login, login_callback=None, persistent_callback=None, auid=0, isGM=False):
        self.persistent_callback = persistent_callback
        if not login_callback:
            login_callback = self.onServerSubLogin
        acc = self.I.WS.getUserAcc( login ) # есть такой в списке логинов?
        self.isAccInCastle = False
        if acc:
            acc.original_snid = self.original_snid
            acc.original_snuid = self.original_snuid
            self.isAccInCastle = True
            touch( acc ) # не удаляйте пока этот аккаунт, мы им интересуемсо
            acc.resetAccStatus()
            
            # да, юзер уже у нас на сервере; нужно ли ждать загрузки persistent user data?
            if self.persistent_callback:                     
                return self.setupPersistentCallback( acc )
            
            self.response["sublogin_ok"] = 2 # already logged on this server
            self.response["ok"] = 1
            return self.fin()
        
        try:
            self.allow_login_underscores = 1 # чтобы login не ругался на "_" в имени юзера
            self.force_login = 1 # чтобы с нас не требовали auth, key и т.п.
            subParams = { "user":[login], "auth":["12345"], "ver":[PWSOC_VERSION], 'geo_info': ['{}'], "isGM": [toint(isGM)] }
            loginAction = LoginAction( subParams, login_callback, self )
            loginAction.auid = auid # чтобы известный нам auid сразу попал на acc={}, создаваемый внутри LoginAction
            loginAction.skipVersionCheck = 1 # для служебного логина не надо проверять версию
            return loginAction.onStart()
        except:
            catch()
    
    # ----------------------------------------------------------------------------------------------
    # по окончанию sublogin юзера -- устраиваем, чтобы по окончанию загрузки пользовательских данных 
    #  выполнился предназначенный для этого юзера play_fin
    def onServerSubLogin(self, sublogin_response):
        info( " sublogin_response=%s" % str(sublogin_response) )
        debug("onServerSubLogin acc.online = %r", self.acc.online)
        if sublogin_response and sublogin_response.get("ok"):
            # юзер успешно залогинен
            uid = toint( sublogin_response.get("uid") )
            acc = users.get( uid )
            if acc:
                acc.online = 0
                self.response["sublogin_ok"] = 1
                self.response["sublogin"] = sublogin_response
                
                # как и в текущем sn_login flow, сначала подписываемся на PS с пустыми данными (потом, после загрузки persistent, сервер отошлет update_game_data, который пофиксит данные)
                self.I.WS.subscribeAccToPersonServer( acc, 0 ) 
                
                if self.persistent_callback:
                    return self.setupPersistentCallback( acc )
                else:
                    # если persistent_callback не указан, на этом заканчиваем с sublogin
                    self.response["ok"] = 1
                    return self.fin()
            else:
                warn("onServerSubLogin: acc not found for uid=%s" % uid)
        # fail:
        elif sublogin_response.get("ws_name", 0): # юзер уже залоган на другом сервере (говорим, на каком)
            ws_name = sublogin_response.get("ws_name")
            self.response["ws_name"] = ws_name
            self.response["ws"] = sublogin_response.get("ws")
            self.response["error"] = "logged on different server (%s)" % ws_name
        
        elif sublogin_response.get("error", "") == "[sql] bad login": # юзер не существует
            self.response["error"] = "no such user"
            
        else:
            self.response["error"] = sublogin_response.get("error", "unknown eror")
            
        if self.persistent_callback:
            # говорим, что пофейлились
            self.persistent_callback( None )

        self.fin()

    def setupPersistentCallback(self, acc):
        if acc.loaded:
            # уже загружен, вызываем callback сразу
            self.persistent_callback( acc )
        else:
            # вешаем callback на получение persistent user data данного аккаунта:
            acc.on_loaded_callbacks = acc.on_loaded_callbacks or []
            acc.on_loaded_callbacks.append( self.persistent_callback )

#----------------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------------
       

class AgentSubloginAction( SubloginActionBase ):
    #----------------------------------------------------------------------------------------------
    # нас просят подтянуть на сервер определенного юзера (вероятно, для каких-то админских действий);
    # при этом мы не уверены, что данные реквизиты snid:snuid именно те, под которыми юзер зареган в кластере; 
    # поэтому сначала спросим у аггрегатора, есть ли такой юзер и какая у него first social network; а уже по реквизитам <fsn.snid>:<fsn.snuid> будем искать юзера в кластере
    #def onAgentSubloginFsn(self):
    @action_timing
    def onStart(self):
        info("AgentSubloginAction.onStart arguments: %r", self.arguments)
        self.wait_persistent = self.getParam("wait_persistent", 0)
        self.pretty = self.getParam("pretty", 0)
        self.isGM = self.getIntParam("isGM", 0)
        if self.checkValidParam("snid"):
            if self.checkValidParam("snuid"):
                self.original_snid = self.snid
                self.original_snuid = self.snuid
                return self.I.AGG.findUser( self.snid, self.snuid, callback=self.onAgentFsnFindUser )
        # fail:
        self.fin()

    @action_timing
    def onAgentFsnFindUser(self, agg_response):
        if self.pretty:
            self.response['onAgentFsnFindUser'] = agg_response
        if agg_response:
            self.auid = toint( agg_response.get("auid", 0) )
            if self.auid:
                return self.I.AGG.getInfo( self.auid, None, include_secure_data=1, callback=self.onAgentFsnGetInfo )
        # fail:
        self.response['onAgentFsnFindUser'] = agg_response
        self.fin()
    
    @action_timing
    def onAgentFsnGetInfo(self, agg_response):
        if self.pretty:
            self.response['onAgentFsnGetInfo'] = agg_response
        if agg_response:
            self.agg_info = agg_response.get('get_info')
            if self.agg_info:
                agg_properties = self.agg_info.get('props') or {}
                fsn_snid = None
                fsn_snuid = None
                fsn = agg_properties.get('fsn')
                fsn_snid, fsn_snuid, dummy = pwaccount.FindSocialNetworkInfo(self.agg_info, fsn)
                if fsn_snid and fsn_snuid:
                    if fsn is None:
                        self.I.AGG.setProperty( self.auid, 'fsn', fsn_snid ) 
                    self.response["fsn_snid"] = fsn_snid
                    self.response["fsn_snuid"] = fsn_snuid
                    self.login = str("%s#%s" % ( fsn_snid, fsn_snuid ))
                    if self.wait_persistent:
                        return self.subLogin( self.login, persistent_callback=self.onAgentSubloginPersistentLoaded, auid=self.auid, isGM=bool(self.isGM) )
                    else:
                        return self.subLogin( self.login, auid=self.auid, isGM=bool(self.isGM) ) # onServerSublogin сам справится с возвратом response[] и self.fin()
        # fail:
        self.response['onAgentFsnGetInfo'] = agg_response
        self.fin()
                    
    #----------------------------------------------------------------------------------------------
    # часть параметров получаем неявно, через self.auid, self.agg_info
    @action_timing
    def onAgentSubloginPersistentLoaded(self, acc):
        #self.I.WS.dumpAccount(acc, "onAgentSubloginPersistentLoaded")
        if acc:
            acc.auid = self.auid
            acc.agg_info = self.agg_info
            acc.original_snid = self.original_snid
            acc.original_snuid = self.original_snuid
            
            if not acc.userlocale:
                acc.userlocale = acc.model.LordInfo.UserLocale

            # здесь надо перепилить разную социальную инфу, чтобы была достаточно полная реплика аккаунта "после обычного sn_login" 
            # (чтобы при загрузке нормально отработали conversion scripts)
            acc.sn_count, acc.sn_count_prev, acc.new_networks = helperCheckSocialNetworkCount(self.agg_info)
            
            self.I.WS.dumpAccount(acc, "onAgentSubloginPersistentLoaded(+agg_info)")
            debug("onAgentSubloginPersistentLoaded acc.online = %r", self.acc.online)
            # зарегистрируем биллинг (нужно получить баланс, т.к. личный кабинет может захотеть исполнять команды за бабло)
            onBalanceCallback = functools.partial(self.onAgentSubloginBalanceLoaded, acc=acc)
            self.I.BILL.initBilling( self.auid, callback=onBalanceCallback )
        else:
            warn("onAgentSubloginPersistentLoaded: failed acc for login=%s:%s" % (self.snid, self.snuid))
        
    #----------------------------------------------------------------------------------------------
    def onAgentSubloginBalanceLoaded(self, billing_response, acc=None):
        info( "onAgentSubloginBalanceLoaded: auid=%s" % acc.auid )
        # Баланс пишем только если мы не в замке ( PF-77305 )
        if hasattr( self, "isAccInCastle" ) and not self.isAccInCastle:
            acc.model.updateBalanceInfo(acc, self.I.BILL)

        self.response["ok"] = 1
        self.response["fraction"] = acc.db.fraction
        self.response["rating"] = acc.db.rating
        self.response["uid"] = acc.uid
        self.response["key"] = acc.key
        self.fin()

