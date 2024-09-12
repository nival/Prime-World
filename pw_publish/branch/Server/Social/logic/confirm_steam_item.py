#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
sys.path.append('../cfg')
import cfg
from subaction import *
import isteam
from logic.requests.ConfirmSteamItemRequest import ConfirmSteamItemRequest

class Confirm_steam_item( SubAction, ConfirmSteamItemRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "confirm_steam_item"
  
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

    self.orderId = self.arguments.orderId
    self.orderInfo = None
    if self.acc.db.steamOrders and self.orderId in self.acc.db.steamOrders:
      self.orderInfo = self.acc.db.steamOrders[self.orderId]
    if not self.orderInfo:
      self.errorResponse( EC.STEAM_OPERATION_FAILURE, "Steam orderInfo %r is not found within acc data" % self.orderInfo) 
      return      

    if not self.arguments.authorized:
      self.acc.steam.cancelTransaction(self.orderId, self.orderInfo["orderCode"])
      del self.acc.db.steamOrders[self.orderId]      
      self.response["ok"] = 1
      self.fin()
      return
      
    items = self.acc.steam.retrieveTransaction(self.orderId, self.orderInfo["orderCode"])
    if not items:
      self.errorResponse( EC.STEAM_OPERATION_FAILURE, "Steam orderId %s is not found" % self.orderId) 
      return           
    
    itemId = items[0][0]    
    steamItem, category, currencyIndex = self.acc.SD.getSteamItem(self.acc.getConfig(), itemId)
      
    if not steamItem:
      self.acc.steam.cancelTransaction(self.orderId, self.orderInfo["orderCode"])
      del self.acc.db.steamOrders[self.orderId]       
      self.errorResponse( EC.STEAM_OPERATION_FAILURE, "Steam item %s is not found, canceled" % itemId)                  
      return    

    steamUserInfo = self.acc.steam.getUser()
    if not steamUserInfo:
      self.errorResponse( EC.STEAM_OPERATION_FAILURE, "Steam userInfo is Empty" ) 
      return       

    steamCurrency = steamUserInfo.get('currency', 'RUB')

    fallbackCurrency = 'USD'
    curInd = currencyIndex.get(steamCurrency)
    if not curInd:
        curInd = currencyIndex.get(fallbackCurrency)
        steamCurrency = fallbackCurrency

    if not curInd:
      self.errorResponse(EC.STEAM_OPERATION_FAILURE, "Index for currency %s is not valid" % steamCurrency)
      return 
    
    steamPrice = self.acc.SD.roundGold(steamItem.Price * curInd)
    
    self.Gold = steamItem.Gold
    self.orderInfo["orderStatus"] = isteam.STEAM_ORDER_STATUS_CONFIRM
    self.I.STEAM_PS.replenish(self.acc.auid, self.Gold, steamPrice, steamCurrency, self.orderId, self.onSteamPsResponse)
    return

    
  def onSteamPsResponse(self, response):
      if self.orderId not in self.acc.db.steamOrders:
          if self.orderInfo is None:
              err("Confirm_steam_item.onSteamPsResponse: order %s is lost! Response: %s", (self.orderId, response))
              self.errorResponse(EC.PAYMENT_SYSTEM_FAILURE, "onSteamPsResponse: Order %s is lost. Response: %s" % (self.orderId, response))
          else:
              warn("Confirm_steam_item.onSteamPsResponse: order %s not found in .acc.db.steamOrders", self.orderId)
              # we can proceed with self.orderInfo
      if response:
          info( "onSteamPsResponse: %s" % response )
          code = response["result"]
          if code == ibilling.PAYMENTS_OK:
              if not self.orderInfo.get("registered", False):
                  self.orderInfo["orderStatus"] = isteam.STEAM_ORDER_STATUS_WAIT_FOR_REPLENISH
              # else - don't change orderStatus, it's => isteam.STEAM_ORDER_STATUS_WAIT_FOR_STEAMCONFIRM already
              self.orderInfo["orderTime"] = int(round(time.time()))
              self.response["ok"] = 1 # success
              self.fin()
              return
          elif code == ibilling.PAYMENTS_FETCH_ERROR:
              self.acc.steam.cancelTransaction(self.orderId, self.orderInfo["orderCode"])
              if not self.orderInfo.get("registered", False):
                  self.acc.db.steamOrders.pop(self.orderId, None)
                  # and don't touch already 'registered' order - it's processed in ModelDataCustom.registerPayment
              self.errorResponse( EC.PAYMENT_SYSTEM_FAILURE, "Payment failed( %r ), canceled steam transaction for orderID %s" % (response,self.orderId) )
              return

      self.acc.steam.cancelTransaction(self.orderId, self.orderInfo["orderCode"])
      if not self.orderInfo.get("registered", False):
          self.acc.db.steamOrders.pop(self.orderId, None)
      self.errorResponse( EC.STEAM_BILLING_PROCESSING_ERROR, "Billing failed( %r ), canceled steam transaction for orderID %s" % (response,self.orderId) )
      return
