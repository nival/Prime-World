# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# IMatchmaker: интерфейс pvx matchmaking service (он же и mock-заглушка)
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *
import functools

from tornado.options import define, options
from tornado.httpclient import HTTPRequest

import MM # matchmaking const

##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class IMatchmaker:
    """ Базовый интерфейс для серверных matchmaking-запросов """
    
    def __init__(self, HTTP=None):
        self.HTTP = HTTP
        
    def stepSessions(self):
        pass

    def handlePacket(self, mm_packet, send_addr=None, callback=None):
        # возвращаем пустой ответ (но грамматически правильный для парсера на стороне WebServer)
        self.reply = {}
        self.fin( self.reply, callback )
        
    def fin(self, reply, callback):
        if callback:
            reply_json = '{"response":{"pvx":%s}}' % json_dumps(reply)
            http_reply = ClassDict( body=reply_json )
            callback( http_reply )
        else:
            return reply
        
## ------------------------------------------------------------------------------------------
## ------------------------------------------------------------------------------------------

class HttpMatchmaker( IMatchmaker ):
    """ Реальная связь по HTTP с удаленным pvx matchmaking сервером. """

    def handlePacket(self, mm_packet, send_addr=None, callback=None):
        self.t0 = time.time()
        _fetch_callback = functools.partial( self.onFetch, icallback=callback )
        url = http_prefix( "%s/x?action=mm" % send_addr )
        request = HTTPRequest( url=url, method="POST", body=json_dumps(mm_packet), use_gzip=False )
        self.HTTP.fetch( request, _fetch_callback, connect_timeout=8.0, request_timeout=20.0)
        
    def onFetch(self, response, icallback=None):
        self.t1 = time.time()
        try:
            ##log( "HttpMatchmaker onFetch(%s) t%0.3f: %s" % ( self.request, self.t1-self.t0, str(response) ) )
            if icallback:
                icallback( response )
        except:
            catch()

## ------------------------------------------------------------------------------------------
## ------------------------------------------------------------------------------------------

