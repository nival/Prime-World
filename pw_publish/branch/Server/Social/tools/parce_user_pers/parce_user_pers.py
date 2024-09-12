#!/usr/bin/env python
# -*- coding: utf8 -*-

import sys
sys.path.append('../../')
sys.path.append('../../cfg')
import cfg
import time
import zlib
import json
import ujson
import re
import pymongo
import csv

"""
Сделать выгрузку по пользователям
https://jira.nivalnetwork.com/browse/IT-18168
https://jira.nivalnetwork.com/browse/IT-18168
как работает скрипт
    читает конфиги SS
    конектится поочередно к монговым базам SS
    ищет в колекциях pers (профилях пользователей) данные о скине
    отображает auid пользователей у которых этот скин есть
    для теста в скрипт мона добавить точно известных пользователей со скином
    #lcache.append('data_377957122049')
    убедится, что auid пользователя возвращается со всеми остальными
    запуск
       python parce_user_pers.py
    вывод
      3468833
    или пусто
"""

def json_loads(data_string):
    if isinstance( data_string, unicode ):
        data_string = data_string.encode("utf8")
    return ujson.decode( data_string )

dcache={}
lcache=[]
with open('./tmpdata/IT-18168_sa_lastlogin_gte_2014-09-25_04-30_utc.csv', 'rb') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=';', quotechar='|')
    for row in spamreader:
       if dcache.get(row[2]) is None:
           dcache[row[2]]=True
           if row[2]=="fb.snuid":
               continue
           lcache.append("data_"+re.sub('\"','',row[2]))

# lcache.append('data_377957122049')

one=pymongo.connection.Connection(host=cfg.CLUSTER_MONGO_CONFIG[0]['mongo_addr'],
                                  port=cfg.CLUSTER_MONGO_CONFIG[0]['mongo_port'])
two=pymongo.connection.Connection(host=cfg.CLUSTER_MONGO_CONFIG[1]['mongo_addr'],
                                  port=cfg.CLUSTER_MONGO_CONFIG[1]['mongo_port'])
list=(one[cfg.CLUSTER_MONGO_CONFIG[0]['mongo_base']],
      two[cfg.CLUSTER_MONGO_CONFIG[1]['mongo_base']], )

for con in list:
    for i in con.pers.find({"key" : {"$in": lcache}}, {"data":1} ):
        persistent_dict = {}
        if i['data']:
            # строка может быть зазипована
            str_head = i['data'][:4]
            if str_head in ["ZLIB", "BZIP"]:
                t0 = time.clock()
                encoded_persistent = i['data'][4:].encode('latin1')
                if i['data'][:4] == "ZLIB":
                    i['data'] = zlib.decompress( encoded_persistent )
                elif i['data'][:4] == "BZIP":
                    i['data'] = bz2.decompress( encoded_persistent )
                del encoded_persistent  # сразу освободить строчный буфер
                t1 = time.clock()

        persistent_dict = json_loads( i['data'] )

        j=json.dumps(persistent_dict)
        # скин witch_s1_a или witch_s1_b
        if re.findall("-1864815166",j):
            print  persistent_dict['db']['db']['load_auid']
