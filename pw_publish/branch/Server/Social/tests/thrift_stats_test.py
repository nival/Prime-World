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

from thrift import Thrift
from thrift.transport import TTransport
from thrift.transport import THttpClient
from thrift.protocol import TBinaryProtocol

os.chdir('..')
sys.path.append('.')

##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

sys.path.append('thrift_pw/statistics/gen-py')
import StatisticCore.StatisticService
from StatisticCore.ttypes import * # LoginInfo, ...

#~SERVER_ADDR = "pw.nivalnetwork.com"
SERVER_ADDR = "127.0.0.1"

if __name__ == "__main__":
    try:
        transport = THttpClient.THttpClient('http://%s:8766/thrift?service=stats' % SERVER_ADDR)
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = StatisticCore.StatisticService.Client(protocol)
        transport.open()

        SIZE_COUNT = 5
        ITERATIONS = 1000
        fail_count = 0
        for iteration in xrange(1,ITERATIONS+1):
            try:
                send_list = []
                for i in xrange(1,iteration*SIZE_COUNT):
                    send_list.append( LoginInfo( auid=i, nick="nick_%d" % i, server="server_%d" % i, cluster="cluster_%d" % i, \
                        timestamp=int(time.time()), ip="1.1.1.1", faction="A", factionselected=True, isdeveloper=False, locale="RU" ) )
                
                t0 = time.time()
                result = client.LoginUsers( send_list )
                t1 = time.time()
                print "[iter=%s, size=%s] LoginUsers error code=%s, timing=%.3f" % (iteration, iteration*SIZE_COUNT, result, t1-t0)
                
            except Thrift.TException, tx:
                print '[iter=%s, size=%s] %s' % (iteration, iteration*SIZE_COUNT, tx.message)
                fail_count += 1
        
        transport.close()
        print '==== RESULT: %s iterations, %s fails (%.3f percent fail)' % (ITERATIONS, fail_count, fail_count*100.0/ITERATIONS)
        
    except Thrift.TException, tx:
        print '%s' % (tx.message)
