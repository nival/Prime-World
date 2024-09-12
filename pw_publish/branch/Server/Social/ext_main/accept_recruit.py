#!/usr/bin/env python
# -"- coding: utf8 -"- 
# (C) Dmitry Kolb 2014, Nival Network 
__author__ = 'dmitry.kolb'

import CC
from modeldata.change_applicator import ModelChangeApplicator
import cfg
from guild.GuildData import GuildData
from siege.SiegeData import SiegeData
from base.service_lock import ServiceLock
from handlers import * # JsonHandler, globals: peers, users..
from subaction import SubAction, action_timing, model_callback
from base.helpers import *
from enums import GuildStatus

class AcceptRecruitAction(SubAction):
    action = "accept_recruit"

    def onStart(self):
        self.log()
        info("AcceptRecruitAction.onStart arguments= %r", self.arguments)
        if self.checkValidIntParam("guildAuid") and self.checkValidIntParam("auid"):
            self.acc = self.I.WS.getUserAccByAuid(self.auid)
            if self.acc:
                debug("AcceptRecruitAction: self.acc.auid=%s", self.acc.auid)
                bestHero = 0
                bestHeroRating = 0.0
                for heroId in self.acc.model.HeroesKeeper:
                    hero = self.acc.model.getHeroByID( heroId )
                    if hero.Rating > bestHeroRating:
                        bestHero = hero.PersistentId
                        bestHeroRating = hero.Rating

                debug("AcceptRecruitAction: dump %r", self.acc)
                if not self.acc.db.guildAuid:
                    self.acc.db.guildAuid = self.guildAuid

                self.I.GS.acceptGuild( self.acc,
                                       self.acc.snid,
                                       self.acc.snuid,
                                       self.acc.uid,
                                       options.server_id,
                                       self.acc.locale or cfg.MATCHMAKER_DEFAULT_LOCALE,
                                       bestHero,
                                       bestHeroRating,
                                       self.onAcceptGuild
                )
                return

            else:
                msg = "AcceptRecruitAction: BAD acc.model (auid=%s), accepting of recruit skipped" % self.acc.auid
                warn(msg)
                self.errorResponse(EC.ACCOUNT_NOT_LOADED, msg)
        else:
            msg = "AcceptRecruitAction: BAD params"
            warn(msg)
            self.errorResponse(EC.BAD_PARAM, msg)

    def onAcceptGuild(self, response):
        debug("AcceptRecruitAction.onAcceptGuild: %r", response)
        ec = EC.OK
        if response:
            isOk = response.get("ok") or 0
            if isOk:
                info("onAcceptGuild: ok, response: %s" % self.I.MD.pretty(response))
                SiegeData_changes = response.get("SiegeData") or []
                if SiegeData_changes:
                    try:
                        ModelChangeApplicator.apply(self.acc, "siegedata", SiegeData, SiegeData_changes)
                    except:
                        catch()
                GuildData_changes = response.get("GuildData") or []
                if GuildData_changes:
                    try:
                        ModelChangeApplicator.apply(self.acc, "guilddata", GuildData, GuildData_changes)
                    except:
                        catch()

                    self.acc.model.write( self.acc.pending )
                    self.acc.pending.setPrefix( "guildAccept:" )
                    self.acc.model.setComment( "auto" )
                    self.acc.model.LordInfo.GuildStatus = GuildStatus.AddedByApplication
                    for giId in self.acc.model.IncomingGuildInvites.keys():
                        guildInvite = self.acc.model.getGuildInviteByID(giId)
                        self.acc.model.IncomingGuildInvites.remove(guildInvite)

                    self.I.WS.removeRecruitApplications(self.acc )

                self.acc.pending_events.append({"GuildData": {"GuildData": GuildData_changes}})
                self.acc.pending_events.append({"SiegeData": {"SiegeData": SiegeData_changes}})
                self.I.STATS.addGuildJoined(self.acc.auid, self.acc.db.guildAuid, self.acc.db.fraction,
                                            len(self.acc.guilddata.Members))
            else:
                self.response['ec'] = response.get("ec") or EC.OK
                info( "AcceptRecruitAction.onAcceptGuild: failed, ec=%d" , self.response['ec'] )
                self.response['error'] = response.get("error") or ""
                self.I.GS.unsubscribe( self.acc, options.server_id, None )
                self.acc.db.guildAuid = 0
        else:
            self.I.GS.unsubscribe( self.acc, options.server_id, None )
            self.acc.db.guildAuid = 0

        if self.acc.pending_handler:
            self.acc.pending_handler()

        #освободим блокировку добавления
        self.lock = ServiceLock(self.I.DATA, 'recruit_' + str(self.acc.auid), self.onSemaphoreReady)

        self.acc.pending_events.append( {"callback": { "callback_ec": [ec], "callback": ["guild_accept"] }} )
        self.response["ok"] = 1
        self.fin()

    def onSemaphoreReady(self):
        self.lock.tryAcquire(self.onLockAquired)

    def onLockAquired(self, OK):
        debug("AcceptRecruitMailAction.onLockAquired %r", OK)
        self.lock.release()
        self.lock.removeVar()