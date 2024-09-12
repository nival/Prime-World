#!/usr/bin/env python
import os
import sys
import pprint
import socket

from thrift.transport import THttpClient
from thrift.protocol import TBinaryProtocol

sys.path.append('./gen-py')

from ClusterManagementAPI import ClusterManagement
from ClusterManagementAPI.ttypes import *

import logging
from logging import error, info, debug


def PingAddr(addr):
    host, _port = addr.split(':')
    port = int(_port)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        s.connect((host, port))
    except socket.error, msg:
        return msg
    return None


def PingAddrs(addrs, retry=True):
    retries = []

    failed = 0
    for stype, addr in addrs:
        print 'Checking %r on %r ' % (stype, addr),
        msg = PingAddr(addr)
        if msg is not None:
            retries.append((stype, addr))
            print msg
            failed += 1
        else:
            print 'OK'

    if retry and len(retries) > 0:
        print 'Found suspicious %d services, retrying' % len(retries)
        return PingAddrs(retries, False)
    else:
        return failed


if len(sys.argv) <= 1 or sys.argv[1] == '--help':
    print 'Prime World PvX Cluster Tool (C) Nival 2008-2013'
    print 'Usage: ' + sys.argv[0] + ' [-u url] function [arg1 [arg2...]]'
    print ''
    print 'Functions:'
    print '  i32 ExecuteCommand()'
    print ''
    sys.exit(0)

handler = logging.StreamHandler()
logFormat = "%(asctime)s.%(msecs)d %(levelname)s: %(message)s" 
dateFormat = '%H:%M:%S'
formatter = logging.Formatter(logFormat, dateFormat)
handler.setFormatter(formatter)
logging.getLogger().addHandler(handler)
logging.getLogger().setLevel(logging.DEBUG)

pp = pprint.PrettyPrinter(indent=2)
host = 'localhost:9090'
argi = 1

if sys.argv[argi] == '-u':
    host = sys.argv[argi + 1]
    argi += 2
info('Host: %s' % host)

transport = THttpClient.THttpClient(host)
protocol = TBinaryProtocol.TBinaryProtocol(transport)
client = ClusterManagement.Client(protocol)
transport.open()

retcode = 0

if '--stopall' in sys.argv:
    services = client.GetServices()
    pp.pprint(services)
    pids = [service.pid for service in services]
    pids = set(pids)
    for pid in pids:
        os.system('TASKKILL /fi "PID eq %d"' % pid)
elif '--showall' in sys.argv:
    services = client.GetServices()
    pp.pprint(services)
elif '--ping' in sys.argv:
    services = client.GetServices()
    addrs = []
    for service in services:
        if service.frontendaddr:
            addrs.append((service.stype, service.frontendaddr))
    sys.exit(PingAddrs(addrs))
else:
    cmd = sys.argv[argi]
    args = sys.argv[argi + 1:]

    if cmd == 'ExecuteCommand':
        if len(args) != 2:
            error('ExecuteCommand requires 2 args')
            sys.exit(1)

        commands = {
            'STOP' : ServiceCommand.STOP,
            'START' : ServiceCommand.START,
            'RELOAD_CONFIG' : ServiceCommand.RELOAD_CONFIG,
            'SOFT_STOP' : ServiceCommand.SOFT_STOP,
        }
        command = commands.get(args[1].upper(), None)
        if command is not None:
            nargs = [
                ('serviceId', args[0]),
            ]
            nargs.append(('command', command))
            nargs.append(('arguments', ''))
            print cmd + '(' + str(nargs) + ') -> ',
            result = client.ExecuteCommand(nargs[0][1], nargs[1][1], nargs[2][1])
            if result == 0:
                print 'OK'
            else:
                print 'ERROR(%d)' % result
        else:
            error('unrecognized Execute argument %r' % args[1])
            retcode = 1
    else:
        error('unrecognized method %s' % cmd)
        retcode = 2

transport.close()
sys.exit(retcode)
