#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GuildRecalcRequest import GuildRecalcRequest

class Guild_recalc( SubAction, GuildRecalcRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "guild_recalc"
  debug = True
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.I.WS.recalcAllGuilds()

    self.response["ok"] = 1
    self.fin()