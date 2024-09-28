#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging, ast

from base.helpers import *
from base.exceptions import DisplaceLoginError, BadModelDataError
from isql import info_sql_callback
from handlers import * # JsonHandler, globals: peers, users..
from subaction import SubAction, action_timing, separate_timing
from instr import *
from modeldata.ModelData import ModelData

import base64

import imemcache

import MM
import EC
import CC

from pwaccount import UserAccount
import pwaccount
from enums import *
##---------------------------------------------------------------------------------------------------
## mc helpers
def _login_key(login):
    return "login_" + str(login)

def _login_data(server_id, uid, pwd, admin):
    return "%d:%s:%s:%d" % ( server_id, str(uid), str(pwd), toint(admin) )
    
def _parse_login_data(login_data):
    try:
        server_id, uid, pwd, admin = login_data.split(":")
        return toint(server_id), toint(uid), pwd, toint(admin)
    except:
        return 0, 0, "", 0
        
def make_login_unlock(login, uid, pwd, admin):
    return _login_key( login ), _login_data( 0, uid, pwd, admin ) 

DONT_LOG_RELOGIN = 2

##-------------------------------------------------------------------------------------
##-------------------------------------------------------------------------------------

# посчитаем, на сколько соц.сетей мы подписаны (хочется вызывать эту штуку из других классов)
def helperCheckSocialNetworkCount(agg_info):
    sn_count = 0
    new_networks = []
    for sn in CC.BONUS_SOCIAL_NETWORK_NAMES:
        sn_dict = agg_info.get(sn)
        if sn_dict and sn_dict.__class__ == dict:
            sn_count += 1
            if "new" in sn_dict:
                new_networks.append(sn)
    # и какое кол-во отмечено в аггрегаторе (если будем подписаны > чем на одну сеть, выдадим бонусные таланты)
    agg_properties = agg_info.get("props") or {}
    sn_count_prev = toint( agg_properties.get(CC.SN_BONUS_PROPERTY, 0) ) # больше не пропускаем 1-ю по порядку соц.сеть
    return sn_count, sn_count_prev, new_networks
    
        
