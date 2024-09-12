# -*- coding: utf-8 -*-

import unittest
import sys, os, time, json, logging
import ujson, bson, functools
import math
import gc
import copy
import timeit

os.chdir('..')
sys.path.append( os.path.abspath('.') )

sys.path.append('base')
sys.path.append('cfg')
sys.path.append('requests')
sys.path.append('modeldata')
sys.path.append('logic/requests')
from helpers import * 

from modeldata.ModelData import ModelData
from modeldata.Hero import Hero
from modeldata.Talent import Talent
from modeldata.validator import Validator
from modeldata import jsonserialize
import modeldata.ref 
from modeldata import collects
from modeldata.Hero_base import Hero_base
from config.MultiConfig import *
from modeldata.persistent_data import PersistentDataManager
from iserialmodel import ISyncSerialModel

#DEFAULT_LOG_LEVEL = logging.INFO
DEFAULT_LOG_LEVEL = logging.WARNING

import xdbload
from modeldata.MultiStaticData import MultiStaticData
from config.ConfigData import ConfigData
from MM import ESex

from ifactory import IfaceFactory
from handlers import PWSOC_VERSION
import istats
        
from modeldata.datamanager import PwNewModelManager
from fake_guid import FakeWSGuidGenerator

def testLoad( self, filename="tests/model_test.dump" ):
    json_file = open( filename, "rt" )
    assert json_file
    json_string = json_file.read()
    info( "loaded json_string: %s \n...\n %s" % (json_string[:256], json_string[-256:]) )

    changeWriter = None
    md = ModelData( )
    
    t0 = time.time()
    md.load( json_string )
    t1 = time.time()
    
    assert md.next_uid == 827 
    assert len(md.HeroesKeeper) == 25 
    assert len(md.ItemsKeeper) == 800 
    
    warn( "============ md2 init ============" )
    t20 = time.time()
    md2 = ModelData( )
    t21 = time.time()
    warn( "============ md2 load ============" )
    t2 = time.time()
    simple_dict = ujson.decode(json_string)
    t3 = time.time()
    md2._serializator.fromDict( simple_dict )
    t4 = time.time()
    
    t23 = time.time()
    md3 = ModelData()
    heroes = {}
    for i in xrange(25):
        hero, heroId = md3.newHero()
        for tsId in hero.TalentSets.keys():
            for j in xrange(32):
                talent, talentId = md3.newTalent()
                hero.hero.TalentSets[tsId].Talents.add( j, talent )
        heroes[i] = hero
    t24 = time.time()
    
    assert md2.next_uid == 827 
    assert len(md2.HeroesKeeper) == 25 
    assert len(md2.ItemsKeeper) == 800 
    
    warn( "loaded: %.3f (construct: %.3f, decode: %.3f, fromDict: %.3f; construct 25/800: %.3f) seconds. heroes count: %d, talents count: %d, next_uid: %d" \
        % (t1-t0, t21-t20, t3-t2, t4-t3, t24-t23, len(md.HeroesKeeper), len(md.ItemsKeeper), md.next_uid) )
        
    data = md2.getJsonDict()
    warn( "md2 jsonDict data: %s" % str(data)[:1024] )
        

def pureCreate():
    t23 = time.time()
    md3 = ModelData()
    heroes = {}
    for i in xrange(25):
        hero, heroId = md3.newHero()
        for tsId in hero.TalentSets.keys():
            for j in xrange(32):
                talent, talentId = md3.newTalent()
                hero.hero.TalentSets[tsId].Talents.add( j, talent )
        heroes[i] = hero
    t24 = time.time()
    
    warn( "construct 25/800: %.3f seconds" % (t24-t23) )
        
    #data = md3.generateJsonDict()
    #warn( "pure create generateJsonDict data: %s" % str(data)[:1024] )

