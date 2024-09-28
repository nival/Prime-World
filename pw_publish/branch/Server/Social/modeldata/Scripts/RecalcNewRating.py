from base.helpers import *

class RecalcNewRating:
    def convertModelData( self, env, acc, md, dict ): 
        for heroId in md.HeroesKeeper:
            hero = md.getHeroByID( heroId )
            if hero.Hired:
                hero.correctRating(md, env.I.Config.getConfig(acc.userlocale), env.I, acc)

        return md, acc.db
