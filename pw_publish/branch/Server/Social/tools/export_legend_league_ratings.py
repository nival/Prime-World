#!/usr/bin/env python
# -*- coding: cp1251 -*-

import sys
import argparse
import time
from itertools import chain
from datetime import datetime
from pymongo import Connection as MongoClient
import MySQLdb
from binascii import crc32

MONGO_HOST = "127.0.0.1"
MONGO_PORT = 27017

TEST_DEBUG = True

if TEST_DEBUG:
    DEST_MONGO_DB = "pw1"
    sql_host = "localhost"
    sql_db = "pw_stat"
    sql_user = "root"
    sql_pass = "1"
else:
    DEST_MONGO_DB = "pwlobby1"
    sql_host = "192.168.78.24"
    sql_db = "pw_stat"
    sql_user = "pws"
    sql_pass = "PassUnknown"

TEST_DEBUG = False

def main(argv):

    parser = argparse.ArgumentParser(add_help=True)
    parser.add_argument('-s', '--season', type=str, required=True, help='persistentId of exported season')
    #parser.add_argument('outfile', nargs='?', help='output file name')

    args = parser.parse_args()
    season_id_s = args.season
    season_id = crc32(season_id_s)
    print 'Exported season id is {0} [{1}]'.format(season_id_s, season_id)

    try:
        start_timestamp = time.time()
        print "Start time: %s" % str(datetime.now())

        sql_table = 'tbl_seasons_league'
        sql_client = MySQLdb.connect(sql_host, sql_user, sql_pass, sql_db)

        print "Get user data from database %s.%s" % (sql_db, sql_table)
        sql_cur = sql_client.cursor()

        mongo_db_client = MongoClient("mongodb://%s:%d" % (MONGO_HOST, MONGO_PORT))
        mongo_db = mongo_db_client[DEST_MONGO_DB]

        export_top100_to_mongo(season_id, sql_cur, mongo_db)

        export_top10_by_heroes(season_id, sql_cur, mongo_db)

        delta_seconds = time.time() - start_timestamp
        m, s = divmod(delta_seconds, 60)
        h, m = divmod(m, 60)
        print "End time: %s, work time = %d:%02d:%02d" % (str(datetime.now()), h, m, s)

    except Exception, e:
        print "Something went wrong: %s" % str(e)


def export_top10_by_heroes(season_idx, sql_cur, mongo_db):
    # далее получаем список героев, встречающихся в рейтингах топов
    hero_list_query = """
            SELECT hero_id FROM tbl_seasons_league where season = {0} group by hero_id;
            """.format(season_idx)
    sql_cur.execute(hero_list_query)
    rows = sql_cur.fetchall()
    hero_ids = list(chain(*rows))

    mongo_dest_collection_name = 'seasons_top10_by_hero'
    print "Save top10 of season {0} for each hero to database {1}.{2}".format(season_idx, DEST_MONGO_DB,
                                                                              mongo_dest_collection_name)

    mongo_dest_collection = mongo_db[mongo_dest_collection_name]

    for hero_id in hero_ids:
        hero_top_query = """
                        SELECT league_place as place, rating, uid as auid from
                           ( SELECT  l.uid,
                            l.nickname,
                            l.rating,
                            l.hero_id,
                            @curRow := @curRow + 1 AS league_place
                            FROM    tbl_seasons_league l
                            JOIN    (SELECT @curRow := 0) r
                            WHERE hero_id = {0} AND season = {1}
                            ORDER BY rating DESC ) as x
                            LIMIT 0,10""".format(hero_id, season_idx)

        sql_cur.execute(hero_top_query)
        rows = list(chain(sql_cur.fetchall()))

        if TEST_DEBUG:
            print 'Season top10 for hero contains {0}'.format(len(rows))
            print rows

        backup = []

        if len(mongo_dest_collection.index_information()) == 0:
            print 'Creating indexes for table %s' % mongo_dest_collection_name
            mongo_dest_collection.create_index('hero_id')
            mongo_dest_collection.create_index('season')
        else:
            print 'Backup and delete prev records for season {0} and hero {1}'.format(season_idx, hero_id)
            cursor = mongo_dest_collection.find({'season': season_idx, 'hero_id': hero_id})
            count = cursor.count()
            print 'Saved {0} records'.format(count)
            for doc in cursor:
                backup.append(doc['top10'])
            mongo_dest_collection.remove({'season': season_idx, 'hero_id': hero_id})

        try:
            top10_doc = {}
            for leaderboard_entry in rows:
                top10_doc[str(leaderboard_entry[2])] = {
                    'place': int(leaderboard_entry[0]),
                    'rating': leaderboard_entry[1]
                }

            dest_doc = {'hero_id': hero_id, 'season': season_idx, 'top10': top10_doc}
            mongo_dest_collection.insert(dest_doc)

            print 'Inserted record for hero {0}'.format(hero_id)
        except Exception, e:
            print "Have occurred error while import hero's[{0}] leaderboard to mongo.\nReason: {1}".format(hero_id, str(e))
            print 'Trying to restore backup'
            for top10_doc in backup:
                dest_doc = {'hero_id': hero_id, 'season': season_idx, 'top10': top10_doc}
                mongo_dest_collection.insert(dest_doc)
            print 'Restored {0} records'.format(len(backup))


