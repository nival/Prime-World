import os, sys
sys.path.append('../../')
sys.path.append('../../base')
sys.path.append('../../cfg')
from modeldata.MultiStaticData import MultiStaticData
from config.MultiConfig import MultiConfig

if len(sys.argv) > 1:

  fame = int(sys.argv[1])

  options_xdb_path = "../../xdb/ExportedSocialData.xml"
  config = MultiConfig()
  staticData = MultiStaticData( options_xdb_path, config.getMainConfig() ).getMainSD()
  print "Fame", fame, "= lord level", staticData.getFameLevel( fame )
  exit(0)

print "Usage GetLordLevelByFame.py fame_points"
