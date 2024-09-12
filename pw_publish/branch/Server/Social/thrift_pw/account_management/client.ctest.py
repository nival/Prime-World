#!/usr/bin/env python

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

if __name__ == "__main__":
    try:
        transport = THttpClient.THttpClient('http://127.0.0.1:8706/thrift?service=account_management')
        #transport = THttpClient.THttpClient('http://IVANOV-MAC:8706/thrift?service=account_management')
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = AccountManagement.Client(protocol)
        transport.open()

        #----------------------------------------------------------------------
        print client.GetAccountBySNUid( "fb", "100000204558976" )
        #----------------------------------------------------------------------
        
        #----------------------------------------------------------------------
#        print client.SendMessageToUser( 77,  "fb#100000204558976", 'BanMessage', "Fuck you, you are banned now !!!!", "Admin" )
        #----------------------------------------------------------------------#
#        print client.MuteUser('fb#100000204558976', 19, 600, 'because', 'Admin')
#        print client.UnmuteUser('fb#100000204558976', 19, 'Admin')
#        print client.KickUser('fb#100000204558976','Admin')

        #print client.GetAccountByAuid( 6155 ) # dan
#        print client.GetAccountBySNUid( "fb", "100000234693443" ) # dan

        transport.close()
    except Thrift.TException, tx:
        print '%s' % (tx.message)
