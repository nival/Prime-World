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

from MonitoringSummary import MonitoringSummary
from MonitoringSummary.ttypes import *

if len(sys.argv) <= 1 or sys.argv[1] == '--help':
  print ''
  print 'Usage: ' + sys.argv[0] + ' [-u url] function [arg1 [arg2...]]'
  print ''
  print 'Functions:'
  print '  i32 GetGameClusterCCU()'
  print '  i32 GetSocialClusterCCU()'
  print '  i32 GetNumberOfMatchmakingUsers()'
  print '  MonitoringInfo GetFullMonitoringInfo()'
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
client = MonitoringSummary.Client(protocol)
transport.open()

if cmd == 'GetGameClusterCCU':
  if len(args) != 0:
    print 'GetGameClusterCCU requires 0 args'
    sys.exit(1)
  pp.pprint(client.GetGameClusterCCU())

if cmd == 'GetMonitoringCounter':
  if len(args) != 1:
    print 'GetMonitoringCounter requires 1 args'
    sys.exit(1)
  pp.pprint(client.GetMonitoringCounter(sys.argv[1]))

elif cmd == 'GetSocialClusterCCU':
  if len(args) != 0:
    print 'GetSocialClusterCCU requires 0 args'
    sys.exit(1)
  pp.pprint(client.GetSocialClusterCCU())

elif cmd == 'GetNumberOfMatchmakingUsers':
  if len(args) != 0:
    print 'GetNumberOfMatchmakingUsers requires 0 args'
    sys.exit(1)
  pp.pprint(client.GetNumberOfMatchmakingUsers())

elif cmd == 'GetFullMonitoringInfo':
  if len(args) != 0:
    print 'GetFullMonitoringInfo requires 0 args'
    sys.exit(1)
  pp.pprint(client.GetFullMonitoringInfo())

else:
  print 'Unrecognized method %s' % cmd
  sys.exit(1)

transport.close()
