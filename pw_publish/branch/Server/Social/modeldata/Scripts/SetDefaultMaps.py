import time
from enums import *

class SetDefaultMaps:
  def convertModelData( self, env, acc, md, dict ): 
    try:
      md.createDefaultMaps(acc.SD)
      
      if hasattr( md.LordInfo, "TrainingMapName" ):
        trainMapId = md.LordInfo.TrainingMapName
      else:
        trainMapId = str(dict["ModelData"]["LordInfo"]["LordInfo"]["TrainingMapName"])
      
      trainMapInfo = md.LordInfo.MapsByType.get(MapType.Tutorial)
      if trainMapInfo:
        trainMapInfo.MapId = trainMapId
        trainMapInfo.Enabled = True
    except KeyError:
      pass    
    return md, acc.db