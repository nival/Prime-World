# -*- coding: utf-8 -*-

from base.helpers import *
from binascii import crc32

addRelPath('gen-py')
import AccountManagementAPI.AccountManagement
import AccountManagementAPI.ttypes

from ext_main.nickname import SetNicknameAction

from thrift_handler import AsyncThriftException
from AccountManagementAPI.ttypes import *
from StatisticCore.ttypes import GMOperationType
from guild.GuildData import GuildData
from modeldata.changes import MakeModelChangeString
from tornado.httpclient import HTTPRequest
from enums.TalentEventType import *
from guild.GuildRequests import *
import cfg


def getMongoKeyAuid( guildAuid ):
    return "gs_%d" % guildAuid

class AsyncResponseProcessor( object ):
    def __init__( self, handler ):
        info( "AsyncResponseProcessor::__init__" )
        self.handler = handler
        self.I = handler.I
        self.finished = False
        self.started = False

    def start( self ):
        self.do()
        self.started = True
        if not self.finished:
            raise AsyncThriftException("async call")

        return self.finished


    def fin( self ):
        self.finished = True
        info( "AsyncResponseProcessor::fin" )
        if self.started:
            self.handler.process()
    
class GetGuildByNameResponse( AsyncResponseProcessor ):
    def __init__( self, handler, shortname, fullname ):
        AsyncResponseProcessor.__init__( self, handler )
        self.shortname = shortname
        self.fullname = fullname
        self.result = AccountManagementAPI.ttypes.GuildInfoResponse( result = AccountManagementAPI.ttypes.RequestResult.BadServiceType, \
            guild = AccountManagementAPI.ttypes.GuildInfo() )

    def getHashCode( self ):
        if self.shortname:
            return "shortname_%d" % crc32( self.shortname )
        elif self.fullname:
            return "fullname_%d" % crc32( self.fullname )

        return ""

    def getResult( self ):
        return self.result

    def do( self ):
        if self.shortname:
            self.I.DATA.find_one( "guilds", "guilds", {"ShortName":{ "$regex": "^" + self.shortname + "$", "$options": '-i' }}, callback=self.onGetGuildAuid )
        elif self.fullname:
            self.I.DATA.find_one( "guilds", "guilds", {"FullName":{ "$regex": "^" + self.fullname + "$", "$options": '-i' }}, callback=self.onGetGuildAuid )
        else:
            err("GetGuildByNameResponse: shortname or fullname should be specified" )
            self.fin()

    def onGetGuildAuid(self, response):
        self.result.result = AccountManagementAPI.ttypes.RequestResult.AuidNotExist

        if response:
            try:
                self.result.guild.guildid = response["r"]["GuildAuid"] or 0
                if self.result.guild.guildid:
                    self.result.result = AccountManagementAPI.ttypes.RequestResult.Success
            except:
                pass

        self.fin()

class GuildOperationResponse( AsyncResponseProcessor ):
    def __init__( self, handler, auid ):
        AsyncResponseProcessor.__init__( self, handler )
        self.auid = auid
        self.result = AccountManagementAPI.ttypes.RequestResult.BadResult

    def getResult( self ):
        return self.result

    def fin( self ):
        if self.acc and self.acc.auid != None:
            self.I.WS.unsubscribeUserAccount( self.acc.auid, self.auid )
        AsyncResponseProcessor.fin( self )

    def onLoadGuild( self, acc, errorMessage=None ):
        self.acc = acc
        if self.acc.GuildData.GuildAuid:
            self.do2()
        else:
            warn( "GuildOperationResponse::onLoadGuild: fail, error message: %r", errorMessage )
            self.fin()

    def do( self ):
        self.I.WS.subscribeUserAccount( CC.GUILD_NEUTRAL_AUID, self.auid, None, None, self.onLoadGuild )
      
