#!/usr/bin/env python
# -*- coding: utf-8 -*-
import functools, datetime
from base.helpers import *
from subaction import SubAction, action_timing, separate_timing
from modeldata.changes import MakeModelChangeString
from guild.GuildRequests import getMongoKey, getMongoKeyAuid, getGuildChatName, getNumberOfDays
from guild.GuildMapData import GuildMapData
from guild.GuildWarsData import GuildWarsData

import EC
import CC
from StatisticCore.ttypes import GuildInteractionType
from StatisticCore.ttypes import TalentInfo, TalentChangeOperation

# ------------------------ SUZERAIN - VASSAL INTERACTIONS ------------------------ #


class UpdateVassalsAndSuzerainInfoAction(SubAction):
    action = "update_vassals_and_suzerain_info"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: UpdateVassalsAndSuzerainInfoAction")
        if self.checkValidIntParam("guildAuid"):
            self.fakeAcc = ClassDict(auid=CC.GUILD_NEUTRAL_AUID, GuildData=None, SiegeData=None, guildAuid=self.guildAuid)
            self.I.WS.loadGuildData(self.fakeAcc, self.loadGuildData)
        else:
            self.fin()


    def loadGuildData(self, acc, errMessage=None):
        info("GuildService: UpdateVassalsAndSuzerainInfoAction  loadGuildData callback call guildAuid: {0}".format(self.guildAuid))
        if errMessage is not None:
            self.response["ok"] = 0
            self.response["error"] = errMessage
            self.fin()
            return

        self.I.WS.resetPendingChanges(self.fakeAcc)
        self.fakeAcc.GuildData.write(acc.pending)
        # почистим лимит инвайтов раз уж GuildData загружена
        # по хорошему надо бы проверять через self.GUILD_SUZERAIN_INVITE_TIMELIMIT
        # но пока у нас 1 день на хранение ограничений
        if self.fakeAcc.GuildData.GuildInfo.CountSuzerainInvitesTimeLimit <= int(time.time()):
            self.fakeAcc.GuildData.GuildInfo.CountSuzerainInvites = 0
            self.fakeAcc.GuildData.GuildInfo.CountSuzerainInvitesTimeLimit = 0

        updateAuids = []
        for vassalId, vassal in self.fakeAcc.GuildData.GuildVassals.iteritems():
            debug("GuildService: UpdateVassalsAndSuzerainInfoAction  loadGuildData ShortInfo dump %r", vassal.ShortInfo.generateJsonDict())
            if vassal and vassal.ShortInfo and vassal.ShortInfo.get() and vassal.ShortInfo.GuildAuid != CC.NPC_VASSAL_AUID:
                updateAuids.append(getMongoKeyAuid(vassal.ShortInfo.GuildAuid))

        debug("GuildService: UpdateVassalsAndSuzerainInfoAction loadGuildData Suzerain dump: {0}".format(self.fakeAcc.GuildData.GuildSuzerain.generateJsonDict()))
        if self.fakeAcc.GuildData.GuildSuzerain and self.fakeAcc.GuildData.GuildSuzerain.get():
            self.GSShortInfo = self.fakeAcc.GuildData.GuildSuzerain.ShortInfo.get()
            debug("GuildService: RecalcRatingAction  ShortInfo dump {0}".format(self.GSShortInfo.generateJsonDict()))
            if (self.GSShortInfo and self.GSShortInfo.GuildAuid and self.GSShortInfo.GuildAuid != CC.NPC_SUZERAIN_AUID):
                updateAuids.append(getMongoKeyAuid(self.GSShortInfo.GuildAuid))

        else:
            # Это странно, но сюзерена нет..
            warn("UpdateVassalsAndSuzerainInfoAction: no suzerain in guild %d", self.fakeAcc.GuildData.GuildAuid)

        if updateAuids:
            self.I.DATA.find("guilds", "guilds", {"key": {"$in": updateAuids}}, self.onGuildsInfoFound)
        else:
            self.onRecommendedVassalsUpdated()
            #self.I.WS.updateRecommendedVassalsList(self.fakeAcc, self.fakeAcc.GuildData, self.onRecommendedVassalsUpdated)

    def onGuildsInfoFound(self, response):
        debug("GuildService: UpdateVassalsAndSuzerainInfoAction.onGuildsInfoFound response: %r", response)
        if response and response["r"].count():
            for vassalInfo in response["r"]:
                try:
                    data_json = vassalInfo["data"]
                    guildDict = json_loads(data_json)
                except :
                    catch()
                    continue

                if guildDict and guildDict.get("GuildData"):
                    guildAuid = pathFind(guildDict, "GuildData/GuildAuid")
                    for vassalId, vassal in self.fakeAcc.GuildData.GuildVassals.iteritems():
                        debug("GuildService: UpdateVassalsAndSuzerainInfoAction.onGuildsInfoFound  ShortInfo dump {0}".format(vassal.ShortInfo.generateJsonDict()))
                        if vassal and vassal.ShortInfo and vassal.ShortInfo.get() and vassal.ShortInfo.GuildAuid == guildAuid:
                            self.I.WS.fillVassal(vassal, guildDict, self.I.SD.getGuildShopLevel(self.fakeAcc.GuildData.RatingInfo.Rating, False))
                            break
                    if self.GSShortInfo.GuildAuid == guildAuid:
                        self.I.WS.updateSuzerainFromDict(self.fakeAcc.GuildData, guildDict)
                        self.I.WS.resetAllShopItems(self.fakeAcc.GuildData)

                # Проверим, не пора ли бунтовать
                if self.GSShortInfo and self.GSShortInfo.Rating < self.fakeAcc.GuildData.RatingInfo.Rating and self.GSShortInfo.GuildAuid != 0:
                    if self.GSShortInfo and self.fakeAcc.GuildData.GuildInfo.StartAutoRevolt:
                        self.I.SIEGE.startSiege((self.fakeAcc.GuildData.GuildAuid, self.fakeAcc.GuildData.RatingInfo.Rating),
                                      (self.fakeAcc.GuildData.GuildAuid, self.fakeAcc.GuildData.RatingInfo.Rating),
                                      (self.GSShortInfo.GuildAuid, self.fakeAcc.GuildData.RatingInfo.Rating),
                                      0, self.onRevoltStarted)
                        return
                    else:
                        self.fakeAcc.GuildData.GuildInfo.StartAutoRevolt = True
                else:
                    self.fakeAcc.GuildData.GuildInfo.StartAutoRevolt = False

        self.onRecommendedVassalsUpdated()
        #self.I.WS.updateRecommendedVassalsList(self.fakeAcc, self.fakeAcc.GuildData, self.onRecommendedVassalsUpdated)

    def onRevoltStarted(self, response):
        if response:
            info("onRevoltStarted response: %s" % response)
            isOk = response.get("ok") or 0
            if isOk:
                guildAuids = []
                self.fakeAcc.SiegeData.write(self.fakeAcc.pending)
                try:
                    # Добавим данные по новой осаде в SiegeData
                    guildAuids = self.fakeAcc.SiegeData.update([response["siege"]])
                except:
                    catch()
                    self.onRecommendedVassalsUpdated()
                    return
                self.fakeAcc.GuildData.GuildInfo.StartAutoRevolt = False

                self.fakeAcc.GuildData.addActiveSiege(response["siege"]["_id"])

                if self.fakeAcc.GuildData.GuildAuid == response["siege"]["target"]:
                    self.fakeAcc.GuildData.SiegeForMyGuildEndTime = response["siege"]['end_time']
                if guildAuids:
                    self.I.EXPORT.getGuildsInfo(guildAuids, self.onSiegeDataFromSQL)
            else:
                self.onRecommendedVassalsUpdated()
                err("StartRevolt: bad response from siege service")


    @action_timing
    def onSiegeDataFromSQL(self, reply):
        r = reply["r"]
        if r and len(r):
            # Обновим заодно и все старые записи, если у этих кланов что-то изменилось
            for guildInfo in r:
                self.fakeAcc.SiegeData.updateGuildInfoFromSQL(guildInfo)
            changes = self.I.WS.pickPendingChanges(self.fakeAcc)
            self.I.WS.sendBroadCast(self.fakeAcc, changes, [], '')
            self.I.WS.saveGuildData(self.fakeAcc, None)
            self.response["GuildData"] = changes.get("guild_data", [])
            self.response["SiegeData"] = changes.get("siege_data", [])
            self.response["ok"] = 1
        self.fin()

    def onRecommendedVassalsUpdated(self):
        changes = self.I.WS.pickPendingChanges(self.fakeAcc)
        self.I.WS.sendBroadCast(self.fakeAcc, changes, [], '')

        if hasattr(self.fakeAcc.GuildData, 'GuildAuid') and self.fakeAcc.GuildData.GuildAuid == 0:
            msg = "UpdateVassalsAndSuzerainInfoAction: attempting to save zero guildAuid"
            warn(msg)
            self.response["ok"] = 0
            self.response["error"] = msg
            self.fin()
        else:
            self.I.WS.saveGuildData(self.fakeAcc, self.onSave)

    def onSave(self, data_reply):
        debug("GuildService: persistent reply (value=%r)", data_reply.get("r") if data_reply else "empty reply from mongo db")
        self.response["ok"] = 1
        self.fin()


class ClearSuzerainInvitesAction(SubAction):

    action = "clear_suzerain_invites"
    @action_timing
    def onStart(self):
        info("GuildService: ClearSuzerainInvitesAction")
        if self.checkValidIntParam("guildAuid"):
            self.I.WS.loadGuildDataByGuildAuid(self.guildAuid, self.onRequestsLoaded)
        else:
            self.response["ok"] = 1
            self.fin()

    def onRequestsLoaded(self, response):
        debug(" ClearSuzerainInvitesAction.onRequestsLoaded response: %r " % response)
        if response:
            try:
                self.Requests = response["r"].get("requests") or  {"SuzerainInvites": {}}
            except:
                self.Requests = {"SuzerainInvites": {}}

            self.I.WS.updateSuzerainInvites(self.guildAuid, self.Requests)

        self.response["ok"] = 1
        self.fin()


