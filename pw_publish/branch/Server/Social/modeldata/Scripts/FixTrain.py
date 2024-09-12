from base.helpers import *
from enums import *

class FixTrain:
  def convertModelData( self, env, acc, md, dict ): 
    try:
      trainMapInfo = md.LordInfo.MapsByType.get(MapType.Tutorial)
      
      if trainMapInfo and trainMapInfo.MapId == 'train':
        warn( "Find '%s' in map info..." % trainMapInfo.MapId )
      
        trainMapDesc = acc.SD.data['DefaultMaps']['Item'][MapType.Tutorial]
        if trainMapDesc and trainMapDesc['map']:
          info( "... replace with '%s'" % trainMapDesc['map']['dbid'] )
          trainMapInfo.MapId = trainMapDesc['map']['dbid']
    except:
      pass    
    return md, acc.db