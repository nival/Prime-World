# -*- coding: utf-8 -*-
from base.helpers import *
import sys
import os
import pymongo, pymongo.errors
import coord_cfg
from binascii import crc32

'''
скрипт для ПРАВКИ выданых наград при переходе между 1 (летним) и 2 (осенним) сезонами
вызывается при апгрейде МД при первом логине юзера после техработ
по результату выполнения, юзеру должно насыпать наград и поменять (сбросить) рейтинг героев,
а так же подготовить записи по новому сезону у каждого из героев
'''

red_talent_awards_pool = ['G451', 'G456', 'G461', 'G465', 'G469', 'G474',
                          'G477', 'G482', 'G487', 'G492', 'G498', 'G503',
                          'G510', 'G515', 'G520', 'G526', 'G531', 'G536',
                          'G547', 'G552', 'G557', 'G562', 'G567']


epic_talent_awards_pool = ['G582', 'G588', 'G593', 'G597', 'G600', 'G604']

awards_by_season = [
    {"Rating": 0,    "Flag": None, "RedPerls": 50, "Talents": [], "Skin": None},
    {"Rating": 1400, "Flag": "season1Vamp_simple", "RedPerls": 110, "Talents": [], "Skin": None},
    {"Rating": 1600, "Flag": "season1Vamp_bronze", "RedPerls": 180, "Talents": [], "Skin": None},
    {"Rating": 1700, "Flag": "season1Vamp_bronze", "RedPerls": 180, "Talents": [], "Skin": "vampire_S3"},
    {"Rating": 1800, "Flag": "season1Vamp_silver", "RedPerls": 260, "Talents": red_talent_awards_pool, "Skin": "vampire_S3"},
    {"Rating": 2000, "Flag": "season1Vamp_gold", "RedPerls": 350, "Talents": red_talent_awards_pool, "Skin": "vampire_S3"},
    {"Rating": sys.maxint, "Flag": "season1Vamp_epic", "RedPerls": 350, "Talents": red_talent_awards_pool, "Skin": "vampire_S3"},
]

epic_settings = {"Flag": "season1Vamp_epic", "Talents": epic_talent_awards_pool}


