# -*- coding: utf-8 -*-

from enums.RollEventRuleType import RollEventRuleType
from modeldata.collects import Set
from RollEventItem import RollEventItem


class RollEventRule_base(object):
    def serializeToFile(self, file, name):
        pass

    def load_from_db_dict(self, config_data, db_dict):
        """

        :param db_dict:
        :type db_dict: dict
        :return:
        """
        _dict = self.__dict__  # type: dict
        _dict['Description'] = db_dict.get('description', '')
        _dict['RuleType'] = db_dict.get('ruleType', RollEventRuleType.Simple)
        _dict['Title'] = db_dict.get('title', '')

        price_dict = db_dict.get('price')  # type: dict
        price = _dict['Price']
        price.load_from_db_dict(price_dict)

        rewards_data = db_dict.get('rewards')  # type: list
        rewards = _dict['Rewards']  # type: Set
        for item_data in rewards_data:
            item, _ = config_data.newRollEventItem()
            item.load_from_db_dict(item_data)
            rewards.add(item)

        reforge_sources_data = db_dict.get('reforgeSource')  # type: list
        reforge_sources = _dict['ReforgeSources']  # type: Set
        for item_data in reforge_sources_data:
            item, _ = config_data.newRollEventItem()
            item.load_from_db_dict(item_data)
            reforge_sources.add(item)
