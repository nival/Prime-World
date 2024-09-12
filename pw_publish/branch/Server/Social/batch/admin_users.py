#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network
import sys, os, time, datetime
import getopt
import urllib, urllib2
import os.path
import gc
from threading import Thread
import pymongo
import math
import multiprocessing
from collections import defaultdict
sys.path.append('..')
sys.path.append('../libs/memcache')
sys.path.append("DBScripts")
import UserDataBaseHandler
import memcache
import zlib, bz2
from base.helpers import *

sys.path.append('../cfg')
##sys.path.append('C:/pw.prod/social/cfg')
import coord_cfg

from binascii import crc32  # zlib version is not cross-platform
from iaggregator import IRealSocialAggregator
from handlers import *
from ihttp import ISyncHttp
import CC

from enums import DynamicQuestAwardType, DynamicQuestAwardConditionType, DynamicQuestCheckType, CastleResources
from modeldata.persistent_data import PersistentDataManager
from modeldata.ModelData import *
from modeldata.StaticData import StaticData
from guild.GuildData import GuildData
from cluster_sql import syncSqlQuery, syncSqlCommand, SyncSqlManager
from cluster_base import crc_hash
import admin_guilds
import time
import itertools
import subprocess


def catch():
    print printException(sys.exc_info())


# ????, ??? ???? ?????
duplicate_uids = {"mongo": {}, "mc": {}}

OUT_PATH = ""
OUT_FILE = ""
OUT_FILE_MODE = "wt"  # ?? ?????? ??????? ????? ?? ??? - ??????? "at"
FOREACH_USERS_PER_GC_COLLECT = 10  # ? ????? ?????? ?? ??? foreach -- ???10 ??????? garbage collect
FOREACH_USERS_PER_GC_COLLECT_CHANGED = False
FOREACH_SLEEP_MSEC_PER_USER = 10  # ? ????? ?????? ?? ??? foreach -- ???? ?? ???????? ???? ??????? ? mongo
FOREACH_SLEEP_USERS_PER_PASS = 1
FOREACH_BATCH_SIZE = 100

DUMP_INPUT_DATA = 0
DUMP_OUTPUT_DATA = 0
PRETTY_DUMP = 1

# ???/????? ??????? ???????????? ????--mongo_config="[..json..]"
MONGO_CONFIG = coord_cfg.COORDINATOR_MONGO_CONFIG
MC_CONFIG = coord_cfg.COORDINATOR_MC_SERVER_LIST
SQL_CONFIG = coord_cfg.COORDINATOR_SQL_CONFIG
MIRROR_CONFIG = coord_cfg.COORDINATOR_MIRROR_QUEUE_CONFIG
EXPORT_CONFIG = coord_cfg.COORDINATOR_MIRROR_EXPORT_CONFIG

NUM_DAYS_FOR_GUILD_RATING_RECOUNT = 7


class ZZimaArgWrapper:
    def addQuery(self, method, args, callback, params):
        ## print "ZZimaArgWrapper.addQuery: method %s, args %s" % (method, args)
        self.method = method
        self.args = args

    def __call__(self):
        return self

    def aggregatorCallback(self, agg_response):
        self.agg_response = agg_response


# -----------------------------------------------------------------------------------------
def checkJsonData(pers_key, data_json, dict_counters, CNAME):
    dict_counters.total_checked += 1
    print "-- check %5s reply obj key: %s, data: %s" % (CNAME, pers_key, str(data_json)[:128])

    key_coll = pers_key.split("_")
    if len(key_coll) == 2:
        prefix = key_coll[0]
        uid = long(key_coll[1])
    else:
        print "! persistence WARNING: bad key (%s)" % (pers_key)
        dict_counters.no_key += 1
        return

    acc = PersistentDataManager.newSimpleDataAcc(data_json)
    db = acc.db

    if uid:
        if uid in duplicate_uids[CNAME]:
            print "--- PERSISTENCE ERROR: DUPLICATE uid %s" % (str(uid))

    if db.original_uid:
        if db.original_uid != uid:
            print "--- PERSISTENCE ERROR: uid %s != db.uid %s" % (str(uid), str(db.original_uid))
            dict_counters.mismatch_uid += 1
        else:
            print "-- ok: uid %d == db.uid %d" % (uid, db.original_uid)
    else:
        print "! persistence WARNING: no db.uid (%s)" % (str(db.original_uid))
        dict_counters.no_uid += 1


# -----------------------------------------------------------------------------------------
def getSocialRequisitesByAuid(auid):
    """ ?????? ????? auid ?? snid:snlogin ? ??????"""
    HTTP = ISyncHttp()
    AGG = IRealSocialAggregator(coord_cfg.COORDINATOR_SOCIAL_AGGREGATOR_ADDRESS, SOCAGG_VERSION, HTTP)

    def onResponse(response):
        global agg_response
        agg_response = response

    AGG.getInfo(auid, None, include_secure_data=1, callback=onResponse)
    sn_id, sn_login = None, None
    if agg_response:
        get_info = agg_response.get("get_info", {})
        print "getInfo(auid=%s) reply: %s" % (auid, get_info)
        sn_id = str(pathFind(get_info, "props/fsn"))
        if sn_id:
            sn_login = str(pathFind(get_info, "%s/snuid" % sn_id))
        else:
            print "ERROR: no fsn for (auid=%s)" % (auid)
    else:
        print "ERROR: bad social aggregator reply for getInfo(auid=%s): %s" % (auid, agg_response)
    return sn_id, sn_login


# -----------------------------------------------------------------------------------------
def prepare_printable_dump(cache_dict):
    if PRETTY_DUMP:
        return pretty(cache_dict)
    else:
        return json_dumps(cache_dict)


# -----------------------------------------------------------------------------------------
def checkMongoUserData():
    mongo_counters = ClassDict(
        total_checked=0,
        no_key=0,
        no_uid=0,
        mismatch_uid=0
    )

    mc_counters = ClassDict(
        total_checked=0,
        no_key=0,
        no_uid=0,
        mismatch_uid=0
    )

    single_mc_counters = ClassDict(
        total_checked=0,
        no_key=0,
        no_uid=0,
        mismatch_uid=0
    )

    print "==== CHECK ALL MONGO USER SAVES ====="
    print "USING MONGO server list: %s" % (MONGO_CONFIG)
    print "USING MC server list: %s" % (MC_CONFIG)

    mc = memcache.Client(MC_CONFIG, debug=0)

    # ?????????????? ? ?? memcache, ???? ????(? ??? ?? ????? ?????????, ??????????? ??, ???? MC-???? ??????)
    mc_dict = {}
    mc_index = 0
    for mc_server in MC_CONFIG:
        mc_index += 1
        mc_single = memcache.Client([mc_server], debug=0)
        mc_name = "mc%d" % mc_index
        mc_dict[mc_name] = mc_single
        duplicate_uids[mc_name] = {}

    for options_dict in MONGO_CONFIG:
        opt = ClassDict(options_dict)
        connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
        db = getattr(connection, opt.mongo_base, None)
        if db:
            ## mongoDB.addQuery("pers", "find", ({"key":data_key},), callback, params)
            coll = getattr(db, "pers")
            func = getattr(coll, "find")

            reply = func(
                new=True)  # new: ?????? ??? ???????????????(????? update ??find_and_modify)
            print "CHECK MONGO base %s -- find reply count: %s" % (opt.mongo_base, reply.count())

            for obj in reply:
                # -----------------------------------------------------------------------------------------
                # MONGO
                data_json = obj["data"]
                pers_key = obj["key"]
                checkJsonData(pers_key, data_json, mongo_counters, "mongo")

                # -----------------------------------------------------------------------------------------
                # MEMCACHE (ALL)
                mc_obj = mc.get(str(pers_key))
                if mc_obj:
                    checkJsonData(pers_key, mc_obj, mc_counters, "mc")
                else:
                    print "! no memcache data for pers_key %s" % pers_key

                # -----------------------------------------------------------------------------------------
                # MEMCACHE (BY SINGLE INSTANCE)
                for mc_name, mc_single in mc_dict.iteritems():
                    mc_obj = mc_single.get(str(pers_key))
                    if mc_obj:
                        checkJsonData(pers_key, mc_obj, single_mc_counters, mc_name)

    print "MONGO TOTALS: checked %d, no_key %d, no_uid %d, mismatch_uid %d" \
          % (mongo_counters.total_checked, mongo_counters.no_key, mongo_counters.no_uid, mongo_counters.mismatch_uid)

    print "MC TOTALS: checked %d, no_key %d, no_uid %d, mismatch_uid %d" \
          % (mc_counters.total_checked, mc_counters.no_key, mc_counters.no_uid, mc_counters.mismatch_uid)


# -----------------------------------------------------------------------------------------
def clearUserData(uid):
    pers_key = "data_%d" % uid
    pers_data = '{"db":{"db":{"fraction":"N","original_uid":%d},"model":{}}}' % uid

    print "clearUserData [%d], pers_key %s" % (uid, pers_key)
    print "USING MONGO server list: %s" % (MONGO_CONFIG)
    print "USING MC server list: %s" % (MC_CONFIG)

    for options_dict in MONGO_CONFIG:
        opt = ClassDict(options_dict)
        connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
        db = getattr(connection, opt.mongo_base, None)
        if db:
            ## mongoDB.addQuery("pers", "find", ({"key":data_key},), callback, params)
            coll = getattr(db, "pers")
            func = getattr(coll, "find_and_modify")

            # new: ?????? ??? ???????????????(????? update ??find_and_modify)
            reply = func({"key": pers_key}, {"$set": {"data": pers_data}}, upsert=False, new=True)
            print "mongo %s find_and_modify reply: %s" % (opt.mongo_base, reply)

    mc = memcache.Client(MC_CONFIG, debug=0)

    mc_reply = mc.replace(str(pers_key), str(pers_data))
    print "mc replace reply: ", mc_reply


# -----------------------------------------------------------------------------------------
# handler_function(sn_id, sn_login, uid, acc) - ??? ????? ????????????? ? ????? acc.db ?acc.model
def handleUserData(sn_id, sn_login, uid, handler_function=None, save_handled_data=0, **kwargs):
    pers_key = "data_%d" % uid

    for options_dict in MONGO_CONFIG:
        opt = ClassDict(options_dict)
        try:
            connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
            db = getattr(connection, opt.mongo_base, None)
            if db:
                ## mongoDB.addQuery("pers", "find", ({"key":data_key},), callback, params)
                coll = getattr(db, "pers")
                func = getattr(coll, "find")

                reply = func({"key": pers_key},
                             new=True)  # new: ?????? ??? ???????????????(????? update ??find_and_modify)
                print "CHECK MONGO base %s -- find reply count: %s" % (opt.mongo_base, reply.count())

                iteration = 0
                for obj in reply:
                    iteration += 1
                    # ??? persistent ??????? ? MONGO
                    data_json = obj["data"]
                    pers_key = obj["key"]

                    ##print "data_json: %r..., type %s" % (str(data_json)[:1024], type(data_json))

                    acc = PersistentDataManager.newSimpleDataAcc(data_json)

                    # "pretty" debug dump to file:
                    if DUMP_INPUT_DATA:
                        cache_dict = PersistentDataManager.makeSaveDict(acc)
                        dump_filename = OUT_PATH + "user_cache_IN__%s_%s_uid_%d_iter_%d.txt" % (
                        sn_id, sn_login, uid, iteration)
                        dump_file = open(dump_filename, "wt")
                        dump_file.write(prepare_printable_dump(cache_dict))
                        dump_file.close()

                    if handler_function:
                        try:
                            reply_ok = handler_function(sn_id, sn_login, uid, acc, iteration, **kwargs)

                            print "reply_ok:%s, db_dict now: %s...\n model_dict: %s..." % (
                                reply_ok, str(acc.db)[:512], str(acc.model)[:512])

                            if reply_ok and save_handled_data:
                                # ????? ??????????????

                                # "pretty" debug dump to file
                                cache_dict = PersistentDataManager.makeSaveDict(acc)
                                if DUMP_OUTPUT_DATA:
                                    dump_filename = OUT_PATH + "user_cache_OUT_%s_%s_uid_%d_iter_%d.txt" % (
                                        sn_id, sn_login, uid, iteration)
                                    dump_file = open(dump_filename, "wt")
                                    dump_file.write(prepare_printable_dump(cache_dict))
                                    dump_file.close()

                                # ----------------------------
                                # prepare new data_json
                                new_data_json = PersistentDataManager.saveReadyDict(cache_dict)

                                # SAVE to MONGO
                                func = getattr(coll, "find_and_modify")
                                # new: ?????? ??? ???????????????(????? update ??find_and_modify)
                                mongo_reply = func({"key": pers_key}, {"$set": {"data": new_data_json}}, upsert=False,
                                                   new=True)
                                print "mongo %s find_and_modify reply: %s..." % (
                                opt.mongo_base, str(mongo_reply)[:1024])

                                return mongo_reply
                            else:
                                return 1  # ? ?? ?????????
                        except:
                            catch()
                            print "ERROR handling data for user %s" % uid

            else:
                print "ERROR finding mongo database %s" % opt.mongo_base

        except:
            catch()
            print "ERROR connecting to mongo at %s:%s" % (opt.mongo_addr, opt.mongo_port)


# -----------------------------------------------------------------------------------------
# ????? ??????? ????(????? key="data_<uid>" ?????
def foreachDuplicateData(foreach_handler_function=None, save_input_data=0, delete_duplicates=0, **kwargs):
    processed_keys = {}
    # memcache ??????, ?? ???? ????? ????
    mc = memcache.Client(MC_CONFIG, debug=0)

    for options_dict in MONGO_CONFIG:
        opt = ClassDict(options_dict)
        connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
        mongo_db = getattr(connection, opt.mongo_base, None)
        if mongo_db:
            coll = getattr(mongo_db, "pers")
            all = coll.find(new=True, timeout=False, snapshot=True)  # ??????????????
            all.batch_size(FOREACH_BATCH_SIZE)
            print "FOREACH user (mongo base %s) -- find record count: %s" % (opt.mongo_base, all.count())

            load_iteration = 0
            obj_iteration = 0
            for obj in all:
                load_iteration += 1
                obj_iteration += 1
                # ??? persistent ??????? ? MONGO
                pers_key = obj.get("key", None)
                if not pers_key:
                    print "bad key %s" % pers_key
                    continue

                if not pers_key in processed_keys:
                    if save_input_data:
                        print "[%.3f] process key: %s" % (time.time(), pers_key)
                    processed_keys[pers_key] = 1

                    replies = coll.find({"key": pers_key}, new=True)
                    if replies.count() > 1:
                        print "[%.3f] DUPLICATE key %s: count=%s" % (time.time(), pers_key, replies.count())

                        main = coll.find_one({"key": pers_key}, new=True)
                        main_id = main.get("_id", None)
                        print "(key %s) MAIN _id=%s " % (pers_key, main_id)

                        best_id = -1
                        best_fame = -1
                        best_server_time = -1
                        best_hero_count = -1
                        best_hero_exp = -1
                        best_building_lvl = -1

                        iteration = 0
                        for item in replies:
                            iteration += 1
                            load_iteration += 1

                            item_stamp = item.get("stamp", None)
                            item_id = item.get("_id", None)
                            print "(key %s) [%d] item _id=%s, stamp=%s" % (pers_key, iteration, item_id, item_stamp)

                            data_json = item.get("data", None)
                            if data_json:
                                # ????uid
                                key_coll = pers_key.split("_")
                                if len(key_coll) == 2:
                                    prefix = key_coll[0]
                                    uid = long(key_coll[1])
                                else:
                                    print "! persistence WARNING: bad key (%s)" % (pers_key)
                                    # dict_counters.no_key += 1
                                    continue

                                try:
                                    ## t0 = time.time()
                                    acc = PersistentDataManager.newSimpleDataAcc(data_json)
                                    MD = ModelData()
                                    MD.load(acc.model)
                                    MD.init(changeWriter=None)
                                    ## t1 = time.time()
                                    ## print "simple load time: %.3f" % (t1-t0)
                                except:
                                    catch()
                                    print "ERROR loading data for user %s" % uid
                                    continue

                                try:
                                    # ----------------------------
                                    # "pretty" debug dump to file:
                                    if DUMP_INPUT_DATA:
                                        cache_dict = PersistentDataManager.makeSaveDict(acc)
                                        dump_filename = OUT_PATH + "user_cache_IN__uid_%d_iter_%d.txt" % (
                                        uid, iteration)
                                        dump_file = open(dump_filename, "wt")
                                        dump_file.write(prepare_printable_dump(cache_dict))
                                        dump_file.close()
                                except:
                                    catch()
                                    print "WARNING: error writing input dump for user %s" % uid

                                fame = pathFind(acc.model, "ModelData/Fame") or pathFind(acc.model,
                                                                                         "ModelData/LordInfo/LordInfo/Fame")
                                server_time = pathFind(acc.model, "ModelData/ServerTime")
                                next_uid = pathFind(acc.model, "ModelData/next_uid_")
                                Heroes = pathFind(acc.model, "ModelData/Heroes/Set") or {}
                                auid = pathFind(acc.db, "auid")
                                nick = pathFind(acc.db, "nick") or ""
                                sn_nick = pathFind(acc.db, "sn_nick") or ""

                                print u"- [%s] auid: %8s, Fame: %10s, ServerTime: %32s, next_uid_: %10s, #heroes: %3s, heroes_exp: %r, building_lvl: %r, nick:%r, sn_nick:%r" \
                                      % (iteration, auid, fame, time.ctime(server_time), next_uid, len(Heroes),
                                         MD.getHeroesExp(),
                                         MD.getBuildingsLvl(), nick, sn_nick)

                                if best_fame < fame:
                                    best_id = item_id
                                    best_fame = fame
                                    best_hero_count = len(Heroes)
                                    best_hero_exp = MD.getHeroesExp()
                                    best_building_lvl = MD.getBuildingsLvl()
                                    best_server_time = server_time
                                elif best_fame == fame and best_hero_count < len(Heroes):
                                    best_id = item_id
                                    best_fame = fame
                                    best_hero_count = len(Heroes)
                                    best_hero_exp = MD.getHeroesExp()
                                    best_building_lvl = MD.getBuildingsLvl()
                                    best_server_time = server_time
                                elif best_fame == fame and best_hero_count == len(
                                        Heroes) and best_hero_exp < MD.getHeroesExp():
                                    best_id = item_id
                                    best_fame = fame
                                    best_hero_count = len(Heroes)
                                    best_hero_exp = MD.getHeroesExp()
                                    best_building_lvl = MD.getBuildingsLvl()
                                    best_server_time = server_time
                                elif best_fame == fame and best_hero_count == len(
                                        Heroes) and best_hero_exp == MD.getHeroesExp() and best_building_lvl < MD.getBuildingsLvl():
                                    best_id = item_id
                                    best_fame = fame
                                    best_hero_count = len(Heroes)
                                    best_hero_exp = MD.getHeroesExp()
                                    best_building_lvl = MD.getBuildingsLvl()
                                    best_server_time = server_time
                                elif best_fame == fame and best_hero_count == len(
                                        Heroes) and best_hero_exp == MD.getHeroesExp() and best_building_lvl == MD.getBuildingsLvl() and best_server_time < server_time:
                                    best_id = item_id
                                    best_fame = fame
                                    best_hero_count = len(Heroes)
                                    best_hero_exp = MD.getHeroesExp()
                                    best_building_lvl = MD.getBuildingsLvl()
                                    best_server_time = server_time

                            else:
                                print "BAD data for key %s, _id %s" % (pers_key, item_id)

                        print "best record found for auid=%s: id=%s, fame=%s, datetime=%r" \
                              % (auid, best_id, best_fame, datetime.datetime.fromtimestamp(best_server_time).ctime())

                        if best_id != main_id:
                            print "--ACHTUNG! best record != main record found for auid=%s" % (auid)

                        if delete_duplicates:
                            res = coll.remove({"key": pers_key, "_id": {"$ne": best_id}})
                            print "REMOVE duplicates (except id=%s) result: %s" % (best_id, res)

                    time.sleep(FOREACH_SLEEP_MSEC_PER_USER / 1000.0)  # ??? ? ???? ?? ?????? ?????

                    # ~ else:
                    # ~ print "key %s: single" % pers_key
                    # ~ else:
                    # ~ print "key %s: already processed" % pers_key

                if load_iteration % FOREACH_USERS_PER_GC_COLLECT == 0:
                    t0 = time.time()
                    collect_count = gc.collect()
                    t1 = time.time()
                    print "gc time: %.3f (collected: %d), passed %d/%d records" % (
                        t1 - t0, collect_count, obj_iteration, all.count())

    print "foreachDuplicateData done."


def isUserOnline(auid):
    """ ????????, ??? ? ?????? ?auid'? '<auid>' """
    fsn_snid, fsn_snuid = getSocialRequisitesByAuid(auid)
    if fsn_snid and fsn_snuid:
        login = str("%s#%s" % (fsn_snid, fsn_snuid))
        ru_sql_db = SyncSqlManager(ClassDict(SQL_CONFIG[0]))
        ru_sql_db.openConnection()
        sql_reply = ru_sql_db.syncSqlQuery("SELECT server_id FROM tbl_login WHERE login='%s'" % login)
        if sql_reply:
            print str(sql_reply)
            ws = sql_reply[0]["server_id"]
            if ws != 0:
                return True
            else:
                return False
        else:
            print "Can't find SQL user for account with login %r" % login
            return False
    else:
        return False


