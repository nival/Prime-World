import datetime
import sys
import os
import time

sys.setrecursionlimit(100000)

START = -1
LOGIN = 0
CASTLE = 1
LOGOUT = 2
BUILD = 3
LAUNCHER_START = 9
LAUNCHER_DOWNLOAD_START = 10
LAUNCHER_DOWNLOAD_END = 11
LAUNCHER_REGISTER = 12
STOP = 13
MM_START = 17
MM_CANCEL = 18
MM_OK = 19
MM_STOP = 20
LAUNCHER_EVENTS = 32

start = 34
count = 8
DRAGONWALD = start
OUTPOST = start+1*count
NATIVEEARTH = start+2*count
PVP = start+3*count
TRAINING = start+4*count
TUTORIAL = start+5*count
ZOMBIELAND = start+6*count
SHUFFLE = start+7*count
PVE = start+8*count
PVES = start+9*count
PVEC = start+10*count

modes = {
    NATIVEEARTH : 'native_earth',
    OUTPOST : 'outpost',
    DRAGONWALD : 'dragonwald',
    PVP : 'pvp',
    TRAINING : 'training',
    TUTORIAL : 'tutorial',
    ZOMBIELAND : 'zombieland',
    SHUFFLE : 'shuffle',
    PVE : 'pve',
    PVES : 'pve_single',
    PVEC : 'pve_coop',
}

mode_names = sorted(modes.values())

actions = {
    START : 'start',
    STOP : 'stop',
    LOGIN : 'login',
    CASTLE : 'castle',
    LOGOUT : 'logout',
    BUILD : 'build',
    LAUNCHER_START : 'start_launcher',
    LAUNCHER_REGISTER : 'register',
    LAUNCHER_DOWNLOAD_START : 'start_download',
    LAUNCHER_DOWNLOAD_END : 'end_download',
    MM_START : 'mm_start',
    MM_CANCEL : 'mm_cancel',
    MM_OK : 'mm_ok',
    MM_STOP : 'mm_stop',
    LAUNCHER_EVENTS : 'launcher_events',
}

loc = {
    START : 'start',
    STOP : 'stop',
    LOGIN : 'login',
    CASTLE : 'castle',
    LOGOUT : 'logout',
    BUILD : 'build',
    LAUNCHER_START : 'start_launcher',
    LAUNCHER_REGISTER : 'register',
    LAUNCHER_DOWNLOAD_START : 'start_download',
    LAUNCHER_DOWNLOAD_END : 'end_download',
    MM_START : 'mm_start',
    MM_CANCEL : 'mm_cancel',
    MM_OK : 'mm_ok',
    MM_STOP : 'mm_stop',
}

results = ['win', 'lose', 'fail', 'async', 'nobody', 'leave', 'ileave']
abbreviatures = {}

for index, (code, name) in enumerate(modes.items()):
    actions[code] = name
    loc[code] = name

    abbreviation = name.replace(' ', '_')
    abbreviatures[abbreviation] = True

    for index2, result in enumerate(results):
        actions[code+index2+1] = abbreviation+'_'+result
        loc[code+index2+1] = result

class Node:

    def __init__(self, action, nid, rank, parent, isClusterized=False):
        self.rank = rank
        self.nid = nid
        self.action = action
        self.children = {}
        self.power = 0
        self.cpower = 0
        self.isClusterized = isClusterized
        self.deaths = []
        self.parent = parent
        self.auids = []

    def Add(self):
        self.power += 1
        return self.power

    def Die(self, auid):
        self.deaths.append(auid)

    def Calculate(self):
        self.cpower = 0
        for action, node in self.children.items():
            self.cpower += node.power

    def Feed(self, action, nid, nodes, isClusterized):        
        if isClusterized:
            self.isClusterized = True
        subnode = self.children.get(action, None)
        if not subnode:
            full_id = actions[action]+nid
            subnode = nodes.get(full_id, None)
            if not subnode:
                subnode = Node(action, nid, self.rank+1, self, isClusterized)
                nodes[full_id] = subnode
            self.children[action] = subnode
        subnode.Add()
        return subnode
    
    def Enum(self, processor):
        result = processor.ProcessNode(self)
        if result:
            for action, node in self.children.items():
                processor.ProcessLink(node, self)
            for action, node in self.children.items():
                node.Enum(processor)

    def Visit(self, auid):
        if auid:
            self.auids.append(auid)

    def GetId(self):
        return actions[self.action]+self.nid

    def GetNid(self):
        return self.nid

    def GetName(self, leaved=0):
        result = loc[self.action]+' ('+str(self.power)
        if len(self.deaths) > 0:
            result += '/%d)' % len(self.deaths)
        else:
            result += ')'
        if leaved > 0:
            result += ' -%d' % leaved
        return result

