# -*- coding: utf-8 -*-
from subaction import *
from logic.requests.CreateRecruitApplicationRequest import *
import CC
from itertools import chain

class Create_recruit_application( SubAction, CreateRecruitApplicationRequest ):
    """Создание запроса игрока на принятие его в клан."""
    action = "create_recruit_application"

    @model_callback  # changes could be made ba checkPlayerGuildApplications
    @parse
    def onStart(self):
        acc = self.acc
        info("Create_recruit_application: auid=%s, guildAuid=%s", acc.db.auid, self.arguments.guildAuid)
        if not self.checkParams():
            return
        # params: self.arguments.guildAuid, self.arguments.message

        if acc.db.guildAuid:
            self.errorResponse(EC.RECRUIT_IN_GUILD, "You're in a guild already.")
            return

        if self.I.WS.checkPlayerGuildApplications(acc) >= acc.SD.data['GuildRecruitment']['maxUserGuildRequests']:
            self.errorResponse(EC.RECRUIT_REQUESTS_LIMIT, "Too many recruit applications from user.")
            return

        if acc.model.checkGuildApplication(self.arguments.guildAuid):
            self.errorResponse(EC.RECRUIT_STILL_WAITING, "Already applied to this guild")
            return

        # Check if the guild is overcrowded. TODO: do it through the guild-coordinator!
        self.I.GS.checkGuildSize(self.arguments.guildAuid, self.onGuildSize)


    def onGuildSize(self, response):
        if not (response and response["ok"]):
            if response and response["ec"] == 0 and response["error"] == "no guild":
                self.errorResponse(EC.RECRUIT_NO_GUILD, "Guild not found")
                return
            warn("Create_recruit_application.onGuildSize bad response: %r", response)
            self.errorResponse(EC.RECRUIT_NO_GUILD, "Guild not found or guild data is broken")
            return

        info("Create_recruit_application.onGuildSize: current %s, max %s", response["current"], response["max"])
        if response["current"] >= response["max"]:
            self.errorResponse(EC.RECRUIT_GUILD_OVERCROWDED, "The guild is full of members, you can't apply.")
            return

        SD = self.acc.SD
        # собираем - массив из пар {hero_id, rating}, заполняется всеми героями трёх старших званий у игрока.
        ratings = {}
        max_rating = 0
        # prepre dict if heroes by their ranks
        for h_id, hero in self.acc.model.Heroes.iteritems():
            if hero.Hired:
                if hero.Rating > max_rating:
                    max_rating = hero.Rating
                ratings.setdefault(SD.getRank(hero.Rating),[]).append((hero.PersistentId, hero.Rating))

        application = dict(
            nickname = self.acc.nick,
            pers_auid = self.acc.db.auid,
            guild_auid = self.arguments.guildAuid,
            text = self.arguments.message,
            heroes = list(chain.from_iterable(ratings[k] for k in sorted(ratings.iterkeys(), reverse=True)[:3])),
            max_rating = max_rating,
            fame = self.acc.model.LordInfo.Fame,
            status = 1, # 1 - active, 0 - declined
            created = int(time.time())
        )
        self.I.DATA.insert(CC.PLAYER_GUILD_REQUESTS_DATA, CC.PLAYER_GUILD_REQUESTS_DATA, application,
                           callback=functools.partial(self.onApplicationSaved, application=application))


    @model_callback
    def onApplicationSaved(self, response, application):
        info("onApplicationSaved: response %r, application %r", response, application)
        if not response or response.get("r") is None:
            err("onApplicationSaved: error saving to mongo: %s", response.get("ex"))
            self.response["ok"] = 0
            self.response["error"] = "Error saving recruit application data"
            self.fin()
            return

        self.acc.model.fillGuildApplication(application, self.acc.SD.data['GuildRecruitment']['guildRequestLifetime'])

        self.I.GS.newRecruitNotification(self.acc.db.auid, self.arguments.guildAuid)

        self.response["ok"] = 1
        self.fin()

