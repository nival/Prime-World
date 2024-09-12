# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class UpgradeTalentRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        target_talent_id = self.getKeeperObjectIDParam("target_talent_id", modeldata)
        self.target_talent = modeldata.getTalentByID(target_talent_id)
        if not self.target_talent:
            self.badParam("target_talent")
        
        
        self.points = self.getIntParam("points")
        if self.points == None:
            self.badParam("points")
        
        


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
            self.arguments = UpgradeTalentRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())