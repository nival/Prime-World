from base.helpers import *

class SetLordRating:
   def convertModelData( self, env, acc, md, dict ):
        ratings = []
        lordRating = acc.SD.START_HERO_RATING['rating']
        for heroId in md.HeroesKeeper:
            hero = md.getHeroByID( heroId )
            if len( ratings ) == 3:
                if ratings[2] < hero.Rating:
                    ratings[2] = hero.Rating
            else:
                ratings.append( hero.Rating )

            ratings.sort()
            ratings.reverse()

        if ratings:
            lordRating = 0.0
            for val in ratings:
                lordRating += val
            lordRating /= len(ratings)

        md.LordInfo.Ratings.LordRating = lordRating
        return md, acc.db
