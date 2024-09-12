# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *
from subaction import *
from handlers import *
from tornado.httpclient import HTTPRequest
import MM  # matchmaking const
import EC  # error codes
import cfg
# from http_dumb import *
## print os.path.abspath( __file__ )

from geo_cfg import DEFAULT_GEO_LOCATION

MM_SEX_NONE = MM.ESex.NONE
MM_SEX_MALE = MM.ESex.MALE
MM_SEX_FEMALE = MM.ESex.FEMALE

from ext_pw.sexchange import FindNickAuidAction
from enums import *


def isAfterLogin(progress):
    return progress > 100


TUTORIAL_FLAG = 'tutorial'
TUTORIAL_MAP = '/Maps/Multiplayer/MOBA/Tutorial/_.ADMPDSCR'
TUTORIAL_FRAC = 'A'
TUTORIAL_PLAYER_NICK = ''


##----------------------------------------------------------------------------------------------------------------------
##----------------------------------------------------------------------------------------------------------------------
class MatchmakingAddAction(SubAction):
    """action, который будет обрабатывать данный класс"""
    action = "mm_add"

    ## клиент просит начать новую matchmaking сессию
    @action_timing
    @model_callback  # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
    def onStart(self):
        """стартовый метод для обработки action"""
        info("MatchmakingAddAction.onStart: %s", self.arguments)

        self.is_tutorial = self.getParam(TUTORIAL_FLAG, '')
        self.origin_map = TUTORIAL_MAP if self.is_tutorial else self.getParam("game_type", "")
        self.with_bots = self.getIntParam("with_bots", 0)
        if self.with_bots:
            staticMap = self.acc.SD.getStaticMap(self.origin_map)
            if staticMap and staticMap['mapWithBots']['dbid']:
                self.session_type = staticMap['mapWithBots']['dbid']
            else:
                self.errorResponse("can't go with bots for %s map" % self.origin_map)
                return
        else:
            self.session_type = self.origin_map

        if not self.is_tutorial:
            #Пересчет playerRating
            self.acc.model.calcDayDifference(self.acc.getConfig())

        isPvpSession = 0
        isMMSession = False
        map = self.acc.SD.getObjectByDbid(self.session_type)
        try:
            if map and (map['mapType'] in ["CTE", "PvP"]):
                isPvpSession = 1
            if map and (map['mapType'] in ["CTE", "PvP", "Cooperative"]):
                isMMSession = 1
        except Exception:
            pass
        # Проверим, не party_go ли у нас. Если party_go и нас сюда пустили, то матч договорный и можно матчмейкаться
        self.is_party_go = getattr(self, "_party_go_", 0)
        if isMMSession and not self.acc.db.isRegularMMAllowed and not self.with_bots:
            if not self.is_party_go:
                self.errorResponse(EC.CANNOT_USE_ACC_FOR_MM,
                                   "Tournament account can't be used for ordinary matchmaking")
                return

        #### begin  Tournament Quest line
        td = self.acc.model.getTournamentMapData(self.origin_map, self.acc)
        self.party_id = toint(self.getParam("party_id"))
        if isPvpSession and td and self.party_id:
            party_auids = self.getParam("party_auids", "")
            fullPartyOnly, mock, fullPartySize = td
            if party_auids and not (fullPartyOnly and mock and fullPartySize == len(party_auids.split(","))):
                self.errorResponse(EC.TOURNAMENT_NOT_STARTED, "Cannot play tournament not started")
                return
        #### end  Tournament Quest line

        if self.acc.model.LordInfo.GuardInfo.RetiredTime > int(time.time()):
            self.errorResponse(EC.RETIRED_LORD, "Too many dodges")
            return

        self.acc.model.Statistics.StartSessionByGate = self.getBoolParam("clickByGate")
        self.acc.model.LordInfo.ComplaintsSessionLeft = self.acc.getConfig().ComplaintsSettings.MAX_COMPLAITS_PER_SESSION + self.acc.model.LordInfo.ExtraComplaintsSession

        if self.I.WS.maintenanceMode != MAINTENANCE_NORMAL:
            ec, em = getMaintenanceInfo(self.I.WS.maintenanceMode)
            self.errorResponse(ec, em, {'tm': self.I.WS.maintenanceTime})
            return

        mm_sex = self.acc.db.sex
        if self.is_tutorial:
            self.acc.isTutorialAccount = True
            src_hero_id = self.acc.model.createTutorialHero(self.acc.SD.getTutorialHeroId(map, mm_sex), self.acc,
                                                            self.I.MD)
        else:
            src_hero_id = self.getIntParam("src_hero_id", 0)
        hero = self.acc.model.getHeroByID(src_hero_id)
        tsId = self.getIntParam("talent_set_id", 0)
        if hero and not self.is_tutorial:

            if not hero.IsValidTalentSet(self.session_type, self.acc.SD, tsId, self.acc.model):
                self.errorResponse(EC.NOT_ENOUGH_TALENTS, "Not enough talents in TalentSet")
                return
            if hero.isHeroInActiveTavern(self.acc.SD, self.acc.model):
                self.errorResponse("Hero is in Tavern quest")
                return
            if not hero.isValidForceForMap(self.session_type, self.acc.SD):
                self.errorResponse(EC.NOT_ENOUGH_FORCE, "Not enough force for map")
                return

        if self.is_tutorial:
            # self.acc.model.createDefaultMaps(self.I.SD.mainStaticData)
            mapInfo, mapId = self.acc.model.newMapInfo()
            mapInfo.Enabled = True
            mapInfo.MapId = TUTORIAL_MAP
            self.acc.model.LordInfo.MapsByType.add(0, mapInfo)

        if not self.acc.data.mm:

            self.fraction = TUTORIAL_FRAC if self.is_tutorial else self.acc.db.fraction
            self.original_fraction = MM.FRACTION_TYPES[self.fraction]

            if self.acc.partydata and self.acc.partydata.party_uid \
                    and self.acc.partydata.owner.get() and self.acc.partydata.owner.person.get():
                faction_types = [faction_type for faction_type, faction_idx in MM.FRACTION_TYPES.iteritems() if
                                 faction_idx == self.acc.partydata.owner.person.fraction]
                if faction_types:
                    info("MatchmakingAddAction.onStart: override faction by party owner's faction (%s -> %s) ",
                         self.fraction, faction_types[0])
                    self.fraction = faction_types[0]

            self.hero_id = src_hero_id

            if (not self.acc.party_id) or self.is_party_go:
                HERO_IDS = []
                if not self.is_tutorial:  # PF-95124 - для туториала проверка списка героев не нужна
                    for heroId in self.acc.model.HeroesKeeper:
                        hero = self.acc.model.getHeroByID(heroId)
                        if hero.Enabled:
                            HERO_IDS.append(hero.id)

                if self.session_type:  # if self.checkPossibleValue(self.session_type, MM.GAME_TYPES, "bad session type"): -- больше не проверяем тип игры по списку допустимых типов
                    if self.checkPossibleValue(self.fraction, MM.FRACTION_TYPES, "bad fraction"):
                        if self.is_tutorial or self.checkPossibleValue(self.hero_id, HERO_IDS,
                                                                       "bad hero id"):  # X - эта проверка для туториала не нужна
                            mmid = self.I.WS.nextNamedGUID("mm")
                            fraction_index = MM.FRACTION_TYPES[self.fraction]
                            avatarLevel = self.acc.SD.getFameLevel(self.acc.getFame())
                            md = self.acc.model
                            lordRating = md.getRating()
                            lordPublicRating = md.getPublicRating()
                            lordWins = md.getNumberOfWins()
                            lordLeaves = md.getLeavesPoint()

                            peer = self.I.WS.peers.get(options.server_id)
                            if peer:
                                self.response["ws_name"] = peer.get("name")

                            client_revision = 0
                            try:
                                client_revision = toint(self.acc.client_ver.split(".")[
                                                            3])  # из версии "0.2.0.2639" матчмейкер интересует 2639
                            except:
                                pass

                            rep_login = self.acc.login[:].replace("#",
                                                                  "^")  # логины вида "zzima#login" приходится пропихивать через HTTP GET с заменой '#' -> '^'
                            if not (mm_sex in [MM_SEX_MALE, MM_SEX_FEMALE]):
                                mm_sex = MM_SEX_MALE  # матчмейкер, к сожалению, не понимает "неизвестный пол".

                            # НЕобязательные параметры (партия)
                            self.party_id = toint(self.getParam("party_id"))
                            self.party_auids = self.getParam("party_auids",
                                                             "")  # пусть передается прямо в виде дампа списка в строчку: "123,456", нам пофиг
                            self.enemy_auids = self.getParam("enemy_auids",
                                                             "")  # пусть передается прямо в виде дампа списка в строчку: "123,456", нам пофиг

                            geolocation, locale = self._get_locs()

                            now = int(time.time())

                            guildRating = 1300
                            guildLevel = -1
                            guildBuildingLevel = -1
                            if self.acc.guilddata:
                                guildRating = self.acc.guilddata.RatingInfo.Rating
                                guildLevel = self.acc.SD.getGuildLevel(self.acc.guilddata.GuildLevelInfo.Experience)
                                guildBuildingLevel = self.acc.model.getGuildBuildingLevel(self.acc.SD)

                            if self.party_id:
                                # для партий берем флаг "согласен только на гвард.режим" от лидера партии
                                self.only_guard = toint(self.getParam("only_guard"))
                            else:
                                self.only_guard = toint(md.LordInfo.GuardInfo.OnlyGuard)

                            session = ClassDict({
                                # --- GAME ---
                                "mmid": mmid,
                                "game_type": self.session_type,
                                "origin_map": self.origin_map,
                                "with_bots": self.with_bots,
                                "guard_only": self.only_guard,
                                # ~ --- HERO ---
                                ## параметры героя теперь добавляются централизованно, через self.I.WS.fillHeroMatchmakingValues (т.к. их может потом менять тамбур)
                                "src_hero_id": self.hero_id,
                            # нужно запомнить, каким героем мы вставали в ММ, т.к. при додже из тамбура нужно будет вернуть исходного героя
                                # --- LORD (castle & logic) ---
                                "lord_rating": lordRating,
                                "guard_rating": lordPublicRating,
                                "lord_wins": lordWins,
                                "lord_leaves": lordLeaves,
                                "avatarLevel": avatarLevel,
                                "win_lose_hist": self.acc.db.win_lose_hist,
                            # история win/lose streak в формате "0011100"
                                "fraction_A": self.fraction,
                                "fraction": fraction_index,
                                "original_fraction": self.original_fraction,
                                # --- USER (login etc.) ---
                                "login": rep_login,
                                "zz_login": self.acc.snuid,
                                "zz_uid": self.acc.auid,
                                # FIXME: временно, чтобы не ломать транк, передаем копии данных под старыми именами
                                "snuid": self.acc.snuid,
                                "sex": mm_sex,
                                "nick": TUTORIAL_PLAYER_NICK if self.is_tutorial else urllib.quote(
                                    self.I.WS.getDecoratedNickname(self.acc)),
                                "geolocation": geolocation,
                                "locale": locale,
                                # --- session status ---
                                "is_valid": 0,
                                "progress": MM.STATUS_NEW,
                                "confirm": 0,
                                "create_ts": now,
                                "ts_client_ping": now,
                                "awards_applied": 0,
                                "start_reported": 0,
                                # --- roll ---
                                "seed": self.acc.db.seed,
                                "session_roll": self.I.WS.getMapSessionRollString(self.acc, self.session_type),
                                "party_id": str(self.party_id),
                                "party_auids": self.party_auids,
                                "enemy_auids": self.enemy_auids,
                                "guild_auid": str(self.acc.db.guildAuid),
                                "guild_rating": tofloat(guildRating),
                                "guild_level": guildLevel,
                                "guild_building_level": guildBuildingLevel,
                                "hasFullLibrary": self.acc.model.isInventoryFull(),
                                # --- server info (for pvx gateway) ---
                                "ip": options.server_addr,
                                "client_revn": client_revision,
                                "pings": self.acc.model.LordInfo.PingResults.dictionary,
                            # pings: {"ru0":33, "ru1":110, "tr0":250}
                                # --- client info (for castle client) ---
                                "pvx_accept_timeout": self.I.WS.mmServerStatus.accept_timeout,
                                "pvx_average_mm_time": self.I.WS.mmServerStatus.average_mm_time,
                                "pvx_average_mm_time_ext": self.I.WS.mmServerStatus.average_mm_time_ext,
                            })

                            self.I.WS.fillHeroMatchmakingValues(session, self.acc, self.hero_id, self.acc.getConfig(),
                                                                tsId)

                            if self.I.WS.doMatchmakingCmd("add", self.acc, mmid, session):
                                hero = md.getHeroByID(self.hero_id)
                                hero.InMatchmaking = True

                                # сохраняем карту
                                isValid, slotId = self.acc.model.isValidMap(self.origin_map, self.acc)
                                if isValid and slotId >= 0:
                                    self.acc.model.LordInfo.LastStartedMap.MapId = self.origin_map
                                    self.acc.model.LordInfo.LastStartedMap.MapSlot = slotId

                                self.response["mmid"] = mmid
                                session.confirm = MM.CONFIRM_NEW

                                # заворачиваем статус по всем текущим сессиям
                                self.response["mm"] = self.acc.data.mm

                                # выселяем героя из всех домиков в которых он сидит
                                # X - пропустить
                                if not self.is_tutorial:
                                    for building_id in hero.InBuildings.keys():
                                        building = self.acc.model.getConstructionByID(building_id)
                                        building.removeHeroFromBuilding(hero, self.acc, self.I)

                                # проверим, что у нас с туториалом
                                if self.acc.model.LordInfo.TutorialState == TutorialState.BattleQuestAdded:
                                    # or self.acc.model.LordInfo.TutorialState == TutorialState.NotStarted:
                                    # if (self.acc.model.LordInfo.TutorialState == TutorialState.NotStarted)
                                    #    self.I.WS.tutorialGameAwards[]
                                    debug("MatchmakingAddAction: Change tutorial state %s -> %s",
                                          enum2String(TutorialState, self.acc.model.LordInfo.TutorialState),
                                          enum2String(TutorialState, TutorialState.SessionMMStarted))
                                    self.acc.model.LordInfo.TutorialState = TutorialState.SessionMMStarted

                                    self.I.STATS.addTutorialStateChange(self.acc.auid, enum2String(TutorialState,
                                                                                                   self.acc.model.LordInfo.TutorialState))

                                # извещаем PersonServer, что мы тут пошли матчмейкаться
                                if self.I.PS and not self.is_tutorial:  # FIXME!!! Неуверен, можно ли от этого отказаться в случае туториала, но, полагаю, можноы
                                    self.I.PS.sendPartyCmd(self.acc.auid, options.server_id, "party_progress",
                                                           self.I.WS.onDummyResponseCallback,
                                                           progress=MM.STATUS_NEW, reason="mm_add",
                                                           game_type=self.session_type, mm_start_time=int(time.time()),
                                                           hero_id=hero.PersistentId)

                                self.response["ok"] = 1

                            else:
                                self.response["error"] = "doMatchmakingCmd failed"
                                self.response["ec"] = EC.MM_SESSION_NOT_VALID
                else:
                    self.response["error"] = "session type is None"
                    self.response["ec"] = EC.MM_SESSION_NOT_VALID

            else:
                self.response["error"] = "can't add new matchmaking: user has party (party_id %d)" % self.acc.party_id
                self.response["ec"] = EC.MM_USER_HAS_PARTY

        else:
            self.response[
                "error"] = "can't add new matchmaking: user already has %d pending matchmaking session(s)" % len(
                self.acc.data.mm)
            self.response["ec"] = EC.MM_USER_HAS_SESSSION

        self.fin()

    '''
    def _tournament_check_fail(self, isPvpSession):
        if self.acc.getConfig().TournamentSettings.IS_TOURNAMENT_SERVER:
            if self.acc.model.TournamentInfo.TournamentTicket.State != TicketState.InTournament and isPvpSession:
                self.errorResponse( EC.TOURNAMENT_CANNOT_MM_GAME_LOST_OR_SPECTATOR, "Cannot MM because lost or spectator" )
                return True

            if self.acc.model.TournamentInfo.isSecondGame() and isPvpSession:
                self.errorResponse( EC.TOURNAMENT_CANNOT_PLAY_SECOND_GAME, "Cannot play second game" )
                return  True

            if self.acc.model.TournamentInfo.TournamentState != TournamentState.InProgress and isPvpSession:
                self.errorResponse( EC.TOURNAMENT_NOT_STARTED, "Cannot play tournament not started" )
                return  True
    '''

    def _get_locs(self):
        msv_hack = self.acc.snid == 'msv' or self.acc.original_snid == 'msv' or self.acc.fsn == 'msv'
        return (
            (self.getParam("geolocation", "") or (
                cfg.MATCHMAKER_MSV_GEOLOCATION if msv_hack else (self.acc.geolocation or DEFAULT_GEO_LOCATION)
            )),
            (self.getParam("locale", "") or (
                # для играющих через Massive (филиппинцев) необходимо проставить специальную локаль - PF-85549
                cfg.MATCHMAKER_MSV_LOCALE if msv_hack else (self.acc.locale or cfg.MATCHMAKER_DEFAULT_LOCALE)
            ))
        )