##-------------------------------------------------------------------------------------
##-------------------------------------------------------------------------------------
class BaseCheckVersionAction( SubAction ):

    #------------------------------------------------------------------------------------
    def RecodeSteamToken(self, token):
        try:
            token = base64.urlsafe_b64decode(token)
            ticket = ''
            for i in token:     
               ticket += "%02X" % (ord(i))
            return ticket
        except Exception, details:
            warn('Error recoding Steam token:' + str(details))
            return None

    def FixGamigaToken(self, token): # PF-95587
        "Fixes '+' sign, replaced for ' ' by Tornado"
        return token.replace(' ', '+')

    def FixGamigaSnuid(self, snuid): # PF-95587
        "Fixes '+' sign, replaced for ' ' by Tornado"
        return snuid.lower()

    def checkClientVersion(self, hi_med_only=False):
        ver_ok = False
        try:
            #DEBUG: кривая подпорка для старого формата VERSION, присылаемого из ланчера (там 3 цифры вместо 4)
            split_ver = self.client_ver.split(".")
            if len(split_ver) == 3:
                self.client_ver += ".0"
                split_ver.append("0")
                
            hi, med, low, revn = split_ver[:4]
            if toint(hi) == PWSOC_VERSION_HIGH and toint(med) == PWSOC_VERSION_MED and (hi_med_only or (toint(low) == PWSOC_VERSION_LOW)):
                REVN_LIST = getattr(cfg, "CLIENT_REVISIONS", [])
                if (not REVN_LIST) or (toint(revn) in REVN_LIST):
                    ver_ok = True
                else:
                    self.response["error"] = "bad client revision (%s)" % ( revn )
                    self.response["ec"] = EC.BAD_CLIENT_VERSION
            elif self.client_ver.startswith(self._DEFAULT_VERSION) and (not options.strict_login_check):
                ver_ok = True
                self.response["warning"] = "development client (ver 0.0.0), non-strict login"
            elif PWSOC_VERSION.startswith(self._DEFAULT_VERSION):
                ver_ok = True
                self.response["warning"] = "development server (ver 0.0.0), non-strict login"
            else:
                self.response["error"] = "client version mismatch (client = %s, server = %s)" % ( self.client_ver, PWSOC_VERSION )
                self.response["ec"] = EC.BAD_CLIENT_VERSION
        except:
            self.response["error"] = "bad version format";
            self.response["ec"] = EC.BAD_CLIENT_VERSION_FORMAT
            
        return ver_ok
        
    # -----------------------------------------------------
    def checkSocialNetworkCount(self, agg_info):
        # посчитаем, на сколько соц.сетей мы подписаны
        self.sn_count, self.sn_count_prev, self.new_networks = helperCheckSocialNetworkCount(agg_info)
        info("checkSocialNetworkCount: sn_count_prev=%s" % self.sn_count_prev)

    #------------------------------------------------------------------------------------
    def updateSocialNetworkCount(self, auid):
        info( "updateSocialNetworkCount: auid=%s" % auid )
        self.update_auid = toint(auid)
        if self.update_auid:
            self.I.AGG.getInfo( self.update_auid, None, include_secure_data=1, callback=self.onSocialNetworkCount )
    
    #------------------------------------------------------------------------------------
    # Аггрегатор ответил на getInfo (можем вытащить пол игрока, никнейм, фото и проч.)
    @action_timing
    def onSocialNetworkCount(self, reply): # reply теперь приходит сразу распарсенный до dict-содержимого
        info( "onSocialNetworkCount: auid %s, response %s" % (self.update_auid, str(reply)) )
        try:
            agg_info = reply.get("get_info")
            agg_properties = agg_info.get('props') or {}

            # закешируем количество зарегистрированных соц.сетей
            self.checkSocialNetworkCount( agg_info )
            self.I.WS.setSnBonusCount( self.update_auid, self.sn_count, self.sn_count_prev, self.new_networks )
            self.response['update_auid'] = self.update_auid
            self.response['sn_count'] = self.sn_count
            self.response['sn_count_prev'] = self.sn_count_prev
            self.response['new_networks'] = self.new_networks
        except:
            catch()
        self.fin()

    #------------------------------------------------------------------------------------
    def markLoginFailed(self, message, code):
        info( "markLoginFailed: ec=%s, message=%s",code, message )
        self.response["error"] = message
        self.response["ec"] = code
        self.fin()


    def checkLoginSymbols(self, snid, snuid, sntoken):
        if not(snuid) or re.search(CC.SOCAGG_LOGIN_CHECK_EX, snuid):
            return False
        if self.checkPossibleValue(snid, CC.LOGIN_SOCIAL_NETWORK_NAMES, error="bad snid"):
            if self.checkSnToken(snid, sntoken):
                return True
        return False

    def checkSnToken(self, snid, sntoken): # beware: not used in AlienLoginAction!
        if not sntoken:
            return False
        if snid == 'arc' or snid == 'gmg': #PF-95292
            return True # PF-95103 - no token symbols check for 'arc'
        return not re.search(CC.SOCAGG_TOKEN_CHECK_EX, sntoken) # только hex символы?



