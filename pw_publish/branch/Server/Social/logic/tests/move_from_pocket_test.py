import sys
sys.path.append('../')
from logic.move_from_pocket import *
from binascii import crc32
from base.helpers import *
sys.path.append('../..')
from enums import *

class move_from_pocket_test:
  def building_move_from_pocket_storage_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    modeldata.LordInfo.LevelOfExpansion = 1
    
    construction = env.add_construction(modeldata, "Storage")
    x = 1
    y = 1
    pitch = 90

    modeldata.Pocket.add(construction.id)
    modeldata.Buildings.remove(construction.id)

    pocketCount = len(modeldata.Pocket)
    assert len(modeldata.Buildings) == buildCount

    requests =  [(Move_from_pocket, MoveFromPocketRequest(modeldata, {"building_id": ["" + str(construction.id) + ""], "x": [x], "y": [y], "pitch": [pitch]}, False))]
    changeList = env.execActions(requests)

    assert len(modeldata.Pocket) == pocketCount - 1
    assert len(modeldata.Buildings) == buildCount + 1
    construction = modeldata.getConstructionByID(construction.id)
    assert construction.Position.X == x
    assert construction.Position.Y == y
    assert construction.Position.Pitch == pitch
    
  def building_move_from_pocket_library_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    modeldata.LordInfo.LevelOfExpansion = 1
    
    construction = env.add_construction(modeldata, "Library")

    modeldata.Pocket.add(construction.id)
    modeldata.Buildings.remove(construction.id)

    assert len(modeldata.Pocket) == 1
    assert len(modeldata.Buildings) == buildCount

    requests =  [(Move_from_pocket, MoveFromPocketRequest(modeldata, {"building_id": ["" + str(construction.id) + ""], "x": ["1"], "y": ["1"], "pitch": ["1"]}, False))]
    changeList = env.execActions(requests)

    assert len(modeldata.Pocket) == 0
    assert len(modeldata.Buildings) == buildCount + 1
    construction = modeldata.getConstructionByID(construction.id)
    assert construction.Position.X == 1
    assert construction.Position.Y == 1
    assert construction.Position.Pitch == 1

  def building_move_from_pocket_house_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    modeldata.LordInfo.LevelOfExpansion = 1
    
    construction = env.add_construction(modeldata, "House_4")

    modeldata.Pocket.add(construction.id)
    modeldata.Buildings.remove(construction.id)

    assert len(modeldata.Pocket) == 1
    assert len(modeldata.Buildings) == buildCount

    requests =  [(Move_from_pocket, MoveFromPocketRequest(modeldata, {"building_id": ["" + str(construction.id) + ""], "x": ["1"], "y": ["1"], "pitch": ["1"]}, False))]
    changeList = env.execActions(requests)

    assert len(modeldata.Pocket) == 0
    assert len(modeldata.Buildings) == buildCount + 1
    construction = modeldata.getConstructionByID(construction.id)
    assert construction.Position.X == 1
    assert construction.Position.Y == 1
    assert construction.Position.Pitch == 1
    
  #def building_move_from_pocket_pinetree_test(self, env):
    #modeldata = env.acc.model
    #buildCount = len(modeldata.Buildings)
    #modeldata.LordInfo.LevelOfExpansion = 1
    
    #construction = env.add_construction(modeldata, "PineTree")

    #modeldata.Pocket.add(construction.id)
    #modeldata.Buildings.remove(construction.id)

    #assert len(modeldata.Pocket) == 1
    #assert len(modeldata.Buildings) == buildCount

    #requests =  [(Move_from_pocket, MoveFromPocketRequest(modeldata, {"building_id": ["" + str(construction.id) + ""], "x": ["1"], "y": ["1"], "pitch": ["1"]}, False))]
    #changeList = env.execActions(requests)

    #assert len(modeldata.Pocket) == 0
    #assert len(modeldata.Buildings) == buildCount + 1
    #construction = modeldata.getConstructionByID(construction.id)
    #assert construction.Position.X == 1
    #assert construction.Position.Y == 1
    #assert construction.Position.Pitch == 1    
  
  def building_move_from_pocket_decor_Lattern_1_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    modeldata.LordInfo.LevelOfExpansion = 1
    
    construction = env.add_construction(modeldata, "Decor_Lattern_1")

    modeldata.Pocket.add(construction.id)
    modeldata.Buildings.remove(construction.id)

    assert len(modeldata.Pocket) == 1
    assert len(modeldata.Buildings) == buildCount

    requests =  [(Move_from_pocket, MoveFromPocketRequest(modeldata, {"building_id": ["" + str(construction.id) + ""], "x": ["1"], "y": ["1"], "pitch": ["1"]}, False))]
    changeList = env.execActions(requests)

    assert len(modeldata.Pocket) == 0
    assert len(modeldata.Buildings) == buildCount + 1
    construction = modeldata.getConstructionByID(construction.id)
    assert construction.Position.X == 1
    assert construction.Position.Y == 1
    assert construction.Position.Pitch == 1

  def building_move_from_pocket_talent_Production_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    modeldata.LordInfo.LevelOfExpansion = 1
    
    construction = env.add_construction(modeldata, "Talent_Production")

    modeldata.Pocket.add(construction.id)
    modeldata.Buildings.remove(construction.id)

    assert len(modeldata.Pocket) == 1
    assert len(modeldata.Buildings) == buildCount

    requests = [(Move_from_pocket, MoveFromPocketRequest(modeldata, {"building_id": ["" + str(construction.id) + ""], "x": ["1"], "y": ["1"], "pitch": ["1"]}, False))]
    changeList = env.execActions(requests)

    assert len(modeldata.Pocket) == 0
    assert len(modeldata.Buildings) == buildCount + 1
    construction = modeldata.getConstructionByID(construction.id)
    assert construction.Position.X == 1
    assert construction.Position.Y == 1
    assert construction.Position.Pitch == 1
  

  def building_move_from_pocket_firstbuy_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    modeldata.LordInfo.LevelOfExpansion = 1
    
    construction = env.add_construction(modeldata, "FirstBuy_Cat")

    modeldata.Pocket.add(construction.id)
    modeldata.Buildings.remove(construction.id)

    assert len(modeldata.Pocket) == 1
    assert len(modeldata.Buildings) == buildCount

    requests =  [(Move_from_pocket, MoveFromPocketRequest(modeldata, {"building_id": ["" + str(construction.id) + ""], "x": ["1"], "y": ["1"], "pitch": ["1"]}, False))]
    changeList = env.execActions(requests)

    assert len(modeldata.Pocket) == 0
    assert len(modeldata.Buildings) == buildCount + 1
    construction = modeldata.getConstructionByID(construction.id)
    assert construction.Position.X == 1
    assert construction.Position.Y == 1
    assert construction.Position.Pitch == 1
    
  def building_move_from_pocket_guild_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    modeldata.LordInfo.LevelOfExpansion = 1
    
    construction = env.add_construction(modeldata, "Guild", 5)

    modeldata.Pocket.add(construction.id)
    modeldata.Buildings.remove(construction.id)

    assert len(modeldata.Pocket) == 1
    assert len(modeldata.Buildings) == buildCount

    requests =  [(Move_from_pocket, MoveFromPocketRequest(modeldata, {"building_id": ["" + str(construction.id) + ""], "x": ["1"], "y": ["1"], "pitch": ["1"]}, False))]
    changeList = env.execActions(requests)

    assert len(modeldata.Pocket) == 0
    assert len(modeldata.Buildings) == buildCount + 1
    construction = modeldata.getConstructionByID(construction.id)
    assert construction.Position.X == 1
    assert construction.Position.Y == 1
    assert construction.Position.Pitch == 1  

  def building_move_from_pocket_heroes_buff_test(self, env):
    
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    modeldata.LordInfo.LevelOfExpansion = 1
    
    construction = env.add_construction(modeldata, "BuffHouse_2")

    modeldata.Pocket.add(construction.id)
    modeldata.Buildings.remove(construction.id)

    pocketCount = len(modeldata.Pocket)
    assert len(modeldata.Buildings) == buildCount
    assert modeldata.getBonusFromBuilding("Energy", env.acc.SD) == 0.0
    assert modeldata.getBonusFromBuilding("Life", env.acc.SD) == 0.0		
    assert modeldata.getStatPointsFromBuilding(env.acc.SD) == 0.0

    requests =  [(Move_from_pocket, MoveFromPocketRequest(modeldata, {"building_id": ["" + str(construction.id) + ""], "x": ["1"], "y": ["1"], "pitch": ["1"]}, False))]
    changeList = env.execActions(requests)

    assert len(modeldata.Pocket) == pocketCount - 1
    assert len(modeldata.Buildings) == buildCount + 1
    construction = modeldata.getConstructionByID(construction.id)
    assert construction.Position.X == 1
    assert construction.Position.Y == 1
    assert construction.Position.Pitch == 1
    
    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(construction.PersistentId)
    points = env.acc.SD.getFloatInterpolated(staticConstruction['HeroesBuildingLevels'], construction.Level, None, "statBufValue", 0)
    energy = points * env.acc.SD.getStatPointsMultiplyer("Energy")
    life = points * env.acc.SD.getStatPointsMultiplyer("Life")
    allPoints = points * len(staticConstruction['buffStats']['Item']) 
    
    assert modeldata.getBonusFromBuilding("Energy", env.acc.SD) == energy
    assert modeldata.getBonusFromBuilding("Life", env.acc.SD) == life	
    assert modeldata.getStatPointsFromBuilding(env.acc.SD) == allPoints
    
  def building_move_from_pocket_gold_production_house_test(self, env):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    modeldata.LordInfo.LevelOfExpansion = 1
    modeldata.ResourcesLimit.Population = env.acc.SD.data['ResourceAndInventoryLimits']['resourceLimits']['Population']
    population = modeldata.ResourcesLimit.Population
    
    construction = env.add_construction(modeldata, "GoldProductionHouse")
    staticConstruction = env.acc.SD.getStaticConstruction(construction)

    modeldata.Pocket.add(construction.id)
    modeldata.Buildings.remove(construction.id)

    assert len(modeldata.Pocket) == 1
    assert len(modeldata.Buildings) == buildCount

    requests = [(Move_from_pocket, MoveFromPocketRequest(modeldata, {"building_id": ["" + str(construction.id) + ""], "x": ["1"], "y": ["1"], "pitch": ["1"]}, False))]
    changeList = env.execActions(requests)

    assert len(modeldata.Pocket) == 0
    assert len(modeldata.Buildings) == buildCount + 1
    construction = modeldata.getConstructionByID(construction.id)
    assert construction.Position.X == 1
    assert construction.Position.Y == 1
    assert construction.Position.Pitch == 1
    assert modeldata.ResourcesLimit.Population == population + staticConstruction['HouseLevels']['Item'][0]['currentMaxPopulation']
    assert modeldata.MarketingEventsInfo.GoldHouseActionState == GoldHouseActionState.ShowNoEvent