#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.MarkEventViewedRequest import MarkEventViewedRequest

class Mark_event_viewed( SubAction, MarkEventViewedRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "mark_event_viewed"
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    eventName = self.arguments.PersistentId
    if eventName not in self.acc.model.MarketingEventsInfo.ViewedEvents:
      self.acc.model.MarketingEventsInfo.ViewedEvents.append( eventName )

    self.response["ok"] = 1
    self.fin()