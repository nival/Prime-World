import sys
sys.path.append('../')
sys.path.append('../..')
from logic.select_skin import *
from logic.buy_skin import *
from binascii import crc32
from base.helpers import *
from enums import *

class select_skin_test:

  def select_skin_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = 1000
    hero, heroId = modeldata.findHeroByCrc32( crc32("thundergod") )
    assert hero
    assert len( hero.HeroSkins.Skins ) == 0
   
    requests = [ ( Buy_skin, BuySkinRequest( modeldata, { "PersistentId" : [crc32("thundergod_S1_A")], "guardParty":[False], "master_auid":[0], "change_party_skin":[True] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( hero.HeroSkins.Skins ) == 1
    assert hero.HeroSkins.Skins.getValues()[0].PersistentId == crc32("thundergod_S1_A")
    assert hero.HeroSkins.CurrentSkin.get()
    assert hero.HeroSkins.CurrentSkin.PersistentId == crc32("thundergod_S1_A")

    requests = [ ( Select_skin, SelectSkinRequest( modeldata, { "hero_id" : [hero.getID()], "skin_id" : [hero.HeroSkins.Skins.getValues()[0].getID()], "guardParty":[False], "master_auid":[0] }, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.HeroSkins.CurrentSkin.get()
    assert hero.HeroSkins.CurrentSkin.PersistentId == crc32("thundergod_S1_A")
  

  def select_skin_none_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = 1000
    hero, heroId = modeldata.findHeroByCrc32( crc32("thundergod") )
    assert hero
    assert len( hero.HeroSkins.Skins ) == 0
   
    requests = [ ( Buy_skin, BuySkinRequest( modeldata, { "PersistentId" : [crc32("thundergod_S1_A")], "guardParty":[False], "master_auid":[0], "change_party_skin":[True] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( hero.HeroSkins.Skins ) == 1
    assert hero.HeroSkins.Skins.getValues()[0].PersistentId == crc32("thundergod_S1_A")
    assert hero.HeroSkins.CurrentSkin.get()
    assert hero.HeroSkins.CurrentSkin.PersistentId == crc32("thundergod_S1_A")

    requests = [ ( Select_skin, SelectSkinRequest( modeldata, { "hero_id" : [hero.getID()], "skin_id" : [hero.HeroSkins.Skins.getValues()[0].getID()], "guardParty":[False], "master_auid":[0], "change_party_skin":[True] }, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.HeroSkins.CurrentSkin.get()
    assert hero.HeroSkins.CurrentSkin.PersistentId == crc32("thundergod_S1_A")
  
    requests = [ ( Select_skin, SelectSkinRequest( modeldata, { "hero_id" : [hero.getID()], "skin_id" : [0], "guardParty":[False], "master_auid":[0], "change_party_skin":[True] }, False ) ) ]
    changeList = env.execActions( requests )

    assert not hero.HeroSkins.CurrentSkin.get()


  def select_skin_none_then_norm_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = 1000
    hero, heroId = modeldata.findHeroByCrc32( crc32("thundergod") )
    assert hero
    assert len( hero.HeroSkins.Skins ) == 0
   
    requests = [ ( Buy_skin, BuySkinRequest( modeldata, { "PersistentId" : [crc32("thundergod_S1_A")], "guardParty":[False], "master_auid":[0], "change_party_skin":[True] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( hero.HeroSkins.Skins ) == 1
    assert hero.HeroSkins.Skins.getValues()[0].PersistentId == crc32("thundergod_S1_A")
    assert hero.HeroSkins.CurrentSkin.get()
    assert hero.HeroSkins.CurrentSkin.PersistentId == crc32("thundergod_S1_A")

    requests = [ ( Select_skin, SelectSkinRequest( modeldata, { "hero_id" : [hero.getID()], "skin_id" : [hero.HeroSkins.Skins.getValues()[0].getID()], "guardParty":[False], "master_auid":[0], "change_party_skin":[True] }, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.HeroSkins.CurrentSkin.get()
    assert hero.HeroSkins.CurrentSkin.PersistentId == crc32("thundergod_S1_A")
  
    requests = [ ( Select_skin, SelectSkinRequest( modeldata, { "hero_id" : [hero.getID()], "skin_id" : [0], "guardParty":[False], "master_auid":[0], "change_party_skin":[True] }, False ) ) ]
    changeList = env.execActions( requests )

    assert not hero.HeroSkins.CurrentSkin.get()

    requests = [ ( Select_skin, SelectSkinRequest( modeldata, { "hero_id" : [hero.getID()], "skin_id" : [hero.HeroSkins.Skins.getValues()[0].getID()], "guardParty":[False], "master_auid":[0], "change_party_skin":[True] }, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.HeroSkins.CurrentSkin.get()
    assert hero.HeroSkins.CurrentSkin.PersistentId == crc32("thundergod_S1_A")
