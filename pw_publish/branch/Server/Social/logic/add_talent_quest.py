# -*- coding: utf-8 -*-
import sys

from subaction import *
from logic.requests.AddTalentQuestRequest import *

class Add_talent_quest( SubAction, AddTalentQuestRequest ):
    action = "add_talent_quest"

    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
            return

        printLog = False

        # region Valid check and inits

        # if not permission in config then finish off
        if self.I.Config.getMainConfig().TalentsCollectionSettings.TALENTS_QUEST_DISABLED:
            if printLog:
                print "TALENTS_QUEST_IS_DISABLED\n"
            self.errorResponse(EC.BAD_ACTION_NAME)
            return

        # if talent is not defined then finish off
        staticTalent = self.acc.SD.getStaticTalentByTalentId(self.arguments.TalentPersistantId)
        if staticTalent is None:
            if printLog:
                print "Bad talent in argument\n"
            self.errorResponse(EC.BAD_PARAM)
            return

        # if talent is forbidden then finish off
        if staticTalent['persistentId'] in self.acc.SD.data['DynamicQuestForTalents']['ForbadeTalents']:
            if printLog:
                print "Forbidden talent in argument\n"
            self.errorResponse(EC.BAD_PARAM)
            return

        # if not permission in config then finish off
        max_active_quests_allowed = self.I.Config.getMainConfig().TalentsCollectionSettings.TALENTS_QUEST_LIMIT
        if max_active_quests_allowed >= 0:
            active_talent_quests_count = 0

            for _, quest in self.acc.model.DynamicQuests.iteritems():
                if quest.Reason == DynamicQuestReasons.Talent and quest.QuestState != QuestState.Complete:
                    active_talent_quests_count += 1

            if active_talent_quests_count >= max_active_quests_allowed:
                if printLog:
                    print "User already has max count of active talent quests\n"
                self.errorResponse(EC.BAD_ACTION_NAME)
                return

        # set price
        price = self.__getPriceList(staticTalent)
        if printLog:
            print "Selected price: {}\n".format(price)

        if price is None:
            if printLog:
                print "Price is not found in SD\n"
            self.errorResponse(EC.NOT_DEFINED_IN_SD)
            return

        if price == self.acc.SD.emptyPrice():
            if printLog:
                print "Price is empty\n"
            self.errorResponse(EC.NOT_DEFINED_IN_SD)
            return

        # endregion

        self.__putNewQuestAndDropResources(printLog, price, staticTalent)

    # Create new price list from just threw in SD
    def __getPriceList(self, staticTal):
        overridenPriceMap = self.acc.SD.data['DynamicQuestForTalents']['OverridenPricesMap']
        overridenPrice = overridenPriceMap[staticTal['persistentId']] if staticTal['persistentId'] in overridenPriceMap else None
        if overridenPrice:
            return self.acc.SD.copyPrice(overridenPrice)
        else:
            priceMap = self.acc.SD.data['DynamicQuestForTalents']['PricesMap']
            return self.acc.SD.copyPrice(priceMap[staticTal['rarity']]) if staticTal['rarity'] in priceMap else None

    # Check enough resources -> add DQ -> drop resources
    def __putNewQuestAndDropResources(self, printLog, price, staticTalent):
        if not self.acc.model.canBuy(price, False):
            self.errorResponse(EC.NOT_ENOUGH_RESOURCES)
            return

        if self.acc.model.addTalentDynamicQuestWithSD(printLog, self.acc, staticTalent):
            self.needGold = int(price.Gold)
            reason = "PW!START_TALENT_DYNAMIC_QUEST"
            self.price = price
            self.buy(price, self.callbackBilling, self.onBuy, reason)
        else:
            self.errorResponse(EC.ACCOUNT_FAILED)

    @action_timing
    def callbackBilling(self, response):
        self.onBuy(response)

    @model_callback
    def onBuy(self, response):
        code = response["code"]
        if code == ibilling.ERROR_CODE_OK:
            self.doConfirmWriteOff(response)
            self.I.STATS.addResourcesChange(self.acc.auid, False, ResourceChangeItem.AddTalentQuest, "", self.price,
                                            self.acc.model.Resources)
            self.response["ok"] = 1
        else:
            self.onBuyError(response, self.needGold)
            return

        self.fin()
