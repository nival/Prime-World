#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys, math
from subaction import *
from modeldata.change_applicator import ModelChangeApplicator
import guild.GuildData as GuildData
from logic.requests.MergeTalentsRequest import MergeTalentsRequest
from StatisticCore.ttypes import TalentChangeOperation, TalentInfo, TalentChangeInfo


class Merge_talents(SubAction, MergeTalentsRequest):
    """action, который будет обрабатывать данный класс"""
    action = "merge_talents"

    @model_callback
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        modeldata = self.acc.model

        target_talent = self.arguments.target_talent
        source_talents = self.arguments.source_talents
        target_staticTalent = self.acc.SD.getStaticTalent(target_talent)

        talents_to_delete = []
        same_source_talents = []
        other_source_talents = []
        used_talents = set()
        total_points = target_talent.Points

        target_talent_max_points = self.acc.SD.getTalentMaxPoints(target_talent)

        for talentId in source_talents:
            if talentId in used_talents:
                continue
            used_talents.add(talentId)

            source_talent = self.acc.model.getTalentByID(talentId)
            if source_talent:
                if source_talent.GuildBankInfo and source_talent.GuildBankInfo.get() and source_talent.GuildBankInfo.OwnerId != self.acc.auid and source_talent.GuildBankInfo.OwnerId != 0:
                    self.errorResponse(EC.GUILD_BANK_TALENT_IMPROPER_USE, "Guild talent can't be merged! TalentOwnerId=%d" % source_talent.GuildBankInfo.OwnerId)
                    return

                if source_talent.Owner and source_talent.Owner.get():
                    self.errorResponse(EC.GUILD_BANK_TALENT_IMPROPER_USE, "Talent (PersistentId=%d)can't be merged! Owner.PersistentId=%d" % (source_talent.PersistentId, source_talent.Owner.PersistentId))
                    return


                source_staticTalent = self.acc.SD.getStaticTalent(source_talent)
                if source_staticTalent:
                    if source_staticTalent['rarity'] != "Class":
                        if source_talent.id in modeldata.UserInventory and not (source_talent.Owner and source_talent.Owner.get()):
                            if target_talent.PersistentId == source_talent.PersistentId:
                                same_source_talents.append(source_talent)
                            else:
                                other_source_talents.append(source_talent)
                        else:
                            self.errorResponse( "Talent " + source_staticTalent['persistentId'] + " wasn't found in UserInventory")
                            return
                    else:
                        self.errorResponse("Class talent can't be neither merged nor improved")
                        return

        needDoConsumption = True
        for same_source_talent in same_source_talents:
            total_points = self.acc.SD.recheckTotalPointsForMergeTalent(total_points, target_staticTalent, target_talent_max_points, same_source_talent)
            # сжигание не нужно, т.к. есть достаточное кол-во таких же талантов, чтобы заточиться до максимума путем слияния
            if target_talent_max_points <= total_points:
                needDoConsumption = False
                break

        total_points = target_talent.Points
        talent_level = self.acc.SD.getTalentLevel(target_talent)

        # сжигание нужно, т.к. есть "иные" таланты в кандидатах на сжигание, а "похожих" нет или их не хватило до макс заточки
        if needDoConsumption:
            # сжигаем таланты по одному - сначала непохожие
            for other_source_talent in other_source_talents:
                if target_talent_max_points <= total_points:
                    break

                # подсчитываем сколько очков за другой сжигаемый талант мы можем получить
                points_to_add = self.acc.SD.getConsumptionPoints(other_source_talent)
                staticSourceTalent = self.acc.SD.getStaticTalent(other_source_talent)

                # учтем какие-то новомодные бонусы к очкам у сжигаемого таланта
                points_to_add += staticSourceTalent['consumptionBonus']['constant']
                points_to_add += round(target_talent_max_points * staticSourceTalent['consumptionBonus']['percent'] / 100.0 - 1e-5)
                # talents with grade (stars) should be taken as talents grade1 * currentGrade

                # если сжигаемый талант уже заточен - сожжем его столько раз сколько у него дополнительных уровней
                current_level = self.acc.SD.getTalentLevel(other_source_talent) + 1
                points_to_add *= current_level

                # странная проверка не дающая сжигать таланты, которые дают 0 очков заточки
                if points_to_add:
                    total_points += points_to_add
                    talents_to_delete.append(other_source_talent)

                # если теперь очков достаточно для получения очередной звезды - проверяем хватит ли "похожих" талантов
                # чтобы прокачаться до максимума (5* на данный момент).
                # Если хватит - учтем их. Если нет - продолжим обычное сжигание.
                new_talent_level = self.acc.SD.getTalentLevelByPoints(total_points, target_staticTalent)
                if new_talent_level > talent_level:
                    tmp_total_points = total_points
                    tmp_talents_to_delete = []
                    for same_source_talent in same_source_talents:
                        if target_talent_max_points <= tmp_total_points:
                            break

                        tmp_total_points = self.acc.SD.getTotalMergePointsFromSameTalent(tmp_total_points, target_staticTalent,
                                                                                    target_talent_max_points, same_source_talent)
                        tmp_talents_to_delete.append(same_source_talent)
                        if target_talent_max_points <= tmp_total_points:
                            total_points = target_talent_max_points
                            talents_to_delete.extend(tmp_talents_to_delete)
                            break

            # теперь сжигаем "похожие" таланты
            for same_source_talent in same_source_talents:
                if target_talent_max_points <= total_points:
                    break

                total_points = self.acc.SD.getTotalMergePointsFromSameTalent(total_points, target_staticTalent,
                                                                            target_talent_max_points,
                                                                            same_source_talent)
                talents_to_delete.append(same_source_talent)
        else:
            # слияние "похожих"
            for same_source_talent in same_source_talents:
                if target_talent_max_points <= total_points:
                    break

                total_points = self.acc.SD.recheckTotalPointsForMergeTalent(total_points, target_staticTalent,
                                                                            target_talent_max_points, same_source_talent)
                talents_to_delete.append(same_source_talent)

        pearls = self.acc.SD.getTalentMergePrice(target_talent.Points, total_points, target_staticTalent)
        price = self.acc.model.createResourcesTable(Perl=pearls)
        if price:

            self.target_staticTalent = target_staticTalent
            self.target_talent = target_talent
            self.talents_to_delete = talents_to_delete
            self.price = price
            self.needGold = int(self.price.Gold)
            if total_points == target_talent.Points:
                self.errorResponse("No points where added.")
                return

            self.total_points = int(total_points) - target_talent.Points
            reason = "PW!TALENT_UPGRADE:" + str(self.target_talent.PersistentId)
            self.buy(self.price, self.onBuy, self.onBuyFunc, reason)
            return None
        else:
            self.errorResponse("Can't merge talents, bad price")
            return

    @model_callback
    def onBuyFunc(self, response):
        code = response["code"]
        if code == ibilling.ERROR_CODE_OK:
            self.doConfirmWriteOff(response)
            pointsBefore = self.target_talent.Points
            self.target_talent.addPoints(self.total_points, self.acc.SD, self.acc.model, self.I.WS, self.acc)
            target_staticTalent = self.acc.SD.getStaticTalent(self.target_talent)
            # Обновим статистику для нашего таланта (PF-87260)
            talInfo = TalentInfo(self.target_talent.PersistentId, self.target_talent.getID(),
                                 getBoundHeroClassId(self.target_talent))
            data = "points before: %d, points after %d" % (pointsBefore, self.target_talent.Points)
            self.I.STATS.addTalentChange(self.acc.db.auid, talInfo, TalentChangeOperation.Refining, data)
            for talent in self.talents_to_delete:
                self.I.STATS.addTalentChange(self.acc.db.auid,
                                             TalentInfo(talent.PersistentId, talent.id, getBoundHeroClassId(talent)),
                                             TalentChangeOperation.UseForRefining, target_staticTalent['persistentId'])
                talent.GuildBankInfo = None
                if talent.Owner and talent.Owner.get():
                    talent.Owner.moveTalentFromTalentSetToLibrary(talent, talent.id)
                self.acc.model.UserInventory.remove(talent)


            self.I.STATS.addResourcesChange(self.acc.auid, False, ResourceChangeItem.UpgradeTalent,
                                            "%r (id=%r)" % (self.target_talent.PersistentId, self.target_talent.id),
                                            self.price, self.acc.model.Resources, self.arguments.aftercontext)

            # update talent info in a guild bank if it was taken from a guild
            if self.target_talent.GuildBankInfo.get() and self.target_talent.GuildBankInfo.OwnerId != self.acc.auid and self.target_talent.GuildBankInfo.OwnerId != 0:
                HeroPersistentId = self.target_talent.GuildBankInfo.HeroClassId
                if self.target_talent.Soulbound.get():
                    HeroPersistentId = self.target_talent.Soulbound.PersistentId
                self.I.GS.guildTalentInfoUpdate(self.acc, self.target_talent.GuildBankInfo.GuildTalentId,
                                                self.target_talent.Points, HeroPersistentId, self.onUpdateGuildData)


            self.response["ok"] = 1  # success
        else:
            self.onBuyError(response, self.price.Perl)
            return

        self.fin()

    @action_timing
    def onBuy(self, response):
        self.onBuyFunc(response)

    @model_callback
    @action_timing
    def onUpdateGuildData(self, response):
        if response:
            info("onUpdateGuildData response: %s" % self.I.MD.pretty(response))
            GuildData_changes = response.get("GuildData") or []
            if GuildData_changes:
                try:
                    ModelChangeApplicator.apply(self.acc, "guilddata", GuildData, GuildData_changes)
                except:
                    catch()
            self.acc.pending_events.append({"GuildData": {"GuildData": GuildData_changes}})
            if self.acc.pending_handler:
                self.acc.pending_handler()
