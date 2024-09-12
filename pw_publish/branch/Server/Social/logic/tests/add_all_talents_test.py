import sys
sys.path.append('../')
from logic.add_all_talents import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class add_all_talents_test:
  def add_all_talents_test( self, env ):
    modeldata = env.acc.model

    defaultinventoryLength = len(modeldata.UserInventory)

    requests =  [ ( Add_all_talents, AddAllTalentsRequest( modeldata, { }, False ) ) ]
    changeList = env.execActions( requests )
    
    sdTalents = 0
    
    for talentID in env.acc.SD.data['Talents']:
      staticTalent = env.acc.SD.getStaticTalentByTalentId( talentID )
      if staticTalent['rarity'] != "Class" and talentID != 0:
        sdTalents += 1
        
    mdTalents = len(modeldata.UserInventory)
    assert sdTalents == mdTalents - defaultinventoryLength