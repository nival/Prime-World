# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class BuildingUpgradeRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        building_id = self.getKeeperObjectIDParam("building_id", modeldata)
        self.building = modeldata.getConstructionByID(building_id)
        if not self.building:
            self.badParam("building")
        
        
        self.aftercontext = self.getBoolParam("aftercontext")
        if self.aftercontext == None:
            self.badParam("aftercontext")
        
        
        self.client_time = self.getIntParam("client_time")
        if self.client_time == None:
            self.badParam("client_time")
        
        


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
            self.arguments = BuildingUpgradeRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())