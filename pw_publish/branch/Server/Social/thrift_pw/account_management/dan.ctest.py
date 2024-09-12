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
from base.helpers import pretty, json_loads, utf8convert

#~SERVER_ADDR = "pw.nivalnetwork.com"
SERVER_ADDR = "127.0.0.1"

if __name__ == "__main__":
    try:
        transport = THttpClient.THttpClient('http://%s:8706/thrift?service=account_management' % SERVER_ADDR)
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = AccountManagement.Client(protocol)
        transport.open()

        nick = utf8convert( u"Данила 25" )
        print "FindNicknameExact(nick=%r) result:", client.FindNicknameExact(nick)
        nick = utf8convert( u"Данила 26" )
        print "FindNicknameExact(nick=%r) result:", client.FindNicknameExact(nick)
        nick = utf8convert( u"Данила 27" )
        print "FindNicknameExact(nick=%r) result:", client.FindNicknameExact(nick)
        exit(0)
        
        #~ print "EditAccountDbValue result:", client.EditAccountDbValue("fb#100000234693443", "ya GMko", "IsSpectator", "yes"),
        #~ exit(0)
        
        #~ print "GetAccountHeroes result:", client.GetAccountHeroes("fb#100000234693443")
        
        #~ heroInfo = AccountManagement.HeroInfo( rating=1290.0, heroClassId=1160508680, energy=99, heroInstanceId=1, experience=0, master=False, epicWins=0 )
        #~ print "EditHero result:", client.EditHero("fb#100000234693443", heroInfo, "gmLogin")
        #~ exit(0)
        
        #~ HeroInfo:
            #~ (1, TType.I32, 'heroClassId', None, None, ), # 1
            #~ (2, TType.I64, 'heroInstanceId', None, None, ), # 2
            #~ (3, TType.I32, 'experience', None, None, ), # 3
            #~ (4, TType.I32, 'energy', None, None, ), # 4
            #~ (5, TType.DOUBLE, 'rating', None, None, ), # 5
            #~ (6, TType.I32, 'epicWins', None, None, ), # 6
            #~ (7, TType.BOOL, 'master', None, None, ), # 7
        
        #~ print "EditAccountDbValue result:", client.EditAccountDbValue("fb#100000234693443", "ya GMko", "IsSpectator", "yes"),
        #~ exit(0)
        
        #~ print "AddUserRestriction error code=%s" % client.AddUserRestriction( "fb", "12347565", "cbtXXXXX" ) # первый вызов должен пройти ок
        #~ print "AddUserRestriction error code=%s" % client.AddUserRestriction( "fb", "12347565", "cbtXXXXX" ) # повторный должен пофейлиться
        #~ print client.GetAccountBySNUid( "fb", "100000234693443" ) # dan
        #print client.GetAccountByAuid( 25 ) # dan
        
        #~ print "RegisterPayment client.RegisterPayment( 25, 1234, 'REAL_BABLO' ) result:", client.RegisterPayment( 25, 1234, 'REAL_BABLO' )
        #~ print "RegisterPayment client.RegisterPayment( 25, 1234, 'BONUSES' ) result:", client.RegisterPayment( 25, 1234, 'BONUSES' )
        #~ print "GetPaymentBonusActions result:", client.GetPaymentBonusActions( 25 )
        #~ exit(0)
        
        #~ ###################
        #~ exit(0)
        #~ ###################
        
        #~ ###################
        #~ exit(0)
        #~ ###################
      
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
