#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ShowErrorRequest import ShowErrorRequest

class Show_error( SubAction, ShowErrorRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "show_error"
  debug = True

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    args_array = {}
    if self.arguments.args:
      args = self.arguments.args.split(",")
      for argpair in args:
        arg = argpair.strip().split(":") 
        if len(arg) == 2:
          args_array[arg[0]] = arg[1]
        
    self.errorResponse( self.arguments.code, "test_error", args_array )
    return
