# -*- coding: utf-8 -*-
import sys
from modeldata.Scripts.BaseAwardsForSeason import BaseAwardsForSeason


class AwardsForSeason2(BaseAwardsForSeason):

    def __init__(self):
        red_talent_awards_pool = ['G451', 'G456', 'G461', 'G465', 'G469', 'G474',
                                  'G477', 'G482', 'G487', 'G492', 'G498', 'G503',
                                  'G510', 'G515', 'G520', 'G526', 'G531', 'G536',
                                  'G547', 'G552', 'G557', 'G562', 'G567']

        epic_talent_awards_pool = ['G582', 'G583', 'G584', 'G585', 'G586',
                                   'G587', 'G588', 'G589', 'G590', 'G591', 'G592', 'G593',
                                   'G594', 'G595', 'G596', 'G597', 'G598', 'G599', 'G600',
                                   'G601', 'G602', 'G603', 'G604', 'G605', ]  # 582 - 605

        self.awards_by_season = [
            {"Rating": 0, "Flag": None, "RedPerls": 150, "Talents": [], "Skin": None},
            {"Rating": 1400, "Flag": "season3_simple", "RedPerls": 330, "Talents": [], "Skin": None},
            {"Rating": 1600, "Flag": "season3_bronze", "RedPerls": 540, "Talents": [], "Skin": None},
            {"Rating": 1700, "Flag": "season3_bronze", "RedPerls": 540, "Talents": red_talent_awards_pool, "Skin": "thundergod_S6"},
            {"Rating": 1800, "Flag": "season3_silver", "RedPerls": 780, "Talents": red_talent_awards_pool, "Skin": "thundergod_S6"},
            {"Rating": 2000, "Flag": "season3_gold", "RedPerls": 1050, "Talents": [red_talent_awards_pool, epic_talent_awards_pool], "Skin": "thundergod_S6"},
            {"Rating": sys.maxint, "Flag": "season3_epic", "RedPerls": 1050, "Talents": [red_talent_awards_pool, epic_talent_awards_pool], "Skin": "thundergod_S6"},
        ]
        self.season_idx = 2
