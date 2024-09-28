# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network
import sys, os, time

os.chdir('..')
sys.path.append( os.path.abspath('.') )
sys.path.append( os.path.abspath('cfg') )
from base.helpers import *


## --------- for sync tests --------------
import handlers

# ---------------------------------
from modeldata.MultiStaticData import MultiStaticData
# ---------------------------------

from base_dummy_test import *
from logic.hire_hero import *
from ipersonserver import *


from party_test_base import PartyTestBase

class PartyTest( PartyTestBase ):
#class PartyTest( ): # -- отключаем весь набор тестов
    """ Этот тест будет создавать локальные копии WS и PS, и завязывать взаимодействие их SubAction-ов напрямую друг на друга 
        (через подмену их интерфейсов I.PS и I.WSX фейками) """

    # -----------------------------------------------------------------------------------------------------------------
    # -----------------------------------------------------------------------------------------------------------------
    # -----------------------------------------------------------------------------------------------------------------

    def test_Invite_Accept_Hero_Go_M1S1_BRIEF(self):
        info("TEST WAS IGNORED BY THE TASK https://devjira.nivalnetwork.com/browse/PF-103776")
        '''logLevel()
        MASTER = 1
        SLAVE = 2
        
        self.createGuestUsers( 2 )

        MASTER = self.accs[MASTER].auid
        SLAVE = self.accs[SLAVE].auid
        
        ##logLevel( logging.DEBUG ) 
        
        # --------------------------
        # отсылаем инвайт
        self.sendInvite(MASTER, SLAVE)
        
        # мастер: получил извещение, что партия создана?
        test, event = self.checkPendingFriendsEvent(MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingEvent(test, MASTER, "create_init", "PartyData", message="created new party during invite", master_auid=MASTER)
        PARTY_ID = event.party_id
        
        # мастер: получил подтверждение, что инвайт отослан?
        self.checkNextPendingEvent(test, MASTER, "invited", message="ok", invite_auid=SLAVE)
        
        # слэйв: получил инвайт?
        test, event = self.checkPendingFriendsEvent(SLAVE, "status_change", "FriendsData", friend_auid=SLAVE)
        test, event = self.checkNextPendingEvent(test, SLAVE, "invite", "from_nick", master_auid=MASTER, party_id=PARTY_ID)
        
        # --------------------------
        # слэйв: принимаем invite
        self.sendAccept(SLAVE, MASTER)
        
        # мастер: получил join?
        test, event = self.checkPendingEvent(MASTER, "friend_status", "PartyData", auid=SLAVE)
        test, event = self.checkNextPendingEvent(test, MASTER, "join", join_auid=SLAVE, party_id=PARTY_ID)

        # слэйв: получил join_init?
        test, event = self.checkPendingEvent(SLAVE, "accept_invite", "FriendsData" )
        self.checkNextPendingEvent(test, SLAVE, "join_init", "PartyData", "master_auid", join_auid=SLAVE, party_id=PARTY_ID )

        info( "------- MASTER HERO KEYS: %s" % self.accs[MASTER].model.HeroesKeeper.keys() )
        
        # --------------------------
        # мастер: выбираем героя (assassin)
        hero_id_1 = self.accs[MASTER].model.HeroesKeeper.keys()[0]
        hero_crc_1 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_1).PersistentId
        hero_id_2 = self.accs[MASTER].model.HeroesKeeper.keys()[1]
        hero_crc_2 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_2).PersistentId
        #~ hero_id_3 = self.accs[MASTER].model.HeroesKeeper.keys()[2]
        #~ hero_crc_3 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_3).PersistentId
        
        self.sendHero( MASTER, PARTY_ID, hero_id=hero_id_1, hero_crc=hero_crc_1 )
        
        # слэйв: выбираем героя (firefox)
        hero_crc = self.accs[SLAVE].model.HeroesKeeper.get(1).PersistentId
        self.sendHero( SLAVE, PARTY_ID, hero_id=hero_id_2, hero_crc=hero_crc_2 )
        
        # мастер: получил 2xhero?
        self.checkPendingEventCount( 2, MASTER, "hero", party_id=PARTY_ID )

        # слэйв: получил 2xhero?
        self.checkPendingEventCount( 2, SLAVE, "hero", party_id=PARTY_ID )
        
        # сменим на карту для ботов
        self.sendMap(MASTER, with_bots = 1)
        # мастер: получил map?
        self.checkPendingEventCount( 1, MASTER, "map", party_id=PARTY_ID )

        # слэйв: получил map?
        self.checkPendingEventCount( 1, SLAVE, "map", party_id=PARTY_ID )        
        
        # --------------------------
        # мастер: GO
        self.sendGo( MASTER, PARTY_ID)
        
        # мастер: получил go?
        test = self.checkPendingGoProgress( 2, MASTER, PARTY_ID )
        
        # слэйв: получил go?
        self.checkPendingGoProgress( 2, SLAVE, PARTY_ID )
        
        ##logLevel( logging.DEBUG ) 

        ## ------------------------------------------------------------------------------
        ## юзер уходит в оффлайн: матчмейкинг должен остановиться
        test = self.sendLogout( SLAVE )
        info("logout reply: %s" % test.reply )
        t0 = time.time()
        while users.get( SLAVE ): 
            self.I.WS.tick()
            # подождем, пока уйдет оффлайн
            time.sleep(0.1)
            self.assert_( time.time() - t0 < 1.5 ) # не ждем больше 1.5 секунд
            
        # мастер: получил оповещение о logout disband?
        test, event = self.checkPendingEvent( MASTER, "progress", party_id=PARTY_ID ) # сначала придет cancel по logout
        self.checkNextPendingEvent( test, MASTER, "disband", "PartyData", party_id=PARTY_ID )
        self.checkNextPendingEvent( test, MASTER, "stop", party_id=PARTY_ID )'''
        
           
    # -----------------------------------------------------------------------------------------------------------------
    # -----------------------------------------------------------------------------------------------------------------
    # -----------------------------------------------------------------------------------------------------------------
    
    def test_Invite_Decline_Status_Expire_M1S1_BRIEF(self):
        logLevel()
        MASTER = 1
        SLAVE = 2
        
        ## logLevel( logging.DEBUG ) 
        
        self.createGuestUsers( 2 )

        ## --------------------------
        ## decline несуществующего invite
        self.sendDecline(SLAVE, MASTER)
        
        # слейв: получил отлуп?
        test, event = self.checkPendingFriendsEvent(SLAVE, "status_change", "FriendsData", friend_auid=SLAVE)
        test, event = self.checkNextPendingEvent(test, SLAVE, "error", failed_cmd="decline", message="bad master_auid specified")
        
        # --------------------------
        # отсылаем инвайт
        self.sendInvite(MASTER, SLAVE)
        
        # мастер: получил извещение, что партия создана?
        test, event = self.checkPendingFriendsEvent(MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingEvent(test, MASTER, "create_init", "PartyData", message="created new party during invite", master_auid=MASTER)
        PARTY_ID = event.party_id
        
        # мастер: получил подтверждение, что инвайт отослан?
        self.checkNextPendingEvent(test, MASTER, "invited", message="ok", invite_auid=SLAVE)
        
        # слэйв: получил инвайт?
        self.checkPendingEvent(SLAVE, "invite", "from_nick", master_auid=MASTER, party_id=PARTY_ID)
        
        #~ # --------------------------
        #~ # получаем status
        #~ self.sendStatus(MASTER)
        
        #~ # MASTER: получил статус?
        #~ self.checkPendingEvent(MASTER, "status", party_id=PARTY_ID)
        
        # --------------------------
        # слэйв: отклоняем invite
        self.sendDecline(SLAVE, MASTER)
        
        # мастер: получил результат decline?
        test, event = self.checkPendingEvent(MASTER, "remove_invite", "PartyData", message="user decline", party_id=PARTY_ID)

        # слэйв: получил результат decline?
        test, event = self.checkPendingFriendEvent(SLAVE, "invite_removed", "FriendsData", message="user decline", party_id=PARTY_ID)
        
        #~ # --------------------------
        #~ # у SLAVE не должно быть партии
        #~ self.sendStatus(SLAVE)
        
        #~ # получил статус?
        #~ self.checkPendingEvent(SLAVE, "status", message="no party", party_id=0)
        
        # --------------------------
        # один раз тикнем PersonServer: партия должна удалиться
        self.iDictPTS.WS.tick()
        
        # мастер: получил смерть партии?
        test, event = self.checkPendingEvent(MASTER, "error", "PartyData", failed_cmd="expire", message="party expired: all invites timed out", party_id=PARTY_ID)
        
        #~ # --------------------------
        #~ # теперь у MASTER не должно быть партии
        #~ self.sendStatus(MASTER)
        
        #~ # MASTER2: получил статус?
        #~ self.checkPendingEvent(MASTER, "status", message="no party", party_id=0)
        

    # -----------------------------------------------------------------------------------------------------------------
    # -----------------------------------------------------------------------------------------------------------------
    # -----------------------------------------------------------------------------------------------------------------
    
        
        
    # -----------------------------------------------------------------------------------------------------------------
    def test_DisbandMaster(self):
        logLevel()
        self.createGuestUsers( 4 )

        MASTER = 1
        SLAVE1 = 2
        SLAVE2 = 3
        SLAVE3 = 4
        
        # рассылаем инвайты
        self.sendInvite(MASTER, SLAVE1)
        
        # мастер: получил извещение, что партия создана?
        test, event = self.checkPendingFriendsEvent(MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingEvent(test, MASTER, "create_init", "PartyData", message="created new party during invite", master_auid=MASTER)
        PARTY_ID = event.party_id
        
        self.sendInvite(MASTER, SLAVE2)
        self.sendInvite(MASTER, SLAVE3)
        
        ## logLevel( logging.DEBUG )
        
        # наприглашал, а сам слился:
        self.sendDisband(MASTER, MASTER)
        
        # слейвы: получили по 2 извещения (инвайт + invite_removed)?
        for index in [SLAVE1, SLAVE2, SLAVE3]:
            test, event = self.checkPendingFriendsEvent(index, "status_change", "FriendsData", friend_auid=index)
            test, event = self.checkNextPendingEvent(test, index, "invite", "FriendsData", master_auid=MASTER)
            self.checkNextPendingFriendEvent(test, index, "invite_removed", "FriendsData", master_auid=MASTER)
            
        # сама партия должна быть совершенно пустая
        party = self.iDictPTS.WS.parties.get( PARTY_ID )
        self.assert_( party ) 
        self.assert_( not party.members ) 
        self.assert_( not party.pending_invites )

        # и на следующем же тике партия должна удалиться
        self.iDictPTS.WS.tick()
        party = self.iDictPTS.WS.parties.get( PARTY_ID )
        self.assert_( party is None ) 

        # а мастер может заново спокойно приглашать всех трех этих юзеров
        self.skipPendingEvents(MASTER)
    
        # инвайты
        self.sendInvite(MASTER, SLAVE1)
        
        # мастер: получил извещение, что партия создана?
        test, event = self.checkPendingEvent(MASTER, "create_init", "PartyData", message="created new party during invite", master_auid=MASTER)
        PARTY_ID = event.party_id

        self.sendInvite(MASTER, SLAVE2)
        self.sendInvite(MASTER, SLAVE3)
        
        # слейвы: получили извещения про новый инвайт?
        for index in [SLAVE1, SLAVE2, SLAVE3]:
            test, event = self.checkPendingEvent(index, "invite", "FriendsData", master_auid=MASTER)



    # -----------------------------------------------------------------------------------------------------------------
    def test_MigrateMaster(self):
        logLevel()
        self.createGuestUsers( 4 )

        MASTER = 1
        SLAVE1 = 2
        SLAVE2 = 3
        SLAVE3 = 4
        
        ## logLevel( logging.DEBUG )
        
        # рассылаем инвайты
        self.sendInvite(MASTER, SLAVE1)
        
        # мастер: получил извещение, что партия создана?
        test, event = self.checkPendingFriendsEvent(MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingEvent(test, MASTER, "create_init", "PartyData", message="created new party during invite", master_auid=MASTER)
        PARTY_ID = event.party_id
        
        self.sendInvite(MASTER, SLAVE2)
        self.sendInvite(MASTER, SLAVE3)

        # двое принимают, третий нет
        self.sendAccept(SLAVE1, MASTER )
        self.sendAccept(SLAVE2, MASTER )
        
        # пропускаем все сообщения
        for index in [MASTER, SLAVE1, SLAVE2, SLAVE3]:
            self.skipPendingEvents(index)

        # сейчас в партии должно быть 3 мембера и 1 инвайт
        party = self.iDictPTS.WS.parties.get( PARTY_ID )
        self.assert_( party ) 
        self.assert_( len(party.members) == 3 ) 
        self.assert_( len(party.pending_invites) == 1 )
        self.assert_( party.getMaster() == MASTER )

        ## logLevel( logging.DEBUG )
        
        # мастер сваливает:
        self.sendDisband(MASTER, MASTER)
        
        # слейвы: получили извещения? (disband + смена мастера)?
        for index in [SLAVE1, SLAVE2]:
            test, event = self.checkPendingEvent(index, "disband", "PartyData", master_auid=SLAVE1)
            
        # теперь мастером партии должен быть SLAVE1, и в ней должно быть 2 мембера и 1 инвайт
        party = self.iDictPTS.WS.parties.get( PARTY_ID )
        self.assert_( len(party.members) == 2 ) 
        self.assert_( len(party.pending_invites) == 1 )
        self.assert_( party.getMaster() == SLAVE1 )
        
        # а вот accept от SLAVE3 теперь не должен проходить (приглашал-то его еще старый мастер)
        self.sendAccept(SLAVE1, MASTER)
        self.checkPendingEvent(SLAVE1, "error", failed_cmd="accept")
        
        # зато если его пригласит новый мастер, то invite + accept должны пройти нормально
        self.sendInvite(SLAVE1, SLAVE3)
        self.checkPendingEvent( SLAVE3, "invite", "FriendsData" )

        self.sendAccept(SLAVE3, SLAVE1)
        test, event = self.checkPendingEvent(SLAVE3, "accept_invite", "FriendsData" )
        self.checkNextPendingEvent(test, SLAVE3, "join_init", "PartyData", "master_auid", join_auid=SLAVE3, party_id=PARTY_ID )
        
        
        

# ---------------------------------------------------------------------------------------------------------------------
    def test_Disband_BRIEF(self):
        logLevel()
        self.createGuestUsers( 4 )

        MASTER = 1
        SLAVE1 = 2
        SLAVE2 = 3
        SLAVE3 = 4
        
        # рассылаем инвайты
        self.sendInvite(MASTER, SLAVE1)
        
        # мастер: получил извещение, что партия создана?
        test, event = self.checkPendingFriendsEvent(MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingEvent(test, MASTER, "create_init", "PartyData", message="created new party during invite", master_auid=MASTER)
        PARTY_ID = event.party_id
        
        self.sendInvite(MASTER, SLAVE2)
        self.sendInvite(MASTER, SLAVE3)
        
        # 1,2 принимают
        self.sendAccept(SLAVE1, MASTER)
        self.sendAccept(SLAVE2, MASTER)
        
        # пропускаем все ответы
        self.skipPendingEvents(MASTER)
        self.skipPendingEvents(SLAVE1)
        self.skipPendingEvents(SLAVE2)
        self.skipPendingEvents(SLAVE3)
        
        ## logLevel( logging.DEBUG ) 
        
        # убеждаемся, что партия есть, в ней д.б. трое members и один инвайт
        party = self.iDictPTS.WS.parties.get(PARTY_ID)
        self.assert_( party and party.party_id == PARTY_ID )
        info( "party members: %s, pending_invites: %s" % (str(party.members), str(party.pending_invites.keys())) )
        self.assert_( len(party.members)==3 and len(party.pending_invites)==1 and party.getMaster()==MASTER )
        
        self.sendDecline(SLAVE3, MASTER)
        ## все должны получить remove_invite (а сам юзер -- invite_removed)
        self.checkPendingFriendEvent(SLAVE3, "invite_removed", "FriendsData", message="user decline", party_id=PARTY_ID)
        for index in [MASTER, SLAVE1, SLAVE2]:
            self.checkPendingEvent(index, "remove_invite", "PartyData", party_id=PARTY_ID)
        
        self.sendDisband(SLAVE1, MASTER)
        ## все должны получить disband (а сам юзер -- party_uid=0)
        
        self.checkPendingEvent(SLAVE1, "disbanded", "PartyData", party_id=PARTY_ID)
        self.checkPendingEvent(MASTER, "disband", "PartyData", party_id=PARTY_ID)
        self.checkPendingEvent(SLAVE2, "disband", "PartyData", party_id=PARTY_ID)
        
        self.sendDisband(SLAVE2, MASTER)
        
        ## тикаем PersonServer, пока не протухнет инвайт: партия должна развалиться
        self.iDictPTS.WS.tick()

        test, event = self.checkPendingEvent(SLAVE2, "disbanded", "PartyData", party_id=PARTY_ID)
        
        test, event = self.checkPendingEvent(MASTER, "disband", "PartyData", party_id=PARTY_ID)
        self.checkNextPendingEvent(test, MASTER, "error", "PartyData", failed_cmd="expire", message="party expired: all invites timed out", party_id=PARTY_ID)
        
    # -----------------------------------------------------------------------------------------------------------------

    def test_Kick_BRIEF(self):
        logLevel()
        self.createGuestUsers( 4 )

        MASTER = 1
        SLAVE1 = 2
        SLAVE2 = 3
        SLAVE3 = 4
        
        ## logLevel( logging.DEBUG ) 
        
        # рассылаем инвайты
        self.sendInvite(MASTER, SLAVE1)
        
        # мастер: получил извещение, что партия создана?
        test, event = self.checkPendingFriendsEvent(MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingEvent(test, MASTER, "create_init", "PartyData", message="created new party during invite", master_auid=MASTER)
        PARTY_ID = event.party_id
        
        self.sendInvite(MASTER, SLAVE2)
        self.sendInvite(MASTER, SLAVE3)
        
        # 1,2 принимают
        self.sendAccept(SLAVE1, MASTER)
        self.sendAccept(SLAVE2, MASTER)
        
        # пропускаем все ответы
        self.skipPendingEvents(MASTER)
        self.skipPendingEvents(SLAVE1)
        self.skipPendingEvents(SLAVE2)
        self.skipPendingEvents(SLAVE3)
        
        ## logLevel( logging.DEBUG ) 
        
        # убеждаемся, что партия есть, в ней д.б. трое members и один инвайт
        party = self.iDictPTS.WS.parties.get(PARTY_ID)
        self.assert_( party and party.party_id == PARTY_ID )
        info( "party members: %s, pending_invites: %s" % (str(party.members), str(party.pending_invites.keys())) )
        self.assert_( len(party.members)==3 and len(party.pending_invites)==1 and party.getMaster()==MASTER )

        # пинаем приглашенного
        self.sendKick(MASTER, SLAVE3)
        ## все должны получить remove_invite (а сам юзер -- invite_removed)
        self.checkPendingFriendEvent(SLAVE3, "invite_removed", "FriendsData", message="kicked", party_id=PARTY_ID)
        for index in [MASTER, SLAVE1, SLAVE2]:
            self.checkPendingEvent(index, "remove_invite", "PartyData", message="kicked", party_id=PARTY_ID)
        
        ## попробуем пнуть себя: д.б. fail
        self.sendKick(MASTER, MASTER)
        self.checkPendingEvent(MASTER, "error", message="cant kick self", party_id=PARTY_ID)
        
        ## попробуем пнуть слейвом мастера: д.б. fail
        self.sendKick(SLAVE1, MASTER)
        self.checkPendingEvent(SLAVE1, "error", party_id=PARTY_ID)
        
        # пинаем остальных
        self.sendKick(MASTER, SLAVE1)
        ## все должны получить disband (а сам юзер -- party_uid=0)
        
        self.checkPendingEvent(SLAVE1, "disbanded", "PartyData", party_id=PARTY_ID)
        self.checkPendingEvent(MASTER, "disband", "PartyData", party_id=PARTY_ID)
        self.checkPendingEvent(SLAVE2, "disband", "PartyData", party_id=PARTY_ID)
        
        self.sendKick(MASTER, SLAVE2)
        
        ## тикаем PersonServer, пока не протухнет инвайт: партия должна развалиться
        self.iDictPTS.WS.tick()

        test, event = self.checkPendingEvent(SLAVE2, "disbanded", "PartyData", party_id=PARTY_ID)
        
        test, event = self.checkPendingEvent(MASTER, "disband", "PartyData", party_id=PARTY_ID)
        self.checkNextPendingEvent(test, MASTER, "error", "PartyData", failed_cmd="expire", message="party expired: all invites timed out", party_id=PARTY_ID)
        

    # -----------------------------------------------------------------------------------------------------------------
    # -----------------------------------------------------------------------------------------------------------------

    def test_BadPartyMM(self):
        logLevel()

        self.createGuestUsers( 5 )

        MASTER = 1
        SLAVE1 = 2
        SLAVE2 = 3
        SLAVE3 = 4
        
        MASTER2 = 5     
        
        ## logLevel( logging.DEBUG ) 
        
        # шлем инвайт 
        self.sendInvite(MASTER, SLAVE1)
        self.sendAccept(SLAVE1, MASTER)
        
        # пропускаем все ответы
        self.skipPendingEvents(MASTER)
        self.skipPendingEvents(SLAVE1)
        
        # у обоих должен появиться party_id != 0
        PARTY_ID = self.accs[MASTER].party_id
        self.assert_( PARTY_ID )
        self.assertEqual( PARTY_ID, self.accs[SLAVE1].party_id )
        
        # пробуем сделать mm_add (должно обломаться)
        self.checkSoloMM_FAIL(MASTER)
        self.checkSoloMM_FAIL(SLAVE1)
        
        # у постороннего юзера матчмейкинг должен стартовать нормально
        self.checkSoloMM_START(SLAVE2)
        self.assert_( not self.accs[SLAVE2].party_id )
        
        # но должен обломаться party invite:
        self.sendInvite(MASTER, SLAVE2)
        # мастер: получил отлуп?
        test, event = self.checkPendingEvent(MASTER, "error", failed_cmd="invite", invite_auid=SLAVE2)
        
        # кикаем члена партии, сами выходим по expire:
        self.sendKick( MASTER, SLAVE1 )
        self.iDictPTS.WS.tick()
        
        # пропускаем все ответы
        self.skipPendingEvents(MASTER)
        self.skipPendingEvents(SLAVE1)
        
        # теперь должен быть !party_id и соло MM стартует нормально
        self.checkSoloMM_START(MASTER)
        self.assert_( not self.accs[MASTER].party_id )
        self.checkSoloMM_START(SLAVE1)
        self.assert_( not self.accs[SLAVE1].party_id )
        
        #~ ## -----------------------------------
        #~ ## приглашаем мастера временной партии
        
        #~ # отсылаем инвайт
        #~ self.sendInvite(MASTER, MASTER2)
        
        #~ # мастер: получил подтверждение, что инвайт отослан? (членам партии тоже придут дубликаты invited)
        #~ for index in [MASTER, SLAVE2, SLAVE3]:
            #~ self.checkPendingEvent(index, "invited", message="ok", invite_auid=MASTER2, party_id=PARTY_ID)
        
        #~ # слэйв: получил инвайт?
        #~ self.checkPendingEvent(MASTER2, "invite", "from_nick", master_auid=MASTER, party_id=PARTY_ID)
        
        #~ # с другой стороны, у MASTER2 все еще должна быть своя собственная временная партия
        #~ self.sendStatus(MASTER2)
        
        #~ # слэйв: получил статус?
        #~ self.checkPendingEvent(MASTER2, "status", party_id=TEMP_PARTY_ID2)
        
        #~ # --------------------------
        #~ # MASTER2: теперь принимаем invite
        #~ self.sendAccept(MASTER2, MASTER)
        
        #~ # все получили join?
        #~ for index in [MASTER, SLAVE2, SLAVE3]:
            #~ self.checkPendingEvent(index, "join", join_auid=MASTER2, party_id=PARTY_ID)

        #~ self.skipPendingEvents(MASTER2) ################# MASTER2 должны прийти несколько евентов про развал временной партии, пока просто проигнорируем их
        
        #~ # теперь у MASTER2 должна быть новая партия
        #~ self.sendStatus(MASTER2)
        
        #~ # MASTER2: получил статус?
        #~ self.checkPendingEvent(MASTER2, "status", party_id=PARTY_ID)
        
    def test_BadPartyMMBecauseOfMaintenance(self):
        logLevel()

        self.createGuestUsers( 5 )

        MASTER = 1
        SLAVE1 = 2
        SLAVE2 = 3
        SLAVE3 = 4
        
        MASTER2 = 5     
        
        ## logLevel( logging.DEBUG ) 
        
        # шлем инвайт 
        self.sendInvite(MASTER, SLAVE1)
        self.sendAccept(SLAVE1, MASTER)
        
        # пропускаем все ответы
        self.skipPendingEvents(MASTER)
        self.skipPendingEvents(SLAVE1)
        
        # у обоих должен появиться party_id != 0
        PARTY_ID = self.accs[MASTER].party_id
        self.assert_( PARTY_ID )
        self.assertEqual( PARTY_ID, self.accs[SLAVE1].party_id )
        
        self.I.WS.toggleMaintenance(handlers.MAINTENANCE_ONGOING, int(time.time()+100))

        # пробуем сделать mm_add (должно обломаться)
        self.checkSoloMM_FAIL(MASTER)
        self.checkSoloMM_FAIL(SLAVE1)
        
        # у постороннего юзера матчмейкинг должен стартовать нормально
        self.checkSoloMM_FAIL(SLAVE2)
        self.assert_( not self.accs[SLAVE2].party_id )
        
    def test_PartyGoAndMaintenance(self):
        logLevel()

        self.createGuestUsers( 2 )

        self.I.WS.toggleMaintenance(handlers.MAINTENANCE_ONGOING, int(time.time()+100))

        MASTER = 1
        SLAVE1 = 2
        
        # шлем инвайты
        self.sendInvite(MASTER, SLAVE1)
        self.sendAccept(SLAVE1, MASTER)
        
        self.buyHero(SLAVE1, "rockman")
        
        # пропускаем все ответы
        self.skipPendingEvents(MASTER)
        self.skipPendingEvents(SLAVE1)
        
        # у MASTER и SLAVE1 должен появиться party_id != 0
        PARTY_ID = self.accs[MASTER].party_id
        self.assert_( PARTY_ID )
        self.assertEqual( PARTY_ID, self.accs[SLAVE1].party_id )
        

        # --------------------------
        # MASTER и SLAVE1: выбираем героя (assassin)
        
        # похимичим с рейтингом/force одного из героев, чтобы person_server выдал предупреждения
        hero_id_1 = sorted(self.accs[MASTER].model.HeroesKeeper.keys())[0]
        hero_crc_1 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_1).PersistentId
        
        hero_id_2 = sorted(self.accs[SLAVE1].model.HeroesKeeper.keys())[1]
        hero_crc_2 = self.accs[SLAVE1].model.HeroesKeeper.get(hero_id_2).PersistentId
        
        self.sendHero( MASTER, PARTY_ID, hero_id=hero_id_1, hero_crc=hero_crc_1 )
        self.sendHero( SLAVE1, PARTY_ID, hero_id=hero_id_2, hero_crc=hero_crc_2 )
        
        # пропускаем все ответы 
        self.skipPendingEvents(MASTER)
        self.skipPendingEvents(SLAVE1)
        
        # мастер: GO
        self.sendGo( MASTER, PARTY_ID, False )
                
    # -----------------------------------------------------------------------------------------------------------------
    # -----------------------------------------------------------------------------------------------------------------
    def test_NoInvitesAfterPartyGo(self):
        logLevel()

        self.createGuestUsers( 3 )

        MASTER = 1
        SLAVE1 = 2
        SLAVE2 = 3
        
        # шлем инвайты
        self.sendInvite(MASTER, SLAVE1)
        self.sendInvite(MASTER, SLAVE2)
        self.sendAccept(SLAVE1, MASTER)
        
        self.buyHero(SLAVE2, "rockman")
        
        # пропускаем все ответы
        self.skipPendingEvents(MASTER)
        self.skipPendingEvents(SLAVE1)
        self.skipPendingEvents(SLAVE2)
        
        # у MASTER и SLAVE1 должен появиться party_id != 0
        PARTY_ID = self.accs[MASTER].party_id
        self.assert_( PARTY_ID )
        self.assertEqual( PARTY_ID, self.accs[SLAVE1].party_id )
        
        # --------------------------
        # MASTER и SLAVE1: выбираем героя (assassin)
        
        # похимичим с рейтингом/force одного из героев, чтобы person_server выдал предупреждения
        hero_id_1 = sorted(self.accs[MASTER].model.HeroesKeeper.keys())[0]
        hero_1 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_1)
        hero_crc_1 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_1).PersistentId
        hero_id_2 = sorted(self.accs[MASTER].model.HeroesKeeper.keys())[1]
        hero_2 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_2)
        hero_crc_2 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_2).PersistentId
        
        hero_id_3 = sorted(self.accs[SLAVE2].model.HeroesKeeper.keys())[2]
        hero_crc_3 = self.accs[SLAVE2].model.HeroesKeeper.get(hero_id_3).PersistentId
        
        hero_1.Rating = 1800
        hero_2.Rating = 1800
        
        self.sendHero( MASTER, PARTY_ID, hero_id=hero_id_1, hero_crc=hero_crc_1 )
        self.sendHero( SLAVE1, PARTY_ID, hero_id=hero_id_2, hero_crc=hero_crc_2 )
        
        # пропускаем все ответы 
        self.skipPendingEvents(MASTER)
        self.skipPendingEvents(SLAVE1)
        self.skipPendingEvents(SLAVE2)
        
        ## logLevel( logging.INFO ) 
        
        # мастер: GO
        self.skipPendingEvents(MASTER)
        self.sendGo( MASTER, PARTY_ID )
        
        # мастер: не смог стартонуть?
        self.checkPendingEvent( MASTER, "error", failed_cmd="go", message="not all party members ready for pvp", party_id=PARTY_ID )
      
        self.sendAccept(SLAVE2, MASTER)
        self.sendHero( SLAVE2, PARTY_ID, hero_id=hero_id_3, hero_crc=hero_crc_3 )
        self.skipPendingEvents(SLAVE1)
        self.skipPendingEvents(SLAVE2)
        self.skipPendingEvents(MASTER)

        self.sendGo( MASTER, PARTY_ID )

        self.checkPendingGoProgress( 3, MASTER, PARTY_ID )
        
        # приглашаем еще раз SLAVE2 (при идущем ММ!)
        self.sendInvite(MASTER, SLAVE2)
        # должен быть отлуп, про "низя во время ММ"
        self.checkPendingEvent( MASTER, "error", failed_cmd="invite", message="user in game" )
        
        logLevel()
        
    def test_TooBigParty(self):
        logLevel()

        self.createGuestUsers( 5 )

        MASTER = 1
        SLAVE1 = 2
        SLAVE2 = 3
        SLAVE3 = 4
        SLAVE4 = 5
        
        # шлем инвайты
        self.sendInvite(MASTER, SLAVE1)
        self.sendInvite(MASTER, SLAVE2)
        self.sendInvite(MASTER, SLAVE3)
        self.sendInvite(MASTER, SLAVE4)
        self.sendAccept(SLAVE1, MASTER)
        self.sendAccept(SLAVE2, MASTER)
        self.sendAccept(SLAVE3, MASTER)
        self.sendAccept(SLAVE4, MASTER)
        
        self.buyHero(SLAVE2, "rockman")
        self.buyHero(SLAVE3, "rockman")
        self.buyHero(SLAVE4, "rockman")
        
        # пропускаем все ответы
        self.skipPendingEvents(MASTER)
        self.skipPendingEvents(SLAVE1)
        self.skipPendingEvents(SLAVE2)
        self.skipPendingEvents(SLAVE3)
        self.skipPendingEvents(SLAVE4)
        
        # у всех должен появиться party_id != 0
        PARTY_ID = self.accs[MASTER].party_id
        self.assert_( PARTY_ID )
        self.assertEqual( PARTY_ID, self.accs[SLAVE1].party_id )
        self.assertEqual( PARTY_ID, self.accs[SLAVE2].party_id )
        self.assertEqual( PARTY_ID, self.accs[SLAVE3].party_id )
        self.assertEqual( PARTY_ID, self.accs[SLAVE4].party_id )
        
        # --------------------------
        # слэйв: выбираем героя (assassin)

        hero_id_1 = self.accs[MASTER].model.HeroesKeeper.keys()[0]
        hero_crc_1 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_1).PersistentId
        hero_id_2 = self.accs[MASTER].model.HeroesKeeper.keys()[1]
        hero_crc_2 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_2).PersistentId
        hero_id_3 = sorted(self.accs[SLAVE2].model.HeroesKeeper.keys())[2]
        hero_crc_3 = self.accs[SLAVE2].model.HeroesKeeper.get(hero_id_3).PersistentId
        
        self.sendHero( MASTER, PARTY_ID, hero_id=hero_id_1, hero_crc=hero_crc_1 )
        self.sendHero( SLAVE1, PARTY_ID, hero_id=hero_id_2, hero_crc=hero_crc_2 )
        self.sendHero( SLAVE2, PARTY_ID, hero_id=hero_id_3, hero_crc=hero_crc_3 )
        self.sendHero( SLAVE3, PARTY_ID, hero_id=hero_id_3, hero_crc=hero_crc_3 )
        self.sendHero( SLAVE4, PARTY_ID, hero_id=hero_id_3, hero_crc=hero_crc_3 )
        
        # пропускаем все ответы 
        self.skipPendingEvents(MASTER)
        self.skipPendingEvents(SLAVE1)
        self.skipPendingEvents(SLAVE2)
        self.skipPendingEvents(SLAVE3)
        self.skipPendingEvents(SLAVE4)
        
        ##logLevel( logging.INFO ) 
        
        # сменим на карту 
        self.sendMap(MASTER, game_type="/Maps/Multiplayer/MOBA/Test_PVP_3x3.ADMPDSCR")
        self.checkPendingEvent( MASTER, "map", party_id=PARTY_ID )
        # мастер: GO
        self.sendGo( MASTER, PARTY_ID )
        
        # должен быть отлуп, про "слишком много игроков в пати"
        self.checkPendingEvent( MASTER, "error", failed_cmd="go", message="party size exceeds map limits" )
        
        # пинаем приглашенного
        self.sendKick(MASTER, SLAVE4)
        self.sendKick(MASTER, SLAVE3)
        
        # пропускаем все ответы 
        self.skipPendingEvents(MASTER)
        self.skipPendingEvents(SLAVE1)
        self.skipPendingEvents(SLAVE2)
        self.skipPendingEvents(SLAVE3)
        self.skipPendingEvents(SLAVE4)
        
        # мастер: GO
        self.sendGo( MASTER, PARTY_ID )
        
        self.checkPendingGoProgress( 3, MASTER, PARTY_ID )
        
        logLevel() 
        
    def test_NoPendingEventsForNewMamber(self):
        logLevel()

        self.createGuestUsers( 4 )

        MASTER = 1
        SLAVE1 = 2
        SLAVE2 = 3
        SLAVE3 = 4
        
        # шлем инвайты
        self.sendInvite(MASTER, SLAVE1)
        self.sendInvite(MASTER, SLAVE2)
        self.sendAccept(SLAVE1, MASTER)
        self.sendAccept(SLAVE2, MASTER)
        
        self.buyHero(SLAVE2, "rockman")
        
        # пропускаем все ответы
        self.skipPendingEvents(MASTER)
        self.skipPendingEvents(SLAVE1)
        self.skipPendingEvents(SLAVE2)
        
        # у обоих должен появиться party_id != 0
        PARTY_ID = self.accs[MASTER].party_id
        self.assert_( PARTY_ID )
        self.assertEqual( PARTY_ID, self.accs[SLAVE1].party_id )
        self.assertEqual( PARTY_ID, self.accs[SLAVE2].party_id )
        
        hero_id_1 = self.accs[MASTER].model.HeroesKeeper.keys()[0]
        hero_crc_1 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_1).PersistentId
        hero_id_2 = self.accs[MASTER].model.HeroesKeeper.keys()[1]
        hero_crc_2 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_2).PersistentId
        hero_id_3 = sorted(self.accs[SLAVE2].model.HeroesKeeper.keys())[2]
        hero_crc_3 = self.accs[SLAVE2].model.HeroesKeeper.get(hero_id_3).PersistentId
        
        # --------------------------
        # слэйв: выбираем героя (assassin)
        self.sendHero( MASTER, PARTY_ID, hero_id=hero_id_1, hero_crc=hero_crc_1 )
        self.sendHero( SLAVE1, PARTY_ID, hero_id=hero_id_2, hero_crc=hero_crc_2 )
        
        # пропускаем все ответы 
        self.skipPendingEvents(MASTER)
        self.skipPendingEvents(SLAVE1)
        self.skipPendingEvents(SLAVE2)
        
        ##logLevel( logging.INFO ) 
        
        # слэйв: выбираем того же героя; должна быть ругань, со списком "слишком много одинаковых героев"
        self.sendHero( SLAVE2, PARTY_ID, hero_id=hero_id_2, hero_crc=hero_crc_2 )
        self.checkPendingEvent( SLAVE2, "hero", party_id=PARTY_ID  )
        
        # мастер: GO
        self.skipPendingEvents(MASTER)
        self.sendGo( MASTER, PARTY_ID )
        
        # должен быть отлуп, про "слишком много одинаковых героев"
        self.checkPendingEvent( MASTER, "error", failed_cmd="go", message="too many similar heroes chosen", party_id=PARTY_ID, same_heroes_auids=[2,3] )

        # слэйв: выбираем другого героя; не должно быть ругани (нет списка "одинаковых героев")
        self.sendHero( SLAVE2, PARTY_ID, hero_id=hero_id_3, hero_crc=hero_crc_3 )
        self.checkPendingEvent( SLAVE2, "hero", party_id=PARTY_ID )
        
        #добавляем еще одного комрада
        self.sendInvite(MASTER, SLAVE3)
        self.sendAccept(SLAVE3, MASTER)
        #self.checkPendingEvent( SLAVE3, "error", failed_cmd="go", message="too many similar heroes chosen", party_id=PARTY_ID, same_heroes_auids=[2,3] )
        
        logLevel() 
        

    def test_Bad_Go_M1S1_BRIEF(self):
        logLevel()
        MASTER = 1
        SLAVE = 2
        
        self.createGuestUsers( 2 )

        MASTER = self.accs[MASTER].auid
        SLAVE = self.accs[SLAVE].auid
        
        # --------------------------
        # отсылаем инвайт
        self.sendInvite(MASTER, SLAVE)
        
        # мастер: получил извещение, что партия создана?
        test, event = self.checkPendingFriendsEvent(MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingEvent(test, MASTER, "create_init", "PartyData", message="created new party during invite", master_auid=MASTER)
        PARTY_ID = event.party_id
        
        # мастер: получил подтверждение, что инвайт отослан?
        self.checkNextPendingEvent(test, MASTER, "invited", message="ok", invite_auid=SLAVE)
        
        # слэйв: получил инвайт?
        test, event = self.checkPendingFriendsEvent(SLAVE, "status_change", "FriendsData", friend_auid=SLAVE)
        test, event = self.checkNextPendingEvent(test, SLAVE, "invite", "from_nick", master_auid=MASTER, party_id=PARTY_ID)
        
        # --------------------------
        # слэйв: принимаем invite
        self.sendAccept(SLAVE, MASTER)
        
        # мастер: получил join?
        test, event = self.checkPendingEvent(MASTER, "friend_status", "PartyData", auid=SLAVE)
        test, event = self.checkNextPendingEvent(test, MASTER, "join", join_auid=SLAVE, party_id=PARTY_ID)

        # слэйв: получил join_init?
        test, event = self.checkPendingEvent(SLAVE, "accept_invite", "FriendsData" )
        self.checkNextPendingEvent(test, SLAVE, "join_init", "PartyData", "master_auid", join_auid=SLAVE, party_id=PARTY_ID )

        #~logLevel( logging.DEBUG )
        #info( "------- MASTER HERO KEYS: %s" % self.accs[MASTER].model.HeroesKeeper.keys() )
        #info( "------- MASTER HERO[1]: %s" % self.accs[MASTER].model.HeroesKeeper.get(1).__dict__ )
        
        # --------------------------
        # мастер: выбираем героя 
        hero_id_1 = self.accs[MASTER].model.HeroesKeeper.keys()[0]
        hero_crc_1 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_1).PersistentId
        hero_id_2 = self.accs[MASTER].model.HeroesKeeper.keys()[1]
        hero_crc_2 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_2).PersistentId
        #~ hero_id_3 = self.accs[SLAVE2].model.HeroesKeeper.keys()[2]
        #~ hero_crc_3 = self.accs[SLAVE2].model.HeroesKeeper.get(hero_id_3).PersistentId
        
        self.sendHero( MASTER, PARTY_ID, hero_id=hero_id_1, hero_crc=hero_crc_1 )
        
        # мастер: получил hero?
        self.checkPendingEvent( MASTER, "hero", party_id=PARTY_ID )
        # слэйв: получил hero?
        self.checkPendingEvent( SLAVE, "hero", party_id=PARTY_ID )

        ## ----------------------------------------------------
        ## пробуем party_go: д.б. отлуп, не все юзеры выбрали героев
        # мастер: GO
        self.sendGo( MASTER, PARTY_ID )
        
        # мастер: получил отлуп?
        self.checkPendingEvent( MASTER, "error", failed_cmd="go", message="not all party members chosen heroes for pvp", party_id=PARTY_ID )
        
        ##logLevel( logging.DEBUG )
        
        # --------------------------
        # слэйв: выбираем героя (assassin)
        hero_crc = self.accs[SLAVE].model.HeroesKeeper.get(1).PersistentId
        self.sendHero( SLAVE, PARTY_ID, hero_id=hero_id_2, hero_crc=hero_crc_2 )
        
        # мастер: получил hero?
        self.checkPendingEvent( MASTER, "hero", party_id=PARTY_ID )
        # слэйв: получил hero?
        self.checkPendingEvent( SLAVE, "hero", party_id=PARTY_ID )

        # мастер: GO
        self.sendGo( MASTER, PARTY_ID )

        # мастер: получил go?
        self.checkPendingGoProgress( 2, MASTER, PARTY_ID )
        
        # слэйв: получил go?
        self.checkPendingGoProgress( 2, SLAVE, PARTY_ID )
        
        ## ----------------------------------------------------
        ## пробуем party_go: д.б. отлуп, партия уже в матчмейкинге
        # мастер: GO
        self.sendGo( MASTER, PARTY_ID )
        
        # мастер: получил отлуп?
        self.checkPendingEvent( MASTER, "error", failed_cmd="go", message="not all party members ready for pvp", party_id=PARTY_ID )
        
        ## ----------------------------------------------------
        ## теперь делаем kick: партия должна сразу выпасть из матчмейкинга
        self.sendKick( MASTER, SLAVE)
        
        # мастер: получил оповещение о kick?
        test, event = self.checkPendingEvent( MASTER, "disband", "PartyData", party_id=PARTY_ID )
        self.checkNextPendingEvent( test, MASTER, "stop", party_id=PARTY_ID )
        
        test, event = self.checkPendingEvent( SLAVE, "disbanded", "PartyData", party_id=PARTY_ID )
        self.checkNextPendingEvent( test, SLAVE, "stop", party_id=PARTY_ID )
        
    
    def __test_SimilarHeroes(self):
        logLevel()

        self.createGuestUsers( 3 )

        MASTER = 1
        SLAVE1 = 2
        SLAVE2 = 3
        
        # шлем инвайты
        ##logLevel( logging.INFO ) # ###################
        
        self.sendInvite(MASTER, SLAVE1)
        self.sendInvite(MASTER, SLAVE2)
        self.sendAccept(SLAVE1, MASTER)
        self.sendAccept(SLAVE2, MASTER)
        
        self.buyHero(SLAVE2, "rockman")
        
        # пропускаем все ответы
        self.skipPendingEvents(MASTER)
        self.skipPendingEvents(SLAVE1)
        self.skipPendingEvents(SLAVE2)
        
        # у обоих должен появиться party_id != 0
        PARTY_ID = self.accs[MASTER].party_id
        self.assert_( PARTY_ID )
        self.assertEqual( PARTY_ID, self.accs[SLAVE1].party_id )
        self.assertEqual( PARTY_ID, self.accs[SLAVE2].party_id )
        
        hero_id_1 = sorted(self.accs[MASTER].model.HeroesKeeper.keys())[0]
        hero_crc_1 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_1).PersistentId
        hero_id_2 = sorted(self.accs[MASTER].model.HeroesKeeper.keys())[1]
        hero_crc_2 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_2).PersistentId
        hero_id_3 = sorted(self.accs[SLAVE2].model.HeroesKeeper.keys())[2]
        hero_crc_3 = self.accs[SLAVE2].model.HeroesKeeper.get(hero_id_3).PersistentId
        
        # --------------------------
        # слэйв: выбираем героя (assassin)
        self.sendHero( MASTER, PARTY_ID, hero_id=hero_id_1, hero_crc=hero_crc_1 )
        self.sendHero( SLAVE1, PARTY_ID, hero_id=hero_id_2, hero_crc=hero_crc_2 )
        
        # пропускаем все ответы 
        self.skipPendingEvents(MASTER)
        self.skipPendingEvents(SLAVE1)
        self.skipPendingEvents(SLAVE2)
        
        ##logLevel( logging.INFO ) 
        
        # слэйв: выбираем того же героя; должна быть ругань, со списком "слишком много одинаковых героев"
        self.sendHero( SLAVE2, PARTY_ID, hero_id=hero_id_2, hero_crc=hero_crc_2 )
        
        ## -- больше нет same_heroes_auids, на одинаковых героев ругаемся на party_go
        self.checkPendingEvent( SLAVE2, "hero", party_id=PARTY_ID )  
        
        # мастер: GO
        self.skipPendingEvents(MASTER)
        self.sendGo( MASTER, PARTY_ID )
        
        # должен быть отлуп, про "слишком много одинаковых героев"
        self.checkPendingEvent( MASTER, "error", failed_cmd="go", message="too many similar heroes chosen", party_id=PARTY_ID, same_heroes_auids=[2,3] )

        # слэйв: выбираем другого героя; не должно быть ругани (нет списка "одинаковых героев")
        self.sendHero( SLAVE2, PARTY_ID, hero_id=hero_id_3, hero_crc=hero_crc_3 )
        ## -- больше нет same_heroes_auids, на одинаковых героев ругаемся на party_go
        self.checkPendingEvent( SLAVE2, "hero", party_id=PARTY_ID )
        
        # мастер: GO
        self.skipPendingEvents(MASTER)
        self.sendGo( MASTER, PARTY_ID )
        
        # мастер: получил подтвержение на go?
        self.checkPendingGoProgress( 3, MASTER, PARTY_ID )
        
        logLevel() 

    def test_PartyPersonUpdate(self):
        logLevel()

        self.createGuestUsers( 2 )

        MASTER = 1
        SLAVE1 = 2
        
        # шлем инвайты
        self.sendInvite(MASTER, SLAVE1)
        self.sendAccept(SLAVE1, MASTER)
        
        # пропускаем все ответы
        self.skipPendingEvents(MASTER)
        self.skipPendingEvents(SLAVE1)
        
        # у обоих должен появиться party_id != 0
        PARTY_ID = self.accs[MASTER].party_id
        self.assert_( PARTY_ID )
        self.assertEqual( PARTY_ID, self.accs[SLAVE1].party_id )
        
        ## logLevel(logging.INFO)
        
        # сообщаем person_server, что SLAVE якобы отвалился от keepalive (должно проапдейтить статус соотв. Person в PartyData)
        self.I.PS.inCastle( SLAVE1, 0 )
        self.checkPendingEvent( MASTER, "friend_status", "PartyData" )
       
        logLevel()

    def test_BadInvites_BRIEF(self):
        info("TEST WAS IGNORED BY THE TASK https://devjira.nivalnetwork.com/browse/PF-103776")
        '''logLevel()

        self.createGuestUsers( 5 )

        MASTER = 1
        SLAVE1 = 2
        SLAVE2 = 3
        SLAVE3 = 4
        
        MASTER2 = 5     
        
        ## logLevel( logging.INFO ) 
        
        ## --------------------------
        ## инвайт несуществующему юзеру
        WRONG_AUID = 12345
        self.sendInvite(MASTER, -1, invite_auid=WRONG_AUID)
        
        # мастер: получил отлуп?
        test, event = self.checkPendingFriendsEvent(MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingEvent(test, MASTER, "error", failed_cmd="invite", invite_auid=WRONG_AUID, message="user not online")
        
        ## ------------------------------------------------------------------------------
        ## инвайт существующему, но только что ушедшему в оффлайн юзеру
        
        ##logLevel( logging.INFO ) 
        
        test = self.sendLogout( SLAVE1 )
        info("logout reply: %s" % test.reply )
        t0 = time.time()
        while users.get( SLAVE1 ): 
            self.I.WS.tick()
            # подождем, пока уйдет оффлайн
            time.sleep(0.1)
            self.assert_( time.time() - t0 < 1.5 ) # не ждем больше 1.5 секунд
        
        ##logLevel() 
        
        # теперь шлем инвайт 
        self.sendInvite(MASTER, SLAVE1)
        
        # мастер: получил отлуп?
        test, event = self.checkPendingEvent(MASTER, "error", failed_cmd="invite", invite_auid=SLAVE1, message="user not online")
        
        ## --------------------------
        ## инвайт себя
        self.sendInvite(MASTER, MASTER)
        
        # мастер: получил отлуп?
        test, event = self.checkPendingEvent(MASTER, "error", failed_cmd="invite", invite_auid=MASTER, message="cant invite self")

        ## -----------------------------------
        ## инвайт юзеру, который уже в партии
        
        # -----------------------------------
        # делаем постоянную партию...
        # отсылаем инвайт
        self.sendInvite(MASTER, SLAVE2)
        
        # мастер: получил извещение, что партия создана?
        test, event = self.checkPendingEvent(MASTER, "create_init", "PartyData", message="created new party during invite", master_auid=MASTER)
        PARTY_ID = event.party_id
        
        # мастер: получил подтверждение, что инвайт отослан?
        self.checkNextPendingEvent(test, MASTER, "invited", message="ok", invite_auid=SLAVE2)
        
        # слэйв: получил инвайт?
        test, event = self.checkPendingFriendsEvent(SLAVE2, "status_change", "FriendsData", friend_auid=SLAVE2)
        test, event = self.checkNextPendingEvent(test, SLAVE2, "invite", "from_nick", master_auid=MASTER, party_id=PARTY_ID)
        
        # --------------------------
        # слэйв: принимаем invite
        self.sendAccept(SLAVE2, MASTER)
        
        # мастер: получил join?
        test, event = self.checkPendingEvent(MASTER, "friend_status", "PartyData", auid=SLAVE2)
        test, event = self.checkNextPendingEvent(test, MASTER, "join", join_auid=SLAVE2, party_id=PARTY_ID)

        # слэйв: получил join_init?
        test, event = self.checkPendingEvent(SLAVE2, "accept_invite", "FriendsData" )
        self.checkNextPendingEvent(test, SLAVE2, "join_init", "PartyData", "master_auid", join_auid=SLAVE2, party_id=PARTY_ID )

        # --------------------------
        # теперь отсылаем инвайт от второго мастера
        self.sendInvite(MASTER2, SLAVE2)

        # мастер: получил отлуп?
        test, event = self.checkPendingFriendsEvent(MASTER2, "status_change", "FriendsData", friend_auid=MASTER2)
        test, event = self.checkNextPendingEvent(test, MASTER2, "error", failed_cmd="invite", message="user already has a party", invite_auid=SLAVE2)
        
        # слэйв: не получал инвайтов?
        self.checkNoPendingEvents(SLAVE2)
        
        ## --------------------------
        ## доставим юзеру [3] инвайт от другого мастера (пусть у MASTER2 будет временная партия)
        self.sendInvite(MASTER2, SLAVE3)

        # мастер: получил извещение, что партия создана?
        test, event = self.checkPendingEvent(MASTER2, "create_init", "PartyData", message="created new party during invite", master_auid=MASTER2)
        TEMP_PARTY_ID2 = event.party_id
        
        # мастер: получил подтверждение, что инвайт отослан?
        self.checkNextPendingEvent(test, MASTER2, "invited", "party_id", message="ok", invite_auid=SLAVE3)
        
        # слэйв: получил инвайт?
        test, event = self.checkPendingFriendsEvent(SLAVE3, "status_change", "FriendsData", friend_auid=SLAVE3)
        test, event = self.checkNextPendingEvent(test, SLAVE3, "invite", "from_nick", master_auid=MASTER2, party_id=TEMP_PARTY_ID2)
        
        #~ # у MASTER2 теперь должна быть своя собственная временная партия
        #~ self.sendStatus(MASTER2)
        
        #~ # слэйв: получил статус?
        #~ self.checkPendingEvent(MASTER2, "status", party_id=TEMP_PARTY_ID2)
        
        
        ## -----------------------------------
        ## инвайт, когда мы мастер постоянной группы
        
        # отсылаем инвайт
        self.sendInvite(MASTER, SLAVE3)
        
        # мастер: получил подтверждение, что инвайт отослан?
        test, event = self.checkPendingEvent(MASTER, "invited", message="ok", invite_auid=SLAVE3, party_id=PARTY_ID)
        
        # слэйв: получил инвайт?
        self.checkPendingEvent(SLAVE3, "invite", "from_nick", master_auid=MASTER, party_id=PARTY_ID)
        
        ## -----------------------------------
        ## инвайт, когда мы не мастер
        
        self.skipPendingEvents(SLAVE2) ################# нам как члену партии должен прийти дубликат "invited"
        
        # отсылаем инвайт
        self.sendInvite(SLAVE2, SLAVE3)

        # мастер: получил отлуп?
        test, event = self.checkPendingEvent(SLAVE2, "error", failed_cmd="invite", invite_auid=SLAVE3, message="party member (not master) cannot invite")
        
        # слэйв: не получал инвайтов?
        self.checkNoPendingEvents(SLAVE3)
        
        ## -----------------------------------
        ## повторный инвайт своего же мембера
        
        # отсылаем инвайт
        self.sendInvite(MASTER, SLAVE2)
        
        # мастер: получил отлуп?
        test, event = self.checkPendingEvent(MASTER, "error", failed_cmd="invite", invite_auid=SLAVE2, message="user already has a party")
        
        # слэйв: не получал инвайтов?
        self.checkNoPendingEvents(SLAVE2)
        
        ## -----------------------------------
        ## двукратный инвайт одного и того же юзера (смотрим, что на N-ный раз все равно отработает accept)

        for i in xrange(10):
            # отсылаем инвайт
            self.sendInvite(MASTER, SLAVE3)
            
            # мастер: получил подтверждение, что инвайт отослан?
            test, event = self.checkPendingEvent(MASTER, "invited", message="ok", invite_auid=SLAVE3, party_id=PARTY_ID)
            
            # слэйв: получил инвайт?
            self.checkPendingEvent(SLAVE3, "invite", "from_nick", master_auid=MASTER, party_id=PARTY_ID)
            
        ################# нам как члену партии должны прийти 10 дубликатов "invited"
        self.checkPendingEvent(SLAVE2, "invited", message="ok", invite_auid=SLAVE3, party_id=PARTY_ID)
                    
        # --------------------------
        # слэйв: наконец, принимаем invite
        self.sendAccept(SLAVE3, MASTER)
        
        # мастер: получил join?
        test, event = self.checkPendingEvent(MASTER, "friend_status", "PartyData", auid=SLAVE3)
        test, event = self.checkNextPendingEvent(test, MASTER, "join", join_auid=SLAVE3, party_id=PARTY_ID)

        # уже бывший в партии слэйв: получил join?
        test, event = self.checkPendingEvent(SLAVE2, "friend_status", "PartyData", auid=SLAVE3)
        test, event = self.checkNextPendingEvent(test, SLAVE2, "join", join_auid=SLAVE3, party_id=PARTY_ID)
        
        # новый слэйв: получил join?
        test, event = self.checkPendingEvent(SLAVE3, "accept_invite", "FriendsData" )
        self.checkNextPendingEvent(test, SLAVE3, "join_init", "PartyData", "master_auid", join_auid=SLAVE3, party_id=PARTY_ID )
        
        ## -----------------------------------
        ## приглашаем мастера временной партии
        #### logLevel( logging.DEBUG ) ####
        
        # отсылаем инвайт
        self.sendInvite(MASTER, MASTER2)
        
        ## по новому поведению это фейл (у MASTER2 есть временная партия, и его нельзя пригласить)
        # мастер: получил отлуп?
        test, event = self.checkPendingEvent(MASTER, "error", failed_cmd="invite", invite_auid=MASTER2, message="user already has a party")
        
        #~ # мастер: получил подтверждение, что инвайт отослан? (членам партии тоже придут дубликаты invited)
        #~ for index in [MASTER, SLAVE2, SLAVE3]:
            #~ self.checkPendingEvent(index, "invited", message="ok", invite_auid=MASTER2, party_id=PARTY_ID)
        
        #~ # слэйв: получил инвайт?
        #~ self.checkPendingEvent(MASTER2, "invite", "from_nick", master_auid=MASTER, party_id=PARTY_ID)
        
        #~ # --------------------------
        #~ # MASTER2: теперь принимаем invite
        #~ self.sendAccept(MASTER2, MASTER)
        
        #~ # все получили join?
        #~ for index in [MASTER, SLAVE2, SLAVE3]:
            #~ self.checkPendingEvent(index, "join", join_auid=MASTER2, party_id=PARTY_ID)

        #~ self.skipPendingEvents(MASTER2) '''


