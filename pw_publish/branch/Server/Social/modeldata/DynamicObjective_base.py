# -*- coding: utf-8 -*-
from base.helpers import debug, err # debug support
from base.helpers import info # info support

from binascii import crc32
from enums import SessionCheckType, DynamicQuestCheckType, ModelDataConditionType, QuestState, CastleResources
from base.helpers import toint

class DynamicObjective_base(object):
    def serializeToFile( self, file, name, lastEventId ):
        pass

    def fillFromSD(self, objectiveDict, lastEventId, quest):
        # convert logic
        objectiveDict["EditId"] = 0
        objectiveDict["Description"] = ""
        objectiveDict["ButtonDescription"] = ""

        self.fill(objectiveDict, lastEventId, quest)

    def fill(self, objective, lastEventId, quest):
        self.EditId = objective["EditId"]
        self.QuestCheckType = objective["QuestCheckType"]
        if (self.QuestCheckType in [DynamicQuestCheckType.SessionInfo, DynamicQuestCheckType.SessionResult]
            and "SessionCondition" in objective):
            persistentIds = objective["SessionCondition"]["PickedHero"].split(",")
            for persistentId in persistentIds:
              self.SessionCondition.PickedHeroes.append(crc32(persistentId))
            mapIds = objective["SessionCondition"]["GameType"].split(",")
            for mapId in mapIds:
              self.SessionCondition.GameTypes.append(mapId)
            self.SessionCondition.CollectingType = objective["SessionCondition"]["CollectingType"]
            self.SessionCondition.TotalValue = objective["SessionCondition"]["TotalValue"]
            self.SessionCondition.IncrementPerBattle = objective["SessionCondition"]["IncrementPerBattle"]
            self.SessionCondition.SessionCheckType = objective["SessionCondition"]["SessionCheckType"]
            if "IsGuildGame" in objective["SessionCondition"]:
                self.SessionCondition.IsGuildGame = bool(objective["SessionCondition"]["IsGuildGame"])
            if "PlayerPartySize" in objective["SessionCondition"] and "EnemyPartySize" in objective["SessionCondition"]:
                self.SessionCondition.PlayerPartySize = objective["SessionCondition"]["PlayerPartySize"]
                self.SessionCondition.EnemyPartySize = objective["SessionCondition"]["EnemyPartySize"]
            if "IsPlayerPartySizeStrongCond" in objective["SessionCondition"] and "IsEnemyPartySizeStrongCond" in objective["SessionCondition"]:
                self.SessionCondition.IsPlayerPartySizeStrongCond = objective["SessionCondition"]["IsPlayerPartySizeStrongCond"]
                self.SessionCondition.IsEnemyPartySizeStrongCond  = objective["SessionCondition"]["IsEnemyPartySizeStrongCond"]
        elif self.QuestCheckType == DynamicQuestCheckType.Instant and "InstantCondition" in objective:
            self.InstantCondition.ResourceType = objective["InstantCondition"]["ResourceType"]
            if self.InstantCondition.ResourceType == CastleResources.TalentsToPay:
                objective["InstantCondition"]["TalentsToPayValue"] = str(objective["InstantCondition"]["TotalValue"])  # все ок, создаём новую переменную TalentsToPayValue
                self.InstantCondition.TalentsToPayValue = objective["InstantCondition"]["TalentsToPayValue"]
                self.fillTalentsToPayTalentsParams()
            elif self.InstantCondition.ResourceType == CastleResources.Custom:
                args = objective["InstantCondition"]["TotalValue"].split(' ')
                self.InstantCondition.CustomCurrencyId = str(args[0])
                self.InstantCondition.TotalValue = int(args[1])
            else:
                try:  # hack: totalval делаем интовым
                    objective["InstantCondition"]["TotalValue"] = int(objective["InstantCondition"]["TotalValue"])
                except Exception:
                    objective["InstantCondition"]["TotalValue"] = 0
                self.InstantCondition.TotalValue = objective["InstantCondition"]["TotalValue"]

        elif self.QuestCheckType == DynamicQuestCheckType.ModelData and "ModelDataCondition" in objective:
            self.ModelDataCondition.TypeToCollect = objective["ModelDataCondition"]["TypeToCollect"]
            if self.ModelDataCondition.TypeToCollect == ModelDataConditionType.CastleLogin:
                quest.QuestState = QuestState.Complete
            persistentIds = objective["ModelDataCondition"]["PersistentId"].split(",")
            for persistentId in persistentIds:
                self.ModelDataCondition.PersistentIds.append(str(crc32(persistentId)))
            self.ModelDataCondition.TotalValue = objective["ModelDataCondition"]["TotalValue"]
            self.ModelDataCondition.LastEventId = lastEventId
        self.Description = objective["Description"]
        self.ButtonDescription = objective["ButtonDescription"]

    def fillTalentsToPayTalentsParams(self):
        # разделяем каждый талант по каждому
        debug("start handle talents to pay talants")

        talentsToPayIdsFromResponse = str(self.InstantCondition.TalentsToPayValue).replace(" ", "").split(',')
        talentsToDeletePersistentIds = self.talentsToDeletePersistentIds

        while len(talentsToDeletePersistentIds):
            talentsToDeletePersistentIds.pop()

        if len(talentsToPayIdsFromResponse) == 0 or talentsToPayIdsFromResponse[0] == '':
            err(":( Can't add talents to pay talents. DynamicQuestValue: {}".format(self.InstantCondition.TalentsToPayValue))
        else:
            # self.DynamicQuestTalentsToPay.talentParams = InstantCondition.TotalValue
            debug("response: {}".format(talentsToPayIdsFromResponse))
            for val in talentsToPayIdsFromResponse:  # Добавляем все таланты в общий список списания
                if val != '':
                    if '(' in val:  # если несколько талантов
                        talentsCount = 1
                        try:
                            talentsCount = val[val.index("(") + 1:val.rindex(")")]
                            talentsCount = int(talentsCount) if talentsCount.isdigit() else 1
                        except Exception:
                            pass
                        for x in range(0, talentsCount):
                            talentsToDeletePersistentIds.append(crc32(val[:val.index("(")]))
                    else:  # если один талант
                        talentsToDeletePersistentIds.append(crc32(val))

            debug("talentsToDeletePersistentIds: {}".format(talentsToDeletePersistentIds.keys()))

    def update(self, objective, lastEventId, quest):
        while len(self.ModelDataCondition.PersistentIds):
            self.ModelDataCondition.PersistentIds.pop()
        while len(self.SessionCondition.PickedHeroes):
            self.SessionCondition.PickedHeroes.pop()
        while len(self.SessionCondition.GameTypes):
             self.SessionCondition.GameTypes.pop()
        self.fill(objective, lastEventId, quest)

    def checkModeConditions(self, lastSessionInfo, fightData):
        isHeroCorrect = lastSessionInfo.PickedHero in self.SessionCondition.PickedHeroes or len(self.SessionCondition.PickedHeroes) == 0
        isMapCorrect = lastSessionInfo.GameType in self.SessionCondition.GameTypes or len(self.SessionCondition.GameTypes) == 0

        isBossKilledCorrect = True
        if self.SessionCondition.CollectingType == "numBossKillsAssist" or self.SessionCondition.CollectingType == "numCatKillAssist" or self.SessionCondition.CollectingType == "numDragonKillAssist":
            iBossesKilled  = toint(fightData.get("numBossKillsAssist", 0))
            iCatsKilled    = toint(fightData.get("numCatKillAssist", 0))
            iDragonsKilled = toint(fightData.get("numDragonKillAssist", 0))
            if iBossesKilled == (iCatsKilled + iDragonsKilled):
                isBossKilledCorrect = True
            else:
                isBossKilledCorrect = False
        debug("checkModeConditions: isBossKilledCorrect=%r", isBossKilledCorrect)

        isWinnerConditionCorrect = True
        if self.SessionCondition.SessionCheckType == SessionCheckType.WinOnly:
            isWinnerConditionCorrect = lastSessionInfo.IsWinner
        elif self.SessionCondition.SessionCheckType == SessionCheckType.Loss:
            isWinnerConditionCorrect = not lastSessionInfo.IsWinner
        
        isGuildFightConditionCorrect = (lastSessionInfo.IsGuildGame and self.SessionCondition.IsGuildGame) or not self.SessionCondition.IsGuildGame
        isGroupSizeCorrect = False
        if (self.SessionCondition.IsPlayerPartySizeStrongCond == 0) and (self.SessionCondition.IsEnemyPartySizeStrongCond == 0):
            isGroupSizeCorrect = (toint(fightData.get("partySize", 1)) >= self.SessionCondition.PlayerPartySize) and (toint(fightData.get("enemyPartySize", 1)) >= self.SessionCondition.EnemyPartySize)
        if (self.SessionCondition.IsPlayerPartySizeStrongCond == 1) and (self.SessionCondition.IsEnemyPartySizeStrongCond == 0):
            isGroupSizeCorrect = (toint(fightData.get("partySize", 1)) == self.SessionCondition.PlayerPartySize) and (toint(fightData.get("enemyPartySize", 1)) >= self.SessionCondition.EnemyPartySize)
        if (self.SessionCondition.IsPlayerPartySizeStrongCond == 0) and (self.SessionCondition.IsEnemyPartySizeStrongCond == 1):
            isGroupSizeCorrect = (toint(fightData.get("partySize", 1)) >= self.SessionCondition.PlayerPartySize) and (toint(fightData.get("enemyPartySize", 1)) == self.SessionCondition.EnemyPartySize)
        if (self.SessionCondition.IsPlayerPartySizeStrongCond == 1) and (self.SessionCondition.IsEnemyPartySizeStrongCond == 1):
            isGroupSizeCorrect = (toint(fightData.get("partySize", 1)) == self.SessionCondition.PlayerPartySize) and (toint(fightData.get("enemyPartySize", 1)) == self.SessionCondition.EnemyPartySize)
        debug("checkModeConditions: isGroupSizeCorrect=%r", isGroupSizeCorrect)        
        return isBossKilledCorrect and isWinnerConditionCorrect and isHeroCorrect and isMapCorrect and isGuildFightConditionCorrect and isGroupSizeCorrect
