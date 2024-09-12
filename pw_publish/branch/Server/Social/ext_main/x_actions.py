# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging
from base64 import b64encode

# чтобы питон правильно понимал относительные пути модулей:
def _addPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)

#_addPath('..')

from handlers import * # JsonHandler, globals: peers, users..
from subaction import SubAction, action_timing
from instr import *

import MM
import EC
import CC

DEFAULT_MSG_EXPIRATION_TIME = 30*24*60*60 # по умолчанию храним месяц

##-------------------------------------------------------------------------------------
##-------------------------------------------------------------------------------------

class XSendAction( SubAction ):
    """ Cлужебный логический handler, поддерживает единственный 'action=send' """
    # recipient=INT64,  // auid пользователя, которому посылают сообщение
    # project=STRING    // строка с названием проекта, в который посылается сообщение
    action = "send"

    #------------------------------------------------------------------------------------
    def getSender(self):
        if self.redirected:
            self.sender = self.getParam("sender")
        else:
            self.sender = self.acc.login

    #------------------------------------------------------------------------------------
    @action_timing
    def onStart(self):
        info("XSendAction.onStart args %r", self.arguments)
        self.is_packet = self.getParam("is_packet")
        self.project = self.getParam("project")
        self.recipient = self.getIntParam("recipient", 0)
        if self.is_packet:
            self.req = self.getParam("body")
            self.body = json_dumps(self.req)
            self.parseMessage(self.req)
            return
        else:
            self.body = self.request.request.body
            self.parseMessage(json_loads(self.request.request.body))
            return


    def parseMessage(self, body):
        self.dest_login = "%s:%s" % (self.project, self.recipient)
        self.redirected = self.getIntParam("re", 0)

        if not self.recipient:
            return self.fail( "bad destination auid (%s)" % self.auid, EC.XS_BAD_DEST_AUID )

        if self.project not in CC.EXCHANGE_PROJECTS:
            return self.fail( "bad destination project %s, allowed: %r" % (self.project, CC.EXCHANGE_PROJECTS), EC.XS_BAD_DEST_PROJECT )

        self.getSender()
        try:
            debug("XSendAction.onStart body: %r, sender %r", body, self.sender)
            self.messages = body
            # проверим, что тело POST-сообщения представляет собой список словарей-сообщений, и у каждого сообщения есть валидный type (строка)
            #FIXME заменить asset на приличную обработку!!!
            assert( isinstance(self.messages, list) )
            for msg in self.messages:
                assert( isinstance(msg, dict) )
                msg_type = msg.get("type", "")
                assert( isinstance(msg_type, basestring) )
                if msg_type in ("session_awards", "s_guild_awards"):
                    self.I.WS.CCU[msg_type] += 1

                # добавляем к каждому сообщению автограф отправителя
                msg["sender"] = self.sender
        except:
            catch()
            try:
                warn("bad send message body: %r" % body)
            except:
                catch()
            return self.fail( "bad send message body", EC.XS_BAD_SEND_MESSAGE_BODY )

        # ок, похоже на логин-пароль.
        debug("current logins (%s)", logins)
        debug("current users (%s)", users)
        self.dest_sid = logins.get(self.dest_login.lower(), 0) # есть такой в списке логинов?
        self.dest_acc = users.get(self.dest_sid)
        if self.dest_acc:
            # адресат прямо у нас на сервере
            info("DESTINATION REACHED(%s)", self.dest_login)

            # добавляем сообщения на dest_acc + сохраняем в mysql
            self.addMessages(self.dest_acc, self.dest_acc.uid, self.messages)

            # сразу прописываем результат запроса
            self.response["result"] = "delivered"
            self.response["ok"] = 1

            # ждем, когда нам ответят на все sql-запросы
            return

        else:
            # у нас нет такого логина; ок, поехали доставать данные из persistent (mysql)
            info("look for login for dest_login=%s", self.dest_login)
            self.I.SQL.seFindLogin( self.dest_login, self.onFindLogin )
            return

    #------------------------------------------------------------------------------------
    def addMessages(self, dest_acc, dest_uid, messages):
        self.add_msg_ids = {} # по этому словарю будем контролировать добавление сообщений в mysql; когда всё добавится, успокоимся и вернем ответ на method=send
        self.response["failed"] = {}
        send_timestamp = toint( time.time() )
        for msg in messages:
            # присваиваем сообщению msg_id, проставляем время получения
            msg_id = self.I.WS.nextInt64GUID( "msg_id" )
            msg["dt_rcv"] = send_timestamp

            tm_expire = toint( msg.get("tm_expire", DEFAULT_MSG_EXPIRATION_TIME) )
            if tm_expire:
                timestamp_expire = tm_expire + send_timestamp
            else:
                timestamp_expire = 0

            if dest_acc:
                dest_acc.messages[msg_id] = msg
            self.add_msg_ids[msg_id] = 1

            json_message = json_dumps(msg)
            debug("writing json_message: %s  for dest_uid %s dest_acc %s", msg, dest_uid, dest_acc)
            encoded_message = b64encode(json_message)
            debug("writing encoded_message (len %s) for dest_uid %s", len(encoded_message), dest_uid)
            self.I.SQL.seAddMessage( self.dest_login, msg_id, msg["type"], encoded_message, expire=timestamp_expire, to_uid=dest_uid, callback=self.onAddSqlMessage )

    #------------------------------------------------------------------------------------
    @action_timing
    def onAddSqlMessage(self, sql_reply):
        debug("onAddSqlMessage(dest_login %s) sql reply: %s", self.dest_login, sql_reply)
        try:
            uid, msg_id, tp, json_message, exp, to = sql_reply["p"]
            reply = sql_reply["r"]
            assert(reply)
        except:
            catch()
            self.response["failed"][ msg_id ] = json_message

        self.add_msg_ids.pop( msg_id )
        info("onAddSqlMessage add_msg_ids: %s", self.add_msg_ids)
        if not self.add_msg_ids: # список пустой, все сообщения дошли до sql
            #
            #TODO: PUSH messages to online client
            #
            debug("onAddSqlMessage dest_acc: %s", self.dest_acc)
            if self.dest_acc:
                info("check push: url %s", self.dest_acc.push_url)
                if self.dest_acc.push_url:
                    self.I.WS.pushAccountMessages(self.dest_acc)

            return self.fin()


    #------------------------------------------------------------------------------------
    # получили ответ на find_login
    @action_timing
    def onFindLogin(self, sql_reply):
        self.dest_uid = 0
        r = sql_reply["r"]
        info( "-- onFindLogin: sql reply: " + str(sql_reply) )
        if r:
            self.dest_uid, self.dest_wsid = r[0].id, r[0].ws
            dest_peer = self.I.WS.peers.get(self.dest_wsid)
            if self.dest_uid:
                if dest_peer:
                    if not self.redirected:
                        # переадресуем запрос dest-серверу
                        info("REDIRECT MSG SEND (%s)" % self.dest_login)

                        # внутрикластерный редирект
                        redirect_args = dict(
                            method = "send",
                            project = self.project,
                            recipient = self.recipient,
                            re = 1,
                            sender = self.sender,
                        )

                        self.response["redirect_from"] = options.server_name
                        self.response["redirect_from_wsid"] = options.server_id
                        self.response["redirect_to"] = dest_peer["name"]
                        self.response["redirect_to_wsid"] = self.dest_wsid

                        self.I.WSX.post( dest_peer["addr"], redirect_args, self.body, self.onSendRedirect, subrequest="x" )
                        return

                    else:
                        return self.fail( "nested redirect", EC.XS_NESTED_REDIRECT )

        # юзер существует, но не залоган; можно писать сообщение прямо в mysql-базу
        #
        #(!АХТУНГ, тут возможен race condition, если юзер уже в процессе логина, и успеет достать из mysql список своих сообщений до завершения нашего INSERT)
        # => ПО-ХОРОШЕМУ, НАДО ЗАЛОЧИТЬ ЮЗЕРА В MYSQL, ДОБАВИТЬ ЕМУ СООБЩЕНИЯ, А ПОТОМ ОТПУСТИТЬ LOGIN LOCK
        #
        info("SAVE MSG TO MYSQL (%s)", self.dest_login)

        # добавляем сообщения на dest_acc + сохраняем в mysql
        self.addMessages(None, toint(self.dest_uid), self.messages)

        # сразу прописываем результат запроса
        self.response["result"] = "stored"
        self.response["ok"] = 1

        return # ждем, пока sql обработает все сообщения

        # не знаем такого логина, пока просто обламываемся
        #~ return self.fail( "unknown dest login: %r" % self.dest_login, EC.XS_NO_DEST_LOGIN )


    #------------------------------------------------------------------------------------
    # получили ответ от peer-сервера на redirect
    @action_timing
    def onSendRedirect( self, redirect_response ):
        info("XSendAction.onSendRedirect: response %s", redirect_response)
        # тупо передаем то, что ответили, клиенту
        self.response.update( redirect_response )
        self.fin()


