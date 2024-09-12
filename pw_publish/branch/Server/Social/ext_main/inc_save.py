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


class IncSaveAction( SubAction ):
    ## action, который будет обрабатывать данный класс:
    action = "inc_save"
    
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        log("IncSaveAction.onStart")
        
        if self.acc.admin:
            self.acc.db.save_counter = self.acc.db.save_counter or 0
            self.acc.db.save_counter += 1
            # заказываем сохранение аккаунта (с новым save_counter)
            self.I.WS.saveUserData( self.acc )

            self.acc.db.save_counter += 1
            # сразу заказываем повтор сохранения аккаунта (должен прийти отказ, "уже сохраняем")
            self.I.WS.saveUserData( self.acc )
            
            info("IncSave: uid=%d, save_counter=%s" % (self.acc.uid, self.acc.db.save_counter))
            
            self.response["db"] = self.acc.db
            self.response["ok"] = 1
            
        self.fin()