##----------------------------------------------------------------------------------------------------------------------
##----------------------------------------------------------------------------------------------------------------------
class MatchmakingPingAction(SubAction):
    """action, который будет обрабатывать данный класс"""
    action = "mm_ping"

    """ отправляем юзеру накопившиеся matchmaking сообщения """

    def sendMessages(self, mmid=MM.PING_ALL):
        if not options.shipping:  # mm_messages работают только при --shipping=0
            mm_messages = self.acc.data.mm_messages
            send_messages = []
            if str(mmid) == MM.PING_ALL:
                # отошлем все сообщения
                if mm_messages:
                    send_messages = mm_messages[:]
                    mm_messages[:] = []  # clear all
            elif mm_messages:
                for i, msg in enumerate(mm_messages[:]):
                    if msg["mmid"] == self.mmid:
                        send_messages.append(msg)
                        mm_messages.remove(i)

            if send_messages:
                self.response["mm_msgs"] = send_messages

    ## клиент запрашивает текущий статус mm-сессии     (mmid=0: всех текущих сессий)
    @action_timing
    @model_callback
    def onStart(self):
        """стартовый метод для обработки action"""
        debug("Matchmaking.Ping.onStart\n self.acc.data: " + pretty(self.acc.data))

        # сессии ММкинга нет
        data = self.acc.data

        # в любом случае отдадим model changes
        self.sendPendingMessages()
        self.sendPendingEvents()

        if not data.mm:
            self.I.WS.doMatchmakingCmd("cancel", self.acc, MM.CANCEL_ALL)
            heroes = self.acc.model.validateHeroesInMatchmaking(self.acc)
            # ~ #! так что приходится выгребать уже готовые changes из response, и перекладывать в pending
            # ~ model_changes_generated = self.response.get("ModelData")
            # ~ if model_changes_generated:
            # ~ if isinstance( model_changes_generated, ResponseObject ):
            # ~ model_changes_generated = model_changes_generated.makeDict()
            # ~ info( "generated mmPingAction model changes: %s" % model_changes_generated )
            # ~ for change in model_changes_generated:
            # ~ self.acc.pending_changes.append( {"ModelData": change} )

            self.sendMessages()  # все равно отошлем все сообщения
            self.response["error"] = "no active matchmaking sessions"
            self.response["ec"] = EC.MM_NO_ACTIVE_SESSIONS
            self.fin()
            return
        else:  # проверим что тех работы не идут и мы не реконнектимся при этом
            if self.I.WS.maintenanceMode != MAINTENANCE_NORMAL and not isAfterLogin(data.mm.progress):
                ec, em = getMaintenanceInfo(self.I.WS.maintenanceMode)
                self.I.WS.doMatchmakingCmd("cancel", self.acc, MM.CANCEL_ALL)
                self.sendMessages()  # все равно отошлем все сообщения
                self.response["error"] = em
                self.response["error_args"] = {'tm': self.I.WS.maintenanceTime}
                self.response["ec"] = ec
                self.fin()
                return

        isNoNeedCheck = False
        if self.acc.partydata and self.acc.partydata.party_uid and self.acc.partydata.owner:
            if self.acc.partydata.owner.person.person_uid != self.acc.auid:
                isNoNeedCheck = True  # полагаемся на лидера

        # сессия ММкинга есть, и карта валидная либо реконнект
        if isNoNeedCheck or self.acc.getConfigValue("DEBUG_ENABLED") or isAfterLogin(data.mm.progress) or \
                self.acc.model.isValidMap(data.mm.origin_map, self.acc)[0]:
            # validate session timestamps:
            self.I.WS.validateMatchMakingSessions(self)  # далеко не базовый интерфейс, есличо; есть только в pwserver

            now = int(time.time())

            session = data.mm

            self.response["mmid"] = session.mmid
            session.ts_client_ping = now
            self.response["mm"] = session.copy()  # shallow copy of dict
            self.response["mm"]["summary_state"] = self.I.WS.mmSummaryState

            if self.acc.db.IsDeveloper:
                self.response["mm"]["mm_debug_status"] = self.I.WS.mmDebugStatus
            self.sendMessages()  # заодно отошлем все сообщения

            self.response["ok"] = 1
            self.fin()
            return

        # сессия ММкинга есть, но карта не валидна
        self.I.WS.doMatchmakingCmd("cancel", self.acc, MM.CANCEL_ALL)
        ##heroes = self.acc.model.validateHeroesInMatchmaking(self.acc)
        # ~ #! так что приходится выгребать уже готовые changes из response, и перекладывать в pending
        # ~ model_changes_generated = self.response.get("ModelData")
        # ~ if model_changes_generated:
        # ~ if isinstance( model_changes_generated, ResponseObject ):
        # ~ model_changes_generated = model_changes_generated.makeDict()
        # ~ info( "generated mmPingAction model changes: %s" % model_changes_generated )
        # ~ for change in model_changes_generated:
        # ~ self.acc.pending_changes.append( {"ModelData": change} )

        self.sendMessages()  # все равно отошлем все сообщения
        self.response["error"] = "mm map has changed"
        self.response["ec"] = EC.MM_MAP_HAS_CHANGED

        self.fin()


