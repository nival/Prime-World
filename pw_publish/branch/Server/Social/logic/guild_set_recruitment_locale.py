# -*- coding: utf-8 -*-
from subaction import *
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData
from logic.requests.GuildSetRecruitmentLocaleRequest import *

class Guild_set_recruitment_locale(SubAction, GuildSetRecruitmentLocaleRequest):
    """action, который будет обрабатывать данный класс"""
    action = "guild_set_recruitment_locale"

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

        self.I.GS.recruitmentLocale(self.acc, self.arguments.locale, self.onLocaleSet)

    @model_callback
    @action_timing
    def onLocaleSet(self, response):
        if response:
            info("onLocaleSet response: %s" % self.I.MD.pretty(response))
            changes = response.get("GuildData") or []
            if changes:
                try:
                    ModelChangeApplicator.apply(self.acc, "guilddata", GuildData, changes)
                except:
                    catch()
            self.acc.pending_events.append({"GuildData": {"GuildData": changes}})
            if self.acc.pending_handler:
                self.acc.pending_handler()
            self.response["ok"] = 1
        self.fin()