def pureLoad():
    json_file = open( "tests/user_data.dan_PWN.dump", "rt" )
    assert json_file
    json_string = json_file.read()

    t0 = time.time()
    
    md2 = ModelData( )
    
    t1 = time.time()
    
    simple_dict = ujson.decode(json_string)
    
    t2 = time.time()
    
    md2._serializator.fromDict( simple_dict )
    
    t3 = time.time()
    
    #~ assert md2.next_uid == 827 
    #~ assert len(md2.HeroesKeeper) == 25 
    #~ assert len(md2.ItemsKeeper) == 800 
    
    warn( "md2 create: %.3f, decode: %.3f, fromDict: %.3f" % (t1-t0, t2-t1, t3-t2) )
    
    return md2
    
    
def loadAndDump():
    json_file = open( "tests/model_test.dump", "rt" )
    assert json_file
    json_string = json_file.read()

    t0 = time.time()
    
    md2 = ModelData( )
    simple_dict = ujson.decode(json_string)
    md2._serializator.fromDict( simple_dict )
    
    t1 = time.time()
    
    assert md2.next_uid == 827 
    assert len(md2.HeroesKeeper) == 25 
    assert len(md2.ItemsKeeper) == 800 

    t2 = time.time()
    
    data = md2.generateJsonDict()
    
    t3 = time.time()
    warn( "md2 generateJsonDict data: %s" % str(data)[:1024] )
    
    data_file = open( "tests/json_dict_data.dump", "wt" )
    data_file.write( str(data) )
    data_file.close()
    
    t4 = time.time()
    
    pretty_data = pretty(data)
    
    t5 = time.time()
    #warn( "md2 PRETTY jsonDict data: %s" % pretty_data[:1024] )
    
    data_file = open( "tests/pretty_jsondict_data.dump", "wt" )
    data_file.write( pretty_data )
    data_file.close()
    
    warn( "md2 decode: %.3f, generateDict: %.3f, PRETTY: %.3f" % (t1-t0, t3-t2, t5-t4) )
    
    
def loadEncode():
    md = pureLoad()
    
    t0 = time.time()
    
    data = md.generateJsonDict()
    
    t1 = time.time()
    
    ujson_data = ujson.encode( data )
    
    t2 = time.time()
    
    warn( "md2 generate: %.3f, encode: %.3f" % (t1-t0, t2-t1) )
    
    return md


##----------------------------------------------------------------
##----------------------------------------------------------------

def loadUserData( iDict, filename="tests/ap70_0.dat" ):
    json_file = open( filename, "rt" )
    assert json_file
    json_string = json_file.read()
    
    data_dict = json_loads( json_string )
    cached_dict = data_dict.pop("data", {})
    persistent_dict = data_dict.pop("db", {})
    
    acc = ClassDict()
    acc.data = createClassDict( cached_dict )
    acc.db = createClassDict( persistent_dict.pop("db", {}) )
    
    fraction = acc.db.fraction or "A"
    sex = acc.db.sex or ESex.FEMALE
    
    warn("db fraction: %s, db sex: %s" % (acc.db.fraction, acc.db.sex))
        
    model_string = persistent_dict.pop("model", "")
    
    SMODEL = IfaceFactory.makeSerialModelInterface("sync", iDict, PWSOC_VERSION, load_conversion_xml=False)
    SMODEL.loadSerialModel( 1, model_string, fraction, sex, ClassDict(), 0, None, iDict.Config, iDict.SD, "RU", "RU", onUserDataLoadedOk )
   
    
