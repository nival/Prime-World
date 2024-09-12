# -*- coding: utf-8 -*-

from base.helpers import *
from binascii import crc32
import CC
from modeldata import TalentSet, collects
class AddNewTalentSets:

    def addClassTalents(self, acc, md, tsId,  hero):
        source = hero.TalentSets[0]
        dest = hero.TalentSets[tsId]
        staticHero = acc.SD.getStaticHero(hero)
        #heroDefaultTalentSet = staticHero['talents'][tsId]
        heroDefaultTalentSet = acc.SD.getDefaultSetTalents(acc.getConfig(), staticHero, tsId)
        for talRow in heroDefaultTalentSet:
            for tal in talRow:
                if tal.rarity == "Class":
                    l = len(dest.Talents.keys())
                    talent = None
                    for tid in source.Talents.values():
                        talent = md.getTalentByID(tid)
                        if talent.PersistentId == tal.CRC32:
                            dest.Talents[tal.position] = tid
                            talent.ParentTalentSets.add(tsId, dest.id)
                            talent.Owner = hero
                            break
                    if len(dest.Talents.keys()) == l:
                        for tid in md.UserInventory:
                            talent = md.getTalentByID(tid)
                            if talent.PersistentId == tal.CRC32:
                                dest.Talents[tal.position] = tid
                                talent.ParentTalentSets.add(tsId, dest.id)
                                talent.Owner = hero
                                break
                    # проверка на дубликаты
                    if hero.Hired:
                        self.clearDublicates(hero, md, tal, talent, 1, staticHero)
                    else:
                        self.clearDublicates(hero, md, tal, talent, 0, staticHero)

    def clearDublicates(self, hero,md,tal,talent,count,staticHero):
        talents = filter(lambda t: t.PersistentId == tal.CRC32, md.UserInventory.values())
        if len(talents) > count:
            warn("Dublicates is found! hero={3} count={0} tal.CRC32={1} ids=[{2}]".format(len(talents), tal.CRC32, ",".join(str(x.id) for x in talents), staticHero["persistentId"]))
            for x in talents:
                if not hero.Hired:
                    md.UserInventory.remove(x)
                    warn("Dublicates was deleted for not hired hero! Deleted talent id={0} tal.CRC32={1}".format(x.id, tal.CRC32))
                elif hero.Hired and talent and x.id != talent.id:
                    md.UserInventory.remove(x)
                    warn("Dublicates was deleted for hired hero! Deleted talent id={0} tal.CRC32={1}".format(x.id, tal.CRC32))

    def updateStats(self, stats, dict):
        for k, v in dict.iteritems():
            if k in ("Strength", "Intellect","Agility", "Cunning", "Fortitude", "Will", "Health", "Mana", "StatPoints") and getattr(stats, k, None) is not None:
                setattr(stats, k, v)

    def initTalentSets(self, env, dict, acc, md, tsId, mdHero, tempCRC):
        self.addClassTalents(acc, md, tsId, mdHero)
        mdHero.TalentSets[tsId].TalentSetCrc = tempCRC
        mdHero.CalcForce( md, env.I.WS, acc, tsId )
        if "GuildStats" in dict["ModelData"]["HeroesKeeper"]["Keeper"][str(mdHero.id)]["Hero"]:
            self.updateStats(mdHero.TalentSets[tsId].GuildStats, dict["ModelData"]["HeroesKeeper"]["Keeper"][str(mdHero.id)]["Hero"]["GuildStats"]["HeroStats"])
        self.updateStats(mdHero.TalentSets[tsId].Stats, dict["ModelData"]["HeroesKeeper"]["Keeper"][str(mdHero.id)]["Hero"]["Stats"]["HeroStats"])
        mdHero.resetHeroStatPoints(acc, tsId)


    def convertModelData( self, env, acc, md, dict ):
        #debug("AddNewTalentSets dict: %r", dict)
        # Меняем таланты, которые на героях
        hiredHero = []
        for heroId in md.HeroesKeeper:
            mdHero = md.getHeroByID( heroId )
            # Если у героя уже есть талантсеты, значит скрипт отработал раньше
            if len(mdHero.TalentSets) > 0:
                return md, acc.db

            tempColl = dict["ModelData"]["HeroesKeeper"]["Keeper"][str(mdHero.id)]["Hero"]["TalentSet"]["Collection"]
            tempCRC = dict["ModelData"]["HeroesKeeper"]["Keeper"][str(mdHero.id)]["Hero"]["talentSetCrc"]
            for i in xrange(env.iDict.Config.getMainConfig().MAX_USER_TALENTSETS_COUNT):
                ts, _id = md.newTalentSet()
                mdHero.TalentSets.add(i, ts.id)

            talentSet = mdHero.TalentSets[0]
            talentSet.IsActiveTalentSet = True
            for key, t in tempColl.iteritems():
                talent = md.getTalentByID(t)
                talentSet.Talents.add( key2int(key), talent.id )
                talent.ParentTalentSets.add(0, talentSet.id)
                md.UserInventory.add(talent)

                talent.Owner = mdHero

            talentSet.TalentSetCrc = tempCRC

            if "GuildStats" in dict["ModelData"]["HeroesKeeper"]["Keeper"][str(mdHero.id)]["Hero"]:
                self.updateStats(talentSet.GuildStats, dict["ModelData"]["HeroesKeeper"]["Keeper"][str(mdHero.id)]["Hero"]["GuildStats"]["HeroStats"])
            self.updateStats(talentSet.Stats, dict["ModelData"]["HeroesKeeper"]["Keeper"][str(mdHero.id)]["Hero"]["Stats"]["HeroStats"])
            mdHero.CalcForce( md, env.I.WS, acc, 0 )

            #поставим классовые таланты в другие билды
            self.initTalentSets(env, dict, acc, md, 1, mdHero, tempCRC)
            self.initTalentSets(env, dict, acc, md, 2, mdHero, tempCRC)

            mdHero.ActiveTalentSet = 0
            hiredHero.append(mdHero.PersistentId)

        for pid, staticHero in acc.SD.data['Heroes'].iteritems():
            if pid not in hiredHero:
                #for heroDefaultTalentSet in staticHero['talents']:
                for i in xrange(acc.getConfig().MAX_USER_TALENTSETS_COUNT):
                    heroDefaultTalentSet = acc.SD.getDefaultSetTalents(acc.getConfig(), staticHero, i)
                    for talRow in heroDefaultTalentSet:
                        for tal in talRow:
                            if tal.rarity == "Class":
                                talents = filter(lambda t: t.PersistentId == tal.CRC32 and t.defaultForHero not in md.Heroes, md.UserInventory.values())
                                if len(talents) >0:
                                    warn("Dublicates for not hired hero is found! hero={3} count={0} tal.CRC32={1} ids=[{2}]".format(len(talents), tal.CRC32, ",".join(str(x.id) for x in talents), staticHero["persistentId"]))
                                    for x in talents:
                                        md.UserInventory.remove(x)
                                        warn("Dublicates was deleted for not hired hero! Deleted talent id={0} tal.CRC32={1}".format(x.id, tal.CRC32))


        return md, acc.db