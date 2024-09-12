import sys
import unittest 
import main
import time
import System.config
import handlers
import urllib
import mocks

from base.helpers import ClassDict

from ext_main.who import User


class MockIOLoop:
    def add_timeout(self, callback, moment):
        pass

class MockWSX:
    
    class Request:
        def __init__(self, addr, args, body, post, callback):
            self.addr = addr
            self.args = args
            self.body = body
            self.post = post
            self.callback = callback

    def __init__(self):
        self.requests = {}

    def fetch(self, addr, args, callback, subrequest, unwrap, timeout):
        self.post(addr, args, None, callback, subrequest, unwrap, timeout)

    def post(self, _addr, args, body, callback, subrequest, unwrap, timeout):
        addr = _addr+'/?' + urllib.urlencode(args)
        if addr not in self.requests:
            self.requests[addr] = []
        self.requests[addr].append(MockWSX.Request(addr, args, body, body!=None, callback ))

    def push(self, addr, index, response):
        requests = self.requests[addr]
        request = requests[index]
        request.callback(response)
        del requests[index]
        if len(requests) == 0:
            del self.requests[addr]
        return request.addr

    def check(self, addr, index):
        requests = self.requests.get(addr, [])
        if index < len(requests):
            return True
        return False
            
        

class MockTimer:

    def __init__(self):
        self.savedTimeFunc = time.time
        self.time = 0.0
        time.time = self.onTime

    def advance(self, value):
        self.time += value

    def onTime(self):
        return self.time

    def __del__(self):  
        if time:
            time.time = self.savedTimeFunc

class Callback:
    def __init__(self):
        self.isCalled = False
        self.args = None

    def __call__(self, *args):
        assert self.isCalled == False
        self.args = args
        self.isCalled = True

class MockApis:

    def __init__(self):
        self.WSX = MockWSX()
        self.REDIS = mocks.MockRedisClient()

