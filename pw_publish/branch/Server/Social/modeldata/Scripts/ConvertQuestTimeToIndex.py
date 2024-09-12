from base.helpers import *

class ConvertQuestTimeToIndex:
  def convertModelData( self, env, acc, md, dict ): 
    index = 0
    for eventId in md.StatisticEvents.keys():
      event = md.getStatisticEventByID(eventId)
      event.time = index
      index += 1

    md.StatisticEventId = index

    for objectiveId in md.ObjectivesKeeper.keys():
      objective = md.getObjectiveByID(objectiveId)
      objective.lastUpdatedTime = md.StatisticEventId         
    return md, acc.db