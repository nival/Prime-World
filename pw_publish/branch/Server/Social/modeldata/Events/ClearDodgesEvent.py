from helpers import *

class ClearDodgesEvent:
  def convertModelData( self, acc, sd, config, stats ):
    info("ClearDodgesEvent: auid=%r" % acc.db.auid)
    acc.model.clearDodges()
    return acc.model  