# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class PartyHeroRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        self.hero_id = self.getIntParam("hero_id")
        if self.hero_id == None:
            self.badParam("hero_id")
        
        
        self.hero_crc = self.getIntParam("hero_crc")
        if self.hero_crc == None:
            self.badParam("hero_crc")
        
        

        self.guardParty = self.getBoolParam("guardParty", False)
        self.master_auid = self.getIntParam("master_auid", 0)
        self.talent_set_id = self.getIntParam("talent_set_id", 0)

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
            self.arguments = PartyHeroRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())