class Graph:

    def __init__(self):
        self.root = Node(START, '', 0, None) 
        self.node = None
        self.nodes = {}
        self.Reset()
        self.auid = None
        self.deaths = {}
        self.deadends = []

    def Reset(self):
        if self.node and self.node.action != LOGOUT and self.auid:
            self.Feed(STOP, False, True, death=True)
        self.node = self.root
        self.auid = None

    def Relogin(self, death=False):
        if self.node and self.node.action != LOGOUT and self.auid:
            self.Feed(STOP, False, True, death=death)
        node = self.nodes.get('login', None)
        assert node
        node.Add()
        self.node = node

    def FailLogin(self, death=False):
        node = self.nodes.get('login', None)
        if node:
            self.node = node
        else:                
            self.Feed(LOGIN, False, False, False, True, death=death)
        self.node.Add()

    def FindDeathNode(self, nid, count):
        tokens = nid.split('_')
        index = int(tokens[0])
        if index+1 < len(self.deadends):
            i = index+1
            n = min(i+count, len(self.deadends))
            while i < n:
                if len(self.deadends[i]) > 0:
                    return self.deadends[i][-1]
                i += 1

    def SetAuid(self, auid, death):
        self.auid = auid
        self.root.Add()

    def Feed(self, action, isLoggedOut=False, isRanked=False, isClusterized=False, isRoot=False, death=False):
        nid = ''
        if isRoot:
            nid = ''
        elif not isLoggedOut:
            if not isRanked:
                nid = self.node.nid+'_'+str(len(self.node.children))
            else:
                nid = str(self.node.rank+1)     
#        print 'feed', actions[action],nid
        self.node = self.node.Feed(action, nid, self.nodes, isClusterized)
        if death:
            self.node.Die(self.auid)
        self.node.Visit(self.auid)
        
    def Enum(self, processor):
        self.root.Enum(processor)
    
    def Prepare(self):
        result = []
        for name, node in self.nodes.items():
            if len(node.deaths) > 0:
                nid = node.GetNid()
                if nid and (node.action == LOGOUT or node.action == STOP):
                    tokens = nid.split('_')
                    index = int(tokens[0])
                    if index >= len(result):
                        count = index-len(result)+1
                        for i in range(count):
                            result.append([])
                    result[index].append(node)
        self.deadends = result

L_START = 0
L_SHOW_AUTH = 1
L_AUTH_SUCCESS = 2
L_DOWNLOADING = 3
L_PAUSED = 4
L_RESUMED = 5
L_READY_PLAY = 6
L_START_PLAY= 7
L_RETURN_FROM_GAME = 8
indices = [L_START, L_SHOW_AUTH, L_AUTH_SUCCESS, L_DOWNLOADING, L_PAUSED, L_RESUMED, L_READY_PLAY, L_START_PLAY, L_RETURN_FROM_GAME]

indices_l = {
    L_START : 'L_START', 
    L_SHOW_AUTH : 'L_SHOW_AUTH',
    L_AUTH_SUCCESS : 'L_AUTH_SUCCESS',
    L_DOWNLOADING : 'L_DOWNLOADING',
    L_PAUSED : 'L_PAUSED', 
    L_RESUMED : 'L_RESUMED',
    L_READY_PLAY : 'L_READY_PLAY',
    L_START_PLAY : 'L_START_PLAY', 
    L_RETURN_FROM_GAME : 'L_RETURN_FROM_GAME',
}

class Context:

    def OnFinish(self):
        pass

