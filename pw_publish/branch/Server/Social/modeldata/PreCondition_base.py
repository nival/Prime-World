# -*- coding: utf-8 -*-
# Automatically generated template file. Remove this string if you modify this file.

class PreCondition_base(object):
    def serializeToFile(self, file, name):
        pass

    def fill(self, cond, quest, model, SD):
        self.PreConditionType = cond["PreConditionType"]
        self.TournamentMapType = cond["TournamentMapType"]
