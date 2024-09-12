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

sys.path.append('../../')
from base.helpers import pretty, json_loads

from AccountManagementAPI.ttypes import RequestResult, PayServiceType, UserOperationType

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print "Usage ban_unban.ctest.py pwc-id"
        exit(1)
    fbid = str(sys.argv[1])
    fbid_str = "pwc#"+fbid
    print "Using FBID:", fbid
    auid = 6
    
    try:
        transport = THttpClient.THttpClient('http://127.0.0.1:8706/thrift?service=account_management')
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = AccountManagement.Client(protocol)
        transport.open()
                                            	
        print "Accinfo:", client.GetAccountByAuid(auid)
        time.sleep(1)
        
        print "\nBanUser:", client.UserOperation(auid, UserOperationType.Ban, 20, "test bam", [7,11], fbid_str, [1150, 1146],0)
        print "\nAccinfo:", client.GetAccountByAuid(auid)
        time.sleep(1)

        print "\nUnbanUser:", client.UserOperation(auid, UserOperationType.Unban, 0, '', [], fbid_str, [1150, 1146],0)
        print "\nAccinfo:", client.GetAccountByAuid(auid)
        time.sleep(1)
        
        print "\nMuteUser:", client.UserOperation(auid, UserOperationType.Mute, 20, "test mute", [13], fbid_str, [1150, 1146],0)
        print "\nAccinfo:", client.GetAccountByAuid(auid)
        time.sleep(1)

        print "\nUnmuteUser:", client.UserOperation(auid, UserOperationType.Unmute, 0, '', [], fbid_str, [1150, 1146],0)
        print "\nAccinfo:", client.GetAccountByAuid(auid)
        time.sleep(1)
        
        print "\nForgive:", client.UserOperation(auid, UserOperationType.Forgive, 0, 'Good person', [19], fbid_str, [1150, 1146],0)

        print "\nSetLeave:", client.UserOperation(auid, UserOperationType.SetLeave, 0, 'Leaver', [19], fbid_str, [1150, 1146], 15)
        print "\nAccinfo:", client.GetAccountByAuid(auid)

        transport.close()

    except Exception:
        traceback.print_exc()
        
#    except Thrift.TException, tx:
#        print '%s' % (tx.message)
