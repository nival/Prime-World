#!/usr/bin/env python
# -*- coding: utf-8 -*-


import sys, time
sys.path.append('gen-py')

from thrift import Thrift
from thrift.transport import TTransport
from thrift.transport import THttpClient
from thrift.protocol import TBinaryProtocol

sys.path.append('gen-py/AccountManagementAPI')
import AccountManagement
import ttypes

import ujson

SERVER_ADDR = "127.0.0.1"

if __name__ == "__main__":
    try:
        transport = THttpClient.THttpClient('http://%s:8706/thrift?service=account_management' % SERVER_ADDR)
        ##transport = THttpClient.THttpClient('http://pw.nivalnetwork.com:8706/thrift?service=account_management')
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = AccountManagement.Client(protocol)
        transport.open()

        questPullsList = client.GetDynamicQuestPullsInfo().questPulls
        print "GetDynamicQuestPullsInfo : %s" % questPullsList

        questPullInfo = ttypes.DynamicQuestPull(
            locale="RU",
            startTime=50,
            endTime=1459087433,
            persistentId=4,
            quests=[20, 21, 22],
            hasRotation=True,
            isActive=True
        )

        auidsList = ttypes.AuidsList(
            index=1,
            description="test auids",
            auids=[1146, 1150]
        )

        #client.AddDynamicQuestPull(questPullInfo, "ЙаГМКо")
        #client.EditDynamicQuestPull(questPullInfo, "ЙаГМКо")
        #questList = client.GetDynamicQuestInfo().quests
        #print "GetDynamicQuestInfo : %s" % questList
        #test_json_file = open( "instant_quest_all_awards.json", "r" )
        #staticQuest = ujson.load( test_json_file )
        #test_json_file.close()
        #client.AddDynamicQuest(ujson.dumps(staticQuest), "RU", "ЙаГМКо")
        #client.AddDynamicQuestsToPull(4, [12, 13], "RU", "ЙаГМКо")
        #client.RemoveDynamicQuestsFromPull(4, [3, 4], "RU", "ЙаГМКо")
        #client.RemoveDynamicQuestPull(4, "RU", "ЙаГМКо")
        #questPullsList = client.GetDynamicQuestPullsInfo().questPulls
        #print "GetDynamicQuestPullsInfo : %s" % questPullsList

        #client.AddDynamicQuestPull(questPullInfo, "ЙаГМКо")
        #client.EditDynamicQuestPull(questPullInfo, "ЙаГМКо")

        #questList = client.GetDynamicQuestInfo().quests
        #print "GetDynamicQuestInfo : %s" % questList

        client.AddAuidsList(auidsList, "ЙаГМКо")
        auidsLists = client.GetAuidsLists().auidsLists
        print "GetAuidsLists : %s" % auidsLists

        transport.close()

    except Thrift.TException, tx:
        print '%s' % (tx.message)
