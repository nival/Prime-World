import sys
sys.path.append('../')
from logic.item_move_ts2ts import *
from binascii import crc32
from modeldata.validator import Validator
sys.path.append('../..')
from enums import *

class item_move_ts2ts_test:
  def item_move_ts2ts_test( self, env ):
    modeldata = env.acc.model
    
    hero = env.add_hero(modeldata, 'rockman')
    talent1 = env.add_talent(modeldata, "Rockman_A1")
    staticTalent1 = env.acc.SD.getStaticTalent(talent1)
    talent2 = env.add_talent(modeldata, "G010")
    staticTalent2 = env.acc.SD.getStaticTalent(talent2)
    modeldata.UserInventory.add(talent1)
    modeldata.UserInventory.add(talent2)
    assert staticTalent1['minLevel'] == staticTalent2['minLevel']
    lvl = staticTalent1['minLevel']
    
    hero.TalentSets[0].Talents.add(lvl + 1, talent1.id)
    hero.TalentSets[0].Talents.add(lvl + 2, talent2.id)

    requests = [ ( Item_move_ts2ts , ItemMoveTsToTsRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                              "src_slot_id" : ["" + str(lvl + 1) + ""],
                                                                              "src_item_id" : ["" + str(talent1.id) + ""],
                                                                              "dest_slot_id" : ["" + str(lvl + 2) + ""],
                                                                              "dest_item_id" : ["" + str(talent2.id) + ""],
                                                                         "talent_set_id" : ["0"]}, False ) ) ]
    changeList = env.execActions( requests )

    assert( hero.TalentSets[0].Talents[lvl + 1] == talent2.id )
    assert( hero.TalentSets[0].Talents[lvl + 2] == talent1.id )