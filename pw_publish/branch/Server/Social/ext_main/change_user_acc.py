# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging

from subaction import SubAction, action_timing
from base.helpers import *

## ---------------------------------------------------------------
## ---------------------------------------------------------------

class ChangeUserAccAction( SubAction ):
    ## action, который будет обрабатывать данный класс:
    action = "change_user_acc"

    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        if self.acc.admin: # safeguard: поставить этот флаг можно только руками в mysql
            if self.checkValidIntParam('acc_auid'):
                dest_acc = self.I.WS.getUserAccByAuid( self.acc_auid )
                if dest_acc:
                    if self.checkValidParam('acc_path'):
                        value = self.getParam("string_value")
                        if value:
                            value = utf8convert( value )
                            info("ChangeUserAccAction: parsed string value (utf8): %r" % value)
                        else:
                            json_value = self.getParam('json_value')
                            if json_value:
                                value = self.getJsonParam('json_value')
                                info("ChangeUserAccAction: parsed json value %r (class %r)" % (value, value.__class__.__name__))
                            else:
                                return self.fail("no json_value", EC.BAD_PARAM)
                                
                        try:
                            result = pathInsertKeyAttr(dest_acc, self.acc_path, value)
                            self.response["result"] = result 
                            info( "ChangeUserAccAction(admin auid=%s): dest_acc auid=%d, path=%s, value %r, insert result %r" \
                                % (self.acc.auid, dest_acc.auid, self.acc_path, value, result) )
                        except:
                            catch()
                            
                        self.response["ok"] = 1
                        
                else:
                    return self.fail('no dest acc (auid=%s)' % self.acc_auid, EC.BAD_PARAM)
        else:
            warn("ChangeUserAccAction: no admin flag for auid=%s" % self.acc.auid)
            
        self.fin()

