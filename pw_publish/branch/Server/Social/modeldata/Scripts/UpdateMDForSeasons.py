# -*- coding: utf-8 -*-
from base.helpers import *
import sys
import os

awards_by_season = [
    {"Rating": 0,    "Flag": None, "RedPerls": 50, "Talents": [], "Skin": None },  #0
    {"Rating": 1400, "Flag": "season1_simple", "RedPerls": 110, "Talents": [], "Skin": None }, #1
    {"Rating": 1600, "Flag": "season1_bronze", "RedPerls": 180, "Talents": [], "Skin": None }, #2
    {"Rating": 1800, "Flag": "season1_silver", "RedPerls": 260, "Talents": [], "Skin": "naga_S3" }, #3
    {"Rating": 2000, "Flag": "season1_gold", "RedPerls": 350, "Talents": ['G451', 'G456', 'G461', 'G465', 'G469', 'G474',
                                                                          'G477', 'G482', 'G487', 'G492', 'G498', 'G503', 'G510',
                                                                          'G515', 'G520', 'G526', 'G531', 'G536'
                                                                          # 'G547', 'G552', 'G557', 'G562', 'G567'
                                                                        ], #4
                                                                    "Skin": "naga_S3" },
    {"Rating": sys.maxint, "Flag": "season1_epic", "RedPerls": 350, "Talents": ['G547', 'G552', 'G557', 'G562', 'G567'], "Skin": "naga_S3" },
]

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


def lose_rating_functor(cur_rating):
    for lose_rating_tuple in lose_rating_table:
        if cur_rating > lose_rating_tuple[0]:
            continue
        if lose_rating_tuple[1]:
            return lose_rating_tuple[1] - cur_rating
    return 0


class UpdateMDForSeasons:
    """ Добавляем в ModelData данные по сезонам """
    def convertModelData( self, env, acc, md, dict ):
        arr_seasons_settings = acc.SD.getAllSeasons()

        legend_ratings_for_start_season = {}
        file_ratings_name = os.getcwd() + "/tools/dump_ratings_for_md_update"

        need_update_prev_info_struct = False

        debug("UpdateHeroForSeasons, try to open %s from %s" % (str(file_ratings_name), os.getcwd()))
        try:
            file_ratings = open(file_ratings_name, 'r')
        except Exception, e:
            file_ratings = None
            debug("UpdateHeroForSeasons, try to open %s, err: %s" % (str(file_ratings_name), str(e)))

        if file_ratings:
            legend_ratings_for_start_season = eval(file_ratings.read())
            file_ratings.close()
            need_update_prev_info_struct = True

        debug("UpdateHeroForSeasons, legend_ratings_for_start_season: %s" % (str(legend_ratings_for_start_season)))

        if acc.db.auid in legend_ratings_for_start_season.keys():
            legend_hero_ratings = legend_ratings_for_start_season[acc.db.auid]
        else:
            legend_hero_ratings = {}

        debug("UpdateHeroForSeasons, all_seasons_settings: %s, legend_hero_ratings :%s" % (
            str(arr_seasons_settings), str(legend_hero_ratings)))
        md.collectSeasonAwards(env.I, acc, arr_seasons_settings[0], arr_seasons_settings[1], awards_by_season,
                               lose_rating_functor, legend_hero_ratings, need_update_prev_info_struct)
        return md, acc.db