##----------------------------------------------------------------------------------------------------------------------
##----------------------------------------------------------------------------------------------------------------------
class MatchmakingCancelAction(SubAction):
    """action, который будет обрабатывать данный класс"""
    action = "mm_cancel"

    ## клиент просит прибить mm-сессию (mmid=0: все текущие сессии)
    @action_timing
    @model_callback  # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
    def onStart(self):
        """стартовый метод для обработки action"""
        log("Matchmaking.Cancel.onStart")

        self.mmid = self.getParam("mmid", MM.CANCEL_ALL)
        data = self.acc.data
        if data.mm:
            session = data.mm
            if session.mmid == self.mmid:
                self.response["mmid"] = session.mmid

                if session.game_type != "SPECTATE":
                    if session.progress in [MM.STATUS_WAITING_IN_LOBBY, MM.STATUS_WAITING_FOR_PARTY, MM.STATUS_IN_GAME,
                                            MM.STATUS_CLIENT_DROPPED, \
                                            MM.STATUS_WAITING_GAME_FINISH, MM.STATUS_GAME_FINISHED, \
                                            MM.STATUS_ACCEPTED_SOCSERVER, MM.STATUS_ACCEPTED_PVX]:
                        # не разрешаем закрывать идущую сессию, пока не дождались награды
                        self.response["mm"] = session  # отошлем актуальную сессию, дабы клиент не пришиб, увидев ec
                        self.response["error"] = "pvx session in progress"
                        self.response["ec"] = EC.MM_CANCEL_INGAME
                        return self.fin()

                    hero = self.acc.model.getHeroByID(session.hero_id)
                    if hero:
                        hero.InMatchmaking = False

                    if session.progress in [MM.STATUS_GUARDS_LOBBY]:
                        # не разрешаем закрывать идущую сессию, из-за чужого лива
                        self.response["mm"] = session  # отошлем актуальную сессию, дабы клиент не пришиб, увидев ec
                        self.response["error"] = "pvx session in progress"
                        self.response["ec"] = EC.MM_CANCEL_INGAME
                        return self.fin()

                self.I.WS.doMatchmakingCmd("cancel", self.acc, MM.CANCEL_ALL)
                self.response["mm"] = data.mm  # заворачиваем сессию (если жива) или None (если удалена)

                self.response["ok"] = 1

            else:
                self.response["error"] = "bad matchmaking session id"
                self.response["ec"] = EC.MM_BAD_MMID
        else:
            self.response["error"] = "no active matchmaking sessions"
            self.response["ec"] = EC.MM_NO_ACTIVE_SESSIONS

        self.fin()


