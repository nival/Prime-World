from base.helpers import *

import pickle


class SetCorrectActionBarIdx:
    def convertModelData( self, env, acc, md, dict ):                
        for talentId in md.UserInventory.keys():
            talent = md.getTalentByID( talentId )
            talent.ActionBarIdx = -1
        for heroId in md.HeroesKeeper:
            hero = md.getHeroByID( heroId )
            actionBarIndexses = []
            for talentId in hero.TalentSet.keys():
                talent = hero.TalentSet.get(talentId)
                if talent:
                    if talent.ActionBarIdx == -1:
                        pass
                    elif not talent.ActionBarIdx in actionBarIndexses:
                        actionBarIndexses.append( talent.ActionBarIdx )
                    else:
                        hero.setActionBarIndexes
                        break
                
        return md, acc.db