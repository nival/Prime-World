# -*- coding: utf-8 -*-
import sys
from subaction import *
from party_flag import *
from logic.requests.ChangeFlagRequest import ChangeFlagRequest

class Change_flag( SubAction, ChangeFlagRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "change_flag"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.guardParty = self.arguments.guardParty
    self.master_auid = self.arguments.master_auid

    if self.arguments.flagType == FlagType.Default:
      self.acc.model.FlagInfo.FlagType = FlagType.Default
      self.acc.model.FlagInfo.PersistentId = self.acc.SD.getDefaultFlagName()
    elif self.arguments.flagType == FlagType.Country:
      if self.acc.SD.countryFlagExists(self.arguments.flagId):
        self.acc.model.FlagInfo.FlagType = FlagType.Country
        self.acc.model.FlagInfo.PersistentId = self.arguments.flagId
      else:
        self.errorResponse(EC.FLAG_NOT_FOUND, "Custom flag was not found")
        return
    elif self.arguments.flagType == FlagType.Special:
      if self.arguments.flagId in self.acc.model.Flags:
        self.acc.model.FlagInfo.FlagType = FlagType.Special
        self.acc.model.FlagInfo.PersistentId = self.arguments.flagId
      else:
        self.errorResponse( EC.FLAG_IS_NOT_OWNED, "Flag is not owned" )
        return
    else:
      self.errorResponse(EC.FLAG_NOT_FOUND, "Illegal flag type")
      return

    try:
      if self.master_auid:
        subParams = ClassDict( master_auid=[self.master_auid], flag_type=[self.acc.model.FlagInfo.FlagType], person_id=[self.acc.db.auid],
                                                        flag_persistent_id=[self.acc.model.FlagInfo.PersistentId], guardParty=[self.guardParty] )
        self.arguments = self.arguments.arguments
        partyAction = Party_flag( subParams, None, I=self.I, acc=self.acc, uid=self.acc.uid, request=self )
        partyAction.onStart()
    except:
      catch()

    self.response["ok"] = 1
    self.fin()