class GetGuildByIdResponse2( GuildOperationResponse ):
    def __init__( self, handler, auid ):
        GuildOperationResponse.__init__( self, handler, auid )
        self.auid = auid
        self.result = AccountManagementAPI.ttypes.GuildInfoResponse(result=AccountManagementAPI.ttypes.RequestResult.AuidNotExist,
                                                                    guild=AccountManagementAPI.ttypes.GuildInfo())

    def getHashCode( self ):
        return "auid_%d" % self.auid

    def do2( self ):
        self.result = AccountManagementAPI.ttypes.GuildInfoResponse(result=AccountManagementAPI.ttypes.RequestResult.BadServiceType,
                                                                    guild=AccountManagementAPI.ttypes.GuildInfo())
        # last call before send on self.onGetOwner
        self.I.AGG.getFriendsInfo( self.acc.GuildData.Owner.Person, 0,0,0, self.onGetFriends )


    def onGetFriends(self, response):
        if response:
            friends = response.get("get_friends_info_all") or {}

            guildMembers = dict()
            for gmId in self.acc.GuildData.Members.keys():
                member = self.acc.GuildData.getGuildMemberByID( gmId )
                guildMembers[member.Person] = dict( auid=member.Person, isofficer=member.IsOfficer,
                                                    addedTalentsDailyCount=member.AddedTalentsDailyCount,
                                                    takenTalentsDailyCount=member.TakenTalentsDailyCount)

            self.members=[]
            for auid_string, friend in friends.iteritems():
                auid = tolong( auid_string )
                nickName = utf8convert( friend.get("props", {}).get("nick", "member_%d?" % auid) )
                if auid in guildMembers:
                    member = guildMembers[auid]
                    self.members.append( AccountManagementAPI.ttypes.GuildMemberInfo(auid, nickName, member["isofficer"],
                                                                                     member["addedTalentsDailyCount"],
                                                                                     member["takenTalentsDailyCount"]))

            self.I.AGG.getInfo( self.acc.GuildData.Owner.Person, None, False, callback=self.onGetOwner )
            return

        warn("GetGuildByIdResponse2: onGetFriends fail" )
        self.fin()

    def onGetOwner(self, response):
        if response:
            ec = toint(response.get("error"))
            friend = response.get("get_info", {})
            configData = self.I.Config.getConfig( self.acc.userlocale )
            if (ec == 0) and friend:
                nickName = utf8convert( friend.get("props", {}).get("nick", "leader_%d?" % self.acc.GuildData.Owner.Person) )
                self.members.append( AccountManagementAPI.ttypes.GuildMemberInfo( self.acc.GuildData.Owner.Person, nickName, True,
                    self.acc.GuildData.Owner.AddedTalentsDailyCount, self.acc.GuildData.Owner.TakenTalentsDailyCount ) )
                vassalsList = []
                for vassalId, vassal in self.acc.GuildData.GuildVassals.iteritems():
                    vassalInfo = AccountManagementAPI.ttypes.GuildShortInfo(guildid=vassal.ShortInfo.GuildAuid,
                                                                            shortname=utf8convert(vassal.ShortInfo.GuildShortName),
                                                                            fullname=utf8convert(vassal.ShortInfo.GuildFullName))
                    vassalsList.append(vassalInfo)
                  # проверим осады
                siegeEndTime = 0
                if len(self.acc.SiegeData.ActiveSieges):
                    for siegeId in self.acc.SiegeData.ActiveSieges:
                        siege = self.acc.SiegeData.getSiegeByID(siegeId)
                        if siege.Target.ShortInfo.GuildAuid == self.acc.GuildData.GuildAuid:
                            siegeEndTime = siege.EndTime
                # final response creation
                self.result = AccountManagementAPI.ttypes.GuildInfoResponse(
                    result=AccountManagementAPI.ttypes.RequestResult.Success,
                    guild=AccountManagementAPI.ttypes.GuildInfo(
                        self.acc.GuildData.GuildAuid, self.acc.GuildData.GuildInfo.ShortName,
                        self.acc.GuildData.GuildInfo.FullName, self.acc.GuildData.GuildInfo.MessageOfTheDay,
                        self.acc.GuildData.Owner.Person, nickName, self.members,
                        guildExperience=self.acc.GuildData.GuildLevelInfo.Experience,
                        iconChangesCount=self.acc.GuildData.GuildInfo.IconChangesCount,
                        # incerementing raw data guild level for GMTools as in Castle UI view
                        # e.g. start level(0 in data) will showed as 1
                        guildLevel = self.I.SD.getGuildLevel(self.acc.GuildData.GuildLevelInfo.Experience) + 1,
                        guildBankAddLimit=configData.GuildBankSettings.GUILD_BANK_ADD_LIMIT,
                        guildBankTakeLimit=configData.GuildBankSettings.GUILD_BANK_TAKE_LIMIT,
                        cwguildpoints=fit_i32(self.acc.GuildData.GuildInfo.CWPoints_Clan),
                        cwrating=fit_i32(self.acc.GuildData.RatingInfo.Rating),
                        suzerain=AccountManagementAPI.ttypes.GuildShortInfo(
                            guildid=self.acc.GuildData.GuildSuzerain.ShortInfo.GuildAuid,
                            shortname=utf8convert(self.acc.GuildData.GuildSuzerain.ShortInfo.GuildShortName),
                            fullname=utf8convert(self.acc.GuildData.GuildSuzerain.ShortInfo.GuildFullName)),
                        vassals=vassalsList, siegeendtime=siegeEndTime, releaselocktime=self.acc.GuildData.GuildInfo.GMLockTime
                    ))

                info("GetGuildByIdResponse2: result = %r" % self.result )
                self.fin()
                return

        warn("GetGuildByIdResponse2: onGetOwner fail" )
        self.fin()
    
class EditGuildResponse(GuildOperationResponse):
    def __init__(self, handler, guildInfo, gmLogin):
        GuildOperationResponse.__init__(self, handler, guildInfo.guildid)
        self.guildInfo = guildInfo
        self.gmLogin = gmLogin

    def getHashCode(self):
        return "editguild_%d" % self.guildInfo.guildid

    def do2( self ):
        config = self.I.Config.getMainConfig()
        ( r, name, encoding ) = SetNicknameAction.checkNickname( self.guildInfo.shortname, config.NICKNAME_REGEXES, config.ADMIN_NICKS, 2, 5 )
        if r != SetNicknameAction.CHECK_OK:
          self.fin()
          return

        ( r, name, encoding ) = SetNicknameAction.checkNickname( self.guildInfo.fullname, config.NICKNAME_REGEXES, config.ADMIN_NICKS, SetNicknameAction.MIN_NICKNAME_LENGTH, SetNicknameAction.MAX_NICKNAME_LENGTH )
        if r != SetNicknameAction.CHECK_OK:
          self.fin()
          return

        self.fullNameChecked = False
        self.fullNameUnique = False
        self.shortNameChecked = False
        self.shortNameUnique = False

        if self.acc.GuildData.GuildInfo.FullName != self.guildInfo.fullname:
          self.I.DATA.find_one( "guilds", "guilds", {"FullName":{ "$regex": "^" + self.guildInfo.fullname + "$", "$options": '-i' }}, callback=self.onFullNameChecked )
        else:
          self.fullNameChecked = True
          self.fullNameUnique = True

        if self.acc.GuildData.GuildInfo.ShortName != self.guildInfo.shortname:
          self.I.DATA.find_one( "guilds", "guilds", {"ShortName":{ "$regex": "^" + self.guildInfo.shortname + "$", "$options": '-i' }}, callback=self.onShortNameChecked )
        else:
          self.shortNameChecked = True
          self.shortNameUnique = True

        self.onNameChecked()

    def onFullNameChecked( self, response ):
        self.fullNameChecked = True
        if response:
          if not response['r']:
            self.fullNameUnique = True

        self.onNameChecked()

    def onShortNameChecked( self, response ):
        self.shortNameChecked = True
        if response:
          if not response['r']:
            self.shortNameUnique = True

        self.onNameChecked()

    def onNameChecked(self):
        if not self.fullNameChecked or not self.shortNameChecked:
            return

        if not self.fullNameUnique or not self.shortNameUnique:
            self.result = AccountManagementAPI.ttypes.RequestResult.BadResult
            self.fin()
            return

        data = "Guild %d" % self.acc.GuildData.GuildAuid
        if self.acc.GuildData.GuildInfo.FullName != self.guildInfo.fullname or self.acc.GuildData.GuildInfo.ShortName != self.guildInfo.shortname:
            self.I.WS.renameGuild(self.acc, self.guildInfo.shortname, self.guildInfo.fullname)
            data += "guild_rename: [%s] %s " % (self.guildInfo.shortname, self.guildInfo.fullname)

        messageoftheday = self.guildInfo.messageoftheday or ""
        if self.acc.GuildData.GuildInfo.MessageOfTheDay != messageoftheday:
            self.I.WS.setMessageOfTheDay(self.acc, messageoftheday)
            data += "message_of_the_day: %s " % messageoftheday

        if self.acc.GuildData.GuildLevelInfo.Experience != self.guildInfo.guildExperience:
            self.I.WS.setExperience(self.acc, self.guildInfo.guildExperience)
            data += "experience: %d " % self.guildInfo.guildExperience

        if self.acc.GuildData.GuildInfo.CWPoints_Clan != self.guildInfo.cwguildpoints:
            self.I.WS.setGuildCWPoints(self.acc, self.guildInfo.cwguildpoints)
            data += "cw_points: %s " % self.guildInfo.cwguildpoints

        if self.acc.GuildData.RatingInfo.Rating != self.guildInfo.guildrating:
            self.I.WS.setGuildRating(self.acc, self.guildInfo.guildrating)
            data += "rating: %s " % self.guildInfo.guildrating

        self.I.STATS.addGMOperation(0, GMOperationType.GuildEdit, self.gmLogin, data)
        changes = self.I.WS.pickPendingChanges(self.acc)
        self.I.WS.sendBroadCast(self.acc, changes, [], '')
        self.I.WS.saveGuildData(self.acc, None)
        self.result = AccountManagementAPI.ttypes.RequestResult.Success
        self.fin()
    
