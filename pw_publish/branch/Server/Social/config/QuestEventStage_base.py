# -*- coding: utf-8 -*-
# Automatically generated template file. Remove this string if you modify this file.

class QuestEventStage_base(object):
    def serializeToFile(self, file, name):
        pass

    def load_from_db_dict(self, config_data, db_dict):
        _dict = self.__dict__
        _dict['Title'] = db_dict.get('title', '')
        _dict['Text'] = db_dict.get('text', '')
        _dict['Image'] = db_dict.get('image', '')

        rewards = _dict['Rewards']
        reward_dict = db_dict.get('reward', {})
        reward, _ = config_data.newRollEventItem()
        reward.load_from_db_dict(reward_dict)
        rewards.add(0, reward)

        steps = _dict['Steps']
        steps_data = db_dict.get('steps', [])
        for item_data in enumerate(steps_data):
            item, _ = config_data.newQuestEventStageStep()
            item.load_from_db_dict(config_data, item_data[1])
            steps.add(item_data[0], item)

        lose_rewards = _dict['LoseRewards']
        lose_reward_dict = db_dict.get('loseReward', {})
        lose_reward, _ = config_data.newRollEventItem()
        lose_reward.load_from_db_dict(lose_reward_dict)
        lose_rewards.add(0, lose_reward)