class LauncherFunnelContext(Context):

    def __init__(self, graph, options):
        self.graph = graph
        self.options = options
        self._Reset()
        self.indices = [0]*len(indices)
        self.no_events = []


    def OnFinish(self):
        print 'no events: %d ' % len(self.no_events)
        for auid in self.no_events:
            print auid,
        print
        print self.indices
        for index in indices:
            print indices_l[index], self.indices[index]

    def _Reset(self):
        self.found = False

    def Reset(self):
        if not self.found:
#            print 'no events', self.user.auid
            self.no_events.append(self.user.auid)
        self.graph.Reset()
        self._Reset()


    def OnNewUser(self, user):
        self.graph.Reset()
        self._Reset()
        self.passed = []
        self.found = False
        self.user = user
        self.graph.SetAuid(user.auid, len(user.events) == 0)

    def _Register(self, index, unique):
        self.found = True
        if index in unique:
            if index not in self.passed:
                self.passed.append(index)
                self.indices[index] += 1
        else:
            self.indices[index] += 1
    
    def OnEvent(self, index, dt, action, auid, param, line):
        if action == LAUNCHER_EVENTS:
            s = bin(int(param))[2:][::-1]
#            print self.user.auid, param, s
            for index in indices:
                if index < len(s):
                    if int(s[index]) == 1:
                        if index == L_AUTH_SUCCESS:
                            self._Register(L_SHOW_AUTH, indices)
                        self._Register(index, indices)
 #                       print index
        elif True:
            if action == LAUNCHER_START:
                self._Register(L_START, indices)
            elif action == LAUNCHER_DOWNLOAD_START:
                self._Register(L_START, indices)
                self._Register(L_SHOW_AUTH, indices)
                self._Register(L_AUTH_SUCCESS, indices)
                self._Register(L_DOWNLOADING, indices)
            elif action == LAUNCHER_DOWNLOAD_END:
                self._Register(L_START, indices)
                self._Register(L_SHOW_AUTH, indices)
                self._Register(L_AUTH_SUCCESS, indices)
                self._Register(L_DOWNLOADING, indices)
                self._Register(L_READY_PLAY, indices)
            elif action == LAUNCHER_REGISTER:
                self._Register(L_START, indices)
                self._Register(L_SHOW_AUTH, indices)
                self._Register(L_AUTH_SUCCESS, indices)
            elif action in [LOGIN, TRAINING, TUTORIAL, PVP, PVE, MM_START]:
                self._Register(L_START, indices)
                self._Register(L_SHOW_AUTH, indices)
                self._Register(L_AUTH_SUCCESS, indices)
                self._Register(L_DOWNLOADING, indices)
                self._Register(L_READY_PLAY, indices)
                self._Register(L_START_PLAY, indices)

session_results = []
session_starts = []

for code, cname in modes.items():
    session_starts.append(code)
    for index, name in enumerate(results):
        session_results.append(code+index+1)

other_castle_operations = [LOGOUT, BUILD, MM_START, MM_CANCEL, MM_OK, MM_STOP, LOGIN]

def findSessionAction(action):
    for code in modes.keys():
        if action >= code+1 and action <= code+len(results):
            return code
    assert 0

def findSessionFailAction(action):
    if action in modes.keys():
        return action+results.index('fail')+1
    factions = {
        PVP : FAIL,
        TRAINING : TFAIL,
        TUTORIAL : UFAIL,
    }
    return factions[action]

class SessionsContext(Context):

    def __init__(self, graph, options):
        self.graph = graph
        self.options = options
        self._Reset()

    def _Reset(self):
        self.inBattle = False
        self.inCastle = False
        self.last_action = None
        self.prev_event = None
               
    def Reset(self):
        if self.prev_event in modes.keys():
            self.graph.Feed(self.prev_event+1+results.index('fail'), isClusterized=True, death=False)
            self.graph.Feed(CASTLE, False, True)
        self.graph.Reset()
        self._Reset()

    def OnNewUser(self, user):
        self.graph.Reset()
        self._Reset()
        self.user = user
        self.graph.SetAuid(user.auid, len(user.events) == 0)
    
    def OnEvent(self, index, dt, action, auid, param, line):
        self.prev_event = action
        death = (index == len(self.user.events)-1)
        if not self.inCastle and (action in session_starts or action in session_results or action in other_castle_operations):
            self.graph.Feed(CASTLE, False, True)
            self.inCastle = True
        if action in session_starts:
            if self.inBattle == True:
                assert self.last_action != None, (line, loc[action], auid)
                faction = findSessionFailAction(self.last_action)
                self.graph.Feed(faction, isClusterized=True, death=death)
                self.inBattle = False
                self.graph.Feed(CASTLE, False, True)
            self.inBattle = True
            self.graph.Feed(action, False, True, isClusterized=False, death=death)
            self.last_action = action
        elif action in session_results:
            if not self.inBattle:
                taction = findSessionAction(action)
                self.inBattle = True
                self.graph.Feed(taction, False, True, isClusterized=False, death=death)
            self.graph.Feed(action, isClusterized=True, death=death)
            self.inBattle = False
            self.graph.Feed(CASTLE, False, True)


