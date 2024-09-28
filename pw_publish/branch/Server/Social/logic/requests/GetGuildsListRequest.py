# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class GetGuildsListRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        self.position = self.getIntParam("position")
        if self.position == None:
            self.badParam("position")
        
        
        self.sortCriteria = self.getIntParam("sortCriteria")
        if self.sortCriteria == None:
            self.badParam("sortCriteria")
        
        
        self.order = self.getIntParam("order")
        if self.order == None:
            self.badParam("order")
        
        
        self.nameFilter = self.getStringParam("nameFilter")
        if self.nameFilter == None:
            self.nameFilter = ""
        
        
        self.ratingFilter = self.getIntParam("ratingFilter")
        if self.ratingFilter == None:
            self.badParam("ratingFilter")
        
        
        self.prevRatingFilter = self.getIntParam("prevRatingFilter")
        if self.prevRatingFilter == None:
            self.badParam("prevRatingFilter")
        
        
        self.statusFilter = self.getIntParam("statusFilter")
        if self.statusFilter == None:
            self.badParam("statusFilter")
        
        
        self.suzerenFilter = self.getStringParam("suzerenFilter")
        if self.suzerenFilter == None:
            self.suzerenFilter = ""
        
        
        self.suzerenRatingFilter = self.getIntParam("suzerenRatingFilter")
        if self.suzerenRatingFilter == None:
            self.badParam("suzerenRatingFilter")
        
        


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
            self.arguments = GetGuildsListRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())