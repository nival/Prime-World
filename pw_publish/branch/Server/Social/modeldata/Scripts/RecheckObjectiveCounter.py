from base.helpers import *

class RecheckObjectiveCounter:
  def convertModelData( self, env, acc, md, dict ): 
    for objectiveId in md.ObjectivesKeeper.keys():
      objective = md.getObjectiveByID(objectiveId)
      try:
        if md.StatisticEventId < objective.lastEventId:
          objective.lastEventId = md.StatisticEventId
      except KeyError:
        pass
    return md, acc.db