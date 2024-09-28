#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, os, random
sys.path.append('..')
from base.helpers import addRelPath
addRelPath( "../cfg" )
from MultiStaticData import MultiStaticData
from config.MultiConfig import MultiConfig


def GenerateSeedPls(numGoodSeeds, numPremiumGoodSeeds):

  GoodSeeds = []
  PremiumGoodSeeds = []

  options_xdb_path = os.path.join( os.path.dirname(os.path.realpath(__file__)), "../xdb/ExportedSocialData.xml" )
  config = MultiConfig()
  staticData = MultiStaticData(options_xdb_path, config.getMainConfig(), applyOverrides=True).mainStaticData
  #config.getMainConfig().applyOverrides(staticData)
  # Заполним статические поля, которые можно перезаписыать из GMTools
  #config.getMainConfig().fillStaticDataDependendValues(staticData)
  print "===================================="
  print config.getMainConfig().EventToolsChangeFields.ORDINARY_TALENTS_DROP_RARITIES.keys()
  print config.getMainConfig().EventToolsChangeFields.PREMIUM_TALENTS_DROP_RARITIES.keys()
  print "===================================="

  tryings = 0
  limitTryings = 10000000
  while (numGoodSeeds or numPremiumGoodSeeds) and tryings < limitTryings:
    seed = random.randrange(100000000)
    if numGoodSeeds:
      if staticData.checkForGoodRandom(seed, config.getMainConfig().EventToolsChangeFields.ORDINARY_TALENTS_DROP_RARITIES) and seed not in GoodSeeds:
        GoodSeeds.append(seed)
        numGoodSeeds -= 1
    if numPremiumGoodSeeds:
      if staticData.checkForGoodRandom(seed, config.getMainConfig().EventToolsChangeFields.PREMIUM_TALENTS_DROP_RARITIES) and seed not in PremiumGoodSeeds:
        PremiumGoodSeeds.append(seed)
        numPremiumGoodSeeds -= 1
    tryings += 1

  if tryings >= limitTryings:
    f = open(os.path.join(os.path.dirname(os.path.realpath(__file__)), "GeneratedSeeds.py"), "w")
    f.write("#!/usr/bin/env python\n")
    f.write("#automatically generated file. do not modify it!!!\n")
    f.write("# -*- coding: cp1251 -*-\n")
    exit(1)

  f = open(os.path.join( os.path.dirname(os.path.realpath(__file__)), "GeneratedSeeds.py"), "w")
  f.write("#!/usr/bin/env python\n")
  f.write("#automatically generated file. do not modify it!!!\n")
  f.write("# -*- coding: cp1251 -*-\n")
  f.write("Probabilities = [" + str(config.getMainConfig().EventToolsChangeFields.ORDINARY_TALENTS_DROP_RARITIES[0]))
  for i in range(1, 6):
    f.write(", "+str(config.getMainConfig().EventToolsChangeFields.ORDINARY_TALENTS_DROP_RARITIES[i]))
  f.write("]\n")
  f.write("GoodSeeds = %r \n" % GoodSeeds)
  f.write("PremiumProbabilities = [" + str(config.getMainConfig().EventToolsChangeFields.PREMIUM_TALENTS_DROP_RARITIES[0]))
  for i in range(1, 6):
    f.write(", "+str(config.getMainConfig().EventToolsChangeFields.PREMIUM_TALENTS_DROP_RARITIES[i]))
  f.write("]\n")
  f.write("PremiumGoodSeeds = %r" % PremiumGoodSeeds)
  f.close()
  print "OK!"

if __name__ == "__main__":
  GenerateSeedPls(100, 100)
