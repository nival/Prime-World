# -*- coding: utf-8 -*-
from base.helpers import *
from binascii import crc32
import gc

''' 
PF-107506
'''

selectedTalCrc = crc32('G662')
maxTalCount = 0

class ClearExtraTalents:
    def convertModelData( self, env, acc, md, dict ):

        try:
            tals_to_delete = []
            findCount = 0
            removedCount = 0

            for _, talent in md.UserInventory.iteritems():
                if talent.PersistentId != selectedTalCrc:
                    continue

                findCount += 1
                if findCount > maxTalCount:
                    tals_to_delete.append(talent)

            for talent in tals_to_delete:
                if talent.Owner and talent.Owner.get():
                    talent.Owner.moveTalentFromTalentSetToLibrary(talent, talent.Id)
                md.UserInventory.remove(talent)
                removedCount += 1

            info("ClearExtraTalents: Found G662 talents: {}. Removed {} ".format(findCount, removedCount))

        # Not enough time to normal test this
        except Exception as e:
            err(e)

        gc.collect()
        return md, acc.db
