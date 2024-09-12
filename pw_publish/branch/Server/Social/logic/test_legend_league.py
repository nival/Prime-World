#!/usr/bin/env python
# -*- coding: utf-8 -*-

import httplib
import md5

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
key="333904526"
nameFilter=""
auidFilter=8
sortCriteria=0
statusFilter="0"
heroidFilter="-1549708651"
uid="3199750635521"
order="0"
position="0"
server_name="one"
server_ip="127.0.0.1"

    #"pw.nivalnetwork.com"

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


#md5_concatactionget_legend_league_listheroidFilter1key829035706nameFilterqworder1position0rid30sortCriteria1uid3199750635521305053c8fb652269cf855172ac651468

#str_for_sign="action=get_legend_league_list&auidFilter=%d&heroidFilter=%s&key=%s&nameFilter=%s&order=%s&position=%s&rid=%d&sortCriteria=%d&uid"%\
#             ( auidFilter, heroidFilter, key, nameFilter, order, position, rid, sortCriteria)

str_for_sign="action=get_legend_league_list&heroidFilter=%s&key=%s&nameFilter=%s&order=%s&position=%s&rid=%d&sortCriteria=%d&uid"%\
             ( heroidFilter, key, nameFilter, order, position, rid, sortCriteria)

sign = gen_sign(str_for_sign)
request_collect="/%s?%s=%s&sign=%s"%(server_name, str_for_sign, uid, sign)
print "request_str: ",request_collect
httpServ.request('GET', request_collect)

response = httpServ.getresponse()
print "Output from HTML request"
printText (response.read())



httpServ.close()
