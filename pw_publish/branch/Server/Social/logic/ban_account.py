#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.BanAccountRequest import BanAccountRequest

class Ban_account( SubAction, BanAccountRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "ban_account"
  debug = True

  # клиент просит переместить вещь из инвентаря в талантсет
  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.acc.db.banned = True
    self.acc.db.autoban = bool(self.arguments.autoBan)
    if self.arguments.minutes == 0:
        self.acc.db.bantime = 0
    else:
        self.acc.db.bantime = int( round( time.time() ) ) + self.arguments.minutes * 60
    self.acc.db.banreason = self.arguments.reason
    
    self.response["ok"] = 1 # success 


    self.fin()
