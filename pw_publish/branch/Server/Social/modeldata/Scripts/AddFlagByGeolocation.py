# -*- coding: utf-8 -*-

from base.helpers import *
from enums.FlagType import *

class AddFlagByGeolocation:
  def convertModelData( self, env, acc, md, dict ):
    if acc.country_code:
      md.setGeolocationalFlag(acc.SD, acc.country_code)
      return md, acc.db

    # Ничего хорошего не нашли, ставим флаг по умолчанию
    md.FlagInfo.PersistentId = acc.SD.getDefaultFlagName()
    md.FlagInfo.FlagType = FlagType.Default
    return md, acc.db