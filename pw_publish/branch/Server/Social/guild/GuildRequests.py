#!/usr/bin/env python
# -*- coding: utf-8 -*-
import functools, datetime
from base.helpers import *

from subaction import *
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData
from guild.GuildWarsData import GuildWarsData
from guild.RecruitsData import RecruitsData
from siege.SiegeData import SiegeData
from StatisticCore.ttypes import GuildInteractionType
from StatisticCore.ttypes import TalentInfo, TalentChangeOperation
from imirror import MirrorDataType

import pymongo
import gc
import math

from enums.TalentEventType import *
import CC

import coord_cfg


def getNumberOfDays():
    return 7


def getMongoKeyAuid(guildAuid):
    return "gs_%d" % guildAuid


def getMongoKey(acc):
    return getMongoKeyAuid(acc.guildAuid)


def getGuildChatName(guildAuid):
    return 'guild_%s' % guildAuid


class AddTechsAction(SubAction):
    action = "add_techs"

    def onStart(self):
        info("AddTechsAction.onStart")
        persistentId = self.getIntParam("persistentId")
        techType = self.getParam("techType").split(',')
        duration = self.getIntParam("compensation")
        startTime = self.getIntParam("startTime", 0)

        if persistentId and "sieges" in techType:
            self.I.WS.techs[persistentId] = {"startTime": startTime, "duration": duration}


class CreateGuildAction(SubAction):
    action = "create_guild"
    intParams = ("auid", "uid", "server", "guildAuid", "bestHero")
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: CreateGuildAction: %s", self.arguments)
        if not (self.checkIntParams()
                and self.checkValidParam("snid")
                and self.checkValidParam("snuid")
                and self.checkValidFloatParam("bestHeroRating")
                and self.checkValidParam("guildFraction")):
            self.fin()
            return

        self.locale = self.getParam("locale", "")
        self.acc, errMessage = self.I.WS.subscribeUserAccountOnGuildCreate(self.auid, self.guildAuid, self.server, self.uid)
        if errMessage is not None:
            return self.errorResponse(0, errMessage)

        self.shname = urllib.unquote(self.getParam("shortname", ""))
        self.flname = urllib.unquote(self.getParam("fullname", ""))

        args = {"FullName": self.flname, "ShortName": self.shname, "GuildAuid": self.guildAuid}
        self.I.DATA.insert("guilds", "guilds", args, callback=self.onInsert)


    @action_timing
    def onInsert(self, response):
        debug("CreateGuildAction: onInsert: %r", response)
        if response:
            if response['r']:
                self.sendOK()
                return

        self.response["ok"] = 0
        self.response["unique"] = False
        self.fin()

    def sendOK(self):
        debug("CreateGuildAction.sendOK for guildAuid %s", self.guildAuid)
        self.I.WS.resetPendingChanges(self.acc)
        self.acc.GuildData = GuildData()  # зачем оно снова создаётся?! ведь уже под subscribeUserAccount создавалось!
        guildData = self.acc.GuildData
        guildData.init(None)

        guildData.GuildInfo.FullName = urllib.unquote(self.getParam("fullname", ""))
        guildData.GuildInfo.ShortName = urllib.unquote(self.getParam("shortname", ""))
        guildData.GuildAuid = self.guildAuid
        guildData.GuildInfo.GuildFraction = self.guildFraction
        guildData.version.LevelsConverted = True

        member, id = guildData.newGuildMember()
        member.Person = self.acc.auid
        member.IsOfficer = True
        member.JoinTime = int(time.time())
        defRating = self.I.Config.getMainConfig().GUILD_DEFAULT_RATING

        member.AddedTalentsDailyCount = self.I.Config.getMainConfig().GuildBankSettings.GUILD_BANK_ADD_LIMIT
        member.TakenTalentsDailyCount = self.I.Config.getMainConfig().GuildBankSettings.GUILD_BANK_TAKE_LIMIT

        member.DailyRating = defRating
        member.EventRating = defRating

        for idx in xrange(0, getNumberOfDays()):
            memberRatingInfo, memberRatingInfo_id = guildData.newMemberDayRating()
            memberRatingInfo.HeroRating = defRating
            memberRatingInfo.Hero = 0
            member.HeroRatings.add(idx, memberRatingInfo)
        guildData.RatingInfo.DailyRating = defRating
        guildData.RatingInfo.Rating = defRating

        guildData.GuildCreateTime = toint(time.time())
        guildData.Owner = member
        guildData.Members.add(member)

        # Считаем кол-во гильдий PF-58833
        _callback = functools.partial(self.onGuildCount, guildData)

        self.guildsCount = 0
        self.I.DATA.find("guilds", "guilds", {"GuildAuid": {"$exists": True}}, _callback)

    def onGuildCount(self, guildData, response):
        info("CreateGuildAction.onGuildCount response: %r", response)
        if response and "r" in response:
            self.guildsCount = toint(response["r"].count())

        info("CreateGuildAction.onGuildCount: GuildCount %d", self.guildsCount)

        guildData.GuildInfo.Place = self.guildsCount
        guildData.GuildInfo.PlaceChange = 0
        guildData.GuildInfo.BestPlace = guildData.GuildInfo.Place
        guildData.GuildSuzerain, _ = guildData.newGuildMapEntity()
        guildData.GuildSuzerain.ShortInfo, _ = guildData.newGuildShortInfo()
        self.addCWNPCEntities()
        self.I.WS.resetAllShopItems(guildData)

        guildData.RecruitmentInfo.Locale = self.locale
        self.I.EXPORT.setGuildRecruitmentParams(guildData.GuildAuid, guildData.RecruitmentInfo.Locale)

        self.acc.SiegeData = SiegeData() # !!!!
        self.acc.SiegeData.init(None)

        changes = [MakeModelChangeString("init_guild", "/", "init", self.acc.GuildData.generateJsonDict())]
        siegeChanges = [MakeModelChangeString("init_siege", "/", "init", self.acc.SiegeData.generateJsonDict())]
        self.response["GuildData"] = changes
        self.response["SiegeData"] = siegeChanges
        self.response["ok"] = 1
        self.I.WS.saveGuildData(self.acc, None)
        self.I.WS.registerGuild(self.guildAuid, self.acc.GuildData, self.acc.SiegeData) # !!! повторно!
        self.acc.RecruitRequests = self.I.WS.getRecruitData(self.guildAuid)
        _callback = functools.partial(self.onSiegeRegister, acc=self.acc)
        self.I.SIEGE.subscribe(self.guildAuid, _callback) # !!! повторно!

        self.I.WS.updateGuildShortName(self.acc.auid, guildData.GuildInfo.ShortName)

        self.fin()

    def addCWNPCEntities(self):
        cEveryDayProfit = self.I.SD.data["ClanWarsData"]["npcVillage"]["everyDayProfit"]
        cVRating = self.I.SD.data["ClanWarsData"]["npcVillage"]["clanRating"]
        CVILLAGE = self.I.SD.data["ClanWarsData"]["countOfNPCVillage"]
        cVillage = self.I.SD.data["ClanWarsData"]["countOfNPCVillage"] + 1
        if self.acc.GuildData:
            while cVillage and len(self.acc.GuildData.GuildVassals) < CVILLAGE:
                vass, _ = self.acc.GuildData.newGuildMapEntity()
                vass.ShortInfo, _ = self.acc.GuildData.newGuildShortInfo()
                vass.ShortInfo.GuildAuid = CC.NPC_VASSAL_AUID
                vass.ShortInfo.DonationToday = self.I.SD.getGuildVassalsTributeCoef() * cEveryDayProfit
                vass.ShortInfo.Experience = cVRating
                cVillage -= 1
                self.acc.GuildData.GuildVassals.add(vass)

    def onSiegeRegister(self, response, acc=None):
        info("GuildService: onSiegeRegister")
        if response and acc:
            guildAuids = []
            try:
                acc.SiegeData.write(acc.pending)
                guildAuids = acc.SiegeData.update(response)
            except:
                err("Bad data from Siege service received")
                return

            if len(guildAuids):
                _callback = functools.partial(self.onSiegeDataFromSQL, acc=acc)
                self.I.EXPORT.getGuildsInfo(guildAuids, _callback)
        else:
            err("Can't load siege data, response = %s, acc = %s", response, acc)

    def onSiegeDataFromSQL(self, reply, acc=None):
        r = reply["r"]
        if r and len(r):
            # Обновим заодно и все старые записи, если у этих кланов что-то изменилось
            for guildInfo in r:
                acc.SiegeData.updateGuildInfoFromSQL(guildInfo)


