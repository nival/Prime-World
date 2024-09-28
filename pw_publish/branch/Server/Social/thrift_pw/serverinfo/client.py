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

from serverinfo import ServerInfo
from serverinfo.ttypes import *

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.transport import THttpClient
from thrift.protocol import TBinaryProtocol

import urllib2


def invokeUrllib2( url, body, headers ):
    request = urllib2.Request(url, body, headers)
    reply_body = urllib2.urlopen(request).read()
    return reply_body

if __name__ == "__main__":
    try:
        ##transport = THttpClient.THttpClient('http://127.0.0.1:8700/thrift?service=serverinfo')
        transport = THttpClient.THttpClient('http://127.0.0.1:8706/thrift?service=serverinfo')
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = ServerInfo.Client(protocol)
        transport.open()

        print client.getServers()
        transport.close()
    except Thrift.TException, tx:
        print '%s' % (tx.message)
