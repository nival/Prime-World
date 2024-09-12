# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GuildGerRecruitsListRequest import *
from guild.RecruitsData import RecruitsData

class Guild_get_recruits_list( SubAction, GuildGerRecruitsListRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "guild_get_recruits_list"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        if not self.acc.db.guildAuid:
            self.errorResponse(EC.NOT_IN_GUILD, "You're not in guild")
            return

        for _id, member in self.acc.guilddata.Members.iteritems():
            if member.Person == self.acc.auid and not member.IsOfficer:
                self.errorResponse(EC.GUILD_ONLY_OFFICER_CAN_OPERATE, "Only officer or leader can view recruits lists")
                return

        self.recruitsData = RecruitsData()
        self.recruitsData.init(None)
        self.I.GS.getRecruitsList(self.acc, self.arguments.position, self.arguments.sortCriteria, self.arguments.order,
                                  self.onRecruitsInfoFound)

    def onRecruitsInfoFound(self, response):
        if response:
            changes = response.get("RecruitsData") or []
            self.response["RecruitsData"] = changes

        self.response["callback"] = ["guild_get_recruits_list"]
        self.response["ok"] = 1
        self.fin()
