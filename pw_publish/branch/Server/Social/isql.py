# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *
import httplib

import tornado.ioloop
import tornado.options
from tornado.options import define, options

import cfg # конфиг кластера (нужен CLUSTER_SQL_SERVER_COUNT)

# NB: пока что реализуем и IData в AsyncMysql, просто через отдельную таблицу tbl_brick в MySQL БД
from idata import IData

##---------------------------------------------------------------------------------------------
from cluster_base import crc_hash

def AsyncSQLIndex(key):
    return ( crc_hash(key) % cfg.CLUSTER_SQL_SERVER_COUNT ) if cfg.CLUSTER_SQL_SERVER_COUNT else 0

def AsyncSQL(key):
    index = AsyncSQLIndex(key)
    return tornado.ioloop.IOLoop.instance().sql[ index ]

def FirstSQL():
    return tornado.ioloop.IOLoop.instance().sql[ 0 ]

# заглушка, на случай когда "не особо нужен callback"
def main_sql_callback( reply ):
    ##log( "- main_sql_callback: reply %s" % str(reply) )
    pass

def info_sql_callback( reply ):
    info( "- sql_callback: reply %s" % str(reply) )

##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

# NB: пока что реализуем и IData здесь же (простым наследованием)
class ISql:
    """ Виртуальный интерфейс для общения с sql database (он же и dummy-заглушка для работы без БД вообще).
        повторяет интерфейс реального общения приложения с sql thread pool (через очередь запросов),
        поэтому параметры и return могут быть странного вида.
        Поведение: якобы успешно исполняем все запросы, uid возвращаем уникальный для каждого логина.
    """
    def __init__(self):
        self._next_uid = 100000 * options.server_id

    def login(self, login_name, server_id, callback):
        """ срочный Login()
            ответ: будет вызван callback( reply = { "r":[{ws, login, pwd, id}] } )
        """
        self._next_uid += 1
        reply = ClassDict( {"ws":server_id, "login":login_name, "pwd":"123", "id":self._next_uid} )
        return callback( { "r": [reply] } )

    def lazyLogin(self, login_name, server_id, callback):
        """ ленивый отложенный spLogin(), через lazy запрос
            ответ: будет вызван callback( reply = { "r":[{ws, login, pwd, id}] } )
        """
        return callback( {"r": None} )

    def logout(self, login_name, server_id, callback):
        """ лениво logout'им юзера """
        return callback( {"r": None} )

    def logEvent(self, login, uid, server_id, timestamp, event):
        """ лениво пишем event в одну БД """
        pass

    def logEventAll(self, uid, server_id, timestamp, event):
        """ лениво пишем event во все БД """
        pass

    def addServer(self, server_id, server_name):
        """ coordinator: прописываем активный сервер во все БД """
        pass

    def removeServer(self, server_name):
        """ coordinator: убираем неактивный сервер из всех БД """
        pass

    def checkNextServerId(self, callback):
        """ coordinator: спрашиваем максимальный AUTO-INC для значения server_id по всем доступным БД """
        reply = ClassDict( {"Auto_increment":1} )
        return callback( {"r": [reply]} )

    def destroy(self):
        """ грубо закрываем лавочку (прибиваем thread pool, очередь запросов и т.п.) """
        pass

    def fadeout(self, syncWait=0 ):
        """ постепенно закрываем лавочку (ждем когда очередь запросов полностью разберут, и тогда прибиваем thread pool) """
        pass

    def isDone(self):
        """ прикрыта ли лавочка? """
        return True # пустышку можно прибивать в любой момент

    def addNewLogin(self, *args, **kwargs):
        """ добавляем в базу (тестовый) логин/пароль """
        pass

    def keepAlive(self, *args, **kwargs):
        """ периодически шлем в каждый connect незначащую команду, чтобы sql-connection не сдох """
        pass

    def setNick(self, *args, **kwargs):
        pass

    def removeOldNick(self, *args, **kwargs):
        pass

    def addBroadcast(self, *args, **kwargs):
        pass

    def editBroadcast(self, *args, **kwargs):
        pass

    def deleteBroadcast(self, *args, **kwargs):
        pass

    def getBroadcastList(self, *args, **kwargs):
        pass

    def pwcRegister(self, *args, **kwargs):
        pass

    def pwcGet(self, *args, **kwargs):
        pass

    def pwcPostRegister(self, *args, **kwargs):
        pass

    def pwcActivate(self, *args, **kwargs):
        pass

    def pwcUpdatePwd(self, *args, **kwargs):
        pass

    def pwcUpdateResendTimestamp(self, *args, **kwargs):
        pass

    def pwcUpdateResetPwdTimestamp(self, *args, **kwargs):
        pass

    def pwcMerge(self, *args, **kwargs):
        pass

    # --------------------------------------------------------
    # Social Exchange
    def seGetMessages(self, *args, **kwargs):
        pass

    def seAddMessage(self, *args, **kwargs):
        pass

    def seDeleteMessages(self, *args, **kwargs):
        pass

    def seFindLogin(self, *args, **kwargs):
        pass

    # --------------------------------------------------------
    # Access Restrictions
    def cbtAddRestrictedUser(self, *args, **kwargs):
        pass

    def cbtCheckUserRestrictions(self, *args, **kwargs):
        pass

    def cbtCheckIpAllowances(self, *args, **kwargs):
        pass

    # --------------------------------------------------------
    # Admin Messages
    def addAdminMessage(self, *args, **kwargs):
        pass


