# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RollEventRoll import *
#from config.RollEvent import RollEvent
from enums.RollEventRuleType import RollEventRuleType
from enums.RollEventItemType import RollEventItemType
from StatisticCore.ttypes import TalentInfo
from StatisticCore.ttypes import TalentChangeOperation

class Roll_event_roll( SubAction, RollEventRoll ):
    action = "roll_event_roll"
  
    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
          return

        availableEvents = self.acc.getConfigValue("RollEvents")
        if not availableEvents:
            self.errorResponse("No available events data")
            return

        if self.arguments.rollEventId not in availableEvents:
            self.errorResponse("No required event found")
            return
        else:
            eventData = availableEvents.get(self.arguments.rollEventId)

        if self.arguments.ruleId not in eventData.Rolls.keys():
            self.errorResponse("Wrong roll data")
            return

        rollRule = eventData.Rolls.get(self.arguments.ruleId)

        self.price = rollRule.Price
        self.needGold = int(self.price.Gold)
        self.talentsToRemove = []

        if not self.acc.model.canBuy(self.price):
            self.errorResponse(EC.NOT_ENOUGH_RESOURCES, "Not enough resource for roll")
            return

        if rollRule.RuleType == RollEventRuleType.Simple:
            self.__doSimpleRoll(eventData, rollRule)
        elif rollRule.RuleType == RollEventRuleType.Reforge:
            self.__doReforgeRoll(eventData, rollRule)
        else:
            self.errorResponse("Unknown rule roll")
            return

    def __getRandomReward(self, rewards, except_id):
        # TODO: Change this for Resource reward type
        valid_rewards = [vr for vr in rewards if vr.PersistentId != except_id]
        if not valid_rewards:
            return None

        ratios = map(lambda r: float(r.Ratio), valid_rewards)
        sum_weights = sum(ratios)
        rewards_probabilities = zip(map(lambda r: r / sum_weights * 100.0, ratios), valid_rewards)

        chance = self.acc.SD.getValueInRange(self.makeAccRandom(), 1, 100)
        reward_probability = 0
        for item in rewards_probabilities:
            reward_probability += item[0]
            if chance <= reward_probability:
                return item[1]

        return valid_rewards[-1]

    def __prepareRandomReward(self, rule_data, except_id):
        self.roll_result = self.__getRandomReward(rule_data.Rewards.values(), except_id)

        if not self.roll_result:
            self.errorResponse("Roll result is nothing")
            return False

        if self.roll_result.ItemType != RollEventItemType.Talent and self.roll_result.ItemType != RollEventItemType.Lootbox:
            self.errorResponse("Roll with reward type %s is not implemented yet" % self.roll_result.ItemType)
            return False

        return True

    @model_callback
    def __doSimpleRoll(self, event_data, rule_data):

        if not self.__prepareRandomReward(rule_data, None):
            error("Can't prepare roll reward: [error=%s] rule_data=%s", self.response['error'], json_pretty(rule_data.generateJsonDict()))
            return

        reason = "PW!ROLLEVENTSIMPLE"
        self.buy(self.price, self.onBuy, self.onBuyFunc, reason)

    @model_callback
    def __doReforgeRoll(self, event_data, rule_data):
        if self.arguments.reforgeSourceId not in rule_data.ReforgeSources.keys():
            self.errorResponse("Wrong roll reforge data")
            return

        reforgeItem = rule_data.ReforgeSources.get(self.arguments.reforgeSourceId)
        if reforgeItem.ItemType != RollEventItemType.Talent:
            self.errorResponse("Roll with reforge source of type %s is not implemented yet" % reforgeItem.ItemType)
            return

        if not self.__isEnoughSpecTalents(reforgeItem.PersistentId):
            self.errorResponse(EC.NOT_ENOUGH_RESOURCES, "Not enough required talents for roll")
            return

        if not self.__prepareRandomReward(rule_data, reforgeItem.PersistentId):
            error("Can't prepare reforge roll reward: %s", self.response['error'])
            return

        reason = "PW!ROLLEVENTREFORGE"
        self.buy(self.price, self.onBuy, self.onBuyFunc, reason)

    def __isEnoughSpecTalents(self, reforge_talent_id):
        tal_res_id = crc32(reforge_talent_id)

        # Find all talents with this type
        free_talents = []
        bound_talents = []
        for talentId in self.acc.model.UserInventory:
            talent = self.acc.model.getTalentByID(talentId)
            if talent.PersistentId == tal_res_id:
                if talent.isSoulbounded() or (talent.Owner and talent.Owner.get()):
                    bound_talents.append(talent)
                else:
                    free_talents.append(talent)

        # Find free talent with minimal point value
        if len(free_talents) > 0:
            selected_talent = min(free_talents, key=lambda t: t.Points)
            self.talentsToRemove.append(selected_talent)
            return True

        # Find bound talent with minimal point value
        if len(bound_talents) > 0:
            selected_talent = min(bound_talents, key=lambda t: t.Points)
            self.talentsToRemove.append(selected_talent)
            return True

        # Fail
        return False

    def __giveTalentReward(self):
        tal_id = crc32(self.roll_result.PersistentId)
        static_talent = self.acc.SD.getStaticTalentByTalentId(tal_id)
        if not static_talent:
            error("Wrong talent id [%s] in roll rewards", self.roll_result.PersistentId)
            self.errorResponse("Wrong talent id in roll rewards")
            return

        talent = self.acc.model.addTalent(tal_id)
        talInfo = TalentInfo(talent.PersistentId, talent.getID(), 0)
        self.I.STATS.addTalentChange(self.acc.auid, talInfo, TalentChangeOperation.GetFromEvent)

    def __giveReward(self):
        if self.roll_result.ItemType == RollEventItemType.Talent:
            self.__giveTalentReward()
        elif self.roll_result.ItemType == RollEventItemType.Lootbox:
            self.acc.model.addLootbox(crc32(self.roll_result.PersistentId), self.acc, open_after_receive=False)


    @model_callback
    def onBuyFunc(self, response):
        info("Roll_event_roll.onBuy response: %s" % response)
        code = response["code"]
        if code == ibilling.ERROR_CODE_OK:
            self.doConfirmWriteOff(response)

            self.__giveReward()

            self.I.STATS.addResourcesChange(self.acc.auid, False, ResourceChangeItem.RollEvent, "", self.price,
                                            self.acc.model.Resources)

            for talent in self.talentsToRemove:
                self.I.STATS.addTalentChange(self.acc.auid,
                                             TalentInfo(talent.PersistentId, talent.id, getBoundHeroClassId(talent)),
                                             TalentChangeOperation.Sell, self.roll_result.PersistentId)
                if talent.Owner and talent.Owner.get():
                    talent.Owner.moveTalentFromTalentSetToLibrary(talent, talent.id)
                self.acc.model.UserInventory.remove(talent)

            # self.response["callback"] = ["roll_event_roll"]
            self.response["roll_result"] = {'event_id': self.arguments.rollEventId,
                                            'rule_id': self.arguments.ruleId,
                                            'reward_id': self.roll_result.getID()}

            self.response["ok"] = 1  # success
        else:
            # self.response["callback"] = ["roll_event_roll"]
            self.onBuyError(response, self.needGold)
            return

        self.fin()

    @action_timing
    def onBuy(self, response):
        self.onBuyFunc(response)
