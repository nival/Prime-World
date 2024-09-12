class ResetStatPoints:
    def convertModelData( self, env, acc, md, dict ): 
        for heroId in md.HeroesKeeper:
            hero = md.getHeroByID( heroId )
            if hero and hero.Hired:
                hero.Stats.Strength = 0
                hero.Stats.Intellect = 0
                hero.Stats.Agility = 0
                hero.Stats.Cunning = 0
                hero.Stats.Fortitude = 0
                hero.Stats.Will = 0
                hero.Stats.Health = 0
                hero.Stats.Mana = 0
                statpoints = 0
                for lvl in xrange( 0, acc.SD.getHeroExpLevel( hero.Experience ) + 1 ):
                    statpoints += acc.SD.getHeroStatPoints( lvl )
                hero.Stats.StatPoints = statpoints
                for tsId in hero.TalentSets.keys():
                    hero.CalcForce( md, None, acc, tsId )
            
        return md, acc.db