##---------------------------------------------------------------------------------------------
## Интерфейс для общения с реальной sql-базой через async thread-pool.
# NB: пока что реализуем и IData здесь же, просто через отдельную таблицу tbl_brick в MySQL БД
class AsyncMysql(ISql, IData):
    def __init__(self):
        self.loop = tornado.ioloop.IOLoop.instance()

    def login(self, login_name, server_id, callback):
        """ срочный Login() """
        AsyncSQL(login_name).addQuery("CALL sp_login(%s,%s);", callback, params=(login_name, server_id,),
                                      args=(login_name, server_id,), opname="login")

    def lazyLogin(self, login_name, server_id, callback):
        """ ленивый, отложенный Login() """
        AsyncSQL(login_name).lazyQuery("CALL sp_login(%s,%s);", callback, params=(login_name, server_id,),
                                       args=(login_name, server_id,), opname="lazyLogin")

    def logout(self, login_name, server_id, callback):
        """ ленивый logout юзера """
        AsyncSQL(login_name).lazyQuery("CALL sp_logout(%s,%s)", callback, params=(login_name, server_id),
                                       args=(login_name, server_id,), opname="logout")

    def forceLogout(self, login_name, callback):
        """ принудительный logout юзера """
        AsyncSQL(login_name).addExec("UPDATE tbl_login SET server_id=0 WHERE login=%s", callback, params=(login_name,),
                                       args=(login_name,), opname="forceLogout")

    def logEvent(self, login_name, uid, server_id, timestamp, event,callback=main_sql_callback):
        AsyncSQL(login_name).lazyQuery("INSERT INTO tbl_log (user_id,server_id,time,msg) VALUES(%s,%s,%s,%s)",
                                       callback=callback,
                                       params=(uid, server_id, timestamp, event,),
                                       args=(uid, server_id, timestamp, event,), opname="logEvent")

    def logEventAll(self, uid, server_id, timestamp, event,callback=main_sql_callback):
        for sql in self.loop.sql:
            sql.lazyQuery("INSERT INTO tbl_log (user_id,server_id,time,msg) VALUES(%s,%s,%s,%s)",
                          callback=callback, params=(uid, server_id, timestamp, event),
                          args=(uid, server_id, timestamp, event), opname="logEventAll")

    def addServer(self, server_id, server_name, callback=main_sql_callback):
        """ coordinator: прописываем активный сервер во все БД """
        for sql in self.loop.sql:
            sql.addExec("REPLACE INTO tbl_servers (id,name) VALUES (%s,%s)",
                        callback, params=(server_id, server_name), args=(server_id, server_name), opname="addServer")

    def removeServer(self, server_name, callback=main_sql_callback):
        """ coordinator: убираем неактивный сервер из всех БД """
        for sql in self.loop.sql:
            sql.addExec("DELETE FROM tbl_servers WHERE name=%s",
                        callback, params=(server_name,), args=(server_name,),  opname="removeServer")

    def checkNextServerId(self, callback):
        """ coordinator: спрашиваем максимальный AUTO-INC для значения server_id по всем доступным БД """
        for sql in self.loop.sql:
            sql.addQuery('SHOW TABLE STATUS LIKE "tbl_servers"', callback, opname="checkNextServerId")

    def destroy(self):
        for sql in self.loop.sql:
            sql.destroy()

    def fadeout(self, syncWait=0):
        """ постепенно прикрываем лавочку (ждем когда очередь запросов полностью разберут, и тогда прибиваем thread pool).
            при syncWait==1 не возвращаем управление, пока полностью не закроемся; syncWait==0 ставит флаг и сразу возвращается (async) """
        for sql in self.loop.sql:
            sql.fadeout(syncWait)

    def keepAlive(self, callback=None):
        """ периодически шлем в каждый connect незначащую команду, чтобы sql-connection не сдох """
        for sql in self.loop.sql:
            for i in range(sql.num_connections): # надо скормить по команде каждому sql-thread
                sql.addExec("SELECT unix_timestamp() AS ts;", callback, opname="keepAlive")

    def isDone(self):
        """ прикрыта ли лавочка? """
        for sql in self.loop.sql:
            if (not sql.threadsDone()) or len(sql.replies):  # остались бегающие threads или неразобранные ответы
                return False
        return True

    def addNewLogin(self, id, username, pwd_md5, server_id=0, callback=None):
        AsyncSQL(username).addExec("INSERT INTO tbl_login (id, login, pwd_md5, server_id) VALUES (%s,%s,%s,%s)",
                                   callback=callback, params=(id, username, pwd_md5, server_id,),
                                   args=(id, username, pwd_md5, server_id), opname="addNewLogin")

    def removeLogin(self, id, username, callback=None):
        AsyncSQL(username).addExec("DELETE FROM tbl_login WHERE id=%s",
                                   callback=callback, params=(id,), args=(id,), opname="removeLogin")

    def removeNicknameById(self, id, username, callback=None):
        AsyncSQL(username).addExec("DELETE FROM tbl_nick WHERE id=%s", callback=callback,
                                   params=(id,), args=(id,), opname="removeNickname")

    # ------------------ IData -------------------------

    def loadAndStampData(self, shard_key, data_key, stamp, callback, params=None):
        """ достаем пользовательские данные (из некоторого БД-шарда по некоторому ключу). """
        AsyncSQL(shard_key).addQuery("CALL sp_load_data(%s,%s)", callback=callback,
                                     params=(data_key, stamp,), args=(data_key, stamp,), opname="loadAndStampData")

    def stampData(self, shard_key, data_key, stamp, callback=None, params=None):
        """ стампим данные неким ключиком stamp (не указав этот ключ, нельзя апдейтить данные). """
        # для SQL реализация в любом случае отвечает (roundtrip), так что вызываем тот же механизм load_data
        AsyncSQL(shard_key).addQuery("CALL sp_load_data(%s,%s)", callback=callback,
                                     params=(data_key, stamp,), args=(data_key, stamp,), opname="stampData")

    #FIXME it looks like it isn't used any more - remove it!
    def saveData(self, shard_key, data_key, stamp, data, callback=None, params=None):
        """ срочное сохранение данных (через основную очередь thread-pool). """
        AsyncSQL(shard_key).addQuery("CALL sp_save_data(%s,%s,%s)", callback=callback, params=(data_key, stamp, data,),
                                     args=(data_key, stamp, data,), opname="saveData")

    #~ def postData(self, shard_key, data_key, stamp, data, callback=None, params=None):
        #~ """ ленивый отложенный save данных, через lazy запрос. """
        #~ # для SQL реализация в любом случае отвечает (roundtrip), так что вызываем тот же запрос, только lazy
        #~ AsyncSQL(shard_key).lazyQuery( "CALL sp_save_data(%r,%d,%r)" % (data_key, stamp, data), callback, params )

    def setNick(self, uid, nick, callback):
        nick64 = unicode(nick, 'utf8')
        info(u"setNick query: CALL sp_nick_add('%s',%s)", nick64, str(uid))
        AsyncSQL(nick.lower()).addQuery(u"CALL sp_nick_add(%s,%s)", callback,
                                        params=(nick, uid,),
                                        args=(nick64, uid,), opname="setNick")

    def removeOldNick(self, uid, oldNick, newNick, callback=main_sql_callback):
        # удалить старый ник данного юзера (if any), но только если он попадает в другой sql-шард (если старый ник был в
        # том же sql-шарде, то он уже благополучно апдейчен на новый)
        if oldNick:
            oldNick64 = oldNick
            oldNick_sql_shard = AsyncSQL(oldNick64.lower())
            if newNick:
                newNick64 = newNick
                newNick_sql_shard = AsyncSQL(newNick64.lower())
            if (not newNick) or (oldNick_sql_shard != newNick_sql_shard):
                info("removeOldNick query: DELETE FROM tbl_nick WHERE `id`= %s" % str(uid))
                oldNick_sql_shard.addExec("DELETE FROM tbl_nick WHERE `id`= %s",
                                          callback=callback, params=(uid,), args=(uid,), opname="removeOldNick" )
            else:
                info("removeOldNick: new nick64 (%r) in the same sql shard as old nick64 (%r)" % (newNick64, oldNick64))

    def findUidByNick(self, nick_utf8, callback):
        nick = unicode(nick_utf8, 'utf8')
        info(u"findByNick query: SELECT id FROM tbl_nick WHERE nick=%s", nick)
        AsyncSQL(nick_utf8.lower()).addQuery("SELECT id FROM tbl_nick WHERE nick=%s",
                                             callback=callback, args=(nick,), params=(nick_utf8,), opname="findUidByNick")

    # специфика поиска логина в том, что шарды делятся как раз по логину; поэтому спросить придется у каждого шарда, и callback будет вызван N раз, в т.ч. будет N-1 фейлов
    def findLoginByUid(self, uid, callback):
        info("findLoginByUid query: SELECT id, login, server_id FROM tbl_login WHERE id=%s" % (uid))
        for sql in self.loop.sql:
            sql.addQuery("SELECT id, login, server_id FROM tbl_login WHERE id=%s", callback,
                         params=(uid,), args=(uid,), opname="findLoginByUid")

    def findUidByLogin(self, login, callback):
        """ поиск uid по логину """
        AsyncSQL(login).addQuery("SELECT id FROM tbl_login WHERE login=%s", callback,
                         params=(login,), args=(login,), opname="findLoginByUid")

    # --------------------------------------------------------
    # Broadcasts
    def addBroadcast(self, msgId, msgText, msgTitle="", tStart=0, tFin=0, interval=0, enabled=0, callback=None):
        if not msgTitle:
            msgTitle = ""
        enabled = 1 if enabled else 0
        FirstSQL().addExec(u"INSERT INTO tbl_broadcast (id,message,title,tstart,tfin,`interval`,enabled) "
                           u"VALUES (%s,%s,%s,%s,%s,%s,%s)",
                           callback=callback,
                           params=(toint(msgId), msgText, msgTitle,toint(tStart), toint(tFin), toint(interval), toint(enabled)),
                           args=(toint(msgId), msgText.decode("utf8"), msgTitle.decode("utf8"), toint(tStart), toint(tFin), toint(interval), toint(enabled)),
                           opname="addBroadcast")

    def editBroadcast(self, msgId, msgText, msgTitle="", tStart=0, tFin=0, interval=0, enabled=0, tLastSent=0, callback=None):
        if not msgTitle:
            msgTitle = ""
        enabled = 1 if enabled else 0
        FirstSQL().addExec(u"UPDATE tbl_broadcast "
                           u"SET message=%s,title=%s,tstart=%s,tfin=%s,`interval`=%s,enabled=%s,tlastsent=%s "
                           u"WHERE id=%s",
                           callback=callback,
                           params=(msgText, msgTitle, toint(tStart), toint(tFin), toint(interval), toint(enabled), toint(tLastSent), toint(msgId)),
                           args=(unicode(msgText, 'utf8'), unicode(msgTitle, 'utf8'), toint(tStart), toint(tFin), toint(interval), toint(enabled), toint(tLastSent), toint(msgId)),
                           opname="editBroadcast")

    def deleteBroadcast(self, msgId, callback=None):
        q = "DELETE FROM tbl_broadcast WHERE id=%d" % (toint(msgId))
        FirstSQL().addExec(q, callback, params=msgId, opname="deleteBroadcast")

    def getBroadcastList(self, callback=None):
        FirstSQL().addQuery("SELECT * FROM tbl_broadcast", callback, opname="getBroadcastList")

    # --------------------------------------------------------
    # PW Connect
    def pwcRegister(self, email_unicode, pwc_snuid, pwd_md5, gender, remote_ip, birthdate, callback=None):
        email_utf8 = email_unicode.encode("utf8")
        email_md5 = hashlib.md5(email_utf8).hexdigest()
        ts_create=toint(time.time())
        info(u"pwcRegister query: INSERT IGNORE INTO tbl_pwconnect (email,email_md5,pwc_snuid,pwd_md5,gender,ip,birthdate,ts_create) " \
             u"VALUES ('%s','%s',%d,'%s',%d,'%s',%d,%d)", email_unicode, email_md5, pwc_snuid, pwd_md5, toint(gender), remote_ip, toint(birthdate), ts_create)
        AsyncSQL(email_md5).addExec(u"INSERT IGNORE "
                                    u"INTO tbl_pwconnect (email,email_md5,pwc_snuid,pwd_md5,gender,ip,birthdate,ts_create) "
                                    u"VALUES (%s,%s,%s,%s,%s,%s,%s,%s)",
                                    callback=callback,
                                    params=(email_utf8, email_md5, pwc_snuid, pwd_md5, toint(gender), remote_ip, toint(birthdate), ts_create,),
                                    args=(email_unicode, email_md5, pwc_snuid, pwd_md5, toint(gender), remote_ip, toint(birthdate), ts_create,),
                                    opname="pwcRegister")

        if AsyncSQLIndex(email_md5) != AsyncSQLIndex( str(pwc_snuid) ):
            # дублируем в другой шард, т.к. аггрегатор будет спрашивать pwc_get_info по pwc_snuid (и получится другое хэширование по шардам)
            AsyncSQL(str(pwc_snuid)).addExec(u"INSERT IGNORE "
                                             u"INTO tbl_pwconnect (email,email_md5,pwc_snuid,pwd_md5,gender,ip,birthdate,ts_create) "
                                             u"VALUES (%s,%s,%s,%s,%s,%s,%s,%s)",
                                             callback=info_sql_callback,
                                             params=(email_utf8, email_md5, pwc_snuid, pwd_md5, toint(gender), remote_ip, toint(birthdate), ts_create,),
                                             args=(email_unicode, email_md5, pwc_snuid, pwd_md5, toint(gender), remote_ip, toint(birthdate), ts_create,),
                                             opname="pwcRegister")  # для дубликата callback не слушаем

    def pwcGet(self, email_md5, callback=None):
        info( "pwcGet query: SELECT email,auid,pwc_snuid,pwd_md5,gender,birthdate,ip,confirm,ts_confirm,active,ts_resend,ts_reset_pwd FROM tbl_pwconnect WHERE email_md5='%s'"  % email_md5 )
        AsyncSQL(email_md5).addQuery("SELECT email,auid,pwc_snuid,pwd_md5,gender,birthdate,ip,confirm,ts_confirm,active,ts_resend,ts_reset_pwd "
                                     "FROM tbl_pwconnect WHERE email_md5=%s",
                                     callback, params=(email_md5,), args=(email_md5,), opname="pwcGet" )

    def pwcGetByPwcSnuid(self, pwc_snuid, callback=None):
        info("pwcGetByPwcSnuid: SELECT email,email_md5,gender,birthdate FROM tbl_pwconnect WHERE pwc_snuid=%d " % (tolong(pwc_snuid)))
        AsyncSQL( str(pwc_snuid) ).addQuery("SELECT email,email_md5,gender,birthdate FROM tbl_pwconnect WHERE pwc_snuid=%s",
                                            callback=callback, params=(pwc_snuid,), args=(pwc_snuid,), opname="pwcGetByPwcSnuid")

    def pwcGetByEmail(self, email, callback=None):
        info("pwcGetByEmail: SELECT email,active FROM tbl_pwconnect WHERE email=%s " % email)
        email_utf8 = email.encode("utf8")
        email_md5 = hashlib.md5(email_utf8).hexdigest()
        AsyncSQL( email_md5 ).addQuery("SELECT email,active FROM tbl_pwconnect WHERE email=%s",
                                            callback=callback, params=(email,), args=(email,), opname="pwcGetByEmail")

    def pwcPostRegister(self, email_md5, auid, confirm_token, callback=None):
        ts_confirm=toint(time.time())
        info("pwcSetAuid query: UPDATE tbl_pwconnect SET auid=%d, active=0, confirm='%s', ts_confirm=%d WHERE email_md5='%s'",
            toint(auid), confirm_token, ts_confirm, email_md5 )
        AsyncSQL(email_md5).addExec("UPDATE tbl_pwconnect SET auid=%s, active=0, confirm=%s, ts_confirm=%s "
                                    "WHERE email_md5=%s", callback=callback,
                                    params=(auid,confirm_token,ts_confirm,email_md5,),
                                    args=(auid,confirm_token,ts_confirm,email_md5,), opname="pwcPostRegister")