class ChangeGuildLeaderResponse( GuildOperationResponse ):
    def __init__( self, handler, auid, leader, gmLogin ):
          GuildOperationResponse.__init__( self, handler, auid )
          self.auid = auid
          self.leader = leader
          self.gmLogin = gmLogin

    def getHashCode( self ):
        return "change_leader_%d_%d" % ( self.auid, self.leader )

    def do2( self ):
        if self.leader == self.acc.GuildData.Owner.Person:
            self.result = AccountManagementAPI.ttypes.RequestResult.Success
            self.fin()
            return

        not_found = True
        for gmId in self.acc.GuildData.Members.keys():
            member = self.acc.GuildData.getGuildMemberByID( gmId )
            if member.Person == self.leader:
                not_found = False
                break

        if not_found:
            self.fin()
            return

        self.I.WS.setLeader( self.acc, self.leader )
        new_owner = self.acc.GuildData.findMemberByAuid(self.leader)
        data = "New leader %d, guild %d" % (new_owner.Person, self.acc.GuildData.GuildAuid)
        self.I.STATS.addGMOperation(new_owner.Person, GMOperationType.GuildEdit, self.gmLogin, data)
        self.result = AccountManagementAPI.ttypes.RequestResult.Success
        self.fin()

class GetGuildMemberByIdResponse( GuildOperationResponse ):
    def __init__( self, handler, auid, memberid ):
        GuildOperationResponse.__init__( self, handler, auid )
        self.auid = auid
        self.memberid = memberid

    def getHashCode( self ):
        return "get_guild_member_by_id_%d" % ( self.auid )

    def do2( self ):
        info("GetGuildMemberByIdResponse, memberid=%r", self.memberid)
        self.result = AccountManagementAPI.ttypes.GuildMemberInfoResponse(result = AccountManagementAPI.ttypes.RequestResult.BadServiceType, \
                                                                          guildMember=AccountManagementAPI.ttypes.GuildMemberInfo() )

        self.I.WS.resetPendingChanges( self.acc )
        self.acc.GuildData.write( self.acc.pending )

        guild_member = self.acc.GuildData.findMemberByAuid( self.memberid )
        if guild_member:
            self.result = AccountManagementAPI.ttypes.GuildMemberInfoResponse( result = AccountManagementAPI.ttypes.RequestResult.Success,
                guildMember=AccountManagementAPI.ttypes.GuildMemberInfo(auid = guild_member.Person, nickname = "", isofficer = guild_member.IsOfficer,
                addedTalentsDailyCount = guild_member.AddedTalentsDailyCount, takenTalentsDailyCount = guild_member.TakenTalentsDailyCount))

        changes = self.I.WS.pickPendingChanges( self.acc )
        self.I.WS.sendBroadCast( self.acc, changes, [], '' )
        self.I.WS.saveGuildData( self.acc, None )
        self.fin()

