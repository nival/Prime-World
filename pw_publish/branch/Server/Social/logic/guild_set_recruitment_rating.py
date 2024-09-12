# -*- coding: utf-8 -*-
from subaction import *
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData
from logic.requests.GuildSetRecruitmentRatingRequest import *

class Guild_set_recruitment_rating( SubAction, GuildSetRecruitmentRatingRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "guild_set_recruitment_rating"

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

        self.I.GS.recruitmentRating(self.acc, self.arguments.rating, self.onRatingSet)

    @model_callback
    @action_timing
    def onRatingSet(self, response):
        if response:
            info("onRatingSet response: %s" % self.I.MD.pretty(response))
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