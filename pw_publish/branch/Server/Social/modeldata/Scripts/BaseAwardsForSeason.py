# -*- coding: utf-8 -*-
from base.helpers import *
import sys
from binascii import crc32
import pymongo, pymongo.errors
import coord_cfg

'''
скрипт для перехода между сезонами
вызывается при апгрейде МД при первом логине юзера после техработ
по результату выполнения, юзеру должно насыпать наград и поменять (сбросить) рейтинг героев,
а так же подготовить записи по новому сезону у каждого из героев
'''


class BaseAwardsForSeason:

    def __init__(self):
        self.awards_by_season = []
        self.season_idx = -1

    """ Добавляем в ModelData данные по сезонам """
    def convertModelData(self, env, acc, md, dict):
        arr_seasons_settings = acc.SD.getAllSeasons()
        from_season = arr_seasons_settings[self.season_idx]
        to_season = arr_seasons_settings[self.season_idx + 1]
        prev_season_id_str = from_season["persistentId"]
        prev_season_id = crc32(prev_season_id_str)

        if len(coord_cfg.COORDINATOR_MONGO_CONFIG) > 0:
            opt = ClassDict(coord_cfg.COORDINATOR_MONGO_CONFIG[0])
            try:
                mongo_db = getattr(pymongo.Connection(opt.mongo_addr, opt.mongo_port), opt.mongo_base, None)
                # mongo_db = getattr(pymongo.Connection(opt.mongo_addr, opt.mongo_port, slave_okay=True), opt.mongo_base, None)
                if not mongo_db:
                    debug("BaseAwardsForSeason, can't connect %s db" % (str(opt.mongo_addr) + ":" + str(opt.mongo_port)))
                else:
                    # определяем, попал ли игрок в топ100 среди всех в лиге (это пока нах никому не надо, правда)
                    cursor = mongo_db.seasons_top100.find({'auid': acc.db.auid, 'season': prev_season_id})
                    user_in_top100 = False if not cursor else True

                    # определяем всех героев юзера, которые попали в свои топы в прошедшем сезоне
                    #db.getCollection('seasons_top10_by_hero').find({"top10.3772815": {$exists: true}})
                    cursor = mongo_db.seasons_top10_by_hero.find({'season': prev_season_id, 'top10.{0}'.format(acc.db.auid): {'$exists': True}})
                    legend_heroes = {}
                    for rec in cursor:
                        legend_heroes[str(rec['hero_id'])] = rec['top10'][str(acc.db.auid)]['place']

                    debug("BaseAwardsForSeason, from_season: %s, to_season: %s, legend_heros: %s " % (
                        str(from_season), str(to_season), str(legend_heroes)))
                    md.collectSeasonAwards(env.I, acc, from_season, to_season, self.awards_by_season,
                                           self._change_rating_functor, legend_heroes, False)
            except pymongo.errors.ConnectionFailure:
                warn("BaseAwardsForSeason, no mongo connection - skip script")

        return md, acc.db

    # функция, определяющая насколько должен измениться рейтинг в контексте данной операции
    def _change_rating_functor(self, cur_rating):
        if cur_rating < 1600:
            return 0
        elif cur_rating < 2000:
            return -50
        return 1950-cur_rating
