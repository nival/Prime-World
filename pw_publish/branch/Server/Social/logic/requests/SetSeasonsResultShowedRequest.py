# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class SetSeasonsResultShowedRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        self.seasonId = self.getIntParam("seasonId")
        if self.seasonId == None:
            self.badParam("seasonId")
        
        
        self.isShowed = self.getBoolParam("isShowed")
        if self.isShowed == None:
            self.badParam("isShowed")
        
        


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
            self.arguments = SetSeasonsResultShowedRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())