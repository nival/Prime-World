#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
import cfg, base64
import iaeria
from logic.requests.BuyAeriaItemRequest import BuyAeriaItemRequest

class Buy_aeria_item(SubAction, BuyAeriaItemRequest):
  """action, который будет обрабатывать данный класс"""
  action = "buy_aeria_item"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    if not self.acc.aeria:
      self.errorResponse(EC.AERIA_OPERATION_FAILURE, "Aeria is not supported")
      return

    aeriaItem = self.acc.SD.getAeriaItem(self.acc.getConfig(), self.arguments.itemId)

    if not aeriaItem:
      self.errorResponse(EC.AERIA_OPERATION_FAILURE, "Aeria item %s is not found" % self.arguments.itemId)
      return

    self.acc.db.aeriaTransaction += 1

    base32str = base64.b32encode( cfg.AGG_BILLING_PREFIX + hex(self.acc.db.auid) + "_" + str(self.acc.db.aeriaTransaction) ).replace( "=", "" )
    callback = functools.partial( self.onAeriaResponse, transId=base32str, price=aeriaItem.Gold )

    self.acc.db.aeriaOrders[base32str] = { "status" : iaeria.AERIA_LG_START_TRANSACTION, "time" : int( time.time() ), "aeria_info" : \
                                           (self.arguments.itemId, aeriaItem.Description, aeriaItem.Price, aeriaItem.Gold, callback), "try" : 0 }

    self.acc.aeria.startTransaction( base32str, self.arguments.itemId, aeriaItem.Description, aeriaItem.Price, callback )


  def onAeriaResponse( self, response, transId, price ):
    if response:
      info( "onAeriaResponse transId %r price %r aeria response: %s" % ( transId, price, response ) )
      if response.get("ok", False):
        balance = response.get('balance', None)
        if balance:
          if transId in self.acc.db.aeriaOrders and self.acc.db.aeriaOrders[transId]["status"] == iaeria.AERIA_LG_START_TRANSACTION:
            self.acc.db.aeriaOrders[transId]["status"] = iaeria.AERIA_LG_REPLENISH
            self.acc.db.aeriaOrders[transId]["time"] = int( time.time() )
            self.acc.db.aeriaOrders[transId]["try"] = 0
            itemId, description, AeriaPrice, gold, callback = self.acc.db.aeriaOrders[transId]["aeria_info"]
            callback = functools.partial( self.acc.model.onAeriaReplenish, txnid=transId, acc=self.acc )
            self.I.AERIA_PS.replenish( self.acc.db.auid, int(price), int(AeriaPrice), "AE", transId, callback )
            self.response["ok"] = 1
        else:
          if transId in self.acc.db.aeriaOrders:
            self.acc.db.aeriaOrders.pop( transId, None )
          self.errorResponse(EC.AERIA_OPERATION_FAILURE, "Aeria start transaction failed to return params")
          return
      else:
        if transId in self.acc.db.aeriaOrders:
          self.acc.db.aeriaOrders.pop( transId, None )
        if response.get('ec',0) == EC.AERIA_NOT_ENOUGH_AP:
          self.errorResponse(EC.AERIA_NOT_ENOUGH_AP, "Not enouth aeria points, balance = %s" % (response.get('balance', '')))
        else:
          self.errorResponse(response.get('ec', EC.AERIA_OPERATION_FAILURE), "Aeria start transaction failed: %s" % (response.get('em', '<no message>'),))
        return
    else:
      if transId in self.acc.db.aeriaOrders:
        self.acc.db.aeriaOrders.pop( transId, None )
      self.errorResponse(EC.AERIA_OPERATION_FAILURE, "Aeria start transaction failed to return response")
      return

    self.fin()
