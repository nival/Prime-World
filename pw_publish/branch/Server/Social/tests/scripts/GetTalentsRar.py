import os, sys

sys.path.append('../../')
sys.path.append('../../base')
sys.path.append('../../cfg')
sys.path.append('../../modeldata')
from StaticData import StaticData
from config.MultiConfig import MultiConfig
from config.MultiConfig import MultiConfig


options_xdb_path = "../../xdb/ExportedSocialData.xml"
config = MultiConfig()
staticData = StaticData( options_xdb_path, config.getMainConfig() )

if len(sys.argv) > 1:
  persistentIds = sys.argv[1:]

  for tid in persistentIds:
    for talentId in staticData.data['Talents'].keys():
      if talentId == int(tid):
        print "rar=%r"%staticData.data['Talents'][talentId]['rarity']