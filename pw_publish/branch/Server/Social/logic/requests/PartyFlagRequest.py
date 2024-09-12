# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class PartyFlagRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        self.flag_type = self.getIntParam("flag_type")
        if self.flag_type == None:
            self.badParam("flag_type")
        
        
        self.flag_persistent_id = self.getStringParam("flag_persistent_id")
        if self.flag_persistent_id == None:
            self.flag_persistent_id = ""
        
        

        self.guardParty = self.getBoolParam("guardParty", False)
        self.master_auid = self.getIntParam("master_auid", 0)

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
            self.arguments = PartyFlagRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())