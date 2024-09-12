# -*- coding: utf-8 -*-
from base.helpers import *
import sys
import os
import pymongo, pymongo.errors
import coord_cfg
from binascii import crc32

awards_by_season = [
    {"Rating": 0,    "Flag": None, "RedPerls": 50, "Talents": [], "Skin": None },
    {"Rating": 1400, "Flag": "season1_simple", "RedPerls": 110, "Talents": [], "Skin": None },
    {"Rating": 1600, "Flag": "season1_bronze", "RedPerls": 180, "Talents": [], "Skin": None },
    {"Rating": 1800, "Flag": "season1_silver", "RedPerls": 260, "Talents": [], "Skin": "naga_S3" },
    {"Rating": 2000, "Flag": "season1_gold", "RedPerls": 350, "Talents": ['G451', 'G456', 'G461', 'G465', 'G469', 'G474',
                                                                          'G477', 'G482', 'G487', 'G492', 'G498', 'G503', 'G510',
                                                                          'G515', 'G520', 'G526', 'G531', 'G536'
                                                                          # 'G547', 'G552', 'G557', 'G562', 'G567'
                                                                        ],
                                                                    "Skin": "naga_S3" },
    {"Rating": sys.maxint, "Flag": "season1_epic", "RedPerls": 350, "Talents": [], "Skin": "naga_S3" },
]

epic_settings = {"Flag": "season1_epic", "Talents": ['G547', 'G552', 'G557', 'G562', 'G567']}

#epic_settings = {"Flag": "season1_epic", "Talents": ['G582', 'G583', 'G584', 'G585',
#                                                     'G586', 'G587', 'G588', 'G489',
#                                                     'G590', 'G591', 'G592', 'G593',
#                                                     'G594', 'G595', 'G596', 'G597',
#                                                     'G598', 'G599', 'G600', 'G601',
#                                                     'G602', 'G603', 'G604', 'G605']}

lose_rating_table = [
    (1399, None), # < 1400    -> None Рекруты, Наемники и Рядовые
    (1499, 1401), # 1400-1500 -> 1401 Капралы
    (1599, 1451), # 1500-1600 -> 1451 Сержанты
    (1699, 1551), # 1600-1700 -> 1551 Лейтенанты
    (1799, 1651), # 1700-1800 -> 1651 Капитаны
    (1899, 1651), # 1800-1900 -> 1651 Майоры
    (1999, 1751), # 1900-2000 -> 1751 Полковники
    (sys.maxint, 1851)
]

