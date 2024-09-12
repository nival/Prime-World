# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# Mock Social Aggregator web-server
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *
import functools

sys.path.append('cfg')

import tornado.options
from tornado.options import define, options
import tornado.httpclient

from iwebserver import *
from ifactory import IfaceFactory
from iuserdata import IDataManager
from modeldata.persistent_data import PersistentDataManager
from modeldata.TournamentInfo_base import TournamentInfo_base
getGoldAndMaxGameDuration = TournamentInfo_base.getGoldAndMaxGameDuration

from handlers import * # JsonHandler, IfaceFactory
from subaction import SubAction

import EC

from imirror import MirrorDataType, MirrorRequestStatus, CheckMirrorRequestStatus
from guild.guild_service import getMongoKeyAuid
from guild.GuildData import GuildData
from config.ConfigData import ConfigData

import mirror_cfg as cfg
import party_const

from config.MultiConfig import *
from modeldata.MultiStaticData import MultiStaticData
from mirror_helper import MirrorDaemonHelper
## ---------------------------------------------------------------------------------------------

def mirror_info_callback(reply):
    info("mirror reply: %s", reply)

def mirror_count_callback(reply):
    global sql_amount , sql_amount_old
    reply = reply['r']
    for portion_of_data in reply :
        if portion_of_data['data_type'] == 1 :
            print ('server replied - amount of pers calls is == %s' % portion_of_data['amount'])
            sql_amount = portion_of_data['amount']
        elif portion_of_data['data_type'] == 2 :
            print ('server replied - amount of guild calls is == %s' % portion_of_data['amount'])
            sql_amount = portion_of_data['amount']
        else :
            pass

    #info("mirror reply: %s", reply['r'])

define("mirror_mode", default="read", help="mirroring mode: write_test|read")
define("mirror_write_count", type=int, default=1, help="add request batch count")
define("mirror_read_count", type=int, default=1, help="get request batch count")
define("mirror_service_count", type=int, default=1, help="service count")
define("mirror_request_type", type=int, default=0, help="request type for processing")
define("max_pending_mysql_export", type=int, default=1024, help="maximum number of pending export mysql queries (table lines)")
define("data_type", default="all", type=str, metavar="TYPE", help="type of data to export: pers, guild or all")
define("req_per_sec", type=int, default=30 , help="amount of requests to MySQL per second")
define("mr_log", type=str , default="HUL" , help="log file of stress tested mirror")

    ## мониторим кол-во запросов по сервисам-обработчикам:
# SELECT handler_id, count(*) FROM pw_mirror.tbl_queue t GROUP BY handler_id;

## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