class MatchmakingTamburLeaveAction(SubAction):
    """action, который будет обрабатывать данный класс"""
    action = "mm_leave_tambur"

    ## клиент просит прибить mm-сессию (mmid=0: все текущие сессии)
    @action_timing
    @model_callback  # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
    def onStart(self):
        """стартовый метод для обработки action"""
        log("Matchmaking.LeaveTambur.onStart")

        self.mmid = self.getParam("mmid", MM.CANCEL_ALL)
        data = self.acc.data
        if data.mm:
            session = data.mm
            if session.mmid == self.mmid:
                self.response["mmid"] = session.mmid

                if session.progress in [MM.STATUS_GUARDS_LOBBY]:
                    info("mm_cancel: dodge from guards tambur (auid %s)" % self.acc.auid)
                    self.acc.model.addDodge(self.I.WS, self.acc)
                    self.I.WS.doMatchmakingCmd("cancel", self.acc, MM.CANCEL_ALL)
                    self.acc.model.validateHeroesInMatchmaking(
                        self.acc)  # после "cancel" у нас уже отсутствует acc.data.mm
                    self.response["mm"] = data.mm  # заворачиваем сессию (если жива) или None (если удалена)
                    self.response["ok"] = 1

                else:
                    # не разрешаем закрывать идущую сессию, если мы не в тамбуре
                    self.response["mm"] = session  # отошлем актуальную сессию, дабы клиент не пришиб, увидев ec
                    self.response["error"] = "pvx session in progress"
                    self.response["ec"] = EC.MM_CANCEL_INGAME
            else:
                self.response["error"] = "bad matchmaking session id"
                self.response["ec"] = EC.MM_BAD_MMID
        else:
            self.response["error"] = "no active matchmaking sessions"
            self.response["ec"] = EC.MM_NO_ACTIVE_SESSIONS

        self.fin()


