# -*- coding: utf-8 -*-
from subaction import *
from binascii import crc32
import math

class GiveBackTalentsForClassRefinement:
    basicPoints = [0, 111, 334, 778, 1668]

    def convertModelData(self, env, acc, md, idict):
        totalPoints = 0
        for talId in md.ItemsKeeper:
            talent = md.getTalentByID(talId)
            staticTalent = acc.SD.getStaticTalent(talent)
            if staticTalent:
                if staticTalent['rarity'] == "Class" and talent.Points > 0:
                    totalPoints += talent.Points
                    talent.Points = self.getNewPointsFromStars(talent.Points, staticTalent, acc.SD)
        totalTalents = int(math.ceil(totalPoints / 110.0))
        for i in xrange(0, totalTalents):
            talent_id = md.addNewTalent()
            talent = md.getTalentByID(talent_id)
            talent.IsNew = True
            talent.ActionBarIdx = -1
            talent.PersistentId = crc32("G199")
            talent.Soulbound = None
            md.UserInventory.add(talent_id)
        return md, acc.db

    def getNewPointsFromStars(self, points, staticTalent, SD):
        # найдём уровни вокруг заточки в старой сетке
        prLevel, nextLevel = self.getTalentPointsForCurrentAndNextLevels(points)
        newPointsToLevel = [0] + SD.getTalentPointsToLevel(staticTalent)
        # если талант заточен по максимуму, просто выдаём максимальную заточку для классовых
        if nextLevel is None:
            return newPointsToLevel[-1]
        if prLevel == nextLevel:
            return newPointsToLevel[prLevel] + int(newPointsToLevel[nextLevel] *
                                                   (self.basicPoints[nextLevel] - points)/self.basicPoints[nextLevel])
        return newPointsToLevel[prLevel] + int((newPointsToLevel[nextLevel] - newPointsToLevel[prLevel]) *
                      (self.basicPoints[nextLevel] - points)/(self.basicPoints[nextLevel] - self.basicPoints[prLevel]))


    def getTalentPointsForCurrentAndNextLevels ( self, target_talent_points ):
        it = -1
        prev = 0
        next = None
        if target_talent_points == self.basicPoints[-1]:
            return -1, -1
        for points in self.basicPoints:
            if target_talent_points == points:
                return it + 1, it + 1
            if target_talent_points < points:
                break
            it += 1
        if it != -1:
            prev = it
        if it < len(self.basicPoints) - 1:
            next = it + 1
        return prev, next