import sys
sys.path.append('../')
sys.path.append('../..')
from logic.check_talent import *
from binascii import crc32
from base.helpers import *
from enums import *

class check_talent_test:

  def check_talent_test( self, env ):
    modeldata = env.acc.model

    hero = modeldata.hireHero( crc32("mowgly"), env.acc.sex, env.I.WS, env.acc, env.I )
    talentId = hero.TalentSets[0].Talents.get( 12 )

    requests = [ ( Check_talent, CheckTalentRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""], "src_slot_id" : ["12"], "src_item_id" : ["" + str(talentId) + ""], "talent_set_id" : ["" + str(0) + ""] }, False ) ) ]
    changeList = env.execActions( requests )
    

  def check_talent_test_dup( self, env ):
    modeldata = env.acc.model

    hero = modeldata.hireHero( crc32("mowgly"), env.acc.sex, env.I.WS, env.acc, env.I )
    talentId = hero.TalentSets[0].Talents.get( 12 )
    talent = modeldata.getTalentByID(talentId)
    createdTalent = env.add_talent(modeldata, talent.PersistentId )
    modeldata.UserInventory.add(createdTalent)

    del_tal = modeldata.getTalentByID(hero.TalentSets[0].Talents.get( 11 ))
    hero.removeTalentFromTalentSet(0, del_tal, del_tal.id)
    hero.TalentSets[0].Talents.add( 11, createdTalent.id )
    createdTalent.Owner = hero
    createdTalent.ParentTalentSets.add(0, hero.TalentSets[0].id)

    tal11 = modeldata.getTalentByID(hero.TalentSets[0].Talents.get(11))
    tal12 = modeldata.getTalentByID(hero.TalentSets[0].Talents.get(12))
    assert tal12.PersistentId == tal11.PersistentId
    inventoryCount = len( modeldata.UserInventory )

    requests = [ ( Check_talent, CheckTalentRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""], "src_slot_id" : ["12"], "src_item_id" : ["" + str(talent.id) + ""], "talent_set_id" : ["" + str(0) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.TalentSets[0].Talents.get( 12 ) == None
    #assert len( modeldata.UserInventory ) == inventoryCount + 1


  def check_talent_test_wrong_tur( self, env ):
    modeldata = env.acc.model

    hero = modeldata.hireHero( crc32("mowgly"), env.acc.sex, env.I.WS, env.acc, env.I )

    createdTalent = env.add_talent(modeldata, "G137")
    createdTalent.Soulbound = hero
    modeldata.UserInventory.add(createdTalent)

    del_tal = modeldata.getTalentByID(hero.TalentSets[0].Talents.get( 3 ))
    hero.removeTalentFromTalentSet(0, del_tal, del_tal.id)
    hero.TalentSets[0].Talents.add( 3, createdTalent.id )
    createdTalent.Owner = hero
    createdTalent.ParentTalentSets.add(0, hero.TalentSets[0].id)


    assert modeldata.getTalentByID(hero.TalentSets[0].Talents.get( 3 )).PersistentId == createdTalent.PersistentId
    inventoryCount = len( modeldata.UserInventory )

    requests = [ ( Check_talent, CheckTalentRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""], "src_slot_id" : ["3"], "src_item_id" : ["" + str(createdTalent.id) + ""], "talent_set_id" : ["" + str(0) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.TalentSets[0].Talents.get( 3 ) == None
    #assert len( modeldata.UserInventory ) == inventoryCount + 1
