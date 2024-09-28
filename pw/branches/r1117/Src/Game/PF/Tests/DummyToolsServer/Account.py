from AccountManagementAPI import AccountManagement
from AccountManagementAPI.ttypes import *
import AccountManagementAPI.ttypes

ACCOUNTS = [
    {'auid': 1,
     'login': 'fb#f123456',
     'snid': 'fb',
     'snuid': 'f123456',
     'nickname': 'User First',
     'email': 'user1@example.com',
     'online': True,
     'gold': 201,
     'silver': 200001,
     'perl': 21,
     'resource1': 30001,
     'resource1': 40001,
     'resource1': 50001,
     'currentsession': 8,
     'fame': 31,
     'fraction': 0,
     'location': 'RU',
     'isDeveloper': True,
     'isSpectator': True,
     'gender': Gender.Male,
     'nickChanges': 3,
     'nickChangesFree': 10,
     'fractionChanges': 5,
     'fractionChangesFree': 10,
     'premiumAccountDate': 1382113909,
     'numberOfWins': 17,
     'lordRating': 1200,
     'dodges': 3,
     'retiredTime': 1312903827,
     'dailyRating': 95,
     'joinedSnids': ['fb', 'vk'],
     'locale': 'RU',
     'muid': 'moomoo',
     'country': 'RU',
     'region': '66',
     'city': 'Saint Petersburg',
     'gmcountry': None,
     'gmregion': None,
     'gmcity': None,
     'cwplayerpoints': 15,
    },
    {'auid': 3,
     'login': 'pwc#2345678',
     'snid': 'pwc',
     'snuid': '2345678',
     'nickname': 'User Second',
     'email': 'user2@playpw.com',
     'online': False,
     'gold': 202,
     'silver': 200002,
     'perl': 22,
     'resource1': 30002,
     'resource1': 40002,
     'resource1': 50002,
     'currentsession': 0,
     'fame': 42,
     'fraction': 1,
     'location': 'RU',
     'isDeveloper': False,
     'isSpectator': False,
     'gender': Gender.Female,
     'nickChanges': 4,
     'nickChangesFree': 9,
     'fractionChanges': 4,
     'fractionChangesFree': 9,
     'premiumAccountDate': 0,
     'numberOfWins': 5,
     'lordRating': 1100,
     'dodges': 0,
     'retiredTime': 0,
     'dailyRating': 0,
     'banFlag': 1,
     'banned': 1384041600,
     'muteFlag': 2,
     'muted': 1384066800,
     'joinedSnids': ['pwc'],
     'locale': 'EN',
     'muid': '',
     'country': 'RU',
     'region': '48',
     'city': 'Moscow',
     'gmcountry': 'BY',
     'gmregion': '04',
     'gmcity': 'Minsk',
     'cwplayerpoints': 35,
    },
    #{'auid': 3, 'nickname': 'User Third'},
    {'auid': 4, 'nickname': 'User Fourth'},
    {'auid': 5, 'nickname': 'User Fifth'},
    {'auid': 6, 'nickname': 'User Sixth'},
    {'auid': 7, 'nickname': 'User Seventh'},
    {'auid': 8, 'nickname': 'User Eighth'},
    {'auid': 9, 'nickname': 'User Ninth'},
    {'auid': 11, 'nickname': 'User Eleventh'},
]

HEROES = {  1: [HeroInfo(1492899903, 1001, 22, 33, 600.0, 7, True), HeroInfo(637171033, 2001, 22, 33, 501.1, 1, False), ],
            2: [HeroInfo(3, "Hero Three", 33, 3333), ],
            3: [HeroInfo(4, "Hero Four", 44, 444), HeroInfo(5, "Hero Five", 55, 555), ],
            4: [HeroInfo(6, "Hero Six", 66, 666), ],
            5: [HeroInfo(7, "Hero Seven", 77, 777), ],
            6: [HeroInfo(8, "Hero Eight", 88, 888), ],
            7: [HeroInfo(9, "Hero Nine", 99, 999), ],
}

