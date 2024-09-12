# -*- coding: utf-8 -*-
# (C) Movsesyan Grigory 2011, Nival

from base.helpers import *
import math

# realpath = os.path.dirname(os.path.realpath(__file__))
# sys.path.append(realpath + '/../')
import xdbload
from binascii import crc32
from enums import *
from logic import return_friend
#from modeldata.ModelData import *
from MM import ESex
import time
from modeldata.SharedTypes.ResourceTable import ResourceTable
import collects


class StaticData(object):
    @staticmethod
    def roundFloatToInt(number):
        return int(math.floor(number + 1e-5))

    @staticmethod
    def roundGold(number):
        return int(math.ceil(float(number)))

    def __init__(self, path, config, applyOverrides):
        info("loading StaticData (%s).." % path)
        self.data, self.dbid = xdbload.getStaticData(path)

        if applyOverrides:
            try:
                config.applyOverrides(self)
            except:
                self.afterApplyOverrides(config)

        self.data['Skins'] = {}

        for PersistentId in self.data['Heroes']:
            staticHero = self.data['Heroes'][PersistentId]
            if staticHero['legal'] and staticHero['heroSkins'] and staticHero['heroSkins']['Item'] and len(
                    staticHero['heroSkins']['Item']) > 0:
                for skin in staticHero['heroSkins']['Item']:
                    skin['heroClassId'] = staticHero['persistentId']
                    self.data['Skins'].update({crc32(skin['persistentId']): skin})

        self.data['GuildProductionLevels'] = {}
        guildLevel = -1
        if 'levels' in self.data['GuildLevels'] and 'Item' in self.data['GuildLevels']['levels']:
            for level in self.data['GuildLevels']['levels']['Item']:
                guildLevel = guildLevel + 1
                if 'Bonuses' in level and 'Item' in level['Bonuses']:
                    for bonus in level['Bonuses']['Item']:
                        if 'classType' in bonus and bonus['classType'] == "GuildProduction" and 'cycle' in bonus:
                            self.data['GuildProductionLevels'].update({guildLevel: bonus['cycle']})
                            continue
            # пересчитаем уровни гильдии PF-74263
            # lastLvlExp = self.data['GuildLevels']['levels']['Item'][-1]['requiredExp']
            multiplier = self.data['GuildLevels']['requiredExpMultiplier']
            for level in self.data['GuildLevels']['levels']['Item']:
                level['requiredExp'] = level['requiredExp'] * multiplier

        # вытащим константу стартового рейтинга героев, чтобы не лазить за ней в недра
        self.START_HERO_RATING = self.data['HeroRatingToFameLevel']['Ratings']['Item'][0]

        self.rollTallents(config)

        #    self.cachedRates = [rankInfo['rating'] for rankInfo in self.data['AIGameLogic']['heroRanks']['ranks']['Item']]
        self.cachedRates = self.data['AIGameLogic']['heroRanks']['ranks']['Item']

        if applyOverrides:
            try:
                # Заполним статические поля, которые можно перезаписыать из GMTools
                config.fillStaticDataDependendValues(self)
            except:
                pass

    def reloadConfigDependendFields(self, config):
        self.rollTallents(config)

    def afterApplyOverrides(self, config):
        # kramarov: дизайнеры практикуют оверрайд талантов. поэтому после оверрайда пересчитываем crc, статы и action bar
        self.ForceParameters = self.data['AIGameLogic']['forceParameters']
        for hero_class_id in self.data['Heroes']:
            self.initTalantSetCrc(hero_class_id)
            self.calcDefaultHeroForce(hero_class_id)
            self.setDefaultActionBarIndexes(hero_class_id)
        self.fillHeroes(config)

    # -----------------------------------------

    @staticmethod
    def getRandomPure(seed):
        hi = 16807 * (seed >> 16)
        lo = 16807 * (seed & 0xffff)
        lo += (hi & 0x7FFF) << 16
        lo += hi >> 15
        if (lo > 2147483647):
            lo -= 2147483647
        return lo

    def rollTallents(self, config):
        info("StaticData.rollTallents")
        self.TALENTS_FOR_ROLL = {}
        self.TalentsByPack = {}
        forbidden_talents = []
        if config:
            forbidden_talents = config.TALENTS_NOT_FOR_ROLL
        all_talents = self.data['Talents'].keys()[:]
        all_talents.sort()
        for PersistentId in all_talents:
            staticTalent = self.data['Talents'][PersistentId]
            try:
                if staticTalent['persistentId'] == None:
                    continue
                if staticTalent['persistentId'] in forbidden_talents:
                    info("StaticData.rollTallents: excluding %r for roll as member of TALENTS_NOT_FOR_ROLL",
                         staticTalent['persistentId'])
                    continue
            except:
                continue

            # Роллим только нужные таланты
            if (int(staticTalent['talentRollGroups']) & 16) == 0:
                continue

            packs = self.data['AIGameLogic']['talentPacks']
            packs2 = packs['packs']

            for pack in packs2['Item']:
                talents = pack['talents']
                packId = pack['id']
                for talent in talents['Item']:
                    if staticTalent['persistentId'] == talent['persistentId']:
                        if packId in self.TalentsByPack:
                            self.TalentsByPack[packId].append(PersistentId)
                        else:
                            self.TalentsByPack[packId] = [PersistentId]

            rarity = str(staticTalent['rarity'])
            if rarity in self.TALENTS_FOR_ROLL:
                self.TALENTS_FOR_ROLL[rarity].append(PersistentId)
            else:
                self.TALENTS_FOR_ROLL[rarity] = [PersistentId]

    def checkForGoodRandom(self, val, rollContainer):
        randValue = val
        newTalensByRarity = {ETalentRarity.Class: [], ETalentRarity.ordinary: [], ETalentRarity.good: [],
                             ETalentRarity.excellent: [], ETalentRarity.magnificent: [], ETalentRarity.exclusive: [], }

        for i in xrange(0, 100):
            persistentId, rarity = self.getTalentForRoll(rollContainer, False, "", "", randValue, randValue)
            intRarity = getattr(ETalentRarity, rarity)
            if intRarity in newTalensByRarity:
                newTalensByRarity[intRarity].append(persistentId)
            else:
                newTalensByRarity[intRarity] = [persistentId]
            randValue = self.getRandomPure(randValue)

        if len(newTalensByRarity[ETalentRarity.Class]) != int(rollContainer[ETalentRarity.Class]):
            return False
        if len(newTalensByRarity[ETalentRarity.ordinary]) != int(rollContainer[ETalentRarity.ordinary]):
            return False
        if len(newTalensByRarity[ETalentRarity.good]) != int(rollContainer[ETalentRarity.good]):
            return False
        if len(newTalensByRarity[ETalentRarity.excellent]) != int(rollContainer[ETalentRarity.excellent]):
            return False
        if len(newTalensByRarity[ETalentRarity.magnificent]) != int(rollContainer[ETalentRarity.magnificent]):
            return False
        if len(newTalensByRarity[ETalentRarity.exclusive]) != int(rollContainer[ETalentRarity.exclusive]):
            return False

        return True

    def getRandomRarity(self, probs, randValue):
        rarities = ["Class", "ordinary", "good", "excellent", "magnificent", "exclusive"]
        value = self.getValueInRange(randValue, 1, 100)
        percent = 0
        for i in xrange(1, len(rarities) - 1):
            percent += probs[i]
            if value <= percent:
                return rarities[i]

        return rarities[-1]

    def getTalentForRoll(self, probs, replace_exclusive, selectedOrangeSet, selectedRedSet, transRandVal,
                         talentRandVal):
        rarity = self.getRandomRarity(probs, transRandVal)
        if replace_exclusive and rarity == "exclusive":
            rarity = "excellent"

        if rarity == "exclusive":
            talent_id = self.getRandomTalent(rarity, selectedOrangeSet, talentRandVal >> 8)
        elif rarity == "outstanding":
            talent_id = self.getRandomTalent(rarity, selectedRedSet, talentRandVal >> 8)
        else:
            talent_id = self.getRandomTalent(rarity, "", talentRandVal >> 8)

        if talent_id:
            return talent_id, rarity
        else:
            warn("Cannot generate random talent with rarity %s" % rarity)
            return None, None

    def fillHeroes(self, config):
        talentsets = 3
        if config:
            # некоторые тесты запускаются без config
            talentsets = config.MAX_USER_TALENTSETS_COUNT
        for PersistentId in self.data['Heroes']:
            staticHero = self.data['Heroes'][PersistentId]
            staticHero['talents'] = []
            for i in xrange(talentsets):
                staticHero['talents'].append(StaticData.calcHeroDefaultTalentSet(self,
                                                                                 self.getDefaultTalentSetSD(config,
                                                                                                            staticHero,
                                                                                                            i,
                                                                                                            ignoreValidation=True)))

    def getValidDefaultTalentSetIdx(self, config, staticHero, setIdx, ignoreDisabledSetsValidation=False):
        numDefaultSets = len(staticHero['defaultTalentsSets']['Item'])
        if numDefaultSets == 0 or not staticHero['defaultTalentsSets']['Item'][0]:
            err("Fail int default talent sets - no valid data was found in SD")

        if setIdx >= numDefaultSets or not staticHero['defaultTalentsSets']['Item'][setIdx]:
            return 0

        if ignoreDisabledSetsValidation or not config:
            return setIdx

        set_dbid = staticHero['defaultTalentsSets']['Item'][setIdx]['dbid']
        if set_dbid in config.DISABLED_DEFAULT_TALENSETS:
            return 0

        return setIdx

    def getDefaultTalentSetSD(self, config, staticHero, setIdx, ignoreValidation=False):
        validSetIdx = self.getValidDefaultTalentSetIdx(config, staticHero, setIdx, ignoreValidation)
        return staticHero['defaultTalentsSets']['Item'][validSetIdx]

    def getDefaultSetTalents(self, config, staticHero, tsId, ignoreValidation=False):
        validSetIdx = self.getValidDefaultTalentSetIdx(config, staticHero, tsId, ignoreValidation)
        return staticHero['talents'][validSetIdx]

    @staticmethod
    def calcHeroDefaultTalentSet(SD, defaultTalentSet):
        res = []
        rowCount = 0

        class StaticTalent:
            pass

        for row in defaultTalentSet['levels']['Item']:
            talents = []
            posCount = 0
            for pos in row['talents']['Item']:
                try:
                    if pos['talent']['persistentId']:
                        talent = StaticTalent()
                        talent.name = str(pos['talent']['persistentId'])
                        talent.ActionBarIdx = pos['talent']['ActionBarIdx'] or 0
                        talent.CRC32 = crc32(talent.name)
                        talent.row = rowCount
                        talent.pos = posCount
                        talent.position = rowCount * 6 + posCount + 1
                        talent.rarity = SD.data['Talents'][talent.CRC32]["rarity"]
                        talents.append(talent)
                except:
                    pass
                posCount += 1
            rowCount += 1
            res.append(talents)
        return res

    @staticmethod
    def getFractions(fracts):
        fractions = []
        if int(fracts) == 1:
            fractions = ['A']
        elif int(fracts) == 2:
            fractions = ['B']
        elif int(fracts) == 3:
            fractions = ['A', 'B']
        return fractions

    @staticmethod
    def getPrereqs(staticTalent):
        prereqs = []
        if staticTalent['prerequisiteTalents']:
            for talent in staticTalent['prerequisiteTalents']['Item']:
                prereqs.append(crc32(str(talent['persistentId'])))
        return prereqs

    def getHeroWithTalent(self, talent, config):
        for PersistentId in self.data['Heroes']:
            staticHero = self.data['Heroes'][PersistentId]
            if staticHero['legal']:
                for tsIdx in xrange(config.MAX_USER_TALENTSETS_COUNT):
                    ts = self.getStaticHeroTalents(config, staticHero, tsIdx);
                    for row in ts:
                        for item in row:
                            if item.CRC32 == talent.CRC32:
                                return staticHero

        return None

    def getFameLevel(self, fame):
        lvl = 0
        for it in self.data['LevelToFameTable']['Levels']['Item']:
            if fame >= it:
                lvl += 1
            else:
                break
        return lvl

    def getGuildLevel(self, exp):
        lvl = -1
        if 'levels' in self.data['GuildLevels'] and 'Item' in self.data['GuildLevels']['levels']:
            for it in self.data['GuildLevels']['levels']['Item']:
                if exp >= it['requiredExp']:
                    lvl += 1
                else:
                    break
        return lvl

    # возвращаем диапазон опыта [начало текущего уровня..начало следующего уровня] для расчета "оставшегося процента опыта"
    def getGuildLevelExpRange(self, level):
        low = 0
        high = 0
        try:
            low = self.data['GuildLevels']['levels']['Item'][level]['requiredExp']
            high = low  # если следующего уровня нет, вернем [1cap,cap]
            high = self.data['GuildLevels']['levels']['Item'][level + 1]['requiredExp']
        except:
            pass
        return low, high

    def getLeftToCapForGuild(self, currentExp):
        if 'levels' in self.data['GuildLevels'] and 'Item' in self.data['GuildLevels']['levels']:
            return max(0, self.data['GuildLevels']['levels']['Item'][-1]['requiredExp'] - currentExp)

    def getGuildProductionCycle(self, level):
        keyLevels = self.data['GuildProductionLevels'].keys()[:]
        keyLevels.sort()

        lastLevel = -1
        for keyLevel in keyLevels:
            if keyLevel > level:
                break
            lastLevel = keyLevel

        if lastLevel == -1:
            return None

        return self.data['GuildProductionLevels'].get(lastLevel)

    def getGuildMembersBonus(self, level):
        if level < 0 or level > len(self.data['GuildLevels']['levels']['Item']):
            return 0

        members = 0
        countLevel = 0

        for sdLevel in self.data['GuildLevels']['levels']['Item']:
            if 'Item' in sdLevel['Bonuses']:
                for bonus in sdLevel['Bonuses']['Item']:
                    if bonus['classType'] == "GuildMemberBonus":
                        if level >= countLevel:
                            members += int(bonus['members'])
            countLevel += 1

        return members

    def getGuildMembersLimit(self, level, I):
        baseSize = I.Config.getMainConfig().GUILD_MAX_SIZE
        bonusMembers = self.getGuildMembersBonus(level)
        return baseSize + bonusMembers

    def getGuildMembersLimitByExp(self, guildExp, I):
        return self.getGuildMembersLimit(self.getGuildLevel(guildExp), I)

    def getGuildStatPointsBonus(self, level):
        if level < 0 or level > len(self.data['GuildLevels']['levels']['Item']):
            return 0
        guildLevel = self.data['GuildLevels']['levels']['Item'][level]
        if guildLevel:
            for bonus in guildLevel['Bonuses']['Item']:
                if bonus['classType'] == "GuildStatsBonus":
                    return int(bonus['MasterPoints'])
        return 0

    def getMapGroup(self, madId):
        madId = madId.lower()
        if 'Item' in self.data['GroupMaps']:
            for group in self.data['GroupMaps']['Item']:
                if 'maps' in group and 'Item' in group['maps']:
                    for MapInGr in group['maps']['Item']:
                        if MapInGr['dbid'].lower() == madId:
                            return group['dbid']
        return None

    def getDefaultMapByType(self, mapType):
        if 'Item' in self.data['DefaultMaps'] and mapType < len(self.data['DefaultMaps']):
            defMap = self.data['DefaultMaps']['Item'][mapType]
            if 'dbid' in defMap['map'] and 'classType' in defMap['map']:
                return defMap['map']['dbid']
            elif 'dbid' in defMap['group'] and 'classType' in defMap['group']:
                return defMap['group']['dbid']
        return None

    def getHeroExpLevel(self, exp):
        lvl = -1
        for it in self.data['LevelToExperienceTable']['Levels']['Item']:
            if exp >= it:
                lvl += 1
            else:
                break
        return lvl

    def getTavernQuestExpBonus(self, stTavern, quest, tavernLevel):
        exp = 0
        if quest and 'reward' in quest and quest['reward']:
            exp = quest['reward']['experience']
            coeff = self.getFloatInterpolated(stTavern['tavernLevels'], tavernLevel, None, "rewardCoefficient", 0.0)
            exp = self.roundFloatToInt(exp * (1.0 + coeff / 100.0))
        return exp

    def getConvertedTavernQuestResources(self, stTavern, quest, tavernLevel):
        if quest and 'reward' in quest and quest['reward']:
            resCount = StaticData.copyPriceFloat(quest['reward']['resource'])
            if not StaticData.isValidPrice(resCount):
                return None

            #итог надо перевести в int
            return StaticData.copyPrice(resCount)
        return None

    def getHeroExpBonusInTavern(self, hero, stTavern, heroExp):
        heroLevel = self.getHeroExpLevel(hero.Experience)
        currentHeroExp = heroExp * self.getFloatInterpolated(stTavern['tavernExpCoeffToHeroLevels'], heroLevel, None,
                                                             "coefficient", 0.0)
        return self.roundFloatToInt(currentHeroExp)

    def getTalentLevel(self, talent):
        staticTalent = self.getStaticTalent(talent)
        lvl = 0
        if staticTalent:
            points = talent.Points
            lvl = self.getTalentLevelByPoints(points, staticTalent)
        return lvl

    def getTalentLevelByPoints(self, points, staticTalent):
        intRarity = getattr(ETalentRarity, staticTalent['rarity'])
        if intRarity is not None:
            if intRarity < len(self.data['TalentLevelToPointsAndRarity']['Item']) and \
                    self.data['TalentLevelToPointsAndRarity']['Item'][intRarity]:
                levelToPoints = self.data['TalentLevelToPointsAndRarity']['Item'][intRarity]['levelToPoints']
                if 'Item' in levelToPoints and len(levelToPoints['Item']) > 0:
                    lvl = 0
                    for item in levelToPoints['Item']:
                        if points >= item:
                            lvl += 1
                        else:
                            break
                    return lvl
                else:
                    return 0
            else:
                return 0
        return 0

    def getTalentPointsToLevel(self, staticTalent):
        intRarity = getattr(ETalentRarity, staticTalent['rarity'])
        if intRarity < len(self.data['TalentLevelToPointsAndRarity']['Item']) and \
                self.data['TalentLevelToPointsAndRarity']['Item'][intRarity]:
            pointsToLevel = self.data['TalentLevelToPointsAndRarity']['Item'][intRarity]['levelToPoints']
            if 'Item' in pointsToLevel:
                return pointsToLevel['Item']

    def getTalentPointsForCurrentAndNextLevels(self, target_talent_points, staticTalent):
        intRarity = getattr(ETalentRarity, staticTalent['rarity'])
        if intRarity != None:
            if intRarity < len(self.data['TalentLevelToPointsAndRarity']['Item']) and \
                    self.data['TalentLevelToPointsAndRarity']['Item'][intRarity]:
                levelToPoints = self.data['TalentLevelToPointsAndRarity']['Item'][intRarity]['levelToPoints']
                if 'Item' in levelToPoints and len(levelToPoints['Item']) != 0:
                    it = -1
                    prev = 0
                    next = None
                    uberNext = None
                    for points in levelToPoints['Item']:
                        if target_talent_points < points:
                            break
                        it += 1
                    if it != -1:
                        prev = levelToPoints['Item'][it]
                    if it < len(levelToPoints['Item']) - 1:
                        next = levelToPoints['Item'][it + 1]
                    if (it + 1) < len(levelToPoints['Item']) - 1:
                        uberNext = levelToPoints['Item'][it + 2]
                    return [prev, next, uberNext]
        return [None, None, None]

    def getTalentMaxPoints(self, talent):
        staticTalent = self.getStaticTalent(talent)
        intRarity = getattr(ETalentRarity, staticTalent['rarity'])
        return self.getTalentMaxPointsByIntRarity(intRarity)

    # warn - check 270 line (award["AdditionalData2"] validation) in DynamicQuest_base if you can change refinePointsCap
    def getTalentMaxPointsByIntRarity(self, intRarity):
        if intRarity < len(self.data['TalentLevelToPointsAndRarity']['Item']) and \
                self.data['TalentLevelToPointsAndRarity']['Item'][intRarity]:
            item = self.data['TalentLevelToPointsAndRarity']['Item'][intRarity]  # type: dict
            if 'refinePointsCap' in item:
                return int(item['refinePointsCap'])
            else:
                return 0

    def getTalentMergePrice(self, prev_points, cur_points, static_talent):
        pearls = 0
        intRarity = getattr(ETalentRarity, static_talent['rarity'])
        prev_level = self.getTalentLevelByPoints(prev_points, static_talent)
        cur_level = self.getTalentLevelByPoints(cur_points, static_talent)
        if intRarity < len(self.data['TalentMergePriceToLevelAndRarity']['Item']) and \
                self.data['TalentMergePriceToLevelAndRarity']['Item'][intRarity]:
            levelToPrice = self.data['TalentMergePriceToLevelAndRarity']['Item'][intRarity]['levelToPrice']
            levels = range(prev_level, cur_level)
            for lvl in levels:
                pearls += levelToPrice['Item'][lvl]

        return pearls

    def getHeroForce(self, hero, tsId, md, bufStatPoints=0.0):
        force = self.ForceParameters['baseHeroForce']

        for pos in hero.TalentSets[tsId].Talents.keys():
            talent = md.getTalentByID(hero.TalentSets[tsId].Talents.get(pos))
            staticTalent = self.getStaticTalent(talent)
            force += self.calcTalentForce(talent, staticTalent, toint(pos))

        statPointsForceMultiplyer = self.ForceParameters['masteryPointForce']

        statPoints = hero.getPutStats(self, tsId)

        force += float(statPoints) * statPointsForceMultiplyer
        force += float(bufStatPoints) * statPointsForceMultiplyer
        return force

    def getHeroStatPoints(self, lvl):
        if lvl >= 0 and lvl < len(self.data['StatpointsToLevelTable']['StatPoints']['Item']):
            return self.data['StatpointsToLevelTable']['StatPoints']['Item'][lvl]
        return self.data['StatpointsToLevelTable']['StatPoints']['Item'][-1]

    def getEditorStatName(self, name):
        # в редакторе статы хранятся под странными именами. таблица перевода нормальных имен в странные.
        if name == 'Agility':
            return 'AttackSpeed'
        if name == 'Cunning':
            return 'Dexterity'
        if name == 'Fortitude':
            return 'Stamina'
        if name == 'Health':
            return 'Life'
        if name == 'Mana':
            return 'Energy'
        return name

    def getCodeStatName(self, name):
        if name == 'AttackSpeed':
            return 'Agility'
        if name == 'Dexterity':
            return 'Cunning'
        if name == 'Stamina':
            return 'Fortitude'
        if name == 'Life':
            return 'Health'
        if name == 'Energy':
            return 'Mana'
        return name

    def getStatPointsMultiplyer(self, stat):
        stat = self.getEditorStatName(stat)

        for item in self.data['StatsBudgetContainer']['stats']['Item']:
            if item['stat'] == stat:
                return item['budget']

    def getMaxHeroExp(self):
        return self.data['LevelToExperienceTable']['Levels']['Item'][-1]

    def getMaxLordFame(self):
        return self.data['LevelToFameTable']['Levels']['Item'][-1]

    def getStaticSkin(self, skin):
        return self.data['Skins'].get(skin.PersistentId)

    def getStaticSkinByPersistentId(self, skin_persistent_id):
        return self.data['Skins'].get(skin_persistent_id)

    def getStaticConstruction(self, construction):
        return self.data['Constructions'].get(construction.PersistentId)

    def getStaticConstructionByPersistentId(self, construction_persistent_id):
        return self.data['Constructions'].get(construction_persistent_id)

    def getStaticHero(self, hero):
        return self.data['Heroes'].get(hero.PersistentId)

    def getStaticHeroByClassId(self, hero_class_id):
        return self.data['Heroes'].get(hero_class_id)

    def getStaticHeroByClassName(self, hero_class_name):
        return self.data['Heroes'].get(crc32(hero_class_name))

    def getStaticQuest(self, quest):
        if hasattr(quest, "persistentId"):
            return self.data['Quests'].get(quest.persistentId)
        else:
            return None

    def getStaticObjective(self, quest, objective):
        if quest and objective:
            staticQuest = self.data['Quests'].get(quest.persistentId)
            if staticQuest and objective.index < len(staticQuest['objectives']['Item']):
                return staticQuest['objectives']['Item'][objective.index]

    def getStaticQuestByFraction(self, acc, questId):
        staticQuest = None
        if acc.db.fraction:
            if acc.db.fraction == 'A':
                staticQuest = self.getStaticQuestById(crc32(questId + "_qA"))
            if acc.db.fraction == 'B':
                staticQuest = self.getStaticQuestById(crc32(questId + "_qB"))
        return staticQuest

    def getStaticQuestOnlyNameByFraction(self, acc, questId):
        staticQuest = None
        if acc.db.fraction == 'A':
            staticQuest = {"persistentId": (questId + "_qA")}
        if acc.db.fraction == 'B':
            staticQuest = {"persistentId": (questId + "_qB")}
        return staticQuest

    def getStaticQuestById(self, id):
        return self.data['Quests'].get(id)

    def getStaticQuestLineByStaticQuestId(self, persistentId):
        for qstLine in self.data['QuestsLine']['Item']:
            for qst in qstLine['quests']['Item']:
                if persistentId == qst['persistentId']:
                    return qstLine
        return None

    def getStaticRerollShopItemById(self, id):
        return self.data['RerollShopSlots'].get(id)

    def getStaticRerollShopGroupById(self, id):
        for group in self.data['RerollShop']['groups']['Item']:
            if crc32(group['persistentId']) == id:
                return group
        return None

    def getStaticMap(self, mapname):
        for map in self.data['AviableMaps']['maps']['Item']:
            if map['dbid'] == mapname:
                return map

    def isValidForceForMap(self, force, map):
        staticMap = self.getStaticMap(map)
        if staticMap and staticMap['mapSettings'] and 'requiredHeroforce' in staticMap['mapSettings']:
            return force >= float(staticMap['mapSettings']['requiredHeroforce'])
        return True

    def getStaticTalent(self, talent):
        if hasattr(talent, "PersistentId"):
            return self.data['Talents'].get(talent.PersistentId)

    def getStaticTalentByTalentId(self, talent_id):
        return self.data['Talents'].get(talent_id)

    def getMap(self):
        return self.data['Map']

    def getExpansionPrice(self, level):
        if level < len(self.data['Map']['Grades']['Item']):
            return self.copyPrice(self.data['Map']['Grades']['Item'][level]['price'])
        return None

    def initTalantSetCrc(self, hero_class_id):
        staticHero = self.getStaticHeroByClassId(hero_class_id)

        for i in range(len(staticHero['defaultTalentsSets']['Item'])):
            talentList = set([])
            dts = self.getDefaultTalentSetSD(None, staticHero, i, ignoreValidation=True)
            rowCount = 0
            for row in dts['levels']['Item']:
                for pos in row['talents']['Item']:
                    try:
                        if pos['talent']['persistentId']:
                            pos['talent']['crc32'] = crc32(pos['talent'][
                                                               'persistentId'])  # сразу посчитаем crc(имени таланта), чтобы потом не тратить время при создании modeldata
                            talentList.add(str(rowCount) + str(pos['talent']['persistentId']))
                    except:
                        pass
                rowCount += 1

            talentsString = "".join(sorted(talentList))
            dts['crc32'] = crc32(talentsString)

    def getTalantSetCrc(self, staticHero, tsIdx, config):
        # staticHero = self.getStaticHero( hero )
        dts = self.getDefaultTalentSetSD(config, staticHero, tsIdx)
        return dts['crc32']

    def calcTalentForce(self, talent, staticTalent, pos):
        if not staticTalent:
            return 0.0

        rarity = staticTalent['rarity']
        intRarity = getattr(ETalentRarity, rarity, None)

        # TODO: ?
        if intRarity is None:
            return 0.0

        talantLevel = int(math.ceil(pos / 6.0)) - 1
        effectiveBudget = staticTalent['budget']

        if effectiveBudget < 0.0:
            if intRarity == 0:
                levelModifier = self.ForceParameters['classTalentLevelForceModifiers']['Item'][talantLevel]
                starModifier = self.ForceParameters['classTalentForceBonusPerStar']
            else:
                levelModifier = self.ForceParameters['talentLevelForceModifiers']['Item'][talantLevel]
                starModifier = self.ForceParameters['talentForceBonusPerStar']

            if talent:
                upgradeLevel = self.getTalentLevel(talent)
            else:
                upgradeLevel = 0

            effectiveBudget = self.data['AIGameLogic']['talentBaseStatBudget'] * self.ForceParameters[
                'talentForceModifier'] / 220.0

            starModifier *= upgradeLevel

            rarityModifier = self.ForceParameters['talentRarityForceModifiers']['Item'][intRarity]

            effectiveBudget *= rarityModifier * 0.01
            effectiveBudget *= (1.0 + levelModifier * 0.01)
            effectiveBudget *= (1.0 + starModifier * 0.01)


        if intRarity == 0:
            modifier = self.ForceParameters['classTalentLevelForceModifiers']['Item'][talantLevel]
        else:
            modifier = self.ForceParameters['talentLevelForceModifiers']['Item'][talantLevel]

        return effectiveBudget / (1.0 + modifier * 0.01) + self.ForceParameters['talentRarityForceSummand']['Item'][
            intRarity]

    def getTotalPoints(self, total_points, target_staticTalent, target_talent_max_points):
        points = self.getTalentPointsForCurrentAndNextLevels(total_points, target_staticTalent)
        # next level is maximum => improve to next lvl
        if points[2] == None:
            total_points = target_talent_max_points
        else:
            points_to_add = points[1] - total_points
            progress = float(total_points - points[0]) / float(points[1] - points[0])
            points_to_add += (points[2] - points[1]) * progress
            total_points += points_to_add

        return total_points

    def getTotalMergePointsFromSameTalent(self, total_points, target_staticTalent, target_talent_max_points,
                                          same_source_talent):
        level = self.getTalentLevel(same_source_talent) + 1
        for i in xrange(0, level):
            total_points = self.getTotalPoints(total_points, target_staticTalent, target_talent_max_points)

        staticSourceTalent = self.getStaticTalent(same_source_talent)
        pointsSource = self.getTalentPointsForCurrentAndNextLevels(same_source_talent.Points, staticSourceTalent)
        total_points += same_source_talent.Points - pointsSource[0]
        return total_points

    def recheckTotalPointsForMergeTalent(self, total_points, target_staticTalent, target_talent_max_points,
                                         same_source_talent):
        level = self.getTalentLevel(same_source_talent) + 1
        for i in xrange(0, level):
            total_points = self.getTotalPoints(total_points, target_staticTalent, target_talent_max_points)

            if target_talent_max_points <= total_points:
                return total_points

        staticSourceTalent = self.getStaticTalent(same_source_talent)
        pointsSource = self.getTalentPointsForCurrentAndNextLevels(same_source_talent.Points, staticSourceTalent)
        total_points += same_source_talent.Points - pointsSource[0]
        return total_points

    def calcDefaultHeroForce(self, hero_class_id):
        staticHero = self.getStaticHeroByClassId(hero_class_id)
        force = self.ForceParameters['baseHeroForce']
        rowBase = 0
        for i in range(len(staticHero['defaultTalentsSets']['Item'])):
            dts = self.getDefaultTalentSetSD(None, staticHero, i, ignoreValidation=True)
            for row in dts['levels']['Item']:
                position = rowBase + 1
                for pos in row['talents']['Item']:
                    try:
                        if pos['talent']['persistentId']:
                            staticTalent = self.getStaticTalentByTalentId(pos['talent']['crc32'])
                            force += self.calcTalentForce(None, staticTalent, position)
                    except:
                        pass
                    position += 1
                rowBase += 6
            dts['Force'] = force

    def getDefaultHeroForce(self, config, hero_class_id, talentSetIdx, bufStatPoints=0.0):
        staticHero = self.getStaticHeroByClassId(hero_class_id)
        dts = self.getDefaultTalentSetSD(config, staticHero, talentSetIdx)
        return dts['Force'] + float(bufStatPoints) * self.ForceParameters['masteryPointForce']

    def setDefaultActionBarIndexes(self, hero_class_id):
        actionBarIndexCount = 0
        staticHero = self.getStaticHeroByClassId(hero_class_id)
        for i in range(len(staticHero['defaultTalentsSets']['Item'])):
            dts = self.getDefaultTalentSetSD(None, staticHero, i, ignoreValidation=True)
            for row in dts['levels']['Item']:
                for pos in row['talents']['Item']:
                    try:
                        if pos['talent']['persistentId']:
                            staticTalent = self.getStaticTalentByTalentId(pos['talent']['crc32'])
                            if staticTalent:
                                if not staticTalent['type'] == "Simple" and not staticTalent['type'] == "Passive":
                                    if actionBarIndexCount < 9:
                                        actionBarIndex = actionBarIndexCount
                                        actionBarIndexCount += 1
                                    else:
                                        actionBarIndex = -1
                                else:
                                    actionBarIndex = -1

                                pos['talent']['ActionBarIdx'] = actionBarIndex

                    except:
                        pass

    def getTalentSellPrice(self, talent):
        intRarity = getattr(ETalentRarity, talent['rarity'])

        price = self.data['TalentsSellPrice']['Item'][intRarity]
        return self.copyPrice(price)

    def getTalentUnsoulboundPrice(self, static_talent, talent_level, config):
        res = self.emptyPrice()

        if static_talent['rarity'] != 'outstanding' and static_talent['rarity'] != 'exclusive':
            return res

        price = self.data['TalentsUnsoulboundPriceByLevel']['Item'][0]['price']

        for item in self.data['TalentsUnsoulboundPriceByLevel']['Item']:
            if talent_level + 1 <= item['level']:
                price = item['price']
                break

        if static_talent['rarity'] == 'outstanding':
            res.Gold = price
        else:
            res.Perl = price
        return res

    def getActualGold(self, maxGold, percentDone):
        percentNeed = 100 - percentDone
        actualGold = maxGold
        if percentNeed >= 0 and percentNeed <= 100:
            for item in self.data['GoldPriceCycleTable']['goldtable']['Item']:
                if percentNeed <= item['timePercent']:
                    actualGold = self.roundGold(maxGold * item['goldPercent'] / 100.0)
            return actualGold
        return 0

    @staticmethod
    def getInterpolLevels(levels, level):
        if levels == None or levels == 'None':
            return None, None
        prLevelFirst = None
        prLevelSecond = None
        for prLevel in levels['Item']:
            if level >= prLevel['currentLevel']:
                prLevelFirst = prLevel
            if level <= prLevel['currentLevel']:
                prLevelSecond = prLevel
                break
        return prLevelFirst, prLevelSecond

    @staticmethod
    def _getNeighborhoodLevelsPrices(levels, level, cycle, name):
        prLevelFirst, prLevelSecond = StaticData.getInterpolLevels(levels, level)
        if prLevelFirst is None or prLevelSecond is None:
            return None, None, None, None

        # подпорка на использование в домиках циклов производста, которые выпилены в 10.2
        if (cycle >= 0 and 'cycles' not in prLevelFirst) or \
                (cycle == -1 and 'cycle' not in prLevelFirst):
            cycle = None

        if cycle is None:
            if name not in prLevelFirst:
                return None, None, None, None

            value1 = prLevelFirst[name]
            value2 = prLevelSecond[name]
        elif cycle == -1:
            value1 = prLevelFirst['cycle'][name]
            value2 = prLevelSecond['cycle'][name]
        else:
            value1 = prLevelFirst['cycles']['Item'][cycle][name]
            value2 = prLevelSecond['cycles']['Item'][cycle][name]

        return value1, value2, prLevelFirst, prLevelSecond

    @staticmethod
    def getPriceInterpolated(levels, level, cycle, name, default, coeff=False):
        value1, value2, prLevelFirst, prLevelSecond = StaticData._getNeighborhoodLevelsPrices(levels, level, cycle,
                                                                                              name)
        if value1 is None:
            return default

        if coeff:
            return StaticData.getFinalPriceCoeff(prLevelFirst, prLevelSecond, value1, value2, level)
        return StaticData.getFinalPrice(prLevelFirst, prLevelSecond, value1, value2, level)

    @staticmethod
    def getFloatInterpolated(levels, level, cycle, name, default):
        value1, value2, prLevelFirst, prLevelSecond = StaticData._getNeighborhoodLevelsPrices(levels, level, cycle,
                                                                                              name)
        if value1 is None:
            return default

        if prLevelFirst['currentLevel'] == prLevelSecond['currentLevel']:
            return value1

        coeff = float(level - prLevelFirst['currentLevel']) / float(
            prLevelSecond['currentLevel'] - prLevelFirst['currentLevel'])
        value = value1 + (value2 - value1) * coeff
        return value

    @staticmethod
    def getIntInterpolated(levels, level, cycle, name, default):
        value = StaticData.getFloatInterpolated(levels, level, cycle, name, default)
        if value is None:
            value = default
        return StaticData.roundFloatToInt(value)

    @staticmethod
    def emptyPrice():
        return ClassDict(
            Gold=0,
            Perl=0,
            RedPerl=0,
            Resource1=0,
            Resource2=0,
            Resource3=0,
            Silver=0,
            Population=0,
            Resource1_Rare=0,
            Resource2_Rare=0,
            Resource3_Rare=0,
            CWPoints_Player=0,
            CWPoints_Clan=0,
            PremiumAccountHours=0,
            Shard=0,
            Currencies=ClassDict()
        )

    @staticmethod
    def add_standard_value(price, res_type, custom_id, res_value):
        if res_type == 'CustomCurrency' and custom_id:
            if custom_id:
                if custom_id not in price.Currencies:
                    price.Currencies[custom_id] = 0
                price.Currencies[custom_id] += res_value
        elif res_type == 'Silver':
            price.Silver += res_value
        elif res_type == 'Pearl':
            price.Perl += res_value
        elif res_type == 'RedPearl':
            price.RedPerl += res_value
        elif res_type == 'Shard':
            price.Shard += res_value
        elif res_type == 'Resource1':
            price.Resource1 += res_value
        elif res_type == 'Resource2':
            price.Resource2 += res_value
        elif res_type == 'Resource3':
            price.Resource3 += res_value

    @staticmethod
    def is_empty_price(price):
        if price.Gold != 0:
            return False
        if price.Perl != 0:
            return False
        if price.RedPerl != 0:
            return False
        if price.Resource1 != 0:
            return False
        if price.Resource2 != 0:
            return False
        if price.Resource3 != 0:
            return False
        if price.Silver != 0:
            return False
        if price.Population != 0:
            return False
        if price.Resource1_Rare != 0:
            return False
        if price.Resource2_Rare != 0:
            return False
        if price.Resource3_Rare != 0:
            return False
        if price.CWPoints_Player != 0:
            return False
        if price.CWPoints_Clan != 0:
            return False
        if price.PremiumAccountHours != 0:
            return False
        if price.Shard != 0:
            return False
        for cc in price.Currencies:
            if price.Currencies[cc] != 0:
                return False
        return True

    @staticmethod
    def copyPrice(price, safe=True, customCurrenciesOnly=False):
        res = StaticData.emptyPrice()
        for k, v in price.iteritems():
            if not safe or k in res:
                if k == 'Currencies':
                    if isinstance(v, dict) or isinstance(v, collects.SimpleDict):
                        for ck, cv in v.iteritems():
                            res[k][ck] = int(cv)
                    else:
                        continue
                elif not customCurrenciesOnly:
                    res[k] = int(v)
        return res

    @staticmethod
    def copyPriceFloat(price, safe=True):
        res = StaticData.emptyPrice()
        for k, v in price.iteritems():
            if not safe or k in res:
                if k == 'Currencies':
                    if isinstance(v, dict) or isinstance(v, collects.SimpleDict):
                        for ck, cv in v.iteritems():
                            res[k][ck] = float(cv)
                    else:
                        continue
                else:
                    res[k] = float(v)
        return res

    @staticmethod
    def isValidPrice(price):
        return not not StaticData.getFirstValueSafe(price)

    @staticmethod
    def overrideNonZeroValuesInPrice(price, amount):
        for k, v in price.iteritems():
            if isinstance(v, dict) or isinstance(v, collects.SimpleDict):
                StaticData.overrideNonZeroValuesInPrice(v, amount)
            elif v != 0:
                price[k] = amount
        return price

    @staticmethod
    def getFirstValue_old(price, default=None):
        # используется только для домиков
        if price.Perl != 0:
            return price.Perl
        if price.RedPerl != 0:
            return price.RedPerl
        if price.Resource1 != 0:
            return price.Resource1
        if price.Resource2 != 0:
            return price.Resource2
        if price.Resource3 != 0:
            return price.Resource3
        if price.Silver != 0:
            return price.Silver

        return default

    @staticmethod
    def getFirstValueSafe(price, default=None, safe=True):
        validPriceDict = StaticData.emptyPrice()
        res = default
        for k, v in price.iteritems():
            if not safe or k in validPriceDict:
                if isinstance(v, dict) or isinstance(v, collects.SimpleDict):
                    res = StaticData.getFirstValueSafe(v, default, safe=False)
                    if res != default:
                        return res
                elif v != 0:
                    return v

        return default

    @staticmethod
    def getResourceShortInfo(price):
        res = ''
        for k, v in price.iteritems():
            if v != 0:
                if res:
                    res += ':'
                res += k + ':' + str(v)

        return res

    @staticmethod
    def getSameValueFromOtherPrice(price1, price2):
        # используется только для домиков
        if price1.Perl != 0:
            return price2.Perl
        if price1.RedPerl != 0:
            return price2.RedPerl
        if price1.Resource1 != 0:
            return price2.Resource1
        if price1.Resource2 != 0:
            return price2.Resource2
        if price1.Resource3 != 0:
            return price2.Resource3
        if price1.Silver != 0:
            return price2.Silver

    @staticmethod
    def applyCoeffToPrice(price1, coeff):
        for k, v in price1.iteritems():
            if isinstance(v, dict):
                StaticData.applyCoeffToPrice(v, coeff)
            else:
                price1[k] = v * coeff
        return price1

    @staticmethod
    def getAddPrice(price1, price2):
        for k in price2.keys():
            v2 = price2.get(k)
            if not v2:
                continue
            if k in price1:
                v1 = price1.get(k)
                if isinstance(v2, dict):
                    if isinstance(v1, dict):
                        StaticData.getAddPrice(v1, v2)
                    else:
                        continue
                else:
                    price1[k] = v1 + v2
            else:
                if isinstance(v2, dict):
                    price1[k] = ClassDict()
                    StaticData.getAddPrice(v1, v2)
                else:
                    price1[k] = 0 + v2

        return price1

    @staticmethod
    def getSubtractPrice(price1, price2):
        for k in price2.keys():
            v2 = price2.get(k)
            if not v2:
                continue
            if k in price1:
                v1 = price1.get(k)
                if isinstance(v2, dict):
                    if isinstance(v1, dict):
                        StaticData.getSubtractPrice(v1, v2)
                    else:
                        continue
                else:
                    price1[k] = v1 - v2
            else:
                if isinstance(v2, dict):
                    price1[k] = ClassDict()
                    StaticData.getSubtractPrice(v1, v2)
                else:
                    price1[k] = 0 - v2

        return price1

    @staticmethod
    def getDividePrice(price1, price2):
        for k in price2.keys():
            v2 = price2.get(k)
            if v2 == 0:
                continue
            if k in price1:
                v1 = price1.get(k)
                if isinstance(v2, dict):
                    if isinstance(v1, dict):
                        StaticData.getDividePrice(v1, v2)
                    else:
                        continue
                else:
                    price1[k] = v1 / v2
            else:
                if isinstance(v2, dict):
                    price1[k] = ClassDict()
                    StaticData.getDividePrice(v1, v2)
                else:
                    price1[k] = 0

        return price1

    @staticmethod
    def getAddValuePrice(r, price1, value):
        for k, v in price1.iteritems():
            if isinstance(v, dict):
                StaticData.getAddValuePrice(r, v, value)
            elif k == r:
                price1[k] = v + value
                return price1
        return price1

    @staticmethod
    def isEnoughCustomCurrencies(price, resources):
        if not price.Currencies or (not isinstance(price.Currencies, dict) and not isinstance(price.Currencies, collects.SimpleDict)):
            return True
        for currency, value in price.Currencies.iteritems():
            if int(value) == 0:
                continue
            if currency not in resources.Currencies:
                return False
            if int(value) > int(resources.Currencies[currency]):
                return False
        return True

    @staticmethod
    def isEnoughResources(price, resources):
        if (int(price.Perl) > resources.Perl and int(price.Perl) != 0) \
                or (int(price.RedPerl) > resources.RedPerl and int(price.RedPerl) != 0) \
                or (int(price.Resource1) > resources.Resource1 and int(price.Resource1) != 0) \
                or (int(price.Resource2) > resources.Resource2 and int(price.Resource2) != 0) \
                or (int(price.Resource3) > resources.Resource3 and int(price.Resource3) != 0) \
                or (int(price.Resource1_Rare) > resources.Resource1_Rare and int(price.Resource1_Rare) != 0) \
                or (int(price.Resource2_Rare) > resources.Resource2_Rare and int(price.Resource2_Rare) != 0) \
                or (int(price.Resource3_Rare) > resources.Resource3_Rare and int(price.Resource3_Rare) != 0) \
                or (int(price.Population) > resources.Population and int(price.Population) != 0) \
                or (int(price.CWPoints_Player) > resources.CWPoints_Player and int(price.CWPoints_Player) != 0) \
                or (int(price.Silver) > resources.Silver and int(price.Silver) != 0) \
                or (int(price.Shard) > resources.Shard and int(price.Shard) != 0) \
                or not StaticData.isEnoughCustomCurrencies(price, resources):
            return False
        return True

    def GetBuyPrice(self, staticConstruction, configdata):
        gold = configdata.EventToolsChangeFields.FIRST_BUY_GOLD_PRICES.get(staticConstruction['persistentId'])
        if gold:
            newPrice = self.copyPrice(staticConstruction['Levels']['Item'][0]['price'])
            newPrice.Gold = gold
            return newPrice
        return self.copyPrice(staticConstruction['Levels']['Item'][0]['price'])

    def GetHeroGoldPrice(self, staticHero, configData, isFemale):
        if isFemale:
            overrideGoldCost = configData.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.get(staticHero['persistentId'])
        else:
            overrideGoldCost = configData.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.get(staticHero['persistentId'])

        if overrideGoldCost and overrideGoldCost > 0:
            return overrideGoldCost

        if isFemale:
            lvlReq = staticHero['lobbyData']['LevelRequireFemale']
            cost = staticHero['lobbyData']['CostFemale']
        else:
            lvlReq = staticHero['lobbyData']['LevelRequireMale']
            cost = staticHero['lobbyData']['CostMale']

        if lvlReq < configData.BuyGoldHeroInfo.MIN_LORD_LVL_REQUIRED:
            return 0
        silverCost = cost['Silver']
        if staticHero['persistentId'] in configData.EventToolsChangeFields.HERO_SILVER_PRICES:
            silverCost = configData.EventToolsChangeFields.HERO_SILVER_PRICES[staticHero['persistentId']]
        return (silverCost / configData.BuyGoldHeroInfo.DISCOUNT_COEFFICIENT) - 1

    @staticmethod
    def getFinalPrice(prLevelFirst, prLevelSecond, price1, price2, level):
        if prLevelFirst['currentLevel'] == prLevelSecond['currentLevel']:
            return StaticData.copyPrice(price1)

        coeff = float(level - prLevelFirst['currentLevel']) / float(
            prLevelSecond['currentLevel'] - prLevelFirst['currentLevel'])

        finalprice = StaticData.copyPriceFloat(price2)
        StaticData.getSubtractPrice(finalprice, price1)
        StaticData.applyCoeffToPrice(finalprice, coeff)
        StaticData.getAddPrice(finalprice, price1)
        return StaticData.copyPrice(finalprice)

    @staticmethod
    def getFinalPriceCoeff(prLevelFirst, prLevelSecond, price1, price2, level):
        if prLevelFirst['currentLevel'] == prLevelSecond['currentLevel']:
            return StaticData.copyPrice(price1)

        coeff = float(level - prLevelFirst['currentLevel']) / float(
            prLevelSecond['currentLevel'] - prLevelFirst['currentLevel'])

        finalprice = StaticData.copyPriceFloat(price2)
        StaticData.getSubtractPrice(finalprice, price1)
        StaticData.applyCoeffToPrice(finalprice, coeff)
        StaticData.getAddPrice(finalprice, price1)
        return finalprice

    @staticmethod
    def getBuildingPrice(staticBuilding, level, startLevel=0):
        price = StaticData.emptyPrice()
        for item in staticBuilding['Levels']['Item'][(startLevel):(level + 1)]:
            StaticData.getAddPrice(price, item['price'])
        # Перестраховка от читов - НЕ ЗНАЮ, нафига она была в этом методе, так что пока оставлю
        price.Gold = 0
        return price

    def getValueInRange(self, value, minV, maxV):
        maxrate = maxV - minV + 1
        if maxrate == 0:
            return 0
        return value % maxrate + minV

    def getCffFromRange(self, value, minV, maxV):
        maxrate = maxV - minV + 1
        return value * maxrate + minV

    def getEventRandomTalent(self, talentClass, selectedSet, randValue):
        talentsPool = []

        if selectedSet == "" or not (talentClass == "exclusive" or talentClass == "outstanding"):
            if talentClass in self.TALENTS_FOR_ROLL:
                talentsPool = self.TALENTS_FOR_ROLL[talentClass]
        elif selectedSet and selectedSet in self.TalentsByPack.keys():
            talentsPool = self.TalentsByPack.get(selectedSet, None)
        else:
            err("Fail roll random talent with rarity %r", talentClass)
            return None

        talentsCount = len(talentsPool)

        if talentsCount > 0:
            randVal = self.getCffFromRange(randValue, 0, talentsCount - 1)
            return talentsPool[int(randVal)]

        err("Fail roll random talent with rarity %r" % talentClass)
        return None

    def getRandomTalent(self, talentClass, selectedSet, randValue):
        talentsPool = []

        if selectedSet == "" or not (talentClass == "exclusive" or talentClass == "outstanding"):
            if talentClass in self.TALENTS_FOR_ROLL:
                talentsPool = self.TALENTS_FOR_ROLL[talentClass]
        elif selectedSet and selectedSet in self.TalentsByPack.keys():
            talentsPool = self.TalentsByPack.get(selectedSet, None)
        else:
            err("Fail roll random talent with rarity %r", talentClass)
            return None

        talentsCount = len(talentsPool)

        if talentsCount > 0:
            randVal = self.getValueInRange(randValue, 0, talentsCount - 1)
            return talentsPool[randVal]

        err("Fail roll random talent with rarity %r" % talentClass)
        return None

    def getObjectByDbid(self, dbid):
        if dbid in self.dbid:
            return self.dbid[dbid]

    def getStatsResetPriceCoef(self):
        return self.copyPrice(self.data['ResetStatsPriceCoef'])

    def getMaxEmptyTalents(self):
        return self.data['MaxEmptyTalents']

    def getHeroRating(self, hero, sex):
        static_hero = self.getStaticHero(hero)
        if static_hero:
            if sex == 2:
                LevelRequire = static_hero['lobbyData']['LevelRequireFemale']
                Default = static_hero['lobbyData']['IsHeroHiredByDefaultFemale']
            else:
                LevelRequire = static_hero['lobbyData']['LevelRequireMale']
                Default = static_hero['lobbyData']['IsHeroHiredByDefaultMale']

            RatingToFameTable = {}
            for rating in self.data['HeroRatingToFameLevel']['Ratings']['Item']:
                RatingToFameTable[rating['fameLevel']] = rating['rating']

            if Default:
                fame = RatingToFameTable[0]
            elif LevelRequire in RatingToFameTable:
                fame = RatingToFameTable[LevelRequire]
            else:
                fame = RatingToFameTable[-1]

            return fame

    def getConsumptionPoints(self, talent):
        staticTalent = self.getStaticTalent(talent)
        intRarity = getattr(ETalentRarity, staticTalent['rarity'])
        if intRarity != None:
            if intRarity < len(self.data['TalentConsumptionPointsToRarity']['Item']) and \
                    self.data['TalentConsumptionPointsToRarity']['Item'][intRarity]:
                points = self.data['TalentConsumptionPointsToRarity']['Item'][intRarity]
                if points:
                    return points
                else:
                    return 0
            else:
                return 0
        else:
            return 0

    def getResourcesForLevelUp(self, lvl):
        finalprice = StaticData.getPriceInterpolated(self.data['LevelToResources']['resourcesPerLevel'], lvl, None,
                                                     "resourcesPerLevel", None)
        return finalprice

    def getRank(self, rating):
        for rank, item in enumerate(self.cachedRates):
            if rating < item['rating']:
                return rank
        return rank + 1

    def getMinRating(self, maxRating, shiftOfMinRank):
        count = self.getRank(maxRating)
        try:
            minRating = self.cachedRates[count - shiftOfMinRank if count > shiftOfMinRank else 0]['rating']
        except KeyError:
            catch("getMinRating: key out of cachedRates list: maxRating %s, count %s, shiftOfMinRank %s", maxRating,
                  count, shiftOfMinRank)
            return 1
        return 1 if minRating == 0 else minRating

    def getMaxRating(self, maxRating):
        count = 0
        try:
            count = self.getRank(maxRating)
            return self.cachedRates[count]['rating']
        except KeyError:
            catch("getMaxRating: key out of cachedRates list: maxRating %s, count %s", maxRating, count)
            return self.cachedRates[-1]['rating']

    def getCapMaxRating(self):
        return self.cachedRates[-1]['rating']

    def findMinMaxRanks(self, ratings):
        if len(ratings) == 0:
            return 0, 0

        minRank = self.getRank(ratings[0])
        maxRank = self.getRank(ratings[0])

        for x in xrange(1, len(ratings)):
            maxRank = max(maxRank, self.getRank(ratings[x]))
            minRank = min(minRank, self.getRank(ratings[x]))
        return minRank, maxRank

    def getGoldLampRollContainer(self, lastPaymentDays):
        settings = self.data['LampEventsSettings']['Item'];
        count = len(settings)
        for i in xrange(count - 1, -1, -1):
            if lastPaymentDays >= settings[i]['lastPayDate']:
                if settings[i]['container']:
                    return settings[i]['container']['dbid']
                else:
                    return ""
        return ""

    def getMarketingEventRollItem(self, persistentId):
        if persistentId not in self.data['MarketingEventRollItem']:
            return None

        return self.data['MarketingEventRollItem'][persistentId]

    def getTrainingFwodSettings(self):
        commonRollSettings = self.data["SessionRollSettings"]
        return commonRollSettings["trainingFWODSettings"]

    def getSteamItem(self, config, itemId):
        currencyIndex = None
        category = None
        steamItem = None
        steamItems = None
        steamInfo = config.BuySteamGoldEventInfo
        if steamInfo:
            steamItems = steamInfo.SteamItems
            category = steamInfo.Category
            currencyIndex = steamInfo.CurrencyIndex
        if steamItems:
            steamItem = steamItems.get(itemId)
        return steamItem, category, currencyIndex

    def getAeriaItem(self, config, itemId):
        aeriaItem = None
        aeriaItems = None
        aeriaInfo = config.BuyAeriaGoldEventInfo
        if aeriaInfo:
            aeriaItems = aeriaInfo.AeriaItems
        if aeriaItems:
            aeriaItem = aeriaItems.get(itemId)
        return aeriaItem

    def getArcGamesItem(self, config, itemId):
        arcGamesItem = None
        arcGamesItems = None
        arcGamesInfo = config.BuyArcGamesGoldEventInfo
        if arcGamesInfo:
            arcGamesItems = arcGamesInfo.ArcGamesItems
        if arcGamesItems:
            arcGamesItem = arcGamesItems.get(itemId)
        return arcGamesItem

    def getZZimaItem(self, config, itemId):
        zzItem = None
        zzItems = None
        zzInfo = config.BuyZZimaGoldEventInfo
        if zzInfo:
            zzItems = zzInfo.ZZimaItems
        if zzItems:
            zzItem = zzItems.get(itemId)
        return zzItem

    def countryFlagExists(self, flagPersistentId):
        for item in self.data['DBUIData']['countryFlags']['Item']:
            if item['id'] == flagPersistentId:
                return True
        return False

    def getCustomFlagById(self, flagPersistentId):
        for item in self.data['DBUIData']['customFlags']['Item']:
            if item['id'] == flagPersistentId:
                return item
        for item in self.data['DBUIData']['adminFlags']['Item']:
            if item['id'] == flagPersistentId:
                return item
        return None

    def getDefaultFlagName(self):
        return self.data['DBUIData']['countryFlags']['Item'][0]['id']

    def getRatingToLooseLevel(self, lastPlayedTime):
        return None  # PF-104481
        ratingLossLevel = None
        # Проверим, какой штраф мы можем получить за то, что долго не были в бою
        for item in self.data['RatingDecreaseByTime']['ratings']['Item']:
            if lastPlayedTime > (int(time.time()) - item['minDaysFromLastBattle'] * 60 * 60 * 24):
                break
            ratingLossLevel = item
        return ratingLossLevel

    def getEResourceTypeName(self, eResourceType):
        if eResourceType == 0:
            return 'Silver'
        if eResourceType == 1:
            return 'Perl'
        if eResourceType == 2:
            return 'Resource1'
        if eResourceType == 3:
            return 'Resource2'
        if eResourceType == 4:
            return 'Resource3'
        return ''

    def getGuildShopItemById(self, item_id):
        return self.data['GuildShopItems'].get(item_id, None)

    def getGuildBufById(self, item_id):
        return self.data['GuildBuffsCollection'].get(item_id, None)

    def getGuildShopLevel(self, exp, hasUltimateShop):
        if hasUltimateShop:
            return len(self.data['GuildShopLevelToSuzerenExperience']['Item']) + 1
        lvl = 0
        if 'Item' in self.data['GuildShopLevelToSuzerenExperience']:
            for it in self.data['GuildShopLevelToSuzerenExperience']['Item']:
                if exp >= it['requiredExp']:
                    lvl += 1
                else:
                    break
        return lvl

    def getAmountByExperienceLevel(self, staticItem, level):
        amount = 0
        if 'Item' in staticItem['shopLevelToItemsAmount']:
            for item in staticItem['shopLevelToItemsAmount']['Item']:
                if int(item['shopLevel']) > level:
                    return amount
                else:
                    amount = int(item['buysPerTime'])
        return amount

    def isValidCycleForGuildBuf(self, cycle, buf):
        if cycle == None or cycle == -1:
            return True
        if 'cycle' not in buf:
            return False
        if int(buf['cycle']) == 0:
            return False
        if int(buf['cycle']) & 2 != 0 and cycle == 1:
            return True
        if int(buf['cycle']) & 1 != 0 and cycle == 0:
            return True
        if int(buf['cycle']) & 4 != 0 and cycle == 2:
            return True
        if int(buf['cycle']) & 8 != 0 and cycle == 3:
            return True
        return False

    def getRatingFilterBorders(self, id):
        ranges = self.data['GuildRatingRanges']['Item']
        if id >= len(ranges) - 1:
            return ranges[len(ranges) - 1], 0
        return ranges[id], ranges[id + 1]

    def getGuildVassalsTributeCoef(self):
        return self.data["ClanWarsData"]["guildVassalsTributeCoef"]

    def getGuildWarEventPointsCap(self):
        return self.data["ClanWarsData"]["guildWarEventData"]["pointsCap"]

    def getGuildWarEventDuration(self):
        return self.data["ClanWarsData"]["guildWarEventData"]["duration"]

    @staticmethod
    def getTutorialHeroId(map, sex):
        return map["heroesOverride"]["singlePlayer" + ("Female" if sex == ESex.FEMALE else "Male")]["ownHero"]["hero"][
            "persistentId"]

    @staticmethod
    def getCastleResourceTypeName(castleResourceType):
        if castleResourceType == CastleResources.Silver:
            return 'Silver'
        if castleResourceType == CastleResources.Perl:
            return 'Perl'
        if castleResourceType == CastleResources.RedPerl:
            return 'RedPerl'
        if castleResourceType == CastleResources.Resource1:
            return 'Resource1'
        if castleResourceType == CastleResources.Resource2:
            return 'Resource2'
        if castleResourceType == CastleResources.Resource3:
            return 'Resource3'
        if castleResourceType == CastleResources.Gold:
            return 'Gold'
        if castleResourceType == CastleResources.Shard:
            return 'Shard'
        return ''

    @staticmethod
    def getResourcePriceInGold(castleResourceType, resourceCount, SD):
        resourcesToConvert = ["Resource1", "Resource2", "Resource3", "Silver", "Perl"]
        gold = 0.0

        strResourceType = StaticData.getCastleResourceTypeName(castleResourceType)
        if strResourceType not in resourcesToConvert:
            warn("getResourcePriceInGold: can't convert resource %s to gold!", strResourceType)
            return gold

        resourcesInPack = SD['resourcesToGoldPrice'][strResourceType]['resourceCount']

        goldPer = SD['resourcesToGoldPrice'][strResourceType]['goldPrice']
        if SD['resourcesToGoldPrice'][strResourceType]['isPack']:
            packsInResource = resourceCount / resourcesInPack + resourceCount % resourcesInPack
            gold = packsInResource * goldPer
        else:
            gold = math.ceil(float(resourceCount) / resourcesInPack * goldPer)

        return int(gold)

    @staticmethod
    def getResourcesPriceInGold(resources, SD):

        gold = 0
        if resources.Resource1 > 0:
            gold += StaticData.getResourcePriceInGold(CastleResources.Resource1, resources.Resource1, SD)
        if resources.Resource2 > 0:
            gold += StaticData.getResourcePriceInGold(CastleResources.Resource2, resources.Resource2, SD)
        if resources.Resource3 > 0:
            gold += StaticData.getResourcePriceInGold(CastleResources.Resource3, resources.Resource3, SD)
        if resources.Silver > 0:
            gold += StaticData.getResourcePriceInGold(CastleResources.Silver, resources.Silver, SD)
        if resources.Perl > 0:
            gold += StaticData.getResourcePriceInGold(CastleResources.Perl, resources.Perl, SD)

        return gold

    def getRollWeightByRollTimes(self, rollGroup, rolls):
        weight = rollGroup['rerollTimesToDropProbabilties'][0]['newProbability']
        if len(rollGroup['rerollTimesToDropProbabilties']) > 0:
            for item in rollGroup['rerollTimesToDropProbabilties']['Item']:
                if item['rerollTime'] <= rolls:
                    weight = item['newProbability']
        return weight

    def getResourcesToPointsConversionByPriceType(self, priceType):
        for item in self.data['RerollShop']['resourcesToPointsTable']['Item']:
            if item['resource'] == 'Resource1' and priceType == 0:
                return item
            elif item['resource'] == 'Resource2' and priceType == 1:
                return item
            elif item['resource'] == 'Resource3' and priceType == 2:
                return item
            elif item['resource'] == 'Perl' and priceType == 3:
                return item
            elif item['resource'] == 'RedPerl' and priceType == 4:
                return item
            elif item['resource'] == 'Silver' and priceType == 5:
                return item
            elif item['resource'] == 'Gold' and priceType == 6:
                return item
        return None

    def talentCanBeSoulbound(self, talentCrc):
        staticTalent = self.getStaticTalentByTalentId(talentCrc)
        return fromETalentRarity(staticTalent["rarity"]) > fromETalentRarity(self.data["RaritiesWithoutSoulbound"]) or \
               staticTalent["rarity"] == "Class"

    ### SEASON section

    def getAllSeasons(self):
        if len(self.data['Seasons']['Item']):
            return self.data['Seasons']['Item']
        return None

    def findSeasonById(self, season_id):
        seasons = self.getAllSeasons()
        if not seasons:
            return None
        for one_season_info in seasons:
            if season_id == crc32(one_season_info["persistentId"]):
                return one_season_info
        return None

    def isSeasonCurrent__(self, season):
        if not season:
            return False
        timestamp = int(time.time())
        return season["startTime"] <= timestamp < season["stopTime"]

    def isSeasonCurrent(self, season_id):
        season = self.findSeasonById(season_id)
        if not season:
            return False
        return self.isSeasonCurrent__(season)

    def getCurrentSeason(self):
        seasons = self.getAllSeasons()
        if not seasons:
            return None
        for one_season_info in seasons:
            if self.isSeasonCurrent__(one_season_info):
                return one_season_info
        return None

    def getCurrentSeasonId(self):
        cur_season = self.getCurrentSeason()
        if not cur_season:
            return None
        return crc32(cur_season["persistentId"])

    ### LEAGUE section

    def getAllSeasonLeagues(self, season):
        if not season:
            return None
        if len(season['ParamLeagues']['Item']):
            return season['ParamLeagues']['Item']
        return None

    def getCurrentSeasonLegendLeague(self):
        cur_season = self.getCurrentSeason()
        if not cur_season:
            return None
        cur_season_leagues = self.getAllSeasonLeagues(cur_season)
        if not cur_season_leagues:
            return None
        cur_season_leagues.sort(key=lambda l: l['quality'])
        return cur_season_leagues[-1]

    def isTimeRecalcBestLeaguePlace(self):
        cur_season = self.getCurrentSeason()
        if not cur_season:
            return False
        return int(time.time()) >= int(cur_season["startTime"]) + 1209600

    def isLeagueReached(self, league, season_info):
        # проверяем место и рейтинг
        # league['minLeaderPlace'] > 0 - требует ли лига места (сейчас это характеризует только легендарную лигу)

        is_legend_league = league['minLeaderPlace'] > 0

        # попадаение в легендарную лигу проверяется по текущему месту и макс рейтингу,
        # в отстальные - просто по макс рейту за сезон

        return (not is_legend_league or (season_info.CurLeaguePlace > 0 and season_info.CurLeaguePlace <= league['minLeaderPlace'])) \
               and season_info.SeasonRating >= league['minRating']

    def getBestSeasonLeague__(self, season_info, season):
        if not season:
            return None
        leagues = self.getAllSeasonLeagues(season)
        best_league = None
        for league in leagues:
            if not best_league or league['quality'] > best_league['quality'] and self.isLeagueReached(league, season_info):
                best_league = league
        return best_league

    def getBestSeasonLeague(self, season_info):
        season = self.findSeasonById(season_info.SeasonId)
        if not season:
            return None
        return self.getBestSeasonLeague__(season_info, season)

    def getStaticLootboxes(self):
        return self.data['Lootboxes']

    def getStaticLootboxById(self, lootbox_id):
        lootboxes = self.data['Lootboxes']
        return lootboxes.get(lootbox_id)

    def getStaticTalentUpgradeEntities(self):
        return self.data['TalentUpgradeEntities']

    def getStaticTalentUpgradeEntityById(self, persistent_id):
        res = self.data['TalentUpgradeEntities']
        return res.get(persistent_id)
