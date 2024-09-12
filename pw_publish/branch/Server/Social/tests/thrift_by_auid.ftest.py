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

import sys, time, os

os.chdir('..')
sys.path.append( os.path.abspath('.') )

sys.path.append('thrift_pw/account_management/gen-py')

from thrift import Thrift
from thrift.transport import TTransport
from thrift.transport import THttpClient
from thrift.protocol import TBinaryProtocol

sys.path.append('thrift_pw/account_management/gen-py/AccountManagementAPI')
import AccountManagement

from base.helpers import pretty, json_loads

#~SERVER_ADDR = "pw.nivalnetwork.com"
SERVER_ADDR = "127.0.0.1"

if __name__ == "__main__":
    try:
        transport = THttpClient.THttpClient('http://%s:8706/thrift?service=account_management' % SERVER_ADDR)
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = AccountManagement.Client(protocol)
        transport.open()

        ###################
        #~ print client.SendMessageToUser( "login123", 26, "_title_", "...text...", "gm123" ) # dan
        #~ exit(0)
        
        #~ print client.GetAccountByAuid( 26 ) # dan
        #~ exit(0)
        
        #~ print client.GetAccountBySNUid( "fb", "100000234693443" ) # dan
        #~ exit(0)
        
        print client.GetAccountHeroes( "fb#100000234693443" ) # dan
        exit(0)
        ###################
      
        print "EditFreeChanges(333,444):", client.EditFreeChanges( "fb#100000234693443", "gmLoginXXX", 333, 444 )
        
        unzipped_data = client.GetFullUserDump( "fb#100000234693443", zip=False )
        json_data = json_loads(unzipped_data.data)
        
        assert( json_data["db"]["db"]["nickChanged"] == 333 )
        assert( json_data["db"]["db"]["fractionChanged"] == 444 )
        print "asserts (x,y) ok"
        
        print "GetAccountBySNUid", client.GetAccountBySNUid( "fb", "100000234693443" ) # dan
        
        print "EditFreeChanges(0,0):", client.EditFreeChanges( "fb#100000234693443", "gmLoginXXX", 0, 0 )
        
        unzipped_data = client.GetFullUserDump( "fb#100000234693443", zip=False )
        json_data = json_loads(unzipped_data.data)
        
        assert( json_data["db"]["db"]["nickChanged"] == 0 )
        assert( json_data["db"]["db"]["fractionChanged"] == 0 )
        print "asserts (0,0) ok"
        
        print "EditFreeChanges(0,0):", client.EditFreeChanges( "fb#100000234693443", "gmLoginXXX", 0, 0 )
        
        print "GetAccountBySNUid", client.GetAccountBySNUid( "fb", "100000234693443" ) # dan
        
        print "EditNickname('Dan'):", client.EditNickname( "fb#100000234693443", "gmLoginXXX", "Dan123" )
        print "EditNickname('Dan^&%*@!'):", client.EditNickname( "fb#100000234693443", "gmLoginXXX", "Dan123^&%*@!" )
        print "EditNickname('Dan', test.danila):", client.EditNickname( "fb#100003297559974", "gmLoginXXX", "Dan123" )
        
        transport.close()
    except Thrift.TException, tx:
        print '%s' % (tx.message)
