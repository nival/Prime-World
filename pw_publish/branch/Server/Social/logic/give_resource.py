#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys, math
from subaction import *
from logic.requests.GiveResourceRequest import GiveResourceRequest
from guild.GuildData import GuildData
from modeldata.change_applicator import ModelChangeApplicator

class Give_resource( SubAction, GiveResourceRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "give_resource"
  debug = True

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    resource =  self.arguments.resource
    value = self.arguments.value
    modeldata = self.acc.model

    resources = self.acc.model.createResourcesTable()  # all 0

    if ':' in resource:
      currencyId = resource.split(':')[1]
      resources.Currencies[currencyId] = value
    else:
      resources[resource] = value
    if resource == "CWPoints_Clan":
      self.I.GS.guildCwpointsSell(self.acc, value, self.onCWPointsAdded)
      self.I.GS.changeMemberRating(self.acc, value, self.onCWPointsAdded)
    else:
      self.acc.model.sell(resources, self.acc, False)
      
    self.response["ok"] = 1 # success 
    self.fin()
    

  @model_callback
  @action_timing
  def onBuy( self, response ):
    self.response["ok"] = 1
    self.fin()
    
  def onCWPointsAdded( self, response ):
    if response:
      info( "onCWPointsAdded response: %s" % self.I.MD.pretty(response) )
      GuildData_changes = response.get("GuildData") or []
      if GuildData_changes:
        try:
          ModelChangeApplicator.apply( self.acc, "guilddata", GuildData, GuildData_changes )
        except:
          catch()

      self.acc.pending_events.append( {"GuildData": { "GuildData": GuildData_changes }} )
      if self.acc.pending_handler:
        self.acc.pending_handler()
