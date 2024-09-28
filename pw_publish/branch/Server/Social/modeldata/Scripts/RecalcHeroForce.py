# -*- coding: utf-8 -*-
from base.helpers import *

class RecalcHeroForce:
    """
    Пересчитаем исходную мощь героев
    """

    def convertModelData(self, env, acc, md, dict):
        # найдём ёлочку и срубим
        for heroId, hero in md.Heroes.items():
            for tsId in hero.TalentSets:
                try:
                    hero.CalcForce(md, env.I.WS, acc, 0)
                except Exception:
                    catch()
        return md, acc.db