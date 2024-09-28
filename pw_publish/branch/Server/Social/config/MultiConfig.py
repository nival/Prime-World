# -*- coding: utf-8 -*-

from base.helpers import *
import subprocess
from threading import Thread, Lock
realpath = os.path.dirname(__file__)
modeldatapath = os.path.join(realpath, "../modeldata")
sys.path.append(modeldatapath)
sharedtypespath = os.path.join(realpath, "../modeldata/SharedTypes")
sys.path.append(sharedtypespath)
import pwconst # специфические константы PW (кол-во талантов в строке TalentSet и т.п.)
from subaction import SubAction
from modeldata.validator import *
from modeldata.changes import GroupPendingChangeWriter
from enums import ETalentRarity
from ConfigData import ConfigData
from Events.event import *
from Events.EventMap import *
thriftypespath = os.path.join(realpath, "../thrift_pw/account_management/gen-py")
sys.path.append(thriftypespath)
from AccountManagementAPI.ttypes import ConfigEventType
import GeneratedSeeds
import itertools, sys
from binascii import crc32

class MultiConfig:
    def __init__(self):
        self.mainConfig = ConfigData()
        self.mainConfig.init(None)
        self.mainConfig.create()
        self.configs = {}
        self.loadLocaleConfigs()
        # Locks for custom events from GMTools
        self.eventsMutex = Lock()
        self.eventMapsMutex = Lock()
        self.eventMapsForBanMutex = Lock()
        self.eventSkinsMutex = Lock()
        self.techsMutex = Lock()
        self.events = []
        self.eventMaps = []
        self.eventMapsForBan = []
        self.techs = {}
        self.seedsGenerationSubprocess = None
        self.premiumSeedGenerationSubprocess = None
        self.GoodSeeds = []
        self.PremiumGoodSeeds = []
        if hasattr(GeneratedSeeds, "Probabilities") and hasattr(GeneratedSeeds, "GoodSeeds"):
            self.GoodSeeds = GeneratedSeeds.GoodSeeds[:]
        else:
            err("Fail set GoodSeeds! Use old random")
        if hasattr(GeneratedSeeds, "PremiumProbabilities") and hasattr(GeneratedSeeds, "PremiumGoodSeeds"):
            self.PremiumGoodSeeds = GeneratedSeeds.PremiumGoodSeeds[:]
        else:
            err("Fail set PremiumGoodSeeds! Use old random")

    def updateConfig(self):
        changeWriter = ClassDict()
        self.resetPendingChanges(changeWriter)
        self.mainConfig.write(changeWriter.pending)
        self.mainConfig.update()
        changes = {}
        changes["main"] = self.pickPendingChanges(changeWriter)
        changes.update(self.updateLocaleConfigs())
        info("ConfigData changes = %r", changes)
        return changes

    def updateLocaleConfigs(self):
        path = os.path.dirname(os.path.realpath(__file__))
        lines = self.loadLocalesFile(path)
        changes = {}
        for line in lines:
            #locale in ""
            startIdx = line.find('"', 0)
            endIdx = line.find('"', startIdx+1)
            if endIdx == -1 or startIdx == -1:
                err("Bad line format(id), skip: %r" % line)
                continue
            localeName = line[startIdx+1:endIdx]
            localeName = localeName.lower()

            #main config filename
            mainConfigStartIdx = line.find(' ', endIdx+1)
            mainConfigEndIdx = line.find('.py', startIdx+1)
            if mainConfigStartIdx == -1 or mainConfigEndIdx == -1:
                err("Bad line format(id), skip: %r" % line)
                continue

            #update config filename
            startIdx = line.find(' ', mainConfigEndIdx+1)
            endIdx = line.find('.py', startIdx+1)
            if startIdx == -1 or endIdx == -1:
                err("Bad line format(id), skip: %r" % line)
                continue
            fileName = line[startIdx+1:endIdx]+".py"
            fullFileName = os.path.join(path, fileName)
            changes[localeName] = self.updateFromFile(fileName, fullFileName, localeName)
        return changes

    def updateFromFile(self, fileName, fullFileName, localeName):
        if os.path.isfile(fullFileName):
            changeWriter = ClassDict()
            self.resetPendingChanges(changeWriter)
            self.configs[localeName].write(changeWriter.pending)
            self.configs[localeName].loadConfig(fullFileName)
            info("Update config %r for locale %r" % (fileName, localeName))
            return self.pickPendingChanges(changeWriter)
        else:
            err("Can not update config file %r" % fileName)
            return []


    def reloadLocaleConfig(self, locale):
        path = os.path.dirname(os.path.realpath(__file__))
        lines = self.loadLocalesFile(path)
        for line in lines:
            #locale in ""
            startIdx = line.find('"', 0)
            endIdx = line.find('"', startIdx+1)
            if endIdx == -1 or startIdx == -1:
                err("Bad line format(id), skip: %r" % line)
                continue
            localeName = line[startIdx+1:endIdx]
            localeName = localeName.lower()
            if localeName == locale:
                #main config filename
                startIdx = line.find(' ', endIdx+1)
                endIdx = line.find('.py', startIdx+1)
                if endIdx == -1 or startIdx == -1:
                    err("Bad line format(id), skip: %r" % line)
                    continue
                fileName = line[startIdx+1:endIdx]+".py"
                fullFileName = os.path.join(path, fileName)
                return self.loadFromFile(fileName, fullFileName, localeName)

    def reloadSeeds(self):
        if self.seedsGenerationSubprocess and self.seedsGenerationSubprocess.poll() is not None:
            seeds, errOutput = self.seedsGenerationSubprocess.communicate()
            self.GoodSeeds = json_loads(seeds)
            self.seedsGenerationSubprocess = None
        if self.premiumSeedGenerationSubprocess  and self.premiumSeedGenerationSubprocess.poll() is not None:
            seeds, errOutput = self.premiumSeedGenerationSubprocess.communicate()
            self.PremiumGoodSeeds = json_loads(seeds)
            self.premiumSeedGenerationSubprocess = None
        return self.seedsGenerationSubprocess is not None or self.premiumSeedGenerationSubprocess is not None

    def loadLocalesFile(self, path):
        localesfile = os.path.normpath(os.path.join(path, "locales.txt"))
        file = open(localesfile, "r")
        lines = file.readlines()
        file.close()
        return lines

    def loadLocaleConfigs(self):
        path = os.path.dirname(os.path.realpath(__file__))
        lines = self.loadLocalesFile(path)
        for line in lines:
            #locale in ""
            startIdx = line.find('"', 0)
            endIdx = line.find('"', startIdx+1)
            if endIdx == -1 or startIdx == -1:
                err("Bad line format(id), skip: %r" % line)
                continue
            localeName = line[startIdx+1:endIdx]
            localeName = localeName.lower()

            #filename
            startIdx = line.find(' ', endIdx+1)
            endIdx = line.find('.py', startIdx+1)
            if endIdx == -1 or startIdx == -1:
                err("Bad line format(id), skip: %r" % line)
                continue
            fileName = line[startIdx+1:endIdx]+".py"
            fullFileName = os.path.join(path, fileName)
            self.loadFromFile(fileName, fullFileName, localeName)

    def loadFromFile(self, fileName, fullFileName, localeName):
        if os.path.isfile( fullFileName ):
            self.configs[localeName] = ConfigData()
            self.configs[localeName].init(None)
            self.configs[localeName].create()
            self.configs[localeName].loadConfig(fullFileName)
            info("Load config %r for locale %r" % (fileName, localeName))
            return True
        else:
            err("Can not load config file %r" % fileName)
            return False

    def getConfig(self, val):
        if isinstance(val, basestring):
            key = val.lower()
            if key in self.configs:
               return self.configs[key]
        return self.mainConfig


    def getMainConfig(self):
        return self.mainConfig


    def loadMainConfig(self, cfg):
        self.mainConfig.load(cfg)

    def applyLocaleOverrides(self, SD):
        for key in self.configs:
            localeSD = SD.getSD(key)
            if localeSD:
                localeSD.reloadConfigDependendFields(self.configs[key])
                self.configs[key].applyOverrides(localeSD)
            else:
                err("Static Data for locale %s was not found", key)

    def resetPendingChanges(self, changeWriter):
        changeWriter.pending_changes = []
        changeWriter.pending = GroupPendingChangeWriter(changeWriter)

    def pickPendingChanges(self, changeWriter):
        response = {}
        SubAction.wrapPendingMessages(changeWriter, None, response)
        changeWriter.pending_changes = []

        changes = response.get("ConfigData") or []
        SubAction.convertResponseObjects(changes)
        return changes

    def fillStaticDataDependendValues(self, SD):
        self.mainConfig.fillStaticDataDependendValues(SD.getMainSD())
        for key in self.configs:
            localeSD = SD.getSD(key)
            if localeSD:
                self.configs[key].fillStaticDataDependendValues(localeSD)
            else:
                err("Static Data for locale %s was not found", key)

    # region Event Applying: ConfigEventType.RerollShopGroupSlots

    @staticmethod
    def apply_reroll_shop_group_slots(event, local_static_data):
        for group in event['newValue']['groups']:
            group_id_crc = crc32(group['groupId'])
            static_group = local_static_data.getStaticRerollShopGroupById(group_id_crc)
            if not static_group:
                continue
            static_group_slots = static_group['slots']['Item']
            group_slots = group['persistentIds']
            for static_slot in list(static_group_slots):  # Possible changes in source list
                if static_slot['slot']['persistentId'] not in group_slots:
                    static_group_slots.remove(static_slot)
            for slot_id in group_slots:
                slot_exists = any((slot for slot in static_group_slots if slot['slot']['persistentId'] == slot_id))
                if slot_exists:
                    continue
                static_slot = local_static_data.getStaticRerollShopItemById(crc32(slot_id))
                static_group_slots.append({'slot': static_slot,
                                           'currencies': 0,
                                           'minPoints': 0,
                                           'maxPoints': 0})

    @staticmethod
    def revert_reroll_shop_group_slots(event, local_static_data):
        for group_defaults in event['defaultValue']:
            group_id_crc = crc32(group_defaults['groupId'])
            static_group = local_static_data.getStaticRerollShopGroupById(group_id_crc)
            if not static_group:
                continue
            static_group_slots = static_group['slots']['Item']
            group_slots = group_defaults['persistentIds']
            for static_slot in list(static_group_slots):  # Possible changes in source list
                if static_slot['slot']['persistentId'] not in group_slots:
                    static_group_slots.remove(static_slot)
            for slot_id in group_slots:
                slot_exists = any((slot for slot in static_group_slots if slot['slot']['persistentId'] == slot_id))
                if slot_exists:
                    continue
                static_slot = local_static_data.getStaticRerollShopItemById(crc32(slot_id))
                default_slot_data = group_defaults[slot_id]
                static_group_slots.append({'slot': static_slot,
                                           'currencies': default_slot_data['currencies'],
                                           'minPoints': default_slot_data['minPoints'],
                                           'maxPoints': default_slot_data['maxPoints']})

    @staticmethod
    def default_reroll_shop_group_slots(event, local_static_data):
        event_defaults = []
        for group in event['newValue']['groups']:
            group_id = group['groupId']
            group_id_crc = crc32(group_id)
            static_group = local_static_data.getStaticRerollShopGroupById(group_id_crc)
            if not static_group:
                continue
            group_default_slots = []
            group_defaults = {'groupId': group_id,
                              'persistentIds': group_default_slots}
            for static_slot in static_group['slots']['Item']:
                static_slot_id = static_slot['slot']['persistentId']
                group_defaults[static_slot_id] = {'currencies': static_slot['currencies'],
                                                  'minPoints': static_slot['minPoints'],
                                                  'maxPoints': static_slot['maxPoints']}
                group_default_slots.append(static_slot_id)
            event_defaults.append(group_defaults)
        event['defaultValue'] = event_defaults

    # endregion

    # region Event Applying: ConfigEventType.RerollShopSlotAmount

    @staticmethod
    def apply_reroll_shop_slot_amount(event, local_static_data, local_config):
        config_slot_resources_amount = local_config.EventToolsChangeFields.REROLL_SHOP_SLOT_RESOURCES_AMOUNT
        for slot in event['newValue']['slots']:
            group_id_crc = crc32(slot['groupId'])
            static_group = local_static_data.getStaticRerollShopGroupById(group_id_crc)
            if not static_group:
                continue
            slot_id = slot['persistentId']
            new_slot_amount = slot['amount']
            for static_slot in static_group['slots']['Item']:
                static_slot_data = static_slot['slot']
                if static_slot_data['persistentId'] != slot_id:
                    continue
                static_slot_class = static_slot_data['classType']
                if static_slot_class == 'ResourceRerollSlot':
                    static_slot_data['amount'] = new_slot_amount
                    config_slot_resources_amount.add(slot['persistentId'], new_slot_amount)
                elif static_slot_class == 'PremiumRerollSlot':
                    static_slot_data['days'] = new_slot_amount
                    config_slot_resources_amount.add(slot['persistentId'], new_slot_amount)

    @staticmethod
    def revert_reroll_shop_slot_amount(event, local_static_data, local_config):
        config_slot_resources_amount = local_config.EventToolsChangeFields.REROLL_SHOP_SLOT_RESOURCES_AMOUNT
        event_defaults = event['defaultValue']
        for slot_id in event_defaults:
            default_slot_data = event_defaults[slot_id]
            group_id_crc = crc32(default_slot_data['groupId'])
            static_group = local_static_data.getStaticRerollShopGroupById(group_id_crc)
            if not static_group:
                continue
            for static_slot in static_group['slots']['Item']:
                static_slot_data = static_slot['slot']
                if static_slot_data['persistentId'] != slot_id:
                    continue
                static_slot_class = static_slot_data['classType']
                default_slot_amount = default_slot_data['amount']
                class_found = False
                if static_slot_class == 'ResourceRerollSlot':
                    static_slot_data['amount'] = default_slot_amount
                    class_found = True
                elif static_slot_class == 'PremiumRerollSlot':
                    static_slot_data['days'] = default_slot_amount
                    class_found = True
                if class_found and slot_id in config_slot_resources_amount.keys():
                    if default_slot_data['overrideConfig']:
                        config_slot_resources_amount[slot_id] = default_slot_amount
                    else:
                        config_slot_resources_amount.remove(slot_id)

    @staticmethod
    def default_reroll_shop_slot_amount(event, local_static_data, local_config):
        config_slot_resources_amount = local_config.EventToolsChangeFields.REROLL_SHOP_SLOT_RESOURCES_AMOUNT
        event_defaults = event['defaultValue']
        for slot in event['newValue']['slots']:
            group_id = slot['groupId']
            group_id_crc = crc32(group_id)
            static_group = local_static_data.getStaticRerollShopGroupById(group_id_crc)
            if not static_group:
                continue
            slot_id = slot['persistentId']
            for static_slot in static_group['slots']['Item']:
                static_slot_data = static_slot['slot']
                if static_slot_data['persistentId'] != slot_id:
                    continue
                static_slot_class = static_slot_data['classType']
                class_found = False
                if static_slot_class == 'ResourceRerollSlot':
                    event_defaults[slot_id] = {'groupId': group_id,
                                               'amount': static_slot_data['amount'],
                                               'overrideConfig': False}
                    class_found = True
                elif static_slot_class == 'PremiumRerollSlot':
                    event_defaults[slot_id] = {'groupId': group_id,
                                               'amount': static_slot_data['days'],
                                               'overrideConfig': False}
                    class_found = True
                if class_found and slot_id in config_slot_resources_amount.keys():
                    event_defaults[slot_id]['overrideConfig'] = True

    # endregion

    # region Event Applying: ConfigEventType.RerollShopSlotPrice

    @staticmethod
    def apply_reroll_shop_slot_price(event, local_static_data):
        for slot in event['newValue']['slots']:
            group_id = crc32(slot['groupId'])
            static_group = local_static_data.getStaticRerollShopGroupById(group_id)
            if not static_group:
                continue
            slot_id = slot['persistentId']
            for static_slot in static_group['slots']['Item']:
                if static_slot['slot']['persistentId'] == slot_id:
                    static_slot['minPoints'] = slot['minPrice']
                    static_slot['maxPoints'] = slot['maxPrice']

    @staticmethod
    def revert_reroll_shop_slot_price(event, local_static_data):
        event_defaults = event['defaultValue']
        for slot_id in event_defaults:
            default_slot_data = event_defaults[slot_id]
            group_id_crc = crc32(default_slot_data['groupId'])
            static_group = local_static_data.getStaticRerollShopGroupById(group_id_crc)
            if not static_group:
                continue
            for static_slot in static_group['slots']['Item']:
                if static_slot['slot']['persistentId'] == slot_id:
                    static_slot['minPoints'] = default_slot_data['minPrice']
                    static_slot['maxPoints'] = default_slot_data['maxPrice']

    @staticmethod
    def default_reroll_shop_slot_price(event, local_static_data):
        event_defaults = event['defaultValue']
        for slot in event['newValue']['slots']:
            group_id = slot['groupId']
            group_id_crc = crc32(group_id)
            static_group = local_static_data.getStaticRerollShopGroupById(group_id_crc)
            if not static_group:
                continue
            slot_id = slot['persistentId']
            for static_slot in static_group['slots']['Item']:
                if static_slot['slot']['persistentId'] == slot_id:
                    event_defaults[slot_id] = {'groupId': group_id,
                                               'minPrice': static_slot['minPoints'],
                                               'maxPrice': static_slot['maxPoints']}

    # endregion

    # region Applying Custom (those new custom events that created for unityUI fullscreen interface) Events

    def __apply_special_event(self, event, changes, change_writer):
        event_id = event['persistentId']
        end_time = event['endTime']
        custom_data = event['newValue']
        locale = custom_data['locale'].lower()
        if locale not in self.configs:
            return False
        locale_config = self.configs[locale]
        locale_config.write(change_writer.pending)

        if event['type'] == ConfigEventType.RollEvent:
            locale_config.add_roll_event(event_id, end_time, custom_data)
        elif event['type'] == ConfigEventType.QuestEvent:
            locale_config.add_quest_event(event_id, end_time, custom_data)
        elif event['type'] == ConfigEventType.TradeEvent:
            locale_config.add_trade_event(event_id, end_time, custom_data)
        elif event['type'] == ConfigEventType.SeasonEvent:
            locale_config.add_season_event(event_id, end_time, custom_data)

        changes[locale] = self.pickPendingChanges(change_writer)
        return True

    def __revert_special_event(self, event, changes, change_writer):
        custom_data = event['newValue']  # type: dict
        locale = custom_data['locale'].lower()  # type: str
        if locale not in self.configs:
            return False
        event_id = event['persistentId']  # type: int
        locale_config = self.configs[locale]  # type: ConfigData
        locale_config.write(change_writer.pending)

        if event['type'] == ConfigEventType.RollEvent:
            locale_config.delete_roll_event(event_id)
        elif event['type'] == ConfigEventType.QuestEvent:
            locale_config.delete_quest_event(event_id)
        elif event['type'] == ConfigEventType.TradeEvent:
            locale_config.delete_trade_event(event_id)
        elif event['type'] == ConfigEventType.SeasonEvent:
            locale_config.delete_season_event(event_id)

        changes[locale] = self.pickPendingChanges(change_writer)
        return True

    def __is_special_event(self, event_type):
        return event_type in [ConfigEventType.RollEvent, ConfigEventType.QuestEvent,
                                 ConfigEventType.TradeEvent, ConfigEventType.SeasonEvent]

    # endregion

    def __apply_donate_event(self, event, locale_config):
        event_id = event['persistentId']
        end_time = event['endTime']
        custom_data = event['newValue']
        locale_config.add_donate_event(event_id, end_time, custom_data)
        return True

    def __revert_donate_event(self, event, locale_config):
        event_id = event['persistentId']  # type: int
        locale_config.delete_donate_event(event_id)
        return True

    def applyEvent(self, SD, event):
        changes = {}
        changeWriter = ClassDict()
        self.resetPendingChanges(changeWriter)
        if event["type"] == ConfigEventType.NewsBanner:
            if event["newValue"]["locale"].lower() not in self.configs:
                return {}, self.seedsGenerationSubprocess
            localeConfig = self.configs[event["newValue"]["locale"].lower()]
            localeConfig.write(changeWriter.pending)
            localeConfig.addNews(event["newValue"]["buttonText"], event["newValue"]["windowCaption"],
                                 event["newValue"]["buttonUrl"], event["newValue"]["mainUrl"],
                                 event["newValue"]["tooltip"], event["newValue"]["mainUrlB"],
                                 event["newValue"]["LoginNetworks"], event["newValue"]["minLordLevel"],
                                 event["newValue"]["hideIfViewed"], event["newValue"]["extensionJson"])
            changes[event["newValue"]["locale"].lower()] = self.pickPendingChanges(changeWriter)
        elif event["type"] == ConfigEventType.RerollShopBanner:
            if event["newValue"]["locale"].lower() not in self.configs:
                return {}, self.seedsGenerationSubprocess
            localeConfig = self.configs[event["newValue"]["locale"].lower()]
            localeConfig.write(changeWriter.pending)
            localeConfig.EventToolsChangeFields.RerollShopBanner.BANNER_URL = event["newValue"]["mainUrl"]
            localeConfig.EventToolsChangeFields.RerollShopBanner.ACTION_END_TIME = event["endTime"]
            changes[event["newValue"]["locale"].lower()] = self.pickPendingChanges(changeWriter)
        elif event["type"] == ConfigEventType.RerollShopTooltip:
            if event["newValue"]["locale"].lower() not in self.configs:
                return {}, self.seedsGenerationSubprocess
            localeConfig = self.configs[event["newValue"]["locale"].lower()]
            localeConfig.write(changeWriter.pending)
            localeConfig.EventToolsChangeFields.REROLL_SHOP_TOOLTIP = event["newValue"]["tooltip"]
            changes[event["newValue"]["locale"].lower()] = self.pickPendingChanges(changeWriter)
        elif event["type"] in [ConfigEventType.CustomEvent, ConfigEventType.EventMap, ConfigEventType.Techs]:
            if event["type"] == ConfigEventType.CustomEvent:
                self.addCustomEvent(event)
            elif event["type"] == ConfigEventType.EventMap:
                self.addCustomMap(event)
            elif event["type"] == ConfigEventType.Techs:
                self.addTechs(event)
        elif event["type"] == ConfigEventType.TalentDropRarity:
            for locale in self.configs:
                localeConfig = self.configs[locale]
                localeConfig.write(changeWriter.pending)
                chgFields = localeConfig.EventToolsChangeFields
                if event["newValue"]["premium"]:
                    chgFields.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.Class] = event["newValue"]["Class"]
                    chgFields.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.ordinary] = event["newValue"]["ordinary"]
                    chgFields.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.good] = event["newValue"]["good"]
                    chgFields.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.excellent] = event["newValue"]["excellent"]
                    chgFields.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.magnificent] = event["newValue"]["magnificent"]
                    chgFields.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.exclusive] = event["newValue"]["exclusive"]
                else:
                    chgFields.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.Class] = event["newValue"]["Class"]
                    chgFields.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.ordinary] = event["newValue"]["ordinary"]
                    chgFields.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.good] = event["newValue"]["good"]
                    chgFields.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.excellent] = event["newValue"]["excellent"]
                    chgFields.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.magnificent] = event["newValue"]["magnificent"]
                    chgFields.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.exclusive] = event["newValue"]["exclusive"]
                changes[locale] = self.pickPendingChanges(changeWriter)
                self.resetPendingChanges(changeWriter)
            seedsType = "GoodSeeds"
            if event["newValue"]["premium"]:
                seedsType = "PremiumGoodSeeds"
            seedsGeneratorFilePath = os.path.join( os.path.dirname(os.path.realpath(__file__)), "../modeldata/GenerateOneTypeSeeds.py" )
            debug("Generating new seeds, file path = %s", seedsGeneratorFilePath)
            seedsGenerationSubprocess = subprocess.Popen([sys.executable, seedsGeneratorFilePath,
                                                          str(event["newValue"]["Class"]),
                                                          str(event["newValue"]["ordinary"]),
                                                          str(event["newValue"]["good"]),
                                                          str(event["newValue"]["excellent"]),
                                                          str(event["newValue"]["magnificent"]),
                                                          str(event["newValue"]["exclusive"]),
                                                          seedsType], stdout=subprocess.PIPE)
            if event["newValue"]["premium"]:
                self.premiumSeedGenerationSubprocess = seedsGenerationSubprocess
            else:
                self.seedsGenerationSubprocess = seedsGenerationSubprocess
        elif event["type"] == ConfigEventType.ReforgeTalentPrice:
            debug("applyEvent, event ReforgeTalentPrice = %r", event)
            if event["newValue"]["listReforgeTalentPrices"]:
                for locale in self.configs:
                    localeConfig = self.configs[locale]
                    localeConfig.write(changeWriter.pending)
                    chgFields = localeConfig.EventToolsChangeFields
                    for price, price_old in itertools.izip(event["newValue"]["listReforgeTalentPrices"] , chgFields.ReforgePrices.iteritems()):
                        price_old[1].Rarity = toint(price["rarity"])
                        price_old[1].RerollPrice = toint(price["rerollPrice"])
                        price_old[1].UpgradePrice = toint(price["upgradePrice"])
                        price_old[1].TalentsToUpgrade = toint(price["talentsToUpgrade"])
                    changes[locale] = self.pickPendingChanges(changeWriter)
                    self.resetPendingChanges(changeWriter)
        elif self.__is_special_event(event['type']):
            apply_event_result = self.__apply_special_event(event, changes, changeWriter)
            if not apply_event_result:
                return {}, self.seedsGenerationSubprocess
        else:
            for locale in self.configs:
                localeConfig = self.configs[locale]
                localeConfig.write(changeWriter.pending)
                if event["type"] == ConfigEventType.TransmutationTalentsPerPerl:
                    localeConfig.EventToolsChangeFields.TRANSMUTATION_TALENTS_PER_PERL = event["newValue"]["talents"]
                elif event["type"] == ConfigEventType.SkinGoldPrice:
                    for skin in event["newValue"]["skins"]:
                        if skin["persistentId"] in localeConfig.EventToolsChangeFields.SKIN_GOLD_PRICES:
                            localeConfig.EventToolsChangeFields.SKIN_GOLD_PRICES[skin["persistentId"]] = skin["price"]
                elif event["type"] == ConfigEventType.HeroPrice:
                    for hero in event["newValue"]["heroes"]:
                        if hero["persistentId"] in localeConfig.EventToolsChangeFields.HERO_SILVER_PRICES:
                            localeConfig.EventToolsChangeFields.HERO_SILVER_PRICES[hero["persistentId"]] = hero["silverPrice"]
                            localeConfig.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE[hero["persistentId"]] = hero["goldPrice"]
                            localeConfig.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE[hero["persistentId"]] = hero["goldPrice"]
                elif event["type"] == ConfigEventType.RerollShopSlots:
                    localeConfig.EventToolsChangeFields.REROLL_SHOP_ORDINARY_SLOTS = event["newValue"]["usualSlots"]
                    localeConfig.EventToolsChangeFields.REROLL_SHOP_PREMIUM_SLOTS = event["newValue"]["premiumSlots"]
                    localeConfig.EventToolsChangeFields.INACTIVE_REROLL_SHOP_ORDINARY_SLOTS = event["newValue"]["maxActiveUsualSlots"]
                    localeConfig.EventToolsChangeFields.INACTIVE_REROLL_SHOP_PREMIUM_SLOTS = event["newValue"]["maxActivePremiumSlots"]
                elif event["type"] == ConfigEventType.RerollShopPrice:
                    localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.Resource1 = event["newValue"]["resource1"]
                    localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.Resource2 = event["newValue"]["resource2"]
                    localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.Resource3 = event["newValue"]["resource3"]
                    localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.Silver = event["newValue"]["silver"]
                    localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.Gold = event["newValue"]["gold"]
                    localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.Perl = event["newValue"]["perl"]
                    localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.RedPerl = event["newValue"]["redPerl"]
                elif event["type"] == ConfigEventType.RerollShopGroupPrice:
                    localSD = SD.getSD(locale)
                    for group in event["newValue"]["groups"]:
                        staticGroup = localSD.getStaticRerollShopGroupById(crc32(group['persistentId']))
                        staticGroup['minPoints'] = group["minPrice"]
                        staticGroup['maxPoints'] = group["maxPrice"]
                elif event["type"] == ConfigEventType.RerollShopGroupProbability:
                    for group in event["newValue"]["groups"]:
                        staticGroup = localeConfig.EventToolsChangeFields.REROLL_SHOP_GROUP_WEIGHTS.get(crc32(group['persistentId']))
                        if len(staticGroup.LevelToWeights) > group["rerollTime"]:
                            staticGroup.LevelToWeights[group["rerollTime"]] = group["probability"]

                        # под изменение параметров заточки талантов в группе стоило бы завести отдельный ивент
                        # но решили сделать быстро и заточка будет прилетать из ивента с пробабилити
                        rerollToUpgradeLevels = localeConfig.EventToolsChangeFields.REROLL_SHOP_GROUP_UPGRADE_LEVELS.get(
                            crc32(group['persistentId']))
                        rerollToUpgradeLevels.MinUpgradeLevel = group['minUpgradeLevel']
                        rerollToUpgradeLevels.MaxUpgradeLevel = group['maxUpgradeLevel']
                elif event["type"] == ConfigEventType.RerollShopGroupCurrencies:
                    localSD = SD.getSD(locale)
                    for group in event["newValue"]["groups"]:
                        staticGroup = localSD.getStaticRerollShopGroupById(crc32(group['persistentId']))
                        staticGroup['currencies'] = group["currencies"]
                elif event["type"] == ConfigEventType.RerollShopSlotPrice:
                    localSD = SD.getSD(locale)
                    self.apply_reroll_shop_slot_price(event, localSD)
                elif event["type"] == ConfigEventType.RerollShopSlotAmount:
                    localSD = SD.getSD(locale)
                    self.apply_reroll_shop_slot_amount(event, localSD, localeConfig)
                elif event["type"] == ConfigEventType.FirstBuyPrice:
                    for petHouse in event["newValue"]["firstBuys"]:
                        localeConfig.EventToolsChangeFields.FIRST_BUY_GOLD_PRICES[petHouse["persistentId"]] = petHouse["price"]
                elif event["type"] == ConfigEventType.PremiumNotInactive:
                    localeConfig.EventToolsChangeFields.PREMIUM_SLOTS_ARE_NOT_INACTIVE = event["newValue"]
                elif event["type"] == ConfigEventType.RerollShopGroupSlots:
                    localSD = SD.getSD(locale)
                    self.apply_reroll_shop_group_slots(event, localSD)
                elif event["type"] == ConfigEventType.DonateEvent:
                    self.__apply_donate_event(event, localeConfig)

                changes[locale] = self.pickPendingChanges(changeWriter)
                self.resetPendingChanges(changeWriter)
        return changes, (self.seedsGenerationSubprocess is not None or self.premiumSeedGenerationSubprocess is not None)

    def revertEvent(self, SD, event):
        changes = {}
        changeWriter = ClassDict()
        self.resetPendingChanges(changeWriter)
        if event["type"] == ConfigEventType.NewsBanner:
            if event["newValue"]["locale"].lower() not in self.configs:
                return {}
            localeConfig = self.configs[event["newValue"]["locale"].lower()]
            localeConfig.write(changeWriter.pending)
            for _id, news in localeConfig.NEWS.items():
                if news.ButtonText == event["newValue"]["buttonText"] \
                    and news.WindowCaption == event["newValue"]["windowCaption"]:
                    localeConfig.NEWS.remove(news)
                    break
            changes[event["newValue"]["locale"].lower()] = self.pickPendingChanges(changeWriter)
        elif self.__is_special_event(event["type"]):
            if not self.__revert_special_event(event, changes, changeWriter):
                return {}
        elif event["type"] == ConfigEventType.RerollShopBanner:
            if event["newValue"]["locale"].lower() not in self.configs:
                return {}
            localeConfig = self.configs[event["newValue"]["locale"].lower()]
            localeConfig.write(changeWriter.pending)
            localeConfig.EventToolsChangeFields.RerollShopBanner.BANNER_URL = event["defaultValue"]["mainUrl"]
            localeConfig.EventToolsChangeFields.RerollShopBanner.ACTION_END_TIME = event["defaultValue"]["endTime"]
            changes[event["newValue"]["locale"].lower()] = self.pickPendingChanges(changeWriter)
        elif event["type"] == ConfigEventType.RerollShopTooltip:
            if event["newValue"]["locale"].lower() not in self.configs:
                return {}
            localeConfig = self.configs[event["newValue"]["locale"].lower()]
            localeConfig.write(changeWriter.pending)
            localeConfig.EventToolsChangeFields.REROLL_SHOP_TOOLTIP = event["defaultValue"]["tooltip"]
            changes[event["newValue"]["locale"].lower()] = self.pickPendingChanges(changeWriter)
        elif event["type"] in [ConfigEventType.CustomEvent, ConfigEventType.EventMap, ConfigEventType.Techs]:
            if event["type"] == ConfigEventType.CustomEvent:
                self.removeCustomEvent(event["persistentId"])
            elif event["type"] == ConfigEventType.EventMap:
                self.removeCustomMap(event["persistentId"])
            elif event["type"] == ConfigEventType.Techs:
                self.removeTechs(event["persistentId"])
        else:
            for locale in self.configs:
                localeConfig = self.configs[locale]
                localeConfig.write(changeWriter.pending)
                if event["type"] == ConfigEventType.TransmutationTalentsPerPerl:
                    localeConfig.EventToolsChangeFields.TRANSMUTATION_TALENTS_PER_PERL = event["defaultValue"]
                elif event["type"] == ConfigEventType.SkinGoldPrice:
                    for skin in event["newValue"]["skins"]:
                        if skin["persistentId"] in localeConfig.EventToolsChangeFields.SKIN_GOLD_PRICES:
                            localeConfig.EventToolsChangeFields.SKIN_GOLD_PRICES[skin["persistentId"]] = \
                              event["defaultValue"][skin["persistentId"]]["price"]
                elif event["type"] == ConfigEventType.HeroPrice:
                    for hero in event["newValue"]["heroes"]:
                        if hero["persistentId"] in localeConfig.EventToolsChangeFields.HERO_SILVER_PRICES:
                            localeConfig.EventToolsChangeFields.HERO_SILVER_PRICES[hero["persistentId"]] = \
                              event["defaultValue"][hero["persistentId"]]["silverPrice"]
                        if hero["persistentId"] in localeConfig.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE:
                            localeConfig.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE[hero["persistentId"]] = \
                              event["defaultValue"][hero["persistentId"]]["goldPrice"]
                        if hero["persistentId"] in localeConfig.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE:
                            localeConfig.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE[hero["persistentId"]] = \
                              event["defaultValue"][hero["persistentId"]]["goldPrice"]
                elif event["type"] == ConfigEventType.TalentDropRarity:
                    if event["newValue"]["premium"]:
                        chgFields = localeConfig.EventToolsChangeFields
                        chgFields.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.Class] = event["defaultValue"]["Class"]
                        chgFields.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.ordinary] = event["defaultValue"]["ordinary"]
                        chgFields.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.good] = event["defaultValue"]["good"]
                        chgFields.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.excellent] = event["defaultValue"]["excellent"]
                        chgFields.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.magnificent] = event["defaultValue"]["magnificent"]
                        chgFields.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.exclusive] = event["defaultValue"]["exclusive"]
                        self.PremiumGoodSeeds = event["defaultValue"]["oldSeeds"]
                    else:
                        chgFields = localeConfig.EventToolsChangeFields
                        chgFields.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.Class] = event["defaultValue"]["Class"]
                        chgFields.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.ordinary] = event["defaultValue"]["ordinary"]
                        chgFields.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.good] = event["defaultValue"]["good"]
                        chgFields.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.excellent] = event["defaultValue"]["excellent"]
                        chgFields.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.magnificent] = event["defaultValue"]["magnificent"]
                        chgFields.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.exclusive] = event["defaultValue"]["exclusive"]
                        self.GoodSeeds = event["defaultValue"]["oldSeeds"]
                elif event["type"] == ConfigEventType.ReforgeTalentPrice:
                    chgFields = localeConfig.EventToolsChangeFields
                    for price, price_old in itertools.izip(event["defaultValue"]["ReforgePrices"], chgFields.ReforgePrices.iteritems()):
                        price_old[1].Rarity = price["Rarity"]
                        price_old[1].RerollPrice = price["RerollPrice"]
                        price_old[1].UpgradePrice = price["UpgradePrice"]
                        price_old[1].TalentsToUpgrade = price["talentsToUpgrade"]
                elif event["type"] == ConfigEventType.RerollShopSlots:
                    localeConfig.EventToolsChangeFields.REROLL_SHOP_ORDINARY_SLOTS = event["defaultValue"]["usualSlots"]
                    localeConfig.EventToolsChangeFields.REROLL_SHOP_PREMIUM_SLOTS = event["defaultValue"]["premiumSlots"]
                    localeConfig.EventToolsChangeFields.INACTIVE_REROLL_SHOP_ORDINARY_SLOTS = event["defaultValue"]["maxActiveUsualSlots"]
                    localeConfig.EventToolsChangeFields.INACTIVE_REROLL_SHOP_PREMIUM_SLOTS = event["defaultValue"]["maxActivePremiumSlots"]
                elif event["type"] == ConfigEventType.RerollShopPrice:
                    localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.Resource1 = event["defaultValue"]["resource1"]
                    localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.Resource2 = event["defaultValue"]["resource2"]
                    localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.Resource3 = event["defaultValue"]["resource3"]
                    localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.Silver = event["defaultValue"]["silver"]
                    localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.Gold = event["defaultValue"]["gold"]
                    localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.Perl = event["defaultValue"]["perl"]
                    localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.RedPerl = event["defaultValue"]["redPerl"]
                elif event["type"] == ConfigEventType.RerollShopGroupPrice:
                    localSD = SD.getSD(locale)
                    for groupId in event["defaultValue"]:
                        staticGroup = localSD.getStaticRerollShopGroupById(crc32(groupId))
                        staticGroup['minPoints'] = event["defaultValue"][groupId]["minPrice"]
                        staticGroup['maxPoints'] = event["defaultValue"][groupId]["maxPrice"]
                elif event["type"] == ConfigEventType.RerollShopGroupProbability:
                    for groupId in event["defaultValue"]:
                        debug("Default value to return: %r", event["defaultValue"][groupId])
                        staticGroup = localeConfig.EventToolsChangeFields.REROLL_SHOP_GROUP_WEIGHTS.get(crc32(groupId))
                        debug("Returning default value %d for rrtimes %d %r: %r", event["defaultValue"][groupId]["rerollTime"], event["defaultValue"][groupId]["probability"], groupId, staticGroup)
                        debug("len LevelToWeights = %d", len(staticGroup.LevelToWeights))
                        if len(staticGroup.LevelToWeights) > event["defaultValue"][groupId]["rerollTime"]:
                            debug("value returned")
                            staticGroup.LevelToWeights[event["defaultValue"][groupId]["rerollTime"]] = event["defaultValue"][groupId]["probability"]

                        # под изменение параметров заточки талантов в группе стоило бы завести отдельный ивент
                        # но решили сделать быстро и заточка будет прилетать из ивента с пробабилити
                        rerollToUpgradeLevels = localeConfig.EventToolsChangeFields.REROLL_SHOP_GROUP_UPGRADE_LEVELS.get(crc32(groupId))
                        rerollToUpgradeLevels.MinUpgradeLevel = event["defaultValue"][groupId]['minUpgradeLevel']
                        rerollToUpgradeLevels.MaxUpgradeLevel = event["defaultValue"][groupId]['maxUpgradeLevel']
                elif event["type"] == ConfigEventType.RerollShopGroupCurrencies:
                    localSD = SD.getSD(locale)
                    for groupId in event["defaultValue"]:
                        staticGroup = localSD.getStaticRerollShopGroupById(crc32(groupId))
                        staticGroup['currencies'] = event["defaultValue"][groupId]["currencies"]
                elif event["type"] == ConfigEventType.RerollShopSlotPrice:
                    localSD = SD.getSD(locale)
                    self.revert_reroll_shop_slot_price(event, localSD)
                elif event["type"] == ConfigEventType.RerollShopSlotAmount:
                    localSD = SD.getSD(locale)
                    self.revert_reroll_shop_slot_amount(event, localSD, localeConfig)
                elif event["type"] == ConfigEventType.FirstBuyPrice:
                    for petHouse in event["newValue"]["firstBuys"]:
                        if petHouse["persistentId"] in localeConfig.EventToolsChangeFields.FIRST_BUY_GOLD_PRICES:
                            localeConfig.EventToolsChangeFields.FIRST_BUY_GOLD_PRICES[petHouse["persistentId"]] = \
                                event["defaultValue"][petHouse["persistentId"]]["price"]
                elif event["type"] == ConfigEventType.PremiumNotInactive:
                    localeConfig.EventToolsChangeFields.PREMIUM_SLOTS_ARE_NOT_INACTIVE = event["defaultValue"]
                elif event["type"] == ConfigEventType.RerollShopGroupSlots:
                    localSD = SD.getSD(locale)
                    self.revert_reroll_shop_group_slots(event, localSD)
                elif event["type"] == ConfigEventType.DonateEvent:
                    self.__revert_donate_event(event, localeConfig)

                changes[locale] = self.pickPendingChanges(changeWriter)
                self.resetPendingChanges(changeWriter)
        return changes

    def setEventDefalutValue(self, SD, event):
        # Для некоторых ивентов значение по умолчанию отсутствует
        if event["type"] in [ConfigEventType.CustomEvent, ConfigEventType.EventMap, ConfigEventType.NewsBanner,
                             ConfigEventType.Techs, ConfigEventType.RollEvent]:
            return
        localeConfig = self.configs["ru"]
        if event["type"] == ConfigEventType.TransmutationTalentsPerPerl:
            event["defaultValue"] = localeConfig.EventToolsChangeFields.TRANSMUTATION_TALENTS_PER_PERL
        elif event["type"] == ConfigEventType.RerollShopBanner:
            event["defaultValue"]["mainUrl"] = localeConfig.EventToolsChangeFields.RerollShopBanner.BANNER_URL
            event["defaultValue"]["endTime"] = localeConfig.EventToolsChangeFields.RerollShopBanner.ACTION_END_TIME
        elif event["type"] == ConfigEventType.RerollShopTooltip:
            event["defaultValue"]["tooltip"] = localeConfig.EventToolsChangeFields.REROLL_SHOP_TOOLTIP
        elif event["type"] == ConfigEventType.SkinGoldPrice:
            for skin in event["newValue"]["skins"]:
                if skin["persistentId"] in localeConfig.EventToolsChangeFields.SKIN_GOLD_PRICES:
                    event["defaultValue"][skin["persistentId"]] = {"price":
                      localeConfig.EventToolsChangeFields.SKIN_GOLD_PRICES[skin["persistentId"]]}
        elif event["type"] == ConfigEventType.HeroPrice:
            for hero in event["newValue"]["heroes"]:
                if hero["persistentId"] in localeConfig.EventToolsChangeFields.HERO_SILVER_PRICES:
                    goldPrice = 0
                    if hero["persistentId"] in localeConfig.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE:
                        goldPrice = localeConfig.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE[hero["persistentId"]]
                    event["defaultValue"][hero["persistentId"]] = {"goldPrice": goldPrice,
                      "silverPrice": localeConfig.EventToolsChangeFields.HERO_SILVER_PRICES[hero["persistentId"]]}
        elif event["type"] == ConfigEventType.RerollShopGroupPrice:
            for group in event["newValue"]["groups"]:
                staticGroup = SD.getSD("ru").getStaticRerollShopGroupById(crc32(group["persistentId"]))
                if staticGroup:
                    event["defaultValue"][group["persistentId"]] = {"minPrice": staticGroup['minPoints'],
                                                                    "maxPrice": staticGroup['maxPoints']}
        elif event["type"] == ConfigEventType.RerollShopGroupProbability:
            for group in event["newValue"]["groups"]:
                staticGroup = localeConfig.EventToolsChangeFields.REROLL_SHOP_GROUP_WEIGHTS.get(crc32(group["persistentId"]))
                default_value = {"rerollTime": 0, "probability": 0, "minUpgradeLevel": 0, "maxUpgradeLevel": 0}
                if staticGroup:
                    default_value["probability"] = staticGroup.LevelToWeights[0]

                # под изменение параметров заточки талантов в группе стоило бы завести отдельный ивент
                # но решили сделать быстро и заточка будет прилетать из ивента с пробабилити
                rerollToUpgradeLevels = localeConfig.EventToolsChangeFields.REROLL_SHOP_GROUP_UPGRADE_LEVELS.get(crc32(group["persistentId"]))
                if rerollToUpgradeLevels:
                    default_value["minUpgradeLevel"] = rerollToUpgradeLevels.MinUpgradeLevel
                    default_value["maxUpgradeLevel"] = rerollToUpgradeLevels.MaxUpgradeLevel

                event["defaultValue"][group["persistentId"]] = default_value
        elif event["type"] == ConfigEventType.RerollShopGroupCurrencies:
            for group in event["newValue"]["groups"]:
                staticGroup = SD.getSD("ru").getStaticRerollShopGroupById(crc32(group["persistentId"]))
                if staticGroup:
                    event["defaultValue"][group["persistentId"]] = {"currencies": staticGroup['currencies']}
        elif event["type"] == ConfigEventType.RerollShopSlotPrice:
            localSD = SD.getSD("ru")
            self.default_reroll_shop_slot_price(event, localSD)
        elif event["type"] == ConfigEventType.RerollShopSlotAmount:
            localSD = SD.getSD("ru")
            self.default_reroll_shop_slot_amount(event, localSD, localeConfig)
        elif event["type"] == ConfigEventType.TalentDropRarity:
            if event["newValue"]["premium"]:
                event["defaultValue"] = {
                    "Class": localeConfig.EventToolsChangeFields.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.Class],
                    "ordinary": localeConfig.EventToolsChangeFields.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.ordinary],
                    "good": localeConfig.EventToolsChangeFields.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.good],
                    "excellent": localeConfig.EventToolsChangeFields.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.excellent],
                    "magnificent": localeConfig.EventToolsChangeFields.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.magnificent],
                    "exclusive": localeConfig.EventToolsChangeFields.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.exclusive],
                    "oldSeeds": self.PremiumGoodSeeds}
            else:
                event["defaultValue"] = {
                    "Class": localeConfig.EventToolsChangeFields.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.Class],
                    "ordinary": localeConfig.EventToolsChangeFields.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.ordinary],
                    "good": localeConfig.EventToolsChangeFields.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.good],
                    "excellent": localeConfig.EventToolsChangeFields.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.excellent],
                    "magnificent": localeConfig.EventToolsChangeFields.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.magnificent],
                    "exclusive": localeConfig.EventToolsChangeFields.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.exclusive],
                    "oldSeeds": self.GoodSeeds}
        elif event["type"] == ConfigEventType.ReforgeTalentPrice:
            event["defaultValue"] = {}
            ldp = []
            for _id, price in localeConfig.EventToolsChangeFields.ReforgePrices.iteritems():
                ldp.append(
                    dict(
                        Rarity = price.Rarity,
                        RerollPrice = price.RerollPrice,
                        UpgradePrice = price.UpgradePrice,
                        talentsToUpgrade = price.TalentsToUpgrade,
                        )
                )
            event["defaultValue"] = {"ReforgePrices": ldp}
        elif event["type"] == ConfigEventType.RerollShopSlots:
            event["defaultValue"] = {
                "usualSlots": localeConfig.EventToolsChangeFields.REROLL_SHOP_ORDINARY_SLOTS,
                "premiumSlots": localeConfig.EventToolsChangeFields.REROLL_SHOP_PREMIUM_SLOTS,
                "maxActiveUsualSlots": localeConfig.EventToolsChangeFields.INACTIVE_REROLL_SHOP_ORDINARY_SLOTS,
                "maxActivePremiumSlots": localeConfig.EventToolsChangeFields.INACTIVE_REROLL_SHOP_PREMIUM_SLOTS}
        elif event["type"] == ConfigEventType.RerollShopPrice:
            event["defaultValue"] = {
                "resource1": localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.Resource1,
                "resource2": localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.Resource2,
                "resource3": localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.Resource3,
                "silver": localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.Silver,
                "gold": localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.Gold,
                "perl": localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.Perl,
                "redPerl": localeConfig.EventToolsChangeFields.REROLL_SHOP_PRICE.RedPerl}
        elif event["type"] == ConfigEventType.FirstBuyPrice:
            for petHouse in event["newValue"]["firstBuys"]:
                if petHouse["persistentId"] in localeConfig.EventToolsChangeFields.FIRST_BUY_GOLD_PRICES:
                    event["defaultValue"][petHouse["persistentId"]] = {"price":
                      localeConfig.EventToolsChangeFields.FIRST_BUY_GOLD_PRICES[petHouse["persistentId"]]}
        elif event["type"] == ConfigEventType.PremiumNotInactive:
            event["defaultValue"] = localeConfig.EventToolsChangeFields.PREMIUM_SLOTS_ARE_NOT_INACTIVE
        elif event["type"] == ConfigEventType.RerollShopGroupSlots:
            localSD = SD.getSD("ru")
            self.default_reroll_shop_group_slots(event, localSD)

    def addCustomEvent(self, customEvent):
        self.eventsMutex.acquire()
        try:
            eventInfo = event(customEvent)
            if eventInfo.isValid:
                self.events.append(eventInfo)
            else:
                err("Bad event line format, skipping: %r" % customEvent)
        finally:
            self.eventsMutex.release()

    def removeCustomEvent(self, persistentId):
        self.eventsMutex.acquire()
        try:
            for event in self.events[:]:
                if event.id == persistentId:
                    self.events.remove(event)
                    break
        finally:
            self.eventsMutex.release()

    def addCustomMap(self, customEvent):
        self.eventMapsMutex.acquire()
        self.eventMapsForBanMutex.acquire()
        try:
            eventMapInfo = EventMap( customEvent )
            if eventMapInfo.isValid:
                if eventMapInfo.isForBan:
                    self.eventMapsForBan.append( eventMapInfo )
                else:
                    self.eventMaps.append( eventMapInfo )
            else:
                err( "Bad eventMap line format, skiping: %r" % customEvent )
        finally:
            self.eventMapsMutex.release()
            self.eventMapsForBanMutex.release()

    def removeCustomMap(self, persistentId):
        self.eventMapsMutex.acquire()
        self.eventMapsForBanMutex.acquire()
        try:
            for map in self.eventMaps[:]:
                if map.id == persistentId:
                    self.eventMaps.remove(map)
                    break
            for map in self.eventMapsForBan[:]:
                if map.id == persistentId:
                    self.eventMapsForBan.remove(map)
                    break
        finally:
            self.eventMapsMutex.release()
            self.eventMapsForBanMutex.release()

    def addTechs(self, customEvent):
        self.techsMutex.acquire()
        try:
            tech = {}
            compensationTypes = customEvent["newValue"]["techType"].split(',')
            for compensationType in compensationTypes:
                if compensationType in ("lamp", "premium", "rating", "guild_buffs", "sieges"):
                    tech[compensationType] = customEvent["newValue"]["compensation"]
                else:
                    warn("addTechs: Unknown compensationType '%s' in event %s", compensationType, customEvent)
            if tech:
                self.techs[customEvent["persistentId"]] = tech
        finally:
            self.techsMutex.release()

    def removeTechs(self, persistentId):
        self.techsMutex.acquire()
        try:
            if persistentId in self.techs:
                del self.techs[persistentId]
        finally:
            self.techsMutex.release()
