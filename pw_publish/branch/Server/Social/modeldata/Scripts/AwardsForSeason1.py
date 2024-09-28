# -*- coding: utf-8 -*-
import sys
from modeldata.Scripts.BaseAwardsForSeason import BaseAwardsForSeason


class AwardsForSeason1(BaseAwardsForSeason):

    def __init__(self):
        red_talent_awards_pool = ['G451', 'G456', 'G461', 'G465', 'G469', 'G474',
                                  'G477', 'G482', 'G487', 'G492', 'G498', 'G503',
                                  'G510', 'G515', 'G520', 'G526', 'G531', 'G536',
                                  'G547', 'G552', 'G557', 'G562', 'G567']

        epic_talent_awards_pool = ['G547', 'G552', 'G557', 'G562', 'G567',
                                   'G582', 'G588', 'G593', 'G597', 'G600', 'G604']

        self.awards_by_season = [
            {"Rating": 0, "Flag": None, "RedPerls": 50, "Talents": [], "Skin": None},
            {"Rating": 1400, "Flag": "season1Vamp_simple", "RedPerls": 110, "Talents": [], "Skin": None},
            {"Rating": 1600, "Flag": "season1Vamp_bronze", "RedPerls": 180, "Talents": [], "Skin": None},
            {"Rating": 1700, "Flag": "season1Vamp_bronze", "RedPerls": 180, "Talents": [], "Skin": "vampire_S3"},
            {"Rating": 1800, "Flag": "season1Vamp_silver", "RedPerls": 260, "Talents": red_talent_awards_pool, "Skin": "vampire_S3"},
            {"Rating": 2000, "Flag": "season1Vamp_gold", "RedPerls": 350, "Talents": red_talent_awards_pool, "Skin": "vampire_S3"},
            {"Rating": sys.maxint, "Flag": "season1Vamp_epic", "RedPerls": 350, "Talents": [red_talent_awards_pool, epic_talent_awards_pool], "Skin": "vampire_S3"},
        ]
        self.season_idx = 1
