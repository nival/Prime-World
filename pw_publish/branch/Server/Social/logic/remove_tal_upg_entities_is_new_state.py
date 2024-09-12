# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RemoveTalentUpgradeEntitiesIsNewStateRequest import *

class Remove_tal_upg_entities_is_new_state( SubAction, RemoveTalentUpgradeEntitiesIsNewStateRequest ):
    """action, ������� ����� ������������ ������ �����"""
    action = "remove_tal_upg_entities_is_new_state"
  
    @model_callback
    @parse
    def onStart(self):
        """��������� ����� ��� ��������� action"""
        self.log()
        if not self.checkParams():
          return

        #ACTION LOGIC
        for id in self.acc.model.TalentUpgradeEntities:
            ent = self.acc.model.getTalentUpgradeEntityByID(id)
            if ent.IsNew:
                ent.IsNew = False

        self.response["ok"] = 1
        self.fin()