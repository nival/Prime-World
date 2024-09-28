import unittest
import sys, os, time, json, logging
from binascii import crc32

os.chdir('..')
sys.path.append( os.path.abspath('.') )

sys.path.append('base')
sys.path.append('cfg')

from modeldata.ModelData import ModelData
import jsonserialize
from helpers import * 

class JSONTest(unittest.TestCase):
    
    def testJson( self ):
        changeWriter = None
        md = ModelData( )
        md.init( changeWriter )
        md.initAllTimesCounters()
        id = md.addNewHero()
        hero = md.getHeroByID(id)
        md.Heroes.add( hero )
        tsId = md.addNewTalentSet()
        hero.TalentSets[0] = md.getTalentSetByID(tsId)
        hero.Experience = 10
        del hero.Experience
        hero.Experience = 6
        talentId = md.addNewTalent()
        talentId2 = md.addNewTalent()
        talent = md.getTalentByID(talentId2)
        hero.TalentSets[0].Talents[1] = talentId
        hero.TalentSets[0].Talents[2] = talentId2
        hero.TalentSets[0].Talents.swap(1, 2)

        data = md.save()
        
        #print "testJson data:", data
        
        result = ModelData()
        result.load(data)
        result.init( changeWriter )
        
        data2 = result.save()
        #print "testJson dat2:", data2
        assert data == data2

    def testJson2( self ):
        changeWriter = None
        md = ModelData( )
        md.init( changeWriter )
        md.initAllTimesCounters()
        id = md.addNewHero()
        hero = md.getHeroByID(id)
        hero.Experience = 10
        del hero.Experience
        hero.Experience = 6
        tsId = md.addNewTalentSet()
        hero.TalentSets[0] = md.getTalentSetByID(tsId)
        talentId = md.addNewTalent()
        talentId2 = md.addNewTalent()
        talent = md.getTalentByID(talentId2)
        hero.TalentSets[0].Talents[1] = talentId
        hero.TalentSets[0].Talents[2] = talentId2
        hero.TalentSets[0].Talents.swap( 1, 2 )

        data = md.save()
        result = ModelData()
        result.load(data)
        result.init( changeWriter )

        data2 = result.save()
        
        id2 = result.addNewHero()
        hero2 = result.getHeroByID(id2)

        path2 = "HeroesKeeper/%d" % id2
        h2 = pathFind( result, path2 )
        assert h2

        path3 = "HeroesKeeper/%d" % 1
        h3 = pathFind( result, path3 )
        assert h3
        
        newTalentId = result.addNewTalent()
        h3.TalentSets[0].Talents.add( 3, newTalentId )
        assert h3.TalentSets[0].Talents
        assert newTalentId in result.ItemsKeeper

    def testSaveTavern( self ):
        changeWriter = None
        md = ModelData( )
        md.init( changeWriter )
        md.initAllTimesCounters()
        bath_uid = md.addNewConstruction()
        bath = md.getConstructionByID( bath_uid )
        bath.PersistentId = crc32("Tavern")
        md.Buildings.add( bath )

        data = md.save()
        
        #print "testJson data:", data
        
        result = ModelData()
        result.load(data)
        result.init( changeWriter )
        
        data2 = result.save()
        #print "testJson data2:", data2
        assert data == data2

    def testSaveTavern2( self ):
        changeWriter = None
        md = ModelData( )
        md.init( changeWriter )
        md.initAllTimesCounters()
        talent_uid = md.addNewTalent()
        talent = md.getTalentByID( talent_uid )
        gbi, gbi_id = md.newGuildBankInfo()
        gbi.GuildAuid = 1
        talent.GuildBankInfo = gbi_id
        md.UserInventory.add( talent )
        assert talent.GuildBankInfo.GuildAuid == 1
        data = md.save()
        
        #print "testJson data1:", data
        
        result = ModelData()
        result.load(data)
        result.init( changeWriter )
        
        data2 = result.save()
        #print "testJson data2:", data2
        assert data == data2
        tal2 = result.getTalentByID( talent_uid )
        assert tal2.GuildBankInfo.GuildAuid == 1

unittest.main()
