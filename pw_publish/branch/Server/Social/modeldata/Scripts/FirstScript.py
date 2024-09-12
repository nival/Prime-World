import time

class FirstScript:
    def convertModelData( self, env, acc, md, dict ):
        md.Heroes.init( md.HeroesKeeper, "Heroes", md )
        for heroId in md.HeroesKeeper:
            hero = md.getHeroByID( heroId )
            if not hasattr( hero, "lastEnergyUpdateTime_" ) or not hero.lastEnergyUpdateTime_:
                hero.lastEnergyUpdateTime_ = time.time()
                if heroId not in md.Heroes.dictionary:
                    md.Heroes.add( hero )    
        for constructionId in md.ConstructionsKeeper:
            construction = md.getConstructionByID( constructionId )
            if not hasattr( construction, "EndProductionTime" ) or not construction.EndProductionTime:
                construction.EndProductionTime = 0
            if construction.PersistentId == 100500 or construction.PersistentId == 0:
                construction.Level = 1
                #construction.Type = "Bath"
                construction.PersistentId = 1465591941
                construction.Position.X = 14
                construction.Position.Y = 36
                construction.Position.Pitch = 0
            if construction.id == None:
                construction.id = constructionId
                construction.path = "ConstructionsKeeper/" + str(constructionId)
        for talentId in md.ItemsKeeper:
            talent = md.getTalentByID( talentId )
            if talent and talent.ActionBarIdx == -2:
                talent.ActionBarIdx = -1
        return md, acc.db