class RenameGuildAction(SubAction):
    action = "rename_guild"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: RenameGuildAction")
        if self.checkValidIntParam("auid"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                if acc.GuildData.Owner.Person != acc.auid:
                    self.response["error"] = "Can not rename guild: you are not owner"
                else:
                    changes = self.I.WS.renameGuild(acc, self.getParam("shortname", ""), self.getParam("fullname", ""))
                    self.response["GuildData"] = changes
                    self.response["ok"] = 1
            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
        self.fin()


class CheckGuildExistsAction(SubAction):
    action = "check_guild_exists"

    @action_timing
    def onStart(self):
        info("GuildService: CheckGuildExistsAction")
        self.exists = True
        if self.checkValidIntParam("guildAuid"):
            self.I.DATA.find_one("guilds", "guilds", {"GuildAuid": self.guildAuid}, callback=self.onGuildChecked)
        else:
            # если нет параметра и ничего непонятно - ложись спать и ничего не трогай!!!
            self.onGuildChecked({})

    def onGuildChecked(self, response):
        info("GuildService: onGuildChecked response: " + str(response))
        if response:
            if not response['r']:
                self.exists = False

        self.response["inviteId"] = self.getIntParam("inviteId", 0)
        self.response["exists"] = self.exists
        self.response["ok"] = 1
        self.fin()


class CheckGuildSizeAction(SubAction):
    action = "check_guild_size"

    @action_timing
    def onStart(self):
        if not self.checkValidIntParam("guildAuid"):
            warn("GuildService: CheckGuildSizeAction bad guildAuid: %r", self.guildAuid)
            self.fin()
            return

        info("GuildService: CheckGuildSizeAction(%s)", self.guildAuid)

        guild = self.I.WS.getGuildDataReadOnly(self.guildAuid)
        if not guild: # perform fast-load and check
            self.I.WS.loadGuildDataByGuildAuid(self.guildAuid, _callback=self.onLoadGuildData)
            return

        self.success(
            len(guild.Members),
            self.I.SD.getGuildMembersLimitByExp(guild.GuildLevelInfo.Experience, self.I)
        )


    def onLoadGuildData(self, response):
        try:
            if response["r"] is None:
                return self.errorResponse(0, "no guild")
            data_json = response["r"]["data"]
            if not data_json:
                raise ValueError("Empty response['r']['data']")
            GData = json_loads(data_json)
        except Exception:
            catch("CheckGuildSizeAction.onLoadGuildData bad response: %r ", response)
            self.response["ok"] = 0
            self.fin()
            return

        info("CheckGuildSizeAction.onLoadGuildData (guildAuid=%s)", self.guildAuid)
        self.success(
            len(pathFind(GData, "GuildData/Members/Set")),
            self.I.SD.getGuildMembersLimitByExp(pathFind(GData, "GuildData/GuildLevelInfo/GuildLevelInfo/Experience"), self.I)
        )


    def success(self, current, max):
        self.response["current"] = current
        self.response["max"] = max
        self.response["ok"] = 1
        self.fin()


class CheckGuildNameAction(SubAction):
    action = "check_guild_name"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: CheckGuildNameAction")
        # заглушка
        if self.checkValidIntParam("auid"):
            self.fullNameChecked = False
            self.shortNameChecked = False

            self.fullNameUnique = False
            self.shortNameUnique = False

            self.fullname = self.getParam("fullname", "")
            self.shortname = self.getParam("shortname", "")
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                #info( "GuildService: acc.short = " + str(acc.GuildData.GuildInfo.ShortName) + " arg.short = " + str(self.shortname))
                if acc.GuildData.GuildInfo.ShortName == self.shortname:
                    #warn("debug: short equal")
                    self.shortNameChecked = True
                    self.shortNameUnique = True
                    self.onNameChecked()
                else:
                    #warn("debug: short equal")
                    self.I.DATA.find_one("guilds", "guilds",
                                         {"ShortName": {"$regex": "^" + self.shortname + "$", "$options": '-i'}},
                                         callback=self.onCheckShortName)

                #info( "GuildService: acc.full = " + str(acc.GuildData.GuildInfo.FullName) + " arg.full = " + str(self.fullname))
                if acc.GuildData.GuildInfo.FullName == self.fullname:
                    #warn("debug: full equal")
                    self.fullNameChecked = True
                    self.fullNameUnique = True
                    self.onNameChecked()
                else:
                    #warn("debug: full equal")
                    self.I.DATA.find_one("guilds", "guilds",
                                         {"FullName": {"$regex": "^" + self.fullname + "$", "$options": '-i'}},
                                         callback=self.onCheckFullName)
            else:
                self.I.DATA.find_one("guilds", "guilds",
                                     {"FullName": {"$regex": "^" + self.fullname + "$", "$options": '-i'}},
                                     callback=self.onCheckFullName)
                self.I.DATA.find_one("guilds", "guilds",
                                     {"ShortName": {"$regex": "^" + self.shortname + "$", "$options": '-i'}},
                                     callback=self.onCheckShortName)

    def onCheckShortName(self, response):
        info("GuildService: onCheckShortName response: " + str(response))
        self.shortNameChecked = True
        if response:
            if not response['r']:
                self.shortNameUnique = True
        self.onNameChecked()

    def onCheckFullName(self, response):
        info("GuildService: onCheckFullName response: " + str(response))
        self.fullNameChecked = True
        if response:
            if not response['r']:
                self.fullNameUnique = True
        self.onNameChecked()

    def onNameChecked(self):
        info("GuildService: onNameChecked")
        if self.fullNameChecked and self.shortNameChecked:
            if self.fullNameUnique == False:
                self.response["unique"] = "Full"
            elif self.shortNameUnique == False:
                self.response["unique"] = "Short"
            else:
                self.response["unique"] = True
            self.response["ok"] = 1
            self.fin()


class KickGuildAction(SubAction):
    action = "kick_guild"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: KickGuildAction")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("personAuid"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)

                if not self.I.WS.isOwner(acc):
                    self.response["error"] = "Can not kick: you are not owner"
                elif self.personAuid == acc.auid:
                    self.response["error"] = "Can not kick yourself"
                else:

                    acc.GuildData.write(acc.pending)

                    isRemoved = self.I.WS.removeGuildMember(acc.GuildData, acc.SiegeData, self.personAuid)

                    changes = self.I.WS.pickPendingChanges(acc)
                    self.I.WS.sendBroadCast(acc, changes, [], '')

                    self.I.FRIENDS.deleteSnFriends(self.personAuid, 'pwg', None)

                    fakeGuildData = GuildData()
                    fakeGuildData.init(None)
                    fakeSiegeData = SiegeData()
                    fakeSiegeData.init(None)
                    fakeRecruitsData = RecruitsData()
                    fakeRecruitsData.init(None)
                    fakechanges = {"guild_data": [MakeModelChangeString("init_guild", "/", "init", fakeGuildData.generateJsonDict())],
                                   "siege_data": [MakeModelChangeString("init_siege", "/", "init", fakeSiegeData.generateJsonDict())],
                                   "recruits_data": [MakeModelChangeString("init_recruits", "/", "init", fakeRecruitsData.generateJsonDict())]}
                    self.I.WS.sendBroadCast(acc, fakechanges, [self.personAuid], 'destroy')
                    self.I.WS.updateGuildShortName(self.personAuid, "")
                    if not isRemoved:
                        self.I.WS.saveGuildData(acc, None)
                    self.response["GuildData"] = changes.get("guild_data", [])
                    self.response["ok"] = 1

            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
        self.fin()


class RemoveGuildMemberAction(SubAction):
    action = "remove_guild_member"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: RemoveGuildMemberAction")
        if self.checkValidIntParam("memberAuid") and self.checkValidIntParam("guildAuid"):
            self.fakeAcc = ClassDict(auid=CC.GUILD_NEUTRAL_AUID, GuildData=None, guildAuid=self.guildAuid)
            self.I.WS.loadGuildData(self.fakeAcc, self.onLoadGuildData)

    def onLoadGuildData(self, data_reply, errMessage=None):
        if errMessage is not None:
            self.response["ok"] = 0
            self.response["error"] = errMessage
            self.fin()
            return

        self.I.WS.resetPendingChanges(self.fakeAcc)
        self.fakeAcc.GuildData.write(self.fakeAcc.pending)
        isRemoved = self.I.WS.removeGuildMember(self.fakeAcc.GuildData, self.fakeAcc.SiegeData, self.memberAuid)
        changes = self.I.WS.pickPendingChanges(self.fakeAcc)
        self.I.WS.sendBroadCast(self.fakeAcc, changes, [], '')
        self.I.FRIENDS.deleteSnFriends(self.memberAuid, 'pwg', None)
        if not isRemoved:
            self.I.WS.saveGuildData(self.fakeAcc, None)
        self.response["ok"] = 1
        self.fin()
        return


class LeaveGuildAction(SubAction):
    action = "leave_guild"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: LeaveGuildAction")
        if self.checkValidIntParam("auid"):
            acc = self.I.WS.getUserAcc(self.auid)
            self.member_auid = self.auid
            if acc:
                guildAuid = acc.GuildData.GuildAuid

                self.I.WS.resetPendingChanges(acc)
                acc.GuildData.write(acc.pending)
                acc.SiegeData.write(acc.pending)

                isRemoved = self.I.WS.removeGuildMember(acc.GuildData, acc.SiegeData, self.member_auid)

                self.I.CHAT.removeUserGroup(self.member_auid, getGuildChatName(guildAuid),
                                            self.I.WS.onGuildChatUnregister)
                self.I.WS.updateGuildShortName(self.member_auid, "")
                self.I.FRIENDS.deleteSnFriends(self.member_auid, 'pwg', None)

                if not isRemoved:
                    self.I.WS.saveGuildData(acc, None)
                # радостная весть отправляется подданым голубиной почтой
                changes = self.I.WS.pickPendingChanges(acc)
                self.I.WS.sendBroadCast(acc, changes, [], '')

                self.I.WS.unsubscribeUserAccount(self.auid, guildAuid)

                #изгоям гилддаты не положено. и точка!
                fakeGuildData = GuildData()
                fakeGuildData.init(None)
                fakeSiegeData = SiegeData()
                fakeSiegeData.init(None)
                fakeRecruitsData = RecruitsData()
                fakeRecruitsData.init(None)
                self.response["GuildData"] = [
                    MakeModelChangeString("init_guild", "/", "init", fakeGuildData.generateJsonDict())]
                self.response["SiegeData"] = [
                    MakeModelChangeString("init_siege", "/", "init", fakeSiegeData.generateJsonDict())]
                self.response["RecruitsData"] = [
                    MakeModelChangeString("init_recruits", "/", "init", fakeRecruitsData.generateJsonDict())]
                self.response["ok"] = 1

            else:
                # ээ, а ты кто?
                err("GuildService: can not find acc by auid=%r",  self.auid)
        self.fin()


class DestroyGuildAction(SubAction):
    action = "destroy_guild"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: DestroyGuildAction")
        if self.checkValidIntParam("auid"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                guildAuid = acc.GuildData.GuildAuid

                if not self.I.WS.isOwner(acc):
                    self.response["ec"] = EC.GUILD_ONLY_OFFICER_CAN_OPERATE
                    self.response["error"] = "Can not destroy guild: you are not guild leader"
                else:
                    auids = []
                    # Возвращаем таланты, которые лежали в банке
                    for gTalId in acc.GuildData.FreeTalents.keys():
                        talent = acc.GuildData.getGuildTalentByID(gTalId)
                        # Добавляем в ModelData наш талант
                        callback = functools.partial(self.onAddGuildTalent, GuildData=acc.GuildData)
                        self.I.WS.createMailAddGuildTalent(talent.Owner.Person, talent.PersistentId, talent.HeroClassId,
                                                           talent.Points, acc.GuildData, callback=callback)
                        self.I.STATS.addTalentChange(talent.Owner.Person,
                                                     TalentInfo(talent.PersistentId, gTalId, talent.HeroClassId),
                                                     TalentChangeOperation.ReturnToUserOnLeave)
                        # Удялем из гильдии
                        talent.Owner = 0
                        acc.GuildData.FreeTalents.remove(talent)

                    # Возвращаем таланты, которые кто-то забрал
                    for gTalId in acc.GuildData.TakenTalents.keys():
                        talent = acc.GuildData.getGuildTalentByID(gTalId)
                        # Добавляем в ModelData наш талант
                        callback = functools.partial(self.onAddGuildTalentTaken, GuildData=acc.GuildData)
                        self.I.WS.createMailAddGuildTalent(talent.Owner.Person, talent.PersistentId, talent.HeroClassId,
                                                           talent.Points, acc.GuildData, callback=callback)
                        self.I.STATS.addTalentChange(talent.Owner.Person,
                                                     TalentInfo(talent.PersistentId, gTalId, talent.HeroClassId),
                                                     TalentChangeOperation.ReturnToUserOnLeave)
                        # Удялем из гильдии
                        talent.Owner = 0
                        talent.Holder = 0
                        acc.GuildData.TakenTalents.remove(talent)

                    for gmId in acc.GuildData.Members.keys():
                        member = acc.GuildData.getGuildMemberByID(gmId)
                        callback = functools.partial(self.onDeleteGuildTalents, GuildData=acc.GuildData)
                        self.I.WS.createMailDeleteAllGuildTalents(member.Person, acc.GuildData, callback=callback)
                        self.I.WS.createMailDestroyGuild(member.Person, acc.GuildData, callback=self.onDestroyGuild)
                        self.I.WS.updateGuildShortName(member.Person, "")
                        self.I.FRIENDS.deleteSnFriends(member.Person, 'pwg', None)
                        if member.Person != acc.auid:
                            auids.append(member.Person)

                    self.I.WS.processDestroyGuild(acc.GuildData, acc.SiegeData)

                    args = {"FullName": acc.GuildData.GuildInfo.FullName,
                            "ShortName": acc.GuildData.GuildInfo.ShortName, "GuildAuid": guildAuid}
                    self.I.DATA.remove("guilds", "guilds", args)

                    self.I.WS.resetPendingChanges(acc)
                    acc.GuildData = GuildData()
                    acc.GuildData.init(None)
                    acc.SiegeData = SiegeData()
                    acc.SiegeData.init(None)
                    acc.RecruitsData = RecruitsData()
                    acc.RecruitsData.init(None)

                    self.I.DATA.remove("guilds", "guilds", {"key": getMongoKeyAuid(guildAuid)},
                                       self.I.WS.onDummyGuildCallback)
                    guildChanges = [MakeModelChangeString("init_guild", "/", "init", acc.GuildData.generateJsonDict())]
                    siegeChanges = [MakeModelChangeString("init_siege", "/", "init", acc.SiegeData.generateJsonDict())]
                    recruitsChanges = [MakeModelChangeString("init_recruits", "/", "init", acc.RecruitsData.generateJsonDict())]
                    changes = {"guild_data": guildChanges, "siege_data": siegeChanges, "recruits_data": recruitsChanges}
                    self.I.WS.sendBroadCast(acc, changes, auids, 'destroy')

                    self.I.CHAT.removeUserGroup(acc.auid, getGuildChatName(guildAuid), self.I.WS.onGuildChatUnregister)
                    self.response["GuildData"] = guildChanges
                    self.response["SiegeData"] = siegeChanges
                    self.response["ok"] = 1
                    # clearing cache
                    self.I.WS.unregisterGuild(guildAuid)
            else:
                err("GuildService: can not find acc by auid=%r" , self.auid)
        self.fin()

    def _guildTalentCB(self, response, GuildData):
        if response is None:
            errStack("Response is None! Possible error in ther caller request.")
        elif response.get('ok', 0) == 1 and response.get('ec', -1) == 0:
            pass
        else:
            self.I.WS.resetMailTickers(GuildData)

    def onAddGuildTalent(self, response, GuildData=None):
        info('DestroyGuildAction::onAddGuildTalent (response=%r)', response)
        self._guildTalentCB(response, GuildData)

    def onAddGuildTalentTaken(self, response, GuildData=None):
        info('DestroyGuildAction::onAddGuildTalentTaken (response=%r)', response)
        self._guildTalentCB(response, GuildData)

    def onDeleteGuildTalents(self, response, GuildData=None):
        info('DestroyGuildAction::onDeleteGuildTalents (response=%r)', response)
        self._guildTalentCB(response, GuildData)

    def onDestroyGuild(self, response, GuildData=None):
        info('DestroyGuildAction::onDestroyGuild (response=%r)', response)
        self._guildTalentCB(response, GuildData)


class InviteToGuildAction(SubAction):
    action = "invite_guild"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: InviteToGuildAction")
        if self.checkValidIntParam("auid"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                canInvite = self.I.WS.canInvite(acc)

                if canInvite:
                    self.response["ok"] = 1
                    self.response["guildName"] = acc.GuildData.GuildInfo.FullName
                else:
                    self.response["error"] = "Can not invite guild: you are not guild leader/officer"
                    self.response["ok"] = 0
            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
        self.fin()


class IsGuildMemberAction(SubAction):
    action = "is_guild_member"
    intParams = ("auid", "personAuid", "guildAuid")
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: IsGuildMemberAction")
        if self.checkIntParams():
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                if acc.GuildData.findMemberByAuid(self.personAuid):
                    self.response["is_member"] = True
                else:
                    self.response["is_member"] = False
                self.response["ok"] = 1
            else:
                self.fakeAcc = ClassDict(auid=CC.GUILD_NEUTRAL_AUID, GuildData=None, guildAuid=self.guildAuid)
                self.I.WS.loadGuildData(self.fakeAcc, self.onGuildLoaded)
                return
        self.fin()

    def onGuildLoaded(self, acc, errMessage=None):
        info("GuildService: IsGuildMemberAction.onGuildLoaded")
        if acc and errMessage is None:
            if acc.GuildData.findMemberByAuid(self.personAuid):
                self.response["is_member"] = True
            else:
                self.response["is_member"] = False
            self.response["ok"] = 1
        else:
            err(errMessage)

        self.fin()


class AcceptGuildAction(SubAction):
    action = "accept_guild"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: AcceptGuildAction")
        if (self.checkValidIntParam("auid")
            and self.checkValidIntParam("uid")
            and self.checkValidIntParam("server")
            and self.checkValidParam("snid")
            and self.checkValidParam("snuid")
            and self.checkValidIntParam("guildAuid")
            and self.checkValidIntParam("bestHero")
            and self.checkValidFloatParam("bestHeroRating") ):
            self.locale = self.getParam("locale", "")
            self.I.WS.subscribeUserAccount(self.auid, self.guildAuid, self.server, self.uid, self.sendOK)
            return
        self.fin()

    def sendOK(self, acc, errMessage=None):
        self.acc = acc
        if self.acc.GuildData.GuildAuid == 0:
            if errMessage:
                info("GuildService: AcceptGuildAction error: %s", errMessage)
                self.response["error"] = errMessage
                self.response["ok"] = 0
            self.fin()
            return

        numMembers = len(self.acc.GuildData.Members)
        maxMembers = self.I.SD.getGuildMembersLimitByExp(self.acc.GuildData.GuildLevelInfo.Experience, self.I)

        # Проверка, что игрок уже в гильдии PF-75123
        for gmId in acc.GuildData.Members.keys():
            member = acc.GuildData.getGuildMemberByID(gmId)
            if member.Person == self.acc.auid:
                warn("GuildService: AcceptGuildAction guild(auid=%r) member(auid=%r) already in", self.acc.GuildData.GuildAuid, self.acc.auid)
                self.I.WS.updateGuildShortName(self.acc.auid, self.acc.GuildData.GuildInfo.ShortName)
                self.I.CHAT.addUserGroup(self.acc.auid, getGuildChatName(self.acc.guildAuid), self.I.WS.onGuildChatRegister)

                changes = [MakeModelChangeString("init_guild", "/", "init", self.acc.GuildData.generateJsonDict())]
                siegechanges = [MakeModelChangeString("init_siege", "/", "init", self.acc.SiegeData.generateJsonDict())]
                if member.IsOfficer:
                    self.I.WS.broadcastRecruitsChanges(self.acc.GuildData, [self.acc.auid])
                self.I.WS.saveGuildData(self.acc, None)
                self.response["GuildData"] = changes
                self.response["SiegeData"] = siegechanges
                self.response["ok"] = 1
                self.fin()
                return

        if numMembers >= maxMembers:
            warn("GuildService: AcceptGuildAction guild(auid=%r) overcrowded: %d/%d, guild exp = %r", self.acc.GuildData.GuildAuid, numMembers, maxMembers, self.acc.GuildData.GuildLevelInfo.Experience)
            self.response["ok"] = 0
            self.response["error"] = "Can not accept - guild(auid=%r) overcrowded(%r/%r), exp(%r)" % (
            self.acc.GuildData.GuildAuid, numMembers, maxMembers, self.acc.GuildData.GuildLevelInfo.Experience)
            self.response["ec"] = EC.GUILD_OVERCROWDED
            self.I.WS.resetPendingChanges(self.acc)
            self.acc.GuildData = GuildData()
            self.acc.GuildData.init(None)
            self.acc.SiegeData = SiegeData()
            self.acc.SiegeData.init(None)
            changes = [MakeModelChangeString("init_guild", "/", "init", self.acc.GuildData.generateJsonDict())]
            siegechanges = [MakeModelChangeString("init_siege", "/", "init", self.acc.SiegeData.generateJsonDict())]
            self.response["GuildData"] = changes
            self.response["SiegeData"] = siegechanges
            self.fin()

            return

        self.I.WS.resetPendingChanges(self.acc)
        self.acc.GuildData.write(self.acc.pending)
        member, id = self.acc.GuildData.newGuildMember()
        member.Person = self.acc.auid
        member.IsOfficer = False
        member.JoinTime = int(time.time())
        defRating = self.I.Config.getMainConfig().GUILD_DEFAULT_RATING

        member.AddedTalentsDailyCount = self.I.Config.getMainConfig().GuildBankSettings.GUILD_BANK_ADD_LIMIT
        member.TakenTalentsDailyCount = self.I.Config.getMainConfig().GuildBankSettings.GUILD_BANK_TAKE_LIMIT

        member.DailyRating = defRating
        member.EventRating = defRating

        for idx in xrange(0, getNumberOfDays()):
            memberRatingInfo, memberRatingInfo_id = self.acc.GuildData.newMemberDayRating()
            memberRatingInfo.HeroRating = defRating
            memberRatingInfo.Hero = 0
            member.HeroRatings.add(idx, memberRatingInfo)

        self.acc.GuildData.Members.add(member)
        changes = self.I.WS.pickPendingChanges(self.acc)
        self.I.WS.sendBroadCast(self.acc, changes, [], '')
        self.I.WS.updateGuildShortName(self.acc.auid, self.acc.GuildData.GuildInfo.ShortName)
        for gmId in self.acc.GuildData.Members.keys():
            mem = self.acc.GuildData.getGuildMemberByID(gmId)
            if mem.Person != self.acc.auid:
                self.I.FRIENDS.addSnFriend(self.acc.auid, mem.Person, 'pwg', None)

        self.I.CHAT.addUserGroup(self.acc.auid, getGuildChatName(self.acc.guildAuid), self.I.WS.onGuildChatRegister)

        changes = [MakeModelChangeString("init_guild", "/", "init", self.acc.GuildData.generateJsonDict())]
        siegechanges = [MakeModelChangeString("init_siege", "/", "init", self.acc.SiegeData.generateJsonDict())]
        self.I.WS.saveGuildData(self.acc, None)
        self.response["GuildData"] = changes
        self.response["SiegeData"] = siegechanges
        self.response["ok"] = 1
        self.fin()
        return


class SubscribeGSAction(SubAction):
    action = "subscribe"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: SubscribeGSAction")
        if (self.checkValidIntParam("auid")
            and self.checkValidIntParam("uid")
            and self.checkValidIntParam("server")
            and self.checkValidParam("snid")
            and self.checkValidParam("snuid")
            and self.checkValidIntParam("guildAuid")
            and self.checkValidIntParam("oldAuid")):
            self.locale = self.getParam("locale", "")
            self.oldAuid = self.getIntParam("oldAuid", 0)
            self.I.WS.subscribeUserAccount(self.auid, self.guildAuid, self.server, self.uid, self.sendOK)
            return

        self.fin()

    def sendOK(self, acc, errMessage=None):
        self.acc = acc
        if self.acc.GuildData.GuildAuid == 0 and errMessage:
            info("GuildService: SubscribeGSAction error: %s", errMessage)
            self.response["error"] = errMessage
            self.response["ok"] = 0
            self.fin()
            return


        self.acc.guildAuid = self.acc.GuildData.GuildAuid

        isFind = False

        for gmId in self.acc.GuildData.Members.keys():
            member = self.acc.GuildData.getGuildMemberByID(gmId)
            if self.oldAuid: # PF-98072 нас акк был размережен, клан остался в акке со старым auid пытаемся
                             # подправить мембера
                if member.Person == self.oldAuid:
                    acc.GuildData.write(acc.pending)
                    debug(" SubscribeGSAction change old auid from %s to %s", self.oldAuid, self.acc.auid )
                    member.Person = self.acc.auid
                    isFind = True
                    self.I.FRIENDS.deleteSnFriends(self.oldAuid,  'pwg', None)
                    self.I.FRIENDS.addSnFriend(acc.GuildData.Owner.Person, member.Person, 'pwg', None)
                    changes = self.I.WS.pickPendingChanges(acc)
                    self.I.WS.sendBroadCast(acc, changes, [], '')
                    self.I.WS.saveGuildData(acc, None)
                    break
                elif member.Person == self.acc.auid:
                    isFind = True
                    break
            elif member.Person == self.acc.auid:
                isFind = True
                break
        changes = [MakeModelChangeString("init_guild", "/", "init", self.acc.GuildData.generateJsonDict())]
        siegeChanges = [MakeModelChangeString("init_siege", "/", "init", self.acc.SiegeData.generateJsonDict())]
        if not isFind:
            self.acc.guildAuid = 0
            self.acc.GuildData = GuildData()
            self.acc.GuildData.init(None)
            self.acc.SiegeData = SiegeData()
            self.acc.SiegeData.init(None)
            self.response["GuildData"] = [
                MakeModelChangeString("init_guild", "/", "init", self.acc.GuildData.generateJsonDict())]
            self.response["SiegeData"] = [
                MakeModelChangeString("init_siege", "/", "init", self.acc.SiegeData.generateJsonDict())]
        else:
            self.response["GuildData"] = changes
            self.response["SiegeData"] = siegeChanges
            # Рядовым можно и не посылать ничего
            member = acc.GuildData.findMemberByAuid(acc.auid)
            if member.IsOfficer:
                self.I.WS.broadcastRecruitsChanges(self.acc.GuildData, [self.acc.auid])

        # self.I.WS.resetChat( self.acc.auid, self.acc.GuildData.GuildInfo.ShortName )
        # - isn't required since GuildService.updateGuildShortName() calls it before return
        self.I.WS.updateGuildShortName(self.acc.auid, self.acc.GuildData.GuildInfo.ShortName)
        self.response["guildAuid"] = self.acc.guildAuid
        self.response["ok"] = 1
        self.fin()
        return


class UnsubscribeGSAction(SubAction):
    action = "unsubscribe"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: UnsubscribeGSAction")
        if self.checkValidIntParam("auid"):
            if self.checkValidIntParam("guildAuid"):
                self.I.WS.unsubscribeUserAccount(self.auid, self.guildAuid)
                self.response["ok"] = 1
        self.fin()


class PromoteGuildAction(SubAction):
    action = "promote_guild"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: PromoteGuildAction")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("personAuid"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                if acc.GuildData.Owner.Person != acc.auid:
                    self.response["error"] = "Can not promote: you are not owner"
                else:
                    member = acc.GuildData.findMemberByAuid(self.personAuid)
                    if member:
                        acc.GuildData.write(acc.pending)
                        member.IsOfficer = True
                        self.I.WS.broadcastRecruitsChanges(self.acc.GuildData, [member.Person])
                        changes = self.I.WS.pickPendingChanges(acc)
                        self.I.WS.sendBroadCast(acc, changes, [], '')
                        self.I.WS.saveGuildData(acc, None)
                        self.response["GuildData"] = changes.get("guild_data", [])
                        self.response["ok"] = 1
                    else:
                        self.response["error"] = "Can not promote: can not find member with auid=%r" % self.personAuid
            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
        self.fin()


class DemoteGuildAction(SubAction):
    action = "demote_guild"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: DemoteGuildAction")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("personAuid"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                if acc.GuildData.Owner.Person != acc.auid:
                    self.response["error"] = "Can not demote: you are not owner"
                else:
                    member = acc.GuildData.findMemberByAuid(self.personAuid)
                    if member:
                        acc.GuildData.write(acc.pending)
                        member.IsOfficer = False
                        changes = self.I.WS.pickPendingChanges(acc)
                        self.I.WS.sendBroadCast(acc, changes, [], '')
                        self.I.WS.saveGuildData(acc, None)
                        self.response["GuildData"] = changes.get("guild_data", [])
                        self.response["ok"] = 1
                    else:
                        self.response["error"] = "Can not demote: can not find member with auid=%r" % self.personAuid
            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
        self.fin()


class InvestInGuildAction(SubAction):
    action = "invest_in_guild"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: InvestInGuildAction")
        if self.checkValidIntParam("auid"):
            if self.checkValidIntParam("amount"):
                acc = self.I.WS.getUserAcc(self.auid)
                if acc:
                    if self.I.SD.getLeftToCapForGuild(acc.GuildData.GuildLevelInfo.Experience) >= self.amount:

                        self.I.WS.resetPendingChanges(acc)

                        acc.GuildData.write(acc.pending)
                        acc.GuildData.GuildLevelInfo.Experience += self.amount
                        member = acc.GuildData.findMemberByAuid(self.auid)
                        member.InvestedResources += self.amount

                        event = acc.GuildData.newGuildInvestEvent()[0]
                        event.auid = self.auid
                        event.timestamp = int(time.time())
                        event.amount = self.amount

                        maxLogSize = self.I.Config.getMainConfig().GUILD_MAX_LOG_SIZE
                        logSize = len(acc.GuildData.InvestStatistics)

                        acc.GuildData.InvestStatistics.add(event)
                        if logSize >= maxLogSize:
                            minTime = int(time.time())
                            minEvent = None
                            for eventId in acc.GuildData.InvestStatistics:
                                checkEvent = acc.GuildData.getGuildInvestEventByID(eventId)
                                if checkEvent and checkEvent.timestamp < minTime:
                                    minTime = checkEvent.timestamp
                                    minEvent = checkEvent

                            acc.GuildData.InvestStatistics.remove(minEvent)

                        acc.GuildData.GuildInfo.AdditionalMembersCount = self.I.SD.getGuildMembersBonus(self.I.SD.getGuildLevel(acc.GuildData.GuildLevelInfo.Experience))

                        changes = self.I.WS.pickPendingChanges(acc)
                        self.I.WS.sendBroadCast(acc, changes, [], '')
                        self.I.WS.saveGuildData(acc, None)
                        self.response["GuildData"] = changes.get("guild_data", [])
                        self.response["ok"] = 1
                    else:
                        self.response["error"] = "Guild level experience limit will be reached"
                        self.response["ok"] = 0
                else:
                    err("GuildService: can not find acc by auid=%r" % self.auid)
        self.fin()


class ChangeGuildOwnerAction(SubAction):
    action = "change_guild_owner"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: ChangeGuildOwnerAction")
        if self.checkValidIntParam("auid"):
            if self.checkValidIntParam("personAuid"):
                acc = self.I.WS.getUserAcc(self.auid)
                if acc:
                    if acc.GuildData.Owner.Person != acc.auid:
                        self.response["error"] = "Can not change owner: you are not owner"
                    else:
                        member = acc.GuildData.findMemberByAuid(self.personAuid)
                        if member:
                            self.I.WS.resetPendingChanges(acc)
                            acc.GuildData.write(acc.pending)
                            oldOwner = acc.GuildData.findMemberByAuid(acc.GuildData.Owner.Person)
                            oldOwner.IsOfficer = False

                            member.IsOfficer = True
                            acc.GuildData.Owner = member
                            changes = self.I.WS.pickPendingChanges(acc)
                            self.I.WS.sendBroadCast(acc, changes, [], '')
                            self.I.WS.saveGuildData(acc, None)
                            self.response["GuildData"] = changes.get("guild_data", [])
                            self.response["ok"] = 1
                        else:
                            self.response[
                                "error"] = "Can not change owner: can not find member with auid=%r" % self.personAuid
                else:
                    err("GuildService: can not find acc by auid=%r" % self.auid)
        self.fin()


class MessageGuildAction(SubAction):
    action = "msg_guild"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: MessageGuildAction")
        if self.checkValidIntParam("auid"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                canInvite = self.I.WS.canInvite(acc)

                if canInvite:
                    acc.GuildData.write(acc.pending)
                    acc.GuildData.GuildInfo.MessageOfTheDay = urllib.unquote(self.getParam("message", ""))
                    changes = self.I.WS.pickPendingChanges(acc)
                    self.I.WS.sendBroadCast(acc, changes, [], '')
                    self.I.WS.saveGuildData(acc, None)
                    self.response["GuildData"] = changes.get("guild_data", [])
                    self.response["ok"] = 1
                else:
                    self.response["error"] = "Can not change message of guild: you are not guild leader/officer"
                    self.response["ok"] = 0
            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
        self.fin()


class HeroRatingAction(SubAction):
    action = "hero_rating"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: HeroRatingAction")
        if self.checkValidIntParam("auid"):
            if self.checkValidFloatParam("rating"):
                if self.checkValidIntParam("bestHero"):
                    if self.checkValidFloatParam("bestHeroRating"):
                        acc = self.I.WS.getUserAcc(self.auid)
                        if acc:
                            member = acc.GuildData.findMemberByAuid(self.auid)
                            if member:
                                if self.rating > member.HeroRatings[0].HeroRating:
                                    self.I.WS.resetPendingChanges(acc)
                                    acc.GuildData.write(acc.pending)
                                    member.HeroRatings[0].HeroRating = self.bestHeroRating
                                    member.HeroRatings[0].Hero = self.bestHero

                                    changes = self.I.WS.pickPendingChanges(acc)

                                    self.I.WS.sendBroadCast(acc, changes, [], '')
                                    self.I.WS.sendBroadCast(acc, changes, [acc.auid], '')
                                    self.I.WS.saveGuildData(acc, None)
                                self.response["ok"] = 1
                            else:
                                err("GuildService: can not find member by auid=%r" % self.auid)
                        else:
                            err("GuildService: can not find acc by auid=%r" % self.auid)
        self.fin()


class RecalcRatingAction(SubAction):
    action = "recalc_rating"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: RecalcRatingAction")
        if self.checkValidIntParam("guildAuid") and self.checkValidIntParam("gw_event_id"):
            self.fakeAcc = ClassDict(auid=CC.GUILD_NEUTRAL_AUID, GuildData=None, SiegeData=None, guildAuid=self.guildAuid)
            self.I.WS.loadGuildData(self.fakeAcc, self.recalc)
        else:
            self.fin()


    def recalc(self, acc, errMessage=None):
        info("GuildService: RecalcRatingAction  loadGuildData callback call guildAuid: {0}".format(self.guildAuid))
        if errMessage is not None:
            self.response["ok"] = 0
            self.response["error"] = errMessage
            self.fin()
            return

        self.I.WS.resetPendingChanges(self.fakeAcc)
        self.fakeAcc.GuildData.write(self.fakeAcc.pending)
        rating = 0

        # Если здесь свалимся, запорем работу всего рекалка, так что заботливо подстелим try-catch.
        try:
            self.I.WS.validateGuildTalents(self.fakeAcc.GuildData)
            self.I.WS.validateGuildBuffs(self.fakeAcc.GuildData)

            self.I.WS.validateGuildWarEventIndex(self.fakeAcc.GuildData, self.guildAuid, event_id=self.gw_event_id,
                                                 acc=self.fakeAcc, mirror=False)
            rating = self.I.WS.recalcGuildRating(self.fakeAcc.GuildData, 0)

            # PF-106691
            # self.I.WS.updateExVassalsAndLostSieges(self.fakeAcc.GuildData)
            #
            # debug("GuildService: RecalcRatingAction  Suzerain dump: {0}".format(self.fakeAcc.GuildData.GuildSuzerain))
            # if self.fakeAcc.GuildData.GuildSuzerain and self.fakeAcc.GuildData.GuildSuzerain.get():
            #     debug("GuildService: RecalcRatingAction ShortInfo dump {0}".format(self.fakeAcc.GuildData.GuildSuzerain.ShortInfo))
            #     if self.fakeAcc.GuildData.GuildSuzerain.ShortInfo and self.fakeAcc.GuildData.GuildSuzerain.ShortInfo.get() \
            #             and self.fakeAcc.GuildData.GuildSuzerain.ShortInfo.GuildAuid == 0:
            #         self.I.WS.resetAllShopItems(self.fakeAcc.GuildData)
        except Exception:
            catch()

        changes = self.I.WS.pickPendingChanges(self.fakeAcc)
        self.I.WS.sendBroadCast(self.fakeAcc, changes, [], '')

        if hasattr(self.fakeAcc.GuildData, 'GuildAuid') and self.fakeAcc.GuildData.GuildAuid == 0:
            msg = "RecalcRankAction: attempting to save zero guildAuid"
            warn(msg)
            self.response["ok"] = 0
            self.response["error"] = msg
            self.fin()
        else:
            self.I.WS.saveGuildData(self.fakeAcc, self.onSave, mirror=True)

        self.response["guildRating"] = rating

    def onSave(self, data_reply):
        debug("GuildService: persistent reply (value=%r)", data_reply.get("r") if data_reply else "empty reply from mongo db" )
        self.response["ok"] = 1
        self.fin()

    def fin(self):
        self.I.WS.tryUnloadGuild(self.guildAuid)
        super(RecalcRatingAction, self).fin()


class RecalcRankAction(SubAction):
    action = "recalc_rank"
    # -----------------------------------------
    @action_timing
    def onStart(self):

        if self.checkValidIntParam("guildAuid") and self.checkValidIntParam("guildRank"):
            debug("GuildService: RecalcRankAction guildAuid: {0}, guildRank: {1}".format(self.guildAuid, self.guildRank))
            self.fakeAcc = ClassDict(auid=CC.GUILD_NEUTRAL_AUID, GuildData=None, guildAuid=self.guildAuid, guildRank=self.guildRank)
            self.I.WS.loadGuildData(self.fakeAcc, self.set_rank)
        else:
            self.response["error"] = "GuildService RecalcRatingAction: Invalid guildAuid={0} or guildRank={1}".format(
                self.guildAuid, self.guildRank)
            self.response["ok"] = 0
            self.fin()

    def set_rank(self, acc, errMessage=None):
        info("GuildService: RecalcRankAction  loadGuildData callback call guildAuid: {0}, guildRank: {1}".format(
            self.guildAuid, self.guildRank))
        if errMessage is not None:
            self.response["ok"] = 0
            self.response["error"] = errMessage
            self.fin()
            return

        self.I.WS.resetPendingChanges(self.fakeAcc)
        self.fakeAcc.GuildData.write(self.fakeAcc.pending)
        self.fakeAcc.SiegeData.write(self.fakeAcc.pending)

        oldPlace = self.fakeAcc.GuildData.GuildInfo.Place
        self.fakeAcc.GuildData.GuildInfo.Place = self.guildRank + 1  # Установка места в рейтинге
        self.fakeAcc.GuildData.GuildInfo.PlaceChange = oldPlace - self.fakeAcc.GuildData.GuildInfo.Place

        if self.fakeAcc.GuildData.GuildInfo.BestPlace == 0 or self.fakeAcc.GuildData.GuildInfo.Place < self.fakeAcc.GuildData.GuildInfo.BestPlace:
            self.fakeAcc.GuildData.GuildInfo.BestPlace = self.fakeAcc.GuildData.GuildInfo.Place

        # PF-106691
        # self.I.WS.updateRatingForSiegeData(self.fakeAcc, self.fakeAcc.GuildData)

        self.addStatistics(self.fakeAcc.GuildData)

        changes = self.I.WS.pickPendingChanges(self.fakeAcc)
        self.I.WS.sendBroadCast(self.fakeAcc, changes, [], '')

        if hasattr(self.fakeAcc.GuildData, 'GuildAuid') and self.fakeAcc.GuildData.GuildAuid == 0:
            msg = "RecalcRankAction: attempting to save zero guildAuid"
            warn(msg)
            self.response["ok"] = 0
            self.response["error"] = msg
            self.fin()
        else:
            self.I.WS.saveGuildData(self.fakeAcc, self.onSave, mirror=True)

    def onSave(self, data_reply):
        debug("GuildService: persistent reply (value=%r)", data_reply.get("r") if data_reply else "empty reply from mongo db")
        self.response["ok"] = 1
        self.fin()

    def fin(self):
        self.I.WS.tryUnloadGuild(self.guildAuid)
        super(RecalcRankAction, self).fin()

    def addStatistics(self, GuildData):
        vassalsInfo = []
        recommVassalsInfo = []
        for vassalId, vassal in GuildData.GuildVassals.iteritems():
            vassalsInfo.append({"guildid": vassal.ShortInfo.GuildAuid, "guildpoints": vassal.DonationYesterday})
        for recommVassalId, recommVassal in GuildData.RecommendedForMapVassals.iteritems():
            recommVassalsInfo.append({"guildid": recommVassal.ShortInfo.GuildAuid, "guildrating": recommVassal.ShortInfo.Rating})

        Ratings = 0 # TODO: What to do with this?
        # Ratings = GuildData.RatingInfo.Ratings[1] if len(GuildData.RatingInfo.Ratings)>=2 else 0

        self.I.STATS.addGuildDailyStatsInfo(GuildData.GuildAuid, GuildData.RatingInfo.Rating, Ratings,
                                            GuildData.GuildInfo.CWPoints_Clan, GuildData.GuildInfo.Place,
                                            vassalsInfo, recommVassalsInfo)


class AddGuildTalentAction(SubAction):
    action = "add_guild_talent"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: AddGuildTalentAction")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("persistentId"):
            self.heroClassId = self.getIntParam("heroClassId", 0)
            self.points = self.getIntParam("points", 0)
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                member = acc.GuildData.findMemberByAuid(self.auid)

                if len(acc.GuildData.FreeTalents) < self.I.Config.getMainConfig().GuildBankSettings.INIT_GUILD_BANK_SLOTS:
                    if member.AddedTalentsDailyCount < self.I.Config.getMainConfig().GuildBankSettings.GUILD_BANK_ADD_LIMIT:
                        acc.GuildData.write(acc.pending)

                        talent, talent_id = acc.GuildData.newGuildTalent()
                        talent.Owner = member
                        talent.HeroClassId = self.heroClassId
                        talent.Points = self.points
                        talent.PersistentId = self.persistentId
                        acc.GuildData.FreeTalents.add(talent)
                        member.AddedTalentsDailyCount += 1
                        self.I.WS.logTalentEvent(acc.GuildData, TalentEventType.Put, self.auid, 0, self.persistentId)

                        changes = self.I.WS.pickPendingChanges(acc)
                        self.I.WS.sendBroadCast(acc, changes, [], '')
                        self.I.WS.saveGuildData(acc, None)
                        self.response["GuildData"] = changes.get("guild_data", [])
                        self.response["ok"] = 1
                    else:
                        self.response["error"] = "Can not add talent - day limit %r/%r" % ( member.AddedTalentsDailyCount, self.I.Config.getMainConfig().GuildBankSettings.GUILD_BANK_ADD_LIMIT )
                        self.response["ec"] = EC.GUILD_BANK_DAY_PUT_LIMIT_EXCEEDED
                        self.response["ok"] = 0
                else:
                    self.response["error"] = "Can not add talent - guild bank overcrowded %r/%r" % ( len(acc.GuildData.FreeTalents), self.I.Config.getMainConfig().GuildBankSettings.INIT_GUILD_BANK_SLOTS )
                    self.response["ec"] = EC.GUILD_BANK_OVERCROWDED
                    self.response["ok"] = 0
            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
                self.response["error"] = "GuildService: can not find acc by auid=%r" % self.auid
                self.response["ok"] = 0
        self.fin()


class TakeGuildTalentAction(SubAction):
    action = "take_guild_talent"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: TakeGuildTalentAction")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("talId"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                member = acc.GuildData.findMemberByAuid(self.auid)
                talent = acc.GuildData.getGuildTalentByID(self.talId)

                if talent:
                    if member.TakenTalentsDailyCount < self.I.Config.getMainConfig().GuildBankSettings.GUILD_BANK_TAKE_LIMIT or talent.Owner == member:
                        acc.GuildData.write(acc.pending)
                        if self.talId in acc.GuildData.FreeTalents:
                            if member == talent.Owner:
                                self.I.WS.logTalentEvent(acc.GuildData, TalentEventType.TakeMy, self.auid, 0,
                                                         talent.PersistentId)
                                talent.Owner = 0
                                acc.GuildData.FreeTalents.remove(talent)
                            else:
                                self.I.WS.logTalentEvent(acc.GuildData, TalentEventType.Take, self.auid,
                                                         talent.Owner.Person, talent.PersistentId)
                                talent.Holder = member
                                acc.GuildData.TakenTalents.add(talent)
                                acc.GuildData.FreeTalents.remove(talent)
                                # счётчик увеличиваем только если взят был чужой талант
                                member.TakenTalentsDailyCount += 1

                            changes = self.I.WS.pickPendingChanges(acc)
                            self.I.WS.sendBroadCast(acc, changes, [], '')
                            self.I.WS.saveGuildData(acc, None)
                            self.response["GuildData"] = changes.get("guild_data", [])
                            self.response["ok"] = 1
                            self.response["PersistentId"] = talent.PersistentId
                            self.response["Points"] = talent.Points
                            self.response["GuildBankInfo.HeroClassId"] = talent.HeroClassId
                            self.response["GuildBankInfo.GuildAuid"] = acc.GuildData.GuildAuid
                            self.response["GuildBankInfo.GuildTalentId"] = self.talId
                            if talent.Owner.get():
                                self.response["OwnerId"] = talent.Owner.Person
                            else:
                                self.response["OwnerId"] = member.Person
                        else:
                            err("TakeGuildTalentAction: talent with id=%r is already taken" % self.talId)
                            self.response["error"] = "TakeGuildTalentAction: talent with id=%r is already taken" % self.talId
                            self.response["ec"] = EC.GUILD_BANK_TALENT_IS_MISSING
                            self.response["ok"] = 0
                    else:
                        self.response["error"] = "Can not take talent - already %r/%r" % (member.TakenTalentsDailyCount,
                                                                                          self.I.Config.getMainConfig().GuildBankSettings.GUILD_BANK_TAKE_LIMIT )
                        self.response["ec"] = EC.GUILD_BANK_DAY_TAKE_LIMIT_EXCEEDED
                        self.response["ok"] = 0
                else:
                    err("TakeGuildTalentAction: can not find talent with id=%r" % self.talId)
                    self.response["error"] = "TakeGuildTalentAction: can not find talent with id=%r" % self.talId
                    self.response["ec"] = EC.GUILD_BANK_TALENT_IS_MISSING
                    self.response["ok"] = 0
            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
                self.response["error"] = "GuildService: can not find acc by auid=%r" % self.auid
                self.response["ok"] = 0
        self.fin()


class GiveBackGuildTalentAction(SubAction):
    action = "give_back_guild_talent"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: GiveBackGuildTalentAction")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("talId"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                member = acc.GuildData.findMemberByAuid(self.auid)

                acc.GuildData.write(acc.pending)
                if self.I.WS.canInvite(acc):
                    talent = acc.GuildData.getGuildTalentByID(self.talId)
                    if talent and self.talId in acc.GuildData.FreeTalents:
                        self.acc = acc
                        self.talent = talent
                        callback = functools.partial(self.onAddGuildTalent, GuildData=acc.GuildData)
                        self.I.WS.createMailAddGuildTalent(talent.Owner.Person, talent.PersistentId, talent.HeroClassId,
                                                           talent.Points, acc.GuildData, callback=callback)
                        self.I.STATS.addTalentChange(talent.Owner.Person,
                                                     TalentInfo(talent.PersistentId, self.talId, talent.HeroClassId),
                                                     TalentChangeOperation.TakeBackFromBank)
                        return
                    else:
                        err("GiveBackGuildTalentAction: can not find talent with id=%r" % self.talId)
                        self.response["error"] = "GiveBackGuildTalentAction: can not find talent with id=%r" % self.talId
                        self.response["ec"] = EC.GUILD_BANK_TALENT_IS_MISSING
                        self.response["ok"] = 0
                else:
                    err("GiveBackGuildTalentAction: non-officer member can't give back talents, tal_id=%r" % self.talId)
                    self.response[
                        "error"] = "GiveBackGuildTalentAction: non-officer member can't give back talents, tal_id=%r" % self.talId
                    self.response["ec"] = EC.GUILD_BANK_CANNOT_GIVE_BACK_TALENT
                    self.response["ok"] = 0
            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
                self.response["error"] = "GuildService: can not find acc by auid=%r" % self.auid
                self.response["ok"] = 0
        self.fin()

    def onAddGuildTalent(self, response, GuildData=None):
        info('GiveBackGuildTalentAction::onAddGuildTalent (response=%r)', response)
        if response.get('ok', 0) == 1 and response.get('ec', -1) == 0:
            acc = self.acc
            talent = self.talent

            self.I.WS.logTalentEvent(acc.GuildData, TalentEventType.GiveBack, self.auid, talent.Owner.Person,
                                     talent.PersistentId)
            talent.Owner = 0
            talent.Holder = 0
            acc.GuildData.FreeTalents.remove(talent)
            changes = self.I.WS.pickPendingChanges(acc)
            self.I.WS.sendBroadCast(acc, changes, [], '')
            self.I.WS.saveGuildData(acc, None)
            self.response["GuildData"] = changes.get("guild_data", [])
            self.response["ok"] = 1
        else:
            err("GuildService: can't send GiveBack message to exchange (auid=%r)", self.auid)
            self.response["error"] = "GuildService: can't send GiveBack message to exchange (auid=%r)" % self.auid
            self.response["ok"] = 0
            self.I.WS.resetMailTickers(GuildData)
        self.fin()


class ReturnGuildTalentAction(SubAction):
    action = "return_guild_talent"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: ReturnGuildTalentAction")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("talId"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                member = acc.GuildData.findMemberByAuid(self.auid)
                if member.AddedTalentsDailyCount < self.I.Config.getMainConfig().GuildBankSettings.GUILD_BANK_ADD_LIMIT:
                    acc.GuildData.write(acc.pending)

                    talent = acc.GuildData.getGuildTalentByID(self.talId)
                    if talent:
                        if self.talId in acc.GuildData.TakenTalents:
                            if talent.Holder == member:
                                self.I.WS.logTalentEvent(acc.GuildData, TalentEventType.Return, self.auid,
                                                         talent.Owner.Person, talent.PersistentId)
                                talent.Holder = 0
                                acc.GuildData.FreeTalents.add(talent)
                                acc.GuildData.TakenTalents.remove(talent)
                                member.AddedTalentsDailyCount += 1
                                changes = self.I.WS.pickPendingChanges(acc)
                                self.I.WS.sendBroadCast(acc, changes, [], '')
                                self.I.WS.saveGuildData(acc, None)
                                self.response["GuildData"] = changes.get("guild_data", [])
                                self.response["ok"] = 1
                            else:
                                err("ReturnGuildTalentAction: can not return stranger talent with id=%r" % self.talId)
                                self.response["error"] = "ReturnGuildTalentAction: can not return stranger talent with id=%r" % self.talId
                                self.response["ok"] = 0
                        else:
                            err("ReturnGuildTalentAction: can not find taken talent with id=%r" % self.talId)
                            self.response["error"] = "ReturnGuildTalentAction: can not find taken talent with id=%r" % self.talId
                            self.response["ec"] = EC.GUILD_BANK_TALENT_IS_MISSING
                            self.response["ok"] = 0
                    else:
                        err("ReturnGuildTalentAction: can not find talent with id=%r" % self.talId)
                        self.response["error"] = "ReturnGuildTalentAction: can not find talent with id=%r" % self.talId
                        self.response["ec"] = EC.GUILD_BANK_TALENT_IS_MISSING
                        self.response["ok"] = 0
                else:
                    self.response["error"] = "Can not add talent - day limit %r/%r" % (member.AddedTalentsDailyCount,
                                                                                       self.I.Config.getMainConfig().GuildBankSettings.GUILD_BANK_ADD_LIMIT )
                    self.response["ec"] = EC.GUILD_BANK_DAY_PUT_LIMIT_EXCEEDED
                    self.response["ok"] = 0
            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
                self.response["error"] = "GuildService: can not find acc by auid=%r" % self.auid
                self.response["ok"] = 0
        self.fin()


class UpdateBankTalentInfo(SubAction):
    action = "guild_talent_info_update"

    """ Обновляем параметры гильзийского таланта, если его кто-то заточил или отвязал/привязал """

    @action_timing
    def onStart(self):
        info("GuildService: UpdateBankTalentInfo")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("guildTalId"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                member = acc.GuildData.findMemberByAuid(self.auid)
                acc.GuildData.write(acc.pending)

                guildTalent = acc.GuildData.getGuildTalentByID(self.guildTalId)
                if guildTalent:
                    if self.guildTalId in acc.GuildData.TakenTalents:
                        guildTalent.Points = self.getIntParam("points", 0)
                        guildTalent.HeroClassId = self.getIntParam("heroClassId", 0)

                        changes = self.I.WS.pickPendingChanges(acc)
                        self.I.WS.sendBroadCast(acc, changes, [], '')
                        self.I.WS.saveGuildData(acc, None)
                        self.response["GuildData"] = changes.get("guild_data", [])
                        self.response["ok"] = 1
                    else:
                        self.response[
                            "error"] = "UpdateBankTalentInfo: can not find taken talent with id=%r" % self.guildTalId
                        err(self.response["error"])
                        self.response["ok"] = 0
                else:
                    self.response["error"] = "UpdateBankTalentInfo: can not find talent with id=%r" % self.guildTalId
                    err(self.response["error"])
                    self.response["ok"] = 0
            else:
                self.response["error"] = "GuildService: can not find acc by auid=%r" % self.auid
                err(self.response["error"])
                self.response["ok"] = 0
        self.fin()


class BuyGuildShopItemAction(SubAction):
    action = "buy_guild_shop_item"

    """ Покупаем что-то в гильдийском магазине и рассылаем достойным """

    @action_timing
    def onStart(self):
        info("GuildService: BuyGuildShopItemAction")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("guildShopItemId"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                acc.GuildData.write(acc.pending)
                # А есть ли у нас вообще такой товар?
                if self.guildShopItemId in self.I.Config.getMainConfig().GUILD_SHOP_ITEMS:
                    staticItem = self.I.SD.getGuildShopItemById(self.guildShopItemId)
                    if staticItem:
                        # Проверим, есть ли айтемы в наличии и есть ли у нас право их покупать
                        if not self.canBuy(str(self.guildShopItemId), acc, staticItem):
                            self.response["ok"] = 0
                            self.fin()
                            return

                        if str(self.guildShopItemId) in acc.GuildData.GuildShopItems:
                            acc.GuildData.GuildShopItems[str(self.guildShopItemId)] -= 1
                        # Если тип товара бонус, надо раздать людям
                        self.response["AffectOnBuyer"] = False
                        if staticItem['classType'] == 'OneTimeGuildShopItem' or staticItem['classType'] == 'SiegePointsBonus':
                            duration = int(time.time()) + int(staticItem['guildBuff']['duration'])
                            affectedMembers, holdGuild = acc.GuildData.getAffectedMembersList(self.auid,
                                                                                   self.I.WS.activeGuildUsers[acc.GuildData.GuildAuid],
                                                                                   staticItem)
                            debug("BuyGuildShopItemAction Buff %r", staticItem['guildBuff']['persistentId'])
                            debug("BuyGuildShopItemAction affectedMembers %r", affectedMembers)
                            if len(affectedMembers) != len(acc.GuildData.Members) and len(affectedMembers) != 1:
                                acc.GuildData.ActiveBuffs[str(crc32(staticItem['guildBuff']['persistentId']))] = duration

                            if holdGuild:
                                acc.GuildData.ActiveHoldGuildBuffs[str(crc32(staticItem['guildBuff']['persistentId']))] = duration

                            try:
                                affectedMembers.remove(self.auid)
                                self.response["AffectOnBuyer"] = True
                            except ValueError:
                                pass

                            for memberAuid in affectedMembers:
                                callback = functools.partial(self.onAddGuildBuf, GuildData=acc.GuildData)
                                self.I.WS.createMailAddGuildBuf(memberAuid, self.guildShopItemId, duration,
                                                                acc.GuildData, callback=callback)

                        changes = self.I.WS.pickPendingChanges(acc)
                        self.I.WS.sendBroadCast(acc, changes, [], '')
                        self.I.WS.saveGuildData(acc, None)
                        self.response["GuildData"] = changes.get("guild_data", [])
                        self.response["ok"] = 1
                        self.fin()
                        return
                    else:
                        self.response["error"] = "BuyGuildShopItemAction: can not find static shop item with id=%r" % self.guildShopItemId
                else:
                    self.response[
                        "error"] = "BuyGuildShopItemAction: can not find shop item with id=%r" % self.guildShopItemId
            else:
                self.response["error"] = "GuildService: can not find acc by auid=%r" % self.auid

        err(self.response["error"])
        self.response["ok"] = 0
        self.fin()

    def canBuy(self, persistentId, acc, staticItem):
        # Проверим на уровень гильдии
        level = self.I.SD.getGuildShopLevel(acc.GuildData.getShopOwnerRating(), acc.GuildData.GuildInfo.HasUltimateShop)
        if level < int(staticItem['levelToUnlock']):
            self.response["error"] = "Can't buy shop item: shop level is too small"
            self.response["ec"] = EC.GUILD_SHOP_CANNOT_BUY_HIGH_LEVEL_ITEMS
            return False

        amount = self.I.SD.getAmountByExperienceLevel(staticItem, level)
        if persistentId in acc.GuildData.GuildShopItems or amount > 0:
            if persistentId not in acc.GuildData.GuildShopItems or acc.GuildData.GuildShopItems[persistentId] <= 0:
                self.response["error"] = "BuyGuildShopItemAction: Can't buy item - day limit exceeded"
                self.response["ec"] = EC.GUILD_SHOP_ITEM_DAY_LIMIT_EXCEEDED
                return False

        # Если покупаем только для гильдии - то за очки гильдии и только советником или главой
        if staticItem['price']['CWPoints_Clan'] != 0:
            if self.I.WS.canInvite(acc):
                # Хватает ли у гильдии денег на покупку?
                if acc.GuildData.GuildInfo.CWPoints_Clan >= staticItem['price']['CWPoints_Clan']:
                    acc.GuildData.GuildInfo.CWPoints_Clan -= staticItem['price']['CWPoints_Clan']
                    return True
                else:
                    self.response[
                        "error"] = "BuyGuildShopItemAction: not enough CWPoints_Clan, id=%r" % self.guildShopItemId
                    self.response["ec"] = EC.NOT_ENOUGH_RESOURCES
                    return False
            else:
                self.response[
                    "error"] = "BuyGuildShopItemAction: non-officer member can't buy guild only items, id=%r" % self.guildShopItemId
                self.response["ec"] = EC.GUILD_SHOP_CANNOT_BUY_GUILD_POINTS_ONLY_ITEM
                return False

        return True

    def _guildBuffCB(self, response, GuildData):
        if response is None:
            errStack("Response is None! Possible error in ther caller request.")
        elif response.get('ok', 0) == 1 and response.get('ec', -1) == 0:
            pass
        else:
            self.I.WS.resetMailTickers(GuildData)

    def onAddGuildBuf(self, response, GuildData=None):
        info('BuyGuildShopItemAction::onAddGuildBuf (response=%r)', response)
        self._guildBuffCB(response, GuildData)


# ---------------------------------- RECRUITMENT REQUESTS -------------------------------------

class RecruitmentLocaleAction(SubAction):
    action = "recruitment_locale"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: RecruitmentLocaleAction")
        if self.checkValidIntParam("auid"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                if self.I.WS.canInvite(acc):
                    acc.GuildData.write(acc.pending)
                    acc.GuildData.RecruitmentInfo.Locale = urllib.unquote(self.getParam("locale", ""))
                    self.I.EXPORT.updateGuildRecruitmentLocale(acc.GuildData.GuildAuid,
                                                            acc.GuildData.RecruitmentInfo.Locale)
                    changes = self.I.WS.pickPendingChanges(acc)
                    self.I.WS.sendBroadCast(acc, changes, [], '')
                    self.I.WS.saveGuildData(acc, None, False)
                    self.response["GuildData"] = changes.get("guild_data", [])
                    self.response["ok"] = 1
                else:
                    self.response["error"] = "Can not change guild locale: you are not guild leader/officer"
                    self.response["ok"] = 0
            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
        self.fin()


class RecruitmentMessageAction(SubAction):
    action = "recruitment_message"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: RecruitmentMessageAction")
        if self.checkValidIntParam("auid"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                if self.I.WS.canInvite(acc):
                    acc.GuildData.write(acc.pending)
                    acc.GuildData.RecruitmentInfo.Message = urllib.unquote(self.getParam("message", ""))
                    self.I.EXPORT.updateGuildRecruitmentMessage(acc.GuildData.GuildAuid,
                                                            acc.GuildData.RecruitmentInfo.Message)
                    changes = self.I.WS.pickPendingChanges(acc)
                    self.I.WS.sendBroadCast(acc, changes, [], '')
                    self.I.WS.saveGuildData(acc, None, False)
                    self.response["GuildData"] = changes.get("guild_data", [])
                    self.response["ok"] = 1
                else:
                    self.response["error"] = "Can't change recruitment message: you are not guild leader/officer"
                    self.response["ok"] = 0
            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
        self.fin()


class RecruitmentRatingAction(SubAction):
    action = "recruitment_rating"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: RecruitmentRatingAction")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("rating"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                if self.I.WS.canInvite(acc):
                    acc.GuildData.write(acc.pending)
                    acc.GuildData.RecruitmentInfo.MinRating = self.rating
                    self.I.EXPORT.updateGuildRecruitmentMinRating(acc.GuildData.GuildAuid,
                                        acc.GuildData.RecruitmentInfo.MinRating)
                    changes = self.I.WS.pickPendingChanges(acc)
                    self.I.WS.sendBroadCast(acc, changes, [], '')
                    self.I.WS.saveGuildData(acc, None, False)
                    self.response["GuildData"] = changes.get("guild_data", [])
                    self.response["ok"] = 1
                else:
                    self.response["error"] = "Can't change recruitment rating of guild: you are not guild leader/officer"
                    self.response["ok"] = 0
            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
        self.fin()


class GetRecruitsListAction(SubAction):
    action = "get_recruits_list"
    intParams = ("auid", "position", "sortCriteria", "order")
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: GetRecruitsListAction")
        if self.checkIntParams():
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                recruitsData = RecruitsData()
                recruitsData.init(None)
                requestLifetime = self.I.SD.data['GuildRecruitment']['guildRequestLifetime']

                #debug("GuildService: GetRecruitsListAction guild %s acc.RecruitRequests = %r", acc.GuildData.GuildAuid, acc.RecruitRequests)
                #debug("GuildService: GetRecruitsListAction self.I.WS.getRecruitData call result: %r", self.I.WS.getRecruitData(acc.GuildData.GuildAuid))
                if acc.RecruitRequests:
                    while len(acc.RecruitRequests) and acc.RecruitRequests[0]["created"] + requestLifetime < int(time.time()):
                        acc.RecruitRequests.pop(0)
                    sortedRequests = self.sortRequests(acc.RecruitRequests, self.sortCriteria, self.order)
                    requestsPerTime = self.I.Config.getMainConfig().GUILDS_IN_LIST_PER_REQUEST
                    # Смотрим, нужна ли следующая страница
                    if len(sortedRequests) > self.position:
                        if len(sortedRequests) > (self.position + requestsPerTime):
                            sortedRequests = sortedRequests[self.position:(self.position + requestsPerTime)]
                        else:
                            sortedRequests = sortedRequests[self.position:]
                    for recruitInfo in sortedRequests:
                        try:
                            recruitsData.addRecruit(recruitInfo, requestLifetime)
                        except Exception:
                            catch()

                changes = [MakeModelChangeString("init_recruitment_data", "/", "init", recruitsData.generateJsonDict())]
                self.I.DATA.remove(CC.PLAYER_GUILD_REQUESTS_DATA, CC.PLAYER_GUILD_REQUESTS_DATA,
                                   {"created": {"$lt": int(time.time() - requestLifetime)}},
                                   self.onExpriredRecruitsRemoved, params=None)
                self.response["RecruitsData"] = changes
                self.response["ok"] = 1
            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
        self.fin()


    def onExpriredRecruitsRemoved(self, response):
        if not response:
            err("GetRecruitsListAction: expired recruits removal failed")

    @staticmethod
    def sortRequests(recruitRequests, sortCriteria, order):
        if sortCriteria == GuildRecruitsSortCritera.Nickname:
            return sorted(recruitRequests, key=lambda x: x["nickname"], reverse=order)
        elif sortCriteria == GuildRecruitsSortCritera.CastleLevel:
            return sorted(recruitRequests, key=lambda x: x["fame"], reverse=order)
        elif sortCriteria == GuildRecruitsSortCritera.HeroRating:
            return sorted(recruitRequests, key=lambda x: x["max_rating"], reverse=order)
        elif sortCriteria == GuildRecruitsSortCritera.Date:
            return sorted(recruitRequests, key=lambda x: x["created"], reverse=order)

        return recruitRequests


class NewRecruitAction(SubAction):
    action = "new_recruit"
    intParams = ("auid", "guildAuid")

    @action_timing
    def onStart(self):
        if not self.checkIntParams():
            warn("NewRecruitAction.onStart BAD call: auid %s, guildAuid %s", self.auid, self.guildAuid)
            self.fin()
            return
        info("NewRecruitAction.onStart: from auid %s to guildAuid %s", self.auid, self.guildAuid)
        self.guild = self.I.WS.getGuildDataReadOnly(self.guildAuid)
        if self.guild:  # if it's not loaded - do nothing, it will update itself later
            self.I.DATA.find_one(CC.PLAYER_GUILD_REQUESTS_DATA, CC.PLAYER_GUILD_REQUESTS_DATA,
                    {"guild_auid": self.guildAuid, "pers_auid": self.auid}, self.onRecruitsInfoFound, params=None)

        self.response["ok"] = 1
        self.fin()

    def onRecruitsInfoFound(self, response):
        recruitInfo = None
        if response:
            try:
                recruitInfo = response["r"]
            except Exception:
                catch()
        else:
            err("NewRecruitAction: empty response from mongo for guild_auid %s, pers_auid %s", self.guildAuid, self.auid)
            return

        if recruitInfo:
            self.I.WS.registerNewRecruitData(self.guildAuid, recruitInfo)
            self.I.WS.broadcastRecruitsChanges(self.guild)
        else:
            err("NewRecruitAction: empty recruit data: %r", recruitInfo)


class RemoveRecruitAction(SubAction):
    action = "rm_recruit"
    intParams = ("auid", "guildAuid")

    @action_timing
    def onStart(self):
        if not self.checkIntParams():
            warn("RemoveRecruitAction.onStart BAD call: auid %s, guildAuid %s", self.auid, self.guildAuid)
            self.fin()
            return
        info("RemoveRecruitAction.onStart: auid %s, guildAuid %s", self.auid, self.guildAuid)
        WS = self.I.WS
        guild = WS.getGuildDataReadOnly(self.guildAuid)
        # if it's not loaded - do nothing, it will update itself later
        if guild and WS.unregisterRecruitData(self.guildAuid, self.auid):
            WS.broadcastRecruitsChanges(guild)


class RenameRecruitAction(SubAction):
    action = "rename_recruit"
    intParams = ("auid", "guildAuid")

    @action_timing
    def onStart(self):
        if not self.checkIntParams() or not self.checkValidParam("nick"):
            warn("RenameRecruitAction.onStart: BAD call: auid %s, nick '%r', guildAiud %s", self.auid, self.nick, self.guildAuid)
            self.fin()
            return
        info("RenameRecruitAction.onStart: auid %s, nick '%s', guildAuid %s", self.auid, self.nick, self.guildAuid)
        WS = self.I.WS
        guild = WS.getGuildDataReadOnly(self.guildAuid)
        if guild:
            for rd in WS.getRecruitData(self.guildAuid):
                if rd['pers_auid'] == self.auid:
                    rd['nickname'] = self.nick
                    debug("RenameRecruitAction: data updated: %s", rd)
                    WS.broadcastRecruitsChanges(guild)
                    break


class DeclineRecruitAction(SubAction):
    action = "decline_recruit"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: DeclineRecruitAction")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("recruitAuid"):
            self.acc = self.I.WS.getUserAcc(self.auid)
            if self.acc:
                self.I.WS.resetPendingChanges(self.acc)
                if self.I.WS.canInvite(self.acc):
                    if self.acc.RecruitRequests:
                        self.I.DATA.update(CC.PLAYER_GUILD_REQUESTS_DATA, CC.PLAYER_GUILD_REQUESTS_DATA,
                            {"guild_auid": self.acc.GuildData.GuildAuid, "pers_auid": self.recruitAuid}, {"status": 0},
                            self.onRecruitsInfoUpdated, params=None)
                        return
                    else:
                        self.errorResponse(EC.RECRUIT_NO_RECRUIT, "acc.RecruitRequests is empty")
                else:
                    self.errorResponse(EC.GUILD_ONLY_OFFICER_CAN_OPERATE, "Can't decline recruit: you are not guild leader/officer")
            else:
                mess = "GuildService: can not find acc by auid=%r" % self.auid
                self.errorResponse(EC.BAD_PARAM, mess)
        else:
            mess = "Bad param (auid or recruitAuid) for DeclineRecruitAction "
            self.errorResponse(EC.BAD_PARAM, mess)

    def onRecruitsInfoUpdated(self, response):
        if response["r"]:
            itemToRemove= None
            for request in self.acc.RecruitRequests:
                if request["pers_auid"] == self.recruitAuid:
                    itemToRemove = request
            if itemToRemove:
                self.acc.RecruitRequests.remove(itemToRemove)
                self.I.WS.createMailRejectedApplication(self.acc.GuildData.GuildAuid, self.acc.GuildData, self.recruitAuid)
                self.I.WS.broadcastRecruitsChanges(self.acc.GuildData)
                self.response["ok"] = 1
                self.fin()
            else:
                self.errorResponse(EC.RECRUIT_NO_RECRUIT, "Can't find recruit application on guild_service")
        else:
            self.errorResponse( EC.BAD_PARAM, "GuildService: can not remove request from acc by auid=%r" % self.recruitAuid)


class ChangeMemberRatingAction(SubAction):
    action = "change_member_rating"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService:  ChangeMemberRatingAction")
        if self.checkValidIntParam("auid") and self.checkValidFloatParam("rating"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                member = acc.GuildData.findMemberByAuid(self.auid)
                if member:
                    self.I.WS.resetPendingChanges(acc)
                    acc.GuildData.write(acc.pending)
                    rating_delta = self.rating
                    member.DailyRating += rating_delta
                    member.EventRating += rating_delta

                    limit = int(self.I.SD.data["ClanWarsData"]["numPlayersFromTopInClanRating"])
                    top_members_sum_rating, topchiki = acc.GuildData.getTopMembersList(limit)

                    if member.Person in topchiki:
                        acc.GuildData.RatingInfo.DailyRating += rating_delta
                    #     acc.GuildData.RatingInfo.Rating += rating_delta

                    acc.GuildData.RatingInfo.Rating = top_members_sum_rating

                    changes = self.I.WS.pickPendingChanges(acc)

                    self.I.WS.sendBroadCast(acc, changes, [], '')
                    self.I.WS.saveGuildData(acc, None)
                    self.response["GuildData"] = changes.get("guild_data", [])
                    self.response["ok"] = 1
                else:
                    err("GuildService: can not find member by auid=%r" % self.auid)
            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
        self.fin()


class CheckGMLockAction(SubAction):
    action = "check_gm_lock"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService:  CheckGMLockAction")
        if self.checkValidIntParam("targetAuid"):
            self.I.WS.loadGuildDataByGuildAuid(self.targetAuid, self.onGuildDataLoaded)
        else:
            self.fin()

    def onGuildDataLoaded(self, response):
        info("GuildService.CheckGMLockAction.onGuildDataLoaded response: %r " % response)
        if response:
            try:
                data_json = response["r"]["data"] or '{"GuildData":{}}'
                #FIXME т.е. случай "клан не найден" мы тут тупо никак не обрабатываем! нет и нет, ok=1
                GData = json_loads(data_json)
                # Проверим на лок от ГМа
                if pathFind(GData, "GuildData/GuildInfo/GuildInfo/GMLockTime") > int(time.time()):
                    self.response["error"] = "Guild is locked by GM"
                    self.response["ec"] = EC.GUILD_IS_LOCKED_BY_GM
                    self.response["ok"] = 0
                    self.fin()
                    return
            except Exception:
                catch()

        self.response["ok"] = 1
        self.fin()

# ------------- DEBUG ACTIONS -------------- #


class GuildBankLimitsResetAction(SubAction):
    action = "guild_bank_limits_reset"
    debug = True
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: GuildBankLimitsResetAction")
        if self.checkValidIntParam("auid"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                member = acc.GuildData.findMemberByAuid(self.auid)

                acc.GuildData.write(acc.pending)
                member.AddedTalentsDailyCount = 0
                member.TakenTalentsDailyCount = 0
                member.JoinTime = int(time.time()) - 25 * 60 * 60

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


class GuildCWPointsSellAction(SubAction):
    action = "guild_cwpoints_sell"
    debug = True
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: GuildCWPointsSellAction")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("cwPoints"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                acc.GuildData.write(acc.pending)

                valueAdd = self.cwPoints
                newValue = acc.GuildData.GuildInfo.CWPoints_Clan + valueAdd
                if type(newValue) is long: # is shouldn't be SO BIG! PF-94129
                    warn("GuildCWPointsSellAction: CWPoints_Clan becomes is too big: %s! It should fit int32 limits.", newValue)
                    newValue = 0x7FFFFFFF if newValue > 0 else (-0x7FFFFFFF-1)
                else:
                    if valueAdd < 0 and newValue < 0:
                        newValue = 0

                acc.GuildData.GuildInfo.CWPoints_Clan = newValue

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


class SetGuildExperience(SubAction):
    action = "set_guild_experience"
    debug = True

    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: SetGuildExperience")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("value"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                acc.GuildData.write(acc.pending)

                if type(self.value) is long:
                    warn("SetGuildExperience: value is too big: %s! It should fit int32 limits.", self.value)
                    self.value = 0x7FFFFFFF if self.value > 0 else (-0x7FFFFFFF-1)
                self.I.WS.setGuildRating(acc, self.value)

                changes = self.I.WS.pickPendingChanges(acc)
                self.I.WS.sendBroadCast(acc, changes, [], '')
                self.I.WS.saveGuildData(acc, None)
                self.I.WS.notifyVassalsAndSuzerain(acc.GuildData)
                self.response["GuildData"] = changes.get("guild_data", [])
                self.response["ok"] = 1
            else:
                err("GuildService: can not find acc by auid=%r" % self.auid)
                self.response["error"] = "GuildService: can not find acc by auid=%r" % self.auid
                self.response["ok"] = 0

        self.fin()


class SetGuildTodayRating(SubAction):
    action = "set_guild_today_rating"
    debug = True

    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("GuildService: SetGuildTodayRating")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("value"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                acc.GuildData.write(acc.pending)

                acc.GuildData.RatingInfo.DailyRating = self.value

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


class ResetGuildShopLimits(SubAction):
    action = "reset_guild_shop_limits"
    debug = True

    @action_timing
    def onStart(self):
        info("GuildService: ResetGuildShopLimits")
        if self.checkValidIntParam("auid"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                acc.GuildData.write(acc.pending)

                self.I.WS.resetAllShopItems(acc.GuildData)
                for buffId in acc.GuildData.ActiveBuffs.keys():
                    del acc.GuildData.ActiveBuffs[buffId]

                for buffId in acc.GuildData.ActiveHoldGuildBuffs.keys():
                    del acc.GuildData.ActiveHoldGuildBuffs[buffId]

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


class UpdateRecruitApplicationAction(SubAction):
    action = "update_recruit_application"
    debug = True
    intParams = ("auid", "guildAuid", "created")

    @action_timing
    def onStart(self):
        if not self.checkIntParams():
            warn("UpdateRecruitApplicationAction.onStart BAD call: auid %s, guildAuid %s", self.auid, self.guildAuid)
            self.fin()
            return
        info("UpdateRecruitApplicationAction.onStart: auid %s, guildAuid %s", self.auid, self.guildAuid)
        guild = self.I.WS.getGuildDataReadOnly(self.guildAuid)
        # if it's not loaded - do nothing, it will update itself later
        if guild:
            recruits = self.I.WS.getRecruitData(self.guildAuid)
            request = self.I.WS.findReq(recruits, self.auid)
            if request:
                request["created"] = self.created
                self.I.WS.broadcastRecruitsChanges(guild)

        self.response["ok"] = 1
        self.fin()


class AddActiveBuffAction(SubAction):
    action = "add_active_buff"
    debug = True

    @action_timing
    def onStart(self):
        info("UpdateRecruitApplicationAction.onStart")
        if self.checkValidIntParam("auid") and self.checkValidParam("buffId"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                acc.GuildData.write(acc.pending)

                staticItem = self.I.SD.getGuildShopItemById(crc32(self.buffId))
                duration = int(time.time()) + int(staticItem['guildBuff']['duration'])
                acc.GuildData.ActiveBuffs[str(crc32(staticItem['guildBuff']['persistentId']))] = duration

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


class AcceptRecruitAction(SubAction):
    action = "accept_recruit"

    @action_timing
    def onStart(self):
        info("GuildService: AcceptRecruitAction")
        if self.checkValidIntParam("auid") and self.checkValidIntParam("guildAuid") and self.checkValidIntParam("recruit_auid"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.I.WS.resetPendingChanges(acc)
                acc.GuildData.write(acc.pending)
                member = acc.GuildData.findMemberByAuid(self.auid)
                if member and not member.IsOfficer:
                    self.errorResponse(EC.GUILD_ONLY_OFFICER_CAN_OPERATE, "You(%r) are not officer!" % self.auid)
                    return

                numMembers = len(acc.GuildData.Members)
                maxMembers = self.I.SD.getGuildMembersLimitByExp(acc.GuildData.GuildLevelInfo.Experience, self.I)

                debug("GuildService: AcceptGuildAction guild(auid=%r)"
                     " overcrowded: %d/%d, guild exp = %r" % ( acc.GuildData.GuildAuid,
                                                               numMembers,
                                                               maxMembers,
                                                               acc.GuildData.GuildLevelInfo.Experience ))

                if numMembers >= maxMembers:
                    warn("GuildService: AcceptGuildAction guild(auid=%r)"
                         " overcrowded: %d/%d, guild exp = %r" % ( acc.GuildData.GuildAuid,
                                                                   numMembers,
                                                                   maxMembers,
                                                                   acc.GuildData.GuildLevelInfo.Experience ))

                    self.errorResponse( EC.RECRUIT_GUILD_OVERCROWDED,
                                       "Can not accept - guild(auid=%r) \
                                        overcrowded(%r/%r), exp(%r)" % ( acc.GuildData.GuildAuid,
                                                                        numMembers,
                                                                        maxMembers,
                                                                        acc.GuildData.GuildLevelInfo.Experience ) )
                    return

                req = self.I.WS.findReq(acc.RecruitRequests, self.recruit_auid)
                debug("GuildService: AcceptGuildAction req(req=%r)" % req)
                if not req:
                    self.errorResponse( EC.RECRUIT_NO_RECRUIT, "Requests for auid %r is absent" % self.recruit_auid )
                    return

                now = time.time()
                requestLifetime = self.I.SD.data['GuildRecruitment']['guildRequestLifetime']
                if req.get("created") + requestLifetime < now:
                    self.acc.RecruitRequests.remove(req)
                    self.I.WS.broadcastRecruitsChanges(self.acc.GuildData)
                    self.errorResponse( EC.RECRUIT_NO_RECRUIT, "Requests timelimit for %r was finished" % self.recruit_auid )
                    return

                changes = self.I.WS.pickPendingChanges(acc)
                self.I.WS.sendBroadCast(acc, changes, [], '')
                self.I.WS.saveGuildData(acc, None)
                self.response["GuildData"] = changes.get("guild_data", [])
                self.response["ok"] = 1
                self.response['ec'] = 0
                self.fin()
                return
            else:
                self.errorResponse(EC.BAD_PARAM, "Bad param auid=%r. Guild isn't found." % self.guildAuid)
                self.fin()
                return

        self.fin()


class UpdateGuildsRatingAction(SubAction):
    action = "update_guilds_rating"

    @action_timing
    def onStart(self):
        info("UpdateGuildsRatingAction data %r", self.request.request.body)
        self.I.WS.buildGuildsRatingQueue(json_loads(self.request.request.body))
        self.response['ok'] = 1
        self.response['ec'] = 0
        self.fin()


class OnGuildWarEventChangedAction(SubAction):
    action = "on_guild_war_event_changed"

    @action_timing
    def onStart(self):
        info("OnGuildWarEventChangedAction data %r", self.request.request.body)
        if self.checkValidIntParam("event_id"):
            self.I.WS.onNewGuildWarEvent(self.event_id, json_loads(self.request.request.body))
            self.response['ok'] = 1
            self.response['ec'] = 0

        self.fin()

