# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GetRecommendedGuildsListRequest import *
from base.sql import RecommendedGuildListQuery
from guild.GuildWarsData import GuildWarsData
from ext_main.guild_app_loader import GuildApplicationsLoader

RecommendedGuildListQuery.setSortCriteria(FindGuildSortCriteria)

class Get_recommended_guilds_list(SubAction, GetRecommendedGuildsListRequest, RecommendedGuildListQuery, GuildApplicationsLoader):
    """action, который будет обрабатывать данный класс"""
    action = "get_recommended_guilds_list"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        self.acc.GuildWarsData = GuildWarsData()
        self.acc.GuildWarsData.init(None)
        if self.acc.db.guildAuid:
            warn("GetRecommendedGuildsListRequest: player is already in guild")
            self.response["ok"] = 1
            self.fin()
            return
        self.callWithGuildApplications(self.getAplicationsInfo)

    def getAplicationsInfo(self):
        self.applicationedGuildAuids = [app.GuildAuid for app_id, app in self.acc.model.GuildApplications.iteritems()]
        if self.applicationedGuildAuids:
            self.I.EXPORT.getRecommendedGuildsInfo(self.applicationedGuildAuids, self.onActualApplicationsInfoFound)
        else:
            self.findRecommendedGuilds()

    def onActualApplicationsInfoFound(self, reply):
        r = reply["r"]
        if r and len(r):
            for guildInfo in r:
                gi, giId = self.acc.GuildWarsData.newGuildRecruitmentInfo()
                gi.ShortInfo, _id = self.acc.GuildWarsData.newGuildShortInfo()
                GuildWarsData.FillGuildRecruitmentInfoFromSQL(gi, guildInfo)
                self.acc.GuildWarsData.RecommendedGuilds.add(gi)
        self.findRecommendedGuilds()

    def findRecommendedGuilds(self):
        maxRating = max([h.Rating for h_id, h in self.acc.model.Heroes.iteritems()])
        query, args = self.createSQLQuery(maxRating, self.applicationedGuildAuids)
        self.I.EXPORT.performQuery(query, args, self.onInfoFromSQL)

    def onInfoFromSQL(self, reply):
        r = reply["r"]
        if r and len(r):
            for guildInfo in r:
                gi, giId = self.acc.GuildWarsData.newGuildRecruitmentInfo()
                gi.ShortInfo, _id = self.acc.GuildWarsData.newGuildShortInfo()
                GuildWarsData.FillGuildRecruitmentInfoFromSQL(gi, guildInfo)
                self.acc.GuildWarsData.RecommendedGuilds.add(gi)

        for applicationId, application in self.acc.model.GuildApplications.items():
            if application.ExpireTime < int(time.time()):
                self.acc.model.GuildApplications.remove(application)

        changes = [MakeModelChangeString("init_guild_wars_data", "/", "init", self.acc.GuildWarsData.generateJsonDict())]
        self.response["callback"] = ["get_recommended_guilds_list"]
        self.response["GuildWarsData"] = changes
        self.response["ok"] = 1
        self.fin()
