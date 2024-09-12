import sys
sys.path.append('../')
from logic.item_set_actbar_idx import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class item_set_actbar_idx_test:
  def item_set_actbar_idx_test( self, env ):
    modeldata = env.acc.model
    
    hero = env.add_hero(modeldata, 'mowgly')    
    talent = env.add_talent(modeldata, 'G137')
    modeldata.UserInventory.add(talent)
    hero.TalentSets[0].Talents.add(1, talent.id)
    talent.ParentTalentSets.add(0,hero.TalentSets[0].id)
    hero.TalentSets[0].InstaCast[0] = False
    actionBarIdx = 1
    
    assert hero.TalentSets[0].ActionBar[actionBarIdx] == -1

    requests =  [ ( Item_set_actbar_idx , ItemSetActoinBarIndexRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                     "slot_id" : ["1"],
                                                                                     "item_id" : ["" + str(talent.id) + ""],
                                                                                     "is_insta_cast" : ["" + str(True) + ""],
                                                                                     "talent_id" : ["" + str(talent.PersistentId) + ""],
                                                                                     "actbar_idx" : ["" + str(actionBarIdx) + ""],
                                                                                     "talent_set_id": ["0"]}, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.TalentSets[0].ActionBar[actionBarIdx] == talent.getID()
    assert hero.TalentSets[0].InstaCast[actionBarIdx] == True