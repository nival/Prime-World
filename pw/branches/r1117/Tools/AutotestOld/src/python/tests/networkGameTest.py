from os.path import join, abspath, normpath, split, exists, isdir
from testApplications.gameApp import GameApp
import test
from os import remove, listdir, rmdir, mkdir, system, getenv
from re import match, search, findall
import shutil
import glob
from socket import gethostbyname, gaierror
from copytree import copytree
import time
import logging
import sourceManager
import settingsManager
import processes
import errors
import pywintypes
from win32api import GetComputerName, CloseHandle
from win32process import TerminateProcess, GetExitCodeProcess
from win32con import STILL_ACTIVE
from string import Template

NET_COORDINATOR = r'Tools\NetRun\PF_NetRunCoordinator.exe'
LOBBY_SERVER_PATH = r'Src\Game\PF\Lobby\.auto'
LOBBY_SERVER_APP = 'LobbyServerApp.exe'
LOBBY_PORT = '35001'
LOBBY_LOG = 'lobby.log'

SHARED_AUTOTEST_FOLDER = 'pf-autotest'
RUN_REMOTE_SCRIPT = 'remote.py'
REMOTE_SCRIPT_LOG = 'autotest.remote.log'
REMOTE_SCRIPT_LOG_LAUNCH_TIME_PATTERN = 'Launch time: (.*)'

SERVER_SCRIPT_TEMPLATE = 'server.cfg.template'
CLIENT_SCRIPT_TEMPLATE = 'client.cfg.template'

LOCAL_SCRIPT_TMP = '$$$.local.cfg'
REMOTE_SCRIPT_TMP = '$$$.remote.cfg'
COORDINATOR_LOG_TMP = '$$$.coordinator.log'

NETMSG_START_LOBBY = 'Starting lobby with server at %s:%s...'
NETMSG_CLIENT_LOGIN_ACCEPTED = 'Client: login accepted, user id = (\d*)'
NETMSG_CLIENT_STARTED = 'Client: started successfully'
NETMSG_START_GAME = 'Starting game for %d players'
NETMSG_PREGAME = 'Entering pre-game, session id = 1'

SERVMSG_CLIENT_LOGIN = 'New client logged in: userId = (\d*)'
SERVMSG_USER_CONNECT = 'New user connected, id = (\d*), nick =\s*(\S+)'

def CoordinatorPath():
  return join(NetworkGameTest.root, NET_COORDINATOR)

def LobbyServerPath(configuration):
  return join(NetworkGameTest.root, LOBBY_SERVER_PATH, configuration, LOBBY_SERVER_APP)

def RunConsoleProcess(cmd, workdir):
  _,_, process = processes.launchApp( join( getenv('windir'), r'system32\cmd.exe' ), 
                                                    '/C "' + cmd + '"', workdir)
  return process

