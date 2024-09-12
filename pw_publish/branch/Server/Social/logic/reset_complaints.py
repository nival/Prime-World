#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ResetComplaintsRequest import  ResetComplaintsRequest

class Reset_complaints( SubAction, ResetComplaintsRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "reset_complaints"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.acc.model.LordInfo.ComplaintsLeft = self.acc.getConfig().ComplaintsSettings.MAX_COMPLAINTS_PER_DAY + self.acc.model.LordInfo.ExtraComplaints

    self.response["ok"] = 1
    self.fin()