class EditGuildMemberResponse( GuildOperationResponse ):
    def __init__( self, handler, auid, member, gmLogin ):
        GuildOperationResponse.__init__( self, handler, auid )
        self.auid = auid
        self.member = member
        self.gmLogin = gmLogin

    def getHashCode( self ):
        return "edit_member_%d" % ( self.auid )

    def do2( self ):
        has_changes = False

        self.I.WS.resetPendingChanges( self.acc )
        self.acc.GuildData.write( self.acc.pending )
        configData = self.I.Config.getConfig( self.acc.userlocale )

        guild_member = self.acc.GuildData.findMemberByAuid( self.member.auid )

        if guild_member:
            if guild_member.IsOfficer != self.member.isofficer and guild_member.Person != self.acc.GuildData.Owner.Person:
                guild_member.IsOfficer = self.member.isofficer
                has_changes = True

            if not self.member.addedTalentsDailyCount > configData.GuildBankSettings.GUILD_BANK_ADD_LIMIT:
                guild_member.AddedTalentsDailyCount = self.member.addedTalentsDailyCount
            if not self.member.takenTalentsDailyCount > configData.GuildBankSettings.GUILD_BANK_TAKE_LIMIT:
                guild_member.TakenTalentsDailyCount = self.member.takenTalentsDailyCount

        changes = self.I.WS.pickPendingChanges( self.acc )
        self.I.WS.sendBroadCast( self.acc, changes, [], '' )
        self.I.WS.saveGuildData( self.acc, None )
        data = "Edit member %d, guild %d" % (guild_member.Person, self.acc.GuildData.GuildAuid)
        self.I.STATS.addGMOperation(guild_member.Person, GMOperationType.GuildEdit, self.gmLogin, data)
        self.result = AccountManagementAPI.ttypes.RequestResult.Success
        self.fin()
    
class RemoveGuildMembersResponse( GuildOperationResponse ):
    def __init__( self, handler, auid, members, gmLogin ):
        GuildOperationResponse.__init__( self, handler, auid )
        self.auid = auid
        self.members = members
        self.gmLogin = gmLogin

    def getHashCode( self ):
        return "remove_guild_members_%d" % ( self.auid )

    def do2(self):
        info("RemoveGuildMembers auids = %r", self.members)
        if len(self.members):
            if len(self.members) == len(self.acc.GuildData.Members):
                info("RemoveGuildMembersResponse: removed members count == guild members count, guild will be destroyed")
                subParams = ClassDict(auid=[self.acc.auid])
                accountAction = DestroyGuildAction( subParams, self.onDestroyResponse, I=self.handler.I, acc=self.acc, uid=self.acc.uid )
                accountAction.onStart()
            else:
                member_auid = self.members.pop()
                subParams = ClassDict( auid=[self.acc.auid], personAuid=[member_auid] )
                accountAction = KickGuildAction( subParams, self.onRemoveResponse, I=self.handler.I, acc=self.acc, uid=self.acc.uid )
                accountAction.onStart()
                data = "Member %d wad removed from guild %d" % (member_auid, self.acc.GuildData.GuildAuid)
                self.I.STATS.addGMOperation(member_auid, GMOperationType.GuildEdit, self.gmLogin, data)
        else:
            self.result = AccountManagementAPI.ttypes.RequestResult.BadResult
            self.fin()

    def onRemoveResponse(self, response):
        if response:
            info( "onRemoveGuildMemberResponse response: %s" % self.I.MD.pretty(response) )
            isOk = response.get("ok") or 0
            if isOk:
                if len(self.members):
                    member_auid = self.members.pop()
                    subParams = ClassDict( auid=[self.acc.auid], personAuid=[member_auid] )
                    accountAction = KickGuildAction( subParams, self.onRemoveResponse, I=self.handler.I, acc=self.acc, uid=self.acc.uid )
                    accountAction.onStart()
                    data = "Member %d wad removed from guild %d" % (member_auid, self.acc.GuildData.GuildAuid)
                    self.I.STATS.addGMOperation(member_auid, GMOperationType.GuildEdit, self.gmLogin, data)
                else:
                    self.result = AccountManagementAPI.ttypes.RequestResult.Success
                    self.fin()
            else:
                info( "Can't kick members, bad response from server" )
                self.result = AccountManagementAPI.ttypes.RequestResult.BadResult
                self.fin()

    def onDestroyResponse(self, response):
        if response:
            info( "onDestroyResponse response: %s" % self.I.MD.pretty(response) )
            isOk = response.get("ok") or 0
            if isOk:
                data = "Guild %d destroyed" % self.acc.GuildData.GuildAuid
                self.I.STATS.addGMOperation(0, GMOperationType.GuildEdit, self.gmLogin, data)
                self.result = AccountManagementAPI.ttypes.RequestResult.Success
                self.fin()
            else:
                info( "Can't kick members, bad response from server" )
                self.result = AccountManagementAPI.ttypes.RequestResult.BadResult
                self.fin()

class SetGuildIconResponse( GuildOperationResponse ):
    """
    Full cycle:
    1. receiving bytes array from GM tools,
    2. if icon already changed N times - checking that guild leader have enough gold,
    3. if so uploading to bytes to cdn for access as png
    4. write off gold
    5. writing new icon url to guildInfo
    6. incerementing icon changes counter

    At this moment this handler just upload file to storage
    http://devjira.nivalnetwork.com/browse/PF-64032
    """
    def __init__( self, handler, auid, image ):
        GuildOperationResponse.__init__( self, handler, auid )
        self.auid = auid
        self.image = image
        self.logs_prefix = "Uploading Icon for Guild guildid=%s:"%(str(auid))

    def getHashCode( self ):
        return "set_guild_icon_%d" % ( self.auid )

    def onIconUploaded(self, response):
        isSuccess = response.code >= 200 and response.code < 300
        if isSuccess:
            info("%s icon successfully uploaded, response code '%s'"%(self.logs_prefix,str(response.code)))
            self.result = AccountManagementAPI.ttypes.RequestResult.Success
        else:
            # error on uploading
            warn("%s unable to upload guild icon, response '%s'"%(self.logs_prefix,str(response.code)))
            self.result = AccountManagementAPI.ttypes.RequestResult.IconFileUploadingError
        self.fin()

    def do2( self ):
        info( "%s" % (self.logs_prefix) )
        self.guildInfo = self.acc.GuildData.GuildInfo
        # guild level check
        configData = self.I.Config.getConfig( self.acc.userlocale )
        # guild level from DB + 1 for natural account
        guildLevel = self.I.SD.getGuildLevel( self.acc.GuildData.GuildLevelInfo.Experience )
        info( "%s guild_name=%s, level=%d, leader_auid=%d" % (self.logs_prefix, self.guildInfo.FullName, guildLevel, self.acc.GuildData.Owner.Person))
        # decreasing GUILD_MIN_LEVEL_FOR_ICON_CHANGE because it stored in UI styled format (0 showed as 1)
        if(guildLevel < configData.GUILD_MIN_LEVEL_FOR_ICON_CHANGE - 1):
            warn("%s guild level (%d) less than required (%d) for icon change"%(self.logs_prefix,guildLevel,configData.GUILD_MIN_LEVEL_FOR_ICON_CHANGE-1))
            self.result = AccountManagementAPI.ttypes.RequestResult.GuildLevelIsTooLow
            self.fin()
            return

        iconUrl = cfg.GUILD_ICONS_UPLOAD_URL_PATTERN
        iconUrl = iconUrl.replace("{guild_id}",str(self.auid))
        iconUrl = iconUrl.replace("{changes_count}",str(self.guildInfo.IconChangesCount + 1))
        info("%s uploading icon to '%s'..."%(self.logs_prefix,iconUrl))
        request = HTTPRequest(iconUrl, method="PUT", body=self.image)
        self.I.HTTP.fetch(request, self.onIconUploaded)
    
