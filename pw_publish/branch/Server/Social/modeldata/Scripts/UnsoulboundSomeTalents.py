# -*- coding: utf-8 -*-
from subaction import *


class UnsoulboundSomeTalents:
    def convertModelData(self, env, acc, md, idict):
        for talId in md.ItemsKeeper:
            talent = md.getTalentByID(talId)
            staticTalent = acc.SD.getStaticTalent(talent)
            if staticTalent and staticTalent["persistentId"] in ("G401", "G399", "G562", "G563", "G564", "G565", "G566"):
                if talent.Soulbound and talent.Soulbound.get():
                    talent.Soulbound = 0
                if talent.GuildBankInfo and talent.GuildBankInfo.get():
                    talent.GuildBankInfo.HeroClassId = 0
                if talent.Owner:
                    hero = talent.Owner.get()
                    if hero:
                        hero.moveTalentFromTalentSetToLibrary(talent, talent.id)
        return md, acc.db