class MirrorDaemon(ICSVActionTimingWriter, ITornadoServer):
    """ """
    server_type_name = "mirr"

    def __init__(self, **kwargs):
        super(MirrorDaemon, self).__init__( **kwargs )
        self.pending_counts = IncDict()
        options.data_type = options.data_type.lower()
        if options.data_type == 'pers':
            self.data_types = (MirrorDataType.MODEL_DATA,)
        elif options.data_type == 'guild':
            self.data_types = (MirrorDataType.GUILD_DATA,)
        else:
            self.data_types = (MirrorDataType.MODEL_DATA, MirrorDataType.GUILD_DATA)


        self.pending_get_timestamps = dict.fromkeys(self.data_types, 0)
        self.PENDING_GET_TIMEOUT = cfg.PENDING_GET_TIMEOUT
        self.GC_PERIOD = cfg.MIRROR_DEFAULT_GC_PERIOD
        self.next_clean_time = 0
        self.config_data = ConfigData()
        self.config_data.init(None)
        self.config_data.create()
        self.DEFAULT_MIRROR_BLOCKING_THRESHOLD = cfg.DEFAULT_MIRROR_BLOCKING_THRESHOLD
        self.REMOVE_TASKS_QUEUE_LEN = cfg.REMOVE_TASKS_QUEUE_LEN
        self.check_request_status = CheckMirrorRequestStatus.CHECK
        self.lock_for_check_request = False
        self.queue_delete_requests = []


    def onSetBlockingAlarm(self, loop):
        if options.blocking_threshold < self.DEFAULT_MIRROR_BLOCKING_THRESHOLD:
            info("onSetBlockingAlarm treshold: %r", self.DEFAULT_MIRROR_BLOCKING_THRESHOLD)
            loop.set_blocking_signal_threshold( self.DEFAULT_MIRROR_BLOCKING_THRESHOLD, self.onBlockingAlarm )
        else:
            ITornadoServer.onSetBlockingAlarm(self, loop)

    # -----------------------------------------------
    def tick(self):
        global y, counter, old_counter, traceback_list, sql_amount , sql_amount_old
        try:
            SEC = toint(time.time())
            if SEC % 60 == 0 and self.lastInstrumentedAction + 10 < SEC:
                self.updateInstrumentedActions()
                self.lastInstrumentedAction = SEC
            if options.mirror_mode == "write_test":
                for i in xrange(options.mirror_write_count):
                    data_type = 1
                    #random.randint(1,2)
                    for x in range(0, 20):
                        data_id = random.randint(1,500000)
                        info("write tick (data_type: %s)" % data_type)
                        self.I.MIRROR.addRequest( data_type, data_id, callback=mirror_info_callback )

            elif options.mirror_mode == "stress_test":
                requests_per_second = options.req_per_sec
                t0 = time.time()
                info("start time = %s" % str(t0))
                for data_type in self.data_types :
                    for x in range(0, requests_per_second):
                        data_id = random.randint(1,500000)
                        #info("write tick (data_type: %s)" % data_type)
                        self.I.MIRROR.addRequest( data_type, data_id) #, callback=mirror_info_callback
                        #i+=1
                    info("taking request to get ammount  from sql table list of data_type=%s" % data_type)
                    self.I.MIRROR.countRequests(data_type) #, callback=mirror_count_callback
                t1 = time.time()
                TIME = t1 - t0
                # проверяем, действительно ли запрос занимает меньше секунды?

                if TIME < 1 :
                    info("will sleep until 1 second ends\n")
                    time.sleep (TIME)
                else :
                    error("ERROR, sql request get more than 1 second to ")
                    traceback.print_exc(file=None)

                if y == 60 :
                    # Раз в минуту читаем логи мирроров, в зависимости от data_type, и подсчитываем количество трейсбеков
                    mirror_log_file = options.mr_log
                    f = open(mirror_log_file+'.'+str(options.server_id), 'r')
                    counter = 1
                    i=0
                    file = f.readlines()
                    for line in file :
                        i+=1
                        if "Traceback" in line:
                            if old_counter > counter :
                                pass
                            else :
                                info("""
                                **********************************************************************************************
                                THERE ARE NEW TRACEBACKS FOUND IN MIRROR LOG FILE LOOK INTO STRESS_TEST LOG FILE FOR MORE INFO
                                **********************************************************************************************""")
                                f2 = open('mirror_stress_test.log', 'a+')
                                print >> f2 , 'From_Log_Traceback_Number : %d , line_in_file : %d , error_message : %s' %(counter , i , line)
                                f2.close()
                                traceback_list.append(line)
                            counter += 1
                    old_counter = counter
                    f.close()
                    # Проверяем, уменьшилось ли количество запросов в очереди, спустя 1 минуту - успевают ли мирроры разгребать очередь на запросы
                    f2 = open('mirror_stress_test.log', 'a+')
                    print >> f2 , "Checking SQL Queue working state"
                    f2.close()
                    if sql_amount_old > sql_amount :
                        info ("""
                        **********************************************************************************************
                                        WARNING : SQL QUEUE DIDN'T DECREASED AFTER 1 MINUTE OF WORK
                        **********************************************************************************************""")
                        f2 = open('mirror_stress_test.log', 'a+')
                        print >> f2 , "WARNING : SQL QUEUE DIDN'T DECREASED AFTER 1 MINUTE OF WORK"
                        f2.close()
                    else :
                        f2 = open('mirror_stress_test.log', 'a+')
                        print >> f2 , "SQL QUEUE IS OK"
                        f2.close()
                    y = 0
                else:
                    y += 1
        except Exception:
            catch()
        # в любом случае, garbage collection пропускать нельзя
        self.gcTick()

    def onCheckStatus(self, response):
        debug("onCheckStatus response: %r", response)
        self.check_request_status = CheckMirrorRequestStatus.DONE
    # ------------------------------------------
    def onGetMirrorRequests(self, sql_reply, data_type=0):
        info("onGetMirrorRequests sql_reply: %s", sql_reply)
        #self.pending_get_timestamps[data_type] = 0
        if sql_reply:
            rows = sql_reply.get("r", [])
            if rows:
                accepted_ids = []
                for row in rows:
                    try:
                        info("mirror request: id=%s, data_type=%s, data_id=%s", row.id, row.data_type, row.data_id)
                        accepted_ids.append( row.id )
                        self.pending_counts.inc( row.data_type )

                        # process requests
                        if row.data_type == MirrorDataType.MODEL_DATA:
                            #вытащить обновленные данные из монго (self.I.DATA) и экспортировать в mysql базу (self.I.EXPORT)
                            data_key = "data_%d" % row.data_id
                            _callback = functools.partial(self.onGetModelData, req_id=row.id)
                            self.I.DATA.getData(data_key, data_key, callback=_callback, params=(row.data_id, row.id, row.data_type))

                        elif row.data_type == MirrorDataType.GUILD_DATA:
                            _callback = functools.partial(self.onLoadGuildData, req_id=row.id)
                            self.I.DATA.find_one("guilds", "guilds", {"key": getMongoKeyAuid(row.data_id)}, _callback, params=None)
                        else:
                            warn("unknown data_type=%s, do timeout", row.data_type)
                            self.doRequestTimeout(row.id, row.data_type)
                    except Exception:
                        catch("onGetMirrorRequests: error processing row %r", row)

                self.I.MIRROR.markRequests(accepted_ids, MirrorRequestStatus.PROCESSING, callback=mirror_info_callback)

    # ------------------------------------------
    def onLoadGuildData( self, response, req_id):
        try:
            if response:
                info("onLoadGuildData: data loaded for req_id %r", req_id )
                #info("Response type=%s, value=%s", type(response), response)
                try:
                    data_json = response["r"]["data"] or '{"GuildData":{}}' 
                except Exception:
                    data_json = '{"GuildData":{}}' 

                guildData = GuildData()
                guildData.load(data_json)
                guildData.init(None)
                if guildData.GuildAuid and guildData.Owner.get():
                    self.I.EXPORT.deleteGuildData(guildData.GuildAuid, int(time.time()))
                    numMembers = len(guildData.Members)

                    guildExp = guildData.GuildLevelInfo.Experience 
                    guildLevel = self.I.SD.getGuildLevel(guildExp)
                    levelPercent = 0
                    low, high = self.I.SD.getGuildLevelExpRange(guildLevel)
                    if guildExp >= high:
                        levelPercent = 100.0
                    elif (low <= guildExp) and (guildExp < high):
                        levelPercent = (guildExp - low) * 100.0 / (high - low + 1)
                    info("guild exp=%s, level=%s, range[%s-%s], percent=%.2f", guildExp, guildLevel, low, high, levelPercent)
                        
                    position = guildData.GuildInfo.Place
                    maxPosition = guildData.GuildInfo.BestPlace
                    iconRevision = guildData.GuildInfo.IconChangesCount
                    shopLevel = self.I.SD.getGuildShopLevel(guildData.getShopOwnerRating(), guildData.GuildInfo.HasUltimateShop)
                    maxMembers = self.I.SD.getGuildMembersLimitByExp(guildData.GuildLevelInfo.Experience, self.I)
                    isLocked = 1 if guildData.LockedByOtherGuild else 0
                    self.I.EXPORT.exportGuildRating(guildData.GuildAuid, guildData.RatingInfo.Rating,
                                                    guildData.RatingInfo.PrevRating, guildData.GuildInfo.PrevPlace,
                                                    guildData.GuildInfo.FullName, guildData.GuildInfo.ShortName,
                                                    party_const.getPartyFraction(guildData.GuildInfo.GuildFraction),
                                                    numMembers, maxMembers, guildExp, guildLevel, levelPercent,
                                                    position, guildData.GuildInfo.PlaceChange, maxPosition,
                                                    iconRevision, guildData.Owner.Person, shopLevel,
                                                    guildData.GuildSuzerain.ShortInfo.GuildAuid,
                                                    guildData.GuildSuzerain.ShortInfo.GuildFullName,
                                                    guildData.GuildSuzerain.ShortInfo.GuildShortName,
                                                    guildData.GuildSuzerain.ShortInfo.Rating, isLocked,
                                                    guildData.SiegeForMyGuildEndTime, guildData.GuildInfo.CurrentEventId)
                else:
                    warn("req_id=%r, BAD guildData.GuildAuid!\nresponse=%r\nguildData=%s",
                         req_id, response, pretty(guildData.generateJsonDict()))
        except Exception:
            catch("onLoadGuildData: ERROR processing response %r", response)

        self.onRequestDone(req_id, MirrorDataType.GUILD_DATA)

                
    # ------------------------------------------
    def onStaleRequests(self, sql_reply):
        if sql_reply:
            rows = sql_reply.get("r", [])
            if rows:
                stale_ids = []
                for row in rows:
                    warn("stale request: id=%s, data_type=%s, data_id=%s", row.id, row.data_type, row.data_id)
                    stale_ids.append( row.id )
                if stale_ids:
                    self.I.MIRROR.deleteRequests(stale_ids, callback=mirror_info_callback)
                
    # ------------------------------------------
    def onGetModelData(self, reply, req_id=0):
        try:
            if reply:
                data_obj = reply.get("r") or {}
                data_id, req_id, data_type = reply.get("p") or (0, 0, 0)
                
                json_data = data_obj.get("data", None)
                pers_key = data_obj.get("key", None)
                info("onGetModelData: data_id=%s, req_id=%s, pers_key=%s", data_id, req_id, pers_key)
                
                try:
                    acc = PersistentDataManager.newSimpleDataAcc( json_data )
                    auid = toint(acc.db.get("auid"))
                    if auid:
                        timestamp = int( time.time() )
                        ## info("onGetModelData: acc.model=%s" % acc.model)
                        self.dumpAccHeroes(acc, auid, data_id, timestamp=timestamp)
                        self.dumpAccBuildings(acc, auid, data_id, timestamp=timestamp)
                        #self.dumpAccStatistics(acc, auid, data_id, timestamp=timestamp)
                        if self.config_data.TournamentSettings.IS_TOURNAMENT_SERVER:
                            self.dumpTournaments(acc, auid, data_id, timestamp=timestamp)

                        # теперь полезем в соц.аггрегатор, достанем персональную инфу (даты регистрации, логинов-логаутов и т.п.)
                        _callback = functools.partial( self.onAggregatorGetInfo, req_id=req_id, auid=auid, acc=acc, timestamp=timestamp )
                        return self.I.AGG.getInfo( auid, None, include_secure_data=1, callback=_callback )
                    else:
                        warn("no auid for uid=%d", data_id)

                except Exception:
                    catch("onGetModelData: ERROR parsing model data for user uid=%s." , data_id)
        except Exception:
            catch("onGetModelData: ERROR processing reply %r", reply)

        self.onRequestDone( req_id, MirrorDataType.MODEL_DATA )
            
    # ------------------------------------------
    def onAggregatorGetInfo(self, reply, req_id=0, auid=0, acc=None, timestamp=0):
        try:
            info("onAggregatorGetInfo: auid=%s, req_id=%s, agg reply=%s", auid, req_id, reply)
            
            # на случай, если с аггрегатором не сложится
            dt_register, dt_login, dt_logout, age, dt_birth = 0,0,0,0,0
            dt_pay = 0 #TODO?
            
            if reply:
                # parse
                userinfo = reply.get("get_info", {})
                dt_register = toint( userinfo.get("dt_register") )
                dt_login = toint( userinfo.get("dt_login") )
                dt_logout = toint( userinfo.get("dt_logout") )
                # доступной birthdate нету, но можно выковырять возраст из "главной соц.сети"
                props = userinfo.get("props", {})
                fsn = props.get("fsn", "")
                if fsn:
                    fsn_info = userinfo.get(fsn, {})
                    age = toint( fsn_info.get("age") )

            if acc:
                nick = acc.db.get("nick") or ''
                snid = acc.db.get("snid") or ''
                snuid = acc.db.get("snuid") or ''
                locale = acc.db.get("locale") or ''
                fraction = party_const.getPartyFraction( acc.db.get("fraction") or 'N' )
                reliability = acc.model["ModelData"]["LordInfo"].get("Reliability") or 0
                #reliability = pathFind( acc.model, "ModelData/LordInfo/Reliability" ) or 0
                gender = acc.db.sex or 0
                lord_level = acc.db.lord_level or 0
                sessions = 0 #TODO?
                
                is_developer = acc.db.IsDeveloper or 0
                is_spectator = bool( acc.db.IsSpectator )
                
                #resourceTable = pathFind( acc.model, "ModelData/Resources/ResourceTable" ) or {}
                resourceTable = acc.model["ModelData"]["Resources"]["ResourceTable"] or {}
                silver = toint( resourceTable.get("Silver"))
                gold = toint( resourceTable.get("Gold"))
                perl = toint( resourceTable.get("Perl"))
                red_perl = toint( resourceTable.get("RedPerl"))
                resource1 = toint( resourceTable.get("Resource1"))
                resource2 = toint( resourceTable.get("Resource2"))
                resource3 = toint( resourceTable.get("Resource3"))
                shard = toint( resourceTable.get("Shard"))


                resourceLimit = acc.model["ModelData"]["ResourcesLimit"]["ResourceTable"] or {}
                population = toint( resourceLimit.get("Population"))

                ovr = acc.db.get("geo_ovr")
                if ovr: # Игроку явно установлен оверрайд геолокации. PF-85128
                    country = ovr['country']
                    region = ovr['region']
                    city = ovr['city']
                else:
                    country = acc.db.get("gcountry", '')
                    region = acc.db.get("gregion", '')
                    city = acc.db.get("gcity", '')
                allow_geo_rating = acc.db.get("gallow", None)
                if allow_geo_rating is None:
                    allow_geo_rating = 1
                #is_leaver = pathFind(acc.model, "ModelData/LordInfo/LordInfo/GuardInfo/GuardInfo/isLeaver")
                gi = acc.model["ModelData"]["LordInfo"]["LordInfo"]["GuardInfo"]["GuardInfo"]
                is_leaver = gi.get("isLeaver", False)
                #leaver_points = pathFind(acc.model, "ModelData/LordInfo/LordInfo/GuardInfo/GuardInfo/LeavesPoint")
                leaver_points = gi.get("LeavesPoint", 0)
                #bad_behaviour_reason = toint(pathFind(acc.model, "ModelData/LordInfo/LordInfo/GuardInfo/GuardInfo/badBehaviourReason"))
                bad_behaviour_reason = toint(gi.get("badBehaviourReason", 0))

                self.I.EXPORT.exportPersonalData(auid, snid, snuid, nick, locale,
                    country, region, city, allow_geo_rating, fraction, reliability, age,
                    dt_register, dt_login, dt_logout, gender, lord_level, timestamp, dt_birth, dt_pay, sessions,
                    silver, gold, perl, red_perl, resource1, resource2, resource3, shard, population, is_developer, is_spectator,
                    is_leaver, leaver_points, bad_behaviour_reason)

        except Exception:
            catch("onAggregatorGetInfo: auid=%s, req_id=%s, agg reply=%s, acc=%r", auid, req_id, reply, acc)
        self.onRequestDone(req_id, MirrorDataType.MODEL_DATA)

    # ------------------------------------------
    def dumpAccHeroes(self, acc, auid, uid, timestamp=0):
        try:
            reliability = acc.model["ModelData"]["LordInfo"].get("Reliability") or 0
            nick = acc.db.get("nick") or ''

            info("dumpAccHeroes: uid %d, auid %d, reliability %d, nick %r" % (uid, auid, reliability, nick))
            self.I.EXPORT.deleteHeroData(auid, timestamp)
            self.I.EXPORT.deleteHeroTalentSetData(auid, timestamp)

            query_params = []
            query_args = []
            query_ts_params = []
            query_ts_args = []
            heroes_set = acc.model["ModelData"]["Heroes"]["Set"]
            hero_keeper = acc.model["ModelData"]["HeroesKeeper"]["Keeper"]
            if heroes_set and isinstance(heroes_set, dict):
                for hero_key in heroes_set:
                    hero_id = toint(hero_key)
                    if hero_id:
                        str_hero_id = str(hero_id)
                        hero_path = "ModelData/HeroesKeeper/Keeper/%d/Hero" % hero_id
                        #hero = pathFind(acc.model, hero_path, force_int_keys=False) # у нас "сырая" ModelData, с символьными ключами; не надо их преобразовывать к int
                        if str_hero_id in hero_keeper.keys():
                            hero = hero_keeper[str_hero_id]["Hero"]
                            static_hero = self.I.SD.getStaticHeroByClassId(hero.get("PersistentId", 0))
                            is_hired = hero.get("Hired", 0)
                            if static_hero and is_hired:
                                #hero_ts_path = "ModelData/HeroesKeeper/Keeper/%d/Hero/TalentSets/Collection" % hero_id
                                #for ts_key, ts_id in pathFind(acc.model, hero_ts_path, force_int_keys=False).items():

                                for ts_key, ts_id in hero_keeper[str_hero_id]["Hero"]["TalentSets"]["Collection"].iteritems():
                                    try:
                                        debug("ts_id is %r", ts_id)
                                        #talentset_path = "ModelData/TalentSetsKeeper/Keeper/%d/TalentSet" % ts_id
                                        #talentset = pathFind(acc.model, talentset_path, force_int_keys=False)
                                        talentset = acc.model["ModelData"]["TalentSetsKeeper"]["Keeper"][str(ts_id)]["TalentSet"]
                                        hero_crc = hero.get("PersistentId", 0)
                                        hero_rating = tofloat(hero.get("Rating", 0.0))
                                        hero_force = tofloat( talentset.get("Force", 0) )
                                        hero_level = self.I.SD.getHeroExpLevel(hero.get("Experience")) + 1
                                        hero_last_played = toint( hero.get("lastPlayed", 0) )
                                        if not (hero_crc and hero_rating):
                                            debug("null hero_crc (%d) or rating(%d) for hero_id %d, path %s", hero_crc, hero_rating, hero_id, hero_path)
                                        #hero_skins_path = "ModelData/HeroesKeeper/Keeper/%d/Hero/HeroSkins/HeroSkins" % hero_id
                                        #hero_skins = pathFind(acc.model, hero_skins_path, force_int_keys=False)
                                        hero_skins = hero_keeper[str_hero_id]["Hero"]["HeroSkins"]["HeroSkins"]
                                        skin_id = toint(hero_skins.get("CurrentSkin", 0))
                                        hero_skin_crc = 0
                                        if skin_id != 0:
                                            #current_skin_path = "ModelData/SkinsKeeper/Keeper/%d/Skin" % skin_id
                                            #current_skin = pathFind(acc.model, current_skin_path, force_int_keys=False)
                                            current_skin = acc.model["ModelData"]["SkinsKeeper"]["Keeper"][str(skin_id)]["Skin"]
                                            if current_skin:
                                                hero_skin_crc = toint(current_skin.get("PersistentId", 0))

                                        hero_stats = self.countHeroStats(acc, hero, talentset)
                                        if hero_stats:
                                            hero_health = toint(hero_stats.get("Health", 0.0))
                                            hero_mana = toint(hero_stats.get("Mana", 0.0))
                                            hero_strength = toint(hero_stats.get("Strength", 0.0))
                                            hero_intellect = toint(hero_stats.get("Intellect", 0.0))
                                            hero_agility = toint(hero_stats.get("Agility", 0.0))
                                            hero_cunning = toint(hero_stats.get("Cunning", 0.0))
                                            hero_fortitude = toint(hero_stats.get("Fortitude", 0.0))
                                            hero_will = toint(hero_stats.get("Will", 0.0))
                                            # ок, фигачим данные в MYSQL
                                            '''
                                            self.I.EXPORT.exportHeroData(auid, hero_id, toint(ts_key), hero_crc, hero_rating, "hero_class", hero_skin_crc, timestamp, hero_force, hero_level, hero_last_played,
                                                hero_health, hero_mana, hero_strength, hero_intellect, hero_agility, hero_cunning, hero_fortitude, hero_will, "attack_type")
                                            '''
                                            query_args.append((auid, hero_id, toint(ts_key), hero_crc, hero_rating, "hero_class", hero_skin_crc, timestamp, hero_force, hero_level, hero_last_played,
                                                               hero_health, hero_mana, hero_strength, hero_intellect, hero_agility, hero_cunning, hero_fortitude, hero_will, "attack_type"))

                                            query_params.append((auid, hero_id))
                                            r = self.dumpHeroTalentSets(acc, auid, hero_id, timestamp)
                                            if r:
                                                query_ts_args.extend(r[0])
                                                query_ts_params.extend([1])

                                        else:
                                            warn("dumpAccHeroes: cant find hero stats for hero_id %d (path %s) for uid=%d", hero_id, hero_path, uid)
                                    except Exception:
                                        catch()
                            else:
                                debug("SKIP: hero_id %d not hired for D=%s", hero_id, uid)
                        else:
                            warn("dumpAccHeroes: cant find hero_id %d (path %s) for uid=%d", hero_id, hero_path, uid)
                    else:
                        warn("dumpAccHeroes: bad hero_id %d (hero_key %s) for uid=%d", hero_id, hero_key, uid)

                if query_args and query_params:
                    self.I.EXPORT.exportManyHeroData(query_args, query_params)

                if query_ts_args and query_ts_params:
                    self.I.EXPORT.exportManyHeroTalentSet(query_ts_args, query_ts_params)
            else:
                warn("dumpAccHeroes: bad heroes_set for uid=%d: %s", uid, str(heroes_set))
        except:
            catch("dumpAccHeroes")

    def countHeroStats(self, acc, hero_dict, talentset_dict):
        #items_keeper_path = "ModelData/ItemsKeeper/Keeper"
        #items_keeper = pathFind(acc.model, items_keeper_path, force_int_keys=False)
        items_keeper = acc.model["ModelData"]["ItemsKeeper"]["Keeper"]
        #keeper_path = "ModelData/ConstructionsKeeper/Keeper"
        #constructions_keeper = pathFind(acc.model, keeper_path, force_int_keys=False)
        constructions_keeper =acc.model["ModelData"]["ConstructionsKeeper"]["Keeper"]
        #pocket = pathFind(acc.model, "ModelData/Pocket/Set", force_int_keys=False) or {}
        pocket = acc.model["ModelData"]["Pocket"].get("Set") or {}
        mdHelper = MirrorDaemonHelper(items_keeper, constructions_keeper, pocket)

        return mdHelper.calculateFullStats(hero_dict, talentset_dict, self.I.SD)

    # ------------------------------------------
    def dumpHeroTalentSets(self, acc, auid, hero_id, timestamp):
        #hero_talentsets_path = "ModelData/HeroesKeeper/Keeper/%d/Hero/TalentSets/Collection" % hero_id
        #hero_talentsets = pathFind(acc.model, hero_talentsets_path, force_int_keys=False)
        query_params = []
        query_args = []
        hero_talentsets = acc.model["ModelData"]["HeroesKeeper"]["Keeper"][str(hero_id)]["Hero"]["TalentSets"]["Collection"]
        for tsId, ts in hero_talentsets.iteritems():
            try:
                talentset_path = "ModelData/TalentSetsKeeper/Keeper/%d/TalentSet/Talents/SimpleDict" % ts
                #hero_talentset = pathFind(acc.model, talentset_path, force_int_keys=False)
                hero_talentset = acc.model["ModelData"]["TalentSetsKeeper"]["Keeper"][str(ts)]["TalentSet"]["Talents"]["SimpleDict"]
                items_keeper_path = "ModelData/ItemsKeeper/Keeper"
                #items_keeper = pathFind(acc.model, items_keeper_path, force_int_keys=False) # у нас "сырая" ModelData, с символьными ключами; не надо их преобразовывать к int)
                items_keeper = acc.model["ModelData"]["ItemsKeeper"]["Keeper"]
                talentsDict = {}
                if hero_talentset and isinstance(hero_talentset, dict):
                    if items_keeper and isinstance(items_keeper, dict):
                        for i in xrange(1, 37):
                            if str(i) in hero_talentset:
                                #talent_path = "ModelData/ItemsKeeper/Keeper/%d/Talent" % hero_talentset[str(i)]
                                #talent = pathFind(acc.model, talent_path, force_int_keys=False)
                                talent = None
                                tk = str(hero_talentset[str(i)])
                                if tk in items_keeper:
                                    talent = items_keeper[tk].get("Talent")
                                if talent:
                                    talentsDict[i] = str(talent.get("PersistentId", "0")) + ":" + str(talent.get("Points", "0"))
                                else:
                                    talentsDict[i] = 0
                            else:
                                talentsDict[i] = 0
                        #self.I.EXPORT.exportHeroTalentSet(auid, timestamp, hero_id, talentsDict, tsId)
                        query_args.append((auid, hero_id, timestamp,  talentsDict[1], talentsDict[2], talentsDict[3], talentsDict[4],
                                           talentsDict[5], talentsDict[6], talentsDict[7], talentsDict[8], talentsDict[9],
                                           talentsDict[10], talentsDict[11], talentsDict[12], talentsDict[13], talentsDict[14], talentsDict[15],
                                           talentsDict[16], talentsDict[17], talentsDict[18], talentsDict[19],
                                           talentsDict[20], talentsDict[21], talentsDict[22], talentsDict[23], talentsDict[24], talentsDict[25],
                                           talentsDict[26], talentsDict[27], talentsDict[28], talentsDict[29],
                                           talentsDict[30], talentsDict[31], talentsDict[32], talentsDict[33],
                                           talentsDict[34], talentsDict[35], talentsDict[36], tsId))
                        query_params.append((auid, hero_id))
                    else:
                        warn("dumpHeroTalentSet: bad or empty keeper (path %r) for auid=%s", items_keeper_path, auid)
                else:
                    warn("dumpHeroTalentSet: bad or empty keeper (path %r) for auid=%s", talentset_path, auid)
            except Exception:
                catch()

        return query_args, query_params

    # ------------------------------------------
    def dumpAccBuildings(self, acc, auid, uid, timestamp=0):
        self.I.EXPORT.deleteBuildingData( auid, timestamp )
        query_params = []
        query_args = []
        keeper_path = "ModelData/ConstructionsKeeper/Keeper"
        #keeper = pathFind(acc.model, keeper_path, force_int_keys=False) # у нас "сырая" ModelData, с символьными ключами; не надо их преобразовывать к int)
        keeper = acc.model["ModelData"]["ConstructionsKeeper"]["Keeper"]
        #pocket = pathFind(acc.model, "ModelData/Pocket/Set", force_int_keys=False) or {}
        pocket = acc.model["ModelData"]["Pocket"]["Set"] or {}
        if keeper and isinstance(keeper, dict):
            try:
                for str_building_id, constr in keeper.iteritems():
                    if constr and isinstance(constr, dict):
                        building = constr.get("Construction")
                        if building and isinstance(building, dict):
                            debug( "building dict: %s" % building )
                            crc = toint( building.get("PersistentId", 0) )
                            building_id = toint( str_building_id )
                            debug( "exportMysqlBuildingsparams: auid %s, building_id %s, crc %s" % (auid, building_id, crc) )
                            if crc:
                                building_level = toint( building.get("Level", 0) )
                                in_pocket = 1 if pocket.get(str_building_id, 0) else 0

                                # ок, фигачим данные в MYSQL
                                #self.I.EXPORT.exportBuildingData(auid, building_id, crc, building_level, timestamp, in_pocket)
                                query_args.append((auid, building_id, crc, building_level, timestamp, in_pocket))
                                query_params.append((auid,building_id))

            except Exception:
                catch("dumpAccBuildings: failed to export buildings for uid=%s", uid)
        else:
            warn("dumpAccBuildings: bad or empty keeper (path %r) for uid=%s", keeper_path, uid)
        if query_args and query_params:
            self.I.EXPORT.exportManyBuildingData(query_args,query_params)
    # ------------------------------------------
    def dumpAccStatistics(self, acc, auid, uid, timestamp=0):
        self.I.EXPORT.deleteStatisticsData(auid, timestamp)

        statistics_path = "ModelData/Statistics/UserStatistics/SummarySessionResults/SessionResults"
        #statistics = pathFind(acc.model, statistics_path, force_int_keys=False) # у нас "сырая" ModelData, с символьными ключами; не надо их преобразовывать к int)
        statistics = acc.model["ModelData"]["Statistics"]["UserStatistics"]["SummarySessionResults"]["SessionResults"]
        #lord_info_path = "ModelData/LordInfo/LordInfo/GuardInfo/GuardInfo"
        #lord_info = pathFind(acc.model, lord_info_path, force_int_keys=False)
        lord_info = acc.model["ModelData"]["LordInfo"]["LordInfo"]["GuardInfo"]["GuardInfo"]
        if statistics and isinstance(statistics, dict):
            try:
                kills = toint(statistics.get("kills", 0))
                damageDealedTotal = tolong(statistics.get("damageDealedTotal", 0))
                neutralCreepsKilled = toint(statistics.get("neutralCreepsKilled", 0))
                enemyCreepsKilled = toint(statistics.get("enemyCreepsKilled", 0))
                totalNumTowersKilled = toint(statistics.get("totalNumTowersKilled", 0))
                totalNumQuartersDestroyed = toint(statistics.get("totalNumQuartersDestroyed", 0))
                numberOfWins = toint(lord_info.get("NumberOfWins", 0))
                healedAmount = toint(statistics.get("healedAmount", 0))
                totalMedalsCountDone = toint(statistics.get("totalMedalsCountDone", 0))
                assists = toint(statistics.get("assists", 0))
                score = toint(statistics.get("score", 0))
                money = tolong(statistics.get("money", 0))
                flagsRaised = toint(statistics.get("flagsRaised", 0))
                damageReceivedTotal = tolong(statistics.get("damageReceivedTotal", 0))

                # ок, фигачим данные в MYSQL
                self.I.EXPORT.exportStatisticsData(auid, timestamp, kills, damageDealedTotal, neutralCreepsKilled, enemyCreepsKilled,
                    totalNumTowersKilled, totalNumQuartersDestroyed, numberOfWins, healedAmount, totalMedalsCountDone,
                    assists, score, money, flagsRaised, damageReceivedTotal, 0)
            except Exception:
                catch("dumpAccStatistics: failed to export statistics for uid=%s", uid)
        else:
            warn("dumpAccStatistics: bad or empty keeper (path %r) for uid=%s", statistics_path, uid)

    # ------------------------------------------
    def dumpTournaments(self, acc, auid, uid, timestamp=0):
        info("dumpTournaments: uid %s, auid %s", uid, auid)
        try:
            ### UGLY HACK:
            # Make ticket as a ClassDict to pass it to getGoldAndMaxGameDuration
            # I hasn't find a lightweight way to create true TournamentTicket object here
            #ticket = createClassDict(pathFind( acc.model, "ModelData/TournamentInfo/TournamentInfo/TournamentTicket/TournamentTicket",force_int_keys=False))
            ticket = createClassDict(acc.model["ModelData"]["TournamentInfo"]["TournamentInfo"]["TournamentTicket"]["TournamentTicket"])
            # ... also change ticket.GameDurations sinse it should has list behaviour at least
            ticket.GameDurations = ticket.GameDurations.SimpleList
            gd = getGoldAndMaxGameDuration(ticket, self.config_data)
            self.I.EXPORT.exportTicketData(
                auid, ticket.TicketId, timestamp, ticket.TicketBoughtType, ticket.State, ticket.Wins, ticket.Losses,
                gd['gold'], gd['maxGameDuration'])
        except Exception:
            catch("dumpTournaments: failed export tournament data, auid=%s, uid=%s, acc=%r", auid, uid, acc)

    # ------------------------------------------
    def doRequestTimeout(self, req_id, data_type):
        ##DEBUG: просто по таймауту отмечаем запрос как выполненный
        loop = tornado.ioloop.IOLoop.instance()
        _callback = functools.partial( self.onRequestDone, req_id=req_id, data_type=data_type )
        loop.add_timeout( time.time() + 5.0, _callback )
                
    def onRequestDone(self, req_id=0, data_type=0):
        self.pending_counts.dec( data_type )
        self.queue_delete_requests.append(req_id)
        #self.I.MIRROR.deleteRequests( [req_id], callback=mirror_info_callback )

    # -----------------------------------------------
    def initHandlers(self, application):
        application.add_handlers( r"(.*)", [ 
            ( r"/x", JsonHandler, dict(SUBADDR=SUBADDR_INTERNAL, I=self.I) ),
        ] )            
        
    # -----------------------------------------------
    # return True if startup enviroment is bad
    @staticmethod
    def checkStartupFail():
        pass

    # -----------------------------------------------
    @staticmethod
    def initOptions():
        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.server_id = MIRROR_DAEMON_ID
            options.server_name = MIRROR_DAEMON_NAME
            options.server_class = "mirror"
            options.data_type = "all"
        else:
            options["server_id"].set(MIRROR_DAEMON_ID)
            options["server_name"].set(MIRROR_DAEMON_NAME)
            options["server_class"].set("mirror")
            options["data_type"].set("all")

    # -----------------------------------------------
    @staticmethod
    def initInterfaces( classOf=None ):
        iDict = ClassDict()
        iDict.WS = IWebServer() # чисто для генерации GUID-ов
        iDict.DATA = IfaceFactory.makeIDataInterfaceSimple( options.data, cfg.CLUSTER_MONGO_CONFIG, None, num_threads=cfg.CLUSTER_MONGO_THREADS )
        iDict.MIRROR = IfaceFactory.makeMirrorInterface( options.mirror, cfg.MIRROR_QUEUE_CONFIG, num_threads=cfg.MIRROR_QUEUE_THREADS )
        iDict.EXPORT = IfaceFactory.makeExportInterface( options.export, cfg.MIRROR_EXPORT_CONFIG, num_threads=cfg.MIRROR_EXPORT_THREADS )
        iDict.HTTP = tornado.httpclient.AsyncHTTPClient( max_clients=cfg.HTTP_CURL_WORKERS )
        iDict.AGG = IfaceFactory.makeSocAggInterface( options.soc_agg, cfg.SOCIAL_AGGREGATOR_ADDRESS, SOCAGG_VERSION, HTTP=iDict.HTTP )
        iDict.Config = MultiConfig()
        iDict.MSD = MultiStaticData("xdb/ExportedSocialData.xml", iDict.Config.getMainConfig(), loadLocales=False)
        iDict.SD = iDict.MSD.getMainSD()  # придется тащить весь ниипический XML, из-за несчастных цифр "опыт -> уровень гильдии", а также "опыт героя -> уровень героя"
        return iDict

    
## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

def main():
    ITornadoServer.main( MirrorDaemon )

if __name__ == "__main__":
    #глобальные переменные для стресс теста да, не красиво, но по быстрому по другому не умею.
    global y, counter, old_counter , traceback_list , sql_amount , sql_amount_old
    y = 0
    counter = 0
    old_counter = 0
    traceback_list = []
    sql_amount = 0
    sql_amount_old = 99999999
    #######################################
    #tornado 3.4 fix
    if options.__class__.__name__ == "OptionParser":
        options.port = 8730
    else:
        options["port"].set(8730)
    main()
