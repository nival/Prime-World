# -*- coding: utf-8 -*-
import sys
from subaction import *
from StatisticCore.ttypes import TalentInfo, TalentChangeOperation
from logic.requests.RemoveTalentsRequest import RemoveTalentsRequest

class Remove_talents(SubAction, RemoveTalentsRequest):
    """action, который будет обрабатывать данный класс"""
    action = "remove_talents"

    @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return
                
        if len(self.arguments.talents) == 0:
            self.errorResponse("Talents is empty")
            return

        # В турнире продавать таланты не разрешается
        if self.I.Config.getMainConfig().TournamentSettings.IS_TOURNAMENT_SERVER and not self.I.Config.getMainConfig().TournamentSettings.CAN_SELL_TALENTS:
            self.errorResponse(EC.CANT_SELL_TALENTS_IN_TOURNAMENT, "Can't sell talents in tournament")
            return

        argTalents = set() # ловить дубликаты
        for talentId in self.arguments.talents:
            if talentId in argTalents:
                err("Remove_talents.onStart: Duplicate talent id %s passed. Player auid %s. All query talents: %s", talentId, self.acc.auid, str(self.arguments.talents))
                continue
            arg_talent = self.acc.model.getTalentByID(talentId)

            if arg_talent:
                if arg_talent.GuildBankInfo and arg_talent.GuildBankInfo.get() and arg_talent.GuildBankInfo.OwnerId != self.acc.auid and arg_talent.GuildBankInfo.OwnerId != 0:
                    self.errorResponse(EC.GUILD_BANK_TALENT_IMPROPER_USE, "Can't sell guild talents! TalentOwnerId=%d" % arg_talent.GuildBankInfo.OwnerId)
                    return

                if arg_talent.Owner and arg_talent.Owner.get() and arg_talent.Owner.InMatchmaking:
                    self.errorResponse(EC.HERO_IN_MATCHMAKING, "hero is in matchmaking")
                    return

                staticTalent = self.acc.SD.getStaticTalent(arg_talent)
                if staticTalent:
                    if staticTalent['rarity'] == "Class":
                        self.errorResponse("Class talents are not allowed to be deleted")
                        return
                else:
                    self.errorResponse("Talent not found")
                    return
                argTalents.add(talentId)
            else:
                self.errorResponse("Talent not found")
                return

        talent = self.acc.model.getTalentByID(self.arguments.talents[0])
        if talent:
            staticTalent = self.acc.SD.getStaticTalent(talent)
            if staticTalent:
                self.talentID = staticTalent['persistentId']
        else:
            self.talentID = ""

        for talentId in argTalents:
            arg_talent = self.acc.model.getTalentByID(talentId)
            staticTalent = self.acc.SD.getStaticTalent(arg_talent)
            arg_talent.GuildBankInfo = None
            if arg_talent.Owner and arg_talent.Owner.get():
                hero = arg_talent.Owner.get()
                hero.moveTalentFromTalentSetToLibrary(arg_talent, arg_talent.id)
                if arg_talent.defaultForHero and arg_talent.defaultForHero.get() and arg_talent.defaultForHero.PersistentId == hero.PersistentId:
                    if talent.PersistentId not in hero.removedDefaultTalents:
                        hero.removedDefaultTalents.append(talent.PersistentId)
                self.I.STATS.addTalentChange(self.acc.db.auid, TalentInfo(arg_talent.PersistentId, talentId, hero.PersistentId), TalentChangeOperation.Sell)
                for tsId in hero.TalentSets:
                    hero.CalcForce(self.acc.model, self.I.WS, self.acc, tsId)
            else:
                self.I.STATS.addTalentChange(self.acc.db.auid,
                                             TalentInfo(arg_talent.PersistentId, talentId, getBoundHeroClassId(arg_talent)),
                                             TalentChangeOperation.Sell)
            self.acc.model.UserInventory.remove(arg_talent)

            staticPrice = self.acc.SD.getTalentSellPrice(staticTalent)
            if staticPrice:
                self.acc.model.sell(staticPrice, self.acc)
                talentString = "%r (id=%r)" % (arg_talent.PersistentId, arg_talent.id)
                self.I.STATS.addResourcesChange(self.acc.auid, True, ResourceChangeItem.TalentSell, talentString, staticPrice, self.acc.model.Resources)
            
        self.acc.model.addStatisticEvent(StatisticEventType.TALENTS_REMOVE, self.talentID, len(self.arguments.talents))
        self.response["ok"] = 1 # success
        self.fin()