def loadUserData_FromAP8DUMP( iDict, filename="tests/ap70_0.dat" ):
    json_file = open( filename, "rt" )
    assert json_file
    json_string = json_file.read()
    
    data_dict = json_loads( json_string )
    cached_dict = data_dict.pop("data", {})
    persistent_dict = data_dict.pop("db", {})
    
    acc = ClassDict()
    acc.data = createClassDict( cached_dict )
    acc.db = createClassDict( persistent_dict.pop("db", {}) )
    
    fraction = acc.db.fraction or "A"
    sex = acc.db.sex or ESex.FEMALE
    
    warn("db fraction: %s, db sex: %s" % (acc.db.fraction, acc.db.sex))
        
    model_dict = persistent_dict.pop("model", "")

    warn( "original json dict hero 1: %s" % json_pretty(model_dict["ModelData"]["HeroesKeeper"]["Keeper"]["1"]) )
    
    model_json_string = json_dumps(model_dict)
    
    SMODEL = IfaceFactory.makeSerialModelInterface("sync", iDict, PWSOC_VERSION, load_conversion_xml=False)
    SMODEL.loadSerialModel( 1, model_json_string, fraction, sex, ClassDict(), 0, None, iDict.Config, iDict.SD, "RU", "RU", onUserDataLoadedOk )

def onUserDataLoadedOk( reply ):
    warn( "onUserDataLoadedOk reply: %s" % str(reply)[:1024] )
    global return_acc
    return_acc = reply["r"]


##----------------------------------------------------------------
##----------------------------------------------------------------

def loadStaticData( xdb_path ):
    iDict = ClassDict()
    
    info( "Loading XML heroes/talents..." )
    t0 = time.time()
    t1 = time.time()
    iDict.Config = MultiConfig()
    iDict.SD = MultiStaticData( xdb_path + "/ExportedSocialData.xml", iDict.Config.getMainConfig() ).getMainSD()
    iDict.Config.getMainConfig().fillStaticDataDependendValues(iDict.SD)
    t2 = time.time()
    
    warn( "XML heroes/talents loaded(%.3f sec): sections count %d" % ( t1-t0, len(iDict.SD.data) ) )
    warn( "StaticData loaded(%.3f sec)" % ( t2-t1 ) )
    warn( "static data garbage count: %d" % gc.collect()) # после загрузки StaticData образуется куча garbage
    
    iDict.STATS = istats.IStats( "", None )

    return iDict 
    
def fullCreate( iDict, fraction, sex, server_version, guest ):
    acc = ClassDict( data=ClassDict() )
    
    t0 = time.time() #------
    
    acc.model = ModelData()
    acc.model.init( changeWriter=None ) 
    
    t1 = time.time() #------
    
    acc.model.create( iDict, acc, create_version=unicode(server_version), create_heroes=-1, fraction=fraction, sex=sex, guest = guest )
    
    t2 = time.time() #------
    
    # строим вспомогательные индексы
    acc.model.buildCrossIndexes( acc.data ) 
    # на случай если размещение талантов в defaultTalentSet не совпадает с указанными рядами для талантов, надо пройтись по всем TalentSets и выкинуть "неподходящие" таланты в инвентарь
    for i in xrange(3):
        Validator.validateTalentSets( acc, server_version, iDict.SD, i )
    
    t3 = time.time() #------
    
    warn( "new modeldata timing: new/init %.3f, create %.3f, cross/validate %.3f" % (t1-t0, t2-t1, t3-t2) )
    
    return acc


def helper_fullCreate():
    fullCreate( iDict, "A", ESex.MALE, "1.1.1", 0 )


##def fullLoad( iDict, fraction, sex, server_version )


##----------------------------------------------------------------
##----------------------------------------------------------------

import cProfile, pstats

def action_callback( reply ):
    print "action_callback: %s" % reply

