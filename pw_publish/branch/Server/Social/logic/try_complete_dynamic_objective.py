# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.TryCompleteDynamicObjectiveRequest import *

class Try_complete_dynamic_objective( SubAction, TryCompleteDynamicObjectiveRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "try_complete_dynamic_objective"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        self.acc.model.validateDynamicQuests(self.acc, self.I)

        self.quest = self.arguments.quest
        self.objective = self.arguments.objective
        if self.quest.getID() not in self.acc.model.DynamicQuests:
            self.errorResponse(EC.DYNAMIC_QUSET_LIFETIME_IS_OVER, "Quest is no longer available.")
            return

        if ((self.objective.getID() in self.quest.Objectives and not
              self.acc.model.checkOwnedDynamicQuestAwards(self.quest.Awards, self.acc))
            or (self.objective.getID() in self.quest.AlternativeObjectives and not
              self.acc.model.checkOwnedDynamicQuestAwards(self.quest.AlternativeAwards, self.acc))):
            tournamentQuests = self.acc.model.getTournamentsMapFromActiveQuests()
            self.acc.model.removeDynamicQuest(self.quest, self.acc, self.I, tournamentQuests)
            if not self.quest.RepeatOnMiss:
                self.acc.model.CompletedDynamicQuests.append(self.quest.PersistentId)
            self.errorResponse(EC.DYNAMIC_QUEST_AWARD_ALREADY_OWNED, "Player already owns such award.")
            return

        if self.objective.QuestCheckType == DynamicQuestCheckType.Instant:
            if self.objective.InstantCondition.ResourceType == CastleResources.TalentsToPay:
                if self.quest.checkTalentsToPayObjectiveComplete(self.acc, self.objective.talentsToDeletePersistentIds, self.objective):
                    self.objective.IsCompleted = True
            else:
                self.price = self.acc.model.getDynamicObjectivePrice(self.objective)
                self.needGold = int( self.price.Gold )
                reason = "PW!DYNAMIC_QUEST:" + str(self.quest.PersistentId)
                self.buy( self.price, self.onBuy, self.onBuyFunc, reason )
                return
        if self.quest.isComplete():
            self.quest.QuestState = QuestState.Complete

        self.response["ok"] = 1
        self.fin()

    @model_callback
    def onBuyFunc( self, response ):
        code = response["code"]
        if code == ibilling.ERROR_CODE_OK:
            self.doConfirmWriteOff( response )
            self.objective.IsCompleted = True
            self.objective.CurrentValue = self.objective.InstantCondition.TotalValue
            self.I.STATS.addResourcesChange(self.acc.auid, False, ResourceChangeItem.DynamicQuestReward,
                                             "QuestId=%r)" % str(self.quest.PersistentId),
                                             self.price, self.acc.model.Resources)
            if self.quest.isComplete():
                self.quest.QuestState = QuestState.Complete
            self.response["ok"] = 1
        else:
            self.onBuyError( response, self.needGold )
            return

        self.fin()


    @action_timing
    def onBuy( self, response ):
        self.onBuyFunc( response )
