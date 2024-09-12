# -*- coding: utf-8 -*-
#!/usr/bin/env python

import os, sys
sys.path.append('../')
sys.path.append('../cfg')
from MultiStaticData import MultiStaticData
from config.MultiConfig import MultiConfig
from config.ConfigData import ConfigData
import unittest

class MainTest(unittest.TestCase):

    def testMain( self ):
        options_xdb_path = "../xdb/ExportedSocialData.xml"

        config = MultiConfig()

        multiStaticData = MultiStaticData( options_xdb_path, config.getMainConfig() )
        assert len(multiStaticData.staticDatas) > 0
        staticData = multiStaticData.getMainSD()
        assert (isinstance(staticData.data['LevelToExperienceTable']['Levels']['Item'], (list)))
        assert (isinstance(staticData.data['LevelToFameTable']['Levels']['Item'], (list)))
        assert (isinstance(staticData.data['StatpointsToLevelTable']['StatPoints']['Item'], (list)))
        assert (len(staticData.data['LevelToExperienceTable']['Levels']['Item']) > 1)
        assert (len(staticData.data['LevelToFameTable']['Levels']['Item']) > 1)
        assert (len(staticData.data['StatpointsToLevelTable']['StatPoints']['Item']) > 1)
        fameLevel = staticData.getFameLevel( 1000 )
        assert( fameLevel > 1 )
        expLevel = staticData.getHeroExpLevel( 1000 )
        assert( expLevel > 0 )
        statPnts = staticData.getHeroStatPoints( 3 )
        assert( statPnts >= 1 )
        staticConstruction = staticData.getStaticConstructionByPersistentId( 706736175 )
        if staticConstruction:
            assert( staticConstruction['petItem']['persistentId'] == "Pet_Cat" )
        else:
            assert( False )
        assert (isinstance(staticData.getObjectByDbid("/Heroes/Mage/_.HROB"), (dict)))


    def testOverrideIntInENLocale( self ):
        config = ConfigData()
        config.init( None )
        config.create()
        config.overrideData( "/Social.ROOT::GoldTalentsUnsoulboundPrice.Item.[3].Silver", "1")

        options_xdb_path = "../xdb/ExportedSocialData.xml"
        multiStaticData = MultiStaticData( options_xdb_path, config, applyOverrides=False)
        staticData = multiStaticData.getMainSD()
        staticDataEn = multiStaticData.getSD("EN")
        oldVal = staticData.data["GoldTalentsUnsoulboundPrice"]["Item"][3]["Silver"]
        config.applyOverrides( staticDataEn )
        config.fillStaticDataDependendValues( staticDataEn )
        assert staticData.data["GoldTalentsUnsoulboundPrice"]["Item"][3]["Silver"] == oldVal
        assert staticDataEn.data["GoldTalentsUnsoulboundPrice"]["Item"][3]["Silver"] == 1

    def testOverrideArrayFRLocale( self ):
        config = ConfigData()
        config.init( None )
        config.create()

        config.overrideData( "/Social.ROOT::TalentLevelToPointsAndRarity.Item.[5].levelToPoints", "[]" )

        options_xdb_path = "../xdb/ExportedSocialData.xml"
        multiStaticData = MultiStaticData( options_xdb_path, config, applyOverrides=False)
        staticData = multiStaticData.getMainSD()
        staticDataFr = multiStaticData.getSD("FR")
        assert len(staticData.data["TalentLevelToPointsAndRarity"]["Item"][5]["levelToPoints"]) > 0
        assert len(staticDataFr.data["TalentLevelToPointsAndRarity"]["Item"][5]["levelToPoints"]) > 0
        config.applyOverrides( staticDataFr )
        config.fillStaticDataDependendValues( staticDataFr )
        assert len(staticData.data["TalentLevelToPointsAndRarity"]["Item"][5]["levelToPoints"]) > 0
        assert len(staticDataFr.data["TalentLevelToPointsAndRarity"]["Item"][5]["levelToPoints"]) == 0

    def testOverrideArrayMainSD( self ):
        config = ConfigData()
        config.init( None )
        config.create()

        config.overrideData( "/Social.ROOT::TalentLevelToPointsAndRarity.Item.[5].levelToPoints", "[]" )

        options_xdb_path = "../xdb/ExportedSocialData.xml"
        multiStaticData = MultiStaticData( options_xdb_path, config, applyOverrides=False)
        staticData = multiStaticData.getMainSD()
        staticDataFr = multiStaticData.getSD("FR")
        assert len(staticData.data["TalentLevelToPointsAndRarity"]["Item"][5]["levelToPoints"]) > 0
        assert len(staticDataFr.data["TalentLevelToPointsAndRarity"]["Item"][5]["levelToPoints"]) > 0
        config.applyOverrides( staticData )
        config.fillStaticDataDependendValues( staticData )
        assert len(staticDataFr.data["TalentLevelToPointsAndRarity"]["Item"][5]["levelToPoints"]) > 0
        assert len(staticData.data["TalentLevelToPointsAndRarity"]["Item"][5]["levelToPoints"]) == 0

unittest.main()
