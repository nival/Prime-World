#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GiveRatingRequest import GiveRatingRequest

class Give_rating( SubAction, GiveRatingRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "give_rating"
  debug = True
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.arguments.hero.changeRating( self.arguments.value, self.I, self.acc )
    self.I.GS.changeHeroRating( self.acc, self.arguments.hero.Rating, self.arguments.hero.PersistentId, self.arguments.hero.Rating, self.onGuild )

    self.response["ok"] = 1
    self.fin()

  @model_callback
  @action_timing
  def onGuild( self, response ):
    if response:
      info( "onGuild response: %s" % self.I.MD.pretty(response) )
      GuildData_changes = response.get("GuildData") or []
      if GuildData_changes:
        try:
          ModelChangeApplicator.apply( self.acc, "guilddata", GuildData, GuildData_changes ) 
        except:
          catch()
      self.acc.pending_events.append( {"GuildData": { "GuildData": GuildData_changes }} )
      if self.acc.pending_handler:
        self.acc.pending_handler()
