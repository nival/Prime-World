# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class CreateComplaintRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        self.toauid = self.getIntParam("toauid")
        if self.toauid == None:
            self.badParam("toauid")
        
        
        self.category = self.getIntParam("category")
        if self.category == None:
            self.badParam("category")
        
        
        self.text = self.getStringParam("text")
        if self.text == None:
            self.text = ""
        
        
        self.sessionid = self.getIntParam("sessionid")
        if self.sessionid == None:
            self.badParam("sessionid")
        
        
        self.source = self.getIntParam("source")
        if self.source == None:
            self.badParam("source")
        
        
        self.kills = self.getIntParam("kills")
        if self.kills == None:
            self.badParam("kills")
        
        
        self.deaths = self.getIntParam("deaths")
        if self.deaths == None:
            self.badParam("deaths")
        
        
        self.assists = self.getIntParam("assists")
        if self.assists == None:
            self.badParam("assists")
        
        
        self.points = self.getIntParam("points")
        if self.points == None:
            self.badParam("points")
        
        
        self.prime = self.getIntParam("prime")
        if self.prime == None:
            self.badParam("prime")
        
        
        self.leave = self.getIntParam("leave")
        if self.leave == None:
            self.badParam("leave")
        
        
        self.distance = self.getIntParam("distance")
        if self.distance == None:
            self.badParam("distance")
        
        
        self.afks = self.getIntParam("afks")
        if self.afks == None:
            self.badParam("afks")
        
        


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
            self.arguments = CreateComplaintRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())