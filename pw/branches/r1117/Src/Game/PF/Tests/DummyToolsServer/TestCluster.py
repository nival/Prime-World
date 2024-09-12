import sys
import time
sys.path.append('gen-py')

from ClusterManagementAPI import ClusterManagement
from ClusterManagementAPI.ttypes import *

from thrift.protocol import TBinaryProtocol
from thrift.transport import TTransport
from thrift.transport import THttpClient

import sys, httplib, urllib2, urllib

if __name__ == "__main__":
    try:
        port_param = [a for a in sys.argv if a.startswith("--port")][0]
        port = int(port_param.split("=")[1])
    except IndexError:
        port = 8888

    transport = THttpClient.THttpClient('http://127.0.0.1:%(port)i/Cluster' % {'port': port})
    transport = TTransport.TBufferedTransport(transport)
    protocol = TBinaryProtocol.TBinaryProtocol(transport)
    client = ClusterManagement.Client(protocol)
    transport.open()
    print client.GetServices()
    time.sleep(2)
    client.ExecuteCommand('1', ServiceCommand.START, '')
    time.sleep(2)
    print client.GetServices()
    time.sleep(2)
    print client.GetServices()
    time.sleep(2)
    client.ExecuteCommand('1', ServiceCommand.SOFT_RESTART, '')
    print client.GetServices()
    time.sleep(2)
    print client.GetServices()
    time.sleep(2)
    client.ChangeParameters('1', [ServiceParameter(name='param1', value='value1', changeable=True, needrestart=False), 
                                  ServiceParameter(name='param2', value='value2', changeable=False, needrestart=True),], 0)
    print client.GetServices()
    time.sleep(2)
    client.ChangeParameters('1', [ServiceParameter(name='param1', value='val666', changeable=False, needrestart=False), 
                                  ServiceParameter(name='param3', value='val333', changeable=True, needrestart=True),], 0)
    print client.GetServices()
    time.sleep(2)
    print client.GetServices()
    time.sleep(2)
    print client.GetServices()
    time.sleep(2)
    print client.GetServices()
    time.sleep(2)

    transport.close()
