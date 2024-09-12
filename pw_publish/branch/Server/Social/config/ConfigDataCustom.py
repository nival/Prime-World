# -*- coding: utf-8 -*-
from base.helpers import *
from binascii import crc32
from modeldata.jsonserialize import JSONSerialization
from modeldata.baseclasses import *
from modeldata.collects import SimpleDict, Collection
from modeldata.ref import Ref
from enums import *

from RollEvent import RollEvent
from RollEventsList import RollEventsList

class OverrideType:
    Both = 0
    Server = 1
    Client = 2

class ConfigDataCustom(BaseObject):
    def __init__(self):
        self.__dict__["_modelChangeWriter"] = None
        self.__dict__["_writeChanges"] = False
        self.__dict__["_comment"] = "auto"

        # чисто серверное поле, не передается на клиент, не сериализуется в модел-дате, приделанное сбоку
        self.__dict__["STATIC_DATA_SERVER_OVERRIDES"] = SimpleDict(self)

    def create(self):
        self.loadConfig(os.path.join(os.path.split(__file__)[0], "logic_cfg.py"))
        self.loadConfig(os.path.join(os.path.split(__file__)[0], "logic_overrides.py"))
        for config_file in self.ADDITIONAL_CONFIGS:
            self.loadConfig(os.path.join(os.path.split(__file__)[0], config_file))

    def update(self):
        self.loadConfig(os.path.join(os.path.split(__file__)[0], "logic_update.py"))

    def loadConfig(self, filename):
        execfile(filename)


    def createFromString(self, str):
        exec(str)

    def serializeToCfgFile(self):
        filename = os.path.join(os.path.split(__file__)[0], "logic_cfg.py")
        file = open( filename, 'w' )
        file.write("# -*- coding: utf-8 -*-\n")
        #file.write( "#!/usr/bin/env python\n\n" )
        self.serializeToFile(file)
        file.close()

    def save(self, save_data=None):
        self._serializator.setMode(False)  # For server side
        save_data = save_data or self.generateJsonDict()
        return json_dumps(save_data)


    def load(self, data):
        if isinstance(data, basestring):
          data = json_loads(data)
        self._serializator.fromDict(data)


    # IChangeWriter
    def modelChange(self, path, op, val):
        if self._modelChangeWriter:
            self._modelChangeWriter.writeStringToResponse(self.__class__.__name__, "auto", path, op, val)

    def write(self, changeWriter):
        self._modelChangeWriter = changeWriter
        self._writeChanges = (changeWriter is not None)

    def stop(self):
        self._modelChangeWriter = None
        self._writeChanges = False


    def addNews(self, ButtonText, WindowCaption, ButtonUrl, MainUrl, Tooltip, MainUrlB = "", LoginNetworks = "", MinLordLevel = 0, HideIfViewed = "false", ExtensionJson = ""):
        news_id = self.addNewNewsInfo()
        news = self.getNewsInfoByID(news_id)
        news.ButtonText = ButtonText
        news.WindowCaption = WindowCaption
        news.ButtonUrl = ButtonUrl
        news.MainUrl = MainUrl
        news.MainUrlB = MainUrlB
        news.Tooltip = Tooltip
        news.LoginNetworkNews = LoginNetworks
        news.MinLordLevel = int(MinLordLevel)
        news.HideIfViewed = (False if HideIfViewed.lower() == 'false' else True) if type(HideIfViewed) is not bool else HideIfViewed
        news.ExtensionJson = ExtensionJson
        self.NEWS.add(news)

    def addSteamItem(self, index, Gold, BonusGold, Price, Image, Description):
        steamItem, steamItemId = self.newBuySteamItem()
        steamItem.Gold = Gold
        steamItem.BonusGold = BonusGold
        steamItem.Price = Price
        steamItem.Image = Image
        steamItem.Description = Description

        self.BuySteamGoldEventInfo.SteamItems.remove(index)
        self.BuySteamGoldEventInfo.SteamItems.add(index, steamItem)

    def addAeriaItem(self, index, Gold, BonusGold, Price, Image, Description):
        aeriaItem, aeriaItemId = self.newBuyAeriaItem()
        aeriaItem.Gold = Gold
        aeriaItem.BonusGold = BonusGold
        aeriaItem.Price = Price
        aeriaItem.Image = Image
        aeriaItem.Description = Description

        self.BuyAeriaGoldEventInfo.AeriaItems.remove(index)
        self.BuyAeriaGoldEventInfo.AeriaItems.add(index, aeriaItem)

    def addZZimaItem(self, index, Gold, BonusGold, Price, Image, Description):
        zzItem, zzItemId = self.newBuyZZimaItem()
        zzItem.Gold = Gold
        zzItem.BonusGold = BonusGold
        zzItem.Price = Price
        zzItem.Image = Image
        zzItem.Description = Description

        self.BuyZZimaGoldEventInfo.ZZimaItems.remove(index)
        self.BuyZZimaGoldEventInfo.ZZimaItems.add(index, zzItem)


    def addCustomFlag(self, flagId, price):
        customFlag, customFlagId = self.newCustomFlag()
        customFlag.PersistentId = flagId
        customFlag.Price = price

        self.CustomFlags.add(customFlag)

    def updateCustomFlagPrice(self, persistentId, price):
        for flagId in self.CustomFlags:
            flag = self.getCustomFlagByID(flagId)
            if flag.PersistentId == persistentId:
                flag.Price = price

    def getCustomFlagById(self, persistentId):
        for flagId in self.CustomFlags:
          flag = self.getCustomFlagByID(flagId)
          if flag.PersistentId == persistentId:
            return flag
        return None

    def addArcGamesItem(self, index, Gold, BonusGold, Price, Image, Description):
        arcGamesItem, arcGamesItemId = self.newBuyArcGamesItem()
        arcGamesItem.Gold = Gold
        arcGamesItem.BonusGold = BonusGold
        arcGamesItem.Price = Price
        arcGamesItem.Image = Image
        arcGamesItem.Description = Description

        self.BuyArcGamesGoldEventInfo.ArcGamesItems.remove(index)
        self.BuyArcGamesGoldEventInfo.ArcGamesItems.add(index, arcGamesItem)

    def addBeginnerPack(self, index, Gold, Image, PersistentId, Description, packTalents):
        packItem, zzItemId = self.newBeginnersPackItem()
        packItem.Gold = Gold
        packItem.Image = Image
        packItem.PersistentId = PersistentId
        packItem.Description = Description

        for talent in packTalents:
          packItem.PackTalents.append(talent)

        self.BeginnersPackEventInfo.BeginnersPackItems.remove(index)
        self.BeginnersPackEventInfo.BeginnersPackItems.add(index, packItem)

    def addGuildShopItems(self, itemsList):
        for item in itemsList:
          self.GUILD_SHOP_ITEMS.append(crc32(item))

    def overrideData(self, key, value, override_type=OverrideType.Both):

        if override_type == OverrideType.Server:
            self.STATIC_DATA_SERVER_OVERRIDES[key] = value
        elif override_type == OverrideType.Client:
            self.STATIC_DATA_OVERRIDES[key] = value
        else:
            self.STATIC_DATA_OVERRIDES[key] = value
            self.STATIC_DATA_SERVER_OVERRIDES[key] = value

    def addLampActiveGroup(self, startDay, endDay):
        activeGroup, activeGroupId = self.newActiveGroup()
        activeGroup.StartDay = startDay
        activeGroup.EndDay = endDay
        self.LampEventSettings.ActiveGroups.add(activeGroup)

    def blockHeroesPairForParty(self, firstHeroId, secondHeroId):
        #pair = HeroesPair()
        #pair.FirstHeroPersistentId = firstHeroId
        #pair.SecondHeroPersistentId = secondHeroId
        pair = firstHeroId + ";" + secondHeroId
        self.FORBIDDEN_FOR_PARTY_HERO_PAIRS.append(pair)

    # region Visible operator events: Quest Event

    def add_roll_event(self, persistent_id, end_time, custom_data):
        events_dict = self.RollEvents  # type: Collection
        roll_event, _ = self.newRollEvent()
        roll_event.load_from_db_dict(self, persistent_id, end_time, custom_data)
        events_dict[persistent_id] = roll_event

    def delete_roll_event(self, persistent_id):
        events_dict = self.RollEvents  # type: Collection
        events_dict.remove(persistent_id)

    # endregion

    # region Visible operator events: Quest Event

    def add_quest_event(self, persistent_id, end_time, custom_data):
        events_dict = self.QuestEvents  # type: Collection
        quest_event, _ = self.newQuestEvent()
        quest_event.load_from_db_dict(self, persistent_id, end_time, custom_data)
        events_dict[persistent_id] = quest_event

    def delete_quest_event(self, persistent_id):
        events_dict = self.QuestEvents  # type: Collection
        events_dict.remove(persistent_id)

    # endregion

    # region Visible operator events: Trade Event

    def add_trade_event(self, persistent_id, end_time, custom_data):
        events_dict = self.TradeEvents  # type: Collection
        trade_event, _ = self.newTradeEvent()
        trade_event.load_from_db_dict(self, persistent_id, end_time, custom_data)
        events_dict[persistent_id] = trade_event

    def delete_trade_event(self, persistent_id):
        events_dict = self.TradeEvents  # type: Collection
        events_dict.remove(persistent_id)

    # endregion

    # region Visible operator events: Season Event

    def add_season_event(self, persistent_id, end_time, custom_data):
        events_dict = self.SeasonEvents  # type: Collection
        season_event, _ = self.newSeasonEvent()
        season_event.load_from_db_dict(self, persistent_id, end_time, custom_data)
        events_dict[persistent_id] = season_event

    def delete_season_event(self, persistent_id):
        events_dict = self.SeasonEvents  # type: Collection
        events_dict.remove(persistent_id)

    # endregion

    # region Visible operator events: Donate Event

    def add_donate_event(self, persistent_id, end_time, custom_data):
        events_dict = self.DonateEvents  # type: Collection
        donate_event, _ = self.newDonateEvent()
        donate_event.load_from_db_dict(self, persistent_id, end_time, custom_data)
        events_dict[persistent_id] = donate_event

    def delete_donate_event(self, persistent_id):
        events_dict = self.DonateEvents  # type: Collection
        events_dict.remove(persistent_id)

    # endregion

    def __findObjectForOverride(self, SD, path):
        if not path:
            return None, None
        splitResult = path.split("::")
        if len(splitResult) != 2:
            return None, None
        dbid = splitResult[0]
        subindexes = splitResult[1]
        rootobj = SD.getObjectByDbid(dbid)
        if not rootobj:
            return None, None
        indexes = subindexes.split(".")
        if not indexes:
            return rootobj, None
        obj = None
        index = None
        subobj = rootobj
        for index in indexes:
            if subobj is None:
                return None, None
            obj = subobj
            if index[0] == '[' and index[-1] == ']':
                index = int(index[1:-1])
            try:
                subobj = obj[index]
            except:
                return None, None
        return obj, index

    def applyOverrides(self, SD):
        for key, value in self.STATIC_DATA_SERVER_OVERRIDES.iteritems():
            try:
                # ищем объект и index (поле/ключ), куда устанавливать новое значение
                obj, index = self.__findObjectForOverride(SD, key)
                if obj is None or index is None:
                    warn("applyOverrides: fail: bad path '%s'", key)
                    continue
                # устанавливаем новое значение
                try:
                    prevValue = obj[index]
                    newObj = SD.getObjectByDbid(value)
                    if newObj:
                        obj[index] = newObj
                    elif value == "[]":
                        obj[index] = []
                    elif value is None:
                        obj[index] = None
                    else:
                        try:
                            obj[index] = prevValue.__class__(value)
                        except:
                            obj[index] = value
                    info("applyOverrides: Ok '%s' : '%r' -> '%r'", key, str(prevValue), str(obj[index]))
                except:
                    warn("applyOverrides: fail to set: obj=%r, index=%r, key=%r" % (str(obj), index, key))
            except:
                catch()
        SD.afterApplyOverrides(self)

    def fillStaticDataDependendValues(self, SD):
        for skinId in SD.data['Skins'].keys():
            skinSD = SD.data['Skins'][skinId]
            if skinSD["persistentId"] not in self.EventToolsChangeFields.SKIN_GOLD_PRICES:
                self.EventToolsChangeFields.SKIN_GOLD_PRICES[skinSD["persistentId"]] = int(skinSD['cost'])

        for heroIdId in SD.data['Heroes'].keys():
            heroSD = SD.data['Heroes'][heroIdId]
            if heroSD["persistentId"] not in self.EventToolsChangeFields.HERO_SILVER_PRICES:
                self.EventToolsChangeFields.HERO_SILVER_PRICES[heroSD["persistentId"]] = int(heroSD['lobbyData']['CostMale']['Silver'])
                self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE[heroSD["persistentId"]] = SD.GetHeroGoldPrice(heroSD, self, False)
                self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE[heroSD["persistentId"]] = SD.GetHeroGoldPrice(heroSD, self, True)

        for constructionId in SD.data['Constructions'].keys():
            staticConstruction = SD.data['Constructions'][constructionId]
            if staticConstruction['classType'] == "FirstBuyBuilding" and staticConstruction["persistentId"] not in self.EventToolsChangeFields.FIRST_BUY_GOLD_PRICES:
                self.EventToolsChangeFields.FIRST_BUY_GOLD_PRICES[staticConstruction["persistentId"]] = \
                    int(staticConstruction['Levels']['Item'][0]['price']['Gold'])

        self.EventToolsChangeFields.ORDINARY_TALENTS_DROP_RARITIES.append(int(SD.data['RollTalentForTransmutationBuilding']['percents']['Item'][ETalentRarity.Class]))
        self.EventToolsChangeFields.ORDINARY_TALENTS_DROP_RARITIES.append(int(SD.data['RollTalentForTransmutationBuilding']['percents']['Item'][ETalentRarity.ordinary]))
        self.EventToolsChangeFields.ORDINARY_TALENTS_DROP_RARITIES.append(int(SD.data['RollTalentForTransmutationBuilding']['percents']['Item'][ETalentRarity.good]))
        self.EventToolsChangeFields.ORDINARY_TALENTS_DROP_RARITIES.append(int(SD.data['RollTalentForTransmutationBuilding']['percents']['Item'][ETalentRarity.excellent]))
        self.EventToolsChangeFields.ORDINARY_TALENTS_DROP_RARITIES.append(int(SD.data['RollTalentForTransmutationBuilding']['percents']['Item'][ETalentRarity.magnificent]))
        self.EventToolsChangeFields.ORDINARY_TALENTS_DROP_RARITIES.append(int(SD.data['RollTalentForTransmutationBuilding']['percents']['Item'][ETalentRarity.exclusive]))

        self.EventToolsChangeFields.PREMIUM_TALENTS_DROP_RARITIES.append(int(SD.data['RollTalentPremiumForTransmutationBuilding']['percents']['Item'][ETalentRarity.Class]))
        self.EventToolsChangeFields.PREMIUM_TALENTS_DROP_RARITIES.append(int(SD.data['RollTalentPremiumForTransmutationBuilding']['percents']['Item'][ETalentRarity.ordinary]))
        self.EventToolsChangeFields.PREMIUM_TALENTS_DROP_RARITIES.append(int(SD.data['RollTalentPremiumForTransmutationBuilding']['percents']['Item'][ETalentRarity.good]))
        self.EventToolsChangeFields.PREMIUM_TALENTS_DROP_RARITIES.append(int(SD.data['RollTalentPremiumForTransmutationBuilding']['percents']['Item'][ETalentRarity.excellent]))
        self.EventToolsChangeFields.PREMIUM_TALENTS_DROP_RARITIES.append(int(SD.data['RollTalentPremiumForTransmutationBuilding']['percents']['Item'][ETalentRarity.magnificent]))
        self.EventToolsChangeFields.PREMIUM_TALENTS_DROP_RARITIES.append(int(SD.data['RollTalentPremiumForTransmutationBuilding']['percents']['Item'][ETalentRarity.exclusive]))

        for staticGroup in SD.data['RerollShop']['groups']['Item']:
            rerollToDrop, _id = self.newRerollShopWeightsToTimes()
            self.EventToolsChangeFields.REROLL_SHOP_GROUP_WEIGHTS.add(crc32(staticGroup['persistentId']), rerollToDrop)
            for item in staticGroup['rerollTimesToDropProbabilties']['Item']:
                rerollToDrop.LevelToWeights.add(item['rerollTime'], item['newProbability'])

            rerollToUpgradeLevels, _id = self.newRerollShopGroupUpgradeLevels()
            self.EventToolsChangeFields.REROLL_SHOP_GROUP_UPGRADE_LEVELS.add(crc32(staticGroup['persistentId']),
                                                                      rerollToUpgradeLevels)
            rerollToUpgradeLevels.MinUpgradeLevel = staticGroup['minUpgradeLevel']
            rerollToUpgradeLevels.MaxUpgradeLevel = staticGroup['maxUpgradeLevel']

        # todo: kramarov: пока что берем цены из xml. цены из gm-tool игнорим
        #for item in SD.data['ReforgeTalentPrices']['Item']:
        #    rarityPrices, _id = self.newReforgeTalentPrices()
        #    rarityPrices.Rarity = fromETalentRarity(item['rarity'])
        #    rarityPrices.RerollPrice = int(item['rerollPrice'])
        #    rarityPrices.UpgradePrice = int(item['upgradePrice'])
        #    rarityPrices.TalentsToUpgrade = int(item['talentsToUpgrade'])
        #    self.EventToolsChangeFields.ReforgePrices.add(rarityPrices)

        transmutationBuilding = SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        self.EventToolsChangeFields.TRANSMUTATION_TALENTS_PER_PERL = transmutationBuilding["TransmutationLevels"]["Item"][0]["perlForBonuse"]

        self.EventToolsChangeFields.REROLL_SHOP_ORDINARY_SLOTS = SD.data['RerollShop']['usualSlots']
        self.EventToolsChangeFields.REROLL_SHOP_PREMIUM_SLOTS = SD.data['RerollShop']['premiumSlots']
        self.EventToolsChangeFields.INACTIVE_REROLL_SHOP_PREMIUM_SLOTS = SD.data['RerollShop']['maxInactivePremiumSlots']
        self.EventToolsChangeFields.INACTIVE_REROLL_SHOP_ORDINARY_SLOTS = SD.data['RerollShop']['maxInactiveUsualSlots']
        self.EventToolsChangeFields.REROLL_SHOP_PRICE.Resource1 = SD.data['RerollShop']['rerollPrice']['Resource1']
        self.EventToolsChangeFields.REROLL_SHOP_PRICE.Resource2 = SD.data['RerollShop']['rerollPrice']['Resource2']
        self.EventToolsChangeFields.REROLL_SHOP_PRICE.Resource3 = SD.data['RerollShop']['rerollPrice']['Resource3']
        self.EventToolsChangeFields.REROLL_SHOP_PRICE.Silver = SD.data['RerollShop']['rerollPrice']['Silver']
        self.EventToolsChangeFields.REROLL_SHOP_PRICE.Gold = SD.data['RerollShop']['rerollPrice']['Gold']
        self.EventToolsChangeFields.REROLL_SHOP_PRICE.Perl = SD.data['RerollShop']['rerollPrice']['Perl']
        self.EventToolsChangeFields.REROLL_SHOP_PRICE.RedPerl = SD.data['RerollShop']['rerollPrice']['RedPerl']
        self.EventToolsChangeFields.PREMIUM_SLOTS_ARE_NOT_INACTIVE = SD.data['RerollShop']['premiumNotInactive']

    def getRollWeightByRollTimes(self, group, rerolls):
        weight = group.get(0)
        for key in sorted(group.keys()):
            if key <= rerolls:
                weight = group.get(key)
        return weight

    # эмулируем доступ к элементу как у словаря, чтобы работал поиск по абсолютным путям
    def get(self, key):
        return self.__dict__.get(key)

    # дополнительные (server-side) сериализуемые поля
    def generateBaseDict(self):
        return dict(
            next_uid_ = self.next_uid_
        )