class PartyTest2( PartyTestBase ):
#class PartyTest2: # отключаем весь набор тестов
    """ """
    def test_checkPartyGoKickStop(self):
        logLevel()
        MASTER = 1
        SLAVE = 2
        
        self.createGuestUsers( 2 )

        MASTER = self.accs[MASTER].auid
        SLAVE = self.accs[SLAVE].auid
        
        # --------------------------
        # отсылаем инвайт
        self.sendInvite(MASTER, SLAVE)
        
        # мастер: получил извещение, что партия создана?
        test, event = self.checkPendingFriendsEvent(MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingEvent(test, MASTER, "create_init", "PartyData", message="created new party during invite", master_auid=MASTER)
        PARTY_ID = event.party_id
        
        # мастер: получил подтверждение, что инвайт отослан?
        self.checkNextPendingEvent(test, MASTER, "invited", message="ok", invite_auid=SLAVE)
        
        # слэйв: получил инвайт?
        test, event = self.checkPendingFriendsEvent(SLAVE, "status_change", "FriendsData", friend_auid=SLAVE)
        self.checkNextPendingEvent(test, SLAVE, "invite", "from_nick", master_auid=MASTER, party_id=PARTY_ID)
        
        # --------------------------
        # слэйв: принимаем invite
        self.sendAccept(SLAVE, MASTER)
        
        # мастер: получил join?
        test, event = self.checkPendingEvent(MASTER, "friend_status", "PartyData", auid=SLAVE)
        test, event = self.checkNextPendingEvent(test, MASTER, "join", join_auid=SLAVE, party_id=PARTY_ID)

        # слэйв: получил join_init?
        test, event = self.checkPendingEvent(SLAVE, "accept_invite", "FriendsData" )
        self.checkNextPendingEvent(test, SLAVE, "join_init", "PartyData", "master_auid", join_auid=SLAVE, party_id=PARTY_ID )

        #info( "------- MASTER HERO KEYS: %s" % self.accs[MASTER].model.HeroesKeeper.keys() )
        #info( "------- MASTER HERO[1]: %s" % self.accs[MASTER].model.HeroesKeeper.get(1).__dict__ )
        
        # --------------------------
        # мастер: выбираем героя 
        hero_id_1 = self.accs[MASTER].model.HeroesKeeper.keys()[0]
        hero_crc_1 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_1).PersistentId
        hero_id_2 = self.accs[MASTER].model.HeroesKeeper.keys()[1]
        hero_crc_2 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_2).PersistentId
        #~ hero_id_3 = self.accs[SLAVE2].model.HeroesKeeper.keys()[2]
        #~ hero_crc_3 = self.accs[SLAVE2].model.HeroesKeeper.get(hero_id_3).PersistentId
        
        ## logLevel( logging.INFO)
        
        self.sendHero( MASTER, PARTY_ID, hero_id=hero_id_1, hero_crc=hero_crc_1 )
        
        # мастер: получил hero?
        self.checkPendingEvent( MASTER, "hero", party_id=PARTY_ID )
        # слэйв: получил hero?
        self.checkPendingEvent( SLAVE, "hero", party_id=PARTY_ID )

        ## ----------------------------------------------------
        ## пробуем party_go: д.б. отлуп, не все юзеры выбрали героев
        # мастер: GO
        self.sendGo( MASTER, PARTY_ID )
        
        # мастер: получил отлуп?
        self.checkPendingEvent( MASTER, "error", failed_cmd="go", message="not all party members chosen heroes for pvp", party_id=PARTY_ID )
        
        ##logLevel( logging.DEBUG )
        
        # --------------------------
        # слэйв: выбираем героя (assassin)
        hero_crc = self.accs[SLAVE].model.HeroesKeeper.get(1).PersistentId
        self.sendHero( SLAVE, PARTY_ID, hero_id=hero_id_2, hero_crc=hero_crc_2 )
        
        # мастер: получил hero?
        self.checkPendingEvent( MASTER, "hero", party_id=PARTY_ID )
        # слэйв: получил hero?
        self.checkPendingEvent( SLAVE, "hero", party_id=PARTY_ID )

        # мастер: GO
        self.sendGo( MASTER, PARTY_ID )

        # мастер: получил go?
        self.checkPendingGoProgress( 2, MASTER, PARTY_ID )
        
        # слэйв: получил go?
        self.checkPendingGoProgress( 2, SLAVE, PARTY_ID )
        
        ## ----------------------------------------------------
        ## пробуем party_go: д.б. отлуп, партия уже в матчмейкинге
        # мастер: GO
        self.sendGo( MASTER, PARTY_ID )
        
        # мастер: получил отлуп?
        self.checkPendingEvent( MASTER, "error", failed_cmd="go", message="not all party members ready for pvp", party_id=PARTY_ID )
        
        ## ----------------------------------------------------
        ## теперь делаем kick: партия должна сразу выпасть из матчмейкинга
        self.sendKick( MASTER, SLAVE)
        
        # мастер: получил оповещение о kick?
        test, event = self.checkPendingEvent( MASTER, "disband", "PartyData", party_id=PARTY_ID )
        self.checkNextPendingEvent( test, MASTER, "stop", party_id=PARTY_ID )
        
        test, event = self.checkPendingEvent( SLAVE, "disbanded", "PartyData", party_id=PARTY_ID )
        self.checkNextPendingEvent( test, SLAVE, "stop", party_id=PARTY_ID )
        
        
