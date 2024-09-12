# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class ReforgeUpgradeTalentRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        self.talents = self.getArrayParam("talents")
        if not self.talents:
            self.badParam("talents")
        
        
        self.selectedOrangeSet = self.getStringParam("selectedOrangeSet")
        if self.selectedOrangeSet == None:
            self.selectedOrangeSet = ""
        
        
        self.selectedRedSet = self.getStringParam("selectedRedSet")
        if self.selectedRedSet == None:
            self.selectedRedSet = ""
        
        
        self.aftercontext = self.getBoolParam("aftercontext")
        if self.aftercontext == None:
            self.badParam("aftercontext")
        
        


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
            self.arguments = ReforgeUpgradeTalentRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())