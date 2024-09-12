# -*- coding: utf-8 -*-
import sys
import base64
import cfg
from subaction import *
from logic.requests.BuyArcGamesItemRequest import *


class Buy_arcgames_item(SubAction, BuyArcGamesItemRequest):
    """action, который будет обрабатывать данный класс"""
    action = "buy_arcgames_item"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        # ACTION LOGIC
        if not self.acc.arcgames:
            self.errorResponse(EC.ARCGAMES_OPERATION_FAILURE, "Arc Games is not supported")
            return

        token = self.arguments.token

        if not token:
            self.errorResponse(EC.ARCGAMES_OPERATION_FAILURE, "Bad token %s for Arc Games auth" % token)
            return
        else:
            # Логинимся, чтобы обновить токен, по другому ArcGames API не позволяет
            self.I.AGG.login(self.acc.snuid,
                                 token,
                                 self.acc.snid,
                                 0,
                                 None,
                                 use_billing=1,
                                 callback=self.onAggLoginReply)


    def onArcGamesResponse(self, response, transId, price):
        if response:
            info("Buy_arcgames_item.onAcGamesResponse transId %r price %r arcgames response: %s" % ( transId, price, response ))
            if response.get("ok", False):
                balance = response.get('balance', None)
                if balance:
                    if transId in self.acc.db.arcgamesOrders and self.acc.db.arcgamesOrders[transId][
                        "status"] == iarcgames.ARCGAMES_LG_START_TRANSACTION:
                        self.acc.db.arcgamesOrders[transId]["status"] = iarcgames.ARCGAMES_LG_REPLENISH
                        self.acc.db.arcgamesOrders[transId]["time"] = int(time.time())
                        self.acc.db.arcgamesOrders[transId]["try"] = 0
                        itemId, description, ArcGamesPrice, gold, callback = self.acc.db.arcgamesOrders[transId][
                            "arcgames_info"]
                        callback = functools.partial(self.acc.model.onArcGamesReplenish, txnid=transId, acc=self.acc)
                        self.I.ARCGAMES_PS.replenish(self.acc.db.auid, int(price), int(ArcGamesPrice), "ARC", transId,
                                                     callback)
                        self.response["ok"] = 1
                else:
                    if transId in self.acc.db.arcgamesOrders:
                        self.acc.db.arcgamesOrders.pop(transId, None)
                    self.errorResponse(EC.ARCGAMES_OPERATION_FAILURE,
                                       "ArcGames start transaction failed to return params")
                    return
            else:
                if transId in self.acc.db.arcgamesOrders:
                    self.acc.db.arcgamesOrders.pop(transId, None)
                if response.get('ec', 0) == EC.ARCGAMES_NOT_ENOUGH_ZEN:
                    self.errorResponse(EC.ARCGAMES_NOT_ENOUGH_ZEN,
                                       "Not enouth arcgames zen, balance = %s" % (response.get('balance', '')))
                else:
                    self.errorResponse(response.get('ec', EC.ARCGAMES_OPERATION_FAILURE),
                                       "ArcGames start transaction failed: %s" % (response.get('em', '<no message>'),))
                return
        else:
            if transId in self.acc.db.arcgamesOrders:
                self.acc.db.arcgamesOrders.pop(transId, None)
            self.errorResponse(EC.ARCGAMES_OPERATION_FAILURE, "ArcGames start transaction failed to return response")
            return

        self.fin()

    def onAggLoginReply(self, reply):
        info("Buy_arcgames_item.onAggLoginReply: %r" % reply)
        if not reply.get('error'):

            arcItem = self.acc.SD.getArcGamesItem(self.acc.getConfig(), self.arguments.itemId)

            if not arcItem:
                self.errorResponse(EC.ARCGAMES_OPERATION_FAILURE, "Arс Games item %s is not found" % self.arguments.itemId)
                return

            self.acc.db.arcgamesTransaction += 1

            base32str = base64.b32encode(
                cfg.AGG_BILLING_PREFIX + hex(self.acc.db.auid) + "_" + str(self.acc.db.arcgamesTransaction)).replace("=",
                                                                                                                     "")
            callback = functools.partial(self.onArcGamesResponse, transId=base32str, price=arcItem.Gold)

            self.acc.db.arcgamesOrders[base32str] = {"status": iarcgames.ARCGAMES_LG_START_TRANSACTION,
                                                     "time": int(time.time()),
                                                     "arcgames_info": (
                                                         self.arguments.itemId,
                                                         arcItem.Description,
                                                         arcItem.Price,
                                                         arcItem.Gold,
                                                         callback),
                                                     "try": 0
            }

            #transactionId, itemId, itemPrice, count,
            item_count = 1
            self.acc.arcgames.startTransaction(base32str, self.arguments.itemId, arcItem.Price, item_count, callback)

        else:
            self.errorResponse(EC.ARCGAMES_OPERATION_FAILURE, "AGG reply: %r" % reply)
            return