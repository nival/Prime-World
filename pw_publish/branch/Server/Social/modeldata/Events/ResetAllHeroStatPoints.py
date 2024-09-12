from base.helpers import *

class ResetAllHeroStatPoints:
  def convertModelData( self, acc, sd, config, stats ):
    for heroId in acc.model.HeroesKeeper:  
      hero = acc.model.getHeroByID( heroId )
      if hero:
        for i in xrange(len(hero.TalentSets)):
          if hero.Hired == True:
            hero.TalentSets[i].Stats.Strength = 0
            hero.TalentSets[i].Stats.Intellect = 0
            hero.TalentSets[i].Stats.Agility = 0
            hero.TalentSets[i].Stats.Cunning = 0
            hero.TalentSets[i].Stats.Fortitude = 0
            hero.TalentSets[i].Stats.Will = 0
            hero.TalentSets[i].Stats.Health = 0
            hero.TalentSets[i].Stats.Mana = 0
            statpoints  = 0
            for lvl in xrange( 0, sd.getHeroExpLevel( hero.Experience ) + 1 ):
              statpoints += sd.getHeroStatPoints( lvl )
            hero.TalentSets[i].Stats.StatPoints = statpoints
            hero.CalcForce( acc.model, None, acc, i )

    return acc.model    