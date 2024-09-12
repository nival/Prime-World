# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class BuyCustomFlagRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        self.flagId = self.getStringParam("flagId")
        if self.flagId == None:
            self.flagId = ""
        
        
        self.guardParty = self.getBoolParam("guardParty")
        if self.guardParty == None:
            self.badParam("guardParty")
        
        
        self.master_auid = self.getIntParam("master_auid")
        if self.master_auid == None:
            self.badParam("master_auid")
        
        


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
            self.arguments = BuyCustomFlagRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())