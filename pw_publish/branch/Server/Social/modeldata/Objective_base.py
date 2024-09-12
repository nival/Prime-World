#!/usr/bin/env python

import time
import re
from base.helpers import err, debug

def hasAdvMap( maps, name ):
  for map in maps:
    if map['dbid'] == name:
      return True
  return False


class Objective_base:
  def update(self, staticObjective, acc, model, SD, friendsdata):
    if 'classType' in staticObjective['condition']:
      if self.value >= int(staticObjective['value']):
        return 0
        
      if staticObjective['condition']['classType'] == "ModelDataCondition":
        value = 0
        value = self.CheckModelDataCondition(staticObjective, acc, model, SD, friendsdata)
        return value

      elif staticObjective['condition']['classType'] == "FinishSessionCondition":
        value = 0
        for eventId in model.StatisticEvents:
          event = model.getStatisticEventByID(eventId)
          if event.actionType == 0:
            if event.time >= self.lastEventId:
              condition = staticObjective['condition']
              if 'Item' not in condition['maps'] or len(condition['maps']['Item']) == 0 or hasAdvMap( condition['maps']['Item'], event.description ):
                if condition['result'] == 'DontCare' or (condition['result'] == 'Win' and event.value == 1) or (condition['result'] == 'Lose' and event.value == 0):
                  if staticObjective['incremental']:
                    value += 1
                    if int(staticObjective['value']) <= value:
                      return value
                  else:
                    if int(staticObjective['value']) <= 1:
                      return 1

        return value

      elif staticObjective['condition']['classType'] == "StatisticEventCondition":
        value = 0
        if 'Item' in staticObjective['condition']['events']:
          for eventId in model.StatisticEvents:
            event = model.getStatisticEventByID(eventId)
            eventValue = event.value
            if staticObjective['condition']['countOnly']:
              eventValue = 1
            for staticEvent in staticObjective['condition']['events']['Item']:
              isMatch = (staticEvent['description'] == None) or (staticEvent['description'] == "") or re.search( staticEvent['description'], event.description )
              if staticEvent['eventType'] == event.intToEventType( event.actionType ) and isMatch and event.time >= self.lastEventId:                
                if int(staticObjective['value']) <= eventValue + value:
                  return value + eventValue              
                if staticObjective['incremental']:
                  value += eventValue
        return value

      
  def CheckModelDataCondition( self, staticObjective, acc, model, SD, friendsdata ):
    value = model.execQuestCondition( staticObjective['condition']['code'], acc.sex, SD, acc.getConfig() )
    return value
  

  def SetValue( self, value, staticObjective, model, SD, gender, fraction, WS, acc, config, STATS, bill, randVal, I ):
    if value != 0:
      if 'timeOutInMinutes' in  staticObjective and (model.ServerTime - self.lastValueChangedTime) < (int(staticObjective['timeOutInMinutes']) *60):
        return
      
      self.lastValueChangedTime = model.ServerTime;
      debug( "Objective.SetValue: old %r - > new %r", self.lastEventId, model.StatisticEventId)
      self.lastEventId = model.StatisticEventId


      if int(staticObjective['value']) <= value:
        value = int(staticObjective['value'])
        if 'completeActions' in staticObjective:
          model.applyActions( staticObjective['completeActions'], SD, gender, fraction, WS, acc, config, STATS, bill, randVal, I )
        
      if staticObjective['incremental']:
        self.value += value
      else:
        self.value = value

