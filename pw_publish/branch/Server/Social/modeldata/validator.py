#!/usr/bin/env python
# -*- coding: utf-8 -*-
# (C) Vadim Petrov 2011, Nival

from base.helpers import *

import pwconst  # специфические константы PW (кол-во талантов в строке TalentSet и т.п.)


class Validator:
    # подходит ли данный item данному герою, в данный номер слота TalentSet?
    @staticmethod
    def checkItemFit(acc, hero, item, slot, SD, check_duplicates=0, hero_talents=None, any_hero_talents=None, tsId=0):
        ##log("checkItemFit: hero %s, item %s, slot %d" % ( str(hero), str(item), slot ))

        talent_id = item.PersistentId
        response_error = ""

        item_row = 1 + ((slot - 1) / pwconst._MAX_TALENTS_PER_ROW)

        if item_row > 0 and item_row <= pwconst._MAX_ROWS:
            if item and item.PersistentId:
                if hero and hero.PersistentId:
                    # смотрим класс героя
                    hero_talents = hero_talents or acc.model.getHeroClassTalents(acc.getConfig(), hero.PersistentId, SD)
                    staticTalent = SD.getStaticTalent(item)

                    if staticTalent['rarity'] == "Class":
                        if staticTalent['persistentId'] not in hero_talents:
                            response_error = "wrong class talent for hero"
                            return False, response_error

                    talent_row = staticTalent['minLevel'] + 1
                    if talent_row:
                        if talent_row == item_row:
                            ## -- а вот дубликаты талантов вставлять нельзя; если такой талант уже есть в TS, фейлимся
                            conflictingTalents = [talent_id]
                            if staticTalent['conflictingTalents'] and staticTalent['conflictingTalents']['Item'] \
                                    and len(staticTalent['conflictingTalents']['Item']) > 0:
                                for talent in staticTalent['conflictingTalents']['Item']:
                                    conflictingTalents.append(talent['persistentId'])


                            hasDublicatesOrConflictingTalents = Validator.findTalent(acc, hero.id, conflictingTalents, except_slot=slot, tsId=tsId)
                            if (not check_duplicates) or (not hasDublicatesOrConflictingTalents):
                                ##log("checkItemFit OK: talent_id %d" % ( talent_id ))
                                curLvl = SD.getHeroExpLevel(hero.Experience)
                                if (staticTalent['rarity'] == 'exclusive' and (
                                    curLvl + 1) < acc.getConfig().REQUIRED_LEVEL_FOR_EXCLUSIVE_TALENTS) \
                                        or (staticTalent['rarity'] == 'outstanding' and (
                                            curLvl + 1) < acc.getConfig().REQUIRED_LEVEL_FOR_OUTSTANDING_TALENTS):
                                    response_error = "this talent doesn't suit for hero with this level %d ! talent_id %d for hero %s" % (
                                    curLvl + 1, talent_id, hero.id)
                                else:
                                    return talent_id, response_error
                            else:
                                response_error = "duplicate talent! already have talent_id %d for hero %s" % (talent_id, hero.id)
                        else:
                            response_error = "bad talent row: talent_id %d should be (row=%d) for hero_id %d (%s); item %s moves to slot %d (row=%d)" \
                                             % (talent_id, talent_row, hero.id, hero.class_name, str(item), slot,
                                                item_row)
                    else:
                        response_error = "bad hero talents"
                else:
                    response_error = "bad hero or hero_class_id"
            else:
                response_error = "bad item or PersistentId"
        else:
            response_error = "bad TalentSet slot %d (row %d)" % (slot, item_row)

        ##warn("checkItemFit FAIL: %s" % ( response_error ))
        return False, response_error

    # ----------------------------------------------------------------------------------------------------------------------
    # есть ли в указанном talent_set хоть один талант из указанного списка talent_list[]?
    #  ( слот с индексом except_slot при проверке пропускаем )
    @staticmethod
    def findTalent(acc, hero_id, talent_list, except_slot=0, tsId=0):
        if talent_list:
            hero = acc.model.getHeroByID(hero_id)
            if hero:
                # нужен кросс-индекс PersistentId->слот; если его нет, давайте построим
                reverse = hero.getReverseTalentIndex(tsId, acc.model)
                for talent_id in talent_list:
                    slot = reverse.get(talent_id)
                    if slot and slot != except_slot:
                        ##log( "findTalent slot found: %s" % str(slot) )
                        return True

    ##--------------------------------------------------------------------------------------------------------
    ## проверяем списки талантов на героях
    ##  если где-то талант не соответствует герою или ряду TalentSet, нужно выкинуть его в общий инвентарь
    @staticmethod
    def validateTalentSets(acc, server_version, SD, tsId):
        acc.data.ts_validation_msgs = []
        t0 = time.time()

        for hero_id, hero in acc.model.HeroesKeeper.iteritems():
            ##log( "- validating TS: hero_id %s, hero %s (%s)" % ( str(hero_id), str(hero), hero.class_name ))
            hero_talents = acc.model.getHeroClassTalents(acc.getConfig(), hero.PersistentId, SD)

            for slot in hero.TalentSets[tsId].Talents.keys():
                ##log( "-- validating TS: slot %d" % ( slot ))
                item = acc.model.getTalentByID(hero.TalentSets[tsId].Talents.get(slot))
                if item:
                    item_id = item.getID()

                    talent_id, response_error = Validator.checkItemFit(acc, hero, item, slot, hero_talents=hero_talents,
                                                                       tsId=tsId)

                    if not talent_id:
                        ##warn( "TS validation: checkItemFit(item %s, slot %d) == %s (error %s)" % ( str(item), slot, str(talent_id), response_error ))
                        # надо прикучить сообщение об ошибке
                        acc.data.ts_validation_msgs.append(
                            {"error": response_error, "hero_id": hero_id, "item_id": item_id})

                        # добавляем ref в UserInventory, удаляем ref из TalentSet
                        # acc.model.UserInventory.add( item )
                        # hero.TalentSets[tsId].Talents.remove( item )
                        hero.removeTalentFromTalentSet(tsId, item, item_id)

                        ### апдейтим изменения в кросс-индексе (данного таланта больше нет у данного героя)
                        ##subDelete( acc.data.index, ("HeroTalents", hero_id, talent_id) )

        t1 = time.time() - t0
        info("validation time: %.3f, ts_validation_msgs: " % (t1) + pretty(acc.data.ts_validation_msgs))

        # проверим версию Model Data -- и, возможно, добавим что-то, чего не хватает в устаревших версиях
        hi, med, low = "0", "0", "0"
        try:
            hi, med, low = acc.model.create_version.split(".")[:3]
        except:
            pass

    @staticmethod
    def getMissingClassTalents(MD, SD, config):
        haveClassTalents = set([])
        allClassTalents = set([])
        for heroId in MD.Heroes:
            hero = MD.getHeroByID(heroId)
            if hero.Hired:
                for tsId in hero.TalentSets.keys():
                    for key in hero.TalentSets[tsId].Talents.keys():
                        talent = MD.getTalentByID(hero.TalentSets[tsId].Talents.get(key))
                        if talent:
                            staticTalent = SD.getStaticTalent(talent)
                            if staticTalent and staticTalent['rarity'] == "Class":
                                if talent.PersistentId not in haveClassTalents:
                                    haveClassTalents.add(talent.PersistentId)

                staticHero = SD.getStaticHero(hero)
                #for dts in staticHero['talents']:
                for i in xrange(config.MAX_USER_TALENTSETS_COUNT):
                    dts = SD.getDefaultSetTalents(config, staticHero, i)
                    for talRow in dts:
                        for tal in talRow:
                            if tal.name:
                                staticTalent = SD.getStaticTalentByTalentId(tal.CRC32)
                                if staticTalent and staticTalent['rarity'] == "Class":
                                    allClassTalents.add(tal.CRC32)

        for talentId in MD.UserInventory.keys():
            talent = MD.getTalentByID(talentId)
            if talent:
                staticTalent = SD.getStaticTalent(talent)
                if staticTalent and staticTalent['rarity'] == "Class":
                    if talent.PersistentId not in haveClassTalents:
                        haveClassTalents.add(talent.PersistentId)

        diff = allClassTalents.difference(haveClassTalents)
        return diff
