#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
sys.path.append('..')
from base.helpers import addRelPath
addRelPath( "../cfg" )
from MultiStaticData import MultiStaticData
from config.MultiConfig import MultiConfig
from modeldata.ModelData import *
from enums import *

def GenerateSeedDistributionPls():

    options_xdb_path = os.path.join( os.path.dirname(os.path.realpath(__file__)), "../xdb/ExportedSocialData.xml" )
    config = MultiConfig()
    staticData = MultiStaticData( options_xdb_path, config.getMainConfig(), applyOverrides=True ).mainStaticData

    print "===================================="
    print staticData.data['RollTalentForTransmutationBuilding']['percents']['Item']
    print "===================================="

    testMD = ModelData()
    seedsDistribution = {}
    for seed in staticData.GoodSeeds:
        seedsDistribution[seed] = getRaritiesDistribution( testMD, seed, staticData )

    f = open( os.path.join( os.path.dirname(os.path.realpath(__file__)), "SeedsDistribution.txt"), "w")
    for seed in seedsDistribution:
        dataString = "%d:" % seed
        for rarity in seedsDistribution[seed]:
            dataString += " %d" % rarity
        dataString += "\n"
        f.write(dataString)
    f.close()

def getRaritiesDistribution(modeldata, val, SD ):
    randValue = val
    newTalensByRarity = []

    for i in xrange(0, 100):
        persistentId, rarity = SD.getTalentForRoll( SD.data['RollTalentForTransmutationBuilding']['percents']['Item'], False, "", "", randValue, randValue, SD )
        intRarity = getattr( ETalentRarity, rarity )
        newTalensByRarity.append(intRarity)
        randValue = modeldata.getRandomPure(randValue)

    return newTalensByRarity

if __name__ == "__main__":
    GenerateSeedDistributionPls()
