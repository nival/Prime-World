# -*- coding: utf-8 -*-

from base.helpers import *

class MoveActionBarIndexesToTS:

    def convertModelData(self, env, acc, md, dict):
        for heroId in md.HeroesKeeper:
            hero = md.getHeroByID(heroId)
            for tsId, talentSet in hero.TalentSets.iteritems():
                if len(talentSet.ActionBar):
                    continue
                for i in xrange(0, 10):
                    talentSet.ActionBar[i] = -1
                for position in talentSet.Talents.keys():
                    talent = md.getTalentByID(talentSet.Talents[position])
                    if talent is None:
                        talentSet.Talents.remove(position)
                        continue
                    if "ActionBarIdx" in dict["ModelData"]["ItemsKeeper"]["Keeper"][str(talent.id)]["Talent"]:
                        actionBatIdx = dict["ModelData"]["ItemsKeeper"]["Keeper"][str(talent.id)]["Talent"]["ActionBarIdx"]
                        if actionBatIdx != -1:
                            talentSet.ActionBar[actionBatIdx] = talent.getID()
        return md, acc.db