# -*- coding: utf-8 -*-
import sys
from modeldata.Scripts.BaseAwardsForSeason import BaseAwardsForSeason


class AwardsForSeason6(BaseAwardsForSeason):

    def __init__(self):
        lootboxes = ["LB_Red567"]
        epic_lootboxes = ["LB_Red567", "LB_Red567_Set8"]

        self.awards_by_season = [
            {"Rating": 0, "Flag": None, "RedPerls": 150, "Talents": [], "Skin": None, "Lootboxes": []},
            {"Rating": 1400, "Flag": "season7_simple", "RedPerls": 330, "Talents": [], "Skin": None, "Lootboxes": []},
            {"Rating": 1600, "Flag": "season7_bronze", "RedPerls": 540, "Talents": [], "Skin": None, "Lootboxes": []},
            {"Rating": 1700, "Flag": "season7_bronze", "RedPerls": 540, "Talents": [], "Skin": "fallenangel_S2", "Lootboxes": lootboxes},
            {"Rating": 1800, "Flag": "season7_silver", "RedPerls": 780, "Talents": [], "Skin": "fallenangel_S2", "Lootboxes": lootboxes},
            {"Rating": 2000, "Flag": "season7_gold", "RedPerls": 1050, "Talents": [], "Skin": "fallenangel_S2", "Lootboxes": epic_lootboxes},
            {"Rating": sys.maxint, "Flag": "season7_epic", "RedPerls": 1050, "Talents": [], "Skin": "fallenangel_S2", "Lootboxes": epic_lootboxes},
        ]
        self.season_idx = 6