class SwitchToNewGuildIconResponse( GuildOperationResponse ):
    """
    Switching guild data to new icon(which was uploaded by SetGuildIcon)
    In fact just increments icon revision (guildInfo.IconChangesCount)
    """
    def __init__( self, handler, auid, gmLogin ):
        GuildOperationResponse.__init__( self, handler, auid )
        self.auid = auid
        self.logs_prefix = "Switching Icon for Guild guildid=%s:"%(str(auid))
        self.gmLogin = gmLogin

    def getHashCode( self ):
        return "switch_to_new_guild_icon_%d" % ( self.auid )

    def do2( self ):
        self.guildInfo = self.acc.GuildData.GuildInfo
        info( "%s guild_name=%s leader_auid=%d" % (self.logs_prefix, self.guildInfo.FullName, self.acc.GuildData.Owner.Person) )
        self.guildInfo.IconChangesCount += 1
        self.I.WS.saveGuildData( self.acc, None )
        info("%s guild icon successfully switched"%(self.logs_prefix))
        data = "%s icon (guild %d) successfully switched" % (self.logs_prefix, self.acc.GuildData.GuildAuid)
        self.I.STATS.addGMOperation(0, GMOperationType.GuildEdit, self.gmLogin, data)
        self.result = AccountManagementAPI.ttypes.RequestResult.Success
        self.fin()

class GetFreeGuildBankTalentsResponse( GuildOperationResponse ):
    """ """
    def __init__( self, handler, auid ):
        GuildOperationResponse.__init__( self, handler, auid )
        self.auid = auid

    def getHashCode( self ):
        return "get_all_free_guild_bank_talents_%d" % ( self.auid )

    def do2( self ):
        freeTalents = []
        for gTalId in self.acc.GuildData.FreeTalents.keys():
            talent = self.acc.GuildData.getGuildTalentByID( gTalId )
            if talent:
                owner = 0
                if talent.Owner.get():
                    owner = talent.Owner.Person
                holder = 0
                if talent.Holder.get():
                    holder = talent.Holder.Person
                freeTalents.append(AccountManagementAPI.ttypes.GuildTalentInfo(owner, holder, talent.HeroClassId,
                                                                           talent.Points, talent.PersistentId, gTalId))

        self.result = AccountManagementAPI.ttypes.GuildBankTalentsResponse( result = AccountManagementAPI.ttypes.RequestResult.Success,
                                                                            guildBankTalents = freeTalents)
        self.fin()

class GetTakenGuildBankTalentsResponse( GuildOperationResponse ):
    """ """
    def __init__( self, handler, auid ):
        GuildOperationResponse.__init__( self, handler, auid )
        self.auid = auid

    def getHashCode( self ):
        return "get_all_taken_guild_bank_talents_%d" % ( self.auid )

    def do2( self ):
        takenTalents = []
        for gTalId in self.acc.GuildData.TakenTalents.keys():
            talent = self.acc.GuildData.getGuildTalentByID( gTalId )
            if talent:
                owner = 0
                if talent.Owner:
                    owner = talent.Owner.Person
                holder = 0
                if talent.Holder:
                    holder = talent.Holder.Person
                takenTalents.append(AccountManagementAPI.ttypes.GuildTalentInfo(owner, holder, talent.HeroClassId,
                                                                             talent.Points, talent.PersistentId, gTalId))

        self.result = AccountManagementAPI.ttypes.GuildBankTalentsResponse( result = AccountManagementAPI.ttypes.RequestResult.Success,
                                                                            guildBankTalents = takenTalents)
        self.fin()

class ReturnTalentToOwnerResponse( GuildOperationResponse ):
    """ """
    def __init__( self, handler, auid, talentId, gmLogin ):
        GuildOperationResponse.__init__( self, handler, auid )
        self.auid = auid
        self.talentId = talentId
        self.gmLogin = gmLogin

    def getHashCode( self ):
        return "give_back_guild_bank_talent_%d" % ( self.auid )

    def do2( self ):
        subParams = ClassDict( auid=[self.acc.auid], talId=[self.talentId] )
        talent = self.acc.GuildData.getGuildTalentByID(self.talentId)
        self.persistentId = talent.PersistentId
        accountAction = GiveBackGuildTalentAction( subParams, self.onGiveResponse, I=self.handler.I, acc=self.acc, uid=self.acc.uid )
        accountAction.onStart()

    def onGiveResponse(self, response):
        if response:
            info( "onGiveBackGuildTalent response: %s" % self.I.MD.pretty(response) )
            isOk = response.get("ok") or 0
            if isOk:
                talent = self.acc.GuildData.getGuildTalentByID(self.talentId)
                data = "Talent %d was returned to owner from guild %d" % (self.persistentId, self.acc.GuildData.GuildAuid)
                self.I.STATS.addGMOperation(0, GMOperationType.GuildEdit, self.gmLogin, data)
                self.result = AccountManagementAPI.ttypes.RequestResult.Success
            else:
                info( "Can't give back talent, bad response from server" )
                self.result = AccountManagementAPI.ttypes.RequestResult.BadResult

        self.fin()

