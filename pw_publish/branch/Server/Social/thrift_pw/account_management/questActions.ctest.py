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
import AccountManagementAPI.ttypes

sys.path.append('../../')
from base.helpers import pretty, json_loads, utf8convert

#~SERVER_ADDR = "pw.nivalnetwork.com"
SERVER_ADDR = "127.0.0.1"

if __name__ == "__main__":
    try:
        fbid = '100001432419583'
        fbid_str = "fb#"+fbid
        print "Using FBID:", fbid
        auid = 510

        transport = THttpClient.THttpClient('http://%s:8706/thrift?service=account_management' % SERVER_ADDR)
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = AccountManagement.Client(protocol)
        transport.open()

        print "Accinfo:", client.GetAccountByAuid(auid)
        time.sleep(1)

        #print "\nChangeQuest = Remove:", client.ChangeQuest(auid, -1627602691, AccountManagementAPI.ttypes.QuestChangeAction.Delete, "ЯГМко")
        print "\nGetQuests", client.GetQuests(auid)
        print "\nChangeQuest = Add:", client.ChangeQuest(auid, -1627602691, AccountManagementAPI.ttypes.QuestChangeAction.Add, "ЯГМко")
        print "\nChangeQuest = Accept:", client.ChangeQuest(auid, -1627602691, AccountManagementAPI.ttypes.QuestChangeAction.Accept, "ЯГМко")
        print "\nChangeQuest = Complete:", client.ChangeQuest(auid, -1627602691, AccountManagementAPI.ttypes.QuestChangeAction.Complete, "ЯГМко")
        print "\nGetQuests", client.GetQuests(auid)
        print "\nChangeQuest = Remove:", client.ChangeQuest(auid, -53741495, AccountManagementAPI.ttypes.QuestChangeAction.Delete, "ЯГМко")
        print "\nChangeQuest = Remove:", client.ChangeQuest(auid, 2004289053, AccountManagementAPI.ttypes.QuestChangeAction.Delete, "ЯГМко")

        print "\nChangeQuest = Add:", client.ChangeQuest(auid, -53741495, AccountManagementAPI.ttypes.QuestChangeAction.Add, "ЯГМко") # c21_qB
        print "\nChangeQuest = Accept:", client.ChangeQuest(auid, -53741495, AccountManagementAPI.ttypes.QuestChangeAction.Accept, "ЯГМко") #c22_qB
        print "\nGetQuests", client.GetQuests(auid)
        print "\nChangeQuest = Add:", client.ChangeQuest(auid, -293709913, AccountManagementAPI.ttypes.QuestChangeAction.Add, "ЯГМко")
        print "\nChangeQuest = Accept:", client.ChangeQuest(auid, -293709913, AccountManagementAPI.ttypes.QuestChangeAction.Accept, "ЯГМко")

        #print "\nGetQuests", client.GetQuests(auid)
        #print "\nChangeQuest = Remove:", client.ChangeQuest(auid, -1627602691, AccountManagementAPI.ttypes.QuestChangeAction.Delete, "ЯГМко")

        print "\nGetQuests", client.GetQuests(auid)


    except Thrift.TException, tx:
        print '%s' % (tx.message)
