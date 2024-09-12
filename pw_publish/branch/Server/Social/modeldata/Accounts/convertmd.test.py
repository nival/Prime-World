# -*- coding: utf-8 -*-
# !/usr/bin/env python

import sys, os, time, logging, gc
from binascii import crc32

sys.path.append('../..')
sys.path.append('..')
sys.path.append('../../base')
sys.path.append('../../cfg')
#from modeldata.ModelData import *
#import jsonserialize
import unittest

from helpers import *
from datamanagerEnv import *
import glob
DEFAULT_LOG_LEVEL = logging.WARNING


def findAllFiles():
    filepath = os.path.dirname(os.path.realpath(__file__))
    path = filepath
    #filelist = ["272081.pwdump"]

    filelist = glob.glob(os.path.join(path,  '*.pwdump'))

    return reversed(sorted(filelist))

def findLastMDVersion():
    filepath = os.path.realpath('../Scripts/version.txt')

    f = open(filepath, "r")
    lines = f.readlines()
    f.close()

    return int(lines[-1].split(' ')[0])


class MainTest(unittest.TestCase):
    def test_Main(self):
        logging.basicConfig(level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s')

        self.env = DataManagerEnv()

        self.lastMDVersion = findLastMDVersion()

        files = findAllFiles()
        for f in files:
            print "Testing", f
            self.env.acc.model = None
            assert self.env.acc.model == None
            self.env.convertModelData(f)
            assert not self.env.acc.model == None
            self.isMDCorrect(self.env.acc, self.env.I.SD)
            #print pretty(self.env.acc.model.generateJsonDict())
            #info(pretty(self.env.acc.model.generateJsonDict()))

    def createMdTalentSet(self, hero, tsId, md):
        talentSet = []

        for talentPos in hero.TalentSets[tsId].Talents:
            talent = md.getTalentByID(hero.TalentSets[tsId].Talents.get(talentPos))
            talentSet.append(talent.PersistentId)
        return talentSet

    def createSdTalentSet(self, staticData, hero):
        talentSet = []
        for i in range(len(hero['defaultTalentsSets']['Item'])):
            dts = staticData.getDefaultTalentSetSD(self.env.acc.getConfig(), hero, i)
            for row in dts['levels']['Item']:
                for pos in row['talents']['Item']:
                    if 'persistentId' in pos['talent'] and pos['talent']['persistentId']:
                        talentSet.append(crc32(pos['talent']['persistentId']))
        return talentSet

    def isMDCorrect(self, acc, SD):
        md = acc.model
        assert md.version.revision == self.lastMDVersion
        assert len(md.HeroesKeeper) == len(md.Heroes)
        is_valid, valid_info = md.checkValidity(acc, SD)
        if not is_valid:
            print "Account not valid: ", valid_info
            md.fixAll(acc, SD)
            print "Validating..."
            is_valid, valid_info = md.checkValidity(acc, SD)
        assert is_valid

        # TODO why 25?! must be 26!
        # assert len(md.HeroesKeeper) == 25
        # assert md.Resources.Silver >= 325000
        # assert md.LordInfo.Fame >= 40500
        assert hasattr(md.LordInfo, "lastFameUpdateTime_")
        assert hasattr(md.LordInfo, "lastDodgesUpdateTime_")

        # male detected
        hiredHeroes = 0
        lockedHeroes = 0
        hiredHeroesList = []
        for heroID in md.Heroes:
            hero = md.getHeroByID(heroID)
            if hero.Hired == True:
                hiredHeroes += 1
                hiredHeroesList.append(hero.PersistentId)
            else:
                lockedHeroes += 1
            # assert hero.Experience == 0
            # assert len(hero.InBuildings) == 0

        # assert hiredHeroes == 3
        # assert lockedHeroes == 22

        # mustBeHiredMale = [-1850465256, 1160508680, 571020430]
        # mustBeHiredFemale = [637171033, 1617033593, -447734811]
        # if acc.sex == 2:
        #  assert len(set(hiredHeroesList).difference(set(mustBeHiredFemale))) == 0
        # else:
        #  assert len(set(hiredHeroesList).difference(set(mustBeHiredMale))) == 0

        for heroId in md.HeroesKeeper:
            mdHero = md.getHeroByID(heroId)
            sdHero = self.env.I.SD.data['Heroes'][mdHero.PersistentId]
            sdTalentSet = self.createSdTalentSet(SD, sdHero)
            for tsId in mdHero.TalentSets.keys():
                mdTalentSet = mdHero.TalentSets[tsId]
                dif = set(mdTalentSet.Talents).difference(set(sdTalentSet))
            # assert len(set(mdTalentSet).difference(set(sdTalentSet))) == 0
        assert acc.db.isRegularMMAllowed == True

        badTalents =[]
        for heroID in md.Heroes:
            mdHero = md.getHeroByID(heroID)
            if not mdHero.Hired:
                continue
            staticHero =SD.getStaticHero(mdHero )
            for tsId in mdHero.TalentSets.keys():
                for talentPos in mdHero.TalentSets[tsId].Talents.keys():
                    talentId = mdHero.TalentSets[tsId].Talents.get(talentPos)
                    talent = md.getTalentByID(talentId)
                    if talent is None:
                        badTalents.append((staticHero["persistentId"], tsId, talentPos, talentId))

        if badTalents:
            print "BAD TALENTS DETECTED!"
            for x in badTalents:
                print "hero {0}, talentsetId {1} slot {2}, talent_id {3}".format(*x)
            print "=" * 10

        assert not badTalents

        badTalentSets = []
        for heroID in md.Heroes:
            mdHero = md.getHeroByID(heroID)
            if not mdHero.Hired:
                continue
            staticHero =SD.getStaticHero(mdHero )
            for tsId in mdHero.TalentSets.keys():
                if tsId >0 and not mdHero.TalentSets[tsId].Talents.keys():
                    badTalentSets.append((staticHero["persistentId"], tsId))

        if badTalentSets:
            print "BAD TALENTSETS DETECTED!"
            for x in badTalentSets:
                print "hero {0}, talentsetId {1}".format(*x)
            print "=" * 10

        assert not badTalentSets


        allInventory = 0
        allHeroesTalent = 0
        for heroID in md.Heroes:
            mdHero = md.getHeroByID(heroID)
            for tsId in mdHero.TalentSets.keys():
                allInventory += len(mdHero.TalentSets[tsId].Talents.keys())
                for talentPos in mdHero.TalentSets[tsId].Talents.keys():
                    talentId = mdHero.TalentSets[tsId].Talents.get(talentPos)
                    talent = md.getTalentByID(talentId)
                    if talent.Owner and talent.Owner.get():
                        allHeroesTalent += 1

        if len(md.UserInventory.keys()) - allInventory != len(md.UserInventory.keys())- allHeroesTalent:
            info("BAD Inventory mdHero.UserInventoryLimit={0} UserInventory-allInventory={1} UserInventory-allHeroesTalent={2}".format(md.UserInventoryLimit,
                                                                                                              len(md.UserInventory.keys()) - allInventory,
                                                                                                              len(md.UserInventory.keys())-allHeroesTalent
                                                                                                              ))



        #assert len(md.UserInventory.keys()) - allInventory == len(md.UserInventory.keys())- allHeroesTalent

        # GiveSomeTalents
        for heroID in md.Heroes:
            hero = md.getHeroByID(heroID)
            staticHero = acc.SD.getStaticHero(hero)
            classTalents = set()
            for ts in staticHero['talents']:
                for row in ts:
                    for tal in row:
                        if tal and tal.rarity == 'Class':
                            classTalents.add(tal.CRC32)
            assert len(classTalents) != 0
            for talentId in md.UserInventory:
                talent = md.getTalentByID(talentId)
                if not talent:
                    continue
                staticTalent = acc.SD.getStaticTalent(talent)
                if staticTalent['rarity'] != 'Class':
                    continue
                classTalents.discard(talent.PersistentId)
            assert len(classTalents) == 0

        # RemoveDuplicatedClassTalents
        classTalents = set()
        for talentId in md.UserInventory:
            talent = md.getTalentByID(talentId)
            if not talent:
                continue
            staticTalent = acc.SD.getStaticTalent(talent)
            if staticTalent['rarity'] != 'Class':
                continue
            assert talent.PersistentId not in classTalents
            classTalents.add(talent.PersistentId)

        # PF-107506 (проверяем, что удалились скрижали)
        G662Id = crc32('G662')
        G662Count = sum(1 for _, t in md.UserInventory.iteritems() if t.PersistentId == G662Id)
        assert G662Count == 0

        # https://devjira.nivalnetwork.com/browse/PF-107368 (проверяем, что удалили кастомные валюты)
        assert 'CC_WC18_Ball' not in md.Resources.Currencies
        assert 'CC_WC18_JP' not in md.Resources.Currencies

#logging.basicConfig(filename='convertmd-test.log', level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s')
gc.disable()
unittest.main()
