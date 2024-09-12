# -*- coding: utf-8 -*-

class TradeEventGroup_base(object):
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

        tradeGroupMembers = _dict['TradeGroupMembers']
        tradeGroupMembersData = db_dict.get('tradeGroupMembers', [])
        for item_data in enumerate(tradeGroupMembersData):
            item, _ = config_data.newTradeGroupMember()
            item.load_from_db_dict(config_data, item_data[1])
            tradeGroupMembers.add(item_data[0], item)
