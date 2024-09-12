import sys
sys.path.append('../')
from logic.building_move import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class building_move_test:
  def building_move_test( self, env ):
    modeldata = env.acc.model
    x = 28
    y = 36
    pitch = 90

    modeldata.LordInfo.LevelOfExpansion = 1
    
    construction = env.add_construction(modeldata, "Storage")	
    
    requests = [ ( Building_move, BuildingMoveRequest( modeldata, { "building_id" : [str(construction.id)], "x" : [x], "y" : [y], "pitch" : [pitch] }, False ) )]
    changeList = env.execActions( requests )

    assert construction.Position.X ==  x
    assert construction.Position.Y ==  y
    assert construction.Position.Pitch ==  pitch