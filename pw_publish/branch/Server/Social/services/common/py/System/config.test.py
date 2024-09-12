import unittest

import config
import base64

class Test_Config(unittest.TestCase):

    def test_Simple(self):
        files = [
            ('config.cfg', base64.b64encode("watchdog_ip = '192.168.1.4'\nwatchdog_port=8889")),
        ]
        c = config.Config(files)
        self.assertEquals([], c.errors)
        self.assertEquals('192.168.1.4', c.watchdog_ip)
        self.assertEquals(8889, c.watchdog_port)

        self.assertEquals(True, 'config.cfg' in c.processed)

    def test_Float(self):
        files = [
            ('config.cfg', base64.b64encode("watchdog_port = 9.2")),
        ]
        c = config.Config(files)
        self.assertEquals([], c.errors)
        self.assertEquals(9.2, c.watchdog_port)

    def test_Bool(self):
        files = [
            ('config.cfg', base64.b64encode("watchdog_flag = True")),
        ]
        c = config.Config(files)
        self.assertEquals([], c.errors)
        self.assertEquals(True, c.watchdog_flag)

    def test_Error(self):
        files = [
            ('config.cfg', base64.b64encode("watchdog_ip = 192.168.1.4")),
        ]
        c = config.Config(files)
        self.assertEquals('config.cfg', c.errors[0][0])
        self.assertEquals(True, c.errors[0][1].find('Traceback') >= 0)

    def test_SubConfig(self):
        files = [
            ('config.cfg', base64.b64encode("include('subconfig.cfg')\n\nport=56")),
            ('subconfig.cfg', base64.b64encode("watchdog_port=8889")),
        ]
        c = config.Config(files)
        self.assertEquals([], c.errors)
        self.assertEquals(8889, c.watchdog_port)
        self.assertEquals(56, c.port)

        self.assertEquals(True, 'config.cfg' in c.processed)
        self.assertEquals(True, 'subconfig.cfg' in c.processed)

    def test_SubConfig2(self):
        files = [
            ('config.cfg', base64.b64encode("include('subconfig.cfg')\r\n")),
            ('subconfig.cfg', base64.b64encode("")),
        ]
        c = config.Config(files)
        self.assertEquals([], c.errors)

        self.assertEquals(True, 'config.cfg' in c.processed)
        self.assertEquals(True, 'subconfig.cfg' in c.processed)

    def test_CustomGlobal(self):
        files = [
            ('config.cfg', base64.b64encode("publish = PUBLISH_INTERNAL")),
        ]
        c = config.Config(files, {'PUBLISH_INTERNAL' : 1})
        self.assertEquals([], c.errors)
        self.assertEquals(1, c.publish)

    def test_Refresh(self):
        files = [
            ('config.cfg', base64.b64encode("publish = PUBLISH_INTERNAL")),
        ]
        g = {}
        c = config.Config(files, g)
        self.assertEquals([], c.errors)
        self.assertEquals('<null>', c.publish)

        g['PUBLISH_INTERNAL'] = 1
        c.Refresh(g)
        self.assertEquals(1, c.publish)

    def test_NestedGlobal(self):
        files = [
            ('config.cfg', base64.b64encode("publish = runtime.value")),
        ]
        class Runtime:
            value = 1
        c = config.Config(files, {'runtime' : Runtime()})
        self.assertEquals([], c.errors)
        self.assertEquals(1, c.publish)        

    def test_FailedStrings(self):
        files = [
            ('config.cfg', base64.b64encode("publish = undefined_var\nname=123")),
        ]
        c = config.Config(files)
        self.assertEquals([], c.errors)
        self.assertEquals(123, c.name)

    def test_InfiniteLoop(self):
        files = [
            ('config.cfg', base64.b64encode("include('subconfig.cfg')")),
            ('subconfig.cfg', base64.b64encode("include('config.cfg')")),
        ]
        c = config.Config(files)
        self.assertEquals([], c.errors)

    def test_NotSetVars(self):
        files = [
            ('config.cfg', base64.b64encode("")),
        ]
        c = config.Config(files)
        self.assertEquals([], c.errors)
        self.assertEquals(None, c.not_existing_var)

    def test_GlobalVarsWithOperation(self):
        files = [
            ('config.cfg', base64.b64encode("publish = BALANCED | DIRECT")),
        ]
        c = config.Config(files, cglobals = {'BALANCED' : 1, 'DIRECT' : 2} )
        self.assertEquals([], c.errors)
        self.assertEquals(3, c.publish)  

    def test_Acquire(self):
        files = [
            ('config.cfg', base64.b64encode("port = acquire(PORT, 8888)")),
        ]
        g = {'PORT' : 1}
        c = config.Config(files, cglobals = g)
        self.assertEquals([], c.errors)
        self.assertEquals(8888, c.port)  

        def Acquire(what, default):
            return 555   

        c.Refresh(g, Acquire)
        self.assertEquals(555, c.port)  


    def test_Policy(self):
        files = [
            ('config.cfg', base64.b64encode("transport='http'")),
        ]
        class Policy:
            pass
        policy = Policy()
#        policy.add_argument('transport', default=None, type=str, choices=['http', 'tcp'])
#        policy.add_argument('protocol', default=None, type=str, choices=['http', 'tcp'])
                    
        c = config.Config(files)
        self.assertEquals([], c.errors)
        self.assertEquals('http', c.transport)

class Test_RawConfig(unittest.TestCase):


    def test_Simple(self):
        c = config.RawConfig(
            {
                'port' : 10004,
                'pwc_version' : '0.12.0.11796.Trunk',
            }
        ) 
        self.assertEquals(10004, c.port)
        self.assertEquals('0.12.0.11796.Trunk', c.pwc_version)
    def test_SubDict(self):
        c = config.RawConfig(
            {
                'port' : 10004,
                'async_http_client' : {
                    'handshake_threads_count' : 16,
                }
            }
        ) 
        self.assertEquals(16, c.async_http_client.handshake_threads_count)



unittest.main()