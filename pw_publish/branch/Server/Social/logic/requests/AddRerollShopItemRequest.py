# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class AddRerollShopItemRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        self.persistentId = self.getIntParam("persistentId")
        if self.persistentId == None:
            self.badParam("persistentId")
        
        
        self.price = self.getIntParam("price")
        if self.price == None:
            self.badParam("price")
        
        
        self.resourceType = self.getIntParam("resourceType")
        if self.resourceType == None:
            self.badParam("resourceType")
        
        
        self.isPremium = self.getBoolParam("isPremium")
        if self.isPremium == None:
            self.badParam("isPremium")
        
        


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
            self.arguments = AddRerollShopItemRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())