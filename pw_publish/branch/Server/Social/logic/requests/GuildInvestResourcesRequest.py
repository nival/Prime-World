# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class GuildInvestResourcesRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        self.res1 = self.getIntParam("res1")
        if self.res1 == None:
            self.badParam("res1")
        
        
        self.res2 = self.getIntParam("res2")
        if self.res2 == None:
            self.badParam("res2")
        
        
        self.res3 = self.getIntParam("res3")
        if self.res3 == None:
            self.badParam("res3")
        
        
        self.silver = self.getIntParam("silver")
        if self.silver == None:
            self.badParam("silver")
        
        


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
            self.arguments = GuildInvestResourcesRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())