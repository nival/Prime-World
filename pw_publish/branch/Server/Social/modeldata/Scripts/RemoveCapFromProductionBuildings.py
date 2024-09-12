# -*- coding: utf-8 -*-

class RemoveCapFromProductionBuildings:
    def convertModelData( self, env, acc, md, dict ):

        for buildingId in md.ConstructionsKeeper:
            construction = md.getConstructionByID(buildingId)
            staticConstruction = acc.SD.getStaticConstruction(construction)
            # Для каждого здания смотрим, того ли оно типа и не превышен ли кап
            if staticConstruction and staticConstruction['classType'] == 'ProductionBuilding':
                if staticConstruction['persistentId'] in ['Production_Resource1', 'Production_Resource2',
                                                          'Production_Resource3']:
                    if construction.ProductionValue > 55000:
                        construction.ProductionValue = 55000
                elif staticConstruction['persistentId'] == 'Production_Silver_fromRes1':
                    if construction.ProductionValue > 17000:
                        construction.ProductionValue = 17000
                elif staticConstruction['persistentId'] == 'Production_Crystal':
                    if construction.ProductionValue > 36:
                        construction.ProductionValue = 36

        return md, acc.db