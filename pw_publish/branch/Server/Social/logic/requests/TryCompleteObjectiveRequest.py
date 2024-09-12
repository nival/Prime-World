# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys
from baserequest import *

class TryCompleteObjectiveRequest(BaseRequest):
    def __init__(self, modeldata, params, obfuscator=True):
        BaseRequest.__init__(self, obfuscator)
        self.bad_param = False
        self.arguments = params
        self.rid = self.getIntParam("rid")
        quest_id = self.getKeeperObjectIDParam("quest_id", modeldata)
        self.quest = modeldata.getQuestByID(quest_id)
        if not self.quest:
            self.badParam("quest")
        
        
        objective_id = self.getKeeperObjectIDParam("objective_id", modeldata)
        self.objective = modeldata.getObjectiveByID(objective_id)
        if not self.objective:
            self.badParam("objective")
        
        

        self.clientValue = self.getIntParam("clientValue", 0)

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
            self.arguments = TryCompleteObjectiveRequest(self.acc.model, self.arguments)
        self.response.update(self.arguments.getResponse())