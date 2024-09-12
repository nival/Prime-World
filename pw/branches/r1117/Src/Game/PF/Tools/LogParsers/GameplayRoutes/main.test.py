import unittest

import main

class TestGen(unittest.TestCase):

    def Run(self, users, relogin=True, matchmaking=False):
        class User:

            def __init__(self, auid, events):
                self.events = events
                self.auid = auid
                
        lusers = []
        for index, events in enumerate(users):
            lusers.append(User(index+1, events))

        options = main.Options()
        options.relogin = relogin
        options.matchmaking = matchmaking
        graph = main.Graph()
        context = main.SimpleContext(graph, options)
        main.GenerateGraph(lusers, context)

        class TestProcessor:

            def __init__(self):
                self.nodes = {}
                self.edges = {}
        
            def __len__(self): 
                return len(self.nodes)

            def ProcessNode(self, child):
                if child.GetId() in self.nodes:
                    return False
                self.nodes[child.GetId()] = child
                return True

            def ProcessLink(self, child, parent):
                key = parent.GetId()+'_'+child.GetId()
                if key not in self.edges:
                    self.edges[key] = True
                else:
                    assert 0, 'duplicate edge'

            def Check(self, src, dst):
                snode = self.nodes[src]
                dnode = self.nodes[dst]
                key = snode.GetId()+'_'+dnode.GetId()
                return (key in self.edges)

            def __getitem__(self, name):
                return self.nodes[name]

        p = TestProcessor()
        graph.Enum(p)
        print p.nodes
        print p.edges
        return p

    def test_Simple(self):
        users = [
            [
                (main.LOGIN),
            ],
        ]
        p = self.Run(users)
        self.assertEquals(3, len(p))
        self.assertEquals(0, p['start'].power)
        self.assertEquals(1, p['login'].power)
        self.assertEquals(1, p['stop2'].power)
        self.assertEquals(True, p.Check('start', 'login'))
        self.assertEquals(False, p.Check('login', 'start'))
        self.assertEquals(True, p.Check('login', 'stop2'))

    def test_WithoutRelogin(self):
        users = [
            [
                (main.LOGIN),
                (main.LOGOUT),
                (main.LOGIN),
                (main.LOGOUT),
            ],
        ]
        p = self.Run(users, False)
        self.assertEquals(7, len(p))
        self.assertEquals(0, p['start'].power)
        self.assertEquals(1, p['login1'].power)
        self.assertEquals(1, p['castle2'].power)
        self.assertEquals(1, p['logout3'].power)
        self.assertEquals(1, p['login4'].power)
        self.assertEquals(1, p['castle5'].power)
        self.assertEquals(1, p['logout6'].power)
        self.assertEquals(True, p.Check('start', 'login1'))
        self.assertEquals(True, p.Check('login1', 'castle2'))
        self.assertEquals(True, p.Check('castle2', 'logout3'))
        self.assertEquals(True, p.Check('logout3', 'login4'))
        self.assertEquals(True, p.Check('login4', 'castle5'))
        self.assertEquals(True, p.Check('castle5', 'logout6'))

    def test_DoubleLoginWithoutRelogin(self):
        users = [
            [
                (main.LOGIN),
                (main.LOGIN),
                (main.LOGOUT),
            ],
        ]
        p = self.Run(users, False)
        self.assertEquals(7, len(p))
        self.assertEquals(0, p['start'].power)
        self.assertEquals(1, p['login1'].power)
        self.assertEquals(1, p['castle2'].power)
        self.assertEquals(1, p['logout3'].power)
        self.assertEquals(1, p['login4'].power)
        self.assertEquals(1, p['castle5'].power)
        self.assertEquals(1, p['logout6'].power)
        self.assertEquals(True, p.Check('start', 'login1'))
        self.assertEquals(True, p.Check('login1', 'castle2'))
        self.assertEquals(True, p.Check('castle2', 'logout3'))
        self.assertEquals(True, p.Check('logout3', 'login4'))
        self.assertEquals(True, p.Check('login4', 'castle5'))
        self.assertEquals(True, p.Check('castle5', 'logout6'))

    def test_Matchmaking(self):
        users = [
            [
                (main.LOGIN),
                (main.MM_START),
                (main.MM_CANCEL),
                (main.LOGOUT),
            ],
        ]
        p = self.Run(users, False)
        self.assertEquals(6, len(p))
        self.assertEquals(0, p['start'].power)
        self.assertEquals(1, p['login1'].power)
        self.assertEquals(1, p['castle2'].power)
        self.assertEquals(1, p['mm_start3'].power)
        self.assertEquals(1, p['mm_cancel3_0'].power)
        self.assertEquals(1, p['logout5'].power)
        self.assertEquals(True, p.Check('start', 'login1'))
        self.assertEquals(True, p.Check('login1', 'castle2'))
        self.assertEquals(True, p.Check('castle2', 'mm_start3'))
        self.assertEquals(True, p.Check('mm_start3', 'mm_cancel3_0'))
        self.assertEquals(True, p.Check('mm_cancel3_0', 'logout5'))

    def test_CollapseWithoutRelogin(self):
        users = [
            [
                (main.LOGIN),
                (main.LOGIN),
                (main.LOGOUT),
            ],
        ]
        p = self.Run(users, False)
        self.assertEquals(4, len(p))
        self.assertEquals(0, p['start'].power)
        self.assertEquals(1, p['login1'].power)
        self.assertEquals(1, p['castle2'].power)
        self.assertEquals(1, p['logout3'].power)
        self.assertEquals(True, p.Check('start', 'login1'))
        self.assertEquals(True, p.Check('login1', 'castle2'))
        self.assertEquals(True, p.Check('castle2', 'logout3'))
        
    def test_Logout(self):
        users = [
            [
                (main.LOGIN),
                (main.LOGOUT),
            ],
        ]
        p = self.Run(users)
        self.assertEquals(4, len(p))
        self.assertEquals(0, p['start'].power)
        self.assertEquals(1, p['login'].power)
        self.assertEquals(1, p['logout3'].power)
        self.assertEquals(1, p['castle2'].power)
        self.assertEquals(True, p.Check('start', 'login'))
        self.assertEquals(True, p.Check('login', 'castle2'))
        self.assertEquals(True, p.Check('castle2', 'logout3'))

    def test_PvX(self):
        users = [
            [
                (main.LOGIN),
                (main.PVP),
                (main.WIN),
                (main.LOGOUT),
            ],
        ]
        p = self.Run(users)
        self.assertEquals(7, len(p))
        self.assertEquals(0, p['start'].power)
        self.assertEquals(1, p['login'].power)
        self.assertEquals(1, p['logout6'].power)
        self.assertEquals(1, p['castle2'].power)
        self.assertEquals(1, p['win3_0'].power)
        self.assertEquals(1, p['pvp3'].power)
        self.assertEquals(1, p['castle5'].power)
        self.assertEquals(True, p.Check('start', 'login'))
        self.assertEquals(True, p.Check('login', 'castle2'))
        self.assertEquals(True, p.Check('castle2', 'pvp3'))
        self.assertEquals(True, p.Check('pvp3', 'win3_0'))
        self.assertEquals(True, p.Check('win3_0', 'castle5'))
        self.assertEquals(True, p.Check('castle5', 'logout6'))

    def test_Build(self):
        users = [
            [
                (main.LOGIN),
                (main.BUILD),
                (main.PVP),
                (main.WIN),
                (main.LOGOUT),
            ],
        ]
        p = self.Run(users)
        self.assertEquals(8, len(p))
        self.assertEquals(0, p['start'].power)
        self.assertEquals(1, p['login'].power)
        self.assertEquals(1, p['build2_0'].power)
        self.assertEquals(1, p['logout7'].power)
        self.assertEquals(1, p['castle2'].power)
        self.assertEquals(1, p['win2_0_0_0'].power)
        self.assertEquals(1, p['pvp2_0_0'].power)
        self.assertEquals(1, p['castle6'].power)
        self.assertEquals(True, p.Check('start', 'login'))
        self.assertEquals(True, p.Check('login', 'castle2'))
        self.assertEquals(True, p.Check('castle2', 'build2_0'))
        self.assertEquals(True, p.Check('build2_0', 'pvp2_0_0'))
        self.assertEquals(True, p.Check('pvp2_0_0', 'win2_0_0_0'))
        self.assertEquals(True, p.Check('win2_0_0_0', 'castle6'))
        self.assertEquals(True, p.Check('castle6', 'logout7'))

    def test_BuildWhileLoggedOut(self):
        users = [
            [
                (main.LOGIN),
                (main.LOGOUT),
                (main.BUILD),
                (main.LOGIN),
                (main.BUILD),
                (main.LOGOUT),
            ],
        ]
        p = self.Run(users)
        self.assertEquals(6, len(p))
        self.assertEquals(0, p['start'].power)
        self.assertEquals(2, p['login'].power)
        self.assertEquals(1, p['build2_1'].power)
        self.assertEquals(1, p['logout3'].power)
        self.assertEquals(1, p['logout4'].power)
        self.assertEquals(2, p['castle2'].power)
        self.assertEquals(True, p.Check('start', 'login'))
        self.assertEquals(True, p.Check('login', 'castle2'))
        self.assertEquals(True, p.Check('castle2', 'build2_1'))
        self.assertEquals(True, p.Check('build2_1', 'logout4'))
        self.assertEquals(True, p.Check('castle2', 'logout3'))

    def test_BuildWhileSession(self):
        users = [
            [
                (main.LOGIN),
                (main.PVP),
                (main.BUILD),
                (main.WIN),
                (main.LOGOUT),
            ],
        ]
        p = self.Run(users)
        self.assertEquals(7, len(p))
        self.assertEquals(0, p['start'].power)
        self.assertEquals(1, p['login'].power)
        self.assertEquals(1, p['logout6'].power)
        self.assertEquals(1, p['castle2'].power)
        self.assertEquals(1, p['win2_0_0'].power)
        self.assertEquals(1, p['pvp2_0'].power)
        self.assertEquals(1, p['castle5'].power)
        self.assertEquals(True, p.Check('start', 'login'))
        self.assertEquals(True, p.Check('login', 'castle2'))
        self.assertEquals(True, p.Check('castle2', 'pvp2_0'))
        self.assertEquals(True, p.Check('pvp2_0', 'win2_0_0'))
        self.assertEquals(True, p.Check('win2_0_0', 'castle5'))
        self.assertEquals(True,
         p.Check('castle5', 'logout6'))


    def test_LogoutWhileSession(self):
        users = [
            [
                (main.LOGIN),
                (main.TRAINING),
                (main.FAIL),
                (main.TRAINING),
                (main.LOGOUT),
                (main.WIN),
            ],
        ]
        p = self.Run(users)
        self.assertEquals(9, len(p))

        self.assertEquals(0, p['start'].power)
        self.assertEquals(1, p['login'].power)
        self.assertEquals(1, p['stop8'].power)
        self.assertEquals(1, p['castle5'].power)
        self.assertEquals(1, p['castle2'].power)
        self.assertEquals(1, p['win5_0_0'].power)
        self.assertEquals(1, p['training5_0'].power)
        self.assertEquals(1, p['fail2_0_0'].power)
        self.assertEquals(1, p['training2_0'].power)
        self.assertEquals(1, p['castle5'].power)
        self.assertEquals(True, p.Check('start', 'login'))
        self.assertEquals(True, p.Check('login', 'castle2'))
        self.assertEquals(True, p.Check('castle2', 'training2_0'))
        self.assertEquals(True, p.Check('training2_0', 'fail2_0_0'))
        self.assertEquals(True, p.Check('fail2_0_0', 'castle5'))
        self.assertEquals(True, p.Check('castle5', 'training5_0'))
        self.assertEquals(True, p.Check('training5_0', 'win5_0_0'))
        self.assertEquals(True, p.Check('win5_0_0', 'stop8'))

    def test_LoginWhileInSession(self):
        users = [
            [
                (main.LOGIN),
                (main.TRAINING),
                (main.LOGIN),
                (main.FAIL),
            ],
        ]
        p = self.Run(users)
        self.assertEquals(6, len(p))

        self.assertEquals(0, p['start'].power)
        self.assertEquals(1, p['login'].power)
        self.assertEquals(1, p['stop5'].power)
        self.assertEquals(1, p['castle2'].power)
        self.assertEquals(1, p['fail2_0_0'].power)
        self.assertEquals(1, p['training2_0'].power)
        self.assertEquals(True, p.Check('start', 'login'))
        self.assertEquals(True, p.Check('login', 'castle2'))
        self.assertEquals(True, p.Check('castle2', 'training2_0'))
        self.assertEquals(True, p.Check('training2_0', 'fail2_0_0'))
        self.assertEquals(True, p.Check('fail2_0_0', 'stop5'))

    def test_DoubleLogout(self):
        users = [
            [
                (main.LOGIN),
                (main.LOGIN),
                (main.LOGOUT),
                (main.LOGOUT),
            ],
        ]
        p = self.Run(users)
        self.assertEquals(5, len(p))

        self.assertEquals(0, p['start'].power)
        self.assertEquals(2, p['login'].power)
        self.assertEquals(1, p['castle2'].power)
        self.assertEquals(1, p['logout3'].power)
        self.assertEquals(1, p['stop2'].power)
        self.assertEquals(True, p.Check('start', 'login'))
        self.assertEquals(True, p.Check('login', 'castle2'))
        self.assertEquals(True, p.Check('castle2', 'logout3'))
        self.assertEquals(True, p.Check('login', 'stop2'))

    def test_DoubleEdge(self):
        users = [
            [
                (main.LOGIN),
                (main.TRAINING),
                (main.FAIL),
                (main.LOGOUT),
            ],
            [
                (main.LOGIN),
                (main.TRAINING),
                (main.WIN),
                (main.LOGOUT),
            ],
        ]
        p = self.Run(users)
        self.assertEquals(8, len(p))

        self.assertEquals(0, p['start'].power)
        self.assertEquals(2, p['login'].power)
        self.assertEquals(2, p['training2_0'].power)
        self.assertEquals(1, p['fail2_0_0'].power)
        self.assertEquals(1, p['win2_0_1'].power)
        self.assertEquals(2, p['castle2'].power)
        self.assertEquals(2, p['castle5'].power)
        self.assertEquals(2, p['logout6'].power)
        self.assertEquals(True, p.Check('start', 'login'))
        self.assertEquals(True, p.Check('login', 'castle2'))
        self.assertEquals(True, p.Check('castle2', 'training2_0'))
        self.assertEquals(True, p.Check('training2_0', 'fail2_0_0'))
        self.assertEquals(True, p.Check('training2_0', 'win2_0_1'))
        self.assertEquals(True, p.Check('fail2_0_0', 'castle5'))
        self.assertEquals(True, p.Check('win2_0_1', 'castle5'))
        self.assertEquals(True, p.Check('castle5', 'logout6'))

unittest.main()