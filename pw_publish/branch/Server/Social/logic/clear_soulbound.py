#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData
from logic.requests.ClearSoulboundRequest import ClearSoulboundRequest

class Clear_soulbound( SubAction, ClearSoulboundRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "clear_soulbound"
  debug = True

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    for talentId in self.acc.model.UserInventory:
      talent = self.acc.model.getTalentByID(talentId)
      if talent.isSoulbounded():
        talent.Soulbound = IGuidGenerator.InvalidUID
        if talent.GuildBankInfo.get():
          talent.GuildBankInfo.HeroClassId = 0
          # Если информация о таланте ещё хранится в гильдии, обновим её
          if talent.GuildBankInfo.OwnerId != self.acc.auid and talent.GuildBankInfo.OwnerId != 0:
            self.I.GS.guildTalentInfoUpdate( self.acc, talent.GuildBankInfo.GuildTalentId, talent.Points, talent.GuildBankInfo.HeroClassId, self.onUpdateGuildData )
          else:
            talent.GuildBankInfo = None

        staticTalent = self.acc.SD.getStaticTalent( talent )
        if staticTalent:        
          self.acc.model.addStatisticEvent( StatisticEventType.TALENT_UNSOULBOUND, staticTalent['persistentId'], 1 )

    self.response["ok"] = 1 # success 
    self.fin()

  @model_callback
  @action_timing
  def onUpdateGuildData( self, response ):
    if response:
      info( "onUpdateGuildData response: %s" % self.I.MD.pretty(response) )
      GuildData_changes = response.get("GuildData") or []
      if GuildData_changes:
        try:
          ModelChangeApplicator.apply( self.acc, "guilddata", GuildData, GuildData_changes )
        except:
          catch()
      self.acc.pending_events.append( {"GuildData": { "GuildData": GuildData_changes }} )
      if self.acc.pending_handler:
        self.acc.pending_handler()
