#!/usr/bin/env python
import re
from enums import *


class StatisticEvent_base:
  def isActual( self, model, eventsDict):
    action = self.intToEventType( self.actionType )
    if action not in eventsDict:
      return False
    
    for staticDesc, staticTime in eventsDict[action].iteritems():
      if staticDesc == "" or re.search( staticDesc, self.description ):
        if staticTime <= self.time:
          return True
    return False
  
  def isActualFinishSessionEvent( self, model, eventsDict):
    result = self.intToSessionResult( self.value )
    if self.description not in eventsDict:
      return False
    
    for staticWin, staticTime in eventsDict[self.description].iteritems():
      if staticWin == "" or staticWin == result:
        if staticTime <= self.time:
          return True
    return False

  
  def intToEventType(self, actionType ):
    for field, value in StatisticEventType.__dict__.iteritems():
      if value == actionType:
        return field
      
    
  def intToSessionResult( self, result ):
    if result == 0:
      return "Loose"
    elif result == 1:
      return "Win"
    else:
      return "DontCare"
    