##-------------------------------------------------------------------------------------
##-------------------------------------------------------------------------------------

class XSendNoLoginAction( XSendAction ):
    """ вариант send без необходимости логиниться """
    action = "send_nl"

    @action_timing
    def onStart(self):
        info("XSendNoLoginAction.onStart args %r", self.arguments)
        if self.getBoolParam("is_packet"):
            debug("XSendNoLoginAction.onStart body %r", self.request.request.body)
            messages = json_loads(self.request.request.body)
            if isinstance(messages, list):
                for x in messages:
                    self.project = x.get("project" )
                    self.recipient = x.get("recipient", 0)
                    self.request = x.get("request")
                    args = ClassDict(project=[self.project],
                                     recipient=[self.recipient],
                                     body=[[self.request]],
                                     is_packet=[True],
                                     )
                    sender = self.getParam("sender")
                    if sender:
                        args["sender"] = [sender]
                    action = XSendAction(args, self.onDummy, I=self.I)
                    action.onStart()
                self.fin()
            else:
                err("XSendNoLoginAction: is_packet is True, but the body isn't a list (type = %s)", type(messages))
                self.errorResponse(EC.BAD_PARAM, "Not a list used with is_packet.")
        else:
            XSendAction.onStart(self)

    def onDummy(self, response):
        pass

    # отличается только тем, что всегда верим клиенту на слово по поводу sender:
    def getSender(self):
        self.sender = self.getParam("sender")


