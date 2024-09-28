# -*- coding: utf-8 -*-

from enums.RollEventItemType import RollEventItemType


class RollEventItem_base(object):
    def serializeToFile(self, file, name):
        pass

    def load_from_db_dict(self, db_dict):
        """

        :param db_dict:
        :type db_dict: dict
        :return:
        """
        _dict = self.__dict__  # type: dict

        _dict['ItemType'] = db_dict.get('itemType', RollEventItemType.Resource)
        _dict['PersistentId'] = db_dict.get('persistentId')

        resource = _dict['Resource']
        resource.load_from_db_dict(db_dict.get('resource', {}))

        _dict['Ratio'] = db_dict.get('ratio')

    @staticmethod
    def get_and_fill_new_reward(config_data, item_data):
        if not item_data:
            return None

        item, _ = config_data.newRollEventItem()
        item.load_from_db_dict(item_data)
        return item
