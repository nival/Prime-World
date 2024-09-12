# coding=utf-8
import sys
sys.path.append('../')
sys.path.append('../..')
from logic.upgrade_hero import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class upgrade_hero_test:

    def upgrade_hero_test_with_no_uses( self, env ):
        modeldata = env.acc.model
        heroCrc = crc32("thundergod")
        hero, heroId = modeldata.findHeroByCrc32(heroCrc)
        assert hero

        requests = [(Upgrade_hero, UpgradeHeroRequest(modeldata, {"PersistentId": ["" + str(heroCrc) + ""]}, False))]
        changeList = env.execActions(requests)
        assert changeList[0]['ok'] == 0

    def upgrade_hero_test_with_uses(self, env):
        modeldata = env.acc.model
        SD = env.acc.SD
        heroCrc = crc32("thundergod")
        hero, heroId = modeldata.findHeroByCrc32(heroCrc)
        assert hero

        targetTab = 2

        talentsSnapShot = []
        for i in xrange(1, 37):
            talentsSnapShot.append(modeldata.getTalentByID(hero.TalentSets[targetTab].Talents.get(i)))

        #add_uses
        modeldata.MarketingEventsInfo.UpgradeHeroTalentsInfo.UsesLeft = 1

        requests = [(Upgrade_hero, UpgradeHeroRequest(modeldata, {"PersistentId": ["" + str(heroCrc) + ""]}, False))]
        changeList = env.execActions(requests)
        assert changeList[0]['ok'] == 1
        assert hero.IsUpgradeHeroEvent
        assert modeldata.MarketingEventsInfo.UpgradeHeroTalentsInfo.UsesLeft == 0

        for i in xrange(1, 37): # проходимся по всем талам в талантсете и если там в каком то слоте остался предыдущий талант - ассертим
            oldTal = talentsSnapShot[i - 1]
            if oldTal:
                oldId = oldTal.getID()
                staticOld = SD.getStaticTalent(oldTal)
            else:
                oldId = -1
                staticOld = {'persistentId': 'None'}

            crrTal = modeldata.getTalentByID(hero.TalentSets[targetTab].Talents.get(i))
            crrId = crrTal.getID()
            staticCrr = SD.getStaticTalent(crrTal)

            assert staticCrr
            debug("No: {} oldId: {}, crrId: {}, nameOld: {}, nameCrr: {}".format(i, oldId, crrId, staticOld['persistentId'], staticCrr['persistentId']))
            assert oldId == crrId if staticCrr['rarity'] == "Class" else oldId != crrId



    def upgrade_hero_test_with_uses_and_hero_is_upgraded(self, env):
        modeldata = env.acc.model
        heroCrc = crc32("thundergod")
        hero, heroId = modeldata.findHeroByCrc32(heroCrc)
        assert hero

        # add_uses
        modeldata.MarketingEventsInfo.UpgradeHeroTalentsInfo.UsesLeft = 1

        # set isUpgradeHeroTalents
        hero.IsUpgradeHeroEvent = True

        requests = [(Upgrade_hero, UpgradeHeroRequest(modeldata, {"PersistentId": ["" + str(heroCrc) + ""]}, False))]
        changeList = env.execActions(requests)
        assert changeList[0]['ok'] == 0