##-------------------------------------------------------------------------------------
##-------------------------------------------------------------------------------------

class XReceiveAction( SubAction ):
    """ забрать список активных сообщений """
    action = "retrieve"

    @action_timing
    def onStart(self):
        info("XReceiveAction.onStart")
        self.response["messages"] = self.acc.messages
        self.response["ok"] = 1
        self.fin()


##-------------------------------------------------------------------------------------
##-------------------------------------------------------------------------------------

class XPurgeAction( SubAction ):
    """ забрать список активных сообщений """
    action = "purge"

    @action_timing
    def onStart(self):
        info("XPurgeAction.onStart")
        self.failed = {}
        self.delete_list = []
        try:
            self.ids = json_loads(self.request.request.body)
            # проверим, что тело POST-сообщения представляет собой список msg_id
            assert( isinstance(self.ids, list) )
            for str_msg_id in self.ids:
                msg_id = toint(str_msg_id)
                msg = self.acc.messages.get( msg_id )
                if msg:
                    self.delete_list.append( msg_id )
                else:
                    self.failed[ msg_id ] = EC.XS_NO_SUCH_MESSAGE

            if self.failed:
                self.response["failed"] = self.failed

            if self.delete_list:
                return self.I.SQL.seDeleteMessages( self.acc.login, self.delete_list, callback=self.onSqlDelete )
            else:
                return self.fail( "no messages to delete", EC.XS_NO_MESSAGES_TO_DELETE )

        except:
            catch()
            return self.fail( "bad purge message body", EC.XS_BAD_PURGE_MESSAGE_BODY )

    #------------------------------------------------------------------------------------
    @action_timing
    def onSqlDelete(self, sql_reply):
        r = sql_reply["r"]
        info( "-- onSqlDelete: sql reply: " + str(sql_reply) )
        if r:
            for msg_id in self.delete_list:
                self.acc.messages.pop( msg_id, None )
            self.response["purged"] = self.delete_list
            self.response["ok"] = 1
            self.fin()
        else:
            return self.fail( "sql failed to delete messages", EC.XS_SQL_DELETE_FAIL )


class XSendToFriendsAction(SubAction):
    action = "send_to_friends"

    @action_timing
    def onStart(self):
        auid = toint(self.getParam("auid"))
        info("XSendToFriendsAction: for auid [%r]", auid)
        if  auid:
            if self.request.request.body:
                self.message = json_loads(self.request.request.body)
                method = self.message.get("method")
                if method == "refresh_friends" :
                    info("refresh friends auid [ " + str(auid) + "]")
                    self.I.FS.refreshFriendList(auid, self.onSendRefresh)
                    return
                else:
                    warn("BAD  method %s skipped", method)
            else:
                warn("Request body is empty!")
        else:
            warn("BAD params skipped")
        self.fin()

    def onSendRefresh(self, response):
        #info("SendFreandsRefreshAction: onSendRefresh %r" % response)
        self.response["ok"] = 1
        self.fin()

