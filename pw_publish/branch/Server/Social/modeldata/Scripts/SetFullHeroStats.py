# -*- coding: utf-8 -*-

from base.helpers import *

class SetFullHeroStats:
    def convertModelData( self, env, acc, md, dict ):
        for heroId in md.Heroes:
            hero = md.getHeroByID(heroId)
            #hero.updateFullStats(md, acc.SD)
        return md, acc.db