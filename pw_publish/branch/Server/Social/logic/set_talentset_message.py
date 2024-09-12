# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetTalentSetMessageRequest import *

class Set_talentset_message( SubAction, SetTalentSetMessageRequest ):
    """action, ������� ����� ������������ ������ �����"""
    action = "set_talentset_message"
  
    @model_callback
    @parse
    def onStart(self):
        """��������� ����� ��� ��������� action"""
        self.log()
        if not self.checkParams():
          return
        hero = self.arguments.hero
        if hero:
            msg = urllib.unquote(self.arguments.message)
            debug("Set_talentset_message mess=%r", msg)
            hero.TalentSets[self.arguments.talent_set_id].TalentSetName = msg

            self.response["ok"] = 1
        else:
            self.response["ok"] = 0
            self.response["ec"] = EC.HERO_NOT_FOUND
        self.fin()