class InviteSuzerainAction(SubAction):
    action = "invite_suzerain"

    """ отсылаем приглашение потенциальному сюзерену на принятие нас любимых в вассалы """

    @action_timing
    def onStart(self):
        info("GuildService.InviteSuzerainAction")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("guildId"):
            self.acc = self.I.WS.getUserAcc(self.auid)
            if self.acc:
                member = self.acc.GuildData.findMemberByAuid(self.auid)
                if member and not member.IsOfficer:
                    self.response["error"] = "You(%r) are not officer!" % self.auid
                    self.response["ec"] = EC.GUILD_ONLY_OFFICER_CAN_OPERATE
                    self.response["ok"] = 0
                    self.fin()
                    return

                if self.acc.GuildData.GuildInfo.CountSuzerainInvites >= self.I.Config.getMainConfig().GUILD_SUZERAIN_INVITE_LIMIT:
                    warn("GuildService.InviteSuzerainAction suzerain invite limit %r" % self.acc.GuildData.GuildInfo.CountSuzerainInvites)
                    self.response["error"] = "Suzerain invite limit %r" % self.acc.GuildData.GuildInfo.CountSuzerainInvites
                    self.response["ec"] = EC.DEBUG_MESSAGE
                    self.response["ok"] = 0
                    self.fin()
                    return
                else:
                   self.I.WS.loadGuildDataByGuildAuid(self.guildId, self.onLoadSuzerainGuild )
            else:
                 err("GuildService.InviteSuzerainAction can not find acc by user auid=%r" % self.auid)
        else:
            err("GuildService.InviteSuzerainAction invalid params " % self.auid)


    @action_timing
    def onLoadSuzerainGuild(self, response):
        info("GuildService.InviteSuzerainAction.onLoadSuzerainGuild response: %r " % response)
        if response:
            try:
                data_json = response["r"]["data"] or '{"GuildData":{}}'
                requests_json = response["r"].get("requests") or  {"SuzerainInvites": {}}
            except:
                data_json = '{"GuildData":{}}'
                requests_json = {"SuzerainInvites": {}}
            GData = json_loads(data_json)
            GData["requests"] = requests_json
            self.processGuild(GData)
        else:
            err("GuildService.InviteSuzerainAction bad response: %r" % response)

    def processGuild(self, guild):
        #info("GuildService.InviteSuzerainAction.processGuild guild: %r " % guild)
        vassalsSet = pathFind(guild, "GuildData/GuildVassals/Set")
        shortInfoKeeper = pathFind(guild, "GuildData/GuildShortInfoKeeper/Keeper")
        if vassalsSet and shortInfoKeeper:
            shortInfoKeys = [pathFind(guild, "GuildData/GuildMapEntityKeeper/Keeper/%s/GuildMapEntity/ShortInfo" % key,
                                     force_int_keys=False) for key in vassalsSet]

            if any(shortInfoKeeper[str(key)]["GuildShortInfo"].get("GuildAuid") == self.acc.GuildData.GuildAuid for key in shortInfoKeys):
                self.response["error"] = "GuildService.InviteSuzerainAction.processGuild: Your guild (%r) already are vassal of the guild (%r) " % (self.acc.GuildData.GuildAuid, self.guildId)
                self.response["ec"] = EC.DEBUG_MESSAGE
                self.response["ok"] = 0
                self.fin()
                return

        if str(self.acc.GuildData.GuildAuid) in guild["requests"]["SuzerainInvites"]:
            self.response["error"] = "GuildService.InviteSuzerainAction.processGuild: You already have suzerain's invite for this guild"
            self.response["ec"] = EC.GUILD_SUZERAININVITES_IS_ALWAYS_ADDED
            self.response["ok"] = 0
            self.fin()
            return

        suzerainInvites = ClassDict()
        suzerainInvites.guildFullName = self.acc.GuildData.GuildInfo.FullName
        suzerainInvites.guildShortName = self.acc.GuildData.GuildInfo.ShortName
        suzerainInvites.timeToAutoDecline = toint( time.time() ) + self.I.Config.getMainConfig().GUILD_SUZERAIN_INVITE_TIMEOUT

        self.I.WS.saveRequests(self.guildId, self.acc.GuildData.GuildAuid, suzerainInvites, self.onSaveRequests)


    def onSaveRequests(self, response):
        info("GuildService.InviteSuzerainAction.onSaveRequests response: %r " % response)
        if response:
            self.I.WS.resetPendingChanges(self.acc)
            self.acc.GuildData.write(self.acc.pending)
            if not self.acc.GuildData.GuildInfo.CountSuzerainInvitesTimeLimit:
                self.acc.GuildData.GuildInfo.CountSuzerainInvitesTimeLimit = toint(time.time()) + self.I.Config.getMainConfig().GUILD_SUZERAIN_INVITE_TIMELIMIT

            self.acc.GuildData.GuildInfo.CountSuzerainInvites += 1
            mess = dict(method="new_recommended_vassal_notify", message={} )
            self.I.SEX.sendToGuildService(self.acc.GuildData.GuildAuid, self.guildId, mess, self.onSuzerainNotify)
            return

        else:
            self.response["ec"] = EC.DEBUG_MESSAGE
            self.response["error"] = "GuildService.InviteSuzerainAction.onSaveRequests: Unknown problems of suzerain's invites saving"
            self.response["ok"] = 0
        self.fin()

    def onSuzerainNotify(self, response):
        info("GuildService.InviteSuzerainAction.onSuzerainNotify response: %r " % response)
        if not response or not response.get("ok"):
            err("bad notify response")

        self.response["ok"] = 1
        changes = self.I.WS.pickPendingChanges(self.acc)
        self.I.WS.sendBroadCast(self.acc, changes, [], '')
        self.I.WS.saveGuildData(self.acc, None)
        self.response["GuildData"] = changes.get("guild_data", [])

        self.fin()


