# -*- coding: utf-8 -*-

class SeasonEventShopGroup_base(object):
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

        items = _dict['Items']
        groupItemsData = db_dict.get('items', [])
        for item_data in enumerate(groupItemsData):
            item, _ = config_data.newSeasonEventShopItem()
            item.load_from_db_dict(config_data, item_data[1])
            items.add(item_data[0], item)