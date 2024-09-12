#!/usr/bin/env python
# -*- coding: utf-8 -*-
# (C) Vadim Petrov 2011, Nival

import os, sys, gc, json, logging, re, fnmatch, imp, glob, inspect
realpath = os.path.dirname( __file__ )
sys.path.append(os.path.join(realpath, '../..'))
sys.path.append(os.path.join(realpath, '../../base'))
sys.path.append(os.path.join(realpath, '../../cfg'))
sys.path.append(os.path.join(realpath, '..'))
sys.path.append(os.path.join(realpath, '../requests'))
from helpers import *
import xdbload
from modeldata.ModelData import ModelData
from friendsdata.FriendsData import FriendsData
from party.PartyData import PartyData
from guild.GuildData import GuildData
from siege.SiegeData import SiegeData
from config.MultiConfig import MultiConfig
from modeldata.changes import GroupPendingChangeWriter
from modeldata.datamanager import PwNewModelManager
from modeldata.persistent_data import PersistentDataManager
from iserialmodel import ISyncSerialModel
from iwebserver import IWebServer
from modeldata.MultiStaticData import MultiStaticData
from ifactory import IfaceFactory
DEFAULT_LOG_LEVEL = logging.DEBUG
FAKE_PWSOC_SERVER_VERSION = "1.2.3"
import ibilling
from subaction import ResponseObject
from pwaccount import UserAccount
from guild.iguildservice import IDummyGuildService
from ixchange import IFakeSocialExchange
from ihttp import IHttpDummyPeerNotify
import cfg
import coord_cfg


def matchPatterns(name, patterns, ignored = []):
  for mask in ignored:
    #TODO
    #print "MASK", mask, fnmatch.translate( mask ), name
    if re.match( fnmatch.translate( mask ), name ):
      return None
    if name.find( mask ) != -1:
      return None
  for pattern in patterns:        
    if re.match( fnmatch.translate( pattern ), name ):
      return pattern        
  return None        


def collectFiles(path, patterns, ignored = [], recursive=True, add_root=True):
  result = []
  for root, dirs, files in os.walk(path):
    for name in files:
      relativePath = os.path.join( root, name )[len(path)+1:]
      if matchPatterns(relativePath, patterns, ignored):
        value = os.path.join(root, name)
        if not add_root:
          value = value[len(path)+1:]    
        result.append(value)
    if not recursive:
      break                    
  return result


class FakeWSGuidGenerator:
  def __init__( self, start_value=0 ):
    self.inc = start_value
  def nextInt64GUID( self, key ):
    self.inc += 1
    return self.inc
  def updateGameDataToPersonServer( self, acc ):
    pass


class fakeSQL:
  def setNick( self, arg1, arg2, callback ):
    callback( {'p':1,'r':[ ClassDict(idok=-1) ]} ) # возвращаем id_ok<0, чтобы SubAction не беспокоился насчет записи в файл никнеймов
  def removeOldNick( self, uid, old_nick, old_nick_encoding):
    pass

  def findUidByNick(self, nick_utf8, callback):
    if nick_utf8 == u'used_nick':
      # мы нашли что-то (пользователя)
      callback( {'p':1,'r':[{'something':0}]} )
    else:
      # не нашли пользователя с таким ником
      callback( {'p':1,'r':[]} )


