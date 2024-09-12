# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class AddStatisticRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        self.actionType = self.getIntParam("actionType")
        if self.actionType == None:
            self.badParam("actionType")
        
        
        self.description = self.getStringParam("description")
        if self.description == None:
            self.description = ""
        
        
        self.value = self.getIntParam("value")
        if self.value == None:
            self.badParam("value")
        
        


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
            self.arguments = AddStatisticRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())