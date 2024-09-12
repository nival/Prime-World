#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from party_action import *
import cfg
from logic.requests.PartyInviteRequest import PartyInviteRequest

class Party_invite( Party_action, PartyInviteRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "party_invite"
  @action_timing
  def onStart(self):

      isTournament = self.acc.getConfig().TournamentSettings.IS_TOURNAMENT_SERVER

      if isTournament and self.acc.db.auid in cfg.TOURNAMENT_SPECTATOR_AUIDS:
          self.errorResponse( EC.TOURNAMENT_SPECTATOR_CANNOT_INVITE, "Spectator can not invite" )
          return

      if isTournament and self.getIntParam( "invite_auid", 0 ) in cfg.TOURNAMENT_SPECTATOR_AUIDS:
          self.errorResponse( EC.TOURNAMENT_SPECTATOR_CANNOT_INVITE, "Spectator can not invite" )
          return
      leaver = True if LordStatus.Leaver == self.acc.model.getInternalUserStatus(self.acc.getConfig()) else False
      
      banEndTime = self.acc.model.getBanEndTime()
      if banEndTime <= int( time.time() ):
          banEndTime = 0
          
      tournamentDynQuestId, dependedTournamentQuests = self.acc.model.getActualTournamentQuestPersistentId()
      isInventoryFull = self.acc.model.isInventoryFull()
      if not self.acc.party_id:
          self.acc.party_id = self.I.WS.nextInt64GUID( "party" )
          info("PartyInviteAction (auid=%s): issuing temp party_id=%s" % (self.acc.auid, self.acc.party_id))
          self.addArguments( party_id=self.acc.party_id, is_temp_party_id=1, flagType=self.acc.model.FlagInfo.FlagType,
                             flagPersistentId=self.acc.model.FlagInfo.PersistentId, isMMAllowed=self.acc.db.isRegularMMAllowed,
                             isInventoryFull=isInventoryFull, isLeaver=leaver, banEndTime=banEndTime,
                             tournamentDynQuestId=tournamentDynQuestId, dependedTournamentQuests=dependedTournamentQuests)
      elif not self.getIntParam("party_id"):
          self.addArguments( party_id=self.acc.party_id, flagType=self.acc.model.FlagInfo.FlagType,
                             flagPersistentId=self.acc.model.FlagInfo.PersistentId, isMMAllowed=self.acc.db.isRegularMMAllowed,
                             isInventoryFull=isInventoryFull, isLeaver=leaver, banEndTime=banEndTime,
                             tournamentDynQuestId=tournamentDynQuestId, dependedTournamentQuests=dependedTournamentQuests)
      return Party_action.onStart(self)
