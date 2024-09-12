# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RecalcMyGuildRequest import *
import CC

class Recalc_my_guild( SubAction, RecalcMyGuildRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "recalc_my_guild"
    debug = True

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        if not self.acc.db.guildAuid:
            self.errorResponse(EC.NOT_IN_GUILD,  "You're not in guild")
            return

        self.I.GS.recalcRating(self.acc.db.guildAuid, self.I.WS.getGuildWarEventId(), self.onRecalcGuild)


    @model_callback
    def onRecalcGuild(self, response):
        if response:
            info("onRecalcGuild response: %s" % self.I.MD.pretty(response))
            isOk = response.get("ok") or 0
            if isOk:
                self.I.GS.updateVassalsAndSuzerainInfo(self.acc.db.guildAuid, self.onUpdateVassalsAndSuzerainInfo)
                return

        self.response["ok"] = 0
        self.fin()


    def onUpdateVassalsAndSuzerainInfo(self, response):
        if response:
            info("onRecalcGuild response: %s" % self.I.MD.pretty(response))
            isOk = response.get("ok") or 0
            if isOk:
                if self.acc.guilddata.GuildSuzerain.ShortInfo.GuildAuid and self.acc.guilddata.GuildSuzerain.ShortInfo.GuildAuid != CC.NPC_SUZERAIN_AUID:
                    args = dict(method="update_vassal_info", message={"targetAuid": self.acc.db.guildAuid})
                    self.I.SEX.sendToGuildService(self.acc.db.guildAuid, self.acc.guilddata.GuildSuzerain.ShortInfo.GuildAuid, args, self.onDummyGuildCallback)
                for vassalId, vassal in self.acc.guilddata.GuildVassals.iteritems():
                    if vassal.ShortInfo.GuildAuid != CC.NPC_VASSAL_AUID:
                        args = dict(method="new_suzerain_notify", message={"dontUpdateTime" : True})
                        self.I.SEX.sendToGuildService(self.acc.db.guildAuid, vassal.ShortInfo.GuildAuid, args, self.onDummyGuildCallback)
                self.response["ok"] = 1
                self.fin()
                return

        self.response["ok"] = 0
        self.fin()

    def onDummyGuildCallback(self, response):
        info("onDummyGuildCallback: result %s" % response)