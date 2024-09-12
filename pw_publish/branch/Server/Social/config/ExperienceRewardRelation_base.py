# -*- coding: utf-8 -*-
from config.RollEventItem_base import RollEventItem_base


class ExperienceRewardRelation_base(object):
    def serializeToFile(self, file, name):
        pass

    def load_from_db_dict(self, config_data, db_dict):
        """

        :param db_dict:
        :type db_dict: dict
        :return:
        """
        _dict = self.__dict__  # type: dict

        _dict['Experience'] = db_dict.get('experience', '')
        _dict['RewardCount'] = db_dict.get('rewardCount', '')
        _dict['IsMinor'] = db_dict.get('isMinor', False)
        _dict['Reward'].add(0, RollEventItem_base.get_and_fill_new_reward(config_data, db_dict.get('reward')))