class SimpleContext(Context):

    def __init__(self, graph, options):
        self.graph = graph
        self.options = options
        self._Reset()

    def _Reset(self):
        self.prev_action = None
        self.loginCounter = 0
        self.castled = False
        self.inBattle = False
    
    def Reset(self):
        self.graph.Reset()
        self._Reset()

    def OnNewUser(self, user):
        self.graph.Reset()
        self._Reset()
        self.user = user
        self.graph.SetAuid(user.auid, len(user.events) == 0)
    
    def OnEvent(self, index, dt, action, auid, param, line):
        if action == BUILD and self.prev_action == BUILD:
            return
        if action == LAUNCHER_START and self.prev_action == LAUNCHER_START:
            return
        death = (index == len(self.user.events)-1)
        self.prev_action = action
        if action == LAUNCHER_REGISTER:
            self.graph.Feed(LAUNCHER_REGISTER, False, not self.options.relogin, death=death)
        elif action == LAUNCHER_START:
            self.graph.Feed(LAUNCHER_START, False, not self.options.relogin, death=death)
        elif action == MM_START:
            self.graph.Feed(CASTLE, False, True)
            self.castled = True
            self.graph.Feed(action, False, True, False, False, death)
        elif action in [MM_STOP, MM_CANCEL, MM_OK]:
            self.graph.Feed(action, False, False, False, False, death)
        elif action == LOGIN:
            if self.inBattle:
      #          assert 0, ('login while in battle', auid, index, actions[action], dt)
                return
            if self.options.relogin and (self.loginCounter > 0 or index > 0):
                self.graph.Relogin(death=death)
                self.loginCounter += 1
                self.prev_action = None
                self.inBattle = False
            else:
                if self.options.relogin or self.loginCounter == 0:
                    self.graph.Feed(LOGIN, False, not self.options.relogin, isRoot=self.options.relogin)
                    self.loginCounter += 1
        else:
            if self.loginCounter == 0:
                if action in session_starts:
                    self.graph.FailLogin(death=death)
                    self.castled = False
                    self.loginCounter += 1
                    self.prev_action = None
                    self.inBattle = False
                elif action in [LOGOUT, BUILD]:
                    return
                else:
                    assert 0, ('action without login', auid, index, actions[action], dt)
            if action in session_starts+[BUILD, LOGOUT]+session_results:
                #print '!!!', actions[action], self.castled
                if action == BUILD and self.inBattle:
                    return # skip build while session
                if not self.castled:
                    self.graph.Feed(CASTLE, False, True)
                    self.castled = True
                if action in session_results:
                    if self.inBattle:
                        self.graph.Feed(action, isClusterized=True, death=death)
                        self.inBattle = False
                    else:
                        assert 0, (auid, actions[action], dt)
                    self.castled = False
                else:
                    if action in session_starts:
                        if action == TRAINING and self.options.matchmaking:
                            self.graph.Feed(MM_START, False, False, False, False, death)
                            self.graph.Feed(MM_OK, False, False, False, False, death)
                        self.inBattle = True
                        self.graph.Feed(action, False, True, death=death)
                    elif action in [LOGOUT] and self.inBattle:
                        pass # skip logout while in battle
                    elif action == LOGOUT:
                        self.graph.Feed(action, isRanked=True, death=death)
                    elif action == BUILD:
                        self.graph.Feed(action, False, True, death=death)
                    else:   
                        self.graph.Feed(action, death=death)
            if action == LOGOUT:
                if not self.inBattle:
                    self._Reset()
                else:
                    pass # logout skipped while in battle



