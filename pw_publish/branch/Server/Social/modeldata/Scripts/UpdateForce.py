from base.helpers import *

class UpdateForce:
    def convertModelData( self, env, acc, md, dict ): 
        for heroId in md.HeroesKeeper:
            hero = md.getHeroByID( heroId )
            for tsId in hero.TalentSets.keys():
                hero.CalcForce( md, None, acc, tsId )
        return md, acc.db