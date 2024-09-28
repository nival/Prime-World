# -*- coding: utf-8 -*-
# Automatically generated template file. Remove this string if you modify this file.
from modeldata.ref import *

class TalentSet_base(object):
    def serializeToFile(self, file, name):
        pass

    def findSameTalent(self, persistentId):
        return any(t[1] == persistentId for t in self.Talents.iteritems())

    def getSameTalent(self, md, persistentId):
        talents = filter(lambda tid: md.getTalentByID(tid).PersistentId == persistentId, self.Talents.values())
        if talents:
            return md.getTalentByID(talents[0])

    def findTalent(self, md, talent):
        for slot, tid in self.Talents.iteritems():
            if tid == talent.id:
                return slot
    '''
    def addTalent(self, index, talent):
        talentRef  = Ref(self._modeldata, self._modeldata.ItemsKeeper, self.path, "slot"+str(index))
        talentRef.set(talent)
        self.Talents.add(index, talentRef)

    def removeTalent(self, index):
        self.Talents.remove(index)
    '''