##----------------------------------------------------------------------------------------------------------------------
##----------------------------------------------------------------------------------------------------------------------
class MatchmakingAcceptAction(SubAction):
    """action, который будет обрабатывать данный класс"""
    action = "mm_accept"

    ## клиент подтверждает начало (уже сматчмейканной) игровой сессии
    @action_timing
    @model_callback  # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
    def onStart(self):
        """стартовый метод для обработки action"""
        log("Matchmaking.Accept.onStart")

        self.mmid = self.getParam("mmid")
        session = self.acc.data.mm or ClassDict()
        session_mmid = session.get("mmid", "")
        session_progress = session.get("progress", 0)
        ts_id = session.get("talent_set_id", 0)

        if session and session_mmid == self.mmid:
            if session_progress in [MM.STATUS_WAITING_ACCEPT]:
                try:
                    session.progress = MM.STATUS_ACCEPTED_SOCSERVER
                    session.confirm = MM.CONFIRM_ACCEPT
                    hero_id = session["hero_id"]
                except:
                    catch()

                map = self.acc.SD.getObjectByDbid(session.game_type)
                acceptParamsDict = self.I.WS.getHeroAcceptParameters(self.acc, hero_id, map, session.game_type, ts_id)
                if self.acc.partydata and self.acc.partydata.party_uid and self.acc.partydata.owner:
                    if self.acc.partydata.owner.person.person_uid == self.acc.auid:
                        acceptParamsDict["partyLeader"] = True
                self.I.WS.doMatchmakingCmd("accept", self.acc, self.mmid, acceptParamsDict)
                # извещаем PersonServer, что мы ушли в бой
                if self.I.PS:
                    self.I.PS.sendPartyCmd(self.acc.auid, options.server_id, "party_progress",
                                           self.I.WS.onDummyResponseCallback,
                                           progress=session.progress, reason="mm_accept", game_type=session.game_type,
                                           mm_start_time=int(time.time()), hero_id=hero_id)

                self.acc.model.Statistics.SessionsStarted += 1
                if session.game_type in self.acc.getConfig().MAPS_FOR_PLAYER_RATING:
                    self.acc.model.Statistics.PRSessionsStarted += 1

                # проверим, что у нас с туториалом
                if self.acc.model.LordInfo.TutorialState == TutorialState.SessionMMStarted:
                    debug("MatchmakingAcceptAction: Change tutorial state %s -> %s",
                                          enum2String(TutorialState, self.acc.model.LordInfo.TutorialState),
                                          enum2String(TutorialState, TutorialState.SessionMMStarted))
                    self.acc.model.LordInfo.TutorialState = TutorialState.SessionMMAccepted
                    self.I.STATS.addTutorialStateChange(self.acc.auid, enum2String(TutorialState,
                                                                                   self.acc.model.LordInfo.TutorialState))

                self.response["mmid"] = self.mmid
                self.response["mm"] = session
                self.response["ok"] = 1

            else:
                return self.fail("bad session progress: %s" % session_progress, EC.MM_WRONG_SESSION_PROGRESS_FOR_ACCEPT)
        else:
            return self.fail("bad or unfinished matchmaking session id", EC.MM_BAD_MMID)

        self.fin()


