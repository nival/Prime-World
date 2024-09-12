# -*- coding: utf-8 -*-
from base.helpers import *
from enums import DynamicQuestAwardType

class ConvertDynamicQuestAwards:
    def convertModelData(self, env, acc, md, dict):
        # инкрементим тип, если надо
        for awardId, award in md.DynamicQuestAwardsKeeper.iteritems():
            if award.QuestAwardType >= DynamicQuestAwardType.RedPerl:
                award.QuestAwardType += 1
        return md, acc.db