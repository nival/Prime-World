# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.AddTalentExRequest import *

class Add_talent_ex( SubAction, AddTalentExRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "add_talent_ex"
    debug = True
  
    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
          return

        #ACTION LOGIC
        static_talent = self.acc.SD.getStaticTalentByTalentId(self.arguments.static_talent_id)
        if not static_talent:
            self.errorResponse("Static talent with id %d not found" % self.arguments.static_talent_id)
            return
        talent_id = self.acc.model.addNewTalent()
        talent = self.acc.model.getTalentByID(talent_id)
        talent.PersistentId = self.arguments.static_talent_id
        talent.IsNew = True
        talent.Points = self.arguments.points
        self.acc.model.UserInventory.add(talent_id)

        self.response["ok"] = 1
        self.fin()
