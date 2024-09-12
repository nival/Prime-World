# -*- coding: utf-8 -*-

from base.helpers import *
from binascii import crc32   # zlib version is not cross-platform
from enums.GoldHouseActionState import *
from MM import ESex

# см PF-84504
class ShowCorrectGoldHouseActionState:
  def convertModelData( self, env, acc, md, dict ):
    # 1. Выдадим домик тем, кто уже купил героя за 9 золотых
    if md.MarketingEventsInfo.IsBuyHeroComplete:
      construction_uid = md.addNewConstruction()
      construction = md.getConstructionByID( construction_uid )
      construction.PersistentId = crc32("GoldProductionHouse")
      md.Pocket.add( construction )
      md.MarketingEventsInfo.GoldHouseActionState = GoldHouseActionState.ShowPlaceHouseEvent
      return md, acc.db

    # 2. Посмотрим, купил ли пользователь всех героев с акцией
    config = env.I.Config.getConfig( acc.userlocale )
    if not md.hasAllHeroesForBuyAction(acc, acc.SD, config):
      md.MarketingEventsInfo.GoldHouseActionState = GoldHouseActionState.ShowBuyHeroEvent
      return md, acc.db

    # 3. Все герои уже куплены и без акции, пусть покупает сам и за золото
    md.MarketingEventsInfo.GoldHouseActionState = GoldHouseActionState.ShowBuyHouseEvent
    return md, acc.db