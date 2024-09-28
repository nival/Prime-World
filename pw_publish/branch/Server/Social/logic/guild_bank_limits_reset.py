#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData
from logic.requests.GuildBankLimitsResetRequest import GuildBankLimitsResetRequest

class Guild_bank_limits_reset( SubAction, GuildBankLimitsResetRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "guild_bank_limits_reset"
  debug = True
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.I.GS.guildBankLimitsReset( self.acc, self.onResetLimits )
    self.response["ok"] = 1
    self.fin()


  @model_callback
  @action_timing
  def onResetLimits( self, response ):
    if response:
      info( "onResetLimits response: %s" % self.I.MD.pretty(response) )
      GuildData_changes = response.get("GuildData") or []
      if GuildData_changes:
        try:
          ModelChangeApplicator.apply( self.acc, "guilddata", GuildData, GuildData_changes ) 
        except:
          catch()

      self.acc.pending_events.append( {"GuildData": { "GuildData": GuildData_changes }} )
      if self.acc.pending_handler:
        self.acc.pending_handler()
