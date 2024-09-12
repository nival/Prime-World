import os, sys
sys.path.append('../../')
sys.path.append('../../base')
sys.path.append('../../cfg')
sys.path.append('../../modeldata')
from StaticData import StaticData
from config.MultiConfig import MultiConfig


options_xdb_path = "../../xdb/ExportedSocialData.xml"
config = MultiConfig()
staticData = StaticData( options_xdb_path, config.getMainConfig() )

if len(sys.argv) > 1:
  persId = int(sys.argv[1])
  for heroId in staticData.data['Heroes'].keys():
    if persId == heroId:
      print heroId, staticData.data['Heroes'][heroId]['persistentId']
      break
  
else:
  for heroId in staticData.data['Heroes'].keys():
    print heroId, staticData.data['Heroes'][heroId]['persistentId']