# ---------------------------------------------------------------------------------------------------------
# ?????? ????? ?? {_id="data_XXXX"}, ?????? ???????? ???? ?????; ???? "??????? ???? ??? (? Fame), ?????????
def removeDuplicateDataByCollection(id_coll_name, key_name, save_input_data=0, delete_duplicates=0):
    processed_keys = {}
    for options_dict in MONGO_CONFIG:
        opt = ClassDict(options_dict)
        connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
        mongo_db = getattr(connection, opt.mongo_base, None)
        if mongo_db:
            coll = getattr(mongo_db, "pers")
            id_coll = getattr(mongo_db, id_coll_name)
            if coll and id_coll:
                all_ids = id_coll.find()
                print "(mongo base %s) id collection '%s' record count=%s" % (
                opt.mongo_base, id_coll_name, all_ids.count())

                load_iteration = 0
                obj_iteration = 0

                for rec in all_ids:
                    pers_key = rec.get(key_name)
                    if not pers_key:
                        print "bad key %s" % pers_key
                        return

                    replies = coll.find({"key": pers_key}, new=True)
                    print "key=%r, data record count=%s" % (pers_key, replies.count())

                    load_iteration += 1
                    obj_iteration += 1
                    isOnline = False
                    if replies and replies.count() > 1:
                        print "[%.3f] DUPLICATE key %s: count=%s" % (time.time(), pers_key, replies.count())

                        main = coll.find_one({"key": pers_key}, new=True)
                        main_id = main.get("_id", None)
                        print "(key %s) MAIN _id=%s " % (pers_key, main_id)

                        best_id = -1
                        best_fame = -1
                        best_server_time = -1
                        best_hero_count = -1
                        best_hero_exp = -1
                        best_building_lvl = -1

                        iteration = 0
                        for item in replies:
                            iteration += 1
                            load_iteration += 1

                            item_stamp = item.get("stamp", None)
                            item_id = item.get("_id", None)
                            print "(key %s) [%d] item _id=%s, stamp=%s" % (pers_key, iteration, item_id, item_stamp)

                            data_json = item.get("data", None)
                            if data_json:
                                # ????uid
                                key_coll = pers_key.split("_")
                                if len(key_coll) == 2:
                                    prefix = key_coll[0]
                                    uid = long(key_coll[1])
                                else:
                                    print "! persistence WARNING: bad key (%s)" % (pers_key)
                                    # dict_counters.no_key += 1
                                    continue

                                try:
                                    ## t0 = time.time()
                                    acc = PersistentDataManager.newSimpleDataAcc(data_json)
                                    MD = ModelData()
                                    MD.load(acc.model)
                                    MD.init(changeWriter=None)
                                    ## t1 = time.time()
                                    ## print "simple load time: %.3f" % (t1-t0)
                                except:
                                    catch()
                                    print "ERROR loading data for user %s" % uid
                                    continue

                                try:
                                    # ----------------------------
                                    # "pretty" debug dump to file:
                                    if DUMP_INPUT_DATA:
                                        cache_dict = PersistentDataManager.makeSaveDict(acc)
                                        dump_filename = OUT_PATH + "user_cache_IN__uid_%d_iter_%d.txt" % (
                                        uid, iteration)
                                        dump_file = open(dump_filename, "wt")
                                        dump_file.write(prepare_printable_dump(cache_dict))
                                        dump_file.close()
                                except:
                                    catch()
                                    print "WARNING: error writing input dump for user %s" % uid

                                fame = pathFind(acc.model, "ModelData/Fame") or pathFind(acc.model,
                                                                                         "ModelData/LordInfo/LordInfo/Fame")
                                server_time = pathFind(acc.model, "ModelData/ServerTime")
                                next_uid = pathFind(acc.model, "ModelData/next_uid_")
                                Heroes = pathFind(acc.model, "ModelData/Heroes/Set") or {}
                                auid = pathFind(acc.db, "auid")
                                nick = pathFind(acc.db, "nick") or ""
                                sn_nick = pathFind(acc.db, "sn_nick") or ""

                                # ????, ??? ? ??????
                                isOnline = isUserOnline(auid)
                                if isOnline:
                                    break

                                print u"- [%s] auid: %8s, Fame: %10s, ServerTime: %32s, next_uid_: %10s, #heroes: %3s, heroes_exp: %r, building_lvl: %r, nick:%r, sn_nick:%r" \
                                      % (iteration, auid, fame, time.ctime(server_time), next_uid, len(Heroes),
                                         MD.getHeroesExp(),
                                         MD.getBuildingsLvl(), nick, sn_nick)

                                if best_fame < fame:
                                    best_id = item_id
                                    best_fame = fame
                                    best_hero_count = len(Heroes)
                                    best_hero_exp = MD.getHeroesExp()
                                    best_building_lvl = MD.getBuildingsLvl()
                                    best_server_time = server_time
                                elif best_fame == fame and best_hero_count < len(Heroes):
                                    best_id = item_id
                                    best_fame = fame
                                    best_hero_count = len(Heroes)
                                    best_hero_exp = MD.getHeroesExp()
                                    best_building_lvl = MD.getBuildingsLvl()
                                    best_server_time = server_time
                                elif best_fame == fame and best_hero_count == len(
                                        Heroes) and best_hero_exp < MD.getHeroesExp():
                                    best_id = item_id
                                    best_fame = fame
                                    best_hero_count = len(Heroes)
                                    best_hero_exp = MD.getHeroesExp()
                                    best_building_lvl = MD.getBuildingsLvl()
                                    best_server_time = server_time
                                elif best_fame == fame and best_hero_count == len(
                                        Heroes) and best_hero_exp == MD.getHeroesExp() and best_building_lvl < MD.getBuildingsLvl():
                                    best_id = item_id
                                    best_fame = fame
                                    best_hero_count = len(Heroes)
                                    best_hero_exp = MD.getHeroesExp()
                                    best_building_lvl = MD.getBuildingsLvl()
                                    best_server_time = server_time
                                elif best_fame == fame and best_hero_count == len(
                                        Heroes) and best_hero_exp == MD.getHeroesExp() and best_building_lvl == MD.getBuildingsLvl() and best_server_time < server_time:
                                    best_id = item_id
                                    best_fame = fame
                                    best_hero_count = len(Heroes)
                                    best_hero_exp = MD.getHeroesExp()
                                    best_building_lvl = MD.getBuildingsLvl()
                                    best_server_time = server_time

                            else:
                                print "BAD data for key %s, _id %s" % (pers_key, item_id)
                        if isOnline:
                            print "User with auid=%r is online now. Duplicate wasn't removed." % auid
                            continue

                        print "best record found for auid=%s: id=%s, fame=%s, datetime=%r" \
                              % (auid, best_id, best_fame, datetime.datetime.fromtimestamp(best_server_time).ctime())

                        if best_id != main_id:
                            print "--ACHTUNG! best record != main record found for auid=%s" % (auid)

                        if delete_duplicates:
                            res = coll.remove({"key": pers_key, "_id": {"$ne": best_id}})
                            print "REMOVE duplicates (except id=%s) result: %s" % (best_id, res)

                    time.sleep(FOREACH_SLEEP_MSEC_PER_USER / 1000.0)  # ??? ? ???? ?? ?????? ?????

                    if load_iteration % FOREACH_USERS_PER_GC_COLLECT == 0:
                        t0 = time.time()
                        collect_count = gc.collect()
                        t1 = time.time()
                        print "gc time: %.3f (collected: %d), passed %d/%d records" % (
                            t1 - t0, collect_count, obj_iteration, all_ids.count())

            else:
                print "ERROR: can't find necessary collections ('pers'=%s, id_coll %r=%s)" % (coll, id_coll)
        else:
            print "ERROR: can't connect to mongo base %r" % opt.mongo_base

    print "foreachDuplicateData done."


# -----------------------------------------------------------------------------------------
# ????? ??mongo-??????, ?? ??? ?????handler_function
def foreachUserData(foreach_handler_function=None, save_input_data=0, save_handled_data=0, dump_handled_data=1,
                    shard_writes=0, **kwargs):
    # memcache ??????, ?? ???? ????? ????
    # ~ mc = memcache.Client(MC_CONFIG, debug=0)

    mongo_shards = []
    for options_dict in MONGO_CONFIG:
        opt = ClassDict(options_dict)
        connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
        mongo_db = getattr(connection, opt.mongo_base, None)
        mongo_shards.append((mongo_db, opt))

    for mongo_db, opt in mongo_shards:
        if mongo_db:
            ## mongoDB.addQuery("pers", "find", ({"key":data_key},), callback, params)
            coll = getattr(mongo_db, "pers")
            reply = coll.find(new=True, timeout=False, snapshot=True)  # ??????????????
            reply.batch_size(FOREACH_BATCH_SIZE)
            reply_count = reply.count()
            print "FOREACH user (mongo base %s) -- find reply count: %s" % (opt.mongo_base, reply_count)

            iteration = 0
            for obj in reply:
                iteration += 1

                # ??? persistent ??????? ? MONGO
                data_json = obj.get("data", None)
                if not data_json: continue
                pers_key = obj.get("key", None)
                if not pers_key: continue

                # ????uid
                key_coll = pers_key.split("_")
                if len(key_coll) == 2:
                    prefix = key_coll[0]
                    uid = long(key_coll[1])
                else:
                    print "! persistence WARNING: bad key (%s)" % (pers_key)
                    dict_counters.no_key += 1
                    continue

                print "foreach: uid %s, time %.3f" % (str(uid), time.time())

                try:
                    ## t0 = time.time()
                    acc = PersistentDataManager.newSimpleDataAcc(data_json)
                    ## t1 = time.time()
                    ## print "simple load time: %.3f" % (t1-t0)
                except:
                    catch()
                    print "ERROR loading data for user %s" % uid
                    continue

                try:
                    # ----------------------------
                    # "pretty" debug dump to file:
                    if DUMP_INPUT_DATA:
                        cache_dict = PersistentDataManager.makeSaveDict(acc)
                        dump_filename = OUT_PATH + "user_cache_IN__uid_%d_iter_%d.txt" % (uid, iteration)
                        dump_file = open(dump_filename, "wt")
                        dump_file.write(prepare_printable_dump(cache_dict))
                        dump_file.close()
                except:
                    catch()
                    print "WARNING: error writing input dump for user %s" % uid

                if foreach_handler_function:
                    try:
                        foreach_handler_function(str(uid), str(uid), uid, acc, iteration=iteration, **kwargs)

                        if save_handled_data:
                            # ????? ??????????????
                            cache_dict = PersistentDataManager.makeSaveDict(acc)

                            if DUMP_OUTPUT_DATA:
                                # "pretty" debug dump to file
                                dump_filename = OUT_PATH + "user_cache_OUT_uid_%d_iter_%d.txt" % (uid, iteration)
                                dump_file = open(dump_filename, "wt")
                                dump_file.write(prepare_printable_dump(cache_dict))
                                dump_file.close()

                            # ----------------------------
                            # prepare new data_json
                            new_data_json = PersistentDataManager.saveReadyDict(cache_dict)

                            # ----------------------------
                            # SAVE to MONGO
                            write_collection = coll
                            if shard_writes:
                                db_index = (crc_hash(pers_key) % len(MONGO_CONFIG))
                                write_mongo_db, write_opt = mongo_shards[db_index]
                                print "redirecting mongo write [key %s] to shard %s (read shard %s)" % (
                                    pers_key, write_opt.mongo_base, opt.mongo_base)
                                write_collection = getattr(write_mongo_db, "pers")

                            # new: ?????? ??? ???????????????(????? update ??find_and_modify)
                            modify_reply = write_collection.find_and_modify({"key": pers_key},
                                                                            {"$set": {"data": new_data_json}},
                                                                            upsert=True, new=True)
                            print "mongo %s find_and_modify reply: %s..." % (opt.mongo_base, str(modify_reply)[:512])

                            if modify_reply and write_mongo_db != mongo_db:
                                remove_reply = coll.remove({"key": pers_key})
                                print "reshard remove reply: %s..." % str(remove_reply)[:512]

                                # ----------------------------
                                # SAVE to MEMCACHE
                                # ~ mc = memcache.Client(MC_CONFIG, debug=0)
                                # ~ mc_reply = mc.replace(str(pers_key), str(new_data_json))
                                # ~ print "mc replace reply: ", mc_reply

                    except:
                        catch()
                        print "ERROR handling data for user %s" % uid

                time.sleep(FOREACH_SLEEP_MSEC_PER_USER / 1000.0)  # ??? ? ???? ?? ?????? ?????

                if iteration % FOREACH_USERS_PER_GC_COLLECT == 0:
                    t0 = time.time()
                    collect_count = gc.collect()
                    t1 = time.time()
                    print "gc time: %.3f (collected: %d), passed %d/%d records" % (
                    t1 - t0, collect_count, iteration, reply_count)


# -----------------------------------------------------------------------------------------
# handler_function ??    handleUserData
def dumpUserData(sn_id, sn_login, uid, acc, iteration, zip=True, **kwargs):
    dump_filename = OUT_PATH + "user_data_%s_%s_uid_%d_iter_%d.txt" % (sn_id, sn_login, uid, iteration)

    try:
        dump_file = open(dump_filename, "wb")

        # ----------------------------
        # prepare new data_json
        new_data_unicode = PersistentDataManager.saveData(acc, zip)

        print "\nnew_data_unicode (len %d): %r\n...\n%r" % (
            len(new_data_unicode), new_data_unicode[:128], new_data_unicode[-128:])
        encoded_userdata = new_data_unicode.encode("latin1")
        print "\nencoded_userdata (len %d): %r\n...\n%r" % (
            len(encoded_userdata), encoded_userdata[:128], encoded_userdata[-128:])

        dump_file.write(encoded_userdata)
        dump_file.close()

    except:
        catch()
        print "ERROR dumping file: %s" % dump_filename


def checkUserData(sn_id, sn_login, uid, acc, iteration, zip=True, **kwargs):
    iDict = kwargs['I']
    model = ModelData()
    model.init(changeWriter=None)
    model.create(iDict, acc, create_version=u"", create_heroes=0, sex=acc['db']['sex'], guest=False)
    model.load(acc['model'])
    model.init(changeWriter=None)
    isValid, invalidText = model.checkValidity(acc, iDict.SD)
    if not isValid:
        print "Error %s %s %s %s" % (sn_id, sn_login, uid, invalidText)


# ??? ???? ?? ???? ?? ????(????, ?? ???????? ????)
def passUserData(sn_id, sn_login, uid, acc, iteration, zip=True, **kwargs):
    pass


def dumpMillionaire(sn_id, sn_login, uid, acc, iteration, zip=True, **kwargs):
    iDict = kwargs['I']
    model = ModelData()
    model.init(changeWriter=None)
    model.create(iDict, acc, create_version=u"", create_heroes=0, sex=acc['db']['sex'], guest=False)
    model.load(acc['model'])
    model.init(changeWriter=None)
    if model.Resources.Silver > 1000000:
        print "======================================================================================================================================"
        print "Millionaire! %s %s %s %r" % (sn_id, sn_login, uid, acc.db.nick)
        print "0 - Silver = %r Resource1 = %r Resource2 = %r Resource3 = %r Perl = %r Population = %r" % (
            model.Resources.Silver, model.Resources.Resource1, model.Resources.Resource2, model.Resources.Resource3,
            model.Resources.Perl, model.Resources.Population)
        print "1 - SNID = %r SNUID = %r" % (acc.db.snid, acc.db.snuid)
        print "2 - NICK = %r SN_NICK = %r" % (acc.db.nick, acc.db.sn_nick)
        print "3 - Registration date = %r" % acc.db.registration_date
        print "4 - None"
        print "5 - None"
        print "6 - Lord level = %r" % iDict.SD.getFameLevel(model.getFame())
        print "7 - Number of magnificent talents = %r" % model.getNumberOfTalents("magnificent", iDict.SD)
        print "8 - Number of all talents = %r" % model.getNumberOfTalents(None, iDict.SD)
        print "9 - Number of heroes 20 level = %r" % model.getNumberOfHeroes(20, iDict.SD)
        print "======================================================================================================================================"


def dumpPopulationLimit(sn_id, sn_login, uid, acc, iteration, zip=True, **kwargs):
    iDict = kwargs['I']
    model = ModelData()
    model.init(changeWriter=None)
    model.create(iDict, acc, create_version=u"", create_heroes=0, sex=acc['db']['sex'], guest=False)
    model.load(acc['model'])
    model.init(changeWriter=None)
    if model.ResourcesLimit.Population > kwargs['limit']:
        print "%r %r %r" % (acc.db.auid, model.ResourcesLimit.Population, acc.db.nick)
        # print "======================================================================================================================================"
        # print "Population limit! %s %s %s %r %r" % (sn_id, sn_login, uid, acc.db.nick, acc.db.auid)
        # print "0 - Population = %r Population Limit = %r" % (model.Resources.Population, model.ResourcesLimit.Population)
        # print "======================================================================================================================================"


# -----------------------------------------------------------------------------------------
# ????? ????????????????????? ????????? ? ??????
def dumpUserAndAggregatorData(snid, snuid, uid, acc, iteration, **kwargs):
    print "\n------ dumpUserAndAggregatorData ------"
    # ???????? ?? ?????????? ???.??????:
    HTTP = ISyncHttp()
    AGG = IRealSocialAggregator(coord_cfg.COORDINATOR_SOCIAL_AGGREGATOR_ADDRESS, SOCAGG_VERSION, HTTP)
    I = ClassDict(AGG=AGG)

    # ????? ??????? callback ? ????wrapper-?(?? ??? ?? ???
    class ArgWrapper:
        def __init__(self, I, acc):
            self.I = I
            self.auid = 0
            self.error = 0
            self.acc = acc

        def run(self, snid, snuid):
            self.I.AGG.findUser(snid, snuid, callback=self.onFindUser)

        def onFindUser(self, agg_response):
            if agg_response and (not agg_response.get("error")):
                self.auid = agg_response.get("auid", 0)
                print "check auid match for user '%s:%s' -- acc.db.auid=%s, aggregator auid=%s" % (
                    snid, snuid, acc.db.auid, self.auid)
                if self.auid and (self.auid == acc.db.auid):
                    # TODO...
                    acc.db.aggregator = ClassDict(auid=self.auid)

                    self.I.AGG.getInfo(self.auid, None, include_secure_data=1, callback=self.onGetInfo)
                else:
                    self.error = "ERROR: bad aggregator auid for user %s:%s" % (snid, snuid)
            else:
                self.error = "ERROR: aggregator bad reply for findUser: %s" % (agg_response)

        def onGetInfo(self, agg_response):
            if agg_response and (not agg_response.get("error")):
                acc.db.aggregator.get_info = agg_response.get("get_info", {})
            else:
                self.error = "ERROR: aggregator bad reply for getInfo: %s" % (agg_response)

    argWrapper = ArgWrapper(I, acc)

    try:
        # ?? ???????? ? ??????auid ?? ???? sn-?????
        argWrapper.run(snid, snuid)
        if not argWrapper.error:
            # ?, ???, ?????, ?????????(???? acc.db.aggregator) ????
            dumpUserData(snid, snuid, uid, acc, iteration, zip=False, **kwargs)
        else:
            print argWrapper.error
    except:
        print catch()

    print "------ /dumpUserAndAggregatorData -------\n"


# -----------------------------------------------------------------------------------------
def dumpResourcesCSV(sn_id, sn_login, uid, acc, iteration, auid=0, csv_file=None, **kwargs):
    resourceTable = pathFind(acc.model, "ModelData/Resources/ResourceTable")
    print "resourceTable(auid=%s): %s" % (auid, resourceTable)
    if resourceTable:
        csv_file.write("%d;%d;%d;%d;%d;%d;%d;%d;%d;\n" % (auid,
                                                          toint(resourceTable.get("Silver")),
                                                          toint(resourceTable.get("Perl")),
                                                          toint(resourceTable.get("RedPerl")),
                                                          toint(resourceTable.get("Resource1")),
                                                          toint(resourceTable.get("Resource2")),
                                                          toint(resourceTable.get("Resource3")),
                                                          toint(resourceTable.get("Gold")),
                                                          toint(resourceTable.get("Population")),
                                                          ))
        return 1  # ok


# -----------------------------------------------------------------------------------------
# handler_function ??    handleUserData
class MatchUserData:
    def __init__(self, path, socagr_url):
        self.f = open(path, 'wt')
        self.socagr_url = 'http://' + socagr_url + '/?'
        print 'Social aggregator address:', self.socagr_url

    def __call__(self, sn_id, sn_login, uid, acc, iteration, **kwargs):
        if acc.db.get('auid', None):
            args = {
                'action': 'get_info',
                'auid': acc.db['auid'],
                'snid': 'fb',
                'include_secure_data': 1,
                'version': '0.3.93',
            }
            address = self.socagr_url + urllib.urlencode(args)
            urlRequest = urllib2.Request(address, None, headers={"Accept-Encoding": "gzip"})
            response = urllib2.urlopen(urlRequest, None, timeout=10.0)
            headers = response.info()
            responseData = response.read()
            _data = json_loads(responseData)
            if _data['error'] == 0:
                for sn in ['fb']:
                    data = _data['get_info'][sn]
                    print acc.db['auid'], '->', sn, data['snuid']
                    self.f.write(
                        '%s\t%s\t%r\t%r\n' % (
                        acc.db['auid'], data['snuid'], acc.db.get('nick', '<unknown>'), data['name']))
                    self.f.flush()


class DumpUserData:
    def __init__(self, path):
        self.f = open(path, 'wt')

    def __call__(self, sn_id, sn_login, uid, acc, iteration, **kwargs):
        print "uid %s, time %.3f" % (uid, time.time())
        if acc.db.get('snuid', None):
            self.f.write('%s\n' % acc.db['snuid'])
            self.f.flush()


# -----------------------------------------------------------------------------------------
# handler_function ??    handleUserData
def replaceUserData(sn_id, sn_login, uid, acc, iteration, user_data_filename="", **kwargs):
    try:
        user_data_file = open(user_data_filename, "rb")
        userdata_string = user_data_file.read()
    except:
        catch()
        print "ERROR reading file: %s" % user_data_filename
        return

    if userdata_string:
        print "\nfile userdata_string (len %d): %r\n...\n%r" % (
            len(userdata_string), userdata_string[:128], userdata_string[-128:])
        unicode_userdata = unicode(userdata_string, "latin1")
        print "\nunicode_userdata (len %d): %r\n...\n%r" % (
            len(unicode_userdata), unicode_userdata[:128], unicode_userdata[-128:])
        load_acc = PersistentDataManager.newSimpleDataAcc(unicode_userdata)

    # ???????????????original uid (??.???, ??????, ?????? uid ? db.uid ????? ? auth)
    if load_acc.db.get("uid"):
        load_acc.db["uid"] = toint(uid)

    if load_acc.db and load_acc.model:
        # ??????? ? ???? ???(??????? ??? ????
        acc.db = load_acc.db
        acc.model = load_acc.model

    user_data_file.close()
    return 1  # ok


