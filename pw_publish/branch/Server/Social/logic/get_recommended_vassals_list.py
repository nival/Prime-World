# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GetRecommendedVassalsListRequest import *
from guild.GuildWarsData import GuildWarsData

class Get_recommended_vassals_list( SubAction, GetRecommendedVassalsListRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "get_recommended_vassals_list"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
          return

        if not self.acc.db.guildAuid:
            self.errorResponse( EC.NOT_IN_GUILD,  "You're not in guild" )
            return

        self.acc.GuildWarsData = GuildWarsData()
        self.acc.GuildWarsData.init(None)

        minRating = self.acc.guilddata.getRatingForRecommendedVassals()
        vauids = [v.ShortInfo.GuildAuid for _id, v in self.acc.guilddata.GuildVassals.iteritems()] + [ self.acc.db.guildAuid ]

        _callback = self.onRecommendedVassalFromSQL

        self.I.EXPORT.exportRecommendedVassalsData(vauids, minRating,
                                                   round(self.acc.guilddata.RatingInfo.Rating - 1), # пока 1 до тех пор пока не внесем параметр в Social
                                                    self.I.Config.getMainConfig().GUILD_LIST_RECOMMENDED_VASSAL_SIZE, #пока хардкод
                                                   _callback )


    def onRecommendedVassalFromSQL(self, reply):
        info("onRecommendedVassalFromSQL reply: %r " % reply)
        r = reply["r"]
        if r and len(r):
            for guildInfo in r:
                gi, giId = self.acc.GuildWarsData.newGuildsListEntity()
                gi.ShortInfo, _id = self.acc.GuildWarsData.newGuildShortInfo()
                GuildWarsData.FillGuildShortInfoFromSQL(gi, guildInfo)

                self.acc.GuildWarsData.RecommendedVassals.add(gi)

        changes = [MakeModelChangeString("init_guild_wars_data", "/", "init", self.acc.GuildWarsData.generateJsonDict())]
        self.response["callback"] = ["get_recommended_vassals_list"]
        self.response["GuildWarsData"] = changes
        self.response["ok"] = 1
        self.fin()