def main1():
    logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )
 
    global iDict
    iDict = loadStaticData( "xdb" )
    #~ acc = fullCreate( iDict, "A", ESex.MALE, "1.1.1" )
    
    #~ warn( "acc.model: %s" % str(acc.model.generateJsonDict())[:2048] )
    
    #loadUserData( iDict, "tests/user_data.dan.AP8.dump" )
    loadUserData_FromAP8DUMP( iDict, "tests/user_data.dan.AP8.dump" )
    model_dict = return_acc.model.generateJsonDict()
    warn( "loaded dan json dict talent 1564: %s" % json_pretty(model_dict["ModelData"]["ItemsKeeper"]["Keeper"][1564]) )
    warn( "loaded dan model talent 1564: %s" % str(return_acc.model.ItemsKeeper.get(1564).__dict__) )
    
    warn( "loaded dan model talent 1564 soulbound: %s" % str(return_acc.model.ItemsKeeper.get(1564).Soulbound.__dict__) )
    warn( "loaded dan model talent 1564 soulbound realdict dictionary: %s" % str(return_acc.model.ItemsKeeper.get(1564).Soulbound.realdict.dictionary) )
    
    warn( "loaded dan json dict hero 232: %s" % json_pretty(model_dict["ModelData"]["HeroesKeeper"]["Keeper"][232]) )

    warn( "loaded dan json dict hero 1: %s" % json_pretty(model_dict["ModelData"]["HeroesKeeper"]["Keeper"][1]) )
    warn( "loaded dan model hero 1: %s" % str(return_acc.model.HeroesKeeper.get(1).__dict__) )
    
    warn( "loaded dan json dict UserInventory: %s" % json_pretty(model_dict["ModelData"]["UserInventory"]["Set"]) )
    
    warn( "loaded dan json dict INV talent 1455: %s" % json_pretty(model_dict["ModelData"]["ItemsKeeper"]["Keeper"][1455]) )
    warn( "loaded dan model INV talent 1455: %s" % str(return_acc.model.ItemsKeeper.get(1455).__dict__) )
    
    warn( "loaded dan model INV talent 1455 soulbound realdict dictionary: %s" % str(return_acc.model.ItemsKeeper.get(1455).Soulbound.realdict.dictionary) )
    warn( "loaded dan model INV talent 1455 defaultForHero realdict dictionary: %s" % str(return_acc.model.ItemsKeeper.get(1455).defaultForHero.realdict.dictionary) )
    
    iDict.WS = FakeWSGuidGenerator()
    iDict.MD = PwNewModelManager( ifaceDict=iDict, load_events=False )
    
    acc = ClassDict( uid=1, model=return_acc.model, data=return_acc.data, pending_events=[], sex=ESex.MALE, db=ClassDict(fraction="A") )
    
    from logic.item_move_inv2ts import *
    
    for hero_id in [661]:
        ifaces = ClassDict( I=iDict, acc=acc )
        request = ItemMoveInvToTsRequest( return_acc.model, { 
            "src_hero_id" : ["" + str(hero_id) + ""],
            "src_item_id" : ["" + str(1455) + ""], 
            "dest_slot_id" : ["" + str(24) + ""], 
            "dest_item_id" : ["" + str(0) + ""],
            "rid" : ["" + str(1) + ""] 
        } )
  
        action = Item_move_inv2ts( request, action_callback, request=ifaces )
        action.onStart()
        
    #warn( "full md2: %s" % json_pretty( md2.generateJsonDict() ))
    
    #~ cProfile.run('helper_fullCreate()', 'cprofile.log')
    
    #~ p = pstats.Stats('cprofile.log')
    #~ p.strip_dirs().sort_stats('time').print_stats()

## -----------------------------------------------------------------------------------------------------
## -----------------------------------------------------------------------------------------------------

def onUserDataCreatedOk( reply ):
    ##warn( "onUserDataCreatedOk reply: %s" % str(reply)[:1024] )
    global return_acc
    return_acc = reply["r"]
    
## -----------------------------------------------------------------------------------------------------

def createSModel( iDict ):
    global SMODEL
    SMODEL = IfaceFactory.makeSerialModelInterface("sync", iDict, PWSOC_VERSION, load_conversion_xml=False)
    
def runSModel( auid=1, fraction="A", sex=ESex.MALE, guest=0, db=ClassDict(), userlocale="RU", country_code="RU", callback=onUserDataCreatedOk ):
    SMODEL.newSerialModel(auid, fraction, sex, guest, db, None, iDict.Config, iDict.SD,  userlocale, country_code,False, callback)
        
