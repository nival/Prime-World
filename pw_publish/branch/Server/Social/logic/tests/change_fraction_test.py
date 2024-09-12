import sys
sys.path.append('../')
from logic.all import *
from logic.requests.all import *
from binascii import crc32
import time
sys.path.append('../..')
from enums import *
import datetime
from Events.event import *

class change_fraction_test:
    def change_fraction_test( self, env ):
        modeldata = env.acc.model
        assert env.acc.db.fraction == 'A'
        hiredHeroes = 0
        for heroId in modeldata.HeroesKeeper:
            hero = modeldata.getHeroByID( heroId )
            if hero.Hired:
                hiredHeroes += 1

        modeldata.Resources = env.generate_resources(100000)
        fame = 80000
        modeldata.LordInfo.Fame = fame
        gold = 100
        modeldata.Resources.Gold = gold

        requests = [ ( Hire_hero, HireHeroRequest( modeldata, { "PersistentId" : [crc32('inventor')] }, False ) ),
                     ( Change_fraction, ChangeFractionRequest( modeldata, { "fraction" : ['B'] }, False ) ) ]
        changeList = env.execActions( requests )

        hiredHeroes2 = 0
        for heroId in modeldata.HeroesKeeper:
            hero = modeldata.getHeroByID( heroId )
            if hero.Hired:
                hiredHeroes2 += 1
        assert hiredHeroes2 == hiredHeroes + 1
        assert env.acc.db.fraction == 'B'
        hero, heroId = modeldata.findHeroByCrc32( crc32('inventor') )
        assert heroId != 0
        hero, heroId = modeldata.findHeroByCrc32( crc32('artist') )
        assert heroId == 0

        assert env.acc.db.fractionChanged == 1
        assert modeldata.Resources.Gold == gold

    def chage_fraction_reset_quests( self, env ):
        modeldata = env.acc.model

        modeldata.Resources = env.generate_resources(10000)
        modeldata.LordInfo.Fame = 80
        modeldata.Resources.Gold = 100

        PersistentId = crc32("s12_qA")
        staticQuest = env.acc.SD.getStaticQuestById( PersistentId )
        addedQuest = modeldata.addQuest( staticQuest, None, None, False, False, env.I.STATS, env.acc )
        modeldata.CompletedQuests.add(addedQuest)

        modeldata.addQuest(env.acc.SD.getStaticQuestById( crc32("c31_qA") ), None, None, False, True, env.I.STATS, env.acc)

        assert len(modeldata.ActiveQuests) == 2
        assert len(modeldata.CompletedQuests) == 2
        assert len(modeldata.PendingQuests) == 1

        requests = [ ( Change_fraction, ChangeFractionRequest( modeldata, { "fraction" : ['B'] }, False ) ) ]
        changeList = env.execActions( requests )

        assert len(modeldata.ActiveQuests) == 2
        assert len(modeldata.CompletedQuests) == 2
        assert len(modeldata.PendingQuests) == 1

        s12_qB = None
        for questId in modeldata.CompletedQuests.keys():
            quest = modeldata.getQuestByID(questId)
            if quest.persistentId == crc32("s12_qB"):
                s12_qB = quest

        #assert s12_qB is not None

    def change_fraction_no_gold_test( self, env ):
        modeldata = env.acc.model
        assert env.acc.db.fraction == 'A'
        modeldata.Resources.Gold = 0
        fractionChanged = env.I.Config.getConfig( env.acc.userlocale ).FREE_FRACTION_CHANGES
        env.acc.db.fractionChanged = fractionChanged

        requests = [ ( Change_fraction, ChangeFractionRequest( modeldata, { "fraction" : ['B'] }, False ) ) ]
        changeList = env.execActions( requests )

        assert env.acc.db.fraction == 'A'
        assert (env.acc.db.fractionChanged == fractionChanged)
        assert (modeldata.Resources.Gold == 0)

    def change_fraction_for_gold_test( self, env ):
        modeldata = env.acc.model
        assert env.acc.db.fraction == 'A'
        modeldata.Resources.Gold = env.I.Config.getConfig( env.acc.userlocale ).COST_FRACTION_CHANGE
        fractionChanged = env.I.Config.getConfig( env.acc.userlocale ).FREE_FRACTION_CHANGES
        env.acc.db.fractionChanged = fractionChanged

        requests =  [ ( Change_fraction, ChangeFractionRequest( modeldata, { "fraction" : ['B'] }, False ) ) ]
        changeList = env.execActions( requests )

        assert env.acc.db.fraction == 'B'
        assert (env.acc.db.fractionChanged == fractionChanged + 1)
        assert (modeldata.Resources.Gold == 0)

    def change_fraction_hero_in_mm_test( self, env ):
        modeldata = env.acc.model
        assert env.acc.db.fraction == 'A'
        hiredHeroes = 0
        for heroId in modeldata.HeroesKeeper:
            hero = modeldata.getHeroByID( heroId )
            if hero.Hired:
                hiredHeroes += 1
                hero.InMatchmaking = True

        requests = [ ( Hire_hero, HireHeroRequest( modeldata, { "PersistentId" : [crc32('inventor')] }, False ) ),
                     ( Change_fraction, ChangeFractionRequest( modeldata, { "fraction" : ['B'] }, False ) ) ]
        changeList = env.execActions( requests )

        assert( changeList.get("ModelData") == None )
        assert env.acc.db.fraction == 'A'

    def change_fraction_antoganist_exp_test( self, env ):
        modeldata = env.acc.model
        assert env.acc.db.fraction == 'A'
        hero = env.add_hero(modeldata, "inventor")

        requests = [ ( Give_experience, GiveExperienceRequest( modeldata, { "hero_id" : ["" + str(hero.id) + ""], "value" : ["500"] }, False ) ),
                     ( Change_fraction, ChangeFractionRequest( modeldata, { "fraction" : ['B'] }, False ) ) ]

        changeList = env.execActions( requests )

        assert (env.acc.db.fractionChanged == 1)
        assert env.acc.db.fraction == 'B'
        hero, heroId = modeldata.findHeroByCrc32( crc32('inventor') )
        assert heroId != 0
        hero, heroId = modeldata.findHeroByCrc32( crc32('artist') )
        assert heroId == 0

    def change_fraction_antoganist_stat_points_test( self, env ):
        modeldata = env.acc.model
        assert env.acc.db.fraction == 'A'
        hero = env.add_hero(modeldata, "inventor")
        hero.changeExperience( 100500, modeldata, env.I.WS, env.acc, env.I )
        points = hero.TalentSets[0].Stats.StatPoints
        assert points > 0

        requests = [ ( Change_fraction, ChangeFractionRequest( modeldata, { "fraction" : ['B'] }, False ) ) ]

        changeList = env.execActions( requests )

        assert (env.acc.db.fractionChanged == 1)
        assert env.acc.db.fraction == 'B'
        hero, heroId = modeldata.findHeroByCrc32( crc32('inventor') )
        assert heroId != 0
        hero, heroId = modeldata.findHeroByCrc32( crc32('artist') )
        assert heroId == 0

    def change_fraction_antoganist_stat_points2_test( self, env ):
        modeldata = env.acc.model
        assert env.acc.db.fraction == 'A'
        hero = env.add_hero(modeldata, "inventor")
        hero.changeExperience( 100500, modeldata, env.I.WS, env.acc, env.I )
        points = hero.TalentSets[0].Stats.StatPoints
        assert points > 0

        requests = [ ( Increase_stat, IncreaseStatRequest( modeldata, { "hero_id" : ["" + str(hero.id) + ""], "stat" : ["Health"], "value" : [points/2] }, False ) ),
                     ( Change_fraction, ChangeFractionRequest( modeldata, { "fraction" : ['B'] }, False ) ) ]

        changeList = env.execActions( requests )

        assert (env.acc.db.fractionChanged == 1)
        assert env.acc.db.fraction == 'B'
        hero, heroId = modeldata.findHeroByCrc32( crc32('inventor') )
        assert heroId != 0
        hero, heroId = modeldata.findHeroByCrc32( crc32('artist') )
        assert heroId == 0

    def change_fraction_antoganist_bad_classId_test( self, env ):
        modeldata = env.acc.model
        assert env.acc.db.fraction == 'A'
        hero = env.add_hero(modeldata, "inventor")
        staticHero = env.acc.SD.getStaticHero(hero)
        tmpAntagonist = staticHero['antagonistId']
        staticHero['antagonistId'] = "jerkface"
        heroesCount = len(modeldata.Heroes)

        requests = [ ( Give_experience, GiveExperienceRequest( modeldata, { "hero_id" : ["" + str(hero.id) + ""], "value" : ["500"] }, False ) ),
                     ( Change_fraction, ChangeFractionRequest( modeldata, { "fraction" : ['B'] }, False ) ) ]

        changeList = env.execActions( requests )

        assert (env.acc.db.fractionChanged == 1)
        assert env.acc.db.fraction == 'B'
        hero, heroId = modeldata.findHeroByCrc32( crc32('inventor') )
        assert heroId != 0
        hero, heroId = modeldata.findHeroByCrc32( crc32('artist') )
        assert heroId == 0
        assert  len(modeldata.Heroes) == heroesCount

        staticHero['antagonistId']  = tmpAntagonist


    def change_fraction_check_valid_antagonist_skin_test( self, env ):
        modeldata = env.acc.model
        assert env.acc.db.fraction == 'A'
        gold = env.I.BILL.getStatusBalance(env.acc.auid)[1]
        env.acc.db.fractionChanged = 0

        self.hero, heroId = modeldata.findHeroByCrc32( crc32("thundergod") )
        assert self.hero
        assert len( self.hero.HeroSkins.Skins ) == 0

        skin_id = modeldata.addNewSkin()
        skin = modeldata.getSkinByID( skin_id )
        skin.PersistentId = crc32("thundergod_S1_A")
        skin.WasBought = True
        self.hero.HeroSkins.Skins.add( skin_id )
        self.hero.HeroSkins.CurrentSkin = skin

        static_skin = env.acc.SD.getStaticSkinByPersistentId( skin.PersistentId )
        config = env.I.Config.getConfig( env.acc.userlocale )

        requests =  [ ( Change_fraction, ChangeFractionRequest( modeldata, { "fraction" : ['B'] }, False ) ),
                      ( Keepalive, KeepaliveRequest( modeldata, { "counter" : [0] }, False ) ) ]
        changeList = env.execActions( requests )

        assert env.acc.db.fraction == 'B'
        assert env.acc.db.fractionChanged == 1
        assert modeldata.Resources.Gold == gold
        assert self.hero.HeroSkins.CurrentSkin.PersistentId == crc32("thundergod_S1_A")

    def change_fraction_and_default_for_skin_test( self, env ):
        modeldata = env.acc.model
        assert env.acc.db.fraction == 'A'
        gold = env.I.BILL.getStatusBalance(env.acc.auid)[1]
        env.acc.db.fractionChanged = 0
        fame = 80000
        silver = 5000000
        modeldata.LordInfo.Fame = fame
        modeldata.Resources.Silver = silver

        requests = [ ( Hire_hero, HireHeroRequest( modeldata, { "PersistentId" : [crc32("prince")] }, False ) ) ]
        changeList = env.execActions( requests )

        self.hero, heroId = modeldata.findHeroByCrc32( crc32("prince") )

        assert self.hero
        #assert len( self.hero.HeroSkins.Skins ) == 2
        #assert self.hero.HeroSkins.CurrentSkin

        #oldFrSkin = self.hero.HeroSkins.CurrentSkin.PersistentId

        requests =  [ ( Change_fraction, ChangeFractionRequest( modeldata, { "fraction" : ['B'] }, False ) ),
                      ( Keepalive, KeepaliveRequest( modeldata, { "counter" : [0] }, False ) ) ]
        changeList = env.execActions( requests )

        assert env.acc.db.fraction == 'B'
        assert env.acc.db.fractionChanged == 1
        #assert len( self.hero.HeroSkins.Skins ) == 2
        #assert self.hero.HeroSkins.CurrentSkin.get()
        #assert self.hero.HeroSkins.CurrentSkin.PersistentId == oldFrSkin

    def change_fraction_give_no_gold_for_event_skin_test( self, env ):
        modeldata = env.acc.model
        assert env.acc.db.fraction == 'A'
        gold = env.I.BILL.getStatusBalance(env.acc.auid)[1]
        env.acc.db.fractionChanged = 0

        self.hero, heroId = modeldata.findHeroByCrc32( crc32("thundergod") )
        assert self.hero
        assert len( self.hero.HeroSkins.Skins ) == 0

        skin_id = modeldata.addNewSkin()
        skin = modeldata.getSkinByID( skin_id )
        skin.PersistentId = crc32("thundergod_S1_A")
        skin.WasBought = False
        self.hero.HeroSkins.Skins.add( skin_id )
        self.hero.HeroSkins.CurrentSkin = skin

        self.hero, heroId = modeldata.findHeroByCrc32( crc32("thundergod") )
        assert self.hero
        assert len( self.hero.HeroSkins.Skins ) == 1

        requests =  [ ( Change_fraction, ChangeFractionRequest( modeldata, { "fraction" : ['B'] }, False ) ),
                      ( Keepalive, KeepaliveRequest( modeldata, { "counter" : [0] }, False ) ) ]
        changeList = env.execActions( requests )

        assert env.acc.db.fraction == 'B'
        assert env.acc.db.fractionChanged == 1
        assert modeldata.Resources.Gold == gold

    def change_fraction_keep_event_skin_test( self, env ):
        modeldata = env.acc.model
        assert env.acc.db.fraction == 'A'
        gold = env.I.BILL.getStatusBalance(env.acc.auid)[1]
        env.acc.db.fractionChanged = 0

        env.add_hero(modeldata, "mage")
        self.hero, heroId = modeldata.findHeroByCrc32( crc32("mage") )
        assert self.hero
        assert len( self.hero.HeroSkins.Skins ) == 0

        skin_id = modeldata.addNewSkin()
        skin = modeldata.getSkinByID( skin_id )
        skin.PersistentId = crc32("mage_S2")
        skin.WasBought = True
        self.hero.HeroSkins.Skins.add( skin_id )
        self.hero.HeroSkins.CurrentSkin = skin

        self.hero, heroId = modeldata.findHeroByCrc32( crc32("mage") )
        assert self.hero
        assert len( self.hero.HeroSkins.Skins ) == 1

        modeldata.EventSkins.append(crc32("mage_S2"))

        requests =  [ ( Change_fraction, ChangeFractionRequest( modeldata, { "fraction" : ['B'] }, False ) ),
                      ( Keepalive, KeepaliveRequest( modeldata, { "counter" : [0] }, False ) ) ]
        changeList = env.execActions( requests )

        assert env.acc.db.fraction == 'B'
        assert env.acc.db.fractionChanged == 1
        assert modeldata.Resources.Gold == gold

        self.hero, heroId = modeldata.findHeroByCrc32( crc32("mage") )
        assert self.hero
        assert len( self.hero.HeroSkins.Skins ) == 1

    def change_fraction_keep_buildings_test( self, env ):
        modeldata = env.acc.model
        modeldata.LordInfo.LevelOfExpansion = 1
        assert env.acc.db.fraction == 'A'
        env.add_construction( modeldata, "Storage", 20)
        buildingsCount = len(modeldata.Buildings)
        pocketCount = len(modeldata.Pocket)


        requests = [ ( Change_fraction, ChangeFractionRequest( modeldata, { "fraction" : ['B'] }, False ) ) ]
        changeList = env.execActions( requests )

        assert buildingsCount == len(modeldata.Buildings)
        assert pocketCount == len(modeldata.Pocket)

    def change_fraction_sell_decoration_test( self, env ):
        modeldata = env.acc.model
        silver = modeldata.Resources.Silver
        modeldata.LordInfo.LevelOfExpansion = 1

        assert env.acc.db.fraction == 'A'
        decor = env.add_construction( modeldata, "Decor_Lattern_1", 20)
        staticConstruction = env.acc.SD.getStaticConstruction( decor )
        oldDecorFraction = staticConstruction['fraction']
        staticConstruction['fraction'] = '1'
        buildingsCount = len(modeldata.Buildings)
        pocketCount = len(modeldata.Pocket)


        requests = [ ( Change_fraction, ChangeFractionRequest( modeldata, { "fraction" : ['B'] }, False ) ) ]
        changeList = env.execActions( requests )

        assert buildingsCount == len(modeldata.Buildings) + 1
        assert pocketCount == len(modeldata.Pocket)
        assert silver < modeldata.Resources.Silver

        staticConstruction['fraction'] = oldDecorFraction

    def change_fraction_keep_building_working_test( self, env ):
        modeldata = env.acc.model
        modeldata.LordInfo.LevelOfExpansion = 1
        assert env.acc.db.fraction == 'A'
        construction = env.add_construction( modeldata, "House_1", 0)
        construction.ProductionState = ProductionState.Busy
        buildingsCount = len(modeldata.Buildings)
        pocketCount = len(modeldata.Pocket)


        requests = [ ( Change_fraction, ChangeFractionRequest( modeldata, { "fraction" : ['B'] }, False ) ) ]
        changeList = env.execActions( requests )

        assert construction.ProductionState == ProductionState.Busy
        assert buildingsCount == len(modeldata.Buildings)
        assert pocketCount == len(modeldata.Pocket)

    def change_fraction_remove_guild_invites_test( self, env ):
        modeldata = env.acc.model
        assert env.acc.db.fraction == 'A'

        inviteId = modeldata.addNewGuildInvite()
        invite = modeldata.getGuildInviteByID( inviteId )
        modeldata.IncomingGuildInvites.add( invite )

        assert len(modeldata.IncomingGuildInvites) == 1

        requests = [ ( Change_fraction, ChangeFractionRequest( modeldata, { "fraction" : ['B'] }, False ) ) ]
        changeList = env.execActions( requests )

        assert len(modeldata.IncomingGuildInvites) == 1
