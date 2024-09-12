from base.helpers import *

class RemoveHeroesFromBuildings:
  def convertModelData( self, env, acc, md, dict ):
    for heroId in md.HeroesKeeper:  
      hero = md.getHeroByID( heroId )
      for constructionRemId in hero.InBuildings.keys():
        hero.InBuildings.remove( constructionRemId )
    
    for constructionId in md.ConstructionsKeeper:
      construction = md.getConstructionByID( constructionId )
      for heroRemId in construction.HeroesInBuilding.keys():
        construction.HeroesInBuilding.remove( heroRemId )

    return md, acc.db