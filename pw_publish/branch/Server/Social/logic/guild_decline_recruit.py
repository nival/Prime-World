# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GuildDeclineRecruitRequest import *
import EC

class Guild_decline_recruit( SubAction, GuildDeclineRecruitRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "guild_decline_recruit"

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

        self.I.GS.declineRecruit(self.acc, self.arguments.auid, self.onRecruitApplicationRejected)


    def onRecruitApplicationRejected(self, response):
        if response:
            if response.get("ok"):
                self.response["ok"] = 1
                self.fin()
            else:
                self.errorResponse( response.get("ec") or EC.INTERNAL_SERVER_ERROR, "Can't decline recruit: %s" % (response.get("error") or "Unknown error" ) )
        else:
            self.errorResponse(EC.INTERNAL_SERVER_ERROR, "Empty response from guild service")
