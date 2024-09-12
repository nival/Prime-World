#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from ext_main.nickname import SetNicknameAction
import base64
from base.helpers import utf8convert
from logic.requests.ChangeNicknameRequest import ChangeNicknameRequest

class Change_nickname( SubAction, ChangeNicknameRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "change_nickname"

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    inMatchmaking = False
    self.oldnick = self.acc.nick
    for heroId in self.acc.model.Heroes:
      hero = self.acc.model.getHeroByID (heroId)
      if hero.InMatchmaking:
        inMatchmaking = True
        self.errorResponse( EC.HERO_IN_MATCHMAKING, "Hero " + hero.class_name + " is in matchmaking", {"hero" : hero.class_name} )
        return

    self.price = self.acc.model.createResourcesTable( Gold = self.acc.getConfigValue("COST_NICK_CHANGE") )
    self.needGold = int( self.price.Gold )
    if self.acc.db.nick and self.arguments.nickname and (utf8convert(self.acc.db.nick) == utf8convert(self.arguments.nickname)):
      self.errorResponse( "Old and new nicks are equal" )
      return
        
    subParams = ClassDict( nickname=[self.arguments.nickname], rid=self.arguments.get("rid") )
    if self.acc.db.fraction == "N":
      self.I.EXPORT.updateLegendNickname(self.acc.db.auid, self.arguments.nickname)
      self.accountAction = SetNicknameAction( subParams, self.onDone, I=self.I, acc=self.acc, uid=self.acc.uid )
      self.accountAction.onStart()
      return None
    elif (self.acc.db.nickChanged >= self.acc.getConfigValue("FREE_NICK_CHANGES") and self.acc.model.canBuy(self.price)) \
    or self.acc.db.nickChanged < self.acc.getConfigValue("FREE_NICK_CHANGES"):
      self.I.EXPORT.updateLegendNickname(self.acc.db.auid, self.arguments.nickname)
      self.accountAction = SetNicknameAction( subParams, self.onDone, I=self.I, acc=self.acc, uid=self.acc.uid )
      self.accountAction.onStart()
      return None
    else:
      self.errorResponse( EC.NOT_ENOUGH_RESOURCES )
      freeChanges = self.acc.getConfigValue("FREE_NICK_CHANGES") - self.acc.db.nickChanged
      if freeChanges < 0:
        freeChanges = 0
      self.errorResponse( EC.NOT_ENOUGH_RESOURCES, "Not enough gold",
        {"free_changes" : freeChanges, "cost" : self.acc.getConfigValue("COST_NICK_CHANGE"), "gold" : self.acc.model.Resources.Gold } )
      return
 
    self.fin()

      
  @model_callback
  @action_timing
  def onDone( self, response ):      
    self.response = response
    info("Change_nickname.onDone response: %s" % response)
    
    if self.response.get('ok') == 1:
      if self.acc.db.fraction == "N":
        self.fin()
        return None
      elif self.acc.db.nickChanged >= self.acc.getConfigValue("FREE_NICK_CHANGES"):
        reason = "PW!CHANGE_NICKNAME:" + str( self.acc.db.nickChanged+1 ) + ":" + base64.b64encode( str( self.arguments.nickname ) )
        self.buy( self.price, self.onBuy, self.onBuyFunc, reason )
        return None
      else:
        self.acc.db.nickChanged += 1
    self.fin()


  @model_callback
  def onBuyFunc( self, response ):
    info("Change_nickname.onBuy response: %s" % response)    
    code = response["code"]
    if code == ibilling.ERROR_CODE_OK:
      self.doConfirmWriteOff( response )
      self.acc.db.nickChanged += 1
      self.I.STATS.addResourcesChange( self.acc.auid, False, ResourceChangeItem.ChangeNickname, "", self.price, self.acc.model.Resources )  
      self.response["ok"] = 1 # success 
    else:
      subParams = ClassDict( nickname=[self.oldnick] )
      self.I.EXPORT.updateLegendNickname(self.acc.db.auid, self.arguments.nickname)
      self.accountAction = SetNicknameAction( subParams, None, I=self.I, acc=self.acc, uid=self.acc.uid )
      self.accountAction.onStart()
      self.onBuyError( response )
      return

    self.fin()


  @action_timing
  def onBuy( self, response ):
    self.onBuyFunc( response )

