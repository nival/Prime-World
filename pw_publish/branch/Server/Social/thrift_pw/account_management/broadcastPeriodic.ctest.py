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

from AccountManagement import BroadcastMessage, BroadcastInfo

if __name__ == "__main__":
    try:
        transport = THttpClient.THttpClient('http://127.0.0.1:8706/thrift?service=account_management')
        ##transport = THttpClient.THttpClient('http://pw.nivalnetwork.com:8706/thrift?service=account_management')
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = AccountManagement.Client(protocol)
        transport.open()

        now = int(time.time())
        msgRU = BroadcastMessage(Locale='RU', Text=u"РусскийПериодический".encode("utf8"))

        info2 = BroadcastInfo( Title="MessageTitle2", Messages=[msgRU], TimeStart=now+20, TimeFinish=now+30, Interval=1, EnabledNow=True )
        response = client.CreateBroadcast( info2, "gmLogin123" )
        print "CreateBroadcastMessage (2): %s" % response
        msg2 = response.id
        
        for i in xrange(60):
            time.sleep( 1 )
            print "."
        
        print "DeleteBroadcastMessage (2): result code %s" % client.DeleteBroadcast( msg2, "gmLogin123" )
        msglist = client.GetBroadcastList( 0,0 ).broadcastList
        print "GetBroadcastList (after delete): %s" % msglist
        
        transport.close()
        
    except Thrift.TException, tx:
        print '%s' % (tx.message)