def GenerateGraph(users, context):
    for uindex, user in enumerate(users):
        context.OnNewUser(user)
        for index, value in enumerate(user.events):
            if type(value) == int:
                action = value
                auid = None
                dt = None
                param = None
            elif len(value) == 2:
                action, auid = value
                param = None
                dt = None
            elif len(value) == 3:
                dt, action, auid = value
                param = None
            else:
                dt, action, auid, param, line = value
            context.OnEvent(index, dt, action, auid, param, line)
        context.Reset()
    context.OnFinish()

class GraphProcessor:

    def __init__(self, graph, lines, count, options):
        self.lines = lines
        self.edges = {}
        self.processed = {}
        self.count = count
        self.options = options
        self.deaths = []
        self.graph = graph

    def Finish(self):
        def ZeroKey(value):
            return value[0]
        self.deaths.sort(key=ZeroKey)
    
    def ProcessNode(self, child):
        cid = child.GetId()
        if cid not in self.processed:
            child.Calculate()
#            print len(self.processed), self.count
#            if child.action == STOP:
#                print '%s;%s' % (child.GetId(), len(child.auids))
            if child.action == LOGOUT and len(child.deaths) > 0:
                self.deaths.append( (child.rank, child.deaths) )
            self.processed[cid] = True
#            print len(self.processed), self.count
            cluster = None
            if child.isClusterized:
                if child.parent and child.parent.isClusterized:
                    cluster = child.parent
                else:
                    cluster = child 
            if cluster:
                self.lines.append('subgraph cluster_%s {' % cluster.GetId())
            if child.action in [LOGIN, LOGOUT]:
                color = 'color=purple shape=box'    
            elif child.action in [STOP]:
                color = 'color=blue shape=box'
            elif child.action in [CASTLE]:
                color = 'shape=house'   
            elif child.action in [START]:
                color = 'shape=invtriangle' 
            else:
                color = ''
            tooltip = child.GetId()
            nid = child.GetNid()
            leaved = 0
            if nid:
                count = 4
                if child.action == CASTLE:
                    count = 1
                dnode = self.graph.FindDeathNode(nid, count)
                if dnode:
#                    print 'dnode', dnode.GetId()
                    leaved = len(set(dnode.deaths) & set(child.auids))
                    if leaved > 0: 
                        tooltip += '&#13;leave at %s: %d' % (dnode.GetId(), leaved)
 #                   print '!!!', child.GetId(), leaved, dnode.GetId()
                if self.options.details and len(child.deaths) > 0:
                    deaths = list(set(child.deaths))
                    tooltip += '&#13;deaths=%r' % deaths
                    print '# %s:%d' % (child.GetId(), len(deaths))
                    for death in deaths:
                        print death,
                    print
                if self.options.details:
#                    print '!!!!!!!!', list(set(child.auids))
                    tooltip += '&#13;auids=%r' % list(set(child.auids))
            self.lines.append('    %s [label="%s" %s tooltip="%s"];' % (child.GetId(), child.GetName(leaved), color, tooltip))
            if cluster:
                self.lines.append('label = "";')
                self.lines.append('}')
            return True
        return False

    def ProcessLink(self, child, parent):
        cid = child.GetId()
        pid = parent.GetId()
        key = pid+'_'+cid
        if key in self.edges:
            assert 0
            return
        percent = ''
        if len(parent.children) > 1:
            percent = '[ shape=onormal label="%2.1f"' % (100.0*child.power/float(parent.cpower))+']'
        self.lines.append('    %s -> %s %s;' % (pid, cid, percent))
        self.edges[key] = True

def Generate(users, options, generatorClass):    
    graph = Graph()
    context = generatorClass(graph, options)
    GenerateGraph(users, context)

    lines = [
        'digraph prof {', 
        '    graph [ ranksep = 0.75 ];' ,
        '    ratio = fill;',
        '    label="PrimeWorld gameplay routes (%s unique users)";' % len(users),
        '    labelloc=t;',
        'fontsize=18;',
        '    node [style=filled];',
    ]    
    graph.Prepare()
    p = GraphProcessor(graph, lines, len(graph.nodes), options)
    graph.Enum(p)
    p.Finish()
    lines.append('}')
    return lines