class GameInstance(object):
  def __init__(self, bServer, machine = '', rootFolder = '', scriptTemplate = ''):
    self.bLocal = (machine == '')
    
    if self.bLocal:
      self.machine = GetComputerName()
    else:
      self.machine = machine
      
    if rootFolder == '':
      self.rootFolder = join(r'\\' + machine, SHARED_AUTOTEST_FOLDER)
    else:
      self.rootFolder = rootFolder

    self.bServer = bServer
      
    try:
      self.ip = gethostbyname(self.machine)
    except gaierror:
      self.ip = ''
    
    self.status = 'N/A'
    
    if self.bLocal:
      self.build = sourceManager.singleton.version
    else:
      self.build = -1
    
    if scriptTemplate != '':
      self.scriptTemplate = scriptTemplate
    else:
      if self.bServer:
        self.scriptTemplate = SERVER_SCRIPT_TEMPLATE
      else:
        self.scriptTemplate = CLIENT_SCRIPT_TEMPLATE

  def createCfgScript(self, name):
    vars = { 'LOBBY_IP_PORT' : self.serverIp + ':' + LOBBY_PORT,
                 'LOGIN' : self.machine,
                 'NUM_PLAYERS' : self.numPlayers }
      
    tmpl = open(join('scripts', self.scriptTemplate), 'r')
    f = open(name, 'w+')
    f.write(Template(tmpl.read()).substitute(vars))
    f.close()

  @staticmethod
  def localCfgScriptAbsPath():
    return join(NetworkGameTest.root, LOCAL_SCRIPT_TMP)

  def runLocal(self, configuration):
    self.createCfgScript(self.localCfgScriptAbsPath())
    _,_, self.hProcess = processes.launchApp(GameApp.application(configuration), 
                                'exec %s' % join('..', LOCAL_SCRIPT_TMP), join(self.rootFolder, 'Bin'))

  @staticmethod
  def ignoreSVNfiles(dir, files):
    if search('\.svn', dir) == None:
      return []
    else:
      return files

  @staticmethod
  def ignoreSVNandLOGfiles(dir, files):
    if search('\.svn', dir) == None and search('log', dir) == None:
      return []
    else:
      return files

  def updateStatus(self):
    if self.bLocal:
      if self.status == 'RUNNING':
        if hasattr(self, 'hProcess'):
          if GetExitCodeProcess(self.hProcess) != STILL_ACTIVE:
            CloseHandle(self.hProcess)
            delattr(self, 'hProcess')
            self.status = 'IDLE'

  def deploy(self, build):
    if self.bLocal:
      return True
    
    if self.build != build:
      # use coordinator to deploy data
      logging.info('Deploying data to %s' % self.machine)
      cmd = '%s deploy --build %d %s' % ( CoordinatorPath(), build, self.ip )
      logging.debug('deploying cmd: ' + cmd)
      
      if system(cmd) != 0:
        return False
      
      self.build = build
    else:
      logging.info('Data on %s is up to date' % self.machine)
    
    return True

  def runRemote(self, configuration):
    self.createCfgScript(REMOTE_SCRIPT_TMP)

    # use coordinator to run game
    cmd = '%s run --noresolve --configuration %s --script %s %s > %s' % ( CoordinatorPath(), configuration,
                REMOTE_SCRIPT_TMP, self.ip, COORDINATOR_LOG_TMP )
    logging.debug('run cmd: ' + cmd)
    system(cmd)
    
    if not exists(COORDINATOR_LOG_TMP):
        raise errors.TestFailed("Failed to run game remotely")
        
    # read query log
    f = open(COORDINATOR_LOG_TMP, 'r')
    if f == None:
      raise errors.TestFailed("Failed to run game remotely")
    text = f.read()
    f.close()  
    
    # extract launch information
    for line in text.splitlines():
      words = line.split()
      if len(words) >= 2 and words[0] == self.ip:
        if words[1] == 'SUCCESS':
          self.launchTime = time.mktime(time.strptime(words[2], test.TIME_FORMAT))
        else:
          raise errors.TestFailed("Failed to run game remotely")
    
  def run(self, configuration, serverIp = '', numPlayers = 2):
    if self.build == -1:
      return
    
    if serverIp == '':
      self.serverIp = self.ip
    else:
      self.serverIp = serverIp
      
    self.numPlayers = numPlayers
    
    self.launchTime = time.time()
    
    if self.bLocal:
      self.runLocal(configuration)
    else:
      self.runRemote(configuration)
      
    self.status = 'RUNNING'

  def kill(self):
    if self.bLocal:
      if hasattr(self, 'hProcess'):
        try:
          TerminateProcess(self.hProcess, -1)
        except pywintypes.error, e:
          pass
          
        CloseHandle(self.hProcess)
        delattr(self, 'hProcess')
    else:
      # kill remote running game
      cmd = '%s kill %s' % ( CoordinatorPath(), self.ip )
      logging.debug('kill cmd: ' + cmd)
      system(cmd)
    
    self.status = 'IDLE'

  def cleanup(self):
    if exists(COORDINATOR_LOG_TMP):
      remove(COORDINATOR_LOG_TMP)

    if self.bLocal:
      if exists(self.localCfgScriptAbsPath()):
        remove(self.localCfgScriptAbsPath())
    else:
      if exists(REMOTE_SCRIPT_TMP):
        remove(REMOTE_SCRIPT_TMP)

  def checkAssertExcptLogs(self):
    self.assertLog = self.findLog('assert\.log')
    self.excptLog = self.findLog('exception\.log')
    return (self.assertLog != None or self.excptLog != None)

  def findLog(self, name):
    return test.findLog('PF', name, join(self.rootFolder, 'Bin/log'), self.launchTime - 1)

  def analyzeLog(self):
    log = self.findLog('output\.txt')
    if log == None:
      raise errors.TestFailed( "Can't locate run log on %s" % self.machine )

    f = open(log, 'r')
    text = f.read()
    f.close()

    if (search(NETMSG_START_LOBBY % (self.serverIp, LOBBY_PORT), text) == None or
        search(NETMSG_CLIENT_STARTED, text) == None or
        search(NETMSG_PREGAME, text) == None or
        search(NETMSG_START_GAME % self.numPlayers, text) == None):
      raise errors.TestFailed( "Client on %s has not reported successfull connection" % self.machine )

