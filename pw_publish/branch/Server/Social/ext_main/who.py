# -*- coding: utf-8 -*-
#
# Social Aggregator Login

import sys, os, time, logging

from handlers import *
from subaction import SubAction, action_timing, parseGeoLocation

import cfg

from login import BaseCheckVersionAction
from instr import * 
from pwc_actions import PWConnectWhoAction 

import EC
import CC                                 

from LoginUser import User

import pwaccount

##-------------------------------------------------------------------------------------
##-------------------------------------------------------------------------------------

class WhoAction( BaseCheckVersionAction ):
    " Cлужебный handler, поддерживает action 'who' и 'l_who'. "
    @action_timing
    def onStart(self):
        self.sn_id = self.getParam("snid", "")
        self.sn_uid_original = self.getParam("snuid", "")
        self.sn_token_original = self.getParam("sntoken", "")
        self.snrefresh_token = self.getParam("snrefresh_token", "")
        self.hostid = self.getParam("hostid", "")
        self.muid = self.getParam("muid", "")
        self.ruid = self.getParam("ruid", "")
        self.locale = str(self.getParam("locale", cfg.MATCHMAKER_DEFAULT_LOCALE)).upper()
        self.nocbt = self.getIntParam("nocbt", 0)
        self.primary = self.getIntParam("primary", 0)
        self.zul_sec = (self.sn_id == 'zzma') and self.getBoolParam("securetoken", False) # PF-91646

        self.client_ver = self.getParam("ver", self._DEFAULT_VERSION)
        self._dont_log = options._dont_log
        
        self.registering = False
        # храним fsn в self для случая регистрации, когда мы не ждем 
        # ответ от аггрегатора о сохранении
        # см. self.I.AGG.setProperty( self.auid, 'fsn'...
        # D.Lavrentyuk: при этом заменяем 'pwe' на 'pwc', потому что агрегатор не знает 'pwe'
        self.fsn = 'pwc' if self.sn_id == 'pwe' else self.sn_id

        self.response["ver"] = PWSOC_VERSION
        self.response["_depth"] = DEPTH_WS
        self.response["iscaptcha"] = False
        if self.sn_id == 'st':
            self.sn_token = self.RecodeSteamToken(self.sn_token_original)
            self.sn_uid = self.sn_uid_original
        elif self.sn_id == 'gmg':
            self.sn_token = self.FixGamigaToken(self.sn_token_original)
            self.sn_uid = self.FixGamigaSnuid(self.sn_uid_original)
        else:
            self.sn_token = self.sn_token_original
            self.sn_uid = self.sn_uid_original

        try:
            headers = self.request.headers    
        except:
            headers = self.request.request.headers    

        self.remote_ip = headers.get("X-Real-IP", "")

        info( "headers: %s" % str(headers) )
        self.geolocation, self.geo_info = parseGeoLocation(self.I.GEO, self.sn_uid, self.remote_ip)

        if self.checkClientVersion( hi_med_only=True ): 
            if self.sn_uid and (not re.search( CC.SOCAGG_LOGIN_CHECK_EX, self.sn_uid )):
                if self.sn_id and self.sn_id == CC.PWCONNECT_LAUNCHER_SNID:
                    # PW Connect
                    original_params = self.getFlatParams() # копия исходных параметров запроса, для проверки подписи
                    info("l_who original params: %s" % original_params) 
                    subParams = ClassDict( email_md5=[self.sn_uid], _params=[original_params], primary=[self.primary] )
                    subAction = PWConnectWhoAction( subParams, self.onPwcWho, I=self.I )
                    subAction.request = self.request
                    subAction.onStart()
                    return # wait for async reply
                    
                elif self.checkPossibleValue( self.sn_id, CC.AGG_SOCIAL_NETWORK_NAMES, error="bad snid" ):
                    if self.checkSnToken(self.sn_id, self.sn_token):
                        ## логинимся через SocialAggregator (sntoken нам дали в открытом виде)
                        self.I.AGG.login(self.sn_uid, self.sn_token, self.sn_id, False, self.snrefresh_token,
                                         callback=self.onAggregatorLogin,
                                         referral=self.getReferral(),
                                         zul=self.zul_sec)
                        return # wait for async reply
                    else:
                        info( "bad sntoken: %r" % self.sn_token )
                        return self.markLoginFailed("bad sntoken", EC.AGGREGATOR_LOGIN_FAIL)
                else:
                    return self.markLoginFailed("bad sn", EC.AGGREGATOR_LOGIN_FAIL)
            else:
                return self.markLoginFailed("bad snuid", EC.AGGREGATOR_LOGIN_FAIL)
        #-- FAIL: отвечаем юзеру
        self.fin()


    #------------------------------------------------------------------------------------
    def getReferral(self):
        return '%s/%s' % (self.locale, self.geolocation)

    #------------------------------------------------------------------------------------
    @action_timing
    def onPwcWho(self, response):
        # тупо сливаем вместе: то, что у нас самих есть в response, и то, что ответил PWConnect
        self.response.update( response )
        self.addResponseTiming( response )
        if response.get("ok", 0):
            self.response["ok"] = 0 # нужно еще получить нормальную инфу от аггрегатора; если он не знает такого auid, тогда fail (pwconnect может зарегать юзера, а СА пофейлить)
            self.sn_id = CC.PWCONNECT_AGGREGATOR_SNID
            self.sn_uid = str( response.get("pwc_snuid", "") )
            self.auid = tolong( response.get("auid", 0) )
            return self.I.AGG.getInfo(self.auid, None, include_secure_data=1,
                                      callback=functools.partial(self.onAggregatorGetInfo, pwc=True))
        #fail:
        self.fin()
    
    #------------------------------------------------------------------------------------
    # Social Aggregator ответил на авторизацию
    @action_timing
    def onAggregatorLogin(self, reply): # reply теперь приходит сразу распарсенный до dict-содержимого
        if not reply:
            return self.markLoginFailed('no aggregator reply', EC.AGGREGATOR_LOGIN_FAIL)
        try:
            info( "WhoAction.onAggregatorLogin: %s" % str(reply) )
            http_error = reply.get('http_error', '')
            reason = reply.get("message", '')
            ecode = reply.get("error", 0)
            if ecode > 0 or reason or http_error:
                if ecode != 8: # soc agr user not found  
                    return self.markLoginFailed("aggregator login fail (code=%d reason=%r http_error=%r)" % (ecode, reason, http_error), EC.AGGREGATOR_LOGIN_FAIL)
                elif not self.registering:
                    self.registering = True
                    return self.I.AGG.register( self.sn_uid, self.sn_token, self.sn_id, self.snrefresh_token,
                                                callback=self.onAggregatorLogin,
                                                referral=self.getReferral(),
                                                zul=self.zul_sec, ruid=self.ruid)
                else:
                    return self.markLoginFailed("aggregator registration fail (code=%d reason=%r http_error=%r)" % (ecode, reason, http_error), EC.AGGREGATOR_LOGIN_FAIL)
            else:
                self.auid = reply.get("auid", None)
                if self.auid != None:
                    if self.registering: 
                        self.I.STATS.addSocialRegister( str(self.hostid), str(self.auid), str(self.sn_id), str(self.sn_uid), str(self.muid), str(self.ruid) )

                        # прошла успешная регистрация в аггрегаторе
                        # и отмечаем, что событие регистрации отправлено
                        self.I.AGG.setProperty( self.auid, 'reg', 1 ) 
                        # проставляем fsn, но не ждем callback
                        # дальше будем использовать fsn, который сохранен в self
                        self.I.AGG.setProperty( self.auid, 'fsn', self.fsn ) 
                        self.response["registered"] = 1
                        
                    # заодно давайте выкачаем из соц.сети user info
                    return self.I.AGG.getInfo( self.auid, None, include_secure_data=1, callback=self.onAggregatorGetInfo )
                else:
                    return self.markLoginFailed("aggregator auid not defined", EC.AGGREGATOR_LOGIN_FAIL)
        except:
            message = catch()
            agg_error = reply.get("error", 0)
            if agg_error:
                self.response['agg_error'] = agg_error 
            return self.markLoginFailed(message, EC.AGGREGATOR_LOGIN_FAIL)
        return self.markLoginFailed("aggregator login fail", EC.AGGREGATOR_LOGIN_FAIL)

    #------------------------------------------------------------------------------------
    # вытаскиваем всяческие свойства из reply и укладываем в user
    def parseAggregatorSocialInfo(self, reply, user):
        info( "parseAggregatorSocialInfo: reply %s" % str(reply) )

        user.remote_ip = self.remote_ip
        user.geolocation = self.geolocation
        user.geo_info = self.geo_info
        # don't set original credentials if already set
        original_snid = getattr(user, 'original_snid', None)
        original_snuid = getattr(user, 'original_snuid', None)

        if original_snid is None or original_snuid is None:
            user.original_snid = self.sn_id    
            user.original_snuid = self.sn_uid    
            info( "parseAggregatorSocialInfo: original credentials set (snid=%r snuid=%s)" % (user.original_snid, user.original_snuid))

        linfo = {}
        try:
            agg_info = reply.get("get_info") or {}
            if agg_info:
                agg_properties = agg_info.get('props') or {}
                # если аггрегатор не прислал fsn используем сохраненный и ругаемся
                if 'fsn' not in agg_properties:
                    warn('aggregator response doesnt contains fsn key. using cached value=%r'%self.fsn)
                user.fsn = agg_properties.get('fsn', self.fsn)
                if user.fsn is not None:
                    user.snid = user.fsn
                    user.snuid = agg_info[user.fsn]['snuid']
                else:
                    warn('user.fsn is None, probably it may affect pw launcher')
                    user.snid = self.sn_id
                    user.snuid = self.sn_uid
                    
                user.registered = agg_properties.get('reg', 0) or self.registering

                gender = agg_info[user.snid].get("gender", None)
                if gender != None:
                    user.sex = toint( gender )

                user.photo = agg_info[user.snid].get("photo", None)
                
                user.nick = utf8convert( agg_properties.get('nick', CC.NICK_EMPTY) )
                if user.nick == CC.NICK_EMPTY:
                    user.nick = ""
                    
                user.sn_nick = utf8convert( agg_info[user.snid].get('name', "") or user.sn_nick )
                active_nick = user.nick or user.sn_nick

                user.fraction = agg_properties.get('fraction', None)

                user.registration_date = toint(agg_info["dt_register"])

                user.auid = self.auid
                user.locale = self.locale
                
                user.secret = md5(self.sn_token_original)
                
                # заодно закешируем количество зарегистрированных соц.сетей
                self.checkSocialNetworkCount( agg_info )
                user.sn_count = self.sn_count
                user.sn_count_prev = self.sn_count_prev
                user.restriction_ok = 0

                fame = agg_properties.get('fame', None)
                if fame:
                    linfo["fame"] = fame

                linfo["auid"] = str(self.auid) # ланчеровский JavaScript не съест int64, так что строкой
                linfo["sex"] = user.sex
                linfo["nick"] = active_nick or CC.NICK_EMPTY

                if user.fraction:
                    linfo["fraction"] = user.fraction
                    
                sns = {}
                sn_pairs = [ utf8convert( "ni:%s" % user.auid) ]
                for name in CC.LOGIN_SOCIAL_NETWORK_NAMES:
                    items = agg_info.get(name)
                    if items:
                        snuid = pwaccount.ParseSnuid(name, items)
                        # если в основной соц.сети нет аватарки, берем первую непустую
                        sn_photo = items.get('photo')
                        if sn_photo and (not user.photo):
                            user.photo = sn_photo
                            
                        if snuid:
                            sns[name] = snuid
                            # в случае, если работаем со списком допущенных юзеров (напр. Test Realm), нужно будет проверить, нет ли данных реквизитов в списке допуска 
                            sn_pair = utf8convert( "%s:%s" % (name, snuid) )
                            sn_pairs.append( sn_pair )
                        else:
                            return self.markLoginFailed('no snuid found (sn=%s)' % name, EC.AGGREGATOR_LOGIN_FAIL)

                user.sns = sns
                user.sn_pairs = sn_pairs
                
                # для случая PWC нужно прикопать на токене pwc_snuid (иначе трудно потом узнать его в случае, когда fsn != pwc)
                user.pwc_snuid = sns.get( CC.PWCONNECT_AGGREGATOR_SNID )
                info("auid=%s, pwc_snuid=%r" % (self.auid, user.pwc_snuid))
                
                if user.photo:
                    linfo["photo"] = user.photo

                self.response['sns'] = sns
                self.response['fsn'] = user.fsn
                self.response["uid"] = str(user.snuid)
                
            else:
                return self.markLoginFailed("no aggregator properties", EC.AGGREGATOR_LOGIN_FAIL)

        except:
            catch()
            return self.markLoginFailed("no aggregator properties", EC.AGGREGATOR_LOGIN_FAIL)
        
        return linfo
        

    #------------------------------------------------------------------------------------
    # Аггрегатор ответил на getInfo (можем вытащить пол игрока, никнейм, фото и проч.)
    @action_timing
    def onAggregatorGetInfo(self, reply, pwc=False): # reply теперь приходит сразу распарсенный до dict-содержимого
        if not reply:
            return self.markLoginFailed('no aggregator reply', EC.AGGREGATOR_LOGIN_FAIL)
        try:
            info("onAggregatorGetInfo(pwc=%s): response %s", pwc, str(reply))

            if pwc:
                # token у нас должен быть уже заведен
                user = self.I.WS.loginCache.get(str(self.auid)).user
            else:
                user = User()
                user.muid = self.muid
                user.ruid = self.ruid

            linfo = self.parseAggregatorSocialInfo(reply, user)

            if linfo:
                if pwc:
                    self.response['info'].update( linfo )
                else:
                    self.response['info'] = linfo
                return self.checkUserRestrictions( user, registerToken=(not pwc) )
            else:
                # при markLoginFailed возвращает None
                return

        except:
            message = catch()
            agg_error = reply.get("error", 0)
            if agg_error:
                self.response['agg_error'] = agg_error
            return self.markLoginFailed(message, EC.AGGREGATOR_LOGIN_FAIL)
        #fail
        self.fin()

    #------------------------------------------------------------------------------------
    def checkUserRestrictions(self, user, registerToken=True):
        if cfg.RESTRICT_FACEBOOK_USERS and (not self.nocbt):
            ## TEST REALM RESTRICTIONS: pre-registered social network users only!
            _callback = functools.partial( self.onSqlCheckUserRestrictions, user=user, registerToken=registerToken )
            self.I.SQL.cbtCheckUserRestrictions( user.sn_pairs, _callback )
        else:
            return self.checkLocationAndIpRestrictions(user, registerToken)

    def _onSqlCheckUserRestrictions(self, cc, ce, sql_reply, user=None, registerToken=True):
        try:
            info("onSqlCheckUserRestrictions2 sql_reply: %s" % sql_reply)
            r = sql_reply["r"]
            if r:
                user.restriction_ok = 1
                return self.successReply( user, registerToken )
        except:
            pass
        # fail:
        self.markLoginFailed( cc, ce )

    def onSqlCheckUserRestrictions(self, sql_reply, user=None, registerToken=True):
        self._onSqlCheckUserRestrictions(CC.TEXT_NOT_A_REGISTERED_AP_USER, EC.NOT_A_REGISTERED_AP_USER, sql_reply, user, registerToken)

    #------------------------------------------------------------------------------------
    def checkLocationAndIpRestrictions(self, user, registerToken=True):
        if cfg.RESTRICT_LOCATIONS and (not self.nocbt):
            if user.geolocation in cfg.RESTRICT_LOCATIONS_ALLOWED:
                return self.successReply(user, registerToken)
            else:
                _callback = functools.partial( self.onSqlCheckLocationAndIpRestrictions, user=user, registerToken=registerToken )
                self.I.SQL.cbtCheckIpAllowances( user.remote_ip, _callback )
        else:
            return self.successReply(user, registerToken)

    def onSqlCheckLocationAndIpRestrictions(self, sql_reply, user=None, registerToken=True):
        try:
            info("onSqlCheckLocationAndIpRestrictions sql_reply: %s" % sql_reply)
            r = sql_reply["r"]
            if r:
                user.restriction_ok = 1
                return self.successReply( user, registerToken )
        except:
            pass
        # trying to check for auid, otherwise already checked
        if not cfg.RESTRICT_FACEBOOK_USERS:
            _callback = functools.partial( self.onSqlCheckUserRestrictions2, user=user, registerToken=registerToken )
            self.I.SQL.cbtCheckUserRestrictions( user.sn_pairs, _callback )
        else:            
            # fail:
            self.markLoginFailed( CC.TEXT_NOT_A_ALLOWED_AP_USER, EC.NOT_A_ALLOWED_AP_USER )


    def onSqlCheckUserRestrictions2(self, sql_reply, user=None, registerToken=True):
        self._onSqlCheckUserRestrictions(CC.TEXT_NOT_A_ALLOWED_AP_USER, EC.NOT_A_ALLOWED_AP_USER, sql_reply, user, registerToken)

    #------------------------------------------------------------------------------------
    def successReply(self, user, registerToken):
        if registerToken:
            token = self.I.WS.registerLogin(str(self.auid), user, primary=self.primary, registering=self.registering)
            if token is None:
                self.response["error"] = "error registering login"
                self.response["ec"] = EC.AUTH_REGISTER_LOGIN_FAILED
                self.fin()
                return 
            self.response['token'] = token
        if self.primary:
            self.I.AGG.markLastLogin(self.auid)
        if user.fsn:
            self.response["ok"] = 1
            self.fin()
        else:
            return self.I.AGG.setProperty(self.auid, 'fsn', self.sn_id, self.onAggregatorSave)
        
    #------------------------------------------------------------------------------------
    @action_timing
    def onAggregatorSave(self, reply): 
        if not reply:
            return self.markLoginFailed('no aggregator reply', EC.AGGREGATOR_LOGIN_FAIL)
        agg_error = reply.get("error", 0)
        try:
            info( "onAggregatorSave: response %s" % str(reply) )
            if agg_error == 0:
                self.response["ok"] = 1
        except:
            message = catch()
            if agg_error:
                self.response['agg_error'] = agg_error
            return self.markLoginFailed(message, EC.AGGREGATOR_LOGIN_FAIL)
        self.fin()
        
        
