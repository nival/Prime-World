from base.helpers import *

class UnloadUnhiredHeroesFromBuildings:
  def convertModelData( self, env, acc, md, dict ):
    for heroId in md.HeroesKeeper:  
      hero = md.getHeroByID( heroId )
      if hero:
        if hero.Hired == False:
          if len(hero.InBuildings) > 0:
            for constructionId in hero.InBuildings.keys():
              construction = md.getConstructionByID( constructionId )
              if construction:
                construction.HeroesInBuilding.remove( hero )
                hero.InBuildings.remove( construction )
    return md, acc.db