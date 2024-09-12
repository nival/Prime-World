#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ChangeLastLoginRequest import ChangeLastLoginRequest

class Change_last_login( SubAction, ChangeLastLoginRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "change_last_login"
  debug = True

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.acc.model.LordInfo.LastLoginTime = self.acc.model.LordInfo.LastLoginTime - self.arguments.days*60*60*24
    
    self.response["ok"] = 1 # success 

    self.fin()