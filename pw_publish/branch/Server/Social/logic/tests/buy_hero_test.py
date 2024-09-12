# -*- coding: utf-8 -*-
import sys
sys.path.append('../')
sys.path.append('../..')
from logic.buy_hero import *
from binascii import crc32
from base.helpers import *
from enums import *
from MM import ESex

class buy_hero_test:

  def buy_hero_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = env.I.Config.getConfig( env.acc.userlocale ).BUY_HERO_PRICE
    modeldata.LordInfo.Fame = 9000
    
    heroesCount = len( modeldata.HeroesKeeper )
    # раньше за покупку героя давался домик с голдой, теперь нет - убрал все проверки на это
    #buildingsCount = len( modeldata.ConstructionsKeeper )
    assert modeldata.MarketingEventsInfo.IsBuyHeroComplete == False

    silver = modeldata.Resources.Silver
    gold = modeldata.Resources.Gold

    requests = [ ( Buy_hero, BuyHeroRequest( modeldata, { "PersistentId" : [crc32("rockman")] }, False ) ) ]
    changeList = env.execActions( requests )
        
    
    assert len(modeldata.HeroesKeeper) == heroesCount + 1
    assert len(modeldata.Heroes) == heroesCount + 1
   #assert len(modeldata.ConstructionsKeeper) == buildingsCount + 1
    
    assert silver == modeldata.Resources.Silver
    Gold = int(env.I.Config.getConfig( env.acc.userlocale ).BUY_HERO_PRICE)
    assert gold - modeldata.Resources.Gold == Gold 
    
    assert modeldata.MarketingEventsInfo.IsBuyHeroComplete == True
    #assert modeldata.MarketingEventsInfo.GoldHouseActionState == GoldHouseActionState.ShowPlaceHouseEvent

  def buy_hero_test_with_wrong_cost( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = env.I.Config.getConfig( env.acc.userlocale ).BUY_HERO_PRICE
    
    heroesCount = len( modeldata.HeroesKeeper )
    buildingsCount = len( modeldata.ConstructionsKeeper )
    assert modeldata.MarketingEventsInfo.IsBuyHeroComplete == False

    silver = modeldata.Resources.Silver
    gold = modeldata.Resources.Gold

    requests = [ ( Buy_hero, BuyHeroRequest( modeldata, { "PersistentId" : [crc32("frogenglut")] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( modeldata.HeroesKeeper ) == heroesCount
    assert len( modeldata.Heroes ) == heroesCount
    assert len(modeldata.ConstructionsKeeper) == buildingsCount
    assert silver == modeldata.Resources.Silver
    assert gold == modeldata.Resources.Gold
    assert modeldata.MarketingEventsInfo.IsBuyHeroComplete == False
    assert modeldata.MarketingEventsInfo.GoldHouseActionState == GoldHouseActionState.ShowBuyHeroEvent
    
  def buy_hero_test_action_expired( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = env.I.Config.getConfig( env.acc.userlocale ).BUY_HERO_PRICE
    modeldata.LordInfo.Fame = 10000
    
    heroesCount = len( modeldata.HeroesKeeper )
    buildingsCount = len( modeldata.ConstructionsKeeper )
    modeldata.MarketingEventsInfo.IsBuyHeroComplete = True

    silver = modeldata.Resources.Silver
    gold = modeldata.Resources.Gold

    requests = [ ( Buy_hero, BuyHeroRequest( modeldata, { "PersistentId" : [crc32("highlander")] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( modeldata.HeroesKeeper ) == heroesCount
    assert len( modeldata.Heroes ) == heroesCount
    assert len(modeldata.ConstructionsKeeper) == buildingsCount
    assert silver == modeldata.Resources.Silver
    assert gold == modeldata.Resources.Gold
    assert modeldata.MarketingEventsInfo.IsBuyHeroComplete == True
    
  def buy_hero_test_non_existing_hero( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = env.I.Config.getConfig( env.acc.userlocale ).BUY_HERO_PRICE
    
    heroesCount = len( modeldata.HeroesKeeper )
    buildingsCount = len( modeldata.ConstructionsKeeper )
    assert modeldata.MarketingEventsInfo.IsBuyHeroComplete == False

    silver = modeldata.Resources.Silver
    gold = modeldata.Resources.Gold

    requests = [ ( Buy_hero, BuyHeroRequest( modeldata, { "PersistentId" : [crc32("non_existing_hero")] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( modeldata.HeroesKeeper ) == heroesCount
    assert len( modeldata.Heroes ) == heroesCount
    assert len(modeldata.ConstructionsKeeper) == buildingsCount
    assert silver == modeldata.Resources.Silver
    assert gold == modeldata.Resources.Gold
    assert modeldata.MarketingEventsInfo.IsBuyHeroComplete == False
    assert modeldata.MarketingEventsInfo.GoldHouseActionState == GoldHouseActionState.ShowBuyHeroEvent
    
  #def buy_hero_test_gender_cost_differ( self, env ):
    #modeldata = env.acc.model
    #modeldata.LordInfo.Fame = 100500 #not to add resourses for levelup
    #modeldata.Resources.Gold = env.I.Config.getConfig( env.acc.userlocale ).BUY_HERO_PRICE
    
    #heroesCount = len( modeldata.HeroesKeeper )
    #assert modeldata.MarketingEventsInfo.IsBuyHeroComplete == False

    #silver = modeldata.Resources.Silver
    #gold = modeldata.Resources.Gold
    
    #requests = [ ( Buy_hero, BuyHeroRequest( modeldata, { "PersistentId" : [crc32("bard")] }, False ) ) ]
    #changeList = env.execActions( requests )

    #assert len( modeldata.HeroesKeeper ) == heroesCount
    #assert len( modeldata.Heroes ) == heroesCount
    #assert silver == modeldata.Resources.Silver
    #assert gold == modeldata.Resources.Gold
    #assert modeldata.MarketingEventsInfo.IsBuyHeroComplete == False
    
    #env.acc.sex = ESex.FEMALE
    #requests = [ ( Buy_hero, BuyHeroRequest( modeldata, { "PersistentId" : [crc32("bard")] }, False ) ) ]
    #changeList = env.execActions( requests )

    #assert len( modeldata.HeroesKeeper ) == heroesCount + 1
    #assert len( modeldata.Heroes ) == heroesCount + 1
    #assert silver == modeldata.Resources.Silver
    #Gold = int(env.I.Config.getConfig( env.acc.userlocale ).BUY_HERO_PRICE)
    #assert gold - modeldata.Resources.Gold == Gold 
    #assert modeldata.MarketingEventsInfo.IsBuyHeroComplete == True
     