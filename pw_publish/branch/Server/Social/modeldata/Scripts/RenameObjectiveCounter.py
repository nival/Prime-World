from base.helpers import *

class RenameObjectiveCounter:
  def convertModelData( self, env, acc, md, dict ): 
    for objectiveId in md.ObjectivesKeeper.keys():
      objective = md.getObjectiveByID(objectiveId)
      try:
        if hasattr( objective, "lastUpdatedTime" ):
          objective.lastEventId = objective.lastUpdatedTime
        else:
          objective.lastEventId = dict["ModelData"]["ObjectivesKeeper"]["Keeper"][str(objective.getID())]["Objective"]["lastUpdatedTime"]
      except KeyError:
        pass
    return md, acc.db