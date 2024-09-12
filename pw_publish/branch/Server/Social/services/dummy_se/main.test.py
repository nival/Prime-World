import sys
sys.path.append('../common/py')
sys.path.append('../..')

import unittest

import main
import time
import System.logs
import System.config
import tempfile

import EC

class MockRequest:

    def __init__(self):
        self.result = None
        self.isDone = False

    def Finish(self, result=None):
        self.result = result
        self.isDone = True

    def Fail(self, ec, message=None):
        self.result = {
            'ec' : ec
        }
        if message:
            self.result['message'] = message
        self.isDone = True

    def Reset(self):
        self.result = None
        self.isDone = False

class MockClusterLink(object):

    class Call:

        def __init__(self, args, callback, data, page, url):
            self.args = args
            self.callback = callback
            self.data = data
            self.page = page
            self.url = url

        def Reply(self, data, message):
            self.callback(data, message)

    def __init__(self, url=None):
        self.calls = []

    def fetch(self, args, callback, data=None, page='', url=None):
        self.calls.append(MockClusterLink.Call(args, callback, data, page, url))

class Test_SocialExchange(unittest.TestCase):

    def setUp(self):
        self.oldTime = time.time
        self.curTime = 0.0
        time.time = self.time    

    def tearDown(self):
        time.time = self.oldTime

    def time(self):
        return self.curTime
    
    def Advance(self, entity, period):
        self.curTime += period
        entity.Update()

    def Create(self, config=None):
        class Config:

            def __init__(self):
                self.db_path = tempfile.mkdtemp()
                self.allowed_projects = ['pw']

        if not config:
            config = Config()
        self.link = MockClusterLink()
        return main.SocialExchange(config, self.link)        

    def test_NotExistingPath(self):
        class Config:

            def __init__(self):
                self.db_path = tempfile.mkdtemp()+'notexists'
                self.allowed_projects = ['pw']
        se = self.Create(Config())
        request0 = MockRequest()
        se.Login(request0, 'pw', 555)

        while not request0.isDone:
            self.Advance(se, 2.0)


    def test_LoginLogout(self):
        se = self.Create()
        request0 = MockRequest()
        se.Login(request0, 'pw', 555)

        while not request0.isDone:
            self.Advance(se, 2.0)

        self.assertEquals(True, 'sid' in request0.result)
        self.assertEquals(False, 'messages' in request0.result)

        request1 = MockRequest()
        se.Logout(request1, request0.result['sid'])
        while not request1.isDone:
            self.Advance(se, 2.0)
        self.assertEquals(None, request1.result)

    def test_AlreadyLoggedIn(self):
        se = self.Create()
        request0 = MockRequest()
        se.Login(request0, 'pw', 555)

        while not request0.isDone:
            self.Advance(se, 2.0)

        request1 = MockRequest()
        se.Login(request1, 'pw', 555)

        while not request1.isDone:
            self.Advance(se, 2.0)

        self.assertEquals(EC.USER_ALREADY_LOGGEDIN, request1.result['ec'])

    def test_AlreadyLoggedOut(self):
        se = self.Create()
        request0 = MockRequest()
        se.Login(request0, 'pw', 555)

        sid = request0.result['sid']
        request0.Reset()
        se.Logout(request0, sid)

        while not request0.isDone:
            self.Advance(se, 2.0)

        request0.Reset()
        se.Logout(request0, sid)

        self.assertEquals(EC.SESSION_ALREADY_CLOSED, request0.result['ec'])

    def test_SendRecieve(self):
        se = self.Create()

        request0 = MockRequest()
        se.Login(request0, 'pw', 555)
        while not request0.isDone:
            self.Advance(se, 2.0)

        request1 = MockRequest()
        messages = [
            {
                'type' : 'TestMessage',
                'field0' : 'value0',
            },
        ]
        se.Send(request1, request0.result['sid'], 777, 'pw', messages)
        while not request1.isDone:
            self.Advance(se, 2.0)
        self.assertEquals(None, request1.result)

        request2 = MockRequest()
        se.Login(request2, 'pw', 777)
        while not request2.isDone:
            self.Advance(se, 2.0)
        self.assertEquals(True, 'sid' in request2.result)
        self.assertEquals(True, 'messages' in request2.result)
        self.assertEquals(1, len(request2.result['messages']))
        key = request2.result['messages'].keys()[0]
        message = request2.result['messages'][key]
        self.assertEquals('value0', message['field0'])
        self.assertEquals('TestMessage', message['type'])
        self.assertEquals(555, message['sender'])
        self.assertEquals(0, message['dt_rcv'])

        request3 = MockRequest()
        se.Retrieve(request3, request2.result['sid'])
        while not request3.isDone:
            self.Advance(se, 2.0)
    
        self.assertEquals(False, 'messages' in request3.result)

        for i in range(3):
            self.Advance(se, 2.0)

        request3.Reset()
        request3 = MockRequest()
        se.Retrieve(request3, request2.result['sid'])
        while not request3.isDone:
            self.Advance(se, 2.0)
        self.assertEquals(True, 'messages' in request2.result)
        self.assertEquals(1, len(request2.result['messages']))
        key = request2.result['messages'].keys()[0]
        message = request2.result['messages'][key]
        self.assertEquals('value0', message['field0'])
        self.assertEquals('TestMessage', message['type'])
        self.assertEquals(555, message['sender'])
        self.assertEquals(0, message['dt_rcv'])
    
    def test_Persistent(self):
        se = self.Create()

        request0 = MockRequest()
        se.Login(request0, 'pw', 555)
        while not request0.isDone:
            self.Advance(se, 2.0)

        request1 = MockRequest()
        messages = [
            {
                'type' : 'JoinRequest',
                'field1' : 'value1',
            },
        ]
        se.Send(request1, request0.result['sid'], 777, 'pw', messages)
        while not request1.isDone:
            self.Advance(se, 2.0)
        self.assertEquals(None, request1.result)

        config = se.config
        del se
        se = self.Create(config)

        request2 = MockRequest()
        se.Login(request2, 'pw', 777)
        while not request2.isDone:
            self.Advance(se, 2.0)
        self.assertEquals(True, 'messages' in request2.result)
        self.assertEquals(1, len(request2.result['messages']))
        key = request2.result['messages'].keys()[0]
        message = request2.result['messages'][key]
        self.assertEquals('value1', message['field1'])
        self.assertEquals('JoinRequest', message['type'])
        self.assertEquals(555, message['sender'])
        self.assertEquals(0, message['dt_rcv'])
    
    def test_DifferentProjects(self):
        se = self.Create()

        request0 = MockRequest()
        se.Login(request0, 'pw', 555)
        while not request0.isDone:
            self.Advance(se, 2.0)

        request1 = MockRequest()
        messages = [
            {
                'type' : 'JoinRequest',
                'field1' : 'value1',
            },
        ]
        se.Send(request1, request0.result['sid'], 777, 'pw', messages)
        while not request1.isDone:
            self.Advance(se, 2.0)
        self.assertEquals(None, request1.result)

        config = se.config
        del se
        se = self.Create(config)

        request2 = MockRequest()
        se.Login(request2, 'em', 777)
        while not request2.isDone:
            self.Advance(se, 2.0)
        self.assertEquals(False, 'messages' in request2.result)

    def test_Expire(self):
        se = self.Create()

        request0 = MockRequest()
        se.Login(request0, 'pw', 555)
        while not request0.isDone:
            self.Advance(se, 2.0)

        request1 = MockRequest()
        messages = [
            {
                'type' : 'JoinRequest',
                'field1' : 'value1',
                'tm_expire' : 60,
            },
        ]
        se.Send(request1, request0.result['sid'], 777, 'pw', messages)
        while not request1.isDone:
            self.Advance(se, 2.0)
        self.assertEquals(None, request1.result)

        for i in range(31):
            self.Advance(se, 2.0)
            
        request2 = MockRequest()
        se.Login(request2, 'pw', 777)
        while not request2.isDone:
            self.Advance(se, 2.0)
        self.assertEquals(False, 'messages' in request2.result)

    def test_Purge(self):
        se = self.Create()

        request0 = MockRequest()
        se.Login(request0, 'pw', 555)
        while not request0.isDone:
            self.Advance(se, 2.0)

        request1 = MockRequest()
        messages = [
            {
                'type' : 'JoinRequest',
                'field1' : 'value1',
            },
        ]
        se.Send(request1, request0.result['sid'], 777, 'pw', messages)
        while not request1.isDone:
            self.Advance(se, 2.0)
        self.assertEquals(None, request1.result)
            
        request2 = MockRequest()
        se.Login(request2, 'pw', 777)
        while not request2.isDone:
            self.Advance(se, 2.0)
        self.assertEquals(True, 'messages' in request2.result)

        request3 = MockRequest()
        messages = request2.result['messages']
        se.Purge(request3, request2.result['sid'], [messages.keys()[0]])
        self.assertEquals([messages.keys()[0]], request3.result['success'])

        for i in range(20):
            request4 = MockRequest()
            se.Retrieve(request4, request2.result['sid'])
            while not request4.isDone:
                self.Advance(se, 2.0)

            self.Advance(se, 2.0)
            self.assertEquals(False, 'messages' in request4.result)


    def test_MultiSend(self):
        pass

    def test_SendFromNotLoggedUser(self):
        se = self.Create()

        request1 = MockRequest()
        se.Send(request1, 'somesid', 777, 'pw', [])
        while not request1.isDone:
            self.Advance(se, 2.0)
        self.assertEquals(EC.SESSION_NOT_FOUND, request1.result['ec'])

    def test_NotAllowedProject(self):
        se = self.Create()

        request0 = MockRequest()
        se.Login(request0, 'eprst', 555)
        while not request0.isDone:
            self.Advance(se, 2.0)
        self.assertEquals(EC.PROJECT_NOT_ALLOWED, request0.result['ec'])

    def test_ForcedLogin(self):
        se = self.Create()
        request0 = MockRequest()
        se.Login(request0, 'pw', 555)

        while not request0.isDone:
            self.Advance(se, 2.0)
        self.assertEquals(True, 'sid' in request0.result)

        request1 = MockRequest()
        se.Login(request1, 'em', 555)
        while not request1.isDone:
            self.Advance(se, 2.0)
        self.assertEquals(True, 'sid' in request0.result)

        request2 = MockRequest()
        se.Login(request2, 'pw', 555)

        while not request2.isDone:
            self.Advance(se, 2.0)
        self.assertEquals(EC.USER_ALREADY_LOGGEDIN, request2.result['ec'])

        request3 = MockRequest()
        se.Login(request3, 'pw', 555, force=1)
        while not request2.isDone:
            self.Advance(se, 2.0)
        self.assertEquals(True, 'sid' in request3.result)
        self.assertNotEquals(request0.result['sid'], request3.result['sid'])

    def test_Push(self):
        se = self.Create()

        request0 = MockRequest()
        se.Login(request0, 'pw', 555)
        while not request0.isDone:
            self.Advance(se, 2.0)

        request1 = MockRequest()
        se.Login(request1, 'pw', 444, url='http://pw.zzima.com:88/one')
        while not request1.isDone:
            self.Advance(se, 2.0)

        request2 = MockRequest()
        messages = [
            {
                'type' : 'TestMessage',
                'field0' : 'value0',
            },
        ]
        se.Send(request2, request0.result['sid'], 444, 'pw', messages)
        while not request2.isDone:
            self.Advance(se, 2.0)
        self.assertEquals(None, request2.result)

        self.assertEquals(1, len(self.link.calls))
        self.assertEquals('http://pw.zzima.com:88/one', self.link.calls[0].url)
        self.assertEquals(444, self.link.calls[0].args['auid'])
        self.assertEquals('send', self.link.calls[0].args['method'])
        data = self.link.calls[0].data 
        self.assertEquals(True, 'messages' in data)
        self.assertEquals(1, len(data['messages']))
        key = data['messages'].keys()[0]
        message = data['messages'][key]
        self.assertEquals('value0', message['field0'])
        self.assertEquals('TestMessage', message['type'])
        self.assertEquals(555, message['sender'])
        self.assertEquals(0, message['dt_rcv'])

        self.link.calls[0].Reply([key], None)

        for i in range(10):
            self.Advance(se, 2.0)

        request3 = MockRequest()
        se.Retrieve(request3, request1.result['sid'])
        while not request3.isDone:
            self.Advance(se, 2.0)
    
        self.assertEquals(False, 'messages' in request3.result)



if __name__ == '__main__':  
    logLevel = 'error'
    if '--verbose' in sys.argv:
        logLevel = 'debug'
    System.logs.setup(None, logLevel)
    unittest.main()