def testModel( model ):
    assert model
    assert model.HeroesKeeper
    assert model.ConstructionsKeeper is not None
    assert model.ItemsKeeper
    assert model.UserInventory is not None
    assert model.Heroes
    assert model.version
    assert model.Resources
    
    assert (model.LordInfo.Fame is not None) and isinstance(model.LordInfo.Fame, float)
    assert (model.next_uid_ is not None) and isinstance(model.next_uid_, int)
    assert model.next_uid_ > 0
    
    hero = model.HeroesKeeper.get(1)
    assert hero
    assert hero.class_name and isinstance(hero.class_name, basestring)
    assert hero.refCounter is not None and isinstance(hero.refCounter, int)
    assert hero.path and isinstance(hero.path, basestring)
    assert hero.id and isinstance(hero.id, int)
    
    talent = model.ItemsKeeper.get(3)
    assert talent
    assert talent.PersistentId and isinstance(talent.PersistentId, int)
    assert talent.refCounter and isinstance(talent.refCounter, int)
    assert talent.IsNew is not None and isinstance(talent.IsNew, bool)
    assert talent.path and isinstance(talent.path, basestring)
    assert talent.id and isinstance(talent.id, int)
    
    ref = talent.Soulbound 
    assert ref and isinstance(ref, modeldata.ref.Ref)
    assert ref.path and isinstance(ref.path, basestring)
    assert ref.realdict and isinstance(ref.realdict, collects.Keeper) and ref.realdict == model.HeroesKeeper
    assert ref.object and isinstance(ref.object, int) and ref.realdict.get( ref.object )

    ref = talent.defaultForHero 
    assert ref and isinstance(ref, modeldata.ref.Ref)
    assert ref.path and isinstance(ref.path, basestring)
    assert ref.realdict and isinstance(ref.realdict, collects.Keeper) and ref.realdict == model.HeroesKeeper
    assert ref.object and isinstance(ref.object, int) and ref.realdict.get( ref.object )
        

## -----------------------------------------------------------------------------------------------------

class Ref1( modeldata.ref.Ref ):
    def __init__(self):
        pass

class Talent1( Talent ):
    def __init__(self):
        pass

## -----------------------------------------------------------------------------------------------------

def prof_loadFromMain():
    _md = ModelData()
    _md._serializator.opt_fromMain( decoded_md )


