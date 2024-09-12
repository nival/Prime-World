#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GuildDeclineRequest import GuildDeclineRequest

class Guild_decline( SubAction, GuildDeclineRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "guild_decline"
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    for giId in self.acc.model.IncomingGuildInvites.keys():
      guildInvite = self.acc.model.getGuildInviteByID( giId )
      if guildInvite.guildAuid == self.arguments.guild_auid:
        self.acc.model.IncomingGuildInvites.remove( guildInvite )

    self.response["ok"] = 1
    self.fin()