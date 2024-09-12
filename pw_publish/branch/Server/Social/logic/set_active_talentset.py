# -*- coding: utf-8 -*-
import sys
from logic.party_hero import Party_hero
from subaction import *
from logic.requests.SetActiveTalentSetRequest import *

class Set_active_talentset( SubAction, SetActiveTalentSetRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "set_active_talentset"

  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.talent_set_id = self.arguments.talent_set_id
    self.hero = self.arguments.hero
    self.guardParty = self.arguments.guardParty
    self.master_auid = self.arguments.master_auid
    self.change_party_ts = self.arguments.change_party_tset

    if self.hero:
      #TODO: check talantset here
      pass
    else:
      self.errorResponse( "Hero is null" )
      return

    try:
      self.hero.ActiveTalentSet = self.arguments.talent_set_id
      if self.master_auid and self.change_party_ts:
        subParams = ClassDict( master_auid=[self.master_auid], hero_id=[self.hero.getID()],
                                                         hero_crc=[self.hero.PersistentId], guardParty=[self.guardParty] )
        self.arguments = self.arguments.arguments
        self.arguments['hero_id'] = [self.hero.getID()]
        self.arguments['hero_crc'] = [self.hero.PersistentId]
        partyAction = Party_hero( subParams, None, I=self.I, acc=self.acc, uid=self.acc.uid, request=self )
        partyAction.onStart()
    except:
      catch()


    self.response["ok"] = 1
    self.fin()

"""
class Set_active_talentset( SubAction, SetActiveTalentSetRequest ):
    action = "set_active_talentset"
  
    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
          return

        hero = self.arguments.hero
        if hero:
            hero.ActiveTalentSet = self.arguments.talent_set_id
            #if self.party_id:
            #    self.I.PS.updateTalentSetInfo(self.acc.auid, self.acc.party_id, hero.ActiveTalentSet)

            self.response["ok"] = 1
        else:
            self.response["ok"] = 0
            self.response["ec"] = EC.HERO_NOT_FOUND
        self.fin()
"""