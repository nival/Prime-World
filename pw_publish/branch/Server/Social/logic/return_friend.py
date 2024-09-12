#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ReturnFriendRequest import ReturnFriendRequest

class Return_friend( SubAction, ReturnFriendRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "return_friend"
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.response["ok"] = 1
    self.fin()