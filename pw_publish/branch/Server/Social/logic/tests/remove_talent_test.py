import sys
sys.path.append('../')
from logic.remove_talents import *
from binascii import crc32
import time
sys.path.append('../..')
from enums import *
import EC

class remove_talent_test:
  def remove_talent_test( self, env ):
    modeldata = env.acc.model
    talent = env.add_talent(modeldata, "G137")
    modeldata.UserInventory.add( talent )
    silver = modeldata.Resources.Silver 

    requests = [ ( Remove_talents, RemoveTalentsRequest( modeldata, { "talents" : ["" + str(talent.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.getTalentByID(talent.id) == None
    staticTalent = env.acc.SD.getStaticTalent( talent )
    assert modeldata.Resources.Silver - silver == int(env.acc.SD.getTalentSellPrice(staticTalent).Silver)

  def remove_talent_from_talentset_test( self, env ):
    modeldata = env.acc.model   
    silver = modeldata.Resources.Silver = 0
    
    talent = env.add_talent(modeldata, "G137")
    hero = env.add_hero(modeldata, 'mowgly')

    hero.TalentSets[0].Talents.add(1, talent.id)
    modeldata.UserInventory.add(talent)
    requests = [ ( Remove_talents, RemoveTalentsRequest( modeldata, { "talents" : ["" + str(talent.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.getTalentByID(talent.id) == None
    staticTalent = env.acc.SD.getStaticTalent( talent )
    assert modeldata.Resources.Silver - silver == int(env.acc.SD.getTalentSellPrice(staticTalent).Silver)


  def remove_class_talent_test( self, env ):
    modeldata = env.acc.model
    talent = env.add_talent(modeldata, "Rockman_A1")
    defaultTSLength = len(modeldata.UserInventory)
    modeldata.UserInventory.add( talent )

    requests = [ ( Remove_talents, RemoveTalentsRequest( modeldata, { "talents" : ["" + str(talent.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert len(modeldata.UserInventory) == 1 + defaultTSLength
    assert changeList[0].get('ec') == EC.DEBUG_MESSAGE 
    
  def remove_not_existing_talent_test( self, env ):
    modeldata = env.acc.model

    requests = [ ( Remove_talents, RemoveTalentsRequest( modeldata, { "talents" : ["100500"] }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert changeList[0].get('ec') == EC.DEBUG_MESSAGE

  def remove_guild_talent_test( self, env ):
    modeldata = env.acc.model
    talent = env.add_talent(modeldata, "G137")
    gbi, gbi_id = modeldata.newGuildBankInfo()
    talent.GuildBankInfo = gbi_id
    talent.GuildBankInfo.OwnerId = env.acc.auid + 1

    modeldata.UserInventory.add( talent )
    silver = modeldata.Resources.Silver

    requests = [ ( Remove_talents, RemoveTalentsRequest( modeldata, { "talents" : ["" + str(talent.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert changeList[0].get("ec") == EC.GUILD_BANK_TALENT_IMPROPER_USE
    assert modeldata.getTalentByID(talent.id) != None
    assert modeldata.Resources.Silver == silver