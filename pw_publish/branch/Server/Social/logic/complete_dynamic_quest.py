# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.CompleteDynamicQuestRequest import *

class Complete_dynamic_quest( SubAction, CompleteDynamicQuestRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "complete_dynamic_quest"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        self.acc.model.validateDynamicQuests(self.acc, self.I)

        quest = self.arguments.quest
        if quest.getID() not in self.acc.model.DynamicQuests:
            self.errorResponse( EC.DYNAMIC_QUSET_LIFETIME_IS_OVER, "Quest is no longer available." )
            return


        if quest.QuestState == QuestState.Complete:
            if (quest.isMainComplete() and len(quest.Awards)) or (quest.isAlternativeComplete() and not len(quest.AlternativeAwards)):
                if not self.acc.model.checkOwnedDynamicQuestAwards(quest.Awards, self.acc):
                    self.removeQuest(quest)
                    self.errorResponse(EC.DYNAMIC_QUEST_AWARD_ALREADY_OWNED, "Player already owns such award.")
                    return
                for awardId, award in quest.Awards.iteritems():
                    self.acc.model.applyDynamicQuestAward(quest, award, self.acc, self.I, self.I.STATS)
            else:
                if not self.acc.model.checkOwnedDynamicQuestAwards(quest.AlternativeAwards, self.acc):
                    self.removeQuest(quest)
                    self.errorResponse(EC.DYNAMIC_QUEST_AWARD_ALREADY_OWNED, "Player already owns such award.")
                    return
                for awardId, award in quest.AlternativeAwards.iteritems():
                    self.acc.model.applyDynamicQuestAward(quest, award, self.acc, self.I, self.I.STATS)

            countTalents = 0
            for objectiveId, objective in quest.Objectives.iteritems():
                if objective.InstantCondition.ResourceType == CastleResources.TalentsToPay:
                    debug("start delete talents")
                    try:
                        quest.checkTalentsToPayObjectiveComplete(self.acc, objective.talentsToDeletePersistentIds, objective, addToTalToRemove = True)
                        for talentId in objective.verifiedTalentsToRemove:
                            self.acc.model.UserInventory.remove(self.acc.model.getTalentByID(talentId))
                            debug("delete talent in {} id".format(talentId))
                            countTalents += 1
                    except AttributeError:
                        debug("verifiedTalentsToRemove no such in objective")
            if countTalents != 0:
                debug("delete complete. {} deleted talents".format(countTalents))

            self.removeQuest(quest)
            self.response["ok"] = 1
            self.fin()
            return

        self.errorResponse( EC.QUEST_IS_NOT_READY_YET, "Quest objectives are not completed yet." )

    def removeQuest(self, quest):
        if not quest.RepeatOnMiss:
            self.acc.model.CompletedDynamicQuests.append(quest.PersistentId)
        self.acc.model.sendCompletedDynamicQuestStatistics(quest, self.acc, self.I)

        tournamentQuests = self.acc.model.getTournamentsMapFromActiveQuests()
        self.acc.model.removeDynamicQuest(quest, self.acc, self.I, tournamentQuests)