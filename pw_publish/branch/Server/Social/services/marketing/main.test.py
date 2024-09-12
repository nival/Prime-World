import unittest
import sys
import datetime
import time
import os

import main
import test
import System.config
import System.logs

from logging import debug

class MockModule:

    def Install(self, events):
        self.installed = True
        events.OnRegister.Bind(self.OnRegister)
        events.OnBeginInstall.Bind(self.OnBeginInstall)
        events.OnCastleLogin.Bind(self.OnCastleLogin)
        events.OnQuest.Bind(self.OnQuest)
        events.OnHeroLevel.Bind(self.OnHeroLevel)
        events.OnHeroRank.Bind(self.OnHeroRank)
        events.OnCastleLevel.Bind(self.OnCastleLevel)
        self.registers = []
        self.installs = []
        self.clogins = []
        self.quests = []
        self.hlevels = []
        self.hranks = []
        self.clevels = []

    def GetPartner(self):
        return None

    def OnCastleLogin(self, user, faction, auid):
        self.clogins.append(user)

    def OnRegister(self, user):
        self.registers.append(user)

    def OnBeginInstall(self, user):
        self.installs.append(user)

    def OnQuest(self, user, quid, status, tm):
        self.quests.append( (user, quid, status, tm))

    def OnHeroLevel(self, user, heroid, level, tm):
        self.hlevels.append((user, heroid, level, tm))

    def OnHeroRank(self, user, heroid, level, rank, rank_up, tm):
        self.hranks.append((user, heroid, level, rank, rank_up, tm))

    def OnCastleLevel(self, user, level, tm):
        self.clevels.append((user, level, tm))

import kontagent

class MockModuleLoader:
   
    def __init__(self):
        self.queues = []
        self.modules = []

    def Load(self, name, config):
        queue = test.MockQueue()
        if name == 'kontagent':
            m = kontagent.Module(queue, config)
        else:
            m = MockModule()
        self.modules.append( (name, m) )
        self.queues.append(queue) 
        return m

class TimeSaver:

    def __init__(self, callback):
        self.saved = time.time
        time.time = callback

    def __del__(self):
        time.time = self.saved

