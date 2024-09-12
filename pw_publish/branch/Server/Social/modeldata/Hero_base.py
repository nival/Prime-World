# -*- coding: utf-8 -*-
import sys, os, time, math
from binascii import crc32
import math

from base.helpers import info, warn, err, catch, debug, toint
from enums import *
from modeldata.validator import Validator
from modeldata import TalentSet, collects


class Hero_base:
    # ##################
    Hero_base_t1 = 0.0
    Hero_base_t2 = 0.0
    Hero_base_t3 = 0.0
    # ##################

    # дополнительные (server-side) сериализуемые поля
    def generateBaseDict(self):
        return dict(
        )

    def isHeroInActiveTavern(self, SD, md):
        if len(self.InBuildings) > 0:
            for constructionId in self.InBuildings.keys():
                construction = md.getConstructionByID(constructionId)
                if construction:
                    staticConstruction = SD.getStaticConstruction(construction)
                    if staticConstruction and staticConstruction['classType'] == "Tavern":
                        if construction.ProductionState != ProductionState.Idle:
                            return True
        return False

    def changeExperience(self, value, modelData, WS, acc, I):
        curLvl = acc.SD.getHeroExpLevel(self.Experience)

        if self.Experience + value <= 0:
            self.Experience = 0
        elif self.Experience + value >= acc.SD.getMaxHeroExp():
            self.Experience = acc.SD.getMaxHeroExp() - 1
        else:
            self.Experience += value

        earnedLvl = acc.SD.getHeroExpLevel(self.Experience)
        static_hero = acc.SD.data['Heroes'][self.PersistentId]
        fame = 0
        if static_hero and earnedLvl > curLvl:
            WS.updateGameDataToPersonServer(acc, self)

            statPoints = 0
            while not curLvl == earnedLvl:
                curLvl += 1

                # Выдаем статпоинты
                statPoints += acc.SD.getHeroStatPoints(curLvl)

                # Выдаем fame
                if curLvl >= 0 and curLvl < len(static_hero['lobbyData']['FameIncrement']['FameIncrement']['Item']):
                    fame += static_hero['lobbyData']['FameIncrement']['FameIncrement']['Item'][curLvl]
                else:
                    fame += static_hero['lobbyData']['FameIncrement']['FameIncrement']['Item'][-1]

                # Выдаем таланты
                modelData.giveTalentsForHeroLevelUp(self, static_hero, curLvl, acc, I)

            if statPoints:
                for tsId in self.TalentSets.keys():
                    self.changeStatPoints(statPoints, tsId)
            if fame:
                modelData.addFame(fame, acc, acc.SD, I.STATS)
            I.STATS.addHeroLevelChange(acc.auid, self.PersistentId, earnedLvl)
            modelData.addStatisticEvent(StatisticEventType.HERO_LEVEL, str(self.PersistentId), earnedLvl + 1, 0)

    def clearTalentSets(self, acc, srarity):
        for i in xrange(len(self.TalentSets)):
            for slot in self.TalentSets[i].Talents.keys():
                item = acc.model.getTalentByID(self.TalentSets[i].Talents.get(slot))
                if item:
                    staticTalent = acc.SD.getStaticTalent(item)
                    if staticTalent['rarity'] == srarity:
                        self.removeTalentFromTalentSet(i, item, slot)
                        #acc.model.UserInventory.add(item)
                        #self.TalentSets[i].Talents.remove(item)

    def setExperience(self, value, WS, acc, I):
        if self.Experience <= value:
            self.changeExperience(value - self.Experience, acc.model, WS, acc, I)
        else:
            curLvl = acc.SD.getHeroExpLevel(self.Experience)
            newLvl = acc.SD.getHeroExpLevel(value)

            self.Experience = value
            I.STATS.addHeroLevelChange(acc.auid, self.PersistentId, newLvl)

            if (newLvl - 1) < acc.getConfig().REQUIRED_LEVEL_FOR_EXCLUSIVE_TALENTS:
                self.clearTalentSets(acc, 'exclusive')

            if (newLvl - 1) < acc.getConfig().REQUIRED_LEVEL_FOR_OUTSTANDING_TALENTS:
                self.clearTalentSets(acc, 'outstanding')

            statPoints = 0
            while newLvl != curLvl:
                newLvl += 1
                statPoints += acc.SD.getHeroStatPoints(curLvl)

            for i in self.TalentSets.keys():

                # Удаляем статпоинты
                hasActiveStats = True
                while statPoints > 0 and hasActiveStats:
                    hasActiveStats = False
                    if self.TalentSets[i].Stats.Strength > 0:
                        self.TalentSets[i].Stats.Strength -= 1
                        hasActiveStats = True
                    elif self.TalentSets[i].Stats.Intellect > 0:
                        self.TalentSets[i].Stats.Intellect -= 1
                        statPoints -= 1
                        hasActiveStats = True
                    elif self.TalentSets[i].Stats.Agility > 0:
                        self.TalentSets[i].Stats.Agility -= 1
                        statPoints -= 1
                        hasActiveStats = True
                    elif self.TalentSets[i].Stats.Cunning > 0:
                        self.TalentSets[i].Stats.Cunning -= 1
                        statPoints -= 1
                        hasActiveStats = True
                    elif self.TalentSets[i].Stats.Fortitude > 0:
                        self.TalentSets[i].Stats.Fortitude -= 1
                        statPoints -= 1
                        hasActiveStats = True
                    elif self.TalentSets[i].Stats.Will > 0:
                        self.TalentSets[i].Stats.Will -= 1
                        statPoints -= 1
                        hasActiveStats = True
                    elif self.TalentSets[i].Stats.Health > 0:
                        self.TalentSets[i].Stats.Health -= 1
                        statPoints -= 1
                        hasActiveStats = True
                    elif self.TalentSets[i].Stats.Mana > 0:
                        self.TalentSets[i].Stats.Mana -= 1
                        statPoints -= 1
                        hasActiveStats = True

                    self.TalentSets[i].Stats.StatPoints -= statPoints

    # SEASON and LEAGUE section

    def findSeasonInfoById(self, acc, season_id):
        for seasonId in self.SeasonsInfo:
            season_info = acc.model.getSeasonInfoByID(seasonId)
            if season_info:
                if season_info.SeasonId == season_id:
                    return season_info
        return None

    def findOrCreateSeasonInfoById(self, acc, SD, season_id):
        season_info = self.findSeasonInfoById(acc, season_id)
        if season_info:
            return season_info
        season_info, _id = acc.model.newSeasonInfo()
        season_info.SeasonId = season_id
        self.SeasonsInfo.add(_id, season_info)
        return season_info

    def findOrCreateCurrentSeasonInfo(self, acc, SD):
        cur_season_id = SD.getCurrentSeasonId()
        if not cur_season_id:
            return None
        return self.findOrCreateSeasonInfoById(acc, SD, cur_season_id)

    def findCurrentSeasonInfo(self, acc):
        cur_season_id = acc.SD.getCurrentSeasonId()
        if not cur_season_id:
            return None
        return self.findSeasonInfoById(acc, cur_season_id)

    def updateSeasonRating(self, acc, SD, new_rating):
        season_info = self.findOrCreateCurrentSeasonInfo(acc, SD)
        if not season_info:
            return
        if season_info.SeasonRating < new_rating:
            season_info.SeasonRating = new_rating

    def updateLegendPlace(self, acc, SD, new_league_place):
        season_info = self.findOrCreateCurrentSeasonInfo(acc, SD)
        if not season_info:
            return
        season_info.CurLeaguePlace = new_league_place
        if acc.SD.isTimeRecalcBestLeaguePlace():
            if season_info.CurLeaguePlace < season_info.BestLeaguePlace or season_info.BestLeaguePlace == 0:
                season_info.BestLeaguePlace = season_info.CurLeaguePlace

    def updateLegendListPlaces(self, acc, SD, list_places):
        season_info = self.findOrCreateCurrentSeasonInfo(acc, SD)
        if not season_info:
            return
        del season_info.NearPlaces[:]
        for one_place in list_places:
            season_info.NearPlaces.append(one_place)
        debug("Hero - updateLegendListPlaces for hero = %d, near_places = %s" % (
            self.PersistentId, str(season_info.NearPlaces.keys())))

    # найти лучшую (по quality) достигнутую лигу
    def getBestLeagueFromPrevSeasons(self, acc, SD):
        best_league = None
        for seasonId in self.SeasonsInfo:
            season_info = acc.model.getSeasonInfoByID(seasonId)
            season = SD.findSeasonById(season_info.SeasonId)
            if season_info and season and not SD.isSeasonCurrent__(season):
                debug("getBestLeagueFromPrevSeasons: check leagues of season %s", season['persistentId'])
                best_season_league = SD.getBestSeasonLeague__(season_info, season)
                debug("getBestLeagueFromPrevSeasons: best league of season %s is %s",
                      season['persistentId'], best_season_league['nameLeague'] if best_season_league else "None")

                if best_season_league and (not best_league or best_season_league['quality'] > best_league['quality']):
                    best_league = best_season_league
                    debug("getBestLeagueFromPrevSeasons: current best league is %s", best_league['nameLeague'])

        debug("getBestLeagueFromPrevSeasons: result best league is %s", best_league['nameLeague'] if best_league else "None")
        return best_league

    #

    def _assignRatig(self, value, I, acc, onHire=False):
        if value <= 0:
            value = 0.0
        rank = acc.SD.getRank(value)
        if self.Rating != value:
            if not onHire:
                acc.model.addStatisticEvent(StatisticEventType.HERO_RATING, str(self.PersistentId), int(round(value)),
                                            int(round(value - self.Rating)))
            oldRank = acc.SD.getRank(self.Rating)
            if oldRank != rank:
                I.STATS.addHeroRankChange(acc.auid, self.PersistentId, acc.SD.getHeroExpLevel(self.Experience),
                                          rank, rank > oldRank)
        self.Rating = value
        return rank

    def changeRating(self, value, I, acc):
        rank = self._assignRatig(self.Rating + value, I, acc)

        if value > 0 and acc.model.LordInfo.Ratings.MaxRank < rank:
            myId = self.getID()
            for heroId in acc.model.Heroes:
                if heroId != myId:
                    h = acc.model.getHeroByID(heroId)
                    if h.Hired:
                        h.correctRating(acc.model, acc.getConfig(), I, acc)
            acc.model.LordInfo.Ratings.MaxRank = rank

        self.updateSeasonRating(acc, acc.SD, self.Rating)

        I.WS.updateGameDataToPersonServer(acc, self)

    # по еще более новому дизайну рейтинг считается по жуткой формуле https://confluence.nivalnetwork.com/display/dot/Rating+matchmaking
    def correctRating(self, MD, configdata, I, acc, onHire=False):
        topRating = configdata.HERO_START_RATING
        for heroId in MD.Heroes:
            h = MD.getHeroByID(heroId)
            if h.Hired:
                if topRating < h.Rating:
                    topRating = h.Rating

        coeffRating = configdata.HERO_START_RATING + configdata.HERO_COEFF_RATING * (
        topRating - configdata.HERO_START_RATING)
        if coeffRating > configdata.HERO_CUP_RATING:
            coeffRating = configdata.HERO_CUP_RATING

        if (topRating - configdata.HERO_START_RATING) < configdata.HERO_DELTA_RATING:
            coeffRating = configdata.HERO_START_RATING

        if self.Rating < coeffRating:
            self._assignRatig(coeffRating, I, acc, onHire)

    def changeStatPoints(self, value, tsId):
        if self.TalentSets[tsId].Stats.StatPoints + value <= 0:
            self.TalentSets[tsId].Stats.StatPoints = 0
        else:
            self.TalentSets[tsId].Stats.StatPoints += value

    def areStatPointsReset(self, tsId):
        isReseted = True
        isReseted = isReseted and self.TalentSets[tsId].Stats.Strength == 0
        isReseted = isReseted and self.TalentSets[tsId].Stats.Intellect == 0
        isReseted = isReseted and self.TalentSets[tsId].Stats.Agility == 0
        isReseted = isReseted and self.TalentSets[tsId].Stats.Cunning == 0
        isReseted = isReseted and self.TalentSets[tsId].Stats.Fortitude == 0
        isReseted = isReseted and self.TalentSets[tsId].Stats.Will == 0
        isReseted = isReseted and self.TalentSets[tsId].Stats.Health == 0
        isReseted = isReseted and self.TalentSets[tsId].Stats.Mana == 0

        isReseted = isReseted and self.TalentSets[tsId].GuildStats.Strength == 0
        isReseted = isReseted and self.TalentSets[tsId].GuildStats.Intellect == 0
        isReseted = isReseted and self.TalentSets[tsId].GuildStats.Agility == 0
        isReseted = isReseted and self.TalentSets[tsId].GuildStats.Cunning == 0
        isReseted = isReseted and self.TalentSets[tsId].GuildStats.Fortitude == 0
        isReseted = isReseted and self.TalentSets[tsId].GuildStats.Will == 0
        isReseted = isReseted and self.TalentSets[tsId].GuildStats.Health == 0
        isReseted = isReseted and self.TalentSets[tsId].GuildStats.Mana == 0
        return isReseted

    def resetHeroStatPoints(self, acc, tsId):
        if self.Hired == True:
            self.TalentSets[tsId].Stats.Strength = 0
            self.TalentSets[tsId].Stats.Intellect = 0
            self.TalentSets[tsId].Stats.Agility = 0
            self.TalentSets[tsId].Stats.Cunning = 0
            self.TalentSets[tsId].Stats.Fortitude = 0
            self.TalentSets[tsId].Stats.Will = 0
            self.TalentSets[tsId].Stats.Health = 0
            self.TalentSets[tsId].Stats.Mana = 0

            self.TalentSets[tsId].GuildStats.Strength = 0
            self.TalentSets[tsId].GuildStats.Intellect = 0
            self.TalentSets[tsId].GuildStats.Agility = 0
            self.TalentSets[tsId].GuildStats.Cunning = 0
            self.TalentSets[tsId].GuildStats.Fortitude = 0
            self.TalentSets[tsId].GuildStats.Will = 0
            self.TalentSets[tsId].GuildStats.Health = 0
            self.TalentSets[tsId].GuildStats.Mana = 0

            statpoints = 0
            guildStatpoints = 0
            for lvl in xrange(0, acc.SD.getHeroExpLevel(self.Experience) + 1):
                statpoints += acc.SD.getHeroStatPoints(lvl)

            guildLevel = acc.model.getGuildBuildingLevel(acc.SD)
            if guildLevel >= 0:
                for lvl in xrange(0, guildLevel + 1):
                    guildStatpoints += acc.SD.getGuildStatPointsBonus(lvl)

            self.TalentSets[tsId].Stats.StatPoints = statpoints
            self.TalentSets[tsId].GuildStats.StatPoints = guildStatpoints

    def removeHeroTalents(self, md, SD, tsId):
        if not self.Hired:
            for key in self.TalentSets[tsId].Talents.keys():
                talent = md.getTalentByID(self.TalentSets[tsId].Talents.get(key))
                if talent:
                    self.removeTalentFromTalentSet(tsId, talent, talent.id)
            return

        for key in self.TalentSets[tsId].Talents.keys():
            talent = md.getTalentByID(self.TalentSets[tsId].Talents.get(key))
            if talent:
                if talent.defaultForHero == 0 or talent.defaultForHero.PersistentId != self.PersistentId:

                    talent.Soulbound = 0
                    #debug("removeHeroTalents: add to userinventory %r", talent.generateJsonDict())
                self.removeTalentFromTalentSet(tsId, talent, talent.id)
        for key in self.TalentSets[tsId].ActionBar:
            self.TalentSets[tsId].ActionBar[key] = -1
            self.TalentSets[tsId].InstaCast.set(key, False)


        for key in md.UserInventory.keys():
            talent = md.getTalentByID(key)
            # staticTalent = SD.getStaticTalent(talent)

            #debug("removeHeroTalents: talent = %r", talent.generateJsonDict())
            # debug("removeHeroTalents: talent.defaultForHero = %r", talent.defaultForHero.generateJsonDict())
            try:
                #   info("removeHeroTalents: try getattr(talent.defaultForHero,'PersistentId'): %s",
                #       getattr(talent.defaultForHero, 'PersistentId'))

                if talent.Owner and talent.Owner.get() and \
                        not talent.ParentTalentSets and \
                        talent.defaultForHero != 0 and \
                        talent.defaultForHero.PersistentId != self.PersistentId:
                    continue
            except:
                #   debug("removeHeroTalents: try getattr(talent.defaultForHero,'PersistentId') failed")
                self.moveTalentFromTalentSetToLibrary(talent, talent.id)
                md.UserInventory.remove(talent)
            else:
                if talent.defaultForHero != 0 \
                        and talent.defaultForHero.get() is not None \
                        and talent.defaultForHero.PersistentId == self.PersistentId:
                    self.moveTalentFromTalentSetToLibrary(talent, talent.id)
                    md.UserInventory.remove(talent)

    def applyDefaultTalentSets(self, md, SD, config, unSoulbound):
        staticHero = SD.getStaticHero(self)

        # Не куплен - просто чистим весь талантсет, и заполняем новым
        if not self.Hired:
            for tsIdx in self.TalentSets.keys():
                for key in self.TalentSets[tsIdx].Talents.keys():
                    talent = md.getTalentByID(self.TalentSets[tsIdx].Talents.get(key))
                    if talent:
                        self.removeTalentFromTalentSet(tsIdx, talent, talent.id)
                self.createTalentSetFromDefault(md, staticHero, SD, tsIdx, config)
            return

        # Герой куплен, все сложнее...

        if unSoulbound:
            # убираем из тс и отвязываем их
            for tsIdx in self.TalentSets.keys():
                for key in self.TalentSets[tsIdx].Talents.keys():
                    talent = md.getTalentByID(self.TalentSets[tsIdx].Talents.get(key))
                    if talent:
                        if talent.defaultForHero == 0 or talent.defaultForHero.PersistentId != self.PersistentId:
                            talent.Soulbound = 0
                            self.removeTalentFromTalentSet(tsIdx, talent, talent.id)
            # отвязываем все soulbound таланты
            for talentId in md.UserInventory.keys():
                talent = md.getTalentByID(talentId)
                staticTalent = SD.getStaticTalent(talent)
                if talent.Soulbound.get() and talent.Soulbound.PersistentId == self.PersistentId and staticTalent['rarity'] != "Class":
                    talent.Soulbound = 0
            # обновляем версию
            self.Version = staticHero['lobbyData']['Version']

        # убираем неактуальный классовый таланты
        actualClassTalents = set()  # актуальные (из дефолтовых талантсетов) классовые таланты
        for ts in staticHero['talents']:
            for row in ts:
                for tal in row:
                    if tal and tal.rarity == 'Class':
                        actualClassTalents.add(tal.CRC32)
        # убираем неактуальный классовый таланты из тс
        for tsIdx in self.TalentSets.keys():
            for key in self.TalentSets[tsIdx].Talents.keys():
                talent = md.getTalentByID(self.TalentSets[tsIdx].Talents.get(key))
                if not talent:
                    continue
                staticTalent = SD.getStaticTalent(talent)
                if not staticTalent:
                    continue
                if staticTalent['rarity'] != 'Class' \
                        or talent.defaultForHero == 0 \
                        or talent.defaultForHero.PersistentId != self.PersistentId:
                    continue
                if talent.PersistentId not in actualClassTalents:
                    self.removeTalentFromTalentSet(tsIdx, talent, talent.id)
                    debug("applyDefaultTalentSets -- Remove talent %s for hero %s from ts %d", staticTalent['persistentId'], self.class_name, tsIdx)
        # убираем неактуальный классовый таланты из инвентаря
        for talentId in md.UserInventory.keys():
            talent = md.getTalentByID(talentId)
            if not talent:
                continue
            staticTalent = SD.getStaticTalent(talent)
            if not staticTalent:
                continue
            if staticTalent['rarity'] != 'Class' \
                    or talent.defaultForHero == 0 \
                    or talent.defaultForHero.PersistentId != self.PersistentId:
                continue
            if talent.PersistentId not in actualClassTalents:
                md.UserInventory.remove(talent)
                debug("applyDefaultTalentSets -- Remove talent %s for hero %s from inventory", staticTalent['persistentId'], self.class_name)

        # добавляем новые классовые таланты (в инвентарь)
        newClassTalents = set(actualClassTalents)
        for talentId in md.UserInventory.keys():
            talent = md.getTalentByID(talentId)
            if not talent:
                continue
            if talent.PersistentId in newClassTalents:
                newClassTalents.remove(talent.PersistentId)
                talent.defaultForHero = self
                if talent.canBeSoulbound(SD):
                    talent.Soulbound = self

                # validate talentsets soulbound
                for tsId, talentSet in self.TalentSets.iteritems():
                    if talent.id not in talentSet.Talents.values() \
                            and tsId in talent.ParentTalentSets.keys():
                        info("Missing {}('{}') tal in talentSet. Delete ref from parentTalentSet {}...".format(SD.getStaticTalent(talent)['persistentId'], self.class_name, tsId))
                        talent.ParentTalentSets.remove(tsId)

        for talentID in newClassTalents:
            createdTalent, talent_id = md.newTalent()
            createdTalent.__dict__["PersistentId"] = talentID
            createdTalent.__dict__["IsNew"] = True
            createdTalent.defaultForHero = self
            if createdTalent.canBeSoulbound(SD):
                createdTalent.Soulbound = self
            md.UserInventory.add(createdTalent)
            debug("applyDefaultTalentSets -- Create talent %s for hero %s", SD.getStaticTalent(createdTalent)['persistentId'], self.class_name)

        # проверяем строки талантов
        for tsIdx in self.TalentSets.keys():
            for key in self.TalentSets[tsIdx].Talents.keys():
                talent = md.getTalentByID(self.TalentSets[tsIdx].Talents.get(key))
                if not talent:
                    continue
                staticTalent = SD.getStaticTalent(talent)
                if not staticTalent:
                    continue
                talentLevel = int(math.ceil(toint(key) / 6.0)) - 1
                if staticTalent['minLevel'] != talentLevel:
                    self.removeTalentFromTalentSet(tsIdx, talent, talent.id)
                    debug("applyDefaultTalentSets -- Remove talent %s for hero %s from ts %d", staticTalent['persistentId'], self.class_name, tsIdx)

        # удаляем кривые таланты (с несуществующим StaticTalent)
        for talentId in md.UserInventory.keys():
            talent = md.getTalentByID(talentId)
            staticTalent = SD.getStaticTalent(talent)
            if staticTalent == "None" or not staticTalent:
                self.moveTalentFromTalentSetToLibrary(talent, talent.id)
                md.UserInventory.remove(talent)

        # обновляем crc тс
        for tsIdx in self.TalentSets.keys():
            self.TalentSets[tsIdx].TalentSetCrc = SD.getTalantSetCrc(staticHero, tsIdx, config)


    def tryPlaceInTS(self, talent, SD, talentInfo, md, tsId, acc_uid = 'unknown', acc_auid = 'unknown'):
        staticTalent = SD.getStaticTalentByTalentId(talent.PersistentId)
        if not staticTalent:
            return False

        # check for duplicates
        for pos, it in self.TalentSets[tsId].Talents.iteritems():
            iter_talent = md.getTalentByID(it)
            if iter_talent:
                if crc32(staticTalent['persistentId']) == iter_talent.PersistentId:
                    return False
            else:
                err("no talent in canPlaceInTS for user[uid = %s, auid = %s]: hero class name %s, talentInfo.row %s, talentInfo.pos %s, it = %s, persistent id = %s" %
                    (str(acc_uid), str(acc_auid), str(self.class_name),  str(talentInfo.row), str(talentInfo.pos), str(it), str(talent.PersistentId)))
                break

        realPos = talentInfo.row * 6 + talentInfo.pos + 1
        if not self.TalentSets[tsId].Talents.get(realPos):
            self.TalentSets[tsId].Talents.add(realPos, talent.id)
            talent.ParentTalentSets.add(tsId, self.TalentSets[tsId].id)
            talent.Owner =self
            return True

        for pos in xrange(staticTalent['minLevel'] * 6, staticTalent['minLevel'] * 6 + 6):
            if not self.TalentSets[tsId].Talents.get(pos + 1):
                self.TalentSets[tsId].Talents.add(pos + 1, talent.id)
                talent.ParentTalentSets.add(tsId, self.TalentSets[tsId].id)
                talent.Owner =self
                #if talent not in md.UserInventory.values():
                #    md.UserInventory.add(talent)
                return True

        # Если талант классовый, его надо насильно положить на нужную строчку.
        if staticTalent['rarity'] == "Class":
            # Сначала попробуем убрать его на дефолтную позицию
            if self.tryPlaceClassTalent(realPos, SD, talent, md, tsId):
                return True
            for pos in xrange(staticTalent['minLevel'] * 6, staticTalent['minLevel'] * 6 + 6):
                if self.tryPlaceClassTalent(pos + 1, SD, talent, md, tsId):
                    return True
        return False

    def tryPlaceClassTalent(self, pos, SD, talent, md, tsId):
        ts = self.TalentSets[tsId]
        currentTalent = md.getTalentByID(ts.Talents.get(pos))
        if currentTalent:
            currentStaticTalent = SD.getStaticTalentByTalentId(currentTalent.PersistentId)
            # Нельзя заменить один классовый талант на другие
            if currentStaticTalent['rarity'] == "Class":
                return False
            # Вернём текущий не классовый талант в инвентарь, чтобы не пропадал.
            self.removeTalentFromTalentSet(tsId, currentTalent, currentTalent.id)

        ts.Talents.add(pos, talent.id)
        talent.ParentTalentSets.add(tsId, ts.id)
        talent.Owner = self
        staticTalent = SD.getStaticTalentByTalentId(talent.PersistentId)
        if not staticTalent['type'] == "Passive" and not staticTalent['type'] == "Simple":
            actionBarIdx = self.GetFreeActionBarSlot(tsId)
            if actionBarIdx != -1:
                ts.ActionBar[actionBarIdx] = talent.getID()
                ts.InstaCast.set(actionBarIdx, False)
        return True

    def moveTalentsToInventory(self, md, tsId):
        for key in self.TalentSets[tsId].Talents.keys():
            talent = md.getTalentByID(self.TalentSets[tsId].Talents.get(key))
            if talent:
                #md.UserInventory.add(talent)
                self.removeTalentFromTalentSet(tsId, talent, key)
                #if talent not in md.UserInventory.values():
                #    md.UserInventory.add(talent)
            else:
                err("no talent in keeper: hero id %d, key %s, talent %s" % (self.id, key, talent))

    def deleteDefaultTalentSet(self, md):
        for talentId in md.UserInventory.keys():
            talent = md.UserInventory.get(talentId)
            if talent.defaultForHero != 0:
                if talent.defaultForHero.PersistentId == self.PersistentId and talent.Points == 0:
                    self.moveTalentFromTalentSetToLibrary(talent,talent.id)
                    md.UserInventory.remove(talent)

    # -----------------------------------------------------------------------------------------------
    # DAN: это практически самая затратная операция при создании MD; попробуем слегка оптимизировать
    def createDefaultTalentSet(self, config, md, SD, staticHero, talentSetId=0):
        hk = md.HeroesKeeper
        ts_dict = self.TalentSets[talentSetId].Talents.__dict__["dictionary"]
        ts = self.TalentSets[talentSetId]
        #ts_dict_reverse = self.TalentSets[talentSetId].Talents.__dict__["reverse"]
        for idx in xrange(0, 10):
            ts.ActionBar[idx] = -1
            ts.InstaCast.set(idx, False)
        refCounter = 0
        tsTalents = SD.getDefaultSetTalents(config, staticHero, talentSetId)
        for talRow in tsTalents: #staticHero['talents'][talentSetId]:
            for tal in talRow:
                if tal.name:
                    createdTalent, talent_id = md.newEmptyTalent()  # md.newTalent()
                    needSoulbound = SD.talentCanBeSoulbound(tal.CRC32)
                    createdTalent.init_create_new(tal.CRC32, self.id, md, hk, createdTalent.path,
                                                  md.GuildBankInfoKeeper, needSoulbound)
                    if needSoulbound:
                        refCounter += 3
                    else:
                        refCounter += 2
                    md.UserInventory.add(createdTalent)
                    if tal.ActionBarIdx != -1:
                        ts.ActionBar[tal.ActionBarIdx] = talent_id #TODO: разобраться с ActionBarIdx в таланте
                        ts.InstaCast.set(tal.ActionBarIdx, False)

                    #if createFlag:
                    position = tal.position
                    ts_dict[position] = createdTalent.id
                    #ts_dict_reverse[createdTalent.id] = position
                    createdTalent.ParentTalentSets.add(talentSetId, ts.id)
                    if createdTalent.id not in md.UserInventory.keys():
                        md.UserInventory.add(createdTalent)

        # раз уж мы хачим создание Ref-ов в талантах, нужно захачить и увеличение рефкаунтов у героя (с каждого таланта по максимум 2 ссылки на героя: Soulbound + defaultForHero)
        self.__dict__["refCounter"] += refCounter

        self.TalentSets[talentSetId].__dict__["TalentSetCrc"] = SD.getTalantSetCrc(staticHero,talentSetId,config)

    def findTalentInTalentSets(self, md, talentId):
        for i in range(len(self.TalentSets)):
            for slot, tid in self.TalentSets[i].Talents.iteritems():
                talent = md.getTalentByID(tid)
                if talent and talent.PersistentId == talentId:
                    return talent

        return None

    def createTalentSetFromDefault(self, md, staticHero, SD, talentSetIdx, config):
        ts = self.TalentSets[talentSetIdx]
        rowCount = 0
        defaultTS = SD.getDefaultTalentSetSD(config, staticHero, talentSetIdx)
        for row in defaultTS['levels']['Item']:
            itemCount = 1
            for pos in row['talents']['Item']:
                pos_talent = pos['talent']
                if 'persistentId' in pos_talent and pos_talent['persistentId']:
                    createdTalent = self.findTalentInTalentSets(md, pos_talent['crc32'])
                    if not createdTalent:
                        item_id = md.addNewTalent()
                        createdTalent = md.getTalentByID(item_id)
                        createdTalent.PersistentId = pos_talent['crc32']
                        # кладем ref в UserInventory
                        #md.UserInventory.add(createdTalent)
                        createdTalent.defaultForHero = self
                        createdTalent.Owner = self
                        if createdTalent.canBeSoulbound(SD):
                            createdTalent.Soulbound = self

                    position = rowCount * 6 + itemCount

                    ts.Talents.add(position, createdTalent.id)
                    createdTalent.ParentTalentSets.add(talentSetIdx, ts.id)

                itemCount += 1
            rowCount += 1
        ts.TalentSetCrc = defaultTS['crc32']  ## -- сами вычисления теперь при препроцессинге StaticData

    #def createOtherTalentSets(self, md, tsId, firstTalentSet, staticHero):
    #    destTS = self.TalentSets[tsId]
    #    for slot in firstTalentSet.Talents:
    #        talent = md.getTalentByID(firstTalentSet.Talents[slot])
    #        destTS.Talents.add(slot, talent.id)
    #        talent.ParentTalentSets.add(tsId, destTS.id)
    #    for idx in firstTalentSet.ActionBar:
    #        destTS.ActionBar.add(idx, firstTalentSet.ActionBar[idx])
    #    destTS.TalentSetCrc = staticHero['crc32']

    def setActionBarIndexes(self, staticData, tsId, md):
        hero = self
        for i in xrange(0, 10):
            hero.TalentSets[tsId].ActionBar.add(i, -1)

        for pos in hero.TalentSets[tsId].Talents:
            talent = md.getTalentByID(hero.TalentSets[tsId].Talents.get(pos))
            if talent:
                try:
                    StaticTalent = staticData.getStaticTalent(talent)
                    if StaticTalent:
                        if not StaticTalent['type'] == "Simple" and not StaticTalent['type'] == "Passive":
                            actionBarIndex = self.GetFreeActionBarSlot(tsId)
                            if actionBarIndex != -1:
                                hero.TalentSets[tsId].ActionBar[actionBarIndex] = talent.getID()
                                if (toint(StaticTalent['flags']) & 256) != 0 and actionBarIndex not in hero.TalentSets[tsId].InstaCast.keys(): #256 is InstaCastFlag. See - EAbilityFlags in GeneratedFromEditor.cs
                                    hero.TalentSets[tsId].InstaCast.set(actionBarIndex, True)
                except:
                    catch()

    def RoundForce(self, force):
        return float(int((force + 0.05) * 10) / 10.0)

    def CalcForce(self, md, WS, acc, tsId, skipStatisticEvent=False):
        force = acc.SD.getHeroForce(self, tsId, md, md.getStatPointsFromBuilding(acc.SD))
        new_force = self.RoundForce(force)
        current_force = self.TalentSets[tsId].Force
        delta_force = new_force - current_force
        if math.fabs(delta_force) > 0.1:
            if not skipStatisticEvent:
                md.addStatisticEvent(StatisticEventType.HERO_FORCE, str(self.PersistentId), int(new_force),
                                     int(delta_force))

            self.TalentSets[tsId].Force = new_force
            if tsId == self.ActiveTalentSet and WS:
                WS.updateGameDataToPersonServer(acc, self)

    def getReverseTalentIndex(self, tsId, md):
        # давайте-ка, не мудрствуя, тупо ребилдить список на каждом обращении (все равно обращения у нас только из ручного перекладывания талантов)
        t0 = time.clock()
        reverse = {}
        for slot_id, talId in self.TalentSets[tsId].Talents.iteritems():
            talent = md.getTalentByID(talId)
            if not talent:
                continue

            reverse[talent.PersistentId] = slot_id
        t1 = time.clock()
        if t1 - t0 > 0.000001:
            info("building reverse index PersistentId->slot for hero %s, time: %.6f" % (self.id, t1 - t0))
        return reverse

    def GetFreeActionBarSlot(self, tsId):
        for actionBarIdx, talId in self.TalentSets[tsId].ActionBar.iteritems():
            if talId == -1:
                return actionBarIdx
        return -1

    def isValidForceForMap(self, map, SD):
        return SD.isValidForceForMap(self.TalentSets[self.ActiveTalentSet].Force, map)

    def IsValidTalentSet(self, map, SD, tsId, md):
        staticMap = SD.getStaticMap(map)
        if staticMap and staticMap['mapType'] == "Tutorial":
            return True

        maxLevel = 0
        # TODO:WTF?! 0 - 37
        for i in xrange(0, 37):
            talent = md.getTalentByID(self.TalentSets[tsId].Talents.get(i))
            if talent:
                staticTalent = SD.getStaticTalent(talent)
                if staticTalent:
                    maxLevel += staticTalent['devPoints']
        return maxLevel >= 36

    def getPutStats(self, SD, tsId):
        statPoints = 0
        heroLevel = SD.getHeroExpLevel(self.Experience)
        curLvl = SD.getHeroExpLevel(0)
        for i in xrange(curLvl, heroLevel + 1):
            statPoints += SD.getHeroStatPoints(i)
        return statPoints - self.TalentSets[tsId].Stats.StatPoints

    def getHeroStatus(self, configdata):
        return HeroStatus.Normal

    def isTalentInTalentSet(self, talentId, tsId):
        for pos in self.TalentSets[tsId].Talents.keys():
            talent = self.TalentSets[tsId].Talents.get(pos)
            if talent == talentId:
                return True
        return False

    def removeTalentFromTalentSet(self, tsId, talent, talentId, isDelInActionBar=True, isDelFromParenTS=True):
        ts = self.TalentSets[tsId]
        for slotId in ts.Talents.keys():
            if ts.Talents[slotId] == talentId:
                ts.Talents.remove(slotId)
                break
        if isDelInActionBar:
            for actionBarIdx, talId in ts.ActionBar.iteritems():
                if talId == talentId:
                    ts.ActionBar[actionBarIdx] = -1
                    ts.InstaCast.set(actionBarIdx, False)
                    break
        if isDelFromParenTS:
            talent.ParentTalentSets.remove(tsId)
            #debug("removeTalentFromTalentSet -- Remove ts %s from parentsets of talent %s [parentTSs size=%d]", tsId, talentId, len(talent.ParentTalentSets))
        if not talent.ParentTalentSets:
            #debug("removeTalentFromTalentSet -- Reset talent owner [talentId = %d]", talentId)
            talent.Owner = 0

    def moveTalentFromTalentSetToLibrary(self, talent, talentId):
        for tsId in self.TalentSets.keys():
            ts = self.TalentSets[tsId]
            for slotId in ts.Talents.keys():
                if talentId == ts.Talents[slotId]:
                    ts.Talents.remove(slotId)
                    break
            for actionBarIdx, talId in ts.ActionBar.iteritems():
                if talId == talentId:
                    ts.ActionBar[actionBarIdx] = -1
                    ts.InstaCast.set(actionBarIdx, False)
                    break
        for tsId in talent.ParentTalentSets.keys():
            talent.ParentTalentSets.remove(tsId)

        if talent.Owner and talent.Owner.get():
            talent.Owner = 0