##----------------------------------------------------------------------------------------------------------------------
##----------------------------------------------------------------------------------------------------------------------
class MatchmakingReconnectAction(SubAction):
    """action, который будет обрабатывать данный класс"""
    action = "mm_reconnect"
    progress_states = [MM.STATUS_CLIENT_DROPPED]

    ## клиент просит реконнектить его к существующей mm-сессии
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        log("Matchmaking.Reconnect.onStart")

        self.mmid = self.getParam("mmid", 0)
        data = self.acc.data
        if data.mm:
            session = data.mm
            self.response["mmid"] = session.mmid
            if session.mmid == self.mmid:
                if session.is_valid:
                    if session.progress in self.progress_states:
                        if cfg.PVX_CAN_RECONNECT:
                            self.I.WS.doMatchmakingCmd("reconnect", self.acc, self.mmid)
                            session["confirm"] = MM.CONFIRM_RECONNECT
                            self.response["mm"] = session
                            self.response["ok"] = 1
                        else:
                            self.response["error"] = "command not supported"
                            self.response["ec"] = EC.CMD_NOT_SUPPORTED
                    else:
                        self.response["error"] = "wrong matchmaking session progress, must be in %s" % str(
                            self.progress_states)
                        self.response["ec"] = EC.MM_WRONG_SESSION_PROGRESS
                else:
                    self.response["error"] = "matchmaking session is not current (is_valid=0)"
                    self.response["ec"] = EC.MM_SESSION_NOT_VALID
            else:
                self.response["error"] = "bad matchmaking session id"
                self.response["ec"] = EC.MM_BAD_MMID
        else:
            self.response["error"] = "no active matchmaking sessions"
            self.response["ec"] = EC.MM_NO_ACTIVE_SESSIONS

        self.fin()


