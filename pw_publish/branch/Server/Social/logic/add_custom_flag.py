# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.AddCustomFlagRequest import *

class Add_custom_flag( SubAction, AddCustomFlagRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "add_custom_flag"
    debug = True

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        self.flagId = self.arguments.flagId

        self.staticCustomFlag = self.acc.SD.getCustomFlagById(self.flagId)
        self.customFlag = self.acc.getConfig().getCustomFlagById(self.flagId)
        if not self.customFlag or not self.staticCustomFlag:
            self.errorResponse(EC.FLAG_NOT_FOUND, "Custom flag was not found")
            return

        for flagId in self.acc.model.Flags:
            boughtFlag = self.acc.model.getOwnedFlagByID(flagId)
            if boughtFlag.PersistentId == self.flagId:
                self.errorResponse(EC.FLAG_IS_ALREADY_OWNED, "A flag is already bought")
                return

        self.acc.model.Flags.append(self.flagId)
        self.acc.model.FlagInfo.PersistentId = self.customFlag.PersistentId
        self.acc.model.FlagInfo.FlagType = FlagType.Special

        self.response["ok"] = 1 # success
        self.fin()