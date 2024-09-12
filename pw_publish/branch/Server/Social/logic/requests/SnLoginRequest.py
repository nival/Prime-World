# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class SnLoginRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        self.snid = self.getStringParam("snid")
        if self.snid == None:
            self.snid = ""
        
        
        self.snuid = self.getStringParam("snuid")
        if self.snuid == None:
            self.snuid = ""
        
        
        self.sntoken = self.getStringParam("sntoken")
        if self.sntoken == None:
            self.sntoken = ""
        
        
        self.ver = self.getStringParam("ver")
        if self.ver == None:
            self.ver = ""
        
        
        self.testkey = self.getIntParam("testkey")
        if self.testkey == None:
            self.badParam("testkey")
        
        
        self.userlocale = self.getStringParam("userlocale")
        if self.userlocale == None:
            self.userlocale = ""
        
        

        self.sntoken2 = self.getStringParam("sntoken2", "")

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
            self.arguments = SnLoginRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())