import sys
sys.path.append('../')
from logic.building_upgrade import *
from binascii import crc32
import time
sys.path.append('../..')
from enums import *
import EC

class building_upgrade_test( ):
  def building_upgrade_transmutation_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)

    env.add_construction(modeldata, "Storage")
    env.add_construction(modeldata, "Storage")	

    Resources = env.generate_resources(2000)
    modeldata.Resources = env.generate_resources(2000)

    construction = env.add_construction(modeldata, "Talent_Production")

    assert len( modeldata.Buildings ) == buildCount + 3

    requests = [ ( Building_upgrade, BuildingUpgradeRequest( modeldata,
                                                             { "building_id" : ["" + str(construction.id) + ""],
                                                               "client_time": ["" + str(modeldata.FatClientServerTime) + ""],
                                                               "aftercontext": ["" + str(False) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId( construction.PersistentId )
    assert construction.Level == 0
    # We don't upgrade Transmutation anymore
    #assert env.compare_price( Resources, modeldata.Resources, staticConstruction['Levels']['Item'][construction.Level]['price'])

  def building_upgrade_storage_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    Resources = env.generate_resources(100)
    modeldata.Resources = env.generate_resources(100)

    construction = env.add_construction(modeldata, "Storage")

    requests =  [ ( Building_upgrade, BuildingUpgradeRequest( modeldata,
                                                             { "building_id" : ["" + str(construction.id) + ""],
                                                               "client_time": ["" + str(modeldata.FatClientServerTime) + ""],
                                                               "aftercontext": ["" + str(False) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId( construction.PersistentId )
    assert construction != None
    assert construction.Level == 1
    assert env.compare_price( Resources, modeldata.Resources, staticConstruction['Levels']['Item'][construction.Level]['price'])

  def building_upgrade_production_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    Resources = env.generate_resources(2000)
    modeldata.Resources = env.generate_resources(2000)
    
    construction = env.add_construction(modeldata, "Production_Resource1")

    assert len( modeldata.Buildings ) == buildCount + 1
    assert construction.Level == 0

    requests =  [ ( Building_upgrade, BuildingUpgradeRequest( modeldata,
                                                             { "building_id" : ["" + str(construction.id) + ""],
                                                               "client_time": ["" + str(modeldata.FatClientServerTime) + ""],
                                                               "aftercontext": ["" + str(False) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId( construction.PersistentId )
    construction = modeldata.Buildings.get(construction.id)
    assert construction != None
    assert construction.Level == 1
    assert env.compare_price( Resources, modeldata.Resources, staticConstruction['Levels']['Item'][construction.Level]['price'])

  def building_upgrade_library_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    Resources = env.generate_resources(2000)
    modeldata.Resources = env.generate_resources(2000)
    
    construction = env.add_construction(modeldata, "Library")

    assert len( modeldata.Buildings ) == buildCount + 1
    assert construction.Level == 0

    requests =  [ ( Building_upgrade, BuildingUpgradeRequest( modeldata,
                                                             { "building_id" : ["" + str(construction.id) + ""],
                                                               "client_time": ["" + str(modeldata.FatClientServerTime) + ""],
                                                               "aftercontext": ["" + str(False) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId( construction.PersistentId )
    construction = modeldata.Buildings.get(construction.id)
    assert construction != None
    assert construction.Level == 1
    assert env.compare_price( Resources, modeldata.Resources, staticConstruction['Levels']['Item'][construction.Level]['price'])

  def building_upgrade_house_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    Resources = env.generate_resources(2000)
    modeldata.Resources = env.generate_resources(2000)
    
    construction = env.add_construction(modeldata, "House_4")

    assert len( modeldata.Buildings ) == buildCount + 1
    assert construction.Level == 0

    requests =  [ ( Building_upgrade, BuildingUpgradeRequest( modeldata,
                                                             { "building_id" : ["" + str(construction.id) + ""],
                                                               "client_time": ["" + str(modeldata.FatClientServerTime) + ""],
                                                               "aftercontext": ["" + str(False) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId( construction.PersistentId )
    construction = modeldata.Buildings.get(construction.id)
    assert construction != None
    assert construction.Level == 1
    assert env.compare_price( Resources, modeldata.Resources, staticConstruction['Levels']['Item'][construction.Level]['price'])

  def building_upgrade_heroesbuff_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    Resources = env.generate_resources(10000)
    modeldata.Resources = env.generate_resources(10000)
    
    construction = env.add_construction(modeldata, "BuffHouse_2")
    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId( construction.PersistentId )
    
    points = env.acc.SD.getFloatInterpolated( staticConstruction['HeroesBuildingLevels'], construction.Level, None, "statBufValue", 0 )
    energy = points * env.acc.SD.getStatPointsMultiplyer( "Energy" )
    life = points * env.acc.SD.getStatPointsMultiplyer( "Life" )
    allPoints = points * len( staticConstruction['buffStats']['Item'] )   

    assert len( modeldata.Buildings ) == buildCount + 1
    assert construction.Level == 0
    assert modeldata.getBonusFromBuilding("Energy", env.acc.SD) == energy
    assert modeldata.getBonusFromBuilding("Life", env.acc.SD) == life
    assert modeldata.getStatPointsFromBuilding( env.acc.SD ) == allPoints

    requests =  [ ( Building_upgrade, BuildingUpgradeRequest( modeldata,
                                                             { "building_id" : ["" + str(construction.id) + ""],
                                                               "client_time": ["" + str(modeldata.FatClientServerTime) + ""],
                                                               "aftercontext": ["" + str(False) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    points = env.acc.SD.getFloatInterpolated( staticConstruction['HeroesBuildingLevels'], construction.Level, None, "statBufValue", 0 )
    energy = points * env.acc.SD.getStatPointsMultiplyer( "Energy" )
    life = points * env.acc.SD.getStatPointsMultiplyer( "Life" )  
    allPoints = points * len( staticConstruction['buffStats']['Item'] )   
    
    assert construction.Level == 1
    assert env.compare_price( Resources, modeldata.Resources, staticConstruction['Levels']['Item'][construction.Level]['price'])
    assert modeldata.getBonusFromBuilding("Energy", env.acc.SD) == energy
    assert modeldata.getBonusFromBuilding("Life", env.acc.SD) == life
    assert modeldata.getStatPointsFromBuilding( env.acc.SD ) == allPoints
    
  def building_upgrade_guild_stat_points_bonus_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    
    hero = env.add_hero(modeldata, 'mowgly')
    
    guildPoints = 5

    env.add_construction(modeldata, "Storage")
    env.add_construction(modeldata, "Storage")	

    Resources = env.generate_resources(200000)
    modeldata.Resources = env.generate_resources(200000)

    construction = env.add_construction(modeldata, "Guild")
    tmpGuildLevel = env.acc.SD.data['GuildLevels']['levels']['Item'][1].copy()
    
    env.acc.SD.data['GuildLevels']['levels']['Item'][1]['Bonuses'] = { 'Item' : [ { 'MasterPoints' : guildPoints, 'classType' : 'GuildStatsBonus' } ] }
    
    env.acc.guilddata.GuildLevelInfo.Experience = 100000000

    assert len( modeldata.Buildings ) == buildCount + 3

    requests = [ ( Building_upgrade, BuildingUpgradeRequest( modeldata,
                                                             { "building_id" : ["" + str(construction.id) + ""],
                                                               "client_time": ["" + str(modeldata.FatClientServerTime) + ""],
                                                               "aftercontext": ["" + str(False) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId( construction.PersistentId )
    assert construction.Level == 1
    assert env.compare_price( Resources, modeldata.Resources, staticConstruction['Levels']['Item'][construction.Level]['price'])
    
    assert len(modeldata.Heroes) > 0
    
    for heroId in modeldata.Heroes:
      hero = modeldata.getHeroByID(heroId)
      for tsId in hero.TalentSets.keys():
        ts = hero.TalentSets[tsId]
        assert ts.GuildStats.StatPoints == guildPoints
      
    env.acc.SD.data['GuildLevels']['levels']['Item'][1] = tmpGuildLevel.copy()
    
  def building_upgrade_guild_not_enough_guild_level_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)

    env.add_construction(modeldata, "Storage")
    env.add_construction(modeldata, "Storage")	

    Resources = env.generate_resources(200000)
    modeldata.Resources = env.generate_resources(200000)

    construction = env.add_construction(modeldata, "Guild")

    assert len( modeldata.Buildings ) == buildCount + 3

    requests = [ ( Building_upgrade, BuildingUpgradeRequest( modeldata,
                                                             { "building_id" : ["" + str(construction.id) + ""],
                                                               "client_time": ["" + str(modeldata.FatClientServerTime) + ""],
                                                               "aftercontext": ["" + str(False) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    changeList[0]['ec'] == EC.DEBUG_MESSAGE
    
  def building_upgrade_no_guild_test( self, env ):
    lvl = env.acc.SD.data['GuildLevels']
    modeldata = env.acc.model
    env.acc.guilddata = None
    buildCount = len(modeldata.Buildings)

    env.add_construction(modeldata, "Storage")
    env.add_construction(modeldata, "Storage")	

    Resources = env.generate_resources(200000)
    modeldata.Resources = env.generate_resources(200000)

    construction = env.add_construction(modeldata, "Talent_Production")

    assert len( modeldata.Buildings ) == buildCount + 3

    requests = [ ( Building_upgrade, BuildingUpgradeRequest( modeldata,
                                                             { "building_id" : ["" + str(construction.id) + ""],
                                                               "client_time": ["" + str(modeldata.FatClientServerTime) + ""],
                                                               "aftercontext": ["" + str(False) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId( construction.PersistentId )
    assert construction.Level == 0
    # We don't upgrade Transmutation anymore
    #assert env.compare_price( Resources, modeldata.Resources, staticConstruction['Levels']['Item'][construction.Level]['price'])

  def building_upgrade_tavern_test( self, env ):
    modeldata = env.acc.model
    config = env.I.Config.getConfig( env.acc.userlocale )
    config.ENABLE_TAVERT_REROLL_ON_LEVELUP = True
    buildCount = len(modeldata.Buildings)
    info("Random Seed %r", modeldata.LordInfo.TavernRandomSeed)

    env.add_construction(modeldata, "Storage")
    env.add_construction(modeldata, "Storage")

    Resources = env.generate_resources(200000)
    modeldata.Resources = env.generate_resources(200000)

    construction = env.add_construction(modeldata, "Tavern")

    assert len( modeldata.Buildings ) == buildCount + 3

    requests = [ ( Building_upgrade, BuildingUpgradeRequest( modeldata,
                                                             { "building_id" : ["" + str(construction.id) + ""],
                                                               "client_time": ["" + str(modeldata.FatClientServerTime) + ""],
                                                               "aftercontext": ["" + str(False) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId( construction.PersistentId )
    assert construction.Level == 1
    assert env.compare_price(Resources, modeldata.Resources, staticConstruction['Levels']['Item'][construction.Level]['price'])
