#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RefreshPingResultsRequest import RefreshPingResultsRequest

class Refresh_ping_results( SubAction, RefreshPingResultsRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "refresh_ping_results"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    if not self.arguments.pingName in self.acc.model.LordInfo.PingResults.keys():
      self.errorResponse( "Ping name is not found" )
      return      
    
    self.acc.model.LordInfo.PingResults[self.arguments.pingName] = self.arguments.pingTime
    
    self.I.STATS.addClientPing( self.acc.auid, str(self.arguments.pingName).upper(), toint(self.arguments.pingTime) )
    
    self.response["ok"] = 1
    self.fin()