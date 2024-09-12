#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
import json
import base.helpers as helpers
from binascii import crc32
import simple_requests
from gevent import time

requests = simple_requests.Requests()

upgrade = False
#upgrade = True
ent_id = "1216"
tal_id = "964"

addlootbox = False
#addlootbox = True
lootbox_id = "LB_TalUpg_Abrasive10"

base_url = "http://127.0.0.1:88/"
email = "ws_test1@1.3"
password = "1234"

client_version = "0.12.1513.47345.11.17"

# base_url = "http://qa.pwcastle.nivalnetwork.com:88/"
# email = "ru1_1@nival.com"
# password = "qqqwwweee"
# ent_id = "15572"
# tal_id = "8192"  # ItemsKeeper\/8192
# client_version = "0.12.1513.47345.11.17"


def prepare_request(server, params, rid, secret):
    p = dict(params)
    p["rid"] = rid
    return base_url + server + "?" + helpers.makeSignedRequest(params, secret)


def send_request(end_point, params, secret=""):
    r = base_url + end_point + "?" + helpers.makeSignedRequest(params, secret)
    print r
    response = requests.one(r)

    res = json.loads(response.content)['response']
    print helpers.pretty(res)
    return res


def login(email, password):
    r = send_request("login0", dict(
        action="l_who",
        # hostid="0e59d0a6fab83e150fdcb6353dfe3626",
        locale="ru",
        primary=1,
        snid="pwe",
        snuid=helpers.md5(email),
    ), helpers.md5(password))

    auid = r['auid']
    token = r['token']

    time.sleep(1)

    # 127.0.0.1:88/login0?action=qlogin&key=720593927&rid=0&sntoken=***&snuid=***&uid=-1&ver=0.12.961.44365&sign=466ecb7ad902f0d63079ff0400220bb6
    r = send_request(r['server'], dict(
        action="qlogin",
        key=720593927,
        rid=0,
        sntoken=token,
        snuid=auid,
        uid=-1,
        ver=client_version
    ))

    time.sleep(1)

    # login0?action=qpoll&key=720593927&rid=1&sntoken=***&snuid=***&uid=0&ver=0.12.961.44365
    r = send_request(r['server'], dict(
        action="qpoll",
        key=720593927,
        rid=1,
        sntoken=token,
        snuid=auid,
        uid=0,
        ver=client_version
    ))
    token = r['token']
    secret = helpers.md5(token)

    time.sleep(1)
    # /one?action=sn_login&key=720593927&rid=2&snid=pw&sntoken=***&snuid=***&testkey=1&uid=0&userlocale=RU&ver=0.12.961.44365&
    r = send_request(r['gserver'], dict(
        action="sn_login",
        key=720593927,
        rid=2,
        snid="pw",
        sntoken=token,
        snuid=auid,
        testkey=1,
        userlocale="RU",
        uid=0,
        ver=client_version
    ), secret)

    key = r['key']
    uid = r['uid']
    server = r['server']

    time.sleep(1)
    # one?action=auth&key=535390086&rid=3&uid=1052266987521&userlocale=RU&
    r = send_request(server, dict(
        action="auth",
        key=key,
        rid=3,
        userlocale="RU",
        uid=uid,
    ), secret)

    return key, uid, secret, server, 4


def logout(key, uid, secret, server):
    # one?action=logout&key=985120977&rid=-1&uid=89515708383274&sign=c8a8417fd2322d09274518b6dfc92c48
    r = send_request(server, dict(
        action="logout",
        key=key,
        rid=-1,
        uid=uid,
    ), secret)


def add_lootbox(key, uid, secret, server, rid):
    # one?action=logout&key=985120977&rid=-1&uid=89515708383274&sign=c8a8417fd2322d09274518b6dfc92c48
    r = send_request(server, dict(
        action="add_lootbox",
        key=key,
        lootboxId=crc32(lootbox_id),
        rid=rid,
        uid=uid,
    ), secret)

    return rid + 1

def upgrade_talent(key, uid, secret, server, rid):
    params = dict(
        entities=ent_id,
        uid=uid,
        key=key,
        action="upgrade_talent_by_entities",
        target_talent_id=tal_id
    )

    rid_start_from = rid
    requests_urls = []
    for i in range(0, 20):
        r = prepare_request(server, params, rid_start_from + i, secret)
        requests_urls.append(r)

    for response in requests.swarm(requests_urls):
        print response.content


if __name__ == '__main__':
    key, uid, secret, server, rid = login(email, password)

    if addlootbox:
        rid = add_lootbox(key, uid, secret, server, rid)
    if upgrade:
        upgrade_talent(key, uid, secret, server, rid)

    logout(key, uid, secret, server)

##    s = SoapAuctionService()
