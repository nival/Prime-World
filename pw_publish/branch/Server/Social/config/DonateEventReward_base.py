# -*- coding: utf-8 -*-
# Automatically generated template file. Remove this string if you modify this file.

class DonateEventReward_base(object):
    def serializeToFile(self, file, name):
        pass

    def load_from_db_dict(self, config_data, db_dict):
        """

        :param db_dict:
        :type db_dict: dict
        :return:
        """
        _dict = self.__dict__  # type: dict

        lootboxes = _dict['Lootboxes']  # type: SimpleList
        for item_data in db_dict.get('lootboxes', []):  # type: str
            lootboxes.append(item_data)
