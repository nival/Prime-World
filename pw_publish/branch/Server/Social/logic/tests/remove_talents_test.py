import sys
sys.path.append('../')
from logic.remove_talents import *
from binascii import crc32
sys.path.append('../..')
from enums import *
from logic.item_move_inv2ts import *

class remove_talents_test:
    def remove_talents_test( self, env ):
        modeldata = env.acc.model

        modeldata.Resources.Silver = silver = 0

        talent = env.add_talent(modeldata, "G137")
        modeldata.UserInventory.add( talent )

        requests = [ ( Remove_talents, RemoveTalentsRequest( modeldata, { "talents" : ["" + str(talent.id) + ""] }, False ) ) ]
        changeList = env.execActions( requests )

        assert modeldata.getTalentByID(talent.id) == None
        staticTalent = env.acc.SD.getStaticTalent( talent )
        assert modeldata.Resources.Silver - silver == int(env.acc.SD.getTalentSellPrice(staticTalent).Silver)
    
    def remove_class_talents_test( self, env ):
        modeldata = env.acc.model

        modeldata.Resources.Silver = silver = 0

        talent = env.add_talent(modeldata, "Rockman_A1")
        modeldata.UserInventory.add( talent )

        requests = [ ( Remove_talents, RemoveTalentsRequest( modeldata, { "talents" : ["" + str(talent.id) + ""] }, False ) ) ]
        changeList = env.execActions( requests )

        assert modeldata.getTalentByID(talent.id).id == talent.id
        assert modeldata.Resources.Silver == silver

    def remove_talents_many_test( self, env ):
        modeldata = env.acc.model

        modeldata.Resources.Silver = silver = 0
        defaultinventoryLength = len(modeldata.UserInventory)
        amount = 10
        talents_str = ""
        for i in xrange(amount):
          talent = env.add_talent(modeldata, "G137")
          talents_str += str(talent.id) + ","
          modeldata.UserInventory.add( talent )
        talents_str = talents_str[:-1]
        assert len(modeldata.UserInventory) == amount + defaultinventoryLength

        requests = [ ( Remove_talents, RemoveTalentsRequest( modeldata, { "talents" : ["" + talents_str + ""] }, False ) ) ]
        changeList = env.execActions( requests )

        assert len(modeldata.UserInventory) == defaultinventoryLength
        staticTalent = env.acc.SD.getStaticTalent( talent )
        assert modeldata.Resources.Silver - silver == int(env.acc.SD.getTalentSellPrice(staticTalent).Silver) * amount

    def remove_talents_many_soulbound_test( self, env ):
        modeldata = env.acc.model

        modeldata.Resources.Silver = silver = 0
        defaultinventoryLength = len(modeldata.UserInventory)
        talents_str = ""

        hero = env.add_hero(modeldata, 'mowgly')

        amount = 10

        for i in xrange(amount):
          talent = env.add_talent(modeldata, "G137")
          talent.Soulbound = hero
          talents_str += str(talent.id) + ","
          modeldata.UserInventory.add( talent )
        assert len(modeldata.UserInventory) == amount + defaultinventoryLength

        talents_str = talents_str[:-1]

        requests =  [ ( Remove_talents, RemoveTalentsRequest( modeldata, { "talents" : ["" + talents_str + ""] }, False ) ) ]
        changeList = env.execActions( requests )

        assert len(modeldata.UserInventory) == defaultinventoryLength
        staticTalent = env.acc.SD.getStaticTalent( talent )
        assert modeldata.Resources.Silver - silver == int(env.acc.SD.getTalentSellPrice(staticTalent).Silver) * amount

    def remove_talents_with_guild_info_test( self, env ):
        modeldata = env.acc.model

        modeldata.Resources.Silver = silver = 0
        defaultinventoryLength = len(modeldata.UserInventory)
        talents_str = ""

        hero = env.add_hero(modeldata, 'mowgly')

        talent = env.add_talent(modeldata, "G137")
        talent.Soulbound = hero
        modeldata.UserInventory.add( talent )
        gbi, gbi_id = env.acc.model.newGuildBankInfo()
        talent.GuildBankInfo = gbi
        talent.GuildBankInfo.GuildAuid = 1
        talent.GuildBankInfo.GuildTalentId = 2
        talent.GuildBankInfo.OwnerId = env.acc.auid
        talent.GuildBankInfo.HeroClassId = hero.PersistentId

        assert len(modeldata.UserInventory) == 1 + defaultinventoryLength


        requests =  [ ( Remove_talents, RemoveTalentsRequest(modeldata, {"talents": ["" + str(talent.id) + ""]}, False))]
        changeList = env.execActions( requests )

        assert len(modeldata.UserInventory) == defaultinventoryLength
        staticTalent = env.acc.SD.getStaticTalent( talent )
        assert modeldata.Resources.Silver - silver == int(env.acc.SD.getTalentSellPrice(staticTalent).Silver)


    def remove_talents_from_ts_test( self, env ):
        modeldata = env.acc.model
        modeldata.LordInfo.Fame = 100500
        modeldata.Resources.Silver = silver = 1000
        modeldata.Resources.Gold = gold = 1000

        talent = env.add_talent(modeldata, "G137")
        modeldata.UserInventory.add( talent )
        staticTalent = env.acc.SD.getStaticTalent(talent)
        tsSlotId = staticTalent['minLevel'] * 6 + 1

        for heroId in modeldata.Heroes:
            hero = modeldata.getHeroByID( heroId )
            if hero.class_name == "highlander":
                hero.TalentSets[1].Talents.remove(tsSlotId)
                break

        assert hero.TalentSets[1].Talents.get(tsSlotId) == None
        requests = [ ( Item_move_inv2ts , ItemMoveInvToTsRequest( modeldata, { "src_hero_id" : ["" + str(hero.id) + ""],
                                                                                "src_item_id" : ["" + str(talent.id) + ""],
                                                                                "dest_slot_id" : ["" + str(tsSlotId) + ""],
                                                                                "dest_item_id" : ["" + str(0) + ""],
                                                                                "useLamp" : ["false"],
                                                                                "talent_set_id": ["1"]}, False ) ) ]
        changeList = env.execActions( requests )
        assert hero.TalentSets[1].Talents.get(tsSlotId) == talent.id

        requests = [(Remove_talents, RemoveTalentsRequest(modeldata, {"talents": ["" + str(talent.id) + ""]}, False))]
        changeList = env.execActions( requests )

        assert talent.id not in modeldata.UserInventory
        assert hero.TalentSets[1].Talents.get(tsSlotId) == None
