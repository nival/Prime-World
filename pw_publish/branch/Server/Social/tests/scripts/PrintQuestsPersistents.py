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
  for talId in staticData.data['Quests'].keys():
    if persId == talId:
      print talId, staticData.data['Quests'][talId]['persistentId']
      break

else:
  for talId in staticData.data['Quests'].keys():
    print talId, staticData.data['Quests'][talId]['persistentId']