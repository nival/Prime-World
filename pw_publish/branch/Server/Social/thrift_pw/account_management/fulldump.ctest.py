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

if __name__ == "__main__":
    try:
        transport = THttpClient.THttpClient('http://127.0.0.1:8706/thrift?service=account_management')
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = AccountManagement.Client(protocol)
        transport.open()

        print "GetAccountByAuid:", client.GetAccountByAuid( 6155 ) # fb:dan
        print "GetAccountBySNUid:", client.GetAccountBySNUid( "fb", "100000234693443" ) # fb:dan
        
        # ----------------------------------------------------------------------------
        ## вариант для StringDataResponse GetFullUserDump(...)
        print "GetFullUserDump(zipped):"
        zipped = client.GetFullUserDump( "fb#100000234693443", zip=True ) # fb:dan
        print zipped
        print "GetFullUserDump(zipped) len:", len(zipped.data)
        
        print "GetFullUserDump(pretty):"
        unzipped = client.GetFullUserDump( "fb#100000234693443", zip=False )
        print pretty( json_loads(unzipped.data) )
        print "GetFullUserDump(unzipped) len:", len(unzipped.data)

        print "----------------------------\nApplyFullUserDump(zipped):"
        apply_ok = client.ApplyFullUserDump( "fb#100003297559974", zipped.data ) # test fb:danila
        print "nApplyFullUserDump result code:", apply_ok
        
        ## print client.RemoveFakeAuid( "fb#100003297559974" ) # test fb:danila
        
        # ----------------------------------------------------------------------------
        ## вариант для string GetFullUserDump(...)
        #~ print "GetFullUserDump(zipped):"
        #~ zipped_data = client.GetFullUserDump( "fb#100000234693443", zip=True ) # fb:dan
        #~ print zipped_data
        #~ print "GetFullUserDump(zipped) len:", len(zipped_data)
        
        #~ print "GetFullUserDump(pretty):"
        #~ unzipped_data = client.GetFullUserDump( "fb#100000234693443", zip=False )
        #~ print pretty( json_loads(unzipped_data) )
        #~ print "GetFullUserDump(unzipped) len:", len(unzipped_data)

        #~ print "----------------------------\nApplyFullUserDump(zipped):"
        #~ apply_ok = client.ApplyFullUserDump( "fb#100003297559974", zipped_data ) # test fb:danila
        #~ print "nApplyFullUserDump result code:", apply_ok
        
        #~ ##print client.RemoveFakeAuid( "fb#100003297559974" ) # test fb:danila
        # ----------------------------------------------------------------------------
                
        transport.close()
        
    except Thrift.TException, tx:
        print '%s' % (tx.message)
