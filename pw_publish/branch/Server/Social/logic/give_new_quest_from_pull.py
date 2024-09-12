# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GiveNewQuestFromPullRequest import *

class Give_new_quest_from_pull( SubAction, GiveNewQuestFromPullRequest ):
    """action, ������� ����� ������������ ������ �����"""
    action = "give_new_quest_from_pull"
  
    @model_callback
    @parse
    def onStart(self):
        """��������� ����� ��� ��������� action"""
        self.log()
        if not self.checkParams():
          return

        for pullId, pull in self.acc.model.DynamicQuestPulls.iteritems():
            pull.LastActiveQuestStartTime -= self.acc.getConfig().ROTATION_QUEST_LIFETIME
            # Если квест ещё не бвл выполнен, сбрасываем его
            if pull.LastActiveQuestId not in self.acc.model.CompletedDynamicQuests:
                self.acc.model.CompletedDynamicQuests.append(pull.LastActiveQuestId)
                for questId, quest in self.acc.model.DynamicQuests.iteritems():
                    if quest.PersistentId == pull.LastActiveQuestId:
                        tournamentQuests = self.acc.model.getTournamentsMapFromActiveQuests()
                        self.acc.model.removeDynamicQuest(quest, self.acc, self.I, tournamentQuests)

        self.response["ok"] = 1
        self.fin()