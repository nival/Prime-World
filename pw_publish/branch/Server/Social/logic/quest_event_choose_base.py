# -*- coding: utf-8 -*-
from subaction import *
from AccountManagementAPI.ttypes import ConfigEventType

from enums.RollEventItemType import RollEventItemType


class Quest_event_choose_base(SubAction):

    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
            return

        event_id = self.arguments.questEventId
        events = self.acc.getConfigValue("QuestEvents")
        if event_id not in events:
            self.errorResponse("Can't find QuestEvent with id %d" % event_id)
            return

        self.quest_event = events[event_id]

        if self.quest_event.Guid not in self.acc.model.QuestEvents:
            self.errorResponse("No progression record for QuestEvent with guid %d" % self.quest_event.Guid)
            return

        self.event_progression = self.acc.model.QuestEvents[self.quest_event.Guid]
        self.next_step_idx = len(self.event_progression.Choices)    # сквозной индекс
        self.quest_stage_idx, self.quest_step_idx = self.quest_event.unwrap_index(self.next_step_idx)
        if self.quest_stage_idx < 0 or self.quest_step_idx < 0:
            self.errorResponse("Wrong choice index for event: %d" % self.next_step_idx)
            return

        self.quest_stage = self.quest_event.Stages[self.quest_stage_idx]
        self.quest_step = self.quest_stage.Steps[self.quest_step_idx]
        self.is_last_choice = self.quest_stage_idx + 1 >= len(self.quest_event.Stages) and \
                           self.quest_step_idx + 1 >= len(self.quest_stage.Steps)
        if self.arguments.choiceIndex < 0 or self.arguments.choiceIndex >= len(self.quest_step.Variants):
            self.errorResponse("Wrong choice index for event: %d" % self.arguments.choiceIndex)
            return
        self.quest_choice = self.quest_step.Variants[self.arguments.choiceIndex]
        self.price = self.quest_choice.Price
        self.needGold = int(self.price.Gold)
        if not self.acc.model.canBuy(self.price):
            self.errorResponse(EC.NOT_ENOUGH_RESOURCES, "Not enough resource for making choice")
            return

        reason = "PW!QUESTEVENTCHOICE"
        self.buy(self.price, self.onBuy, self.onBuyFunc, reason)

    def _do_roll(self, step):
        # do override
        return False

    def __clear_stage_progression(self):
        base_step_idx = self.quest_event.wrap_index(self.quest_stage_idx, 0)
        for idx in range(self.next_step_idx, base_step_idx, -1):
            del self.event_progression.Choices[idx - 1]

    def __on_roll_win(self):
        if self.is_last_choice:
            # Clear to first stage step
            self.__clear_stage_progression()
        else:
            # Store choice index in progression
            self.event_progression.Choices.append(self.arguments.choiceIndex)
        # Send to stats
        self.I.STATS.questEventStageChange(self.acc.auid, self.quest_stage_idx + 1)
        self.I.STATS.questEventStateChange(self.acc.auid, self.quest_step_idx + 1, self.quest_stage_idx + 1)

    def __on_roll_lose(self):
        # Clear to first stage step
        self.__clear_stage_progression()

    def __give_stage_reward(self, roll_result):
        reward = self.quest_stage.LoseRewards[0]
        if roll_result:
            reward = self.quest_stage.Rewards[0]
        if reward.ItemType == RollEventItemType.Lootbox:
            if not self.acc.model.addLootbox(crc32(reward.PersistentId), self.acc)[0]:
                self.errorResponse("Wrong lootbox id quest event stage")
                return False
        else:
            self.errorResponse("Unsupported reward type in quest event stage")
            return False
        return True

    @action_timing
    def onBuy(self, response):
        self.onBuyFunc(response)

    @model_callback
    def onBuyFunc(self, response):
        code = response['code']
        if code != ibilling.ERROR_CODE_OK:
            self.onBuyError(response, self.needGold)
            return

        self.doConfirmWriteOff(response)
        self.I.STATS.addResourcesChange(self.acc.auid, False, ResourceChangeItem.QuestEvent, "", self.price,
                                        self.acc.model.Resources)

        roll_result = self._do_roll()
        if roll_result:
            self.__on_roll_win()
        else:
            self.__on_roll_lose()

        if not self.__give_stage_reward(roll_result):
            return

        self.response['choice_result'] = {'event_id': self.arguments.questEventId,
                                          'stage_id': self.quest_stage_idx,
                                          'step_id': self.quest_step_idx,
                                          'result': roll_result}
        self.response["ok"] = 1
        self.fin()
