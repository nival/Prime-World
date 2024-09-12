# -*- coding: utf-8 -*-

class SeasonEventShopItem_base(object):
    def serializeToFile(self, file, name):
        pass

    def load_from_db_dict(self, config_data, db_dict):
        """

        :param db_dict:
        :type db_dict: dict
        :return:
        """
        _dict = self.__dict__  # type: dict

        _dict['Title'] = db_dict.get('name', '')
        _dict['Image'] = db_dict.get('image', '')

        _dict['Cost'] = db_dict.get('cost', -1)
        #_dict['RewardB'].add(0, RollEventItem_base.get_and_fill_new_reward(config_data, db_dict.get('rewardB')))
        _dict['LootboxPersistentId'] = db_dict.get('lootboxId')
        _dict['Limit'] = db_dict.get('limit', -1)
