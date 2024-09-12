# -*- coding: utf-8 -*-
import sys
from modeldata.Scripts.BaseAwardsForSeason import BaseAwardsForSeason


class AwardsForSeason10(BaseAwardsForSeason):

    def __init__(self):
        # новые сезоны, наград нет, скрипт для апдейта MD и выдачи лиг для рамок
        # верим в то, что надо строго 7 лиг, как в прошлых сезонах
        self.awards_by_season = [
            {"Rating": 0, "Flag": None, "RedPerls": 0, "Talents": [], "Skin": None, "Lootboxes": []},
            {"Rating": 1400, "Flag": None, "RedPerls": 0, "Talents": [], "Skin": None, "Lootboxes": []},
            {"Rating": 1600, "Flag": None, "RedPerls": 0, "Talents": [], "Skin": None, "Lootboxes": []},
            {"Rating": 1700, "Flag": None, "RedPerls": 0, "Talents": [], "Skin": None, "Lootboxes": []},
            {"Rating": 1800, "Flag": None, "RedPerls": 0, "Talents": [], "Skin": None, "Lootboxes": []},
            {"Rating": 2000, "Flag": None, "RedPerls": 0, "Talents": [], "Skin": None, "Lootboxes": []},
            {"Rating": sys.maxint, "Flag": None, "RedPerls": 0, "Talents": [], "Skin": None, "Lootboxes": []},
        ]
        self.season_idx = 10

    # после сезона 7 не снижаем рейтинг вовсе, см. PF-108828
    def _change_rating_functor(self, cur_rating):
        return 0
