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
        transport = THttpClient.THttpClient('http://192.168.2.6:8706/thrift?service=account_management')
        ##transport = THttpClient.THttpClient('http://pw.nivalnetwork.com:8706/thrift?service=account_management')
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = AccountManagement.Client(protocol)
        transport.open()

        locales = client.GetBroadcastLocales()
        print 'Locales', locales.locales

        msglist = client.GetBroadcastList( 0, -1 ).broadcastList
        print "GetBroadcastList (previous persistent messages): %s" % msglist
        for msg in msglist:
            print 'delete', msg.Id
            client.DeleteBroadcast(msg.Id, "gmLogin123")

        msglist = client.GetBroadcastList( 0, -1 ).broadcastList
        prev_len = len(msglist)

        msgRU = BroadcastMessage(Locale='RU', Text=u"Русский".encode("utf8"))
        msgUS = BroadcastMessage(Locale='EN', Text=u"American".encode("utf8"))
        msgTR = BroadcastMessage(Locale='TR', Text=u"Turkish".encode("utf8"))
                
        info = BroadcastInfo( Title="MessageTitle1", Messages=[msgRU, msgUS, msgTR], TimeStart=0, TimeFinish=0, Interval=0, EnabledNow=True )
        response = client.CreateBroadcast( info, "gmLogin123" )
        print "CreateBroadcastMessage: %s" % response
        info.Id = response.id
        msg1 = response.id
           
        msglist = client.GetBroadcastList( 0, -1 ).broadcastList
        print "GetBroadcastList (after create): %s" % msglist
        assert( len(msglist) - prev_len == 1 )
        
        now = int(time.time())
        msgRU = BroadcastMessage(Locale='RU', Text=u"РусскийПериодический".encode("utf8"))
        msgUS = BroadcastMessage(Locale='EN', Text=u"AmericanPeriodic".encode("utf8"))
        msgTR = BroadcastMessage(Locale='TR', Text=u"TurkishPeriodic".encode("utf8"))
        info2 = BroadcastInfo( Title="MessageTitle2", Messages=[msgRU, msgUS, msgTR], TimeStart=now, TimeFinish=now+15, Interval=5, EnabledNow=True )
        response = client.CreateBroadcast( info2, "gmLogin123" )
        print "CreateBroadcastMessage (2): %s" % response
        msg2 = response.id
        
        info.Messages[0].Text = u"Русский Текст Периодический, Бессмысленный И Беспощадный".encode("utf8")
        info.EnabledNow = True
        print "EditBroadcastMessage: result code %s" % client.EditBroadcast( info, "gmLogin123" )
        
        msglist = client.GetBroadcastList( 0, 0 ).broadcastList
        print "GetBroadcastList (after edit): %s" % msglist
        assert( len(msglist) - prev_len == 2 )
        assert( msglist[prev_len+0].Messages[0].Text == u"Русский Текст Периодический, Бессмысленный И Беспощадный".encode("utf8") )
        assert( msglist[prev_len+0].Messages[0].Locale == 'RU' )

        print "StartMessageRotation: result code %s" % client.StartMessageRotation( msg1, "gmLogin123" )
        
        msglist = client.GetBroadcastList( prev_len+0,1 ).broadcastList
        print "GetBroadcastList [0:1] (after start): %s" % msglist
        assert( len(msglist) == 1 )
        assert( msglist[0].EnabledNow == True )
        
        msglist = client.GetBroadcastList( prev_len+1,1 ).broadcastList
        print "GetBroadcastList [1:1] (after start): %s" % msglist
        assert( len(msglist) == 1 )
        
        msglist = client.GetBroadcastList( prev_len+10,1 ).broadcastList
        print "GetBroadcastList [10:1] (after start): %s" % msglist
        assert( len(msglist) == 0 )
        
        print "StopMessageRotation: result code %s" % client.StopMessageRotation( msg1, "gmLogin123" )
        
        msglist = client.GetBroadcastList( 0,0 ).broadcastList
        print "GetBroadcastList (after stop): %s" % msglist
        assert( len(msglist) - prev_len == 2 )
        assert( msglist[prev_len+0].EnabledNow == False )
        
        print "StartMessageRotation: result code %s" % client.StartMessageRotation( msg1, "gmLogin123" )
        
        for i in xrange(20):
            time.sleep( 1 )
            print "."
        
        print "DeleteBroadcastMessage: result code %s" % client.DeleteBroadcast( msg1, "gmLogin123" )
        msglist = client.GetBroadcastList( 0,0 ).broadcastList
        print "GetBroadcastList (after delete): %s" % msglist
        assert( len(msglist) - prev_len == 1 )
        
        print "DeleteBroadcastMessage (2): result code %s" % client.DeleteBroadcast( msg2, "gmLogin123" )
        msglist = client.GetBroadcastList( 0,0 ).broadcastList
        print "GetBroadcastList (after delete): %s" % msglist
        assert( len(msglist) - prev_len == 0 )
        
        transport.close()
        
    except Thrift.TException, tx:
        print '%s' % (tx.message)
