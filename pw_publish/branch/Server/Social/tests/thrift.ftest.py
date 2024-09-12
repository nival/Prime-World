import unittest
import os, sys

os.chdir('..')
sys.path.append( os.path.abspath('.') )

sys.path.append('cfg')
sys.path.append('base')
sys.path.append('memcache')

import urllib2
import httplib, urllib

sys.path.append( os.path.abspath('thrift_pw/serverinfo/gen-py') )
from serverinfo import ServerInfo
from serverinfo.ttypes import *

from base.helpers import ClassDict

from coord_cfg import COORDINATOR_WS_SERVERS

from thrift import Thrift
from thrift.transport import TTransport
from thrift.transport import THttpClient
from thrift.protocol import TBinaryProtocol

from thrift_pw.serverinfo.serverinfo_handler import ServerInfoHandler

class ThriftNetworkTest(unittest.TestCase):
    def test_getServers(self):
        transport = THttpClient.THttpClient('http://127.0.0.1:8700/thrift?service=serverinfo')
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocol(transport)
        client = ServerInfo.Client(protocol)
        transport.open()
        servers = client.getServers()
        self.assertTrue(isinstance(servers, list))
        for server in servers:
            self.assertTrue(isinstance(server, Server))
        transport.close()

    def test_getServers_get(self):
        conn = httplib.HTTPConnection("127.0.0.1:8700")
        conn.request("GET", "/thrift?service=serverinfo")
        response = conn.getresponse()
        self.assertEqual(response.status, 400)

    def test_getServers_post_empty(self):
        conn = httplib.HTTPConnection("127.0.0.1:8700")
        conn.request("POST", "/thrift?service=serverinfo")
        response = conn.getresponse()
        self.assertEqual(response.status, 400)

    def test_getServers_post_fail(self):
        params = urllib.urlencode({'spam': 1, 'eggs': 2, 'bacon': 3})
        conn = httplib.HTTPConnection("127.0.0.1:8700")
        conn.request("POST", "/thrift?service=serverinfo", params)
        response = conn.getresponse()
        self.assertEqual(response.status, 400)

class DummyISS:
    def getServers(self):
        return COORDINATOR_WS_SERVERS

class ThriftLocalTest(unittest.TestCase):
    def test_getServers(self):
        client_transport = TTransport.TMemoryBuffer()
        client_protocol = TBinaryProtocol.TBinaryProtocol(client_transport)
        client = ServerInfo.Client(client_protocol)
        client_transport.open()
        client.send_getServers()
        
        request_string = client_transport.getvalue()

        dummy_handler = ClassDict( I=ClassDict( WS=DummyISS() ) )
        server_handler = ServerInfoHandler( dummy_handler )
        server_processor = ServerInfo.Processor(server_handler)
        server_transport = TTransport.TMemoryBuffer(request_string)
        server_output_transport = TTransport.TMemoryBuffer()
        ifactory = TBinaryProtocol.TBinaryProtocolFactory()
        iprot = ifactory.getProtocol(server_transport)
        oprot = ifactory.getProtocol(server_output_transport)
        server_processor.process(iprot, oprot)
        
        output_string = server_output_transport.getvalue()
        
        client_return_transport = TTransport.TMemoryBuffer(output_string)
        client_return_protocol = TBinaryProtocol.TBinaryProtocol(client_return_transport)
        client_return = ServerInfo.Client(client_return_protocol)
        servers = client_return.recv_getServers()
        
        self.assertTrue(isinstance(servers, list))
        for server in servers:
            self.assertTrue(isinstance(server, Server))

if __name__=="__main__":
    unittest.main()