class SetSteamGenderAction( BaseCheckVersionAction ):
    """ Cлужебный handler, поддерживает 'action=l_set_gender'. """
    @action_timing
    def onStart(self):  
        info( "SetSteamGenderAction.onStart: AGG=%s" % self.I.AGG )
        self.sn_id = self.getParam("snid")
        self.auid = self.getParam("auid")
        self.gender = self.getIntParam("gender", None)
        
        if self.gender and self.sn_id in ['st', 'ae']:  
            self.I.AGG.setGender( self.auid, self.sn_id, self.gender )
            self.I.WS.setLoginGender(self.auid, self.gender)
            
        self.response["ok"] = 1
        self.fin()
            

class AddUserAction( SubAction ):
    
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        data = json.loads(self.request.request.body)
        #warn("AddUserAction data: %s", data)
        user = User()
        user.fromJson(data)
        #warn("AddUserAction: user.auid %s %r", type(user.auid), user.auid)
        info('Added user (auid=%s snid=%r original_snid=%r muid=%r ruid=%r)', user.auid, user.snid, user.original_snid, user.muid, user.ruid)

        token = self.getParam("token")
        primary = self.getIntParam("primary", 0)
        self.I.WS.registerLogin(str(user.auid), user, token, primary=primary)
        nsecret = md5(token)
        info('Recalculating secret (old=%r new=%r)', user.secret, nsecret)
        user.secret = nsecret
        if user.pwconnect and user.pwc_data:
            user.pwc_data['challenge'] = token
            user.pwc_data['secret'] = user.secret
            self.I.WS.pwc[ str(user.pwc_data['pwc_snuid']) ] = ClassDict(user.pwc_data)
        self.response["ok"] = 1
        self.fin()