class Test_MarketingService(unittest.TestCase):

    def test_Module(self):
        data = {
            'partners' : {
                'rambler' : {
                    'code' : 'ff',
                    'source' : 'landing'
                },
                'pw' : {
                    'code' : 'ee',
                    'source' : 'copy'
                },
            },
            'modules' : { 'kontagent' : { 'url' : '' }, 'gameguru' : {}  },
            'db' : tempfile.mktemp(),
            'edb' : tempfile.mktemp(),
            'flush_period' :  2.0,
            'exchange_rate' : 2.0,
            'muid_presets' : [],
        }                       
        config = System.config.RawConfig(data)
        loader = MockModuleLoader()
        m = main._MarketingService(config, loader)
        queue = loader.queues[0]

        self.assertEquals(2, len(loader.modules))
        self.assertEquals('kontagent', loader.modules[1][0])
        self.assertEquals('gameguru', loader.modules[0][0])

        module = loader.modules[0][1]
        self.assertEquals(True, module.installed)

    def test_CountCastleLoginNoMuid(self):
        data = {
            'partners' : {
                'rambler' : {
                    'code' : 'ff',
                    'source' : 'landing'
                },
                'pw' : {
                    'code' : 'ee',
                    'source' : 'copy'
                },
            },
            'modules' : { 'kontagent' : { 'url' : '' }, 'mymodule' : {}  },
            'db' : tempfile.mktemp(),
            'edb' : tempfile.mktemp(),
            'flush_period' :  2.0,
            'exchange_rate' : 2.0,
            'muid_presets' : [],
        }                       
        config = System.config.RawConfig(data)
        loader = MockModuleLoader()
        m = main._MarketingService(config, loader)
        queue = loader.queues[0]

        request = test.MockRequest()
        m.CreateMuid(request)
        self.assertEquals(True, request.isDone)
        self.assertEquals(True, None != request.result['muid'])
        muid = request.result['muid']
        self.assertEquals('q', muid)

        request = test.MockRequest()
        m.CastleLogin(request, '444', '0')
        self.assertEquals(main.NO_MUID, request.result['ec'])

        request1 = test.MockRequest()
        m.CastleLogin(request1, '444', '0')
        self.assertEquals(main.NO_MUID, request.result['ec'])


        request = test.MockRequest()
        m.FirstLogin(request, muid, 444)
        self.assertEquals(True, request.isDone)
        self.assertEquals(0, request.result['ec'])
        self.assertEquals(main.DecodeKey(muid), request.result.get('muid', None))

        self.assertEquals('mymodule', loader.modules[1][0])
        self.assertEquals(2, loader.modules[1][1].clogins[1].clogins)

    def test_CountCastleLogin(self):
        data = {
            'partners' : {
                'rambler' : {
                    'code' : 'ff',
                    'source' : 'landing'
                },
                'pw' : {
                    'code' : 'ee',
                    'source' : 'copy'
                },
            },
            'modules' : { 'kontagent' : { 'url' : '' }, 'mymodule' : {}  },
            'db' : tempfile.mktemp(),
            'edb' : tempfile.mktemp(),
            'flush_period' :  2.0,
            'exchange_rate' : 2.0,
            'muid_presets' : [],
        }                       
        config = System.config.RawConfig(data)
        loader = MockModuleLoader()
        m = main._MarketingService(config, loader)
        queue = loader.queues[0]

        request = test.MockRequest()
        m.CreateMuid(request)
        self.assertEquals(True, request.isDone)
        self.assertEquals(True, None != request.result['muid'])
        muid = request.result['muid']
        self.assertEquals('q', muid)

        request = test.MockRequest()
        m.FirstLogin(request, muid, 444)
        self.assertEquals(True, request.isDone)
        self.assertEquals(0, request.result['ec'])
        self.assertEquals(main.DecodeKey(muid), request.result.get('muid', None))

        request = test.MockRequest()
        m.CastleLogin(request, '444', '0')
        self.assertEquals(0, request.result['ec'])

        self.assertEquals('mymodule', loader.modules[1][0])
        self.assertEquals(1, loader.modules[1][1].clogins[0].clogins)

        request1 = test.MockRequest()
        m.CastleLogin(request1, '444', '0')
        self.assertEquals(0, request.result['ec'])

        self.assertEquals('mymodule', loader.modules[1][0])
        self.assertEquals(2, loader.modules[1][1].clogins[1].clogins)

    def test_NoMuidForAuid(self):
        data = {
            'partners' : {
                'rambler' : {
                    'code' : 'ff',
                    'source' : 'landing'
                },
                'pw' : {
                    'code' : 'ee',
                    'source' : 'copy'
                },
            },
            'modules' : { 'kontagent' : { 'url' : '' }  },
            'db' : tempfile.mktemp(),
            'edb' : tempfile.mktemp(),
            'flush_period' :  2.0,
            'exchange_rate' : 2.0,
            'muid_presets' : [],
        }                       
        config = System.config.RawConfig(data)
        loader = MockModuleLoader()
        m = main._MarketingService(config, loader)
        queue = loader.queues[0]

        request = test.MockRequest()
        m.FirstLogin(request, 'old_muid_xfsr', '444')
        self.assertEquals(True, request.isDone)
        self.assertEquals(0, request.result['ec'])
        self.assertEquals(5, len(queue.requests))
        self.assertEquals('/ucc/?i=0&tu=partner&su=ee000000&s=1&st1=aquisition&st2=pw', queue.requests[0])
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=pw&n=copy', queue.requests[1])
        self.assertEquals('/apa/?s=1&su=ee000000', queue.requests[2])
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=pw&n=first_login', queue.requests[3])
        self.assertEquals('/cpu/?s=1', queue.requests[4])
        queue.Reset()

    def test_NoMuidCreationBeforePartner(self):
        data = {
            'partners' : {
                'rambler' : {
                    'code' : 'ff',
                    'source' : 'landing'
                },
                'pw' : {
                    'code' : 'ee',
                    'source' : 'copy'
                },
            },
            'modules' : { 'kontagent' : { 'url' : '' }  },
            'db' : tempfile.mktemp(),
            'edb' : tempfile.mktemp(),
            'flush_period' :  2.0,
            'exchange_rate' : 2.0,
            'muid_presets' : [],
        }                       
        config = System.config.RawConfig(data)

        loader = MockModuleLoader()
        m = main._MarketingService(config, loader)
        queue = loader.queues[0]

        request = test.MockRequest()
        m.CreateMuid(request)
        self.assertEquals(True, request.isDone)
        self.assertEquals(True, None != request.result['muid'])
        muid = request.result['muid']
        self.assertEquals('q', muid)
        self.assertEquals(True, request.result['new'])

        self.assertEquals(0, len(queue.requests))
        queue.Reset()

    def test_MuidCreationWeekAfter(self):
        data = {
            'partners' : {
                'pw' : {
                    'code' : 'ee',
                    'source' : 'copy'
                },
            },
            'modules' : { 'kontagent' : { 'url' : '' }  },
            'db' : tempfile.mktemp(),
            'edb' : tempfile.mktemp(),
            'flush_period' :  2.0,
            'exchange_rate' : 2.0,
            'expire_muid_period' : 5*3600*24,
            'muid_presets' : [],
        }                       
        config = System.config.RawConfig(data)

        loader = MockModuleLoader()
        m = main._MarketingService(config, loader)
        queue = loader.queues[0]

        request = test.MockRequest()
        m.CreateMuid(request)
        self.assertEquals(True, request.isDone)
        self.assertEquals(True, None != request.result['muid'])
        muid = request.result['muid']
        self.assertEquals('q', muid)
        self.assertEquals(0, len(queue.requests))

        # muid exists in cookie
        request1 = test.MockRequest()
        m.OnReturn(request1, muid)
        muid = request1.result['muid']
        self.assertEquals('q', muid)

        d = datetime.datetime.fromtimestamp(time.time())
        d += datetime.timedelta(seconds = config.expire_muid_period+1)
        self.currentTime = time.mktime(d.timetuple())

        saver = TimeSaver(self.GetTime)

        # muid exists in cookie
        request2 = test.MockRequest()
        m.OnReturn(request2, muid)
        muid = request2.result['muid']
        self.assertEquals('7', muid)
        self.assertEquals(True, request2.result['new'])

    def test_MuidCreationWithBadMuid(self):
        data = {
            'partners' : {
                'pw' : {
                    'code' : 'ee',
                    'source' : 'copy'
                },
            },
            'modules' : { 'kontagent' : { 'url' : '' }  },
            'db' : tempfile.mktemp(),
            'edb' : tempfile.mktemp(),
            'flush_period' :  2.0,
            'exchange_rate' : 2.0,
            'expire_muid_period' : 5*3600*24,
            'muid_presets' : [],
        }                       
        config = System.config.RawConfig(data)

        loader = MockModuleLoader()
        m = main._MarketingService(config, loader)
        queue = loader.queues[0]

        request = test.MockRequest()
        m.CreateMuid(request)
        self.assertEquals(True, request.isDone)
        self.assertEquals(True, None != request.result['muid'])
        muid = request.result['muid']
        self.assertEquals('q', muid)
        self.assertEquals(0, len(queue.requests))

        # muid exists in cookie
        request1 = test.MockRequest()
        m.OnReturn(request1, 'qqqqqqqq')
        self.assertEquals(True, request1.isDone)
        self.assertEquals(0, request1.result['ec'])
        self.assertEquals('7', request1.result['muid'])


    def test_MuidCreationWithAuidLinkedWeekAfter(self):
        data = {
            'partners' : {
                'pw' : {
                    'code' : 'ee',
                    'source' : 'copy'
                },
            },
            'modules' : { 'kontagent' : { 'url' : '' }  },
            'db' : tempfile.mktemp(),
            'edb' : tempfile.mktemp(),
            'flush_period' :  2.0,
            'exchange_rate' : 2.0,
            'expire_muid_period' : 5*3600*24,
            'muid_presets' : [],
        }                       
        config = System.config.RawConfig(data)

        loader = MockModuleLoader()
        m = main._MarketingService(config, loader)
        queue = loader.queues[0]

        request = test.MockRequest()

        # no muid if cookie
        m.CreateMuid(request)
        self.assertEquals(True, request.isDone)
        self.assertEquals(True, None != request.result['muid'])
        muid = request.result['muid']
        self.assertEquals('q', muid)

        request1 = test.MockRequest()
        m.FirstLogin(request1, muid, 555)

        d = datetime.datetime.fromtimestamp(time.time())
        d += datetime.timedelta(seconds = config.expire_muid_period+1)
        self.currentTime = time.mktime(d.timetuple())

        saver = TimeSaver(self.GetTime)

        # muid exists in cookie
        request2 = test.MockRequest()
        m.OnReturn(request2, muid)
        muid = request2.result['muid']
        self.assertEquals('q', muid)
        self.assertEquals(None, request2.result.get('new', None))

    def test_AuidMuidLinkageAfterAuidExclusiveCalls(self):
        data = {
            'partners' : {
                'pw' : {
                    'code' : 'ee',
                    'source' : 'copy'
                },
            },
            'modules' : { 'kontagent' : { 'url' : '' }  },
            'db' : tempfile.mktemp(),
            'edb' : tempfile.mktemp(),
            'flush_period' :  2.0,
            'exchange_rate' : 2.0,
            'expire_muid_period' : 5*3600*24,
            'muid_presets' : [],
        }                       
        config = System.config.RawConfig(data)

        loader = MockModuleLoader()
        m = main._MarketingService(config, loader)
        queue = loader.queues[0]

        request = test.MockRequest()
        m.CreateMuid(request)
        self.assertEquals(True, request.isDone)
        self.assertEquals(True, None != request.result['muid'])
        muid = request.result['muid']
        self.assertEquals('q', muid)

        request = test.MockRequest()
        m.SessionStart(request, '555', '0', '1', '5', 'fox', 'True')
        self.assertEquals(True, request.isDone)
        self.assertEquals(main.NO_MUID, request.result['ec'])

        queue = loader.queues[0]
        self.assertEquals(0, len(queue.requests))

        request = test.MockRequest()
        m.FirstLogin(request, muid, 555)
        self.assertEquals(True, request.isDone)
        self.assertEquals(0, request.result['ec'])
        self.assertEquals(main.DecodeKey(muid), request.result.get('muid', None))

        self.assertEquals(7, len(queue.requests))
        self.assertEquals('/ucc/?i=0&tu=partner&su=ee000000&s=1&st1=aquisition&st2=pw', queue.requests[0])
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=pw&n=copy', queue.requests[1])
        self.assertEquals('/apa/?s=1&su=ee000000', queue.requests[2])
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=pw&n=first_login', queue.requests[3])
        self.assertEquals('/cpu/?s=1', queue.requests[4])

        self.assertEquals('/evt/?s=1&st1=aquisition&st2=pw&n=first_session_pvp', queue.requests[5]) 
        self.assertEquals('/evt/?s=1&st3=fox&st1=session&st2=docts&n=session_start_pvp', queue.requests[6])

    def GetTime(self):
        return self.currentTime

    def test_FirstLoginWithNoMuid(self):
        data = {
            'partners' : {
                'rambler' : {
                    'code' : 'ff',
                    'source' : 'landing'
                },
                'pw' : {
                    'code' : 'ee',
                    'source' : 'copy'
                },
            },
            'modules' : { 'kontagent' : { 'url' : '' } },
            'db' : tempfile.mktemp(),
            'edb' : tempfile.mktemp(),
            'flush_period' :  2.0,
            'exchange_rate' : 2.0,
            'muid_presets' : [],
        }                       
        config = System.config.RawConfig(data)
        loader = MockModuleLoader()
        m = main._MarketingService(config, loader)
        queue = loader.queues[0]

        request = test.MockRequest()
        m.CreateMuid(request)
        self.assertEquals(True, request.isDone)
        self.assertEquals(True, None != request.result['muid'])
        muid = request.result['muid']
        self.assertEquals('q', muid)

        request = test.MockRequest()
        m.CastleLogin(request, '444', '0')
        self.assertEquals(True, request.isDone)
        self.assertEquals(main.NO_MUID, request.result['ec'])
        self.assertEquals(0, len(queue.requests))

        request = test.MockRequest()
        m.FirstLogin(request, muid, 444)
        self.assertEquals(True, request.isDone)
        self.assertEquals(0, request.result['ec'])
        self.assertEquals(main.DecodeKey(muid), request.result.get('muid', None))

        self.assertEquals(7, len(queue.requests))
        self.assertEquals('/ucc/?i=0&tu=partner&su=ee000000&s=1&st1=aquisition&st2=pw', queue.requests[0])
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=pw&n=copy', queue.requests[1])
        self.assertEquals('/apa/?s=1&su=ee000000', queue.requests[2])
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=pw&n=first_login', queue.requests[3])
        self.assertEquals('/cpu/?s=1', queue.requests[4])

        self.assertEquals('/evt/?s=1&st1=aquisition&st2=pw&n=first_castle', queue.requests[5])
        self.assertEquals('/evt/?s=1&st1=login&st2=docts&n=castle_login', queue.requests[6])


    def test_SelectFactionWithNoMuid(self):
        data = {
            'partners' : {
                'rambler' : {
                    'code' : 'ff',
                    'source' : 'landing'
                },
                'pw' : {
                    'code' : 'ee',
                    'source' : 'copy'
                },
            },
            'modules' : { 'kontagent' : { 'url' : '' } },
            'db' : tempfile.mktemp(),
            'edb' : tempfile.mktemp(),
            'flush_period' :  2.0,
            'exchange_rate' : 2.0,
            'muid_presets' : [],
        }                       
        config = System.config.RawConfig(data)

        loader = MockModuleLoader()
        m = main._MarketingService(config, loader)
        queue = loader.queues[0]

        request = test.MockRequest()
        m.SelectFaction(request, '444', '0')
        self.assertEquals(True, request.isDone)
        self.assertEquals(main.NO_MUID, request.result['ec'])

        request = test.MockRequest()
        m.FirstLogin(request, None, 444)
        self.assertEquals(True, request.isDone)
        self.assertEquals(0, request.result['ec'])
        muid = request.result['muid']
        self.assertEquals(1, muid)

        self.assertEquals(6, len(queue.requests))
        self.assertEquals('/ucc/?i=0&tu=partner&su=ee000000&s=1&st1=aquisition&st2=pw', queue.requests[0])
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=pw&n=copy', queue.requests[1])
        self.assertEquals('/apa/?s=1&su=ee000000', queue.requests[2])
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=pw&n=first_login', queue.requests[3])
        self.assertEquals('/cpu/?s=1', queue.requests[4])

        self.assertEquals('/evt/?s=1&st1=aquisition&st2=pw&n=faction_selected', queue.requests[5])

    def test_RuTracker(self):
        data = {
            'partners' : {
                'rut' : {
                    'code' : 'aa',
                    'source' : 'torrent'
                },
                'rambler' : {
                    'code' : 'ff',
                    'source' : 'landing'
                },
                'pw' : {
                    'code' : 'ee',
                    'source' : 'copy'
                },
            },
            'modules' : { 'kontagent' : { 'url' : '' }  },
            'db' : tempfile.mktemp(),
            'edb' : tempfile.mktemp(),
            'flush_period' :  2.0,
            'exchange_rate' : 2.0,
            'muid_presets' : [],
        }                       
        config = System.config.RawConfig(data)
        loader = MockModuleLoader()
        m = main._MarketingService(config, loader)
        queue = loader.queues[0]

        request = test.MockRequest()
        m.FirstLogin(request, 'PrimeWorld_rutracker', '444')
        self.assertEquals(5, len(queue.requests))
        self.assertEquals('/ucc/?i=0&tu=partner&su=aa000000&s=1&st1=aquisition&st2=rut', queue.requests[0])
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=rut&n=torrent', queue.requests[1])
        self.assertEquals('/apa/?s=1&su=aa000000', queue.requests[2])
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=rut&n=first_login', queue.requests[3])
        self.assertEquals('/cpu/?s=1', queue.requests[4])
        queue.Reset()

    def test_LandingLogin(self):
        data = {
            'partners' : {
                'rut' : {
                    'code' : 'aa',
                    'source' : 'torrent'
                },
                'rambler' : {
                    'code' : 'ff',
                    'source' : 'landing'
                },
                'pw' : {
                    'code' : 'ee',
                    'source' : 'copy'
                },
            },
            'modules' : { 'kontagent' : { 'url' : '' }  },
            'db' : tempfile.mktemp(),
            'edb' : tempfile.mktemp(),
            'flush_period' :  2.0,
            'exchange_rate' : 2.0,
            'muid_presets' : [],
        }                       
        config = System.config.RawConfig(data)
        loader = MockModuleLoader()
        m = main._MarketingService(config, loader)
        queue = loader.queues[0]

        request = test.MockRequest()            
        m.LandingLogin(request, 'PrimeWorld_rutracker', '444')
        self.assertEquals(2, len(queue.requests))
        self.assertEquals('/ucc/?i=0&tu=partner&su=aa000000&s=1&st1=aquisition&st2=rut', queue.requests[0])
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=rut&n=torrent', queue.requests[1])
        queue.Reset()

    def test_PageView(self):
        data = {
            'partners' : {
                'rut' : {
                    'code' : 'aa',
                    'source' : 'torrent'
                },
                'rambler' : {
                    'code' : 'ff',
                    'source' : 'landing'
                },
                'pw' : {
                    'code' : 'ee',
                    'source' : 'copy'
                },
            },
            'modules' : { 'kontagent' : { 'url' : '' }  },
            'db' : tempfile.mktemp(),
            'edb' : tempfile.mktemp(),
            'flush_period' :  2.0,
            'exchange_rate' : 2.0,
            'muid_presets' : [],
        }                       
        config = System.config.RawConfig(data)
        loader = MockModuleLoader()
        m = main._MarketingService(config, loader)
        queue = loader.queues[0]

        request = test.MockRequest()
        m.CreateMuid(request)
        self.assertEquals(True, request.isDone)
        self.assertEquals(True, None != request.result['muid'])
        muid = request.result['muid']
        self.assertEquals('q', muid)

        queue.Reset()

        s = TimeSaver(self.Time)    
        m.OnPageView(muid, '127.0.0.1')
        self.assertEquals(1, len(queue.requests))
        self.assertEquals('/pgr/?ip=127.0.0.1&s=1&ts=555', queue.requests[0])

    def Time(self): 
        return 555

    def test_SessionStart(self):
        data = {
            'partners' : {
                'rut' : {
                    'code' : 'aa',
                    'source' : 'torrent',
                },
                'rambler' : {
                    'code' : 'ff',
                    'source' : 'landing',
                },
                'pw' : {
                    'code' : 'ee',
                    'source' : 'copy',
                },
            },
            'modules' : { 'kontagent' : { 'url' : '' }  },
            'db' : tempfile.mktemp(),
            'edb' : tempfile.mktemp(),
            'flush_period' :  2.0,
            'exchange_rate' : 2.0,
            'muid_presets' : [],
        }                       
        config = System.config.RawConfig(data)
        loader = MockModuleLoader()
        m = main._MarketingService(config, loader)
        queue = loader.queues[0]

        request = test.MockRequest()
        m.CreateMuid(request)
        self.assertEquals(True, request.isDone)
        self.assertEquals(True, None != request.result['muid'])
        muid = request.result['muid']
        self.assertEquals('q', muid)

        request = test.MockRequest()
        m.FirstLogin(request, muid, 444)
        self.assertEquals(True, request.isDone)
        self.assertEquals(0, request.result['ec'])
        muid = request.result['muid']
        self.assertEquals(1, muid)
        queue.Reset()

        request = test.MockRequest()
        m.SessionStart(request, '444', '0', '1', '5', 'fox', 'True')
        self.assertEquals(True, request.isDone)
        self.assertEquals(0, request.result['ec'])
        self.assertEquals(True, None == request.result.get('muid', None))
        self.assertEquals(2, len(queue.requests))

        self.assertEquals('/evt/?s=1&st1=aquisition&st2=pw&n=first_session_pvp', queue.requests[0]) 
        self.assertEquals('/evt/?s=1&st3=fox&st1=session&st2=docts&n=session_start_pvp', queue.requests[1])
        
        queue.Reset()

        s = TimeSaver(self.Time)    
        m.OnPageView('q')
        self.assertEquals(1, len(queue.requests))
        self.assertEquals('/pgr/?s=1&ts=555', queue.requests[0])

    def _prepare_test(self, cfg_data=None):
        data = {
            'partners' : {
                'pw' : {
                    'code' : 'ee',
                    'source' : 'copy',
                },
            },
            'modules' : { 'kontagent' : { 'url' : '' }, 'zx' : {}  },
            'db' : tempfile.mktemp(),
            'edb' : tempfile.mktemp(),
            'flush_period' :  2.0,
            'exchange_rate' : 2.0,
            'muid_presets' : [],
            'id_tutorial' : ['34'],
        }
        if cfg_data:
            data.upadte(cfg_data)
        config = System.config.RawConfig(data)
        loader = MockModuleLoader()
        m = main._MarketingService(config, loader)
        queue = loader.queues[0]

        request = test.MockRequest()
        m.CreateMuid(request)
        self.assertEquals(True, request.isDone)
        self.assertEquals(True, None != request.result['muid'])
        muid = request.result['muid']
        self.assertEquals('q', muid)
        self.assertEquals(0, len(queue.requests))

        request = test.MockRequest()
        auid = '777'
        m.FirstLogin(request, muid, auid)

        return (loader, m, queue, auid)

    def test_Quest(self):
        loader, m, queue, auid = self._prepare_test()

        self.assertEquals(5, len(queue.requests))
        self.assertEquals('/ucc/?i=0&tu=partner&su=ee000000&s=1&st1=aquisition&st2=pw', queue.requests[0])
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=pw&n=copy', queue.requests[1])
        self.assertEquals('/apa/?s=1&su=ee000000', queue.requests[2])
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=pw&n=first_login', queue.requests[3])
        self.assertEquals('/cpu/?s=1', queue.requests[4])
        queue.Reset()

        request = test.MockRequest()
        m.ProcessQuest(request, auid, '34', '0')

        self.assertEquals(0, len(queue.requests))
        self.assertEquals( ('34', '0', None), loader.modules[1][1].quests[0][1:])        


    def test_HeroLevel(self):
        loader, m, queue, auid = self._prepare_test()
        queue.Reset()

        request = test.MockRequest()
        m.ProcessHeroLevel(request, auid, '1', '5')

        self.assertEquals(0, len(queue.requests))
        self.assertEquals(('1', '5', None), loader.modules[1][1].hlevels[0][1:])


    def test_HeroRank(self):
        loader, m, queue, auid = self._prepare_test()
        queue.Reset()

        request = test.MockRequest()
        m.ProcessHeroRank(request, auid, '1', '5', '3', '1')

        self.assertEquals(0, len(queue.requests))
        self.assertEquals(('1', '5', '3', 1, None), loader.modules[1][1].hranks[0][1:])


    def test_CastleLevel(self):
        loader, m, queue, auid = self._prepare_test()
        queue.Reset()

        request = test.MockRequest()
        m.ProcessCastleLevel(request, auid, '30')

        self.assertEquals(0, len(queue.requests))
        self.assertEquals(('30', None), loader.modules[1][1].clevels[0][1:])


    def test_Simple(self):
        data = {
            'partners' : {
                'rambler' : {
                    'code' : 'ff',
                    'source' : 'landing'
                },
                'pw' : {
                    'code' : 'ee',
                    'source' : 'copy',
                },
            },
            'modules' : { 'kontagent' : { 'url' : '' }  },
            'db' : tempfile.mktemp(),
            'edb' : tempfile.mktemp(),
            'flush_period' :  2.0,
            'exchange_rate' : 2.0,
            'muid_presets' : [],
        }                       
        config = System.config.RawConfig(data)
        loader = MockModuleLoader()
        m = main._MarketingService(config, loader)
        queue = loader.queues[0]

        request = test.MockRequest()
        m.CreateMuid(request)
        self.assertEquals(True, request.isDone)
        self.assertEquals(True, None != request.result['muid'])
        muid = request.result['muid']
        self.assertEquals('q', muid)
        self.assertEquals(0, len(queue.requests))

        request = test.MockRequest()
        m.LinkPartner(request, muid, 'rambler')
        self.assertEquals(True, request.isDone)
        # TODO: check result
        self.assertEquals(2, len(queue.requests))
        self.assertEquals('/ucc/?i=0&tu=partner&su=ff000000&s=1&st1=aquisition&st2=rambler', queue.requests[0])
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=rambler&n=landing', queue.requests[1])
        queue.Reset()

        request = test.MockRequest()
        m.BeginDownload(request, muid)
        self.assertEquals(1, len(queue.requests))
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=rambler&n=begin_download', queue.requests[0])
        queue.Reset()

        request = test.MockRequest()
        m.LaunchInstall(request, muid)
        self.assertEquals(1, len(queue.requests))
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=rambler&n=launch_install', queue.requests[0])
        queue.Reset() 
        
        request = test.MockRequest()
        m.BeginInstall(request, muid)
        self.assertEquals(1, len(queue.requests))
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=rambler&n=begin_install', queue.requests[0])
        queue.Reset()

        request = test.MockRequest()
        m.EndInstall(request, muid)
        self.assertEquals(1, len(queue.requests))
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=rambler&n=end_install', queue.requests[0])
        queue.Reset()

        request = test.MockRequest()
        m.CancelInstall(request, muid)
        self.assertEquals(1, len(queue.requests))
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=rambler&n=cancel_install', queue.requests[0])
        queue.Reset()       
        
        request = test.MockRequest()
        m.FirstLogin(request, muid, '444')
        self.assertEquals(3, len(queue.requests))
        self.assertEquals('/apa/?s=1&su=ff000000', queue.requests[0])
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=rambler&n=first_login', queue.requests[1])
        self.assertEquals('/cpu/?s=1', queue.requests[2])
        queue.Reset()

        request = test.MockRequest()
        m.DownloadClientBegin(request, '444')
        self.assertEquals(1, len(queue.requests))
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=rambler&n=download_client_begin', queue.requests[0])
        queue.Reset()

        request = test.MockRequest()
        m.DownloadClientEnd(request, '444')
        self.assertEquals(1, len(queue.requests))
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=rambler&n=download_client_end', queue.requests[0])
        queue.Reset()

        request = test.MockRequest()
        m.SelectFaction(request, '444', '0')
        self.assertEquals(1, len(queue.requests))
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=rambler&n=faction_selected', queue.requests[0])
        queue.Reset()

        request = test.MockRequest()
        m.CastleLogin(request, '444', '0')
        self.assertEquals(2, len(queue.requests))
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=rambler&n=first_castle', queue.requests[0])
        self.assertEquals('/evt/?s=1&st1=login&st2=docts&n=castle_login', queue.requests[1])
        queue.Reset()

        request = test.MockRequest()
        m.CastleLogin(request, '444', '0')
        self.assertEquals(1, len(queue.requests))
        self.assertEquals('/evt/?s=1&st1=login&st2=docts&n=castle_login', queue.requests[0])
        queue.Reset()

        request = test.MockRequest()
        m.SessionStart(request, '444', '0', '1', '5', 'fox', 'True')
        self.assertEquals(2, len(queue.requests))
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=rambler&n=first_session_pvp', queue.requests[0])
        self.assertEquals('/evt/?s=1&st3=fox&st1=session&st2=docts&n=session_start_pvp', queue.requests[1])
        queue.Reset()

        request = test.MockRequest()
        m.SessionStart(request, '444', '0', '0', '5', 'fox', 'False')
        self.assertEquals(2, len(queue.requests))
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=rambler&n=first_session_training', queue.requests[0])
        self.assertEquals('/evt/?s=1&st3=fox&st1=session&st2=docts&n=session_start_training', queue.requests[1])
        queue.Reset()

        request = test.MockRequest()
        m.SessionStart(request, '444', '1', '0', '5', 'fox','False')
        self.assertEquals(1, len(queue.requests))
        self.assertEquals('/evt/?s=1&st3=fox&st1=session&st2=adornians&n=session_start_training', queue.requests[0])
        queue.Reset()

        request = test.MockRequest()
        m.SessionStart(request, '444', '1', '0', None, None, 'False')
        self.assertEquals(1, len(queue.requests))
        self.assertEquals('/evt/?s=1&st1=session&st2=adornians&n=session_start_training', queue.requests[0])
        queue.Reset()

        request = test.MockRequest()
        m.SessionStart(request, '444', '1', '1', '5', 'fox', 'True')
        self.assertEquals(1, len(queue.requests))
        self.assertEquals('/evt/?s=1&st3=fox&st1=session&st2=adornians&n=session_start_pvp', queue.requests[0])
        queue.Reset()

        request = test.MockRequest()
        m.SessionStart(request, '444', '1', '1', '5', 'fox', 'False')
        self.assertEquals(1, len(queue.requests))
        self.assertEquals('/evt/?s=1&st3=fox&st1=session&st2=adornians&n=session_start_training', queue.requests[0])
        queue.Reset()

        request = test.MockRequest()
        m.MakePayment(request, 'ruopr_444', 100, 'yandex')
        self.assertEquals(4, len(queue.requests))

        self.assertEquals('/mtu/?s=1&st1=yandex&v=200', queue.requests[0])
        self.assertEquals('/evt/?s=1&v=200&st1=aquisition&st2=rambler&n=payment_yandex', queue.requests[1])
        self.assertEquals('/evt/?s=1&st1=resources&st2=gold&st3=gold_income&v=100&n=yandex', queue.requests[2])
        self.assertEquals('/evt/?s=1&v=0&st1=resources&st2=gold&n=gold_amount', queue.requests[3])
        queue.Reset()

        request = test.MockRequest()
        m.ChangeResource(request, '444', 'hero_unlock', 'false', '0', '300', '0', '0', '0', '0')
        self.assertEquals(2, len(queue.requests))

        self.assertEquals('/evt/?s=1&st1=aquisition&st2=rambler&n=first_spend', queue.requests[0])
        self.assertEquals('/evt/?s=1&st1=resources&st2=silver&st3=silver_spend&v=300&n=hero_unlock', queue.requests[1])
        queue.Reset()

        request = test.MockRequest()
        m.ChangeResource(request, '444', 'hero_unlock', 'true', '0', '300', '0', '0', '0', '0')
        self.assertEquals(1, len(queue.requests))

        self.assertEquals('/evt/?s=1&st1=resources&st2=silver&st3=silver_income&v=300&n=hero_unlock', queue.requests[0])
        queue.Reset()

        self.checkResource(queue, m, 'Building_Work', 'gold', 100)
        self.checkResource(queue, m, 'Unsoulbound', 'perl', 120)
        self.checkResource(queue, m, 'TalentSell', 'resource1', 1202)
        self.checkResource(queue, m, 'FinishProduction', 'resource2', 1233)
        self.checkResource(queue, m, 'BuildingSell', 'resource3', 125)

        self.checkResource(queue, m, 'Building_Work', 'gold', -100)
        self.checkResource(queue, m, 'Unsoulbound', 'perl', -120)
        self.checkResource(queue, m, 'TalentSell', 'resource1', -1202)
        self.checkResource(queue, m, 'FinishProduction', 'resource2', -1233)
        self.checkResource(queue, m, 'BuildingSell', 'resource3', -125)

    def checkResource(self, queue, m, source, resource, amount):
        resources = ['gold', 'silver', 'perl', 'resource1', 'resource2', 'resource3']
        index = resources.index(resource)
        request = test.MockRequest()
        params = ['0']*len(resources)
        params[index] = str(amount)
        m.ChangeResource(request, '444', source, 'true', *params)
        self.assertEquals(1, len(queue.requests))
        self.assertEquals('/evt/?s=1&st1=resources&st2=%s&st3=%s_income&v=%d&n=%s' % (resource, resource, amount, source), queue.requests[0])
        queue.Reset()

    def test_LoginFromLauncher(self):
        data = {
            'partners' : {
                'rambler' : {
                    'code' : 'ff',
                    'source' : 'landing'
                },
                'pw' : {
                    'code' : 'ee',
                    'source' : 'copy'
                },
            },
            'modules' : { 'kontagent' : { 'url' : '' }  },
            'db' : tempfile.mktemp(),
            'edb' : tempfile.mktemp(),
            'flush_period' :  2.0,
            'exchange_rate' : 2.0,
            'muid_presets' : [],
        }                       
        config = System.config.RawConfig(data)
        loader = MockModuleLoader()
        m = main._MarketingService(config, loader)
        queue = loader.queues[0]

        for i in range(100):
            request = test.MockRequest()
            m.CreateMuid(request)
            muid = request.result['muid']

            request = test.MockRequest()
            m.LinkPartner(request, muid, 'rambler')
            self.assertEquals(True, request.isDone)

        queue.Reset()

        request = test.MockRequest()
        m.CreateMuid(request)
        self.assertEquals(True, request.isDone)
        self.assertEquals(True, None != request.result['muid'])
        muid = request.result['muid']
        self.assertEquals('kz', muid)

        request = test.MockRequest()
        m.LinkPartner(request, muid, 'rambler')
        self.assertEquals(True, request.isDone)

        muid = 'PWSetup_'+muid

        self.assertEquals(2, len(queue.requests))
        self.assertEquals('/ucc/?i=0&tu=partner&su=ff000064&s=101&st1=aquisition&st2=rambler', queue.requests[0])
        self.assertEquals('/evt/?s=101&st1=aquisition&st2=rambler&n=landing', queue.requests[1])
        queue.Reset()

        request = test.MockRequest()
        m.BeginDownload(request, muid)
        self.assertEquals(1, len(queue.requests))
        self.assertEquals('/evt/?s=101&st1=aquisition&st2=rambler&n=begin_download', queue.requests[0])
        queue.Reset()

        request = test.MockRequest()
        m.BeginInstall(request, muid)
        self.assertEquals(1, len(queue.requests))
        self.assertEquals('/evt/?s=101&st1=aquisition&st2=rambler&n=begin_install', queue.requests[0])
        queue.Reset()

        request = test.MockRequest()
        m.EndInstall(request, muid)
        self.assertEquals(1, len(queue.requests))
        self.assertEquals('/evt/?s=101&st1=aquisition&st2=rambler&n=end_install', queue.requests[0])
        queue.Reset()

        request = test.MockRequest()
        m.FirstLogin(request, muid, '444')
        self.assertEquals(3, len(queue.requests))
        self.assertEquals('/apa/?s=101&su=ff000064', queue.requests[0])
        self.assertEquals('/evt/?s=101&st1=aquisition&st2=rambler&n=first_login', queue.requests[1])
        self.assertEquals('/cpu/?s=101', queue.requests[2])
        queue.Reset()

    def test_LoginFromLauncherWithZzimaLauncher(self):
        data = {
            'partners' : {
                'rambler' : {
                    'code' : 'ff',
                    'source' : 'landing'
                },
                'pw' : {
                    'code' : 'ee',
                    'source' : 'landing'
                },
                'zzima' : {
                    'code' : 'ec',
                    'source' : 'zzima'
                },
            },
            'modules' : { 'kontagent' : { 'url' : '' }  },
            'db' : tempfile.mktemp(),
            'edb' : tempfile.mktemp(),
            'flush_period' :  2.0,
            'exchange_rate' : 2.0,
            'muid_presets' : ['zzima'],
        }                       
        config = System.config.RawConfig(data)
        loader = MockModuleLoader()
        m = main._MarketingService(config, loader)
        queue = loader.queues[0]

        muid = "PWSetup_zzima"

        request = test.MockRequest()
        m.FirstLogin(request, muid, '444')
        self.assertEquals(5, len(queue.requests))
        self.assertEquals('/ucc/?i=0&tu=partner&su=ec000000&s=1&st1=aquisition&st2=zzima', queue.requests[0])
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=zzima&n=zzima', queue.requests[1])
        self.assertEquals('/apa/?s=1&su=ec000000', queue.requests[2])
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=zzima&n=first_login', queue.requests[3])
        self.assertEquals('/cpu/?s=1', queue.requests[4])

    def test_SecondUser(self):
        data = {
            'partners' : {
                'rambler' : {
                    'code' : 'ff',
                    'source' : 'landing'
                },
                'pw' : {
                    'code' : 'ee',
                    'source' : 'copy'
                },
            },
            'modules' : { 'kontagent' : { 'url' : '' }  },
            'db' : tempfile.mktemp(),
            'edb' : tempfile.mktemp(),
            'flush_period' :  2.0,
            'exchange_rate' : 2.0,
            'muid_presets' : [],
        }                       
        config = System.config.RawConfig(data)
        loader = MockModuleLoader()
        m = main._MarketingService(config, loader)
        queue = loader.queues[0]

        request = test.MockRequest()
        m.CreateMuid(request)
        self.assertEquals(True, request.isDone)
        self.assertEquals(True, None != request.result['muid'])
        muid = request.result['muid']

        request = test.MockRequest()
        m.LinkPartner(request, muid, 'rambler')
        self.assertEquals(True, request.isDone)

        self.assertEquals(2, len(queue.requests))
        self.assertEquals('/ucc/?i=0&tu=partner&su=ff000000&s=1&st1=aquisition&st2=rambler', queue.requests[0])
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=rambler&n=landing', queue.requests[1])
        queue.Reset()

        request = test.MockRequest()
        m.FirstLogin(request, muid, '444')
        self.assertEquals(3, len(queue.requests))
        self.assertEquals('/apa/?s=1&su=ff000000', queue.requests[0])
        self.assertEquals('/evt/?s=1&st1=aquisition&st2=rambler&n=first_login', queue.requests[1])
        self.assertEquals('/cpu/?s=1', queue.requests[2])
        queue.Reset()

        request = test.MockRequest()
        m.CreateMuid(request)
        self.assertEquals(True, request.isDone)
        self.assertEquals(True, None != request.result['muid'])
        muid = request.result['muid']

        request = test.MockRequest()
        m.LinkPartner(request, muid, 'rambler', '234')
        self.assertEquals(True, request.isDone)

        self.assertEquals(2, len(queue.requests))
        self.assertEquals('/ucc/?i=0&tu=partner&su=ff000001&s=2&st1=aquisition&st2=rambler&st3=234', queue.requests[0])
        self.assertEquals('/evt/?s=2&st3=234&st1=aquisition&st2=rambler&n=landing', queue.requests[1])
        queue.Reset()

        request = test.MockRequest()
        m.FirstLogin(request, muid, '555')
        self.assertEquals(3, len(queue.requests))
        self.assertEquals('/apa/?s=2&su=ff000001', queue.requests[0])
        self.assertEquals('/evt/?s=2&st3=234&st1=aquisition&st2=rambler&n=first_login', queue.requests[1])
        self.assertEquals('/cpu/?s=2', queue.requests[2])
        queue.Reset()

    def test_MuidChange(self):
        pass

    def test_BadFraction(self):
        pass

    def test_BadGain(self):
        pass

