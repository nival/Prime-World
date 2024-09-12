#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from base.helpers import *
from binascii import crc32

class BonusType:
    Session = 0
    Roll = 1
    Pass = 2

class BaseBonusProcessor:
    def __init__(self, WS):
        self.WS = WS
        self.current_hero = None

    def process(self, acc, hero_crc32_id, map_dbid, bonus_dict):
        heroes_dict = {}
        if "heroes" in bonus_dict and type(bonus_dict["heroes"]) == dict:
            heroes_dict = bonus_dict['heroes']['Item']

        availableHeroes = [crc32(hero['persistentId']) for hero in heroes_dict]
        if availableHeroes and hero_crc32_id not in availableHeroes:
            return False

        if map_dbid:
            maps_dict = {}
            if "gameSettings" in bonus_dict \
                    and "maps" in bonus_dict["gameSettings"] \
                    and type(bonus_dict["gameSettings"]["maps"]) == dict:
                maps_dict = bonus_dict['gameSettings']["maps"]['Item']

            availableMaps = [map['dbid'] for map in maps_dict]
            debug("bonus allowed on maps %s", availableMaps)
            if availableMaps and map_dbid not in availableMaps:
                return False

        self.current_hero, hero_id = acc.model.findHeroByCrc32(hero_crc32_id)
        if self.current_hero is None:
            return False

        return True

class StatBonusProcessor(BaseBonusProcessor):
    def process(self, acc, hero_crc32_id, map_dbid, bonus_dict):

        if not BaseBonusProcessor.process(self, acc, hero_crc32_id, map_dbid, bonus_dict):
            return None

        if isinstance(bonus_dict["statBonuses"], str):
            statBonuses = []
        else:
            statBonuses = bonus_dict["statBonuses"].get("Item") or []

        statDict = {}

        if isinstance(bonus_dict["excludedBufs"], str):
            excludedBuffs = []
        else:
            excludedBuffs =  bonus_dict["excludedBufs"].get("Item") or []

        for bonus in statBonuses:
            stat = bonus['statType']
            statDict[stat] = bonus['modifiers']
            statDict[stat]['multiplicativeValue'] = float(statDict[stat]['multiplicativeValue'])
            statDict[stat]['additiveValue'] = float(statDict[stat]['additiveValue'])

            if excludedBuffs:
                maxStatVal = 0
                maxStat = ''
                heroStats = {}
                for ex_stat in excludedBuffs:
                    heroStats[ex_stat] = acc.model.getHeroMaxLevelStat( self.current_hero, ex_stat, acc.SD )
                    if heroStats[ex_stat] > maxStatVal:
                        maxStat = ex_stat
                        maxStatVal = heroStats[ex_stat]

                for ex_stat in excludedBuffs:
                    if ex_stat is not maxStat:
                        statDict.pop(ex_stat, None)

        return ClassDict(type=BonusType.Session, toggle=bonus_dict['toggle'], statBonuses=statDict)


class SessionAwardBonusProcessor(BaseBonusProcessor):
    def process( self, acc, hero_crc32_id, map_dbid, bonus_dict ):
        if not BaseBonusProcessor.process(self, acc, hero_crc32_id, map_dbid, bonus_dict):
            return None

        return ClassDict(type=BonusType.Roll, dbid=bonus_dict['dbid'])

class GuildWarEventPassBonusProcessor(BaseBonusProcessor):
    def process( self, acc, hero_crc32_id, map_dbid, bonus_dict ):
        if not BaseBonusProcessor.process(self, acc, hero_crc32_id, map_dbid, bonus_dict):
            return None

        return ClassDict(type=BonusType.Pass, dbid=bonus_dict['dbid'])

class GuildBonusProcessor:
    processors = {}
    def __init__(self, WS):
        self.WS = WS
        self.addProcessors(StatBonusProcessor, 'StatChangeBonus')
        self.addProcessors(SessionAwardBonusProcessor, 'SessionResourceBonus')
        self.addProcessors(SessionAwardBonusProcessor, 'ClanPointsBonus')
        self.addProcessors(SessionAwardBonusProcessor, 'PlayerPointsBonus')
        self.addProcessors(SessionAwardBonusProcessor, 'SessionTalentsBonus')
        self.addProcessors(SessionAwardBonusProcessor, 'HeroExperienceBonus')
        self.addProcessors(SessionAwardBonusProcessor, 'HeroEnergyBonus')
        self.addProcessors(GuildWarEventPassBonusProcessor, 'GuildWarEventPass')

    def addProcessors( self, bonusParser, bonusClass ):
        self.processors[bonusClass] = bonusParser(self.WS)

    def __process( self, acc, hero_crc32_id, map_dbid, bonus ):
        bonusType = bonus['classType']
        if bonusType in self.processors:
            return self.processors[bonusType].process( acc, hero_crc32_id, map_dbid, bonus )
        else:
            info("no suitable processor for bonus type %s", bonusType)
            return None



    @staticmethod
    def getModifiedValue(base_value, modifiers):
        return base_value*modifiers['multiplicativeValue'] + modifiers['additiveValue']

    def getModifiersFromGuildBuffs(self, acc, hero_crc32_id, map_dbid, test_buffs=None):
        desc_dict = {}

        desc_dict['at36level'] = []
        desc_dict['atStart'] = []
        desc_dict['roll'] = []
        desc_dict['pass'] = []

        if not acc.getConfig().GUILD_WARS_ENABLED:
            return desc_dict

        # мы надеемся на флаг IsEnabled, если он выставлен, значи большая часть учсловий по бафам обработанна

        staticBuffs = []
        if test_buffs:
            buffs_ids = [crc32(test_buff) for test_buff in test_buffs]
            for buffId in buffs_ids:
                staticBuffs.append(acc.SD.getGuildBufById(buffId))
        else:
            for buffId in acc.model.GuildBufs.keys():
                buff = acc.model.getGuildBufByID(buffId)
                if buff is None:
                    continue

                if not buff.IsEnabled:
                    continue

                staticBuff = acc.SD.getGuildBufById(buff.PersistentId)
                if staticBuff:
                    staticBuffs.append(staticBuff)
                else:
                    warn("can't find buff %r in static data", buff.PersistentId)



        for staticBuff in staticBuffs:
            buffPersistentId = staticBuff["persistentId"]
            bonuses = staticBuff["bonuses"]["Item"]
            for bonus in bonuses:
                res = self.__process(acc, hero_crc32_id, map_dbid, bonus)
                if res is None:
                    continue

                if res.type == BonusType.Session:
                    if res.toggle:
                        sub_dict = desc_dict['at36level'] if res.toggle == 'By36Level' else desc_dict['atStart']
                        for stat in res.statBonuses:
                            #подцепим тут bufId для статистики
                            res.statBonuses[stat]['buffPersistentId'] = buffPersistentId

                            sub_dict.append((stat, res.statBonuses[stat]))
                elif res.type == BonusType.Roll:
                    desc_dict['roll'].append(res.dbid)
                elif res.type == BonusType.Pass:
                    desc_dict['pass'].append(buffPersistentId)

        debug( "active session and roll buffs %r for hero %r", desc_dict, hero_crc32_id)
        return desc_dict