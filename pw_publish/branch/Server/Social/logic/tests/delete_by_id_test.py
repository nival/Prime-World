import sys
sys.path.append('../')
sys.path.append('../..')
from logic.hire_hero import *
from logic.select_skin import *
from logic.buy_skin import *
from binascii import crc32
from base.helpers import *
from enums import *

class delete_by_id_test:
  def delete_by_id_test( self, env ):
    modeldata = env.acc.model
    assert env.acc.db.fraction == 'A'
    hero, heroId = modeldata.findHeroByCrc32( crc32('inventor') )
    assert heroId == 0
    silver = modeldata.Resources.Silver = 100000
    Resource1 = modeldata.Resources.Resource1 = 100000
    Resource2 = modeldata.Resources.Resource2 = 100000
    Resource3 = modeldata.Resources.Resource3 = 100000
    modeldata.LordInfo.Fame = 80000

    requests = [ ( Hire_hero, HireHeroRequest( modeldata, { "PersistentId" : [crc32('inventor')] }, False ) )]
    changeList = env.execActions( requests )

    hero, heroId = modeldata.findHeroByCrc32( crc32('inventor') )
    assert heroId != 0
    modeldata.deleteByID( heroId )
    hero = modeldata.getHeroByID( heroId )
    assert hero == None

  def delete_by_id_too_many_refs_test( self, env ):
    modeldata = env.acc.model
    modeldata.LordInfo.Fame = 100000
    assert env.acc.db.fraction == 'A'

    silver = modeldata.Resources.Silver = 1000
    Resource1 = modeldata.Resources.Resource1 = 1000
    Resource2 = modeldata.Resources.Resource2 = 1000
    Resource3 = modeldata.Resources.Resource3 = 1000

    requests = [ ( Hire_hero, HireHeroRequest( modeldata, { "PersistentId" : [crc32("highlander")] }, False ) )]
    changeList = env.execActions( requests )

    talentId = modeldata.addNewTalent( )
    talent = modeldata.getTalentByID( talentId )
    hero, heroId = modeldata.findHeroByCrc32( crc32("highlander") )
    talent.defaulfForHero = hero
    hero.__dict__["refCounter"] = 100500
    assert 100500 == hero.__dict__["refCounter"]
    modeldata.deleteByID( hero.id )
    hero = modeldata.getHeroByID( hero.id )
    assert hero == None
    
  def delete_skin_by_id_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = 1000
    hero, heroId = modeldata.findHeroByCrc32( crc32("thundergod") )
    assert hero
    assert len( hero.HeroSkins.Skins ) == 0

    requests = [ ( Buy_skin, BuySkinRequest( modeldata, { "PersistentId" : [crc32("thundergod_S1_A")], "guardParty":[False], "master_auid":[0], "change_party_skin":[False] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( hero.HeroSkins.Skins ) == 1

    assert hero.HeroSkins.Skins.getValues()[0].PersistentId == crc32("thundergod_S1_A")
    assert hero.HeroSkins.CurrentSkin.get()
    assert hero.HeroSkins.CurrentSkin.PersistentId == crc32("thundergod_S1_A")

    requests = [ ( Select_skin, SelectSkinRequest( modeldata, { "hero_id" : [hero.getID()], "skin_id" : [hero.HeroSkins.Skins.getValues()[0].getID()], "guardParty":[False], "master_auid":[0], "change_party_skin":[True] }, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.HeroSkins.CurrentSkin.get()
    assert hero.HeroSkins.CurrentSkin.PersistentId == crc32("thundergod_S1_A")



    modeldata.deleteByID( hero.HeroSkins.Skins.getValues()[0].id )
    hero = modeldata.getHeroByID( hero.id )
    assert len( hero.HeroSkins.Skins ) == 0
    assert len( modeldata.SkinsKeeper) == 0
    assert hero.HeroSkins.CurrentSkin.object == 0

