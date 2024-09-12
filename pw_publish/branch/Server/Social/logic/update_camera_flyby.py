#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.UpdateCameraFlybyRequest import UpdateCameraFlybyRequest

class Update_camera_flyby( SubAction, UpdateCameraFlybyRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "update_camera_flyby"

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    self.acc.model.LordInfo.CameraFlybyTime = int(round(time.time()))
    self.response["ok"] = 1 # success 
    self.fin()
