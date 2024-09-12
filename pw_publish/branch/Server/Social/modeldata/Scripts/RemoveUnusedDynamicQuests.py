# -*- coding: utf-8 -*-
from base.helpers import *

class RemoveUnusedDynamicQuests:
    """ Уберём нерабочие динамические квесты, для которых добавили данные в кипер, но не добавили в сет """
    def convertModelData( self, env, acc, md, dict ):
        for questId, quest in md.DynamicQuestKeeper.items():
            if questId not in md.DynamicQuests:
                md.DynamicQuestKeeper.__delitem__(questId)
        for objectiveId, objective in md.DynamicObjectivesKeeper.items():
            isActive = False
            for questId, quest in md.DynamicQuests.iteritems():
                if objectiveId in quest.Objectives:
                    isActive = True
                    break
            if not isActive:
                md.DynamicObjectivesKeeper.__delitem__(objectiveId)
        for awardId, award in md.DynamicQuestAwardsKeeper.items():
            isActive = False
            for questId, quest in md.DynamicQuests.iteritems():
                if awardId in quest.Awards:
                    isActive = True
                    break
            if not isActive:
                md.DynamicQuestAwardsKeeper.__delitem__(awardId)
        return md, acc.db