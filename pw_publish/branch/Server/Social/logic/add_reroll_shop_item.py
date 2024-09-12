# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.AddRerollShopItemRequest import *

class Add_reroll_shop_item( SubAction, AddRerollShopItemRequest ):
    debug = True
    action = "add_reroll_shop_item"
  
    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
          return

        staticShopItem = self.acc.SD.getStaticRerollShopItemById(self.arguments.persistentId)
        if staticShopItem:
            item, item_id = self.acc.model.newRerollShopItem()
            item.PersistentId = self.arguments.persistentId
            item.PriceResource = self.arguments.resourceType
            item.Price = self.arguments.price
            item.IsPremium = self.arguments.isPremium

            self.acc.model.RerollShopInfo.ShopItems.add(item)

        self.response["ok"] = 1
        self.fin()