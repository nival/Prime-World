from base.helpers import *

class MoveStatField:
    def convertModelData( self, env, acc, md, dict ):
        for heroId in md.HeroesKeeper:
            hero = md.getHeroByID( heroId )
            if hero:
                try:
                    hero.Stats.StatPoints = int(dict["ModelData"]["HeroesKeeper"]["Keeper"][str(hero.getID())]["Hero"]["StatPoints"])
                except KeyError:
                    pass


        return md, acc.db