class LUser:

    def __init__(self, auid, events=[]):
        self.auid = auid 
        self.events = list(events)
        assert len(self.events) == 0

    def Prepare(self):
        def ZeroItem(p):
            return p[0]
        self.events.sort(key=ZeroItem)        
        
def ParseAuids(path):
    if not os.path.isfile(path):
        raise Exception('File not found: %r' % path)

    result = []
    f = open(path, 'rb')
    for line in f.readlines():
        line = line.replace('\r', '').replace('\n', '')
        if line:
            result.extend(line.split())
    return result

class Distribution:

    def __init__(self):
        self.items = {}

    def Add(self, key):
        if key in self.items:
            self.items[key] += 1
        else:
            self.items[key] = 1

def FailParamFunc(action, param):
    # 1 - no results 2 nobody came 3 - async results 4 - async detected
    if param == '1':
        return action+1+results.index('leave')
    elif param == '2':
        return action+1+results.index('nobody')
    elif param == '-1':
        return action+1+results.index('fail')
    elif param == '3':
        return action+1+results.index('async')
    elif param == '4':
        return action+1+results.index('async')
    else:
        assert 0, param
    return action

def LeaveParamFunc(action, param):
    # 1 - no results 2 nobody came 3 - async results 4 - async detected
    if param == '0':
        return action+1+results.index('leave')
    elif param == '1':
        return action+1+results.index('ileave')
    else:
        assert 0, param
    return action

def MMFunc(action, param):
    if param == '0':
        return MM_OK
    elif param == '1':
        return MM_STOP
    elif param == '2':
        return MM_CANCEL
    else:
        assert 0, param
    return action


parse_tokens = {
    'launcher_start' : (LAUNCHER_START, 0, 3, None),
    'launcher_dstart' : (LAUNCHER_DOWNLOAD_START, 0, 3, None),        
    'launcher_dend' : (LAUNCHER_DOWNLOAD_END, 0, 3, None),        
    'launcher_events' : (LAUNCHER_EVENTS, 0, 3, None),        
    'login' : (LOGIN, 0, 0, None),
    'logout' : (LOGOUT, 0, 0, None),        
    'resource' : (BUILD, 0, 3, None),        
    'social_register' : (LAUNCHER_REGISTER, 0, 3, None),        
    'mm_start' : (MM_START, 0, 3, None),        
    'mm_end' : (MM_STOP, 0, 3, MMFunc),        
}
ractions = {}

def ConvertToDict(lst):
    result = {}
    for item in lst:
        result[item] = True
    return result

def ParseActionName(action, all_events):
    if action not in all_events:
        tokens = action.split(' ')
        action = tokens[0]+'_'+tokens[1]
        if len(tokens) > 2:
            action += ' '+' '.join(tokens[2:])
    return action

def Parse(path, actions, _fauids, all_events, _fnauids):
    def _UpdateProgress(progress):
        print "\rProgress: [{0:50s}] {1:.1f}%".format('#' * int(progress * 50), progress * 100),

    crep = { 
        'leave' : 'leave',
        'won' : 'win',
        'failed': 'fail',
        'lose' : 'lose',
    }

    for code, name in modes.items():
        parse_tokens[name] = (code, 2, None, None)
        for aname, cname in crep.items():
            acode = code+results.index(cname)+1
            fname = name+' '+aname
            if cname == 'fail':
                parse_tokens[fname] = (acode, 3, 3, FailParamFunc)
            elif cname == 'leave':
                parse_tokens[fname] = (acode, 3, 3, LeaveParamFunc)
            else:
                parse_tokens[fname] = (acode, 3, None, None)
            ractions[fname] = code
    print parse_tokens
    d = Distribution()
    fauids = ConvertToDict(_fauids)
    fnauids = ConvertToDict(_fnauids)

    auids = []
    users = {}
    f = open(path, 'rb')
    total_size = os.path.getsize(path)
    index = 0
    iline = 0
    current_size = 0
    prev_ts = 0
    for _line in f.readlines():
        if time.time()-prev_ts > 0.5:
            progress = current_size/float(total_size)
            _UpdateProgress(progress)
            prev_ts = time.time()
        current_size += len(_line)
        if index == 0:
            index += 1
            continue
        iline += 1
        line = _line.replace('\r', '').replace('\n', '')
        tokens = line.split(';')
        if len(tokens) < 3:
            continue
        action = tokens[2]
        auid = tokens[1]
        if not auid:
            continue
        if len(fauids) > 0 and auid not in fauids:
            continue

        if len(fnauids) > 0 and auid in fnauids:
            continue

        if auid not in users:
            assert auid, (_line, index, tokens)
            auids.append(auid)
            users[auid] = LUser(auid)

        action = ParseActionName(action, all_events)

        if action not in all_events:
            print 'Unsupported action %r' % action
            continue
        d.Add(action)
        if action not in actions:
            continue

        acode = None
        param = None
        tm = int(tokens[0])
        presult = parse_tokens.get(action, None)
        if presult != None:
            acode, _tm, _param, _func = presult
            if _param != None:
                param = tokens[_param]
                if _func:
                    acode = _func(ractions[action], param)
            tm += _tm
        else:
            assert 0, tokens
        users[auid].events.append( (tm, acode, auid, param, iline) )
        index += 1
    result = [
    ]
    for i in range(len(auids)):
        result.append(users[auids[i]])
    _UpdateProgress(1.0)
    print
    return result, d