# -----------------------------------------------------------------------------------------
# foreach_handler_function ??    foreachUserData
def dumpUserHeroesData2Mysql(sn_id, sn_login, uid, acc, iteration, sql_options={}, **kwargs):
    auid = toint(acc.db.get("auid"))
    if auid:
        reliability = pathFind(acc.model, "ModelData/LordInfo/Reliability") or 0
        nick = acc.db.get("nick") or ''
        snid = acc.db.get("snid") or ''
        snuid = acc.db.get("snuid") or ''
        locale = acc.db.get("locale") or ''
        now = int(time.time())
        fraction = acc.db.get("fraction") or 'N'

        print "dumpUserHeroesData2Mysql: uid %d, auid %d, reliability %d, nick %r" % (uid, auid, reliability, nick)

        heroes_set = pathFind(acc.model, "ModelData/Heroes/Set")
        if heroes_set and isinstance(heroes_set, dict):
            for hero_key in heroes_set:
                hero_id = toint(hero_key)
                if hero_id:
                    hero_path = "ModelData/HeroesKeeper/Keeper/%d/Hero" % hero_id
                    hero = pathFind(acc.model, hero_path,
                                    force_int_keys=False)  # ???"???" ModelData, ??????? ????? ? ?? ? ???????? ?int
                    if hero:
                        is_hired = hero.get("Hired", 0)
                        if is_hired:
                            hero_crc = hero.get("PersistentId", 0)
                            hero_rating = tofloat(hero.get("Rating", 0.0))
                            hero_force = tofloat(hero.get("Force", 0))
                            hero_last_played = toint(hero.get("lastPlayed", 0))
                            if not (hero_crc and hero_rating):
                                print "WARNING: null hero_crc (%d) or rating(%d) for hero_id %d, path %s" % (
                                    hero_crc, hero_rating, hero_id, hero_path)

                            # ?, ???? ?????MYSQL
                            print "dumpUserHeroesData2Mysql params: %r,%r,%r,%r,%r,%r,%r,%r,%r,%r,%r,%r" \
                                  % (
                                  auid, hero_id, hero_crc, hero_rating, reliability, now, nick, snid, snuid, fraction,
                                  hero_force,
                                  hero_last_played)
                            query = u"INSERT INTO tbl_user_hero_stats (`auid`,`hero_id`,`hero_crc`,`hero_rating`,`reliability`,`timestamp`,`nickname`" \
                                    ",`snid`,`snuid`,`fraction`,`hero_force`,`hero_last_played`, `locale`)" \
                                    + u"VALUES (%d,%d,%d,%d,%d,%d,'%s','%s','%s','%s',%.3f,%d,'%s')" \
                                      % (
                                          auid, hero_id, hero_crc, hero_rating, reliability, now, nick, snid, snuid,
                                          fraction, hero_force,
                                          hero_last_played, locale)
                            reply = syncSqlCommand(query, sql_options)
                            print "- dumpUserHeroesData2Mysql (hero_id %d) query %r, reply: %r" % (
                            hero_id, query, reply)
                        else:
                            print "SKIP: hero_id %d not hired for uid=%s" % (hero_id, uid)
                    else:
                        print "WARNING: cant find hero_id %d (path %s) for uid=%d" % (hero_id, hero_path, uid)
                else:
                    print "WARNING: bad hero_id %d (hero_key %s) for uid=%d" % (hero_id, hero_key, uid)
        else:
            print "WARNING: bad heroes_set for uid=%d: %s" % (uid, str(heroes_set))
    else:
        print "WARNING: no auid for uid=%d" % (uid)


# -----------------------------------------------------------------------------------------
# foreach_handler_function ?? foreachUserData
def findUserByNickname(sn_id, sn_login, uid, acc, iteration, nick_unicode=u"", **kwargs):
    db_nick_unicode = acc.db.get("nick", "")
    auid = toint(acc.db.get("auid"))
    if db_nick_unicode == nick_unicode:
        print "findUserByNickname: uid=%d, auid=%d, found nick: %r" % (uid, auid, db_nick_unicode)


# -----------------------------------------------------------------------------------------
# handler_function ??    handleUserData
def changeUserFraction(sn_id, sn_login, uid, acc, iteration, fraction):
    print "setting fraction=%s for uid=%s" % (fraction, uid)
    acc.db.fraction = fraction
    return 1


# -----------------------------------------------------------------------------------------
# handler_function ??    handleUserData
def hireHero(sn_id, sn_login, uid, acc, iteration, hero_class_name):
    print "searching hero class_name=%s for uid=%s..." % (hero_class_name, uid)
    heroes = pathFind(acc.model, "ModelData/HeroesKeeper/Keeper")
    if heroes:
        for hero_id in heroes.keys():
            hero = heroes[hero_id]["Hero"]
            ## print "hero_id %s, class_name %s" % (hero_id, hero.get("class_name"))
            if hero and hero.get("class_name") == hero_class_name:
                print ">>> FOUND hero_id=%s, class_name=%s, setting Hired=true" % (hero_id, hero.get("class_name"))
                hero["Hired"] = True
                return 1
    else:
        print "no HeroesKeeper found"


def addModelValue(sn_id, sn_login, uid, acc, iteration, change_path, change_key, add_value):
    print "searching model data path %r[%r] for uid=%s..." % (change_path, change_key, uid)
    dct = pathFind(acc.model, change_path,
                   force_int_keys=False)  # ???"???" ModelData, ??????? ????? ? ?? ? ???????? ?int)
    if dct and isinstance(dct, dict):
        value_string = dct.get(change_key)
        try:
            old_value = int(value_string)
            dct[change_key] = max(old_value + add_value, 0)
            print ">>> SET new value %s = %s (old) + %s (add)" % (dct[change_key], old_value, add_value)
            return 1
        except:
            catch()
            print "ERROR: can't change key '%s' for uid=%s (was %s)" % (change_key, uid, value_string)
    else:
        print "ERROR: can't find dict path '%s' for uid=%s" % (change_path, uid)


def exportMysqlBuildings(sn_id, sn_login, uid, acc, iteration, sql_options={}, building_crc=0, timestamp=0, auid=0):
    keeper_path = "ModelData/ConstructionsKeeper/Keeper"
    keeper = pathFind(acc.model, keeper_path,
                      force_int_keys=False)  # ???"???" ModelData, ??????? ????? ? ?? ? ???????? ?int)
    pocket = pathFind(acc.model, "ModelData/Pocket/Set", force_int_keys=False) or {}
    if keeper and isinstance(keeper, dict):
        try:
            for str_building_id, constr in keeper.iteritems():
                if constr and isinstance(constr, dict):
                    building = constr.get("Construction")
                    if building and isinstance(building, dict):
                        print "building dict: %s" % building
                        crc = toint(building.get("PersistentId", 0))
                        building_id = toint(str_building_id)
                        print "exportMysqlBuildingsparams: auid %s, building_id %s, crc %s" % (auid, building_id, crc)
                        if crc and ((crc == building_crc) or (building_crc == 0)):
                            building_level = toint(building.get("Level", 0))
                            in_pocket = 1 if pocket.get(str_building_id, 0) else 0

                            # ?, ???? ?????MYSQL
                            print "- exportMysqlBuildingsparams: %r,%r,%r,%r,%r,%r" \
                                  % (auid, building_id, crc, building_level, timestamp, in_pocket)
                            query = u"INSERT INTO tbl_user_build_stats (`auid`,`build_id`,`build_crc`,`build_level`,`timestamp`,`in_pocket`) " \
                                    + u"VALUES (%d,%d,%d,%d,%d,%d)" \
                                      % (auid, building_id, crc, building_level, timestamp, in_pocket)
                            reply = syncSqlCommand(query, sql_options)
                            print "- exportMysqlBuildingsparams (auid %s, building_id %s) query %r, reply: %r" % (
                                auid, building_id, query, reply)
            return 1
        except:
            catch()
            print "ERROR: failed to export buildings for uid=%s" % (uid)
    else:
        print "ERROR: can't find keeper path %r for uid=%s" % (keeper_path, uid)


# ????? premium account ? ???????? ??? (?? ??? ??, ??????? ????? ????)
def addPremiumDuration(sn_id, sn_login, uid, acc, iteration, premium_duration):
    change_path = "ModelData/LordInfo/LordInfo"
    print "searching model data path %r for uid=%s..." % (change_path, uid)
    dct = pathFind(acc.model, change_path,
                   force_int_keys=False)  # ???"???" ModelData, ??????? ????? ? ?? ? ???????? ?int)
    if dct and isinstance(dct, dict):
        start = toint(dct.get("PremiumAccountStart", 0))
        end = toint(dct.get("PremiumAccountEnd", 0))
        print "found premium duration: start %s, end %s" % (start, end)
        now = toint(time.time())
        if start and end and (end > now):
            end += premium_duration
        else:
            start = now
            end = start + premium_duration
        dct["PremiumAccountStart"] = start
        dct["PremiumAccountEnd"] = end
        print "corrected premium duration: start %s, end %s, new LordInfo: %s" % (start, end, dct)
        return 1
    else:
        print "ERROR: can't find dict path '%s' for uid=%s" % (change_path, uid)


# ? ????snid, snlogin ?????????????????: ????????????????? ??????? ??????
def getSqlUserRequisites(sn_id, sn_login):
    login = "%s#%s" % (sn_id, sn_login.lower())

    CLUSTER_SQL_SERVER_COUNT = len(SQL_CONFIG)
    db_index = (crc_hash(login) % CLUSTER_SQL_SERVER_COUNT)
    options_dict = SQL_CONFIG[db_index]
    opts = ClassDict(options_dict)

    return login, opts, db_index


# ??????????? id ??? (if any)
def getSqlUserUID(login, opts):
    reply = syncSqlQuery("SELECT id FROM tbl_login WHERE login=%r" % login, opts)
    print "- getSqlUserUID reply: %r" % reply
    try:
        if reply[0].id:
            return reply[0].id
    except:
        pass


# ????? ??? ?????? ?tbl_login
def addNewSqlUser(id, login, pwd, opts):
    reply = syncSqlCommand("INSERT INTO tbl_login (id, login, pwd_md5) VALUES (%d, %r, %r)" % (id, login, pwd), opts)
    print "- addNewSqlUser reply: %r" % reply
    try:
        if reply:
            return reply
    except:
        pass


# ????? ??? ?????? ?tbl_login ??????????????
def addNewSqlUserDB(db, id, login, pwd):
    reply = db.syncSqlCommand("INSERT INTO tbl_login (id, login, pwd_md5) VALUES (%d, %r, %r)" % (id, login, pwd))
    return reply


# ????? ??? ?????? ?tbl_nick
def addNewSqlUserNickname(id, nick, opts):
    reply = syncSqlCommand(u"INSERT INTO tbl_nick (id, nick) VALUES (%d, '%s')" % (id, unicode(nick, 'utf8')), opts)
    print "- addNewSqlUserNickname reply: %r" % reply
    try:
        if reply:
            return reply
    except:
        pass


# ????? ??? ?????? ?tbl_nick ??????????????
def addNewSqlUserNicknameDB(db, id, nick):
    reply = db.syncSqlCommand(u"INSERT INTO tbl_nick (id, nick) VALUES (%d, '%s')" % (id, unicode(nick, 'utf8')))
    return reply


# ???? ?????? ? tbl_login
def deleteSqlUser(id, login, opts):
    cmd = "DELETE FROM tbl_login WHERE login=%r AND id=%d" % (login, toint(id))
    reply = syncSqlCommand(cmd, opts)
    print "- deleteSqlUser reply: %r" % reply
    try:
        if reply:
            return reply
    except:
        pass


# ???? ?????? ? tbl_login
def deleteSqlUser(id, opts):
    cmd = "DELETE FROM tbl_login WHERE id=%d" % toint(id)
    reply = syncSqlCommand(cmd, opts)
    print "- deleteSqlUser reply: %r" % reply
    try:
        if reply:
            return reply
    except:
        pass


# ???? ?????? ? tbl_login
def deleteSqlUsersRange(min_id, max_id, opts):
    cmd = "DELETE FROM tbl_login WHERE id>=%d AND id<=%d" % (toint(min_id), toint(max_id))
    reply = syncSqlCommand(cmd, opts)
    print "- deleteSqlUsersRange(%s) reply: %r" % (cmd, reply)
    try:
        if reply:
            return reply
    except:
        pass


# ???? ?????? ? tbl_nick
def deleteSqlUserNickname(id, opts):
    cmd = "DELETE FROM tbl_nick WHERE id=%d" % toint(id)
    reply = syncSqlCommand(cmd, opts)
    print "- deleteSqlUserNickname reply: %r" % reply
    try:
        if reply:
            return reply
    except:
        pass


# -----------------------------------------------------------
def grep_file(filename, model_string, outfile):
    f = open(filename, "rt")
    lines_found = 0

    for line in f:
        pos = line.find(model_string)
        if pos >= 0:
            outfile.write(line)
            lines_found += 1

    msg = "==================\n total lines found in file %r: %d \n" % (filename, lines_found)

    outfile.flush()
    print msg

    f.close()


# -----------------------------------------------------------
def grep_fb_users_from_file(filename):
    f = open(filename, "rt")

    model_string = "logged in user 'fb#"
    model_string2 = "(uid="

    for line in f:
        pos = line.find(model_string)
        if pos >= 0:
            fbid_string = line[pos + len(model_string):]
            pos2 = fbid_string.find("'")
            fbid_string = fbid_string[:pos2]

            pos3 = line.find(model_string2)
            uid_string = line[pos3 + len(model_string2):]
            pos4 = uid_string.find(")")
            uid_string = uid_string[:pos4]

            uid = int(uid_string)
            fbid = int(fbid_string)

            uid_list[uid] = fbid_string

            f_out.write(line)
            f_out.write("fbid %s:%d, uid %s:%d\n" % (fbid_string, fbid, uid_string, uid))

    msg = "total uids found: %d \n %s" % (len(uid_list), uid_list)
    f_out.write(msg)
    f_out.flush()
    print msg

    f.close()


def forEachMongoUserKey_AddMirrorRequest():
    mirror_config = ClassDict(MIRROR_CONFIG)
    print "USING MIRROR_CONFIG: %s" % (mirror_config)
    print "USING MONGO_CONFIG: %s" % (MONGO_CONFIG)
    import imirror

    mongo_shards = []
    for options_dict in MONGO_CONFIG:
        opt = ClassDict(options_dict)
        connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
        mongo_db = getattr(connection, opt.mongo_base, None)
        mongo_shards.append((mongo_db, opt))

    for mongo_db, opt in mongo_shards:
        if mongo_db:
            coll = getattr(mongo_db, "pers")
            reply = coll.find({}, {"_id": 1, "key": 1}, timeout=False,
                              snapshot=True)  # ????????? ??? ???, ??? ???? ??????????????
            reply.batch_size(FOREACH_BATCH_SIZE)
            reply_count = reply.count()
            print "FOREACH user (mongo base %s) -- find reply count: %s" % (opt.mongo_base, reply_count)

            iteration = 0
            for obj in reply:
                iteration += 1

                try:
                    # ??? persistent ??????? ? MONGO
                    pers_key = obj.get("key", None)
                    if not pers_key:
                        continue

                    # ????uid
                    key_coll = pers_key.split("_")
                    if len(key_coll) == 2:
                        prefix = key_coll[0]
                        uid = long(key_coll[1])
                    else:
                        print "! persistence WARNING: bad key (%s)" % (pers_key)
                        continue

                    ts = toint(time.time())
                    sql = "INSERT INTO tbl_queue (`data_type`,`data_id`,`timestamp`) VALUES (%d,%d,%d) ON DUPLICATE KEY UPDATE `timestamp`=%d" \
                          % (imirror.MirrorDataType.MODEL_DATA, uid, ts, ts)

                    sql_reply = syncSqlCommand(sql, mirror_config)
                    print "sql query: %r\n reply: %r" % (sql, sql_reply)

                except:
                    catch()
                    print "ERROR handling data for obj %s" % str(obj)

                time.sleep(FOREACH_SLEEP_MSEC_PER_USER / 1000.0)  # ??? ? ???? ?? ?????? ?????

                if iteration % FOREACH_USERS_PER_GC_COLLECT == 0:
                    t0 = time.time()
                    collect_count = gc.collect()
                    t1 = time.time()
                    print "gc time: %.3f (collected: %d), passed %d/%d records" % (
                    t1 - t0, collect_count, iteration, reply_count)

            print "DONE (mongo base %s: %d records)" % (opt.mongo_base, reply_count)


def forEachMongoUserKey_FindDuplicates():
    print "USING MONGO_CONFIG: %s" % (MONGO_CONFIG)
    mongo_shards = []
    for options_dict in MONGO_CONFIG:
        opt = ClassDict(options_dict)
        connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
        mongo_db = getattr(connection, opt.mongo_base, None)
        mongo_shards.append((mongo_db, opt))

    user_stamps = {}
    duplicates = {}

    for mongo_db, opt in mongo_shards:
        if mongo_db:
            coll = getattr(mongo_db, "pers")
            reply = coll.find({}, {"_id": 1, "key": 1, "stamp": 1}, timeout=False,
                              snapshot=True)  # ????????? ??? ???, ??? ???? ??????????????
            reply.batch_size(FOREACH_BATCH_SIZE)
            reply_count = reply.count()
            print "FOREACH user (mongo base %s) -- find reply count: %s" % (opt.mongo_base, reply_count)

            iteration = 0
            for obj in reply:
                iteration += 1

                try:
                    pers_key = obj.get("key", None)
                    if not pers_key:
                        continue
                    # ????uid
                    key_coll = pers_key.split("_")
                    if len(key_coll) == 2:
                        prefix = key_coll[0]
                        uid = long(key_coll[1])
                    else:
                        print "! persistence WARNING: bad key (%s)" % (pers_key)
                        continue

                    # ????? stamp
                    stamp = obj.get("stamp", 0)
                    stamps = user_stamps.get(uid) or []
                    stamps.append(stamp)
                    user_stamps[uid] = stamps

                    if len(stamps) > 1:
                        print "DUPLICATE stamps(%s): uid=%s, stamps=%s (last _id=%s)" % (
                            len(stamps), uid, stamps, obj.get("_id", ""))
                        duplicates[uid] = stamps

                except:
                    catch()
                    print "ERROR handling data for obj %s" % str(obj)

                if iteration % FOREACH_SLEEP_USERS_PER_PASS == 0:
                    time.sleep(FOREACH_SLEEP_MSEC_PER_USER / 1000.0)  # ??? ? ???? ?? ?????? ?????

                if iteration % FOREACH_USERS_PER_GC_COLLECT == 0:
                    t0 = time.time()
                    collect_count = gc.collect()
                    t1 = time.time()
                    print "%s gc time: %.3f (collected: %d), passed %d/%d records" % (
                        time.ctime(), t1 - t0, collect_count, iteration, reply_count)

            print "DONE (mongo base %s: %d records)" % (opt.mongo_base, reply_count)
            print "DUPLICATES FOUND(%s): %s" % (len(duplicates), pretty(duplicates))


def fixGuildData():
    startTime = time.time()
    logFile = open("fixGuildData.log", "w")
    print "Check rule 1"
    # ???? ??"???? ????? {"key" : "gs_#auid#"}
    gs_guildAuids = []
    for options_dict in coord_cfg.COORDINATOR_MONGO_CONFIG:
        opt = ClassDict(options_dict)
        connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
        mongo_db = getattr(connection, opt.mongo_base, None)
        if mongo_db:
            coll = getattr(mongo_db, "guilds")
            func = getattr(coll, "find")
            reply = func({"key": {"$exists": True}})
            for obj in reply:
                guildAuid = tolong(str(obj.get("key", None))[3:])
                isGuildKey = str(obj.get("key", None))[:3] == "gs_"
                if isGuildKey:
                    gs_guildAuids.append(guildAuid)

    coll = getattr(mongo_db, "guilds")
    func = getattr(coll, "find")
    numErasedGuilds = 0
    iteration = 0
    for auid in gs_guildAuids:
        reply = func({"GuildAuid": auid})
        if not admin_guilds.checkShortInfoByGSKey(reply, auid, coll):
            numErasedGuilds += 1
            logFile.write("Guild %d was removed\n" % auid)

        reply = func({"key": "gs_" + str(auid)})
        if not admin_guilds.checkGuildDataByGSKey(reply, auid, coll):
            numErasedGuilds += 1
            logFile.write("Guild %d was removed\n" % auid)

        iteration += 1
        if iteration % FOREACH_SLEEP_USERS_PER_PASS == 0:
            time.sleep(FOREACH_SLEEP_MSEC_PER_USER / 1000.0)  # ??? ? ???? ?? ?????? ?????
        if iteration % FOREACH_USERS_PER_GC_COLLECT == 0:
            gc.collect()

    print "Rule 1 info: total guilds =", len(gs_guildAuids), "erased guilds =", numErasedGuilds

    iteration = 0
    print "Check rule 2"
    # ???? ??shortinfo ????? {"GuildAuid" : #auid#}
    short_guildAuids = []
    for options_dict in coord_cfg.COORDINATOR_MONGO_CONFIG:
        opt = ClassDict(options_dict)
        connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
        mongo_db = getattr(connection, opt.mongo_base, None)
        if mongo_db:
            coll = getattr(mongo_db, "guilds")
            func = getattr(coll, "find")
            reply = func({"GuildAuid": {"$exists": True}})
            for obj in reply:
                guildAuid = tolong(str(obj.get("GuildAuid", None)))
                short_guildAuids.append(guildAuid)

    coll = getattr(mongo_db, "guilds")
    func = getattr(coll, "find")
    numErasedGuilds = 0
    for auid in short_guildAuids:
        reply = func({"key": "gs_" + str(auid)})
        if not admin_guilds.checkGuildDataByShortInfo(reply, auid, coll):
            numErasedGuilds += 1
            logFile.write("Guild %d was removed\n" % auid)

        reply = func({"GuildAuid": auid})
        if not admin_guilds.checkShortInfoByShortInfo(reply, auid, coll):
            numErasedGuilds += 1
            logFile.write("Guild %d was removed\n" % auid)

        iteration += 1
        if iteration % FOREACH_SLEEP_USERS_PER_PASS == 0:
            time.sleep(FOREACH_SLEEP_MSEC_PER_USER / 1000.0)  # ??? ? ???? ?? ?????? ?????
        if iteration % FOREACH_USERS_PER_GC_COLLECT == 0:
            gc.collect()

    print "Rule 2 info: total guilds =", len(short_guildAuids), "erased guilds =", numErasedGuilds

    endTime = time.time()
    logFile.close()
    print "Total time:", endTime - startTime


