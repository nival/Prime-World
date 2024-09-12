#!/usr/bin/env python
# -*- coding: utf-8 -*-
# http://code.activestate.com/recipes/149368/
from base.helpers import *
from enums import SessionCheckType, DynamicQuestCheckType, CastleResources, DynamicQuestAwardType, TalentUpgradeEntityType

sys.path.append('..')

import gc
import xml.sax.handler
from binascii import crc32 


def xml2obj(src):
    non_id_char = re.compile('[^_0-9a-zA-Z]')
    def _name_mangle(name):
        return non_id_char.sub('_', name)


    def cleanTalents( tals ):
        for tal in tals['Item']:
            deltal = tal
            if 'talent' in tal:
                deltal = tal['talent']

            if 'talentRollGroups' in deltal:
                del deltal['talentRollGroups']
            if 'naftaCost' in deltal:
                del deltal['naftaCost']
            if 'devPoints' in deltal:
                del deltal['devPoints']
            if 'isGenderTalent' in deltal:
                del deltal['isGenderTalent']
            if 'isGenderTalent' in deltal:
                del deltal['isGenderTalent']
            if 'prerequisiteTalents' in deltal:
                del deltal['prerequisiteTalents']
            if 'upgradeLevel' in deltal:
                del deltal['upgradeLevel']
            if 'minLevel' in deltal:
                del deltal['minLevel']
            if 'budget' in deltal:
                del deltal['budget']
            if 'conditionFormulas' in deltal:
                del deltal['conditionFormulas']
            if 'caption' in deltal:
                del deltal['caption']
            if 'consumptionBonus' in deltal:
                del deltal['consumptionBonus']
            if 'classType' in deltal:
                del deltal['classType']
            if 'isTakenOnStart' in deltal:
                del deltal['isTakenOnStart']
            if 'rarity' in deltal:
                del deltal['rarity']
            if 'type' in deltal:
                del deltal['type']
            if 'passiveApplicators' in deltal:
                del deltal['passiveApplicators']
            if 'constants' in deltal:
                del deltal['constants']
            if 'dbid' in deltal:
                del deltal['dbid']
            if 'conflictingTalents' in deltal:
                del deltal['conflictingTalents']
            if 'mightyTalentSet' in deltal:
                del deltal['mightyTalentSet']



    def convertPrice( price ):
        if 'Gold' in price:
            price['Gold'] = int(price['Gold'])
        if 'Perl' in price:
            price['Perl'] = int(price['Perl'])
        if 'RedPerl' in price:
            price['RedPerl'] = int(price['RedPerl'])
        if 'Resource1' in price:
            price['Resource1'] = int(price['Resource1'])
        if 'Resource2' in price:
            price['Resource2'] = int(price['Resource2'])
        if 'Resource3' in price:
            price['Resource3'] = int(price['Resource3'])
        if 'Silver' in price:
            price['Silver'] = int(price['Silver'])
        if 'Population' in price:
            price['Population'] = int(price['Population'])
        if 'Resource1_Rare' in price:
            price['Resource1_Rare'] = int(price['Resource1_Rare'])
        if 'Resource2_Rare' in price:
            price['Resource2_Rare'] = int(price['Resource2_Rare'])
        if 'Resource3_Rare' in price:
            price['Resource3_Rare'] = int(price['Resource3_Rare'])
        if 'CWPoints_Player' in price:
            price['CWPoints_Player'] = int(price['CWPoints_Player'])
        if 'CWPoints_Clan' in price:
            price['CWPoints_Clan'] = int(price['CWPoints_Clan'])
        if 'Shard' in price:
            price['Shard'] = int(price['Shard'])
        if 'Currencies' in price:
            currencies_dict = {}
            if 'Item' in price['Currencies']:
                for item in price['Currencies']['Item']:
                    currencies_dict[item['Id']] = int(item['Value'])
            price['Currencies'] = currencies_dict


    def convertCommon( building ):
        del building['VisualChangingLevels']
        del building['OffsetA']
        del building['OffsetB']
        del building['Destroyable']
        del building['Movable']
        del building['SupportVisualGradesChanging']
        del building['IconPathB']
        del building['IconPathA']
        del building['ModelsPathB']
        del building['ModelsPathA']
        building['SellPricePercent'] = float( building['SellPricePercent'] )
        building['LevelRequired'] = int( building['LevelRequired'] )
        building['SectionsSize'] = int( building['SectionsSize'] )
        for item in building['Levels']['Item']:
            convertPrice( item['price'] )
            item['fame'] = int( item['fame'] )
        if building['GroupBuildingLimits']:
            for item in building['GroupBuildingLimits']['Item']:
                item['MaxNumberOfBuilding'] = int( item['MaxNumberOfBuilding'] )
        for item in building['SectionsLockedForBuilding']['Sections']['Item']:
            item['x'] = int( item['x'] )
            item['y'] = int( item['y'] )
        for item in building['SectionsLockedForDecorations']['Sections']['Item']:
            item['x'] = int( item['x'] )
            item['y'] = int( item['y'] )
   

    def convertHouseBuildings( SD ):
        for PersistentId in SD['Constructions']:
            construction = SD['Constructions'][PersistentId]
            if 'classType' in construction and construction['classType'] == "HouseBuilding":
                house = construction
                convertCommon( house )
                house['productionTimePeriod'] = int(house['productionTimePeriod'])
                house['minimalCollectTime'] = int(house['minimalCollectTime'])
                for item in house['HouseLevels']['Item']:
                    convertPrice(item['resourcesToProduce'])
                    convertPrice(item['totalProduceCapacity'])
                    convertPrice(item['boostPrice'])
                    item['fameToProduce'] = int(item['fameToProduce'])
                    item['currentLevel'] = int(item['currentLevel'])
                    item['currentMaxPopulation'] = int(item['currentMaxPopulation'])
                    item['cycle']['fameToProduce'] = int( item['cycle']['fameToProduce'] )
                    convertPrice( item['cycle']['priceToStart'] )
                    convertPrice( item['cycle']['resourcesToProduce'] )
                    item['cycle']['timeblock']['gold'] = int( item['cycle']['timeblock']['gold'] )
                    item['cycle']['timeblock']['time'] = int( item['cycle']['timeblock']['time'] )

    def convertPineTreeBuildings( SD ):
        for PersistentId in SD['Constructions']:
            construction = SD['Constructions'][PersistentId]
            if 'classType' in construction and construction['classType'] == "PineTreeBuilding":
                pineTree = construction
                convertCommon( pineTree )
                for item in pineTree['PineTreeLevels']['Item']:
                    item['currentLevel'] = int(item['currentLevel'])
                    item['cycle']['fameToProduce'] = int( item['cycle']['fameToProduce'] )
                    convertPrice( item['cycle']['priceToStart'] )
                    convertPrice( item['cycle']['resourcesToProduce'] )
                    item['cycle']['timeblock']['gold'] = int( item['cycle']['timeblock']['gold'] )
                    item['cycle']['timeblock']['time'] = int( item['cycle']['timeblock']['time'] )
                    
    def convertGuildBuildings( SD ):
        for PersistentId in SD['Constructions']:
            construction = SD['Constructions'][PersistentId]
            if 'classType' in construction and construction['classType'] == "GuildBuilding":
                guild = construction
                convertCommon( guild )   

    def convertLibraryBuildings( SD ):
        for PersistentId in SD['Constructions']:
            construction = SD['Constructions'][PersistentId]
            if 'classType' in construction and construction['classType'] == "LibraryBuilding":
                library = construction
                convertCommon( library )
                for item in library['LibraryLevels']['Item']:
                    item['currentLevel'] = int(item['currentLevel'])
                    item['additionalTalentSlots'] = int(item['additionalTalentSlots'])


    def convertStorageBuildings( SD ):
        for PersistentId in SD['Constructions']:
            construction = SD['Constructions'][PersistentId]
            if 'classType' in construction and construction['classType'] == "StorageBuilding":
                storage = construction
                convertCommon( storage )
                for item in storage['StorageLevels']['Item']:
                    item['currentLevel'] = int(item['currentLevel'])
                    convertPrice( item['additionalStorage'] )


    def convertBathBuildings( SD ):
        for PersistentId in SD['Constructions']:
            construction = SD['Constructions'][PersistentId]
            if 'classType' in construction and construction['classType'] == "Bath":
                bath = construction
                convertCommon( bath )
                bath['GoldBoostPrice'] = float( bath['GoldBoostPrice'] )
                for item in bath['BathCycles']['Item']:
                    item['cycleDuration'] = int(item['cycleDuration'])
                    item['restoringEnergy'] = int(item['restoringEnergy'])
                for item in bath['BathLevels']['Item']:
                    item['heroesCount'] = int(item['heroesCount'])
                    item['currentLevel'] = int(item['currentLevel'])
                    item['recoveryPriceDiscount'] = float(item['recoveryPriceDiscount'])
                    item['passiveEnergyRecoveryBoost'] = float(item['passiveEnergyRecoveryBoost'])


    def convertFirstBuyBuildings( SD ):
        for PersistentId in SD['Constructions']:
            construction = SD['Constructions'][PersistentId]
            if 'classType' in construction and construction['classType'] == "FirstBuyBuilding":
                firstBuy = construction
                convertCommon( firstBuy )
                for item in firstBuy['FirstBuyLevels']['Item']:
                    item['currentLevel'] = int(item['currentLevel'])
                    item['additionalTalentSlots'] = int(item['additionalTalentSlots'])
                    convertPrice( item['additionalStorage'] )
                    convertPrice( item['resources'] )
                    item['cycle']['fameToProduce'] = int(item['cycle']['fameToProduce'])
                    convertPrice( item['cycle']['priceToStart'] )
                    convertPrice( item['cycle']['resourcesToProduce'] )
                    item['cycle']['percents']['Item'] = map( lambda x: int(x), item['cycle']['percents']['Item'] )
                    item['cycle']['timeblock']['gold'] = int( item['cycle']['timeblock']['gold'] )
                    item['cycle']['timeblock']['time'] = int( item['cycle']['timeblock']['time'] )


    def convertHeroesBuildings( SD ):
        for PersistentId in SD['Constructions']:
            construction = SD['Constructions'][PersistentId]
            if 'classType' in construction and construction['classType'] == "HeroesBuilding":
                heroes = construction
                convertCommon( heroes )
                heroes['heroClass'] = int( heroes['heroClass'] )
                for item in heroes['HeroesBuildingLevels']['Item']:
                    item['currentLevel'] = int(item['currentLevel'])
                    item['discount'] = float( item['discount'] )
                    item['fameReqDecr'] = int(item['fameReqDecr'])
                    item['statBufValue'] = float(item['statBufValue'])
                    
    def convertTavernBuilding( SD ):
        for PersistentId in SD['Constructions']:
            construction = SD['Constructions'][PersistentId]
            if 'classType' in construction and construction['classType'] == "Tavern":
                tavern = construction
                convertCommon( tavern )   
                convertTavernQuest(tavern['patrollQuest'])   
                for item in tavern['tavernLevelQuests']['Item']:
                    for q in item['tavernQuests']['Item']:
                        convertTavernQuest(q)
                tavern['questRollRange'] = int(tavern['questRollRange'])                             
                for item in tavern['tavernLevels']['Item']:
                    item['heroesCount'] = int(item['heroesCount'])
                    item['currentLevel'] = int(item['currentLevel'])      
                    item['rewardCoefficient'] = float( item['rewardCoefficient'] )
                for item in tavern['tavernExpCoeffToHeroLevels']['Item']:
                    item['currentLevel'] = int(item['currentLevel'])
                    item['coefficient'] = float(item['coefficient'])                   
                    
    def convertTavernQuest(quest):
        if quest:
            quest['estimate']['time'] = int(quest['estimate']['time'])
            quest['estimate']['gold'] = int(quest['estimate']['gold'])
            convertPrice( quest['priceToStart'] )
            quest['energyDecrease'] = int(quest['energyDecrease'])
            if 'reward' in quest:
                quest['reward']['experience'] = int(quest['reward']['experience'] )
                quest['reward']['resourceRewardCount'] = int(quest['reward']['resourceRewardCount'] )
                if 'resource' in quest['reward']:
                    convertPrice(quest['reward']['resource'])
                if 'rollContainer' in quest['reward'] and quest['reward']['rollContainer'] and quest['reward']['rollContainer']['dbid']!='':
                    quest['reward']['rollContainer']['percents']['Item'] = map( lambda x: int(x), quest['reward']['rollContainer']['percents']['Item'] )
            quest['questStatCount'] = int(quest['questStatCount'])

    def convertTransmutationBuildings( SD ):
        for PersistentId in SD['Constructions']:
            construction = SD['Constructions'][PersistentId]
            if 'classType' in construction and construction['classType'] == "TransmutationBuilding":
                trans = construction
                convertCommon( trans )
                trans['time'] = int( trans['time'])
                trans['requiredLeveForReforging'] = int(trans['requiredLeveForReforging'])
                trans['requiredLeveForReforgingExclusiveTalents'] = int(trans['requiredLeveForReforgingExclusiveTalents'])
                for item in trans['TransmutationLevels']['Item']:
                    item['currentLevel'] = int(item['currentLevel'])
                    item['perlForBonuse'] = int(item['perlForBonuse'])
                    item['fameToProducePerCrystal'] = int(item['fameToProducePerCrystal'])
                    convertPrice( item['priceToStart'] )


    def converReforgePrices(SD):
        for rar in SD['ReforgeTalentPrices']:
            rar_price = SD['ReforgeTalentPrices'][rar]
            for points_price in rar_price['rerollPrices']['Item']:
                points_price['stars'] = int(points_price['stars'])
                convertPrice(points_price['priceWithoutSetFilter'])
                convertPrice(points_price['priceWithSetFilter'])
            convertPrice(rar_price['upgradePrice'])
            rar_price['talentsToUpgrade'] = int(rar_price['talentsToUpgrade'])


    def convertDecorBuildings( SD ):
        for PersistentId in SD['Constructions']:
            construction = SD['Constructions'][PersistentId]
            if 'classType' in construction and construction['classType'] == "Decoration":
                decor = construction
                convertCommon( decor )


    def convertProductionBuildings( SD ):
        for PersistentId in SD['Constructions']:
            construction = SD['Constructions'][PersistentId]
            if 'classType' in construction and construction['classType'] == "ProductionBuilding":
                production = construction
                convertCommon( production )
                production['productionTimePeriod'] = int(production['productionTimePeriod'])
                production['minimalCollectTime'] = int(production['minimalCollectTime'])
                for item in production['ProductionLevels']['Item']:
                    item['currentLevel'] = int(item['currentLevel'])
                    convertPrice(item['resourcesToProduce'])
                    convertPrice(item['totalProduceCapacity'])
                    convertPrice(item['boostPrice'])
                    item['fameToProduce'] = int(item['fameToProduce'])
                    if item['cycles']:
                        for cycle in item['cycles']['Item']:
                            cycle['fameToProduce'] = int(cycle['fameToProduce'])
                            convertPrice( cycle['priceToStart'] )
                            convertPrice( cycle['resourcesToProduce'] )
                            cycle['timeblock']['gold'] = int( cycle['timeblock']['gold'] )
                            cycle['timeblock']['time'] = int( cycle['timeblock']['time'] )

    def convertGoldProductionBuildings( SD ):
        for PersistentId in SD['Constructions']:
            construction = SD['Constructions'][PersistentId]
            if 'classType' in construction and construction['classType'] == "GoldProductionBuilding":
                goldHouse = construction
                convertCommon( goldHouse )
                for item in goldHouse['HouseLevels']['Item']:
                    item['currentLevel'] = int(item['currentLevel'])
                    item['currentMaxPopulation'] = int(item['currentMaxPopulation'])
                    item['cycle']['fameToProduce'] = int( item['cycle']['fameToProduce'])
                    convertPrice(item['cycle']['priceToStart'])
                    convertPrice(item['cycle']['resourcesToProduce'])
                    item['cycle']['timeblock']['gold'] = int(item['cycle']['timeblock']['gold'])
                    item['cycle']['timeblock']['time'] = int(item['cycle']['timeblock']['time'])

    def convertRerollShopBuildings( SD ):
        for PersistentId in SD['Constructions']:
            construction = SD['Constructions'][PersistentId]
            if 'classType' in construction and construction['classType'] == "RerollShopBuilding":
                shop = construction
                convertCommon( shop )

    def convertDynamicQuestsForTalentsToMaps( SD ):
        persistentIdsForbadeTalents = map(lambda x: str(x['persistentId']), SD['DynamicQuestForTalents']['ForbadeTalents']['Item'])
        SD['DynamicQuestForTalents']['ForbadeTalents'] = dict(zip(persistentIdsForbadeTalents, [None] * len(persistentIdsForbadeTalents)))
        # print 'ForbadeTalents: ' + str(SD['DynamicQuestForTalents']['ForbadeTalents'])

        if 'Item' in SD['DynamicQuestForTalents']['OverridenPricesMap']:
            persistentIdsTalents = map(lambda x: str(x['Talent']['persistentId']), SD['DynamicQuestForTalents']['OverridenPricesMap']['Item'])
            resourcesItems = map(lambda x: x['Resources'], SD['DynamicQuestForTalents']['OverridenPricesMap']['Item'])
            SD['DynamicQuestForTalents']['OverridenPricesMap'] = dict(zip(persistentIdsTalents, resourcesItems))
        else:
            SD['DynamicQuestForTalents']['OverridenPricesMap'] = {}
        # print 'OverridenPricesMap: ' + str(SD['DynamicQuestForTalents']['OverridenPricesMap'])

        raritiesInPriceMap = map(lambda x: str(x['ETalentRarity']), SD['DynamicQuestForTalents']['PricesMap']['Item'])
        resourcesItems = map(lambda x: x['Resources'], SD['DynamicQuestForTalents']['PricesMap']['Item'])
        SD['DynamicQuestForTalents']['PricesMap'] = dict(zip(raritiesInPriceMap, resourcesItems))
        # print 'PricesMap: ' + str(SD['DynamicQuestForTalents']['PricesMap'])

        if 'Item' in SD['DynamicQuestForTalents']['OverridenDifficultiesMap']:
            persistentIdsTalents = map(lambda x: str(x['Talent']['persistentId']), SD['DynamicQuestForTalents']['OverridenDifficultiesMap']['Item'])
            difficultyItems = map(lambda x: x['Difficulty'], SD['DynamicQuestForTalents']['OverridenDifficultiesMap']['Item'])
            SD['DynamicQuestForTalents']['OverridenDifficultiesMap'] = dict(zip(persistentIdsTalents, difficultyItems))
        else:
            SD['DynamicQuestForTalents']['OverridenDifficultiesMap'] = {}
        # print 'OverridenDifficultiesMap: ' + str(SD['DynamicQuestForTalents']['OverridenDifficultiesMap'])

        raritiesInPriceMap = map(lambda x: str(x['ETalentRarity']), SD['DynamicQuestForTalents']['DifficultiesMap']['Item'])
        difficultyItems = map(lambda x: x['Difficulty'], SD['DynamicQuestForTalents']['DifficultiesMap']['Item'])
        SD['DynamicQuestForTalents']['DifficultiesMap'] = dict(zip(raritiesInPriceMap, difficultyItems))
        # print 'DifficultiesMap: ' + str(SD['DynamicQuestForTalents']['DifficultiesMap'])

        difficultyInQuestsGroups = map(lambda x: str(x['Difficulty']), SD['DynamicQuestForTalents']['QuestsGroups']['Item'])
        questsInQuestsGroups = map(lambda x: x['Quests']['Item'], SD['DynamicQuestForTalents']['QuestsGroups']['Item'])
        SD['DynamicQuestForTalents']['QuestsGroups'] = dict(zip(difficultyInQuestsGroups, questsInQuestsGroups))
        # print 'QuestsGroups: ' + str(SD['DynamicQuestForTalents']['QuestsGroups'])

        # convert SD dynamicQuestsToTalents to GMTool view (convert str to ints,  convert others with specific rules)
        for questsGroups in SD['DynamicQuestForTalents']['QuestsGroups'].values():
            for questDict in questsGroups:
                for objectiveDict in questDict['DynamicObjectives']['Item']:
                    # may be repeat same quests that identical quests maybe is in different quests groups
                    # this check looks at quest converted status
                    if not isinstance(objectiveDict["QuestCheckType"], str):
                        continue

                    # get var with a name that equally DynamicQuestCheckType
                    objectiveDict["QuestCheckType"] = \
                        [value for key, value in DynamicQuestCheckType.__dict__.iteritems() if
                         key == objectiveDict["QuestCheckType"]][0]

                    # get var with a name that equally ResourceType
                    if objectiveDict["InstantCondition"]["ResourceType"]:
                        objectiveDict["InstantCondition"]["ResourceType"] = \
                        [value for key, value in CastleResources.__dict__.iteritems()
                         if key == objectiveDict["InstantCondition"]["ResourceType"]][0]

                    # response from GM tool have one str value - 'TotalValue'. Convert to true view
                    if objectiveDict["InstantCondition"]["ResourceType"] == CastleResources.TalentsToPay:
                        objectiveDict["InstantCondition"]["TalentsToPayValue"] = objectiveDict["InstantCondition"]["TotalValue"]
                        objectiveDict["InstantCondition"]["TotalValue"] = 0
                    else:
                        objectiveDict["InstantCondition"]["TotalValue"] = int(objectiveDict["InstantCondition"]["TotalValue"])

                    # print '\'{0}\''.format(objectiveDict["SessionCondition"]["PickedHeroes"])

                    # fix sessions conditions
                    if objectiveDict["SessionCondition"]["PickedHeroes"]:
                        objectiveDict["SessionCondition"]["PickedHero"] = ','.join(map(lambda x: str(x), objectiveDict["SessionCondition"]["PickedHeroes"]['Item']))
                    else:
                        allheroesNames = []
                        for PersistentId in SD['Heroes']:
                            staticHero = SD['Heroes'][PersistentId]
                            allheroesNames.append(staticHero['id'])
                        objectiveDict["SessionCondition"]["PickedHero"] = ','.join(allheroesNames)

                    if objectiveDict["SessionCondition"]["GameTypes"]:
                        objectiveDict["SessionCondition"]["GameType"] = ','.join(map(lambda x: str(x), objectiveDict["SessionCondition"]["GameTypes"]['Item']))
                    else:
                        objectiveDict["SessionCondition"]["GameType"] = ' '

                    objectiveDict["SessionCondition"]["IncrementPerBattle"] = int(objectiveDict["SessionCondition"]["IncrementPerBattle"])
                    objectiveDict["SessionCondition"]["TotalValue"] = int(objectiveDict["SessionCondition"]["TotalValue"])
                    objectiveDict["SessionCondition"]["PlayerPartySize"] = int(objectiveDict["SessionCondition"]["PlayerPartySize"])
                    objectiveDict["SessionCondition"]["EnemyPartySize"] = int(objectiveDict["SessionCondition"]["EnemyPartySize"])
                    objectiveDict["SessionCondition"]["SessionCheckType"] = SessionCheckType.__dict__[objectiveDict["SessionCondition"]["SessionCheckType"]]



                    # print objectiveDict

                if not 'DynamicAwards' in questDict:
                    continue

                if not 'Item' in questDict['DynamicAwards']:
                    continue

                for awardDict in questDict['DynamicAwards']['Item']:
                    # look at first check in handle objectives
                    if not isinstance(awardDict["AwardType"], str):
                        continue

                    # get var with a name that equally awardType
                    awardDict["AwardType"] = \
                    [value for key, value in DynamicQuestAwardType.__dict__.iteritems() if key == awardDict["AwardType"]][0]

                    awardDict["PersistentId"] = int(awardDict["PersistentId"])
                    # print awardDict
        # structure SD after convert:

        # ForbadeTalents: {'G057': None}
        # OverridenPricesMap: {'G001': { / * ResourceTable * /}}
        # PricesMap: {'exclusive': { / * ResourceTable * /}, 'outstanding': { / ** /}, 'magnificent': { / ** /}, 'excellent': { / ** /}}
        # OverridenDifficultiesMap: {'G059': '4'}
        # DifficultiesMap: {'exclusive': '6', 'outstanding': '7', 'magnificent': '5', 'excellent': '4'}
        # QuestsGroups: {'5': [{ / * quest1 * /}, { / * quest2 * /}], '4': [ / ** /], '7': [ / ** /], '6': [ / ** /]}

    def convertAviableMaps( SD ):
        for m in SD['AviableMaps']['maps']['Item']:
            m['matchmakingSettings']['fullPartySize'] = int(m['matchmakingSettings']['fullPartySize'])
            m['matchmakingSettings']['mock'] = bool(m['matchmakingSettings']['mock'])
            m['matchmakingSettings']['useRanking'] = bool(m['matchmakingSettings']['useRanking'])
            m['mapSettings']['fullPartyOnly'] = bool( m['mapSettings'].get('fullPartyOnly', False))
            m['mapSettings']['maxRequiredHeroForce'] = int(m['mapSettings'].get('maxRequiredHeroForce', 0))
            m['mapSettings']['minRequiredHeroForce'] = int(m['mapSettings'].get('minRequiredHeroForce', 0))

    # Primitive type converters TODO: Move up

    def toInt(dict_, field):
        """

        :param dict_:
        :type dict_: dict
        :param field:
        :type field: str
        :return:
        """
        dict_[field] = int(dict_[field])

    def toFloat(dict_, field):
        """

        :param dict_:
        :type dict_: dict
        :param field:
        :type field: str
        :return:
        """
        dict_[field] = float(dict_[field])

    def toList(dict_, field, converter=None):
        """

        :param dict_:
        :type dict_: dict
        :param field:
        :type field: str
        :param converter:
        :return:
        """
        list_ = []
        list_dict = dict_[field]
        if list_dict:
            for item in list_dict['Item']:
                if converter:
                    if converter(item):
                        list_.append(item)
                else:
                    list_.append(item)
        dict_[field] = list_

    # Interface converters TODO: Move up

    def toInterface_RollItem(class_dict):
        if 'ready' in class_dict:
            return
        class_type = class_dict['classType']
        if class_type == 'NothingRollItem':
            toClass_NothingRollItem(class_dict)
        elif class_type == 'RarityTalentListRollItem':
            toClass_RarityTalentListRollItem(class_dict)
        elif class_type == 'ResourceRollItem':
            toClass_ResourceRollItem(class_dict)
        elif class_type == 'RollContainer':
            toClass_RollContainer(class_dict)
        elif class_type == 'TalentRollItem':
            toClass_TalentRollItem(class_dict)
        elif class_type == 'TalentUpgradeRollItem':
            toClass_TalentUpgradeRollItem(class_dict)
        elif class_type == 'HeroRollItem':
            toClass_HeroRollItem(class_dict)
        elif class_type == 'SkinRollItem':
            toClass_SkinRollItem(class_dict)
        elif class_type == 'FlagRollItem':
            toClass_FlagRollItem(class_dict)
        elif class_type == 'MarketingEventRollItem':
            toClass_MarketingEventRollItem(class_dict)
        elif class_type == 'PremiumAccRollItem':
            toClass_PremiumAccRollItem(class_dict)
        elif class_type == 'GoldRollItem':
            toClass_GoldRollItem(class_dict)
        elif class_type == 'TalentUpgradeEntityRollItem':
            toClass_TalentUpgradeEntityRollItem(class_dict)
        else:
            error("Unsupported RollItem type: {0}".format(class_type))
        class_dict['ready'] = True

    # Class converters TODO: Move up

    def toClass_NothingRollItem(class_dict):
        toInt(class_dict, 'dummy')

    def toClass_GoldRollItem(class_dict):
        toInt(class_dict, 'count')

    def toClass_PremiumAccRollItem(class_dict):
        toInt(class_dict, 'days')

    def toClass_RarityTalentListRollItem(class_dict):
        # Nothing to convert here
        pass

    def toClass_ResourceRollItem(class_dict):
        def item_converter(item):
            toInt(item, 'count')
            toInt(item, 'deviation')
            toInt(item, 'level')
            return True
        toList(class_dict, 'itemsFromLord', converter=item_converter)

    def toClass_RollContainer(class_dict):
        def item_converter(item):
            toFloat(item, 'probability')
            sub_item = item['item']
            if not sub_item:
                return False
            toInterface_RollItem(sub_item)
            return True
        toInt(class_dict, 'multiplicator')
        toList(class_dict, 'items', converter=item_converter)

    def toClass_TalentRollItem(class_dict):
        talent = class_dict['talent']
        class_dict['talent'] = crc32(talent['persistentId'])

    def toClass_TalentUpgradeProbabilityTable(class_dict):
        def item_converter(item):
            toInt(item, 'points')
            toFloat(item, 'probability')
            return True
        toList(class_dict, 'upgrades', converter=item_converter)

    def toClass_TalentUpgradeRollItem(class_dict):
        talent_item = class_dict['talentItem']
        toInterface_RollItem(talent_item)
        upgrade_table = class_dict['upgradeTable']
        toClass_TalentUpgradeProbabilityTable(upgrade_table)

    def toClass_HeroRollItem(class_dict):
        hero = class_dict['hero']
        class_dict['hero'] = crc32(hero['persistentId'])

    def toClass_SkinRollItem(class_dict):
        skin = class_dict['skin']
        class_dict['skin'] = crc32(skin['persistentId'])

    def toClass_TalentUpgradeEntityRollItem(class_dict):
        entity = class_dict['entity']
        class_dict['entity'] = crc32(entity['persistentId'])

    def toClass_FlagRollItem(class_dict):
        flag = class_dict['flag']
        class_dict['flag'] = flag['id']

    def toClass_MarketingEventRollItem(class_dict):
        # GoldLampEvent and UpgradeHeroTalentsEvent supported only
        if class_dict['marketingEvent']['classType'] == 'UpgradeHeroTalentsEvent'\
                or class_dict['marketingEvent']['classType'] == 'GoldLampEvent':
            class_dict['marketingEvent'] = dict(count=toint(class_dict['count']),
                                                classType=class_dict['marketingEvent']['classType'],
                                                dbid=class_dict['marketingEvent']['dbid'])
        else:
            class_dict['marketingEvent'] = dict(count=0, classType="Unsupported")

    # Domain converters TODO: Move down

    def convertLootboxes(SD):
        lootboxes = SD['Lootboxes']
        for pid in lootboxes:
            lootbox = lootboxes[pid]
            roll_container = lootbox['rollContainer']
            toInterface_RollItem(roll_container)

    def convertTalentUpgradeEntities(SD):
        for persistent_id in SD['TalentUpgradeEntities']:
            static_ent = SD['TalentUpgradeEntities'][persistent_id]
            static_ent['probability'] = int(static_ent['probability'])
            static_ent['talentLevelLimit'] = int(static_ent['talentLevelLimit'])
            static_ent['type'] = TalentUpgradeEntityType.__dict__[static_ent['type']]
            if 'description' in static_ent:
                del static_ent['description']
            if 'tooltip' in static_ent:
                del static_ent['tooltip']
            if 'icon' in static_ent:
                del static_ent['icon']

    def convertStringsToTypes( SD ):
        SD['AIGameLogic']['forceParameters']['baseHeroForce'] = float(SD['AIGameLogic']['forceParameters']['baseHeroForce'])
        SD['AIGameLogic']['forceParameters']['masteryPointForce'] = float(SD['AIGameLogic']['forceParameters']['masteryPointForce'])

        SD['AIGameLogic']['forceParameters']['classTalentLevelForceModifiers']['Item'] = map( lambda x: float(x), SD['AIGameLogic']['forceParameters']['classTalentLevelForceModifiers']['Item'] )
        SD['AIGameLogic']['forceParameters']['talentLevelForceModifiers']['Item'] = map( lambda x: float(x), SD['AIGameLogic']['forceParameters']['talentLevelForceModifiers']['Item'] )
        SD['AIGameLogic']['forceParameters']['talentRarityForceModifiers']['Item'] = map( lambda x: float(x), SD['AIGameLogic']['forceParameters']['talentRarityForceModifiers']['Item'] )
        SD['AIGameLogic']['forceParameters']['talentRarityForceSummand']['Item'] = map( lambda x: float(x), SD['AIGameLogic']['forceParameters']['talentRarityForceSummand']['Item'] )

        SD['AIGameLogic']['forceParameters']['defaultStatBonus'] = float( SD['AIGameLogic']['forceParameters']['defaultStatBonus'] )
        SD['AIGameLogic']['forceParameters']['defaultBaseForce'] = float( SD['AIGameLogic']['forceParameters']['defaultBaseForce'] )
        SD['AIGameLogic']['forceParameters']['statBonusByForce'] = float( SD['AIGameLogic']['forceParameters']['statBonusByForce'] )

        SD['AIGameLogic']['talentBaseStatBudget'] = float(SD['AIGameLogic']['talentBaseStatBudget'])
        SD['AIGameLogic']['forceParameters']['talentForceModifier'] = float(SD['AIGameLogic']['forceParameters']['talentForceModifier'])
        SD['AIGameLogic']['forceParameters']['talentForceBonusPerStar'] = float(SD['AIGameLogic']['forceParameters']['talentForceBonusPerStar'])
        SD['AIGameLogic']['forceParameters']['classTalentForceBonusPerStar'] = float(SD['AIGameLogic']['forceParameters']['classTalentForceBonusPerStar'])

        SD['MaxEmptyTalents'] = int(SD['MaxEmptyTalents'])
        SD['FirstBuyHeroExpBonus'] = int(SD['FirstBuyHeroExpBonus'])
 
        SD['Map']['MapCenter']['x'] = int( SD['Map']['MapCenter']['x'] )
        SD['Map']['MapCenter']['y'] = int( SD['Map']['MapCenter']['y'] )
        SD['Map']['MapCenter']['z'] = int( SD['Map']['MapCenter']['z'] )
        SD['Map']['SectionSize'] = int( SD['Map']['SectionSize'] )
        SD['Map']['MapSize']['x'] = int( SD['Map']['MapSize']['x'] )
        SD['Map']['MapSize']['y'] = int( SD['Map']['MapSize']['y'] )

        SD['LevelToFameTable']['Levels']['Item'] = map( lambda x: int(x), SD['LevelToFameTable']['Levels']['Item'] )

        SD['LevelToExperienceTable']['Levels']['Item'] = map( lambda x: int(x), SD['LevelToExperienceTable']['Levels']['Item'] )

        for lvl in SD['TalentLevelToPointsAndRarity']['Item']:
            if 'Item' in lvl['levelToPoints']:
                lvl['levelToPoints']['Item'] = map( lambda x: int(x), lvl['levelToPoints']['Item'] )

        for lvl in SD['TalentMergePriceToLevelAndRarity']['Item']:
            lvl['levelToPrice']['Item'] = map( lambda x: int(x), lvl['levelToPrice']['Item'] )

        SD['StatpointsToLevelTable']['StatPoints']['Item'] = map( lambda x: int(x), SD['StatpointsToLevelTable']['StatPoints']['Item'] )

        for item in SD['StatsBudgetContainer']['stats']['Item']:
            item['budget'] = float(item['budget'])

        convertBathBuildings(SD)
        convertStorageBuildings(SD)
        convertLibraryBuildings(SD)
        convertHouseBuildings(SD)
        convertPineTreeBuildings(SD)
        convertFirstBuyBuildings(SD)
        convertGuildBuildings(SD)
        convertHeroesBuildings(SD)
        convertTransmutationBuildings(SD)
        converReforgePrices(SD)
        convertProductionBuildings(SD)
        convertDecorBuildings(SD)
        convertTavernBuilding(SD)
        convertGoldProductionBuildings(SD)
        convertRerollShopBuildings(SD)
        convertDynamicQuestsForTalentsToMaps(SD)
        convertLootboxes(SD)
        convertTalentUpgradeEntities(SD)

        for PersistentId in SD['Talents']:
            staticTalent = SD['Talents'][PersistentId]
            staticTalent['budget'] = float( staticTalent['budget'] )
            staticTalent['minLevel'] = int( staticTalent['minLevel'] )
            staticTalent['devPoints'] = int( staticTalent['devPoints'] )
            staticTalent['naftaCost'] = int( staticTalent['naftaCost'] )
            staticTalent['upgradeLevel'] = int( staticTalent['upgradeLevel'] )
            staticTalent['talentRollGroups'] = int( staticTalent['talentRollGroups'] )
            if staticTalent['isGenderTalent'] and staticTalent['isGenderTalent'] == "true":
                staticTalent['isGenderTalent'] = True
            else:
                staticTalent['isGenderTalent'] = False
            if staticTalent['isTakenOnStart'] and staticTalent['isTakenOnStart'] == "true":
                staticTalent['isTakenOnStart'] = True
            else:
                staticTalent['isTakenOnStart'] = False
            del staticTalent['conditionFormulas']
            del staticTalent['caption']
            del staticTalent['passiveApplicators']
            del staticTalent['constants']
            staticTalent['consumptionBonus']['percent'] = int( staticTalent['consumptionBonus']['percent'] )
            staticTalent['consumptionBonus']['constant'] = int( staticTalent['consumptionBonus']['constant'] )
            staticTalent['forceBonus'] = float( staticTalent['forceBonus'] )
            talentStats = staticTalent['talentStats']
            if talentStats:
              for talentStat in talentStats['Item']:
                for i in xrange( 0, len( talentStat['values']['Item'] ) ):
                  talentStat['values']['Item'][i] = float( talentStat['values']['Item'][i] )

        for item in SD['TalentsSellPrice']['Item']:
            convertPrice( item )

        for item in SD['TalentsUnsoulboundPriceByLevel']['Item']:
            # TalentLevelToUnsoulboundPrice
            item['level'] = int(item['level'])
            item['price'] = int(item['price'])

        # for item in SD['GoldTalentsUnsoulboundPrice']['Item']:
        #     convertPrice( item )

        for item in SD['GoldPriceCycleTable']['goldtable']['Item']:
            item['timePercent'] = int(item['timePercent'])
            item['goldPercent'] = int(item['goldPercent'])

        for PersistentId in SD['Heroes']:
            staticHero = SD['Heroes'][PersistentId]
            staticHero['lobbyData']['Classes'] = int(staticHero['lobbyData']['Classes'])
            staticHero['lobbyData']['LevelRequireFemale'] = int(staticHero['lobbyData']['LevelRequireFemale'])
            convertPrice(staticHero['lobbyData']['CostFemale'])
            staticHero['lobbyData']['LevelRequireMale'] = int(staticHero['lobbyData']['LevelRequireMale'])
            convertPrice(staticHero['lobbyData']['CostMale'])
            staticHero['lobbyData']['Version'] = int(staticHero['lobbyData']['Version'])
            del staticHero['lobbyData']['heroAskSoundA']
            del staticHero['lobbyData']['heroAskSoundB']

            staticHero['lobbyData']['Stats']['MaxEndurance'] = int( staticHero['lobbyData']['Stats']['MaxEndurance'] )
            for item in staticHero['lobbyData']['Stats']['EnduranceRegen']['Item']:
                item['level'] = int( item['level'] )
                item['enduranceRegenTime'] = int( item['enduranceRegenTime'] )
    
            staticHero['lobbyData']['FameIncrement']['FameIncrement']['Item'] = map( lambda x: int(x), staticHero['lobbyData']['FameIncrement']['FameIncrement']['Item'] )
            convertPrice( staticHero['lobbyData']['ProductionResultIncrement'] )
            
            for item in staticHero['lobbyData']['BonusTalentsForLevel']['Levels']['Item']:
                if item['Talents']:
                    cleanTalents( item['Talents'] )

            if hasattr(staticHero, 'defaultTalentsSet'):
                for item in staticHero['defaultTalentsSet']['levels']['Item']:
                    if item['talents']:
                        cleanTalents( item['talents'] )

            try:
                for dts in staticHero['defaultTalentsSets']['Item']:
                    if not dts:
                        continue
                    for item in dts['levels']['Item']:
                        if item['talents']:
                            cleanTalents(item['talents'])
            except Exception as e:
                logging.error(str(e))
                logging.error("heroId: " + str(PersistentId))
                logging.error(str(staticHero['defaultTalentsSets']))

            if hasattr(staticHero['mightyTalentSet'], 'levels'):
                for item in staticHero['mightyTalentSet']['levels']['Item']:
                    if item['talents']:
                        cleanTalents(item['talents'])
                    
            for item in staticHero['stats']['stats']['Item']:
                item['calcValue'] = float( item['calcValue'] )
                item['calcIncrement'] = float( item['calcIncrement'] )
                
            staticHero['totalStatsBudget'] = float( staticHero['totalStatsBudget'] )

        convertPrice( SD['ResetStatsPriceCoef'] )

        for item in SD['HeroRatingToFameLevel']['Ratings']['Item']:
            item['rating'] = int(item['rating'])
            item['fameLevel'] = int(item['fameLevel'])

        SD['TalentConsumptionPointsToRarity']['Item'] = map( lambda x: int(x), SD['TalentConsumptionPointsToRarity']['Item'] )

        for item in SD['LevelToResources']['resourcesPerLevel']['Item']:
            item['currentLevel'] = int(item['currentLevel'])
            convertPrice(item['resourcesPerLevel'])
            if 'PremiumAccountHours' in item:
                item['PremiumAccountHours'] = int(item['PremiumAccountHours'])
        
        if hasattr( SD, 'HonorLevelTable' ) and 'Item' in SD['HonorLevelTable']['rewardPerLevel']:
            for item in SD['HonorLevelTable']['rewardPerLevel']['Item']:
                item['points'] = float(item['points'])
                if 'percents' in item['rollTalentsReward']:
                    item['rollTalentsReward']['percents']['Item'] = map( lambda x: int(x), item['rollTalentsReward']['percents']['Item'] )

        if 'highLevelsMMRating' in SD['AIGameLogic']['heroRanks']:
            SD['AIGameLogic']['heroRanks']['highLevelsMMRating'] = int(SD['AIGameLogic']['heroRanks']['highLevelsMMRating'])
        for item in SD['AIGameLogic']['heroRanks']['ranks']['Item']:
            item['rating'] = int(item['rating'])
            item['rewardTalentsCountForUI'] = int(item['rewardTalentsCountForUI'])

        for item in SD['BathPriceToHeroLevel']['Item']:
            item['currentLevel'] = int(item['currentLevel'])
            item['silver'] = float(item['silver'])

        convertPrice( SD['GuestInitParams']['resourceTable'] )
        SD['GuestInitParams']['fame'] = int(SD['GuestInitParams']['fame'])
 
        #SD['DefaultTrainMap']['victoryPoint'] = int(SD['DefaultTrainMap']['victoryPoint'])
        #SD['DefaultTrainMap']['teamSize'] = int(SD['DefaultTrainMap']['teamSize'])


        convertPrice( SD['PlayerInitParams']['resourceTable'] )
        SD['PlayerInitParams']['fame'] = int(SD['PlayerInitParams']['fame'])
        convertPrice( SD['GuestInitParams']['resourceTable'] )
        SD['GuestInitParams']['fame'] = int(SD['GuestInitParams']['fame'])

        convertPrice( SD['ResourceAndInventoryLimits']['resourceLimits'] )
        convertPrice( SD['GuestResourceAndInventoryLimits']['resourceLimits'] )
        SD['ResourceAndInventoryLimits']['inventoryLimits'] = int( SD['ResourceAndInventoryLimits']['inventoryLimits'] )
        SD['GuestResourceAndInventoryLimits']['inventoryLimits'] = int( SD['GuestResourceAndInventoryLimits']['inventoryLimits'] )

        SD['RollTalentForTransmutationBuilding']['percents']['Item'] = map(lambda x: int(x), SD['RollTalentForTransmutationBuilding']['percents']['Item'])
        SD['RollTalentPremiumForTransmutationBuilding']['percents']['Item'] = map(lambda x: int(x), SD['RollTalentPremiumForTransmutationBuilding']['percents']['Item'])

        for item in SD['Map']['Grades']['Item']:
            item['sectionsCount'] = int( item['sectionsCount'] )
            convertPrice( item['price'] )

        SD['GuildLevels']['requiredExpMultiplier'] = int(SD['GuildLevels']['requiredExpMultiplier'])
        if 'levels' in SD['GuildLevels'] and 'Item' in SD['GuildLevels']['levels']:
            for level in SD['GuildLevels']['levels']['Item']:
                if 'Bonuses' in level and 'Item' in level['Bonuses']:
                    for bonus in level['Bonuses']['Item']:
                        if 'classType' in bonus and bonus['classType'] == "GuildProduction" and 'cycle' in bonus:
                            bonus['cycle']['fameToProduce'] = int(bonus['cycle']['fameToProduce'])
                            convertPrice( bonus['cycle']['priceToStart'] )
                            convertPrice( bonus['cycle']['resourcesToProduce'] )
                            bonus['cycle']['percents']['Item'] = map( lambda x: int(x), bonus['cycle']['percents']['Item'] )
                            bonus['cycle']['timeblock']['gold'] = int( bonus['cycle']['timeblock']['gold'] )
                            bonus['cycle']['timeblock']['time'] = int( bonus['cycle']['timeblock']['time'] ) 
                        elif 'classType' in bonus and bonus['classType'] == "HeroEnergyRestoreBonus":
                            bonus['coef'] = float(bonus['coef'])
                if 'requiredExp' in level:
                    level['requiredExp'] = long(level['requiredExp'])

        if 'Item' in SD['GuildShopLevelToSuzerenExperience']:
            for item in SD['GuildShopLevelToSuzerenExperience']['Item']:
                item['requiredExp'] = long( item['requiredExp'] )
                        
        for item in SD['LampEventsSettings']['Item']:
            item['lastPayDate'] = int( item['lastPayDate'] )
          
        for item in SD['MarketingEvents']['lampEvents']['Item']:
            item['bonusPersent'] = int( item['bonusPersent'] )

        for item in SD['DBUIData']['customFlags']['Item']:
            item['Price'] = int(item['Price'])

        for item in SD['DBUIData']['adminFlags']['Item']:
            item['Price'] = int(item['Price'])

        if "RecentPlayers" in SD["DBUIData"]:
            SD["DBUIData"]["RecentPlayers"] = int(SD["DBUIData"]["RecentPlayers"])

        SD['RatingDecreaseByTime']['minRatingToLoose'] = int(SD['RatingDecreaseByTime']['minRatingToLoose'])
        for item in SD['RatingDecreaseByTime']['ratings']['Item']:
            item['ratingToLoose'] = int(item['ratingToLoose'])
            item['minDaysFromLastBattle'] = int(item['minDaysFromLastBattle'])

        SD["ClanWarsData"]["npcVillage"]["clanRating"] = int(SD["ClanWarsData"]["npcVillage"]["clanRating"])
        SD["ClanWarsData"]["npcVillage"]["everyDayProfit"] = int(SD["ClanWarsData"]["npcVillage"]["everyDayProfit"])
        SD["ClanWarsData"]["npcSuzerain"]["clanRating"] = int(SD["ClanWarsData"]["npcSuzerain"]["clanRating"])
        SD["ClanWarsData"]["npcSuzerain"]["defaultSiegePoints"] = int(SD["ClanWarsData"]["npcSuzerain"]["defaultSiegePoints"])
        SD["ClanWarsData"]["countOfNPCVillage"] = int(SD["ClanWarsData"]["countOfNPCVillage"])
        SD["ClanWarsData"]["shopAncientRating"] = int(SD["ClanWarsData"]["shopAncientRating"])
        SD["ClanWarsData"]["guildVassalsTributeCoef"] = float(SD["ClanWarsData"]["guildVassalsTributeCoef"])
        SD["ClanWarsData"]["defencePointsPercent"] = float(SD["ClanWarsData"]["defencePointsPercent"])

        SD["ClanWarsData"]["guildWarEventData"]["pointsCap"] = long(SD["ClanWarsData"]["guildWarEventData"]["pointsCap"])
        SD["ClanWarsData"]["guildWarEventData"]["duration"] = int(SD["ClanWarsData"]["guildWarEventData"]["duration"])
        for item in SD['ClanWarsData']['guildWarEventData']['awards']['Item']:
            item['maxPlace'] = int(item['maxPlace'])
            item['members'] = int(item['members'])
            item['award']['count'] = int(item['award']['count'])

        SD['GuildRecruitment']['guildRequestLifetime'] = int(SD['GuildRecruitment']['guildRequestLifetime'])
        SD['GuildRecruitment']['maxUserGuildRequests'] = int(SD['GuildRecruitment']['maxUserGuildRequests'])
        SD['GuildRecruitment']['maxUserGuildRequestSize'] = int(SD['GuildRecruitment']['maxUserGuildRequestSize'])
        SD['GuildRecruitment']['maxGuildRecruitTextSize'] = int(SD['GuildRecruitment']['maxGuildRecruitTextSize'])

        SD['resourcesToGoldPrice']['Resource1']['isPack'] = bool(SD['resourcesToGoldPrice']['Resource1']['isPack'])
        SD['resourcesToGoldPrice']['Resource2']['isPack'] = bool(SD['resourcesToGoldPrice']['Resource2']['isPack'])
        SD['resourcesToGoldPrice']['Resource3']['isPack'] = bool(SD['resourcesToGoldPrice']['Resource3']['isPack'])
        SD['resourcesToGoldPrice']['Silver']['isPack'] = bool(SD['resourcesToGoldPrice']['Silver']['isPack'])
        SD['resourcesToGoldPrice']['Perl']['isPack'] = bool(SD['resourcesToGoldPrice']['Perl']['isPack'])

        SD['resourcesToGoldPrice']['Resource1']['resourceCount'] = int(SD['resourcesToGoldPrice']['Resource1']['resourceCount'])
        SD['resourcesToGoldPrice']['Resource2']['resourceCount'] = int(SD['resourcesToGoldPrice']['Resource2']['resourceCount'])
        SD['resourcesToGoldPrice']['Resource3']['resourceCount'] = int(SD['resourcesToGoldPrice']['Resource3']['resourceCount'])
        SD['resourcesToGoldPrice']['Silver']['resourceCount'] = int(SD['resourcesToGoldPrice']['Silver']['resourceCount'])
        SD['resourcesToGoldPrice']['Perl']['resourceCount'] = int(SD['resourcesToGoldPrice']['Perl']['resourceCount'])

        SD['resourcesToGoldPrice']['Resource1']['goldPrice'] = float(SD['resourcesToGoldPrice']['Resource1']['goldPrice'])
        SD['resourcesToGoldPrice']['Resource2']['goldPrice'] = float(SD['resourcesToGoldPrice']['Resource2']['goldPrice'])
        SD['resourcesToGoldPrice']['Resource3']['goldPrice'] = float(SD['resourcesToGoldPrice']['Resource3']['goldPrice'])
        SD['resourcesToGoldPrice']['Silver']['goldPrice'] = float(SD['resourcesToGoldPrice']['Silver']['goldPrice'])
        SD['resourcesToGoldPrice']['Perl']['goldPrice'] = float(SD['resourcesToGoldPrice']['Perl']['goldPrice'])

        SD['RerollShop']['usualSlots'] = int(SD['RerollShop']['usualSlots'])
        SD['RerollShop']['premiumSlots'] = int(SD['RerollShop']['premiumSlots'])
        SD['RerollShop']['maxInactiveUsualSlots'] = int(SD['RerollShop']['maxInactiveUsualSlots'])
        SD['RerollShop']['maxInactivePremiumSlots'] = int(SD['RerollShop']['maxInactivePremiumSlots'])
        convertPrice(SD['RerollShop']['rerollPrice'])

        for staticGroup in SD['RerollShop']['groups']['Item']:
            staticGroup['currencies'] = int(staticGroup['currencies'])
            staticGroup['minPoints'] = int(staticGroup['minPoints'])
            staticGroup['maxPoints'] = int(staticGroup['maxPoints'])
            staticGroup['minUpgradeLevel'] = int(staticGroup['minUpgradeLevel'])
            staticGroup['maxUpgradeLevel'] = int(staticGroup['maxUpgradeLevel'])
            for item in staticGroup['rerollTimesToDropProbabilties']['Item']:
                item['rerollTime'] = int(item['rerollTime'])
                item['newProbability'] = float(item['newProbability'])
            for groupSlot in staticGroup['slots']['Item']:
                groupSlot['currencies'] = int(groupSlot['currencies'])
                groupSlot['minPoints'] = int(groupSlot['minPoints'])
                groupSlot['maxPoints'] = int(groupSlot['maxPoints'])

        for persistentId in SD['RerollShopSlots']:
            slot = SD['RerollShopSlots'][persistentId]
            if slot['classType'] == "ResourceRerollSlot":
                slot['amount'] = int(slot['amount'])
                convertPrice(slot['resource'])
            elif slot['classType'] == "PremiumRerollSlot":
                slot['days'] = int(slot['days'])
            elif slot['classType'] == "LampRerollSlot":
                slot['lifeTime'] = int(slot['lifeTime'])
                slot['maxBonus'] = int(slot['maxBonus'])
            elif slot['classType'] == "UpgradeHeroTalentsRerollSlot":
                slot['uses'] = int(slot['uses'])
            elif slot['classType'] == "LootboxRerollSlot":
                slot['count'] = int(slot['count'])
                slot['lootboxPersistentId'] = slot['lootbox']['persistentId']
        for item in SD['RerollShop']['resourcesToPointsTable']['Item']:
            item['priceInPoints'] = float(item['priceInPoints'])
            item['roundToDigits'] = int(item['roundToDigits'])

        # склеиваем SD['SeasonLeagues']['Item'] и SD['Seasons']['Item'][...]['ParamLeagues']

        leagues = {}
        for item_season_league in SD['SeasonLeagues']['Item']:
            # print("xml2obj item_season_league: %s"%str(item_season_league))
            item_season_league['leagueId'] = int(item_season_league['leagueId'])
            item_season_league['flashDataIndex'] = int(item_season_league['flashDataIndex'])
            # TODO: kramarov: crownFlashIdx
            # TODO: kramarov: nameLeague
            item_season_league['quality'] = int(item_season_league['quality'])
            leagues[item_season_league['leagueId']] = item_season_league

        for item_season in SD['Seasons']['Item']:
            # print("xml2obj item_season: %s"%str(item_season))
            item_season['startTime'] = int(item_season['startTime'])
            item_season['stopTime'] = int(item_season['stopTime'])
            # TODO: kramarov:
            item_season['nameSeason'] = "id:%s" % (item_season['persistentId'])
            if len(item_season['ParamLeagues']):
                for item_fame in item_season['ParamLeagues']['Item']:
                    item_fame['minRating'] = int(item_fame['minRating'])
                    item_fame['minLeaderPlace'] = int(item_fame['minLeaderPlace'])
                    item_fame['leagueId'] = int(item_fame['leagueId'])
                    # TODO: kramarov:
                    item_fame['nameLeague'] = "seasonId:%s leagueId:%d" % (item_season['persistentId'], item_fame['leagueId'])
                    for k, v in leagues[item_fame['leagueId']].iteritems():
                        item_fame[k] = v

        convertAviableMaps( SD )



    def add_xml_attr( dict, name, value ):
        if isinstance( value, unicode ):
            try:
                value = str(value)
                if value == "false":
                    value = False
                elif value == "true":
                    value = True
            except:
                value = None

        if isinstance( name, unicode ):
            try:
                name = str(name)
            except:
                pass

        if not value: 
            if value != False:
                dict[name] = ''
                return

        if name in dict:
            # multiple attribute of the same name are represented by a list
            children = dict[name]
            if not isinstance(children, list):
                children = [children]
                dict[name] = children
            children.append(value)
        else:
            dict[name] = value


    class TreeBuilder(xml.sax.handler.ContentHandler):

        def __init__(self):
            self.stack = []
            self.root = {}
            self.current = self.root
            self.text_parts = []

        def startElement(self, name, attrs):
            self.stack.append((self.current, self.text_parts))
            self.current = {}
            self.text_parts = []
            # xml attributes --> python attributes
            for k, v in attrs.items():
                add_xml_attr( self.current, _name_mangle(k), v )
  
        def endElement(self, name):
            text = ''.join(self.text_parts).strip()
            if self.current:
                obj = self.current
            else:
                # a text only node is simply represented by the string
                try:
                    obj = str(text) or ''
                    if obj == "false":
                        obj = False
                    elif obj == "true":
                        obj = True
                except:
                    obj = None
            self.current, self.text_parts = self.stack.pop()
            add_xml_attr( self.current, _name_mangle(name), obj )

        def characters(self, content):
            self.text_parts.append(content)
        
        def makeDataDict(self):
            self.dataDict = {}
            for name in builder.root['CastleData']['Data']['ObjData']:
                self.dataDict[name['dbid']] = name
                name['dbid'] = None
            builder.root['CastleData']['Data']['ObjData'] = []
            self.dataDict['MarketingEventRollItem'] = {}
        
        def makeObjectDict(self):
            self.objectDict = {}
            for name, value in builder.root['CastleData']['Objects'].items():
                if isinstance(value, list):
                    for item in value:
                        self.objectDict[item['dbid']] = name
                else:
                    self.objectDict[value['dbid']] = name
            builder.root['CastleData']['Objects'] = []
        
        def linkData( self, obj ):            
            if isinstance(obj, dict):
                if 'Item' in obj:
                    self.objToList(obj)
                
                if "href" in obj:
                    dbid = str( obj["href"] )
                    del obj['href']
                    if "id" in obj:
                        dbid += ":" + str( obj["id"] )
                        del obj['id']
                    if dbid in self.dataDict:
                        for obj_name, obj_value in self.dataDict[dbid].items(): 
                            obj[obj_name] = obj_value
                        type = self.objectDict[dbid]
                        obj["classType"] = type
                        self.dbid[dbid] = obj
                        if type == "MarketingEventRollItem":
                          id = crc32( obj["persistentId"] )
                          self.dataDict['MarketingEventRollItem'][id] = obj
                    obj['dbid'] = dbid
                else:
                    for item in obj:
                        self.linkData(obj[item])
            elif isinstance(obj, list):
                for item in obj:
                    self.linkData(item)

        #if there is only one value in 'Item' it will be deserialized as attr. To avoid it we'll transform it back to list
        def objToList(self, obj):
            if not isinstance(obj['Item'], list):
                tempList = []
                tempList.append(obj["Item"])
                obj["Item"] = tempList
                
        def linkObjects(self):
            self.dbid = {}
            self.makeDataDict()
            self.makeObjectDict()
            self.linkData( self.dataDict )
            if '/Social.ROOT' in self.dataDict:
                staticData = self.dataDict['/Social.ROOT']
            elif '/SocialTest.ROOT' in self.dataDict:
                staticData = self.dataDict['/SocialTest.ROOT']

            staticData['Heroes'] = staticData['Heroes']['heroes']
            staticData['MarketingEventRollItem'] = self.dataDict['MarketingEventRollItem']
            self.dbid['/Social.ROOT'] = staticData
            
            for name, value in staticData.items():
                tempDict = {}
                i = 0
                if name == "Heroes":
                    for list_value in value['Item']:
                        id = crc32(list_value['id'])
                        tempDict[id] = list_value
                    staticData[name] = tempDict
                elif name == "Talents":
                    for list_value in value['Item']:
                        id = crc32(list_value['persistentId'])
                        tempDict[id] = list_value
                    staticData[name] = tempDict
                elif name == "Constructions":                   
                    for list_value in value['Item']:
                        id = crc32(list_value['persistentId'])
                        tempDict[id] = list_value
                    staticData[name] = tempDict
                elif name == "Lootboxes":
                    for list_value in value['Item']:
                        id = crc32(list_value['persistentId'])
                        tempDict[id] = list_value
                    staticData[name] = tempDict
                elif name == "Quests":
                    if 'Item' in value:
                        for questLine in value['Item']:
                            if 'Item' in questLine['quests']:
                                for quest in questLine['quests']['Item']:
                                    id = crc32(quest['persistentId'])
                                    tempDict[id] = quest
                    staticData[name].update(tempDict)
                    staticData["QuestsLine"] = value
                elif name == "SingleQuests":
                    if 'Item' in value:
                        for quest in value['Item']:
                            id = crc32(quest['persistentId'])
                            tempDict[id] = quest
                    staticData['Quests'].update(tempDict)
                elif name == "StartQuest":
                    id = crc32(value['persistentId'])
                    tempDict[id] = value
                    staticData["Quests"] = tempDict
                elif name == "StartQuestsForFractionChange":
                    id = crc32(value['persistentId'])
                    tempDict[id] = value
                    staticData["Quests"].update(tempDict)
                elif name == "GuildShopItems":
                    if "Item" in value:
                        for list_value in value['Item']:
                            id = crc32(list_value['persistentId'])
                            list_value['levelToUnlock'] = int(list_value['levelToUnlock'])
                            convertPrice(list_value['price'])
                            tempDict[id] = list_value
                        staticData[name] = tempDict
                elif name == "GuildBuffsCollection":
                    if "buffs" in value and "Item" in value['buffs']:
                        for list_value in value['buffs']['Item']:
                            if not list_value or type(list_value) is not dict:
                                warn(" something wrong with GuildBuffsCollection" )
                                continue
                            if 'duration' not in list_value:
                                warn(" something wrong with buff %s", list_value )
                                continue

                            list_value['duration'] = int(list_value['duration'])
                            list_value['numGames'] = int(list_value['numGames'])
                            list_value['priority'] = int(list_value['priority'])
                            id = crc32(list_value['persistentId'])
                            tempDict[id] = list_value
                        staticData[name] = tempDict
                elif name == "RerollShop":
                    for staticGroup in value['groups']['Item']:
                        for groupSlot in staticGroup['slots']['Item']:
                            if crc32(groupSlot['slot']['persistentId']) not in tempDict:
                                id = crc32(groupSlot['slot']['persistentId'])
                                tempDict[id] = groupSlot['slot']
                    staticData["RerollShopSlots"] = tempDict
                elif name == "ReforgeTalentPrices":
                    for pr in value['Item']:
                        tempDict[pr['rarity']] = pr
                    staticData["ReforgeTalentPrices"] = tempDict
                elif name == "TalentUpgradeEntities":
                    if 'Item' in value:
                        for list_value in value['Item']:
                            id = crc32(list_value['persistentId'])
                            tempDict[id] = list_value
                    staticData[name] = tempDict
            self.objectDict = {}
            self.dataDict = {}

            return staticData, self.dbid        
                
    t0 = time.time()
    builder = TreeBuilder()
    if isinstance(src, basestring):
        xml.sax.parseString(src, builder)
    else:
        xml.sax.parse(src, builder)
    logging.info("Load StaticData time: %.3f" % (time.time()-t0))
    t0 = time.time()
    StaticData, dbid = builder.linkObjects()
    logging.info("Linking StaticData time: %.3f" % (time.time()-t0))
    
    convertStringsToTypes(StaticData)

    gc.collect()    
    return StaticData, dbid
