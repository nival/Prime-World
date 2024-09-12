import sys
import time
sys.path.append('gen-py')

from AccountManagementAPI import AccountManagement
from AccountManagementAPI.ttypes import *

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

    transport = THttpClient.THttpClient('http://127.0.0.1:%(port)i/Account' % {'port': port})
    transport = TTransport.TBufferedTransport(transport)
    protocol = TBinaryProtocol.TBinaryProtocol(transport)
    client = AccountManagement.Client(protocol)
    transport.open()

    print client.GetAccountBySNUid('fb', 'f123234234234234')
    print client.GetGameSession(2)
    print client.GetAccountBySNUid('fb', 'f123234234234234')
    print client.EditAccount('fb', 'f123234234234234' , AccountEdit("User Third Modified", 3, 3, 3, 3))
    print client.GetAccountBySNUid('fb', 'f123234234234234')
    print client.EditHero('fb', 'f123234234234234', 4, HeroEdit(666, 777))
    print client.GetAccountHeroes("fb", "f123456");
    print client.GetAccountBySNUid('fb', 'f123234234234234')
    
    transport.close()