import tempfile

import ShelveDb
class Test_PersistentQueue(unittest.TestCase):

    def test_Simple(self):
        http_client = test.MockHttpClient()
        class Config:
            db_path = tempfile.mkdtemp()
            request_rate = 10
            flush_period = 10
            start_request_rate = 10
            rate_period = 10
        queue = main.PersistentQueue(http_client, Config, os.path.join(Config.db_path, 'xxx.db'))
        queue.Push('evt/?s=1')
        self.assertEquals(1, len(http_client.requests))
        self.assertEquals('evt/?s=1', http_client.requests[0].request)
        http_client.requests[0].Set('1')
        http_client.Execute()

        queue.Update()
        self.assertEquals(0, len(http_client.requests))

    def test_SecondSend(self):
        http_client = test.MockHttpClient()
        class Config:
            db_path = tempfile.mkdtemp()
            request_rate = 10
            flush_period = 10
            start_request_rate = 10
            rate_period = 10
        queue = main.PersistentQueue(http_client, Config, os.path.join(Config.db_path, 'xxx.db'))
        queue.Push('evt/?s=1')
        self.assertEquals(1, len(http_client.requests))
        self.assertEquals('evt/?s=1', http_client.requests[0].request)

        queue.Update()
        self.assertEquals(1, len(http_client.requests))
        http_client.requests[0].Set(None, 'error')
        http_client.Execute()

        queue.Update()
        self.assertEquals(1, len(http_client.requests))
        self.assertEquals('evt/?s=1', http_client.requests[0].request)

        queue.Update()
        self.assertEquals(1, len(http_client.requests))
        http_client.requests[0].Set('1')
        http_client.Execute()

        queue.Update()
        self.assertEquals(0, len(http_client.requests))

    def test_Persistent(self):
        http_client = test.MockHttpClient()
        class Config:
            db_path = tempfile.mkdtemp()
            request_rate = 10
            flush_period = 10
            start_request_rate = 10
            rate_period = 10
        config = Config()

        queue = main.PersistentQueue(http_client, config, os.path.join(Config.db_path, 'xxx.db'))
        queue.Push('evt/?s=1')
        self.assertEquals(1, len(http_client.requests))
        self.assertEquals('evt/?s=1', http_client.requests[0].request)

        del queue
        http_client.Clear()
        queue = main.PersistentQueue(http_client, config, os.path.join(Config.db_path, 'xxx.db'))

        self.assertEquals(0, len(http_client.requests))
        queue.Update()  

        self.assertEquals('evt/?s=1', http_client.requests[0].request)


    def test_PersistentBadUrl(self):
        http_client = test.MockHttpClient()
        class Config:
            db_path = tempfile.mkdtemp()
            request_rate = 10
            flush_period = 10
            start_request_rate = 10
            rate_period = 10
        config = Config()

        queue = main.PersistentQueue(http_client, config, os.path.join(Config.db_path, 'xxx.db'))
        self.assertEquals(False, queue.Push('evt/?s=1 fuck'))
        self.assertEquals(0, len(http_client.requests))

