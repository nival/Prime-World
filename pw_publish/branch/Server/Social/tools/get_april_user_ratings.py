#!/usr/bin/env python
# -*- coding: utf-8 -*-

import ujson as json
import struct
import zlib, bz2
import os
import time
from datetime import datetime
from pymongo import Connection as MongoClient

HOST = "127.0.0.1"
PORT = 27017

FILE_MD_DUMP = "dump_april_ratings"

TEST_DEBUG = False

if TEST_DEBUG:
    DB_LIST_NAMES = ["pw1", "pw2"]
else:
    DB_LIST_NAMES = ["pwlobby1", "pwlobby2"]

april_user_ratings = {}



def decompress_data(data_dict):
    persistent_str = data_dict["data"]
    str_head = persistent_str[:4]
    if str_head in ["ZLIB", "BZIP"]:
        encoded_persistent = persistent_str[4:].encode('latin1')
        if str_head == "ZLIB":
            persistent_str = zlib.decompress(encoded_persistent)
        elif str_head == "BZIP":
            persistent_str = bz2.decompress(encoded_persistent)
        del encoded_persistent
        return json.loads(persistent_str)
    return None

def get_pers_data(db, start_pos, output_file_err, info_file):
    current_pos = start_pos
    last_pos = 0
    str_auid = ''
    pers_col = db["pers"]
    users_old_ratings_col = db["old_ratings"]
    users_old_ratings_col.create_index('auid')

    users_count = pers_col.count()
    s_users_count = str(users_count)
    for x in pers_col.find().skip(start_pos):#.limit(10000):
        try:
            current_pos += 1

            if 'data' in x.keys():
                json_str = decompress_data(x)
                if json_str and "auid" in json_str["db"]["db"].keys() and json_str["db"]["db"]["auid"] is not None:
                    is_banned = bool(json_str["db"]["db"]["banned"])
                    str_auid = json_str["db"]["db"]["auid"]
                    #last_login_time = json_str["db"]["model"]["ModelData"]["LordInfo"]["LordInfo"]["LastLoginTime"]

                    if not is_banned:
                        heroes_keeper = json_str["db"]["model"]["ModelData"]["HeroesKeeper"]["Keeper"]
                        best_rating = 0
                        user_old_ratings = {}
                        ratings = {}
                        for one_hero_info_key in heroes_keeper.keys():
                            hero_info = heroes_keeper[one_hero_info_key]['Hero']

                            if TEST_DEBUG:
                                is_valid_hero = "PersistentId" in hero_info.keys()
                            else:
                                is_valid_hero = "PersistentId" in hero_info.keys() and hero_info["lastPlayed"] > 0

                            if is_valid_hero:
                                hero_p_id = hero_info["PersistentId"]
                                hero_rating = hero_info["Rating"]
                                ratings[str(hero_p_id)] = int(hero_rating)
                                if hero_rating > best_rating:
                                    best_rating = hero_rating

                        if best_rating > 0:
                            if current_pos > last_pos + 1000:
                                last_pos = current_pos
                                print "%3.2f%% Process user [%d/%s] with auid %s" % (
                                    float(current_pos) / users_count * 100.0, current_pos, s_users_count, str_auid)

                            info_file.seek(0)
                            info_file.write(struct.pack('i', current_pos))

                            user_old_ratings['best_rating'] = int(best_rating)
                            user_old_ratings['ratings'] = ratings

                            rec = {
                                'auid': str_auid,
                                'rating_data': user_old_ratings
                            }

                            users_old_ratings_col.insert(rec)

                del json_str
        except Exception, e:
            print "Wrong %s for data" % (str(e))
            output_file_err.write("Wrong %s for data: %s\n" % (str(e), str_auid))

    return current_pos

try:
    if os.path.exists("err"):
        os.remove("err")
    if os.path.exists(FILE_MD_DUMP):
        os.remove(FILE_MD_DUMP)

    file_err = open("err", "w+")


    start_timestamp = time.time()
    print "Start time: %s"%str(datetime.now())

    client = MongoClient("mongodb://%s:%d" % (HOST, PORT))

    for pw_name in DB_LIST_NAMES:
        start_from = 0
        info_file_name = pw_name + ".info"
        if not os.path.exists(info_file_name):
            file_info = open(info_file_name, "wb")
        else:
            file_info = open(info_file_name, "rb+")
            pos = struct.unpack('i', file_info.read(8))[0]
            if pos:
                start_from = pos

        db_client = client[pw_name]

        print "Get user data from database %s"%pw_name
        get_pers_data(db_client, start_from, file_err, file_info)
        file_info.close()

    file_err.close()


    if TEST_DEBUG:
        print april_user_ratings

    file_for_md_dump = open(FILE_MD_DUMP, "w")
    file_for_md_dump.write(str(april_user_ratings))
    file_for_md_dump.close()

    if TEST_DEBUG:
        file_for_md_dump = open(FILE_MD_DUMP,"r")
        legend_ratings_for_start_season = eval(file_for_md_dump.read())
        for one_user_key in  legend_ratings_for_start_season.keys():
            print "one_user_info[" + str(one_user_key) + "]: " + str(legend_ratings_for_start_season[one_user_key])
            print legend_ratings_for_start_season[one_user_key].keys()

    delta_seconds = time.time() - start_timestamp
    m, s = divmod(delta_seconds, 60)
    h, m = divmod(m, 60)
    print "End time: %s, work time = %d:%02d:%02d"%(str(datetime.now()), h, m, s)

except Exception, e:
    print "Something wrong: %s"%str(e)
