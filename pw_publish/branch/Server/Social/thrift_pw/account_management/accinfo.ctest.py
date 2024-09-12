#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys, time
import traceback
import pprint

sys.path.append('gen-py')

from thrift import Thrift
from thrift.transport import TTransport
from thrift.transport import THttpClient
from thrift.protocol import TBinaryProtocol

sys.path.append('gen-py/AccountManagementAPI')
import AccountManagement

sys.path.append('../../')
from base.helpers import pretty, json_loads

from AccountManagementAPI.ttypes import RequestResult, PayServiceType, UserOperationType

if __name__ == "__main__":
# XXX: write your testing values here!
    sn = 'pwc'
    snuid = '8583423421579265'
    auid = 310491 # test
    email = "aww@aww.com"

    try:
        transport = THttpClient.THttpClient('http://127.0.0.1:8706/thrift?service=account_management')
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = AccountManagement.Client(protocol)
        transport.open()

        res = client.ActivateEmail(email, "")
        print "ActivateEmail Res: %r" % res

        res = client.GetAccountByAuid(auid)
        if res.result == 0:
            acc = res.accountInfo
            print "Login:", acc.login
            print "Nick:", acc.nickname
            print "JoinedSnids:", acc.joinedSnids
            print "Locale:", acc.locale
            print "Muid:", acc.muid
        else:
            print "Error!"
            print res

        res = client.GetLocaleInfoByAuid(auid)
        print "GetLocaleInfoByAuid Res: %r" % res
        res = client.GetLocaleInfoBySNUid(sn, snuid)
        print "GetLocaleInfoBySNUid Res: %r" % res

        # and here should be errors
        res = client.GetLocaleInfoBySNUid('hz', '992348024820394283042')
        print "GetLocaleInfoBySNUid wrong snuid Res: %r" % res

        # and this will genereate an exception since it couldn't translate auid to (snid, snuid)
        res = client.GetLocaleInfoByAuid(12354534512)
        print "GetLocaleInfoByAuid wrong auid Res: %r" % res

        transport.close()

    except Exception:
        traceback.print_exc()

#    except Thrift.TException, tx:
#        print '%s' % (tx.message)
