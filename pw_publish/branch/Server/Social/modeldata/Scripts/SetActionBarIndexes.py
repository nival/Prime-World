class SetActionBarIndexes:
    def convertModelData( self, env, acc, md, dict ):        
        for heroId in md.HeroesKeeper:
            actionBarIndexCount = -1
            hero = md.getHeroByID( heroId )
            for pos in hero.TalentSet:
                talent = hero.TalentSet.get( pos )
                if talent:
                    #talent = md.ItemsKeeper.get( talentId )
                    StaticTalent = acc.SD.getStaticTalent( talent )
                    if StaticTalent:
                        if StaticTalent['type'] == "Active":
                            if actionBarIndexCount < 9:
                                actionBarIndexCount += 1
                                actionBarIndex = actionBarIndexCount
                            else:
                                actionBarIndex = -1
                        else:
                            actionBarIndex = -1
                        talent.ActionBarIdx = actionBarIndex
              
        return md, acc.db