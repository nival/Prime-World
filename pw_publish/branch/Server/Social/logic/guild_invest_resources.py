#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData
from logic.requests.GuildInvestResourcesRequest import GuildInvestResourcesRequest

class Guild_invest_resources( SubAction, GuildInvestResourcesRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "guild_invest_resources"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    if not self.acc.db.guildAuid:
      self.errorResponse( EC.NOT_IN_GUILD,  "You're not in guild" )
      return
    
    self.needGold = 0
    self.price = self.acc.model.createResourcesTable()
    
    self.price.Resource1 = self.arguments.res1
    self.price.Resource2 = self.arguments.res2
    self.price.Resource3 = self.arguments.res3
    self.price.Silver = self.arguments.silver
        
    self.amount = self.arguments.res1 + self.arguments.res2 + self.arguments.res3 + self.arguments.silver / int(self.acc.getConfigValue("SILVER_TO_GUILD_RESOURCES_COEFF"))
    if self.price.Resource1 < 0 or self.price.Resource2 < 0 or self.price.Resource3 < 0 or self.price.Silver < 0:
      self.errorResponse( EC.BAD_PARAM, "Amount should be positive" )
      return
    
    if self.acc.guilddata:
      if self.acc.SD.getLeftToCapForGuild( self.acc.guilddata.GuildLevelInfo.Experience) < self.amount:
        self.errorResponse( "Guild level experience limit will be reached" )
        return        
      
    
    reason = "PW!INVEST IN GUILD: " + str(self.acc.db.guildAuid)
    self.buy( self.price, self.onBuy, self.onBuyFunc, reason )
    return None


  def onBuyFunc( self, response ):
    code = response["code"]
    if code == ibilling.ERROR_CODE_OK:
      self.doConfirmWriteOff( response )
      self.I.GS.investInGuild( self.acc, self.amount, self.onInvestInGuild )
      
      self.response["ok"] = 1 # success 
    else:
      self.onBuyError( response, self.needGold )
      return

    self.fin()


  @action_timing
  def onBuy( self, response ):
    self.onBuyFunc( response )
    
  @model_callback
  @action_timing
  def onInvestInGuild( self, response ):
    if response:
      info( "onInvestInGuild response: %s" % self.I.MD.pretty(response) )
      isOk = response.get("ok") or 0
      if not isOk: #все накрeнилось, вернем ресурсы
        self.acc.model.write( self.acc.pending )
        self.acc.pending.setPrefix( "resourcesReturned:" )
        self.acc.model.setComment( "auto" )        
        self.acc.model.sell( self.price, self.acc )
      else:
        self.I.STATS.addResourcesChange( self.acc.auid, False, ResourceChangeItem.InvestInGuild, "", self.price, self.acc.model.Resources )
        GuildData_changes = response.get("GuildData") or []
        if GuildData_changes:
          try:
            ModelChangeApplicator.apply( self.acc, "guilddata", GuildData, GuildData_changes ) 
          except:
            catch()
        self.acc.pending_events.append( {"GuildData": { "GuildData": GuildData_changes }} )

      if self.acc.pending_handler:
        self.acc.pending_handler()
