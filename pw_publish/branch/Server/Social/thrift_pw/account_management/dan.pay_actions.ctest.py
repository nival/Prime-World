#!/usr/bin/env python
# -*- coding: utf-8 -*-

#
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements. See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership. The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License. You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied. See the License for the
# specific language governing permissions and limitations
# under the License.
#

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
    try:
        transport = THttpClient.THttpClient('http://127.0.0.1:8706/thrift?service=account_management')
        #transport = THttpClient.THttpClient('http://IVANOV-MAC:8706/thrift?service=account_management')
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = AccountManagement.Client(protocol)
        transport.open()

        #print client.GetAccountByAuid( 6155 ) # dan
        print client.GetAccountBySNUid( "fb", "100000234693443" ) # dan
        print "\nEditFreeChanges(0,0):", client.EditFreeChanges( "fb#100000234693443", "gmLoginXXX", 0, 0 )
        
        unzipped_data = client.GetFullUserDump( "fb#100000234693443", zip=False ).data
        assert unzipped_data
        json_data = json_loads(unzipped_data)
        assert( json_data["db"]["db"]["nickChanged"] == 0 )
        assert( json_data["db"]["db"]["fractionChanged"] == 0 )
        print "asserts (0,0) ok"
        
        result = client.PayChangeFraction( "fb#100000234693443", 1 )
        print "\nPayChangeFraction(1):", result
        
        result = client.PayChangeFraction( "fb#100000234693443", 0 )
        print "\nPayChangeFraction(0):", result
        
        result = client.PayChangeFraction( "fb#100000234693443", 0 )
        print "\nPayChangeFraction(0):", result
        
        result = client.PayEditNickname( "fb#100000234693443", "Dan123^&%*@!" )
        print "\nPayEditNickname('Dan^&%*@!'):", result
        assert result.result == RequestResult.BadResult
        assert result.ec == 12
        print "asserts ok"
        
        result = client.PayEditNickname( "fb#100000234693443", "Dan123" )
        print "\nPayEditNickname('Dan123'):", result
        assert result.result == RequestResult.Success
        print "asserts ok"
        
        #~ result = client.PayEditNickname( "fb#100003297559974", "Dan123" )
        #~ print "\nPayEditNickname('Dan123', test.danila):", result
        #~ assert result.result == RequestResult.BadResult
        #~ assert result.ec == 10
        #~ print "asserts ok"
        
        #~ result = client.PayEditNickname( "fb#100000234693443", "Dan1234" )
        #~ print "\nPayEditNickname('Dan1234'):", result
        #~ assert result.result == RequestResult.BadResult
        #~ assert result.ec == 50
        #~ print "asserts ok"
        
        #~ result = client.PayService( "fb#100000234693443", PayServiceType.PremiumAccount )
        #! print "\nPayService(servicetype=%s):" % PayServiceType.PremiumAccount, result
        
        transport.close()
        
    except Thrift.TException, tx:
        print '%s' % (tx.message)
