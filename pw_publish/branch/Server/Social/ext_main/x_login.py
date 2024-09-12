# -*- coding: utf8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging
from base64 import b64decode

# чтобы питон правильно понимал относительные пути модулей:
def _addPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)

from handlers import * # JsonHandler, globals: peers, users..
from subaction import SubAction, action_timing

from instr import * 

import MM
import EC
import CC


##-------------------------------------------------------------------------------------
##-------------------------------------------------------------------------------------

class XLoginAction( SubAction ):
    """ Cлужебный логический handler, поддерживает единственный 'action=login' """
    #~ method=login,                // название метода, обязательно к указанию
    #~ project=<STRING>,            // код проекта, см CrossPlatformSocialProtocol
    #~ auid=INT64,                  // auid пользователя, обязательно к указанию
    #~ period=INT,                  // период времени в секундах (но не больше 30 секунд) в течении которого повторное чтение не будет произведено, по умолчанию равно 5 секундам
    #~ force=INT,                   // флаг форсированного логина, sid будет выдан даже в случае если пользователь уже залогинен, по умолчанию равен 0
    #~ url=STRING,                  // url для операции push, по умолчанию: ""    
    
    action = "login"
    
    @action_timing
    def onStart(self):
        info("XLoginAction.onStart")
        self.project = self.getParam("project")
        if self.project and self.project.find(":") < 0:
            self.auid = self.getIntParam("auid", 0)
            self.period = self.getIntParam("period", 0)
            self.force = self.getIntParam("force", 1) # по умолчанию форсируем релогин
            self.url = self.getParam("url")
            self.redirect_from = self.getParam("redirect_from", "")
            
            self.relogin = 0
            
            self.response["ver"] = self.I.WS.SERVER_VERSION
            self.response["_depth"] = DEPTH_WS
            if self.redirect_from:
                self.response["redirect_from"] = self.redirect_from
            
            self.login = "%s:%s" % (self.project, self.auid)
            self.create_new_login = 0
            
            if self.auid:
                if self.project and (self.project in CC.EXCHANGE_PROJECTS):
                    # ок, похоже на логин-пароль.
                    self.sid = logins.get(self.login.lower(), 0) # есть такой в списке логинов?
                    self.acc = users.get(self.sid)
                    if self.acc:
                        # разрешаем релогин, если не указан ключ force=0
                        if self.force:
                            # successful relogin 
                            self.touch()
                            self.response["re"] = 1 # relogin
                            self.relogin = 1 # relogin
                            self.acc.push_url = self.url
                            return self.doLoginFinish()
                        else:
                            return self.fail( "already logged", EC.XS_ALREADY_LOGGED )
                    else:
                        # не знаем такого логина; ок, поехали доставать данные из persistent (mysql)
                        info( "check login for login=%s" % self.login )
                        info( "check server_id=%s" % options.server_id )
                        self.I.SQL.login( self.login, options.server_id, self.onSqlLogin )
                        return 
                        
                else:
                    return self.fail( "bad project, allowed: %r" % CC.EXCHANGE_PROJECTS, EC.XS_BAD_PROJECT )
            else:
                return self.fail( "bad auid (%s)" % self.auid, EC.XS_BAD_AUID )
        else:
            return self.fail( "bad project mask", EC.XS_BAD_PROJECT )
                
    
    #------------------------------------------------------------------------------------
    ## получили ответ на sp_login
    @action_timing
    def onSqlLogin(self, sql_reply):
        r = sql_reply["r"]
        info( "-- onSqlLogin: sql sp_login reply: " + str(sql_reply) )
        if r and len(r):
            try:
                ws, login, self.pwd, self.uid = r[0].ws, r[0].login, r[0].pwd, r[0].id
                if ws and ws == options.server_id:
                    # лок юзера в БД удался; можно добавлять
                    if self.uid:
                        # добавляем нового юзера в аккаунты
                        self.doLoginAddUser()                        
                        self.response["_depth"] = DEPTH_SQL
                        return self.doLoginFinish()                        
                    else:
                        return self.fail( "[sql] bad user id for xs login %r" % self.login, EC.XS_BAD_SQL_USER_ID )
                else:
                    peer = self.I.WS.peers.get(ws)
                    if peer:
                        # redirect to peer XS
                        peer_addr = peer.get("addr", "")
                        params = self.getFlatParams()
                        params["redirect_from"] = options.server_name
                        self.redirect_addr = http_prefix(peer_addr) + "/?" + urllib.urlencode( params )            
                        self.response["__redirect__"] = self.redirect_addr
                        return self.fin()
                    else:
                        warn("Can't redirect to peer %r - peer isn't known", ws)
                        self.response["ws"] = ws
                        return self.fail( "[sql] already logged on different server", EC.XS_ALREADY_LOGGED )
            except:
                catch()
                warn( "can't parse sql.sp_login reply: " + str(sql_reply) )
                return self.fail( "[sql] can't parse sp_login reply for xs login %r" % self.login, EC.XS_BAD_SQL_REPLY )
                
        else:
            # ответ от базы данных пустой, нету такого логина
            if not self.create_new_login:
                # создаем новый логин в mysql базе
                self.create_new_login = 1
                new_uid = self.I.WS.nextInt64GUID( "sql_uid" )
                pwd_hash = "" 
                return self.I.SQL.addNewLogin( new_uid, self.login, pwd_hash, options.server_id, callback=self.onNewLoginAdded )
            else:
                # похоже, попытка создать новый логин в mysql провалилась, обламываемся.
                return self.fail( "[sql] failed with new xs login: %r" % self.login, EC.XS_BAD_SQL_LOGIN )
            
    #------------------------------------------------------------------------------------
    @action_timing
    def onNewLoginAdded(self, sql_reply):
        info("onNewLoginAdded: sql reply %s" % sql_reply)
        if sql_reply["r"]:
            # повторяем попытку логина
            self.I.SQL.login( self.login, options.server_id, self.onSqlLogin )
        else:
            # похоже, попытка создать новый логин в mysql провалилась, обламываемся.
            return self.fail( "[sql] failed to create new xs login: %r" % self.login, EC.XS_BAD_SQL_LOGIN )

    #------------------------------------------------------------------------------------
    # имеем все логин-данные, осталось добавить новый user account
    def doLoginAddUser(self):
        # генерируем новый session_id, добавляем сессию в список активных аккаунтов
        self.sid = self.I.WS.nextInt64GUID( "sid" )

        # логин вида "<project>#<auid>"
        self.acc = ClassDict( uid=self.uid, login=self.login, ka=time.time(), \
                              project=self.project, auid=self.auid, sid=self.sid, \
                              push_url=self.url, push_lock=0, pending_push=0, ts_push=0, ts_expire=0, messages={} \
                            )
        
        users[self.sid] = self.acc
        logins[self.login.lower()] = self.sid

    
    #------------------------------------------------------------------------------------
    # имеем валидный self.acc, осталось только ответить юзеру
    def doLoginFinish(self):
        if self.acc:
            self.response["auid"] = self.acc.auid
            self.response["sid"] = self.acc.sid
            self.response["ka"] = self.acc.ka
            
            info( "logged in user %r (sid=%d, auid=%s)" % (self.acc.login, self.acc.sid, self.acc.auid) )
            
            # подтянем persistent данные юзера (для SE это список messages, лежащих в базе)
            # if not self.response.get("re", 0):
            return self.I.SQL.seGetMessages( self.acc.login, self.onGetMessages )
        else:
            return self.fail( "no user acc", EC.XS_FAIL_LOGIN_ACC )
                

    #------------------------------------------------------------------------------------
    @action_timing
    def onGetMessages(self, sql_reply):
        try:
            info( "onGetMessages(auid=%s, project=%s): sql reply %s", self.acc.auid, self.acc.project, sql_reply )
            replies = sql_reply["r"]
            if replies:
                x_uid = sql_reply["p"]
                for reply in replies:
                    try:
                        if reply:
                            info( "onGetMessages2 (auid=%s, project=%s): add message id=%s, type=%s, msg=%r (len %d)", self.acc.auid, self.acc.project, reply.id, reply.type, reply.msg, len(reply.msg) )
                            decoded_msg = b64decode( reply.msg )
                            msg_dict = json_loads( decoded_msg )
                            dt_rcv = toint( msg_dict.get("dt_rcv") )
                            info( "onGetMessages3 (auid=%s, project=%s): add message id=%s, type=%s, received:%s, msg=%r (decoded json len %d)", self.acc.auid, self.acc.project, reply.id, reply.type, time.ctime(dt_rcv), msg_dict, len(decoded_msg))
                            self.acc.messages[ reply.id ] = msg_dict
                        else:
                            err("onGetMessages: bad SQL reply!")
                    except:
                        catch()

            # ок, сообщения загрузили, можно отвечать
            info( "XLoginAction.onGetMessages OK  %r:%r" % (self.acc.project, self.acc.auid ) )
            self.response["messages"] = self.acc.messages
            self.response["count"] = len(self.acc.messages)
            self.response["ok"] = 1
            self.fin()
            
        except:
            catch()
            return self.fail( "[sql] get messages error", EC.XS_GET_MESSAGES_ERROR )
        

## ---------------------------------------------------------------
## ---------------------------------------------------------------

class XLogoutAction( SubAction ):
    """action, который будет обрабатывать данный класс"""
    action = "logout"
    
    ## клиент покидает здание
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        info("XLogoutAction.onStart")
        self.acc.ka = 0 # сбрасываем "keepalive-стамп", следующая же проверка юзеров должна заключить, что юзер протух
        
        self.response["ok"] = 1
        self.fin()

