class RestoreHeroesEnergyAndExperience:
    def convertModelData( self, env, acc, md, dict ): 
        for heroId in md.HeroesKeeper:
            hero = md.getHeroByID( heroId )
            hero.Experience = 0
            
        return md, acc.db