#!/usr/bin/env python
# -*- coding: utf-8 -*-

import zlib, bz2
from pymongo import Connection as MongoClient
from pymongo.cursor import Cursor
import sys, traceback
import json
import zlib, bz2
import os
import time
from datetime import datetime

HOST = "127.0.0.1"
PORT = 27017

FILE_SQL_DUMP = "dump_ratings_for_pw_stat"
FILE_MD_DUMP = "dump_ratings_for_md_update"

TEST_DEBUG = False

# период для определения активных игроков 5-й лиги - тех, кто сыграл хотя бы 1 любой бой за прошлый пол года (от даты старта скрипта)
PERIOD_ACTUAL_PLAY = 15778800

if TEST_DEBUG:
    DB_LIST_NAMES = ["pw1", "pw2"]
    FIVE_LEAGUE_RATING = 1200
else:
    DB_LIST_NAMES = ["pwlobby1", "pwlobby2"]
    FIVE_LEAGUE_RATING = 2000

import operator

legend_ratings_for_start_season = {}
hero_map_for_season = {}
hero_active_map_for_season = {}
list_for_sql_dump = []

def decompress_data(data_dict):
    persistent_str = data_dict["data"]
    str_head = persistent_str[:4]
    if str_head in ["ZLIB", "BZIP"]:
        encoded_persistent = persistent_str[4:].encode('latin1')
        if persistent_str[:4] == "ZLIB":
            persistent_str = zlib.decompress( encoded_persistent )
        elif persistent_str[:4] == "BZIP":
            persistent_str = bz2.decompress( encoded_persistent )
        return json.loads(persistent_str)
    return None

def get_user_nickname(json_str):
    res_nickname = ''

    if "sn_nick" in json_str["db"]["db"].keys():
        user_nickname = json_str["db"]["db"]["sn_nick"].encode('utf-8')

    if not len(res_nickname):
        if "nick" in json_str["db"]["db"].keys():
            user_nickname = json_str["db"]["db"]["nick"].encode('utf-8')
        else:
            user_nickname = ''

    return user_nickname

def get_pers_data(mycollection, active_timestamp):
    try:
        for x in mycollection.find():
            if 'data' in x.keys():
                json_str = decompress_data(x)
                if json_str and "auid" in json_str["db"]["db"].keys() and json_str["db"]["db"]["auid"] is not None:
                    user_auid = int(json_str["db"]["db"]["auid"])
                    is_banned = bool(json_str["db"]["db"]["banned"])
                    print "Process user with auid %s, is_banned = %s..."%(str(user_auid), str(is_banned))
                    if not is_banned:
                        user_nickname = get_user_nickname(json_str)
                        heroes_keeper = json_str["db"]["model"]["ModelData"]["HeroesKeeper"]["Keeper"]
                        for one_hero_info_key in heroes_keeper.keys():
                            hero_info = heroes_keeper[one_hero_info_key]['Hero']

                            if TEST_DEBUG:
                                need_add_hero = "PersistentId" in hero_info.keys()
                            else:
                                need_add_hero = "PersistentId" in hero_info.keys() and hero_info["lastPlayed"] > 0 and hero_info["Rating"] >= FIVE_LEAGUE_RATING

                            if need_add_hero:
                                hero_p_id = hero_info["PersistentId"]
                                hero_rating = hero_info["Rating"]
                                #тут при первом прогоне создавались записи в "лидербордах" нулевого "сезона"
                                list_for_sql_dump.append("call `pw_stat`.`update_league_info`( %s, %d, %f, '%s' );\n"%(user_auid, hero_p_id, hero_rating, user_nickname))
                                if hero_p_id not in hero_map_for_season.keys():
                                    hero_map_for_season[hero_p_id] = { user_auid: hero_rating }
                                else:
                                    hero_map_for_season[hero_p_id][user_auid] = hero_rating

                                if hero_info["lastPlayed"] >= active_timestamp:
                                    if hero_p_id not in hero_active_map_for_season.keys():
                                        hero_active_map_for_season[hero_p_id] = { user_auid: hero_rating }
                                    else:
                                        hero_active_map_for_season[hero_p_id][user_auid] = hero_rating
    except Exception, e:
        file_err = open( "err","w+")
        file_err.write("Wrong %s for data: %s"%(str(e), str(json_str)))
        file_err.close()