def listGuildMembers(guilds):
    if guilds == '*':
        guilds = None
    else:
        guilds = set((gid[3:] if gid[:3] == 'gs_' else gid) for gid in guilds.split(','))
    all_members = {}
    for options_dict in coord_cfg.COORDINATOR_MONGO_CONFIG:
        opt = ClassDict(options_dict)
        connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
        mongo_db = getattr(connection, opt.mongo_base, None)
        if mongo_db:
            reply = [obj for obj in mongo_db.guilds.find({"key": {"$exists": True}})
                     if "data" in obj and str(obj.get("key", ""))[:3] == "gs_"]
            for obj in reply:
                auid = obj["key"][3:]
                if not guilds or auid in guilds:
                    if not admin_guilds.getGuildMembers(auid, obj["data"], all_members):
                        return  # duplicate guild for a player found
    json_result = json_dumps(all_members)
    if OUT_FILE:
        global OUT_FILE_MODE
        with open(OUT_FILE, OUT_FILE_MODE) as f:
            f.write(json_result)
            f.write("\n")
        if OUT_FILE_MODE == "wt":
            print "Result stored into the file %s" % OUT_FILE
            OUT_FILE_MODE = "at"
        else:
            print "Result appended to the file %s" % OUT_FILE
    else:
        print json_result


def checkMultiguildMembers():
    all_members = {}
    for options_dict in coord_cfg.COORDINATOR_MONGO_CONFIG:
        opt = ClassDict(options_dict)
        connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
        mongo_db = getattr(connection, opt.mongo_base, None)
        if mongo_db:
            reply = [obj for obj in mongo_db.guilds.find({"key": {"$exists": True}})
                     if "data" in obj and str(obj.get("key", ""))[:3] == "gs_"]
            for obj in reply:
                auid = obj["key"][3:]
                admin_guilds.getDupGuildMembers(auid, obj["data"], all_members)
            dups = [(k, v) for k, v in all_members.iteritems() if len(v) > 1]
            if dups:
                print "Duplicates found:"
                for auid, gids in dups:
                    print "Auid %s in guilds: %s" % (auid, ",".join(gids))
            else:
                print "OK. No duplicate guildmembership found."


def returnGuildAuidToAcc(filename="data.json", checkForNull=False):
    startTime = time.time()
    auidToGuildAuidMap = {}
    handledUsers = 0
    with open(os.path.join(os.path.dirname(os.path.realpath(__file__)), filename), "r") as f:
        auidToGuildAuidMap = json.load(f)

    if len(coord_cfg.COORDINATOR_MONGO_CONFIG) > 0:
        opt = ClassDict(coord_cfg.COORDINATOR_MONGO_CONFIG[0])
        connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
        mongo_db = getattr(connection, opt.mongo_base, None)
        if mongo_db:
            coll = getattr(mongo_db, "pers")
            func = getattr(coll, "find")
            func2 = getattr(coll, "update")

            curIdx = 0
            total = len(auidToGuildAuidMap.keys())
            for auid in auidToGuildAuidMap.keys():
                sn_id, sn_login = getSocialRequisitesByAuid(auid)
                login, opts, dbi = getSqlUserRequisites(sn_id, sn_login)
                uid = getSqlUserUID(login, opts)

                try:
                    pers_key = "data_%d" % long(uid)
                except:
                    catch()
                    sys.stdout.write("ERROR cannot find auid(%r) in SQL\n" % auid)
                    continue
                reply = func({"key": pers_key}, new=True)
                if reply.count() != 1:
                    sys.stdout.write("ERROR cannot find auid(%r) uid(%r) in Mongo\n" % (auid, uid))
                    continue

                for obj in reply:

                    # 1) ?????????? ????? ? ??
                    ####################################################
                    data_json = obj["data"]

                    curIdx += 1

                    if curIdx % 100 == 0:
                        sys.stdout.write("Fix guild for: %r/%r\n" % (curIdx, total))

                    if curIdx % FOREACH_USERS_PER_GC_COLLECT == 0:
                        gc.collect()

                    # 2) ?????acc
                    ####################################################
                    acc = PersistentDataManager.newSimpleDataAcc(data_json)
                    MD = ModelData()
                    MD.load(acc.model)
                    MD.init(changeWriter=None)
                    ####################################################

                    # 3) ?????? guildauid
                    ####################################################
                    if not checkForNull or acc.db.guildAuid == 0:
                        acc.db.guildAuid = auidToGuildAuidMap[auid]
                        handledUsers += 1

                    # 4) ????? acc ?json ?zip'?
                    ####################################################
                    new_data_json = PersistentDataManager.saveData(acc, True)
                    ####################################################

                    # 5) ??? ??? ????
                    ####################################################
                    mongo_reply = func2({"key": pers_key}, {"$set": {"data": new_data_json}}, upsert=True, safe=True)
                    if not mongo_reply.get("ok", None):
                        sys.stdout.write("ERROR save to mongo: %r\n" % mongo_reply)
                        ####################################################
    print "Total users fixed: " + str(handledUsers)


def processFixedAccounts(processingFunc, filename="data.json"):
    startTime = time.time()
    with open(os.path.join(os.path.dirname(os.path.realpath(__file__)), filename), "r") as f:
        auidToGuildAuidMap = json.load(f)

    total = len(auidToGuildAuidMap)
    for auid in auidToGuildAuidMap:
        sn_id, sn_login = getSocialRequisitesByAuid(auid)
        login, opts, dbi = getSqlUserRequisites(sn_id, sn_login)
        for options_dict in MONGO_CONFIG:
            opt = ClassDict(options_dict)
            try:
                connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
                db = getattr(connection, opt.mongo_base, None)
                if db:
                    coll = getattr(db, "pers")
                    func = getattr(coll, "find")
                    func2 = getattr(coll, "update")

                    curIdx = 0

                    uid = getSqlUserUID(login, opts)

                    try:
                        pers_key = "data_%d" % long(uid)
                    except:
                        catch()
                        sys.stdout.write("ERROR cannot find auid(%r) in SQL\n" % auid)
                        continue
                    reply = func({"key": pers_key}, new=True)
                    if reply.count() != 1:
                        sys.stdout.write("ERROR cannot find auid(%r) uid(%r) in Mongo\n" % (auid, uid))
                        continue

                    for obj in reply:

                        # 1) ?????????? ????? ? ??
                        ####################################################
                        data_json = obj["data"]

                        curIdx += 1

                        if curIdx % 100 == 0:
                            sys.stdout.write("Fix account for: %r/%r\n" % (curIdx, total))

                        if curIdx % FOREACH_USERS_PER_GC_COLLECT == 0:
                            gc.collect()

                        # 2) ?????acc
                        ####################################################
                        acc = PersistentDataManager.newSimpleDataAcc(data_json)
                        MD = ModelData()
                        MD.load(acc.model)
                        MD.init(changeWriter=None)
                        ####################################################

                        # 3) ?????? ???
                        ####################################################
                        processingFunc(acc)
                        print("new revision = %d", acc.model["ModelData"]["version"]["Version"]["revision"])

                        # 4) ????? acc ?json ?zip'?
                        ####################################################
                        new_data_json = PersistentDataManager.saveData(acc, True)
                        ####################################################

                        # 5) ??? ??? ????
                        ####################################################
                        mongo_reply = func2({"key": pers_key}, {"$set": {"data": new_data_json}}, upsert=True,
                                            safe=True)
                        if not mongo_reply.get("ok", None):
                            sys.stdout.write("ERROR save to mongo: %r\n" % mongo_reply)
                            ####################################################
            except:
                catch()
                print "ERROR connecting to mongo at %s:%s" % (opt.mongo_addr, opt.mongo_port)


def convertMDVersion(acc):
    acc.model["ModelData"]["version"]["Version"]["revision"] = 80


def CountTalentStatistics(cursor, total, threadId, logFileName):
    curIdx = 0

    logFile = open(logFileName + str(threadId) + ".log", "w")
    logFile.write("{")
    personDict = {}
    for obj in cursor:

        # 1) ?????????? ????? ? ??
        ####################################################
        if not obj.get("data", None):
            sys.stdout.write("Data for account %r was not found\n" % str(obj))
            continue
        data_json = obj["data"]
        pers_key = obj["key"]

        curIdx += 1

        if curIdx % 100 == 0:
            sys.stdout.write("Thread: %r convert: %r/%r\n" % (threadId, curIdx, total))

        # ???? ??? ????? ??????? ??????? ???(+????)
        FOREACH_USERS_PER_GC_COLLECT = 100
        if curIdx % FOREACH_USERS_PER_GC_COLLECT == 0:
            gc.collect()

        key_coll = pers_key.split("_")
        if len(key_coll) == 2:
            prefix = key_coll[0]
            uid = long(key_coll[1])
        else:
            sys.stdout.write("ERROR bad key %r\n" % pers_key)
            continue
            ####################################################

        # 2) ?????acc
        ####################################################
        try:
            acc = PersistentDataManager.newSimpleDataAcc(data_json)
            MD = ModelData()
            MD.load(acc.model)
            MD.init(changeWriter=None)
        except Exception:
            sys.stdout.write("ERROR bad data for key %r\n" % pers_key)
            continue
            ####################################################

        # 3) ??? ??????????
        ####################################################
        personDict = {acc.db.auid: {"TotalSessionResultsReceived": MD.Statistics.TotalSessionResultsReceived,
                                    "SummarySessionResults": MD.Statistics.SummarySessionResults.generateAtributeOnlyDict(),
                                    "MaxSessionResults": MD.Statistics.MaxSessionResults.generateAtributeOnlyDict()}}
        logFile.write(str(personDict))

    logFile.write("}")
    logFile.close()


def findUsersWithWrongTalentset(cursor, total, threadId, logFileName, iDict, funcUpdate, funcRemove):
    curIdx = 0
    suspiciousAuids = []

    logFile = open(logFileName + str(threadId) + ".log", "w")
    for obj in cursor:

        # 1) ?????????? ????? ? ??
        ####################################################
        if not obj.get("data", None):
            sys.stdout.write("Data for account %r was not found\n" % str(obj))
            continue
        data_json = obj["data"]
        pers_key = obj["key"]

        curIdx += 1

        if curIdx % 100 == 0:
            sys.stdout.write("Thread: %r convert: %r/%r\n" % (threadId, curIdx, total))

        # ???? ??? ????? ??????? ??????? ???(+????)
        FOREACH_USERS_PER_GC_COLLECT = 100
        if curIdx % FOREACH_USERS_PER_GC_COLLECT == 0:
            gc.collect()

        key_coll = pers_key.split("_")
        if len(key_coll) == 2:
            prefix = key_coll[0]
            uid = long(key_coll[1])
        else:
            sys.stdout.write("ERROR bad key %r\n" % pers_key)
            continue
            ####################################################

        # 2) ?????acc
        ####################################################
        try:
            acc = PersistentDataManager.newSimpleDataAcc(data_json)
            MD = ModelData()
            MD.load(acc.model)
            MD.init(changeWriter=None)
        except Exception:
            sys.stdout.write("ERROR bad data for key %r\n" % pers_key)
            continue
            ####################################################

        # 3) ????? modeldata
        ####################################################
        for heroId in MD.HeroesKeeper:
            hero = MD.getHeroByID(heroId)
            hero_talents = MD.getHeroClassTalents(acc.getConfig(), hero.PersistentId, iDict.SD)
            # ?? ?????????? ???????? ??? ? ??? ? ????
            isIntruder = False
            for talId in hero.TalentSet.keys():
                talent = hero.TalentSet.get(talId)
                staticTalent = iDict.SD.getStaticTalent(talent)
                if staticTalent:
                    if staticTalent['rarity'] == "Class":
                        if staticTalent['persistentId'] not in hero_talents:
                            isIntruder = True
                            break
            if isIntruder:
                suspiciousAuids.append(acc.db.auid)
                break

    json.dump(suspiciousAuids, logFile)
    logFile.close()

def findUsersWithBadPremiumAcc(cursor, total, threadId, logFileName, iDict, funcUpdate, funcRemove, **kwargs):
    curIdx = 0
    Auids = []
    import codecs
    logFile = open(logFileName + str(threadId) + ".log", "w")

    for obj in cursor:

        # 1) ?????????? ????? ? ??
        ####################################################
        if not obj.get("data", None):
            sys.stdout.write("Data for account %r was not found\n" % str(obj))
            continue
        data_json = obj["data"]
        pers_key = obj["key"]

        curIdx += 1

        if curIdx % 100 == 0:
            sys.stdout.write("Thread: %r convert: %r/%r\n" % (threadId, curIdx, total))

        # ???? ??? ????? ??????? ??????? ???(+????)
        FOREACH_USERS_PER_GC_COLLECT = 100
        if curIdx % FOREACH_USERS_PER_GC_COLLECT == 0:
            gc.collect()

        key_coll = pers_key.split("_")
        if len(key_coll) == 2:
            prefix = key_coll[0]
            uid = long(key_coll[1])
        else:
            sys.stdout.write("ERROR bad key %r\n" % pers_key)
            continue
            ####################################################

        # 2) ?????acc
        ####################################################
        try:
            acc = PersistentDataManager.newSimpleDataAcc(data_json)
            MD = ModelData()
            MD.load(acc.model)
            MD.init(changeWriter=None)
        except Exception:
            sys.stdout.write("ERROR bad data for key %r\n" % pers_key)
            continue
            ####################################################

        # 3) ????? modeldata
        ####################################################
        secs = toint(kwargs.get("secs"))
        diff = MD.LordInfo.PremiumAccountEnd - MD.LordInfo.PremiumAccountStart
        if diff >= secs:
            print " {} : auid = {} -> PremiumAccount = {} sec".format(threadId, acc.db.auid, diff)
            # funcRemove({"key":pers_key})
            Auids.append(acc.db.auid)

    json.dump(Auids, logFile)
    logFile.close()

def deleteTutorialAccounts(cursor, total, threadId, logFileName, iDict, funcUpdate, funcRemove, **kwargs):
    curIdx = 0
    Auids = []
    import codecs
    logFile = open(logFileName + str(threadId) + ".log", "w")

    for obj in cursor:

        # 1) ?????????? ????? ? ??
        ####################################################
        if not obj.get("data", None):
            sys.stdout.write("Data for account %r was not found\n" % str(obj))
            continue
        data_json = obj["data"]
        pers_key = obj["key"]

        curIdx += 1

        if curIdx % 100 == 0:
            sys.stdout.write("Thread: %r convert: %r/%r\n" % (threadId, curIdx, total))

        # ???? ??? ????? ??????? ??????? ???(+????)
        FOREACH_USERS_PER_GC_COLLECT = 100
        if curIdx % FOREACH_USERS_PER_GC_COLLECT == 0:
            gc.collect()

        key_coll = pers_key.split("_")
        if len(key_coll) == 2:
            prefix = key_coll[0]
            uid = long(key_coll[1])
        else:
            sys.stdout.write("ERROR bad key %r\n" % pers_key)
            continue
            ####################################################

        # 2) ?????acc
        ####################################################
        try:
            acc = PersistentDataManager.newSimpleDataAcc(data_json)
            MD = ModelData()
            MD.load(acc.model)
            MD.init(changeWriter=None)
        except Exception:
            sys.stdout.write("ERROR bad data for key %r\n" % pers_key)
            continue
            ####################################################

        # 3) ????? modeldata
        ####################################################
        if MD.version.revision >= 103 and len(MD.LordInfo.MapsByType) <= 1:
            sys.stdout.write(
                "delete modeldata for pers_key {0} auid={1} modeldata_revision={2} \n".format(pers_key, acc.db.auid,
                                                                                              MD.version.revision))

            """
            dump = codecs.open(pers_key + ".json", "w", "utf8")
            persistent_str = data_json
            str_head = persistent_str[:4]
            if str_head in ["ZLIB", "BZIP"]:
                encoded_persistent = persistent_str[4:].encode('latin1')
                if persistent_str[:4] == "ZLIB":
                    persistent_str = zlib.decompress( encoded_persistent )
                elif persistent_str[:4] == "BZIP":
                    persistent_str = bz2.decompress( encoded_persistent )

                dump.write(persistent_str)
            dump.close()
            """
            # funcRemove({"key":pers_key})
            Auids.append(acc.db.auid)

    json.dump(Auids, logFile)
    logFile.close()


def clearListCompletedDynQuests(cursor, total, threadId, logFileName, iDict, funcUpdate, funcRemove):
    curIdx = 0
    suspiciousAuids = []

    logFile = open(logFileName + str(threadId) + ".log", "w")
    for obj in cursor:

        # 1) ?????????? ????? ? ??
        ####################################################
        if not obj.get("data", None):
            sys.stdout.write("Data for account %r was not found\n" % str(obj))
            continue
        data_json = obj["data"]
        pers_key = obj["key"]

        curIdx += 1

        if curIdx % 100 == 0:
            sys.stdout.write("Thread: %r convert: %r/%r\n" % (threadId, curIdx, total))

        # ???? ??? ????? ??????? ??????? ???(+????)
        FOREACH_USERS_PER_GC_COLLECT = 100
        if curIdx % FOREACH_USERS_PER_GC_COLLECT == 0:
            gc.collect()

        key_coll = pers_key.split("_")
        if len(key_coll) == 2:
            prefix = key_coll[0]
            uid = long(key_coll[1])
        else:
            sys.stdout.write("ERROR bad key %r\n" % pers_key)
            continue
            ####################################################

        # 2) ?????acc
        ####################################################
        try:
            acc = PersistentDataManager.newSimpleDataAcc(data_json)
        except Exception:
            sys.stdout.write("ERROR bad data for key %r\n" % pers_key)
            continue
            ####################################################

        # 3) ????? modeldata
        ####################################################
        if os.path.exists("./removeLossQuests.in"):
            fRLQ = open("removeLossQuests.in", "r")
            data = fRLQ.read()
            fRLQ.close()
            removeLossQuests = [toint(x.strip()) for x in data.split(",")]
        else:
            removeLossQuests = []
        if removeLossQuests:
            for x in removeLossQuests:
                if acc.model.get("ModelData") and acc.model.get("ModelData").get("LossDynamicQuests") and x in \
                        acc.model["ModelData"]["LossDynamicQuests"].get("SimpleList"):
                    acc.model["ModelData"]["LossDynamicQuests"]["SimpleList"].remove(x)
        else:
            if acc.model.get("ModelData") and acc.model.get("ModelData").get("LossDynamicQuests") and acc.model.get(
                    "ModelData").get("LossDynamicQuests").get("SimpleList"):
                acc.model["ModelData"]["LossDynamicQuests"]["SimpleList"] = []

        if os.path.exists("./removeCompletedQuests.in"):
            fRCQ = open("removeCompletedQuests.in", "r")
            data = fRCQ.read()
            fRCQ.close()
            removeCompletedQuests = [toint(x.strip()) for x in data.split(",")]
        else:
            removeCompletedQuests = []
        if removeCompletedQuests:
            for x in removeCompletedQuests:
                if acc.model.get("ModelData") and acc.model.get("ModelData").get("CompletedDynamicQuests") and x in \
                        acc.model["ModelData"]["CompletedDynamicQuests"].get("SimpleList"):
                    acc.model["ModelData"]["CompletedDynamicQuests"]["SimpleList"].remove(x)
        else:
            if acc.model.get("ModelData") and acc.model.get("ModelData").get("CompletedDynamicQuests") and \
                    acc.model["ModelData"]["CompletedDynamicQuests"].get("SimpleList"):
                acc.model["ModelData"]["CompletedDynamicQuests"]["SimpleList"] = []

        cache_dict = PersistentDataManager.makeSaveDict(acc)

        # ----------------------------
        # prepare new data_json
        new_data_json = PersistentDataManager.saveData(acc)
        print "Updateting for pers_key={0} auid={1}".format(pers_key, acc.db.auid)
        mongo_reply = funcUpdate({"key": pers_key}, {"$set": {"data": new_data_json}}, upsert=False, new=True)
        print mongo_reply
    logFile.close()