# ---------------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------------
class PartyTest3( PartyTestBase ):
##class PartyTest3( ):
    """ """
    def test_checkDodgePartyGo(self):
        logLevel()
        MASTER = 1
        SLAVE = 2
        
        self.createGuestUsers( 2 )

        MASTER = self.accs[MASTER].auid
        SLAVE = self.accs[SLAVE].auid
        
        # --------------------------
        # отсылаем инвайт
        self.sendInvite(MASTER, SLAVE)
        
        # мастер: получил извещение, что партия создана?
        test, event = self.checkPendingFriendsEvent(MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingEvent(test, MASTER, "create_init", "PartyData", message="created new party during invite", master_auid=MASTER)
        PARTY_ID = event.party_id
        
        # мастер: получил подтверждение, что инвайт отослан?
        self.checkNextPendingEvent(test, MASTER, "invited", message="ok", invite_auid=SLAVE)
        
        # слэйв: получил инвайт?
        test, event = self.checkPendingFriendsEvent(SLAVE, "status_change", "FriendsData", friend_auid=SLAVE)
        test, event = self.checkNextPendingEvent(test, SLAVE, "invite", "from_nick", master_auid=MASTER, party_id=PARTY_ID)
        
        # --------------------------
        # слэйв: принимаем invite
        #logLevel( logging.INFO )
        
        self.sendAccept(SLAVE, MASTER)
        
        # мастер: получил join?
        test, event = self.checkPendingEvent(MASTER, "friend_status", "PartyData", auid=SLAVE)
        test, event = self.checkNextPendingEvent(test, MASTER, "join", join_auid=SLAVE, party_id=PARTY_ID)

        # слэйв: получил join_init?
        test, event = self.checkPendingEvent(SLAVE, "accept_invite", "FriendsData" )
        self.checkNextPendingEvent(test, SLAVE, "join_init", "PartyData", "master_auid", join_auid=SLAVE, party_id=PARTY_ID )

        #info( "------- MASTER HERO KEYS: %s" % self.accs[MASTER].model.HeroesKeeper.keys() )
        #info( "------- MASTER HERO[1]: %s" % self.accs[MASTER].model.HeroesKeeper.get(1).__dict__ )
        
        # --------------------------
        # мастер: выбираем героя 
        hero_id_1 = self.accs[MASTER].model.HeroesKeeper.keys()[0]
        hero_crc_1 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_1).PersistentId
        hero_id_2 = self.accs[MASTER].model.HeroesKeeper.keys()[1]
        hero_crc_2 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_2).PersistentId
        #~ hero_id_3 = self.accs[SLAVE2].model.HeroesKeeper.keys()[2]
        #~ hero_crc_3 = self.accs[SLAVE2].model.HeroesKeeper.get(hero_id_3).PersistentId
        
        ## logLevel( logging.INFO)
        
        self.sendHero( MASTER, PARTY_ID, hero_id=hero_id_1, hero_crc=hero_crc_1 )
        
        # мастер: получил hero?
        self.checkPendingEvent( MASTER, "hero", party_id=PARTY_ID )
        # слэйв: получил hero?
        self.checkPendingEvent( SLAVE, "hero", party_id=PARTY_ID )

        # слэйв: выбираем героя (assassin)
        hero_crc = self.accs[SLAVE].model.HeroesKeeper.get(1).PersistentId
        self.sendHero( SLAVE, PARTY_ID, hero_id=hero_id_2, hero_crc=hero_crc_2 )
        
        # мастер: получил hero?
        self.checkPendingEvent( MASTER, "hero", party_id=PARTY_ID )
        # слэйв: получил hero?
        self.checkPendingEvent( SLAVE, "hero", party_id=PARTY_ID )

        ## ----------------------------------------------------
        self.accs[1].model.LordInfo.GuardInfo.RetiredTime = time.time() + 100500
        self.sendDodge( MASTER, PARTY_ID )
        self.accs[2].model.LordInfo.GuardInfo.RetiredTime = time.time() + 100500
        self.sendDodge( SLAVE, PARTY_ID )
        # мастер: получил dodge?
        self.checkPendingEvent( MASTER, "dodge", party_id=PARTY_ID )
        # слэйв: получил dodge?
        self.checkPendingEvent( SLAVE, "dodge", party_id=PARTY_ID )
        
        
        ## пробуем party_go: д.б. отлуп, retiredtime > time.time()
        # мастер: GO
        self.sendGo( MASTER, PARTY_ID )
        
        # мастер: получил отлуп?
        self.checkPendingEvent( MASTER, "error", failed_cmd="go", message="user is retired", party_id=PARTY_ID )
        
        # --------------------------
        ## ----------------------------------------------------
        self.accs[1].model.LordInfo.GuardInfo.RetiredTime = 0
        self.sendDodge( MASTER, PARTY_ID )
        self.accs[2].model.LordInfo.GuardInfo.RetiredTime = time.time() + 100500
        self.sendDodge( SLAVE, PARTY_ID )
        # мастер: получил dodge?
        self.checkPendingEvent( MASTER, "dodge", party_id=PARTY_ID )
        # слэйв: получил dodge?
        self.checkPendingEvent( SLAVE, "dodge", party_id=PARTY_ID )
        
        ## пробуем party_go: д.б. отлуп, retiredtime > time.time()
        # мастер: GO
        self.sendGo( MASTER, PARTY_ID )
        
        # мастер: получил отлуп?
        self.checkPendingEvent( MASTER, "error", failed_cmd="go", message="user is retired", party_id=PARTY_ID )
        
        ##logLevel( logging.DEBUG )
        
        # --------------------------
        ## ----------------------------------------------------
        self.accs[1].model.LordInfo.GuardInfo.RetiredTime = 0
        self.sendDodge( MASTER, PARTY_ID )
        self.accs[2].model.LordInfo.GuardInfo.RetiredTime = 0
        self.sendDodge( SLAVE, PARTY_ID )
        # мастер: получил dodge?
        self.checkPendingEvent( MASTER, "dodge", party_id=PARTY_ID )
        # слэйв: получил dodge?
        self.checkPendingEvent( SLAVE, "dodge", party_id=PARTY_ID )
        
        ## пробуем party_go: д.б. отлуп, retiredtime > time.time()
        # мастер: GO
        self.sendGo( MASTER, PARTY_ID )
        
        # мастер: получил go?
        self.checkPendingGoProgress( 2, MASTER, PARTY_ID )
        
        # слэйв: получил go?
        self.checkPendingGoProgress( 2, SLAVE, PARTY_ID )
        
        ##logLevel( logging.DEBUG )
        
        # --------------------------

