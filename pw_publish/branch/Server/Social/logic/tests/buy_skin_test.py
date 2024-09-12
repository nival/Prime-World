import sys
sys.path.append('../')
sys.path.append('../..')
from logic.buy_skin import *
from binascii import crc32
from base.helpers import *
from enums import *

class buy_skin_test:
  def buy_skin_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = 1000
    
    hero, heroId = modeldata.findHeroByCrc32( crc32("thundergod") )
    assert hero
    assert len( hero.HeroSkins.Skins ) == 0
   
    requests = [ ( Buy_skin, BuySkinRequest( modeldata, { "PersistentId" : [crc32("thundergod_S1_A")], "guardParty":[False], "master_auid":[0], "change_party_skin":[False] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( hero.HeroSkins.Skins ) == 1
    assert hero.HeroSkins.Skins.getValues()[0].PersistentId == crc32("thundergod_S1_A")


  def buy_skin_badname_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = 1000
    hero, heroId = modeldata.findHeroByCrc32( crc32("thundergod") )
    assert hero
    assert len( hero.HeroSkins.Skins ) == 0
   
    requests = [ ( Buy_skin, BuySkinRequest( modeldata, { "PersistentId" : [crc32("bla-bla")], "guardParty":[False], "master_auid":[0], "change_party_skin":[False] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( hero.HeroSkins.Skins ) == 0


  def buy_skin_badfraction_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = 1000
    hero, heroId = modeldata.findHeroByCrc32( crc32("thundergod") )
    assert hero
    assert len( hero.HeroSkins.Skins ) == 0
   
    requests = [ ( Buy_skin, BuySkinRequest( modeldata, { "PersistentId" : [crc32("thundergod_S1_B")], "guardParty":[False], "master_auid":[0], "change_party_skin":[False] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( hero.HeroSkins.Skins ) == 1


  def buy_skin_badhero_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = 1000
    hero, heroId = modeldata.findHeroByCrc32( crc32("thundergod") )
    assert hero
    assert len( hero.HeroSkins.Skins ) == 0
   
    requests = [ ( Buy_skin, BuySkinRequest( modeldata, { "PersistentId" : [crc32("archeress_S1_A")], "guardParty":[False], "master_auid":[0], "change_party_skin":[False] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( hero.HeroSkins.Skins ) == 0


  def buy_skin_twice_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = 1000
    hero, heroId = modeldata.findHeroByCrc32( crc32("thundergod") )
    assert hero
    assert len( hero.HeroSkins.Skins ) == 0
    skinId = crc32("thundergod_S1_A")
   
    requests = [ ( Buy_skin, BuySkinRequest( modeldata, { "PersistentId" : [skinId], "guardParty":[False], "master_auid":[0], "change_party_skin":[False] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( hero.HeroSkins.Skins ) == 1

    requests = [ ( Buy_skin, BuySkinRequest( modeldata, { "PersistentId" : [skinId], "guardParty":[False], "master_auid":[0], "change_party_skin":[False] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( hero.HeroSkins.Skins ) == 1


  def buy_skin_override_price_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = 1000
    hero, heroId = modeldata.findHeroByCrc32( crc32("thundergod") )
    assert hero
    assert len( hero.HeroSkins.Skins ) == 0
    config = env.I.Config.getConfig( env.acc.userlocale )
    config.EventToolsChangeFields.SKIN_GOLD_PRICES["thundergod_S1_A"] = 73

    requests = [ ( Buy_skin, BuySkinRequest( modeldata, { "PersistentId" : [crc32("thundergod_S1_A")], "guardParty":[False], "master_auid":[0], "change_party_skin":[False] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( hero.HeroSkins.Skins ) == 1
    assert modeldata.Resources.Gold+config.EventToolsChangeFields.SKIN_GOLD_PRICES["thundergod_S1_A"] == 1000
    config.EventToolsChangeFields.SKIN_GOLD_PRICES.remove("thundergod_S1_A")


  def buy_skin_override_price_notenought_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = 10
    hero, heroId = modeldata.findHeroByCrc32( crc32("thundergod") )
    assert hero
    assert len( hero.HeroSkins.Skins ) == 0
    config = env.I.Config.getConfig( env.acc.userlocale )
    config.EventToolsChangeFields.SKIN_GOLD_PRICES["thundergod_S1_A"] = 73

    requests = [ ( Buy_skin, BuySkinRequest( modeldata, { "PersistentId" : [crc32("thundergod_S1_A")], "guardParty":[False], "master_auid":[0], "change_party_skin":[False] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( hero.HeroSkins.Skins ) == 0
    assert modeldata.Resources.Gold == 10
    
    config.EventToolsChangeFields.SKIN_GOLD_PRICES.remove("thundergod_S1_A")



  def buy_second_skin_fail_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = 1000
    hero, heroId = modeldata.findHeroByCrc32( crc32("thundergod") )
    assert hero
    assert len( hero.HeroSkins.Skins ) == 0
   
    requests = [ ( Buy_skin, BuySkinRequest( modeldata, { "PersistentId" : [crc32("thundergod_S1_A")], "guardParty":[False], "master_auid":[0], "change_party_skin":[False] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( hero.HeroSkins.Skins ) == 1
    assert hero.HeroSkins.Skins.getValues()[0].PersistentId == crc32("thundergod_S1_A")

    requests = [ ( Buy_skin, BuySkinRequest( modeldata, { "PersistentId" : [crc32("thundergod_S3_A")], "guardParty":[False], "master_auid":[0], "change_party_skin":[False] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( hero.HeroSkins.Skins ) == 1
    
  def buy_event_skin_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = 1000
    
    hero, heroId = modeldata.findHeroByCrc32( crc32("thundergod") )
    assert hero
    assert len( hero.HeroSkins.Skins ) == 0
    
    modeldata.EventSkins.append(crc32("thundergod_S1_A"))
    modeldata.ActiveEventSkins.append(crc32("thundergod_S1_A"))
   
    requests = [ ( Buy_skin, BuySkinRequest( modeldata, { "PersistentId" : [crc32("thundergod_S1_A")], "guardParty":[False], "master_auid":[0], "change_party_skin":[False] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( hero.HeroSkins.Skins ) == 1
    assert hero.HeroSkins.Skins.getValues()[0].PersistentId == crc32("thundergod_S1_A") 
    
  def buy_disabled_event_skin_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = 1000
    
    hero, heroId = modeldata.findHeroByCrc32( crc32("thundergod") )
    assert hero
    assert len( hero.HeroSkins.Skins ) == 0
    
    modeldata.EventSkins.append(crc32("thundergod_S1_A"))
   
    requests = [ ( Buy_skin, BuySkinRequest( modeldata, { "PersistentId" : [crc32("thundergod_S1_A")], "guardParty":[False], "master_auid":[0], "change_party_skin":[False] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( hero.HeroSkins.Skins ) == 0
  


    