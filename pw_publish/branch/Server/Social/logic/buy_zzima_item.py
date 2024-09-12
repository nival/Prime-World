# -*- coding: utf-8 -*-
import sys
import cfg
import base64
import izzimacom
from subaction import *
from logic.requests.BuyZZimaItemRequest import *


class Buy_zzima_item(SubAction, BuyZZimaItemRequest):
    """action, который будет обрабатывать данный класс"""
    action = "buy_zzima_item"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        # ACTION LOGIC
        if not self.acc.zzimacom:
            self.errorResponse(EC.ZZIMA_OPERATION_FAILURE, "ZZima is not supported")
            return

        zzItem = self.acc.SD.getZZimaItem(self.acc.getConfig(), self.arguments.itemId)

        if not zzItem:
            self.errorResponse(EC.ZZIMA_OPERATION_FAILURE, "ZZima item %s is not found" % self.arguments.itemId)
            return

        self.acc.db.zzimacomTransaction += 1

        base32str = base64.b32encode(
            cfg.AGG_BILLING_PREFIX + hex(self.acc.db.auid) + "_" + str(self.acc.db.zzimacomTransaction)).replace("=",
                                                                                                                 "")
        callback = functools.partial(self.onZZimaResponse, transId=base32str, price=zzItem.Gold)

        self.acc.db.zzimacomOrders[base32str] = {"status": izzimacom.ZZIMA_LG_START_TRANSACTION,
                                                 "time": int(time.time()),
                                                 "zzimacom_info": (
                                                     self.arguments.itemId,
                                                     zzItem.Description,
                                                     zzItem.Price,
                                                     zzItem.Gold,
                                                     callback),
                                                 "try": 0
        }

        #transactionId, itemId, itemPrice, count,
        item_count = 1
        self.acc.zzimacom.startTransaction(base32str, self.arguments.itemId, zzItem.Price, item_count, callback)


    def onZZimaResponse(self, response, transId, price):
        info("Buy_zzima_item.onZZimaResponse transId %r price %r zzima response: %s" % ( transId, price, response ))
        if response:
            if response.get("ok", False):
                balance = response.get('balance', None)
                if balance:
                    if transId in self.acc.db.zzimacomOrders and self.acc.db.zzimacomOrders[transId][
                        "status"] == izzimacom.ZZIMA_LG_START_TRANSACTION:
                        self.acc.db.zzimacomOrders[transId]["status"] = izzimacom.ZZIMA_LG_REPLENISH
                        self.acc.db.zzimacomOrders[transId]["time"] = int(time.time())
                        self.acc.db.zzimacomOrders[transId]["try"] = 0
                        itemId, description, ZZPrice, gold, callback = self.acc.db.zzimacomOrders[transId][
                            "zzimacom_info"]
                        callback = functools.partial(self.acc.model.onZZimacomReplenish, txnid=transId, acc=self.acc)
                        self.I.ZZIMA_PS.replenish(self.acc.db.auid, int(price), int(ZZPrice), "ZZIMA", transId,
                                                     callback)
                        self.response["ok"] = 1
                else:
                    if transId in self.acc.db.zzimacomOrders:
                        self.acc.db.zzimacomOrders.pop(transId, None)
                    self.errorResponse(EC.ZZIMA_OPERATION_FAILURE,
                                       "ZZima start transaction failed to return params")
                    return
            else:
                if transId in self.acc.db.zzimacomOrders:
                    self.acc.db.zzimacomOrders.pop(transId, None)
                if response.get('ec', 0) == EC.ZZIMA_NOT_ENOUGH_ZZGOLD:
                    self.errorResponse(EC.ZZIMA_NOT_ENOUGH_ZZGOLD,
                                       "Not enough zzima zzgol, balance = %s" % (response.get('balance', '')))
                else:
                    self.errorResponse(response.get('ec', EC.ZZIMA_OPERATION_FAILURE),
                                       "ZZima start transaction failed: %s" % (response.get('em', '<no message>'),))
                return
        else:
            if transId in self.acc.db.arcgamesOrders:
                self.acc.db.zzimacomOrders.pop(transId, None)
            self.errorResponse(EC.ZZIMA_OPERATION_FAILURE, "ZZima start transaction failed to return response")
            return

        self.fin()