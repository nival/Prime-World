# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging

sys.path.append( os.path.abspath('..') )
from subaction import SubAction, action_timing

sys.path.append( os.path.abspath('../base') )
from helpers import *

## ---------------------------------------------------------------
## ---------------------------------------------------------------


class CCUAction( SubAction ):
    ## action, который будет обрабатывать данный класс:
    action = "ccu"
    
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        log("CCUAction.onStart")
        
        if self.acc.admin:
            self.response["ccu"] = self.I.WS.CCU
            self.response["ok"] = 1
            
            self.response["instrActions"] = times2msec( self.I.WS.instrActions )
            self.response["instrActionsHistory"] = times2msec( self.I.WS.instrActionsHistory )
            
        self.fin()