class FixAwardsForSeasons:
    """ Добавляем в ModelData данные по сезонам """
    def convertModelData( self, env, acc, md, dict ):
        arr_seasons_settings = acc.SD.getAllSeasons()

        legend_ratings_for_start_season = {}
        april_ratings_for_start_season = {}

        file_legend_ratings_name = os.getcwd() + "/tools/dump_ratings_for_md_update"

        debug("FixAwardsForSeasons, try to open %s from %s"%(str(file_legend_ratings_name), os.getcwd()))
        try:
            file_ratings = open(file_legend_ratings_name, 'r')
        except Exception, e:
            file_ratings = None
            debug("FixAwardsForSeasons, try to open %s, err: %s"%(str(file_legend_ratings_name), str(e)))

        if file_ratings:
            legend_ratings_for_start_season = eval(file_ratings.read())
            file_ratings.close()


        debug("FixAwardsForSeasons, legend_ratings_for_start_season: %s"%(str(legend_ratings_for_start_season)))

        if len(coord_cfg.COORDINATOR_MONGO_CONFIG) > 0:
            opt = ClassDict(coord_cfg.COORDINATOR_MONGO_CONFIG[0])

            try:
                mongo_db = getattr(pymongo.Connection(opt.mongo_addr, opt.mongo_port), opt.mongo_base, None)
                # mongo_db = getattr(pymongo.Connection(opt.mongo_addr, opt.mongo_port, slave_okay=True), opt.mongo_base, None)
                if not mongo_db:
                    debug("FixAwardsForSeasons, can't connect %s db" % (str(opt.mongo_addr) + ":" + str(opt.mongo_port)))
                else:
                    cursor = mongo_db.old_ratings.find_one({'auid': acc.db.auid})

                    if not cursor:
                        debug("FixAwardsForSeasons, can't find data for user %s" % (str(acc.db.auid)))
                        return md, acc.db

                    april_hero_ratings = cursor['rating_data']['ratings']

                    if acc.db.auid in legend_ratings_for_start_season.keys():
                        legend_hero_ratings = legend_ratings_for_start_season[acc.db.auid]
                    else:
                        legend_hero_ratings = {}

                    debug("FixAwardsMDForSeasons, all_seasons_settings: %s, legend_hero_ratings :%s, april_hero_ratings : %s"%(str(arr_seasons_settings), str(legend_hero_ratings), str(april_hero_ratings)))
                    self.fixSeasonAwards(md, env.I, acc, arr_seasons_settings[0], arr_seasons_settings[1], awards_by_season, lose_rating_table, epic_settings, legend_hero_ratings, april_hero_ratings)
            except pymongo.errors.ConnectionFailure:
                warn("FixAwardsMDForSeasons, no mongo connection - skip script")

        return md, acc.db

    def getSeasonRating(self, cur_rating, lose_rating_table):
        for lose_rating_tuple in lose_rating_table:
            if cur_rating >= lose_rating_tuple[0]:
                continue

            if lose_rating_tuple[1]:
                return lose_rating_tuple[1]
            break

    def fixSeasonAwards(self, md, I, acc, prev_season_settings, new_season_settings, awards_by_season, lose_rating_table, epic_settings, legend_hero_ratings, april_hero_ratings):
        # разовый метод, который правит первые криво начисленные награды при переходе на систему сезонов
        # и испольется соотвествующим скриптом - FixSeasonAwards
        prev_season_id = crc32(prev_season_settings["persistentId"])
        new_season_id = crc32(new_season_settings["persistentId"])

        debug("fixSeasonAwards for auid = %d, prev_season_settings:%s, new_season_settings:%s"%(acc.db.auid, str(prev_season_settings), str(new_season_settings)))

        prev_best_league_index = 0
        find_awards_info = False
        for awards_id in md.SeasonAwardsKeeper:
            season_awards_info = md.getSeasonAwardsByID(awards_id)
            if season_awards_info.SeasonId == prev_season_id:
                find_awards_info = True
                break

        is_legend_league = False
        best_league_index = 0
        talents_ids = []


        for heroId, cur_process_hero in md.HeroesKeeper.iteritems():
            # если героем не играли вообще или не играли в последнем сезоне - никакой инфы ему добавлять не будем
            if cur_process_hero.lastPlayed <= 0 or cur_process_hero.lastPlayed < prev_season_settings["startTime"]:
                continue

            strPersistentId = str(cur_process_hero.PersistentId)
            debug("fixSeasonAwards for auid = %d, cur_process_hero: %s (%s), id_season: %d"%(acc.db.auid, str(cur_process_hero.class_name),
                                                                                             strPersistentId, prev_season_id))

            if find_awards_info == False:
                season_awards_info, season_awards_id = md.newSeasonAwards()
                season_awards_info.SeasonId = prev_season_id

            prev_season_info = cur_process_hero.findOrCreateSeasonInfoById(acc, acc.SD, prev_season_id)
            #cur_season_info = cur_process_hero.findOrCreateSeasonInfoById(acc, acc.SD, new_season_id)   # TODO: не используется

            if prev_best_league_index < prev_season_info.LeagueIndex:
                prev_best_league_index = prev_season_info.LeagueIndex

            if strPersistentId in april_hero_ratings.keys():
                # корректируем макс рейтинг героя в "нулевом" сезоне
                if prev_season_info.SeasonRating < april_hero_ratings[strPersistentId]:
                    prev_season_info.SeasonRating = april_hero_ratings[strPersistentId]

                # стартовый рейтинг героя в "первом" сезоне
                new_season_rating = self.getSeasonRating(april_hero_ratings[strPersistentId], lose_rating_table)
                if not new_season_rating:
                    new_season_rating = april_hero_ratings[strPersistentId]

                debug("fixSeasonAwards for auid = %d, cur_process_hero.Rating: %d, new_season_rating:%d" % (acc.db.auid, cur_process_hero.Rating, new_season_rating))

                # корректируем текущий рейтинг героя
                if new_season_rating > cur_process_hero.Rating:
                    cur_process_hero.changeRating(new_season_rating - cur_process_hero.Rating, I, acc)

                # определяем индекс лиги по состоянию на апрель
                best_april_hero_league_index = 0
                if cur_process_hero.PersistentId in legend_hero_ratings.keys() and legend_hero_ratings[cur_process_hero.PersistentId] <= 10:
                    best_april_hero_league_index = 5
                    is_legend_league = True
                else:
                    for i in range(len(awards_by_season) - 1, -1, -1):
                        if april_hero_ratings[strPersistentId] >= awards_by_season[i]["Rating"]:
                            if i > best_april_hero_league_index:
                                best_april_hero_league_index = i
                            break

                # подготавливаем данные сезонов и лиг для выдачи награды
                if prev_season_info.LeagueIndex < best_april_hero_league_index:
                    if is_legend_league:
                        prev_season_info.CurLeaguePlace = legend_hero_ratings[cur_process_hero.PersistentId]
                        prev_season_info.BestLeaguePlace = prev_season_info.CurLeaguePlace
                        talents_ids.append(random.choice(epic_settings["Talents"]))
                    else:
                        if best_april_hero_league_index == 4:
                            talents_ids.append(random.choice(awards_by_season[best_april_hero_league_index]["Talents"]))

                    if best_april_hero_league_index > best_league_index:
                        best_league_index = best_april_hero_league_index

                    prev_season_info.LeagueIndex = best_april_hero_league_index

                    # непонятно зачем мы трогаем "текущий" сезон
                    #cur_season_info.LeagueIndex = best_april_hero_league_index
                    #cur_process_hero.updateLegendPlace(acc, acc.SD, cur_season_info.CurLeaguePlace)

        if best_league_index > prev_best_league_index:
            debug("fixSeasonAwards for auid = %d, new best_league_index: %d, was: %d", acc.db.auid, best_league_index, prev_best_league_index)

            season_awards_info.IsShowedToUser = False

            debug("fixSeasonAwards for auid = %d, change Perls amount from %d to %d"%(acc.db.auid, awards_by_season[prev_best_league_index]["RedPerls"], awards_by_season[best_league_index]["RedPerls"]))
            changed_perls_amount = awards_by_season[best_league_index]["RedPerls"] - awards_by_season[prev_best_league_index]["RedPerls"]
            season_awards_info.RedPerls = changed_perls_amount

            if awards_by_season[best_league_index]["Skin"] is not None:
                skin_id = awards_by_season[best_league_index]["Skin"]
                static_skin = acc.SD.getStaticSkinByPersistentId(crc32(skin_id))
                if static_skin:
                    debug("fixSeasonAwards for auid = %d, skin_id: %s", acc.db.auid, skin_id)
                    hero_for_skin = md.getHeroForSkin(static_skin, acc.SD)
                    if not hero_for_skin:
                        debug("fixSeasonAwards for auid = %d, not hero found for skin %s, try to buy hero %s"%(acc.db.auid, skin_id, static_skin['heroClassId']))
                        hero_for_skin = md.hireHero(crc32(static_skin['heroClassId']), acc.sex, I.WS, acc, I)
                    else:
                        debug("fixSeasonAwards for auid = %d, find haro for skin: %s (%s) skin_id: %s"%(acc.db.auid, str(hero_for_skin.class_name), str(hero_for_skin.PersistentId), skin_id))
                    if hero_for_skin:
                        config = acc.getConfig()
                        debug("fixSeasonAwards for auid = %d, addSkinForHero cur_process_hero: %s (%s) skin_id: %s"%(acc.db.auid, str(hero_for_skin.class_name), str(hero_for_skin.PersistentId), skin_id))
                        md.addSkinForHero(crc32(skin_id), hero_for_skin, isDefault=True, wasBought=True,
                                            IsAnimatedAvatar=static_skin['persistentId'] not in config.SKIN_AVATAR_BLOCK)
                        season_awards_info.Skin = crc32(skin_id)
                    else:
                        debug("fixSeasonAwards for auid = %d, not hero found or buy for skin %s"%(acc.db.auid, skin_id))
                else:
                    debug("collectSeasonAwards for auid = %d, skin for skin_id: %s NOT FOUND in staticData!", acc.db.auid, skin_id)

            if is_legend_league:
                flag_name = epic_settings["Flag"]
            else:
                flag_name = awards_by_season[best_league_index]["Flag"]

            md.removeSeasonFlag(acc, season_awards_info.Flag)
            md.appendSeasonAwards(acc, prev_season_id, flag_name, talents_ids, [])

            md.addResourcesForFree({"Perl": str(season_awards_info.RedPerls)})

            debug("collectSeasonAwards for auid = %d, result awards: seasonId = %s, Talents: %s, RedPerls: %d"%(acc.db.auid,
                                                                                                                str(season_awards_info.SeasonId), ', '.join(talents_ids), season_awards_info.RedPerls))

            if find_awards_info == False:
                md.SeasonsAwardsInfo.add(prev_season_id, season_awards_info)