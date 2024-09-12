import sys
sys.path.append('../')
from logic.item_move_inv2ts import *
from logic.item_move_ts2inv import *
from binascii import crc32
from modeldata.validator import Validator
sys.path.append('../..')
from enums import *
import EC 
import time

class item_move_inv2ts_test:
  def item_move_inv2ts_to_empty_slot_test( self, env ):
    modeldata = env.acc.model
    
    hero = env.add_hero(modeldata, 'mowgly')
    hero.Experience = 100500
    hero.TalentSets[0].InstaCast[0] = True
    invTalent = env.add_talent(modeldata, "G397")
    staticTalent = env.acc.SD.getStaticTalent(invTalent)
    modeldata.UserInventory.add( invTalent )
    res = invTalent.id not in modeldata.UserInventory.itervalues()


    tsSlotId = staticTalent['minLevel'] + 1
    heroForce = hero.TalentSets[0].Force
    
    requests = [ ( Item_move_inv2ts , ItemMoveInvToTsRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "src_item_id" : ["" + str(invTalent.id) + ""],
                                                                                "dest_slot_id" : ["" + str(tsSlotId) + ""],
                                                                                "dest_item_id" : ["" + str(0) + ""],
                                                                                "useLamp" : ["false"],
                                                                                "talent_set_id": ["0"]

                                                                           }, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.TalentSets[0].Talents.get(tsSlotId) == invTalent.id
    assert invTalent.Soulbound == hero.id 
    assert hero.TalentSets[0].ActionBar[0] != -1
    assert hero.TalentSets[0].InstaCast[0] == False
    #assert not invTalent.id in modeldata.UserInventory
    assert heroForce != hero.TalentSets[0].Force
    
  def item_move_inv2ts_to_full_slot_test( self, env ):
    modeldata = env.acc.model
    
    hero = env.add_hero(modeldata, 'mowgly')
    invTalent = env.add_talent(modeldata, "G010")
    tsTalent = env.add_talent(modeldata, "G010")
    staticTalent = env.acc.SD.getStaticTalent(invTalent)
    modeldata.UserInventory.add( invTalent )
    modeldata.UserInventory.add( tsTalent )
    tsSlotId = staticTalent['minLevel'] + 1
    hero.TalentSets[0].Talents.add(tsSlotId, tsTalent.getID())
    heroForce = hero.TalentSets[0].Force
    hero.TalentSets[0].InstaCast[0] = True
    
    requests = [ ( Item_move_inv2ts , ItemMoveInvToTsRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "src_item_id" : ["" + str(invTalent.id) + ""],
                                                                                "dest_slot_id" : ["" + str(tsSlotId) + ""],
                                                                                "dest_item_id" : ["" + str(tsTalent.id) + ""],
                                                                                "talent_set_id": ["0"],
                                                                                "useLamp" : ["false"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.TalentSets[0].Talents[tsSlotId] == invTalent.id
    assert invTalent.Soulbound == 0
    assert hero.TalentSets[0].ActionBar[0] == invTalent.id
    assert hero.TalentSets[0].InstaCast[0] == False
    assert invTalent.id in modeldata.UserInventory
    assert tsTalent.id in modeldata.UserInventory
    assert heroForce != hero.TalentSets[0].Force
    
  def item_move_inv2ts_empty_slot_solbound_to_self_test( self, env ):
    modeldata = env.acc.model
    
    hero = env.add_hero(modeldata, 'mowgly')
    invTalent = env.add_talent(modeldata, "G010")
    invTalent.Soulbound = hero
    staticTalent = env.acc.SD.getStaticTalent(invTalent)
    modeldata.UserInventory.add( invTalent )
    tsSlotId = staticTalent['minLevel'] + 1
    heroForce = hero.TalentSets[0].Force
    
    modeldata.Resources.Silver = 0
    modeldata.Resources.Gold = 0
    
    requests = [ ( Item_move_inv2ts , ItemMoveInvToTsRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                            "src_item_id" : ["" + str(invTalent.id) + ""],
                                                                            "dest_slot_id" : ["" + str(tsSlotId) + ""],
                                                                            "dest_item_id" : ["0"], "talent_set_id": ["0"],
                                                                            "useLamp" : ["false"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.TalentSets[0].Talents[tsSlotId] == invTalent.id
    assert hero.TalentSets[0].ActionBar[0] == invTalent.id
    assert hero.TalentSets[0].InstaCast[0] == False
    assert invTalent.id in modeldata.UserInventory
    assert heroForce != hero.TalentSets[0].Force
    
  def item_move_inv2ts_empty_slot_solbound_to_other_no_money_test( self, env ):
    modeldata = env.acc.model
    
    hero = env.add_hero(modeldata, 'mowgly')
    hero.Experience = 100500
    hero2 = env.add_hero(modeldata, 'mowgly')
    invTalent = env.add_talent(modeldata, "G642")
    invTalent.Soulbound = hero2
    staticTalent = env.acc.SD.getStaticTalent(invTalent)
    modeldata.UserInventory.add( invTalent )
    tsSlotId = staticTalent['minLevel'] + 28
    heroForce = hero.TalentSets[0].Force
    
    modeldata.Resources.Silver = 0
    modeldata.Resources.Gold = 0
    
    requests = [ ( Item_move_inv2ts , ItemMoveInvToTsRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "src_item_id" : ["" + str(invTalent.id) + ""],
                                                                                "dest_slot_id" : ["" + str(tsSlotId) + ""],
                                                                                "dest_item_id" : ["0"], "talent_set_id" : ["0"],
                                                                                "useLamp" : ["false"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert changeList[0].get('ec') == EC.NOT_ENOUGH_GOLD
    assert hero.TalentSets[0].Talents[tsSlotId] == None
    assert invTalent.Soulbound == hero2
    assert invTalent.id in modeldata.UserInventory
    
  def item_move_inv2ts_empty_slot_solbound_to_other_unsoulbound_test( self, env ):
    modeldata = env.acc.model
    
    hero = env.add_hero(modeldata, 'prince')
    hero.Experience = 100500
    hero2 = env.add_hero(modeldata, 'prince')
    invTalent = env.add_talent(modeldata, "G397")
    invTalent.Soulbound = hero2
    staticTalent = env.acc.SD.getStaticTalent(invTalent)
    modeldata.UserInventory.add( invTalent )
    tsSlotId = staticTalent['minLevel'] + 1
    heroForce = hero.TalentSets[0].Force
    hero.TalentSets[0].InstaCast[0] = True
    
    silver = modeldata.Resources.Silver = 1000
    gold = modeldata.Resources.Gold = 1000
    perl = modeldata.Resources.Perl = 1000
    
    requests = [ ( Item_move_inv2ts , ItemMoveInvToTsRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "src_item_id" : ["" + str(invTalent.id) + ""],
                                                                                "dest_slot_id" : ["" + str(tsSlotId) + ""],
                                                                                "dest_item_id" : ["0"], "talent_set_id" : ["0"],
                                                                                "useLamp" : ["false"] }, False ) ) ]
    changeList = env.execActions( requests )
    talent_level = env.acc.SD.getTalentLevelByPoints(invTalent.Points, staticTalent)
    assert silver - modeldata.Resources.Silver == int(env.acc.SD.getTalentUnsoulboundPrice( staticTalent, talent_level, env.I.Config.getConfig( env.acc.userlocale ) ).Silver)
    assert gold - modeldata.Resources.Gold == int(env.acc.SD.getTalentUnsoulboundPrice( staticTalent, talent_level, env.I.Config.getConfig( env.acc.userlocale ) ).Gold)
    assert perl - modeldata.Resources.Perl == int(env.acc.SD.getTalentUnsoulboundPrice(staticTalent, talent_level, env.I.Config.getConfig(env.acc.userlocale)).Perl)
    
    assert hero.TalentSets[0].Talents[tsSlotId] == invTalent.id
    assert invTalent.Soulbound == hero.id 
    assert hero.TalentSets[0].ActionBar[0] == invTalent.id
    assert hero.TalentSets[0].InstaCast[0] == False
    assert invTalent.id in modeldata.UserInventory
    assert heroForce != hero.TalentSets[0].Force

  def item_move_inv2ts_empty_slot_solbound_to_other_no_soulbound_test( self, env ):
    modeldata = env.acc.model

    hero = env.add_hero(modeldata, 'prince')
    invTalent = env.add_talent(modeldata, "G010")
    invTalent.Soulbound = 0
    staticTalent = env.acc.SD.getStaticTalent(invTalent)
    modeldata.UserInventory.add( invTalent )
    tsSlotId = staticTalent['minLevel'] + 1
    heroForce = hero.TalentSets[0].Force

    silver = modeldata.Resources.Silver = 0
    gold = modeldata.Resources.Gold = 0
    hero.TalentSets[0].InstaCast[0] = True

    requests = [ ( Item_move_inv2ts , ItemMoveInvToTsRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "src_item_id" : ["" + str(invTalent.id) + ""],
                                                                                "dest_slot_id" : ["" + str(tsSlotId) + ""],
                                                                                "dest_item_id" : ["0"], "talent_set_id" : ["0"],
                                                                                "useLamp" : ["false"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert silver == modeldata.Resources.Silver
    assert gold == modeldata.Resources.Gold

    assert hero.TalentSets[0].Talents[tsSlotId] == invTalent.id
    assert invTalent.Soulbound == 0
    assert hero.TalentSets[0].ActionBar[0] == invTalent.id
    assert hero.TalentSets[0].InstaCast[0] == False
    assert invTalent.id in modeldata.UserInventory
    assert heroForce != hero.TalentSets[0].Force
    
  def item_move_inv2ts_to_empty_slot_duplicate_test( self, env ):
    modeldata = env.acc.model
    
    hero = env.add_hero(modeldata, 'prince')
    invTalent = env.add_talent(modeldata, "G010")
    tsTalent = env.add_talent(modeldata, "G010")
    staticTalent = env.acc.SD.getStaticTalent(invTalent)
    modeldata.UserInventory.add( invTalent )    
    tsSlotId = staticTalent['minLevel'] + 1
    hero.TalentSets[0].Talents.add(tsSlotId + 1, tsTalent.getID)
    heroForce = hero.TalentSets[0].Force
    
    requests = [ ( Item_move_inv2ts , ItemMoveInvToTsRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "src_item_id" : ["" + str(invTalent.id) + ""],
                                                                                "dest_slot_id" : ["" + str(tsSlotId) + ""],
                                                                                "dest_item_id" : ["" + str(0) + ""],
                                                                                "talent_set_id" : ["0"],
                                                                                "useLamp" : ["false"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert changeList[0].get('ec') == EC.DEBUG_MESSAGE
    assert hero.TalentSets[0].Talents[tsSlotId] == None
    assert invTalent.id in modeldata.UserInventory
    
  def item_move_inv2ts_to_empty_slot_duplicate_test( self, env ):
    modeldata = env.acc.model
    
    hero = env.add_hero(modeldata, 'prince')
    invTalent = env.add_talent(modeldata, "G010")
    tsTalent = env.add_talent(modeldata, "G010")
    staticTalent = env.acc.SD.getStaticTalent(invTalent)
    modeldata.UserInventory.add( invTalent )    
    tsSlotId = staticTalent['minLevel'] + 1
    hero.TalentSets[0].Talents.add(tsSlotId + 1, tsTalent.id)
    heroForce = hero.TalentSets[0].Force
    
    requests = [ ( Item_move_inv2ts , ItemMoveInvToTsRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "src_item_id" : ["" + str(invTalent.id) + ""],
                                                                                "dest_slot_id" : ["" + str(tsSlotId) + ""],
                                                                                "dest_item_id" : ["" + str(0) + ""],
                                                                                "talent_set_id" : ["0"],
                                                                                "useLamp" : ["false"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert changeList[0].get('ec') == EC.DEBUG_MESSAGE
    assert hero.TalentSets[0].Talents[tsSlotId] == None
    assert invTalent.id in modeldata.UserInventory
 
  
  def item_move_inv2ts_empty_slot_class_from_self_test( self, env ):
    modeldata = env.acc.model
    
    hero = env.add_hero(modeldata, 'rockman')
    invTalent = env.add_talent(modeldata, "Rockman_A1")
    staticTalent = env.acc.SD.getStaticTalent(invTalent)
    modeldata.UserInventory.add( invTalent )
    tsSlotId = staticTalent['minLevel'] + 1
    heroForce = hero.TalentSets[0].Force
    hero.TalentSets[0].InstaCast[0] = True
    
    silver = modeldata.Resources.Silver = 1000
    gold = modeldata.Resources.Gold = 1000
    
    requests = [ ( Item_move_inv2ts , ItemMoveInvToTsRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "src_item_id" : ["" + str(invTalent.id) + ""],
                                                                                "dest_slot_id" : ["" + str(tsSlotId) + ""],
                                                                                "dest_item_id" : ["0"], "talent_set_id" : ["0"],
                                                                                "useLamp" : ["false"] }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert hero.TalentSets[0].Talents[tsSlotId] == invTalent.id
    assert invTalent.Soulbound == hero.id 
    assert hero.TalentSets[0].ActionBar[0] == invTalent.id
    assert hero.TalentSets[0].InstaCast[0] == False
    assert invTalent.id in modeldata.UserInventory
    assert heroForce != hero.TalentSets[0].Force
    
  def item_move_inv2ts_to_wrong_slot_test( self, env ):
    modeldata = env.acc.model
    
    hero = env.add_hero(modeldata, 'prince')
    invTalent = env.add_talent(modeldata, "G010")
    staticTalent = env.acc.SD.getStaticTalent(invTalent)
    modeldata.UserInventory.add( invTalent )
    tsSlotId = staticTalent['minLevel'] + 7
    heroForce = hero.TalentSets[0].Force
    
    requests = [ ( Item_move_inv2ts , ItemMoveInvToTsRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "src_item_id" : ["" + str(invTalent.id) + ""],
                                                                                "dest_slot_id" : ["" + str(tsSlotId) + ""],
                                                                                "dest_item_id" : ["" + str(0) + ""],
                                                                                "talent_set_id" : ["0"],
                                                                                "useLamp" : ["false"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert changeList[0].get('ec') == EC.DEBUG_MESSAGE
    assert hero.TalentSets[0].Talents[tsSlotId] == None
    assert invTalent.id in modeldata.UserInventory
    
  def item_move_inv2ts_to_wrong_item_test( self, env ):
    modeldata = env.acc.model
    
    hero = env.add_hero(modeldata, 'prince')
    invTalent = env.add_talent(modeldata, "G010")
    staticTalent = env.acc.SD.getStaticTalent(invTalent)
    modeldata.UserInventory.add( invTalent )
    tsSlotId = staticTalent['minLevel'] + 1
    heroForce = hero.TalentSets[0].Force
    
    requests = [ ( Item_move_inv2ts , ItemMoveInvToTsRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "src_item_id" : ["" + str(invTalent.id + 1) + ""],
                                                                                "dest_slot_id" : ["" + str(tsSlotId) + ""],
                                                                                "dest_item_id" : ["" + str(0) + ""],
                                                                                "talent_set_id" : ["0"],
                                                                                "useLamp" : ["false"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert changeList[0].get('ec') == EC.DEBUG_MESSAGE
    assert hero.TalentSets[0].Talents[tsSlotId] == None
    assert invTalent.id in modeldata.UserInventory
    
  def item_move_inv2ts_to_wrong_hero_test( self, env ):
    modeldata = env.acc.model
    
    hero = env.add_hero(modeldata, 'prince')
    invTalent = env.add_talent(modeldata, "G010")
    staticTalent = env.acc.SD.getStaticTalent(invTalent)
    modeldata.UserInventory.add( invTalent )
    tsSlotId = staticTalent['minLevel'] + 1
    heroForce = hero.TalentSets[0].Force
    
    requests = [ ( Item_move_inv2ts , ItemMoveInvToTsRequest( modeldata, { "src_hero_id" : ["" + str(hero.id + 1) + ""],
                                                                                "src_item_id" : ["" + str(invTalent.id) + ""],
                                                                                "dest_slot_id" : ["" + str(tsSlotId) + ""],
                                                                                "dest_item_id" : ["" + str(0) + ""],
                                                                                "talent_set_id" : ["0"],
                                                                                "useLamp" : ["false"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert changeList[0].get('ec') == EC.DEBUG_MESSAGE
    assert hero.TalentSets[0].Talents[tsSlotId] == None
    assert invTalent.id in modeldata.UserInventory
    
  def item_move_inv2ts_with_lamp_test( self, env ):
    modeldata = env.acc.model
    
    hero = env.add_hero(modeldata, 'prince')
    hero.Experience = 100500
    hero2 = env.add_hero(modeldata, 'rockman')
    invTalent = env.add_talent(modeldata, "G397")
    invTalent.Soulbound = hero2
    staticTalent = env.acc.SD.getStaticTalent(invTalent)
    modeldata.UserInventory.add( invTalent )
    tsSlotId = staticTalent['minLevel'] * 6 + 1
    heroForce = hero.TalentSets[0].Force
    
    silver = modeldata.Resources.Silver = 3
    gold = modeldata.Resources.Gold = 3
    
    now = time.time()
    modeldata.MarketingEventsInfo.LampEventInfo.AllowedLamps = 0
    modeldata.replaceGoldLampEvent( 20, 2000, 1, 300 )
    requests = [ ( Item_move_inv2ts , ItemMoveInvToTsRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "src_item_id" : ["" + str(invTalent.id) + ""],
                                                                                "dest_slot_id" : ["" + str(tsSlotId) + ""],
                                                                                "dest_item_id" : ["0"], "talent_set_id" : ["0"],
                                                                                "useLamp" : ["true"] }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert silver == modeldata.Resources.Silver
    assert gold == modeldata.Resources.Gold
    
    assert hero.TalentSets[0].Talents[tsSlotId] == invTalent.id
    assert invTalent.Soulbound == hero.id 
    assert invTalent.id in modeldata.UserInventory
    assert heroForce != hero.TalentSets[0].Force
  
  def item_move_inv2ts_guild_talent_to_empty_slot_test( self, env ):
    modeldata = env.acc.model

    hero = env.add_hero(modeldata, 'prince')
    firstGuildTalent = env.add_talent(modeldata, "G010")
    gbi, gbi_id = modeldata.newGuildBankInfo()
    firstGuildTalent.GuildBankInfo = gbi_id
    firstGuildTalent.GuildBankInfo.OwnerId = env.acc.auid + 1
    firstStaticTalent = env.acc.SD.getStaticTalent(firstGuildTalent)
    firstTdSlotId = firstStaticTalent['minLevel'] + 1
    hero.TalentSets[0].Talents.add( firstTdSlotId, firstGuildTalent.getID() )

    secondGuildTalent = env.add_talent(modeldata, "G001")
    gbi2, gbi_id2 = modeldata.newGuildBankInfo()
    secondGuildTalent.GuildBankInfo = gbi_id2
    secondGuildTalent.GuildBankInfo.OwnerId = env.acc.auid + 1
    secondStaticTalent = env.acc.SD.getStaticTalent(secondGuildTalent)
    secondTdSlotId = secondStaticTalent['minLevel'] + 2
    hero.TalentSets[0].Talents.add( secondTdSlotId, secondGuildTalent.getID() )

    invGuildTalent = env.add_talent(modeldata, "G002")
    gbi3, gbi_id3 = modeldata.newGuildBankInfo()
    invGuildTalent.GuildBankInfo = gbi_id3
    invGuildTalent.GuildBankInfo.OwnerId = env.acc.auid + 1
    staticTalent = env.acc.SD.getStaticTalent(invGuildTalent)

    modeldata.UserInventory.add( invGuildTalent )

    tsSlotId = staticTalent['minLevel'] + 3
    heroForce = hero.TalentSets[0].Force

    requests = [ ( Item_move_inv2ts , ItemMoveInvToTsRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "src_item_id" : ["" + str(invGuildTalent.id) + ""],
                                                                                "dest_slot_id" : ["" + str(tsSlotId) + ""],
                                                                                "dest_item_id" : ["" + str(0) + ""],
                                                                                "talent_set_id" : ["0"],
                                                                                "useLamp" : ["false"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert changeList[0].get("ec") == EC.GUILD_BANK_GUILD_TALENTS_LIMIT_IN_TS_EXCEEDED
    assert hero.TalentSets[0].Talents[tsSlotId] != invGuildTalent.id
    assert invGuildTalent.Soulbound != hero.id
    assert invGuildTalent.id in modeldata.UserInventory
    assert heroForce == hero.TalentSets[0].Force


  def item_move_inv2ts_wrong_class_talent_test( self, env ):
    modeldata = env.acc.model

    hero = env.add_hero(modeldata, 'prince')
    invTalent = env.add_talent(modeldata, "Firefox_A0")
    staticTalent = env.acc.SD.getStaticTalent(invTalent)
    modeldata.UserInventory.add( invTalent )
    tsSlotId = staticTalent['minLevel'] * 6 + 1
    heroForce = hero.TalentSets[0].Force

    now = time.time()
    modeldata.MarketingEventsInfo.LampEventInfo.AllowedLamps = 0
    modeldata.replaceGoldLampEvent( 20, 2000, 1, 300 )
    requests = [ ( Item_move_ts2inv , ItemMoveTsToInvRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "dest_slot_id" : ["" + str(tsSlotId) + ""], "talent_set_id" : ["0"],
                                                                                "dest_item_id" : ["" + str(hero.TalentSets[0].Talents[tsSlotId]) + ""]}, False ) ) ]
    changeList = env.execActions( requests )
    assert hero.TalentSets[0].Talents[tsSlotId] == None
    requests = [ ( Item_move_inv2ts , ItemMoveInvToTsRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "src_item_id" : ["" + str(invTalent.id) + ""],
                                                                                "dest_slot_id" : ["" + str(tsSlotId) + ""],
                                                                                "dest_item_id" : ["0"], "talent_set_id" : ["0"],
                                                                                "useLamp" : ["true"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.TalentSets[0].Talents[tsSlotId] == None
    assert invTalent.id in modeldata.UserInventory

  def item_move_inv2ts_good_class_talent_test( self, env ):
    modeldata = env.acc.model

    hero = env.add_hero(modeldata, 'firefox')
    invTalent = env.add_talent(modeldata, "Firefox_A0")
    staticTalent = env.acc.SD.getStaticTalent(invTalent)
    modeldata.UserInventory.add( invTalent )
    tsSlotId = staticTalent['minLevel'] * 6 + 1
    heroForce = hero.TalentSets[0].Force

    now = time.time()
    modeldata.MarketingEventsInfo.LampEventInfo.AllowedLamps = 0
    modeldata.replaceGoldLampEvent( 20, 2000, 1, 300 )
    requests = [ ( Item_move_ts2inv , ItemMoveTsToInvRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "dest_slot_id" : ["" + str(tsSlotId) + ""], "talent_set_id" : ["0"],
                                                                                "dest_item_id" : ["" + str(hero.TalentSets[0].Talents[tsSlotId]) + ""]}, False ) ) ]
    assert hero.TalentSets[0].Talents[tsSlotId] == None
    changeList = env.execActions( requests )
    requests = [ ( Item_move_inv2ts , ItemMoveInvToTsRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "src_item_id" : ["" + str(invTalent.id) + ""],
                                                                                "dest_slot_id" : ["" + str(tsSlotId) + ""],
                                                                                "dest_item_id" : ["0"], "talent_set_id" : ["0"],
                                                                                "useLamp" : ["true"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.TalentSets[0].Talents[tsSlotId] == invTalent.id
    assert invTalent.id in modeldata.UserInventory