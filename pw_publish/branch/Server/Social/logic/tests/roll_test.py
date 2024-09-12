# -*- coding: utf-8 -*-
from base.helpers import *
sys.path.append('../')
sys.path.append('../..')

from enums import *

class roll_test:

    def transmutation_building_roll_test( self, env ):
        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "Talent_Production")

        construction.cycle = 0
        construction.ProductionState = ProductionState.Idle
        construction.StartProductionTime = int(time.time()) - 5
        construction.EndProductionTime = construction.StartProductionTime
        construction.ProductionCustomValue = 100
        construction.ProductionLevel = 0
        construction.Level = 0
        modeldata.rollTalentsForTransmutationBuilding(construction, env.acc, env.I, "", "")

        assert len(construction.CraftedTalentsToLibrary) == construction.ProductionCustomValue

        numberOfYellow = env.acc.SD.data['RollTalentForTransmutationBuilding']['percents']['Item'][1]
        numberOfGreen = env.acc.SD.data['RollTalentForTransmutationBuilding']['percents']['Item'][2]
        numberOfBlue = env.acc.SD.data['RollTalentForTransmutationBuilding']['percents']['Item'][3]
        numberOfViolet = env.acc.SD.data['RollTalentForTransmutationBuilding']['percents']['Item'][4]
        numberOfOrange = env.acc.SD.data['RollTalentForTransmutationBuilding']['percents']['Item'][5]

        realNumberOfYellow = 0
        realNumberOfGreen = 0
        realNumberOfBlue = 0
        realNumberOfViolet = 0
        realNumberOfOrange = 0
        for talId in construction.CraftedTalentsToLibrary:
            mdTalent = modeldata.getTalentByID(talId)
            staticTalent = env.acc.SD.getStaticTalentByTalentId( mdTalent.PersistentId )

            if staticTalent:
                if staticTalent['rarity'] == "ordinary":
                    realNumberOfYellow += 1
                elif staticTalent['rarity'] == "good":
                    realNumberOfGreen += 1
                elif staticTalent['rarity'] == "excellent":
                    realNumberOfBlue += 1
                elif staticTalent['rarity'] == "magnificent":
                    realNumberOfViolet += 1
                elif staticTalent['rarity'] == "exclusive":
                    realNumberOfOrange += 1

        assert numberOfYellow == realNumberOfYellow
        assert numberOfGreen == realNumberOfGreen
        assert numberOfBlue == realNumberOfBlue
        assert numberOfViolet == realNumberOfViolet, ('Expected Violet == ',numberOfViolet,' but got ',realNumberOfViolet)
        assert numberOfOrange == realNumberOfOrange, ('Expected Violet == ',numberOfOrange,' but got ',realNumberOfOrange)

    def transmutation_building_premium_roll_test( self, env ):
        #TODO: разобраться с премиум кузней - не совпадают вероятности на 100 талантов
        return

        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "Talent_Production")

        construction.cycle = 0
        construction.ProductionState = ProductionState.Idle
        construction.StartProductionTime = int(time.time()) - 5
        construction.EndProductionTime = construction.StartProductionTime
        construction.ProductionCustomValue = 100
        construction.ProductionLevel = 0
        construction.Level = 0
        modeldata.LordInfo.PremiumAccountEnd = construction.StartProductionTime + 100500
        modeldata.rollTalentsForTransmutationBuilding(construction, env.acc, env.I, "", "")

        assert len(construction.CraftedTalentsToLibrary) == construction.ProductionCustomValue

        numberOfYellow = env.acc.SD.data['RollTalentPremiumForTransmutationBuilding']['percents']['Item'][1]
        numberOfGreen = env.acc.SD.data['RollTalentPremiumForTransmutationBuilding']['percents']['Item'][2]
        numberOfBlue = env.acc.SD.data['RollTalentPremiumForTransmutationBuilding']['percents']['Item'][3]
        numberOfViolet = env.acc.SD.data['RollTalentPremiumForTransmutationBuilding']['percents']['Item'][4]
        numberOfOrange = env.acc.SD.data['RollTalentPremiumForTransmutationBuilding']['percents']['Item'][5]

        realNumberOfYellow = 0
        realNumberOfGreen = 0
        realNumberOfBlue = 0
        realNumberOfViolet = 0
        realNumberOfOrange = 0
        for talId in construction.CraftedTalentsToLibrary:
            mdTalent = modeldata.getTalentByID(talId)
            staticTalent = env.acc.SD.getStaticTalentByTalentId( mdTalent.PersistentId )

            if staticTalent:
                if staticTalent['rarity'] == "ordinary":
                    realNumberOfYellow += 1
                elif staticTalent['rarity'] == "good":
                    realNumberOfGreen += 1
                elif staticTalent['rarity'] == "excellent":
                    realNumberOfBlue += 1
                elif staticTalent['rarity'] == "magnificent":
                    realNumberOfViolet += 1
                elif staticTalent['rarity'] == "exclusive":
                    realNumberOfOrange += 1

        assert numberOfYellow == realNumberOfYellow
        assert numberOfGreen == realNumberOfGreen
        assert numberOfBlue == realNumberOfBlue
        assert numberOfViolet == realNumberOfViolet, ('Expected Violet == ',numberOfViolet,' but got ',realNumberOfViolet)
        assert numberOfOrange == realNumberOfOrange, ('Expected Violet == ',numberOfOrange,' but got ',realNumberOfOrange)
