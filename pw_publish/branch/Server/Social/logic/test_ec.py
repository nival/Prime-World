#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.TestECRequest import TestECRequest

class Test_ec( SubAction, TestECRequest ):
  """возвращает присланный EC, сообщение и аргументы для тестирование поведения клиента"""
  action = "test_ec"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    ec = self.arguments.ec
    message = self.arguments.message
    args = self.arguments.args

    ar = args.split(":")
    errArgs = {}
    i = 0
    while i < len(ar):
      if i+1 >= len(ar):
        errArgs[ar[i]] = ""
      else:
        errArgs[ar[i]] = ar[i+1]
      i+=2

    self.errorResponse( ec, message, errArgs )