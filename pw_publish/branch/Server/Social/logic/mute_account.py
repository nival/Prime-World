#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.MuteAccountRequest import MuteAccountRequest

class Mute_account( SubAction, MuteAccountRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "mute_account"

  # клиент просит переместить вещь из инвентаря в талантсет
  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.acc.db.muted = 1
    if self.arguments.minutes == 0:
        self.acc.db.mutetime = 0
    else:
        self.acc.db.mutetime = int(round(time.time())) + self.arguments.minutes * 60
    self.acc.db.mutereason = self.arguments.reason
    
    self.response["ok"] = 1 # success 

    self.fin()
