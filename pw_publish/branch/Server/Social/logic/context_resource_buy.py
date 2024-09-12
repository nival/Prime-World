# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ContextResourceBuyRequest import *
from StaticData import StaticData

class Context_resource_buy( SubAction, ContextResourceBuyRequest ):
    """action, для обработки запроса на контекстную покупку ресурсов за голду"""
    action = "context_resource_buy"
  
    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
          return

        self.resourcesToBuy = StaticData.emptyPrice()
        self.resourcesToBuy.Resource1 = self.arguments.res1
        self.resourcesToBuy.Resource2 = self.arguments.res2
        self.resourcesToBuy.Resource3 = self.arguments.res3
        self.resourcesToBuy.Silver = self.arguments.silv
        self.resourcesToBuy.Perl = self.arguments.perl

        gold = StaticData.getResourcesPriceInGold( self.resourcesToBuy, self.acc.SD.data )
        if gold != self.arguments.gold:
            #TODO: тут надо ответить с ошибкой рассинхрона логики
            return

        if gold >= 0:
            self.price = self.acc.model.createResourcesTable( Gold = gold )
        else:
            self.errorResponse( "Gold price for resources less or equal 0" )
            return

        if self.price:
            self.needGold = int( self.price.Gold )
            if self.needGold >= 0:
                reason = "PW!CONTEXTBUY:" + StaticData.getResourceShortInfo(self.resourcesToBuy)
                self.buy( self.price, self.onBuy, self.onBuyFunc, reason )
            return
        else:
          self.errorResponse( "Can't buy resources, the price is negative" )
          return

        self.response["ok"] = 1
        self.fin()



    @model_callback
    def onBuyFunc( self, response ):
        code = response["code"]
        if code == ibilling.ERROR_CODE_OK:
            self.doConfirmWriteOff( response )
            self.acc.model.sell(self.resourcesToBuy, self.acc, False)

            resourceChange = StaticData.copyPrice(self.resourcesToBuy)
            resourceChange.Gold = self.needGold

            self.I.STATS.addResourcesChange( self.acc.auid, False, ResourceChangeItem.ContextBuyResource , "", resourceChange, self.acc.model.Resources )

            self.response["ok"] = 1
        else:
            self.onBuyError( response, self.needGold )
            return

        self.fin()


    @action_timing
    def onBuy( self, response ):
        self.onBuyFunc( response )