SESSIONS = [
    {'sessionid': 1,
     'teamdocts': [AccountShortInfo('fb', 'f123456', 1, 'user1@example.com', 'User First'), AccountShortInfo('zzima', 'z323456', 2, 'user2@example.com', 'User Second')],
     'teamadorni': [AccountShortInfo('fb', 'f123234234234234', 3, 'user4@example.com', 'User Third'), AccountShortInfo('fb', 'f12345434346', 4, 'user4@example.com', 'User Fourth')],
    },
    {'sessionid': 2,
     'teamdocts': [AccountShortInfo('fb', 'v3244555', 5, 'user5@example.com', 'User Fifth'), AccountShortInfo('fb', 'v3234666', 6, 'user6@example.com', 'User Sixth')],
     'teamadorni': [AccountShortInfo('fb', 'v327777', 7, 'user7@example.com', 'User Seventh')],
    },
]

GUILDS = [
    {'guildid': 1,
     'shortname': 'MLK',
     'fullname': 'Milky band',
     'messageoftheday': 'The best team ever',
     'guildExperience': 800,
     'cwguildpoints': 799,
     'cwrating': 5,
     'leaderauid': 1,
     'leadernickname': 'User First',
     'members': [GuildMemberInfo(2, 'User Second', True), GuildMemberInfo(3, 'User Third', False), GuildMemberInfo(4, 'User Fourth', False)],
     'suzerain': GuildShortInfo(2, 'YAG', 'Yet Another Guild'),
     'vassals': [],
     'siegeendtime': 0,
     'releaselocktime': 0,
    },
    {'guildid': 2,
     'shortname': 'YAG',
     'fullname': 'Yet Another Guild',
     'messageoftheday': 'Random guys',
     'guildExperience': 50,
     'cwguildpoints': 20,
     'cwrating': 55,
     'leaderauid': 2,
     'leadernickname': 'User Second',
     'members': [GuildMemberInfo(5, 'User Fifth', False), GuildMemberInfo(6, 'User Sixth', False), GuildMemberInfo(9, 'User Ninth', False)],
     'suzerain': GuildShortInfo(-1, '', ''),
     'vassals': [GuildShortInfo(1, 'MLK', 'The best team ever'), GuildShortInfo(3, 'FA', 'Forever alone')],
     'siegeendtime': 1412337330,
     'releaselocktime': 1412337330,
    },
    {'guildid': 3,
     'shortname': 'FA',
     'fullname': 'Forever alone',
     'messageoftheday': 'Nobody loves me :(',
     'guildExperience': 2,
     'cwguildpoints': 1,
     'cwrating': 555,
     'leaderauid': 11,
     'leadernickname': 'User Eleventh',
     'members': [],
     'suzerain': GuildShortInfo(2, 'YAG', 'Yet Another Guild'),
     'vassals': [],
     'siegeendtime': 1412337330,
     'releaselocktime': 1412337330,
    }
]

SKINS = [
    {'persistentId':'assassin_s1_a',
     'heroClassId':-1139813982,
     'owned':True,
     'available':True,
     'cost':100,
    },
    {'persistentId':'mowgly_s1_a',
     'heroClassId':1160508680,
     'owned':True,
     'available':True,
     'cost':100,
    },
    {'persistentId':'mage_s1_a',
     'heroClassId':-1233569438,
     'owned':False,
     'available':False,
     'cost':200,
    },
    {'persistentId':'ratcatcher_s1_a',
     'heroClassId':-834226607,
     'owned':False,
     'available':True,
     'cost':350,
    }
]

TALENTS = [
    {'talentClassId':2045110466,
     'talentInstanceId':10001,
     'refineRate':0,
     'boundHeroClassId':1492899903,
     'boundHeroInstanceId':1001,
    },
    {'talentClassId':-551525603,
     'talentInstanceId':10002,
     'refineRate':100,
     'boundHeroClassId':1492899903,
     'boundHeroInstanceId':1001,
    },
    {'talentClassId':1329240631,
     'talentInstanceId':10003,
     'refineRate':0,
     'boundHeroClassId':637171033,
     'boundHeroInstanceId':0,
    },
]

