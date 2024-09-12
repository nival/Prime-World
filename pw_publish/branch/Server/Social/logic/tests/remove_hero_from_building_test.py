import sys
sys.path.append('../')
from logic.remove_hero_from_building import *
from binascii import crc32
sys.path.append('../..')
from enums import *
import EC

class remove_hero_from_building_test:
  def remove_hero_from_building_test( self, env ):   
    modeldata = env.acc.model
    
    construction = env.add_construction(modeldata, "Tavern")
    
    heroes = env.add_heroes_to_construction(modeldata, construction, 1)
    
    assert len(heroes[0].InBuildings) == 1 
    assert len(construction.HeroesInBuilding) == 1

    requests = [ ( Remove_hero_from_building, RemoveHeroFromBuildingRequest( modeldata, { "src_hero_id" : ["" + str(heroes[0].id) + ""], "construction_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(heroes[0].InBuildings) == 0 
    assert len(construction.HeroesInBuilding) == 0

  def remove_hero_from_working_building_test( self, env ):   
    modeldata = env.acc.model
    
    construction = env.add_construction(modeldata, "Tavern")
    
    heroes = env.add_heroes_to_construction(modeldata, construction, 2)
    construction.ProductionState = ProductionState.Busy
    
    assert len(heroes[0].InBuildings) == 1 
    assert len(heroes[1].InBuildings) == 1 
    assert len(construction.HeroesInBuilding) == 2

    requests = [ ( Remove_hero_from_building, RemoveHeroFromBuildingRequest( modeldata, { "src_hero_id" : ["" + str(heroes[0].id) + ""], "construction_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    construction.ProductionState = ProductionState.Busy
    assert len(heroes[0].InBuildings) == 0 
    assert len(heroes[1].InBuildings) == 1 
    assert len(construction.HeroesInBuilding) == 1
    
  def remove_last_hero_from_working_building_test( self, env ):   
    modeldata = env.acc.model
    
    construction = env.add_construction(modeldata, "Tavern")
    construction.ProductionState = ProductionState.Busy
    
    heroes = env.add_heroes_to_construction(modeldata, construction, 1)
    
    assert len(heroes[0].InBuildings) == 1 
    assert len(construction.HeroesInBuilding) == 1

    requests = [ ( Remove_hero_from_building, RemoveHeroFromBuildingRequest( modeldata, { "src_hero_id" : ["" + str(heroes[0].id) + ""], "construction_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(heroes[0].InBuildings) == 0 
    assert len(construction.HeroesInBuilding) == 0
    construction.ProductionState = ProductionState.Idle
    
  def remove_hero_from_building_with_no_hero_test( self, env ):   
    modeldata = env.acc.model
    
    construction = env.add_construction(modeldata, "Tavern")
  
    assert len(construction.HeroesInBuilding) == 0

    requests = [ ( Remove_hero_from_building, RemoveHeroFromBuildingRequest( modeldata, { "src_hero_id" : ["1"], "construction_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert changeList[0].get('ec') == EC.DEBUG_MESSAGE