def Output(user):
    print '----- auid: %r -----' % user.auid
    for index, (dt, action, auid, param, index) in enumerate(user.events):
        result = '    ('+str(dt)+', '+actions[action].upper()+", %s)," % auid+' # '+str(index)
        if param:
            result +=' (%s)' % param
        print result
#        if param:
#            print param
#        else:
#            print

matchmaking = ['mm_start', 'mm_end']
resources = ['resource']
launcher_brief = ['launcher_start']
launcher_events = ['launcher_events']
launcher = launcher_brief+['launcher_dstart', 'launcher_dend']+launcher_events

statuses = ['won', 'lose', 'failed', 'leave']

game = []
for mode in mode_names:
    game.append(mode)
    for status in statuses:
        game.append('%s %s' % (mode, status))

login = ['login', 'logout'] #, 'social_register', 
register = ['social_register']

gameplay = login+game
all_events = gameplay+launcher+resources+matchmaking+register+login+launcher
print 'All events: %d' % len(set(all_events))

class Options:

    def __init__(self):
        self.relogin = False
        self.matchmaking = False
        self.details = False

def ParseAuidsFromCmdLine(name):
    result = []
    try:
        auids_index = sys.argv.index(name)
    except:
        auids_index = -1
    if auids_index >= 0:
        return ParseAuids(sys.argv[auids_index+1])
    return []    

def main():
    print 'Args:', sys.argv
    events = []
    auids = ParseAuidsFromCmdLine('--auids')
    if len(auids) > 0:  
        print 'Applying filter for %d users' % len(auids)
    nauids = ParseAuidsFromCmdLine('--nauids')
    if len(nauids) > 0:  
        print 'Skipping %d users' % len(nauids)

    generatorClass = SimpleContext
    if '--sessions' in sys.argv:
        events = game + resources + matchmaking + launcher_events + login
        generatorClass = SessionsContext
    elif '--main' in sys.argv:
        events = game + resources + login
        generatorClass = SessionsContext
    elif '--launcher' in sys.argv:
        events = all_events
        generatorClass = LauncherFunnelContext
    else:
        events = gameplay
    if len(sys.argv) > 2:
        print 'Parsing %r with events %s' % (sys.argv[2], events)

        lusers, distr = Parse(sys.argv[2], events, auids, all_events, nauids)
        print 'Found %d users' % len(lusers)
        print 'Events distribution:'
        for name, count in distr.items.items():
            print ' '*3, '%s: %d' % (name, count)
        for user in lusers:
            user.Prepare()
            if '--log_users' in sys.argv:
                Output(user)
    else:
        print 'Using test data'
        lusers = [LUser(index, events) for index, events in enumerate(users)]
    options = Options()
    options.relogin = ('--plain' not in sys.argv)
    options.matchmaking = ('mm_start' in events)
    options.details = ('--details' in sys.argv)
    if generatorClass:
        lines = Generate(lusers, options, generatorClass)
        f = open(sys.argv[1], 'wb')
        f.write('\r\n'.join(lines))
        f.close()

if __name__ == '__main__':
    main()
                                                        