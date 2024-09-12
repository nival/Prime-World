import sys
sys.path.append('../')
sys.path.append('../..')
from logic.buy_special_hero import *
from binascii import crc32
from base.helpers import *
from enums import *

class buy_special_hero_test:

  def buy_special_hero_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = env.I.Config.getConfig( env.acc.userlocale ).BuySpecialHeroEventInfo.Price
    modeldata.LordInfo.Fame = 9000 #not to add resourses for levelup
    
    heroes_count_keeper = len( modeldata.HeroesKeeper ) 
    heroes_count = len( modeldata.Heroes )

    silver = modeldata.Resources.Silver
    gold = modeldata.Resources.Gold

    requests = [ ( Buy_special_hero, BuySpecialHeroRequest( modeldata,{  }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( modeldata.HeroesKeeper ) == heroes_count_keeper + 1 
    assert len( modeldata.Heroes ) == heroes_count + 1
    assert silver == modeldata.Resources.Silver
    assert gold - env.I.Config.getConfig( env.acc.userlocale ).BuySpecialHeroEventInfo.Price == modeldata.Resources.Gold

    if env.acc.db.fraction == 'A':
      PersistentId = crc32(env.I.Config.getConfig( env.acc.userlocale ).BuySpecialHeroEventInfo.HeroIdA)
    else:
      PersistentId = crc32(env.I.Config.getConfig( env.acc.userlocale ).BuySpecialHeroEventInfo.HeroIdB)    
    hero, heroId = modeldata.findHeroByCrc32( PersistentId )
    assert heroId !=0
    
  def buy_special_hero_expired_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = env.I.Config.getConfig( env.acc.userlocale ).BuySpecialHeroEventInfo.Price
    modeldata.LordInfo.Fame = 9000 #not to add resourses for levelup
    if "/UI/Content/MarketingEvents/BuySpecialHero" in env.I.Config.getConfig( env.acc.userlocale ).MARKETING_EVENTS:
      env.I.Config.getConfig( env.acc.userlocale ).MARKETING_EVENTS.remove("/UI/Content/MarketingEvents/BuySpecialHero")
    
    heroes_count_keeper = len( modeldata.HeroesKeeper ) 
    heroes_count = len( modeldata.Heroes )

    silver = modeldata.Resources.Silver
    gold = modeldata.Resources.Gold

    requests = [ ( Buy_special_hero, BuySpecialHeroRequest( modeldata,{  }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( modeldata.HeroesKeeper ) == heroes_count_keeper
    assert len( modeldata.Heroes ) == heroes_count 
    assert silver == modeldata.Resources.Silver
    assert gold  == modeldata.Resources.Gold