def fill_legend_ratings_info(one_hero_info, last_range):
    hero_id = one_hero_info[0]
    list_hero_ranks = one_hero_info[1]
    for index_hero_rating_pair in range(0, last_range):
        auid_pair_info = list_hero_ranks[index_hero_rating_pair][0]
        res_rating = index_hero_rating_pair + 1
        if not auid_pair_info in legend_ratings_for_start_season.keys():
            legend_ratings_for_start_season[auid_pair_info] = {hero_id: res_rating}
        else:
            legend_ratings_for_start_season[auid_pair_info][hero_id] = res_rating

try:
    этот скрипт использовался при переходе на фичу Сезоны, больше он не нужен
    в дальнейшем данные о топ10 по героям будут экспортироваться из таблицы pw_stat.tbl_seasons_league
    и помещаться в монгу в коллекцию pw1.seasons_top10_by_hero, откуда уже скрипты начисления наград и будут брать данные

    start_timestamp = time.time()
    active_timestamp = start_timestamp - PERIOD_ACTUAL_PLAY
    print "Start time: %s"%str(datetime.now())

    os.path.exists("err") and os.remove("err")
    os.path.exists(FILE_SQL_DUMP) and os.remove(FILE_SQL_DUMP)
    os.path.exists(FILE_MD_DUMP) and os.remove(FILE_MD_DUMP)
    os.path.exists("empty_nickname*") and os.remove("empty_nickname*")

    for pw_name in DB_LIST_NAMES:
        client = MongoClient("mongodb://%s:%d"%(HOST, PORT))
        db_client_pw1 = client[pw_name]
        mycollection_pw1 = db_client_pw1["pers"]
        print "Get user data from database %s"%pw_name
        get_pers_data(mycollection_pw1, active_timestamp)

    #{8: {}, 9: {}, 10: {}} - auids map
    #print str(legend_ratings_for_start_season)
    for one_hero_info in hero_map_for_season:
        hero_map_for_season[one_hero_info] = sorted(hero_map_for_season[one_hero_info].items(), key=operator.itemgetter(1), reverse=True)

    for one_hero_info in hero_active_map_for_season:
        hero_active_map_for_season[one_hero_info] = sorted(hero_active_map_for_season[one_hero_info].items(), key=operator.itemgetter(1), reverse=True)

    if TEST_DEBUG:
        print hero_map_for_season

    #for auid_key in legend_ratings_for_start_season:
    for one_hero_info in hero_map_for_season.items():
        if TEST_DEBUG:
            print "one_hero_info: " + str(one_hero_info)
        #-1279629653: [(9, 1290.0)], 701063780: [(10, 1290.0)], 1255640165: [(10, 1290.0)]
        last_range = len(one_hero_info[1])
        fill_legend_ratings_info(one_hero_info, last_range)

    for one_hero_info in hero_active_map_for_season.items():
        if TEST_DEBUG:
            print "one_active_hero_info: " + str(one_hero_info)
        last_range = len(one_hero_info[1])
        if last_range > 11:
            last_range = 11
        fill_legend_ratings_info(one_hero_info, last_range)

    if TEST_DEBUG:
        print legend_ratings_for_start_season

    file_sql_dump = open( FILE_SQL_DUMP,"w")
    for i in reversed(list_for_sql_dump):
        file_sql_dump.write(i)
    file_sql_dump.close()

    file_for_md_dump = open( FILE_MD_DUMP,"w")
    file_for_md_dump.write(str(legend_ratings_for_start_season))
    file_for_md_dump.close()

    delta_seconds = time.time() - start_timestamp
    m, s = divmod(delta_seconds, 60)
    h, m = divmod(m, 60)
    print "End time: %s, work time = %d:%02d:%02d"%(str(datetime.now()), h, m, s)

except Exception, e:
    print "Something wrong: %s"%str(e)
