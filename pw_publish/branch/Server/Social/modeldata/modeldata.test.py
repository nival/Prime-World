# -*- coding: utf-8 -*-
#!/usr/bin/env python

import sys, os, time, logging

sys.path.append('..')
sys.path.append('../base')
sys.path.append('../cfg')
from modeldata.ModelData import *
import jsonserialize
import unittest

from helpers import * 

class MainTest(unittest.TestCase):
    def testMain( self ):
        changeWriter = None # DummyRequestWriter()
        changeWriterOff = None # DummyRequestWriter( "NONE: TURNED OFF " )

        md = ModelData( )
        md.init( changeWriter )
        md.initAllTimesCounters()
        id = md.addNewHero()
        hero = md.getHeroByID(id)
        hero.Experience = 10

        #---------------------------------------------------
        # временно отключаем генерацию model change 
        # (например, для добавления служебного поля, или для добавления целого большого объекта, который обновим руками, через сериализацию)
        md.write( changeWriterOff )

        del hero.Experience
        hero.Experience = 6
        tsId = md.addNewTalentSet()
        hero.TalentSets[0] = md.getTalentSetByID(tsId)

        # включаем обратно генерацию model change 
        md.write( changeWriter )

        #---------------------------------------------------

        talentId = md.addNewTalent()
        talentId2 = md.addNewTalent()
        talent = md.getTalentByID(talentId2)
        hero.TalentSets[0].Talents.add( 1, talentId2 )
        hero.TalentSets[0].Talents.add( 2, talentId )

        hero.TalentSets[0].Talents.swap( 1, 2 )

        #---------------------------------------------------
        # поиск по абсолютному пути в MD:
        path = "HeroesKeeper/%d" % id
        h = pathFind( md, path )

        data = md.save()
        #print "raw:", data
    
        result = ModelData()
        result.load( data )
        result.init( changeWriter )
        
        id2 = result.addNewHero()
        hero2 = result.getHeroByID(id2)

        path2 = "HeroesKeeper/%d" % id2
        h2 = pathFind( result, path2 )
 
        path3 = "HeroesKeeper/%d" % 1
        h3 = pathFind( result, path3 )
        newTalentId = result.addNewTalent()
        h3.TalentSets[0].Talents.add( 3, newTalentId )

        data2 = result.save()
        #print data2

        hero.TalentSets[0].Talents.remove( talentId2 )
        hero.TalentSets[0].Talents.remove( talentId )

unittest.main()