def main2():
    logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )

    #~ for i in xrange(36):
        #~ warn( "%d -> int(math.ceil(i/6)):%d" % (i+1, int(math.ceil((i+1)/6))) )

    global iDict
    iDict = loadStaticData( "xdb" )
    
    # ######################################################
    # loadUserData( iDict, "tests/user_data.dan.dump" )
    # ######################################################
    
    createSModel( iDict )
    
    warn( "---- Hero_base times: %.3f, %.3f, %.3f" % (Hero_base.Hero_base_t1, Hero_base.Hero_base_t2, Hero_base.Hero_base_t3) )
    t0 = time.time()

    runSModel()
    
    t1 = time.time()
    warn( "---- Hero_base times: %.3f, %.3f, %.3f; total new model: %.3f" % (Hero_base.Hero_base_t1, Hero_base.Hero_base_t2, Hero_base.Hero_base_t3, t1-t0) )
    
    model_dict = return_acc.model.generateJsonDict()
    testModel( return_acc.model )
    
    #warn( "created new model, json dict: %s" % json_pretty(model_dict)[:1024] )
    dumpfile = open("tests/smodel.hacked2.create.%d.txt" % time.time(), "wt")
    dumpfile.write(json_pretty(model_dict))
    dumpfile.close()
            
    json_md = ujson.encode(model_dict)
    t20 = time.time()
    global decoded_md # нужна для prof_loadFromMain
    decoded_md = ujson.decode(json_md)
    t21 = time.time()
    ##warn( "decoded ujson model in %.3f, decoded result: %s" % (t21-t20, json_pretty(model_dict)[:2048]) )
    
    t22 = time.time()
    _md = ModelData()
    _md._serializator.opt_fromMain( decoded_md )
    t23 = time.time()
    warn( "decoded model_dict in %.3f" % (t23-t22) )
    
    # ########################################################################
    # чтобы таланты без Ref-ов смогли сохраниться, нужно подменить метод-генератор
    Talent.generateJsonDict = Talent.generateJsonDict_2
    # ########################################################################
    
    decoded_model_dict = _md.generateJsonDict()
    warn( "decoded model_dict result: %s" % (json_pretty(decoded_model_dict)[:2048]) )
    
    #! при этом меняется порядок ключей в словарях, т.к. числовые ключи в MD =int, а в json-е =string
    dumpfile = open("tests/smodel.hacked.DECODED.NOREF.%d.txt" % time.time(), "wt") 
    dumpfile.write(json_pretty(decoded_model_dict))
    dumpfile.close()
    
    # проверяем целостность MD, загруженной через fromMain
    testModel( _md )
    
    _talent = return_acc.model.ItemsKeeper.get(2)
    _ref = _talent.Soulbound 
   
    t30 = time.time()
    talentDict = {}
    for i in xrange(800):
        talent = Talent1()
        object.__setattr__(talent, "__dict__", _talent.__dict__)
        talentDict[i] = talent
    refDict = {}
    for i in xrange(1600):
        ref1 = Ref1()
        object.__setattr__(ref1, "__dict__", _ref.__dict__)
        refDict[i] = ref1
    t31 = time.time()
    warn( "created 800+1600 empty objects: %.3f, talentDict: %s" % (t31-t30, str(talentDict[1].__dict__)[:1024]) )

    #PROFILE СОЗДАНИЯ:
    #~ cProfile.run('runSModel()', 'cprofile.log')
    
    #PROFILE загрузки (fromMain):
    cProfile.run('prof_loadFromMain()', 'cprofile.log')
    
    p = pstats.Stats('cprofile.log')
    p.strip_dirs().sort_stats('cumulative').print_stats()
    p.strip_dirs().sort_stats('time').print_stats()
    
#--------------------------------------------------------------------------

def main3_create_only():
    warn( "---- Hero_base times: %.3f, %.3f, %.3f" % (Hero_base.Hero_base_t1, Hero_base.Hero_base_t2, Hero_base.Hero_base_t3) )
    t0 = time.time()

    runSModel()
    
    t1 = time.time()
    warn( "---- Hero_base times: %.3f, %.3f, %.3f (total Hero_base: %.3f); total new model: %.3f" \
        % (Hero_base.Hero_base_t1, Hero_base.Hero_base_t2, Hero_base.Hero_base_t3, Hero_base.Hero_base_t1+Hero_base.Hero_base_t2+Hero_base.Hero_base_t3, t1-t0) )
    
    model_dict = return_acc.model.generateJsonDict()
    testModel( return_acc.model )
    
    #warn( "created new model, json dict: %s" % json_pretty(model_dict)[:1024] )
    dumpfile = open("tests/smodel.original.create.%d.txt" % time.time(), "wt")
    dumpfile.write(json_pretty(model_dict))
    dumpfile.close()

    dumpfile = open("tests/last_create_test.dump", "wt")
    dumpfile.write(json_pretty(model_dict))
    dumpfile.close()
    
    #PROFILE создания:
    t0 = time.time()
    cProfile.run('runSModel()', 'cprofile.log')
    t1 = time.time()
    warn( "---- PROFILE Hero_base times: %.3f, %.3f, %.3f (total Hero_base: %.3f); total new model: %.3f" \
        % (Hero_base.Hero_base_t1, Hero_base.Hero_base_t2, Hero_base.Hero_base_t3, Hero_base.Hero_base_t1+Hero_base.Hero_base_t2+Hero_base.Hero_base_t3, t1-t0) )
        
    p = pstats.Stats('cprofile.log')
    p.strip_dirs().sort_stats('cumulative').print_stats()
    p.strip_dirs().sort_stats('time').print_stats()

    
