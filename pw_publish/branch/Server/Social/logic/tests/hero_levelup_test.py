import sys
sys.path.append('../')
from binascii import crc32
from base.helpers import *
sys.path.append('../..')
from enums import *
import MM

class hero_levelup_test:

  def hero_levelup_test( self, env ):
    modeldata = env.acc.model

    modeldata.hireHero( crc32('highlander'), 0, env.I.WS, env.acc, env.I )
    hero, heroId = modeldata.findHeroByCrc32( crc32("highlander") )
    assert hero
    inventoryCount = len( modeldata.UserInventory )
    ignoreSoulboundCheck = set()
    for talId in modeldata.UserInventory:
      tal = modeldata.getTalentByID( talId )
      staticTal = env.acc.SD.getStaticTalent(tal)
      if staticTal['rarity'] in ["exclusive", "outstanding"]:
        ignoreSoulboundCheck.add(tal)
    heroLevel = env.acc.SD.getHeroExpLevel( hero.Experience )
    level = 11
    exp = env.acc.SD.data['LevelToExperienceTable']['Levels']['Item'][level]

    hero.changeExperience( exp, modeldata, env.I.WS, env.acc, env.I )

    assert env.acc.SD.getHeroExpLevel( hero.Experience ) == heroLevel + level
    assert len( modeldata.UserInventory ) == inventoryCount + level + 1
    for talId in modeldata.UserInventory:
      tal = modeldata.getTalentByID( talId )
      staticTal = env.acc.SD.getStaticTalent(tal)
      if tal not in ignoreSoulboundCheck and staticTal['rarity'] in ["exclusive", "outstanding"]:
        assert hero == tal.Soulbound


  def hero_levelup2_test( self, env ):
    modeldata = env.acc.model

    modeldata.hireHero( crc32('highlander'), 0, env.I.WS, env.acc, env.I )
    
    level = 2
    exp = env.acc.SD.data['LevelToExperienceTable']['Levels']['Item'][level]

    hero, heroId = modeldata.findHeroByCrc32( crc32("highlander") )

    assert hero
    inventoryCount = len( modeldata.UserInventory )
    heroLevel = env.acc.SD.getHeroExpLevel( hero.Experience )

    hero.changeExperience( exp, modeldata, env.I.WS, env.acc, env.I )

    assert env.acc.SD.getHeroExpLevel( hero.Experience ) == heroLevel + level
    assert len( modeldata.UserInventory ) == inventoryCount + level


  def hero_levelup5_test( self, env ):
    modeldata = env.acc.model

    modeldata.hireHero( crc32('highlander'), 0, env.I.WS, env.acc, env.I )
    
    level = 5
    exp = env.acc.SD.data['LevelToExperienceTable']['Levels']['Item'][level]

    hero, heroId = modeldata.findHeroByCrc32( crc32("highlander") )

    assert hero
    inventoryCount = len( modeldata.UserInventory )
    heroLevel = env.acc.SD.getHeroExpLevel( hero.Experience )

    hero.changeExperience( exp, modeldata, env.I.WS, env.acc, env.I )

    assert env.acc.SD.getHeroExpLevel( hero.Experience ) == heroLevel + level
    assert len( modeldata.UserInventory ) == inventoryCount + level
