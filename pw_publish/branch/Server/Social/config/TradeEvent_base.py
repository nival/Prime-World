# -*- coding: utf-8 -*-

class TradeEvent_base(object):
    def serializeToFile(self, file, name):
        pass

    def load_from_db_dict(self, config_data, persistent_id, end_time, db_dict):
        _dict = self.__dict__

        _dict['_modelChangeWriter'] = None
        _dict['_writeChanges'] = False

        _dict['Title'] = db_dict.get('title', '')
        _dict['Text'] = db_dict.get('text', '')
        _dict['PersistentId'] = persistent_id
        _dict['EndTimestamp'] = end_time

        _dict['ExperienceCurrencyName'] = db_dict.get('experienceCurrencyName', '')
        _dict['Guid'] = db_dict.get('guid', -1)
        _dict['CompletionTalentId'] = db_dict.get('completionTalentId', '')
        _dict['CompletionTalentRatio'] = db_dict.get('completionTalentRatio', -1)
        _dict['RewardsBlockTitle'] = db_dict.get('rewardsBlockTitle', '')

        _dict['BannerUrl'] = db_dict.get('bannerUrl', '')

        tradeEventGroups = _dict['TradeEventGroups']
        groupsData = db_dict.get('tradeEventGroups', [])
        for item_data in enumerate(groupsData):
            item, _ = config_data.newTradeEventGroup()
            item.load_from_db_dict(config_data, item_data[1])
            tradeEventGroups.add(item_data[0], item)

        experienceRelations = _dict['ExperienceRewardRelations']
        experienceRelationsData = db_dict.get('experienceRewardRelations', [])
        for item_data in enumerate(experienceRelationsData):
            item, _ = config_data.newExperienceRewardRelation()
            item.load_from_db_dict(config_data, item_data[1])
            experienceRelations.add(item_data[0], item)

        ratingRewardRelations = _dict['WorldRatingRewardRelations']
        ratingRewardRelationsData = db_dict.get('worldRatingRewardRelations', [])
        for item_data in enumerate(ratingRewardRelationsData):
            item, _ = config_data.newWorldRatingRewardRelation()
            item.load_from_db_dict(config_data, item_data[1])
            ratingRewardRelations.add(item_data[0], item)