def fixUsersWithExtraProductionInBuildings(cursor, total, threadId, logFileName, iDict, funcUpdate, funcRemove, **kwarfs):
    curIdx = 0
    suspiciousAuids = []

    logFile = open(logFileName + str(threadId) + ".log", "w")
    for obj in cursor:

        # 1) ?????????? ????? ? ??
        ####################################################
        if not obj.get("data", None):
            sys.stdout.write("Data for account %r was not found\n" % str(obj))
            continue
        data_json = obj["data"]
        pers_key = obj["key"]

        curIdx += 1

        if curIdx % 100 == 0:
            sys.stdout.write("Thread: %r convert: %r/%r\n" % (threadId, curIdx, total))

        # ???? ??? ????? ??????? ??????? ???(+????)
        FOREACH_USERS_PER_GC_COLLECT = 100
        if curIdx % FOREACH_USERS_PER_GC_COLLECT == 0:
            gc.collect()

        key_coll = pers_key.split("_")
        if len(key_coll) == 2:
            prefix = key_coll[0]
            uid = long(key_coll[1])
        else:
            sys.stdout.write("ERROR bad key %r\n" % pers_key)
            continue
            ####################################################

        # 2) ?????acc
        ####################################################
        try:
            acc = PersistentDataManager.newSimpleDataAcc(data_json)
            MD = ModelData()
            MD.load(acc.model)
            MD.init(changeWriter=None)
        except Exception:
            sys.stdout.write("ERROR bad data for key %r\n" % pers_key)
            continue
            ####################################################

        # 3) ????? modeldata
        ####################################################
        # ?? ??? ????? ???, ??? ???? ????
        if MD.version.revision < 87:
            continue
        isIntruder = False
        for buildingId in MD.ConstructionsKeeper:
            construction = MD.getConstructionByID(buildingId)
            staticConstruction = iDict.SD.getStaticConstruction(construction)
            # ?? ??????? ???? ?? ? ???? ?? ????? ? ??
            if staticConstruction['classType'] == 'ProductionBuilding':
                if staticConstruction['persistentId'] in ['Production_Resource1', 'Production_Resource2',
                                                          'Production_Resource3']:
                    if construction.ProductionValue > 55000:
                        isIntruder = True
                        break
                elif staticConstruction['persistentId'] == 'Production_Silver_fromRes1':
                    if construction.ProductionValue > 17000:
                        isIntruder = True
                        break
                elif staticConstruction['persistentId'] == 'Production_Crystal':
                    if construction.ProductionValue > 36:
                        isIntruder = True
                        break
        if isIntruder:
            suspiciousAuids.append(acc.db.auid)
        else:
            continue

    json.dump(suspiciousAuids, logFile)
    logFile.close()


def findUsersWithSpecialConditions(conditionFunc, logFilename, maxThreads=10, **kwargs):
    startTime = time.time()

    iDict = ClassDict()
    iDict.Config = MultiConfig()
    iDict.SD = StaticData("../xdb/ExportedSocialData.xml", iDict.Config.getMainConfig())

    # ?????auids.json ?uids.json
    ####################################################
    print "findUsersWithSpecialConditions.onStart"
    print "Num threads:", maxThreads
    th_count = maxThreads
    ####################################################

    if len(coord_cfg.COORDINATOR_MONGO_CONFIG) > 0:
        for shard in coord_cfg.COORDINATOR_MONGO_CONFIG:
            opt = ClassDict(shard)
            mongo_db = getattr(pymongo.Connection(opt.mongo_addr, opt.mongo_port), opt.mongo_base, None)
            if mongo_db:
                coll = getattr(mongo_db, "pers")
                funcFind = getattr(coll, "find")
                funcUpdate = getattr(coll, "update")
                funcRemove = getattr(coll, "remove")
                reply = mongo_db.pers.find({"key": {"$exists": True}})
                print "Mongo reply type is %s" % type(reply)
                total = reply.count()

                print "Total acc:", total
                threads = []
                cel = int(math.ceil(float(total) / maxThreads))
                th_count = cel if maxThreads > cel else maxThreads
                print "Total threads:", th_count
                for x in xrange(0, th_count):
                    start = 0 if x == 0 else cel * x + 1
                    end = cel * (x + 1) + 1
                    if end > total:
                        end = total + 1
                    slice = reply.clone()[start:end]
                    thread = Thread(target=conditionFunc, args=(slice, end - start, x,
                                                                logFilename + shard["mongo_base"], iDict, funcUpdate,
                                                                funcRemove), kwargs=kwargs)
                    thread.start()
                    threads.append(thread)
                for thread in threads:
                    thread.join()

            else:
                print "ERROR mongo_db is None"
                exit(1)
    else:
        print "ERROR coord_cfg.COORDINATOR_MONGO_CONFIG is empty"
        exit(1)

    # ?????? ????????
    ####################################################
    # TODO ???? ??? ??????? ??? maxThreads == 1 !
    # ??? ???????? ??.
    logFile = open(logFilename + ".log", "w")
    totalAuids = []
    for shard in coord_cfg.COORDINATOR_MONGO_CONFIG:
        for x in range(0, th_count):

            f = open(logFilename + shard["mongo_base"] + str(x) + ".log", "r")
            d = f.read()
            if d.strip():
                d1 = json_loads(d)
                totalAuids.extend(d1)
            f.close()
            os.remove(logFilename + shard["mongo_base"] + str(x) + ".log")
    logFile.write(json_dumps(totalAuids))
    logFile.close()

    endTime = time.time()
    print "Total time:", endTime - startTime
    # print "Timings:", timings


def getInputKeys(keysFileName, start, end, cursor):
    if os.path.exists(keysFileName):
        return

    keysFile = open(keysFileName, "w")
    keysArr = []
    for i in xrange(start, end):
        try:
            obj = cursor.next()
        except Exception:
            break
        if not obj.get("key", None):
            continue
        keysArr.append(obj["key"])
    keysFile.write(json_dumps(keysArr))
    keysFile.close()


