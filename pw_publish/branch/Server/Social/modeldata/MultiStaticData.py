# -*- coding: utf-8 -*-

from base.helpers import *
from copy import deepcopy
from StaticData import StaticData


class MultiStaticData:
    def __init__(self, path, config, loadLocales = True, applyOverrides = True):
        self.__defaultStaticData = {}
        self.mainStaticData = {}
        self.staticDatas = {}
        self.loadLocales = True
        #
        self.__defaultStaticData = StaticData(path, config, applyOverrides)
        self.__defaultStaticData.DynamicQuests = {}
        self.__defaultStaticData.DynamicQuestPulls = {}
        self.mainStaticData = deepcopy(self.__defaultStaticData)
        self.mainStaticData.DynamicQuests["isMainSD"] = True
        self.loadLocales = loadLocales
        if loadLocales:
            self.__loadLocaleStaticDatas()

    def __loadLocaleStaticDatas(self):
        path = os.path.dirname(os.path.realpath(__file__))
        localesfile = os.path.normpath(os.path.join(path, "locales.txt"))
        file = open(localesfile, "r")
        lines = file.readlines()
        file.close()
        for line in lines:
            #locale in ""
            time1 = time.time()
            startIdx = line.find('"', 0)
            endIdx = line.find('"', startIdx+1)
            if endIdx == -1 or startIdx == -1:
                err("Bad line format(id), skip: %r" % line)
                continue
            localeName = line[startIdx+1:endIdx]
            localeName = localeName.lower()

            self.staticDatas[localeName] = deepcopy(self.mainStaticData)
            self.staticDatas[localeName].DynamicQuests["isMainSD"] = False
            info("Added static data for locale %r, time: %.3f sec", localeName, time.time() - time1)

    def reloadStaticData(self, config):
        debug("deepcopy...")
        self.mainStaticData = deepcopy(self.__defaultStaticData)
        debug("reloadConfigDependendFields...")
        self.mainStaticData.reloadConfigDependendFields(config)
        if self.loadLocales:
            self.__loadLocaleStaticDatas()

    def reloadLocaleStaticData(self, locale):
        if self.hasSDForLocale(locale):
            self.staticDatas[locale] = deepcopy(self.mainStaticData)
            self.staticDatas[locale].DynamicQuests["isMainSD"] = False

    def getSD(self, val):
        if isinstance(val, basestring):
            key = val.lower()
            if key in self.staticDatas:
                return self.staticDatas[key]
        return self.mainStaticData

    def hasSDForLocale(self, val):
        if isinstance(val, basestring):
            key = val.lower()
            if key in self.staticDatas:
                return True
        return False

    def getMainSD(self):
        return self.mainStaticData

    def backupDynamicQuests(self):
        dynamicQuests = {}
        dynamicQuestPulls = {}
        for locale in self.staticDatas:
            dynamicQuests[locale] = deepcopy(self.staticDatas[locale].DynamicQuests)
            dynamicQuestPulls[locale] = deepcopy(self.staticDatas[locale].DynamicQuestPulls)
        return dynamicQuests, dynamicQuestPulls

    def loadDynamicQuests(self, dynamicQuests, dynamicQuestPulls):
        self.mainStaticData.DynamicQuests["isMainSD"] = True
        for locale in self.staticDatas:
            self.staticDatas[locale].DynamicQuestPulls = deepcopy(dynamicQuestPulls[locale])
            self.staticDatas[locale].DynamicQuests = deepcopy(dynamicQuests[locale])
            self.staticDatas[locale].DynamicQuests["isMainSD"] = False

    def validateDynamicQuests(self):
        for locale in self.staticDatas:
            for questId in self.staticDatas[locale].DynamicQuests.keys():
                if questId == "isMainSD":
                    continue
                questInfo = self.staticDatas[locale].DynamicQuests[questId]
                try:
                    if "QuestEndTime" in questInfo and (int(questInfo["QuestEndTime"]) != 0 and
                                                        int(questInfo["QuestEndTime"]) < int(time.time())):
                        del self.staticDatas[locale].DynamicQuests[questId]
                except Exception:
                    catch()
                    del self.staticDatas[locale].DynamicQuests[questId]
            for pullId in self.staticDatas[locale].DynamicQuestPulls.keys():
                pullInfo = self.staticDatas[locale].DynamicQuestPulls[pullId]
                try:
                    if "RotationEndTime" in pullInfo and (int(pullInfo["RotationEndTime"]) != 0 and
                                                        int(pullInfo["RotationEndTime"]) < int(time.time())):
                        del self.staticDatas[locale].DynamicQuestPulls[pullId]
                except Exception:
                    catch()
                    del self.staticDatas[locale].DynamicQuestPulls[pullId]