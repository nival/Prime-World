import sys
sys.path.append('../')
sys.path.append('../..')
from logic.buy_hero_gold import *
from binascii import crc32
from base.helpers import *
from enums import *
from MM import ESex

class buy_hero_gold_test:

  def buy_hero_gold_test( self, env ):
    modeldata = env.acc.model
    staticHero = env.acc.SD.getStaticHeroByClassId( crc32("alchemist") )
    Gold = int(env.acc.SD.GetHeroGoldPrice(staticHero, env.I.Config.getConfig( env.acc.userlocale ), env.acc.sex == ESex.FEMALE))
    modeldata.Resources.Gold = Gold
    modeldata.LordInfo.Fame = 9000
    
    heroesCount = len( modeldata.HeroesKeeper )

    silver = modeldata.Resources.Silver
    gold = modeldata.Resources.Gold

    requests = [ ( Buy_hero_gold, BuyHeroGoldRequest( modeldata, { "PersistentId" : [crc32("alchemist")] }, False ) ) ]
    changeList = env.execActions( requests )
            
    assert len( modeldata.HeroesKeeper ) == heroesCount + 1
    assert len( modeldata.Heroes ) == heroesCount + 1
    
    assert silver == modeldata.Resources.Silver
    assert gold - Gold == modeldata.Resources.Gold 
    
    
def buy_hero_gold_wrong_level_test( self, env ):
    modeldata = env.acc.model
    staticHero = env.acc.SD.getStaticHeroByClassId( crc32("highlander") )
    Gold = int(env.acc.SD.GetHeroGoldPrice(staticHero, env.I.Config.getConfig( env.acc.userlocale ), env.acc.sex == ESex.FEMALE))
    modeldata.Resources.Gold = Gold
    modeldata.LordInfo.Fame = 9000
    
    heroesCount = len( modeldata.HeroesKeeper )

    silver = modeldata.Resources.Silver
    gold = modeldata.Resources.Gold

    requests = [ ( Buy_hero_gold, BuyHeroGoldRequest( modeldata, { "PersistentId" : [crc32("highlander")] }, False ) ) ]
    changeList = env.execActions( requests )
            
    assert len( modeldata.HeroesKeeper ) == heroesCount 
    assert len( modeldata.Heroes ) == heroesCount
    
    assert silver == modeldata.Resources.Silver
    assert gold == modeldata.Resources.Gold     