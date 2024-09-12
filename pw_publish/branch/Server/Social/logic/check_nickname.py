#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from ext_main.nickname import CheckNicknameAction
from logic.requests.ChangeNicknameRequest import ChangeNicknameRequest
from logic.requests.CheckNicknameRequest import CheckNicknameRequest
import base64
from base.helpers import utf8convert

class Check_nickname( SubAction, ChangeNicknameRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "check_nickname"

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    subParams = ClassDict( nickname=[self.arguments.nickname] )
    self.accountAction = CheckNicknameAction( subParams, self.onDone, I=self.I, acc=self.acc, uid=self.acc.uid )
    self.accountAction.onStart()
    return None
 
    # self.fin()

      
  @model_callback
  @action_timing
  def onDone( self, response ):      
    self.response = response    
    info("Check_nickname.onDone response: %s" % response)

    self.fin()

