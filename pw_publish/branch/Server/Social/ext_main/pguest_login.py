# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# Social Aggregator Login
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging, base64

# чтобы питон правильно понимал относительные пути модулей:
def _addPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)

_addPath('..')
from handlers import * # JsonHandler, globals: peers, users..
from subaction import SubAction, action_timing
from instr import * 

import iaggregator

from login import BaseCheckVersionAction, LoginAction
from geo_cfg import DEFAULT_GEO_LOCATION

##-------------------------------------------------------------------------------------
##-------------------------------------------------------------------------------------


class PersistentGuestLoginAction( BaseCheckVersionAction ):
    """ Cлужебный handler, для тестового логина в режиме persistent guest """
    action = "pguest_login"
    
    @action_timing
    def onStart(self):
        info( "PersistentGuestLoginAction.onStart" )
        self.login = self.getParam("login")
        
        self.client_ver = self.getParam("ver", self._DEFAULT_VERSION)
        self.testkey = self.getIntParam("testkey")
        self.testkeypass = self.getIntParam("testkeypass")
        self.key = self.getParam("key", "") # позволяем подхватить прошлую сессию, если она еще активна
        self.sex = self.getIntParam("sex", 1) # позволяем задавать guest-у произвольный пол
        self._dont_log = options._dont_log
        
        self.response["ver"] = PWSOC_VERSION
        self.response["_depth"] = DEPTH_WS
        
        try:
            remote_ip = self.request.request.remote_ip
            location, aux_info = self.I.GEO.getLocationInfoByIP(remote_ip)
            info( "remote_ip: %s, location: %s, aux_info: %s" % (remote_ip, location, aux_info) )
            self.geolocation = utf8convert( unicode(location, "latin1") ) 
            self.geo_info = str(aux_info)
        except:
            info( "can't get location by IP: set default (%s)" % (DEFAULT_GEO_LOCATION) )
            self.geolocation = DEFAULT_GEO_LOCATION
            self.geo_info = ""

        # -- geolocation -----------------------------
        self.response["geolocation"] = self.geolocation
        self.response["geo_info"] = self.geo_info
        
        if self.checkClientVersion(): 
            ## аналогично sn_login, обращаемся к SocialAggregator (оттуда придет отлуп, конечно, но нам и неважно)
            return self.subLogin()
                
        #-- FAIL: отвечаем юзеру
        self.fin()            
    
    
    #------------------------------------------------------------------------------------
    # стартуем sublogin (нормальный гестовый login должен уже лежать в self.login)
    def subLogin(self):
        if self.login:
            subParams = { "user":[self.login], "auth":["0"], "_allow_guest_relogin_":[1], "key":[self.key], "sex":[self.sex],
                "testkey":[self.testkey], "testkeypass":[self.testkeypass], "ver":[self.client_ver] }
            loginAction = LoginAction( subParams, self.onReLogin, self )
            return loginAction.onStart()
        else:
            # логин не указан, так что сразу просим сделать нового guest-юзера
            subParams = { "guest":[1], "sex":[self.sex], "key":[self.key], "testkey":[self.testkey], "testkeypass":[self.testkeypass], "ver":[self.client_ver] }
            loginAction = LoginAction( subParams, self.onNewGuestLogin, self )
            return loginAction.onStart()
    
    
    #------------------------------------------------------------------------------------
    # получили ответ на sublogin ( обычный питоновский response[] )
    @action_timing
    def onReLogin(self, sublogin_response):
        info( "PersistentGuestLoginAction: onReLogin response %s" % str(sublogin_response) )
        self.response["sublogin_response"] = sublogin_response
        self.addResponseTiming(sublogin_response)
        if sublogin_response and sublogin_response.get("ok"):
            # юзер успешно залогинен, можно отвечать обычным auth
            self.response["ok"] = 1
            self.uid = sublogin_response.get("uid")
            self.response["uid"] = self.uid 
            self.response["key"] = sublogin_response.get("key")
            
            self.acc = users.get(self.uid)
            self.acc.online = 1
            
        elif sublogin_response.get("ws", 0) or sublogin_response.get("error", "") == "already logged":
            # 1) юзер уже залоган (на другом рабочем сервере) 
            self.response["error"] = "already logged"
            self.response["ec"] = EC.ALREADY_LOGGED
            
        self.fin()
            
    #------------------------------------------------------------------------------------
    # получили ответ на new guest login ( обычный питоновский response[] )
    @action_timing
    def onNewGuestLogin(self, sublogin_response):
        info( "PersistentGuestLoginAction: onNewGuestLogin response %s" % str(sublogin_response) )
        self.response["sublogin_response"] = sublogin_response
        self.addResponseTiming(sublogin_response)
        if sublogin_response and sublogin_response.get("ok"):
            # юзер успешно залогинен, можно отвечать обычным auth
            self.uid = sublogin_response.get("uid")
            self.response["uid"] = self.uid 
            self.key = sublogin_response.get("key")
            self.response["key"] = self.key
            
            self.acc = users.get(self.uid)
            if self.acc:
                self.login = self.acc.login
                return self.I.SQL.addNewLogin( self.uid, self.login, "persistent_guest", options.server_id, callback=self.onNewLoginAdded )
                
        # fail new guest login:
        self.fin()
            

    #------------------------------------------------------------------------------------
    # в БД создался новый login; теперь можно снимать признак guest
    @action_timing
    def onNewLoginAdded(self, sql_reply):
        self.acc = users.get(self.uid)
        if self.acc:
            self.acc.online = 1
            self.acc.guest = 0 # снимаем признак "guest", теперь это нормальный сохраняемый юзер
            return self.subLogin() # и вот теперь логаемся нормально, с регистрацией в memcache и sql

        # fail:
        self.fin()