class ExecActions( object ):
  def __init__( self ):
    params = sys.argv[1:]
    if len( params ) != 8 and len( params ) != 1:
      err( "Must be 8 params: modeldata, friendsdata, configdata, guilddata, siegedata, userinfo, actions, changes. Or batch mode" )
      exit( 1 )

    self.initAll()

    if len( params ) == 1:
      if params[0] == "batch":
        self.doBatch()
    else:
      self.generateChanges( params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7] )


  def doBatch( self ):
    listOfTests = self.getListOfTests()
    for testName in listOfTests:
      mdFile = "md." + testName + ".json"
      fdFile = "fd." + testName + ".json"
      cdFile = "cd." + testName + ".json"
      gdFile = "gd." + testName + ".json"
      sdFile = "sd." + testName + ".json"
      uiFile = "userinfo." + testName + ".txt"
      actFile = "actions." + testName + ".txt"
      chFile = "changes." + testName + ".txt"
      self.generateChanges( mdFile, gdFile, sdFile, fdFile, cdFile, uiFile, actFile, chFile )


  def getListOfTests( self ):
    path = os.getcwd() + "\\tests"
    files = collectFiles( path, ['md.*.json'], recursive=False, ignored=['*.svn*'] )
    testNames = []
    for f in files:
      filename = os.path.basename( f )
      testName = filename[3:-5]
      testNames.append( testName )
    return testNames


  def parseActions( self, actionsFile ):
    if os.path.isfile( "tests/" + actionsFile ):
      file = open( "tests/" + actionsFile )
      actionsLines = file.readlines()
      for line in actionsLines:
        if len( line ) < 10:
          continue
        params = line.split('&')

        actionName = ""
        ActionParams = {}
        
        for param in params:
          token = param.split( '=' )
          if len( token ) != 2:
            err( "Can not parse action %r", line )
            exit( 1 )
          if token[0] == "action":
            actionName = token[1]
          else:
            ActionParams.update( { token[0].replace('\n', '') : [token[1].replace('\n', '')] } )
            
        if actionName not in self.register_requests:
          err( "Unregistered action %r", line )
          exit( 1 )    
        
        ActionRequestClass = self.register_requests[actionName]

        realAction = ActionRequestClass( self.acc.model, ActionParams )
        self.actions.append( (self.register_actions[actionName], realAction) )
        handler =  self.register_actions[actionName]( realAction, self.callback, request=self )
        handler.onStart()
        resfile = open( self.resultFile, "a" )
        for change in self.changeList:
          resfile.write( str(change)+"\n" )
        resfile.close()
        self.changeList = []


  def callback( self, reply ):
    if isinstance( reply, dict ):
      for key in reply:
        if isinstance( reply[key], ResponseObject ):
          reply[key] = reply[key].makeDict()
    reply = json_dumps( reply )
    self.changeList.append( reply )

  def extract_module_names(self, python_files):    
    module_names = []
    files_to_remove = []
    for py_file in python_files:
      # убираем all.py, потому что он импортит все остальные модули внутри себя
      if not "__" in py_file and not "\\all.py" in py_file:
        module_name = (os.path.basename(py_file))[:-3]
        module_names.append(module_name)
      else:
        files_to_remove.append(py_file)
    for rem_file in files_to_remove:
      python_files.remove(rem_file)
    return module_names

  def load_modules(self, modules, py_files):
    module_count = len(modules)
    for i in range(0, module_count):
      module = imp.load_source(modules[i], py_files[i])
      name = modules[i][0].capitalize() + modules[i][1:]

      obj = getattr(module, name)

      self.register_actions[modules[i]] = obj

      parents = obj.__bases__
      for type in parents:
        if type.__module__.endswith("Request"):
          request = type.__module__.replace("logic.requests.", "")

      module = imp.load_source(request, "../requests/" + request + ".py")
      obj = getattr(module, request)        
      self.register_requests[modules[i]] = obj

      globals()[modules[i]] = module

  def importModules(self, path):
    python_files = glob.glob( path + '\\*.py')
    module_names = self.extract_module_names(python_files)
    self.load_modules(module_names, python_files)

  def initAll( self ):

    self.register_requests = {}
    self.register_actions = {}

    self.importModules("../")

    logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )

    cfg.DLCs_INFO = coord_cfg.COORDINATOR_DLCS
    cfg.MUID_TO_DLCS = coord_cfg.COORDINATOR_MUID_TO_DLCS
    cfg.TOURNAMENT_SERVER = coord_cfg.COORDINATOR_TOURNAMENT_SERVER
    cfg.TOURNAMENT_SERVER_ADDR = coord_cfg.COORDINATOR_TOURNAMENT_SERVER_ADDR
    cfg.TOURNAMENT_XSERVER_ADDR = coord_cfg.COORDINATOR_TOURNAMENT_XSERVER_ADDR
    cfg.TOURNAMENT_SPECTATOR_AUIDS = coord_cfg.COORDINATOR_TOURNAMENT_SPECTATOR_AUIDS
    cfg.TOURNAMENT_APPLY_RESULTS = coord_cfg.COORDINATOR_TOURNAMENT_APPLY_RESULTS

    self.I = ClassDict()
    self.I.coord_res = {}
    self.I.coord_res["deploy_name"] = "RU"
    self.I.BILL = IfaceFactory.makeBillingInterface( "dummy", self.I )
    self.I.Config = MultiConfig()
    self.I.MSD = MultiStaticData( "../../xdb/ExportedSocialData.xml", self.I.Config.getMainConfig() )
    self.I.SD = self.I.MSD.getMainSD()
    self.I.Config.getMainConfig().fillStaticDataDependendValues(self.I.SD)
    self.I.GS = IDummyGuildService()
    self.I.WS = IWebServer()
    self.I.MD = PwNewModelManager( ifaceDict=self.I, load_events=False, load_techs=False )
    self.I.PDM = PersistentDataManager( ifaceDict=self.I )
    self.I.SMODEL = ISyncSerialModel( self.I, FAKE_PWSOC_SERVER_VERSION )
    self.I.STATS = IfaceFactory.makeIStatsInterface( "none", "", self.I )
    self.I.SQL = fakeSQL()
    self.I.WS.reset()
    self.I.WS.TEST_MODE = True
    self.I.SEX = IFakeSocialExchange(HTTP=None)
    self.I.HTTP = IHttpDummyPeerNotify()
    self.uid = 1
    self.acc = UserAccount( uid=self.uid, guest=0, pending_events=[] )
    self.acc.loaded = 1
    self.acc.db = ClassDict()
    self.acc.data = ClassDict()
    self.acc.friendsdata = FriendsData()
    self.acc.partydata = PartyData()
    self.acc.guilddata = GuildData()
    self.acc.siegedata = SiegeData()
    self.acc.db.nickChanged = 0
    self.acc.db.fractionChanged = 0
    self.acc.db.dlcs = []
    self.acc.auid = 0
    self.acc.db.auid = 0
    self.acc.snid = "fb"
    self.acc.db.snid = "fb"
    self.acc.snuid = "100001"
    self.acc.db.snuid = "100001"
    self.acc.Config = self.I.Config
    self.acc.SD = self.I.SD    
    self.I.BILL.initBilling( self.acc.auid )
    self.acc.pending = GroupPendingChangeWriter( self.acc )


  def find_imports(self, toCheck):
    importedItems = []
    with open(toCheck, 'r') as pyFile:
      for line in pyFile:
        line = line.strip().split(' ')
        if line[0] == "from" and line[1].endswith("Request"):
          return line[1]

  def loadFromFile( self, filename ):
    if os.path.isfile( "tests/" + filename ):
      file = open( "tests/" + filename )
      result = file.read()
      return result

  def generateChanges( self, mdFile, gdFile, sdFile, fdFile, cdFile, uiFile, actFile, chFile ):
    #print mdFile
    mdStr = self.loadFromFile( mdFile )
    if not mdStr:
      err( "Error read modeldata" )
      exit( 1 )
      
    gdStr = self.loadFromFile( gdFile )
    if not gdStr:
      err( "Error read guilddata" )
      exit( 1 )

    sdStr = self.loadFromFile( sdFile )
    if not sdStr:
      err( "Error read guilddata" )
      exit( 1 )

    fdStr = self.loadFromFile( fdFile )
    if not fdStr:
      err( "Error read friendsdata" )
      exit( 1 )

    configStr = self.loadFromFile( cdFile )
    if not configStr:
      err( "Error read configdata" )
      exit( 1 )

    userinfoStr = self.loadFromFile( uiFile )
    if not userinfoStr:
      err( "Error read userinfo" )
      exit( 1 )
    infos = userinfoStr.split(' ')
    if len( infos ) != 4:
      err( "Error read userinfo" )
      exit( 1 )

    self.resultFile = "tests/" + chFile

    self.changeList = []

    self.I.Config.loadMainConfig( configStr )
    self.acc.sex = int(infos[0])
    self.acc.db.sex = int(infos[0])
    self.acc.db.fraction = infos[1]
    self.acc.db.guildAuid = 1
    self.acc.db.nick = infos[2]
    #TODO:LOFIK:ENCIPHER_TRAFFIC
    #cfg.ENCIPHER_TRAFFIC = int( infos[3] )
    self.I.MD.loadModel( self.acc, mdStr, self.I, FAKE_PWSOC_SERVER_VERSION, fraction=self.acc.db.fraction,
                         sex=self.acc.sex, run_conversion_scripts=False, run_event_scripts=False,
                         generateRandomSeed=False, clear_event_skins=False, validate_guild=False,
                         validate_default_heroes=False, validate_heroes_stats=False, validate_dynamic_quests=False,
                         validate_last_login=False, do_not_change_time=True)
    self.acc.model.initAllTimesCounters()
    self.I.BILL.setGold( self.acc.auid, self.acc.model.Resources.Gold )
    self.acc.friendsdata.load( fdStr )
    self.acc.friendsdata.init( None )
    self.acc.guilddata.load( gdStr )
    self.acc.guilddata.init( None )
    self.acc.partydata.init( None )
    self.acc.guilddata.init( None )
    self.acc.siegedata.init( None )
    self.actions = []
    self.parseActions( actFile )



gc.disable()
main = ExecActions()
