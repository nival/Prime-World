#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.IncreaseStatRequest import IncreaseStatRequest

class Increase_stat( SubAction, IncreaseStatRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "increase_stat"

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    hero = self.arguments.hero
    stat =  self.arguments.stat
    value = self.arguments.value
    talent_set_id  = self.arguments.talent_set_id
    if hero and hero.Hired:
      #if not hero.InMatchmaking:
        if value > 0 and (hero.TalentSets[talent_set_id].Stats.StatPoints + hero.TalentSets[talent_set_id].GuildStats.StatPoints) >= value:

          coef = self.acc.SD.getStatPointsMultiplyer( stat )
          if not coef:
            self.errorResponse(  "Bad stat name '" + str(stat) + "'" )
            return

          points = value
          guildPoints = 0

          if hero.TalentSets[talent_set_id].Stats.StatPoints < value:
            guildPoints = value - hero.TalentSets[talent_set_id].Stats.StatPoints
            points = hero.TalentSets[talent_set_id].Stats.StatPoints

          addValue = getattr(hero.TalentSets[talent_set_id].Stats, stat) + points * coef
          setattr(hero.TalentSets[talent_set_id].Stats, stat, addValue)
          hero.TalentSets[talent_set_id].Stats.StatPoints -= points

          addValue = getattr(hero.TalentSets[talent_set_id].GuildStats, stat) + guildPoints * coef
          setattr(hero.TalentSets[talent_set_id].GuildStats, stat, addValue)
          hero.TalentSets[talent_set_id].GuildStats.StatPoints -= guildPoints

          hero.CalcForce( self.acc.model, self.I.WS, self.acc, talent_set_id )

        else:
          self.errorResponse(  "Not enough statpoints" )
          return
      #else:
        #self.errorResponse(  "hero is in matchmaking" )
        #return
    else:
      self.errorResponse(  "hero not hired" )
      return

    self.response["ok"] = 1 # success
    self.fin()