##----------------------------------------------------------------------------------------------------------------------
##----------------------------------------------------------------------------------------------------------------------
class MatchmakingLeaveAction(SubAction):
    """action, который будет обрабатывать данный класс"""
    action = "mm_leave"
    progress_states = [MM.STATUS_CLIENT_DROPPED]

    ## клиент просит реконнектить его к существующей mm-сессии
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        log("Matchmaking.Reconnect.onStart")

        self.mmid = self.getParam("mmid", 0)
        data = self.acc.data
        if data.mm:
            session = data.mm
            self.response["mmid"] = session.mmid
            if session.mmid == self.mmid:
                if session.is_valid:
                    if session.progress in self.progress_states:

                        self.I.WS.doMatchmakingCmd("leave", self.acc, self.mmid)
                        session["confirm"] = MM.CONFIRM_LEAVE
                        self.response["mm"] = session
                        self.response["ok"] = 1

                    else:
                        self.response["error"] = "wrong matchmaking session progress, must be in %s" % str(
                            self.progress_states)
                        self.response["ec"] = EC.MM_WRONG_SESSION_PROGRESS
                else:
                    self.response["error"] = "matchmaking session is not current (is_valid=0)"
                    self.response["ec"] = EC.MM_SESSION_NOT_VALID
            else:
                self.response["error"] = "bad matchmaking session id"
                self.response["ec"] = EC.MM_BAD_MMID
        else:
            self.response["error"] = "no active matchmaking sessions"
            self.response["ec"] = EC.MM_NO_ACTIVE_SESSIONS

        self.fin()


##----------------------------------------------------------------------------------------------------------------------
##----------------------------------------------------------------------------------------------------------------------
class MatchmakingSpectateAction(SubAction):
    """ Хотим вписаться зрителем в идущую pvx сессию к юзеру '<nickname>' """
    action = "mm_spectate"

    @action_timing
    @model_callback  # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
    def onStart(self):
        if self.checkValidParam("nickname"):
            # обычные пляски с конвертацией из неизвестно какой codepage (надеемся на utf8)
            try:
                nickname_unicode = unicode(self.nickname, 'utf8')
                self.nickname = nickname_unicode.encode('utf8')
            except:
                catch()
                return self.fail("can't convert nickname (should be utf8 encoded)", EC.BAD_SPECTATOR_NICKNAME)

            if self.acc.db.IsSpectator:
                action = FindNickAuidAction(acc=self.acc, I=self.I, nick=self.nickname, fin_callback=self.onFindAuid)
                return action.onStart()
            else:
                return self.fail("not allowed to spectate", EC.NOT_ALLOWED_SPECTATOR)

        self.fin()

    @action_timing
    @model_callback  # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
    def onFindAuid(self, response):
        if response:
            info("MatchmakingSpectateAction.onFindAuid response: %r", response)
            self.target_auid = response.get("auid", 0)
            if self.target_auid:
                target_user_acc = self.I.WS.getUserAccByAuid(toint(self.target_auid))
                if target_user_acc:
                    if target_user_acc.data and target_user_acc.data.mm:
                        if target_user_acc.data.mm.game_type == "SPECTATE":
                            return self.fail("doMatchmakingCmd failed, current user is already a spectator", EC.MM_SESSION_NOT_VALID)
                        else:
                            return self.onCheckForSpectator({'ok': 1})
                    else:
                        return self.fail("Can't spectate player that is not playing=%r" % self.nickname, EC.NO_GAME_TO_SPECTATE)
                else:
                    self.I.AGG.getInfo(self.target_auid, None, include_secure_data=1, callback=self.onAgentFsnGetInfo)
                    return
            else:
                return self.fail("can't find user auid by nickname=%r" % self.nickname, EC.FIND_NICK_NO_AUID)

        self.fin()

    @action_timing
    def onAgentFsnGetInfo(self, agg_response):
        if agg_response:
            self.agg_info = agg_response.get('get_info')
            if self.agg_info:
                agg_properties = self.agg_info.get('props') or {}
                fsn = agg_properties.get('fsn')
                if fsn:
                    sn_info = self.agg_info.get(fsn)
                    if sn_info:
                        fsn_snid = fsn
                        fsn_snuid = sn_info.get('snuid', '')
                        self.response["fsn_snid"] = fsn_snid
                        self.response["fsn_snuid"] = fsn_snuid
                        if fsn_snid and fsn_snuid:
                            self.login = str("%s#%s" % (fsn_snid, fsn_snuid))
                            return self.I.SQL.login(self.login, options.server_id, self.onFindUserInSql)
        # fail:
        return self.onCheckForSpectator({'ok': 1})

    @action_timing  # Ищем, на каком ws зарегистрирован target_auid
    def onFindUserInSql(self, sql_reply):
        r = sql_reply["r"]
        info("-- onFindUserInSql: sql sp_login reply: %r", str(sql_reply))
        if r and len(r):
            try:
                ws, login, self.pwd, self.uid = r[0].ws, r[0].login, r[0].pwd, r[0].id
                peer = self.I.WS.peers.get(ws)
                if peer:
                    ws_addr = peer.get("addr")
                    ws_name = peer.get("name")
                else:
                    return self.onCheckForSpectator({'ok': 1})
            except:
                catch()
                return self.onCheckForSpectator({'ok': 1})

            args = dict(action="check_for_spectator", auid=self.target_auid)


            self.I.WSX.fetch(ws_addr, args, self.onCheckForSpectator, subrequest="")
            #req = HTTPRequest(url='http://' + ws_name + '/?' + urllib.urlencode(args), method="GET",  connect_timeout=20.0, request_timeout=20.0)
            #self.I.HTTP.fetch(req, self.onCheckForSpectator)
            return

        return self.onCheckForSpectator({'ok': 1})

    @action_timing
    @model_callback  # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
    def onCheckForSpectator(self, response):
        info("onCheckForSpectator: %r", response)
        isOk = False
        if isinstance(response, dict):
            if response.get("ok", False):
                isOk = True
        elif response and (not response.error) and response.body is not None and len(response.body) > 0:
            result = jsonResult(response)
            if result.get("response", None) and result["response"].get("ok", None):
                isOk = result["response"].get("ok", False)
                if "ec" in response and "error" in response:
                    return self.fail(response["error"], response["ec"])
        if isOk:
            if not self.acc.data.mm:
                mmid = self.I.WS.nextNamedGUID("mm")
                now = toint(time.time())
                self.session_type = "SPECTATE"

                session = ClassDict({
                    # --- GAME ---
                    "mmid": mmid,
                    "game_type": self.session_type,
                    "origin_map": self.session_type,
                    "zz_login": self.acc.snuid,
                    "zz_uid": self.acc.auid,
                    "target_uid": str(self.target_auid),  # gateway ждет target_uid строчкой
                    "nick": urllib.quote(self.I.WS.getDecoratedNickname(self.acc)),
                    # --- session status ---
                    "is_valid": 0,
                    "progress": MM.STATUS_NEW,
                    "confirm": 0,
                    "create_ts": now,
                    "ts_client_ping": now,
                    "awards_applied": 0,
                    "start_reported": 0,

                })

                if self.I.WS.doMatchmakingCmd("spectate", self.acc, mmid, session):
                    self.response["mmid"] = mmid
                    session.confirm = MM.CONFIRM_NEW

                    # заворачиваем статус по всем текущим сессиям
                    self.response["mm"] = self.acc.data.mm

                    # извещаем PersonServer, что мы тут пошли матчмейкаться
                    if self.I.PS:
                        self.I.PS.sendPartyCmd(self.acc.auid, options.server_id, "party_progress",
                                               self.I.WS.onDummyResponseCallback, progress=MM.STATUS_NEW, reason="mm_spectate",
                                               game_type=self.session_type, mm_start_time=int(time.time()))

                    self.response["ok"] = 1

                else:
                    return self.fail("doMatchmakingCmd failed", EC.MM_SESSION_NOT_VALID)
            else:
                return self.fail("can't add new matchmaking: user already has %d pending matchmaking session(s)", len(self.acc.data.mm), EC.MM_USER_HAS_SESSSION)
        else:
            return self.fail("doMatchmakingCmd failed, current user is already a spectator", EC.MM_SESSION_NOT_VALID)

        self.fin()


