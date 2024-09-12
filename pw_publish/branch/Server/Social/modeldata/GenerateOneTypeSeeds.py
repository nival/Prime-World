#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, os, random, ujson
sys.path.append(os.path.join(os.path.dirname(os.path.realpath(__file__)), '../base'))
sys.path.append(os.path.join(os.path.dirname(os.path.realpath(__file__)), '..'))
from base.helpers import addRelPath
addRelPath("../cfg")
addRelPath('../modeldata')

from MultiStaticData import MultiStaticData
from config.MultiConfig import MultiConfig

def GenerateOneTypeSeeds(numGoodSeeds, SD, probabilities):
    GoodSeeds = []

    tryings = 0
    limitTryings = 10000000
    while numGoodSeeds and tryings < limitTryings:
        seed = random.randrange(100000000)
        if numGoodSeeds:
            if SD.checkForGoodRandom(seed, probabilities) and seed not in GoodSeeds:
              GoodSeeds.append(seed)
              numGoodSeeds -= 1
        tryings += 1

    if tryings >= limitTryings:
        return GoodSeeds
    return GoodSeeds

if __name__ == "__main__":
    probabilities = []
    NewSeeds = []
    seedsType = ""
    if len(sys.argv) == 8:
        for i in xrange(1,7):
            probabilities.append(int(sys.argv[i]))
        seedsType = sys.argv[7]

        options_xdb_path = os.path.join( os.path.dirname(os.path.realpath(__file__)), "../xdb/ExportedSocialData.xml" )
        config = MultiConfig()
        staticData = MultiStaticData( options_xdb_path, config.getMainConfig() ).mainStaticData
        NewSeeds = GenerateOneTypeSeeds(100, staticData, probabilities)
        seedsStr = ""
        #for seed in NewSeeds:
         # print seed
        print ujson.encode(NewSeeds)
    else:
        exit(1)