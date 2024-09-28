#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
import isteam
from logic.requests.BuySteamItemRequest import BuySteamItemRequest

class Buy_steam_item( SubAction, BuySteamItemRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "buy_steam_item"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    if not self.acc.steam:
      self.errorResponse( EC.STEAM_OPERATION_FAILURE, "Steam is not supported" ) 
      return          
    
    steamItem, category, currencyIndex = self.acc.SD.getSteamItem(self.acc.getConfig(), self.arguments.itemId)
      
    if not steamItem:
      self.errorResponse( EC.STEAM_OPERATION_FAILURE, "Steam item %s is not found" % self.arguments.itemId) 
      return           
    
    steamUserInfo = self.acc.steam.getUser()
    if not steamUserInfo:
      self.errorResponse( EC.STEAM_OPERATION_FAILURE, "Steam userInfo is Empty" ) 
      return       
    
    steamCurrency = steamUserInfo.get('currency', 'RUB')
    steamLangCode = 'RU' #steamUserInfo.get('country', 'RU')

    if not currencyIndex:
      self.errorResponse( EC.STEAM_OPERATION_FAILURE, "Steam currency crosstable is Empty" ) 
      return            

    fallbackCurrency = 'USD'
    curInd = currencyIndex.get(steamCurrency)
    if not curInd:
      curInd = currencyIndex.get(fallbackCurrency)
      steamCurrency = fallbackCurrency

    if not curInd:
      self.errorResponse( EC.STEAM_OPERATION_FAILURE, "Index for currency %s is not valid" % steamCurrency)
      return 
    
    steamPrice = self.acc.SD.roundGold(steamItem.Price * curInd)
    
    self.acc.steam.startTransaction(steamLangCode, steamCurrency, [ (self.arguments.itemId, 1, steamPrice, steamItem.Description, category)], self.onSteamResponse)
    return
    
  def onSteamResponse( self, response ):
    if response:
      info( "onStartTransaction steam response: %s" % response )
      isOk = response.get("ok") or 0
      if isOk:
        orderCode = response.get('orderCode', None)
        orderId = response.get('orderId', None)
        if orderCode and orderId:
          self.acc.db.steamOrders[orderId] = { "orderCode" : orderCode, "orderStatus" : isteam.STEAM_ORDER_STATUS_BUY, "orderTime" : int( round( time.time() ) ) } 
          self.response["ok"] = 1
        else:
          self.errorResponse( EC.STEAM_OPERATION_FAILURE, "Steam start transaction failed to return params") 
          return        
      else:
        self.errorResponse( EC.STEAM_OPERATION_FAILURE, "Steam start transaction failed with EC = %s:%s" % (response.get('ec', ''),response.get('em', ''))) 
        return   
    else:
      self.errorResponse( EC.STEAM_OPERATION_FAILURE, "Steam start transaction failed to return response") 
      return        
    self.fin()