#
    def pwcActivate(self, email_md5, confirm_token, callback=None):
        ts_active=toint(time.time())
        info("pwcActivate query: UPDATE tbl_pwconnect SET active=1, ts_active='%s' WHERE email_md5='%s' AND confirm='%s'" % ( str(ts_active), email_md5, confirm_token))
        AsyncSQL(email_md5).addExec("UPDATE tbl_pwconnect SET active=1, ts_active=%s "
                                    "WHERE email_md5=%s AND confirm=%s",
                                    callback=callback, params=(ts_active, email_md5, confirm_token,),
                                    args=(ts_active, email_md5, confirm_token,), opname="pwcActivate")

    def pwcForceActivate(self, email, callback=None):
        ts_active=toint(time.time())
        email_utf8 = email.encode("utf8")
        email_md5 = hashlib.md5(email_utf8).hexdigest()
        info("pwcForceActivate query: UPDATE tbl_pwconnect SET active=1, ts_active='%s' WHERE email_md5='%s'" % ( str(ts_active), email_md5))
        AsyncSQL(email_md5).addExec("UPDATE tbl_pwconnect SET active=1, ts_active=%s "
                                    "WHERE email_md5=%s",
                                    callback=callback, params=(ts_active, email_md5,),
                                    args=(ts_active, email_md5,), opname="pwcForceActivate")

    def pwcUpdatePwd(self, email_md5, pwd_md5, pwc_snuid, callback=None):
        info( "pwcUpdatePwd query: UPDATE tbl_pwconnect SET pwd_md5=%s WHERE email_md5=%s"  % (pwd_md5, email_md5))
        AsyncSQL(email_md5).addExec("UPDATE tbl_pwconnect SET pwd_md5=%s WHERE email_md5=%s",
                                     callback=callback,
                                     params=(pwd_md5, email_md5),args=(pwd_md5, email_md5,),
                                     opname="pwcUpdatePwd")

        if AsyncSQLIndex(email_md5) != AsyncSQLIndex( str(pwc_snuid) ):
            # дублируем в другой шард, т.к. при смене email могут перепутаться шард-копии
            info("pwcUpdatePwd query: UPDATE tbl_pwconnect SET pwd_md5='%s' WHERE pwc_snuid='%s'" % (str(pwd_md5), str(pwc_snuid)))
            AsyncSQL( str(pwc_snuid) ).addExec("UPDATE tbl_pwconnect SET pwd_md5=%s WHERE pwc_snuid=%s",
                                               callback=info_sql_callback, params=(pwd_md5, toint(pwc_snuid),),
                                               args=(pwd_md5, toint(pwc_snuid),), opname="pwcUpdatePwd") # для дубликата callback не слушаем

    def pwcUpdateResendTimestamp(self, email_md5, callback=None):
        ts_resend=toint(time.time())
        info("pwcUpdateResendTimestamp query: UPDATE tbl_pwconnect SET ts_resend='%s' WHERE email_md5='%s'" % (str(ts_resend), email_md5))
        AsyncSQL(email_md5).addExec("UPDATE tbl_pwconnect SET ts_resend=%s WHERE email_md5=%s",
                                    callback=callback, params=(ts_resend,email_md5,), args=(ts_resend,email_md5,),
                                    opname="pwcUpdateResendTimestamp")

    def pwcUpdateResetPwdTimestamp(self, email_md5, callback=None):
        ts_reset_pwd=toint(time.time())
        info("pwcUpdateResetPwdTimestamp query: UPDATE tbl_pwconnect SET ts_reset_pwd='%s' WHERE email_md5='%s'" % (str(ts_reset_pwd), email_md5))
        AsyncSQL(email_md5).addExec("UPDATE tbl_pwconnect SET ts_reset_pwd=%s WHERE email_md5=%s",
                                    callback=callback, params=(ts_reset_pwd, email_md5,),
                                    args=(ts_reset_pwd, email_md5,), opname="pwcUpdateResetPwdTimestamp")

    def pwcChangeEmail(self, pwc_snuid, new_email, old_email_md5, new_email_md5, pwc, callback=None):
        info("pwcChangeEmail qiery: UPDATE tbl_pwconnect SET email='%s', email_md5='%s' WHERE pwc_snuid='%s'"  % ( new_email, new_email_md5, pwc_snuid ))
        AsyncSQL( str(pwc_snuid) ).addExec("UPDATE tbl_pwconnect SET email=%s, email_md5=%s WHERE pwc_snuid=%s",
                                           callback=callback, params=(new_email, new_email_md5, pwc_snuid),
                                           args=(new_email, new_email_md5, pwc_snuid,), opname="pwcChangeEmail")

        if AsyncSQLIndex(old_email_md5) != AsyncSQLIndex( str(pwc_snuid) ):
            # дубликатная запись, хэшированная по старому email_md5, лежала в другом шарде
            if AsyncSQLIndex(new_email_md5) == AsyncSQLIndex( old_email_md5 ):
                info("pwcChangeEmail qiery (old_email_md5 != pwc_snuid): UPDATE tbl_pwconnect SET email='%s', email_md5='%s' WHERE email_md5='%s'"  % ( new_email, new_email_md5, old_email_md5))
                # и новая запись должна лежать там же: делаем апдейт
                AsyncSQL(old_email_md5).addExec("UPDATE tbl_pwconnect SET email=%s, email_md5=%s WHERE email_md5=%s",
                                                callback=info_sql_callback, params= ( new_email, new_email_md5, old_email_md5,),
                                                args= ( new_email, new_email_md5, old_email_md5,),
                                                opname="pwcChangeEmail")  # для дубликата callback не слушаем
                return # в этом случае делать INSERT с new_email_md5 не надо, уже проапдейтили
            else:
                # а новая запись должна лежать в другом шарде: старую удаляем
                info("pwcChangeEmail qiery (old_email_md5 == pwc_snuid): DELETE FROM tbl_pwconnect WHERE email_md5='%s'" % (old_email_md5))
                AsyncSQL(old_email_md5).addExec("DELETE FROM tbl_pwconnect WHERE email_md5=%s",
                                                callback=info_sql_callback, params=(old_email_md5,),
                                                args=(old_email_md5,), opname="pwcChangeEmail") # для дубликата callback не слушаем

        if AsyncSQLIndex(new_email_md5) != AsyncSQLIndex( str(pwc_snuid) ):
            # дубликатная запись, хэшированная по новому email_md5, должна лежать в другом шарде
            info(u"pwcChangeEmail query (new_email_md5 != pwc_snuid): INSERT INTO tbl_pwconnect (email,email_md5,pwc_snuid,pwd_md5,ip,gender,birthdate) VALUES ('%s','%s',%d,'%s','%s',%d,%d)"
                % ( new_email, new_email_md5, pwc_snuid, str(pwc.secret), str(pwc.ip), toint(pwc.gender), toint(pwc.birthdate)))
            AsyncSQL(new_email_md5).addExec("INSERT INTO tbl_pwconnect (email,email_md5,pwc_snuid,pwd_md5,ip,gender,birthdate) "
                                            "VALUES (%s,%s,%s,%s,%s,%s,%s)", callback=info_sql_callback,
                                            params=(new_email, new_email_md5, pwc_snuid, str(pwc.secret), str(pwc.ip), toint(pwc.gender), toint(pwc.birthdate),),
                                            args=(new_email, new_email_md5, pwc_snuid, str(pwc.secret), str(pwc.ip), toint(pwc.gender), toint(pwc.birthdate),),
                                            opname="pwcChangeEmail")

    def pwcMerge(self, email_md5, main_auid, delete_auid, callback=info_sql_callback):
        info( "pwcMerge query: UPDATE tbl_pwconnect SET auid=%d WHERE email_md5='%s' AND auid=%d", tolong(main_auid), email_md5, tolong(delete_auid))
        AsyncSQL(email_md5).addExec("UPDATE tbl_pwconnect SET auid=%s WHERE email_md5=%s AND auid=%s",
                                    callback=callback, params=(tolong(main_auid), email_md5, tolong(delete_auid),),
                                    args=(tolong(main_auid), email_md5, tolong(delete_auid),), opname="pwcMerge")

    # --------------------------------------------------------
    # Social Exchange
    def seGetMessages(self, x_login, callback=None):
        info( "seGetAll query: SELECT `id`,`type`,`msg`,`expire` FROM tbl_message WHERE `to`='%s'", x_login)
        AsyncSQL( str(x_login) ).addQuery("SELECT `id`,`type`,`msg`,`expire` FROM tbl_message WHERE `to`=%s",
                                          callback=callback, params=(x_login,),args=(x_login,), opname="seGetMessages")

    def seAddMessage(self, to_login, msg_id, msg_type, message, to_uid=0, expire=0, callback=None):
        debug(u"seAddMessage query: INSERT INTO tbl_message (`uid`,`id`,`type`,`msg`,`expire`,`to`) VALUES(%d,%d,'%s','%s',%d,'%s')",
              to_uid, msg_id, msg_type, message, expire, to_login)
        AsyncSQL( str(to_login) ).addExec("INSERT INTO tbl_message (`uid`,`id`,`type`,`msg`,`expire`,`to`) VALUES(%s,%s,%s,%s,%s,%s)",
                                          callback=callback,
                                          params=(to_uid, msg_id, msg_type, message, expire, to_login),
                                          args=(to_uid, msg_id, msg_type, message, expire, to_login),
                                          opname="seAddMessage")

    def seDeleteMessages(self, x_login, msg_id_list, callback=None):
        mask = ','.join("%s" for x in xrange(len(msg_id_list)))
        info( "seDeleteMessages query: DELETE FROM tbl_message WHERE `id` IN (%s)" % (strList(msg_id_list)))
        AsyncSQL( str(x_login) ).addExec("DELETE FROM tbl_message WHERE `id` IN ("+mask+")",
                                         callback=callback, params=msg_id_list,
                                         args=msg_id_list, opname="seDeleteMessages")

    def seFindLogin(self, x_login, callback=None):
        info( "seFindLogin query: SELECT `id`,`server_id` AS ws FROM tbl_login WHERE login=%r" % x_login)
        AsyncSQL( str(x_login) ).addQuery("SELECT `id`,`server_id` AS ws FROM tbl_login WHERE login=%s",
                                          callback=callback, params=(x_login,), args=(x_login,), opname="seFindLogin")

    # собирать протухшие сообщения надо со всех mysql шардов, и callback будет вызван N раз
    def seGetExpiredMessages(self, timestamp_now, callback=None):
        info( "seGetExpiredMessages query: SELECT `id`,`type`,`to`,`expire` FROM tbl_message WHERE `expire`<%d" % (tolong(timestamp_now)))
        for sql in self.loop.sql:
            sql.addQuery("SELECT `id`,`type`,`to`,`expire` FROM tbl_message WHERE `expire`<%s",
                         callback=callback, params=(timestamp_now,), args=(timestamp_now,),
                         opname="seGetExpiredMessages")

    # --------------------------------------------------------
    # Access Restrictions
    def cbtAddRestrictedUser(self, login, timestamp=0, access_key='', callback=None):
        info( "cbtAddRestrictedUser query: INSERT INTO tbl_user_restrictions (`login`,`timestamp`,`key`) VALUES ('%s',%d,'%s')" % (login, timestamp, access_key))
        FirstSQL().addExec("INSERT INTO tbl_user_restrictions (`login`,`timestamp`,`key`) VALUES (%s,%s,%s)",
                           callback=callback, params=(login, timestamp, access_key,),
                           args=(login, timestamp, access_key,), opname="cbtAddRestrictedUser" )

    def cbtCheckUserRestrictions(self, login_list, callback=None):
        info( "cbtCheckUserRestrictions query: SELECT id FROM tbl_user_restrictions WHERE `login` IN (%s)" % reprList(login_list))
        mask = ','.join("%s" for x in xrange(len(login_list)))
        FirstSQL().addQuery("SELECT id FROM tbl_user_restrictions WHERE `login` IN ("+ mask + ")",
                            callback=callback, params=login_list, args=login_list,
                            opname="cbtCheckUserRestrictions" )

    def cbtCheckIpAllowances(self, ip, callback=None):
        info( "cbtCheckIpAllowances query: SELECT id FROM tbl_ip_allowances WHERE `ip`=%r" % ip)
        FirstSQL().addQuery("SELECT id FROM tbl_ip_allowances WHERE `ip`=%s",
                            callback=callback, params=(ip,), args=(ip,), opname="cbtCheckIpAllowances" )


    # --------------------------------------------------------
    # Administrator messages
    def addAdminMessage(self, login, instance_id, messageTitle, messageText, gmLogin, timestamp, callback=None):
        FirstSQL().addExec("INSERT INTO tbl_admin_messages (`login`, `instance_id`, `title`, `message`, `gmlogin`, `timestamp`) "
                                  "VALUES (%s,%s,%s,%s,%s,%s)",
                                   callback=callback, params=(login, instance_id, messageTitle, messageText, gmLogin, timestamp,),
                                   args=(login, instance_id, messageTitle, messageText, gmLogin, timestamp,), opname="addAdminMessage")


    def getAccountAdminMessages(self, login, callback=None):
        info( "getAccountAdminMessages query: SELECT * FROM tbl_admin_messages WHERE `login`=%r" % login)
        FirstSQL().addQuery("SELECT * FROM tbl_admin_messages WHERE `login`=%s",
                            callback=callback, params=(login,), args=(login,), opname="getAccountAdminMessages" )
