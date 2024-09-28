# -*- coding: utf-8 -*-
from base.helpers import *

class ConvertGuildBankInfo:
    def convertModelData( self, env, acc, md, dict ): 
        for talentId in md.ItemsKeeper:
            talent = md.getTalentByID( talentId )
            try:
                if type(dict["ModelData"]["ItemsKeeper"]["Keeper"][str(talent.id)]["Talent"]["GuildBankInfo"]) is int:
                    continue
                talent.GuildBankInfo.__dict__["object"] = 0
                if dict["ModelData"]["ItemsKeeper"]["Keeper"][str(talent.id)]["Talent"]["GuildBankInfo"]["GuildBankInfo"]["GuildAuid"]:
                    gbi, gbi_id = md.newGuildBankInfo()
                    gbi.GuildAuid = int(dict["ModelData"]["ItemsKeeper"]["Keeper"][str(talent.id)]["Talent"]["GuildBankInfo"]["GuildBankInfo"]["GuildAuid"])
                    gbi.GuildTalentId = int(dict["ModelData"]["ItemsKeeper"]["Keeper"][str(talent.id)]["Talent"]["GuildBankInfo"]["GuildBankInfo"]["GuildTalentId"])
                    gbi.OwnerId = int(dict["ModelData"]["ItemsKeeper"]["Keeper"][str(talent.id)]["Talent"]["GuildBankInfo"]["GuildBankInfo"]["OwnerId"])
                    gbi.HeroClassId = int(dict["ModelData"]["ItemsKeeper"]["Keeper"][str(talent.id)]["Talent"]["GuildBankInfo"]["GuildBankInfo"]["HeroClassId"])
                    talent.GuildBankInfo = gbi_id
            except KeyError:
                pass
        return md, acc.db