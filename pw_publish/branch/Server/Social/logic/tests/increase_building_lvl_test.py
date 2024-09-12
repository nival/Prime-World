import sys
sys.path.append('../')
from logic.increase_building_lvl import *
from binascii import crc32
from base.helpers import *
sys.path.append('../..')
from enums import *

class increase_building_lvl_test:

  def increase_building_lvl_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Buildings)
    level = 5
    
    construction = env.add_construction(modeldata, "Storage")
    
    assert len( modeldata.Buildings ) == buildCount + 1
    assert construction.Level == 0

    requests =  [ ( Increase_building_lvl, IncreaseBuildingLvlRequest( modeldata, { "building_id" : ["" + str(construction.id) + ""], "level" : [level] }, False ) ) ]
    changeList = env.execActions( requests )

    assert construction.Level == level