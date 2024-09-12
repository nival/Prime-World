# -*- coding: utf-8 -*-
from config.RollEventItem_base import RollEventItem_base


class WorldRatingRewardRelation_base(object):
    def serializeToFile(self, file, name):
        pass

    def load_from_db_dict(self, config_data, db_dict):
        """

        :param db_dict:
        :type db_dict: dict
        :return:
        """
        _dict = self.__dict__  # type: dict

        _dict['WorldPosition'] = db_dict.get('worldPosition', 0)
        _dict['RewardCount'] = db_dict.get('rewardCount', 0)
        _dict['Reward'].add(0, RollEventItem_base.get_and_fill_new_reward(config_data, db_dict.get('reward')))