class Test_Callback(unittest.TestCase):

    class MyCallback:

        def __init__(self):
            self.isCalled = False

        def __call__(self, request, user, auid, faction):
            self.isCalled = True
            self.request = request
            self.user = user
            self.auid = auid
            self.faction = faction

    def test_Simple(self):
        request = test.MockRequest()

        cb = Test_Callback.MyCallback()
        c = main.UserCallback(cb, request, auid=444, faction=0)
        c('user')
        self.assertEquals(request, cb.request)
        self.assertEquals('user', cb.user)
        self.assertEquals(444, cb.auid)
        self.assertEquals(0, cb.faction)

    def test_Fail(self):
        request = test.MockRequest()

        cb = Test_Callback.MyCallback()
        c = main.UserCallback(cb, request, auid=444, faction=0)
        c(None)
        self.assertEquals(False, cb.isCalled)

class Test_Key(unittest.TestCase):
    
    def test_Simple(self):
        self.assertEquals('b', main.EncodeKey(0))
        self.assertEquals('8', main.EncodeKey(29))
        self.assertEquals('bq', main.EncodeKey(30))
        self.assertEquals('fv', main.EncodeKey(255))
        self.assertEquals('b25d', main.EncodeKey(255000))
        self.assertEquals('74h6vj5gnh', main.EncodeKey(255123131312312))
        self.assertEquals(30, main.DecodeKey('bq'))
        self.assertEquals(29, main.DecodeKey('8'))
        self.assertEquals(0, main.DecodeKey('b'))
        self.assertEquals(255, main.DecodeKey('fv'))
        self.assertEquals(255000, main.DecodeKey('b25d'))
        self.assertEquals(255123131312312, main.DecodeKey('74h6vj5gnh'))
        self.assertEquals('x9jnj', main.EncodeKey(4000098))
        self.assertEquals(3987566, main.DecodeKey('wxt1j'))
        self.assertEquals('zgznj', main.EncodeKey(3999453))
        self.assertEquals('zkf1j', main.EncodeKey(3982833))

