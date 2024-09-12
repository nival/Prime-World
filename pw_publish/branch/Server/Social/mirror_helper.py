# -*- coding: utf8 -*-
from base.helpers import *
from enums.HeroStat import HeroStat


KEYS = tuple([arg for arg in dir(HeroStat) if not arg.startswith('_')])

class MirrorDaemonHelper():
    """1. Рассчитывет полные статы героя при миррорнге данных игрока в pw_stat"""
    def __init__(self, items_keeper, constructions_keeper, pocket):
        self.items_keeper = items_keeper
        self.constructions_keeper = constructions_keeper
        self.pocket = pocket

    def calculateFullStats(self, hero_dict, talentset_dict, SD):
        stats = self.getHeroMaxLevelStats(hero_dict, talentset_dict, SD)
        stats = dict(((k, stats.get(SD.getEditorStatName(k), 0)) for k in KEYS))
        return stats

    def getHeroMaxLevelStat(self, hero_dict, talentset_dict, stat, SD):
        stats = self.getHeroMaxLevelStats(hero_dict, talentset_dict, SD)
        return stats.get(stat, 0)


    def getHeroMaxLevelStats(self, hero_dict, talentset_dict, SD):
        try:
            staticHero = SD.getStaticHeroByClassId(hero_dict.get("PersistentId", 0))
            if not staticHero:
                return {}
            level = 36

            # collecting static stats for easy access in calculations
            heroStaticStats = {}
            for sdStat in staticHero['stats']['stats']['Item']:
                if sdStat:
                    statid = sdStat['statId']
                    heroStaticStats[statid] = sdStat

            # filling with all stats and zeroes
            heroStats = {}
            for f in KEYS:
                heroStats[SD.getEditorStatName(f)] = 0

            #hero_stats_path = "Stats/HeroStats"
            #hero_stats = pathFind(talentset_dict, hero_stats_path, force_int_keys=False)
            hero_stats = talentset_dict["Stats"]["HeroStats"]
            #hero_guild_stats_path = "GuildStats/HeroStats"
            #hero_guild_stats = pathFind(talentset_dict, hero_guild_stats_path, force_int_keys=False)
            hero_guild_stats = talentset_dict["GuildStats"]["HeroStats"]
            k = level / 36
            for cStat in heroStats:
                codeStat = SD.getCodeStatName(cStat)
                staticStat = heroStaticStats.get(cStat)
                calc = 0
                if staticStat:
                    calc = staticStat['calcValue']

                # static stats + hero stats + guild stats
                tryInc( heroStats, cStat, calc + k * (hero_stats.get(codeStat, 0) + hero_guild_stats.get(codeStat, 0)))
                # buildings stats
                heroStats[cStat] += self.getBonusFromBuilding(cStat, SD)

            totalBudget = 0
            #hero_talentset_path = "Talents/SimpleDict"
            #hero_talentset = pathFind(talentset_dict, hero_talentset_path, force_int_keys=False)
            hero_talentset = talentset_dict["Talents"]["SimpleDict"]
            # base talents stats
            if hero_talentset and isinstance(hero_talentset, dict):
                for i in xrange(1, 37):
                    si = str(i)
                    if si in hero_talentset:
                        #talent_path = "%d/Talent" % hero_talentset[si]
                        #talent_dict = pathFind(self.items_keeper, talent_path, force_int_keys=False)
                        _talent_dict = self.items_keeper.get(str(hero_talentset[si]), None)
                        if _talent_dict:
                            talent_dict = _talent_dict["Talent"]
                            staticTalent = SD.getStaticTalentByTalentId(talent_dict.get("PersistentId", 0))
                            if staticTalent:
                                talentLevel = SD.getTalentLevelByPoints(talent_dict.get("Points", 0), staticTalent)
                                totalBudget += staticTalent['forceBonus']
                                talentStats = staticTalent['talentStats']
                                if talentStats:
                                    for talentStat in talentStats['Item']:
                                        if 0 <= talentLevel < len(talentStat['values']['Item']):
                                            tryInc(heroStats, talentStat['stat'], tofloat(talentStat['values']['Item'][talentLevel]))
            else:
                return {}

            # stats points from force
            statsBonusBudget = SD.ForceParameters['defaultStatBonus']
            if talentset_dict.get("Force", 0) > SD.ForceParameters['defaultBaseForce']:
                statsBonusBudget += (talentset_dict.get("Force", 0) - SD.ForceParameters['defaultBaseForce']) * SD.ForceParameters['statBonusByForce']

            forceCoef = (statsBonusBudget * totalBudget / staticHero['totalStatsBudget'] / 6.0 / 100.0) + level

            for cStat in heroStats:
                staticStat = heroStaticStats.get( cStat )
                if staticStat:
                    tryInc( heroStats, cStat, staticStat['calcIncrement'] * forceCoef )

            # variative stat mods (stat modsstaticStat['calcIncrement'] * forceCoef depending on current hero stats)
            statModifiersAdditions = {}
            for i in xrange(1, 37):
                si = str(i)
                if si in hero_talentset:
                    #talent_path = "%d/Talent" % hero_talentset[str(i)]
                    #talent_dict = pathFind(self.items_keeper, talent_path, force_int_keys=False)
                    _talent_dict = self.items_keeper.get(str(hero_talentset[str(si)]), None)
                    if _talent_dict:
                        talent_dict = _talent_dict["Talent"]
                        staticTalent = SD.getStaticTalentByTalentId(talent_dict.get("PersistentId", 0))
                        if staticTalent:
                            talentLevel = SD.getTalentLevelByPoints(talent_dict.get("Points", 0), staticTalent)
                            # info( "talent id=%r, level=%r" % ( staticTalent['persistentId'], talentLevel ) )

                            # in variative stats looking for max stat in hero
                            maxf = 'variativeMaxTalentStats'
                            variativeMaxTalentStats = staticTalent[maxf]
                            variativeMaxByName = {}

                            if variativeMaxTalentStats:
                                for talentStat in variativeMaxTalentStats['Item']:
                                    if talentStat.get('addValueName'):
                                        if talentStat['addValueName'] not in variativeMaxByName:
                                            variativeMaxByName[talentStat['addValueName']] = []

                                        variativeMaxByName[talentStat['addValueName']].append(talentStat)

                                for talentStatsByValueName in variativeMaxByName.itervalues():
                                    found = False
                                    maxStat = None
                                    currentMaxValue = float('-inf')
                                    for talentStat in talentStatsByValueName:
                                        if heroStats[talentStat['stat']] >= currentMaxValue:
                                            found = True
                                            currentMaxValue = heroStats[talentStat['stat']]
                                            maxStat = talentStat

                                    if found:
                                        cStat = maxStat['stat']
                                        if cStat not in statModifiersAdditions:
                                            statModifiersAdditions[cStat] = 0

                                        if 0 <= talentLevel < len( maxStat['values']['Item'] ):
                                            statModifiersAdditions[cStat] += tofloat(maxStat['values']['Item'][talentLevel])
                                        else:
                                            warn("Attempting to get variative stat modifier for level %r but it is not exist in static data. Talent %r",
                                                  talentLevel, staticTalent["persistentId"])

                            # in variative stats looking for min stat in hero
                            minf = 'variativeMinTalentStats'
                            variativeMinTalentStats = staticTalent[minf]
                            variativeMinByName = {}

                            if variativeMinTalentStats:
                                for talentStat in variativeMinTalentStats['Item']:
                                    if talentStat.get('addValueName'):
                                        if talentStat['addValueName'] not in variativeMinByName:
                                            variativeMinByName[talentStat['addValueName']] = []

                                        variativeMinByName[talentStat['addValueName']].append(talentStat)

                                for talentStatsByValueName in variativeMinByName.itervalues():
                                    minStat = None
                                    found = False
                                    currentMinValue = float('+inf')
                                    for talentStat in talentStatsByValueName:
                                        if heroStats[talentStat['stat']] <= currentMinValue:
                                            found = True
                                            currentMinValue = heroStats[talentStat['stat']]
                                            minStat = talentStat
                                            break

                                    if found:
                                        cStat = minStat['stat']
                                        if cStat not in statModifiersAdditions:
                                            statModifiersAdditions[cStat] = 0

                                        if 0 <= talentLevel < len( minStat['values']['Item'] ):
                                            statModifiersAdditions[cStat] += tofloat(minStat['values']['Item'][talentLevel])
                                        else:
                                            warn( "Attempting to get variative stat modifier for level %r but it is not exist in static data. Talent %r",
                                                  talentLevel, staticTalent["persistentId"])

            for smAdd in statModifiersAdditions:
                tryInc( heroStats, smAdd, statModifiersAdditions[smAdd] )
                #info("addvalue %r stat %r", statModifiersAdditions[smAdd], smAdd)

            return heroStats
        except:
            catch("getHeroMaxLevelStat")
            return {}


    def getBonusFromBuilding(self, stat, SD):
        result = 0.0
        for buildingId, construction in self.constructions_keeper.iteritems():
            if construction and isinstance(construction, dict):
                building = construction.get("Construction")
                staticBuilding = SD.getStaticConstructionByPersistentId(building.get("PersistentId", 0))
                if staticBuilding:
                    if staticBuilding['classType'] == "HeroesBuilding" and stat in staticBuilding['buffStats']['Item']:
                        result += SD.getFloatInterpolated(staticBuilding['HeroesBuildingLevels'], building.get("Level", 0),
                                                          None, "statBufValue", 0) * SD.getStatPointsMultiplyer(stat)
        return result