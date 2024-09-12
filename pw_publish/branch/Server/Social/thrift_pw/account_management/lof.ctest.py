#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys, time
sys.path.append('gen-py')

from thrift import Thrift
from thrift.transport import TTransport
from thrift.transport import THttpClient
from thrift.protocol import TBinaryProtocol

sys.path.append('gen-py/AccountManagementAPI')
import AccountManagement

sys.path.append('../../')
from base.helpers import pretty, json_loads

from tornado.httpclient import HTTPRequest, HTTPClient

#~SERVER_ADDR = "pw.nivalnetwork.com"
SERVER_ADDR = "127.0.0.1"

if __name__ == "__main__":
    try:
        methodname = "BuyTournamentTicket"
        args = ( "fb#100000766247771", 2 ) # dan
        
        # пакуем вызов метода в строчку, и отсылаем ее обычным HTTP post
        send_transport = TTransport.TMemoryBuffer()
        send_protocol = TBinaryProtocol.TBinaryProtocol( send_transport )
        client = AccountManagement.Client( send_protocol )
        send_transport.open()
        
        send_methodname = "send_%s" % methodname
        send_method = getattr(client, send_methodname, None)
        send_method( *args ) 
        send_string = send_transport.getvalue()
        
        url = "http://%s:8706/thrift?service=account_management" % SERVER_ADDR
        request = HTTPRequest( url, method="POST", body=send_string )
        HTTP = HTTPClient()
        response = HTTP.fetch(request)

        # ответ распаковываем тоже с помощью thrift transport
        return_transport = TTransport.TMemoryBuffer( response.body )
        return_protocol = TBinaryProtocol.TBinaryProtocol( return_transport )
        client_return = AccountManagement.Client( return_protocol )
        
        recv_methodname = "recv_%s" % methodname
        recv_method = getattr( client_return, recv_methodname, None )
        print recv_method()
        
    except Thrift.TException, tx:
        print '%s' % (tx.message)
