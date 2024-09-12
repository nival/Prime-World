# -*- coding: utf-8 -*-
from subaction import *

from StatisticCore.ttypes import TalentInfo
from StatisticCore.ttypes import TalentChangeOperation
from StatisticCore.ttypes import ResourceChangeItem

from logic.requests.GuildBuyShopItemRequest import *
from guild.GuildData import GuildData
from modeldata.change_applicator import ModelChangeApplicator

class Guild_buy_shop_item(SubAction, GuildBuyShopItemRequest):
    """action, который будет обрабатывать данный класс"""
    action = "guild_buy_shop_item"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        if not self.acc.db.guildAuid:
            self.errorResponse(EC.NOT_IN_GUILD, "You're not in guild")
            return

        if not self.arguments.persistentId in self.acc.getConfig().GUILD_SHOP_ITEMS:
            self.errorResponse(EC.BAD_PARAM, "Can't find shop item in config")
            return

        self.shopItem = self.acc.SD.getGuildShopItemById(self.arguments.persistentId)
        if not self.shopItem:
            self.errorResponse(EC.BAD_PARAM, "Can't find shop item in static data")
            return

        if self.shopItem['classType'] == 'SkinGuildShopItem':
            validSkin, reason = self.acc.model.isValidSkin(crc32(self.shopItem['skin']['persistentId']), self.acc)
            if not validSkin:
                self.errorResponse(reason)
                return
        elif self.shopItem['classType'] == 'FlagGuildShopItem':
            customFlag = self.acc.SD.getCustomFlagById(self.shopItem['flag']['persistentId'])
            if customFlag['id'] in self.acc.model.Flags:
                self.errorResponse(EC.FLAG_IS_ALREADY_OWNED, "You already have this flag")
                return

        # Ура, мы наконец-то проверили, что можем купить этот айтем!
        reason = "PW!BUY GUILD SHOP ITEM: " + str(self.acc.db.guildAuid)
        self.price = self.acc.SD.copyPrice(self.shopItem['price'])
        self.needGold = int( self.price.Gold )
        self.buy(self.price, self.onBuy, self.onBuyFunc, reason)

    def onBuyFunc(self, response):
        code = response["code"]
        if code == ibilling.ERROR_CODE_OK:
            self.doConfirmWriteOff(response)
            self.I.GS.buyGuildShopItem(self.acc, self.arguments.persistentId, self.onBuyShopItem)
        else:
            self.onBuyError(response, self.needGold)

    @action_timing
    def onBuy(self, response):
        self.onBuyFunc(response)

    @model_callback
    @action_timing
    def onBuyShopItem(self, response):
        self.response["callback"] = ["guild_buy_shop_item"]
        if response:
            info("onBuyShopItem response: %s" % self.I.MD.pretty(response))
            isOk = response.get("ok") or 0
            if isOk:
                GuildData_changes = response.get("GuildData") or []
                if GuildData_changes:
                    try:
                        ModelChangeApplicator.apply(self.acc, "guilddata", GuildData, GuildData_changes)
                    except Exception:
                        catch()

                self.sendStatistics()
                if self.shopItem['classType'] == 'SkinGuildShopItem':
                    self.acc.model.giveSkinForFree(crc32(self.shopItem['skin']['persistentId']), self.acc, False, True)
                elif self.shopItem['classType'] == 'FlagGuildShopItem':
                    self.acc.model.Flags.append(self.shopItem['flag']['persistentId'])
                elif self.shopItem['classType'] == 'TalentGuildShopItem':
                    staticTalent = self.acc.SD.getStaticTalentByTalentId(crc32(self.shopItem['talent']['persistentId']))
                    if staticTalent and staticTalent['rarity'] != "Class":
                        talent = self.acc.model.addTalent(crc32(self.shopItem['talent']['persistentId']))
                        statistics_talent_info = TalentInfo(talent.PersistentId, talent.getID(), 0)
                        self.I.STATS.addTalentChange(self.acc.auid, statistics_talent_info, TalentChangeOperation.GetFromEvent, 'from_guildshop - id guild %r' % self.acc.db.guildAuid)
                elif self.shopItem['classType'] == 'OneTimeGuildShopItem' and (response.get("AffectOnBuyer") or False):
                    expTime = int(time.time()) + int(self.shopItem['guildBuff']['duration'])
                    if not self.acc.model.AddOneTimeGuildShopItem(self.acc, self.acc.SD, expTime, self.shopItem):
                        self.response["error"] = "onBuyShopItem: failed while buying item '%s'" % self.shopItem['persistentId']
                        self.response["ec"] = EC.BAD_PARAM
                        self.response["ok"] = 0
                        self.fin()
                        return
                elif self.shopItem['classType'] == 'LootboxGuildShopItem':
                    if not self.acc.model.addLootbox(crc32(self.shopItem['lootbox']['persistentId']), self.acc)[0]:
                        self.errorResponse("AddLootbox error")
                        return

                self.acc.pending_events.append({"GuildData": {"GuildData": GuildData_changes}})
                if self.acc.pending_handler:
                    self.acc.pending_handler()

                self.sendPendingEvents()
                self.response["ok"] = 1
            else:
                #все накренилось, вернем ресурсы
                self.acc.model.write(self.acc.pending)
                self.acc.pending.setPrefix("resourcesReturned:")
                self.acc.model.setComment("auto")
                self.acc.model.sell(self.price, self.acc)
                if "ec" in response:
                    self.errorResponse(response["ec"], "Can't buy shop item, bad response from server")
                else:
                    self.errorResponse(response["error"])
                return
        self.fin()

    def sendStatistics(self):
        hasSuzerain = (self.acc.guilddata.GuildSuzerain.ShortInfo.GuildAuid != 0)
        level = self.acc.SD.getGuildShopLevel(self.acc.guilddata.getShopOwnerRating(), self.acc.guilddata.GuildInfo.HasUltimateShop)
        self.I.STATS.addBuyGuildShopItem(self.acc.auid, self.acc.db.guildAuid, hasSuzerain, level, self.arguments.persistentId,
                                          self.price, self.acc.model.Resources, int(self.shopItem['price']['CWPoints_Clan']),
                                          self.acc.guilddata.GuildInfo.CWPoints_Clan)