class CheckVassalApplicationAction(SubAction):
    action = "check_vassal_application"
    """ Смотрим, есть ли у нас прошение от клана и пробуем принять, если нашлось """

    @action_timing
    def onStart(self):
        info("GuildService: CheckVassalApplicationAction")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("guildId"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                if acc.Requests and "SuzerainInvites" in acc.Requests and str(self.guildId) in acc.Requests["SuzerainInvites"]:
                    args = ClassDict(auid=[self.auid], guildId=[self.guildId])
                    action = AcceptVassalAction(args, self.onVassalApplicationHandled, I=self.I)
                    action.onStart()
                    return
                else:
                    self.errorResponse(EC.GUILD_YOU_MUST_START_SIEGE, "No vassal application from %d" % self.guildId)
        self.fin()

    def onVassalApplicationHandled(self, response):
        if response:
            isOk = response.get("ok") or 0
            if isOk:
                self.response["ok"] = 1
            else:
                self.response["error"] = response.get("error") or ""
                self.response["ec"] = response.get("ec") or 0
        self.fin()


class AcceptVassalAction(SubAction):
    action = "accept_vassal"

    """ Принимаем прошение от вассала """

    @action_timing
    def onStart(self):
        info("GuildService: AcceptVassalAction [auid=%s, candidateGuildAuid=%s]",
             self.arguments.get("auid"), self.arguments.get("candidateGuildAuid"))
        if self.checkValidIntParam("auid") and self.checkValidIntParam("candidateGuildAuid"):
            self.potentialVassalAuid = self.candidateGuildAuid
            self.acc = self.I.WS.getUserAcc(self.auid)
            info( "acc.guildAuid=%s  self.acc.GuildData.GuildAuid=%s ", self.acc.guildAuid, self.acc.GuildData.GuildAuid )

            if self.acc:
                self.tryAcceptVassal()
                return
            else:
                err("GuildService.AcceptVassalAction can not find acc by user auid=%r" % self.auid)
        else:
            err("GuildService.AcceptVassalAction invalid params " % self.auid)

        self.fin()

    def tryAcceptVassal(self):
        member = self.acc.GuildData.findMemberByAuid(self.auid)
        if member and not member.IsOfficer:
            self.errorResponse(EC.GUILD_ONLY_OFFICER_CAN_OPERATE, "You(%r) are not officer!" % self.auid)
            return

        if self.acc.GuildData.GuildInfo.GMLockTime > int(time.time()):
            self.errorResponse(EC.GUILD_IS_LOCKED_BY_GM, "Guild %d is locked by GM" % self.acc.GuildData.GuildAuid)
            return

        #info( "AcceptVassalAction: requests = %s" %  self.acc.Requests)
        if not self.acc.Requests or not self.acc.Requests['SuzerainInvites']:
            warn(" Have to load guild requests from db [guildAuid=%s, action_name=AcceptVassalAction]", self.acc.guildAuid)
            self.I.WS.loadGuildDataByGuildAuid(self.acc.guildAuid, self.onRequestsLoaded)
        else:
            self.acceptRequest(self.acc.Requests['SuzerainInvites'])

    def onRequestsLoaded(self, response):
        info("GuildService.AcceptVassalAction.onRequestsLoaded response: %r " % response)
        if response:
            try:
                self.acc.Requests = response["r"].get("requests") or  {"SuzerainInvites": {}}
            except:
                self.acc.Requests = {"SuzerainInvites": {}}

        self.acceptRequest(self.acc.Requests['SuzerainInvites'])

    def acceptRequest(self, suzerain_invites):
        info("GuildService.AcceptVassalAction.acceptRequest: %r ", suzerain_invites)
        if not suzerain_invites or str(self.potentialVassalAuid) not in suzerain_invites:
            self.errorResponse(EC.GUILD_YOU_MUST_START_SIEGE, "No vassal application from %s" % self.potentialVassalAuid)
            return

        self.I.WS.loadGuildDataByGuildAuid(self.potentialVassalAuid, self.onLoadVassalGuild)

    def onLoadVassalGuild(self, response):
        info("GuildService.AcceptVassalAction.onLoadVassalGuild response: %r " % response)
        if response:
            try:
                data_json = response["r"]["data"] or '{"GuildData":{}}'
            except:
                data_json = '{"GuildData":{}}'

            self.addVassal(json_loads(data_json))
        else:
            err("GuildService.AcceptVassalAction.onLoadVassalGuild bad response: %r" % response)
            self.fin()

    def addVassal(self, vassal_guild):
        if pathFind(vassal_guild, "GuildData/GuildInfo/GuildInfo/GMLockTime") > int(time.time()):
            self.errorResponse(EC.GUILD_IS_LOCKED_BY_GM, "Guild is locked by GM")
            return

        suzerainId = pathFind(vassal_guild, "GuildData/GuildSuzerain")
        shortInfoId = pathFind(vassal_guild, "GuildData/GuildMapEntityKeeper/Keeper/%s/GuildMapEntity/ShortInfo" % suzerainId, force_int_keys=False)
        if pathFind(vassal_guild, "GuildData/GuildShortInfoKeeper/Keeper/%s/GuildShortInfo/GuildAuid" % shortInfoId, force_int_keys=False):
            self.errorResponse(EC.GUILD_YOU_MUST_START_SIEGE, "You need to start siege for accepting vassal!")
            return

        # а теперь посмотрим осаждают ли потенциального вассала
        _callback = functools.partial(self.onGetSieges, vassal_guild)
        self.I.SIEGE.getSieges(self.potentialVassalAuid, _callback)

    def onGetSieges(self, vassal_guild, response):
        info("GuildService.AcceptVassalAction.onGetSieges response: %r" % response)
        if response:
            for siegeInfo in response:
                if siegeInfo["target"] == self.potentialVassalAuid:
                    # Чувак тя осаждают! Сча мы вломим этим супостатам
                    self.errorResponse(EC.GUILD_YOU_MUST_JOIN_SIEGE, "You need to join siege for accepting vassal!")
                    return

        # если response пустой или мы не нашли осады, предметом которой является потенциальный вассал

        if len(self.acc.GuildData.GuildVassals) >= self.I.Config.getMainConfig().GUILD_MAX_VASSAL_SIZE:
            self.errorResponse(EC.GUILD_MAX_VASSAL_SIZE, "Your clan already have maximum count of vassals!")
            return

        # если у вассала нету сюзерена, проверяем стоимость и автоматом добавляем его
        targetRating = pathFind(vassal_guild, "GuildData/RatingInfo/RatingInfo/Rating")
        priceToAccept = self.acc.GuildData.getSiegeStartPrice(self.potentialVassalAuid, targetRating, self.I.Config.getMainConfig().SiegeSettings)
        if self.acc.GuildData.GuildInfo.CWPoints_Clan >= priceToAccept:
            self.guild = vassal_guild
            _callback = functools.partial(self.onNotifySuzerain, priceToAccept)
            self.notifySuzerain(self.potentialVassalAuid, _callback)
            return
        else:
            self.errorResponse(EC.NOT_ENOUGH_RESOURCES, "StartSiege: not enough guild points")
            return

    def notifySuzerain(self, guildAuid, callback):
        mess = dict(method="new_suzerain_notify", message={})
        self.I.SEX.sendToGuildService(self.acc.GuildData.GuildAuid, guildAuid, mess, callback)

    def onNotifySuzerain(self, priceToAccept, response ):
        info("GuildService: AcceptVassalAction.onNotifySuzerain response: %r " % response)
        if response and response.get("ok") and self.guild:
            self.I.WS.resetPendingChanges(self.acc)
            self.acc.GuildData.write(self.acc.pending)

            self.acc.GuildData.GuildInfo.CWPoints_Clan -= priceToAccept
            self.I.WS.createVassal(self.acc.GuildData, self.guild)
            self.removeGuildFromRequests(self.guild)
            self.I.WS.removeGuildFromRecommendedVassal(self.acc, self.potentialVassalAuid)
            if str(self.potentialVassalAuid) in self.acc.GuildData.ExVassals:
                del self.acc.GuildData.ExVassals[str(self.potentialVassalAuid)]

            changes = self.I.WS.pickPendingChanges(self.acc)

            self.I.WS.sendBroadCast(self.acc, changes, [], '')
            self.I.WS.saveGuildData(self.acc, None)
            self.response["GuildData"] = changes.get("guild_data", [])
            self.response["ok"] = 1
        else:
            # что то пошло не так с нотификацией
            self.response["ec"] = EC.GUILD_CANNOT_NOTIFY
            self.response["error"] = "Can not notify our vassal that I am his suzerain!"
            self.response["ok"] = 0
        self.fin()

    def removeGuildFromRequests(self, guild):
        GuildAuid = pathFind(guild, "GuildData/GuildAuid")
        if str(GuildAuid) in self.acc.Requests["SuzerainInvites"]:
            del self.acc.Requests["SuzerainInvites"][str(GuildAuid)]
        self.I.WS.removeRequestsData(self.acc.GuildData.GuildAuid, {"requests.SuzerainInvites.%s" % str(GuildAuid) : str(GuildAuid)})


class DeclineVassalAction(SubAction):
    action = "decline_vassal"

    """ отказываемcя принимать в вассалы """

    @action_timing
    def onStart(self):
        info("GuildService: DeclineVassalAction")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("guildId"):
            self.acc = self.I.WS.getUserAcc(self.auid)
            if self.acc and self.acc.Requests and self.acc.Requests['SuzerainInvites']:
                self.removeRequest()
            else:
                warn(" Have to load guild requests from db [guildAuid=%s, action_name=DeclineVassalAction]", self.acc.guildAuid)
                self.I.WS.loadGuildDataByGuildAuid(self.acc.guildAuid, self.onRequestsLoaded)
                return

    def onRequestsLoaded(self, response):
        info("GuildService.AcceptVassalAction.onRequestsLoaded response: %r " % response)
        if response:
            try:
                self.acc.Requests = response["r"].get("requests") or  {"SuzerainInvites": {}}
            except:
                self.acc.Requests = {"SuzerainInvites": {}}

        self.removeRequest()

    def removeRequest(self):
        if str(self.guildId) in self.acc.Requests["SuzerainInvites"]:
            del self.acc.Requests["SuzerainInvites"][str(self.guildId)]
            self.I.WS.removeRequestsData(self.acc.GuildData.GuildAuid, {"requests.SuzerainInvites.%s" % self.guildId : str(self.guildId)}, self.onRemoveRequestsData)
        else:
            self.response["ec"] = EC.DEBUG_MESSAGE
            self.response["error"] = "GuildService.DeclineVassalAction: SuzerainInvite %s is absent!" % str(self.guildId)
            self.response["ok"] = 1
            self.fin()

    def onRemoveRequestsData(self, response):
        info("GuildService.DeclineVassalAction.onRemoveRequestsData response: %r " % response)
        if response:
            self.response["ok"] = 1
        else:
            self.response["ec"] = EC.DEBUG_MESSAGE
            self.response["error"] = "GuildService.DeclineVassalAction.onRemoveRequestsData: Unknown problems of suzerain's invites removing"
            self.response["ok"] = 0
        self.fin()
        return


class RemoveVassalAction(SubAction):
    action = "remove_vassal"

    """ Проверяем, можем ли убрать вассала и высылаем ему изменения, если что """
    @action_timing
    def onStart(self):
        info("GuildService: RemoveVassal")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("targetAuid") and self.checkValidBoolParam("notifyVassal"):
            if self.auid != CC.GUILD_NEUTRAL_AUID:
                self.acc = self.I.WS.getUserAcc(self.auid)
                if self.acc:
                    if self.targetAuid == CC.NPC_VASSAL_AUID:
                        self.onGMLockChecked({"ok": 1})
                    else:
                        self.I.WS.checkGMLock(self.targetAuid, self.onGMLockChecked)
                    return
                self.response["error"] = "GuildService: can not find acc by auid=%r" % self.auid
            # Сторонний запрос или логин через GMTools
            else:
                if self.checkValidIntParam("toGuildAuid"):
                    if self.toGuildAuid != CC.NPC_VASSAL_AUID:
                        self.acc = ClassDict(auid=CC.GUILD_NEUTRAL_AUID, GuildData=None, guildAuid=self.toGuildAuid)
                        self.I.WS.loadGuildData(self.acc, self.onDataLoaded)
                        return
                    else:
                        self.removeVassal()
                        return

        self.response["ok"] = 0
        self.fin()

    def onGMLockChecked(self, response):
        if response:
            if response.get("ok"):
                if self.acc.GuildData.GuildInfo.GMLockTime < int(time.time()):
                    self.removeVassal()
                else:
                    self.errorResponse(EC.GUILD_IS_LOCKED_BY_GM, "Guild %d is locked by GM" % self.acc.GuildData.GuildAuid)
                return
            self.errorResponse(response["ec"], response["error"])
        else:
            self.response["error"] = "Can't check GMLock for guild %d" % self.targetAuid

        self.response["ok"] = 0
        self.fin()

    def onDataLoaded(self, acc, errMessage=None):
        info("GuildService: RemoveVassalAction.onStart")
        if acc and errMessage is None:
            # Если это сторонний вызов, то на лок не проверяем
            self.removeVassal()
        else:
            info("GuildService: VassalLostNotifyAction.onDataLoaded bad response")
            self.response["ok"] = 0
            self.fin()

    def removeVassal(self):
        self.I.WS.resetPendingChanges(self.acc)
        self.acc.GuildData.write(self.acc.pending)
        self.acc.SiegeData.write(self.acc.pending)
        if self.I.WS.canInvite(self.acc):
            hasVassal = False
            for vassalId, vassal in self.acc.GuildData.GuildVassals.items():
                if vassal.ShortInfo.GuildAuid == self.targetAuid:
                    hasVassal = True
                    sGuildAuid = str(vassal.ShortInfo.GuildAuid)
                    #self.acc.GuildData.ExVassals[sGuildAuid] = int(time.time())

                    self.acc.GuildData.removeVassal(vassal)

                    # Если это не нпс, то обработаем его сюзерена и осады
                    if self.targetAuid != CC.NPC_VASSAL_AUID:
                        self.acc.GuildData.ExVassals[sGuildAuid] = int(time.time())
                        # Если этого вассала осаждали, автоматически выходим из боя
                        if self.acc.SiegeData.isTarget(self.targetAuid):
                            callback = functools.partial(self.onSiegeLeaveReply, acc=self.acc)
                            self.I.SIEGE.leaveSiege(self.acc.GuildData.GuildAuid, self.targetAuid, callback)

                        # Вассала кикнули, теперь надо ему об этом сообщить, если мы сами его кикнули
                        if self.notifyVassal:
                            args = dict(method="new_suzerain_notify", message={})
                            self.I.SEX.sendToGuildService(0, self.targetAuid, args, self.onNewSuzerainAdded)

                    # Посмотрим, не ждёт ли нас кто-нибудь
                    self.pendingSiege = self.acc.SiegeData.getPendingSiege(self.acc.GuildData.InitiatedSieges)
                    if self.pendingSiege:
                        self.I.SIEGE.winnerChoice(self.pendingSiege.Target.ShortInfo.GuildAuid, "accept", self.onPendingSiegesCheckReply)
                        return
                    break

            if not hasVassal:
                warn("Vassal %d was not found in guild %d", self.targetAuid, self.acc.GuildData.GuildAuid)

            changes = self.I.WS.pickPendingChanges(self.acc)
            self.I.WS.sendBroadCast(self.acc, changes, [], '')
            self.I.WS.saveGuildData(self.acc, None)
            if self.acc.auid != CC.GUILD_NEUTRAL_AUID:
                self.response["GuildData"] = changes.get("guild_data", [])
            self.response["ok"] = 1
            self.fin()
            return
        else:
            self.response["error"] = "RemoveVassal: can't remove vassal if member is not officer."
            self.response["ec"] = EC.GUILD_ONLY_OFFICER_CAN_OPERATE
            self.fin()

    def onNewSuzerainAdded(self, response):
        if response:
            isOk = response.get("ok") or 0
            if not isOk:
                err("New suzerain was not added for guild %d", self.targetAuid)

    def onPendingSiegesCheckReply(self, response):
        if response:
            isOk = response.get("ok") or 0
            if isOk:
                info("onPendingSiegesCheckReply: Ok:")
                self.vassalAuid = self.pendingSiege.Target.ShortInfo.GuildAuid
                self.I.DATA.find_one("guilds", "guilds", {"key": getMongoKeyAuid(self.vassalAuid)}, self.onVassalDataFound, params=None)
                return
            else:
                err("LeaveSiege: bad response from siege service")
                self.response["ok"] = 0
        self.fin()

    def onVassalDataFound(self, response):
        if response:
            try:
                data_json = response["r"]["data"]
                guildDict = json_loads(data_json)
            except:
                self.errorResponse(EC.SIEGE_NO_DATA_IN_DATABASE, "RemoveVassal: error in parsing guild_data for guildAuid %d" % self.vassalAuid)
                return

            self.I.WS.createVassal(self.acc.GuildData, guildDict)
            # Уберём инвайт от вассала, если он был
            if self.acc.Requests and "SuzerainInvites" in self.acc.Requests and str(self.vassalAuid) in self.acc.Requests["SuzerainInvites"]:
                del self.acc.Requests["SuzerainInvites"][str(self.vassalAuid)]
            self.I.WS.removeRequestsData(self.acc.GuildData.GuildAuid, {"requests.SuzerainInvites.%s" % str(self.vassalAuid): str(self.vassalAuid)})

            # Уберём осаду, в которой целью присутствовал новоприобретённый вассал и соберём данные для статистики
            deltaTime = int(time.time()) - self.pendingSiege.EndTime
            siegeId = self.pendingSiege.Uid
            self.acc.GuildData.removeSiege(siegeId)
            self.acc.SiegeData.removeSiege(siegeId)

            # Вассала взяли, теперь надо ему об этом сообщить
            args = dict(method="new_suzerain_notify", message={})
            callback = functools.partial(self.onTargetSuzerainUpdated, deltaTime=deltaTime, siegeId=siegeId)
            self.I.SEX.sendToGuildService(self.acc.GuildData.GuildAuid, self.vassalAuid, args, callback)
            # Посмотрим, что со старым сюзереном, расскажем ему, что вассала забрали, если что
            suzerainId = pathFind(guildDict, "GuildData/GuildSuzerain")
            shortInfoId = pathFind(guildDict, "GuildData/GuildMapEntityKeeper/Keeper/%s/GuildMapEntity/ShortInfo" % suzerainId, force_int_keys=False)
            oldSuzerainAuid = pathFind(guildDict, "GuildData/GuildShortInfoKeeper/Keeper/%s/GuildShortInfo/GuildAuid" % shortInfoId, force_int_keys=False)
            if oldSuzerainAuid and oldSuzerainAuid != -1:
                args = dict(method="remove_vassal", message={"auid": CC.GUILD_NEUTRAL_AUID,
                                                             "targetAuid": self.vassalAuid,
                                                             "notifyVassal": False})
                self.oldSuzerainAuid = oldSuzerainAuid
                self.I.SEX.sendToGuildService(self.vassalAuid, oldSuzerainAuid, args, self.onVassalRemoved)

            changes = self.I.WS.pickPendingChanges(self.acc)
            self.I.WS.sendBroadCast(self.acc, changes, self.acc.GuildData.getAllMembers(), '')
            self.I.WS.saveGuildData(self.acc, None)
        else:
            err("RemoveVassalAction: bad response from database")
            self.response["ok"] = 0
            self.fin()

    def onVassalRemoved(self, response):
        if response:
            isOk = response.get("ok") or 0
            if not isOk:
                err("Vassal %d was not removed from previous suzerain %d", self.vassalAuid, self.oldSuzerainAuid)

    @action_timing
    def onTargetSuzerainUpdated(self, data_reply, deltaTime=0, siegeId=0):
        self.I.STATS.addGuildInteraction(self.acc.GuildData.GuildAuid, self.vassalAuid,
                GuildInteractionType.Capture, siegeId, deltaTime)
        info("GuildService: add suzerain reply (value=%r)", data_reply)
        self.response["ok"] = 1
        self.fin()

    def onSiegeLeaveReply(self, siegeResponse, acc=None):
        if siegeResponse:
            info("onSiegeServiceReply response: %s" , siegeResponse)
            isOk = siegeResponse.get("ok") or 0
            if isOk and "siege" in siegeResponse:

                acc.SiegeData.removeSiege(siegeResponse["siege"])
                acc.GuildData.removeSiege(siegeResponse["siege"])

                changes = self.I.WS.pickPendingChanges(acc)
                self.I.WS.sendBroadCast(acc, changes, acc.GuildData.getAllMembers(), '')
                self.I.WS.saveGuildData(acc, None)
            else:
                err("RemoveVassal onSiegeLeaveReply: bad response from siege service")


class SendTributeAction(SubAction):
    action = "send_tribute"
    """ Отсылает дань сюзерену"""

    @action_timing
    def onStart(self):
        info("GuildService: SendTribute")
        if (self.checkValidIntParam("fromGuildAuid")
            and self.checkValidIntParam("toGuildAuid")
            and self.checkValidIntParam("tribute")):
            self.fakeAcc = ClassDict(auid=CC.GUILD_NEUTRAL_AUID, GuildData=None, guildAuid=self.toGuildAuid)
            self.I.WS.loadGuildData(self.fakeAcc, self.updateSuzerainData)
        else:
            self.fin()

    def updateSuzerainData(self, acc, errMessage=None):
        info("GuildService: SendTribute.updateSuzerainData")
        if acc and errMessage is None:
            self.I.WS.resetPendingChanges(self.fakeAcc)
            self.fakeAcc.GuildData.write(self.fakeAcc.pending)
            self.fakeAcc.GuildData.GuildInfo.CWPoints_Clan += self.tribute
            for vid, vassal in self.fakeAcc.GuildData.GuildVassals.iteritems():
                if vassal.ShortInfo.GuildAuid == self.fromGuildAuid:
                    vassal.DonationYesterday = vassal.DonationToday
                    vassal.DonationToday = self.tribute
                    break

            changes = self.I.WS.pickPendingChanges(self.fakeAcc)
            self.I.WS.sendBroadCast(self.fakeAcc, changes, [], '')
            self.I.WS.saveGuildData(self.fakeAcc, self.onSave)
            return
        else:
            err(errMessage)

        self.fin()

    def onSave(self, data_reply):
        info("GuildService: persistent reply (value=%r)", data_reply.get("r") if data_reply else "empty reply from mongo db")
        self.response["ok"] = 1
        self.fin()


class GetGuildDataForMapAction(SubAction):
    action = "get_guilddata_for_map"
    """ Получаем данные для карты клана по его guildAuid"""

    @action_timing
    def onStart(self):
        info("GuildService: GetGuildDataForMapAction")
        if (self.checkValidIntParam("auid") and self.checkValidIntParam("guildAuid")):
            self.I.WS.loadGuildDataByGuildAuid(self.guildAuid, self.updateMapData )
        else:
            warn("GetGuildDataForMapAction.updateMapData: bad params ! ")

    def updateMapData(self, response):
        info("GetGuildDataForMapAction.updateMapData response:  %r" % response)
        if response:
            try:
                data_json = response["r"]["data"] or '{"GuildData":{}}'
            except:
                data_json = '{"GuildData":{}}'

            gdata = json_loads(data_json)

            if not gdata:
                # игнорируем плохой клан, но не ругаемся на него
                warn("GetGuildDataForMapAction.updateMapData: can't load guild data! ")
                self.response["ok"] = 1
                self.fin()
                return

            self.gmapdata = GuildMapData()
            self.gmapdata.init(None)
            if self.fillSVMapData(self.gmapdata, gdata):
                info("After GetGuildDataForMapAction.fillSVMapData: %r " % self.gmapdata)
                self.I.SIEGE.getSieges(self.guildAuid, self.onLoadSieges)
        else:
            err("GetGuildDataForMapAction.updateMapData: bad response! ")
            self.fin()

    def fillSVMapData(self, gmapdata, gdata):

        gi = pathFind(gdata, "GuildData/GuildInfo/GuildInfo")

        if not gi:
            # игнорируем плохой клан, но не ругаемся на него
            warn("GetGuildDataForMapAction.fillSVMapData: can't parse guild info! ")
            self.response["ok"] = 1
            self.fin()
            return False

        info("GetGuildDataForMapAction.fillSVMapData GuildInfo: %r ", gi)
        gmapdata.ShortInfo, _id = gmapdata.newGuildShortInfo()
        self.I.WS.fillShortInfo(gmapdata.ShortInfo, pathFind(gdata, "GuildData/GuildAuid"), gi.get("ShortName", ""), gi.get("FullName", ""),
                                self.I.SD.getGuildLevel(pathFind(gdata, "GuildData/GuildLevelInfo/GuildLevelInfo/Experience") or 0),
                                pathFind(gdata, "GuildData/RatingInfo/RatingInfo/Rating"), gi.get("Place", ""),
                                GuildWarsData.GetRatingPositionChange(gi.get("PlaceChange" ,0)), 0,
                                len(pathFind(gdata, "GuildData/Members/Set")), gi.get("IconChangesCount", 0))
        gmapdata.HasUltimateShop = gi.get("HasUltimateShop","")


        gmapdata.GuildMapSuzerain, _id = gmapdata.newGuildShortInfo()
        suzerainId = pathFind(gdata, "GuildData/GuildSuzerain")
        shortInfoId = pathFind(gdata, "GuildData/GuildMapEntityKeeper/Keeper/%s/GuildMapEntity/ShortInfo" % suzerainId, force_int_keys=False)
        suzerain = pathFind(gdata, "GuildData/GuildShortInfoKeeper/Keeper/%s/GuildShortInfo" % shortInfoId, force_int_keys=False)
        if suzerain:
            self.I.WS.fillShortInfo(gmapdata.GuildMapSuzerain, suzerain.get("GuildAuid", 0), suzerain.get("GuildShortName", ""),
                                    suzerain.get("GuildFullName", ""), suzerain.get("Level", 0), suzerain.get("Rating", 0),
                                    suzerain.get("Place", 0), suzerain.get("RatingPositionChange", 0), suzerain.get("ShopLevel", 0),
                                    suzerain.get("MembersCount", 0), suzerain.get("IconChangesCount", 0))

        shopRating = gmapdata.ShortInfo.Rating
        if gmapdata.GuildMapSuzerain.GuildAuid:
            shopRating = gmapdata.GuildMapSuzerain.Rating
        gmapdata.ShortInfo.ShopLevel = self.I.SD.getGuildShopLevel(shopRating, gmapdata.HasUltimateShop)


        set = pathFind(gdata, "GuildData/GuildVassals/Set")
        for vid in set.keys():
            shortInfoId = pathFind(gdata, "GuildData/GuildMapEntityKeeper/Keeper/%d/GuildMapEntity/ShortInfo" % toint(vid), force_int_keys=False)
            vassal = pathFind(gdata, "GuildData/GuildShortInfoKeeper/Keeper/%d/GuildShortInfo" % toint(shortInfoId), force_int_keys=False)
            if vassal:
                v, _id = gmapdata.newGuildShortInfo()
                self.I.WS.fillShortInfo(v, vassal.get("GuildAuid", 0), vassal.get("GuildShortName", ""),
                                        vassal.get("GuildFullName", ""), vassal.get("Level", 0),
                                        vassal.get("Rating", 0), vassal.get("Place", 0),
                                        vassal.get("RatingPositionChange", 0), vassal.get("ShopLevel", 0),
                                        vassal.get("MembersCount", 0), vassal.get("IconChangesCount", 0))
                gmapdata.GuildMapVassals.add(v)

        return True

    def onLoadSieges(self, response):
        info("GetGuildDataForMapAction.onLoadSieges response: %r" % response)
        changes = "{}"
        if response:
            self.updateSieges(self.gmapdata, response)
            return

        changes = [MakeModelChangeString("init_guildmap", "/", "init",  self.gmapdata.generateJsonDict())]
        self.response["GuildMapData"] = changes
        self.response["ok"] = 1
        self.fin()

    def updateSieges(self, gmapdata, response ):
        participants = []
        for siegeInfo in response:
            siege, siegeId = gmapdata.newSiegeInfo()
            siege.EndTime = siegeInfo["end_time"]
            siege.IsLocked = siegeInfo["status"] == 'locked'
            siege.Id = siegeInfo["_id"]

            for participant in siegeInfo["participants"]:
                attacker, attackerId = gmapdata.newSiegeGuildInfo()
                attacker.ShortInfo, _id = gmapdata.newGuildShortInfo()
                attacker.ShortInfo.GuildAuid = participant["id"]
                participants.append(attacker.ShortInfo.GuildAuid)
                attacker.SiegePoints = participant["score"]
                siege.Participants.add(attacker)

            siege.Target, targetId = gmapdata.newSiegeGuildInfo()
            siege.Target.ShortInfo, _id = gmapdata.newGuildShortInfo()
            siege.Target.ShortInfo.GuildAuid = siegeInfo["target"]
            if siege.Target.ShortInfo.GuildAuid not in participants:
                participants.append(siege.Target.ShortInfo.GuildAuid)
            gmapdata.Sieges.add(siege)

        self.I.EXPORT.getGuildsInfo(participants, self.onSiegeDataFromSQL)

    def onSiegeDataFromSQL(self, reply):
        r = reply["r"]
        if r and len(r):
            # Обновим заодно и все старые записи, если у этих кланов что-то изменилось
            for guildInfoResponse in r:
                for guildInfoId, guildInfo in self.gmapdata.SiegeGuildInfoKeeper.iteritems():
                    if guildInfo.ShortInfo.GuildAuid == guildInfoResponse.guild_id:
                        self.I.WS.fillShortInfo(guildInfo.ShortInfo, guildInfoResponse.guild_id,
                                                guildInfoResponse.guild_short_name,
                                                guildInfoResponse.guild_name,
                                                guildInfoResponse.guild_level,
                                                guildInfoResponse.rating,
                                                guildInfoResponse.position,
                                                GuildWarsData.GetRatingPositionChange(guildInfoResponse.position_change),
                                                guildInfoResponse.shop_level,
                                                guildInfoResponse.num_members,
                                                guildInfoResponse.icon_revision)

        changes = [MakeModelChangeString("init_guildmap", "/", "init",  self.gmapdata.generateJsonDict())]
        self.response["GuildMapData"] = changes
        self.response["ok"] = 1
        self.fin()


class NewSuzerainNotify(SubAction):
    action = "new_suzerain_notify"
    """ сообщаем вассалу о том что у него появился новый сюзерен или обновились данные текущего сюзерена """

    @action_timing
    def onStart(self):
        info("GuildService: NewSuzerainNotify")
        if self.checkValidIntParam("fromGuildAuid") and self.checkValidIntParam("toGuildAuid"):
            self.fakeAcc = ClassDict(auid=CC.GUILD_NEUTRAL_AUID, GuildData=None, guildAuid=self.toGuildAuid)
            self.I.WS.loadGuildData(self.fakeAcc, self.onLoad)
        else:
            self.fin()

    def onLoad(self, acc, errMessage=None):
        info("GuildService: NewSuzerainNotify.updateSuzerainData: from %s, to %s", self.fromGuildAuid, self.toGuildAuid)
        if acc and errMessage is None:
            if self.fromGuildAuid == 0:
                # Нас кинули, обнулим-ка сюзерена..
                self.I.WS.resetPendingChanges(self.fakeAcc)
                self.fakeAcc.GuildData.write(self.fakeAcc.pending)



                if not self.getBoolParam("dontUpdateTime", False):
                    self.fakeAcc.GuildData.GuildSuzerain.JoinTime = int(time.time())
                    willHaveUltimateShop = self.fakeAcc.GuildData.RatingInfo.Rating >= self.I.SD.data["ClanWarsData"]["shopAncientRating"]
                    self.I.WS.checkGuildShopOnNewSuzerain(self.fakeAcc.GuildData, self.fakeAcc.GuildData.RatingInfo.Rating, willHaveUltimateShop)

                self.I.WS.fillSuzerain(self.fakeAcc.GuildData, 0, "", "", 0, 0, 0, 0, 0, 0, 0)

                changes = self.I.WS.pickPendingChanges(self.fakeAcc)
                self.I.WS.sendBroadCast(self.fakeAcc, changes, [], '')
                self.I.WS.saveGuildData(self.fakeAcc, self.onSave)
                return
            else:
                self.I.WS.loadGuildDataByGuildAuid(self.fromGuildAuid, self.updateSuzerainData)
                return
        else:
            err("err: %r" % errMessage)
            info("GuildService: NewSuzerainNotify.onLoad bad response")
        self.fin()

    def updateSuzerainData(self, response):
        info("GuildService: NewSuzerainNotify.updateSuzerainData response: %r" , response)
        if response:
            try:
                data_json = response["r"]["data"] or '{"GuildData":{}}'
            except:
                data_json = '{"GuildData":{}}'

            gdata = json_loads(data_json)

            self.I.WS.resetPendingChanges(self.fakeAcc)
            self.fakeAcc.GuildData.write(self.fakeAcc.pending)

            self.I.WS.checkGuildShopOnNewSuzerain(self.fakeAcc.GuildData, pathFind(gdata, "GuildData/RatingInfo/RatingInfo/Rating"), False)

            self.I.WS.updateSuzerainFromDict(self.fakeAcc.GuildData, gdata)



            self.fakeAcc.GuildData.GuildSuzerain.DonationYesterday = 0
            self.fakeAcc.GuildData.DonationToday = 0

            if not self.getBoolParam("dontUpdateTime"):
                self.fakeAcc.GuildData.GuildSuzerain.JoinTime = int(time.time())
            # Проверим, не надо ли дать нашей гильдии доступ к убермагазину
            self.fakeAcc.GuildData.checkUltimateShop(self.I.SD)

            changes = self.I.WS.pickPendingChanges(self.fakeAcc)
            self.I.WS.sendBroadCast(self.fakeAcc, changes, [], '')
            self.I.WS.saveGuildData(self.fakeAcc, self.onSave)
            return

        self.fin()

    def onSave(self, data_reply):
        info("GuildService: persistent reply (value=%r)", data_reply.get("r") if data_reply else "empty reply from mongo db")
        self.response["ok"] = 1
        self.fin()


class HideRecommendedVassalAction(SubAction):
    action = "hide_recommended_vassal"
    """ убираем вассала из списка рекомендованных"""

    @action_timing
    def onStart(self):
        info("GuildService: HideRecommendedVassalAction")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("guildAuid"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                acc.GuildData.write(acc.pending)

                self.I.WS.removeGuildFromRecommendedVassal(acc, self.guildAuid)
                acc.GuildData.GuildsRemovedFromSearch[self.guildAuid] = int(time.time())

                changes = self.I.WS.pickPendingChanges(acc)

                self.I.WS.sendBroadCast(acc, changes, [], '')
                self.I.WS.saveGuildData(acc, None)

                self.response["GuildData"] = changes.get("guild_data", [])
                self.response["ok"] = 1
            else:
                self.response["error"] = "GuildService: can not find acc by auid=%r" % self.auid
                self.response["ok"] = 0

        self.fin()


class UpdateVassalInfoAction(SubAction):
    action = "update_vassal_info"
    """ Обновление информации по вассалу в данных сюзерена """

    @action_timing
    def onStart(self):
        info("GuildService: UpdateVassalInfoAction")
        if self.checkValidIntParam("toGuildAuid") and self.checkValidIntParam("targetAuid"):
            self.fakeAcc = ClassDict(auid=CC.GUILD_NEUTRAL_AUID, GuildData=None, guildAuid=self.toGuildAuid)
            self.I.WS.loadGuildData(self.fakeAcc, self.onLoad)
        else:
            self.fin()

    def onLoad(self, acc, errMessage=None):
        info("GuildService: UpdateVassalInfoAction.onLoad")
        if acc and errMessage is None:
            self.I.WS.loadGuildDataByGuildAuid(self.targetAuid, self.onLoadVassalGuild)
        else:
            info("GuildService: UpdateVassalInfoAction.onLoad bad response %r", errMessage)
            self.fin()

    def onLoadVassalGuild(self, response):
        info("GuildService: UpdateVassalInfoAction.onLoadVassalGuild")
        if response:
            try:
                data_json = response["r"]["data"] or '{"GuildData":{}}'
                vassDict = json_loads(data_json)
            except:
                err("No data for vassal %d found", self.targetAuid)
                self.fin()
                return

            if vassDict and vassDict.get("GuildData"):
                self.I.WS.resetPendingChanges(self.fakeAcc)
                self.fakeAcc.GuildData.write(self.fakeAcc.pending)

                for vassalId, vassal in self.fakeAcc.GuildData.GuildVassals.iteritems():
                    debug("GuildService: UpdateVassalInfoAction.onLoadVassalGuild ShortInfo dump  %r", vassal.ShortInfo)
                    if vassal.ShortInfo and vassal.ShortInfo.get() and vassal.ShortInfo.GuildAuid == self.targetAuid:
                        self.I.WS.fillVassal(vassal, vassDict, self.I.SD.getGuildShopLevel(self.fakeAcc.GuildData.RatingInfo.Rating, False))
                        break

                changes = self.I.WS.pickPendingChanges(self.fakeAcc)
                self.I.WS.sendBroadCast(self.fakeAcc, changes, [], '')
                self.I.WS.saveGuildData(self.fakeAcc, None)
                self.response["ok"] = 1
            else:
                self.response["error"] = "GuildService: can not find acc by auid=%r" % self.auid
        else:
            warn("UpdateVassalInfoAction: Bad response params")
        self.fin()


# ---------------------- SIEGE ACTIONS --------------------- #

class StartSiegeAction( SubAction ):
    action = "start_siege"

    """ Проверяем, можем ли мы начать осаду, и пробрасываем запрос на siege service """
    @action_timing
    def onStart(self):
        info("GuildService: StartSiege")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("targetAuid") and (self.getBoolParam("join") is not None):
            self.join = self.getBoolParam("join")
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                # Проверим, не иссяк ли лимит одновременных осад и счётчик начатых осад, чтобы не было race conditions
                if len(acc.GuildData.InitiatedSieges) < self.I.Config.getMainConfig().SiegeSettings.MAX_ACTIVE_SIEGES:
                    if not acc.GuildData.hasVassal(self.targetAuid):
                        if self.checkAttackPermissions(acc):
                            if acc.GuildData.GuildInfo.GMLockTime < int(time.time()):
                                self.I.WS.resetPendingChanges(acc)
                                acc.GuildData.write(acc.pending)
                                acc.SiegeData.write(acc.pending)
                                member = acc.GuildData.findMemberByAuid(self.auid)
                                if member.IsOfficer:
                                    self.initiatedSiege, initiatedSiegeId = acc.GuildData.newInitiatedSiege()
                                    acc.GuildData.InitiatedSieges.add(self.initiatedSiege)
                                    callback = functools.partial(self.onRatingInfo, acc=acc)
                                    self.I.DATA.find_one("guilds", "guilds", {"key": getMongoKeyAuid(self.targetAuid)}, callback, params=None)
                                    return
                                else:
                                    self.response["error"] = "StartSiege: can't start siege if member is not officer."
                                    self.response["ec"] = EC.GUILD_ONLY_OFFICER_CAN_OPERATE
                            else:
                                self.response["error"] = "StartSiege: can't start siege, your guild is locked by GM."
                                self.response["ec"] = EC.GUILD_IS_LOCKED_BY_GM
                    else:
                        self.response["error"] = "StartSiege: can't siege your own vassal."
                        self.response["ec"] = EC.CANT_START_SIEGE_FOR_VASSAL_OR_SELF
                else:
                    self.response["error"] = "StartSiege: active sieges limit exceeded."
                    self.response["ec"] = EC.GUILD_HAVE_ACTIVE_SIEGE
            else:
                self.response["error"] = "GuildService: can not find acc by auid=%r" % self.auid

        self.response["ok"] = 0
        self.fin()

    def checkAttackPermissions(self, acc):
        # Не даём повторно инициировать захват про только что проигранной осаде
        if str(self.targetAuid) in acc.GuildData.LostSiegesGuilds:
            if (acc.GuildData.LostSiegesGuilds[str(self.targetAuid)] + self.I.Config.getMainConfig().SiegeSettings.TIMEOUT_FOR_CAPTURE_AFTER_LOSS) > int(time.time()):
                self.response["error"] = "StartSiege: can't start siege, guild have recently lost siege for this target."
                self.response["ec"] = EC.GUILD_CANT_SIEGE_RECENTLY_LOST_GUILD
                return False
            else:
                # Если время уже прошло, уберём гильдию, чтобы не мешалась
                del acc.GuildData.LostSiegesGuilds[str(self.targetAuid)]
        if str(self.targetAuid) in acc.GuildData.ExVassals:
            if (acc.GuildData.ExVassals[str(self.targetAuid)] + self.I.Config.getMainConfig().SiegeSettings.SIEGE_DURATION) > int(time.time()):
                self.response["error"] = "StartSiege: can't start siege for recently lost vassal."
                self.response["ec"] = EC.GUILD_CANT_SIEGE_EX_VASSAL
                return False
        return True

    def onRatingInfo(self, response, acc=None):
        if response:
            try:
                data_json = response["r"]["data"]
                guildDict = json_loads(data_json)
            except:
                acc.GuildData.InitiatedSieges.remove(self.initiatedSiege)
                self.errorResponse(EC.SIEGE_NO_DATA_IN_DATABASE, "StartSiege: error in parsing guild_data for guildAuid %d" % self.targetAuid)
                return

            if guildDict is not None:
                if pathFind(guildDict, "GuildData/GuildInfo/GuildInfo/GMLockTime") < int(time.time()):
                    targetRating = guildDict["GuildData"]["RatingInfo"]["RatingInfo"]["Rating"]
                    targetSuzerainEntityId = guildDict["GuildData"]["GuildSuzerain"]
                    targetSuzerainId = guildDict["GuildData"]["GuildMapEntityKeeper"]["Keeper"][str(targetSuzerainEntityId)]["GuildMapEntity"]["ShortInfo"]
                    targetSuzerain = guildDict["GuildData"]["GuildShortInfoKeeper"]["Keeper"][str(targetSuzerainId)]["GuildShortInfo"]["GuildAuid"]
                    targetSuzerainRating = guildDict["GuildData"]["GuildShortInfoKeeper"]["Keeper"][str(targetSuzerainId)]["GuildShortInfo"]["Rating"]

                    self.priceToStart = acc.GuildData.getSiegeStartPrice(self.targetAuid,
                                            targetSuzerainRating if acc.GuildData.GuildAuid == self.targetAuid else targetRating,
                                            self.I.Config.getMainConfig().SiegeSettings)
                    if acc.GuildData.GuildInfo.CWPoints_Clan >= self.priceToStart:
                        callback = functools.partial(self.onSiegeServiceReply, acc=acc)
                        if self.join:
                            self.I.SIEGE.joinSiege(acc.GuildData.GuildAuid, acc.GuildData.RatingInfo.Rating, self.targetAuid, self.priceToStart, callback)
                        else:
                            self.I.SIEGE.startSiege((acc.GuildData.GuildAuid, acc.GuildData.RatingInfo.Rating),
                                                (self.targetAuid, targetRating), (targetSuzerain, targetSuzerainRating), self.priceToStart, callback)
                    else:
                        acc.GuildData.InitiatedSieges.remove(self.initiatedSiege)
                        self.errorResponse(EC.NOT_ENOUGH_RESOURCES, "StartSiege: not enough guild points")
                else:
                    acc.GuildData.InitiatedSieges.remove(self.initiatedSiege)
                    self.errorResponse(EC.GUILD_IS_LOCKED_BY_GM, "Guild %d is locked by GM" % self.targetAuid)
        else:
            acc.GuildData.InitiatedSieges.remove(self.initiatedSiege)
            self.errorResponse(EC.SIEGE_NO_DATA_IN_DATABASE, "StartSiege: can not find guild rating in Mongo for guildAuid %d" % self.targetAuid)


    def onSiegeServiceReply(self, siegeResponse, acc=None):
        if siegeResponse:
            info("onSiegeServiceReply response: %s" % siegeResponse)
            if siegeResponse.get("ok"):
                guildAuids = []
                try:
                    # Добавим данные по новой осаде в SiegeData
                    guildAuids = acc.SiegeData.update([siegeResponse["siege"]])
                except:
                    catch()
                    self.response["ok"] = 0
                    self.fin()
                    return
                acc.GuildData.GuildInfo.CWPoints_Clan -= self.priceToStart
                acc.GuildData.addActiveSiege(siegeResponse["siege"]["_id"])

                if siegeResponse["siege"]["target"] == acc.GuildData.GuildAuid:
                    acc.GuildData.SiegeForMyGuildEndTime = siegeResponse["siege"]['end_time']

                self.initiatedSiege.SiegeId = siegeResponse["siege"]["_id"]
                self.initiatedSiege.StartPrice = self.priceToStart
                if guildAuids:
                    callback = functools.partial(self.onSiegeDataFromSQL, acc=acc)
                    self.I.EXPORT.getGuildsInfo(guildAuids, callback)
            else:
                acc.GuildData.InitiatedSieges.remove(self.initiatedSiege)
                self.response["error"] = siegeResponse.get('error') or "StartSiege: bad response from siege service"
                if "ec" in siegeResponse:
                    self.response["ec"] = siegeResponse["ec"]
                self.response["ok"] = 0
                self.fin()

    @action_timing
    def onSiegeDataFromSQL(self, reply, acc=None):
        r = reply["r"]
        if r and len(r):
            # Обновим заодно и все старые записи, если у этих кланов что-то изменилось
            for guildInfo in r:
                acc.SiegeData.updateGuildInfoFromSQL(guildInfo)
            changes = self.I.WS.pickPendingChanges(acc)
            self.I.WS.sendBroadCast(acc, changes, [], '')
            self.I.WS.saveGuildData(acc, None)
            self.response["GuildData"] = changes.get("guild_data", [])
            self.response["SiegeData"] = changes.get("siege_data", [])
            self.response["ok"] = 1
        self.fin()


class LeaveSiegeAction( SubAction ):
    action = "leave_siege"

    """ Проверяем, можем ли мы ливнуть из осады, и пробрасываем запрос на siege service """
    @action_timing
    def onStart(self):
        info("GuildService: LeaveSiege")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("targetAuid"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                member = acc.GuildData.findMemberByAuid(self.auid)
                if acc.GuildData.GuildInfo.GMLockTime < int(time.time()):
                    if member.IsOfficer:
                        callback = functools.partial(self.onSiegeServiceReply, acc=acc)
                        self.I.SIEGE.leaveSiege(acc.GuildData.GuildAuid, self.targetAuid, callback)
                        return
                    else:
                        self.response["error"] = "LeaveSiege: can't leave siege if member is not officer."
                        self.response["ec"] = EC.GUILD_ONLY_OFFICER_CAN_OPERATE
                else:
                    self.response["error"] = "LeaveSiege: can't leave siege, guild %d is locked by GM." % acc.GuildData.GuildAuid
                    self.response["ec"] = EC.GUILD_IS_LOCKED_BY_GM
            else:
                self.response["error"] = "GuildService: can not find acc by auid=%r" % self.auid

        self.response["ok"] = 0
        self.fin()

    @action_timing
    def onSiegeServiceReply(self, siegeResponse, acc=None):
        if siegeResponse:
            info("onSiegeServiceReply response: %s" % siegeResponse)
            isOk = siegeResponse.get("ok") or 0
            if isOk and "siege" in siegeResponse:
                self.I.WS.resetPendingChanges(acc)
                acc.GuildData.write(acc.pending)
                acc.SiegeData.write(acc.pending)
                siege = acc.SiegeData.getSiegeById(siegeResponse["siege"])
                # Если клан не был целью осады, то можно выйти безболезненно
                # В противном случае удаление осады будут делать другие методы
                if siege and siege.Target.ShortInfo.GuildAuid != acc.GuildData.GuildAuid:
                    acc.GuildData.removeSiege(siegeResponse["siege"])
                    acc.SiegeData.removeSiege(siegeResponse["siege"])
                    acc.GuildData.LostSiegesGuilds[str(self.targetAuid)] = int(time.time())

                changes = self.I.WS.pickPendingChanges(acc)
                self.I.WS.sendBroadCast(acc, changes, [], '')
                self.I.WS.saveGuildData(acc, None)
                self.response["GuildData"] = changes.get("guild_data", [])
                self.response["SiegeData"] = changes.get("siege_data", [])
                self.response["ok"] = 1
            else:
                self.response["error"] = "StartSiege: bad response from siege service"
                if "ec" in siegeResponse:
                    self.response["ec"] = siegeResponse["ec"]
                self.response["ok"] = 0
        self.fin()


class UpdateSiegeAction( SubAction ):
    action = "update_siege"

    """ Форвардим изменения, приходящие от siege_service """
    @action_timing
    def onStart(self):
        if self.checkValidIntParam("guildAuid"):
            info("GuildService: UpdateSiege for %s", self.guildAuid)
            acc = ClassDict(auid=CC.GUILD_NEUTRAL_AUID, GuildData=None, SiegeData=None, guildAuid=self.guildAuid)
            self.I.WS.loadGuildData(acc, self.onGuildDataLoaded)
        else:
            warn("GuildService: UpdateSiege - no guildAuid! Arguments: %r", self.arguments)
            self.fin()

    def onGuildDataLoaded(self, acc, errMessage = None):
        if acc and errMessage is None:
            info("GuildService: UpdateSiege for %s body: %r", self.guildAuid, self.request.request.body)
            self.seageInfo = json_loads(self.request.request.body)
            siegeUpdateDict = self.seageInfo["siegeInfo"]

            self.I.WS.resetPendingChanges(acc)
            acc.GuildData.write(acc.pending)
            acc.SiegeData.write(acc.pending)
            newSieges = []
            for siegeUpdate in siegeUpdateDict:
                try:
                    # Кто-то из участников покинул осаду
                    if siegeUpdate["cmd"] == "leave":
                        acc.SiegeData.removeParticipant(siegeUpdate["_id"], siegeUpdate["guildAuid"])
                    # Убрать осаду из активных (кончилась или все отказались)
                    elif siegeUpdate["cmd"] == "remove":
                        siege = acc.SiegeData.getSiegeById(siegeUpdate["_id"])
                        if siege:
                            if siege.Target.ShortInfo.GuildAuid == acc.GuildData.GuildAuid:
                                acc.GuildData.SiegeForMyGuildEndTime = 0
                                acc.GuildData.LockedByOtherGuild = False
                            else:
                                # Если мы нападали, но не выиграли, надо запомнить эту гильдию
                                for siegeId, se in acc.GuildData.InitiatedSieges.iteritems():
                                    if se.SiegeId == siegeUpdate["_id"]:
                                        acc.GuildData.LostSiegesGuilds[str(siege.Target.ShortInfo.GuildAuid)] = int(time.time())
                        acc.SiegeData.removeSiege(siegeUpdate["_id"])
                        acc.GuildData.removeSiege(siegeUpdate["_id"])
                    # Убрать осаду из активных (клан распустился)
                    elif siegeUpdate["cmd"] == "destroy":
                        siege = acc.SiegeData.getSiegeById(siegeUpdate["_id"])
                        if siege and siege.Target.ShortInfo.GuildAuid == acc.GuildData.GuildAuid:
                            acc.GuildData.SiegeForMyGuildEndTime = 0
                            acc.GuildData.LockedByOtherGuild = False
                        for siegeId, se in acc.GuildData.InitiatedSieges.iteritems():
                            if se.SiegeId == siegeUpdate["_id"]:
                                acc.GuildData.GuildInfo.CWPoints_Clan += se.StartPrice
                                self.I.STATS.addGuildPointsChange(acc.GuildData.GuildAuid, 0,
                                                                  "GMGuildStopSiege", 0, 0,
                                                                  se.StartPrice, acc.GuildData.GuildInfo.CWPoints_Clan)
                        acc.SiegeData.removeSiege(siegeUpdate["_id"])
                        acc.GuildData.removeSiege(siegeUpdate["_id"])
                    # Изменились очки одного из участников
                    elif siegeUpdate["cmd"] == "score":
                        acc.SiegeData.updateScore(siegeUpdate["_id"], siegeUpdate["guildAuid"], siegeUpdate["score"])
                    # К осаде присоединился новый участник
                    elif siegeUpdate["cmd"] == "join":
                        acc.SiegeData.addParticipant(siegeUpdate["_id"], siegeUpdate["guildAuid"])
                        newSieges.append(siegeUpdate["guildAuid"])
                    # Король Артур, на нас напали!!!
                    elif siegeUpdate["cmd"] == "start":
                        participants = acc.SiegeData.update([siegeUpdate["siege"]])
                        for participant in participants:
                            newSieges.append(participant)
                        acc.GuildData.addActiveSiege(siegeUpdate["siege"]["_id"])
                        if siegeUpdate["siege"]["target"] == acc.GuildData.GuildAuid:
                            acc.GuildData.SiegeForMyGuildEndTime = siegeUpdate["siege"]["end_time"]
                    elif siegeUpdate["cmd"] == "time":
                        siege = acc.SiegeData.getSiegeById(siegeUpdate["_id"])
                        if siege and siege.Target.ShortInfo.GuildAuid == acc.GuildData.GuildAuid:
                            acc.GuildData.SiegeForMyGuildEndTime = siegeUpdate["end_time"]
                        for siegeId, se in acc.GuildData.InitiatedSieges.iteritems():
                            if se.SiegeId == siegeUpdate["_id"]:
                                se.EndTime = siegeUpdate["end_time"]
                    # Осада заблокирована, ожидаем решения победителя
                    elif siegeUpdate["cmd"] == "lock":
                        siege = acc.SiegeData.getSiegeById(siegeUpdate["_id"])
                        if siege:
                            siege.IsLocked = True
                            siege.EndTime = siegeUpdate["end_time"]
                        if siege and siege.Target.ShortInfo.GuildAuid == acc.GuildData.GuildAuid:
                            acc.GuildData.LockedByOtherGuild = True
                            acc.GuildData.SiegeForMyGuildEndTime = siegeUpdate["end_time"]
                    else:
                        err("Unknown command from siege service: %s", siegeUpdate["cmd"])
                except Exception:
                    catch()
                    err("UpdateSiegeAction: Unknown error !")
            if newSieges:
                callback = functools.partial(self.onSiegeDataFromSQL, guilds=newSieges, acc=acc)
                self.I.EXPORT.getGuildsInfo(newSieges, callback)
                return
            changes = self.I.WS.pickPendingChanges(acc)
            self.I.WS.sendBroadCast(acc, changes, [], '')
            self.I.WS.saveGuildData(acc, None)
            self.response["ok"] = 1
            self.fin()
            return
        else:
            self.response["error"] = "GuildService: can not find active acc by guildAuid=%r" % self.guildAuid
        self.response["ok"] = 0
        self.fin()


    @action_timing
    def onSiegeDataFromSQL(self, reply, guilds=None, acc=None):
        r = reply["r"]
        if r and len(r):
            # Обновим заодно и все старые записи, если у этих кланов что-то изменилось
            for guildInfo in r:
                acc.SiegeData.updateGuildInfoFromSQL(guildInfo)
        else:
            warn("UpdateSiegeAction.onSiegeDataFromSQL: empty reply (%s) for guilds %r", r, guilds)

        changes = self.I.WS.pickPendingChanges(acc)
        self.I.WS.sendBroadCast(acc, changes, [], '')
        self.I.WS.saveGuildData(acc, None)
        self.response["ok"] = 1
        self.fin()


class WinSiegeAction(SubAction):
    action = "win_siege"

    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: WinSiegeAction")
        if self.checkValidIntParam("guildAuid") and self.checkValidIntParam("siegeId"):
            self.fakeAcc = ClassDict(auid=CC.GUILD_NEUTRAL_AUID, GuildData=None, SiegeData=None, guildAuid=self.guildAuid)
            self.I.WS.loadGuildData(self.fakeAcc, self.addNewVassal)
        else:
            self.fin()

    def addNewVassal(self, acc, errMessage=None):
        # acc here is self.fakeAcc
        info("GuildService: WinSiegeAction loadGuildData callback call guildAuid: %s", self.guildAuid)
        if errMessage is not None:
            self.response["ok"] = 0
            self.response["error"] = errMessage
            self.fin()
            return

        self.currentSiege = acc.SiegeData.getSiegeById(self.siegeId)
        if self.currentSiege:
            self.vassalAuid = self.currentSiege.Target.ShortInfo.GuildAuid
            if acc.guildAuid == self.vassalAuid:
                # Мы отстояли себя, в этом случае ремувать других вассалов не надо
                self.processLiberation()
                return
            else:
                if len(acc.GuildData.GuildVassals) < self.I.Config.getMainConfig().GUILD_MAX_VASSAL_SIZE:
                    self.I.DATA.find_one("guilds", "guilds", {"key": getMongoKeyAuid(self.vassalAuid)}, self.onVassalInfoFound, params=None)
                    return
                else:
                    self.I.WS.resetPendingChanges(acc)
                    acc.SiegeData.write(acc.pending)
                    acc.GuildData.write(acc.pending)
                    acc.SiegeData.lockSiegeByTargetId(self.vassalAuid)

                    #поищем есть ли у нас такой рекомендованный вассал
                    isRVassal = not any(self.vassalAuid==v.ShortInfo.GuildAuid
                                        for k,v in self.fakeAcc.GuildData.RecommendedVassalKeeper.iteritems()
                                        if v and v.ShortInfo.get())
                    # список рекомендованных вассалов не полон и мы не удаляли сегодня этого вассала с карты
                    if (len(acc.GuildData.RecommendedForMapVassals) < self.I.Config.getMainConfig().GUILD_MAX_RECOMMENDED_VASSAL_SIZE
                        and self.vassalAuid not in acc.GuildData.GuildsRemovedFromSearch and isRVassal):
                            self.I.WS.loadGuildDataByGuildAuid(self.vassalAuid, self.onAddRecomendedVassal)
                            return

                    else:
                        changes = self.I.WS.pickPendingChanges(acc)
                        self.I.WS.sendBroadCast(acc, changes, acc.GuildData.getAllMembers(), '')
                        # Вассалы переполнены, известим об этом сервис осад
                        self.response["lock_siege"] = 1
                        self.response["ok"] = 1
        else:
            self.response["lock_siege"] = 1
            self.response["error"] = "No siege data for siege with id %d" % self.siegeId
            self.response["ok"] = 0
        self.fin()

    def onAddRecomendedVassal(self, response):
        info("WinSiegeAction.onAddRecomendedVassal reponse: %r" % response)
        if response:
            try:
                data_json = response["r"]["data"] or '{"GuildData":{}}'
            except:
                data_json = '{"GuildData":{}}'
            vass = json_loads(data_json)
            if vass and vass.get("GuildData"):
                Rating = pathFind(vass, "GuildData/RatingInfo/RatingInfo/Rating")
                minRating = self.fakeAcc.GuildData.getRatingForRecommendedVassals()

                if minRating < Rating:
                    rv, _ = self.fakeAcc.GuildData.newRecommendedVassal()
                    self.I.WS.addRecommendedVassal(self.fakeAcc, self.vassalAuid, rv, vass)
                    self.fakeAcc.GuildData.RecommendedForMapVassals.add(rv)
            else:
                warn("WinSiegeAction.onAddRecomendedVassal bad guilddata")

        changes = self.I.WS.pickPendingChanges(self.fakeAcc)
        self.I.WS.sendBroadCast(self.fakeAcc, changes, self.fakeAcc.GuildData.getAllMembers(), '')
        # Вассалы переполнены, известим об этом сервис осад
        self.response["lock_siege"] = 1
        self.response["ok"] = 1
        self.fin()

    def processLiberation(self):
        guildData = self.fakeAcc.GuildData
        guildSuzerain = self.fakeAcc.GuildData.GuildSuzerain
        debug("processLiberation for %s", self.fakeAcc.GuildAuid)
        self.I.WS.resetPendingChanges(self.fakeAcc)
        guildData.write(self.fakeAcc.pending)
        self.fakeAcc.SiegeData.write(self.fakeAcc.pending)
        # Если хозяин был, надо ему сообщить, что вассал освободился
        if guildSuzerain.ShortInfo.GuildAuid and guildSuzerain.ShortInfo.GuildAuid != CC.NPC_SUZERAIN_AUID:
            debug("processLiberation: suzerain was %s", guildSuzerain.ShortInfo.GuildAuid)
            args = dict(method="remove_vassal", message={"auid": CC.GUILD_NEUTRAL_AUID,
                                                         "targetAuid": self.vassalAuid,
                                                         "notifyVassal": False})
            self.oldSuzerainAuid = guildSuzerain.ShortInfo.GuildAuid
            self.I.SEX.sendToGuildService(self.vassalAuid, self.oldSuzerainAuid, args, self.onVassalRemoved)
        # Если был хоть какой-то хозяин, поделимся со статистикой
        if guildSuzerain.ShortInfo.GuildAuid:
            self.I.STATS.addGuildInteraction(guildData.GuildAuid, guildSuzerain.ShortInfo.GuildAuid,
                                             GuildInteractionType.Revolt, self.currentSiege.Uid, int(time.time()) - self.currentSiege.EndTime)
        willHaveUltimateShop = guildData.RatingInfo.Rating >= self.I.SD.data["ClanWarsData"]["shopAncientRating"]
        self.I.WS.checkGuildShopOnNewSuzerain(guildData, guildData.RatingInfo.Rating, willHaveUltimateShop)
        self.I.WS.fillSuzerain(guildData, 0, "", "", 0, 0, 0, 0, 0, 0, 0)
        guildSuzerain.JoinTime = int(time.time())
        guildSuzerain.DonationYesterday = 0
        guildSuzerain.DonationToday = 0
        # Уберём осаду
        guildData.removeSiege(self.currentSiege.Uid)
        self.fakeAcc.SiegeData.removeSiege(self.currentSiege.Uid)
        guildData.SiegeForMyGuildEndTime = 0
        guildData.LockedByOtherGuild = False
        changes = self.I.WS.pickPendingChanges(self.fakeAcc)
        self.I.WS.sendBroadCast(self.fakeAcc, changes, guildData.getAllMembers(), '')
        self.I.WS.saveGuildData(self.fakeAcc, None)
        self.response["lock_siege"] = 0
        self.response["ok"] = 1
        self.fin()

    def onVassalRemoved(self, response):
        if response:
            isOk = response.get("ok") or 0
            if not isOk:
                err("Vassal %d was not removed from previous suzerain %d", self.vassalAuid, self.oldSuzerainAuid)

    def onVassalInfoFound(self, response, acc=None):
        if response:
            try:
                data_json = response["r"]["data"]
                guildDict = json_loads(data_json)
            except:
                self.response["error"] = "WinSiegeAction: error in parsing guild_data for guildAuid %d" % self.vassalAuid
                self.response["ec"] = EC.SIEGE_NO_DATA_IN_DATABASE
                self.response["ok"] = 0
                self.fin()
                return

            acc = self.fakeAcc
            self.I.WS.resetPendingChanges(acc)
            acc.SiegeData.write(acc.pending)
            acc.GuildData.write(acc.pending)
            self.I.WS.createVassal(acc.GuildData, guildDict)
            self.I.WS.removeGuildFromRecommendedVassal(acc, self.vassalAuid)
            # Уберём инвайт от вассала, если он был
            if acc.Requests and ("SuzerainInvites" in acc.Requests) and (str(self.vassalAuid) in acc.Requests["SuzerainInvites"]):
                del acc.Requests["SuzerainInvites"][str(self.vassalAuid)]
            # Посмотрим, надо ли убрать гильдию из экс-вассалов
            if str(self.vassalAuid) in acc.GuildData.ExVassals:
                del acc.GuildData.ExVassals[str(self.vassalAuid)]
            self.I.WS.removeRequestsData(acc.GuildData.GuildAuid, {"requests.SuzerainInvites.%s" % str(self.vassalAuid): str(self.vassalAuid)})
            # Вассала взяли, теперь надо ему об этом сообщить
            args = dict(method="new_suzerain_notify", message={})
            self.I.SEX.sendToGuildService(acc.GuildData.GuildAuid, self.vassalAuid, args, self.onTargetSuzerainUpdated)
            # Посмотрим, что со старым сюзереном, расскажем ему, что вассала забрали, если что
            oldSuzerainId = pathFind(guildDict, "GuildData/GuildSuzerain")
            shortInfoId = pathFind(guildDict, "GuildData/GuildMapEntityKeeper/Keeper/%s/GuildMapEntity/ShortInfo" % oldSuzerainId, force_int_keys=False)
            oldSuzerainAuid = pathFind(guildDict, "GuildData/GuildShortInfoKeeper/Keeper/%s/GuildShortInfo/GuildAuid" % shortInfoId, force_int_keys=False) or 0
            if oldSuzerainAuid and oldSuzerainAuid != -1:
                args = dict(method="remove_vassal", message={"auid": CC.GUILD_NEUTRAL_AUID,
                                                             "targetAuid": self.vassalAuid,
                                                             "notifyVassal": False})
                self.oldSuzerainAuid = oldSuzerainAuid
                self.I.SEX.sendToGuildService(self.vassalAuid, oldSuzerainAuid, args, self.onVassalRemoved)

            # Уберём осаду, в которой целью присутствовал новоприобретённый вассал
            acc.GuildData.removeSiege(self.currentSiege.Uid)
            acc.SiegeData.removeSiege(self.currentSiege.Uid)

            changes = self.I.WS.pickPendingChanges(acc)
            self.I.WS.sendBroadCast(acc, changes, acc.GuildData.getAllMembers(), '')
            self.I.WS.saveGuildData(acc, None)
            self.response["ok"] = 1
            self.fin()
        else:
            err("WinSiegeAction: bad response from database")
            self.response["ok"] = 0
            self.fin()

    @action_timing
    def onTargetSuzerainUpdated(self, data_reply):
        info("GuildService: add suzerain reply (value=%r)", data_reply)
        self.I.STATS.addGuildInteraction(self.fakeAcc.GuildData.GuildAuid, self.vassalAuid,
                                             GuildInteractionType.Capture, self.currentSiege.Uid, int(time.time()) - self.currentSiege.EndTime)


class NewRecommendedVassalNotify(SubAction):
    action = "new_recommended_vassal_notify"
    """ сообщаем сюзерену что у него появился новый потенциальный кандидат в вассалы"""

    @action_timing
    def onStart(self):
        info("GuildService: NewRecommendedVassalNotify")
        if self.checkValidIntParam("fromGuildAuid") and self.checkValidIntParam("toGuildAuid"):
            self.fakeAcc = ClassDict(auid=CC.GUILD_NEUTRAL_AUID, GuildData=None, guildAuid=self.toGuildAuid)
            self.I.WS.loadGuildData(self.fakeAcc, self.onLoad)
        else:
            self.fin()

    def onLoad(self, acc, errMessage=None):
        info("GuildService: NewRecommendedVassalNotify")
        if acc and errMessage is None:
            self.I.WS.loadGuildDataByGuildAuid(self.fromGuildAuid, self.updateSuzerainData)
            return
        else:
            err("err: %r" % errMessage)
            info("GuildService: NewRecommendedVassalNotify.onLoad bad response")
        self.fin()

    def updateSuzerainData(self, response):
        info("GuildService: NewRecommendedVassalNotify.updateSuzerainData response: %r" % response)
        if response:
            try:
                data_json = response["r"]["data"] or '{"GuildData":{}}'
            except:
                data_json = '{"GuildData":{}}'

            vass = json_loads(data_json)

            self.I.WS.resetPendingChanges(self.fakeAcc)
            self.fakeAcc.GuildData.write(self.fakeAcc.pending)

            if vass and vass.get("GuildData"):
                Rating = pathFind(vass, "GuildData/RatingInfo/RatingInfo/Rating")
                minRating = self.fakeAcc.GuildData.getRatingForRecommendedVassals()

                #поищем есть ли у нас рекомендованный Вассал
                isRVassal = not any(self.fromGuildAuid == v.ShortInfo.GuildAuid
                                    for k, v in self.fakeAcc.GuildData.RecommendedForMapVassals.iteritems())

                if (minRating < Rating
                    and len(self.fakeAcc.GuildData.RecommendedForMapVassals) < self.I.Config.getMainConfig().GUILD_MAX_RECOMMENDED_VASSAL_SIZE
                    and  self.fromGuildAuid not in self.fakeAcc.GuildData.GuildsRemovedFromSearch and isRVassal):
                    rv, _ = self.fakeAcc.GuildData.newRecommendedVassal()
                    self.I.WS.addRecommendedVassal(self.fakeAcc, self.fromGuildAuid, rv, vass)
                    self.fakeAcc.GuildData.RecommendedForMapVassals.add(rv)
                    changes = self.I.WS.pickPendingChanges(self.fakeAcc)

                    self.I.WS.sendBroadCast(self.fakeAcc, changes, [], '')
                    self.I.WS.saveGuildData(self.fakeAcc, self.onSave)
                    return
                else:
                    warn("GuildService: NewRecommendedVassalNotify.updateSuzerainData bad candidate")
            else:
                warn("GuildService: NewRecommendedVassalNotify.updateSuzerainData bad guilddata")
        self.fin()

    def onSave(self, data_reply):
        info("GuildService: persistent reply (value=%r)", data_reply.get("r") if data_reply else "empty reply from mongo db")
        self.response["ok"] = 1
        self.fin()


class AddVassalAction(SubAction):
    action = "add_vassal"

    """ Принимаем вассала, можно вызвать через чит или через GMTools """
    @action_timing
    def onStart(self):
        info("GuildService: AddVassalAction")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("targetAuid"):
            if self.auid != CC.GUILD_NEUTRAL_AUID:
                self.acc = self.I.WS.getUserAcc(self.auid)
                if self.acc:
                    self.I.WS.loadGuildDataByGuildAuid(self.targetAuid, self.onLoadVassalGuild )
                    return
                self.response["error"] = "GuildService: can not find acc by auid=%r" % self.auid
            # Сторонний запрос или логин через GMTools
            else:
                if self.checkValidIntParam("toGuildAuid"):
                    self.acc = ClassDict(auid=CC.GUILD_NEUTRAL_AUID, GuildData=None, guildAuid=self.toGuildAuid)
                    self.I.WS.loadGuildData(self.acc, self.onDataLoaded)
                    return
        else:
            err("GuildService.AddVassalAction invalid params " % self.auid)


    def onDataLoaded(self, acc, errMessage=None):
        info("GuildService: AddVassalAction.onDataLoaded")
        if acc and errMessage is None:
            self.I.WS.loadGuildDataByGuildAuid(self.targetAuid, self.onLoadVassalGuild)
        else:
            info("GuildService: AddVassalAction.onDataLoaded bad response")
            self.response["ok"] = 0
            self.fin()

    def onLoadVassalGuild(self, response):
        info("GuildService.AddVassalAction.onLoadVassalGuild")
        if response:
            try:
                data_json = response["r"]["data"] or '{"GuildData":{}}'
            except Exception:
                data_json = '{"GuildData":{}}'
            self.addVassal(json_loads(data_json))
        else:
            err("GuildService.AddVassalAction.onLoadVassalGuild bad response: %r", response)

    def addVassal(self, guild):
        if len(self.acc.GuildData.GuildVassals) < self.I.Config.getMainConfig().GUILD_MAX_VASSAL_SIZE:
            self.guild = guild
            self.notifySuzerain(pathFind(guild, "GuildData/GuildAuid"),  self.onNotifySuzerain)
            oldSuzerainId = pathFind(guild, "GuildData/GuildSuzerain")
            shortInfoId = pathFind(guild, "GuildData/GuildMapEntityKeeper/Keeper/%s/GuildMapEntity/ShortInfo" % oldSuzerainId, force_int_keys=False)
            oldSuzerainAuid = pathFind(guild, "GuildData/GuildShortInfoKeeper/Keeper/%s/GuildShortInfo/GuildAuid" % shortInfoId, force_int_keys=False) or 0
            if oldSuzerainAuid and oldSuzerainAuid != -1 and oldSuzerainAuid != self.acc.GuildData.GuildAuid:
                args = dict(method="remove_vassal", message={"auid": CC.GUILD_NEUTRAL_AUID, "targetAuid": self.targetAuid})
                self.oldSuzerainAuid = oldSuzerainAuid
                self.I.SEX.sendToGuildService(self.targetAuid, oldSuzerainAuid, args, self.onVassalRemoved)
        else:
            self.response["ec"] = EC.GUILD_MAX_VASSAL_SIZE
            self.response["error"] = "Your clan already have maximum count of vassals!"
            self.response["ok"] = 0
            self.fin()

    def notifySuzerain(self, guildAuid, callback):
        mess = dict(method="new_suzerain_notify", message={})
        self.I.SEX.sendToGuildService(self.acc.GuildData.GuildAuid, guildAuid, mess, callback)

    def onNotifySuzerain(self, response ):
        info("GuildService: AddVassalAction.onNotifySuzerain response: %r " , response)
        if response and response.get("ok") and self.guild:
            self.I.WS.resetPendingChanges(self.acc)
            self.acc.GuildData.write(self.acc.pending)
            self.I.WS.createVassal(self.acc.GuildData, self.guild)
            if str(self.targetAuid) in self.acc.GuildData.ExVassals:
                del self.acc.GuildData.ExVassals[str(self.targetAuid)]
            changes = self.I.WS.pickPendingChanges(self.acc)
            self.I.WS.sendBroadCast(self.acc, changes, [], '')
            self.I.WS.saveGuildData(self.acc, None)
            self.response["GuildData"] = changes.get("guild_data", [])
            self.response["ok"] = 1
        else:
            # что то пошло не так с нотификацией
            self.response["ec"] = EC.GUILD_CANNOT_NOTIFY
            self.response["error"] = "Can not notify our vassal that I am his suzerain!"
            self.response["ok"] = 0
        self.fin()

    def onVassalRemoved(self, response):
        if response:
            isOk = response.get("ok") or 0
            if not isOk:
                err("Vassal %d was not removed from previous suzerain %d", self.vassalAuid, self.oldSuzerainAuid)

# ------------- DEBUG ACTIONS -------------- #


class ResetSiegesCounterAction(SubAction):
    action = "reset_sieges_counter"
    debug = True

    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: ResetSiegesCounterAction")
        if self.checkValidIntParam("auid"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                acc.GuildData.write(acc.pending)

                while len(acc.GuildData.ActiveSieges):
                    acc.GuildData.ActiveSieges.pop()
                for siegeId, siege in acc.GuildData.InitiatedSieges.items():
                    acc.GuildData.InitiatedSieges.remove(siege)
                acc.GuildData.SiegeForMyGuildEndTime = 0
                acc.GuildData.LockedByOtherGuild = False
                changes = self.I.WS.pickPendingChanges(acc)
                self.I.WS.sendBroadCast(acc, changes, [], '')
                self.I.WS.saveGuildData(acc, None)
                self.response["GuildData"] = changes.get("guild_data", [])
                self.response["ok"] = 1
            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
                self.response["error"] = "GuildService: can not find acc by auid=%r" % self.auid
                self.response["ok"] = 0

        self.fin()


class SetSiegeDurationAction(SubAction):
    action = "set_siege_duration"
    debug = True

    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: SetSiegeDurationAction")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("targetAuid") and \
            self.checkValidIntParam("duration"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                acc.GuildData.write(acc.pending)

                self.I.SIEGE.setSiegeDuration(self.targetAuid, self.duration, self.onSiegeDurationChanged)

                changes = self.I.WS.pickPendingChanges(acc)
                self.I.WS.sendBroadCast(acc, changes, [], '')
                self.I.WS.saveGuildData(acc, None)
                self.response["GuildData"] = changes.get("guild_data", [])
                self.response["ok"] = 1
            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
                self.response["error"] = "GuildService: can not find acc by auid=%r" % self.auid
                self.response["ok"] = 0

        self.fin()

    def onSiegeDurationChanged(self, response):
        if not response.get("ok"):
            err("SetSiegeDurationAction failed: bad response from siege_service")


class SetSiegeScoreAction(SubAction):
    action = "set_siege_score"
    debug = True

    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: SetSiegeScoreAction")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("targetAuid") and \
            self.checkValidIntParam("score"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                acc.GuildData.write(acc.pending)

                self.I.SIEGE.setSiegeScore(acc.GuildData.GuildAuid, self.targetAuid, self.score, self.onSiegeScoreChanged)

                changes = self.I.WS.pickPendingChanges(acc)
                self.I.WS.sendBroadCast(acc, changes, acc.GuildData.getAllMembers(), '')
                self.I.WS.saveGuildData(acc, None)
                self.response["GuildData"] = changes.get("guild_data", [])
                self.response["SiegeData"] = changes.get("siege_data", [])
                self.response["ok"] = 1
            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
                self.response["error"] = "GuildService: can not find acc by auid=%r" % self.auid
                self.response["ok"] = 0

        self.fin()

    def onSiegeScoreChanged(self, response):
        if not response.get("ok"):
            err("SetSiegeScoreAction failed: bad response from siege_service")


class DebugUpdateSiegeAction(SubAction):
    action = "debug_update_siege"
    debug = True

    """ Форвардим изменения, приходящие от siege_service """
    @action_timing
    def onStart(self):
        if self.checkValidIntParam("guildAuid"):
            info("GuildService: DebugUpdateSiegeAction body: %r" % self.request.request.body)
            self.seageInfo = json_loads(self.request.request.body)
            siegeInfo = self.seageInfo["siegeInfo"]

            acc = ClassDict(auid=CC.GUILD_NEUTRAL_AUID, GuildData=None, SiegeData=None, guildAuid=self.guildAuid)
            acc.GuildData = self.I.WS.getGuildData(acc.guildAuid)
            acc.SiegeData = self.I.WS.getSiegeData(acc.guildAuid)
            if acc.GuildData and acc.SiegeData:
                self.I.WS.resetPendingChanges(acc)
                acc.GuildData.write(acc.pending)
                acc.SiegeData.write(acc.pending)
                for siegeUpdate in siegeInfo:
                    try:
                        # Поменяли длительность
                        if siegeUpdate["cmd"] == "duration":
                            siege = acc.SiegeData.getSiegeById(siegeUpdate["_id"])
                            if siege:
                                siege.EndTime = siegeUpdate["end_time"]
                            else:
                                warn("Bad siege _id %r for guild %r", siegeUpdate["_id"], acc.guildAuid)

                            if siege and siege.Target.ShortInfo.GuildAuid == acc.GuildData.GuildAuid:
                                acc.GuildData.SiegeForMyGuildEndTime = siegeUpdate["end_time"]
                        elif siegeUpdate["cmd"] == "score":
                            acc.SiegeData.updateScore(siegeUpdate["_id"], siegeUpdate["guildAuid"], siegeUpdate["score"])
                        elif siegeUpdate["cmd"] == "time":
                            siege = acc.SiegeData.getSiegeById(siegeUpdate["_id"])
                            if siege and siege.Target.ShortInfo.GuildAuid == acc.GuildData.GuildAuid:
                                acc.GuildData.SiegeForMyGuildEndTime = siegeUpdate["end_time"]
                            for siegeId, se in acc.GuildData.InitiatedSieges.iteritems():
                                if se.SiegeId == siegeUpdate["_id"]:
                                    se.EndTime = siegeUpdate["end_time"]
                        else:
                            err("Unknown command from siege service: %s", siegeUpdate["cmd"])
                    except Exception:
                        catch()

                changes = self.I.WS.pickPendingChanges(acc)
                self.I.WS.sendBroadCast(acc, changes, [], '')
                self.I.WS.saveGuildData(acc, None)
                self.response["ok"] = 1
                self.fin()
                return
            else:
                self.response["error"] = "GuildService: can not find active acc by guildAuid=%r" % self.guildAuid
        self.response["ok"] = 0
        self.fin()


class SetLostTargetLeftTimeAction(SubAction):
    action = "set_lost_target_left_time"
    debug = True

    @action_timing
    def onStart(self):
        info("GuildService: SetLostTargetLeftTimeAction")
        if self.checkValidIntParam("auid") and self.checkValidParam("guildAuid") and self.checkValidIntParam("value"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                acc.GuildData.write(acc.pending)

                if self.guildAuid in acc.GuildData.LostSiegesGuilds:
                    acc.GuildData.LostSiegesGuilds[self.guildAuid] = int(time.time()) + self.value - self.I.Config.getMainConfig().SiegeSettings.TIMEOUT_FOR_CAPTURE_AFTER_LOSS
                changes = self.I.WS.pickPendingChanges(acc)
                self.I.WS.sendBroadCast(acc, changes, [], '')
                self.I.WS.saveGuildData(acc, None)
                self.response["GuildData"] = changes.get("guild_data", [])
                self.response["ok"] = 1
            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
                self.response["error"] = "GuildService: can not find acc by auid=%r" % self.auid
                self.response["ok"] = 0

        self.fin()


class SetExVassalLeftTimeAction(SubAction):
    action = "set_ex_vassal_left_time"
    debug = True

    @action_timing
    def onStart(self):
        info("GuildService: SetExVassalLeftTimeAction")
        if self.checkValidIntParam("auid") and self.checkValidParam("guildAuid") and self.checkValidIntParam("value"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                acc.GuildData.write(acc.pending)

                if self.guildAuid in acc.GuildData.ExVassals:
                    acc.GuildData.ExVassals[self.guildAuid] = (int(time.time()) + self.value -
                                                              self.I.Config.getMainConfig().SiegeSettings.TIMEOUT_FOR_EX_VASSAL_CAPTURE -
                                                              self.I.Config.getMainConfig().SiegeSettings.SIEGE_DURATION)
                changes = self.I.WS.pickPendingChanges(acc)
                self.I.WS.sendBroadCast(acc, changes, [], '')
                self.I.WS.saveGuildData(acc, None)
                self.response["GuildData"] = changes.get("guild_data", [])
                self.response["ok"] = 1
                self.response["ok"] = 1
            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
                self.response["error"] = "GuildService: can not find acc by auid=%r" % self.auid
                self.response["ok"] = 0

        self.fin()



