# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class PartyInviteRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        self.invite_auid = self.getIntParam("invite_auid")
        if self.invite_auid == None:
            self.badParam("invite_auid")
        
        
        self.as_enemy = self.getIntParam("as_enemy")
        if self.as_enemy == None:
            self.badParam("as_enemy")
        
        
        self.game_type = self.getStringParam("game_type")
        if self.game_type == None:
            self.game_type = ""
        
        
        self.with_bots = self.getIntParam("with_bots")
        if self.with_bots == None:
            self.badParam("with_bots")
        
        


    def badParam(self, name):
        self.bad_param_name = name
        self.bad_param = True

    def checkParams(self):
        if self.arguments.bad_param:
            self.errorResponse("bad param '" + self.arguments.bad_param_name + "'")
            return False
        return True    

    def getResponse(self):
      return self.response

    def parse(self):    
        if not isinstance(self.arguments, BaseRequest):
            self.arguments = PartyInviteRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())