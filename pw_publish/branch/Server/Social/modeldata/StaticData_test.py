# -*- coding: utf-8 -*-
#!/usr/bin/env python
import json
import os, sys
sys.path.append('../')
sys.path.append('../base')
sys.path.append('../cfg')
from StaticData import StaticData
from config.MultiConfig import MultiConfig
from config.ConfigData import ConfigData
import unittest
from binascii import crc32

class MainTest(unittest.TestCase):

    def testMain( self ):
        options_xdb_path = "../xdb/ExportedSocialData.xml"

        config = MultiConfig()

        staticData = StaticData( options_xdb_path, config.getMainConfig(), False )
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

    def testOverrideInt( self ):
        config = ConfigData()
        config.init( None )
        config.create()
        config.overrideData( "/Social.ROOT::GoldTalentsUnsoulboundPrice.Item.[3].Silver", "1")

        options_xdb_path = "../xdb/ExportedSocialData.xml"
        staticData = StaticData( options_xdb_path, config, True )
        oldVal = staticData.data["GoldTalentsUnsoulboundPrice"]["Item"][3]["Silver"]
        config.applyOverrides( staticData )
        assert staticData.data["GoldTalentsUnsoulboundPrice"]["Item"][3]["Silver"] == 1

    def testOverrideArray( self ):
        config = ConfigData()
        config.init( None )
        config.create()

        config.overrideData( "/Social.ROOT::TalentLevelToPointsAndRarity.Item.[5].levelToPoints", "[]" )

        options_xdb_path = "../xdb/ExportedSocialData.xml"
        staticData = StaticData( options_xdb_path, config, False )
        assert len(staticData.data["TalentLevelToPointsAndRarity"]["Item"][5]["levelToPoints"]) > 0
        config.applyOverrides( staticData )
        assert len(staticData.data["TalentLevelToPointsAndRarity"]["Item"][5]["levelToPoints"]) == 0

    def testOverridePrice(self):
        config = ConfigData()
        config.init(None)
        config.create()

        config.overrideData("/Items/ClanItems/CS201_LB_Red123::price.CWPoints_Player", "700")

        options_xdb_path = "../xdb/ExportedSocialData.xml"
        staticData = StaticData(options_xdb_path, config, False)
        assert int(staticData.data["GuildShopItems"][crc32("CS201")]["price"]["CWPoints_Player"]) == 600
        config.applyOverrides(staticData)
        assert int(staticData.data["GuildShopItems"][crc32("CS201")]["price"]["CWPoints_Player"]) == 700

    def testPrices(self):
        config = ConfigData()
        config.init(None)
        config.create()

        options_xdb_path = "../xdb/ExportedSocialData.xml"
        staticData = StaticData(options_xdb_path, config, True)

        p1 = StaticData.emptyPrice()

        assert StaticData.isValidPrice(p1) == False

        p2 = StaticData.copyPrice(p1)
        assert StaticData.isValidPrice(p2) == False

        p2.Gold += 10
        p2.Currencies['currency1'] = 12
        assert StaticData.isValidPrice(p2) == True

        StaticData.getAddPrice(p1, p2)
        assert StaticData.isValidPrice(p1) == True

        StaticData.getSubtractPrice(p1, p2)
        assert StaticData.isValidPrice(p1) == False

        StaticData.getAddPrice(p1, p2)
        StaticData.applyCoeffToPrice(p1, 0.6)

        v = StaticData.getFirstValueSafe(p1)
        assert v != 0
        assert p1.Gold == 6.0
        assert p1.Currencies['currency1'] == 12*0.6

        p3 = StaticData.copyPriceFloat(p1)
        StaticData.getAddValuePrice('currency1', p3, -v)
        p3 = StaticData.copyPrice(p3)
        assert p3.Currencies['currency1'] == 0

        p3 = StaticData.copyPriceFloat(p2)
        p1 = StaticData.copyPriceFloat(p2)
        StaticData.applyCoeffToPrice(p3, 0.5)
        StaticData.getDividePrice(p1, p3)
        assert p1.Gold == 2.0
        assert p1.Currencies['currency1'] == 2.0

        StaticData.overrideNonZeroValuesInPrice(p2, 7)
        assert p2.Gold == 7
        assert p2.Currencies['currency1'] == 7

        StaticData.getSubtractPrice(p2, p2)
        assert StaticData.isValidPrice(p2) == False

    def testOverrideRef(self):
        config = ConfigData()
        config.init(None)
        config.create()
        config.overrideData(
            "/Items/Talents/Archeress.TALENTSET::levels.Item.[4].talents.Item.[0].talent",
            "/Items/Talents/Level5/G263_Int_LifeReg.TALENT")

        options_xdb_path = "../xdb/ExportedSocialData.xml"
        staticData = StaticData(options_xdb_path, config, False)

        ts = staticData.getObjectByDbid("/Items/Talents/Archeress.TALENTSET")
        prevTalent = ts["levels"]["Item"][4]["talents"]["Item"][0]["talent"]
        assert prevTalent["persistentId"] == "Archeress_A1_SUP"
        config.applyOverrides(staticData)
        newTalent = ts["levels"]["Item"][4]["talents"]["Item"][0]["talent"]
        assert newTalent["persistentId"] == "G263"

    def testOverrideNone(self):
        config = ConfigData()
        config.init(None)
        config.create()
        config.overrideData(
            "/Items/Talents/Archeress.TALENTSET::levels.Item.[4].talents.Item.[0].talent",
            None)

        options_xdb_path = "../xdb/ExportedSocialData.xml"
        staticData = StaticData(options_xdb_path, config, False)

        ts = staticData.getObjectByDbid("/Items/Talents/Archeress.TALENTSET")
        prevTalent = ts["levels"]["Item"][4]["talents"]["Item"][0]["talent"]
        assert prevTalent["persistentId"] == "Archeress_A1_SUP"
        config.applyOverrides(staticData)
        newTalent = ts["levels"]["Item"][4]["talents"]["Item"][0]["talent"]
        assert newTalent is None

    def testOverridePricesMapsInTralentQuest(self):
        config = ConfigData()
        config.init(None)
        config.create()

        # overrides for server
        config.overrideData("/Social/Quests/TalentQuests/_Settings::PricesMap.excellent.Shard", "15")
        config.overrideData("/Social/Quests/TalentQuests/_Settings::OverridenPricesMap.G217.Shard", "250")

        options_xdb_path = "../xdb/ExportedSocialData.xml"
        staticData = StaticData(options_xdb_path, config, False)

        # print 'Before' + json.dumps(staticData.getObjectByDbid('/Social/Quests/TalentQuests/_Settings'), sort_keys=True, indent=2,
        #                  ensure_ascii=False)

        config.applyOverrides(staticData)

        # print 'After' + json.dumps(staticData.getObjectByDbid('/Social/Quests/TalentQuests/_Settings'), sort_keys=True, indent=2,
        #                  ensure_ascii=False)

        assert staticData.data['DynamicQuestForTalents']['PricesMap']['excellent']['Shard'] == "15"
        assert staticData.data['DynamicQuestForTalents']['OverridenPricesMap']['G217']['Shard'] == "250"

    def testRerollShopItem(self):
        config = ConfigData()
        config.init(None)
        config.create()
        config.overrideData("/Items/RerollShop/Group_Orange::rerollTimesToDropProbabilties.Item.[0].newProbability", "300")

        options_xdb_path = "../xdb/ExportedSocialData.xml"
        staticData = StaticData(options_xdb_path, config, False)

        group = staticData.getObjectByDbid("/Items/RerollShop/Group_Orange")
        config.applyOverrides(staticData)
        prop = group["rerollTimesToDropProbabilties"]["Item"][0]["newProbability"]
        assert prop == 300

if __name__ == '__main__':
    unittest.main(argv=sys.argv[:1])
