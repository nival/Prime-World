import sys
sys.path.append('../')
from logic.move_to_pocket import *
from binascii import crc32
from base.helpers import *
sys.path.append('../..')
from enums import *

class move_to_pocket_test:

  def move_to_pocket_library_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)

    construction = env.add_construction(modeldata, "Library")

    assert len(modeldata.Pocket) == 0
    assert len(modeldata.Buildings) == buildCount + 1

    requests = [ ( Move_to_pocket, MoveToPocketRequest( modeldata, { "building_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(modeldata.Pocket) == 1
    assert len(modeldata.Buildings) == buildCount

  def building_move_to_pocket_house_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)

    construction = env.add_construction(modeldata, "House_4")

    assert len(modeldata.Pocket) == 0
    assert len(modeldata.Buildings) == buildCount + 1

    requests = [ ( Move_to_pocket, MoveToPocketRequest( modeldata, { "building_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(modeldata.Pocket) == 1
    assert len(modeldata.Buildings) == buildCount
    
  #def building_move_to_pocket_pinetree_test( self, env ):
    #modeldata = env.acc.model
    #buildCount = len(modeldata.Buildings)

    #construction = env.add_construction(modeldata, "PineTree")

    #assert len(modeldata.Pocket) == 0
    #assert len(modeldata.Buildings) == buildCount + 1

    #requests = [ ( Move_to_pocket, MoveToPocketRequest( modeldata, { "building_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    #changeList = env.execActions( requests )

    #assert len(modeldata.Pocket) == 1
    #assert len(modeldata.Buildings) == buildCount    

  def building_move_to_pocket_decoration_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)

    construction = env.add_construction(modeldata, "Decor_Lattern_1")

    assert len(modeldata.Pocket) == 0
    assert len(modeldata.Buildings) == buildCount + 1

    requests = [ ( Move_to_pocket, MoveToPocketRequest( modeldata, { "building_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(modeldata.Pocket) == 1
    assert len(modeldata.Buildings) == buildCount

  def building_move_to_pocket_transmutation_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)

    construction = env.add_construction(modeldata, "Talent_Production")

    assert len(modeldata.Pocket) == 0
    assert len(modeldata.Buildings) == buildCount + 1

    requests = [ ( Move_to_pocket, MoveToPocketRequest( modeldata, { "building_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(modeldata.Pocket) == 1
    assert len(modeldata.Buildings) == buildCount

  def building_move_to_pocket_storage_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)

    construction = env.add_construction(modeldata, "Storage")

    assert len(modeldata.Pocket) == 0
    assert len(modeldata.Buildings) == buildCount + 1

    requests = [ ( Move_to_pocket, MoveToPocketRequest( modeldata, { "building_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(modeldata.Pocket) == 1
    assert len(modeldata.Buildings) == buildCount

  def building_move_to_pocket_production_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)

    construction = env.add_construction(modeldata, "Production_Resource1")

    assert len(modeldata.Pocket) == 0
    assert len(modeldata.Buildings) == buildCount + 1

    requests = [ ( Move_to_pocket, MoveToPocketRequest( modeldata, { "building_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(modeldata.Pocket) == 1
    assert len(modeldata.Buildings) == buildCount

  def move_to_pocket_transmutation_with_talent_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    defaultTalents = len(modeldata.UserInventory)

    construction = env.add_construction(modeldata, "Talent_Production")

    talent = env.add_talent(modeldata, 'G137')

    construction.CraftedTalents.append( talent.PersistentId )

    assert len(modeldata.Pocket) == 0
    assert len(modeldata.Buildings) == buildCount + 1

    assert len(construction.CraftedTalents) == 1
    assert len(modeldata.UserInventory) == defaultTalents

    requests = [ ( Move_to_pocket, MoveToPocketRequest( modeldata, { "building_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(modeldata.Pocket) == 1
    assert len(modeldata.Buildings) == buildCount
    assert len(construction.CraftedTalents) == 0
    assert len(modeldata.UserInventory) == defaultTalents + 1

  def building_move_to_pocket_firstbuy_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)

    construction = env.add_construction(modeldata, "FirstBuy_Cat")

    assert len(modeldata.Pocket) == 0
    assert len(modeldata.Buildings) == buildCount + 1

    requests = [ ( Move_to_pocket, MoveToPocketRequest( modeldata, { "building_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(modeldata.Pocket) == 1
    assert len(modeldata.Buildings) == buildCount
    
    
  def building_move_to_pocket_guild_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)

    construction = env.add_construction(modeldata, "Guild")

    assert len(modeldata.Pocket) == 0
    assert len(modeldata.Buildings) == buildCount + 1

    requests = [ ( Move_to_pocket, MoveToPocketRequest( modeldata, { "building_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(modeldata.Pocket) == 1
    assert len(modeldata.Buildings) == buildCount  


  def building_move_to_pocket_production_building_population_change_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)

    construction = env.add_construction(modeldata, "Talent_Production")

    modeldata.calcResourcesLimit( env.acc.SD, env.acc.guest )

    population = modeldata.Resources.Population

    requests = [ ( Move_to_pocket, MoveToPocketRequest( modeldata, { "building_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert population < modeldata.Resources.Population

    assert len(modeldata.Pocket) == 1


  def building_move_to_pocket_heroesbuff_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)

    construction = env.add_construction(modeldata, "BuffHouse_2")  

    assert len(modeldata.Pocket) == 0
    assert len(modeldata.Buildings) == buildCount + 1
    
    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId( construction.PersistentId )
    points = env.acc.SD.getFloatInterpolated( staticConstruction['HeroesBuildingLevels'], construction.Level, None, "statBufValue", 0 )
    energy = points * env.acc.SD.getStatPointsMultiplyer( "Energy" )
    life = points * env.acc.SD.getStatPointsMultiplyer( "Life" )
    allPoints = points * len( staticConstruction['buffStats']['Item'] ) 
    
    assert modeldata.getBonusFromBuilding("Energy", env.acc.SD) == energy
    assert modeldata.getBonusFromBuilding("Life", env.acc.SD) == life	
    assert modeldata.getStatPointsFromBuilding( env.acc.SD ) == allPoints

    requests = [ ( Move_to_pocket, MoveToPocketRequest( modeldata, { "building_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(modeldata.Pocket) == 1
    assert len(modeldata.Buildings) == buildCount
    assert modeldata.getBonusFromBuilding("Energy", env.acc.SD) == 0.0
    assert modeldata.getBonusFromBuilding("Life", env.acc.SD) == 0.0		
    assert modeldata.getStatPointsFromBuilding( env.acc.SD ) == 0.0

  def building_move_to_pocket_golden_house_population_change_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)

    construction = env.add_construction(modeldata, "GoldProductionHouse")
    staticConstruction = env.acc.SD.getStaticConstruction(construction)

    modeldata.calcResourcesLimit( env.acc.SD, env.acc.guest )

    population = modeldata.Resources.Population

    requests = [ ( Move_to_pocket, MoveToPocketRequest( modeldata, { "building_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.Resources.Population < population
    assert len(modeldata.Pocket) == 1