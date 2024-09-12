from base.helpers import *
from binascii import crc32

class GiveHeroRating:
  def convertModelData( self, acc, sd, config, stats ):
    for heroId in acc.model.HeroesKeeper:  
      hero = acc.model.getHeroByID( heroId )
      if hero:
        if hero.Hired == True:
          hero.Rating = 1666
          
    return acc.model    
