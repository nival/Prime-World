from base.helpers import *

class SetNewHeroRating:
    def convertModelData( self, env, acc, md, dict ): 
        topRating = 0.0
        for heroId in md.HeroesKeeper:
            hero = md.getHeroByID( heroId )
            if hero.Hired:
                if hero.Rating > topRating:
                    topRating = hero.Rating

        if topRating < env.I.Config.getConfig( acc.userlocale ).HERO_START_RATING:
            return md, acc.db

        for heroId in md.HeroesKeeper:
            hero = md.getHeroByID( heroId )
            if hero.Hired:
                newRating = env.I.Config.getConfig( acc.userlocale ).HERO_START_RATING + env.I.Config.getConfig( acc.userlocale ).HERO_COEFF_RATING * ( topRating - env.I.Config.getConfig( acc.userlocale ).HERO_START_RATING )

                if newRating > env.I.Config.getConfig( acc.userlocale ).HERO_CUP_RATING:
                    newRating = env.I.Config.getConfig( acc.userlocale ).HERO_CUP_RATING
                if hero.Rating < newRating:
                    hero.Rating = newRating

        return md, acc.db