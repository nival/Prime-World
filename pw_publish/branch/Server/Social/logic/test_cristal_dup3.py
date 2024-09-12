#!/usr/bin/env python
# -*- coding: utf-8 -*-

import httplib
import md5
import time

# образец запрос для trunk'a:
#http://pw.nivalnetwork.com:88/two?action=get_guilds_list&key=262756517&nameFilter=test3&order=1&position=0&ratingFilter=-1&rid=19&sortCriteria=3&statusFilter=-1&suzerenRatingFilter=-1&uid=25370371817473&sign=966d103647f330130011b08eaeb0ec41

# как использовать:
# 1. magic_srv_key - сценарий из PF-103790 с использованием cheat_engine  7. Открыть процесс castle.exe, и найти строку actionkeep
# 2. key - ключ подключения, ищется по логам сервера, либо перехватывается wireshark'ом или чем-то подобным при нормлаьном сборе ресурсов,
# 3. nameFilter - фильтр для поиска по имени клана
# 4. ratingFilter - фильтр для поиска по рейтингу, -1 - без фильтрации
# 5. sortCriteria - критерий сортировки
# 6. suzerenRatingFilter -  фильтр для поиска по рейтингу вассала. -1 - без фильтрации
# 7. statusFilter -  фильтр для поиска по рейтингу вассала. -1 - без фильтрации
# 8. statusFilter -  фильтр для поиска по рейтингу вассала. -1 - без фильтрации
# 9. uid - uid пользователя
# 10. order - сортировка по возрастанию/убыванию
# 11. position - "постраничность" запроса, результаты от position до position+GUILDS_IN_LIST_PER_REQUEST

rid=30
magic_srv_key="1357a94564203a8bb9f135fa2800e4f76be"
key="732735043"
construction_id=1145
isShowed="True"
seasonId=68131154
uid="3199750635521"
server_name="two"
server_ip="127.0.0.1"
    #"pw.nivalnetwork.com"

count_tests = 30

#(1) 10:11:04.622 NetLog (i): Queue: http://pw.nivalnetwork.com:88/one?action=item_move_inv2ts&dest_item_id=0&dest_slot_id=36&key=446405553&rid=29&src_hero_id=41&src_item_id=222&talent_set_id=0&uid=25366076850177&useLamp=False&sign=470febbde095e1ad123073ee0b32cf3e
def printText(txt):
    lines = txt.split('\n')
    for line in lines:
        print line.strip()

def gen_sign(str_for_sign):
    str_template_md5=str_for_sign.replace("=", '')
    str_template_md5=str_template_md5.replace("&", '')
    str_template_md5+=magic_srv_key
    print "md5_concat: ",str_template_md5
    m = md5.new()
    m.update(str_template_md5)
    return m.hexdigest()


httpServ = httplib.HTTPConnection(server_ip, 88)
httpServ.connect()


#md5_concat=actionset_season_results_showedisShowedTruekey773115486rid30seasonId68131154uid4372276707329c21339e7a42e9c0386d3cb3224953ae6

for x in range(0,count_tests):
    client_time = str(time.time())
    str_move_to_pocket="action=move_to_pocket&client_time=%s&building_id=%d&key=%s&rid=%d&uid"%(client_time, construction_id, key, rid)
    sign = gen_sign(str_move_to_pocket)
    request_move="/%s?%s=%s&sign=%s"%(server_name, str_move_to_pocket, uid, sign)
    print "request_move_str: ",request_move
    httpServ.request('GET', request_move)
    response = httpServ.getresponse()
    print "Output from HTML request"
    printText (response.read())

    client_time = str(int(time.time()))
    str_collect_production="action=collect_production_results&client_time=%s&construction_id=%d&key=%s&rid=%d&uid"%(client_time, construction_id, key, rid)
    sign = gen_sign(str_collect_production)
    request_collect="/%s?%s=%s&sign=%s"%(server_name, str_collect_production, uid, sign)
    print "request_collect_str: ",request_collect
    httpServ.request('GET', request_collect)

    response = httpServ.getresponse()
    print "Output from HTML request"
    printText (response.read())

httpServ.close()