class LoginAction( BaseCheckVersionAction ):
    action = "login"
    DEFAULT_KEY = "12345"
    
    """ Cлужебный логический handler, поддерживает единственный 'action=login'. """
    @action_timing
    def onStart(self):
        info("LoginAction.onStart %r", self.arguments)
        self.login = self.getParam("user")
        self.auth = self.getParam("auth")
        self.client_ver = self.getParam("ver", self._DEFAULT_VERSION)
        self.guest = self.getIntParam("guest", 0)
        self.userlocale = self.getParam("userlocale")
        self.isGM = self.getIntParam("isGM", 0)
        self.rid = self.getIntParam("rid",0)
        self.country_code = None
        self.geo_info = {}
        try:
            self.geo_info = ast.literal_eval(self.getParam("geo_info"))
            if self.geo_info:
                self.country_code = self.geo_info.get("country_code", None)
        except Exception:
            info("LoginAction.onStart failed to parse geo_info. Raw geo_info value: %r", self.arguments.get("geo_info"))
        # TODO: PF-86214, Чит для проверки Американского туториала, убрать после того, как таск проверят!
        if cfg.COORDINATOD_PREDEFINED_LOCALES is not None and self.login in cfg.COORDINATOD_PREDEFINED_LOCALES:
            self.country_code = cfg.COORDINATOD_PREDEFINED_LOCALES[self.login]
        info("CountryCode: %r", self.country_code)
        self.testkey = self.getIntParam("testkey")
        # слегка закроемся от случайного попадания опции testkey=1 в релизные билды клиента, дополнительной проверкой пароля
        self.testkeypass = self.getIntParam("testkeypass")
        cfgpass = getattr(cfg, "TESTKEYPASS", 0)
        ##warn( "[testpass]: self.testkeypass=%s, cfgpass=%s, mashed=%s" % (self.testkeypass, cfgpass, self.testkeypass ^ 1234567890) )
        if (not self.testkeypass) or (not cfgpass) or ((self.testkeypass ^ 1234567890) != cfgpass):
            ##warn( "[testpass]: fail" )
            self.testkey = 0            
            
        self.key = self.getParam("key", "") # позволяем подхватить прошлую сессию, если она еще активна        
        self.nick = ""
        self.sn_nick = ""
        
        self.locale = str(self.getParam("locale", cfg.MATCHMAKER_DEFAULT_LOCALE)).upper()
        
        if self.guest:
            # Турнирный сервер - только по билетам
            if cfg.TOURNAMENT_SERVER:
                self.response["ec"] = EC.TOURNAMENT_TICKET_NOT_BUY
                self.response["error"] = "Ticket not buyed"
                self.fin()
                return

            self.nick = "guest"
            self.sn_nick = "sn_guest"
            self.login = "guest"
            self.auth = "0"
            self.admin = 0
            sex = self.getIntParam("sex", 1)
            if sex == 2:
                self.sex = MM.ESex.FEMALE
            else:
                self.sex = MM.ESex.MALE
       
        self._dont_log = options._dont_log
        self.relogin = 0
        
        self.response["ver"] = PWSOC_VERSION
        #TODO:LOFIK:ENCIPHER_TRAFFIC
        #if cfg.ENCIPHER_TRAFFIC:
        #  self.response["encipher"] = 1
        self.response["_depth"] = DEPTH_WS
        
        login_check_ex = "[^0-9A-Za-z_.\=\-@]" # только символы, допустимые в именах
        if getattr(self.request, "allow_login_underscores", 0):
            login_check_ex = "[^0-9A-Za-z_.\=\-@#]" # разрешаем и спец.символ #
        
        if self.getParam("_allow_guest_relogin_", 0):
            login_check_ex = "[^0-9A-Za-z_.\=\-@:]" # для гестовых релогинов разрешаем спец.символ :
            self.login = urllib.unquote( self.login )
            
        self.force_login = getattr(self.request, "force_login", 0)

        if getattr(self, "skipVersionCheck", 0) or self.checkClientVersion(): 
            if self.login and (not re.search( login_check_ex, self.login )):
                if self.auth and (not re.search("[^0-9ABCDEFabcdef]", self.auth)): # только hex символы?
                    # ок, похоже на логин-пароль.
                    self.uid = logins.get(self.login.lower(), 0) # есть такой в списке логинов?
                    self.acc = users.get(self.uid)
                    if self.acc:
                        # пускаем если 
                        # - указан ключ testkey=1
                        # - указан правильный ключ релогина
                        # - юзер был залоган с помощью служебного sublogin (о чем говорит self.acc.online=0)
                        # - юзер в pvx-игре, в статусе ClientDropped (соц.сервер искусственно держит его сесиию)
                        
                        # - а не забанен ли наш пользователь?
                        if self.acc.banned or (self.acc.db.banned and (time.time() < self.acc.db.bantime or self.acc.db.bantime == 0)): 
                            if self.acc.db.autoban:
                                self.response["ec"] = EC.ACCOUNT_AUTOBAN
                            elif self.acc.db.bantime == 0:
                                self.response["ec"] = EC.ACCOUNT_BANNED_FOREVER
                            else:
                                self.response["ec"] = EC.ACCOUNT_BANNED
                            self.response["error_args"] = {"banreason" : self.acc.db.banreason, "bantime" : self.acc.db.bantime }
                        else:
                            # кстати, проверим этот самый случай с ClientDropped:   
                            is_dropped = 0
                            if self.acc.data.mm:
                                session = self.acc.data.mm
                                #FIXME: статус 102/108 тоже пока подпираем, т.к. есть проблемы с зависанием в этом статусе у лобби 
                                # (когда pvx клиент рассыпался с ошибкой "нет сессии" или "нет места в сессии")
                                if session.progress in [MM.STATUS_CLIENT_DROPPED, MM.STATUS_WAITING_IN_LOBBY, MM.STATUS_WAITING_FOR_PARTY]: 
                                    is_dropped = 1
                            
                            if self.testkey or (self.key == self.acc["key"]) or (not self.acc.online) or (is_dropped):
                                # да он прямо у нас на сервере; отвечаем сразу
                                self.touch()
                                self.acc.resetAccStatus()
                                self._dont_log = DONT_LOG_RELOGIN # в случае "релогина при живом аккаунте" не отсылаем такой login-евент в статистику (чтобы не накручивать CCU)
                                self.relogin = 1 # relogin
                                self.response["re"] = 1 # relogin
                                self.acc["key"] = self.makeNewKey() # генерируем новый ключ, чтобы выкинуть старую сессию
                                # PF-96933 - поставим SD нужной локали (при первом входе в игру локаль не задаётся)
                                self.acc.SD = self.I.SD.getSD(self.userlocale)
                                info( "relogin for uid=%s" % self.acc.uid )
                                return self.doLoginFinish()
                            else:
                                if self.isGM :
                                    info("LoginAction.onStart: Send already logged name=%s, sid=%s to thrift", options.server_name, options.server_id)
                                    self.response["error"] = "already logged"
                                    self.response["ec"] = EC.ALREADY_LOGGED
                                    self.response["ws"] = options.server_id
                                    self.response["ws_name"] = options.server_name
                                else:
                                    info("LoginAction.onStart: already logged on %s", options.server_name)
                                    return self.I.SQL.login( self.login, options.server_id, self.onOldSqlLogin )
                    else:
                        # проверим, а место-то есть на сервере? может, лимит на количество юзеров не позволяет
                        if len(users) < self.I.WS.MAX_USERS or cfg.SKIP_LIMIT_CHECK:
                            if self.guest:
                                # v.105 специальный guest-login (выдаем временный autoinc user_id, загрузку и сохранение через MC/DATA отключаем)
                                self.uid = self.I.WS.nextInt64GUID( "sql_uid" )
                                self.login = "guest:%d" % self.uid
                                self.nick = utf8convert(u"гость_%d" % self.uid)
                                self.sn_nick = "sn_guest_%d" % self.uid
                                info( "guest login: uid %s (0x%x), login %s" % (str(self.uid), self.uid, str(self.login)) )
                                self.pwd = "123"
                                self.response["re"] = 1 # статус "relogin", чтобы не грузили данные юзера из storage
                                self.doLoginAddUser() # добавляем нового юзера в аккаунты
                                return self.doLoginFinish()
                                
                            else:
                                # не знаем такого логина; ок, поехали доставать данные из persistent (sql)
                                self.I.SQL.login( self.login, options.server_id, self.onSqlLogin )
                                return 
                        else:
                            self.fail( "user limit exceeded", EC.USER_LIMIT_EXCEEDED )
                else:
                    self.response["error"] = "bad auth";
            else:
                self.response["error"] = "bad user name";
                
        #-- FAIL: отвечаем юзеру
        self.fin()            

    @action_timing
    def onOldSqlLogin(self, sql_reply):
        r = sql_reply["r"]
        info( "-- onOldSqlLogin: sql sp_login reply: " + str(sql_reply) )
        if r and len(r):
            try:
                ws, login, self.pwd, self.uid = r[0].ws, r[0].login, r[0].pwd, r[0].id
                try:
                    self.admin = r[0].admin
                except Exception:
                    self.admin = 0
                '''
                if self.isGM and ws and ws != options.server_id:
                    debug("%r == %r", ws, options.server_id)
                    self.response["error"] = "already logged"
                    self.response["ec"] = EC.ALREADY_LOGGED
                    self.response["ws"] = ws
                    peer = self.I.WS.peers.get(ws)
                    if peer:
                        self.response["ws_name"] = peer.get("name")
                else:
                '''
                info("-- onOldSqlLogin: [sql] already logged on different server (%s)", ws)
                return self.doLogoutOldUser(ws, login)

            except Exception:
                catch()
                self.response["error"] = "can't parse sql.sp_login reply or finalize user login";
                warn("can't parse sql.sp_login reply or finalize user login. Reply: " + str(sql_reply))
                self.I.SQL.logout(self.login, options.server_id, None)
        else:
            error("[sql] bad login")
    #------------------------------------------------------------------------------------
    ## получили ответ на sp_login
    @action_timing
    def onSqlLogin(self, sql_reply, isRepeatedLogin=False):
        r = sql_reply["r"]
        info( "-- onSqlLogin: sql sp_login reply: " + str(sql_reply) )
        if r and len(r):
            try:
                ws, login, self.pwd, self.uid = r[0].ws, r[0].login, r[0].pwd, r[0].id
                try:
                    self.admin = r[0].admin
                except Exception:
                    self.admin = 0
                if ws and ws == options.server_id:
                    # лок юзера в БД удался; можно добавлять 
                    if self.uid:
                        # добавляем нового юзера в аккаунты
                        self.doLoginAddUser()
                        self.response["_depth"] = DEPTH_SQL

                        # отвечаем клиенту
                        return self.doLoginFinish()
                    else:
                        self.response["error"] = "[sql] bad user id";
                elif ws and self.isGM:
                    debug("%r == %r", toint(ws), toint(options.server_id))
                    self.response["error"] = "[sql] already logged on different server"
                    self.response["ec"] = EC.ALREADY_LOGGED_ON_DIFF_SERVER
                    self.response["ws"] = ws
                    peer = self.I.WS.peers.get(ws)
                    if peer:
                        self.response["ws_name"] = peer.get("name")
                else:
                    if isRepeatedLogin:
                        peer = self.I.WS.peers.get(ws)
                        mess = "Repeating of displaced login! server_id={0} server_name={3} login={1} uid={2}.".format(ws, login, self.uid, peer.get("name") if peer else "unknown server_name")
                        raise DisplaceLoginError(mess)
                    else:
                        info("-- onSqlLogin: [sql] already logged on different server (%s)", ws)
                        return self.doLogoutOldUser(ws, login)

            except DisplaceLoginError as e:
                self.response["error"] = e.message
                self.response["ec"] = EC.ALREADY_LOGGED_ON_DIFF_SERVER
                self.response["ok"] = 0
                self.response["ws"] = ws
                peer = self.I.WS.peers.get(ws)
                if peer:
                    self.response["ws_name"] = peer.get("name")
                err(e.message)
            except Exception:
                catch()
                self.response["error"] = "can't parse sql.sp_login reply or finalize user login";
                warn("can't parse sql.sp_login reply or finalize user login. Reply: " + str(sql_reply))
                self.I.SQL.logout(self.login, options.server_id, None)
        else:
            self.response["error"] = "[sql] bad login";
        #-- FAIL: отвечаем юзеру
        self.fin()
        

    #------------------------------------------------------------------------------------
    # генерируем новый ключ
    def makeNewKey(self):
        if not self.testkey:
            self.key = str( random.randint(100000000,999999999) ) # случайный 9-значный ключ
        else:
            self.key = self.DEFAULT_KEY
        return self.key
            
    #------------------------------------------------------------------------------------
    # имеем все логин-данные, осталось добавить новый user account
    def doLoginAddUser(self):
        # добавляем в список наших аккаунтов:
        uid32 = self.I.WS.repackGUID64to32(self.uid)
        
        # если выполняется служебный sublogin, то в self.login будет логин вида "<snid>#<snuid>", и из него придется выковырять snid/snuid для acc
        if self.login.find("#") >= 0:
            snid, snuid = self.login.split("#")
        elif self.login[:5] == "guest":
            snid, snuid = self.login.split(":")
        else:
            warn("bad self.login format: %r" % self.login)
            snid, snuid = "?", "?"
            
        self.auid = getattr(self, "auid", 0)
        
        now = toint(time.time())
        self.acc = UserAccount({
            "uid":self.uid, 
            "auid":self.auid,
            "login":self.login, 
            "key":self.makeNewKey(), 
            "secret":'',
            "ka":now, 
            "pwd":self.pwd, 
            "admin":self.admin, 
            "snid":snid, 
            "snuid":snuid, 
            "sex":0, 
            "client_ver":self.client_ver, 
            "nick":self.nick, 
            "sn_nick":self.sn_nick, 
            "pending_events":[], 
            "pending_changes":[], 
            "pend_data_load":0,
            "pend_data_save":0,
            "finalize_tm":0,
            "finalize_data":0,
            "acc_status": pwaccount.ACC_STATUS_ACTIVE,
            "sex_touch":now, 
            "in_castle":0, 
            "ts_incastle":0,
            "geo_info": self.geo_info,
            "country_code":self.country_code, 
            "locked":1, # сразу с рождения ставим статус locked, чтобы случайно не прошел logout+сохранение до начала загрузки данных
            "Config":self.I.Config, # выдаем аккаунту ссылку на конфиг
            "SD":self.I.SD.getSD(self.userlocale), # и ссылку на StaticData
            #!!! этими копиями конфига/SD юзер будет пользоваться вплоть до логаута, даже если глобальный конфиг+StaticData будут перегружены
        } )
        users[self.uid] = self.acc

        logins[self.login.lower()] = self.uid

        if self.auid:
            # если нам уже известен auid (например при служебном sublogin_fsn), сразу регистрируем соответствие auid->acc
            self.I.WS.registerAuid( self.auid, self.uid )

        # заведем правильную структуру данных аккаунта (acc.data, acc.db, acc.model)
        ##self.I.WS.onUserData( self.acc, "" ) 
        self.I.PDM.createAccountData( self.acc ) 
        
        self.I.WS.dumpAccount( self.acc, "doLoginAddUser" )
        
        if self.guest: # v.105 специальный guest-login (выдаем временный autoinc user_id, загрузку и сохранение через MC/DATA отключаем)
            self.acc.guest = 1 # признак "не сохранять"
            self.acc.loaded = 1 # все данные уже загружены, типа
            self.acc.snid = "guest"
            self.acc.snuid = str(self.uid)
            self.acc.sex = self.sex 
            self.acc.photoUrl = "http://photo_" + self.acc.snuid + ".fake" # link to photo
            self.acc.locale = str(self.locale)

            # давайте и соц.инфу для guest-ов зафейкаем
            self.acc.sninfo = { 
                "gender": random.randint(0,3),           # 0 - not specified, 1 - male, 2 - female, 3 - other
                "photo": self.acc.photoUrl,
            }
            
            self.acc.auid = uid32 #WORKAROUND: выдаем guest-ам auid, чтобы можно было адекватно тестировать социальные команды (party и проч.)
            self.I.PDM.loadAccountData( self.acc, "" ) # сделайте нам emptyModel плз
                        
            self.I.WS.registerAuid( self.acc.auid, self.acc.uid )
            self.I.WS.subscribeAccToPersonServer( self.acc, 0 ) #WORKAROUND: ну и поскольку загрузки persistent data все равно не будет, можем сразу подписать юзера на PS
            
            self.I.WS.dumpAccount( self.acc, "guest login" )
            self.acc.locked = 0 # все данные загружены, разблокируем акк

    
    #------------------------------------------------------------------------------------
    # имеем валидный self.acc, осталось только ответить юзеру
    def doLoginFinish(self):
        if self.acc:
            self.response["ok"] = 1
            self.response["auid"] = toint(self.acc.auid)
            self.response["uid"] = self.uid
            self.response["key"] = self.acc.key
            self.response["ka"] = self.acc.ka
            self.response["admin"] = self.acc.admin
            repeated_requests["sn_login"][self.acc.login] = (self.rid, toint(time.time()) + CC.REPEATING_TIMEOUT )
            info( "logged in user %r (uid=%d), key=%s", self.acc.login, self.uid, self.acc.key)
            
            self.acc.finalize = {} # на всякий случай сбрасываем статус finalize (вдруг мы были в процессе логаута)
            self.acc.pers_key = makePersKey( self.uid )
            
            # подтянем persistent данные юзера 
            #! (потом, возможно, это лучше будет делать уже в процессе логина? хотя нам, кстати, еще на auth challenge должны ответить)
            if not self.response.get("re", 0):
                self.acc.pend_data_load += 1
                self.I.DATA.loadAndStampData(self.acc.login, self.acc.pers_key, options.server_id, self.I.WS.onUserPersistentData, params=(self.uid,0) )
        
        else:
            self.response["error"] = "no user acc"
            
        self.fin()

    def doLogoutOldUser(self, ws, login):
        peer = self.I.WS.peers.get(ws)
        self.old_ws = ws
        self.login = login
        if options.server_id != ws:
            if peer:
                ws_name = peer.get("name")
            else:
                self.response["error"] = "ws is not found"
                self.response["ec"] = EC.INTERNAL_SERVER_ERROR
                self.response["ws"] = ws
                self.fin()
                return

            args = dict(action="logout_old_user", login=login)

            ws_addr = self.I.WS.getPeerServerByName(ws_name)["addr"]
            debug("doLogoutOldUser peers %r , ws_name %r, ws_addr %r", self.I.WS.peers, ws_name, ws_addr)
            self.I.WSX.fetch(ws_addr, args, self.onDoLogoutOldUser, subrequest=ws_name)
            return

        else:
            '''
            ws_addr = ws
            while ws == ws_addr:
                ws_id = pickRandom(self.I.WS.peers.keys())
                p = self.I.WS.peers.get(ws_id)
                ws_addr = p.get("addr")
                ws_name = p.get("name")
            '''
            args = ClassDict(login=[login])
            action = LogoutOldUserAction(args, self.onDoLogoutOldUser, I=self.I)

            action.onStart()
            return

        '''
        args = dict(action="logout_old_user", login=login)

        #ws_addr = self.I.WS.getPeerServerByName(ws_name)["addr"]
        debug("doLogoutOldUser peers %r , ws_name %r, ws_addr %r", self.I.WS.peers, ws_name, ws_addr)
        self.I.WSX.fetch(ws_addr, args, self.onDoLogoutOldUser, subrequest=ws_name)
        return
        '''

    def onDoLogoutOldUser(self, response):
        info("onDoLogoutOldUser: login=%r response  %r", self.login, response)
        if response:
            if response.get("ok"):
                _callback = functools.partial(self.onSqlLogin, isRepeatedLogin=True)
                return self.I.SQL.login( self.login, options.server_id, _callback )
            else:
                self.response["error"] = response.get("error")
                self.response["ec"] = response.get("ec")
                self.response["ok"] = 0
                self.fin()
                return
        else:
            self.I.SQL.logout(self.login, self.old_ws, None)
            self.response["error"] = "bad response from ws(server_id=%r) service" % self.old_ws
            self.response["ec"] = EC.ALREADY_LOGGED_ON_DIFF_SERVER
            self.response["ok"] = 0
            self.fin()
            return

