# -*- coding: utf-8 -*-
import sys
from modeldata.Scripts.BaseAwardsForSeason import BaseAwardsForSeason


class AwardsForSeason5(BaseAwardsForSeason):

    def __init__(self):
        lootboxes = ["LB_Red456"]
        epic_lootboxes = ["LB_Red456", "LB_Red456_Set8"]

        self.awards_by_season = [
            {"Rating": 0, "Flag": None, "RedPerls": 150, "Talents": [], "Skin": None, "Lootboxes": []},
            {"Rating": 1400, "Flag": "season6_simple", "RedPerls": 330, "Talents": [], "Skin": None, "Lootboxes": []},
            {"Rating": 1600, "Flag": "season6_bronze", "RedPerls": 540, "Talents": [], "Skin": None, "Lootboxes": []},
            {"Rating": 1700, "Flag": "season6_bronze", "RedPerls": 540, "Talents": [], "Skin": "ent_S1", "Lootboxes": lootboxes},
            {"Rating": 1800, "Flag": "season6_silver", "RedPerls": 780, "Talents": [], "Skin": "ent_S1", "Lootboxes": lootboxes},
            {"Rating": 2000, "Flag": "season6_gold", "RedPerls": 1050, "Talents": [], "Skin": "ent_S1", "Lootboxes": epic_lootboxes},
            {"Rating": sys.maxint, "Flag": "season6_epic", "RedPerls": 1050, "Talents": [], "Skin": "ent_S1", "Lootboxes": epic_lootboxes},
        ]
        self.season_idx = 5
