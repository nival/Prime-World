import sys
sys.path.append('../')
sys.path.append('../..')
from logic.open_lootbox import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class open_lootbox_test:

    def open_lootbox_test( self, env ):
        model_data = env.acc.model
        static_lootbox_id = crc32("LB_Orange234_Set2")
        initial_inventory_len = len(model_data.UserInventory)
        initial_silver = model_data.Resources.Silver
        for retry in range(100):
            lootbox_id = model_data.addNewLootbox()
            lootbox = model_data.getLootboxByID(lootbox_id)
            lootbox.PersistentId = static_lootbox_id
            requests = [(Open_lootbox, OpenLootboxRequest(model_data,
                                                          {"rid": [retry*100], "lootbox_id": [lootbox_id]},
                                                          False))]
            env.execActions(requests)
            assert lootbox.Reward.IsApplied
        inventory_len = len(model_data.UserInventory)
        silver = model_data.Resources.Silver
        assert inventory_len > initial_inventory_len or silver > initial_silver

    def open_LampLootbox_test(self, env):
        model_data = env.acc.model
        static_lootbox_id = crc32("LB_TestRune")

        model_data.MarketingEventsInfo.LampEventInfo.dbId = ""

        for retry in range(1):
            lootbox_id = model_data.addNewLootbox()
            lootbox = model_data.getLootboxByID(lootbox_id)
            lootbox.PersistentId = static_lootbox_id
            requests = [(Open_lootbox,
                         OpenLootboxRequest(model_data, {"rid": [retry * 100], "lootbox_id": [lootbox_id]}, False))]
            env.execActions(requests)
            assert lootbox.Reward.IsApplied

        lampSettings = env.acc.getConfig().LampEventSettings
        assert model_data.MarketingEventsInfo.LampEventInfo.dbId == "/UI/Content/MarketingEvents/GoldLamp_200"
        assert model_data.MarketingEventsInfo.LampEventInfo.BonusLeft == lampSettings.BonusGold
        assert model_data.MarketingEventsInfo.LampEventInfo.TransactionsLeft == lampSettings.Transactions

    def open_ChampionRuneLootbox_test( self, env ):
        model_data = env.acc.model
        static_lootbox_id = crc32("LB_ChampionRune")
        initial_upgradeherotals = model_data.MarketingEventsInfo.UpgradeHeroTalentsInfo.UsesLeft
        for retry in range(100):
            lootbox_id = model_data.addNewLootbox()
            lootbox = model_data.getLootboxByID(lootbox_id)
            lootbox.PersistentId = static_lootbox_id
            requests = [(Open_lootbox, OpenLootboxRequest(model_data,
                                                          {"rid": [retry*100], "lootbox_id": [lootbox_id]},
                                                          False))]
            env.execActions(requests)
            assert lootbox.Reward.IsApplied
        upgradeherotals = model_data.MarketingEventsInfo.UpgradeHeroTalentsInfo.UsesLeft
        # print upgradeherotals
        assert upgradeherotals > initial_upgradeherotals

    def open_all_lootboxes_test(self, env):
        model_data = env.acc.model
        static_lootboxes = env.acc.SD.getStaticLootboxes()
        rid = 0
        for static_lootbox_id in static_lootboxes:
            static_lootbox = static_lootboxes[static_lootbox_id]
            info('INFO: Trying to open "%s"' % static_lootbox['persistentId'])
            lootbox_id = model_data.addNewLootbox()
            lootbox = model_data.getLootboxByID(lootbox_id)
            lootbox.PersistentId = static_lootbox_id
            requests = [(Open_lootbox, OpenLootboxRequest(model_data,
                                                          {"rid": [rid], "lootbox_id": [lootbox_id]},
                                                          False))]
            env.execActions(requests)
            assert lootbox.Reward.IsApplied
            rid += 1

    def __create_NothingRollItem(self):
        item = {
            'ready': True,
            'classType': 'NothingRollItem',
        }
        return item

    def __create_RarityTalentListRollItem(self, rarity):
        item = {
            'ready': True,
            'classType': 'RarityTalentListRollItem',
            'rarity': rarity,
        }
        return item

    def __create_ResourceRollItem(self, currency_type, custom_currency_id):
        item = {
            'ready': True,
            'classType': 'ResourceRollItem',
            'itemsFromLord':[
                { 'level': 0, 'count': 1, 'deviation': 0, },
            ],
            'type': currency_type,
            'customCurrencyId': custom_currency_id,
        }
        return item

    def __create_RollContainer(self, mul):
        item = {
            'ready': True,
            'classType': 'RollContainer',
            'multiplicator': mul,
            'items': [
                #{ 'probability': ???, 'item': ???, },
            ],
        }
        return item

    def __create_TalentRollItem(self, talent_id):
        item = {
            'ready': True,
            'classType': 'TalentRollItem',
            'talent': talent_id,
        }
        return item

    def __create_TalentUpgradeRollItem(self):
        item = {
            'ready': True,
            'classType': 'TalentUpgradeRollItem',
            'talentItem': None,
            'upgradeTable': {
                'upgrades': [
                    #{ 'probability': ???, 'points': ???, },
                ],
            },
        }
        return item

    def __create_HeroRollItem(self, hero_id):
        item = {
            'ready': True,
            'classType': 'HeroRollItem',
            'hero': hero_id,
        }
        return item

    def __create_SkinRollItem(self, skin_id):
        item = {
            'ready': True,
            'classType': 'SkinRollItem',
            'skin': skin_id,
        }
        return item

    def __create_TalentUpgradeEntityRollItem(self, ent_id):
        item = {
            'ready': True,
            'classType': 'TalentUpgradeEntityRollItem',
            'entity': ent_id,
        }
        return item

    def __create_GoldRollItem(self, amount):
        item = {'ready': True, 'classType': 'GoldRollItem', 'count': toint(amount), }
        return item

    def __create_PremiumAccRollItem(self, amount):
        item = {'ready': True, 'classType': 'PremiumAccRollItem', 'days': toint(amount), }
        return item

    def __create_LampRollItem(self):
        item = {
            'ready': True,
            'classType': 'MarketingEventRollItem',
            'count': toint(0),
            'marketingEvent': {
                'classType': 'GoldLampEvent'
            },
            'persistentId': 'GoldLampItem_20'
        }
        return item

    def __is_hero_exist(self, model_data, persistent_id):
        for heroId in model_data.Heroes:
            hero = model_data.getHeroByID(heroId)
            if hero.PersistentId == persistent_id:
                return True
        return False

    def __is_talent_upgrade_entity_exist(self, model_data, persistent_id):
        for id in model_data.TalentUpgradeEntities:
            ent = model_data.getTalentUpgradeEntityByID(id)
            if ent.PersistentId == persistent_id:
                return True
        return False

    def test_rarityTalentRoll(self, env):
        model_data = env.acc.model
        lb_persistent_id = crc32('LB_Orange234_Set2')
        static_lootbox = env.acc.SD.getStaticLootboxById(lb_persistent_id)
        static_lootbox['rollContainer'] = self.__create_RarityTalentListRollItem('exclusive')
        _, lootbox = model_data.addLootbox(lb_persistent_id, env.acc)
        result = model_data.openLootbox(env.acc, static_lootbox)
        model_data.applyLootboxRoll(env.acc, env.I, env.I.STATS, '', lootbox, result)
        assert len(lootbox.Reward.Talents) == 1

    def test_resourceRoll(self, env):
        model_data = env.acc.model
        lb_persistent_id = crc32('LB_Orange234_Set2')
        static_lootbox = env.acc.SD.getStaticLootboxById(lb_persistent_id)
        roll_container = self.__create_RollContainer(1)
        roll_container['items'].append({'probability':-1, 'item':self.__create_ResourceRollItem('Silver', None)})
        roll_container['items'].append({'probability':-1, 'item':self.__create_ResourceRollItem('CustomCurrency', 'b')})
        roll_container['items'].append({'probability':-1, 'item':self.__create_ResourceRollItem('CustomCurrency', 'a')})
        static_lootbox['rollContainer'] = roll_container
        _, lootbox = model_data.addLootbox(lb_persistent_id, env.acc)
        result = model_data.openLootbox(env.acc, static_lootbox)
        model_data.applyLootboxRoll(env.acc, env.I, env.I.STATS, '', lootbox, result)
        assert lootbox.Reward.Resources.Silver == 1
        assert lootbox.Reward.Resources.Currencies['a'] == 1
        assert lootbox.Reward.Resources.Currencies['b'] == 1

    def test_containerMulRoll(self, env):
        model_data = env.acc.model
        lb_persistent_id = crc32('LB_Orange234_Set2')
        static_lootbox = env.acc.SD.getStaticLootboxById(lb_persistent_id)
        roll_container = self.__create_RollContainer(5)
        roll_container['items'].append({'probability': -1, 'item': self.__create_ResourceRollItem('Silver', None)})
        static_lootbox['rollContainer'] = roll_container
        _, lootbox = model_data.addLootbox(lb_persistent_id, env.acc)
        result = model_data.openLootbox(env.acc, static_lootbox)
        model_data.applyLootboxRoll(env.acc, env.I, env.I.STATS, '', lootbox, result)
        assert lootbox.Reward.Resources.Silver == 5

    def test_talentRoll(self, env):
        model_data = env.acc.model
        lb_persistent_id = crc32('LB_Orange234_Set2')
        static_lootbox = env.acc.SD.getStaticLootboxById(lb_persistent_id)
        static_lootbox['rollContainer'] = self.__create_TalentRollItem(crc32('G662'))
        _, lootbox = model_data.addLootbox(lb_persistent_id, env.acc)
        result = model_data.openLootbox(env.acc, static_lootbox)
        model_data.applyLootboxRoll(env.acc, env.I, env.I.STATS, '', lootbox, result)
        assert len(lootbox.Reward.Talents) == 1

    def test_hero_roll(self, env):
        model_data = env.acc.model
        lb_persistent_id = crc32('LB_Orange234_Set2')
        hero_persistent_id = crc32('rockman')
        static_lootbox = env.acc.SD.getStaticLootboxById(lb_persistent_id)
        static_lootbox['rollContainer'] = self.__create_HeroRollItem(hero_persistent_id)
        _, lootbox = model_data.addLootbox(lb_persistent_id, env.acc)
        result = model_data.openLootbox(env.acc, static_lootbox)
        assert not self.__is_hero_exist(model_data, hero_persistent_id)
        model_data.applyLootboxRoll(env.acc, env.I, env.I.STATS, '', lootbox, result)
        assert self.__is_hero_exist(model_data, hero_persistent_id)
        assert len(lootbox.Reward.Heroes) == 1

    def test_entity_roll_1(self, env):
        model_data = env.acc.model
        lb_persistent_id = crc32('LB_Orange234_Set2')
        ent_persistent_id = crc32('TalUpg_Abrasive10')
        static_lootbox = env.acc.SD.getStaticLootboxById(lb_persistent_id)
        static_lootbox['rollContainer'] = self.__create_TalentUpgradeEntityRollItem(ent_persistent_id)
        _, lootbox = model_data.addLootbox(lb_persistent_id, env.acc)
        result = model_data.openLootbox(env.acc, static_lootbox)
        assert not self.__is_talent_upgrade_entity_exist(model_data, ent_persistent_id)
        model_data.applyLootboxRoll(env.acc, env.I, env.I.STATS, '', lootbox, result)
        assert self.__is_talent_upgrade_entity_exist(model_data, ent_persistent_id)
        assert len(lootbox.Reward.TalentUpgradeEntities) == 1

    def test_skin_roll_1(self, env):
        model_data = env.acc.model
        lb_persistent_id = crc32('LB_Orange234_Set2')
        hero_persistent_id = crc32('rockman')
        skin_persistent_id = crc32('rockman_S2_A')
        static_lootbox = env.acc.SD.getStaticLootboxById(lb_persistent_id)
        static_lootbox['rollContainer'] = self.__create_SkinRollItem(skin_persistent_id)
        _, lootbox = model_data.addLootbox(lb_persistent_id, env.acc)
        result = model_data.openLootbox(env.acc, static_lootbox)
        assert not self.__is_hero_exist(model_data, hero_persistent_id)
        assert not model_data.isSkinOwned(skin_persistent_id, env.acc.SD)
        model_data.applyLootboxRoll(env.acc, env.I, env.I.STATS, '', lootbox, result)
        assert self.__is_hero_exist(model_data, hero_persistent_id)
        assert model_data.isSkinOwned(skin_persistent_id, env.acc.SD)
        assert len(lootbox.Reward.Heroes) == 1
        assert len(lootbox.Reward.Skins) == 1

    def test_skin_roll_2(self, env):
        model_data = env.acc.model
        lb_persistent_id = crc32('LB_Orange234_Set2')
        hero_persistent_id = crc32('firefox')
        skin_persistent_id = crc32('firefox_S3')
        static_lootbox = env.acc.SD.getStaticLootboxById(lb_persistent_id)
        static_lootbox['rollContainer'] = self.__create_SkinRollItem(skin_persistent_id)
        _, lootbox = model_data.addLootbox(lb_persistent_id, env.acc)
        result = model_data.openLootbox(env.acc, static_lootbox)
        assert self.__is_hero_exist(model_data, hero_persistent_id)
        assert not model_data.isSkinOwned(skin_persistent_id, env.acc.SD)
        model_data.applyLootboxRoll(env.acc, env.I, env.I.STATS, '', lootbox, result)
        assert self.__is_hero_exist(model_data, hero_persistent_id)
        assert model_data.isSkinOwned(skin_persistent_id, env.acc.SD)
        assert len(lootbox.Reward.Heroes) == 0
        assert len(lootbox.Reward.Skins) == 1

    def test_gold_roll(self, env):
        model_data = env.acc.model

        model_data.updateBalanceInfo(env.acc, env.I.BILL)
        gold = model_data.Resources.Gold

        lb_persistent_id = crc32('LB_Orange234_Set2')
        static_lootbox = env.acc.SD.getStaticLootboxById(lb_persistent_id)
        roll_container = self.__create_RollContainer(1)
        roll_container['items'].append({'probability': -1, 'item': self.__create_GoldRollItem(5)})
        static_lootbox['rollContainer'] = roll_container
        _, lootbox = model_data.addLootbox(lb_persistent_id, env.acc)
        result = model_data.openLootbox(env.acc, static_lootbox)

        model_data.applyLootboxRoll(env.acc, env.I, env.I.STATS, '', lootbox, result)
        model_data.updateBalanceInfo(env.acc, env.I.BILL)

        assert model_data.Resources.Gold == gold + 5

    def test_premium_acc_roll(self, env):
        model_data = env.acc.model

        assert model_data.LordInfo.PremiumAccountStart == 0
        assert model_data.LordInfo.PremiumAccountEnd == 0

        lb_persistent_id = crc32('LB_Orange234_Set2')
        static_lootbox = env.acc.SD.getStaticLootboxById(lb_persistent_id)
        roll_container = self.__create_RollContainer(1)
        roll_container['items'].append({'probability': -1, 'item': self.__create_PremiumAccRollItem(5)})
        static_lootbox['rollContainer'] = roll_container
        _, lootbox = model_data.addLootbox(lb_persistent_id, env.acc)
        result = model_data.openLootbox(env.acc, static_lootbox)

        model_data.applyLootboxRoll(env.acc, env.I, env.I.STATS, '', lootbox, result)

        assert model_data.LordInfo.PremiumAccountEnd - model_data.LordInfo.PremiumAccountStart == 5 * 24 * 60 * 60
        assert model_data.IsPremiumAccount()

    def test_lamp_roll(self, env):
        model_data = env.acc.model

        assert model_data.LordInfo.PremiumAccountStart == 0
        assert model_data.LordInfo.PremiumAccountEnd == 0

        model_data.MarketingEventsInfo.LampEventInfo.dbId = ""

        lb_persistent_id = crc32('LB_Orange234_Set2')
        static_lootbox = env.acc.SD.getStaticLootboxById(lb_persistent_id)
        roll_container = self.__create_RollContainer(1)
        roll_container['items'].append({'probability': -1, 'item': self.__create_LampRollItem()})
        static_lootbox['rollContainer'] = roll_container
        _, lootbox = model_data.addLootbox(lb_persistent_id, env.acc)
        result = model_data.openLootbox(env.acc, static_lootbox)

        model_data.applyLootboxRoll(env.acc, env.I, env.I.STATS, '', lootbox, result)

        lampSettings = env.acc.getConfig().LampEventSettings
        assert model_data.MarketingEventsInfo.LampEventInfo.dbId == "/UI/Content/MarketingEvents/GoldLamp_20"
        assert model_data.MarketingEventsInfo.LampEventInfo.BonusLeft == lampSettings.BonusGold
        assert model_data.MarketingEventsInfo.LampEventInfo.TransactionsLeft == lampSettings.Transactions
