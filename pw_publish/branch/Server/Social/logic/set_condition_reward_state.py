# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetConditionRewardStateRequest import *

class Set_condition_reward_state( SubAction, SetConditionRewardStateRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "set_condition_reward_state"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    quest = self.arguments.quest
    if quest and quest.state == QuestState.InProgress and quest.id in self.acc.model.ActiveQuests:
      quest.applyConditionalAction = self.arguments.state

    self.response["ok"] = 1
    self.fin()