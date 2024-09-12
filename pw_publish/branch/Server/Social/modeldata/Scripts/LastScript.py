import time

class LastScript:
    def convertModelData( self, env, acc, md, dict ):
        for heroId in md.HeroesKeeper:
            hero = md.getHeroByID( heroId )
            if not hasattr( hero, "lastEnergyUpdateTime_" ):
                hero.lastEnergyUpdateTime_ = time.time()
        return md, acc.db