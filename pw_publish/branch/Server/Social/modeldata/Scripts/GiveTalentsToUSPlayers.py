from base.helpers import *
from binascii import crc32

TALENTS_FOR_WITCH = ['G129', 'G130', 'G238', 'G239', 'G145', 'G144', 'G191', 'G192', 'G195', 'G043', 'G079', 'G080',
                        'G081', 'G061', 'G169', 'G197', 'G198', 'G077', 'G078', 'G205', 'G206', 'G232', 'G233', 'G208', 'G207']
TALENTS_FOR_CRUSADER = ['G129', 'G130', 'G088', 'G238', 'G239', 'G145', 'G144', 'G009', 'G089', 'G195', 'G043', 'G079', 'G080',
                        'G081', 'G061', 'G169', 'G197', 'G198', 'G093', 'G078', 'G205', 'G206', 'G232', 'G233', 'G208', 'G207']

class GiveTalentsToUSPlayers:
  def convertModelData( self, env, acc, md, dict ):
    if not acc.db.IsUSAacc:
      return md, acc.db

    for heroId in md.HeroesKeeper:
      hero = md.getHeroByID( heroId )
      if (hero.PersistentId == crc32("crusader_A") or hero.PersistentId == crc32("crusader_B")) and hero.Hired:
        self.giveTalentsFromList(acc, TALENTS_FOR_CRUSADER, env)
      if (hero.PersistentId == crc32("witch")):
        self.giveTalentsFromList(acc, TALENTS_FOR_WITCH, env)

    return md, acc.db

  def giveTalentsFromList(self, acc, talentsList, env):
    for talId in talentsList:
      staticTalent = acc.SD.getStaticTalentByTalentId( crc32(talId) )
      if staticTalent:
        if staticTalent['rarity'] != "Class":
          talent_id = acc.model.addNewTalent()
          talent = acc.model.getTalentByID( talent_id )
          talent.IsNew = True
          talent.PersistentId = crc32(talId)
          acc.model.UserInventory.add( talent_id )