class FixAwardsForSeason1:
    """ Добавляем в ModelData данные по сезонам """
    def convertModelData( self, env, acc, md, dict ):
        arr_seasons_settings = acc.SD.getAllSeasons()

        from_season = arr_seasons_settings[1]  # летний, он же seasson1
        to_season = arr_seasons_settings[2]  # осенний, он же seasson2(?)
        prev_season_id_str = from_season["persistentId"]
        prev_season_id = crc32(prev_season_id_str)

        legend_heroes = {}

        if len(coord_cfg.COORDINATOR_MONGO_CONFIG) > 0:
            opt = ClassDict(coord_cfg.COORDINATOR_MONGO_CONFIG[0])
            try:
                mongo_db = getattr(pymongo.Connection(opt.mongo_addr, opt.mongo_port), opt.mongo_base, None)
                # mongo_db = getattr(pymongo.Connection(opt.mongo_addr, opt.mongo_port, slave_okay=True), opt.mongo_base, None)
                if not mongo_db:
                    debug("FixAwardsMDForSeason1, can't connect %s db" % (str(opt.mongo_addr) + ":" + str(opt.mongo_port)))
                else:
                    # определяем, попал ли игрок в топ100 среди всех в лиге (это пока нах никому не надо, правда)
                    cursor = mongo_db.seasons_top100.find({'auid': acc.db.auid, 'season': prev_season_id})
                    user_in_top100 = False if not cursor else True

                    # определяем всех героев юзера, которые попали в свои топы в прошедшем сезоне
                    #db.getCollection('seasons_top10_by_hero').find({"top10.3772815": {$exists: true}})
                    cursor = mongo_db.seasons_top10_by_hero.find({'season': prev_season_id, 'top10.{0}'.format(acc.db.auid): {'$exists': True}})
                    for rec in cursor:
                        legend_heroes[str(rec['hero_id'])] = int(rec['top10'][str(acc.db.auid)]['place'])
            except pymongo.errors.ConnectionFailure:
                warn("FixAwardsForSeasons1, no mongo connection - skip script")

        debug("FixAwardsMDForSeason1, from_season: %s, to_season: %s, legend_heros: %s " % (
            str(from_season), str(to_season), str(legend_heroes)))
        self.fix_season1_awards(md, env.I, acc, from_season, to_season, awards_by_season, legend_heroes)

        return md, acc.db

    @staticmethod
    def fix_season1_awards(md, I, acc, prev_season_settings, new_season_settings, awards_data, heroes_top10):
        # разовый метод, который правит первые криво начисленные награды при переходе на систему сезонов

        prev_season_id = crc32(prev_season_settings["persistentId"])
        new_season_id = crc32(new_season_settings["persistentId"])

        debug("fixSeason1Awards for auid = %d, prev_season_settings:%s, new_season_settings:%s"%(acc.db.auid, str(prev_season_settings), str(new_season_settings)))

        season_awards_info = None
        for awards_id in md.SeasonAwardsKeeper:
            season_awards_info = md.getSeasonAwardsByID(awards_id)
            if season_awards_info.SeasonId == prev_season_id:
                break

        if not season_awards_info:
            debug("fixSeason1Awards no awards to fix found !")
            return

        #    season_awards_info, season_awards_id = md.newSeasonAwards()
        #    season_awards_info.SeasonId = prev_season_id

        debug("fixSeason1Awards for auid = %d, prev awards: seasonId = %s, Flag: %s, RedPerls: %d, Skin=%s" % (
            acc.db.auid, str(season_awards_info.SeasonId), season_awards_info.Flag, season_awards_info.RedPerls, str(season_awards_info.Skin)))

        debug("fixSeason1Awards for auid = %d, trying to find prev_best_award_index:" % acc.db.auid )
        prev_best_award_index = 0
        for award_row in awards_data:
            if not award_row:
                break
            award_skin_id = 0 if not award_row['Skin'] else crc32(award_row['Skin'])
            debug("\t compare row from awards_data: flag: {0}, RedPerls: {1}, Skin: {2}({3})".format(award_row['Flag'],
                                                                                                     award_row['RedPerls'],
                                                                                                     award_row['Skin'],
                                                                                                     award_skin_id))

            if award_row['Flag'] == season_awards_info.Flag and \
                award_row['RedPerls'] == season_awards_info.RedPerls and \
                    award_skin_id == season_awards_info.Skin:
                break
            else:
                prev_best_award_index += 1
        debug("\t prev_best_award_index = {0}".format(prev_best_award_index))

        is_legend_league = False
        best_award_index = 0
        talents_ids = []

        for heroId, cur_process_hero in md.HeroesKeeper.iteritems():
            # если героем не играли вообще или не играли в последнем сезоне - никакой инфы ему добавлять не будем
            if cur_process_hero.lastPlayed <= 0 or cur_process_hero.lastPlayed < prev_season_settings["startTime"]:
                continue

            # героем заходили в новом сезоне, но не играли в предыдущем?
            prev_season_info = cur_process_hero.findSeasonInfoById(acc, prev_season_id)
            if prev_season_info is None:
                continue

            strPersistentId = str(cur_process_hero.PersistentId)
            debug("fixSeason1Awards for auid = %d, cur_process_hero: %s (%s), id_season: %d"%(acc.db.auid, str(cur_process_hero.class_name),
                                                                                             strPersistentId, prev_season_id))

            #if prev_best_league_index < prev_season_info.LeagueIndex:
            #    prev_best_league_index = prev_season_info.LeagueIndex

            # определяем *правильный* индекс лиги за прошедший сезон
            best_award_index_for_hero = 0
            hero_key = str(cur_process_hero.PersistentId)
            if hero_key in heroes_top10.keys() and heroes_top10[hero_key] <= 10:

                talents_ids.append(random.choice(epic_settings["Talents"]))
                is_legend_league = True
                best_award_index_for_hero = len(awards_by_season) - 1
            else:
                for i in range(len(awards_by_season) - 1, -1, -1):
                    # если есть запись по сезону у героя - берем рейтинг из нее, если нет - текущий рейтинг берем
                    if prev_season_info.SeasonRating >= awards_by_season[i]["Rating"]:
                        if i > best_award_index_for_hero:
                            best_award_index_for_hero = i
                        break

            debug(
                "fixSeason1Awards current hero info: MaxSeasonRating = {0}, CurrentRating = {1}, Award index = {2}".format(
                    prev_season_info.SeasonRating, cur_process_hero.Rating, best_award_index_for_hero))

            if best_award_index_for_hero > best_award_index:
                best_award_index = best_award_index_for_hero

            # мы не знаем какие таланты и из какого пула выдавались в прошлый раз,
            # поэтому просто выдаем если они не выдавались, а должны
            #if prev_season_info.LeagueIndex < best_award_index_for_hero:
            if not season_awards_info.Talents or len(season_awards_info.Talents) == 0:
                hero_awards = awards_by_season[best_award_index_for_hero]
                if 'Talents' in hero_awards and len(hero_awards['Talents']) > 0:
                    talents_ids.append(random.choice(hero_awards['Talents']))

                if is_legend_league:
                    talents_ids.append(random.choice(epic_settings["Talents"]))


        # тут даже если предыдущий индекс лиги совпадает - все равно перевыдаем разницу,
        # ибо награды выдавались по текущему рейтингу а не по индексу лиги
        if best_award_index >= prev_best_award_index:
            debug("fixSeason1Awards for auid = %d, new best_award_index: %d, was: %d", acc.db.auid, best_award_index, prev_best_award_index)

            season_awards_info.IsShowedToUser = False

            debug("fixSeason1Awards for auid = %d, change Perls amount from %d to %d" % (acc.db.auid, awards_data[prev_best_award_index]["RedPerls"], awards_data[best_award_index]["RedPerls"]))
            changed_perls_amount = awards_data[best_award_index]["RedPerls"] - awards_data[prev_best_award_index]["RedPerls"]

            #корректируем общее кол-во полученых кристалов по результатам работы двух скриптов AwardsForSeason1 и FixAwardsForSeason1
            season_awards_info.RedPerls = season_awards_info.RedPerls + changed_perls_amount

            if awards_data[best_award_index]["Skin"] is not None:
                skin_id = awards_data[best_award_index]["Skin"]
                static_skin = acc.SD.getStaticSkinByPersistentId(crc32(skin_id))
                if static_skin:
                    debug("fixSeason1Awards for auid = %d, skin_id: %s", acc.db.auid, skin_id)
                    hero_for_skin = md.getHeroForSkin(static_skin, acc.SD)
                    if not hero_for_skin:
                        debug("fixSeason1Awards for auid = %d, not hero found for skin %s, try to buy hero %s"%(acc.db.auid, skin_id, static_skin['heroClassId']))
                        hero_for_skin = md.hireHero(crc32(static_skin['heroClassId']), acc.sex, I.WS, acc, I)
                    else:
                        debug("fixSeason1Awards for auid = %d, find hero for skin: %s (%s) skin_id: %s"%(acc.db.auid, str(hero_for_skin.class_name), str(hero_for_skin.PersistentId), skin_id))
                    if hero_for_skin:
                        config = acc.getConfig()
                        debug("fixSeason1Awards for auid = %d, addSkinForHero cur_process_hero: %s (%s) skin_id: %s"%(acc.db.auid, str(hero_for_skin.class_name), str(hero_for_skin.PersistentId), skin_id))
                        md.addSkinForHero(crc32(skin_id), hero_for_skin, isDefault=True, wasBought=True,
                                            IsAnimatedAvatar=static_skin['persistentId'] not in config.SKIN_AVATAR_BLOCK)
                        season_awards_info.Skin = crc32(skin_id)
                    else:
                        debug("fixSeason1Awards for auid = %d, not hero found or buy for skin %s"%(acc.db.auid, skin_id))
                else:
                    debug("fixSeason1Awards for auid = %d, skin for skin_id: %s NOT FOUND in staticData!", acc.db.auid, skin_id)

            if is_legend_league:
                flag_name = epic_settings["Flag"]
            else:
                flag_name = awards_data[best_award_index]["Flag"]

            # убираем выданный флаг
            md.removeSeasonFlag(acc, season_awards_info.Flag)
            # если таланты выдавали - ничего не выдем, иначе выдаем таланты
            talents_to_add = [] if len(season_awards_info.Talents) > 0 else talents_ids
            md.appendSeasonAwards(acc, prev_season_id, flag_name, talents_to_add, [])

            if changed_perls_amount > 0:
                md.addResourcesForFree({"Perl": str(changed_perls_amount)})

            debug("fixSeason1Awards for auid = %d, fixed awards: seasonId = %s, Talents: %s, RedPerls: %d" % (
                acc.db.auid, str(season_awards_info.SeasonId), ', '.join(talents_to_add), season_awards_info.RedPerls))

            #if not find_awards_info:
            #    md.SeasonsAwardsInfo.add(prev_season_id, season_awards_info)