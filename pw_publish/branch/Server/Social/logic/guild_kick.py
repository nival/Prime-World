#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData
from logic.requests.GuildKickRequest import GuildKickRequest

class Guild_kick( SubAction, GuildKickRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "guild_kick"
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    if not self.acc.db.guildAuid:
      self.errorResponse( EC.NOT_IN_GUILD,  "You're not in guild" )
      return

    self.I.GS.kickGuild( self.acc, self.arguments.person_auid, self.onKick )
    self.response["ok"] = 1
    self.fin()


  @model_callback
  @action_timing
  def onKick( self, response ):
    if response:
      info( "onKick response: %s" % self.I.MD.pretty(response) )
      GuildData_changes = response.get("GuildData") or []
      if GuildData_changes:
        try:
          ModelChangeApplicator.apply( self.acc, "guilddata", GuildData, GuildData_changes ) 
        except:
          catch()
      self.acc.pending_events.append( {"GuildData": { "GuildData": GuildData_changes }} )
      self.I.STATS.addGuildLeaved( self.arguments.person_auid, self.acc.db.guildAuid, self.acc.db.fraction, True,
                                   len(self.acc.guilddata.Members) )
      if self.acc.pending_handler:
        self.acc.pending_handler()