class Test_WS(unittest.TestCase):

    def setUp(self):
        self.timer = MockTimer()

    def tearDown(self):
        self.timer = None

    def test_Simple(self):
        ioloop = MockIOLoop()
        _config = {
            'service' : {
                'max_pending' : 10,
                'max_immediate_pending' : 0,
                'login_token_check_time' : 1,
                'login_token_expire_time' : 30,
                'login_offset_time' : 0,
            },
        }
        cfg = System.config.RawConfig(_config)

        apis = MockApis()
        ws = main.DummyWS(ioloop, cfg, apis)
        for i in range(10):
            ws.Update()

        user = User()
        token = ws.registerLogin('555', user, primary=1)
        self.assertEqual(True, token is not None)

        self.timer.advance(29)
        ws.Update()
        context = ws.checkLoginContext('555', token)
        self.assertEquals(context.user, user)

        self.timer.advance(7)
        ws.Update()
        context = ws.checkLoginContext('555', token)
        self.assertEquals(context.user, user)

        callback = Callback()
        ws.loginUser('555', context, callback)
        self.assertEquals(True, callback.isCalled)

        self.timer.advance(29)
        ws.Update()
        context = ws.checkLoginContext('555', token)
        self.assertEquals(context.user, user)
        
        self.timer.advance(2)
        ws.Update()
        context = ws.checkLoginContext('555', token)
        self.assertEquals(None, context)

    def test_NoExpireBeforeLogin(self):
        ioloop = MockIOLoop()
        _config = {
            'service' : {
                'max_pending' : 10,
                'max_immediate_pending' : 10,
                'login_token_check_time' : 5,
                'login_token_expire_time' : 30,
                'login_offset_time' : 0,
            },
        }
        cfg = System.config.RawConfig(_config)

        apis = MockApis()
        ws = main.DummyWS(ioloop, cfg, apis)
        for i in range(10):
            ws.Update()

        user = User()
        token = ws.registerLogin('555', user, primary=1)
        self.assertEqual(True, token is not None)

        self.timer.advance(29)
        ws.Update()
        context = ws.checkLoginContext('555', token)
        self.assertEquals(context.user, user)

        self.timer.advance(7)
        ws.Update()
        context = ws.checkLoginContext('555', token)
        self.assertEquals(context.user, user)


    def test_Cancel(self):
        ioloop = MockIOLoop()
        _config = {
            'service' : {
                'max_pending' : 1,
                'max_immediate_pending' : 0,
                'login_token_check_time' : 5,
                'login_token_expire_time' : 30,
                'login_offset_time' : 0,
            },
        }
        cfg = System.config.RawConfig(_config)

        apis = MockApis()
        ws = main.DummyWS(ioloop, cfg, apis)

        user = User()
        token = ws.registerLogin('555', user, primary=1)

        context = ws.checkLoginContext('555', token)
        callback = Callback()
        ws.loginUser('555', context, callback)
        ws.Update()

        peers = {
            'two' : {
                'on' : 1,
                'rdy' : 1,
                'max_users' : 100,
                'cur_users' : 0,
                'addr' : '127.0.0.1:555',
            },
        }      
        ws.onPeersRecieved(peers)

        callback = Callback()
        context = ws.checkLoginContext('555', token)
        ws.cancelUser('555', context, callback)
        self.assertEquals((False, None, None, 0, 0, 0), callback.args)

        ws.Update()
        context = ws.checkLoginContext('555', token)
        self.assertEquals(main.USER_CANCELED, context.status)

    def test_CancelDuringLoginNewLogin(self):
        ioloop = MockIOLoop()
        _config = {
            'service' : {
                'max_pending' : 1,
                'max_immediate_pending' : 1,
                'login_token_check_time' : 5,
                'login_token_expire_time' : 30,
                'login_offset_time' : 0,
            },
        }
        cfg = System.config.RawConfig(_config)

        apis = MockApis()
        ws = main.DummyWS(ioloop, cfg, apis)

        peers = {
            'two' : {
                'on' : 1,
                'rdy' : 1,
                'max_users' : 100,
                'cur_users' : 0,
                'addr' : '127.0.0.1:555',
                'server_id' : 34,
            },
        }      
        ws.onPeersRecieved(peers)

        user = User()
        token = ws.registerLogin('555', user, primary=1)

        context = ws.checkLoginContext('555', token)
        lcallback = Callback()
        ws.loginUser('555', context, lcallback)
        self.assertEquals(1, len(apis.WSX.requests))

        outToken = context.outToken

        ccallback = Callback()
        context = ws.checkLoginContext('555', token)
        ws.cancelUser('555', context, ccallback)
        self.assertEquals((False, None, None, 0, 0, 0), ccallback.args)

        context = ws.checkLoginContext('555', token)
        self.assertEquals(None, context)

        token = ws.registerLogin('555', user, primary=1)  # new login
        apis.WSX.push('127.0.0.1:555/?action=add_user&auid=555&token=%s&primary=1' % outToken, 0, None)

    def test_CancelDuringLogin(self):
        ioloop = MockIOLoop()
        _config = {
            'service' : {
                'max_pending' : 1,
                'max_immediate_pending' : 1,
                'login_token_check_time' : 5,
                'login_token_expire_time' : 30,
                'login_offset_time' : 0,
            },
        }
        cfg = System.config.RawConfig(_config)

        apis = MockApis()
        ws = main.DummyWS(ioloop, cfg, apis)

        peers = {
            'two' : {
                'on' : 1,
                'rdy' : 1,
                'max_users' : 100,
                'cur_users' : 0,
                'addr' : '127.0.0.1:555',
                'server_id' : 34,
            },
        }      
        ws.onPeersRecieved(peers)

        user = User()
        token = ws.registerLogin('555', user, primary=1)

        context = ws.checkLoginContext('555', token)
        lcallback = Callback()
        ws.loginUser('555', context, lcallback)
        self.assertEquals(1, len(apis.WSX.requests))

        outToken = context.outToken

        ccallback = Callback()
        context = ws.checkLoginContext('555', token)
        ws.cancelUser('555', context, ccallback)
        self.assertEquals((False, None, None, 0, 0, 0), ccallback.args)

        context = ws.checkLoginContext('555', token)
        self.assertEquals(None, context)

        apis.WSX.push('127.0.0.1:555/?action=add_user&auid=555&token=%s&primary=1' % outToken, 0, None)

    def test_CancelDuringDelayedLogin(self):
        ioloop = MockIOLoop()
        _config = {
            'service' : {
                'max_pending' : 1,
                'max_immediate_pending' : 1,
                'login_token_check_time' : 5,
                'login_token_expire_time' : 30,
                'login_offset_time' : 1,
            },
        }
        cfg = System.config.RawConfig(_config)

        apis = MockApis()
        ws = main.DummyWS(ioloop, cfg, apis)

        peers = {
            'two' : {
                'on' : 1,
                'rdy' : 1,
                'max_users' : 100,
                'cur_users' : 0,
                'addr' : '127.0.0.1:555',
                'server_id' : 34,
            },
        }      
        ws.onPeersRecieved(peers)

        user = User()
        token = ws.registerLogin('555', user, primary=1)

        context = ws.checkLoginContext('555', token)
        callback = Callback()
        ws.loginUser('555', context, callback)
        self.assertEquals(0, len(apis.WSX.requests))

        self.timer.advance(2.0)
        ws.Update()
        self.assertEquals(1, len(apis.WSX.requests))

        outToken = context.outToken

        callback = Callback()
        context = ws.checkLoginContext('555', token)
        ws.cancelUser('555', context, callback)
        self.assertEquals((False, None, None, 0, 0, 0), callback.args)

        context = ws.checkLoginContext('555', token)
        self.assertEquals(None, context)

        apis.WSX.push('127.0.0.1:555/?action=add_user&auid=555&token=%s&primary=1' % outToken, 0, None)


    def test_Recalc(self):
        ioloop = MockIOLoop()
        _config = {
            'service' : {
                'max_pending' : 1,
                'max_immediate_pending' : 0,
                'login_token_check_time' : 5,
                'login_token_expire_time' : 30,
                'login_offset_time' : 0,
            },
        }
        cfg = System.config.RawConfig(_config)

        apis = MockApis()
        ws = main.DummyWS(ioloop, cfg, apis)

        peers = {
            'two' : {
                'on' : 1,
                'rdy' : 1,
                'max_users' : 100,
                'cur_users' : 0,
                'addr' : '127.0.0.1:555',
                'server_id' : 33,
            },
        }      
        ws.onPeersRecieved(peers)

        user = User()
        token = ws.registerLogin('555', user, primary=1)

        context = ws.checkLoginContext('555', token)
        callback = Callback()
        ws.loginUser('555', context, callback)
        self.assertEquals(True, callback.isCalled)
        
        callback = Callback()
        ws.pollUser('555', context, callback)
        self.assertEquals(False, callback.isCalled)

        sid = 12
        peer = ClassDict()
        peer.name = 'one'
        peer.on = 1
        peer.rdy = 1
        peer.addr = '127.0.0.1:8000'
        peer.max_users = 1500
        peer.cur_users = 405
        ws.peers[sid] = peer
        ws.onGetPeerServer(peer, peer.name, sid, handlers.PEER_ADDED) 
        self.assertEquals(True, callback.isCalled)
        self.assertEquals((False, None, None, 1, 1, 0), callback.args)

        ws.Update()
        self.assertEquals(1, len(apis.WSX.requests))
        apis.WSX.push('127.0.0.1:555/?action=add_user&auid=555&token=%s&primary=1' % context.outToken, 0, 'OK')

    def test_SecondLogin(self):
        ioloop = MockIOLoop()
        _config = {
            'port' : 5656,
            'coordinator' : {
                'url' : 'htpp://coordinator',
            },
            'service' : {
                'max_pending' : 1,
                'max_immediate_pending' : 0,
                'login_token_check_time' : 5,
                'login_token_expire_time' : 180,
                'login_offset_time' : 60,  # offset 
            },
        }
        cfg = System.config.RawConfig(_config)

        apis = MockApis()
        ws = main.DummyWS(ioloop, cfg, apis)

        peers = {
            'two' : {
                'on' : 1,
                'rdy' : 1,
                'max_users' : 100,
                'cur_users' : 0,
                'addr' : '127.0.0.1:555',
                'server_id' : 33,
            },
            'one' : {
                'on' : 1,
                'rdy' : 1,
                'max_users' : 100,
                'cur_users' : 0,
                'addr' : '127.0.0.1:777',
                'server_id' : 34,
            },
        }      
        ws.onPeersRecieved(peers)

        user = User()
        token0 = ws.registerLogin('555', user, primary=1)
        context = ws.checkLoginContext('555', token0)

        callback = Callback()
        ws.loginUser('555', context, callback)
        self.assertEquals(True, callback.isCalled)
        self.assertEquals(0, len(apis.WSX.requests))

        ws.Update()
        self.assertEquals(0, len(apis.WSX.requests))

        self.timer.advance(14.0)
        ws.Update()
        self.assertEquals(0, len(apis.WSX.requests))

        token1 = ws.registerLogin('555', user, primary=1)
        ws.Update()
        self.assertEquals(0, len(apis.WSX.requests))

        self.timer.advance(59.0)
        ws.Update()
        self.assertEquals(0, len(apis.WSX.requests))

        self.timer.advance(2.0)
        ws.Update()
        self.assertEquals(0, len(apis.WSX.requests))  # no login for a while

        context = ws.checkLoginContext('555', token1)
        callback = Callback()
        ws.loginUser('555', context, callback)
        self.assertEquals(True, callback.isCalled)
        self.assertEquals(0, len(apis.WSX.requests))

        self.timer.advance(5.0)
        
        ws.Update()
        self.assertEquals(0, len(apis.WSX.requests))

        self.timer.advance(54.0)
        ws.Update()
        self.assertEquals(False, apis.WSX.check('127.0.0.1:555/?action=add_user&auid=555&token=%s&primary=1' % context.outToken, 0))

        self.timer.advance(6.0)
        ws.Update()

        self.assertEquals(True, apis.WSX.check('127.0.0.1:555/?action=add_user&auid=555&token=%s&primary=1' % context.outToken, 0))
        apis.WSX.push('127.0.0.1:555/?action=add_user&auid=555&token=%s&primary=1' % context.outToken, 0, 'OK')

    def test_DisableLogin(self):
        ioloop = MockIOLoop()
        _config = {
            'service' : {
                'max_pending' : 1,
                'max_immediate_pending' : 0,
                'login_token_check_time' : 5,
                'login_token_expire_time' : 30,
                'login_offset_time' : 0,
            },
            'coordinator' : {
                "url": "127.0.0.1:8700",
                "stype": "http"
            },
            'port' : 555,
        }
        cfg = System.config.RawConfig(_config)

        apis = MockApis()
        ws = main.DummyWS(ioloop, cfg, apis)

        peers = {
            'two' : {
                'on' : 1,
                'rdy' : 1,
                'max_users' : 100,
                'cur_users' : 0,
                'addr' : '127.0.0.1:555',
                'server_id' : 33,
            },
            'one' : {
                'on' : 1,
                'rdy' : 1,
                'max_users' : 100,
                'cur_users' : 0,
                'addr' : '127.0.0.1:777',
                'server_id' : 34,
            },
        }      
        ws.onPeersRecieved(peers)

        user = User()
        token = ws.registerLogin('555', user, primary=1)

        context = ws.checkLoginContext('555', token)
        callback = Callback()

        ws.loginUser('555', context, callback)
        self.assertEquals(True, callback.isCalled)
        self.assertEquals(0, len(apis.WSX.requests))

        ws.Update()
        self.assertEquals(1, len(apis.WSX.requests))
        apis.WSX.push('127.0.0.1:555/?action=add_user&auid=555&token=%s&primary=1' % context.outToken, 0, None)

        self.timer.advance(14.0)

        ws.Update()
        self.assertEquals(1, len(apis.WSX.requests))
        apis.WSX.push('127.0.0.1:777/?action=add_user&auid=555&token=%s&primary=1' % context.outToken, 0, None)
        self.assertEquals(0, len(apis.WSX.requests))

        self.timer.advance(2.0)
        ws.Update()
        self.assertEquals(0, len(apis.WSX.requests))

        for i in range(3):
            self.timer.advance(4.0)
            ws.Update()
            self.assertEquals(0, len(apis.WSX.requests))

        self.timer.advance(5.0)
        ws.Update()
        self.assertEquals(2, len(apis.WSX.requests)) # 1 login and 1 connect to coordinator 
        apis.WSX.push('127.0.0.1:555/?action=add_user&auid=555&token=%s&primary=1' % context.outToken, 0, 'OK')

    def test_LoginLimit(self):
        ioloop = MockIOLoop()
        _config = {
            'port' : 5656,
            'coordinator' : {
                'url' : 'htpp://coordinator',
            },
            'service' : {
                'max_pending' : 200,
                'max_immediate_pending' : 10,
                'login_token_check_time' : 30,
                'login_token_expire_time' : 180,
                'login_offset_time' : 0,
            },
        }
        cfg = System.config.RawConfig(_config)

        apis = MockApis()
        ws = main.DummyWS(ioloop, cfg, apis)

        peers = {
            'one' : {
                'on' : 1,
                'rdy' : 1,
                'max_users' : 1,
                'cur_users' : 0,
                'addr' : '127.0.0.1:777',
                'server_id' : 34,
            },
        }      
        ws.onPeersRecieved(peers)

        user0 = User()
        token0 = ws.registerLogin('555', user0, primary=1)
        context0 = ws.checkLoginContext('555', token0)

        user1 = User()
        token1 = ws.registerLogin('666', user1, primary=1)
        context1 = ws.checkLoginContext('666', token1)

        user2 = User()
        token2 = ws.registerLogin('777', user2, primary=1)
        context2 = ws.checkLoginContext('777', token2)

        callback0 = Callback()
        ws.loginUser('555', context0, callback0)
        self.assertEquals(False, callback0.isCalled)
        self.assertEquals(1, len(apis.WSX.requests))

        callback1 = Callback()
        ws.loginUser('666', context1, callback1)
        self.assertEquals((False, None, None, 1, 1, 0), callback1.args)
        self.assertEquals(1, len(apis.WSX.requests))

        callback2 = Callback()
        ws.loginUser('777', context2, callback2)
        self.assertEquals((False, None, None, 2, 1, 0), callback2.args)
        self.assertEquals(1, len(apis.WSX.requests))

        peers = {
            'one' : {
                'on' : 1,
                'rdy' : 1,
                'max_users' : 1,
                'cur_users' : 1,
                'addr' : '127.0.0.1:777',
                'server_id' : 34,
            },
        }      
        ws.onPeersRecieved(peers)
        apis.WSX.push('127.0.0.1:777/?action=add_user&auid=555&token=%s&primary=1' % context0.outToken, 0, 'OK')

        user3 = User()
        token3 = ws.registerLogin('888', user3, primary=1)
        context3 = ws.checkLoginContext('888', token3)

        user4 = User()
        token4 = ws.registerLogin('999', user4, primary=1)
        context4 = ws.checkLoginContext('999', token4)

        callback3 = Callback()
        ws.loginUser('888', context3, callback3)
        self.assertEquals(True, callback3.isCalled)    
        self.assertEquals((False, None, None, 3, 1, 0), callback3.args)
        self.assertEquals(0, len(apis.WSX.requests))

        callback4 = Callback()
        ws.loginUser('999', context4, callback4)
        self.assertEquals(True, callback4.isCalled)
        self.assertEquals((False, None, None, 4, 1, 0), callback4.args)
        self.assertEquals(0, len(apis.WSX.requests))

        ws.Update()
        self.timer.advance(4.0)
        ws.Update()

        peers = {
            'one' : {
                'on' : 1,
                'rdy' : 1,
                'max_users' : 1,
                'cur_users' : 0,
                'addr' : '127.0.0.1:777',
                'server_id' : 34,
            },
        }      
        ws.onPeersRecieved(peers)
        self.timer.advance(4.0)
        ws.Update()
        self.assertEquals(1, len(apis.WSX.requests))
        ws.Update()
        self.assertEquals(1, len(apis.WSX.requests))
        self.timer.advance(4.0)
        ws.Update()
        apis.WSX.push('127.0.0.1:777/?action=add_user&auid=666&token=%s&primary=1' % context1.outToken, 0, 'OK')
        ws.Update()

    def test_NoLimit(self):
        ioloop = MockIOLoop()
        _config = {
            'port' : 5656,
            'coordinator' : {
                'url' : 'htpp://coordinator',
            },
            'service' : {
                'max_pending' : 200,
                'max_immediate_pending' : 10,
                'login_token_check_time' : 30,
                'login_token_expire_time' : 180,
                'login_offset_time' : 0,
            },
        }
        cfg = System.config.RawConfig(_config)

        apis = MockApis()
        ws = main.DummyWS(ioloop, cfg, apis)

        peers = {
            'one' : {
                'on' : 1,
                'rdy' : 1,
                'cur_users' : 0,
                'addr' : '127.0.0.1:777',
                'server_id' : 34,
            },
        }      
        ws.onPeersRecieved(peers)
        user0 = User()
        token0 = ws.registerLogin('555', user0, primary=1)
        context0 = ws.checkLoginContext('555', token0)

        callback0 = Callback()
        ws.loginUser('555', context0, callback0)
        self.assertEquals(False, callback0.isCalled)
        self.assertEquals(1, len(apis.WSX.requests))

    def test_PrimaryFlag(self):
        ioloop = MockIOLoop()
        _config = {
            'port' : 5656,
            'coordinator' : {
                'url' : 'htpp://coordinator',
            },
            'service' : {
                'max_pending' : 200,
                'max_immediate_pending' : 10,
                'login_token_check_time' : 30,
                'login_token_expire_time' : 180,
                'login_offset_time' : 0,
            },
        }
        cfg = System.config.RawConfig(_config)

        apis = MockApis()
        ws = main.DummyWS(ioloop, cfg, apis)

        peers = {
            'one' : {
                'on' : 1,
                'rdy' : 1,
                'cur_users' : 0,
                'addr' : '127.0.0.1:777',
                'server_id' : 34,
            },
        }      
        ws.onPeersRecieved(peers)

        user0 = User()
        user0.snid = 'fb'
        user0.snuid = '777'
        user0.original_snid = 'fb'
        user0.original_snuid = '777'
        token0 = ws.registerLogin('555', user0, primary=1)

        user1 = User()
        user1.snid = 'ok'
        user1.snuid = '888'
        user1.original_snid = 'ok'
        user1.original_snuid = '888'
        token1 = ws.registerLogin('555', user1, primary=0)
        self.assertEquals(token0, token1)

        context0 = ws.checkLoginContext('555', token0)
        callback0 = Callback()
        ws.loginUser('555', context0, callback0)
        self.assertEquals(False, callback0.isCalled)
        self.assertEquals(1, len(apis.WSX.requests))

        apis.WSX.push('127.0.0.1:777/?action=add_user&auid=555&token=%s&primary=1' % context0.outToken, 0, 'OK')
        self.assertEquals(True, callback0.isCalled)
        result, server, token, arg0, arg1, arg2 = callback0.args
        self.assertEquals((True, 'one', 0, 0, 0), (result, server, arg0, arg1, arg2) )

    def test_MergeAndLoginPrimary(self):
        ioloop = MockIOLoop()
        _config = {
            'port' : 5656,
            'coordinator' : {
                'url' : 'htpp://coordinator',
            },
            'service' : {
                'max_pending' : 200,
                'max_immediate_pending' : 10,
                'login_token_check_time' : 30,
                'login_token_expire_time' : 180,
                'login_offset_time' : 0,
            },
        }
        cfg = System.config.RawConfig(_config)

        apis = MockApis()
        ws = main.DummyWS(ioloop, cfg, apis)

        peers = {
            'one' : {
                'on' : 1,
                'rdy' : 1,
                'cur_users' : 0,
                'addr' : '127.0.0.1:777',
                'server_id' : 34,
            },
        }      
        ws.onPeersRecieved(peers)

        user0 = User()
        user0.snid = 'fb'
        user0.snuid = '777'
        user0.original_snid = 'fb'
        user0.original_snuid = '777'
        token0 = ws.registerLogin('555', user0, primary=1)

        user1 = User()
        user1.snid = 'ok'
        user1.snuid = '888'
        user1.original_snid = 'ok'
        user1.original_snuid = '888'
        token1 = ws.registerLogin('666', user1, primary=0)
        self.assertNotEquals(token0, token1)

        mcallback = Callback()
        ws.mergeAccounts('555', '666', mcallback)
        self.assertEquals(False, mcallback.isCalled) 

        apis.WSX.push('127.0.0.1:777/?action=l_merge_internal&email_md5=None&auid0=555&auid1=666&pwc_snuid=None', 0, {'update_auid': 555, 'sn_count' : 2, 'sn_count_prev' : 1})
        self.assertEquals(True, mcallback.isCalled) 

        context0 = ws.checkLoginContext('555', token0)
        callback0 = Callback()
        ws.loginUser('555', context0, callback0)
        self.assertEquals(False, callback0.isCalled)
        self.assertEquals(1, len(apis.WSX.requests))

        apis.WSX.push('127.0.0.1:777/?action=add_user&auid=555&token=%s&primary=1' % context0.outToken, 0, "OK")
        self.assertEquals(True, callback0.isCalled)
        result, server, token, arg0, arg1, arg2 = callback0.args
        self.assertEquals((True, 'one', 0, 0, 0), (result, server, arg0, arg1, arg2) )

    def test_MergeAndLoginNotPrimary(self):
        ioloop = MockIOLoop()
        _config = {
            'port' : 5656,
            'coordinator' : {
                'url' : 'htpp://coordinator',
            },
            'service' : {
                'max_pending' : 200,
                'max_immediate_pending' : 10,
                'login_token_check_time' : 30,
                'login_token_expire_time' : 180,
                'login_offset_time' : 0,
            },
        }
        cfg = System.config.RawConfig(_config)

        apis = MockApis()
        ws = main.DummyWS(ioloop, cfg, apis)

        peers = {
            'one' : {
                'on' : 1,
                'rdy' : 1,
                'cur_users' : 0,
                'addr' : '127.0.0.1:777',
                'server_id' : 34,
            },
        }      
        ws.onPeersRecieved(peers)

        user0 = User()
        user0.snid = 'fb'
        user0.snuid = '777'
        user0.original_snid = 'fb'
        user0.original_snuid = '777'
        token0 = ws.registerLogin('555', user0, primary=1)

        user1 = User()
        user1.snid = 'ok'
        user1.snuid = '888'
        user1.original_snid = 'ok'
        user1.original_snuid = '888'
        token1 = ws.registerLogin('666', user1, primary=0)
        self.assertNotEquals(token0, token1)

        mcallback = Callback()
        ws.mergeAccounts('666', '555', mcallback)
        self.assertEquals(False, mcallback.isCalled) 

        apis.WSX.push('127.0.0.1:777/?action=l_merge_internal&email_md5=None&auid0=666&auid1=555&pwc_snuid=None', 0, {'update_auid': 666, 'sn_count' : 2, 'sn_count_prev' : 1})
        self.assertEquals(True, mcallback.isCalled) 

        context0 = ws.checkLoginContext('666', token1)
        callback0 = Callback()
        ws.loginUser('666', context0, callback0)
        self.assertEquals(False, callback0.isCalled)
        self.assertEquals(1, len(apis.WSX.requests))

        apis.WSX.push('127.0.0.1:777/?action=add_user&auid=666&token=%s&primary=1' % context0.outToken, 0, "OK")
        self.assertEquals(True, callback0.isCalled)
        result, server, token, arg0, arg1, arg2 = callback0.args
        self.assertEquals((True, 'one', 0, 0, 0), (result, server, arg0, arg1, arg2) )

    def test_Register(self):
        ioloop = MockIOLoop()
        _config = {
            'port' : 5656,
            'coordinator' : {
                'url' : 'htpp://coordinator',
            },
            'service' : {
                'max_pending' : 200,
                'max_immediate_pending' : 10,
                'login_token_check_time' : 30,
                'login_token_expire_time' : 180,
                'login_offset_time' : 0,
                'allowed_muids' : ['mail.ru'],
            },
        }
        cfg = System.config.RawConfig(_config)

        apis = MockApis()
        ws = main.DummyWS(ioloop, cfg, apis)

        user0 = User()
        user0.snid = 'fb'
        user0.snuid = '777'
        user0.original_snid = 'fb'
        user0.original_snuid = '777'
        user0.muid = 'mailru'
        user0.ruid = 'mailru'
        token0 = ws.registerLogin('555', user0, primary=1, registering=True)
        self.assertEquals(1, apis.REDIS.items['regs/muid']['mailru'])
        self.assertEquals(1, apis.REDIS.items['regs/ruid']['mailru'])
        self.assertEquals(1, apis.REDIS.items['regs/snid']['fb'])

        user0 = User()
        user0.snid = 'vk'
        user0.snuid = '777'
        user0.original_snid = 'vk'
        user0.original_snuid = '777'
        user0.muid = 'torrent'
        user0.ruid = 'torrent'
        token0 = ws.registerLogin('555', user0, primary=1, registering=True)
        self.assertEquals(1, apis.REDIS.items['regs/muid']['<other>'])
        self.assertEquals(1, apis.REDIS.items['regs/ruid']['<other>'])
        self.assertEquals(1, apis.REDIS.items['regs/snid']['vk'])

