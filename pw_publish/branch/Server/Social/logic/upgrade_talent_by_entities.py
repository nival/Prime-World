#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.UpgradeTalentByEntityRequest import *
from StatisticCore.ttypes import TalentChangeOperation, TalentInfo, TalentChangeInfo
from modeldata.change_applicator import ModelChangeApplicator
import guild.GuildData as GuildData

CATALISTS_LIMIT = 2

class Upgrade_talent_by_entities( SubAction, UpgradeTalentByEntityRequest ):
    action = "upgrade_talent_by_entities"

    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
          return

        self.target_talent = self.arguments.target_talent

        # if not self.acc.getConfig().IS_REFORGE_ACTIVE:
        #     self.errorResponse("Reforge is not permitted")
        #     return
        static_talent = self.acc.SD.getStaticTalent(self.target_talent)
        if not static_talent:
            self.response["callback"] = ["upgrade_talent_by_entities"]
            self.errorResponse("Target talent with persistent Id {0} wasn't found in StaticData".format(self.target_talent.PersistentId))
            return

        # тут уровень исчесляется от 0 и надо это иметь ввиду сравнивая его с некторыми данными
        current_talent_level = self.acc.SD.getTalentLevel(self.target_talent)

        log("UpgradeTalentByEntityRequest: tal_info: persistentId={0}, level={1}".format(self.target_talent.PersistentId, current_talent_level))

        points_to_level_map = self.acc.SD.getTalentPointsToLevel(static_talent)
        if len(points_to_level_map) <= current_talent_level:
            self.response["callback"] = ["upgrade_talent_by_entities"]
            self.errorResponse("Target talent with persistent Id {0} can't be upgraded to level {1}".format(self.target_talent.PersistentId, current_talent_level))
            return

        rune = None
        catalysts = []
        to_remove_ents = []

        for entity_id in self.arguments.entities:
            if entity_id not in self.acc.model.TalentUpgradeEntities.keys():
                self.response["callback"] = ["upgrade_talent_by_entities"]
                self.errorResponse("Wrong entity")
                return

            entity = self.acc.model.getTalentUpgradeEntityByID(entity_id)
            if not entity:
                self.response["callback"] = ["upgrade_talent_by_entities"]
                self.errorResponse("Wrong entity")
                return

            to_remove_ents.append(entity)

            static_entity = self.acc.SD.getStaticTalentUpgradeEntityById(entity.PersistentId)
            if not static_entity:
                self.response["callback"] = ["upgrade_talent_by_entities"]
                self.errorResponse("Entity with persistent Id {0} wasn't found in StaticData".format(entity.PersistentId))
                return

            if static_entity['type'] == TalentUpgradeEntityType.Rune:

                # допустимый уровень таланта в данных энтити задан от 1 и его надо привести к шкале уровня таланта, т.е. вычесть 1
                log("UpgradeTalentByEntityRequest: rune_info: persistentId={0}, level={1}".format(
                    static_entity['persistentId'], static_entity['talentLevelLimit']-1))

                if current_talent_level > static_entity['talentLevelLimit'] - 1:
                    self.response["callback"] = ["upgrade_talent_by_entities"]
                    self.errorResponse("This entity [{0}] can be applied to talents with level<={1}, talent level is {2}".format(entity.PersistentId, static_entity['talentLevelLimit'], current_talent_level))
                    return

                if rune is None:
                    rune = static_entity
            else:
                if len(catalysts) < CATALISTS_LIMIT:
                    catalysts.append(static_entity)

        if rune is None:
            self.response["callback"] = ["upgrade_talent_by_entities"]
            self.errorResponse("Entity with type Rune is required to upgrade talents")
            return

        probability = rune['probability']
        for catalyst in catalysts:
            probability += catalyst['probability']

        chance = self.acc.SD.getValueInRange(self.makeAccRandom(), 1, 100)
        success = False
        if chance <= probability:
            success = True
            points_before = self.target_talent.Points
            self.target_talent.Points = points_to_level_map[current_talent_level]
            # Обновим статистику для нашего таланта (PF-87260)
            talInfo = TalentInfo(self.target_talent.PersistentId, self.target_talent.getID(),
                                 getBoundHeroClassId(self.target_talent))
            data = "points before: %d, points after %d" % (points_before, self.target_talent.Points)
            self.I.STATS.addTalentChange(self.acc.db.auid, talInfo, TalentChangeOperation.UpgradeByEntity, data)

            # update talent info in a guild bank if it was taken from a guild
            if self.target_talent.GuildBankInfo.get() and self.target_talent.GuildBankInfo.OwnerId != self.acc.auid and self.target_talent.GuildBankInfo.OwnerId != 0:
                hero_persistent_id = self.target_talent.GuildBankInfo.HeroClassId
                if self.target_talent.Soulbound.get():
                    hero_persistent_id = self.target_talent.Soulbound.PersistentId
                self.I.GS.guildTalentInfoUpdate(self.acc, self.target_talent.GuildBankInfo.GuildTalentId,
                                                self.target_talent.Points, hero_persistent_id, self.onUpdateGuildData)

        for ent in to_remove_ents:
            static_entity = self.acc.SD.getStaticTalentUpgradeEntityById(ent.PersistentId)
            if static_entity:
                data = "tal_upg_entity used: pId={0}, type={1}, talPersId={2}, success={3}".format(
                    static_entity['persistentId'],
                    static_entity['type'],
                    self.target_talent.PersistentId,
                    success)
                self.I.STATS.addTalentChange(self.acc.db.auid,
                                             TalentInfo(ent.PersistentId, ent.id, 0),
                                             TalentChangeOperation.EntityUsedForUpgrade, data)
            self.acc.model.TalentUpgradeEntities.remove(ent.id)  # так вроде правилнее удалять

        self.response["callback"] = ["upgrade_talent_by_entities"]
        self.response["ok"] = 1  # success
        self.fin()

    @model_callback
    @action_timing
    def onUpdateGuildData(self, response):
        if response:
            info("onUpdateGuildData response: %s" % self.I.MD.pretty(response))
            guild_data_changes = response.get("GuildData") or []
            if guild_data_changes:
                try:
                    ModelChangeApplicator.apply(self.acc, "guilddata", GuildData, guild_data_changes)
                except:
                    catch()
            self.acc.pending_events.append({"GuildData": {"GuildData": guild_data_changes}})
            if self.acc.pending_handler:
                self.acc.pending_handler()