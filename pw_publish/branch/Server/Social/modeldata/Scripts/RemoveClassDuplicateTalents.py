from base.helpers import *
import pickle
from binascii import crc32


class RemoveClassDuplicateTalents:
    def convertModelData( self, env, acc, md, dict ):
                
        for talentId in md.UserInventory.keys():
            talent = md.getTalentByID( talentId )
            staticTalent = acc.SD.getStaticTalent(talent)
            if staticTalent != "None" and staticTalent != None:
                if staticTalent['rarity'] == "Class" and talent.defaultForHero == 0:
                    md.UserInventory.remove(talent.id)

        return md, acc.db
