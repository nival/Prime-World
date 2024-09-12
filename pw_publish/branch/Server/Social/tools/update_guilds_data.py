#!/usr/bin/env python
# -*- coding: utf-8 -*-

from pymongo import MongoClient
import json

def update_guild_data(mycollection, guild_auid, need_rating, array_ratings):
    key_str = "gs_%s"%guild_auid
    for x in mycollection.find({"key" : key_str}):
        if 'data' in x.keys():
            print "X_data:::: %s, type = %s"%(x['data'], type(x['data']))
            if type(x['data']) is unicode:
                res_json = json.loads(x['data'], 'utf-8')
                res_json["GuildData"]["RatingInfo"]["RatingInfo"]["Ratings"]["SimpleList"] = array_ratings
                res_json["GuildData"]["RatingInfo"]["RatingInfo"]["Rating"] = need_rating
                out_json = json.dumps(res_json)
                print "out_json: %s"%out_json.encode('utf-8')
                mycollection.update({"key" : key_str}, { "key" : key_str, "data": out_json.encode('utf-8')})
        else:
            print "X:::: %s"%x

try:
    client = MongoClient("mongodb://localhost:27017")
    db_client_pw1 = client["pw1"]
    db_client_pw2 = client["pw2"]
    mycollection_pw1 = db_client_pw1["guilds"]
    mycollection_pw2 = db_client_pw2["guilds"]

    for line in open('losers_guild_info'):
        print line
        guild_dict = eval(line)
        if guild_dict:
            print guild_dict["Rating"]
            update_guild_data(mycollection_pw1, guild_dict["Guild_uid"], guild_dict["Rating"], guild_dict["RatingsInfo"])
            update_guild_data(mycollection_pw2, guild_dict["Guild_uid"], guild_dict["Rating"], guild_dict["RatingsInfo"])
except Exception, e:
    print "Something wrong: %s"%str(e)
