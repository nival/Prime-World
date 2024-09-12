# -*- coding: utf-8 -*-
# Automatically generated template file. Remove this string if you modify this file.

class DonateEventRange_base(object):
    def serializeToFile(self, file, name):
        pass

    def load_from_db_dict(self, config_data, db_dict):
        """

        :param db_dict:
        :type db_dict: dict
        :return:
        """
        _dict = self.__dict__  # type: dict

        _dict['AmountFrom'] = db_dict.get('amountFrom', 0)
        _dict['AmountTo'] = db_dict.get('amountTo', -1)

        rewards = _dict['Rewards']  # type: Set
        for item_data in db_dict.get('rewards', []):  # type: dict
            item, _ = config_data.newDonateEventReward()
            item.load_from_db_dict(config_data, item_data)
            rewards.add(item)
