# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class SetSiegeDurationRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        self.targetAuid = self.getIntParam("targetAuid")
        if self.targetAuid == None:
            self.badParam("targetAuid")
        
        
        self.duration = self.getIntParam("duration")
        if self.duration == None:
            self.badParam("duration")
        
        


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
            self.arguments = SetSiegeDurationRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())