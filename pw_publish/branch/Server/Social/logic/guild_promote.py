#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData
from logic.requests.GuildPromoteRequest import GuildPromoteRequest

class Guild_promote( SubAction, GuildPromoteRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "guild_promote"
  
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

    self.I.GS.promoteGuild( self.acc, self.arguments.person_auid, self.onPromote )
    self.response["ok"] = 1
    self.fin()


  @model_callback
  @action_timing
  def onPromote( self, response ):
    if response:
      info( "onPromote response: %s" % self.I.MD.pretty(response) )
      GuildData_changes = response.get("GuildData") or []
      if GuildData_changes:
        try:
          ModelChangeApplicator.apply( self.acc, "guilddata", GuildData, GuildData_changes ) 
        except:
          catch()
      self.acc.pending_events.append( {"GuildData": { "GuildData": GuildData_changes }} )
      if self.acc.pending_handler:
        self.acc.pending_handler()
