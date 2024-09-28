# -*- coding: utf-8 -*-

from base.helpers import *

class GetLordLevelupBonus:
    def convertModelData( self, env, acc, md, dict ): 
        curLvl = acc.SD.getFameLevel( md.LordInfo.Fame )
        # Выдадим награды
        for lvl in xrange( 1, curLvl+1 ):
            price = acc.SD.getResourcesForLevelUp( lvl )
            if price:
                md.sell( price, acc, False )
        return md, acc.db
