# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.UpgradeHeroRequest import *

class Upgrade_hero( SubAction, UpgradeHeroRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "upgrade_hero"

    @model_callback
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
          return

        md = self.acc.model
        if md.MarketingEventsInfo.UpgradeHeroTalentsInfo.UsesLeft <= 0:
            self.end(False)
            return

        self.PersistentId = self.arguments.PersistentId

        # upLevelHero
        levelToUP = 14  #TODO: oleg karlovskiy: hardcode

        hero, heroId = md.findHeroByCrc32(self.PersistentId)
        if hero.IsUpgradeHeroEvent:
            self.end(False)
            return

        # прокачиваем героя до 15 уровня, если он не прокачан до 15 уровня
        expTableNeedLevel = self.acc.SD.data['LevelToExperienceTable']['Levels']['Item'][levelToUP]
        heroLevel = self.acc.SD.getHeroExpLevel(hero.Experience)

        if (heroLevel < levelToUP):
            hero.changeExperience(expTableNeedLevel - hero.Experience, self.acc.model, self.I.WS, self.acc, self.I)

        # выпихиваем все таланты из талантсета
        targetTab = 2
        for talentPos in hero.TalentSets[targetTab].Talents.keys():
            talent = self.acc.model.getTalentByID(hero.TalentSets[targetTab].Talents.get(talentPos))
            if talent:
                staticTalent = self.acc.SD.getStaticTalent(talent)
                if not staticTalent['rarity'] == "Class":  # если они не классовые
                    hero.removeTalentFromTalentSet(targetTab, talent, talent.id, False)  # выкидываем в общий инвентарь, но не чистим actionBar
                    if talent not in self.acc.model.UserInventory.values():
                        self.acc.model.UserInventory.add(talent)
                # else:
                #     levelToPoints = self.acc.SD.data['TalentLevelToPointsAndRarity']['Item'][
                #         getattr(ETalentRarity, staticTalent['rarity'])]['levelToPoints']['Item'][1]
                #     talent.Points = levelToPoints

        # создаём и расставляем таланты
        rowCount = 0
        mightyTalentSet = self.acc.SD.getStaticHeroByClassId(hero.PersistentId)['mightyTalentSet']
        talentSetGrid = hero.TalentSets[targetTab]

        for row in mightyTalentSet['levels']['Item']:
            talPos = 1
            for pos in row['talents']['Item']:
                targetTalent = pos['talent']  # mightyTalentSet['levels']['Item'][row]['talents']['Item'][pos]['talent']
                if targetTalent and 'persistentId' in targetTalent and targetTalent['persistentId']:
                    if not targetTalent['rarity'] == "Class":
                        #зацепили нужный талант, теперь пройдёмся по всем слотам GRID и как только находим пустой ставим его туда
                        for itersInSix in xrange(1, 7):
                            finalPos = rowCount * 6 + itersInSix
                            if not talentSetGrid.Talents[finalPos]:
                                # внутри цикла и тучи условий
                                item_id = md.addNewTalent()
                                addingTalent = md.getTalentByID(item_id)
                                addingTalent.PersistentId = crc32(targetTalent['persistentId'])
                                addingTalent.defaultForHero = hero
                                addingTalent.Owner = hero
                                if addingTalent.canBeSoulbound(self.acc.SD):
                                    addingTalent.Soulbound = hero

                                # количество очков, которое нужно дать таланту
                                levelToPoints = self.acc.SD.data['TalentLevelToPointsAndRarity']['Item'][
                                    getattr(ETalentRarity, targetTalent['rarity'])]['levelToPoints']['Item'][5]

                                addingTalent.Points = levelToPoints

                                md.UserInventory.add(addingTalent)

                                talentSetGrid.Talents.add(finalPos, addingTalent.id)
                                addingTalent.ParentTalentSets.add(targetTab, talentSetGrid.id)

                                break
                talPos += 1
            rowCount += 1

        #колдуем с экшн баром
        actionBarIdx = 0
        for idx in xrange(1, 37):   #1 - 37 это все таланты
            talent = md.getTalentByID(hero.TalentSets[targetTab].Talents.get(idx))
            if talent:
                staticTalent = self.acc.SD.getStaticTalent(talent)
                if not staticTalent['type'] == "Passive" and not staticTalent['type'] == "Simple" and actionBarIdx < 9:
                    talentSetGrid.ActionBar[actionBarIdx] = talent.getID()
                    talentSetGrid.InstaCast.set(actionBarIdx, False)
                    actionBarIdx += 1

        for idx in xrange(actionBarIdx, 10):
            talentSetGrid.ActionBar[idx] = -1
            talentSetGrid.InstaCast.set(actionBarIdx, False)

        hero.CalcForce(self.acc.model, self.I.WS, self.acc, targetTab, True)  # пересчитываем мощь

        self.acc.SD.initTalantSetCrc(hero.PersistentId)  # считаем CRC

        hero.IsUpgradeHeroEvent = True  # говорим, что проапали героя
        md.MarketingEventsInfo.UpgradeHeroTalentsInfo.UsesLeft -= 1
        self.I.STATS.addRuneHeroApply(self.acc.auid, self.acc.model.getUpgHeroLampType(), hero.class_name)

        self.end(True)

    def end(self, ok):
        self.response["ok"] = 1 if ok else 0
        self.fin()