def export_top100_to_mongo(season_idx, sql_cur, mongo_db):
    top10_query = """SELECT league_place, rating, hero_id, uid as auid  from 
                ( SELECT  l.uid, 
                l.rating, 
                l.hero_id, 
                @curRow := @curRow + 1 AS league_place 
                FROM    tbl_seasons_league l 
                JOIN    (SELECT @curRow := 0) r  
                WHERE season = {0}
                ORDER BY rating DESC ) as x 
                LIMIT 0,100""".format(season_idx)
    sql_cur.execute(top10_query)
    rows = sql_cur.fetchall()
    if len(rows) == 0:
        print 'Wrong season leaderbord (contains only {0} records)'.format(len(rows))
        exit(2)

    if TEST_DEBUG:
        for row in rows:
            print '%s\n' % str(row)

    mongo_dest_collection_name = 'seasons_top100'
    print "Save top10 of season {0} to database {1}.{2}".format(season_idx, DEST_MONGO_DB, mongo_dest_collection_name)
    backup = []
    mongo_dest_collection = mongo_db[mongo_dest_collection_name]
    if len(mongo_dest_collection.index_information()) == 0:
        print 'Creating indexes for table %s' % mongo_dest_collection_name
        mongo_dest_collection.create_index('auid')
        mongo_dest_collection.create_index('season')
    else:
        print 'Backup and delete prev records for season {0}'.format(season_idx)
        cursor = mongo_dest_collection.find({'season': season_idx})
        count = cursor.count()
        print 'Saved {0} records'.format(count)
        for doc in cursor:
            backup.append((doc['place'], doc['rating'], doc['hero_id'], doc['auid']))

        mongo_dest_collection.remove({'season': season_idx})
    try:
        for leaderboard_entry in rows:
            auid = leaderboard_entry[3]
            place = int(leaderboard_entry[0])
            rating = leaderboard_entry[1]
            hero_id = leaderboard_entry[2]

            dest_doc = {'auid': auid, 'season': season_idx, 'place': place, 'rating': rating, 'hero_id': hero_id}

            mongo_dest_collection.insert(dest_doc)

        print 'Inserted {0} records'.format(len(rows))
    except Exception, e:
        print 'Have occurred error while import leaderboard to mongo.\nReason: {1}'.format(str(e))
        print 'Trying to restore backup'
        for leaderboard_entry in backup:
            auid = leaderboard_entry[3]
            place = int(leaderboard_entry[0])
            rating = leaderboard_entry[1]
            hero_id = leaderboard_entry[2]

            dest_doc = {'auid': auid, 'season': season_idx, 'place': place, 'rating': rating, 'hero_id': hero_id}

            mongo_dest_collection.insert(dest_doc)
        print 'Restored {0} records'.format(len(backup))

if __name__ == "__main__":
    main(sys.argv[1:])
