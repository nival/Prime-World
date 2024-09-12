#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData
from logic.requests.GuildGiveBackRequest import GuildGiveBackRequest

class Guild_give_back( SubAction, GuildGiveBackRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "guild_give_back"
  

  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.I.GS.giveBackGuildTalent( self.acc, self.arguments.talentid, self.onGiveBackGuildTalent )


  @model_callback
  @action_timing
  def onGiveBackGuildTalent( self, response ):
    if response:
      info( "onGiveBackGuildTalent response: %s" % self.I.MD.pretty(response) )
      isOk = response.get("ok") or 0
      if isOk:
        GuildData_changes = response.get("GuildData") or []
        if GuildData_changes:
          try:
            ModelChangeApplicator.apply( self.acc, "guilddata", GuildData, GuildData_changes )
          except:
            catch()

        self.acc.pending_events.append( {"GuildData": { "GuildData": GuildData_changes }} )
        if self.acc.pending_handler:
          self.acc.pending_handler()

        self.response["ok"] = 1
        self.fin()
      else:
        self.errorResponse( response["ec"],  "Can't give back talent, bad response from server" )  
