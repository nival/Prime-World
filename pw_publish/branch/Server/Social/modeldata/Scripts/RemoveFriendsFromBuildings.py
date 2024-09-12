from base.helpers import *

class RemoveFriendsFromBuildings:
  def convertModelData( self, env, acc, md, dict ):
    for constructionId in md.ConstructionsKeeper:
      construction = md.getConstructionByID( constructionId )
      construction.FriendsBonus = 0.0
      if construction.get("FriendsInBuilding"):
        while len(construction.FriendsInBuilding):
          construction.FriendsInBuilding.pop()
    return md, acc.db