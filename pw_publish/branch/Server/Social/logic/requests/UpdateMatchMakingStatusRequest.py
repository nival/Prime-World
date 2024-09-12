# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class UpdateMatchMakingStatusRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        self.is_active_window = self.getBoolParam("is_active_window")
        if self.is_active_window == None:
            self.badParam("is_active_window")
        
        
        self.is_device_lost = self.getBoolParam("is_device_lost")
        if self.is_device_lost == None:
            self.badParam("is_device_lost")
        
        


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
            self.arguments = UpdateMatchMakingStatusRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())