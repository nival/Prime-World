# coding=utf-8
from base.helpers import *
import pickle


class FixZeroActionBarIdx:
    def convertModelData( self, env, acc, md, dict ):                
        for talentId in md.UserInventory.keys():
            talent = md.getTalentByID( talentId )
            talent.ActionBarIdx = -1

        """
        нам более не нужно править индексы в этом скрипте, т.к. после введения альтернативных талент-сетов
        все трансформации и правки индексов экшин бара происходят в скриптах 
        73 0 0 AddNewTalentSets.py
        107 0 0 MoveActionBarIndexesToTS.py
        """

        """
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
                        talent.ActionBarIdx = -1
                        break
        """
        return md, acc.db
