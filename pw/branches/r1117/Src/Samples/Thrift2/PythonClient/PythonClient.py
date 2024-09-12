#!/usr/bin/env python
import sys

sys.path.append('gen-py')

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

from tutorial import *
from tutorial.ttypes import *

transport = TSocket.TSocket('127.0.0.1', 9090)

transport = TTransport.TBufferedTransport(transport)
 
protocol = TBinaryProtocol.TBinaryProtocol(transport)

client = Calculator.Client(protocol)

transport.open()

print client.ping()

print client.add(12,30)