def findUsersWithSpecialConditionsSubprocess(handlerClassName, logFilename, rewriteData=False, maxThreads=10, **kwargs):
    startTime = time.time()

    handlerFilePath = os.path.join(os.path.dirname(os.path.realpath(__file__)), "DBScripts", "UserDataBaseHandler.py")

    # ?????auids.json ?uids.json
    ####################################################
    print "findUsersWithSpecialConditions.onStart"
    print "Num threads:", maxThreads
    th_count = maxThreads
    ####################################################

    if len(coord_cfg.COORDINATOR_MONGO_CONFIG) > 0:
        for shard in coord_cfg.COORDINATOR_MONGO_CONFIG:
            opt = ClassDict(shard)
            mongo_db = getattr(pymongo.Connection(opt.mongo_addr, opt.mongo_port), opt.mongo_base, None)
            #mongo_db = getattr(pymongo.Connection(opt.mongo_addr, opt.mongo_port, slave_okay=True), opt.mongo_base, None)
            if mongo_db:
                cursor = mongo_db.pers.find()
                total = cursor.count()

                print "Total acc:", total
                print "kwargs = ", kwargs
                subprocesses = []
                cel = int(math.ceil(float(total) / maxThreads))
                th_count = cel if maxThreads > cel else maxThreads
                print "Total threads:", th_count
                for x in xrange(0, th_count):
                    start = 0 if x == 0 else cel * x + 1
                    end = cel * (x + 1) + 1
                    if end > total:
                        end = total + 1
                    keysFileName = ("inputKeys%d" % x) + shard["mongo_base"] + ".txt"
                    getInputKeys(keysFileName, start, end, cursor)
                    process = subprocess.Popen(
                        [sys.executable, handlerFilePath, json_dumps(shard), str(end - start), keysFileName, str(x),
                         logFilename + shard["mongo_base"], handlerClassName, str(rewriteData),
                         json_dumps(kwargs)],
                        stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    subprocesses.append(process)
                isWorking = len(subprocesses)
                while isWorking:
                    for process in subprocesses[:]:
                        if process.poll() is not None:
                            isWorking -= 1
                            output, errOutput = process.communicate()
                            if output:
                                sys.stdout.write(output)
                            if errOutput:
                                print "Error = ", errOutput
                            subprocesses.remove(process)

                    time.sleep(60*1)
            else:
                print "ERROR mongo_db is None"
                exit(1)
    else:
        print "ERROR coord_cfg.COORDINATOR_MONGO_CONFIG is empty"
        exit(1)

    if handlerClassName in ("findUsersWithLesserVersion"):
        mergeFiles(logFilename, th_count, True)
    else:
        mergeFiles(logFilename, th_count)

    endTime = time.time()
    print "Total time:", endTime - startTime

def multi_run_wrapper(args):
   return UserDataBaseHandler.main(*args)

def findUsersWithSpecialConditionsPoolProcess(handlerClassName, logFilename, rewriteData=False, maxThreads=10, **kwargs):
    startTime = time.time()

    handlerFilePath = os.path.join(os.path.dirname(os.path.realpath(__file__)), "DBScripts", "UserDataBaseHandler.py")

    # ?????auids.json ?uids.json
    ####################################################
    print "findUsersWithSpecialConditions.onStart"
    print "Num fork:", maxThreads
    th_count = maxThreads
    ####################################################

    if len(coord_cfg.COORDINATOR_MONGO_CONFIG) > 0:
        for shard in coord_cfg.COORDINATOR_MONGO_CONFIG:
            opt = ClassDict(shard)
            mongo_db = getattr(pymongo.Connection(opt.mongo_addr, opt.mongo_port), opt.mongo_base, None)
            #mongo_db = getattr(pymongo.Connection(opt.mongo_addr, opt.mongo_port, slave_okay=True), opt.mongo_base, None)
            if mongo_db:
                cursor = mongo_db.pers.find()
                total = cursor.count()

                print "Total acc:", total
                print "kwargs = ", kwargs
                subprocesses = []
                cel = int(math.ceil(float(total) / maxThreads))
                th_count = cel if maxThreads > cel else maxThreads
                print "Total forks:", th_count
                pool = multiprocessing.Pool(th_count)
                results = []
                for x in xrange(0, th_count):
                    start = 0 if x == 0 else cel * x + 1
                    end = cel * (x + 1) + 1
                    if end > total:
                        end = total + 1
                    keysFileName = ("inputKeys%d" % x) + shard["mongo_base"] + ".txt"
                    getInputKeys(keysFileName, start, end, cursor)
                    args = [shard, end - start, keysFileName, x,
                         logFilename + shard["mongo_base"], handlerClassName, rewriteData, kwargs]
                    #results.append(args)
                    results.append(pool.apply_async(UserDataBaseHandler.main,args))
                    print "Start worker %s args = %s" % (x,  args)
                #print pool.map(multi_run_wrapper, results)
                while results:
                    for x in results[:]:
                        x.get()
                        results.remove(x)
            else:
                print "ERROR mongo_db is None"
                exit(1)
    else:
        print "ERROR coord_cfg.COORDINATOR_MONGO_CONFIG is empty"
        exit(1)

    if handlerClassName in ("findUsersWithLesserVersion"):
        mergeFiles(logFilename, th_count, True)
    else:
        mergeFiles(logFilename, th_count)

    endTime = time.time()
    print "Total time:", endTime - startTime



def mergeFiles(logFilename, th_count, mergeDictionaries=False):
    logFile = open(logFilename + ".log", "w")
    totalOutput = []
    if mergeDictionaries:
        totalOutput = {}
    for shard in coord_cfg.COORDINATOR_MONGO_CONFIG:
        for x in range(0, th_count):
            if os.path.exists(logFilename + shard["mongo_base"] + str(x) + ".log"):
                f = open(logFilename + shard["mongo_base"] + str(x) + ".log", "r")
                d = f.read()
                if d.strip():
                    d1 = json_loads(d)
                    if mergeDictionaries:
                        for dictKey in d1:
                            if dictKey not in totalOutput:
                                totalOutput[dictKey] = d1[dictKey]
                            else:
                                totalOutput[dictKey] += d1[dictKey]
                    else:
                        totalOutput.extend(d1)
                f.close()
                os.remove(logFilename + shard["mongo_base"] + str(x) + ".log")
    logFile.write(json_dumps(totalOutput))
    logFile.close()


def DumpUserSessionStats(cursor, logFileName):
    curIdx = 0
    # ???? ???????? ????? ??????? ??????? ???(+????)
    gc_rate = FOREACH_USERS_PER_GC_COLLECT if FOREACH_USERS_PER_GC_COLLECT_CHANGED else 500

    outFile = open(logFileName, "w")
    outFile.write("{")
    for obj in cursor:
        # 1) ?????????? ????? ? ??
        ####################################################
        if not obj.get("data", None):
            sys.stdout.write("Data for account %r was not found\n" % str(obj))
            continue
        data_json = obj["data"]
        pers_key = obj["key"]

        curIdx += 1

        if curIdx % 1000 == 0:
            print "Converted: %r" % (curIdx,)

        if curIdx % gc_rate == 0:
            t0 = time.time()
            collect_count = gc.collect()
            t1 = time.time()
            print "gc time: %.3f (collected: %d), passed %d auids" % (t1 - t0, collect_count, curIdx - 1)
        #            gc.collect()

        key_coll = pers_key.split("_")
        if len(key_coll) == 2:
            prefix = key_coll[0]
            uid = long(key_coll[1])
        else:
            print "ERROR bad key %r" % pers_key
            continue
            ####################################################

        # 2) ?????acc
        ####################################################
        try:
            acc = PersistentDataManager.newSimpleDataAcc(data_json)
            MD = ModelData()
            MD.load(acc.model)
            MD.init(changeWriter=None)
        except Exception:
            print "ERROR bad data for key %r" % pers_key
            continue
            ####################################################

        # 3) ??? ??????????
        ####################################################
        outFile.write(str(
            {acc.db.auid: {"TotalSessionResultsReceived": MD.Statistics.TotalSessionResultsReceived,
                           "SummarySessionResults": MD.Statistics.SummarySessionResults.generateAtributeOnlyDict(),
                           "MaxSessionResults": MD.Statistics.MaxSessionResults.generateAtributeOnlyDict()}}
        ))

        if curIdx % FOREACH_SLEEP_USERS_PER_PASS == 0:
            time.sleep(FOREACH_SLEEP_MSEC_PER_USER / 1000.0)  # ??? ? ???? ?? ?????? ?????

    outFile.write("}\n")
    outFile.close()


def getAllGuildMembers():
    startTime = time.time()

    ####################################################
    logFile = open("users_by_guild.csv", "w")
    # ???? ??? ????? ??????? ??????? ???(+????)
    FOREACH_USERS_PER_GC_COLLECT = 100
    curIdx = 0

    if len(coord_cfg.COORDINATOR_MONGO_CONFIG) > 0:
        opt = ClassDict(coord_cfg.COORDINATOR_MONGO_CONFIG[0])
        connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
        mongo_db = getattr(connection, opt.mongo_base, None)
        if mongo_db:
            coll = getattr(mongo_db, "guilds")
            func = getattr(coll, "find")
            cursor = func({"key": {"$exists": True}})
            total = cursor.count()

            print "Total guilds:", total
            for obj in cursor:
                # 1) ?????????? ????? ?????
                ####################################################
                data_json = obj["data"]
                guild_key = obj["key"]

                if "guildAllDaysRating" in data_json:
                    continue

                if guild_key == 0:
                    print("ERROR bad mongo key %r\n" % guild_key)
                    continue
                ####################################################

                # 2) ?????guilddata
                ####################################################
                try:
                    guilddata = GuildData()
                    guilddata.load(data_json)
                    guilddata.init(changeWriter=None)
                except Exception:
                    print("ERROR bad mongo data %r\n" % data_json)
                    continue
                ####################################################

                # 3) ?? ??auid's
                ####################################################
                for memberId in guilddata.GuildMemberKeeper:
                    member = guilddata.getGuildMemberByID(memberId)
                    logFile.write("%d; %d; %d;\n" % (member.Person, guilddata.GuildAuid, guilddata.RatingInfo.Rating))

                curIdx += 1

                if curIdx % 100 == 0:
                    sys.stdout.write("Counted: %r/%r\r" % (curIdx, total))

                if curIdx % FOREACH_USERS_PER_GC_COLLECT == 0:
                    gc.collect()
        else:
            print "ERROR mongo_db is None"
    else:
        print "ERROR coord_cfg.COORDINATOR_MONGO_CONFIG is empty"

    logFile.close()
    endTime = time.time()
    print "Total time:", endTime - startTime
    # print "Timings:", timings


def findUsersSingleThread(handler, logFilename, maxThreads=10):
    startTime = time.time()

    ####################################################
    print "[%s] findUsersSingleThread starting" % time.strftime("%X")
    ####################################################

    # FIXME - ???? ?????? ?? ?????? ??, ?? ??? ??? ?????
    if len(coord_cfg.COORDINATOR_MONGO_CONFIG) > 0:
        mongo_db = connect_mongo(coord_cfg.COORDINATOR_MONGO_CONFIG[0])
        if mongo_db:
            reply = mongo_db.pers.find({"key": {"$exists": True}})
            # total = reply.count()
            # print "Total accs: %s" % total
            handler(reply, logFilename)
        else:
            print "ERROR mongo_db is None for db %s" % (coord_cfg.COORDINATOR_MONGO_CONFIG[0],)
            exit(1)
    else:
        print "ERROR coord_cfg.COORDINATOR_MONGO_CONFIG is empty"
        exit(1)

    endTime = time.time()
    print "Total time:", endTime - startTime
    # print "Timings:", timings


def handleGuildData(logFileName, handler_function=None, isCheck=False, **kwargs):
    startTime = time.time()
    handledKeys = []
    logFile = open(logFileName, "w")

    for options_dict in MONGO_CONFIG:
        opt = ClassDict(options_dict)
        print ("\nConverting %r" % opt.mongo_base)
        curIdx = 0
        try:
            connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
            db = getattr(connection, opt.mongo_base, None)
            if db:
                ## mongoDB.addQuery("pers", "find", ({"key":data_key},), callback, params)
                coll = getattr(db, "guilds")
                func = getattr(coll, "find")
                func2 = getattr(coll, "update")
                cursor = func({"key": {"$exists": True}})
                total = cursor.count()

                print "Total guilds:", total
                for obj in cursor:
                    # 1) ?????????? ????? ?????
                    ####################################################
                    guild_key = obj["key"]

                    try:
                        data_json = obj["data"]
                    except Exception:
                        msg = catch()
                        logFile.write("Failed to get GuildData from document for guild %s:\n %r" % (guild_key, msg))
                        continue

                    if "guildAllDaysRating" in data_json or guild_key in handledKeys:
                        curIdx += 1
                        continue

                    if guild_key == 0:
                        print("ERROR bad mongo key %r\n" % guild_key)
                        curIdx += 1
                        continue
                    ####################################################

                    # 2) ?????guilddata
                    ####################################################
                    try:
                        guilddata = GuildData()
                        guilddata.load(data_json)
                        guilddata.init(changeWriter=None)
                    except Exception:
                        catch()
                        print("ERROR bad mongo data %r\n" % data_json)
                        curIdx += 1
                        continue

                    kwargs["rawData"] = json_loads(data_json)
                    guilddata = handler_function(guilddata, logFile, **kwargs)

                    # 5) ????? guilddata ?json
                    ####################################################
                    new_data_json = guilddata.save()
                    ####################################################

                    # 6) ??? ??? ????
                    ####################################################
                    if not isCheck:
                        mongo_reply = func2({"key": guild_key}, {"$set": {"data": new_data_json}}, upsert=True,
                                            new=True)
                        if not mongo_reply.get("ok", None):
                            print ("ERROR save to mongo: %r\n" % mongo_reply)
                        handledKeys.append(guild_key)

                    # 7) ??????? ????
                    ####################################################
                    curIdx += 1

                    if curIdx % 100 == 0:
                        sys.stdout.write("Counted: %r/%r\r" % (curIdx, total))

                    if curIdx % FOREACH_USERS_PER_GC_COLLECT == 0:
                        gc.collect()

        except Exception:
            catch()

    logFile.close()

def findGuildWithAbnormalExp(guilddata, logFile, **kwargs):
    count = toint(kwargs.get("count"))
    auidDict = defaultdict(int)
    investDict = defaultdict(int)
    timestamps = defaultdict(list)
    for _id in guilddata.InvestStatistics:
        invest = guilddata.getGuildInvestEventByID(_id)
        if invest:
            auidDict[invest.auid] += 1
            investDict[invest.auid] += invest.amount
            timestamps[invest.auid].append(invest.timestamp)

    for k, v in auidDict.iteritems():
        if v >= count:
            print >> logFile, json_dumps({guilddata.GuildAuid:dict(auid=k, count=v, timestamps=timestamps[k],  investment=investDict[k])})
    return guilddata

def recalcOldGuildRating(guilddata, logFile, **kwargs):
    while len(guilddata.RatingInfo.Ratings):
        guilddata.RatingInfo.Ratings.pop()
    for i in xrange(0, 7):
        guilddata.RatingInfo.Ratings.append(guilddata.RatingInfo.Rating)
    for memeber_id, member in guilddata.Members.iteritems():
        while len(member.Ratings):
            member.Ratings.pop()
        for idx in xrange(0, 7):
            memberRatingInfo, memberRatingInfo_id = guilddata.newMemberDayRating()
            memberRatingInfo.HeroRating = 0
            memberRatingInfo.Hero = 0
            member.HeroRatings.add(idx, memberRatingInfo)
            member.Ratings.append(0)
    return guilddata


def addCWNPCEntities(guilddata, logFile, I):
    cEveryDayProfit = I.SD.data["ClanWarsData"]["npcVillage"]["everyDayProfit"]
    cVRating = I.SD.data["ClanWarsData"]["npcVillage"]["clanRating"]
    CVILLAGE = I.SD.data["ClanWarsData"]["countOfNPCVillage"]
    cVillage = I.SD.data["ClanWarsData"]["countOfNPCVillage"] + 1
    if guilddata:
        while cVillage and len(guilddata.GuildVassals) < CVILLAGE:
            vass, _ = guilddata.newGuildMapEntity()
            vass.ShortInfo, _id = guilddata.newGuildShortInfo()
            vass.ShortInfo.GuildAuid = CC.NPC_VASSAL_AUID
            vass.DonationToday = I.SD.getGuildVassalsTributeCoef() * cEveryDayProfit
            vass.ShortInfo.Rating = cVRating
            cVillage -= 1
            guilddata.GuildVassals.add(vass)

        guilddata.GuildSuzerain.ShortInfo, _id = guilddata.newGuildShortInfo()
        guilddata.GuildSuzerain.ShortInfo.GuildAuid = CC.NPC_SUZERAIN_AUID
        guilddata.GuildSuzerain.DonationToday = I.SD.data["ClanWarsData"]["npcVillage"]["everyDayProfit"]
        guilddata.GuildSuzerain.ShortInfo.Rating = I.SD.data["ClanWarsData"]["npcSuzerain"]["clanRating"]

        # ???? ? ???? ????
        level = I.SD.getGuildShopLevel(guilddata.GuildSuzerain.ShortInfo.Rating, False)
        for shopItemId in I.Config.getMainConfig().GUILD_SHOP_ITEMS:
            staticItem = I.SD.getGuildShopItemById(shopItemId)
            if not staticItem:
                continue

            if level < staticItem['levelToUnlock']:
                continue
            amount = I.SD.getAmountByExperienceLevel(staticItem, level)
            # ?? ???????????? ???? ? ????????? ????-??
            if amount > 0:
                guilddata.GuildShopItems[str(shopItemId)] = amount

    return guilddata


def changeBadCWNPCVassals(guilddata, logFile, I):
    for _id, vass in guilddata.GuildVassals.iteritems():
        if vass.GuildAuid == CC.NPC_VASSAL_AUID:
            if _id not in guilddata.GuildVassals.keys():
                guilddata.GuildVassals.add(vass)

    return guilddata


def removeNPCSuzerains(guilddata, logFile, moneybackAuildsList):
    auidsfile = open(moneybackAuildsList, "r")
    auidsmap = ujson.load(auidsfile)
    auidsfile.close()
    if guilddata:
        if guilddata.GuildSuzerain.ShortInfo.GuildAuid == CC.NPC_SUZERAIN_AUID:
            guilddata.GuildSuzerain.ShortInfo.GuildAuid = 0
            guilddata.GuildSuzerain.ShortInfo.Rating = 0
            guilddata.GuildSuzerain.JoinTime = 0
            guilddata.GuildSuzerain.ShortInfo.Place = 0
            guilddata.GuildSuzerain.DonationToday = 0
            guilddata.GuildSuzerain.DonationYesterday = 0
            guilddata.GuildSuzerain.ShortInfo.IconChangesCount = 0
        if str(guilddata.GuildAuid) in auidsmap.keys():
            for siegeId, siege in guilddata.InitiatedSieges.items():
                if siege.SiegeId in auidsmap[str(guilddata.GuildAuid)]:
                    guilddata.GuildInfo.CWPoints_Clan += siege.StartPrice
                    guilddata.InitiatedSieges.remove(siege)

    return guilddata


def removeNPCSuzerainsPwStat():
    try:
        ru_sql_db = SyncSqlManager(ClassDict(EXPORT_CONFIG))
        ru_sql_db.openConnection()
        sql_reply = ru_sql_db.db.execute("UPDATE tbl_guild_rating SET suzerain = 0 WHERE suzerain = -1")
    except Exception:
        catch("Can't remove NPC-suzerain records from pw_stat: empty reply")


def siegesRemoveNPCSuserain():
    guildsAffected = dict()
    for options in MONGO_CONFIG:
        print "\nProcessing %r" % options['mongo_base']
        try:
            connection = pymongo.Connection(options['mongo_addr'], options['mongo_port'])
            db = getattr(connection, options['mongo_base'], None)
            if db and db.sieges and db.sieges.count():
                dbsieges = db.sieges
                sieges = [s for s in dbsieges.find({})]
                print "Total sieges:", len(sieges)
                for siege in sieges:
                    try:
                        if siege['suzerain'] == CC.NPC_SUZERAIN_AUID:
                            money_back_guild = _removeNPCSuzerain(siege, dbsieges)
                            if money_back_guild:
                                guildsAffected.setdefault(money_back_guild, []).append(siege['_id'])
                    except Exception:
                        catch("Error processing siege %s", siege['_id'])
        except Exception:
            catch()
    with open("siege_moneyback.json", 'wt') as f:
        f.write(json_dumps(guildsAffected))
        f.write("\n")


def _removeNPCSuzerain(siege, dbsieges):
    money_back_guild = None
    if [part for part in siege['participants'] if part['id'] == siege['target']]:  # target is also a participant
        if len(siege['participants']) == 2:  # just end the siege, returning money
            money_back_guild = [part['id'] for part in siege['participants'] if part['id'] == siege['target']][0]
        else:  # remove the suzerain and let others continue
            siege['participants'] = [part for part in siege['participants'] if part['id'] != CC.NPC_SUZERAIN_AUID]
            print "Siege %s, removed NPC: %s" % (siege['_id'], siege['participants'])
    else:  # substitute the suzerain for the target and let the participants continue
        for part in siege['participants']:
            if part['id'] == CC.NPC_SUZERAIN_AUID:
                part['id'] = siege['target']
                part['rating'] = siege['target_rating']
                print "Siege %s: changed NPC for vassal: %s" % (siege['_id'], part)
                break
    if money_back_guild:
        print "Destroing siege: %s" % siege
        mongo_reply = dbsieges.remove({"_id": siege['_id']}, w=1)
    else:
        mongo_reply = dbsieges.update({"_id": siege['_id']}, {
            '$set': {'participants': siege['participants'], 'suzerain': 0, 'suzerain_raiting': 0}}, w=1)
    if not (mongo_reply and mongo_reply.get("ok", None)):
        print "ERROR saving siege %s to mongo: %r\n" % (siege['_id'], mongo_reply)
    return money_back_guild


def returnGuildShortInfo(logFileName, auidsFileName):
    startTime = time.time()
    handledKeys = []
    logFile = open(logFileName, "w")
    auidsFile = open(auidsFileName, "w")
    auidsMap = {}
    for options_dict in MONGO_CONFIG:
        opt = ClassDict(options_dict)
        curIdx = 0
        try:
            connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
            db = getattr(connection, opt.mongo_base, None)
            if db:
                coll = getattr(db, "guilds")
                func = getattr(coll, "find")
                find_one = getattr(coll, "find_one")
                func2 = getattr(coll, "update")
                cursor = func({"key": {"$exists": True}})

                gs_guildAuids = []
                for obj in cursor:
                    guildAuid = tolong(str(obj.get("key", None))[3:])
                    isGuildKey = str(obj.get("key", None))[:3] == "gs_"
                    if isGuildKey:
                        gs_guildAuids.append(guildAuid)
                total = len(gs_guildAuids)
                print "Total guilds:", total
                for guildAuid in gs_guildAuids:
                    try:
                        obj = find_one({"key": "gs_" + str(guildAuid)})
                        # 1) ?????????? ????? ?????
                        ####################################################
                        data_json = obj["data"]
                        guild_key = obj["key"]

                        if "guildAllDaysRating" in data_json or guild_key in handledKeys:
                            curIdx += 1
                            continue

                        if guild_key == 0:
                            print("ERROR bad mongo key %r\n" % guild_key)
                            curIdx += 1
                            continue
                        ####################################################

                        # 2) ?????guilddata
                        ####################################################
                        try:
                            guilddata = GuildData()
                            guilddata.load(data_json)
                            guilddata.init(changeWriter=None)
                        except Exception:
                            catch()
                            print("ERROR bad mongo data %r\n" % data_json)
                            curIdx += 1
                            continue

                        # 3) ??? ??? ???? ?? ???
                        ####################################################
                        shortInfoReply = func({"GuildAuid": guilddata.GuildAuid})

                        if not shortInfoReply.count():
                            try:
                                mongo_reply = func2({"GuildAuid": guilddata.GuildAuid}, {
                                    "$set": {"FullName": guilddata.GuildInfo.FullName,
                                             "ShortName": guilddata.GuildInfo.ShortName}}, upsert=True, safe=True)
                                logFile.write("Short info fixed for guild %d, full name %s\n" % (
                                guilddata.GuildAuid, guilddata.GuildInfo.FullName))
                                if not mongo_reply.get("ok", None):
                                    print ("ERROR save to mongo: %r\n" % mongo_reply)
                                for memberId in guilddata.Members:
                                    member = guilddata.getGuildMemberByID(memberId)
                                    auidsMap[member.Person] = guilddata.GuildAuid
                            except Exception:
                                msg = catch()
                                logFile.write(
                                    "Failed to restore ShortInfo for guild %d:\n %r" % (guilddata.GuildAuid, msg))
                                continue

                        handledKeys.append(guild_key)
                        # 4) ??????? ????
                        ####################################################
                        curIdx += 1

                        if curIdx % 100 == 0:
                            sys.stdout.write("Counted: %r/%r\r" % (curIdx, total))

                        if curIdx % FOREACH_USERS_PER_GC_COLLECT == 0:
                            gc.collect()
                    except Exception:
                        catch()
                        continue
        except Exception:
            catch()

            # json.dump(auidsMap, auidsFile)


def convertGuildVassals(guilddata, logFile, rawData):
    if guilddata:
        for vassalId, vassal in guilddata.GuildVassals.items():
            del guilddata.GuildVassals.dictionary[vassalId]
        for vassalId, recommVassal in guilddata.RecommendedForMapVassals.items():
            del guilddata.RecommendedForMapVassals.dictionary[vassalId]
        vassalsKeeper = pathFind(rawData, "GuildData/GuildVassalKeeper/Keeper")
        if vassalsKeeper:
            for vid, vassal in vassalsKeeper.iteritems():
                if vassal.get("GuildVassal") and isinstance(vassal.get("GuildVassal"), dict):
                    v, _id = guilddata.newGuildMapEntity()
                    v.ShortInfo, _id = guilddata.newGuildShortInfo()
                    v.ShortInfo.Rating = vassal["GuildVassal"].get("Experience", 0)
                    v.ShortInfo.GuildAuid = vassal["GuildVassal"].get("GuildAuid", 0)
                    v.ShortInfo.GuildShortName = vassal["GuildVassal"].get("GuildShortName", "")
                    v.ShortInfo.GuildFullName = vassal["GuildVassal"].get("GuildFullName", "")
                    v.ShortInfo.IconChangesCount = vassal["GuildVassal"].get("IconChangesCount", 0)
                    v.ShortInfo.Place = vassal["GuildVassal"].get("Position", 0)
                    v.ShortInfo.RatingPositionChange = vassal["GuildVassal"].get("RatingPositionChange", 0)
                    v.DonationToday = vassal["GuildVassal"].get("DonationToday", 0)
                    v.DonationYesterday = vassal["GuildVassal"].get("DonationYesterday", 0)
                    v.JoinTime = vassal["GuildVassal"].get("JoinTime", 0)
                    guilddata.GuildVassals.add(v)

        suzerain = pathFind(rawData, "GuildData/GuildSuzerain/GuildSuzerain")
        if suzerain:
            guilddata.GuildSuzerain, _id = guilddata.newGuildMapEntity()
            guilddata.GuildSuzerain.ShortInfo, _id = guilddata.newGuildShortInfo()
            guilddata.GuildSuzerain.ShortInfo.Rating = suzerain.get("Rating", 0)
            guilddata.GuildSuzerain.ShortInfo.GuildAuid = suzerain.get("GuildAuid", 0)
            guilddata.GuildSuzerain.ShortInfo.GuildShortName = suzerain.get("GuildShortName", "")
            guilddata.GuildSuzerain.ShortInfo.GuildFullName = suzerain.get("GuildFullName", "")
            guilddata.GuildSuzerain.ShortInfo.IconChangesCount = suzerain.get("IconChangesCount", 0)
            guilddata.GuildSuzerain.ShortInfo.Place = suzerain.get("Position", 0)
            guilddata.GuildSuzerain.ShortInfo.RatingPositionChange = suzerain.get("RatingPositionChange", 0)
            guilddata.GuildSuzerain.DonationToday = suzerain.get("DonationToday", 0)
            guilddata.GuildSuzerain.DonationYesterday = suzerain.get("DonationYesterday", 0)
            guilddata.GuildSuzerain.JoinTime = suzerain.get("JoinTime", 0)

    return guilddata


def removeUnknownGuildMembers(guilddata, logFile, rawData):
    if guilddata:
        members = []
        for mId in guilddata.Members:
            members.append(mId)

        for mId, member in guilddata.GuildMemberKeeper.items():
            if mId not in members:
                for gTalId in guilddata.TakenTalents.keys():
                    talent = guilddata.getGuildTalentByID(gTalId)
                    if talent.Holder == member:
                        talent.Holder = 0
                        guilddata.FreeTalents.add(talent)
                        guilddata.TakenTalents.remove(talent)

                # Забираем наши таланты, которые уже взяли
                for gTalId in guilddata.TakenTalents.keys():
                    talent = guilddata.getGuildTalentByID(gTalId)
                    if talent.Owner == member:
                        # Удаляем из ModelData у того, кто взял наш талант
                        talent.Holder = 0
                        talent.Owner = 0
                        guilddata.TakenTalents.remove(talent)

                # Забираем наши таланты, которые еще не взяли и они лежат в гильдбанке
                for gTalId in guilddata.FreeTalents.keys():
                    talent = guilddata.getGuildTalentByID(gTalId)
                    if talent.Owner == member:
                        # Удялем из гильдии
                        talent.Owner = 0
                        guilddata.FreeTalents.remove(talent)

                guilddata.GuildMemberKeeper.remove(mId)

    return guilddata


def fillGuildRecruitmentParams(guilddata, logFile, rawData, sqlDb, I):
    if guilddata.GuildAuid == 0 or not guilddata.Owner.get():
        logFile.write("Wrong data for guild %s \n" % rawData)
        return guilddata

    guilddata.RecruitmentInfo.Message = ""
    guilddata.RecruitmentInfo.MinRating = 1000
    locale_reply = sqlDb.syncSqlQuery("SELECT locale FROM tbl_user_profile WHERE auid='%s'" % guilddata.Owner.Person)
    if locale_reply:
        guilddata.RecruitmentInfo.Locale = locale_reply[0]["locale"]
    else:
        guilddata.RecruitmentInfo.Locale = "RU"
    maxMembers = I.SD.getGuildMembersLimitByExp(guilddata.GuildLevelInfo.Experience, I)
    sqlDb.syncSqlCommand("""INSERT INTO tbl_guild_recruitment (guild_id, message, locale, min_rating)
                                    VALUES (%d,'','%s',1000)""" % (
    guilddata.GuildAuid, guilddata.RecruitmentInfo.Locale))
    sqlDb.syncSqlCommand(
        """UPDATE tbl_guild_rating SET max_members=%d WHERE guild_id=%d""" % (maxMembers, guilddata.GuildAuid))
    return guilddata


def mongoPgreqEnsureIndexes():
    "Ensure mongo indexes for pgreq collection"
    for options in MONGO_CONFIG:
        print ("\nConverting %r" % options['mongo_base'])
        try:
            connection = pymongo.Connection(options['mongo_addr'], options['mongo_port'])
            db = getattr(connection, options['mongo_base'], None)
            if db:
                collection = getattr(db, CC.PLAYER_GUILD_REQUESTS_DATA)
                collection.ensure_index("pers_auid", unique=False)
                collection.ensure_index("guild_auid", unique=False)
        except Exception:
            catch()


def fixGuildHeroRatings(guilddata, logFile, rawData):
    if guilddata.GuildAuid == 0:
        return guilddata

    for memId, member in guilddata.Members.iteritems():
        if not len(member.HeroRatings):
            for idx in xrange(0, 7):
                memberRatingInfo, memberRatingInfo_id = guilddata.newMemberDayRating()
                memberRatingInfo.HeroRating = 0
                memberRatingInfo.Hero = 0
                member.HeroRatings.add(idx, memberRatingInfo)
                member.Ratings.append(0)
            while len(member.Ratings) > 7:
                member.Ratings.pop(7)

    return guilddata


def fixGuildSoulboundTalents(guilddata, logFile, rawData, SD):
    if guilddata.GuildAuid == 0:
        return guilddata

    for talId, talent in guilddata.GuildTalentKeeper.iteritems():
        staticTalent = SD.getStaticTalentByTalentId(talent.PersistentId)
        if staticTalent and staticTalent['rarity'] in ["excellent", "magnificent"]:
            talent.HeroClassId = 0

    return guilddata


def checkReproductionVassalsSuzerain(guilddata, logFile, rawData, c):
    GMapEntity = []
    GShortInfo = []
    if guilddata.GuildSuzerain and guilddata.GuildSuzerain.get():
        GMapEntity.append(guilddata.GuildSuzerain.id)
        GShortInfo.append(guilddata.GuildSuzerain.ShortInfo.id)

    for Id, vass in guilddata.GuildVassals.iteritems():
        GMapEntity.append(Id)
        GShortInfo.append(vass.ShortInfo.id)

    for Id, vass in guilddata.RecommendedForMapVassals.iteritems():
        GShortInfo.append(vass.ShortInfo.id)

    for Id, me in guilddata.GuildMapEntityKeeper.iteritems():
        if Id not in GMapEntity:
            logFile.write("Guild id: %r  Zombie GuildMapEntity: %r \n" % (guilddata.GuildAuid, me.generateJsonDict()))
            c.me += 1

    for Id, gsi in guilddata.GuildShortInfoKeeper.iteritems():
        if Id not in GShortInfo:
            logFile.write("Guild id: %r  Zombie GuildShortInfo: %r \n" % (guilddata.GuildAuid, gsi.generateJsonDict()))
            c.gsi += 1

    time.sleep(0.005)
    return guilddata


def fixReproductionVassalsSuzerain(guilddata, logFile, rawData):
    GMapEntity = []
    GShortInfo = []
    if guilddata.GuildSuzerain and guilddata.GuildSuzerain.get():
        GMapEntity.append(guilddata.GuildSuzerain.id)
        GShortInfo.append(guilddata.GuildSuzerain.ShortInfo.id)

    for Id, vass in guilddata.GuildVassals.iteritems():
        GMapEntity.append(Id)
        GShortInfo.append(vass.ShortInfo.id)

    for Id, vass in guilddata.RecommendedForMapVassals.iteritems():
        GShortInfo.append(vass.ShortInfo.id)

    for Id, me in guilddata.GuildMapEntityKeeper.items():
        if Id not in GMapEntity:
            logFile.write("fix Guild: %r,  Zombie GuildMapEntity: %r \n" % (guilddata.GuildAuid, me.generateJsonDict()))
            me.refCounter = 0
            guilddata.GuildMapEntityKeeper.deleteByID(Id)

    for Id, gsi in guilddata.GuildShortInfoKeeper.items():
        if Id not in GShortInfo:
            logFile.write(
                "fix Guild: %r,  Zombie GuildShortInfo: %r \n" % (guilddata.GuildAuid, gsi.generateJsonDict()))
            gsi.refCounter = 0
            guilddata.GuildShortInfoKeeper.deleteByID(Id)

    return guilddata


def handleDynamicQuests(logFileName, action):
    # debug("handleDynamicQuests_0: logFileName=%r, action=%r", logFileName, action)
    # info("info handleDynamicQuests_0: logFileName=%r, action=%r", logFileName, action)
    print("print handleDynamicQuests_0: logFileName=%r, action=%r", logFileName, action)
    logFile = open(logFileName, "w")
    for options in MONGO_CONFIG:
        print ("\nConverting %r" % options['mongo_base'])
        try:
            connection = pymongo.Connection(options['mongo_addr'], options['mongo_port'])
            db = getattr(connection, options['mongo_base'], None)
            if db:
                collection = getattr(db, CC.DYNAMIC_QUESTS_DATA)
                func = getattr(collection, "find")
                func_update = getattr(collection, "update")
                reply = func({"key": {"$exists": True}})
                for obj in reply:
                    jsonQuestData = json_loads(obj["data"])
                    action(jsonQuestData, logFile)
                    obj["data"] = json_dumps(jsonQuestData)
                    mongo_reply = func_update({"key": obj["key"]}, {"$set": {"data": obj["data"]}})
                    if mongo_reply and not mongo_reply.get("ok", None):
                        print >> logFile, ("ERROR save to mongo: %r\n" % mongo_reply)
        except Exception:
            catch()
    logFile.close()


def convertDynamicQuests(jsonQuestData, logFileName):
    for award in itertools.chain(jsonQuestData["Awards"], jsonQuestData["AlternativeAwards"]):
        if award["AwardType"] >= DynamicQuestAwardType.RedPerl and award[
            "AwardType"] < DynamicQuestAwardType.RandomTalentFromPool:
            award["AwardType"] += 1
    if jsonQuestData["QuestData"]:
        for objective in jsonQuestData["QuestData"]:
            if objective["QuestCheckType"] == DynamicQuestCheckType.Instant and objective["InstantCondition"][
                "ResourceType"] > CastleResources.Perl:
                objective["InstantCondition"]["ResourceType"] += 1
    if jsonQuestData["AlternativeQuestData"]:
        for objective in jsonQuestData["AlternativeQuestData"]:
            if objective["QuestCheckType"] == DynamicQuestCheckType.Instant and objective["InstantCondition"][
                "ResourceType"] > CastleResources.Perl:
                objective["InstantCondition"]["ResourceType"] += 1


def convertDynamicQuestsForPartySizeStrong(jsonQuestData, logFileName):
    if "SessionCondition" not in jsonQuestData:
        jsonQuestData["SessionCondition"] = list()

    for cond in itertools.chain(jsonQuestData["SessionCondition"]):
        if "IsPlayerPartySizeStrongCond" not in cond:
            cond["IsPlayerPartySizeStrongCond"] = 0
        if "IsEnemyPartySizeStrongCond" not in cond:
            cond["IsEnemyPartySizeStrongCond"] = 0


def convertDynamicQuestsForTournament(jsonQuestData, logFileName):
    if "PreConditions" not in jsonQuestData:
        jsonQuestData["PreConditions"] = list()

    for award in itertools.chain(jsonQuestData["Awards"], jsonQuestData["AlternativeAwards"]):
        if "AwardConditionType" not in award:
            award["AwardConditionType"] = DynamicQuestAwardConditionType.AfterWin


def convertDynamicQuestsForNewTournamentFormat(jsonQuestData, logFileName):
    if "AcceptFilter" in jsonQuestData and "DependedTournamentQuests" not in jsonQuestData["AcceptFilter"]:
        jsonQuestData["AcceptFilter"]["DependedTournamentQuests"] = list()


def removeUnusedHeroRatings(guilddata, logFile, rawData):
    if guilddata.GuildAuid == 0:
        return guilddata

    actualIds = []
    for memId, member in guilddata.Members.iteritems():
        for ratingInfoId in member.HeroRatings.values():
            actualIds.append(ratingInfoId)

    for _id, heroRating in guilddata.MemberDayRatingKeeper.items():
        if _id not in actualIds:
            guilddata.MemberDayRatingKeeper.__delitem__(_id)
            logFile.write("Hero rating with id %d removed from GuildData of guild %d\n" % (_id, guilddata.GuildAuid))

    return guilddata


def leaveNoMoreThanNVassals(guilddata, logFile, rawData, removedAuids, moneyback):
    # change it if you need
    N = 5
    if guilddata.GuildAuid == 0:
        return guilddata
    if guilddata.GuildAuid in moneyback:
        guilddata.GuildInfo.CWPoints_Clan += moneyback[guilddata.GuildAuid]
        del moneyback[guilddata.GuildAuid]
    vassalRatings = {}
    for _id, vassal in guilddata.GuildVassals.items():
        if vassal and vassal.ShortInfo.get():
            vassalRatings[_id] = vassal.ShortInfo.Rating
        else:
            # ?? ?????? ???, ? ???? ?
            guilddata.GuildVassals.remove(vassal)
    vassalsSorted = [vassalId for vassalId, rating in sorted(vassalRatings.items(), key=lambda x: x[1])]
    if len(vassalsSorted) > N:
        while len(vassalsSorted) > N:
            vassal = guilddata.getGuildMapEntityByID(vassalsSorted.pop(0))
            removedAuids.append(vassal.ShortInfo.GuildAuid)
            logFile.write("Vassal with id %d removed from GuildData of guild %d\n" % (
            vassal.ShortInfo.GuildAuid, guilddata.GuildAuid))
            vassal.ShortInfo = 0
            guilddata.GuildVassals.remove(vassal)

    return guilddata


def removeSuzerainForSelectedGuilds(guilddata, logFile, rawData, SD, removedAuids):
    if guilddata.GuildAuid == 0 or guilddata.GuildAuid not in removedAuids:
        return guilddata

    if not (guilddata.GuildSuzerain and guilddata.GuildSuzerain.get()):
        guilddata.GuildSuzerain, _id = guilddata.newGuildMapEntity()

    suzerain = guilddata.GuildSuzerain
    if not (suzerain.ShortInfo and suzerain.ShortInfo.get()):
        suzerain.ShortInfo, _id = guilddata.newGuildShortInfo()

    shortInfo = suzerain.ShortInfo
    logFile.write("Suzerain with id %d removed from GuildData of guild %d\n" % (
    suzerain.ShortInfo.GuildAuid, guilddata.GuildAuid))
    shortInfo.GuildAuid = 0
    shortInfo.GuildShortName = ""
    shortInfo.GuildFullName = ""
    shortInfo.Level = 0
    shortInfo.Rating = 0
    shortInfo.Place = 0
    shortInfo.RatingPositionChange = 0
    shortInfo.ShopLevel = 0
    shortInfo.MembersCount = 0
    shortInfo.IconChangesCount = 0
    # ????, ? ?? ? ?? ??? ??????? ???????
    guilddata.checkUltimateShop(SD)

    return guilddata


def siegesRemove():
    guildsAffected = dict()
    for options in MONGO_CONFIG:
        print "\nProcessing %r" % options['mongo_base']
        try:
            connection = pymongo.Connection(options['mongo_addr'], options['mongo_port'])
            db = getattr(connection, options['mongo_base'], None)
            if db and db.sieges and db.sieges.count():
                dbsieges = db.sieges
                sieges = [s for s in dbsieges.find({})]
                print "Total sieges:", len(sieges)
                for siege in sieges:
                    try:
                        # ??? ?????? ?????????
                        for target in siege['participants']:
                            if target['price']:
                                guildsAffected[target['id']] = target['price']
                        mongo_reply = dbsieges.remove({"_id": siege['_id']}, w=1)
                        if not (mongo_reply and mongo_reply.get("ok", None)):
                            print "ERROR saving siege %s to mongo: %r\n" % (siege['_id'], mongo_reply)
                    except Exception:
                        catch("Error processing siege %s", siege['_id'])
        except Exception:
            catch()
    with open("siege_moneyback.json", 'wt') as f:
        f.write(json_dumps(guildsAffected))
        f.write("\n")
    return guildsAffected


def connect_mongo(config):
    opt = ClassDict(coord_cfg.COORDINATOR_MONGO_CONFIG[0])
    return getattr(pymongo.Connection(opt.mongo_addr, opt.mongo_port), opt.mongo_base, None)


def main():
    gc.disable()

    arglist = sys.argv[1:]
    print "arglist: ", arglist
    # TODO: ????????
    # 1. ???? ??? ? ???
    # 2. ????????? ???? ????????????
    opts, args = getopt.getopt(arglist, "", ["check", "reset_users=", "add_fb_users_file=", "del_users=",
                                             "dump_users_data=", "fulldump_users_data=", "replace_users_data=",
                                             "change_fraction=", "grep_users_from_log=", "hire_hero=",
                                             "dump_mysql_heroes=", "find_user_by_nick=", "dump_all_users_data",
                                             "check_all_users_data",
                                             "dump_millionaire_users", "dump_populationlimit_users=", "match_auid",
                                             "dump_all_users_snid", "grep_file=",
                                             "light_duplicates", "dump_duplicates", "remove_duplicates",
                                             "remove_duplicates_coll=", "reshard_users", "add_user_restrictions=",
                                             "add_fame=", "add_silver=", "replenish_gold=", "add_resource=",
                                             "add_premium=", "export_mysql_buildings=", "mirror_all_users",
                                             "out=", "out_path=", "soc_agr=", "foreach_gc=", "foreach_sleep=",
                                             "foreach_sleep_users=", "foreach_batch=",
                                             "dump_input_data=", "dump_output_data=", "dump_resources_csv=",
                                             "mongo_config=", "sql_config=", "mirror_config=", "pretty_dump=",
                                             "convert_mongo_json=", "compensate_ratings=", "fix_guilddata",
                                             "return_guildauid_to_acc=", "return_guildauid_to_acc_with_null_check=",
                                             "find_users_with_wrong_class_talents=", "download_user_statistics=",
                                             "list_guild_members=", "check_multiguild_members", "ignore_multiguild",
                                             "fix_users_md_version=", "get_all_guild_members", "convert_guild_ratings",
                                             "add_cw_npc_entities", "change_bad_npc_vassals",
                                             "unsiege_npc", "remove_npc_suzerains=", "convert_guild_entities",
                                             "remove_unknown_guild_members",
                                             "return_guild_short_info", "fill_guild_recruitment_params",
                                             "index_mongo_recruitment", "fix_guild_hero_ratings",
                                             "check_reproduction_vs",
                                             "fix_reproduction_vs", "convert_dynamic_quests",
                                             "convert_dynquests_for_tournament",
                                             "convert_dynquests_for_party_size_strong",  # PF-98150
                                             "remove_unused_hero_ratings", "decrease_vassals_number",
                                             "cut_extra_production_from_buildings",
                                             "fix_guild_soulbound_talents",
                                             "convert_dynquests_for_new_tournament_format",
                                             "clear_list_completed_dynquests", "delete_tutorial_accounts",
                                             "find_users_with_small_md_version=", "fix_users_with_small_md_version",
                                             "find_users_with_bad_premium_acc=", "find_guild_with_abnormal_exp=",
                                             "find_broken_tutorial_acc=",
                                             ])

    # ??? ???????? ????? (?????
    # ????? ????? ?????? ????? ?????? ??????? ????????
    # TODO - ?????????
    global SOC_AGR
    global OUT_PATH
    for opt, arg in opts:
        if opt == "--out" and arg:
            global OUT_FILE
            OUT_FILE = arg

        elif opt == "--out_path":
            if arg and isinstance(arg, basestring):
                if arg[-1] not in ['/', '\\']:
                    arg += '/'
                OUT_PATH = arg

        elif opt == "--soc_agr":
            SOC_AGR = arg

        elif opt == "--dump_input_data":
            global DUMP_INPUT_DATA
            DUMP_INPUT_DATA = toint(arg)

        elif opt == "--dump_output_data":
            global DUMP_OUTPUT_DATA
            DUMP_OUTPUT_DATA = toint(arg)

        elif opt == "--pretty_dump":
            global PRETTY_DUMP
            PRETTY_DUMP = toint(arg)

        elif opt == "--foreach_gc":
            global FOREACH_USERS_PER_GC_COLLECT
            FOREACH_USERS_PER_GC_COLLECT = max(1, toint(arg))
            global FOREACH_USERS_PER_GC_COLLECT_CHANGED
            FOREACH_USERS_PER_GC_COLLECT_CHANGED = True
            print "foreach_gc(%s): FOREACH_USERS_PER_GC_COLLECT=%s now" % (arg, FOREACH_USERS_PER_GC_COLLECT)

        elif opt == "--foreach_sleep":
            global FOREACH_SLEEP_MSEC_PER_USER
            FOREACH_SLEEP_MSEC_PER_USER = max(1, toint(arg))
            print "foreach_sleep(%s): FOREACH_SLEEP_MSEC_PER_USER=%s msec now" % (arg, FOREACH_SLEEP_MSEC_PER_USER)

        elif opt == "--foreach_sleep_users":
            global FOREACH_SLEEP_USERS_PER_PASS
            FOREACH_SLEEP_USERS_PER_PASS = max(1, toint(arg))
            print "foreach_sleep_users(%s): FOREACH_SLEEP_USERS_PER_PASS=%s now" % (arg, FOREACH_SLEEP_USERS_PER_PASS)

        elif opt == "--foreach_batch":
            global FOREACH_BATCH_SIZE
            FOREACH_BATCH_SIZE = max(10, toint(arg))
            print "foreach_batch(%s): FOREACH_BATCH_SIZE=%s now" % (arg, FOREACH_BATCH_SIZE)

        elif opt == "--mongo_config":
            global MONGO_CONFIG
            try:
                MONGO_CONFIG = json_loads(arg)
                print "parsed mongo_config: %s" % (MONGO_CONFIG)
            except:
                catch()
                exit(0)

        elif opt == "--sql_config":
            global SQL_CONFIG
            try:
                SQL_CONFIG = json_loads(arg)
                print "parsed sql_config: %s" % (SQL_CONFIG)
            except:
                catch()
                exit(0)

        elif opt == "--mirror_config":
            global MIRROR_CONFIG
            try:
                MIRROR_CONFIG = json_loads(arg)
                print "parsed mirror_config: %s" % (MIRROR_CONFIG)
            except:
                catch()
                exit(0)

        elif opt == "--ignore_multiguild":
            admin_guilds.IGNORE_MULTIGUILD = True

    # ??? ???? ????? (????)
    # ?????, ????? ??? ???? ?? ???? ????????? ??? ??? ????????!
    for opt, arg in opts:
        if opt == "--grep_file":
            try:
                in_path, filemask, model_string, outfilename = arg.split(",")
            except:
                print "ERROR: bad arguments for --grep_file, should be --grep_file=<in_path>,<filemask>,<model_string>,<outfilename>"
                return

            print "GREP in_path=%r, filemask: %r, model string: %r, outfilename: %r (OUT_PATH: %r)" % (
                in_path, filemask, model_string, outfilename, OUT_PATH)

            f_out = open(OUT_PATH + outfilename, "wt")
            file_list = os.listdir(in_path)

            for filename in file_list[:]:
                if filename[:len(filemask)] == filemask:
                    msg = '================== GREP FILENAME: %s =======================\n' % filename
                    print msg
                    f_out.write(msg)

                    grep_file(in_path + filename, model_string, f_out)

            f_out.close()

        elif opt == "--return_guildauid_to_acc":
            returnGuildAuidToAcc(arg, False)

        elif opt == "--return_guildauid_to_acc_with_null_check":
            returnGuildAuidToAcc(arg, True)

        elif opt == "--fix_guilddata":
            fixGuildData()

        elif opt == "--list_guild_members":
            listGuildMembers(arg)

        elif opt == "--check_multiguild_members":
            checkMultiguildMembers()

        elif opt == "--grep_users_from_log":
            PATH = "../logs/"

            filemask = arg
            print "GREP_USERS_FROM_LOG filemask: ", filemask

            uid_list = {}
            f_out = open(OUT_PATH + "fb_users.log", "wt")
            file_list = os.listdir(PATH)

            for filename in file_list[:]:
                if filename[:len(filemask)] == filemask:
                    msg = '================== GREP FILENAME: %s =======================' % filename
                    print msg
                    f_out.write(msg)

                    grep_fb_users_from_file(PATH + filename)

            f_out.close()

            # ??? ?????, ? ????? ???
            users_total = 0
            users_added = 0
            users_present = 0
            users_failed = 0
            print "ADD FB USERS: from grepped log"

            for uid, fb_login in uid_list.iteritems():
                users_total += 1
                print "===== ADD_USER %r : uid %d ======" % (fb_login, uid)
                login, opts, dbi = getSqlUserRequisites("fb", fb_login)
                prev_uid = getSqlUserUID(login, opts)
                if not prev_uid:
                    reply = addNewSqlUser(uid, login, "AUTOADD", opts)

                    if reply:
                        users_added += 1
                    else:
                        print "WARNING: couldnt add new fb user (uid=%r, login=%r)" % (uid, login)
                        users_failed += 1

                elif prev_uid == uid:
                    users_present += 1
                    print "WARNING: fb user %r already present in sql base (uid=%r)" % (login, uid)

                else:  ## prev_uid != uid:
                    print "FAIL: prev_uid %d != uid %d for login '%s'" % (prev_uid, uid, login)
                    users_failed += 1

            print "==============\n ADDED USERS: %d / %d (already present: %d, failed: %d)" % (
                users_added, users_total, users_present, users_failed)


        elif opt in ["--reset_users", "--dump_users_data", "--del_users", "--change_fraction", "--replace_users_data",
                     "--fulldump_users_data"] \
                and isinstance(arg, basestring):
            user_logins = arg.split(",")
            for login_pair in user_logins:
                if login_pair and isinstance(login_pair, basestring):
                    try:
                        sn_id, sn_login = login_pair.split(":")[:2]
                        if sn_id and sn_login:
                            if sn_id == "auid":
                                auid = sn_login
                                sn_id, sn_login = getSocialRequisitesByAuid(auid)
                                print "[getSocialRequisitesByAuid] snid:snlogin %r:%r found for auid=%s" % (
                                sn_id, sn_login, auid)

                            print "===== %s USER %r:%r ======" % (opt, sn_id, sn_login)
                            login, opts, dbi = getSqlUserRequisites(sn_id, sn_login)
                            uid = getSqlUserUID(login, opts)
                            if uid:
                                # --------------------------------------------------------------------
                                if opt == "--reset_users":
                                    clearUserData(uid)

                                # --------------------------------------------------------------------
                                elif opt == "--dump_users_data":
                                    handleUserData(sn_id, sn_login, uid, dumpUserData)

                                elif opt == "--fulldump_users_data":
                                    handleUserData(sn_id, sn_login, uid, dumpUserAndAggregatorData)

                                # --------------------------------------------------------------------
                                elif opt == "--replace_users_data":
                                    try:
                                        user_data_filename = login_pair.split(":")[2]
                                        try:
                                            handleUserData(sn_id, sn_login, uid, replaceUserData, save_handled_data=1,
                                                           user_data_filename=user_data_filename)
                                        except:
                                            catch()
                                            print "ERROR: cant load data for login pair %r:%r, user data filename %r" % (
                                                sn_id, sn_login, user_data_filename)
                                    except:
                                        catch()
                                        print "ERROR: no user data filename specified for login pair %r:%r, should be <snid>:<snlogin>:<user_data_filename>" \
                                              % (sn_id, sn_login)

                                # --------------------------------------------------------------------
                                elif opt == "--change_fraction":
                                    try:
                                        fraction = login_pair.split(":")[2]
                                        try:
                                            handleUserData(sn_id, sn_login, uid, changeUserFraction,
                                                           save_handled_data=1, fraction=fraction)
                                        except:
                                            catch()
                                            print "ERROR: cant handle data for login pair %r:%r" % (sn_id, sn_login)
                                    except:
                                        catch()
                                        print "ERROR: no fraction specified for login pair %r:%r, should be <snid>:<snlogin>:<fraction>" % (
                                            sn_id, sn_login)

                                # --------------------------------------------------------------------
                                elif opt == "--del_users":
                                    reply = deleteSqlUser(uid, login, opts)
                                    clearUserData(uid)

                            else:
                                print "ERROR: cant find uid for login pair %r:%r" % (sn_id, sn_login)
                        else:
                            raise
                    except:
                        catch()
                        print "ERROR: bad login pair: %r, should be '<snid>:<snuid>' or 'auid:<auid>'" % login_pair

        elif opt == "--check":
            checkMongoUserData()

        elif opt == "--add_user_restrictions":
            users_file = open(arg, "rt")
            sql_options = ClassDict(SQL_CONFIG[0])  # ??? ??? ?FirstSQL ???
            added_count = 0
            login_count = 0
            for uid_string in users_file:
                sn_login = uid_string.strip()
                if sn_login:
                    login_count += 1
                    try:
                        snid, snuid = sn_login.split(":")
                    except:
                        catch()
                        print "ERROR: bad sn_login: %r, should be '<snid>:<snuid>'" % sn_login
                        continue

                    try:
                        query = "INSERT INTO tbl_user_restrictions (`login`,`timestamp`,`key`) VALUES ('%s',%d,'admin_users');" % (
                            sn_login, int(time.time()))
                        print "run sql query: %s" % query
                        result = syncSqlCommand(query, sql_options)
                        print "- sql result: %s" % result
                        if result:
                            added_count += 1
                    except:
                        catch()
                        print "ERROR: failed to add sn_login=%r to MYSQL" % sn_login

            print "=== DONE; added %d/%d logins to tbl_user_restrictions" % (added_count, login_count)

        # FOREACH mongo user
        elif opt in ["--dump_mysql_heroes", "--find_user_by_nick", "--dump_all_users_data", "--check_all_users_data",
                     "--dump_millionaire_users",
                     '--match_auid', '--dump_all_users_snid', '--dump_populationlimit_users', "--reshard_users"]:
            if opt == "--dump_mysql_heroes":
                try:
                    # ???? ?? ?????JSON: {"sql_host":"localhost:3306","sql_base":"pw1","sql_user":"pw","sql_pass":"pwdata"}
                    sql_options = ClassDict(json_loads(arg))
                    if sql_options and len(sql_options) == 4:
                        foreachUserData(dumpUserHeroesData2Mysql, sql_options=sql_options)  # save_input_data=1

                except:
                    catch()
                    print 'ERROR: bad arguments, should be --dump_mysql_heroes_data={"sql_host":"<host>","sql_base":"<base>","sql_user":"<user>","sql_pass":"<pass>"}'

            elif opt == "--find_user_by_nick":
                # ???? ?? ??? <nickname>:<nickname_encoding>, default nickname_encoding="cp1251"
                args_split = arg.split(":")
                if len(args_split) == 1:
                    nick_encoded = arg
                    nick_encoding = "cp1251"
                elif len(args_split) == 2:
                    nick_encoded, nick_encoding = args_split
                else:
                    print 'ERROR: bad arguments %r, should be --find_user_by_nick=<nick>:<cp1251|utf8|..other nick encoding..>,...' % str(
                        arg)

                try:
                    nick_unicode = nick_encoded.decode(nick_encoding)
                    print "converted to nick_unicode: %r" % (nick_unicode)
                except:
                    catch()
                    print "ERROR: cant convert nick from encoding %r to unicode" % (nick_encoding)
                    return

                foreachUserData(findUserByNickname, nick_unicode=nick_unicode)

            elif opt == "--dump_all_users_data":
                foreachUserData(dumpUserData)
            elif opt == "--check_all_users_data":
                iDict = ClassDict()
                iDict.Config = MultiConfig()
                iDict.SD = StaticData("../xdb/ExportedSocialData.xml", iDict.Config.getMainConfig())
                foreachUserData(checkUserData, save_input_data=0, save_handled_data=0, I=iDict)
            elif opt == "--dump_millionaire_users":
                iDict = ClassDict()
                iDict.Config = MultiConfig()
                iDict.SD = StaticData("../xdb/ExportedSocialData.xml", iDict.Config.getMainConfig())
                foreachUserData(dumpMillionaire, save_input_data=0, save_handled_data=0, I=iDict)
            elif opt == "--dump_populationlimit_users":
                limit = 2000
                if arg:
                    limit = int(arg)

                iDict = ClassDict(Config=MultiConfig())
                iDict.SD = StaticData("../xdb/ExportedSocialData.xml", iDict.Config.getMainConfig())
                foreachUserData(dumpPopulationLimit, save_input_data=0, save_handled_data=0, I=iDict, limit=limit)
            elif opt == "--match_auid":
                m = MatchUserData('auid_snid.txt', SOC_AGR)
                foreachUserData(m)
            elif opt == "--dump_all_users_snid":
                m = DumpUserData(os.path.abspath(OUT_PATH) + '\\snid.txt')
                foreachUserData(m)
            elif opt == "--reshard_users":
                foreachUserData(passUserData, save_input_data=0, save_handled_data=1, dump_handled_data=0,
                                shard_writes=1)

        elif opt == "--light_duplicates":
            forEachMongoUserKey_FindDuplicates()
        elif opt == "--dump_duplicates":
            foreachDuplicateData(save_input_data=DUMP_INPUT_DATA)
        elif opt == "--remove_duplicates":
            foreachDuplicateData(save_input_data=DUMP_INPUT_DATA, delete_duplicates=1)

        elif opt == "--remove_duplicates_coll":
            args_split = arg.split(":")
            if len(args_split) == 3:
                id_coll_name = args_split[0]
                key_name = args_split[1]
                delete_duplicates = toint(args_split[2])
            else:
                print 'ERROR: bad arguments %r, should be --remove_duplicates_coll=<id_collection_name>:<key_name>:<delete_duplicates=0/1>' % str(
                    arg)
            removeDuplicateDataByCollection(id_coll_name, key_name, save_input_data=DUMP_INPUT_DATA,
                                            delete_duplicates=delete_duplicates)

        elif opt == "--mirror_all_users":
            # ?????? ?? ?? mongo (????? ???????? ???? "pers") ?????? ??? ???? ? ???
            forEachMongoUserKey_AddMirrorRequest()

        elif opt == "--add_fb_users_file":
            try:
                args = arg.split(":")
                if len(args) == 2:
                    filename = args[0]
                    start_id = max(1, tolong(args[1]))
                elif len(args) == 1:
                    print "WARNING: no start_id, assuming start_id=1"
                    filename = arg
                    start_id = 1
                else:
                    print "ERROR: bad arguments (%r), should be --add_fb_users_file=<filename>:<start_id>" % arg
                    continue
                print "ADD FB USERS: from filename %r, start_id=%d" % (filename, start_id)

                # ??? ????? ????, ? ???
                users_total = 0
                users_added = 0
                users_present = 0
                users_failed = 0

                users_file = open(filename, "rt")
                for uid_string in users_file:
                    users_total += 1
                    start_id += 1
                    sn_id = "fb"
                    sn_login = uid_string.strip()
                    print "===== ADD_USER %r:%r ======" % (sn_id, sn_login)
                    login, opts, dbi = getSqlUserRequisites("fb", sn_login)
                    uid = getSqlUserUID(login, opts)
                    if not uid:
                        ##print "TODO: add new fb user (login=%r)" % (login)
                        id = (dbi + 1) * 100000 + start_id
                        reply = addNewSqlUser(id, login, "AUTOADD", opts)

                        if reply:
                            users_added += 1
                        else:
                            print "WARNING: couldnt add new fb user (id=%r, login=%r)" % (id, login)
                            users_failed += 1
                    else:
                        users_present += 1
                        print "WARNING: fb user %r already present in sql base (uid=%r)" % (sn_login, uid)

                print "==============\n ADDED USERS: %d / %d (already present: %d, failed: %d)" % (
                    users_added, users_total, users_present, users_failed)

            except:
                catch()
                print "ERROR: can't open file %r" % arg


        elif opt in ["--replenish_gold"]:
            try:
                args = arg.split(":")
                if len(args) == 2:
                    filename = args[0]
                    amount = float(args[1])
                else:
                    print "ERROR: bad arguments (%r), should be %s=<auids_filename>:<replenish_amount>" % (args, opt)
                    continue

                # -------------------------------------------------------------------------------------------------
                # ????ZZima-?????
                import base64, binascii
                from suds.client import Client
                import izzima

                zzWrapper = ZZimaArgWrapper()
                # AsyncZZima ??????? ?? zzWrapper ?????? ?????? ?????? AsyncZZ().addQuery("AccountReplenish", args, callback, params)
                ZZ = izzima.AsyncZZima(None, coord_cfg.COORDINATOR_ZZIMA_SERVICE_NAME)
                izzima.AsyncZZ = zzWrapper
                connection = Client(coord_cfg.COORDINATOR_ZZIMA_WSDL)

                # -------------------------------------------------------------------------------------------------
                # ???????? ?? ?????????? ???.??????
                HTTP = ISyncHttp()

                failed_filename = "failed." + filename
                print "%s: for fbid list from filename %r; failed fbid list will go to file '%s'" % (
                    opt, filename, failed_filename)

                # ????? ? ???
                users_total = 0

                users_file = open(filename, "rt")
                failed_users_file = open(failed_filename, "wt")

                for auid_string in users_file:
                    users_total += 1
                    print "\n-- next user %s --------------------------" % auid_string

                    try:
                        auid = toint(auid_string.strip())
                        if auid:
                            bid = coord_cfg.COORDINATOR_AGG_BILLING_PREFIX + str(auid)
                            ##ZZ.getBalance(bid) # ?????????? ?? ???
                            if amount > 0:
                                ZZ.replenish(bid, amount, "admin_users_replenish")  # ?????????? ?? ???
                            else:
                                ZZ.writeOff(bid, -amount, "admin_users_replenish")  # ?????????? ?? ???
                            result = eval('connection.service.%s(zzWrapper.args)' % zzWrapper.method)
                            print "%s result: %s" % (zzWrapper.method, str(result))

                            if result.code == 0:
                                # OK
                                continue
                            else:
                                if result.code == -1008:
                                    ZZ.getBalance(bid)
                                    result = eval('connection.service.%s(zzWrapper.args)' % zzWrapper.method)
                                    print "%s result: %s" % (zzWrapper.method, str(result))
                                    if result.code == 0:
                                        ZZ.writeOff(bid, result.amount, "admin_users_replenish")  # ?????????? ?? ???
                                        secondResult = eval('connection.service.%s(zzWrapper.args)' % zzWrapper.method)
                                        if secondResult.code == 0:
                                            continue
                                else:
                                    print "ERROR: billing operation FAILED (error code %s) for user %s (billing id %r)" % (
                                        result.code, auid, bid)
                        else:
                            print "ERROR: aggregator auid for user %s not found" % (auid)
                    except:
                        print catch()
                        # FAIL: ????? ????? ??? ??? failed_users
                        failed_users_file.write("%s\n" % auid_string)

            except:
                print catch()

        elif opt == "--compensate_ratings":
            try:
                from ixchange import IAsyncHttpSocialExchange

                HTTP = ISyncHttp()
                print 'using social exchange on address %r' % coord_cfg.COORDINATOR_SOCIAL_EXCHANGE_URL
                SEX = IAsyncHttpSocialExchange(HTTP, coord_cfg.COORDINATOR_SOCIAL_EXCHANGE_URL, '', request_limit=1000)

                print "loading users from file: %r" % arg
                import_file = open(arg, "rt")
                sessions = {}
                winners = {}
                users = 0
                # loading users
                for index, json_string in enumerate(import_file):
                    tokens = [token for token in json_string.replace('\n', '').replace('\r', '').split(';') if token]
                    if len(tokens) > 0:
                        sid, team, auid, hero, rating_change = tokens
                        if sid not in sessions:
                            sessions[sid] = []
                        sessions[sid].append((team, auid, hero, float(rating_change)))
                        users += 1
                print 'found %d sessions, %d users' % (len(sessions), users)
                import_file.close()

                # determine who is winner
                for sid, users in sessions.items():
                    win_team = None
                    lose_team = None
                    winners[sid] = None
                    for team, auid, hero, rating_change in users:
                        if rating_change > 0:
                            winners[sid] = team
                            break

                # collect victims list
                victims = {}
                for sid, win_team in winners.items():
                    users = sessions[sid]
                    for team, auid, hero, rating_change in users:
                        if rating_change < 0 and (
                                            win_team == None or team != win_team or True):  # use True for compensating all negative rating change
                            if auid not in victims:
                                victims[auid] = []
                            victims[auid].append((hero, rating_change, win_team != team))
                print 'found %d victims' % len(victims)

                # sending changes
                HERO_RATING = 4
                total_rating = 0
                heroes = 0
                for auid, changes in victims.items():
                    awards = []
                    for hero, rating_change, loser in changes:
                        awards.append({'type': HERO_RATING, 'id': hero, 'count': -rating_change})
                        total_rating += -rating_change
                        heroes += 1
                    change = {
                        'type': 'session_awards',
                        'tm_expire': 60 * 60 * 24 * 30 * 12,
                        'roll_id': int(time.time()),
                        'count': 1,
                        'awards': awards
                    }
                    data = [change]
                    if True:
                        print 'processing user (auid=%s heroes=%d)' % (auid, len(changes))
                        SEX.sendMail('pw', auid, data)
                if heroes > 0:
                    print 'compensated rating (users=%d heroes=%d total=%2.1f avg=%2.1f)' % (
                        len(victims), heroes, total_rating, total_rating / heroes)
            except:
                catch()

        elif opt == "--convert_mongo_json":
            try:
                print "converting file: %r" % arg
                import_file = open(arg, "rt")
                for json_string in import_file:
                    json_doc = json_loads(json_string)
                    if json_doc:
                        user_data_string = json_doc.get("data", {})
                        user_key = json_doc.get("key", "")
                        print "parsing data for user key=%r" % user_key
                        if user_data_string and user_key:
                            try:
                                acc = PersistentDataManager.newSimpleDataAcc(user_data_string)
                            except:
                                catch()
                                print "ERROR loading data for user key %r" % user_key
                                return

                            try:
                                cache_dict = PersistentDataManager.makeSaveDict(acc)
                                export_filename = arg + "." + user_key + ".json"
                                print "writing json output to file: %r (pretty=%s)" % (export_filename, PRETTY_DUMP)
                                export_file = open(export_filename, "wt")
                                export_file.write(prepare_printable_dump(cache_dict))
                                export_file.close()
                            except:
                                catch()
                                print "ERROR writing output json for user key %r" % user_key
                import_file.close()
            except:
                catch()


        elif opt in ["--hire_hero", "--add_fame", "--add_silver", "--add_resource", "--add_premium",
                     "--export_mysql_buildings", "--dump_resources_csv"]:
            try:
                args = arg.split(":")
                if len(args) > 1:
                    filename = args[0]
                else:
                    print "ERROR: bad auid filename in arguments (%r), should be %s=<filename>:..." % (arg, opt)
                    continue

                failed_filename = "failed." + filename
                print "%s: for auid list from filename %r; failed auid list will go to file '%s'" % (
                    opt, filename, failed_filename)

                if opt == "--dump_resources_csv":
                    if len(args) > 1:
                        csv_filename = args[1]
                        csv_file = open(csv_filename, "wt")
                        csv_file.write("auid;Silver;Perl;Resource1;Resource2;Resource3;Gold;Population;\n")
                    else:
                        print "ERROR: bad output csv filename in arguments (%r), should be %s=<auid_filename>:<csv_filename>" % (
                            arg, opt)
                        exit(0)

                # ??? ????? ????, ? ???
                users_total = 0
                users_added = 0
                users_failed = 0
                users_not_present = 0

                users_file = open(filename, "rt")
                failed_users_file = open(failed_filename, "wt")
                for auid_string in users_file:
                    auid = toint(auid_string.strip())
                    if auid:
                        users_total += 1

                        # ??? ????? ????????? ???? -- ???????
                        time.sleep(FOREACH_SLEEP_MSEC_PER_USER / 1000.0)  # ??? ? ???? ?? ?????? ?????
                        if users_total % FOREACH_USERS_PER_GC_COLLECT == 0:
                            t0 = time.time()
                            collect_count = gc.collect()
                            t1 = time.time()
                            print "gc time: %.3f (collected: %d), passed %d auids" % (
                            t1 - t0, collect_count, users_total - 1)

                        print "===== find user auid %r ======" % (auid)

                        sn_id, sn_login = getSocialRequisitesByAuid(auid)
                        print "snid:snlogin %r:%r found for auid=%s" % (sn_id, sn_login, auid)

                        # ???? ??????, ????? ? ??? ??uid ?modeldata
                        if sn_id and sn_login:
                            login, opts, dbi = getSqlUserRequisites(sn_id, sn_login)
                            uid = getSqlUserUID(login, opts)
                            if uid:
                                try:
                                    if opt == "--hire_hero":
                                        print "ERROR: ?solete option, can't automatically hire heroes now, use GM Tools instead"
                                        # hero_class_name = args[1]
                                        return

                                    elif opt == "--add_fame":
                                        try:
                                            add_value = int(args[1])
                                        except():
                                            catch()
                                            print "ERROR: bad arguments (%r), should be %s=<filename>:<add_fame_value>" % (
                                            arg, opt)
                                            return

                                        mongo_reply = handleUserData(sn_id, sn_login, uid, addModelValue,
                                                                     save_handled_data=1, \
                                                                     change_path="ModelData/LordInfo",
                                                                     change_key="Fame",
                                                                     add_value=add_value)

                                    # ---------------------------------------------------------
                                    elif opt == "--add_silver":
                                        try:
                                            add_value = int(args[1])
                                        except():
                                            catch()
                                            print "ERROR: bad arguments (%r), should be %s=<filename>:<add_silver_value>" % (
                                            arg, opt)
                                            return

                                        mongo_reply = handleUserData(sn_id, sn_login, uid, addModelValue,
                                                                     save_handled_data=1, \
                                                                     change_path="ModelData/Resources/ResourceTable",
                                                                     change_key="Silver",
                                                                     add_value=add_value)

                                    elif opt == "--add_resource":
                                        try:
                                            resource_name, add_value = args[1], int(args[2])
                                        except():
                                            catch()
                                            print "ERROR: bad arguments (%r), should be %s=<filename>:<resource_name>:<add_value>" % (
                                                arg, opt)
                                            return

                                        mongo_reply = handleUserData(sn_id, sn_login, uid, addModelValue,
                                                                     save_handled_data=1, \
                                                                     change_path="ModelData/Resources/ResourceTable",
                                                                     change_key=resource_name, add_value=add_value)

                                    elif opt == "--add_premium":
                                        try:
                                            premium_duration = int(args[1])
                                        except():
                                            catch()
                                            print "ERROR: bad arguments (%r), should be %s=<filename>:<add_duration_seconds>" % (
                                            arg, opt)
                                            return

                                        mongo_reply = handleUserData(sn_id, sn_login, uid, addPremiumDuration,
                                                                     save_handled_data=1, \
                                                                     premium_duration=premium_duration)

                                    elif opt == "--export_mysql_buildings":
                                        try:
                                            building_type = args[1] or ""
                                            if building_type.lower() == "all":
                                                building_crc = 0
                                            else:
                                                building_crc = crc32(building_type)
                                            print "parsed building_type=%r, building_crc=%s" % (
                                            building_type, building_crc)

                                            args2 = arg.split("::")
                                            if len(args2) == 2:
                                                sql_options = ClassDict(json_loads(args2[1]))
                                                if not (sql_options and len(sql_options) == 4):
                                                    print 'ERROR: bad sql_options (%r), should be like {"sql_host":"host:port","sql_base":"..","sql_user":"..","sql_pass":".."}' % (
                                                        args2[1])
                                                    return
                                            else:
                                                print "ERROR: bad arguments (%r), should be %s=<filename>:<building_name|ALL>::{json_sql_options}" % (
                                                    arg, opt)

                                        except():
                                            catch()
                                            print "ERROR: bad arguments (%r), should be %s=<filename>:<building_type>" % (
                                            arg, opt)
                                            return

                                        mongo_reply = handleUserData(sn_id, sn_login, uid, exportMysqlBuildings,
                                                                     save_handled_data=0, \
                                                                     sql_options=sql_options, building_crc=building_crc,
                                                                     auid=auid,
                                                                     timestamp=toint(time.time()))

                                    elif opt == "--dump_resources_csv":
                                        mongo_reply = handleUserData(sn_id, sn_login, uid, dumpResourcesCSV,
                                                                     save_handled_data=0, \
                                                                     auid=auid, csv_file=csv_file)

                                    # ---------------------------------------------------------

                                    if mongo_reply:
                                        users_added += 1
                                        continue
                                    else:
                                        print "ERROR: handleUserData returned empty mongo_reply for user %r! failed" % sn_login
                                        users_failed += 1
                                except:
                                    catch()
                                    print "ERROR: cant handle data for login pair %r:%r" % (sn_id, sn_login)
                                    users_failed += 1
                            else:
                                users_not_present += 1
                                print "WARNING: %r user %r not registered" % (sn_id, sn_login)
                        else:
                            print "WARNING: sn requisites not found for auid %r" % (auid)

                        # failed auid: add to "failed.filename"
                        failed_users_file.write("%s\n" % auid)

                print "==============\n PROCESSED USERS: %d / %d (failed: %d, not present: %s)" % (
                    users_added, users_total, users_failed, users_not_present)
                failed_users_file.close()

            except:
                catch()
                print "ERROR: can't open file %r" % arg

        elif opt == "--find_users_with_wrong_class_talents":
            findUsersWithSpecialConditions(findUsersWithWrongTalentset, arg, 1)

        elif opt == "--clear_list_completed_dynquests":
            findUsersWithSpecialConditions(clearListCompletedDynQuests, arg, 1)

        elif opt == "--delete_tutorial_accounts":
            findUsersWithSpecialConditions(deleteTutorialAccounts, arg)

        elif opt == "--cut_extra_production_from_buildings":
            findUsersWithSpecialConditions(fixUsersWithExtraProductionInBuildings, "guiltyAuids", 1)

        elif opt == "--download_user_statistics":
            # findUsersWithSpecialConditions(CountTalentStatistics, arg, 1)
            findUsersSingleThread(DumpUserSessionStats, arg)

        elif opt == "--fix_users_md_version":
            processFixedAccounts(convertMDVersion, arg)

        elif opt == "--get_all_guild_members":
            getAllGuildMembers()

        elif opt == "--convert_guild_ratings":
            handleGuildData("convert_guild_ratings.log", recalcOldGuildRating, )

        elif opt == "--find_guild_with_abnormal_exp":
            handleGuildData("find_guild_with_abnormal_exp.log", findGuildWithAbnormalExp, count=arg )


        elif opt == "--add_cw_npc_entities":
            iDict = ClassDict()
            iDict.Config = MultiConfig()
            iDict.SD = StaticData("../xdb/ExportedSocialData.xml", iDict.Config.getMainConfig())
            handleGuildData("add_cw_npc_entities.log", addCWNPCEntities, I=iDict)

        elif opt == "--change_bad_npc_vassals":
            iDict = ClassDict()
            iDict.Config = MultiConfig()
            iDict.SD = StaticData("../xdb/ExportedSocialData.xml", iDict.Config.getMainConfig())
            handleGuildData("change_bad_npc_vassals.log", changeBadCWNPCVassals, I=iDict)

        elif opt == "--unsiege_npc":
            siegesRemoveNPCSuserain()

        elif opt == "--remove_npc_suzerains":
            iDict = ClassDict()
            iDict.Config = MultiConfig()
            handleGuildData("change_bad_npc_vassals.log", removeNPCSuzerains, moneybackAuildsList=arg)
            removeNPCSuzerainsPwStat()

        elif opt == "--return_guild_short_info":
            returnGuildShortInfo("returnGuildShortInfo.log", "data.json")

        elif opt == "--convert_guild_entities":
            handleGuildData("convert_guild_entities.log", convertGuildVassals)

        elif opt == "--remove_unknown_guild_members":
            handleGuildData("remove_unknown_guild_members.log", removeUnknownGuildMembers)

        elif opt == "--fill_guild_recruitment_params":
            sql_db = SyncSqlManager(ClassDict(EXPORT_CONFIG))
            sql_db.openConnection()
            iDict = ClassDict()
            iDict.Config = MultiConfig()
            iDict.SD = StaticData("../xdb/ExportedSocialData.xml", iDict.Config.getMainConfig())
            handleGuildData("fill_guild_recruitment_params.log", fillGuildRecruitmentParams,
                            sqlDb=sql_db, I=iDict)

        elif opt == "--index_mongo_recruitment":
            mongoPgreqEnsureIndexes()

        elif opt == "--fix_guild_hero_ratings":
            handleGuildData("fix_guild_hero_ratings.log", fixGuildHeroRatings)

        elif opt == "--check_reproduction_vs":
            count = ClassDict()
            count.me = 0
            count.gsi = 0
            handleGuildData("check_reproduction_vs.log", checkReproductionVassalsSuzerain, isCheck=True, c=count)
            print ("Bad GuildMapEntity count: %d \n" % count.me)
            print ("Bad GuildShortInfo count: %d \n" % count.gsi)

        elif opt == "--fix_reproduction_vs":
            handleGuildData("fix_reproduction_vs.log", fixReproductionVassalsSuzerain)

        elif opt == "--convert_dynamic_quests":
            handleDynamicQuests("convert_dynamic_quests.log", convertDynamicQuests)

        elif opt == "--convert_dynquests_for_party_size_strong":
            handleDynamicQuests("convert_dynquests_for_party_size_strong.log", convertDynamicQuestsForPartySizeStrong)

        elif opt == "--convert_dynquests_for_tournament":
            handleDynamicQuests("convert_dynquests_for_tournament.log", convertDynamicQuestsForTournament)

        elif opt == "--convert_dynquests_for_new_tournament_format":
            handleDynamicQuests("convert_dynquests_for_new_tournament_format.log",
                                convertDynamicQuestsForNewTournamentFormat)

        elif opt == "--remove_unused_hero_ratings":
            handleGuildData("remove_unused_hero_ratings.log", removeUnusedHeroRatings)

        elif opt == "--decrease_vassals_number":
            iDict = ClassDict()
            iDict.Config = MultiConfig()
            iDict.SD = StaticData("../xdb/ExportedSocialData.xml", iDict.Config.getMainConfig())
            removedAuids = []
            moneyback = siegesRemove()
            handleGuildData("decrease_vassals_number_remove_vassals.log", leaveNoMoreThanNVassals,
                            removedAuids=removedAuids, moneyback=moneyback)
            handleGuildData("decrease_vassals_number_remove_suzerains.log", removeSuzerainForSelectedGuilds,
                            SD=iDict.SD, removedAuids=removedAuids)

        elif opt == "--fix_guild_soulbound_talents":
            iDict = ClassDict()
            iDict.Config = MultiConfig()
            iDict.SD = StaticData("../xdb/ExportedSocialData.xml", iDict.Config.getMainConfig())
            handleGuildData("fix_guild_soulbound_talents.log", fixGuildSoulboundTalents, SD=iDict.SD)

        elif opt == "--find_users_with_small_md_version":
            findUsersWithSpecialConditionsPoolProcess("findUsersWithLesserVersion", "findUsersWithLesserVersion_",
                                                     False, 10, version=arg)

        elif opt == "--fix_users_with_small_md_version":
            findUsersWithSpecialConditionsPoolProcess("fixUsersWithLesserVersion", "fixUsersWithLesserVersion_",
                                                     True, 10)

        elif opt == "--find_users_with_bad_premium_acc":
            #findUsersWithSpecialConditions(findUsersWithBadPremiumAcc, "findUsersWithBadPremiumAcc", 10, secs=arg)  #threads
            findUsersWithSpecialConditionsPoolProcess("findUsersWithBadPremiumAcc", "findUsersWithBadPremiumAcc_", False, 10, secs=arg) #forks
            #findUsersWithSpecialConditionsSubprocess("findUsersWithBadPremiumAcc", "findUsersWithBadPremiumAcc_", False, 10, secs=arg) #subprocess
        elif opt == "--find_broken_tutorial_acc":
            findUsersWithSpecialConditionsPoolProcess("findBrokenTutorialAccounts", "findBrokenTutorialAccounts_",
                                                      False, 10, version=arg)  # forks


# --------------------------------------

if __name__ == "__main__":
    main()
