import sys
sys.path.append('../')
from logic.change_map import *
from binascii import crc32
import time
sys.path.append('../..')
from enums import *

class change_map_test( ):

  def change_nick_test( self, env ):
    modeldata = env.acc.model

    mapName = 'test_map'

    requests = [ ( Change_map, ChangeMapRequest( modeldata, { "map" : [mapName] }, False ) ) ]
    changeList = env.execActions( requests )
    
    mapInfo = modeldata.LordInfo.MapsByType.get(MapType.CTF)
    assert mapInfo
    assert mapInfo.MapId == mapName