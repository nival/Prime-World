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

sys.path.append('../../')
from base.helpers import pretty, json_loads

from AccountManagementAPI.ttypes import RequestResult, PayServiceType

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print "Usage pay_actions.ctest.py fb-id"
        exit(1)
    fbid = str(sys.argv[1])
    fbid_str = "fb#"+fbid
    print "Using FBID:", fbid
    
    try:
        transport = THttpClient.THttpClient('http://127.0.0.1:8706/thrift?service=account_management')
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = AccountManagement.Client(protocol)
        transport.open()

        print "Accinfo:", client.GetAccountBySNUid( "fb", fbid )
       
        result = client.PayChangeFraction( fbid_str, 1 )
        print "\nPayChangeFraction(1):", result
        
        result = client.PayChangeFraction( fbid_str, 0 )
        print "\nPayChangeFraction(0):", result
        
        result = client.PayChangeFraction( fbid_str, 0 )
        print "\nPayChangeFraction(0):", result
        
        result = client.GetPrices( fbid_str, PayServiceType.PremiumAccount )
        print "\nGetPrices(servicetype=PremiumAccount):", result

        result = client.BuyService( fbid_str, PayServiceType.PremiumAccount, 0 )
        print "\nBuyService(servicetype=PremiumAccount, paramValue=0):", result
        
        transport.close()
        
    except Thrift.TException, tx:
        print '%s' % (tx.message)
