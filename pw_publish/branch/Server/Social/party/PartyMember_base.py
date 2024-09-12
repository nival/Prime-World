#!/usr/bin/env python

class PartyMember_base:
    def copyMember(self, member):
        self.isValidTS = member.isValidTS
        self.isEnemy = member.isEnemy
        self.isInventoryFull = member.isInventoryFull
        self.banEndTime = member.banEndTime
        self.isTamburReady = member.isTamburReady
        self.flagType = member.flagType
        self.flagPersistentId = member.flagPersistentId
        self.isMMAllowed = member.isMMAllowed
        self.isLeaver = member.isLeaver
        self.tournamentDynQuestId = member.tournamentDynQuestId
        self.dependedTournamentQuests = member.dependedTournamentQuests
        self.IsAnimatedAvatar = member.IsAnimatedAvatar
        self.LeagueIndex = member.LeagueIndex