class NetworkGameTest(test.Test):
  def __init__(self, configuration, maxNumPlayers, clientNames):
    super(NetworkGameTest, self).__init__(configuration)
    self.maxNumPlayers = maxNumPlayers
    self.clientNames = clientNames

  def key(self): return '|'.join([self.__class__.__name__, self.pd.configuration])

  def info(self, configuration):
    return (GameApp.application(configuration), GameApp.workingDir(configuration), 'exec "../Tools/Autotest/scripts/single.quit.cfg"', 120000)

  @classmethod
  def configure(cls, settings):
    super(NetworkGameTest, cls).configure(settings)

    # UnitTests can be shared between configurations
    cls.configurations = settings.configurations
    cls.root = settingsManager.getRoot(settings)

  @staticmethod
  def useGoldenImages():
    return False

  @staticmethod
  def getRequiredComponents():
    return ['Src/PF.sln', r'Src\Game\PF\Lobby\LobbyServerApp.application']

  def analyzeServerLog(self):
    # can't collect that log for some mystical reason
    # running LobbyServerApp with subprocess.Popen() with stdout redirection to file
    # has no effect -- file remains empty
    return [], []
    
    if not exists(LOBBY_LOG):
      raise errors.TestFailed( "Can't locate lobby server run log" )

    f = open(LOBBY_LOG, 'r')
    text = f.read()
    f.close()
    
    clients = findall(SERVMSG_CLIENT_LOGIN, text)
    users = findall(SERVMSG_USER_CONNECT, text)
    
    return clients, users

  def analyzeLogs(self):
    for g in self.games:
      g.analyzeLog()
    
    # server log not available
    return
    
    clients, users = self.analyzeServerLog()
    
    not_logged_in = [ g for g in self.games if str(g.userId) not in clients ]
    not_connected = [ g for g in self.clients if (str(g.userId), g.machine) not in users ]
    
    failed = [ g.machine for g in self.games if g in not_logged_in or g in not_connected ]

    if failed != []:
      raise errors.TestFailed( "Server has not reported connection from following clients: %s" % ' '.join(failed) )
  
  def updateClientsStatus(self):
    # run query through coordinator
    cmd = '%s query --noresolve  %s > %s' % ( CoordinatorPath(), ' '.join([c.ip for c in self.clients]), COORDINATOR_LOG_TMP )
    logging.debug('query cmd: ' + cmd)
    system(cmd)
    
    if not exists(COORDINATOR_LOG_TMP):
        raise errors.TestFailed("Failed to query network status")
        
    # read query log
    f = open(COORDINATOR_LOG_TMP, 'r')
    if f == None:
      raise errors.TestFailed("Failed to query network status")
    text = f.read()
    f.close()  
    
    # create query result in form of dictionary
    machines = {}
    for line in text.splitlines():
      words = line.split()
      if len(words) == 3 and words[2] == 'IDLE':
        machines[words[0]] = words[1], words[2]

    # update status
    for c in self.clients:
      if machines.has_key(c.ip):
        build, c.status = machines[c.ip]
        if build == 'NO_BUILD':
          c.build = -1
        else:
          c.build = int(build)

  def killAll(self):
    # kill all remote running games
    cmd = '%s kill %s' % ( CoordinatorPath(), ' '.join([c.ip for c in self.clients]) )
    logging.debug('kill cmd: ' + cmd)
    system(cmd)
    
    for c in self.clients:
      c.status = 'IDLE'
    
    self.server.kill()

  def runLobbyServer(self):
    # create private.cfg that ensures local authentication
    f = open(join(self.root, r'Profiles\private.cfg'), 'w')
    f.write('setvar authentication_service = local')
    f.close()
    
    # run lobby server from Bin folder so that it uses private.cfg
    _,_,self.lobby = processes.launchApp( LobbyServerPath(self.pd.configuration), '', join(self.root, 'Bin') )

  @staticmethod
  def pushUpRightBuild(client1, client2):
    if client1.build == sourceManager.singleton.version and client2.build != sourceManager.singleton.version:
        return -1
    return 0
  
  def run(self):
    if self.maxNumPlayers <= 1:
      raise errors.TestFailed( "Error - max number of players set to %d" % self.maxNumPlayers )
    
    if len(self.clientNames) == 0:
      raise errors.TestFailed( "No client machines specified" )
    
    self.server = GameInstance(bServer = True, rootFolder = self.root)
    self.clients = [ GameInstance(bServer = False, machine = n)  for n in self.clientNames ]

    self.updateClientsStatus()

    # remove non-idle clients
    self.clients = [ c for c in self.clients if c.status == 'IDLE' ]
    
    logging.info('Idle clients reported: ' + ' '.join([ c.machine for c in self.clients ]))
    
    # sort clients so that those having correct build are on top
    self.clients.sort(cmp = self.pushUpRightBuild)
    
    # leave only the number of clients required
    if len(self.clients) > self.maxNumPlayers - 1:
      del self.clients[self.maxNumPlayers - 1:]

    logging.info('Clients selected for test: ' + ' '.join([ c.machine for c in self.clients ]))

    # deploy data for all games
    for g in self.clients + [self.server]:
      g.deploy(sourceManager.singleton.version)
    
    # remove clients with failed deployment
    wrongBuild = [ c.machine for c in self.clients if c.build != sourceManager.singleton.version ]
    if len(wrongBuild) > 0:
      logging.info('Failed to deploy data to: ' + ' '.join(wrongBuild))
    self.clients = [ c for c in self.clients if c.build == sourceManager.singleton.version ]
    
    if len(self.clients) < 1:
      raise errors.TestFailed( "No clients available" )

    self.games = [self.server] + self.clients
    
    try:
      # run lobby server
      logging.info('Running lobby server on %s' % self.server.machine)
      self.runLobbyServer()
      
      # run game in server mode
      logging.info('Running host on %s' % self.server.machine)
      self.server.run(self.pd.configuration, numPlayers = len(self.games))
      
      # give server some time to get up
      time.sleep(10)
      
      # run games in client mode
      for c in self.clients:
        logging.info('Running client on %s' % c.machine)
        c.run(self.pd.configuration, serverIp = self.server.ip, numPlayers = len(self.games))

      # give everybody some time to finish execution
      time.sleep(300)

      # kill lobby server
      try:
        TerminateProcess(self.lobby, -1)
      except pywintypes.error, e:
        pass    

      # check that all games exited cleanly
      self.server.updateStatus()
      self.updateClientsStatus()
      hanged = [ g.machine for g in self.games if g.status == 'RUNNING' ]
      if len(hanged) > 0:
        logging.info("Following machines hanged: " + ' '.join(hanged))

    finally:
      # clean up
      self.killAll()

      for game in self.games:
        game.cleanup()


    # check run logs
    self.analyzeLogs()
    
    # check for assert / exception logs
    bAssertsExcpts = False
    for game in self.games:
      bAssertsExcpts |= game.checkAssertExcptLogs()
    
    if len(hanged) > 0:
      if bAssertsExcpts:
        raise errors.NetworkTestCrashed([ (g.machine, g.assertLog) for g in self.games if g.assertLog != None ], [ (g.machine, g.excptLog) for g in self.games if g.excptLog != None  ])
      else:
        raise errors.TestHanged(self)
