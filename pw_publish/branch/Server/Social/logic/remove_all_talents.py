# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RemoveAllTalentsRequest import *

class Remove_all_talents( SubAction, RemoveAllTalentsRequest ):
    debug = True
    action = "remove_all_talents"
  
    @model_callback
    @parse
    def onStart(self):
        """��������� ����� ��� ��������� action"""
        self.log()
        if not self.checkParams():
          return

        for _id, item in self.acc.model.UserInventory.items():
            staticTalent = self.acc.SD.getStaticTalentByTalentId(item.PerisitentId)
            if staticTalent['rarity'] != "Class":
                if item.Owner and item.Owner.get():
                    continue
                self.acc.model.UserInventory.remove(item)

        self.response["ok"] = 1
        self.fin()