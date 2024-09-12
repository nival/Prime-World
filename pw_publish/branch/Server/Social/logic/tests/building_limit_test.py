import sys
sys.path.append('../')
from binascii import crc32
sys.path.append('../..')
from enums import *

class building_limit_test:

  def building_limit_test( self, env ):
    modeldata = env.acc.model
    modeldata.LordInfo.LevelOfExpansion = 1
    
    construction1 = env.add_construction(modeldata, "House_1")	
    construction2 = env.add_construction(modeldata, "House_1")	
    construction3 = env.add_construction(modeldata, "House_1")	
    construction4 = env.add_construction(modeldata, "House_1")	
    construction5 = env.add_construction(modeldata, "House_1")	
    construction6 = env.add_construction(modeldata, "House_1")	
    construction7 = env.add_construction(modeldata, "House_1")	
    construction8 = env.add_construction(modeldata, "House_1")	

    construction1.Level = 28
    construction2.Level = 28
    construction3.Level = 28
    construction4.Level = 28
    construction5.Level = 28
    construction6.Level = 28
    construction7.Level = 28
    construction8.Level = 28

    Resource1 = modeldata.Resources.Resource1 = 1000
    Resource3 = modeldata.Resources.Resource3 = 1000

    assert len(modeldata.Buildings) == 8

    buildingNames = ["House_1","House_2","House_3","House_4","Production_Silver_fromRes1"]
    modeldata.applyBuildingLimits( buildingNames, env.acc.SD )

    assert len(modeldata.Buildings) == 0
   
    assert modeldata.Resources.Resource1 == Resource1
    assert modeldata.Resources.Resource3 == Resource3


  def building_second_limit_test( self, env ):
    modeldata = env.acc.model
    modeldata.LordInfo.LevelOfExpansion = 1
    
    construction1 = env.add_construction(modeldata, "Production_Silver_fromRes1")	
    construction2 = env.add_construction(modeldata, "Production_Silver_fromRes1")	

    construction1.Level = 28
    construction2.Level = 28

    modeldata.Pocket.add(construction2)

    modeldata.Buildings.remove(construction2)

    Resource1 = modeldata.Resources.Resource1 = 1000
    Resource2 = modeldata.Resources.Resource2 = 1000
    Resource3 = modeldata.Resources.Resource3 = 1000

    assert len(modeldata.Buildings) == 1
    assert len(modeldata.Pocket) == 1

    buildingNames = ["House_1","House_2","House_3","House_4","Production_Silver_fromRes1"]
    modeldata.applyBuildingLimits( buildingNames, env.acc.SD )

    assert len(modeldata.Pocket) == 1
   
    assert modeldata.Resources.Resource1 > Resource1
    assert modeldata.Resources.Resource2 > Resource2
    assert modeldata.Resources.Resource3 > Resource3


  def building_third_limit_test( self, env ):
    modeldata = env.acc.model
    modeldata.LordInfo.LevelOfExpansion = 1
    
    construction1 = env.add_construction(modeldata, "Production_Silver_fromRes1")	
    construction2 = env.add_construction(modeldata, "Production_Silver_fromRes1")	
    construction3 = env.add_construction(modeldata, "Production_Silver_fromRes1")	

    construction1.Level = 22
    construction2.Level = 23
    construction3.Level = 28

    Resource1 = modeldata.Resources.Resource1 = 1000
    Resource2 = modeldata.Resources.Resource2 = 1000
    Resource3 = modeldata.Resources.Resource3 = 1000

    assert len(modeldata.Buildings) == 3

    buildingNames = ["House_1","House_2","House_3","House_4","Production_Silver_fromRes1"]
    modeldata.applyBuildingLimits( buildingNames, env.acc.SD )

    assert len(modeldata.Buildings) == 1
   
    assert modeldata.Resources.Resource1 > Resource1
    assert modeldata.Resources.Resource2 > Resource2
    assert modeldata.Resources.Resource3 > Resource3

    for buildingId in modeldata.Buildings.keys():
      building = modeldata.getConstructionByID( buildingId )
      assert building
      assert building.Level == 28
    