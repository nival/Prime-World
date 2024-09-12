import sys
sys.path.append('../')
from logic.building_remove import *
from binascii import crc32
import time
sys.path.append('../..')
from enums import *

class building_remove_test():
  def building_remove_house_test(self, env):
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "House_4")

    requests = [(Building_remove, BuildingRemoveRequest(modeldata, {"building_id": ["" + str(construction.id) + ""]}, False))]
    changeList = env.execActions(requests)

    assert(modeldata.Buildings.get(construction.id) == None)
    
  #def building_remove_pinetree_test(self, env):
    #modeldata = env.acc.model

    #construction = env.add_construction(modeldata, "PineTree")

    #requests = [(Building_remove, BuildingRemoveRequest(modeldata, {"building_id": ["" + str(construction.id) + ""]}, False))]
    #changeList = env.execActions(requests)

    #assert(modeldata.Buildings.get(construction.id) == None)    

  def building_remove_decoration_test(self, env):
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "Decor_Lattern_1")

    requests =  [(Building_remove, BuildingRemoveRequest(modeldata, {"building_id": ["" + str(construction.id) + ""]}, False))]
    changeList = env.execActions(requests)

    assert(modeldata.Buildings.get(construction.id) == None)

  def building_remove_tavern_test(self, env):
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "Tavern")

    requests =  [(Building_remove, BuildingRemoveRequest(modeldata, {"building_id": ["" + str(construction.id) + ""]}, False))]
    changeList = env.execActions(requests)

    assert(modeldata.Buildings.get(construction.id) == None)
    
  def building_remove_with_heroes_test(self, env):
    modeldata = env.acc.model
    
    construction = env.add_construction(modeldata, "Tavern")

    heroes = env.add_heroes_to_construction(modeldata, construction, 2)

    requests = [(Building_remove, BuildingRemoveRequest(modeldata, {"building_id": ["" + str(construction.id) + ""]}, False))]
    changeList = env.execActions(requests)

    assert(modeldata.Buildings.get(construction.id) == None)
    assert(len(heroes[0].InBuildings) == 0)
    assert(len(heroes[1].InBuildings) == 0)

  def building_remove_transmutation_test(self, env):
    
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "Talent_Production")

    requests =  [(Building_remove, BuildingRemoveRequest(modeldata, {"building_id": ["" + str(construction.id) + ""]}, False))]
    changeList = env.execActions(requests)

    assert(modeldata.Buildings.get(construction.id) == None)

  def building_remove_storage_test(self, env):
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "Storage")

    requests =  [(Building_remove, BuildingRemoveRequest(modeldata, {"building_id": ["" + str(construction.id) + ""]}, False))]
    changeList = env.execActions(requests)

    assert(modeldata.Buildings.get(construction.id) == None)
    

  def building_remove_storage_limits_change_test(self, env):
    env.acc.guest = 0
    modeldata = env.acc.model
    modeldata.Resources.Resource1 = res1 = 100000
    modeldata.ResourcesLimit.Resource1 = res1 = 100000

    construction = env.add_construction(modeldata, "Storage")

    requests =  [(Building_remove, BuildingRemoveRequest(modeldata, {"building_id": ["" + str(construction.id) + ""]}, False))]
    changeList = env.execActions(requests)

    assert(modeldata.Buildings.get(construction.id) == None)
    assert(modeldata.Resources.Resource1 == res1)

  def building_remove_production_test(self, env):
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "Production_Resource1")

    requests =  [(Building_remove, BuildingRemoveRequest(modeldata, {"building_id": ["" + str(construction.id) + ""]}, False))]
    changeList = env.execActions(requests)

    assert(modeldata.Buildings.get(construction.id) == None)

  def building_remove_library_test(self, env):
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "Library")

    requests =  [(Building_remove, BuildingRemoveRequest(modeldata, {"building_id": ["" + str(construction.id) + ""]}, False))]
    changeList = env.execActions(requests)

    assert(modeldata.Buildings.get(construction.id) == None)


  def building_remove_tavern_test(self, env):
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "Tavern")

    requests =  [(Building_remove, BuildingRemoveRequest(modeldata, {"building_id": ["" + str(construction.id) + ""]}, False))]
    changeList = env.execActions(requests)

    assert(modeldata.Buildings.get(construction.id) == None)

  def building_remove_firstbuy_test(self, env):
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "FirstBuy_Cat")

    requests =  [(Building_remove, BuildingRemoveRequest(modeldata, {"building_id": ["" + str(construction.id) + ""]}, False))]
    changeList = env.execActions(requests)

    assert(modeldata.Buildings.get(construction.id) == None)
    
  def building_remove_guild_test(self, env):
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "Guild")

    requests =  [(Building_remove, BuildingRemoveRequest(modeldata, {"building_id": ["" + str(construction.id) + ""]}, False))]
    changeList = env.execActions(requests)

    assert(modeldata.Buildings.get(construction.id) == None)  
    

  def building_remove_population_change_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)

    construction = env.add_construction(modeldata, "Talent_Production")

    modeldata.calcResourcesLimit(env.acc.SD, env.acc.guest)

    pop1 = modeldata.Resources.Population

    requests = [(Building_remove, BuildingRemoveRequest(modeldata, {"building_id": ["" + str(construction.id) + ""]}, False))]
    changeList = env.execActions(requests)

    pop2 = modeldata.Resources.Population    
    assert pop1 < pop2

  def building_remove_heroesbuff_test(self, env):
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "BuffHouse_2")

    assert modeldata.getBonusFromBuilding("Energy", env.acc.SD) != 0.0
    assert modeldata.getBonusFromBuilding("Life", env.acc.SD) != 0.0		
    assert modeldata.getStatPointsFromBuilding(env.acc.SD) != 0.0

    requests = [(Building_remove, BuildingRemoveRequest(modeldata, {"building_id": ["" + str(construction.id) + ""]}, False))]
    changeList = env.execActions(requests)

    assert(modeldata.Buildings.get(construction.id) == None)	
    assert modeldata.getBonusFromBuilding("Energy", env.acc.SD) == 0.0
    assert modeldata.getBonusFromBuilding("Life", env.acc.SD) == 0.0		
    assert modeldata.getStatPointsFromBuilding(env.acc.SD) == 0.0
    
  def building_remove_change_limits_with_cap_test(self, env):
    env.acc.guest = 0
    modeldata = env.acc.model
    
    construction = env.add_construction(modeldata, "Storage")
    modeldata.ResourcesLimit.Resource1 = 200
    modeldata.ResourcesLimit.Resource2 = 200
    modeldata.ResourcesLimit.Resource3 = 200
    
    buildCount = len(modeldata.Buildings) 
    amount = 2000
    modeldata.Resources = env.generate_resources(amount)

    requests = [(Building_remove, BuildingRemoveRequest(modeldata, {"building_id": ["" + str(construction.id) + ""]}, False))]
    changeList = env.execActions(requests)

    assert len(modeldata.Buildings) == buildCount - 1
    
    limits = env.acc.SD.data['ResourceAndInventoryLimits']
    if env.acc.guest == 1:
      limits = env.acc.SD.data['GuestResourceAndInventoryLimits']
    
    staticBuilding = env.acc.SD.getStaticConstruction(construction)
    price = staticBuilding['Levels']['Item'][0]['price']
        
    assert limits['resourceLimits']['Resource1'] <= modeldata.Resources.Resource1
    assert amount == modeldata.Resources.Resource1
    assert limits['resourceLimits']['Resource2'] <= modeldata.Resources.Resource2
    assert amount == modeldata.Resources.Resource2 
    assert limits['resourceLimits']['Resource3'] <= modeldata.Resources.Resource3
    assert amount == modeldata.Resources.Resource3 
    
  def guild_building_remove_place_bonus_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    guildPoints = 100500
    
    hero = env.add_hero(modeldata, 'mowgly')
    for tsId in hero.TalentSets.keys():
        ts = hero.TalentSets[tsId]
        ts.GuildStats.StatPoints = guildPoints
        
    construction = env.add_construction(modeldata, "Guild")
    tmpGuildLevel = env.acc.SD.data['GuildLevels']['levels']['Item'][1].copy()
    
    env.acc.SD.data['GuildLevels']['levels']['Item'][1]['Bonuses'] = {'Item': [{'MasterPoints': guildPoints, 'classType': 'GuildStatsBonus'}]}
    
    env.acc.guilddata.GuildLevelInfo.Experience = 100000000

    assert len(modeldata.Buildings) == buildCount + 1
    requests = [(Building_remove, BuildingRemoveRequest(modeldata, {"building_id": ["" + str(construction.id) + ""]}, False))]
    changeList = env.execActions(requests)

    
    assert len(modeldata.Heroes) > 0
    
    for heroId in modeldata.Heroes:
      hero = modeldata.getHeroByID(heroId)
      for tsId in hero.TalentSets.keys():
        ts = hero.TalentSets[tsId]
        assert ts.GuildStats.StatPoints == 0
      
    env.acc.SD.data['GuildLevels']['levels']['Item'][1] = tmpGuildLevel.copy()

  def building_remove_gold_production_house_test(self, env):
    modeldata = env.acc.model
    construction = env.add_construction(modeldata, "GoldProductionHouse")
    staticConstruction = env.acc.SD.getStaticConstruction(construction)
    modeldata.ResourcesLimit.Population = env.acc.SD.data['ResourceAndInventoryLimits']['resourceLimits']['Population'] \
                                          + staticConstruction['HouseLevels']['Item'][0]['currentMaxPopulation']
    oldPopulation = modeldata.ResourcesLimit.Population


    requests = [(Building_remove, BuildingRemoveRequest(modeldata, {"building_id": ["" + str(construction.id) + ""]}, False))]
    changeList = env.execActions(requests)

    assert(modeldata.Buildings.get(construction.id) == None)
    assert(modeldata.ResourcesLimit.Population == oldPopulation - staticConstruction['HouseLevels']['Item'][0]['currentMaxPopulation'])
    assert modeldata.MarketingEventsInfo.GoldHouseActionState == GoldHouseActionState.ShowBuyHouseEvent