class CheckForSpectatorAction(SubAction):
    """action, который будет обрабатывать данный класс"""
    action = "check_for_spectator"

    def onStart(self):
        info("CheckForSpectatorAction arguments: %r", self.arguments)
        if not self.checkValidIntParam("auid"):
            info("CheckForSpectatorAction: bad auid")
            self.response["ok"] = 1
            self.fin()
            return

        target_user_acc = self.I.WS.getUserAccByAuid(self.auid)
        if target_user_acc:
            if target_user_acc.data:
                if target_user_acc.data.mm:
                    if target_user_acc.data.mm.game_type == "SPECTATE":
                        self.response["isSpectator"] = True
                        return self.fail("doMatchmakingCmd failed, current user is already a spectator", EC.CANT_SPECTATE_SPECTATOR)
                    else:
                        self.response["ok"] = 1
                        self.fin()
                        return
        self.response["isSpectator"] = True
        return self.fail("doMatchmakingCmd failed, current user doesn't have active mm sessions",  EC.NO_GAME_TO_SPECTATE)


##----------------------------------------------------------------------------------------------------------------------
##----------------------------------------------------------------------------------------------------------------------
class MatchmakingAlliesAction(SubAction):
    """action, который будет обрабатывать данный класс"""
    action = "mm_allies"

    ## клиент просит реконнектить его к существующей mm-сессии
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        info("Matchmaking.Allies.onStart arguments: %r", self.arguments)
        post_data = self.getParam("post_data", "")
        allies = json_loads(post_data)
        # allies = self.getParam("allies_auids", "")
        data = self.acc.data
        if allies:
            if data.mm:
                session = data.mm
                if session.is_valid:
                    self.I.FRIENDS.addRecentAllies(self.acc.auid, allies)
                else:
                    self.response["error"] = "matchmaking session is not current (is_valid=0)"
                    self.response["ec"] = EC.MM_SESSION_NOT_VALID
            else:
                self.response["error"] = "no active matchmaking sessions"
                self.response["ec"] = EC.MM_NO_ACTIVE_SESSIONS
        else:
            err("Matchmaking.Allies: no allies auids")

        self.fin()
