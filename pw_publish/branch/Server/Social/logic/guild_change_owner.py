#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData
from logic.requests.GuildChangeOwnerRequest import GuildChangeOwnerRequest

class Guild_change_owner( SubAction, GuildChangeOwnerRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "guild_change_owner"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    if not self.acc.db.guildAuid:
      self.errorResponse( EC.NOT_IN_GUILD,  "You're not in guild" )
      return

    self.I.GS.changeGuildOwner( self.acc, self.arguments.person_auid, self.onChangeOwner )
    self.response["ok"] = 1
    self.fin()


  @model_callback
  @action_timing
  def onChangeOwner( self, response ):
    if response:
      info( "onDemote response: %s" % self.I.MD.pretty(response) )
      GuildData_changes = response.get("GuildData") or []
      if GuildData_changes:
        try:
          ModelChangeApplicator.apply( self.acc, "guilddata", GuildData, GuildData_changes ) 
        except:
          catch()

      self.acc.pending_events.append( {"GuildData": { "GuildData": GuildData_changes }} )
      if self.acc.pending_handler:
        self.acc.pending_handler()