BUILDINGS = [
    {'classid':152667591,
     'instanceid':12301,
     'level':15,
     'instorage':False
    },
    {'classid':152667591,
     'instanceid':12302,
     'level':20,
     'instorage':False
    },
    {'classid':6558568,
     'instanceid':12303,
     'level':30,
     'instorage':False
    },
    {'classid':-785442342,
     'instanceid':12304,
     'level':21,
     'instorage':False
    },
    {'classid':-1507317428,
     'instanceid':12305,
     'level':28,
     'instorage':True
    },
    {'classid':1210468448,
     'instanceid':12306,
     'level':21,
     'instorage':True
    },
]

BROADCASTS = [
    { 'Id':1,
      'Title':'Test1',
      'Messages':[BroadcastMessage('RU','Tekst testovoi rassilki'),
                  BroadcastMessage('EN','Test broadcast message'),
                  BroadcastMessage('TR','Djevuschka djevuschka kuda zhe vi??')],
      'TimeStart': 1389542068,
      'TimeFinish':1389642068,
      'Interval':300,
      'EnabledNow':False,
    },
]

COMMONEVENTS = [
    {
        'persistentId': 100,
        'type' : 0,
        'startTime': 1428839400,
        'endTime': 1428926400,
        'enabled': False,
        'description': 'texraboti',
    },
    {
        'persistentId': 101,
        'type' : 1,
        'startTime': 1428839400,
        'endTime': 1428926400,
        'enabled': True,
        'description': 'custom event',
    },
    {
        'persistentId': 102,
        'type' : 2,
        'startTime': 1428839400,
        'endTime': 1428926400,
        'enabled': False,
        'description': 'event map',
    },
    {
        'persistentId': 103,
        'type' : 3,
        'startTime': 1428839400,
        'endTime': 1428926400,
        'enabled': True,
        'description': 'talent rarity',
    },
    {
        'persistentId': 104,
        'type' : 4,
        'startTime': 1428849400,
        'endTime': 1428936400,
        'enabled': False,
        'description': 'news banner',
    },
    {
        'persistentId': 105,
        'type' : 5,
        'startTime': 1428859400,
        'endTime': 1428946400,
        'enabled': True,
        'description': 'skin price',
    },
    {
        'persistentId': 106,
        'type' : 6,
        'startTime': 1428859400,
        'endTime': 1428946400,
        'enabled': False,
        'description': 'hero price',
    },
    {
        'persistentId': 107,
        'type' : 7,
        'startTime': 1428859400,
        'endTime': 1428946400,
        'enabled': True,
        'description': 'transmutation',
    }
]

DEFAULTSKINPRICES = [
    {
        'persistentId': 'healer_s1_A',
        'heroClassId': 1617033593,
        'price': 199,
    },
    {
        'persistentId': 'healer_s1_B',
        'heroClassId': 1617033593,
        'price': 299,
    },
    {
        'persistentId': 'mowgly_s2_A',
        'heroClassId': 1160508680,
        'price': 49,
    },
    {
        'persistentId': 'mowgly_s3_A',
        'heroClassId': 1160508680,
        'price': 99,
    },
    {
        'persistentId': 'unicorn_korovushka',
        'heroClassId': 1492899903,
        'price': 499,
    },
]


DEFAULTHEROPRICES = [
    {
        'heroClassId': -129083474,
        'silverPrice': 101000,
        'goldPrice': 101,
    },
    {
        'heroClassId': -1465956636,
        'silverPrice': 202000,
        'goldPrice': 202,
    },
    {
        'heroClassId': 242966457,
        'silverPrice': 303000,
        'goldPrice': 303,
    },
    {
        'heroClassId': 22648455,
        'silverPrice': 404000,
        'goldPrice': 404,
    },
    {
        'heroClassId': -1139813982,
        'silverPrice': 505000,
        'goldPrice': 505,
    },

]