class ReturnTalentToGuildBankResponse( GuildOperationResponse ):
    """ """
    def __init__( self, handler, auid, talentId, gmLogin ):
        GuildOperationResponse.__init__( self, handler, auid )
        self.auid = auid
        self.talentId = talentId
        self.gmLogin = gmLogin

    def getHashCode( self ):
        return "give_back_guild_bank_talent_%d" % ( self.auid )

    def do2( self ):
        talent = self.acc.GuildData.getGuildTalentByID( self.talentId )
        if talent:
            self.I.WS.resetPendingChanges( self.acc )
            self.acc.GuildData.write( self.acc.pending )

            # Удаляем их из ModelData "одолжившего"
            self.I.WS.createMailDeleteGuildTalent( talent.Holder.Person, self.talentId, self.acc.GuildData )
            self.I.WS.logTalentEvent( self.acc.GuildData, TalentEventType.Return, talent.Holder.Person, talent.Owner.Person, talent.PersistentId )
            talent.Holder = 0
            self.acc.GuildData.FreeTalents.add( talent )
            self.acc.GuildData.TakenTalents.remove( talent )

            changes = self.I.WS.pickPendingChanges( self.acc )
            self.I.WS.sendBroadCast( self.acc, changes, [], '' )
            self.I.WS.saveGuildData( self.acc, None )
            data = "Talent %d was returned to bank of guild %d" % (talent.PersistentId, self.acc.GuildData.GuildAuid)
            self.I.STATS.addGMOperation(0, GMOperationType.GuildEdit, self.gmLogin, data)
            self.result = AccountManagementAPI.ttypes.RequestResult.Success
            self.fin()
            return

        info( "Can't return talent to bank, bad response from server" )
        self.result = AccountManagementAPI.ttypes.RequestResult.BadResult
        self.fin()



class AcquireGuildLockResponse(GuildOperationResponse):
    """ Lock guild for any vassal-suzerain interactions or siege activities for 10 minutes"""
    def __init__(self, handler, auid, gmLogin):
        GuildOperationResponse.__init__(self, handler, auid)
        self.auid = auid
        self.gmLogin = gmLogin

    def getHashCode(self):
        return "acquire_guild_lock_%d" % (self.auid)

    def do2(self):
        self.I.WS.resetPendingChanges(self.acc)
        self.acc.GuildData.write(self.acc.pending)

        self.acc.GuildData.GuildInfo.GMLockTime = int(time.time()) + 60*10
        self.I.STATS.addGMOperation(0, GMOperationType.GuildLock, self.gmLogin, str(self.acc.GuildData.GuildAuid))

        changes = self.I.WS.pickPendingChanges(self.acc)
        self.I.WS.sendBroadCast(self.acc, changes, [], '')
        self.I.WS.saveGuildData(self.acc, None)
        self.result = AccountManagementAPI.ttypes.RequestResult.Success
        self.fin()

class ReleaseGuildLockResponse(GuildOperationResponse):
    """ Unlock guild for any vassal-suzerain interactions or siege activities"""
    def __init__(self, handler, auid, gmLogin):
        GuildOperationResponse.__init__(self, handler, auid)
        self.auid = auid
        self.gmLogin = gmLogin

    def getHashCode(self):
        return "release_guild_lock_%d" % self.auid

    def do2(self):
        self.I.WS.resetPendingChanges(self.acc)
        self.acc.GuildData.write(self.acc.pending)

        self.acc.GuildData.GuildInfo.GMLockTime = 0
        self.I.STATS.addGMOperation(0, GMOperationType.GuildUnlock, self.gmLogin, str(self.acc.GuildData.GuildAuid))

        changes = self.I.WS.pickPendingChanges(self.acc)
        self.I.WS.sendBroadCast(self.acc, changes, [], '')
        self.I.WS.saveGuildData(self.acc, None)
        self.result = AccountManagementAPI.ttypes.RequestResult.Success
        self.fin()

class AddGuildSuzerainResponse(GuildOperationResponse):
    """ Attach suzerain to a free guild"""
    def __init__(self, handler, auid, suzerainAuid, gmLogin):
        GuildOperationResponse.__init__(self, handler, auid)
        self.auid = auid
        self.gmLogin = gmLogin
        self.suzerainAuid = suzerainAuid

    def getHashCode(self):
        return "add_guild_suzerain_%d" % self.auid

    def do2(self):
        if self.acc.GuildData.GuildInfo.GMLockTime > int(time.time()):
            if not self.acc.SiegeData.isTarget(self.acc.GuildData.GuildAuid):
                if not self.acc.GuildData.GuildSuzerain.ShortInfo.GuildAuid:
                    args = dict(method="add_vassal", message={"toGuildAuid": self.suzerainAuid, "targetAuid": self.acc.GuildData.GuildAuid})
                    self.I.SEX.sendToGuildService(self.acc.GuildData.GuildAuid, self.suzerainAuid, args, self.onSuzerainAddedResponse)
                    return
                else:
                    self.result = AccountManagementAPI.ttypes.RequestResult.IncorrectSuzerain
            else:
                self.result = AccountManagementAPI.ttypes.RequestResult.SiegeInProgress
        else:
            self.result = AccountManagementAPI.ttypes.RequestResult.GuildLockRequired
        self.fin()

    def onSuzerainAddedResponse(self, response):
        self.result = AccountManagementAPI.ttypes.RequestResult.BadResult
        if response:
            info("AddGuildSuzerainResponse.onSuzerainAddedResponse response: %s" % self.I.MD.pretty(response))
            isOk = response.get("ok") or 0
            if isOk:
                data = "Suzerain %d added to guild %d" % (self.suzerainAuid, self.acc.GuildData.GuildAuid)
                self.I.STATS.addGMOperation(0, GMOperationType.GuildSuzerainChange, self.gmLogin, data)
                self.result = AccountManagementAPI.ttypes.RequestResult.Success
                self.fin()
                return

            if "ec" in response and response["ec"] == EC.GUILD_MAX_VASSAL_SIZE:
                self.result = AccountManagementAPI.ttypes.RequestResult.MaxVassalsReached

        self.fin()


