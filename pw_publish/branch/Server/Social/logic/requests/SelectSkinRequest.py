# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class SelectSkinRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        hero_id = self.getKeeperObjectIDParam("hero_id", modeldata)
        self.hero = modeldata.getHeroByID(hero_id)
        if not self.hero:
            self.badParam("hero")
        
        
        self.skin_id = self.getIntParam("skin_id")
        if self.skin_id == None:
            self.badParam("skin_id")
        
        
        self.guardParty = self.getBoolParam("guardParty")
        if self.guardParty == None:
            self.badParam("guardParty")
        
        
        self.master_auid = self.getIntParam("master_auid")
        if self.master_auid == None:
            self.badParam("master_auid")
        
        
        self.change_party_skin = self.getBoolParam("change_party_skin")
        if self.change_party_skin == None:
            self.badParam("change_party_skin")
        
        


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
            self.arguments = SelectSkinRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())