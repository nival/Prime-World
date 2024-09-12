# -*- coding: utf-8 -*-

import sys
sys.path.append('../')
from logic.item_move_ts2inv import *
from binascii import crc32
sys.path.append('../..')
from enums import *
import EC

class item_move_ts2inv_test:
  def item_move_ts2inv_test( self, env ):
    modeldata = env.acc.model
    hero = env.add_hero(modeldata, 'mowgly')
    tsTalent = env.add_talent(modeldata, "G010")
    staticTalent = env.acc.SD.getStaticTalent(tsTalent)
    modeldata.UserInventory.add( tsTalent )
    tsSlotId = staticTalent['minLevel'] + 1
    for i in xrange(3):
      hero.TalentSets[i].Talents.add(tsSlotId, tsTalent.id)
      tsTalent.ParentTalentSets.add(i, hero.TalentSets[i].id)
    tsTalent.Owner =hero


    requests = [ ( Item_move_ts2inv , ItemMoveTsToInvRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "src_slot_id" : ["" + str(tsSlotId) + ""],
                                                                                "src_item_id" : ["" + str(tsTalent.id) + ""],
                                                                                "talent_set_id" : ["0"],
                                                                           }, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.TalentSets[0].Talents.get(tsSlotId) == None
    assert tsTalent.id in modeldata.UserInventory

  def item_move_ts2inv_full_test( self, env ):
    # Лимиты теперь ничему не мешают
    return
    modeldata = env.acc.model
    
    hero = env.add_hero(modeldata, 'mowgly')
    for x in xrange(0,32):
      invTalent = env.add_talent(modeldata, "G010")
      modeldata.UserInventory.add( invTalent )
      
    tsTalent = env.add_talent(modeldata, "G010")
    staticTalent = env.acc.SD.getStaticTalent(tsTalent)
    tsSlotId = staticTalent['minLevel'] + 1
    hero.TalentSets[0].Talents.add(tsSlotId, tsTalent)
    
    inventoryCount = len(modeldata.UserInventory)

    requests = [ ( Item_move_ts2inv , ItemMoveTsToInvRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "src_slot_id" : ["" + str(tsSlotId) + ""],
                                                                                "src_item_id" : ["" + str(tsTalent.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(modeldata.UserInventory) == inventoryCount
    assert changeList[0].get('ec') == EC.DEBUG_MESSAGE
    assert hero.TalentSets[0].Talents.getID(tsSlotId) == tsTalent.id

  def item_move_ts2inv_for_prince_test( self, env ):
    modeldata = env.acc.model

    hero = modeldata.hireHero(crc32('prince'), env.acc.sex, env.I.WS, env.acc, env.I)

    #  Prince_A3
    tsSlotId =2
    tsTalent = modeldata.getTalentByID(hero.TalentSets[0].Talents.get(tsSlotId))

    requests = [ ( Item_move_ts2inv , ItemMoveTsToInvRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "src_slot_id" : ["" + str(tsSlotId) + ""],
                                                                                "src_item_id" : ["" + str(tsTalent.id) + ""],
                                                                                "talent_set_id" : ["0"],
                                                                           }, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.TalentSets[0].Talents.get(tsSlotId) == None
    assert tsTalent in modeldata.UserInventory.values()
  
  def item_move_ts2inv_for_prince2_test( self, env ):
    modeldata = env.acc.model

    hero = modeldata.hireHero( crc32('inventor'), env.acc.sex, env.I.WS, env.acc, env.I )

    #  Prince_A3
    tsSlotId =2
    tsTalent =None
    for tsId in hero.TalentSets.keys():
        tsTalent = modeldata.getTalentByID(hero.TalentSets[tsId].Talents.get(tsSlotId))

        requests = [ ( Item_move_ts2inv , ItemMoveTsToInvRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "src_slot_id" : ["" + str(tsSlotId) + ""],
                                                                                "src_item_id" : ["" + str(tsTalent.id) + ""],
                                                                                "talent_set_id" : [""+ str(tsId)+""],
                                                                           }, False ) ) ]
        changeList = env.execActions( requests )

        assert hero.TalentSets[0].Talents.get(tsSlotId) == None
        assert tsTalent in modeldata.UserInventory.values()

    assert tsTalent is not None
    assert tsTalent.Owner == 0
    assert bool(tsTalent.ParentTalentSets) == False

