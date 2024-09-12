# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class ContextResourceBuyRequest(BaseRequest):
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
        
        
        self.perl = self.getIntParam("perl")
        if self.perl == None:
            self.badParam("perl")
        
        
        self.silv = self.getIntParam("silv")
        if self.silv == None:
            self.badParam("silv")
        
        
        self.gold = self.getIntParam("gold")
        if self.gold == None:
            self.badParam("gold")
        
        


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
            self.arguments = ContextResourceBuyRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())