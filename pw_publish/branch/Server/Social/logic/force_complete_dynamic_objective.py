# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ForceCompleteDynamicObjectiveRequest import *

class Force_complete_dynamic_objective( SubAction, ForceCompleteDynamicObjectiveRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "force_complete_dynamic_objective"
    debug = True

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        quest = self.arguments.quest
        for objectiveId in quest.Objectives:
            objective = self.acc.model.getDynamicObjectiveByID(objectiveId)
            if objective.QuestCheckType == DynamicQuestCheckType.Instant:
                objective.Value = objective.InstantCondition.TotalValue
            elif objective.QuestCheckType in [DynamicQuestCheckType.SessionInfo, DynamicQuestCheckType.SessionResult]:
                objective.Value = objective.SessionCondition.TotalValue
            elif objective.QuestCheckType == DynamicQuestCheckType.ModelData:
                objective.Value = objective.ModelDataCondition.TotalValue
            objective.IsCompleted = True
        quest.QuestState = QuestState.Complete

        self.response["ok"] = 1
        self.fin()