# -*- coding: utf-8 -*-
from config.RollEventItem_base import RollEventItem_base


class TradeGroupMember_base(object):
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

        _dict['RewardA'].add(0, RollEventItem_base.get_and_fill_new_reward(config_data, db_dict.get('rewardA')))
        _dict['RewardACost'] = db_dict.get('rewardACost', -1)
        _dict['RewardB'].add(0, RollEventItem_base.get_and_fill_new_reward(config_data, db_dict.get('rewardB')))
        _dict['RewardBCost'] = db_dict.get('rewardBCost', -1)
        _dict['CurrencyName'] = db_dict.get('currencyName', '')
        _dict['CurrencyCostPerExp'] = db_dict.get('currencyCostPerExp', -1)


