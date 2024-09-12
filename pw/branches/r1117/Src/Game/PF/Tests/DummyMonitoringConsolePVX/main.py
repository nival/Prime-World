#!/usr/bin/env python

import sys
import pprint
from urlparse import urlparse
from thrift.transport import TTransport
from thrift.transport import TSocket
from thrift.transport import THttpClient
from thrift.protocol import TBinaryProtocol

import sys
sys.path.append('./gen-py')

from Monitoring import Monitoring
from Monitoring.ttypes import *

if len(sys.argv) <= 1 or sys.argv[1] == '--help':
  print ''
  print 'Usage: ' + sys.argv[0] + ' [-u url] function [arg1 [arg2...]]'
  print ''
  print 'Functions:'
  print '  GetGameClusterCCU <perfCounterName>'
  print ''
  sys.exit(0)

pp = pprint.PrettyPrinter(indent = 2)
host = 'http://localhost'
argi = 1

if sys.argv[argi] == '-u':
  host = sys.argv[argi+1]
  argi += 2

cmd = sys.argv[argi]
args = sys.argv[argi+1:]

transport = THttpClient.THttpClient(host)
protocol = TBinaryProtocol.TBinaryProtocol(transport)
client = Monitoring.Client(protocol)
transport.open()

if cmd == 'GetGameClusterCCU':
  if len(args) != 1:
    print 'GetGameClusterCCU requires 1 arg, <perfCounterName>'
    print 'ex.'
    print '  GetGameClusterCCU OPRP/CCU'
    sys.exit(1)
  perf_counter_name = args[0]
  list_PerfCounterSample = client.GetPerfCounterSamples()
  ## print "list_PerfCounterSample = %r" % list_PerfCounterSample
  for sample in list_PerfCounterSample:
    if sample.name == perf_counter_name:
      pp.pprint( int(sample.value) )

else:
  print 'Unrecognized method %s' % cmd
  sys.exit(1)

transport.close()
