# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class StartBuildingProductionRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        construction_id = self.getKeeperObjectIDParam("construction_id", modeldata)
        self.construction = modeldata.getConstructionByID(construction_id)
        if not self.construction:
            self.badParam("construction")
        
        
        self.cycle = self.getIntParam("cycle")
        if self.cycle == None:
            self.badParam("cycle")
        if self.cycle < 0 or self.cycle > 3 : self.badParam( "cycle" )
        
        self.aftercontext = self.getBoolParam("aftercontext")
        if self.aftercontext == None:
            self.badParam("aftercontext")
        
        

        self.customValue = self.getIntParam("customValue", 0)

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
            self.arguments = StartBuildingProductionRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())