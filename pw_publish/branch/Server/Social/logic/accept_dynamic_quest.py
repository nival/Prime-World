# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.AcceptDynamicQuestRequest import *

class Accept_dynamic_quest( SubAction, AcceptDynamicQuestRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "accept_dynamic_quest"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    quest = self.arguments.quest

    self.acc.model.validateDynamicQuests(self.acc, self.I)
    if quest.getID() not in self.acc.model.DynamicQuests:
        self.errorResponse(EC.DYNAMIC_QUSET_LIFETIME_IS_OVER, "Quest is no longer available.")
        return

    if quest and quest.QuestState == QuestState.New:
      quest.QuestState = QuestState.InProgress
      self.I.STATS.addDynamicQuestChange(self.acc.auid, quest.PersistentId, quest.QuestName, 1, False)

    self.response["ok"] = 1
    self.fin()