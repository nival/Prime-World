#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from party_const import *
import MM

class Party_action( SubAction ):
    """action, который будет обрабатывать данный класс"""
    action = "party_"
    
    ## клиент запрашивает текущий статус mm-сессии     (mmid=0: всех текущих сессий)
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        info("ClientPartyAction.onStart")
        
        self.cmd = self.action
        if self.checkPossibleValue(self.cmd, PARTY_COMMANDS, "bad party command"):
            if self.acc.auid:
                ## info( "party request: %r" % self.request )
                ## info( "party arguments: %r" % self.arguments )
                
                if not self.getIntParam("party_id"):
                    self.addArguments( party_id=toint(self.acc.party_id) )
          
                # форвардим команду на PersonServer, вместе со всеми дополнительными параметрами
                full_args = self.getFlatParams()
                
                param_dict = self.getFlatParams( except_list=["cmd", "action", "uid", "key"] )
                ## info( "flat param_dict: %r" % param_dict )
                
                callback = functools.partial( self.I.WS.onPartyCmdCallback, uid=self.acc.uid, args=full_args )
                self.I.PS.sendPartyCmd( self.acc.auid, options.server_id, self.cmd, callback, **param_dict )
                
                self.response["ok"] = 1
            else:
                self.response["error"] = "no auid, can't use party commands"
                
        self.fin()