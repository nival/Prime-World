#!/usr/bin/env python
# -*- coding: utf-8 -*-

SERVICEDB_HOST='b512.nivalnetwork.com'
SERVICEDB_PORT=5438
MANAGEMENTDB_NAME='pw_management'
DB_USER='etl'
DB_PASSWD='Iethaij9'

import psycopg2
import datetime

tuple_loser_guilds = (6309306957829,81441169866755,17158394347521,88622355185676,12747462934530,31065498451970,97019016249347,19743964659714,
                     26495653249029,3466038607996,96228742266886,59347858096132,8323646619663,61190399066117,42382737276933,3466038608057,
                     107670535143428,15264313769989,28488518074374,3466038607943,4032974290956,31323196489729,88880053223429,37168646979585,
                     90413356548098,53846004989955,89945205112839,96349001351174,16604343566338,95541547499522,4329327034376,12640088752131,
                     100888781783044,105467216920577,79697413144578,4286377361409,48979807043590,4093103833090,99853694664710,7468948127746,
                     88003879895042,9315784065025,8418135900164,3483218477172,65575560675330,36983963385858,10123237916684,11433202941955,
                     75093208203265,10149007720464,33711198306305,53218939764739,3508988280854,89266600280072,41270340747267,29051158790147,10273561772045,)

str_loser_guilds = "(6309306957829,81441169866755,17158394347521,88622355185676,12747462934530,31065498451970,97019016249347,19743964659714,"\
                     "26495653249029,3466038607996,96228742266886,59347858096132,8323646619663,61190399066117,42382737276933,3466038608057,"\
                     "107670535143428,15264313769989,28488518074374,3466038607943,4032974290956,31323196489729,88880053223429,37168646979585,"\
                     "90413356548098,53846004989955,89945205112839,96349001351174,16604343566338,95541547499522,4329327034376,12640088752131,"\
                     "100888781783044,105467216920577,79697413144578,4286377361409,48979807043590,4093103833090,99853694664710,7468948127746,"\
                     "88003879895042,9315784065025,8418135900164,3483218477172,65575560675330,36983963385858,10123237916684,11433202941955,"\
                     "75093208203265,10149007720464,33711198306305,53218939764739,3508988280854,89266600280072,41270340747267,29051158790147,10273561772045)"

def recalc_rating(arr_ratings):
    result = reduce(lambda a,b: a+b, arr_ratings)
    return round(result / 7.0)

def import_data_from_db(file_results, loser_guilds):
    try:
        conn_string = "dbname='%s' user='%s' host='%s' port=%d password='%s'"%(MANAGEMENTDB_NAME, DB_USER, SERVICEDB_HOST, SERVICEDB_PORT, DB_PASSWD)
        print "Connecting to database\n	-> %s" % (conn_string)
        conn = psycopg2.connect(conn_string)
        cursor = conn.cursor()
        str_request = "select guild, sum(guildpointschange) as sum_guildpoints, (timestamp + interval '180 minute')::date as date "\
                           "from guildpointslog "\
                           "where timestamp + interval '180 minute' >= now()::date - interval '7 day' "\
                           "and timestamp + interval '180 minute' < now()::date "\
                           "and guild in %s and type = 'Session' group by (timestamp + interval '180 minute')::date, guild "\
                           "order by guild, (timestamp + interval '180 minute')::date DESC"%loser_guilds
        print "Run query to database\n	-> %s" % (str_request)
        cursor.execute(str_request)
        array_res = cursor.fetchall()
        cursor.close()

        cur_guild = None
        cur_guild_info = {}

        for one_res in array_res:
            print "One data str\n	-> %s" % str(one_res)
            if cur_guild != one_res[0]:
                if cur_guild is not None:
                    cur_guild_info["Rating"] = recalc_rating(cur_guild_info["RatingsInfo"])
                    file_results.write(str(cur_guild_info) + "\n")
                cur_guild = one_res[0]
                cur_guild_info = { "Guild_uid": str(cur_guild), "RatingsInfo": [int(one_res[1])] }
            else:
                cur_guild_info["RatingsInfo"].append(int(one_res[1]))

        cur_guild_info["Rating"] = recalc_rating(cur_guild_info["RatingsInfo"])
        file_results.write(str(cur_guild_info) + "\n")

    except Exception, e:
        print "Something wrong: %s"%str(e)

try:
    file_results = open('losers_guild_info', 'w')
    file_inserts_for_mirror = open('inserts_for_mirror', 'w')
    import_data_from_db(file_results, str_loser_guilds)
    for one_guild in tuple_loser_guilds:
        file_inserts_for_mirror.write("INSERT INTO tbl_queue (`data_type`,`data_id`,`timestamp`) VALUES (2,%s,UNIX_TIMESTAMP()) ON DUPLICATE KEY UPDATE `timestamp`=UNIX_TIMESTAMP();"%str(one_guild) + "\n")
    file_results.close()
    file_inserts_for_mirror.close()
except Exception, e:
    print "Something wrong: %s"%str(e)
