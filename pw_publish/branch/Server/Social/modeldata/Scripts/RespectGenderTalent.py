from base.helpers import *
from binascii import crc32   # zlib version is not cross-platform

class RespectGenderTalent:
    def convertModelData( self, env, acc, md, dict ): 
        for talId in md.ItemsKeeper:
            tal = md.getTalentByID( talId )
            if tal.PersistentId == crc32('Gender_F_1'):
                tal.PersistentId = crc32('Gender_M_1')
        return md, acc.db