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

def printAccInfo(client, auid):
    res = client.GetAccountByAuid(auid)
    acc = res.accountInfo
    print "Accinfo:", acc
    print "Country: %s, region: %s, city: %s" % (acc.country, acc.region, acc.city)
    print "OVR Country: %s, region: %s, city: %s" % (acc.gmcountry, acc.gmregion, acc.gmcity)


if __name__ == "__main__":
    #if len(sys.argv) != 2:
    #    print "Usage geoshou.ctest.py fb-id"
    #    exit(1)
    #fbid = str(sys.argv[1])
    fbid = '100000257782810'
    fbid_str = "fb#"+fbid
    print "Using FBID:", fbid
    auid = 20968
    
    try:
        transport = THttpClient.THttpClient('http://127.0.0.1:8706/thrift?service=account_management')
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = AccountManagement.Client(protocol)
        transport.open()
        
        printAccInfo(client, auid)                                           	
        time.sleep(1)
		
        print "\nUpdateGeoshowFlag = On:", client.UpdateGeoshowFlag(auid, True)
        time.sleep(7)
        print "\nUpdateGeoshowFlag = Off:", client.UpdateGeoshowFlag(auid, False)

        print "Set geoposition override:", client.BindToGeolocation(auid, "RU", "07", "Moscow", fbid_str)
        printAccInfo(client, auid)                                           	
        
        print "Remoe override:", client.BindToGeolocation(auid, None, None, None, fbid_str)
        printAccInfo(client, auid)                                           	
        
        print "Erroneous override:", client.BindToGeolocation(auid, None, "0", "", fbid_str)
        printAccInfo(client, auid)                                           	
        
        transport.close()

    except Exception:
        traceback.print_exc()
        
#    except Thrift.TException, tx:
#        print '%s' % (tx.message)
