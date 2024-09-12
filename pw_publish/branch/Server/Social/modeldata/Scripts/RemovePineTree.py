# -*- coding: utf-8 -*-
from base.helpers import *

class RemovePineTree:
    """
    Раз в год выпиливаем ёлочку из замка
    """

    def convertModelData(self, env, acc, md, dict):
        # найдём ёлочку и срубим
        for constructionId, construction in md.ConstructionsKeeper.items():
            staticConstruction = acc.SD.getStaticConstruction(construction)
            if staticConstruction and staticConstruction['classType'] == "PineTreeBuilding":
                md.Buildings.remove(constructionId)
                md.Pocket.remove(constructionId)
        return md, acc.db