class RemoveGuildSuzerainResponse(GuildOperationResponse):
    """ Remove suzerain from this guild """
    def __init__(self, handler, auid, gmLogin):
        GuildOperationResponse.__init__(self, handler, auid)
        self.auid = auid
        self.gmLogin = gmLogin

    def getHashCode(self):
        return "remove_guild_suzerain_%d" % self.auid

    def do2(self):
        debug("RemoveGuildSuzerainResponse.do2: auid %s, GuildAuid %s, SuzerainAuid %s",
              self.acc.auid, self.acc.GuildData.GuildAuid, self.acc.GuildData.GuildSuzerain.ShortInfo.GuildAuid)
        if self.acc.GuildData.GuildInfo.GMLockTime > int(time.time()):
            if not self.acc.SiegeData.isTarget(self.acc.GuildData.GuildAuid):
                if self.acc.GuildData.GuildSuzerain.ShortInfo.GuildAuid:
                    # Для нпс достаточно просто уведомить наш клан о смене сюзерена
                    if self.acc.GuildData.GuildSuzerain.ShortInfo.GuildAuid == CC.NPC_SUZERAIN_AUID:
                        debug("Removing NPC-suzerain")
                        args = ClassDict(auid=[self.acc.auid], toGuildAuid=[self.acc.GuildData.GuildAuid],
                                         fromGuildAuid=[0])
                        action = NewSuzerainNotify(args, self.onSuzerainRemovedResponse, I=self.I)
                        action.onStart()
                    # Для нормального сюзерена вызовем remove_vassal от его имени
                    else:
                        debug("Removing real suzerain")
                        args = dict(method="remove_vassal", message={"auid": CC.GUILD_NEUTRAL_AUID,
                                                             "targetAuid": self.acc.GuildData.GuildAuid,
                                                             "notifyVassal": True})
                        self.I.SEX.sendToGuildService(self.acc.GuildData.GuildAuid, self.acc.GuildData.GuildSuzerain.ShortInfo.GuildAuid, args, self.onSuzerainRemovedResponse)
                    return
                else:
                    self.result = AccountManagementAPI.ttypes.RequestResult.IncorrectSuzerain
            else:
                self.result = AccountManagementAPI.ttypes.RequestResult.SiegeInProgress
        else:
            self.result = AccountManagementAPI.ttypes.RequestResult.GuildLockRequired

        self.fin()


    def onSuzerainRemovedResponse(self, response):
        self.result = AccountManagementAPI.ttypes.RequestResult.BadResult
        if response:
            info("RemoveGuildSuzerainResponse.onSuzerainRemovedResponse response: %s" % self.I.MD.pretty(response))
            isOk = response.get("ok") or 0
            if isOk:
                data = "Suzerain was removed from guild %d" % self.acc.GuildData.GuildAuid
                self.I.STATS.addGMOperation(0, GMOperationType.GuildSuzerainChange, self.gmLogin, data)
                self.result = AccountManagementAPI.ttypes.RequestResult.Success

        self.fin()


class StopGuildSiegeResponse(GuildOperationResponse):
    """ Attach suzerain to a free guild"""
    def __init__(self, handler, auid, gmLogin):
        GuildOperationResponse.__init__(self, handler, auid)
        self.auid = auid
        self.gmLogin = gmLogin

    def getHashCode(self):
        return "stop_guild_siege%d" % self.auid

    def do2(self):
        if self.acc.GuildData.GuildInfo.GMLockTime > int(time.time()):
            if self.acc.SiegeData.isTarget(self.acc.GuildData.GuildAuid):
                self.I.SIEGE.destroySiege(self.acc.GuildData.GuildAuid, safe=False, callback=self.onSiegeDestroyed)
                return
            else:
                self.result = AccountManagementAPI.ttypes.RequestResult.SiegeNotExists
        else:
            self.result = AccountManagementAPI.ttypes.RequestResult.GuildLockRequired
        self.fin()

    def onSiegeDestroyed(self, response):
        self.result = AccountManagementAPI.ttypes.RequestResult.BadResult
        if response:
            info("StopGuildSiegeResponse.onSiegeDestroyed response: %s" % self.I.MD.pretty(response))
            isOk = response.get("ok") or 0
            if isOk:
                self.I.STATS.addGMOperation(0, GMOperationType.GuildStopSiege, self.gmLogin, str(self.acc.GuildData.GuildAuid))
                self.result = AccountManagementAPI.ttypes.RequestResult.Success
                self.fin()
                return

        self.fin()

class GetFullGuildDumpResponse(GuildOperationResponse):
    def __init__(self, handler, auid, zip):
        GuildOperationResponse.__init__(self, handler, auid)
        self.auid = auid
        self.zip = zip

    def getHashCode( self ):
        return "get_full_dump_%d_%d" % (self.auid, self.zip)

    def do2( self ):
        json_data = self.acc.GuildData.generateJsonDict()
        str_data = json_dumps(json_data)
        encoded_userdata = str_data.encode("latin1")
        self.result = AccountManagementAPI.ttypes.StringDataResponse(AccountManagementAPI.ttypes.RequestResult.Success,
                                                                     encoded_userdata)
        self.fin()

