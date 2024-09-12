#!/usr/bin/env python
# -*- coding: utf-8 -*-

import httplib
import md5

# как использовать:
# 1. magic_srv_key - сценарий из PF-103790 с использованием cheat_engine
# 2. p_id_hero - PersistentId героя, можно узнать через gmtool
# 3. key - ключ подключения, ищется по логам сервера, либо перехватывается wireshark'ом или чем-то подобным при обычной покупке героя. На транке - просто ищется в логах замка
# 4. uid - uid пользователя, под которым заходим в игру
# 5. server_name - имя ws, к которой привязан юзверь. Тоже ищется по логам замка

# В случае транка практически все параметры находятся в логе. Например, ищем запрос keepalive:
# Queue: http://127.0.0.1:88/one?action=keepalive&counter=79&is_active_window=False&is_device_lost=False&key=477773482&onlyFriends=False&rid=81&uid=850403524609&sign=253721c79a8e93d878414694130a2e05
# из него получаем: one - server_name, 477773482 - key, 850403524609 - uid

magic_srv_key="85040352460997908fd81023a03fb09e24772c840a72"
key="460140481"
rid=310
uid="850403524609"
p_id_hero="-1850465256"
server_name="two"

# для транка
#server_ip="pw.nivalnetwork.com"

# для локального экземпляра SS
server_ip="127.0.0.1"

def printText(txt):
    lines = txt.split('\n')
    for line in lines:
        print line.strip()

def gen_sign(p_id_hero, key, rid, magic_srv_key):
    str_template_md5="PersistentId%sactionhire_herokey%srid%duid%s"%(p_id_hero, key, rid, magic_srv_key)
    m = md5.new()
    m.update(str_template_md5)
    return m.hexdigest()


httpServ = httplib.HTTPConnection(server_ip, 88)
httpServ.connect()

for x in range(0, 1):
    rid += 20
    sign = gen_sign(p_id_hero, key, rid, magic_srv_key)
    #like http://pw.zzima.com:88/one?PersistentId=-1279629653&action=hire_hero&key=607239491&rid=151&uid=102632538505217&sign=8cafe3efbeb52a2967ab00ba1d383061
    request_collect="/%s?PersistentId=%s&action=hire_hero&key=%s&rid=%d&uid=%s&sign=%s"%(server_name, p_id_hero, key, rid, uid, sign)
    print "request_hire: ",request_collect
    httpServ.request('GET', request_collect)

    response = httpServ.getresponse()
    print "Output from HTML request"
    printText (response.read())

httpServ.close()