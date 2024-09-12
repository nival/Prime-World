# -*- coding: utf-8 -*-
import sys
from modeldata.Scripts.BaseAwardsForSeason import BaseAwardsForSeason


class AwardsForSeason7(BaseAwardsForSeason):

    def __init__(self):
        lootboxes = ["LB_Red567"]
        epic_lootboxes = ["LB_Red567", "LB_Red567_Set9"]

        self.awards_by_season = [
            {"Rating": 0, "Flag": None, "RedPerls": 150, "Talents": [], "Skin": None, "Lootboxes": []},
            {"Rating": 1400, "Flag": "season8_simple", "RedPerls": 330, "Talents": [], "Skin": None, "Lootboxes": []},
            {"Rating": 1600, "Flag": "season8_bronze", "RedPerls": 540, "Talents": [], "Skin": None, "Lootboxes": []},
            {"Rating": 1700, "Flag": "season8_bronze", "RedPerls": 540, "Talents": [], "Skin": "angel_S2", "Lootboxes": lootboxes},
            {"Rating": 1800, "Flag": "season8_silver", "RedPerls": 780, "Talents": [], "Skin": "angel_S2", "Lootboxes": lootboxes},
            {"Rating": 2000, "Flag": "season8_gold", "RedPerls": 1050, "Talents": [], "Skin": "angel_S2", "Lootboxes": epic_lootboxes},
            {"Rating": sys.maxint, "Flag": "season8_epic", "RedPerls": 1050, "Talents": [], "Skin": "angel_S2", "Lootboxes": epic_lootboxes},
        ]
        self.season_idx = 7