class LogoutAction( SubAction ):
    """action, который будет обрабатывать данный класс"""
    action = "logout"

    ## клиент покидает здание
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        info("LogoutAction.onStart (acc.uid=%s)", self.acc.uid)
        reset_ka = True  # "keepalive-стамп" по умолчанию сбрасываем
        forceLogout = self.getBoolParam("force", False)
        kicked = self.getBoolParam("kick", False)

        session = self.acc.data.mm
        if session:
            # если у нас есть матчмейкинг-сессии в стадии "еще не в игре", нужно их остановить
            if session.progress in [MM.STATUS_GUARDS_LOBBY]:
                self.acc.model.addDodge( self.I.WS, self.acc )
            if session.progress not in [MM.STATUS_WAITING_IN_LOBBY, MM.STATUS_WAITING_FOR_PARTY, MM.STATUS_IN_GAME, MM.STATUS_CLIENT_DROPPED,
            MM.STATUS_WAITING_GAME_FINISH, MM.STATUS_GAME_FINISHED]:
                info( "LogoutAction canceling mm sessions on logout (uid=%s)", self.acc.uid )
                self.I.WS.doMatchmakingCmd( "cancel", self.acc, MM.CANCEL_ALL )
            # если же есть матчмейкинг-сессии в стадии "еще в игре", то не сбрасываем keepalive, чтобы юзер пожил еще немного на сервере
            if session.progress in [ MM.STATUS_WAITING_IN_LOBBY, MM.STATUS_WAITING_FOR_PARTY, MM.STATUS_IN_GAME, MM.STATUS_CLIENT_DROPPED,
            MM.STATUS_WAITING_GAME_FINISH ]:
                reset_ka = False
        if reset_ka or forceLogout or kicked:
            self.acc.ka = 0 # сбрасываем "keepalive-стамп", следующая же проверка юзеров должна заключить, что юзер протух
            if self.acc.wait_inform_user:
                self.acc.wait_inform_user = False

        elif reset_ka == forceLogout == kicked == False:
            self.acc.ka = 0
            #self.acc.wait_inform_user = True

        if forceLogout:
            try:
                self.I.WS.doMatchmakingCmd( "cancel", self.acc, MM.CANCEL_ALL )
            except Exception:
                catch()

            if getattr(self.acc, "isTutorialAccount", False) and isinstance(self.acc.model, ModelData) and not self.acc.model.isTutorialComplete():
                # кикаем юзера потому как он фейковый и его сохранять не нужно
                self.I.WS.throwOutTutorialAcc(self.acc, self.uid, None)
            else:
                self.I.WS.onAccActive(self.acc, self.acc.uid)

        if kicked:
            self.acc.wait_inform_user = True
            self.I.WS.onAccActive(self.acc, self.acc.uid)

        self.response["ok"] = 1
        self.fin()