##----------------------------------------------------------------
##----------------------------------------------------------------

# ---------------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------------
class PartyTest4( PartyTestBase ):
##class PartyTest3( ):
    """ Тесты на взаимодействия при создании afterparty """

    def test_Choose_Party_Again_Three_Persons_Agree(self):
        """Создаём пати после боя, когда все 3 участника соглашаются"""
        logLevel()
        MASTER = 1
        SLAVE1 = 2
        SLAVE2 = 3


        ## logLevel( logging.DEBUG )

        self.createGuestUsers(3)
        self.setLastPlayedMap(MASTER, "/Maps/Multiplayer/MOBA/_.ADMPDSCR")
        self.setLastPlayedMap(SLAVE1, "/Maps/Multiplayer/MOBA/_.ADMPDSCR")
        self.setLastPlayedMap(SLAVE2, "/Maps/Multiplayer/MOBA/_.ADMPDSCR")

        ## --------------------------
        ## первый игрок приходит из боя
        self.sendChoosePartyAgain(MASTER, [MASTER, SLAVE1, SLAVE2], 1)

        # мастер: получил пати-дату?
        test, event = self.checkPendingFriendsEvent(MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        # Из-за ожидания запроса сначала приходит информация о сопартийцах и только потом о создании пати
        test, event = self.checkNextPendingEvent(test, MASTER, "person_info", "PartyData")
        test, event = self.checkNextPendingEvent(test, MASTER, "person_info", "PartyData")
        test, event = self.checkNextPendingEvent(test, MASTER, "create_init", "PartyData", message="created same party after battle", master_auid=MASTER)
        PARTY_ID = event.party_id

        # --------------------------
        # слейв1: соглашается
        self.sendChoosePartyAgain(SLAVE1, [MASTER, SLAVE1, SLAVE2], 1)

        # мастер: получил уведомление о том, что слейв1 присоединился?
        test, event = self.checkPendingEvent(MASTER, "change", "PartyData", message="afterparty member status changed", join_auid=SLAVE1)

        # слейв1: получил извещение, что партия создана?
        test, event = self.checkPendingFriendsEvent(SLAVE1, "status_change", "FriendsData", friend_auid=SLAVE1)
        test, event = self.checkNextPendingEvent(test, SLAVE1, "create_init", "PartyData", master_auid=MASTER,
                                                 message="joined same party after battle", party_id=PARTY_ID)

        # --------------------------
        # слейв2: соглашается
        self.sendChoosePartyAgain(SLAVE2, [MASTER, SLAVE1, SLAVE2], 1)

        # мастер: получил уведомление о том, что слейв2 присоединился?
        test, event = self.checkPendingEvent(MASTER, "change", "PartyData", message="afterparty member status changed", join_auid=SLAVE2)
        # слейв1: получил уведомление о том, что слейв2 присоединился?
        test, event = self.checkPendingEvent(SLAVE1, "change", "PartyData", message="afterparty member status changed", join_auid=SLAVE2)

        # слейв2: получил извещение, что партия создана?
        test, event = self.checkPendingFriendsEvent(SLAVE2, "status_change", "FriendsData", friend_auid=SLAVE2)
        test, event = self.checkNextPendingEvent(test, SLAVE2, "create_init", "PartyData", master_auid=MASTER,
                                                 message="joined same party after battle", party_id=PARTY_ID)

        # --------------------------
        # один раз тикнем PersonServer: партия должна финализироваться
        self.iDictPTS.WS.tick()

        # мастер: получил уведомление о том, что пати готова?
        test, event = self.checkPendingEvent(MASTER, "change", "PartyData", message="afterparty was finalized")
        # слейв1: получил уведомление о том, что пати готова?
        test, event = self.checkPendingEvent(SLAVE1, "change", "PartyData", message="afterparty was finalized")
        # слейв2: получил уведомление о том, что пати готова?
        test, event = self.checkPendingEvent(SLAVE2, "change", "PartyData", message="afterparty was finalized")

        # Проверим, что пати финализировалась
        party = self.iDictPTS.WS.parties.get(PARTY_ID)
        self.assert_(party is not None)
        self.assert_(len(party.members) == 3)
        self.assert_(party.PartyData.madeAfterBattle is False)
        self.assert_(party.PartyData.afterBattleLockEndTime == 0)


    def test_Choose_Party_Again_Two_Persons_Agree_One_Not(self):
        """Создаём пати после боя, когда 2 участника соглашаются, один против
            Должна создатся пати из 2-х игроков, отказавшемус уведомления этой пати не приходят"""
        logLevel()
        MASTER = 1
        SLAVE1 = 2
        SLAVE2 = 3

        ## logLevel( logging.DEBUG )

        self.createGuestUsers(3)
        self.setLastPlayedMap(MASTER, "/Maps/Multiplayer/MOBA/_.ADMPDSCR")
        self.setLastPlayedMap(SLAVE1, "/Maps/Multiplayer/MOBA/_.ADMPDSCR")
        self.setLastPlayedMap(SLAVE2, "/Maps/Multiplayer/MOBA/_.ADMPDSCR")

        ## --------------------------
        ## первый игрок приходит из боя
        self.sendChoosePartyAgain(MASTER, [MASTER, SLAVE1, SLAVE2], 1)

        # мастер: получил пати-дату?
        test, event = self.checkPendingFriendsEvent(MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        # Из-за ожидания запроса сначала приходит информация о сопартийцах и только потом о создании пати
        test, event = self.checkNextPendingEvent(test, MASTER, "person_info", "PartyData")
        test, event = self.checkNextPendingEvent(test, MASTER, "person_info", "PartyData")
        test, event = self.checkNextPendingEvent(test, MASTER, "create_init", "PartyData", message="created same party after battle", master_auid=MASTER)
        PARTY_ID = event.party_id

        # --------------------------
        # слейв1: соглашается
        self.sendChoosePartyAgain(SLAVE1, [MASTER, SLAVE1, SLAVE2], 1)

        # мастер: получил уведомление о том, что слейв1 присоединился?
        test, event = self.checkPendingEvent(MASTER, "change", "PartyData", message="afterparty member status changed", join_auid=SLAVE1)

        # слейв1: получил извещение, что партия создана?
        test, event = self.checkPendingFriendsEvent(SLAVE1, "status_change", "FriendsData", friend_auid=SLAVE1)
        test, event = self.checkNextPendingEvent(test, SLAVE1, "create_init", "PartyData", master_auid=MASTER,
                                                 message="joined same party after battle", party_id=PARTY_ID)

        # слейв2: обновил статус?
        test, event = self.checkPendingFriendsEvent(SLAVE2, "status_change", "FriendsData", friend_auid=SLAVE2)
        # ---------------------------------------------------
        # ПРОВЕРИМ, ЧТО ЗАПРОСЫ СМЕНЫ КАРТЫ, ГЕРОЯ, ФЛАГА... НЕ ДОХОДЯТ ДО ЕЩЁ НЕ РЕШИВШЕГО ИГРОКА
        # ---------------------------------------------------

        # --------------------------
        # ГЕРОЙ
        # --------------------------
        # мастер: выбираем героя
        hero_id_1 = self.accs[MASTER].model.HeroesKeeper.keys()[0]
        hero_crc_1 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_1).PersistentId
        self.sendHero(MASTER, PARTY_ID, hero_id=hero_id_1, hero_crc=hero_crc_1)
        # все согласившиеся получили hero?
        self.checkChangeEventForAllMembers([MASTER, SLAVE1], "hero", PARTY_ID)
        # слейв2: получил уведомление?
        test = self.checkNoPendingEvents(SLAVE2)

        # --------------------------
        # КАРТА
        # --------------------------
        # мастер: меняем карту
        self.sendMap(MASTER, game_type="/Maps/Multiplayer/MOBA/Test_PVP_3x3.ADMPDSCR")
        # все согласившиеся получили map?
        self.checkChangeEventForAllMembers([MASTER, SLAVE1], "map", PARTY_ID)
        # слейв2: получил уведомление?
        test = self.checkNoPendingEvents(SLAVE2)

        # --------------------------
        # ФЛАГ
        # --------------------------
        self.addCustomFlag(MASTER, "rak")
        # мастер: меняем флаг
        self.sendFlag(MASTER, FlagType.Special, "rak")
        # все согласившиеся получили flag?
        self.checkChangeEventForAllMembers([MASTER, SLAVE1], "flag", PARTY_ID)
        # слейв2: получил уведомление?
        test = self.checkNoPendingEvents(SLAVE2)

        # --------------------------
        # ИНВЕНТАРЬ
        # --------------------------
        # мастер: меняем "заполненность" инвентаря
        self.sendInventoryIsFull(MASTER, True)
        # все согласившиеся получили is_inventory_full?
        self.checkChangeEventForAllMembers([MASTER, SLAVE1], "is_inventory_full", PARTY_ID)
        # слейв2: получил уведомление?
        test = self.checkNoPendingEvents(SLAVE2)


        # --------------------------
        # слейв2: не соглашается
        self.sendChoosePartyAgain(SLAVE2, [MASTER, SLAVE1, SLAVE2], 0)

        # мастер: получил уведомление о том, что слейв2 присоединился?
        test, event = self.checkPendingEvent(MASTER, "change", "PartyData", message="afterparty member status changed", join_auid=SLAVE2)
        # слейв1: получил уведомление о том, что слейв2 присоединился?
        test, event = self.checkPendingEvent(SLAVE1, "change", "PartyData", message="afterparty member status changed", join_auid=SLAVE2)

        # слейв2: получил извещение, что партия создана?
        test = self.checkNoPendingEvents(SLAVE2)

        # --------------------------
        # один раз тикнем PersonServer: партия должна финализироваться
        self.iDictPTS.WS.tick()

        # мастер: получил уведомление о том, что пати готова?
        test, event = self.checkPendingEvent(MASTER, "change", "PartyData", message="afterparty was finalized")
        # слейв1: получил уведомление о том, что пати готова?
        test, event = self.checkPendingEvent(SLAVE1, "change", "PartyData", message="afterparty was finalized")
        # слейв2: получил уведомление о том, что пати готова?
        test = self.checkNoPendingEvents(SLAVE2)

        # Проверим, что пати финализировалась
        party = self.iDictPTS.WS.parties.get(PARTY_ID)
        self.assert_(party is not None)
        self.assert_(len(party.members) == 2)
        self.assert_(party.PartyData.madeAfterBattle is False)
        self.assert_(party.PartyData.afterBattleLockEndTime == 0)

    def test_Choose_Party_Again_First_Player_Declines(self):
        """Создаём пати после боя, первый, приславший уведомление, отказывается, двое соглашаются"""
        logLevel()
        MASTER = 1
        SLAVE1 = 2
        SLAVE2 = 3

        ## logLevel( logging.DEBUG )

        self.createGuestUsers(3)
        self.setLastPlayedMap(MASTER, "/Maps/Multiplayer/MOBA/_.ADMPDSCR")
        self.setLastPlayedMap(SLAVE1, "/Maps/Multiplayer/MOBA/_.ADMPDSCR")
        self.setLastPlayedMap(SLAVE2, "/Maps/Multiplayer/MOBA/_.ADMPDSCR")

        ## --------------------------
        ## первый игрок приходит из боя
        self.sendChoosePartyAgain(SLAVE2, [MASTER, SLAVE1, SLAVE2], 0)

        # слейв1: обновил статус?
        test, event = self.checkPendingFriendsEvent(SLAVE1, "status_change", "FriendsData", friend_auid=SLAVE1)

        # слейв2: обновил статус?
        test, event = self.checkPendingFriendsEvent(SLAVE2, "status_change", "FriendsData", friend_auid=SLAVE2)
        # слейв2: отказался и больше никому ничего не должен
        test = self.checkNoPendingEvents(SLAVE2)

        # --------------------------
        # мастер: соглашается
        self.sendChoosePartyAgain(MASTER, [MASTER, SLAVE1, SLAVE2], 1)

        # мастер и слейв2: получил уведомление о том, что слейв1 присоединился?
        test = self.checkNoPendingEvents(SLAVE2)
        test = self.checkNoPendingEvents(SLAVE1)

        # слейв1: получил извещение, что партия создана?
        test, event = self.checkPendingFriendsEvent(MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingEvent(test, MASTER, "create_init", "PartyData", master_auid=MASTER,
                                                 message=u"joined same party after battle")
        PARTY_ID = event.party_id

        # ---------------------------------------------------
        # ПРОВЕРИМ, ЧТО ЗАПРОСЫ СМЕНЫ КАРТЫ, ГЕРОЯ, ФЛАГА... НЕ ДОХОДЯТ ДО ОТКАЗАВШЕНГОСЯ И ЕЩЁ НЕ РЕШИВШЕГО ИГРОКА
        # ---------------------------------------------------

        # --------------------------
        # ГЕРОЙ
        # --------------------------
        # мастер: выбираем героя
        hero_id_1 = self.accs[MASTER].model.HeroesKeeper.keys()[0]
        hero_crc_1 = self.accs[MASTER].model.HeroesKeeper.get(hero_id_1).PersistentId
        self.sendHero(MASTER, PARTY_ID, hero_id=hero_id_1, hero_crc=hero_crc_1)
        # все согласившиеся получили hero?
        self.checkChangeEventForAllMembers([MASTER], "hero", PARTY_ID)
        # слейв2: получил уведомление?
        test = self.checkNoPendingEvents(SLAVE2)
        test = self.checkNoPendingEvents(SLAVE1)

        # --------------------------
        # КАРТА
        # --------------------------
        # мастер: меняем карту
        self.sendMap(MASTER, game_type="/Maps/Multiplayer/MOBA/Test_PVP_3x3.ADMPDSCR")
        # все согласившиеся получили map?
        self.checkChangeEventForAllMembers([MASTER], "map", PARTY_ID)
        # слейв2: получил уведомление?
        test = self.checkNoPendingEvents(SLAVE2)
        test = self.checkNoPendingEvents(SLAVE1)

        # --------------------------
        # ФЛАГ
        # --------------------------
        self.addCustomFlag(MASTER, "rak")
        # мастер: меняем флаг
        self.sendFlag(MASTER, FlagType.Special, "rak")
        # все согласившиеся получили flag?
        self.checkChangeEventForAllMembers([MASTER], "flag", PARTY_ID)
        # слейв2: получил уведомление?
        test = self.checkNoPendingEvents(SLAVE2)
        test = self.checkNoPendingEvents(SLAVE1)

        # --------------------------
        # ИНВЕНТАРЬ
        # --------------------------
        # мастер: меняем "заполненность" инвентаря
        self.sendInventoryIsFull(MASTER, True)
        # все согласившиеся получили is_inventory_full?
        self.checkChangeEventForAllMembers([MASTER], "is_inventory_full", PARTY_ID)
        # слейв2: получил уведомление?
        test = self.checkNoPendingEvents(SLAVE2)
        test = self.checkNoPendingEvents(SLAVE1)


        # --------------------------
        # слейв1: соглашается
        self.sendChoosePartyAgain(SLAVE1, [MASTER, SLAVE1, SLAVE2], 1)

        test = self.checkPendingEvent(SLAVE1, "create_init", "PartyData", master_auid=MASTER,
                                      message="joined same party after battle", party_id=PARTY_ID)

        # мастер: получил уведомление о том, что слейв1 присоединился?
        test, event = self.checkPendingEvent(MASTER, "change", "PartyData", message="afterparty member status changed", join_auid=SLAVE1)

        # --------------------------
        # один раз тикнем PersonServer: партия должна финализироваться
        self.iDictPTS.WS.tick()

        # мастер: получил уведомление о том, что пати готова?
        test, event = self.checkPendingEvent(MASTER, "change", "PartyData", message="afterparty was finalized")
        # слейв1: получил уведомление о том, что пати готова?
        test, event = self.checkPendingEvent(SLAVE1, "change", "PartyData", message="afterparty was finalized")
        # слейв2: получил уведомление о том, что пати готова?
        test = self.checkNoPendingEvents(SLAVE2)

        # Проверим, что пати финализировалась
        party = self.iDictPTS.WS.parties.get(PARTY_ID)
        self.assert_(party is not None)
        self.assert_(len(party.members) == 2)
        self.assert_(party.PartyData.madeAfterBattle is False)
        self.assert_(party.PartyData.afterBattleLockEndTime == 0)

    def test_Choose_Party_Again_Party_Disbanded(self):
        """Создаём пати после боя, когда cогласился только 1 участник
            2 отказываются до тайм-аута"""
        logLevel()
        MASTER = 1
        SLAVE1 = 2
        SLAVE2 = 3


        ## logLevel( logging.DEBUG )

        self.createGuestUsers(3)
        self.setLastPlayedMap(MASTER, "/Maps/Multiplayer/MOBA/_.ADMPDSCR")
        self.setLastPlayedMap(SLAVE1, "/Maps/Multiplayer/MOBA/_.ADMPDSCR")
        self.setLastPlayedMap(SLAVE2, "/Maps/Multiplayer/MOBA/_.ADMPDSCR")

        ## --------------------------
        ## первый игрок приходит из боя
        self.sendChoosePartyAgain(MASTER, [MASTER, SLAVE1, SLAVE2], 1)

        # слейвы: обвновим статус
        test, event = self.checkPendingFriendsEvent(SLAVE1, "status_change", "FriendsData", friend_auid=SLAVE1)
        test, event = self.checkPendingFriendsEvent(SLAVE2, "status_change", "FriendsData", friend_auid=SLAVE2)

        # мастер: получил пати-дату?
        test, event = self.checkPendingFriendsEvent(MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        # Из-за ожидания запроса сначала приходит информация о сопартийцах и только потом о создании пати
        test, event = self.checkNextPendingEvent(test, MASTER, "person_info", "PartyData")
        test, event = self.checkNextPendingEvent(test, MASTER, "person_info", "PartyData")
        test, event = self.checkNextPendingEvent(test, MASTER, "create_init", "PartyData", message="created same party after battle", master_auid=MASTER)
        PARTY_ID = event.party_id

        # --------------------------
        # слейв1: не соглашается
        self.sendChoosePartyAgain(SLAVE1, [MASTER, SLAVE1, SLAVE2], 0)

        # мастер: получил уведомление о том, что слейв1 присоединился?
        test, event = self.checkPendingEvent(MASTER, "change", "PartyData", message="afterparty member status changed", join_auid=SLAVE1)

        # слейв1,2: получил извещение, что партия создана?
        test = self.checkNoPendingEvents(SLAVE1)
        test = self.checkNoPendingEvents(SLAVE2)

        # --------------------------
        # слейв2: не соглашается
        self.sendChoosePartyAgain(SLAVE2, [MASTER, SLAVE1, SLAVE2], 0)

        # мастер: получил уведомление о том, что слейв2 присоединился?
        test, event = self.checkPendingEvent(MASTER, "change", "PartyData", message="afterparty member status changed", join_auid=SLAVE2)
        test = self.checkNoPendingEvents(SLAVE1)
        test = self.checkNoPendingEvents(SLAVE2)

        # --------------------------
        # один раз тикнем PersonServer: партия должна финализироваться
        self.iDictPTS.WS.tick()

        # мастер: получил уведомление о том, что пати готова?
        test, event = self.checkPendingEvent(MASTER, "change", "PartyData", message="afterparty was finalized")
        test, event = self.checkNextPendingEvent(test, MASTER, "error", "PartyData", message="party expired: all invites timed out")
        test = self.checkNoPendingEvents(SLAVE1)
        test = self.checkNoPendingEvents(SLAVE2)

        # Проверим, что пати удалилась
        party = self.iDictPTS.WS.parties.get(PARTY_ID)
        self.assert_(party is None)

##----------------------------------------------------------------
##----------------------------------------------------------------

def main():
    DEFAULT_LOG_LEVEL = logging.INFO
    #~ DEFAULT_LOG_LEVEL = logging.WARNING
    #~DEFAULT_LOG_LEVEL = logging.ERROR
    #print "DEFAULT_LOG_LEVEL: %s" % DEFAULT_LOG_LEVEL
    setDefaultLogLevel( DEFAULT_LOG_LEVEL )
    logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )
    
    info( "Loading XDB..." )
    config = MultiConfig()
    _SD = MultiStaticData( options.xdb_path + "/ExportedSocialData.xml", config.getMainConfig() )
    config.fillStaticDataDependendValues(_SD)
    BaseDummyTest.setXDB( _SD )
    
    info( "-- START tests.." )
    
    #~ suite = unittest.TestLoader().loadTestsFromTestCase( PartyTest2 )
    #~ unittest.TextTestRunner(verbosity=2).run(suite)
    #~ exit(0)
    
    ITERATIONS = 1
    for i in range(ITERATIONS):
        try:
            unittest.main()
        except SystemExit:
            if str( exc() ) == "True":
                sys.exit(1)
        except:
            catch()
            sys.exit(1)
            
    info( "-- Finish tests (x %d)." % ITERATIONS )
    

if __name__ == "__main__":
    main()
