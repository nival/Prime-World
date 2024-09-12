# -*- coding: utf-8 -*-
from subaction import *

class RecountGreenTalents:
    greenTalents = None

    def __init__(self):
        if not self.greenTalents:
            self.__class__.greenTalents = ["G196","G058","G016","G004","G163","G125","G178","G136","G059","G024","G162",
                                           "G005","G124","G142","G014","G173","G135","G186","G048","G161","G203","G015",
                                           "G105","G134","G211","G062","G116","G158","G150","G037","G159","G117","G036",
                                           "G151","G097","G143","G152","G114","G106","G148","G140","G095","G149","G107",
                                           "G094","G141","G133","G204","G175","G167","G008","G121","G174","G001","G166",
                                           "G120","G139","G010","G018","G123","G165","G002","G011","G160","G176","G019",
                                           "G122","G076","G003","G164","G112","G115","G177","G025","G021","G146","G108",
                                           "G100","G032","G109","G147","G104","G066","G056","G101","G031","G118","G110",
                                           "G098","G026","G102","G023","G119","G113","G038","G111","G099","G103","G022"]

    def convertModelData(self, env, acc, md, idict):
        greenRarity = getattr(ETalentRarity, "good")
        levelToGreenPoints = [0] + acc.SD.data['TalentLevelToPointsAndRarity']['Item'][greenRarity]['levelToPoints']['Item']
        for talId in md.ItemsKeeper:
            talent = md.getTalentByID(talId)
            staticTalent = acc.SD.getStaticTalent(talent)
            if staticTalent:
                if staticTalent['persistentId'] in self.greenTalents and talent.Points > 0:
                    talent.Points = self.getNewPointsFromStars(talent.Points, staticTalent, acc.SD, levelToGreenPoints)
        return md, acc.db

    def getNewPointsFromStars(self, points, staticTalent, SD, levelToGreenPoints):
        # найдём уровни вокруг заточки в старой сетке
        prLevel, nextLevel = self.getTalentPointsForCurrentAndNextLevels(points, levelToGreenPoints)
        newPointsToLevel = [0] + SD.getTalentPointsToLevel(staticTalent)
        # если талант заточен по максимуму, просто выдаём максимальную заточку для классовых
        if nextLevel is None:
            return newPointsToLevel[-1]
        if prLevel == nextLevel:
            return newPointsToLevel[prLevel] + int(newPointsToLevel[nextLevel] *
                                                   (levelToGreenPoints[nextLevel] - points)/levelToGreenPoints[nextLevel])
        return newPointsToLevel[prLevel] + int((newPointsToLevel[nextLevel] - newPointsToLevel[prLevel]) *
                      (points - levelToGreenPoints[prLevel])/(levelToGreenPoints[nextLevel] - levelToGreenPoints[prLevel]))

    def getTalentPointsForCurrentAndNextLevels (self, target_talent_points, levelToGreenPoints):
        it = -1
        prev = 0
        next = None
        if target_talent_points == levelToGreenPoints[-1]:
            return -1, -1
        for points in levelToGreenPoints:
            if target_talent_points == points:
                return it + 1, it + 1
            if target_talent_points < points:
                break
            it += 1
        if it != -1:
            prev = it
        if it < len(levelToGreenPoints) - 1:
            next = it + 1
        return prev, next