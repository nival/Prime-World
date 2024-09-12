from base.helpers import *

class GiveBonusTalents:
    def convertModelData( self, env, acc, md, dict ): 
        for heroId in md.HeroesKeeper:
            hero = md.getHeroByID( heroId )
            if hero.Hired:
                staticHero = acc.SD.getStaticHero( hero )
                earnedLvl = acc.SD.getHeroExpLevel( hero.Experience )
                if staticHero:
                    for curLvl in xrange( 1, earnedLvl+1 ):
                        md.giveTalentsForHeroLevelUp( hero, staticHero, curLvl, acc, env.I )

        return md, acc.db