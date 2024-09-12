# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetMDVersionRequest import *

class Set_md_version( SubAction, SetMDVersionRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "set_md_version"
  debug = True

  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.acc.model.version.revision = self.arguments.versionNum

    self.response["ok"] = 1
    self.fin()