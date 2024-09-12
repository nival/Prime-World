from StatisticCore.ttypes import TalentChangeOperation, TalentInfo

class SendAlreadyGatheredEntitiesToStats:
    def convertModelData( self, env, acc, md, dict ):
        for ent_id in md.TalentUpgradeEntities.keys():
            ent = md.getTalentUpgradeEntityByID(ent_id)
            static_entity = acc.SD.getStaticTalentUpgradeEntityById(ent.PersistentId)
            if static_entity:
                data = "tal_upg_entity from_lootbox: pId={0}, type={1}, lootboxId={2}".format(
                    static_entity['persistentId'], static_entity['type'], 0)
                env.iDict.STATS.addTalentChange(acc.db.auid,
                                            TalentInfo(ent.PersistentId, ent.id, 0),
                                            TalentChangeOperation.GetEntityFromLootbox, data)
        return md, acc.db