class MockDatabase:

    def __init__(self):
        self.items = {}
        self.isDirty = False

    def __getitem__(self, key):
        return self.items.get(key, None)

    def __setitem__(self, key, value):
        self.items[key] = value

    def __delitem__(self, key):
        del self.items[key]

    def has_key(self, key):
        return self.items.has_key(key)

    def get(self, key, default=None):
        return self.items.get(key, default)

class Test_PersistentEvents(unittest.TestCase):

    def test_Simple(self):
        db = MockDatabase()
        pq = ShelveDb.PersistentEventsQueue(db)
        pq.Push(555, { 'faction' : 0, 'etype' : 'SelectFaction' })
        queue = pq.Retrieve(555)
        self.assertEquals(1, len(queue))
        self.assertEquals('SelectFaction', queue[0]['etype'])
        self.assertEquals(0, queue[0]['faction'])

        pq.Clear(555)
        queue = pq.Retrieve(555)
        self.assertEquals(0, len(queue))

    def test_Two(self):
        db = MockDatabase()
        pq = ShelveDb.PersistentEventsQueue(db)
        pq.Push(777, { 'faction' : 0, 'etype' : 'SelectFaction' })
        pq.Push(777, { 'quid' : 550, 'status' : 2, 'tm' : 13231231, 'etype' : 'ProcessQuest' })
        queue = pq.Retrieve(777)
        self.assertEquals(2, len(queue))
        self.assertEquals('SelectFaction', queue[0]['etype'])
        self.assertEquals(0, queue[0]['faction'])
        self.assertEquals('ProcessQuest', queue[1]['etype'])
        self.assertEquals(550, queue[1]['quid'])
        self.assertEquals(2, queue[1]['status'])
        self.assertEquals(13231231, queue[1]['tm'])
        pq.Clear(777)
        queue = pq.Retrieve(777)
        self.assertEquals(0, len(queue))

class Test_ParseAuid(unittest.TestCase):

    def test_Simple(self):
        self.assertEquals('345', main.ParseAuidFromUser('opr_345'))
        self.assertEquals('345', main.ParseAuidFromUser('345'))
        self.assertEquals(None, main.ParseAuidFromUser('abcd'))
        

if __name__ == '__main__':
    verbose = '--verbose' in sys.argv
    if verbose:
        System.logs.setup(None, 'debug')
    else:
        System.logs.setup(None, 'critical')
    import logging
    unittest.main()