class Test_LoadWS(unittest.TestCase):

    def test_Simple(self):
        ioloop = MockIOLoop()
        _config = {
            'service' : {
                'max_pending' : 10,
                'max_immediate_pending' : 10,
                'login_token_check_time' : 0,
                'login_token_expire_time' : 180,
                'login_offset_time' : 0,
            },
        }
        cfg = System.config.RawConfig(_config)

        apis = MockApis()
        ws = main.DummyWS(ioloop, cfg, apis)
        for i in range(10000):
            user = User()
            token = ws.registerLogin(str(i), user, primary=1)

        start = time.time()
        
        ws.Update()

class Test_LoginMath(unittest.TestCase):

    def test_IncrementalAverage(self):
        c = main.IncAverageCalculator()
        self.assertEquals(0, c.average)

        c.push(1.0)
        self.assertEquals(1, c.average)

        c.push(2.0)
        self.assertEquals(1.5, c.average)

        c.push(3.0)
        self.assertEquals(2.0, c.average)

    def test_WaitTime(self):
        def getEstimatedWaitTime(qlength, avgWaitTime, avgLoginTime, userWaitTime, shiftTime, processorsCount, addon):
            return (avgWaitTime-userWaitTime)+((avgLoginTime*qlength)+min(shiftTime, avgLoginTime)) / float(processorsCount);

        self.assertEquals(12, getEstimatedWaitTime(qlength=1, avgWaitTime=10, avgLoginTime=1, userWaitTime=0, shiftTime=1, processorsCount=1, addon=0))
        self.assertEquals(7, getEstimatedWaitTime(qlength=1, avgWaitTime=10, avgLoginTime=1, userWaitTime=5, shiftTime=1, processorsCount=1, addon=0))

        self.assertEquals(11, getEstimatedWaitTime(qlength=1, avgWaitTime=10, avgLoginTime=1, userWaitTime=0, shiftTime=1, processorsCount=2, addon=0))

if __name__ == '__main__':        
    if '--verbose' in sys.argv:
        import logging
        logging.getLogger().setLevel(logging.DEBUG)

    unittest.main()