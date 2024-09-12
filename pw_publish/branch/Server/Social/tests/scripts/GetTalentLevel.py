import os, sys
sys.path.append('../../')
sys.path.append('../../base')
sys.path.append('../../cfg')
from modeldata.MultiStaticData import MultiStaticData
from config.MultiConfig import MultiConfig

if len(sys.argv) > 2:

  talentName = int(sys.argv[1])
  talentPoints = int(sys.argv[2])

  options_xdb_path = "../../xdb/ExportedSocialData.xml"
  config = MultiConfig()
  staticData = MultiStaticData( options_xdb_path, config.getMainConfig() ).getMainSD()

  for talId in staticData.data['Talents'].keys():
    if talentName == talId:
      print talentName, talentPoints, staticData.getTalentLevelByPoints( talentPoints, staticData.data['Talents'][talId] )+1
      exit(0)
  print "Not found"

print "Usage GetTalentLevel.py talId points"
