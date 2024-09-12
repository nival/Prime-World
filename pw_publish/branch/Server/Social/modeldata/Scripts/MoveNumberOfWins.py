from base.helpers import *

class MoveNumberOfWins:
   def convertModelData( self, env, acc, md, dict ):
        try:
            md.LordInfo.GuardInfo.NumberOfWins = int(dict["ModelData"]["LordInfo"]["LordInfo"]["NumberOfWins"])
        except KeyError:
            pass

        count = 0
        for heroId in md.HeroesKeeper:
            hero = md.getHeroByID( heroId )
            if hero.Hired:
                count += 1

        if count >= 5 and md.LordInfo.GuardInfo.NumberOfWins < 10:
            md.LordInfo.GuardInfo.NumberOfWins = 10

        return md, acc.db