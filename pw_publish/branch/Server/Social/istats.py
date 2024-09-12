# -*- coding: utf-8 -*-

import time
from functools import partial

from base.helpers import info, warn, bad_warn, json_dumps, jsonResult, toint, tolong, err, debug, catch, http_prefix, toint32
from base.wstools import AddLoopCallback, RemoveLoopCallback

from tornado.httpclient import HTTPRequest
from modeldata.StaticData import StaticData
# --------------------------------------------------------------------------------------------

RESEND_PERIOD = (0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55)
PERIODS = len(RESEND_PERIOD)

class IStats:
    _THRIFT_TYPES = [
        "LoginUsers",
        "LogoutUsers",
        "MoveTalentToSet",
        "MoveTalentFromSet",
        "UnlockHero",
        "JoinPvpSession",
        "ChatMessages",
        "BanUser",
        "MuteUser",
        "ModeratorMuteUser",
        "UnbanUser",
        "UnmuteUser",
        "ForgiveUser",
        "SetLeaveUser",
        "GMEditUser",
        "GMUnlockHero",
        "GMLockHero",
        "MonitoringResults",
        "AddIgnore",
        "RemoveIgnore",
        'MoveHeroToBath',
        'GiveSessionAwards',
        'LauncherStart',
        'LauncherDActions',
        'LauncherEvents',
        'SocialRegister',
        'SocialJoin',
        'SocialMerge',
        'ResourcesChange',
        'QuestChange',
        'DynamicQuestChange',
        'TournamentQuestChange',
        'TutorialStateChange',
        'TalentChange',
        'FactionSelect',
        'RatingChange',
        'GuildCreated',
        'GuildRenamed',
        'GuildJoined',
        'GuildLeaved',
        'GuildDisbanded',
        'ClientPings',
        'RuneExpire',
        'RuneUnsoulbound',
        'RuneReplenish',
        'RuneHeroApply',
        'GMOperation',
        'GMUserOperation',
        'UserClaims',
        'CastleLevelChange',
        'HeroLevelChange',
        'HeroRankChange',
        'GuildShopBuy',
        'GuildDailyStats',
        'GuildInteraction',
        'GuildSiege',
        'GuildPointsChange',
        'AfterParty',
        'LeaverPointsChange',
        'RuneRoll',
        'ReRollShop',
        'GWEventAdd',
        'GWScoreChange',
        'QuestEventStageChange',
        'QuestEventStateChange',
    ]
    
    def __init__(self, url, iDict):
        self.url = http_prefix( url )
        self.I = iDict

        for ttypename in self._THRIFT_TYPES:
            setattr( self, ttypename, [] )
        
    #----------------------------------------------------
    
    def addLogin(self, *args, **kwargs):
        pass
    def addLogout(self, *args, **kwargs):
        pass
    def addMoveTalentToSet(self, *args, **kwargs):
        pass
    def addMoveTalentFromSet(self, *args, **kwargs):
        pass
    def addUnlockHero(self, *args, **kwargs):
        pass
    def addJoinPvpSession(self, *args, **kwargs):
        pass
    def addChatMessages(self, *args, **kwargs):
        pass
    def addBanUser(self, *args, **kwargs):
        pass
    def addMuteUser(self, *args, **kwargs):
        pass
    def addModeratorMuteUser(self, *args, **kwargs):
        pass
    def addUnbanUser(self, *args, **kwargs):
        pass
    def addUnmuteUser(self, *args, **kwargs):
        pass
    def addSetLeaveUser(self, *args, **kwargs):
        pass
    def addGMEditUser(self, *args, **kwargs):
        pass
    def addGMUnlockHero(self, *args, **kwargs):
        pass
    def addGMLockHero(self, *args, **kwargs):
        pass
    def addMonitoringResults(self, *args, **kwargs):
        pass
    def addAddIgnore(self, *args, **kwargs):
        pass
    def addRemoveIgnore(self, *args, **kwargs):
        pass
    def addGiveSessionAwards(self, *args, **kwargs):
        pass
    def addLauncherStart(self, *args, **kwargs):
        pass
    def addLauncherEvents(self, *args, **kwargs):
        pass
    def addLauncherDActions(self, *args, **kwargs):
        pass
    def addLauncherRegister(self, *args, **kwargs):
        pass
    def addLauncherJoin(self, *args, **kwargs):
        pass
    def addLauncherMerge(self, *args, **kwargs):
        pass
    def addResourcesChange( self, *args, **kwargs):
        pass
    def addQuestChange( self, *args, **kwargs):
        pass
    def addDynamicQuestChange( self, *args, **kwargs):
        pass
    def addTournamentQuestChange( self, *args, **kwargs):
        pass
    def addTutorialStateChange( self, *args, **kwargs):
        pass
    def addTalentChange( self, *args, **kwargs):
        pass
    def addFactionSelect(self, *args, **kwargs):
        pass
    def addRatingChange(self, *args, **kwargs):
        pass
    def addHeroLevelChange(self, *args, **kwargs):
        pass
    def addHeroRankChange(self, *args, **kwargs):
        pass
    def addCastleLevelChange(self, *args, **kwargs):
        pass
    def addGuildCreated(self, *args, **kwargs):
        pass
    def addGuildRenamed(self, *args, **kwargs):
        pass
    def addGuildJoined(self, *args, **kwargs):
        pass
    def addGuildLeaved(self, *args, **kwargs):
        pass
    def addGuildDisbanded(self, *args, **kwargs):
        pass
    def addClientPing(self, *args, **kwargs):
        pass
    def addRuneExpire(self, *args, **kwargs):
        pass
    def addRuneUnsoulbound(self, *args, **kwargs):
        pass
    def addRuneReplenish(self, *args, **kwargs):
        pass
    def addRuneHeroApply(self, *args, **kwargs):
        pass
    def addGMOperation(self, *args, **kwargs):
        pass
    def addGMUserOperation(self, *args, **kwargs):
        pass
    def addUserClaim(self, *args, **kwargs):
        pass
    def addBuyGuildShopItem(self, *args, **kwargs):
        pass
    def addGuildDailyStatsInfo(self, *args, **kwargs):
        pass
    def addGuildInteraction(self, *args, **kwargs):
        pass
    def addGuildPointsChange(self, guildid, auid, source, playerpointschange, playerpointstotal, guildpointschange,
                             guildpointstotal):
        pass
    def addAfterParty(self, *args, **kwargs):
        pass
    def addLeaverPointsChange(self, *args, **kwargs):
        pass
    def addLampRoll( self, *args, **kwargs):
        pass
    def addGWEvent( self, *args, **kwargs):
        pass
    def addGWScoreChange( self, *args, **kwargs):
        pass
    def questEventStageChange( self, *args, **kwargs):
        pass
    def questEventStateChange( self, *args, **kwargs):
        pass
    #----------------------------------------------------
    def addReRollShop(self, *args, **kwargs):
        pass
  
    def Send(self, *args, **kwargs):
        pass

