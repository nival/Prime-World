# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging, re

from subaction import SubAction, action_timing

from base.helpers import *
from tornado.options import options
from handlers import users

## ---------------------------------------------------------------
## ---------------------------------------------------------------


class PingAction( SubAction ):
    """ Отложенный поллинг: клиент присылает запрос, который висит на сервере до таймаута или до момента, когда серверу есть что сказать юзеру """
    
    ## action, который будет обрабатывать данный класс:
    action = "ping"
    
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.start_time = time.time()
        info( "PingAction: uid=%d, start_time=%5.3f" % (self.acc.uid, self.start_time) )
        
        self.wait = self.getIntParam("wait", 0) 
        self.wait = min( self.wait, self.I.WS.POLLING_PING_TIMEOUT ) # больше, чем указанный таймаут, ждать не разрешаем
                    
        ###### if self.acc.pending_events or (self.wait <= 0):
        if 1: ## WORKAROUND АП8: механизм ping работает БЕЗ long polling, всегда отвечает сразу
            # серверу _уже_ есть что сказать, либо в параметрах сказали "не ждать"; отвечаем мгновенно
            self.pending_timeout = None
            self.pingReply()
        
        else:
            # вешаем таймаут (если за 15 секунд ничего не произойдет, pingReply вызовется просто по таймауту)
            loop = self.I.WS.getIOLoop()
            self.pending_timeout = loop.add_timeout(self.start_time + self.wait, self.onTimeoutReply)
            self.acc.pending_handler = self.onPingReply # а если что-нибудь произойдет, пусть нас дернут по этому хвостику
            
    @action_timing
    def onTimeoutReply(self):
        # нас вызвали по таймауту: значит таймаут из IOLoop убирать не нужно
        self.pending_timeout = None
        self.pingReply()

    @action_timing
    def onPingReply(self):
        self.pingReply()
        
    def pingReply(self):
        if self.pending_timeout:
            # если нас вызвали раньше времени (прямым вызовом, не по таймауту), нужно удалить повешенный в IOLoop "вызов по таймауту":
            loop = self.I.WS.getIOLoop()
            loop.remove_timeout( self.pending_timeout )
        
        self.response["ok"] = 1
        self.response["response_time"] = "%5.3f" % time.time()
        
        self.sendPendingEvents() # заворачиваем накопившиеся pending events
        self.acc.pending_handler = None # ждем следующего пинга
        
        ##info( "PingAction reply: uid=%d, response str:%s" % (self.acc.uid, self.response) )
        info( "PingAction reply: uid=%d, response:%s" % (self.acc.uid, self.I.MD.pretty(self.response)) )
        
        self.fin()
        
        
        
## ---------------------------------------------------------------
## ---------------------------------------------------------------

class WakeAction( SubAction ):
    """ Все что мы делаем - это "будим" юзера, ждущего свой отложенный пинг (кладем ему в pending_events тестовое сообщение и дергаем его acc.pending_handler """
    
    ## action, который будет обрабатывать данный класс:
    action = "wake"
    
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        if self.checkValidIntParam( "wake_uid" ):
            wake_acc = users.get(self.wake_uid)
            if wake_acc:
                self.response["ok"] = 1
                wake_acc.pending_events.append( "WAKE from uid=%d" % self.acc.uid )
                
                if wake_acc.pending_handler:
                    wake_acc.pending_handler()
                    self.response["waken"] = "ok"
                else:
                    self.response["waken"] = "no pending handler"
                    
            else:
                self.response["error"] = "no such user on server"
    
        self.fin()