# -*- coding: utf-8 -*-
import sys
from modeldata.Scripts.BaseAwardsForSeason import BaseAwardsForSeason


class AwardsForSeason4(BaseAwardsForSeason):

    def __init__(self):
        red_talent_awards_pool = ['G451', 'G456', 'G461', 'G465', 'G469', 'G474',
                                  'G477', 'G482', 'G487', 'G492', 'G498', 'G503',
                                  'G510', 'G515', 'G520', 'G526', 'G531', 'G536',
                                  'G547', 'G552', 'G557', 'G562', 'G567', 'G582',
                                  'G588', 'G593', 'G597', 'G600', 'G604', 'G616',
                                  'G623']

        epic_talent_awards_pool = ['G629', 'G633', 'G637', 'G641', 'G647']

        self.awards_by_season = [
            {"Rating": 0, "Flag": None, "RedPerls": 150, "Talents": [], "Skin": None},
            {"Rating": 1400, "Flag": "season5_simple", "RedPerls": 330, "Talents": [], "Skin": None},
            {"Rating": 1600, "Flag": "season5_bronze", "RedPerls": 540, "Talents": [], "Skin": None},
            {"Rating": 1700, "Flag": "season5_bronze", "RedPerls": 540, "Talents": red_talent_awards_pool, "Skin": "rockman_S3"},
            {"Rating": 1800, "Flag": "season5_silver", "RedPerls": 780, "Talents": red_talent_awards_pool, "Skin": "rockman_S3"},
            {"Rating": 2000, "Flag": "season5_gold", "RedPerls": 1050, "Talents": [red_talent_awards_pool, epic_talent_awards_pool], "Skin": "rockman_S3"},
            {"Rating": sys.maxint, "Flag": "season5_epic", "RedPerls": 1050, "Talents": [red_talent_awards_pool, epic_talent_awards_pool], "Skin": "rockman_S3"},
        ]
        self.season_idx = 4
