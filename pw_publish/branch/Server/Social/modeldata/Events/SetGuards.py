from base.helpers import *
from binascii import crc32

class SetGuards:
  def convertModelData( self, acc, sd, config, stats ):
    for heroId in acc.model.HeroesKeeper:  
      hero = acc.model.getHeroByID( heroId )
      if hero:
        if hero.Hired == True:
          hero.Master = True
          hero.EpicWins = 42
          
    return acc.model    
