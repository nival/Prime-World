import sys
sys.path.append('../')
from logic.clear_item_soulbound import *
from logic.hire_hero import *
from binascii import crc32
import time
sys.path.append('../../modeldata')
from changes import *
sys.path.append('../..')
from enums import *
import EC

class clear_item_soulbound_test:
    def clear_item_soulbound_test( self, env ):
        modeldata = env.acc.model
        modeldata.Resources.Gold = gold = 100

        hero = env.add_hero(modeldata, "mowgly")
        talent = env.add_talent(modeldata, "G137") 
        
        talent.Soulbound = hero
        modeldata.UserInventory.add( talent )
    
        requests = [ ( Clear_item_soulbound, ClearItemSoulboundRequest(modeldata, {"talent_id" : ["" + str(talent.id) + ""],
                                                                                   "useLamp" : ["false"],
                                                                                   "aftercontext": ["false"]},
                                                                       False))]
        changeList = env.execActions( requests )
    
        assert talent.Soulbound == IGuidGenerator.InvalidUID 
        assert modeldata.getTalentByID(talent.id).Soulbound == IGuidGenerator.InvalidUID
        
        staticTalent = env.acc.SD.getStaticTalent( talent )
        talent_level = env.acc.SD.getTalentLevelByPoints(talent.Points, staticTalent)
        assert gold - modeldata.Resources.Gold == int(env.acc.SD.getTalentUnsoulboundPrice( staticTalent, talent_level, env.I.Config.getConfig( env.acc.userlocale ) ).Gold)
  
    def clear_item_soulbound_from_ts_with_soulbound_test( self, env ):
        modeldata = env.acc.model
        modeldata.LordInfo.Fame = 100500
        modeldata.Resources.Silver = silver = 1000
        modeldata.Resources.Gold = gold = 1000
    
        requests = [ ( Hire_hero, HireHeroRequest( modeldata, { "PersistentId" : [crc32("highlander")] }, False ) ) ]
        changeList = env.execActions( requests )
        
        for heroId in modeldata.Heroes:
            hero = modeldata.getHeroByID( heroId )
            if hero.class_name == "highlander":
                force = hero.TalentSets[0].Force
                talentId = hero.TalentSets[0].Talents[4]
                talent = modeldata.getTalentByID(talentId)
                hero.TalentSets[1].Talents.add(4, talentId)
                talent.Owner = hero
                talent.ParentTalentSets.add(1,hero.TalentSets[1].id)
                talent.Soulbound = hero
                break
    
        modeldata.Resources.Silver = Silver = 1000
        requests = [ ( Clear_item_soulbound, ClearItemSoulboundRequest(modeldata, {"talent_id": ["" + str(talentId) + ""],
                                                                                   "useLamp" : ["false"],
                                                                                   "aftercontext": ["false"]},
                                                                       False))]
        changeList = env.execActions( requests )
    
        assert talent.id in modeldata.UserInventory 
        assert hero.TalentSets[0].Talents.get(4) is None
        assert bool(talent.ParentTalentSets) == False
        assert talent.Soulbound == IGuidGenerator.InvalidUID
        assert modeldata.Resources.Silver <= silver or modeldata.Resources.Gold <= gold
        staticTalent = env.acc.SD.getStaticTalent( talent )
        talent_level = env.acc.SD.getTalentLevelByPoints(talent.Points, staticTalent)
        assert gold - modeldata.Resources.Gold == int(env.acc.SD.getTalentUnsoulboundPrice( staticTalent, talent_level, env.I.Config.getConfig( env.acc.userlocale ) ).Gold)
        assert silver - modeldata.Resources.Silver == int(env.acc.SD.getTalentUnsoulboundPrice( staticTalent, talent_level, env.I.Config.getConfig( env.acc.userlocale ) ).Silver)

    def clear_item_soulbound_from_ts_test( self, env ):
        modeldata = env.acc.model
        modeldata.LordInfo.Fame = 100500
        modeldata.Resources.Silver = silver = 1000
        modeldata.Resources.Gold = gold = 1000

        requests = [ ( Hire_hero, HireHeroRequest( modeldata, { "PersistentId" : [crc32("highlander")] }, False ) ) ]
        changeList = env.execActions( requests )

        for heroId in modeldata.Heroes:
            hero = modeldata.getHeroByID( heroId )
            if hero.class_name == "highlander":
                force = hero.TalentSets[0].Force
                talentId = hero.TalentSets[0].Talents[4]
                talent = modeldata.getTalentByID(talentId)
                hero.TalentSets[1].Talents.add(4, talentId)
                talent.Owner = hero
                talent.ParentTalentSets.add(1,hero.TalentSets[1].id)
                break

        modeldata.Resources.Silver = Silver = 1000
        requests = [ ( Clear_item_soulbound, ClearItemSoulboundRequest(modeldata, {"talent_id": ["" + str(talentId) + ""],
                                                                                   "useLamp" : ["false"],
                                                                                   "aftercontext": ["false"]},
                                                                       False))]
        changeList = env.execActions( requests )

        assert talent.id in modeldata.UserInventory
        assert hero.TalentSets[0].Talents.get(4) is not None
        assert bool(talent.ParentTalentSets) == True
        assert talent.Soulbound == IGuidGenerator.InvalidUID
        assert modeldata.Resources.Silver == silver or modeldata.Resources.Gold == gold
        staticTalent = env.acc.SD.getStaticTalent( talent )
        assert gold - modeldata.Resources.Gold == 0
        assert silver - modeldata.Resources.Silver == 0

  
    def clear_item_soulbound_no_money( self, env ):
      modeldata = env.acc.model
      modeldata.Resources.Silver = 0
      modeldata.Resources.Gold = 0
  
      hero = env.add_hero(modeldata, "mowgly")
      talent = env.add_talent(modeldata, "G137") 
  
      requests = [ ( Clear_item_soulbound, ClearItemSoulboundRequest(modeldata, {"talent_id": ["" + str(talent.id) + ""],
                                                                                 "useLamp": ["false"],
                                                                                 "aftercontext": ["false"]},
                                                                     False))]
      changeList = env.execActions( requests )
  
      assert( changeList[0].get("ec") == EC.DEBUG_MESSAGE ) 
      assert talent.Soulbound is not None
  
    def clear_item_soulbound_class_from_ts_test( self, env ):
        modeldata = env.acc.model
    
        for heroId in modeldata.HeroesKeeper:
            hero = modeldata.getHeroByID( heroId )
            hero.Hired = True
            talentId = hero.TalentSets[0].Talents[1]
            break
    
        requests = [ ( Clear_item_soulbound, ClearItemSoulboundRequest(modeldata, {"talent_id": ["" + str(talentId) + ""],
                                                                                   "useLamp": ["false"],
                                                                                   "aftercontext": ["false"]},
                                                                       False))]
        changeList = env.execActions( requests )
    
        assert( changeList.get("ModelData") == None ) 
      
    def clear_class_soulbound_test( self, env ):
      modeldata = env.acc.model
      
      hero = env.add_hero(modeldata, "rockman")
      talent = env.add_talent(modeldata, "Rockman_A1") 
  
      talent.Soulbound = hero
      
      modeldata.UserInventory.add( talent ) 
  
      requests = [ ( Clear_item_soulbound, ClearItemSoulboundRequest(modeldata, {"talent_id": ["" + str(talent.id) + ""],
                                                                                 "useLamp": ["false"],
                                                                                 "aftercontext": ["false"]},
                                                                     False))]
      changeList = env.execActions( requests )
  
  
      assert changeList[0].get('ec') == EC.DEBUG_MESSAGE
      assert( modeldata.getTalentByID(talent.id).Soulbound == hero.id ) 
      
    def clear_unsoulbounded_talent_test( self, env ):
        modeldata = env.acc.model
    
        talent = env.add_talent(modeldata, "G137") 
        
        modeldata.UserInventory.add( talent ) 
    
        requests = [ ( Clear_item_soulbound, ClearItemSoulboundRequest(modeldata, {"talent_id": ["" + str(talent.id) + ""],
                                                                                   "useLamp": ["false"],
                                                                                   "aftercontext": ["false"]},
                                                                       False))]
        changeList = env.execActions( requests )
    
        assert changeList[0].get('ec') == EC.DEBUG_MESSAGE
        
    def clear_excellent_item_soulbound_test( self, env ):
        modeldata = env.acc.model

        hero = env.add_hero(modeldata, "mowgly")
        talent = env.add_talent(modeldata, "G314")
        staticTalent = env.acc.SD.getStaticTalent(talent)

        startResources = env.acc.SD.copyPrice(modeldata.Resources)
        talent_level = env.acc.SD.getTalentLevelByPoints(talent.Points, staticTalent)
        price = env.acc.SD.getTalentUnsoulboundPrice(staticTalent, talent_level, env.acc.getConfig())

        modeldata.sell(price, env.acc, False)

        talent.Soulbound = hero
        modeldata.UserInventory.add( talent )
    
        requests = [ ( Clear_item_soulbound, ClearItemSoulboundRequest(modeldata, {"talent_id": ["" + str(talent.id) + ""],
                                                                                   "useLamp": ["false"],
                                                                                   "aftercontext": ["false"]},
                                                                       False))]
        changeList = env.execActions( requests )


        finalResources = env.acc.SD.copyPrice(modeldata.Resources)
        env.acc.SD.getSubtractPrice(finalResources, startResources)

        assert talent.Soulbound == IGuidGenerator.InvalidUID 
        assert modeldata.getTalentByID(talent.id).Soulbound == IGuidGenerator.InvalidUID
        

        assert env.acc.SD.isValidPrice(finalResources) == False
      
    def clear_item_soulbound_with_lamp_test( self, env ):
        modeldata = env.acc.model
        hero = env.add_hero( modeldata, "mowgly" )
        talent = env.add_talent( modeldata, "G314" ) 
        talent.Soulbound = hero
        modeldata.UserInventory.add( talent )
        
        now = time.time()
        modeldata.MarketingEventsInfo.LampEventInfo.AllowedLamps = 0
        modeldata.replaceGoldLampEvent( 20, 2000, 1, 300 )
    
        requests = [ ( Clear_item_soulbound, ClearItemSoulboundRequest(modeldata, {"talent_id": ["" + str(talent.id) + ""],
                                                                                   "useLamp": ["true"],
                                                                                   "aftercontext": ["false"]},
                                                                       False))]
        changeList = env.execActions( requests )
    
        assert talent.Soulbound == IGuidGenerator.InvalidUID 
        assert modeldata.getTalentByID( talent.id ).Soulbound == IGuidGenerator.InvalidUID
        assert modeldata.MarketingEventsInfo.LampEventInfo.dbId == ""
  
    def clear_item_soulbound_infinity_lamp_test( self, env ):
        modeldata = env.acc.model
        hero = env.add_hero( modeldata, "mowgly" )
        talent = env.add_talent( modeldata, "G314" )
        talent.Soulbound = hero
        modeldata.UserInventory.add( talent )
        modeldata.UserInventory.add( talent )
        now = time.time()
        modeldata.MarketingEventsInfo.LampEventInfo.AllowedLamps = 0
        modeldata.replaceGoldLampEvent( 20, 2000, 1, 300 )
    
        modeldata.MarketingEventsInfo.LampEventInfo.TransactionsLeft = 0
    
        requests = [ ( Clear_item_soulbound, ClearItemSoulboundRequest(modeldata, {"talent_id": ["" + str(talent.id) + ""],
                                                                                   "useLamp": ["true"],
                                                                                   "aftercontext": ["false"]},
                                                                       False))]
        changeList = env.execActions( requests )
    
        assert talent.Soulbound == IGuidGenerator.InvalidUID
        assert modeldata.getTalentByID( talent.id ).Soulbound == IGuidGenerator.InvalidUID
        assert modeldata.MarketingEventsInfo.LampEventInfo.dbId != ""
  
  
    def clear_item_soulbound_with_guild_info_test( self, env ):
        modeldata = env.acc.model
        modeldata.Resources.Gold = gold = 100
        modeldata.Resources.Perl = perl = 100
    
        hero = env.add_hero(modeldata, "mowgly")
        talent = env.add_talent(modeldata, "G137") 
        
        talent.Soulbound = hero
        gbi, gbi_id = env.acc.model.newGuildBankInfo()
        talent.GuildBankInfo = gbi
        talent.GuildBankInfo.GuildAuid = 1
        talent.GuildBankInfo.GuildTalentId = 2
        talent.GuildBankInfo.OwnerId = 3
        talent.GuildBankInfo.HeroClassId = 4
    
        modeldata.UserInventory.add( talent )
    
        requests = [ ( Clear_item_soulbound, ClearItemSoulboundRequest(modeldata, {"talent_id": ["" + str(talent.id) + ""],
                                                                                   "useLamp": ["false"],
                                                                                   "aftercontext": ["false"]},
                                                                       False))]
        changeList = env.execActions( requests )
    
        assert talent.Soulbound == IGuidGenerator.InvalidUID
        assert modeldata.getTalentByID(talent.id).Soulbound == IGuidGenerator.InvalidUID
        assert talent.GuildBankInfo.HeroClassId == IGuidGenerator.InvalidUID
        
        staticTalent = env.acc.SD.getStaticTalent( talent )
        talent_level = env.acc.SD.getTalentLevelByPoints(talent.Points, staticTalent)
        assert gold - modeldata.Resources.Gold == int(env.acc.SD.getTalentUnsoulboundPrice( staticTalent, talent_level, env.I.Config.getConfig( env.acc.userlocale ) ).Gold)
        
    def clear_outstanding_item_soulbound_test( self, env ):
        modeldata = env.acc.model
        modeldata.Resources.Gold = gold = 100
        modeldata.Resources.Perl = perl = 100
    
        hero = env.add_hero(modeldata, "mowgly")
        talent = env.add_talent(modeldata, "G463")
        
        talent.Soulbound = hero
        modeldata.UserInventory.add( talent )
    
        requests = [ ( Clear_item_soulbound, ClearItemSoulboundRequest(modeldata, {"talent_id" : ["" + str(talent.id) + ""],
                                                                                   "useLamp" : ["false"],
                                                                                   "aftercontext": ["false"]},
                                                                       False))]
        changeList = env.execActions( requests )
    
        assert talent.Soulbound == IGuidGenerator.InvalidUID 
        assert modeldata.getTalentByID(talent.id).Soulbound == IGuidGenerator.InvalidUID
        
        staticTalent = env.acc.SD.getStaticTalent( talent )
        talent_level = env.acc.SD.getTalentLevelByPoints(talent.Points, staticTalent)
        assert gold - modeldata.Resources.Gold == int(env.acc.SD.getTalentUnsoulboundPrice( staticTalent, talent_level, env.I.Config.getConfig( env.acc.userlocale ) ).Gold)
        assert perl - modeldata.Resources.Perl == int(env.acc.SD.getTalentUnsoulboundPrice( staticTalent, talent_level, env.I.Config.getConfig( env.acc.userlocale ) ).Perl)

    def clear_outstanding_item_soulbound_with_lamp_test( self, env ):
        modeldata = env.acc.model
        hero = env.add_hero( modeldata, "mowgly" )
        talent = env.add_talent( modeldata, "G463" )
        talent.Soulbound = hero
        modeldata.UserInventory.add( talent )

        now = time.time()
        modeldata.MarketingEventsInfo.LampEventInfo.AllowedLamps = 0
        modeldata.replaceGoldLampEvent( 0, 2000, 1, 300 )

        requests = [ ( Clear_item_soulbound, ClearItemSoulboundRequest(modeldata, {"talent_id": ["" + str(talent.id) + ""],
                                                                                   "useLamp": ["true"],
                                                                                   "aftercontext": ["false"]},
                                                                       False))]
        changeList = env.execActions( requests )

        assert talent.Soulbound == IGuidGenerator.InvalidUID
        assert modeldata.getTalentByID( talent.id ).Soulbound == IGuidGenerator.InvalidUID
        assert modeldata.MarketingEventsInfo.LampEventInfo.dbId == ""

    def clear_item_soulbound_without_soulbound ( self, env ):
        modeldata = env.acc.model
        modeldata.Resources.Gold = gold = 100

        hero = env.add_hero(modeldata, "mowgly")
        talent = env.add_talent(modeldata, "G137")

        talent.Soulbound = None

        modeldata.UserInventory.add( talent )

        requests = [ ( Clear_item_soulbound, ClearItemSoulboundRequest(modeldata, {"talent_id": ["" + str(talent.id) + ""],
                                                                                   "useLamp": ["false"],
                                                                                   "aftercontext": ["false"]},
                                                                       False))]
        changeList = env.execActions( requests )

        assert talent.Soulbound is None or talent.Soulbound == IGuidGenerator.InvalidUID
        staticTalent = env.acc.SD.getStaticTalent( talent )
        assert changeList[0].get('ec') == EC.DEBUG_MESSAGE
        assert gold - modeldata.Resources.Gold == 0

    def clear_item_soulbound_without_soulbound_GI ( self, env ):
        modeldata = env.acc.model
        modeldata.Resources.Gold = gold = 100

        hero = env.add_hero(modeldata, "mowgly")
        talent = env.add_talent(modeldata, "G137")
        modeldata.UserInventory.add( talent )

        #talent.Soulbound = None
        gbi, gbi_id = env.acc.model.newGuildBankInfo()
        talent.GuildBankInfo = gbi
        talent.GuildBankInfo.GuildAuid = 1
        talent.GuildBankInfo.GuildTalentId = 2
        talent.GuildBankInfo.OwnerId = 3
        talent.GuildBankInfo.HeroClassId = 4

        requests = [ ( Clear_item_soulbound, ClearItemSoulboundRequest(modeldata, {"talent_id": ["" + str(talent.id) + ""],
                                                                                   "useLamp": ["false"],
                                                                                   "aftercontext": ["false"]},
                                                                       False))]
        changeList = env.execActions( requests )

        assert talent.Soulbound is None or talent.Soulbound == IGuidGenerator.InvalidUID
        staticTalent = env.acc.SD.getStaticTalent( talent )
        talent_level = env.acc.SD.getTalentLevelByPoints(talent.Points, staticTalent)
        assert gold - modeldata.Resources.Gold == int(env.acc.SD.getTalentUnsoulboundPrice( staticTalent, talent_level, env.I.Config.getConfig( env.acc.userlocale ) ).Gold)

