# coding:utf-8

import sys
import time

from base.helpers import ClassDict
from modeldata.ModelData import ModelData




import CC



ACC_STATUS_ACTIVE = 1
ACC_STATUS_PROCESS_SAVE = 2
ACC_STATUS_SAVED = 3
ACC_STATUS_LOADED = 4
ACC_STATUS_PROCESS_LOAD = 5
# Состояни аккаунта для случая выгрузки
ACC_STATUS_SHUTDOWN_ACTIVE = 6
ACC_STATUS_SHUTDOWN_PROCESS_SAVE = 7
ACC_STATUS_SHUTDOWN_SAVED = 8


class UserAccount(ClassDict):

    def getConfigValue(self, config_key):
        ##info("UserAccount(auid=%s).getConfigValue(%s)" % (self.auid, config_key))
        return getattr(self.Config.getConfig(self.userlocale), config_key, None)

    def getConfig(self):
        return self.Config.getConfig(self.userlocale)

    def getConfigJson(self):
        return self.Config.getConfig(self.userlocale).generateJsonDict()

    def getFame(self):
        if self.model and isinstance(self.model, ModelData):
            return self.model.getFame()
        return 0

    def setAccStatusDataSaved(self):
        self.finalize_data = 1
        self.acc_status = ACC_STATUS_SAVED

    def setAccStatusDataLoaded(self):
        self.finalize_data = 1
        self.acc_status = ACC_STATUS_LOADED

    def setAccStatusProcessSave(self):
        self.finalize_tm = time.time()
        self.acc_status = ACC_STATUS_PROCESS_SAVE

    def setAccStatusProcessLoad(self):
        self.finalize_tm = time.time()
        self.acc_status = ACC_STATUS_PROCESS_LOAD

    def resetAccStatus(self):
        self.finalize_tm = 0
        self.finalize_data = 0
        self.acc_status = ACC_STATUS_ACTIVE

    def getNickname(self):
        return self.nick or self.sn_nick

def ParseSnuid(sn, info):
    snuid = info.get('snuid', None)
    if not snuid:
        photo = info.get('photo', None)
        if photo:
            if sn == 'fb':
                photo = photo.replace('http://graph.facebook.com/', '')
                index = photo.find('/picture')
                if index >= 0:
                    snuid = photo[:index]
            else:
                pass  # TODO: parse ok snuid from photo :(
    return snuid

def ParseSocialNetworkInfo(result, sn):
    # print 'parse', sn, result
    email = None
    snuid = None
    info = result.get(sn, None)
    if info:
        snuid = ParseSnuid(sn, info)
        email = info.get('email', None)
    return (sn, snuid, email)


def FindSocialNetworkInfo(result, fsn):
    if fsn:
        snid, snuid, email = ParseSocialNetworkInfo(result, fsn)
        if snid and snuid:
            return (snid, snuid, email)

    for key in result.keys():
        if key in CC.AGG_SOCIAL_NETWORK_NAMES:
            snid, snuid, email = ParseSocialNetworkInfo(result, key)
            if snid and snuid:
                return (snid, snuid, email)

    return (None, None, None)
