# -*- coding: utf-8 -*-
import sys
sys.path.append('../common/py')
sys.path.append('../..')
sys.path.append('../../base')

import System.logs
import System.fsm
import System.config
from helpers import *

import os.path
import tornado.escape
import tornado.httpserver
import tornado.ioloop
import tornado.options
import tornado.web
import tornado.httpclient
import json
import hashlib

import Network
import Network.HttpClient
from Network.SOA import Service

import logging
from logging import debug, info, error, warning

from thrift import Thrift
from thrift.transport import TTransport
from thrift.transport import THttpClient
from thrift.protocol import TBinaryProtocol

sys.path.append('../../thrift_pw/account_management/gen-py/AccountManagementAPI')
import AccountManagement

class DoHandler(tornado.web.RequestHandler):

    def initialize(self, config, http_client, service):
        self.http_client = http_client
        self.config = config
        self.service = service

    @tornado.web.asynchronous
    def get(self):
        auid = int(self.get_argument('auid'))
        amount = int(self.get_argument('amount'))
        txnid = self.get_argument('txnid')
        sign = self.get_argument('sign')
        ps = self.get_argument('ps')

        if self.config.check_sign:
            args = {
                'auid' : auid,
                'amount' : amount,
                'txnid' : txnid,
            }
            expectedSign = makeParamsSignature(args, self.config.secret_key)
            if expectedSign != sign:
                warning('Check sign failed (expected=%r actual=%r)' % (expectedSign, sign))
                raise tornado.web.HTTPError(401)

        data = {
            'result' : 0,
            'txnid' : txnid,
            'logid' : self.service.logid,
            'amount' : amount,
            'auid' : auid,
        }
        self.finish(json.dumps(data))
        self.service.Call(auid, amount, ps, txnid)

class _Service:

    def __init__(self, url):
        self.logid = 0
        self.client = THttpClient.THttpClient(url)
        self.transport = TTransport.TBufferedTransport(self.client)
        self.protocol = TBinaryProtocol.TBinaryProtocolAccelerated(self.transport)
        self.aclient = AccountManagement.Client(self.protocol)

    def Call(self, auid, amount, source, txnid):
        self.logid += 1
        self.transport.open()
        self.aclient.ReplenishUserGold( auid, amount, source )
        self.aclient.RegisterPayment( auid, amount, source, txnid )
        self.transport.close()

class DummyPaymentService(Service):

    def __init__(self, sid):
        super(DummyPaymentService, self).__init__(sid)
        self.entity = None

    def Start(self, link, config):
        self.config = config
        self.link = link
        
        self.http_client = Network.HttpClient.AsyncHttpClient(validate_cert=False)
        self.service = _Service(self.config.push_url)
        
        handlers = [
            ('/', DoHandler, dict(config=config, http_client=self.http_client, service=self.service)),
        ]

        self.application = tornado.web.Application( 
            handlers,
            debug=self.config.debug,
            autoescape=None )   
        self.http_server = tornado.httpserver.HTTPServer(self.application)
        self.http_server.bind(self.config.port)
        self.http_server.start(self.config.nump)
        self.fsm.Move(Service.STARTED)

    def Update(self):
        self.HttpLoggerTick()
        if self.fsm.state == Service.STOPPING:   
            self.fsm.Move(Service.STOPPED)
            
    def Stop(self, how):
        pass

def main(args, gate):
    if args.config:
        config = System.config.RawConfig(args.config)
    else:
        data = {
            'port' : 10006,
            'nump' : 1,
            'debug' : True,
            'push_url' : 'http://localhost:8706/thrift?service=account_management',
            'check_sign' : True,
            'secret_key' : 'PaymentSecretSalt',
        }
        config = System.config.RawConfig(data)
    svn = DummyPaymentService(args.sid)
    gate.AddService(svn, config)
    svn.HttpLoggerInit(args, config)


if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--config', default=None, help='Config path') 
    parser.add_argument('--sid', default='Payment', help='Service id')
    parser.add_argument('--pid', default='ps', help='Service process (instance) id')
    System.logs.setupParserArgs( parser )
    args = parser.parse_args()
    
    System.logs.setup(args.log, args.loglevel, args.logrotate)
    
    gate = Network.SOA.ServiceGate()

    main(args, gate)
    gate.Run() 
                