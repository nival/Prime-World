# -*- coding: utf-8 -*-

from base.helpers import *

#для PF-87379
class ResetBuyHeroEventNewState:
  def convertModelData( self, env, acc, md, dict ):

    dbId = "/UI/Content/MarketingEvents/BuyHero"

    #проверим, есть ли у нас акция покупки героя в просмотренных
    if dbId not in md.MarketingEventsInfo.ViewedEvents:
      return md,acc.db

    # убираем из MarketingEventsInfo.ViewedEvents эвент про героя если он не был выполнен
    if not md.MarketingEventsInfo.IsBuyHeroComplete and not md.hasAllHeroesForBuyAction(acc, acc.SD, env.I.Config.getConfig( acc.userlocale )):
      md.MarketingEventsInfo.ViewedEvents.remove(dbId)
      return md, acc.db

    return md, acc.db