# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class ItemMoveTsToInvRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        src_hero_id = self.getKeeperObjectIDParam("src_hero_id", modeldata)
        self.src_hero = modeldata.getHeroByID(src_hero_id)
        if not self.src_hero:
            self.badParam("src_hero")
        
        
        self.src_item_id = self.getIntParam("src_item_id")
        if self.src_item_id == None:
            self.badParam("src_item_id")
        
        
        self.src_slot_id = self.getIntParam("src_slot_id")
        if self.src_slot_id == None:
            self.badParam("src_slot_id")
        
        
        self.talent_set_id = self.getIntParam("talent_set_id")
        if self.talent_set_id == None:
            self.badParam("talent_set_id")
        
        


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
            self.arguments = ItemMoveTsToInvRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())