# --------------------------------------------------------------------------------------------

class StatsAgent(IStats):

    def __init__(self, url, iDict, resend_pool_limit = 10000):
        IStats.__init__(self, url, iDict)
        self.resend_pool_limit = resend_pool_limit
        self.sent = dict()
        self.resend = dict()

    def addLogin(self, auid, nick, servername, ip, fraction, fractionselected, isdeveloper, locale, guildid,
                 guildshortname, guildfullname, leaverpoints, isleaver):
        self.LoginUsers.append(dict(auid=tolong(auid), nick=nick, timestamp=int(time.time()), server=servername, ip=ip,
                                    faction=fraction, factionselected=fractionselected, isdeveloper=isdeveloper,
                                    locale=locale, guildid=guildid, guildshortname=guildshortname,
                                    guildfullname=guildfullname, leaverpoints=leaverpoints, isleaver=isleaver))
        #~ 1: i64 auid // это везде auid
        #~ 2: string nick // nickname
        #~ 3: string server // one 
        #~ 4: string cluster // имя кластера (?)
        #~ 5: i32 timestamp // unixtime
        #~ 6: string ip // remote_ip юзера (из HTTP-заголовка)
        #~ 7: string faction // фракция: A - докты, B - адорнийцы
        #~ 8: bool factionselected // выбирал ли игрок фракцию перед логином
        #~ 9: bool isdeveloper // разработчик или нет
        #~ 10: string locale // локаль игрока
        #~ 11: i64 guildid  // auid гильдии
        #~ 12: string guildshortname // аббревиатура гильдии
        #~ 13: string guildfullname // полное название гильдии
        #~ 13: i32 leaverpoints // очки лива
        #~ 13: bool isleaver // ливер или нет
    
    def addLogout(self, auid, nick, servername):
        self.LogoutUsers.append( dict( auid=tolong(auid), nick=nick, timestamp=int(time.time()), server=servername ))
        #~ 1: i64 auid // это везде auid
        #~ 2: string nick // nickname
        #~ 3: string server // one 
        #~ 4: string cluster // имя кластера (?)
        #~ 5: i32 timestamp // unixtime
  
    ## void MoveTalentToSet(1:list<MoveTalentInfo> infos),
    def addMoveTalentToSet(self, auid, nick, talentid, heroid, slot):
        self.MoveTalentToSet.append( dict( auid=tolong(auid), nick=nick, talentid=toint(talentid), heroid=toint(heroid), slot=toint(slot), timestamp=int(time.time()) ))
        #~ 1: i64 auid
        #~ 2: string nick
        #~ 3: i32 talentid // CRC32 signed
        #~ 4: i32 heroid // CRC32 signed
        #~ 5: byte slot
        #~ 6: i32 timestamp
        
    ## void MoveTalentFromSet(1:list<MoveTalentInfo> infos),
    def addMoveTalentFromSet(self, auid, nick, talentid, heroid, slot):
        self.MoveTalentFromSet.append( dict( auid=tolong(auid), nick=nick, talentid=toint(talentid), heroid=toint(heroid), slot=toint(slot), timestamp=int(time.time()) ))
        #~ 1: i64 auid
        #~ 2: string nick
        #~ 3: i32 talentid // CRC32 signed
        #~ 4: i32 heroid // CRC32 signed
        #~ 5: byte slot
        #~ 6: i32 timestamp
        
    ## void UnlockHero(1:list<UnlockHeroInfo> infos),
    def addUnlockHero(self, auid, heroid, rchange, rtotal):
        change = dict( Gold=rchange.Gold, Silver=rchange.Silver, Perl=rchange.Perl, RedPerl=rchange.RedPerl, Population=rchange.Population, Resource1=rchange.Resource1, Resource2=rchange.Resource2, Resource3=rchange.Resource3, Shard=rchange.Shard )
        total = dict( Gold=rtotal.Gold, Silver=rtotal.Silver, Perl=rtotal.Perl, RedPerl=rtotal.RedPerl, Population=rtotal.Population, Resource1=rtotal.Resource1, Resource2=rtotal.Resource2, Resource3=rtotal.Resource3, Shard=rtotal.Shard )
        self.UnlockHero.append( dict( auid=tolong(auid), heroid=toint(heroid), rchange=change, rtotal=total, timestamp=int(time.time()) ))
        #~ 1: i64 auid
        #~ 2: i32 heroid
        #~ 3: struct rchange
        #~ 4: struct rtotal
        #~ 5: i32 timestamp

    ## void JoinPvpSession(1:list<JoinSessionInfo> infos),
    def addJoinPvpSession(self, auid, gameid, heroid, talent_id_list, guildbuffs_id_list, guild_war_event_pass):
        self.JoinPvpSession.append( dict( auid=tolong(auid), sessionpersistentid=tolong(gameid), heroid=toint(heroid),
                                          talentset=talent_id_list, guildbuffs=guildbuffs_id_list,
                                          guildwareventpass=guild_war_event_pass,
                                          timestamp=int(time.time())
                                        ))
        #~ 1: i64 auid
        #~ 2: string nick
        #~ 3: i32 heroid
        #~ 4: list<i32> talentset // список PersistentId, по порядку слотов
        #~ 5: list<i32> guildbuffs // список клановых бафов, аффектящих сессию
        #~ 6: int guildwareventpass
        #~ 7: i32 timestamp

    ## void ChatMessages(1:list<ChatMessageInfo> infos),
    def addChatMessages(self, auid, channel, message):
        self.ChatMessages.append(dict(auid=tolong(auid), channel=channel, message=message, timestamp=int(time.time())))
        #~ 1: i64 auid
        #~ 2: i32 timestamp
        #~ 3: string channel
        #~ 4: string message

    ##  GMMuteBanInfo: __init__(self, auid=None, gmlogin=None, minutes=None, reason=None, timestamp=None,):
    def addBanUser(self, auid, gmlogin, minutes, reason, claimIds):
        self.BanUser.append(dict(auid=tolong(auid), gmlogin=gmlogin, minutes=minutes, reason=reason, claimIds=claimIds, timestamp=int(time.time())))
        #~ 1: i64 auid
        #~ 2: string gmlogin
        #~ 3: i32 minutes
        #~ 4: string reason
        #~ 5: list claimIds
        #~ 6: i32 timestamp
        
    ## void MuteUser(1:list<GMMuteBanInfo> infos),
    def addMuteUser(self, auid, gmlogin, minutes, reason, claimIds):
        self.MuteUser.append(dict(auid=tolong(auid), gmlogin=gmlogin, minutes=minutes, reason=reason, claimIds=claimIds, timestamp=int(time.time())))
        #~ 1: i64 auid
        #~ 2: string gmlogin
        #~ 3: i32 minutes
        #~ 4: string reason
        #~ 5: list claimIds
        #~ 6: i32 timestamp

    ## void MuteUser(1:list<GMMuteBanInfo> infos),
    def addModeratorMuteUser(self, auid, gmlogin, minutes, reason):
        self.ModeratorMuteUser.append(dict(auid=tolong(auid), gmlogin=gmlogin, minutes=minutes, reason=reason, claimIds=[], timestamp=int(time.time())))
        #~ 1: i64 auid
        #~ 2: string gmlogin
        #~ 3: i32 minutes
        #~ 4: string reason
        #~ 5: list claimIds
        #~ 6: i32 timestamp
        
    ## void UnbanUser(1:list<GMUserInfo> infos),
    def addUnbanUser(self, auid, gmlogin):
        self.UnbanUser.append(dict( auid=tolong(auid), gmlogin=gmlogin, timestamp=int(time.time())))
        #~ 1: i64 auid
        #~ 2: string gmlogin
        #~ 3: i32 timestamp  
        
    ## void UnmuteUser(1:list<GMUserInfo> infos),
    def addUnmuteUser(self, auid, gmlogin):
        self.UnmuteUser.append(dict(auid=tolong(auid), gmlogin=gmlogin, timestamp=int(time.time())))
        #~ 1: i64 auid
        #~ 2: string gmlogin
        #~ 3: i32 timestamp  

    ## void ForgiveUser(1:list<GMMuteBanInfo> infos),
    def addForgiveUser(self, auid, gmlogin, reason, claimIds):
        self.ForgiveUser.append(dict(auid=tolong(auid), gmlogin=gmlogin, reason=reason, claimIds=claimIds, timestamp=int(time.time())))
        #~ 1: i64 auid
        #~ 2: string gmlogin
        #~ 5: list claimIds


    def addSetLeaveUser(self, auid, gmlogin, reason, points, claimIds):
        self.SetLeaveUser.append(dict(auid=tolong(auid), gmlogin=gmlogin, reason=reason, points=points, claimIds=claimIds, timestamp=int(time.time())))
        #~ 1: i64 auid
        #~ 2: string gmlogin
        #~ 8: i32 points


    ## void GMEditUser(1:list<GMEditFieldInfo> infos),
    def addGMEditUser(self, auid, gmlogin, field, oldvalue, newvalue):
        self.GMEditUser.append( dict( auid=tolong(auid), gmlogin=gmlogin, field=field, oldvalue=oldvalue, newvalue=newvalue, timestamp=int(time.time()) ))
        #~ 1: i64 auid
        #~ 2: string gmlogin
        #~ 3: i32 timestamp
        #~ 4: string field
        #~ 5: string oldvalue
        #~ 6: string newvalue

    ## void GMUnlockHero(1:list<GMHeroActionInfo> infos),
    def addGMUnlockHero(self, auid, gmlogin, heroid):
        self.GMUnlockHero.append( dict( auid=tolong(auid), gmlogin=gmlogin, heroid=toint(heroid), timestamp=int(time.time()) ))
        #~ 1: i64 auid
        #~ 2: string gmlogin
        #~ 3: i32 heroid
        #~ 4: i32 timestamp
        
    ## void GMLockHero(1:list<GMHeroActionInfo> infos),
    def addGMLockHero(self, auid, gmlogin, heroid):
        self.GMLockHero.append( dict( auid=tolong(auid), gmlogin=gmlogin, heroid=toint(heroid), timestamp=int(time.time()) ))
        #~ 1: i64 auid
        #~ 2: string gmlogin
        #~ 3: i32 heroid
        #~ 4: i32 timestamp

    ## void MonitoringResults(1:list<MonitoringResultInfo> results),
    def addMonitoringResults(self, property, counter, value):
        self.MonitoringResults.append( dict( property=property, counter=counter, value=toint(value), timestamp=int(time.time()) ))
        #~ 1: string property
        #~ 2: string counter
        #~ 3: i32 value
        #~ 4: i32 timestamp

    def addAddIgnore(self, auid, ignoreauid, reason):
        self.AddIgnore.append( dict( auid=tolong(auid), ignoreauid=tolong(ignoreauid), reason=reason, timestamp=int(time.time()) ))
        #~ 1: i64 auid
        #~ 2: i64 ignoreauid
        #~ 3: string reason
        #~ 4: i32 timestamp

    def addRemoveIgnore(self, auid, ignoreauid):
        self.RemoveIgnore.append( dict( auid=tolong(auid), ignoreauid=tolong(ignoreauid), timestamp=int(time.time()) ))
        #~ 1: i64 auid
        #~ 2: i64 ignoreauid
        #~ 3: i32 timestamp

    def addResourcesChange(self, auid, gain, source, _buildingname, _change, _total, _aftercontext = False, customCurrenciesOnly = False):
        if not StaticData.isValidPrice(_change):
            return
        if _aftercontext:
            _buildingname = _buildingname + " aftercontext"

        changeToSend = StaticData.copyPrice(_change, safe=True, customCurrenciesOnly=customCurrenciesOnly)
        totalToSend = StaticData.copyPrice(_total, safe=True, customCurrenciesOnly=customCurrenciesOnly)

        self.ResourcesChange.append(
            dict(auid=tolong(auid), gain=gain, source=source, buildingname=_buildingname, rchange=changeToSend,
                 rtotal=totalToSend, timestamp=int(time.time())))

        if len(changeToSend.Currencies) > 1:
            for key in changeToSend.Currencies.keys()[1:]:
                if key not in totalToSend.Currencies:
                    continue
                rchange = StaticData.emptyPrice()
                rchange.Currencies[key] = changeToSend.Currencies[key]

                rtotal = StaticData.emptyPrice()
                rtotal.Currencies[key] = totalToSend.Currencies[key]

                self.ResourcesChange.append(dict(auid=tolong(auid), gain=gain, source=source, buildingname=_buildingname, rchange=rchange, rtotal=rtotal, timestamp=int(time.time())))

        #~ (1, TType.I64, 'auid', None, None, ), # 1
        #~ (2, TType.BOOL, 'gain', None, None, ), # 2
        #~ (3, TType.I32, 'source', None, None, ), # 3
        #~ (4, TType.STRUCT, 'rchange', None, None, ), # 4
        #~ (5, TType.STRUCT, 'rtotal', None, None, ), # 5
        #~ (6, TType.I32, 'timestamp', None, None, ), # 6
    
    def addQuestChange(self, auid, questid, reason):
        #если это не стартовый квест.
        if questid != -1357395686:
            self.QuestChange.append( dict( auid=tolong(auid), questid=questid, reason = reason, timestamp=int(time.time() )) )
        #~ (1, TType.i64, 'auid', None, None, ), # 1
        #~ (2, TType.i32, 'questid', None, None, ), # 2
        #~ (3, TType.i32, 'reason', None, None, ), # 3
        #~ (4, TType.I32, 'timestamp', None, None, ), # 4

    def addDynamicQuestChange( self, auid, questindex, questname, reason, alternativeline):
        self.DynamicQuestChange.append( dict( auid=tolong(auid), questindex=questindex, questname=questname, reason=reason,
                                              timestamp=int(time.time()), alternativeline=alternativeline) )
        #~ (1, TType.i64, 'auid', None, None, ), # 1
        #~ (2, TType.i32, 'questindex', None, None, ), # 2
        #~ (3, TType.string, 'questname', None, None, ), # 3
        #~ (4, TType.i32, 'reason', None, None, ), # 4
        #~ (5, TType.I32, 'timestamp', None, None, ), # 5
        #~ (6, TType.bool, 'alternativeline', None, None, ), # 6

    def addTournamentQuestChange( self, auid, questindex, questname, reason, alternativeline):
        self.TournamentQuestChange.append( dict( auid=tolong(auid), questindex=questindex, questname=questname, reason=reason,
                                              timestamp=int(time.time()), alternativeline=alternativeline) )
        #~ (1, TType.i64, 'auid', None, None, ), # 1
        #~ (2, TType.i32, 'questindex', None, None, ), # 2
        #~ (3, TType.string, 'questname', None, None, ), # 3
        #~ (4, TType.i32, 'reason', None, None, ), # 4
        #~ (5, TType.I32, 'timestamp', None, None, ), # 5
        #~ (6, TType.bool, 'alternativeline', None, None, ), # 6

    def addTutorialStateChange(self, auid, tutorialstate):
        self.TutorialStateChange.append( dict( auid=tolong(auid), tutorialstate=tutorialstate, timestamp=int(time.time() )) )
        #~ (1, TType.i64, 'auid', None, None, ), # 1
        #~ (2, TType.string, 'tutorialstate', None, None, ), # 2
        #~ (3, TType.I32, 'timestamp', None, None, ), # 4

    def addTalentChange(self, auid, talent, operation, data=""):
        self.TalentChange.append(dict(auid=tolong(auid), talent=talent, operation=operation, timestamp=int(time.time()), data=data))
        #~ (1, TType.i64, 'auid', None, None, ), # 1
        #~ (2, TType.TalentInfo, 'talent', None, None, ), # 2
        #~ (3, TType.TalentChangeOperation, 'operation', None, None, ), # 3
        #~ (4, TType.I32, 'timestamp', None, None, ), # 4
        #~ (5, TType.string, 'data', "", "", ), # 5


    def addFactionSelect(self, auid, oldfaction, newfaction, _change, _total):
        change = dict( Gold=_change.Gold, Silver=_change.Silver, Perl=_change.Perl, RedPerl=_change.RedPerl, Population=_change.Population, Resource1=_change.Resource1, Resource2=_change.Resource2, Resource3=_change.Resource3, Shard=_change.Shard)
        total = dict( Gold=_total.Gold, Silver=_total.Silver, Perl=_total.Perl, RedPerl=_total.RedPerl, Population=_total.Population, Resource1=_total.Resource1, Resource2=_total.Resource2, Resource3=_total.Resource3, Shard=_total.Shard)
        self.FactionSelect.append( dict( auid=tolong(auid), oldfaction=oldfaction, newfaction=newfaction, rchange=change, rtotal=total, timestamp=int(time.time()) ) )

    def addRatingChange(self, auid, rating_type, game_id, hero_id, inc_rating, new_rating):
        #~ 1: i64 auid
        #~ 2: RatingType type
        #~ 3: i64 sessionpersistentid
        #~ 4: i32 heroid
        #~ 5: i32 rating_inc
        #~ 6: i32 rating_new
        #~ 7: i32 timestamp
        self.RatingChange.append( dict( auid=tolong(auid), type=rating_type, sessionpersistentid=tolong(game_id), heroid=toint(hero_id),
            rating_inc=toint(inc_rating), rating_new=toint(new_rating), timestamp=int(time.time()) ) )

    def addHeroLevelChange(self, auid, heroId, newLevel):
        #~ 1: i64 auid
        #~ 2: i32 heroid
        #~ 3: i32 level
        #~ 4: i32 timestamp
        self.HeroLevelChange.append(dict(auid=tolong(auid), heroid=toint(heroId), level=newLevel, timestamp=int(time.time())))

    def addHeroRankChange(self, auid, heroId, level, rank, up):
        #~ 1: i64 auid
        #~ 2: i32 heroid
        #~ 3: i32 level
        #~ 4: i32 rank
        #~ 5: bool up  // is it rank-up or rank-down change
        #~ 6: i32 timestamp
        self.HeroRankChange.append(dict(auid=tolong(auid), heroid=toint(heroId), level=level, rank=rank, up=up, timestamp=int(time.time())))

    def addCastleLevelChange(self, auid, newLevel):
        #~ 1: i64 auid
        #~ 2: i32 level
        #~ 3: i32 timestamp
        self.CastleLevelChange.append(dict(auid=tolong(auid), level=newLevel, timestamp=int(time.time())))

    def addGiveSessionAwards(self, auid, sessionpersistentid, nick, heroid, rchange, rtotal, inc_reliability,
                             new_reliability, list_talents, force, guildpointschange, guildpointstotal,
                             appliedbuffs, leaverpointschange, leaverpointstotal, isleaverchanged, isleaver,  leaverPointReason, isBadBehaviour):
        change = dict( Gold=rchange.Gold,
                       Silver=rchange.Silver,
                       Perl=rchange.Perl,
                       RedPerl=rchange.RedPerl,
                       Population=rchange.Population,
                       Resource1=rchange.Resource1,
                       Resource2=rchange.Resource2,
                       Resource3=rchange.Resource3,
                       Shard=rchange.Shard,
                       CWPoints_Player=rchange.CWPoints_Player,
        )
        total = dict( Gold=rtotal.Gold,
                      Silver=rtotal.Silver,
                      Perl=rtotal.Perl,
                      RedPerl=rtotal.RedPerl,
                      Population=rtotal.Population,
                      Resource1=rtotal.Resource1,
                      Resource2=rtotal.Resource2,
                      Resource3=rtotal.Resource3,
                      Shard=rtotal.Shard,
                      CWPoints_Player=rtotal.CWPoints_Player,
        )
        self.GiveSessionAwards.append( dict( auid=tolong(auid), sessionpersistentid=tolong(sessionpersistentid), nick=nick, heroid=toint(heroid),
            rchange=change, rtotal=total,
            inc_reliability=toint(inc_reliability), new_reliability=toint(new_reliability),
            timestamp=int(time.time()),
            talents=list_talents,
            force=force,
            guildpointschange=guildpointschange,
            guildpointstotal=guildpointstotal,
            appliedbuffs=appliedbuffs,
            leaverpointschange=dict(
                auid=tolong(auid),
                leaverpointschange=leaverpointschange,
                leaverpointstotal=leaverpointstotal,
                isleaverchanged=isleaverchanged,
                isleaver=isleaver,
                isbadbehaviour=isBadBehaviour,
                type=str(leaverPointReason),
                timestamp=int(time.time())
                )
            ))
            #~ 1: i64 auid
            #~ 2: i64 sessionpersistentid
            #~ 3: string nick
            #~ 4: i32 heroid // CRC32 signed
            #~ 5: STRUCT rchange
            #~ 6: STRUCT rtotal
            #~ 7: i32 inc_reliability
            #~ 8: i32 new_reliability
            #~ 9: i32 timestamp
            #~ 10: list<i32> talents
            #~ 11: double force
            #~ 12: i32 guildpointschange
            #~ 13: i32 guildpointstotal
            #~ 14: list<i32> appliedbuffs
            #~ 15: LeaverPointsChangeInfo leaverpointschange


    def addLauncherStart(self, hostid, version, auid, ip="", location="", locale=""):
        self.LauncherStart.append( dict( hostid=hostid, version=version, auid=auid, ip=ip, location=location, locale=locale ))
        #~ 1: string hostid
        #~ 2: string package
        #~ 3: string version
        #~ 4: LauncherStatus status
        #~ 5: i64 auid
        #~ 6: string ip
        #~ 7: string location
        #~ 8: string locale

    def addLauncherEvents(self, ruid, muid, auid, bitmask, timestamp, locale):
        self.LauncherEvents.append( dict( muid=muid, auid=auid, bitmask=bitmask, timestamp=timestamp, locale=locale ))
        #~ 1: string muid
        #~ 2: i64 auid
        #~ 3: i64 bitmask
        #~ 4: i32 timestamp
        #~ 5: string locale
        
    def addLauncherDActions(self, **kwargs):
        self.LauncherDActions.append( kwargs )
        #~ 1: string action
        #~ 2: string hostid
        #~ 3: string version
        #~ 4: string muid
        #~ 5: string ruid
        #~ 6: string auid
        #~ 7: double speed
        #~ 8: double avg_speed
        #~ 9: double min_speed
        #~ 10: i32 total_patches
        #~ 11: i32 applied_patches
        #~ 12: double total_download
        #~ 13: double downloaded
        #~ 14: string error
        #~ 15: i32 need_close
        #~ 16: i32 timestamp
        #~ 17: string geolocation
        #~ 18: i32 server_timestamp
        #~ 19: string locale
        
    def addSocialRegister(self, hostid, auid, snid, snuid, muid, ruid):
        self.SocialRegister.append( dict( hostid=hostid, auid=auid, snid=snid, snuid=snuid, muid=muid ))
        #~ 1: string hostid
        #~ 2: string auid
        #~ 3: string snid
        #~ 4: string snuid


    def addSocialJoin(self, auid, snid, snuid):
        self.SocialJoin.append( dict( auid=auid, snid=snid, snuid=snuid ))
        #~ 1: string auid
        #~ 2: string snid
        #~ 3: string snuid
        
    def addSocialMerge(self, auid1, auid2):
        self.SocialMerge.append( dict( auid1=auid1, auid2=auid2 ))
        #~ 1: string auid1
        #~ 2: string auid2

    def addGuildCreated( self, auid, guildid, faction, shortname, fullname, rchange, rtotal, guildmembers ):
        change = dict( Gold=rchange.Gold, Silver=rchange.Silver, Perl=rchange.Perl, RedPerl=rchange.RedPerl, Population=rchange.Population, Resource1=rchange.Resource1, Resource2=rchange.Resource2, Resource3=rchange.Resource3, Shard=rchange.Shard )
        total = dict( Gold=rtotal.Gold, Silver=rtotal.Silver, Perl=rtotal.Perl, RedPerl=rtotal.RedPerl, Population=rtotal.Population, Resource1=rtotal.Resource1, Resource2=rtotal.Resource2, Resource3=rtotal.Resource3, Shard=rtotal.Shard )
        self.GuildCreated.append( dict( auid=auid, guildid=guildid, faction=faction, shortname=shortname, fullname=fullname, rchange=change, rtotal=total, timestamp=int(time.time()), guildmembers=guildmembers ))

    def addGuildRenamed( self, auid, guildid, faction, shortname, fullname, rchange, rtotal, guildmembers ):
        change = dict( Gold=rchange.Gold, Silver=rchange.Silver, Perl=rchange.Perl, RedPerl=rchange.RedPerl, Population=rchange.Population, Resource1=rchange.Resource1, Resource2=rchange.Resource2, Resource3=rchange.Resource3, Shard=rchange.Shard )
        total = dict( Gold=rtotal.Gold, Silver=rtotal.Silver, Perl=rtotal.Perl, RedPerl=rtotal.RedPerl, Population=rtotal.Population, Resource1=rtotal.Resource1, Resource2=rtotal.Resource2, Resource3=rtotal.Resource3, Shard=rtotal.Shard )
        self.GuildRenamed.append( dict( auid=auid, guildid=guildid, faction=faction, shortname=shortname, fullname=fullname, rchange=change, rtotal=total, timestamp=int(time.time()), guildmembers=guildmembers ))

    def addGuildJoined( self, auid, guildid, faction, guildmembers ):
        self.GuildJoined.append( dict( auid=auid, guildid=guildid, faction=faction, timestamp=int(time.time()), guildmembers=guildmembers ))

    def addGuildLeaved( self, auid, guildid, faction, kicked, guildmembers ):
        self.GuildLeaved.append( dict( auid=auid, guildid=guildid, faction=faction, kicked=kicked, timestamp=int(time.time()), guildmembers=guildmembers ))

    def addGuildDisbanded( self, auid, guildid, faction, guildmembers ):
        self.GuildDisbanded.append( dict( auid=auid, guildid=guildid, faction=faction, timestamp=int(time.time()), guildmembers=guildmembers ))

    def addClientPing(self, auid, location, msecPing):
        self.ClientPings.append( dict( auid=auid, location=location, msecPing=toint(msecPing), timestamp=int(time.time()) ))

    def addRuneExpire(self, auid, rune, transactionsLeft, bonusLeft):
        self.RuneExpire.append( dict( auid=tolong(auid), rune=toint32(rune), transactionsLeft=toint32(transactionsLeft),
                                      bonusLeft=toint32(bonusLeft), timestamp=int(time.time()) ))
        
    def addRuneUnsoulbound(self, auid, rune, talent):
        self.RuneUnsoulbound.append( dict( auid=tolong(auid), rune=toint32(rune), talent=toint32(talent), timestamp=int(time.time()) ))
        
    def addRuneReplenish(self, auid, rune):
        self.RuneReplenish.append( dict( auid=tolong(auid), rune=toint32(rune), timestamp=int(time.time()) ))

    def addRuneHeroApply(self, auid, rune, hero):
        self.RuneHeroApply.append(dict(auid=tolong(auid), rune=toint32(rune), hero=str(hero), timestamp=int(time.time())))

    def addGMOperation( self, auid, operation, gmlogin, data ):
        self.GMOperation.append( dict( auid=tolong(auid), operation=operation, gmlogin=gmlogin, data=data, timestamp=int(time.time()) ))
        
    def addUserClaim(self, category, from_auid, to_auid, comment, log, source, locale, muid,
                     session_id=0, deaths=0, kills=0, assists=0, points=0, prime=0, leave=0, distance=0, afks=0):
        self.UserClaims.append(dict(
            fromAuid=tolong(from_auid),
            toAuid=tolong(to_auid),
            source=toint32(source),
            category=toint32(category),
            comment=comment,
            log=log,
            timestamp=int(time.time()),
            sessionpersistentid=tolong(session_id),
            kills=toint32(kills),
            deaths=toint32(deaths),
            assists=toint32(assists),
            points=toint32(points),
            prime=toint32(prime),
            distance=toint32(distance),
            afks=toint32(afks),
            connstatus=toint32(leave),
            locale=locale,
            muid=muid,
        ))

    def addBuyGuildShopItem(self, auid, guildid, hassuzerain, shoplevel, shopitemid, rchange, rtotal,
                            guildpointschange, guildpointstotal ):
        change = dict( Gold=rchange.Gold, Silver=rchange.Silver, Perl=rchange.Perl, RedPerl=rchange.RedPerl, Population=rchange.Population,
                       Resource1=rchange.Resource1, Resource2=rchange.Resource2, Resource3=rchange.Resource3, Shard=rchange.Shard,
                       CWPoints_Player=rchange.CWPoints_Player, Currencies=rchange.Currencies )
        total = dict( Gold=rtotal.Gold, Silver=rtotal.Silver, Perl=rtotal.Perl, RedPerl=rtotal.RedPerl, Population=rtotal.Population,
                      Resource1=rtotal.Resource1, Resource2=rtotal.Resource2, Resource3=rtotal.Resource3, Shard=rtotal.Shard,
                      CWPoints_Player=rtotal.CWPoints_Player, Currencies=rtotal.Currencies )
        self.GuildShopBuy.append(dict(auid=auid, guildid=guildid, hassuzerain=hassuzerain, shoplevel=shoplevel,
                                      shopitemid=shopitemid, rchange=change, rtotal=total,
                                      guildpointschange=guildpointschange, guildpointstotal=guildpointstotal,
                                      timestamp=int(time.time())
        ))
        #~ 1: i64 auid
        #~ 2: i64 guildid
        #~ 3: bool hassuzerain              // чтобы понять, у сюзерена покупали или у себя
        #~ 4: i32 shoplevel                 // уровень магазина
        #~ 5: i32 shopitemid                // id итема из магазина (CRC32 как обычно)
        #~ 6: ResourceTable rchange
        #~ 7: ResourceTable rtotal
        #~ 8: i32 guildpointschange
        #~ 9: i32 guildpointstotal
        #~ 10: i32 timestamp


    def addGuildDailyStatsInfo(self, guildid, guildrating, guildratingtoday, guildpoints, guildrank, vassals, suggested):
        self.GuildDailyStats.append(dict(guildid=guildid, guildrating=guildrating, guildratingtoday=guildratingtoday,
                                         guildpoints=guildpoints, guildrank=guildrank, timestamp=int(time.time()),
                                         vassals=vassals, suggested=suggested))

        #~ 1: i64 guildid
        #~ 2: i32 guildrating               // рейтинг клана
        #~ 3: i32 guildratingtoday          // рейтинг за сегодняшний день
        #~ 4: i32 guildpoints               // текущее количество очков клана
        #~ 5: i32 guildrank                 // положение в мире
        #~ 6: i32 timestamp
        #~ 7: list<GuildDailyStatsVassalInfo> vassals        // вассалы
        #~ 8: list<GuildDailyStatsSuggestedInfo> suggested   // предлагаемые вассалы

    def addGuildInteraction(self, guildid, targetguildid, type, siegeid, waitingtime):
        self.GuildInteraction.append(dict(guildid=guildid, targetguildid=targetguildid, type=type, siegeid=siegeid,
                                          waitingtime=waitingtime, timestamp=int(time.time())))

        #~ 1: i64 guildid                   // клан выполняющий действие
        #~ 2: i64 targetguildid             // клан-потерпевший
        #~ 3: GuildInteractionType type
        #~ 4: i64 siegeid                   // id осады, если взаимодействие происходит по результатам осады
        #~ 5: i32 waitingtime               // время ожидания принятие решения после осады
        #~ 6: i32 timestamp

    def addGuildSiege(self, siegeId, guildId, guildRating, targetGuildId, targetGuildRating,
                      targetSuzerainId, targetSuzerainRating, guildPointsPrice, startTimestamp, endTimestamp,
                      participants, winnerGuildId):
        data = dict(
            siegeid=siegeId, guildid=guildId, guildrating=guildRating,
            targetguildid=targetGuildId, targetguildrating=targetGuildRating,
            targetsuzerainid=targetSuzerainId, targetsuzerainrating=targetSuzerainRating,
            guildpointsprice=guildPointsPrice, starttimestamp=startTimestamp, endtimestamp=endTimestamp,
            participants=participants, winnerguildid=winnerGuildId
        )
        #debug("STATS.addGuildSiege: %r", data)
        self.GuildSiege.append(data)

        #~  1: i64 siegeid
        #~  2: i64 guildid
        #~  3: i32 guildrating
        #~  4: i64 targetguildid
        #~  5: i32 targetguildrating
        #~  6: i64 targetsuzerainid
        #~  7: i32 targetsuzerainrating
        #~  8: i32 guildpointsprice
        #~  9: i32 starttimestamp
        #~  10: i32 endtimestamp
        #~  11: list<GuildSiegeParticipantInfo> participants
        #~  12: i64 winnerguildid

    def addGuildPointsChange(self, guildid, auid, source, playerpointschange, playerpointstotal, guildpointschange,
                             guildpointstotal):
        self.GuildPointsChange.append(dict(guildid=guildid, auid=auid, source=source, playerpointschange=playerpointschange,
                                      playerpointstotal=playerpointstotal, guildpointschange=guildpointschange,
                                      guildpointstotal=guildpointstotal, timestamp=int(time.time())))
        #~  1: i64 guildid
        #~  2: i64 auid
        #~  3: i32 source
        #~  4: i32 playerpointschange
        #~  5: i32 playerpointstotal
        #~  6: i32 guildpointschange
        #~  7: i32 guildpointstotal
        #~  8: i32 timestamp

    def addAfterParty(self, mmstart, membs):

        self.AfterParty.append(dict(mmstarted=mmstart, members=membs, timestamp=int(time.time())))
        '''
        AfterPartyMemberInfo {
        1: i64 auid
        2: i64 sessionPersistentId
        3: bool kicked
        4: bool leaved
        }

        AfterPartyInfo {
        1: bool mmstarted
        2: list<AfterPartyMemberInfo> members
        3: i32 timestamp
        '''

    def addLeaverPointsChange(self, auid ,tp, leaverpointschange, leaverpointstotal, isleaverchanged, isleaver,isbadbehaviour):
        self.LeaverPointsChange.append(dict(auid=auid,
                                            type=str(tp),
                                            leaverpointschange=leaverpointschange,
                                            leaverpointstotal=leaverpointstotal,
                                            isleaverchanged=isleaverchanged,
                                            isleaver=isleaver,
                                            isbadbehaviour=isbadbehaviour,
                                            timestamp=int(time.time())))

        '''
        struct LeaverPointsChangeInfo {
        1: i64 auid
        2: string type
        3: i32 leaverpointschange
        4: i32 leaverpointstotal
        5: bool isleaverchanged
        6: bool isleaver
        7: bool isbadbehaviour
        8: i32 timestamp
        }
       '''

    def addLampRoll(self, auid, rune, source, sessionpersistentid=0, runescountold=1, runescountnew=1):
        self.RuneRoll.append(dict(auid=tolong(auid), rune=toint32(rune), source=source,
                                  sessionpersistentid=tolong(sessionpersistentid), timestamp=int(time.time()), runescountold=runescountold, runescountnew=runescountnew))
        #~ (1, TType.i64, 'auid', None, None, ), # 1
        #~ (2, TType.i32, 'rune', None, None, ), # 2
        #~ (3, TType.RuneRollSource , 'source', None, None, ), # 3
        #~ (4, TType.i64, 'sessionpersistentid', None, None, ), # 4
        #~ (5, TType.i32, 'timestamp', "", "", ), # 5
        #~ (6, TType.i32, 'runescountold', "", "", ), # 6
        #~ (7, TType.i32, 'runescountnew', "", "", ), # 7

    def addGWEvent(self, mongoid, eventidx, enabled, points, endtime, limit):
        self.GWEventAdd.append(dict(mongoid=str(mongoid), eventidx=toint32(eventidx), enabled=bool(enabled),
                                    points=toint32(points), endtime=toint32(endtime), limit=toint32(limit)))
        '''
        
        struct GWEventInfo {
            1: string mongoid
            2: i32 eventidx
            3: bool enabled
            4: i32 points
            5: i32 endtime
            6: i32 limit
        }

        
        '''

    def addGWScoreChange(self, gweventmid, guildid, lastpoints, currentpoints):
        self.GWScoreChange.append(dict(gweventmid=str(gweventmid), guildid=guildid, lastpoints=toint32(lastpoints),
                                       currentpoints=toint32(currentpoints), timestamp=int(time.time()), auid=int(0)))
        '''

        struct GWScoreChangeInfo {
          1: string gweventmid
          2: i32 guildid
          3: i32 lastpoints
          4: i32 currentpoints
          5: i32 timestamp
        }

        '''

    def questEventStageChange( self, auid, tostagechange):
        self.QuestEventStageChange.append(dict(auid=auid,tostagechange=tostagechange,timestamp=int(time.time())))
        '''
        
        struct QuestEventsStagesInfo {
            1: i32 auid
            2: i32 tostagechange
            3: i32 timestamp
        } 
        
        '''
    def questEventStateChange( self, auid, tostepschange, stage):
        self.QuestEventStateChange.append(dict(auid=auid, tostepschange=tostepschange, stage=stage, timestamp=int(time.time())))

        '''

        struct QuestEventsStatesInfo {
            1: i32 auid
            2: i32 tostepschange
            3: i32 stage
            4: i32 timestamp
        }

        '''

    def addReRollShop(self, auid, itemId, itemGroup, itemPrice, itemPriceType, rerollCount, slotType):
        self.ReRollShop.append(dict(auid=tolong(auid), itemId=itemId, itemGroup=itemGroup, itemPrice=itemPrice, itemPriceType=itemPriceType,
                                    rerollCount=rerollCount,slotType=slotType, timestamp=int(time.time())))
        '''
        struct ReRollShopInfo
        {
         1: i64 auid            //игрок
         2: i32 itemId          //ID товара в слоте:
                                //   Талант persistentID из *.TALENT
                                //   Герой id из *.HROB
                                //   Скин героя persistentID из *.HEROSKIN
                                //   Ресурс persistentID из ResourceRerollSlot
                                //   Премиум подписка на опр срок persistentID из ResourceRerollSlot
                                //   Руна на опр срок persistentID из ResourceRerollSlot

         3: i32 itemGroup       // ID Группы из которой был получен товар
         4: i64 itemPrice       //Price - уже сформированная на основе очков и типа ресурса цена, за которую игрок купил товар
         5: i32 itemPriceType   //TypePrice - тип ресурса, за который продавался товар
         6: i32 rerollCount     // Кол-во рероллов в течении дня, которые сделал игрок прежде чем купить этот товар
         7: i32 slotType        // Тип слота, в котором был куплен товар - премиум слот или обычный слот
         8: i32 timestamp
        }
        '''



    # ----------------------------------------------------
    def Send(self):
        send_dict = {}
        for ttypename in self._THRIFT_TYPES:
            tlist = getattr( self, ttypename )
            if tlist:
                send_dict[ ttypename ] = tlist

        if send_dict:
            # ок, есть чего посылать..
            try:
                self.startSend( send_dict )
            except:
                catch()
                try:
                    warn("ISTATS.Send failed on send_dict: %s" % send_dict)
                except:
                    catch()

            for ttypename in self._THRIFT_TYPES:
                setattr( self, ttypename, [] )

        self.checkResendPool()
    
    # ----------------------------------------------------
    # транспортная часть отправки сообщения (для тестов можно override именно эту часть; например, на прямой вызов StatisticAgentHandler.processRawData)
    def startSend(self, send_dict):
        # unique packet key for delivery tracking
        packet_id = self.I.WS.nextStringGUID('stat_send')
        body = json_dumps(send_dict)
        self.sent[packet_id] = body
        self.doSend(packet_id, 0)


    def addResend(self, packet_id, attempt):
        if attempt > 0:
            self.resend[packet_id] = (
                attempt,
                AddLoopCallback(
                    partial(self.doSend, packet_id = packet_id, attempt = attempt + 1),
                    RESEND_PERIOD[attempt if attempt < PERIODS else -1]))
            # self.resend values are pairs fo (attempt, wserver._Timeout())
        else:
            self.doSend(packet_id, 1)


    def doSend(self, packet_id, attempt):
        "Create request object and send it, called from startSend() or scheduled by addResend()"
        if packet_id not in self.sent:
            warn('[Stats] _send called with unknown packet_id %s' % packet_id)
            return
        if attempt > 0:
            self.resend.pop(packet_id, None)
        request = HTTPRequest(self.url + "/x?packet_id=" + packet_id, method="POST", body=self.sent[packet_id])
        try:
            self.I.HTTP.fetch(request, partial(self.onSend, packet_id = packet_id, attempt = attempt))
        except:
            catch()
            # in case of exception let it wait at least 1 second
            self.onSend(None, packet_id = packet_id, attempt = attempt if attempt else 1)

    # ----------------------------------------------------
    def onSend(self, http_reply, packet_id, attempt):
        info("[Stats] agent onSend packet %s reply: '%s'" % (packet_id, (http_reply.body if http_reply else None)))
        try:
            if http_reply and (not http_reply.error) and len(http_reply.body) > 0:
                result = jsonResult(http_reply)
                if result['ok'] and 'packet_id' in result:
                    if result.get('dup'):
                        warn('[Stats] statistic_agent indicates duplicate packet_id %s' % (result['packet_id'],))
                    if result['packet_id'] == packet_id:
                        self.sent.pop(packet_id, None)
                    else:
                        warn('[Stats] onSend: wrong or unknown packet_id %r in response' % (result['packet_id'],))
                    return

            warn("[Stats] onSend: BAD statistic_agent http reply: %r" % http_reply)
            self.addResend(packet_id, attempt)
        except:
            catch()
            warn("[Stats] onSend: EXCEPTION on statistic_agent http reply: %r" % http_reply)


    def checkResendPool(self):
        "Check self.sent size against limit and dump old unsent items to disk if necessary"
        # check self.sent, not self.resend, to count all unconfirmed packages
        if len(self.sent) > self.resend_pool_limit:
            # dump data for all resend tasks (sorted y packet_id) and drop these tasks
            # NOTE that packets being (re)sended now wont be affected here
            self.dumpUnsent(sorted( ((packet_id, task[1]) for packet_id, task in self.resend.iteritems()),
                            key=lambda task: int(task[0].split('_')[1])))


    def dumpUnsent(self, tasks):
        "Dump unsent statistics to a file. If it fails -- dump to the log."
        if len(tasks) == 0:
            return
        ws = self.I.WS
        # first unschedule all these tasks
        for t in tasks:
            RemoveLoopCallback(t[1])
            del self.resend[t[0]]
        # dump and remove from self.sent
        dumpFile = None
        try:
            dumpFile = ws.mkStatDump()
            t = time.time()
            print >> dumpFile, time.strftime('[%Y.%m.%d %H:%M:%S', time.localtime(int(t))) + (',%03d]' % (int((t - int(t))*1000),))
            print >> dumpFile, "Statistics resend buffer has been overflown! Emergency dump:"
            for packet_id, t in tasks:
                if packet_id in self.sent:
                    print >> dumpFile, str(packet_id) + ': ' + self.sent[packet_id]
            dumpFile.close()
            for packet_id in tasks.iterkeys():  # only after successful prints
                    self.sent.pop(packet_id, None)
        except Exception:
            catch()
            try:
                if dumpFile:
                    dumpFile.close()
            except Exception:
                catch()
        else:
            return
        # The last resort: dump stats to the main log
        bad_warn("[Stats] dumpUnsent: dump to a special file failed. Fallback to log.")
        for packet_id, t in tasks:
            if packet_id in self.sent:
                warn(str(packet_id) + ': ' + self.sent.pop(packet_id))
        warn("========[ The end of the statistics dump ]========")

