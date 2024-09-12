#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, time
import traceback
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
        fbid = '100000766247771'
        fbid_str = "fb#"+fbid
        print "Using FBID:", fbid
        auid = 102

        transport = THttpClient.THttpClient('http://%s:8706/thrift?service=account_management' % SERVER_ADDR)
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = AccountManagement.Client(protocol)
        transport.open()

        print "AccInfo:", client.GetAccountByAuid(auid)
        time.sleep(1)

        print client.ApplyDLC( auid, "dlc_for_test" )
        print "AccInfo:", client.GetAccountByAuid(auid)

        print client.ApplyDLC( auid, "dlc_for_test" )
        print "AccInfo:", client.GetAccountByAuid(auid)

        print client.ApplyDLC( auid, "dlc_for_test_multi" )
        print "AccInfo:", client.GetAccountByAuid(auid)

        print client.ApplyDLC( auid, "dlc_for_test_multi" )
        print "AccInfo:", client.GetAccountByAuid(auid)

    except Exception:
        traceback.print_exc()
