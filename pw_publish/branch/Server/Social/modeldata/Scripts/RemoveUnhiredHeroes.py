from base.helpers import *

class RemoveUnhiredHeroes:
  def convertModelData( self, env, acc, md, dict ):
    listUnhiredHeroes = []
    for heroId in md.HeroesKeeper:
      hero = md.getHeroByID( heroId )
      if not hero.Hired:
        listUnhiredHeroes.append( hero )

    for hero in listUnhiredHeroes:
      hero.refCounter = 1
      md.Heroes.remove( hero )

    return md, acc.db