class MockMatchmaker( IMatchmaker ):
    """ Заглушка, умеет притворяться pvx matchmaking сервером. """
    
    handlers = [ # чтобы не ломался порядок обработки команд (cancel в первую очередь; ping в последнюю очередь, после add/accept)
        ( "cancel", "onCancel" ), 
        ( "add",    "onAdd" ),
        ( "accept", "onAccept" ),
        ( "ping",   "onPing" ),
    ]
    
    MM_PROGRESS_STEP = 50
    
    GUARDS_TAMBUR_SIZE = 5
    
    # -----------------------------------------------
    def __init__(self, HTTP=None):
        self.mm = {}
        self.guards_requests = []
        self.session_id_autoinc = 1
        self.HTTP = HTTP
        
    # -----------------------------------------------
    # якобы увеличиваем "прогресс" текущих сессий, до max=MM.STATUS_WAITING_ACCEPT
    def stepSessions(self):
        if self.mm:
            for uid, session in self.mm.iteritems():
                mmid = session.mmid
                # если мы в процессе mathcmaking, двигаем "прогресс матчмейкинга"
                if session.progress:
                    prev_progress = session.progress
                    if prev_progress < MM.MAX_PROGRESS:
                        session.progress = min( prev_progress + self.MM_PROGRESS_STEP, MM.MAX_PROGRESS )
                    
                        if prev_progress < MM.MAX_PROGRESS and session.progress >= MM.MAX_PROGRESS:
                            info( "stepSessions: matchmaking finished (uid %s, mmid %s)" % (uid, mmid) )
                            session.accepted = session.accepted or 0 # с этого момента принимаем команду accept для этого mmid 
                            
                    # если начало сессии подтверждено, двигаем "прогресс игры"
                    if session.accepted:
                        if not session.playing:
                            session.playing = 1
                            
                            # генерируем сессионный ключ
                            session_id = "sk_%d_%d" % (int(time.time()), self.session_id_autoinc)
                            self.session_id_autoinc += 1
                            session.session_id = session_id
                            
                        prev_progress = session.playing
                        if prev_progress < MM.MAX_PROGRESS:
                            session.playing = min( prev_progress + self.MM_PROGRESS_STEP, MM.MAX_PROGRESS )
                            
            self.stepGuardsMaking()
        
    # -----------------------------------------------
    def stepGuardsMaking(self):
        while len(self.guards_requests) >= self.GUARDS_TAMBUR_SIZE:
            info( "stepGuardsMaking guards_requests: %s" % self.guards_requests )
            tambur_uids = self.guards_requests[:self.GUARDS_TAMBUR_SIZE]
            self.guards_requests = self.guards_requests[self.GUARDS_TAMBUR_SIZE:]
            info( "stepGuardsMaking tambur_uids: %s, guards_requests now: %s" % (tambur_uids, self.guards_requests) )
            
            # создаем новую "гвардейскую инфу"
            self.session_id_autoinc += 1
            game_id = self.session_id_autoinc
            allies = []
            for uid in tambur_uids:
                allies.append( { "uid":str(uid), "rdy":0 } )
            guards_info = {
                "guards_game":1,
                "allies": allies,
                "foes_rdy": 1,
            }
            
            for uid in tambur_uids:
                session = self.mm[uid]
                session.guards_info = guards_info
                session.game_id = game_id
    
    # -----------------------------------------------
    # map to section handlers
    def handlePacket(self, mm_packet, send_addr=None, callback=None):
        ## STEP: якобы увеличиваем "прогресс" текущих сессий
        #~ self.stepSessions()
        self.reply = {}
        
        if mm_packet:
            info( "IMatchmaker.handlePacket (self %s): " % self + pretty(mm_packet) )

            # map packet sections (sub-keys) to handler methods
            for cmd_handler_pair in self.handlers:
                cmd, handler = cmd_handler_pair
                subdict = mm_packet.get(cmd)
                if subdict:
                    method = getattr(self, handler, None)
                    if method:
                        method(subdict)
    
        return self.fin( self.reply, callback )
                
    # -----------------------------------------------
    def onAdd(self, dct):
        for uid in sorted(dct.keys()):
            session_request = dct.get(uid)
            mmid = session_request.mmid
            if not self.mm.has_key( uid ):
                # не разрешаем больше одной сессии для одного uid
                session = ClassDict( session_request )
                session.progress = 2
                session.game_id = 0
                session.guards_info = 0
                self.mm[uid] = session
                
                if session.guard_only:
                    self.guards_requests.append(uid)
                
                # добавляем строчку к ответу
                subInsert(self.reply, ("add", uid), session.progress)
                
            else:
                # failed (уже есть сессия у данного uid)
                subInsert(self.reply, ("add", uid), 0)
                    
        ##err( "MockMatchmaker.onAdd: dct " + pretty(dct) + "\n mm now: " + pretty(self.mm) )
                

    # -----------------------------------------------
    def onPing(self, dct):
        for uid in sorted(dct):
            # всегда запрашиваем статус любой (имеющейся) сессии данного юзера
            session = self.mm.get(uid)
            if session:
                # добавляем строчку к ответу
                session_id = session.session_id or 0
                subInsert(self.reply, ("ping", uid), [session.progress, session_id, 0,0,0,0, session.game_id, session.mmid, session.guards_info])
            else:
                # нету сессий для этого юзера
                subInsert(self.reply, ("ping", uid), 0)
                    
        info( "IMatchmaker.onPing: dct " + pretty(dct) + "\n reply now: " + pretty(self.reply) )

    # -----------------------------------------------
    def onCancel(self, dct):
        for uid in sorted(dct):
            if uid in self.mm:
                self.mm.pop( uid )
                cancel_result = 1 
            else:
                cancel_result = 0
                
            # добавляем строчку к ответу
            subInsert(self.reply, ("cancel", uid), cancel_result)
                    
        info( "IMatchmaker.onCancel: dct " + pretty(dct) + "\n mm now: " + pretty(self.mm) + "\n reply now:" + pretty(self.reply) )
        
        
    # -----------------------------------------------
    def onAccept(self, dct):
        for uid in sorted(dct):
            accept_result = 0
            session = self.mm.get(uid)
            if session and session.accepted != None:
                session.accepted = 1
                session.progress = MM.PROGRESS_ACCEPTED
                accept_result = 1
                
            # добавляем строчку к ответу
            subInsert(self.reply, ("accept", uid), accept_result)
                        
        info( "IMatchmaker.onAccept: dct " + pretty(dct) + "\n mm now: " + pretty(self.mm) + "\n reply now: " + pretty(self.reply) )

