# -*- coding: utf-8 -*-

#!/usr/bin/env python

import sys, os, time, logging

from subaction import SubAction, action_timing
from base.helpers import *

from tornado.options import options
import base64

import EC
import coord_cfg

## ---------------------------------------------------------------
## ---------------------------------------------------------------

class MessageAction( SubAction ):
    ## action, который будет обрабатывать данный класс:
    action = "msg"

    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        log("MessageAction.onStart")
        
        self.I.CHAT.systemMessage( self.arguments['auid'], 
            base64.urlsafe_b64encode(self.arguments['title']), 
            base64.urlsafe_b64encode(self.arguments['text']), 
            self.onFinalResponse )
    
    @action_timing
    def onFinalResponse(self, json_response):
        info("MessageAction: response %s" % json_response)
        if json_response and json_response.get('ec', -1) == 0:
            self.response['ok'] = 1
        else:
            self.response['ok'] = 0
            self.response['ec'] = EC.CHAT_SERVICE_NOT_AVAILABLE
        self.fin()

