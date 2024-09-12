# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class ZzLoginRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        self.zz_user = self.getStringParam("zz_user")
        if self.zz_user == None:
            self.zz_user = ""
        
        
        self.zz_auth = self.getStringParam("zz_auth")
        if self.zz_auth == None:
            self.zz_auth = ""
        
        
        self.ver = self.getStringParam("ver")
        if self.ver == None:
            self.ver = ""
        
        
        self.testkey = self.getIntParam("testkey")
        if self.testkey == None:
            self.badParam("testkey")
        
        


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
            self.arguments = ZzLoginRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())