class AccountManagementHandler:

    def __init__(self, accounts, sessions, heroes, guilds, skins, talents, buildings, broadcasts, commonevents, defaultskinprices, defaultheroprices):
        self.accounts = [AccountInfo(**account) for account in accounts]
        self.sessions = [GameSessionShortInfo(**session) for session in sessions]
        self.heroes = heroes
        for k,v in self.heroes.items():
            self.heroes[k] = [hero for hero in v]
        self.guilds = [GuildInfo(**guild) for guild in guilds]
        self.skins = [SkinInfo(**skin) for skin in skins]
        self.talents = [TalentInfo(**talent) for talent in talents]
        self.buildings = [BuildingInfo(**building) for building in buildings]
        self.broadcasts = [BroadcastInfo(**broadcast) for broadcast in broadcasts]
        self.commonevents = [CommonEventInfo(**e) for e in commonevents]
        self.defaultskinprices = [SkinGoldPrice(**p) for p in defaultskinprices]
        self.defaultheroprices = [HeroPrice(**p) for p in defaultheroprices]

    def GetSocServerVersion(self):
        return SocServerVersionResponse(RequestResult.Success, 'dummy server, don\'t take it serious')

    def GetAccountBySNUid(self, snid, snuid):
        for account in self.accounts:
            if account.snid == snid and account.snuid == snuid:
                return AccountInfoResponse(0, account)
        return NickSnidResponse(RequestResult.SnUidNotExist)

    def GetLocaleInfoBySNUid(self, snid, snuid):
        print 'GetLocaleInfoBySNUid', snid, snuid
        for account in self.accounts:
            if account.snid == snid and account.snuid == snuid:
                return LocaleInfoResponse(0, LocaleInfo(account.locale, account.muid))
        return(RequestResult.LoginNotExist, LocaleInfo())

    def GetLocaleInfoByAuid(self, auid):
        print 'GetLocaleInfoByAuid', auid
        for account in self.accounts:
            if account.auid == auid:
                return LocaleInfoResponse(0, LocaleInfo(account.locale, account.muid))
        return(RequestResult.LoginNotExist, LocaleInfo())

    def GetSocialNetworks(self):
        print 'GetSocialNetworks()'
        return SocialNetworksResponse(RequestResult.Success, ['fb', 'vk', 'pwc'])

    def GetAccountByAuid(self, auid):
        for account in self.accounts:
            if account.auid == auid:
                for guild in self.guilds:
                    if any(m for m in guild.members if m.auid == account.auid) or guild.leaderauid == account.auid:
                        account.guildid = guild.guildid
                        account.guildFullName = guild.fullname
                        break
                return AccountInfoResponse(0, account)
        return AccountInfoResponse(RequestResult.AuidNotExist)

    def FindNicknameExact(self, nickname):
        for account in self.accounts:
            if account.nickname == nickname:
                return NickSnidResponse(0, AccountShortInfo(account.snid, account.snuid, account.login, account.email, account.nickname))
        return NickSnidResponse(RequestResult.LoginNotExist)

    def GetGameSession(self, sessionid):
        for session in self.sessions:
            if session.sessionid == sessionid:
                return session
        return None

    def GetAccountLibrary(self, login):
        for account in self.accounts:
            if account.login == login and account.auid == 1:
                return LibraryResponse(0, self.talents)
        return LibraryResponse(0, [])

    def AddTalents(self, login, talentIds, gmLogin):
        print 'AddTalents', login, talentIds, gmLogin
        return RequestResult.Success

    def GetHeroTalentSet(self, login, heroInstanceId):
        for account in self.accounts:
            if account.login == login and account.auid == 1:
                return TalentSetResponse(0, [t for t in self.talents if t.boundHeroInstanceId == heroInstanceId])
        return TalentSetResponse(0, [])

    def EditTalent(self, login, talentEdit, gmLogin):
        return 0

    def GetAccountHeroes(self, login):
        for account in self.accounts:
            if account.login == login: 
                return HeroesResponse(0, self.heroes[account.auid]) 
        return None

    def EditAccount(self, snid, snuid, edit):
        account = self.GetAccountBySNUid(snid, snuid)
        if account != None:
            account.fullname = edit.fullname
            account.gold = edit.gold
            account.silver = edit.silver
            account.prime = edit.prime
            account.materials = edit.materials
            return 0
        return -1

    def EditHero(self, login, edit, gmlogin):
        for account in self.accounts:
            if account.login == login: 
                for hero in self.heroes[account.auid]:
                    if hero.heroClassId == edit.heroClassId:
                        hero.experience = edit.experience
                        hero.rating = edit.rating
                        return RequestResult.Success
        return RequestResult.BadResult

    def GetAccountSkins(self, auid):
        return SkinsResponse(0, auid, self.skins)

    def AddSkin(self, auid, skinPersistentId, gmLogin):
        print auid, skinPersistentId, gmLogin
        return RequestResult.Success

    def DeleteSkin(self, auid, skinPersistentId, gmLogin):
        print auid, skinPersistentId, gmLogin
        return RequestResult.Success

    def GetAccountBuildings(self, auid):
        if auid != 1:
            return BuildingsInfoResponse(RequestResult.BadResult)
        return BuildingsInfoResponse(0, auid, self.buildings)

    def MoveBuildingToStorage(self, auid, buildingInstanceId, gmLogin):
        print 'MoveBuildingToStorage', auid, buildingInstanceId, gmLogin
        return RequestResult.Success

    def AddBuilding(self, auid, buildingClassId, level, gmLogin):
        print 'AddBuilding', auid, buildingClassId, level, gmLogin
        return RequestResult.Success

    def DeleteBuilding(self, auid, buildingInstanceId, gmLogin):
        print 'DeleteBuilding', auid, buildingInstanceId, gmLogin
        return RequestResult.Success

    def DisjointSN(self, auid, snid):
        print 'DisjointSN', auid, snid
        return RequestResult.Success

    def GetGuildById(self, guildid):
        for guild in self.guilds:
            if guild.guildid == guildid:
                return GuildInfoResponse(0, guild)
        return GuildInfoResponse(RequestResult.BadResult)

    def GetGuildByName(self, shortname, fullname):
        for guild in self.guilds:
            if guild.shortname == shortname or guild.fullname == fullname:
                return GuildInfoResponse(0, guild)
        return GuildInfoResponse(RequestResult.BadResult)

    def EditGuild(self, guild, gmLogin):
        for edited_guild in self.guilds:
            if edited_guild.guildid == guild.guildid:
                if guild.shortname is not None and guild.shortname != '':
                    edited_guild.shortname = guild.shortname
                if guild.fullname is not None and guild.fullname != '':
                    edited_guild.fullname = guild.fullname
                if guild.messageoftheday is not None and guild.messageoftheday != '':
                    edited_guild.messageoftheday = guild.messageoftheday
                if guild.guildExperience is not None:
                    edited_guild.guildExperience = guild.guildExperience
                if guild.cwguildpoints is not None:
                    edited_guild.cwguildpoints = guild.cwguildpoints
                return RequestResult.Success
        return RequestResult.BadResult
    
    def ChangeGuildOfficers(self, guildid, members):
        for guild in self.guilds:
            if guild.guildid == guildid:
                for editmember in members:
                    for guildmember in guild.members:
                        if guildmember.auid == editmember.auid:
                            guildmember.isofficer = editmember.isofficer
                return RequestResult.Success
        return RequestResult.BadResult

    def AddGuildMembers(self, guildid, auids):
        for guild in self.guilds:
            if guild.guildid == guildid:
                for newauid in auids:
                    for a in self.accounts:
                        if a.auid == newauid:
                            guild.members.append(GuildMemberInfo(a.auid, a.nickname))
                            break
                return RequestResult.Success
        return RequestResult.BadResult

    def RemoveGuildMembers(self, guildid, auids):
        for guild in self.guilds:
            if guild.guildid == guildid:
                guild.members = [m for m in guild.members if m.auid not in auids]
                return RequestResult.Success
        return RequestResult.BadResult

    def ChangeGuildLeader(self, guildid, auid):
        for guild in self.guilds:
            if guild.guildid == guildid:
                for m in guild.members:
                    if m.auid == auid:
                        acc, = (a2 for a2 in self.accounts if a2.auid == guild.leaderauid)
                        guild.members.append(GuildMemberInfo(acc.auid, acc.nickname, False))
                        guild.members = [m2 for m2 in guild.members if m2.auid != auid]
                        guild.leaderauid = m.auid
                        guild.leadernickname = m.nickname
                        return RequestResult.Success
        return RequestResult.BadResult

    def SetGuildIcon(self, guildid, image):
        for x in image:
            print x
        return RequestResult.Success

    def EditAccountDbValue(self, login, gmLogin, key, value):
        for account in self.accounts:
            if account.login == login: 
                if key == 'IsSpectator':
                    account.isSpectator = value == 'yes'
                    return RequestResult.Success
        return RequestResult.BadResult


    def PayService(self, login, servicetype, paramValue):
        print 'PayService', login, servicetype, paramValue
        return RequestResult.Success

    def UserOperation(self, type, auid, minutes, reason, claims, gmLogin):
        print 'UserOperation', type, auid, minutes, reason, claims, gmLogin
        return RequestResult.Success


    def GetBroadcastLocales(self):
        return BroadcastLocalesResponse(RequestResult.Success, ['RU', 'EN', 'TR', 'DE', 'ES', 'FR'])

    def GetBroadcastList(self, skipLines, takeLines):
        print 'GetBroadcastList', skipLines, takeLines
        return BroadcastListResponse(RequestResult.Success, self.broadcasts * 30)

    def CreateBroadcast(self, createInfo, gmLogin):
        print 'CreateBroadcast', createInfo, gmLogin
        return BroadcastCreateResponse(RequestResult.Success,2)

    def EditBroadcast(self, editInfo, gmLogin):
        print 'EditBroadcast', editInfo, gmLogin
        return RequestResult.Success

    def DeleteBroadcast(self, id, gmLogin):
        print 'DeleteBroadcast', id, gmLogin
        return RequestResult.Success

    def StartMessageRotation(self, id, gmLogin):
        print 'StartMessageRotation', id, gmLogin
        return RequestResult.Success

    def StopMessageRotation(self, id, gmLogin):
        print 'StopMessageRotation', id, gmLogin
        return RequestResult.Success

    def BindToGeolocation(self, auid, country, region, city, gmlogin):
        print 'BindToGeolocation', auid, country, region, city, gmlogin
        return RequestResult.Success

    def AcquireGuildLock(self, guildid, gmlogin):
        print 'AcquireGuildLock', guildid, gmlogin
        for guild in self.guilds:
            if guild.guildid == guildid:
                guild.releaselocktime = 1
                return RequestResult.Success
        return RequestResult.BadResult

    def ReleaseGuildLock(self, guildid, gmlogin):
        print 'ReleaseGuildLock', guildid, gmlogin
        for guild in self.guilds:
            if guild.guildid == guildid:
                guild.releaselocktime = 0
                return RequestResult.Success
        return RequestResult.BadResult

    def StopGuildSiege(self, guildid, gmlogin):
        print 'StopGuildSiege', guildid, gmlogin
        for guild in self.guilds:
            if guild.guildid == guildid:
                guild.siegeendtime = 0
                return RequestResult.Success
        return RequestResult.BadResult

    def AddGuildSuzerain(self, guildid, suzerainguildid, gmlogin):
        print 'AddGuildSuzerain', guildid, suzerainguildid, gmlogin
        for guild in self.guilds:
            if guild.guildid == guildid:
                if guild.suzerain.guildid == -1:
                    for suzerainguild in self.guilds:
                        print suzerainguild.guildid
                        print suzerainguildid
                        if suzerainguild.guildid == suzerainguildid:
                            guild.suzerain.guildid = suzerainguild.guildid
                            guild.suzerain.shortname = suzerainguild.shortname
                            guild.suzerain.fullname = suzerainguild.fullname
                            suzerainguild.vassals.append(GuildShortInfo(guild.guildid, guild.shortname, guild.fullname))
                return RequestResult.Success
        return RequestResult.BadResult

    def RemoveGuildSuzerain(self, guildid, gmlogin):
        print 'RemoveGuildSuzerain', guildid, gmlogin
        for guild in self.guilds:
            if guild.guildid == guildid:
                if guild.suzerain.guildid != -1:
                    for suzerainguildid in self.guilds:
                        if suzerainguildid.guildid == guild.suzerain.guildid:
                            guild.suzerain.guildid = -1
                            guild.suzerain.shortname = ''
                            guild.suzerain.fullname = ''
                            for vassal in suzerainguildid.vassals:
                                if vassal.guildid == guild.guildid:
                                    suzerainguildid.vassals.remove(vassal)
                                    return RequestResult.Success
        return RequestResult.BadResult


    # Event tool methods

    def GetAvailableEvents(self):
        print 'GetAvailableEvents'
        return CommonEventsListResponse(RequestResult.Success, self.commonevents)

    def ChangeEventStateById(self, persistentId, state):
        print 'ChangeEventStateById', persistentId, state
        return RequestResult.Success

    def DeleteEventById(self, persistentId):
        print 'DeleteEventById', persistentId
        return RequestResult.Success

    def GetSkinPrices(self):
        print 'GetSkinPrices'
        return SkinGoldPricesResponse(RequestResult.Success, [], self.defaultskinprices)

    def GetSkinPriceById(self, persistentId):
        print 'GetSkinPriceById', persistentId
        e = SkinGoldPriceEvent(persistentId, [SkinGoldPrice('healer_s1_A', 1617033593, 166), SkinGoldPrice('unicorn_korovushka', 1492899903, 466)], 1428839400, 1428926400, True, 'test skin price event')
        return SkinGoldPriceByIdResponse(RequestResult.Success, e, self.defaultskinprices)

    def AddSkinPricesEvent(self, skinEvent):
        print "AddSkinPricesEvent", skinEvent
        return RequestResult.Success

    def EditSkinPricesEvent(self, skinEvent):
        print "EditSkinPricesEvent", skinEvent
        return RequestResult.Success

    def GetHeroPrices(self):
        print "GetHeroPrices"
        return HeroPricesResponse(RequestResult.Success, [], self.defaultheroprices)

    def GetHeroPriceById(self, persistentId):
        print 'GetHeroPriceById', persistentId
        e = HeroPriceEvent(persistentId, [HeroPrice('',22648455,765432,1012),HeroPrice('',-1465956636,654321,997)], 1428839400, 1428926400, False, 'test hero price event')
        return HeroPriceByIdResponse(RequestResult.Success, e, self.defaultheroprices)

    def AddHeroPricesEvent(self, skinEvent):
        print "AddHeroPricesEvent", skinEvent
        return RequestResult.Success

    def EditHeroPricesEvent(self, skinEvent):
        print "EditHeroPricesEvent", skinEvent
        return RequestResult.Success

    def GetCustomEventById(self, persistentId):
        print 'GetCustomEventById', persistentId
        return CustomEventByIdResponse(RequestResult.Success, CustomEvent(persistentId, 'some type', 1428839400, 1428926400, True, 'description for custom event'))

    def AddCustomEvent(self, customEvent):
        print 'AddCustomEvent', customEvent
        return RequestResult.Success

    def EditCustomEvent(self, customEvent):
        print 'EditCustomEvent', customEvent
        return RequestResult.Success

    def GetTechsInfoById(self, persistentId):
        print 'GetTechsInfoById', persistentId
        return TechsInfoByIdResponse(RequestResult.Success, TechsInfo(persistentId, 1428839400, 1428926400, 'some ugly type', 3211, 'techs description'))

    def AddTechs(self, techInfo):
        print 'AddTechs', techInfo
        return RequestResult.Success

    def EditTechs(self, techInfo):
        print 'EditTechs', techInfo
        return RequestResult.Success

    def GetCustomMapById(self, persistentId):
        print 'GetCustomMapById', persistentId
        return CustomMapByIdResponse(RequestResult.Success, CustomMap(persistentId, 1428839400, 1428926400, 'MO', '13', '15', '/Maps/MOBA/_.ADMPS', 'mtype', True, False, 'short about info'))

    def AddCustomMap(self, customMap):
        print 'AddCustomMap', customMap
        return RequestResult.Success

    def EditCustomMap(self, customMap):
        print 'EditCustomMap', customMap
        return RequestResult.Success

    def GetTalentDropRarities(self, premium):
        print 'GetTalentDropRarities', premium
        return TalentDropRaritiesResponse(RequestResult.Success, [], TalentDropRarity(0,0,45,40,10,5), TalentDropRarity(0,0,0,70,20,10))

    def GetTalentDropRarityById(self, premium, persistentId):
        print 'GetTalentDropRarityById', premium, persistentId
        return TalentDropRarityByIdResponse(RequestResult.Success, TalentDropRarityEvent(persistentId,TalentDropRarity(0,0,30,30,25,15), 1428839400, 1428926400, True, 'some drops info', False), TalentDropRarity(0,0,45,40,10,5), TalentDropRarity(0,0,0,70,20,10))

    def AddTalentDropRarities(self, dropRarity):
        print 'AddTalentDropRarities', dropRarity
        return RequestResult.Success

    def EditTalentDropRarities(self, dropRarity):
        print 'EditTalentDropRarities', dropRarity
        return RequestResult.Success

    def GetNewsBannerById(self, persistentId):
        print 'GetTechsInfoById', persistentId
        return NewsBannerByIdResponse(RequestResult.Success, NewsBanner(persistentId, 'button text', 'window caption', 'button url', 'main url', 'tooltip', 'mainUrl B!', 'Login netw', 13, True, 1428839400, 1428926400, 'EU', True, 'mega interesting banner'))

    def AddNewsBanner(self, banner):
        print 'AddNewsBanner', banner
        return RequestResult.Success

    def EditNewsBanner(self, banner):
        print 'EditNewsBanner', banner
        return RequestResult.Success

    def GetTransmutationTalentsPerPerl(self):
        print 'GetTransmutationTalentsPerPerl'
        return TransmutationTalentsPerPerlResponse(RequestResult.Success, [], 2)

    def GetTransmutationTalentsPerPerlById(self, persistentId):
        print 'GetTransmutationTalentsPerPerlById', persistentId
        return TransmutationTalentsPerPerlByIdResponse(RequestResult.Success, TransmutationTalentsPerPerl(persistentId, 4, 1428839400, 1428926400, False, 'more talents pls'), 2)

    def AddTalentPerPerlEvent(self, talentsPerPerlEvent):
        print 'AddTalentPerPerlEvent', talentsPerPerlEvent
        return RequestResult.Success

    def EditTalentPerPerlEvent(self, talentsPerPerlEvent):
        print 'EditTalentPerPerlEvent', talentsPerPerlEvent
        return RequestResult.Success



def GetParams():
    handler = AccountManagementHandler(ACCOUNTS, SESSIONS, HEROES, GUILDS, SKINS, TALENTS, BUILDINGS, BROADCASTS, COMMONEVENTS, DEFAULTSKINPRICES, DEFAULTHEROPRICES)
    processor = AccountManagement.Processor(handler)
    return { 'processor' : processor, 'types' : AccountManagementAPI.ttypes }