class LogoutOldUserAction(SubAction):
    action = "logout_old_user"

    """ Cлужебный логический handler, выполняет выгрузку аккаунта игрока, если игрок пытается  залогинится на другую ws-ку  """

    @action_timing
    def onStart(self):
        info("LogoutOldUser: %r", self.arguments)
        login =self.getParam("login").lower()
        self.uid = logins.get(login) # есть такой в списке логинов?
        self.acc = users.get(self.uid)

        if self.acc and not self.acc.failed:
            info("LogoutOldUser.onStart (acc.uid=%s) start saving", self.acc.uid)
            if getattr(self.acc, "isTutorialAccount", False):

                try:
                    self.I.WS.doMatchmakingCmd( "cancel", self.acc, MM.CANCEL_ALL )
                except Exception:
                    catch()
                # кикаем юзера потому как он фейковый и его сохранять не нужно
                old_users.append(self.uid)
                self.I.WS.throwOutTutorialAcc(self.acc, self.uid, self.onSQLLogoutOldUser)

                return

            session = self.acc.data.mm
            if session:
                # если у нас есть матчмейкинг-сессии в стадии "еще не в игре", нужно их остановить
                if session.progress not in [MM.STATUS_WAITING_IN_LOBBY, MM.STATUS_WAITING_FOR_PARTY, MM.STATUS_IN_GAME, MM.STATUS_CLIENT_DROPPED,
                MM.STATUS_WAITING_GAME_FINISH, MM.STATUS_GAME_FINISHED]:
                    info( "LogoutOldUser: canceling mm sessions on logout (uid=%s)", self.acc.uid )
                    try:
                        #пока так, чтобы в дальнейшем понять почему иногда не протухают сессии
                        self.I.WS.doMatchmakingCmd( "cancel", self.acc, MM.CANCEL_ALL )
                    except Exception:
                        catch()
                        warn("Bad modeldata for %r", self.acc.auid)


            self.acc.ka = 0 # сбрасываем "keepalive-стамп", следующая же проверка юзеров должна заключить, что юзер протух
            if getattr(self.acc, "wait_inform_user", False):
                self.acc.wait_inform_user = False
            old_users.append(self.uid)
            self.I.WS.onAccActive(self.acc, self.acc.uid, self.onLogoutOldAccSaved)
            return


        info("LogoutOldUser: user %r wasn't found", login)
        old_users.append(self.uid)
        if self.acc:
            self.acc.ka = 0
            self.acc.wait_inform_user = None # кикнем неизвестного плохого юзера
        else:
            info("LogoutOldUser: user %r was kicked from sql", login)
            self.I.SQL.logout( login, toint(options.server_id), self.onLogoutOldUserSave)
            return

        self.response["ok"] = 1
        self.fin()

    def onSQLLogoutOldUser(self, reply):
        info("onSQLLogoutOldUser reply %r", reply)
        self.onLogoutOldUserSave()

    def onLogoutOldAccSaved(self):
        info("onLogoutOldAccSaved Logout-saving for acc[%d] is completed!", self.uid)
        self.I.WS.onAccSaved(self.acc, self.uid)
        self.onLogoutOldUserSave()

    def onLogoutOldUserSave(self, response=None):
        if response:
            info("onLogoutOldUserSave finished response=%r", response)
        else:
            info("onLogoutOldUserSave finished")
        self.response["ok"] = 1
        self.fin()

## ---------------------------------------------------------------
## ---------------------------------------------------------------



