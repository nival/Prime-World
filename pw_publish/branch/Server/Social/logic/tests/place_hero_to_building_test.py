import sys
sys.path.append('../')
from logic.place_hero_to_building import *
from binascii import crc32
import time
sys.path.append('../..')
from enums import *
import EC

class place_hero_to_building_test( ):
  def place_mm_hero_to_building_test( self, env ):   
    modeldata = env.acc.model
    
    construction = env.add_construction(modeldata, "Tavern")
    
    hero = env.add_hero(modeldata, "mowgly")
    hero.InMatchmaking = True
    
    requests = [ ( Place_hero_to_building, PlaceHeroToBuildingRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""], "construction_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert len(construction.HeroesInBuilding) == 0
    assert len(hero.InBuildings) == 0
    assert changeList[0].get('ec') == EC.DEBUG_MESSAGE

  def place_hero_to_working_full_building_test( self, env ):   
    modeldata = env.acc.model
    
    construction = env.add_construction(modeldata, "Tavern")
    
    hero = env.add_hero(modeldata, "mowgly")
    heroCount = 4
    
    for i in xrange(0, heroCount):
      construction.HeroesInBuilding.add(modeldata.addNewHero( ))

    construction.ProductionState = ProductionState.Busy

    requests =  [ ( Place_hero_to_building, PlaceHeroToBuildingRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""], "construction_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert construction.ProductionState == ProductionState.Busy 
    
    assert len(construction.HeroesInBuilding) == heroCount
    assert len(hero.InBuildings) == 0
    assert changeList[0].get('ec') == EC.DEBUG_MESSAGE

  def place_hero_to_working_building_test( self, env ):   
    modeldata = env.acc.model
    
    construction = env.add_construction(modeldata, "Tavern")
    
    hero = env.add_hero(modeldata, "mowgly")

    construction.ProductionState = ProductionState.Busy

    requests =  [ ( Place_hero_to_building, PlaceHeroToBuildingRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""], "construction_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert len(construction.HeroesInBuilding) == 1
    assert len(hero.InBuildings) == 1
    assert construction.ProductionState == ProductionState.Idle
    assert construction.cycle == -1

  def place_hero_to_full_building_test( self, env ):   
    modeldata = env.acc.model
    
    construction = env.add_construction(modeldata, "Tavern")
    
    hero = env.add_hero(modeldata, "mowgly")

    heroCount = 4
    
    for i in xrange(0, heroCount):
      construction.HeroesInBuilding.add(modeldata.addNewHero( ))

    requests =  [ ( Place_hero_to_building, PlaceHeroToBuildingRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""], "construction_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )    
    
    assert len(construction.HeroesInBuilding) == heroCount
    assert len(hero.InBuildings) == 0
    assert changeList[0].get('ec') == EC.DEBUG_MESSAGE

  def place_hero_to_building_twice_test( self, env ):   
    modeldata = env.acc.model
    
    construction = env.add_construction(modeldata, "Tavern")
    construction.Level = 10
    
    hero = env.add_hero(modeldata, "mowgly")

    requests =  [ ( Place_hero_to_building, PlaceHeroToBuildingRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""], "construction_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert len(construction.HeroesInBuilding) == 1
    assert len(hero.InBuildings) == 1
    
    requests =  [ ( Place_hero_to_building, PlaceHeroToBuildingRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""], "construction_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert len(construction.HeroesInBuilding) == 1
    assert len(hero.InBuildings) == 1
    assert changeList[1].get('ec') == EC.DEBUG_MESSAGE

  def place_hero_to_building_test( self, env ):   
    modeldata = env.acc.model
    
    construction = env.add_construction(modeldata, "Tavern")
    
    hero = env.add_hero(modeldata, "mowgly")

    requests =  [ ( Place_hero_to_building, PlaceHeroToBuildingRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""], "construction_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert len(construction.HeroesInBuilding) == 1
    assert len(hero.InBuildings) == 1

  def place_hero_to_building_with_product_test( self, env ):   
    modeldata = env.acc.model
    
    construction = env.add_construction(modeldata, "Tavern")

    construction2 = env.add_construction(modeldata, "Production_Resource1")
    construction2.ProductionState = ProductionState.Busy    

    hero = env.add_hero(modeldata, "mowgly")

    cost = 0
    cost += int(modeldata.Resources.Gold)
    cost += int(modeldata.Resources.Perl)
    cost += int(modeldata.Resources.Silver)
    cost += int(modeldata.Resources.Population)
    cost += int(modeldata.Resources.Resource1)
    cost += int(modeldata.Resources.Resource2)
    cost += int(modeldata.Resources.Resource3)
    cost += int(modeldata.Resources.Resource1_Rare)
    cost += int(modeldata.Resources.Resource2_Rare)
    cost += int(modeldata.Resources.Resource3_Rare)

    requests = [ ( Place_hero_to_building, PlaceHeroToBuildingRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""], "construction_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    cost2 = 0
    cost2 += int(modeldata.Resources.Gold)
    cost2 += int(modeldata.Resources.Perl)
    cost2 += int(modeldata.Resources.Silver)
    cost2 += int(modeldata.Resources.Population)
    cost2 += int(modeldata.Resources.Resource1)
    cost2 += int(modeldata.Resources.Resource2)
    cost2 += int(modeldata.Resources.Resource3)
    cost2 += int(modeldata.Resources.Resource1_Rare)
    cost2 += int(modeldata.Resources.Resource2_Rare)
    cost2 += int(modeldata.Resources.Resource3_Rare)

    assert cost == cost2

    assert len(construction.HeroesInBuilding) == 1
    assert len(hero.InBuildings) == 1