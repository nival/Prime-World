#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ClearMmRequest import ClearMmRequest

class Clear_mm( SubAction, ClearMmRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "clear_mm"
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
    
    if self.acc.data.mm:
      self.acc.data.mm = None
    
    self.response["ok"] = 1 # success 

    self.fin()