class GuildManagementServerHandler(AccountManagementAPI.AccountManagement.Iface):
    """ """
    def __init__(self, handler):
        self.handler = handler
        self.service = handler.service
        self.I = handler.I
        self.asyncProcessors = dict()

    @staticmethod
    def getProcessorClass():
        return AccountManagementAPI.AccountManagement.Processor

    def ProcessAsync( self, processor ):
        hash = processor.getHashCode()
        if hash in self.asyncProcessors:
            realProcessor = self.asyncProcessors[hash]
            result = realProcessor.getResult()
            self.asyncProcessors.pop( hash )
            return result
        else:
            self.asyncProcessors[hash] = processor
            startResult = processor.start()
            if startResult:
                self.asyncProcessors.pop( hash )
            result = processor.getResult()
            return result

    def GetGuildByName(self, shortname, fullname):
        info( "GuildManagementServerHandler::GetGuildByName %s, %s" % (shortname, fullname) )
        processor = GetGuildByNameResponse( self.handler, shortname, fullname )
        return self.ProcessAsync( processor )

    def GetGuildById(self, auid):
        info( "GuildManagementServerHandler::GetGuildById %d" % auid )
        processor = GetGuildByIdResponse2( self.handler, auid )
        return self.ProcessAsync( processor )

    def GetGuildMemberById(self, auid, memberid):
        info( "GuildManagementServerHandler::GetGuildMemberById %s, %s" % (auid, memberid) )
        processor = GetGuildMemberByIdResponse( self.handler, auid, memberid )
        return self.ProcessAsync( processor )

    def EditGuild(self, guildInfo, gmLogin):
        info("GuildManagementServerHandler::EditGuild %d, %s, %s" % (guildInfo.guildid, guildInfo.shortname, guildInfo.fullname))
        processor = EditGuildResponse(self.handler, guildInfo, gmLogin)
        return self.ProcessAsync(processor)

    def ChangeGuildLeader(self, auid, leader, gmLogin):
        info( "GuildManagementServerHandler::ChangeGuildLeader %d, %d" % ( auid, leader ) )
        processor = ChangeGuildLeaderResponse( self.handler, auid, leader, gmLogin )
        return self.ProcessAsync( processor )

    def EditGuildMember(self, auid, member, gmLogin):
        info( "GuildManagementServerHandler::EditGuildMember %d, %r" % ( auid, member ) )
        processor = EditGuildMemberResponse( self.handler, auid, member, gmLogin )
        return self.ProcessAsync( processor )

    def RemoveGuildMembers(self, auid, members, gmLogin):
        info( "GuildManagementServerHandler::RemoveGuildMembers %d, %r" % ( auid, members ) )
        processor = RemoveGuildMembersResponse( self.handler, auid, members, gmLogin )
        return self.ProcessAsync( processor )

    def SetGuildIcon(self, auid, image):
        info( "GuildManagementServerHandler::SetGuildIcon %d" % ( auid ) )
        processor = SetGuildIconResponse( self.handler, auid, image )
        return self.ProcessAsync( processor )

    def SwitchToNewGuildIcon(self, auid, gmLogin):
        info( "GuildManagementServerHandler::SwitchToNewGuildIcon %d" % ( auid ) )
        processor = SwitchToNewGuildIconResponse( self.handler, auid, gmLogin )
        return self.ProcessAsync( processor )

    def GetFreeGuildBankTalents(self, auid):
        info( "GuildManagementServerHandler::GetFreeGuildBankTalents %d" % ( auid ) )
        processor = GetFreeGuildBankTalentsResponse( self.handler, auid )
        return self.ProcessAsync( processor )

    def GetTakenGuildBankTalents(self, auid):
        info( "GuildManagementServerHandler::GetTakenGuildBankTalents %d" % ( auid ) )
        processor = GetTakenGuildBankTalentsResponse( self.handler, auid )
        return self.ProcessAsync( processor )

    def ReturnTalentToGuildBank(self, auid, talentid, gmLogin):
        info( "GuildManagementServerHandler::ReturnTalentToGuildBank %d %d" % ( auid, talentid ) )
        processor = ReturnTalentToGuildBankResponse( self.handler, auid, talentid, gmLogin )
        return self.ProcessAsync( processor )

    def ReturnTalentToOwner(self, auid, talentid, gmLogin):
        info("GuildManagementServerHandler::ReturnTalentToOwner %d %d" % (auid, talentid))
        processor = ReturnTalentToOwnerResponse( self.handler, auid, talentid, gmLogin )
        return self.ProcessAsync( processor )

    def AcquireGuildLock(self, auid, gmLogin):
        info("GuildManagementServerHandler::AcquireGuildLock %d" % auid)
        processor = AcquireGuildLockResponse(self.handler, auid, gmLogin)
        return self.ProcessAsync(processor)

    def ReleaseGuildLock(self, auid, gmLogin):
        info("GuildManagementServerHandler::ReleaseGuildLock %d" % auid)
        processor = ReleaseGuildLockResponse(self.handler, auid, gmLogin)
        return self.ProcessAsync(processor)

    def AddGuildSuzerain(self, auid, suzerainAuid, gmLogin):
        info("GuildManagementServerHandler::AddGuildSuzerain %d" % auid)
        processor = AddGuildSuzerainResponse(self.handler, auid, suzerainAuid, gmLogin)
        return self.ProcessAsync(processor)

    def RemoveGuildSuzerain(self, auid, gmLogin):
        info("GuildManagementServerHandler::RemoveGuildSuzerain %d" % auid)
        processor = RemoveGuildSuzerainResponse(self.handler, auid, gmLogin)
        return self.ProcessAsync(processor)

    def StopGuildSiege(self, auid, gmLogin):
        info("GuildManagementServerHandler::StopGuildSiege %d" % auid)
        processor = StopGuildSiegeResponse(self.handler, auid, gmLogin)
        return self.ProcessAsync(processor)

    def GetFullGuildDump(self, auid, zip):
        info("GuildManagementServerHandler::GetFullGuildDump %d" % auid)
        processor = GetFullGuildDumpResponse(self.handler, auid, zip)
        return self.ProcessAsync(processor)