## -----------------------------------------------------------------------------------------------------
## -----------------------------------------------------------------------------------------------------

def testLoad_MD_only( filename="tests/last_create_test.dump" ):
    json_file = open( filename, "rt" )
    assert json_file
    json_string = json_file.read()
    info( "loaded json_string: %s \n...\n %s" % (json_string[:256], json_string[-256:]) )

    changeWriter = None
    md = ModelData( )
    
    t0 = time.clock()
    md.load( json_string )
    t1 = time.clock()
    
    warn( "---- PURE MD.LOAD TIME: %.3f" % (t1-t0) )
    
    testModel( md )
    
    return md
    
    
#--------------------------------------------------------------------
# грузим с профилированием (результат профайла идет в файл "Lprofile.log")
def profile_runTestLoad_MD_only():
    md.load( json_string )
    
def profile_TestLoad_MD_only( filename="tests/last_create_test.dump" ):
    json_file = open( filename, "rt" )
    assert json_file
    global json_string 
    json_string = json_file.read()
    info( "loaded json_string: %s \n...\n %s" % (json_string[:256], json_string[-256:]) )

    changeWriter = None
    global md
    md = ModelData( )
    
    cProfile.run('profile_runTestLoad_MD_only()', 'Lprofile.log')
    
        
def main4_load_only():
    md = testLoad_MD_only()

    #PROFILE загрузки:
    profile_TestLoad_MD_only()
    p = pstats.Stats('Lprofile.log')
    p.strip_dirs().sort_stats('cumulative').print_stats()
    p.strip_dirs().sort_stats('time').print_stats()
    
    # DUMP
    model_dict = md.generateJsonDict()
    dumpfile = open("tests/last_load_test.dump", "wt")
    dumpfile.write(json_pretty(model_dict))
    dumpfile.close()
    
## -----------------------------------------------------------------------------------------------------
## -----------------------------------------------------------------------------------------------------
    
def main5_create_noprofile():
    ## warn( "---- Hero_base times: %.3f, %.3f, %.3f" % (Hero_base.Hero_base_t1, Hero_base.Hero_base_t2, Hero_base.Hero_base_t3) )
    t0 = time.time()

    runSModel()
    
    t1 = time.time()
    warn( "---- Hero_base times: %.3f, %.3f, %.3f (total Hero_base: %.3f); total new model: %.3f" \
        % (Hero_base.Hero_base_t1, Hero_base.Hero_base_t2, Hero_base.Hero_base_t3, Hero_base.Hero_base_t1+Hero_base.Hero_base_t2+Hero_base.Hero_base_t3, t1-t0) )
        
## -----------------------------------------------------------------------------------------------------
## -----------------------------------------------------------------------------------------------------
    
## print "ceil:", int( math.ceil(1/6) )

if __name__ == "__main__":
    logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )
    gc.disable()

    global iDict
    iDict = loadStaticData( "xdb" )
    iDict.coord_res = ClassDict(deploy_name="RU")
    if not getattr(iDict, "MD"):
        iDict.MD = PwNewModelManager( ifaceDict=iDict, load_events=False )
    createSModel( iDict )
    
    main3_create_only()
    main4_load_only()    
    
    #main5_create_noprofile()
    #print "gc counts: %s" % str(gc.get_count())
    
    #~ t0 = time.time()
    #~ try:
        #~ model2 = copy.deepcopy( return_acc.model )
    #~ except:
        #~ catch()
    #~ t1 = time.time()
    
    #~ print "deepcopy time: %.3f" % (t1-t0) #, model2 dict: %s" , model2.generateJsonDict())
    
    #~ for x in gc.garbage:
        #~ print "garbage: %s" % str(x)

    gc.set_debug( gc.DEBUG_SAVEALL )
    gc_collected_count = gc.collect()
    print "gc collected: %d, garbage size: %d" % (gc_collected_count, len(gc.garbage))
    
