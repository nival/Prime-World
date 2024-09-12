#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from enums import *
from logic.requests.GuildDeleteMsgRecievedRequest import GuildDeleteMsgRecievedRequest

class Guild_delete_msg_recieved( SubAction, GuildDeleteMsgRecievedRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "guild_delete_msg_recieved"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.sendPendingMessages()
    self.acc.model.LordInfo.GuildStatus = GuildStatus.NoneState

    self.response["ok"] = 1
    self.fin()