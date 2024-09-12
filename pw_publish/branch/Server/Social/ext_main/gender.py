# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging, re

from subaction import SubAction, action_timing 
from base.helpers import *
from tornado.options import options

import EC # error codes

## ---------------------------------------------------------------
## ---------------------------------------------------------------

class SetGenderAction( SubAction ):
    ## action, который будет обрабатывать данный класс:
    action = "set_gender"
    debug = True
    
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        info("SetGenderAction.onStart")
                    
        self.gender = self.getIntParam("gender", None)
        if self.gender:
            self.acc.db.sex = self.gender
 
        self.response["db"] = self.acc.db
        self.response["ok"] = 1
        self.fin()