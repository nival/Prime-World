# -*- coding: utf-8 -*-

from base.helpers import *
from binascii import crc32  # zlib version is not cross-platform
from enums.TutorialState import *

class ReplaceTutorialQuests3_0:
    def convertModelData(self, env, acc, md, dct):
        linfo = pathFind(dct,"ModelData/LordInfo/LordInfo")
        if linfo and linfo.get("TutorialState") == TutorialState.BattleQuestAdded:
            md.LordInfo.TutorialState = TutorialState.Skipped
        return md, acc.db
