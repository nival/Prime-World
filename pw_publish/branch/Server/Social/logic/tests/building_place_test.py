import sys
sys.path.append('../')
sys.path.append('../logic')
from logic.building_place import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class building_place_test():

  def building_place_library_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    I = env.I

    modeldata.LordInfo.LevelOfExpansion = 1
    Resources = env.generate_resources(2000)
    modeldata.Resources = env.generate_resources(2000)
    assert len(modeldata.Buildings) == buildCount

    plan_id = crc32("Library")
    x = 100500
    y = 100500
    pitch = 0

    requests = [(Building_place, BuildingPlaceRequest(modeldata, {"PersistentId": ["" + str(plan_id) + ""], "x": ["" + str(x) + ""], "y": ["" + str(y) + ""], "pitch": ["" + str(pitch) + ""]}, False))]
    changeList = env.execActions(requests)

    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(plan_id)

    for buildingId in modeldata.Buildings:
      building = modeldata.getConstructionByID(buildingId)
      if building:
        if building.Position.X == x and building.Position.Y == y and building.Position.Pitch == pitch and building.PersistentId == plan_id:
          building = building

    assert building != None
    assert env.compare_price(Resources, modeldata.Resources, staticConstruction['Levels']['Item'][building.Level]['price'])
    assert len(modeldata.Buildings) == buildCount + 1

  def building_place_house_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    I = env.I

    modeldata.LordInfo.LevelOfExpansion = 1
    Resources = env.generate_resources(2000)
    modeldata.Resources = env.generate_resources(2000)
    assert len(modeldata.Buildings) == buildCount

    plan_id = crc32("House_4")
    x = 100500
    y = 100500
    pitch = 0

    requests = [(Building_place, BuildingPlaceRequest(modeldata, {"PersistentId": ["" + str(plan_id) + ""], "x": ["" + str(x) + ""], "y": ["" + str(y) + ""], "pitch": ["" + str(pitch) + ""]}, False))]
    changeList = env.execActions(requests)

    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(plan_id)

    for buildingId in modeldata.Buildings:
      building = modeldata.getConstructionByID(buildingId)
      if building:
        if building.Position.X == x and building.Position.Y == y and building.Position.Pitch == pitch and building.PersistentId == plan_id:
          building = building

    assert building != None
    assert env.compare_price(Resources, modeldata.Resources, staticConstruction['Levels']['Item'][building.Level]['price'])
    assert len(modeldata.Buildings) == buildCount + 1

  #def building_place_pinetree_test(self, env):
    #modeldata = env.acc.model
    #buildCount = len(modeldata.Buildings)
    #I = env.I

    #modeldata.LordInfo.LevelOfExpansion = 1
    #Resources = env.generate_resources(2000)
    #modeldata.Resources = env.generate_resources(2000)
    #assert len(modeldata.Buildings) == buildCount

    #plan_id = crc32("PineTree")
    #x = 100500
    #y = 100500
    #pitch = 0

    #requests = [(Building_place, BuildingPlaceRequest(modeldata, {"PersistentId": ["" + str(plan_id) + ""], "x": ["" + str(x) + ""], "y": ["" + str(y) + ""], "pitch": ["" + str(pitch) + ""]}, False))]
    #changeList = env.execActions(requests)

    #staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(plan_id)

    #for buildingId in modeldata.Buildings:
      #building = modeldata.getConstructionByID(buildingId)
      #if building:
        #if building.Position.X == x and building.Position.Y == y and building.Position.Pitch == pitch and building.PersistentId == plan_id:
          #building = building

    #assert building != None
    #assert env.compare_price(Resources, modeldata.Resources, staticConstruction['Levels']['Item'][building.Level]['price'])
    #assert len(modeldata.Buildings) == buildCount + 1

  def building_place_decoration_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    I = env.I

    modeldata.LordInfo.LevelOfExpansion = 1
    Resources = env.generate_resources(2000)
    modeldata.Resources = env.generate_resources(2000)
    assert len(modeldata.Buildings) == buildCount

    plan_id = crc32("Decor_Lattern_1")
    x = 100500
    y = 100500
    pitch = 0

    requests = [(Building_place, BuildingPlaceRequest(modeldata, {"PersistentId": ["" + str(plan_id) + ""], "x": ["" + str(x) + ""], "y": ["" + str(y) + ""], "pitch": ["" + str(pitch) + ""]}, False))]
    changeList = env.execActions(requests)

    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(plan_id)

    for buildingId in modeldata.Buildings:
      building = modeldata.getConstructionByID(buildingId)
      if building:
        if building.Position.X == x and building.Position.Y == y and building.Position.Pitch == pitch and building.PersistentId == plan_id:
          building = building

    assert building != None
    assert env.compare_price(Resources, modeldata.Resources, staticConstruction['Levels']['Item'][building.Level]['price'])
    assert len(modeldata.Buildings) == buildCount + 1

  def building_place_building_not_enough_space_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    I = env.I
    buildingLimit = 50

    modeldata.LordInfo.LevelOfExpansion = 1
    assert len(modeldata.Buildings) == buildCount

    plan_id = crc32("Storage")
    x = 100500
    y = 100500
    pitch = 0

    for i in xrange(buildingLimit):
      construction_id = modeldata.addNewConstruction()
      construction = modeldata.getConstructionByID(construction_id)
      construction.PersistentId = plan_id
      modeldata.Buildings.add(construction_id)

    assert len(modeldata.Buildings) == buildCount + buildingLimit

    requests = [(Building_place, BuildingPlaceRequest(modeldata, {"PersistentId": ["" + str(plan_id) + ""], "x": ["" + str(x) + ""], "y": ["" + str(y) + ""], "pitch": ["" + str(pitch) + ""]}, False))]
    changeList = env.execActions(requests)

    assert len(modeldata.Buildings) == buildCount + buildingLimit
    assert(changeList.get("ModelData") == None)

  def building_place_transmutation_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    I = env.I

    modeldata.LordInfo.Fame = 100000
    modeldata.LordInfo.LevelOfExpansion = 1
    Resources = env.generate_resources(2000)
    modeldata.Resources = env.generate_resources(2000)
    assert len(modeldata.Buildings) == buildCount

    plan_id = crc32("Talent_Production")
    x = 100500
    y = 100500
    pitch = 0

    requests = [(Building_place, BuildingPlaceRequest(modeldata, {"PersistentId": ["" + str(plan_id) + ""], "x": ["" + str(x) + ""], "y": ["" + str(y) + ""], "pitch": ["" + str(pitch) + ""]}, False))]
    changeList = env.execActions(requests)

    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(plan_id)

    for buildingId in modeldata.Buildings:
      building = modeldata.getConstructionByID(buildingId)
      if building:
        if building.Position.X == x and building.Position.Y == y and building.Position.Pitch == pitch and building.PersistentId == plan_id:
          building = building

    assert building != None
    assert len(modeldata.Buildings) == buildCount + 1
    assert env.compare_price(Resources, modeldata.Resources, staticConstruction['Levels']['Item'][building.Level]['price'])

  def building_place_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    env.info("model: %s" % str(modeldata))

    modeldata.LordInfo.LevelOfExpansion = 1
    Resources = env.generate_resources(2000)
    modeldata.Resources = env.generate_resources(2000)
    assert len(modeldata.Buildings) == buildCount

    plan_id = crc32("Storage")
    x = 22
    y = 35
    pitch = 0
    id = modeldata.next_uid_+1

    requests = [(Building_place, BuildingPlaceRequest(modeldata, {"PersistentId": ["" + str(plan_id) + ""], "x": ["" + str(x) + ""], "y": ["" + str(y) + ""], "pitch": ["" + str(pitch) + ""]}, False))]
    changeList = env.execActions(requests)

    construction_id = id
    assert len(modeldata.Buildings) == buildCount + 1
    assert(modeldata.getConstructionByID(construction_id).id == construction_id)
    assert(modeldata.getConstructionByID(construction_id).Position.X == x)
    assert(modeldata.getConstructionByID(construction_id).Position.Y == y)
    assert(modeldata.getConstructionByID(construction_id).Position.Pitch == pitch)
    assert(modeldata.Buildings.get(construction_id).id == construction_id)

  def building_place_storage_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    I = env.I

    modeldata.LordInfo.LevelOfExpansion = 1
    Resources = env.generate_resources(100)
    modeldata.Resources = env.generate_resources(100)
    assert len(modeldata.Buildings) == buildCount

    plan_id = crc32("Storage")
    x = 100500
    y = 100500
    pitch = 0

    requests = [(Building_place, BuildingPlaceRequest(modeldata, {"rid":["0"],"PersistentId": ["" + str(plan_id) + ""], "x": ["" + str(x) + ""], "y": ["" + str(y) + ""], "pitch": ["" + str(pitch) + ""]}, False))]
    changeList = env.execActions(requests)

    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(plan_id)

    for buildingId in modeldata.Buildings:
      building = modeldata.getConstructionByID(buildingId)
      if building:
        if building.Position.X == x and building.Position.Y == y and building.Position.Pitch == pitch and building.PersistentId == plan_id:
          building = building

    assert building != None
    assert env.compare_price(Resources, modeldata.Resources, staticConstruction['Levels']['Item'][building.Level]['price'])
    assert len(modeldata.Buildings) == buildCount + 1

  def building_place_production_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    I = env.I

    modeldata.LordInfo.LevelOfExpansion = 1
    Resources = env.generate_resources(2000)
    modeldata.Resources = env.generate_resources(2000)
    assert len(modeldata.Buildings) == buildCount


    plan_id = crc32("Production_Resource1")
    x = 100500
    y = 100500
    pitch = 0

    requests = [(Building_place, BuildingPlaceRequest(modeldata, {"PersistentId": ["" + str(plan_id) + ""], "x": ["" + str(x) + ""], "y": ["" + str(y) + ""], "pitch": ["" + str(pitch) + ""]}, False))]
    changeList = env.execActions(requests)


    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(plan_id)

    for buildingId in modeldata.Buildings:
      building = modeldata.getConstructionByID(buildingId)
      if building:
        if building.Position.X == x and building.Position.Y == y and building.Position.Pitch == pitch and building.PersistentId == plan_id:
          building = building

    assert building != None
    assert env.compare_price(Resources, modeldata.Resources, staticConstruction['Levels']['Item'][building.Level]['price'])
    assert len(modeldata.Buildings) == buildCount + 1

  def decoration_place_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)

    modeldata.LordInfo.LevelOfExpansion = 1
    assert len(modeldata.Buildings) == buildCount

    plan_id = crc32("Decor_Lattern_1")
    x = 22
    y = 35
    pitch = 0

    silver = modeldata.Resources.Silver = 1000
    Resource1 = modeldata.Resources.Resource1 = 1000
    Resource2 = modeldata.Resources.Resource2 = 1000
    Resource3 = modeldata.Resources.Resource3 = 1000

    requests = [(Building_place, BuildingPlaceRequest(modeldata, {"PersistentId": ["" + str(plan_id) + ""], "x": ["" + str(x) + ""], "y": ["" + str(y) + ""], "pitch": ["" + str(pitch) + ""]}, False))]
    changeList = env.execActions(requests)

    assert len(modeldata.Buildings) == buildCount + 1

  def decoration_place_test2(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)

    modeldata.LordInfo.LevelOfExpansion = 1
    assert len(modeldata.Buildings) == buildCount

    plan_id = crc32("Decor_Lattern_1")
    x = 22
    y = 35
    pitch = 0

    silver = modeldata.Resources.Silver = 1000
    Resource1 = modeldata.Resources.Resource1 = 1000
    Resource2 = modeldata.Resources.Resource2 = 1000
    Resource3 = modeldata.Resources.Resource3 = 1000

    requests = [(Building_place, BuildingPlaceRequest(modeldata, {"PersistentId": ["" + str(plan_id) + ""], "x": ["" + str(x) + ""], "y": ["" + str(y) + ""], "pitch": ["" + str(pitch) + ""]}, False))]
    changeList = env.execActions(requests)

    assert len(modeldata.Buildings) == buildCount + 1

  def building_place_firstbuy_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    I = env.I

    modeldata.LordInfo.LevelOfExpansion = 1
    modeldata.Resources = env.generate_resources(2000)
    assert len(modeldata.Buildings) == buildCount

    plan_id = crc32("FirstBuy_Cat")
    x = 100500
    y = 100500
    pitch = 0

    requests = [(Building_place, BuildingPlaceRequest(modeldata, {"PersistentId": ["" + str(plan_id) + ""], "x": ["" + str(x) + ""], "y": ["" + str(y) + ""], "pitch": ["" + str(pitch) + ""]}, False))]
    changeList = env.execActions(requests)

    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(plan_id)

    for buildingId in modeldata.Buildings:
      building = modeldata.getConstructionByID(buildingId)
      if building:
        if building.Position.X == x and building.Position.Y == y and building.Position.Pitch == pitch and building.PersistentId == plan_id:
          building = building

    assert building != None
    assert len(modeldata.Buildings) == buildCount + 1
    
    
  def building_place_guild_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    I = env.I

    modeldata.LordInfo.LevelOfExpansion = 1
    modeldata.Resources = env.generate_resources(20000)
    assert len(modeldata.Buildings) == buildCount

    plan_id = crc32("Guild")
    x = 100500
    y = 100500
    pitch = 0

    requests = [(Building_place, BuildingPlaceRequest(modeldata, {"PersistentId": ["" + str(plan_id) + ""], "x": ["" + str(x) + ""], "y": ["" + str(y) + ""], "pitch": ["" + str(pitch) + ""]}, False))]
    changeList = env.execActions(requests)

    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(plan_id)

    for buildingId in modeldata.Buildings:
      building = modeldata.getConstructionByID(buildingId)
      if building:
        if building.Position.X == x and building.Position.Y == y and building.Position.Pitch == pitch and building.PersistentId == plan_id:
          building = building

    assert building != None
    assert len(modeldata.Buildings) == buildCount + 1    


  def building_place_heroesbuff_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    I = env.I

    modeldata.LordInfo.Fame = 100000
    modeldata.LordInfo.LevelOfExpansion = 1
    modeldata.Resources = env.generate_resources(20000)
    assert len(modeldata.Buildings) == buildCount
    assert modeldata.getBonusFromBuilding("Energy", env.acc.SD) == 0.0
    assert modeldata.getBonusFromBuilding("Life", env.acc.SD) == 0.0
    assert modeldata.getStatPointsFromBuilding(env.acc.SD) == 0.0

    plan_id = crc32("BuffHouse_2")
    x = 100500
    y = 100500
    pitch = 0

    requests = [(Building_place, BuildingPlaceRequest(modeldata, {"PersistentId": ["" + str(plan_id) + ""], "x": ["" + str(x) + ""], "y": ["" + str(y) + ""], "pitch": ["" + str(pitch) + ""]}, False))]
    changeList = env.execActions(requests)

    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(plan_id)

    building = None
    for buildingId in modeldata.Buildings:
      building = modeldata.getConstructionByID(buildingId)
      if building:
        if building.Position.X == x and building.Position.Y == y and building.Position.Pitch == pitch and building.PersistentId == plan_id:
          building = building

    assert building != None
    assert len(modeldata.Buildings) == buildCount + 1

    staticBuilding = env.acc.SD.getStaticConstruction(building)
    for buffStat in staticBuilding['buffStats']['Item']:  
      result = env.acc.SD.getFloatInterpolated(staticBuilding['HeroesBuildingLevels'], building.Level, None, "statBufValue", 0) * env.acc.SD.getStatPointsMultiplyer(buffStat)
      assert modeldata.getBonusFromBuilding(buffStat, env.acc.SD) == result
     
    result =  env.acc.SD.getFloatInterpolated(staticBuilding['HeroesBuildingLevels'], building.Level, None, "statBufValue", 0) * len(staticBuilding['buffStats']['Item'])            
    assert modeldata.getStatPointsFromBuilding(env.acc.SD) == result

  def building_place_cannotbuy_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    I = env.I

    modeldata.LordInfo.LevelOfExpansion = 1
    modeldata.Resources = env.generate_resources(2000)
    assert len(modeldata.Buildings) == buildCount

    plan_id = crc32("CanNotBuy")
    x = 100500
    y = 100500
    pitch = 0

    requests = [(Building_place, BuildingPlaceRequest(modeldata, {"PersistentId": ["" + str(plan_id) + ""], "x": ["" + str(x) + ""], "y": ["" + str(y) + ""], "pitch": ["" + str(pitch) + ""]}, False))]
    changeList = env.execActions(requests)

    assert len(modeldata.Buildings) == buildCount
    
  def building_place_increase_limits_with_cap_test(self, env):
    env.acc.guest = 0
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings) 
    amount = 2000
    modeldata.Resources = env.generate_resources(amount)
    modeldata.LordInfo.LevelOfExpansion = 1
    
    plan_id = crc32("Storage")
    x = 100500
    y = 100500
    pitch = 0

    requests = [(Building_place, BuildingPlaceRequest(modeldata, {"PersistentId": ["" + str(plan_id) + ""], "x": ["" + str(x) + ""], "y": ["" + str(y) + ""], "pitch": ["" + str(pitch) + ""]}, False))]
    changeList = env.execActions(requests)

    assert len(modeldata.Buildings) == buildCount + 1
    
    limits = env.acc.SD.data['ResourceAndInventoryLimits']
    if env.acc.guest == 1:
      limits = env.acc.SD.data['GuestResourceAndInventoryLimits']
    
    staticBuilding = env.acc.SD.getStaticConstructionByPersistentId(plan_id)
    prLevelFirst, prLevelSecond = env.acc.SD.getInterpolLevels(staticBuilding['StorageLevels'], 0)
    if prLevelFirst['currentLevel'] == prLevelSecond['currentLevel']:
        newLimitsResource1 = limits['resourceLimits']['Resource1'] + prLevelFirst['additionalStorage']['Resource1']
        newLimitsResource2 = limits['resourceLimits']['Resource2'] + prLevelFirst['additionalStorage']['Resource2']
        newLimitsResource3 = limits['resourceLimits']['Resource3'] + prLevelFirst['additionalStorage']['Resource3']
        
    price = staticBuilding['Levels']['Item'][0]['price']
        
    assert newLimitsResource1 <= modeldata.Resources.Resource1
    assert amount == modeldata.Resources.Resource1 + price['Resource1']
    assert newLimitsResource2 <= modeldata.Resources.Resource2
    assert amount == modeldata.Resources.Resource2 + price['Resource2']
    assert newLimitsResource3 <= modeldata.Resources.Resource3
    assert amount == modeldata.Resources.Resource3 + price['Resource3']
    
  def building_place_gold_production_house_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    modeldata.Resources.Gold = 100

    modeldata.LordInfo.LevelOfExpansion = 1
    assert len(modeldata.Buildings) == buildCount
    modeldata.ResourcesLimit.Population = env.acc.SD.data['ResourceAndInventoryLimits']['resourceLimits']['Population']
    population = modeldata.ResourcesLimit.Population
    plan_id = crc32("GoldProductionHouse")
    x = 100500
    y = 100500
    pitch = 0

    requests = [(Building_place, BuildingPlaceRequest(modeldata, {"PersistentId": ["" + str(plan_id) + ""], "x": ["" + str(x) + ""], "y": ["" + str(y) + ""], "pitch": ["" + str(pitch) + ""]}, False))]
    changeList = env.execActions(requests)

    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(plan_id)

    for buildingId in modeldata.Buildings:
      building = modeldata.getConstructionByID(buildingId)
      if building:
        if building.Position.X == x and building.Position.Y == y and building.Position.Pitch == pitch and building.PersistentId == plan_id:
          building = building

    assert building != None
    assert modeldata.ResourcesLimit.Population == population + staticConstruction['HouseLevels']['Item'][0]['currentMaxPopulation']
    assert len(modeldata.Buildings) == buildCount + 1
    assert modeldata.MarketingEventsInfo.GoldHouseActionState == GoldHouseActionState.ShowNoEvent
