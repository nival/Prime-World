# -*- coding: utf-8 -*-
from subaction import *

class UnsoulboundBlueAndViolet:
    def convertModelData(self, env, acc, md, idict):
          for talId in md.ItemsKeeper:
              talent = md.getTalentByID(talId)
              staticTalent = acc.SD.getStaticTalent(talent)
              if staticTalent and staticTalent['rarity'] in ["excellent", "magnificent"]:
                  if talent.Soulbound and talent.Soulbound.get():
                      talent.Soulbound = 0
                  if talent.GuildBankInfo and talent.GuildBankInfo.get():
                      talent.GuildBankInfo.HeroClassId = 0
          return md, acc.db