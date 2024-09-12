# -*- coding: utf-8 -*-
#
# Thrift Agent web-server: принимает внешние запросы по thrift, мапит их на внутрикластерные http-запросы
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *
import traceback
from functools import partial
from base.wstools import AddLoopCallback
##---------------------------------------------------------------------------------------------------

addRelPath('gen-py')

import AccountManagementAPI.AccountManagement
import AccountManagementAPI.ttypes

from handlers import logins, users, touch
import party_const
from ext_pw import SetFractionAction
from ext_main.nickname import SetNicknameAction
from ext_main.gender import SetGenderAction
from ext_main.login import LogoutAction
from ext_main.wipe import *
from modeldata.changes import *
from logic.remove_talents import *
from logic.add_talent import *
from logic.change_fraction_GM import *
from logic.change_fraction import *
from logic.ban_account import *
from logic.mute_account import *
from logic.buy_premium_account_gm import *
from logic.buy_unban_gm import *
from logic.buy_premium_account import *
from logic.get_prices import *
from logic.building_remove import *
from logic.move_to_pocket import *
from logic.buy_tournament_ticket import *

from thrift_handler import AsyncThriftException
from AccountManagementAPI.ttypes import RequestResult, StringDataResponse, ServerActionResponse, PayServiceType, PriceServiceInfo, PriceServiceDataResponse, UserOperationType, LocaleInfo, LocaleInfoResponse, PayTicketType
from modeldata.persistent_data import PersistentDataManager

import StatisticCore.ttypes
from StatisticCore.ttypes import GMOperationType, TalentChangeOperation, RuneRollSource

from logic.change_nickname import *
from logic.purchase_guild_icon_change import *


from modeldata.ModelData import ModelData

from subaction import SubAction
from binascii import crc32
from enums import *
from MM import ESex
import CC

class AccountManagementServerHandler(AccountManagementAPI.AccountManagement.Iface):
    """ """
    def __init__( self, handler ):
        self.handler = handler
        self.service = handler.service
        self.I = handler.I

    @staticmethod
    def getProcessorClass():
        return AccountManagementAPI.AccountManagement.Processor

    def GMToolBan( self, acc ):
        if not acc.db.banned or ( (acc.db.bantime < (time.time()+60)) and acc.db.bantime != 0 ):
            subParams = ClassDict( minutes=[1], reason=[u"Над Вашим аккаунтом проводятся технические работы, зайдите попозже"], autoBan=[1], rid=[1] )
            accountAction = Ban_account( subParams, partial(self.callbackFnAuid, auid=acc.auid), I=self.handler.I, acc=acc, uid=acc.uid )
            accountAction.onStart()
          
    def FillAccountInfo( self, acc ):
        if acc:
            if not acc.banned: # если только не включено "экстренное выпинывание" нашего юзера после какой-то операции, требующей релогина
                touch( acc ) # не удаляйте пока этот аккаунт, мы им интересуемся

            if not acc.model:
                warn("onAggregatorGetUserSnList: acc model not loaded (yet?) for %s %s", self.snid, self.snuid)
                resInfo = AccountManagementAPI.ttypes.RequestResult.ServerReturnedNull
                accInfo = AccountManagementAPI.ttypes.AccountInfo( snid="Account ModelData is null", snuid="Account ModelData is null" )
                return AccountManagementAPI.ttypes.AccountInfoResponse( accountInfo = accInfo, result = resInfo )

            # Заполняем данные по бану
            newBan = acc.db.bantime
            newBanFlag = 0
            if acc.db.banned:
                if acc.db.bantime == 0:
                    newBanFlag = 2
                else:
                    newBanFlag = 1
            # Заполняем данные по муту
            newMute = acc.db.mutetime
            newMuteFlag = 0
            if acc.db.muted:
                if acc.db.mutetime == 0:
                    newMuteFlag = 2
                else:
                    newMuteFlag = 1

            premiumAccountEnd = acc.model.LordInfo.PremiumAccountEnd
            if not acc.model.IsPremiumAccount():
                premiumAccountEnd = 0



            seasons_awards = []
            all_season_settings = acc.SD.getAllSeasons()
            for one_season_info in all_season_settings:
                is_found_awards = False
                for awards_id in acc.model.SeasonAwardsKeeper:
                    awards_info = acc.model.getSeasonAwardsByID(awards_id)
                    if crc32(one_season_info["persistentId"]) == awards_info.SeasonId:
                        is_found_awards = True
                        season = acc.SD.findSeasonById(awards_info.SeasonId)

                        static_skin = acc.SD.getStaticSkinByPersistentId(awards_info.Skin)
                        export_skin_name = ""
                        if static_skin:
                            export_skin_name = static_skin["persistentId"]

                        export_season_awards = AccountManagementAPI.ttypes.SeasonAwards( seasonId = awards_info.SeasonId,
                                                                                         seasonName = utf8convert(season["nameSeason"]),
                                                                                         startDate = season["startTime"],
                                                                                         endDate = season["stopTime"],
                                                                                         perls = awards_info.RedPerls,
                                                                                         skin = export_skin_name,
                                                                                         flag = awards_info.Flag,
                                                                                         talents = str(awards_info.Talents.keys()).strip('[]'),
                                                                                         lootboxes = str(awards_info.Lootboxes.keys()).strip('[]'))
                        seasons_awards.append(export_season_awards)
                        break

                if not is_found_awards:
                    season = acc.SD.findSeasonById(crc32(one_season_info["persistentId"]))
                    export_season_awards = AccountManagementAPI.ttypes.SeasonAwards( seasonId = crc32(one_season_info["persistentId"]),
                                                                                         seasonName = utf8convert(season["nameSeason"]),
                                                                                         startDate = season["startTime"],
                                                                                         endDate = season["stopTime"])
                    seasons_awards.append(export_season_awards)


            info( "FillAccountInfo: auid=%s, snuid=%r, nickname=%r", acc.auid, acc.snuid, acc.nick)
            geo_ovr = acc.db.get("geo_ovr", {})

            # fill currencies
            currenciesDict = acc.model.Resources.Currencies.dictionary
            currencyNamesFromSD = map(lambda e: e['Id'], acc.SD.data['currencies']['CurrencyList']['Item'])

            for currencyName in currencyNamesFromSD:
                if currencyName not in currenciesDict:
                    currenciesDict[currencyName] = 0

            accInfo = AccountManagementAPI.ttypes.AccountInfo(
                snid=acc.snid, snuid=acc.snuid, login=acc.login,
                registerdate = acc.db.registration_date, email="TODO",
                nickname=acc.nick, online=acc.online, auid=acc.auid,
                gold = acc.model.Resources.Gold,
                silver = acc.model.Resources.Silver, fame = acc.model.LordInfo.Fame,
                resource1 = acc.model.Resources.Resource1, resource2 = acc.model.Resources.Resource2,
                resource3 = acc.model.Resources.Resource3, perl = acc.model.Resources.Perl,
                redPerl = acc.model.Resources.RedPerl, cwplayerpoints = acc.model.Resources.CWPoints_Player, Shard = acc.model.Resources.Shard, currencies = currenciesDict,
                reliability = acc.model.LordInfo.Reliability, location = acc.geolocation,
                isDeveloper = acc.db.IsDeveloper, banned = newBan,
                banFlag = newBanFlag, muted = newMute, muteFlag = newMuteFlag,
                fraction = party_const.getPartyFraction( acc.db.fraction ),
                nickChanges = acc.db.nickChanged, gender = acc.db.sex,
                nickChangesFree = acc.getConfigValue("FREE_NICK_CHANGES"),
                fractionChanges = acc.db.fractionChanged,
                fractionChangesFree = acc.getConfigValue("FREE_FRACTION_CHANGES"),
                premiumAccountDate = premiumAccountEnd, lordRating = acc.model.getRating(),
                numberOfWins = acc.model.LordInfo.GuardInfo.NumberOfWins, dodges = acc.model.LordInfo.GuardInfo.Dodges,
                retiredTime = acc.model.LordInfo.GuardInfo.RetiredTime,
                guardRating = acc.model.getPublicRating(), guildid = acc.db.guildAuid,
                guildBuildingLevel = acc.model.getGuildBuildingLevel( acc.SD ),
                isSpectator = acc.db.IsSpectator, hasLamp = acc.model.hasLamp(),
                lastPaymentTime = acc.model.Statistics.LastPaymentTime,
                lastLampDropTime = acc.model.Statistics.LastLampDropTime,
                joinedSnids = acc.snlist, isRegularMMAllowed= acc.db.isRegularMMAllowed,
                locale = acc.db.locale,
                muid = acc.db.muid,
                country = utf8convert(acc.db.get("gcountry",'')),
                region = utf8convert(acc.db.get("gregion",'')),
                city = utf8convert(acc.db.get("gcity",'')),
                gmcountry = utf8convert(geo_ovr.get("country",'')),
                gmregion = utf8convert(geo_ovr.get("region",'')),
                gmcity = utf8convert(geo_ovr.get("city",'')),
                leaverPoints = acc.model.LordInfo.GuardInfo.LeavesPoint,
                isLeaver = acc.model.LordInfo.GuardInfo.isLeaver,
                isBadBehaviour = acc.model.LordInfo.GuardInfo.isBadBehaviour,
                canMute = acc.db.IsModerator,
                PlayerRating = acc.model.getPlayerRating(),
                PlayerRatingHero = acc.model.LordInfo.Ratings.MaxPRHero,
                PlayerRatingHeroLastPlayed = acc.model.LordInfo.Ratings.MaxPRHeroLastPlayed,
                numberOfWinsForPR = acc.model.LordInfo.Ratings.NumberOfWinsForPR,
                extraComplaints = acc.model.LordInfo.ExtraComplaints,
                extraSessionComplaints = acc.model.LordInfo.ExtraComplaintsSession,
                listSeasonsAwards = seasons_awards,
             )
            if acc.data.mm:
                accInfo.currentsession = toint(acc.data.mm.game_id)
            resInfo = AccountManagementAPI.ttypes.RequestResult.Success
        else:
            # по какой-то причине нет аккаунта.. вернем пустую запись
            warn("Account is null")
            resInfo = AccountManagementAPI.ttypes.RequestResult.SnUidNotExist
            accInfo = AccountManagementAPI.ttypes.AccountInfo( snid="Account is null", snuid="Account is null" )
            
        return AccountManagementAPI.ttypes.AccountInfoResponse( accountInfo = accInfo, result = resInfo )


    # ------------------ AccountManagement.Iface ------------------------------------
    def GetAccountBySNUidOld( self, snid, snuid ):
        acc = self.handler.I.WS.getUserAccSN( snid, snuid ) # достанем из соц.сервера аккаунт юзера
        return self.FillAccountInfo( acc )
        
    # ----------------------------------------------
    def GetAccountBySNUid(self, snid, snuid):
        info("GetAccountBySNUid(%s, %s)", snid, snuid)
        self.snid = snid
        self.snuid = snuid
        acc = self.handler.I.WS.getUserAccSN(snid, snuid) # достанем из соц.сервера аккаунт юзера
        if not acc:
            warn("acc not found for GetAccountBySNUid(%s,%s)", snid, snuid)
            return self.FillAccountInfo(acc)
        if getattr(self, 'aggregator_call_ok', 0):
            # вызов к аггрегатору уже исполнен, возвращаем ответ
            return self.FillAccountInfo(acc)
        # нужен асинхронный запрос к аггрегатору;
        cb = partial(self.onAggregatorGetUserSnList, acc=acc)
        self.handler.I.AGG.getUserSnList(snid, snuid, callback=cb)
        # после запроса временно срубим исполнение thrift-обработчика специальным exception-ом
        raise AsyncThriftException("async aggregator call")

    def onAggregatorGetUserSnList(self, agg_response, acc):
        info("onAggregatorGetUserSnList: agg-response %s", agg_response)
        #acc = self.handler.I.WS.getUserAccSN(self.snid, self.snuid) # достанем из соц.сервера аккаунт юзера
        if acc:
            if 'snlist' in agg_response:
                acc.snlist = agg_response['snlist']
            self.aggregator_call_ok = 1
            self.handler.process() # вызываем повторную обработку евента (теперь должно вернуть ответ)
        else:
            warn("onAggregatorGetUserSnList: acc not found for %s %s",self.snid, self.snuid)
            self.FillAccountInfo(acc)

    # ------------------------------------------------------------------------

    ## вариант для string GetFullUserDump(...)
    #~ def GetFullUserDump( self, login, zip ):
        #~ self.login = login
        #~ acc = self.I.WS.getUserAcc( self.login )
        #~ if acc:
            #~ if acc.db.agg_properties != None:
                #~ if acc.db.agg_properties:
                    #~ #TODO: завернуть дамп
                    #~ info( "GetFullUserDump: wrapping data dump: login=%s, zip=%s" % (login, zip) ) 
                    #~ new_data_unicode = PersistentDataManager.saveData( acc, zip )
                    #~ encoded_userdata = new_data_unicode.encode("latin1")
                    #~ acc.db.pop( "agg_properties", None ) # удаляем за собой
                    #~ return encoded_userdata
                #~ else:
                    #~ err("GetFullUserDump error, aggregator properties fail for login %s" % login)
                    #~ return ""
            #~ elif acc.auid:
                #~ # нужен асинхронный запрос к аггрегатору; 
                #~ self.I.AGG.getInfo( acc.auid, None, include_secure_data=0, callback=self.onGetAggProperties )
                #~ # после запроса временно срубим исполнение thrift-обработчика специальным exception-ом
                #~ raise AsyncThriftException("async aggregator call")
        #~ else:
            #~ err("ResetUserAccount error, get acc by login(%s) fail" % login)
            #~ return ""
            
    ## вариант для StringDataResponse GetFullUserDump(...)
    def GetFullUserDump( self, login, zip ):
        self.login = login
        acc = self.I.WS.getUserAcc( self.login )
        if acc:
            if acc.db.agg_properties != None:
                if acc.db.agg_properties:
                    #TODO: завернуть дамп
                    info( "GetFullUserDump: wrapping data dump: login=%s, zip=%s" % (login, zip) ) 
                    new_data_unicode = PersistentDataManager.saveData( acc, zip )
                    encoded_userdata = new_data_unicode.encode("latin1")
                    acc.db.pop( "agg_properties", None ) # удаляем за собой
                    return StringDataResponse( RequestResult.Success, encoded_userdata )
                else:
                    err("GetFullUserDump error, aggregator properties fail for login %s" % login)
                    return StringDataResponse( RequestResult.BadResult )
            elif acc.auid:
                # нужен асинхронный запрос к аггрегатору; 
                self.I.AGG.getInfo( acc.auid, None, include_secure_data=0, callback=self.onGetAggProperties )
                # после запроса временно срубим исполнение thrift-обработчика специальным exception-ом
                raise AsyncThriftException("async aggregator call")
        else:
            err("ResetUserAccount error, get acc by login(%s) fail" % login)
            return StringDataResponse( RequestResult.LoginNotExist )
            
    def onGetAggProperties( self, agg_response ):
        info( "onGetAggProperties: agg-response %s" % agg_response )
        acc = self.I.WS.getUserAcc( self.login )
        if acc:
            agg_info = agg_response.get('get_info') or {}
            agg_properties = agg_info.get('props') or {}
            acc.db.agg_properties = agg_properties
            # заодно давайте уж достанем sn_nick
            fsn = agg_properties.get('fsn')
            if fsn:
                sn_info = agg_info.get(fsn) or {}
                sn_nick = sn_info.get('name')
                if sn_nick:
                    acc.db.sn_nick = sn_nick
        self.handler.process() # вызываем повторную обработку евента (теперь должно вернуть ответ)        
        
    # ------------------------------------------------------------------------
    def ApplyFullUserDump( self, login, dumpdata ):
        self.login = login
        acc = self.I.WS.getUserAcc( login )
        if acc:
            acc.oldGuildAuid = acc.db.guildAuid
            if not acc.full_dump_applied:
                # - временно заблокируем юзера
                acc.banned = 1
                self.old_nick = acc.nick
                info( "ApplyFullUserDump: login %s, auid %s, dumpdata: %s\n...\n%s ", login, acc.auid, dumpdata[:128], dumpdata[-128:] )
                # - накатить дамп данных на acc и в аггрегатор (пачка setProperty)
                unicode_data = unicode( dumpdata, "latin1" )

                # добавим callback, который вызовется по окончании загрузки
                acc.on_loaded_callbacks = acc.on_loaded_callbacks or []
                acc.on_loaded_callbacks.append( self.onUserDumpApplied )
                self.I.PDM.loadAccountData( acc, unicode_data )
                
                # нужно попихать свойства в аггрегатор (это можно, наверное, не контролировать асинхронно)
                if acc.db.agg_properties:
                    _aggregatorProperties = ["nick", "fame", "fraction"]
                    for prop_name in _aggregatorProperties:
                        prop_value = acc.db.agg_properties.get(prop_name)
                        if prop_value is not None:
                            self.I.AGG.setProperty( acc.auid, prop_name, prop_value )
                acc.db.pop("agg_properties", None) # зачищаем за собой
                
                # ждем асинхронной обработки; временно срубим исполнение thrift-обработчика специальным exception-ом
                raise AsyncThriftException("async apply data dump")
                
            else:
                # ок, получили callback по окончании применения данных; можно отвечать, что все получилось.
                info( "ApplyFullUserDump: success (login %s, auid %s)", self.login, acc.auid)
                acc.ka = 0 # вызываем автоматический логаут аккаунта, причем из-за лока/бана никто не может нам помешать
                return RequestResult.Success
                
        else:
            err("ApplyFullUserDump error, get acc by login(%s) fail" % login)
            return RequestResult.LoginNotExist

    # асинхронный callback, по окончании загрузки аккаунта из persistent
    def onUserDumpApplied( self, acc ):
        info( "onUserDumpApplied: login %s, auid %s", self.login, acc.auid )

        debug( "onUserDumpApplied change_nickname: old = %s, new= %s", self.old_nick, acc.nick )
        if acc.nick != self.old_nick:
            self.nickname_utf8 = utf8convert(acc.nick)
            #self.handler.I.SQL.setNick( acc.uid, self.nickname_utf8, self.dummy_callback )
            self.handler.I.SQL.removeOldNick(acc.uid, self.old_nick, self.nickname_utf8)
            subParams = ClassDict( nickname=[acc.nick] )
            accountAction = SetNicknameAction( subParams, self.dummy_callback, I=self.handler.I, acc=acc, uid=acc.uid )
            accountAction.onStart()

        acc.full_dump_applied = 1
        acc.db.guildAuid = acc.oldGuildAuid
        self.handler.process() # вызываем повторную обработку евента (теперь должно вернуть ответ)        

    def dummy_callback(self, response):
        info( "dummy_callback: response %s", response )

    # ------------------------------------------------------------------------
    def RemoveFakeAuid( self, login ):
        self.login = login
        acc = self.I.WS.getUserAcc( login )
        if acc:
            return RequestResult.Success
        else:
            err("RemoveFakeAuid error, get acc by login(%s) fail" % login)
            return RequestResult.LoginNotExist            
        
    # ------------------------------------------------------------------------
    def EditFreeChanges(self, login, gmLogin, nickChanges, fractionChanges):
        acc = self.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )
            if acc.db.nickChanged != toint(nickChanges):
                self.handler.I.STATS.addGMEditUser(acc.auid, gmLogin, "nickChanges",
                                                   str(acc.db.nickChanged), str(nickChanges))
                acc.db.nickChanged = toint(nickChanges)
            if acc.db.fractionChanged != toint(fractionChanges):
                self.handler.I.STATS.addGMEditUser(acc.auid, gmLogin, "fractionChanges",
                                                   str(acc.db.fractionChanged), str(fractionChanges))
                acc.db.fractionChanged = toint(fractionChanges)
            self.I.WS.saveUserData( acc )
            return RequestResult.Success
        else:
            err("SetFreeChangeLimits error, get acc by login(%s) fail" % login)
            return RequestResult.LoginNotExist            
            
    # ------------------------------------------------------------------------
    def ResetUserAccount( self, login, gmLogin ):
        self.login = login
        acc = self.handler.I.WS.getUserAcc( self.login )
        if acc:
            self.GMToolBan( acc )
            subParams = ClassDict( fraction=["N"], force_new = [1], full_reset=[1] )
            resetAccountAction = SetFractionAction( subParams, self.callbackFn, I=self.handler.I, acc=acc, uid=acc.uid )
            acc.ka = 0 # и пусть юзера выкинет с сервера на следующем тике, чтобы данные сохранились
            resetAccountAction.onStart()
        else:
            err("ResetUserAccount error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success

    def callbackFn(self, response):
        acc = self.handler.I.WS.getUserAcc(self.login)
        if acc:
            SubAction._postponeResponseChanges(response, acc) # переносим накопленные response model changes в acc.pending_changes
        if not response.get("ok"):
            err("Callback failed: response %s", response)

    def callbackFnAuid(self, response, auid):
        acc = self.handler.I.WS.getUserAccByAuid(auid)
        if acc:
            SubAction._postponeResponseChanges(response, acc) # переносим накопленные response model changes в acc.pending_changes
        if not response.get("ok"):
            err("Callback failed: response %s" % response)


    def GetAccountLibrary( self, login ):
        acc = self.handler.I.WS.getUserAcc( login )
        libList = []
        if acc:
            acc.model.write( acc.pending )
            for talentId in acc.model.UserInventory:
                talent = acc.model.getTalentByID(talentId)
                isBounded = not (talent.Soulbound == IGuidGenerator.InvalidUID or talent.Soulbound.get() == None)
                if isBounded:
                    boundHeroId = talent.Soulbound.get().getID()
                    boundClassId = talent.Soulbound.get().PersistentId
                else:
                    boundHeroId = 0
                    boundClassId = 0

                libList.append(AccountManagementAPI.ttypes.TalentInfo( talentClassId = talent.PersistentId,
                                                                       talentInstanceId = talent.getID(),
                                                                       refineRate = talent.Points,
                                                                       boundHeroClassId = boundClassId,
                                                                       boundHeroInstanceId = boundHeroId))

            resInfo = AccountManagementAPI.ttypes.RequestResult.Success
        else:
            err("GetAccountInventory error, get acc by login(%s) fail" % login)
            resInfo = AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        
        return AccountManagementAPI.ttypes.LibraryResponse( result = resInfo, libraryList = libList )

    def GetAccountHeroes( self, login ):
        acc = self.handler.I.WS.getUserAcc( login )
        heroList = []
        if acc:
            acc.model.write( acc.pending )
            for heroId in acc.model.Heroes:
                hero = acc.model.getHeroByID(heroId)
                if hero.Hired:

                    heroList.append(AccountManagementAPI.ttypes.HeroInfo(heroClassId=hero.PersistentId,
                                                                  heroInstanceId=heroId,
                                                                  experience=hero.Experience,
                                                                  rating=hero.Rating,
                                                                  epicWins=hero.EpicWins))
            resInfo = AccountManagementAPI.ttypes.RequestResult.Success
        else:
            err("GetAccountHeroes error, get acc by login(%s) fail" % login)
            resInfo = AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.HeroesResponse( result = resInfo, heroesList = heroList )

    def GetHeroTalentSet(self, login, heroInstanceId):
        acc = self.handler.I.WS.getUserAcc(login)
        tsList = []
        if acc:
            acc.model.write(acc.pending)
            hero = acc.model.getHeroByID(heroInstanceId)
            if hero:
                for tsId in hero.TalentSets.keys():
                    ts = []
                    for pos, talentId in hero.TalentSets[tsId].Talents.iteritems():
                        talent = acc.model.getTalentByID(talentId)
                        ts.append(AccountManagementAPI.ttypes.TalentInfo(talentClassId = talent.PersistentId,
                                                                         talentInstanceId = talent.getID(),
                                                                         refineRate = talent.Points,
                                                                         boundHeroClassId = hero.PersistentId,
                                                                         boundHeroInstanceId = hero.getID()))
                    tsList.append(AccountManagementAPI.ttypes.TalentSetInfo(talentSetId = tsId,
                                                                            talents = ts))
                resInfo = AccountManagementAPI.ttypes.RequestResult.Success
            else:
                err("GetHeroTalentSet error, hero(%d) is null" % heroInstanceId)
                resInfo = AccountManagementAPI.ttypes.RequestResult.HeroInstIdNotExist
        else:
            err("GetHeroTalentSet error, get acc by login(%s) fail" % login)
            resInfo = AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.TalentSetResponse( result = resInfo, talentSetList = tsList )

    def GetHeroSeasonsInfo(self, login, heroInstanceId):
        acc = self.handler.I.WS.getUserAcc(login)
        array_seasons_info = []
        if acc:
            acc.model.write(acc.pending)
            hero = acc.model.getHeroByID(heroInstanceId)
            if hero:
                all_season_settings = acc.SD.getAllSeasons()
                for one_season_info in all_season_settings:
                    p_id_season = crc32(one_season_info["persistentId"])
                    season = acc.SD.findSeasonById(p_id_season)
                    is_found_info = False
                    for seasonId in hero.SeasonsInfo:
                        season_info = acc.model.getSeasonInfoByID(seasonId)
                        if season_info and season_info.SeasonId == p_id_season:
                            is_found_info = True
                            export_season_info = AccountManagementAPI.ttypes.SeasonInfo( seasonId = season_info.SeasonId,
                                                                                         seasonName = utf8convert(season["nameSeason"]),
                                                                                         startDate = season["startTime"],
                                                                                         endDate = season["stopTime"],
                                                                                         seasonRating = season_info.SeasonRating,
                                                                                         leagueIndex = season_info.LeagueIndex,
                                                                                         curLeaguePlace = season_info.CurLeaguePlace,
                                                                                         bestLeaguePlace = season_info.BestLeaguePlace)
                            array_seasons_info.append(export_season_info)
                            break
                    if not is_found_info:
                        export_season_info = AccountManagementAPI.ttypes.SeasonInfo( seasonId = p_id_season,
                                                                                     seasonName = utf8convert(season["nameSeason"]),
                                                                                     startDate = season["startTime"],
                                                                                     endDate = season["stopTime"])
                        array_seasons_info.append(export_season_info)

                resInfo = AccountManagementAPI.ttypes.RequestResult.Success
            else:
                err("GetHeroTalentSet error, hero(%d) is null" % heroInstanceId)
                resInfo = AccountManagementAPI.ttypes.RequestResult.HeroInstIdNotExist
        else:
            err("GetHeroTalentSet error, get acc by login(%s) fail" % login)
            resInfo = AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.SeasonInfoResponse( result = resInfo, seasonInfoList = array_seasons_info )

    def MoveTalentFromTalentSetToLibrary( self, login, heroInstanceId, talentInstanceId, gmLogin ):
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )
            hero = acc.model.getHeroByID( heroInstanceId )
            if hero:
                talent = acc.model.getTalentByID( talentInstanceId )
                if talent:
                    self.handler.I.STATS.addMoveTalentFromSet( acc.auid, acc.nick, talent.PersistentId, hero.PersistentId, 0 )
                    hero.moveTalentFromTalentSetToLibrary(talent, talentInstanceId)
                else:
                    err("MoveTalentFromTalentSetToLibrary error, talent(%d) is null" % talentInstanceId)
                    return AccountManagementAPI.ttypes.RequestResult.TalentInstIdNotExist
            else:
                err("MoveTalentFromTalentSetToLibrary error, hero(%d) is null" % heroInstanceId)
                return AccountManagementAPI.ttypes.RequestResult.HeroInstIdNotExist
        else:
            err("MoveTalentFromTalentSetToLibrary error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success

    def RemoveTalentFromTalentSet( self, login, heroInstanceId, talentInstanceId, talentSetId, gmLogin ):
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )
            hero = acc.model.getHeroByID( heroInstanceId )
            if hero:
                talent = acc.model.getTalentByID( talentInstanceId )
                if talent:
                    self.handler.I.STATS.addMoveTalentFromSet( acc.auid, acc.nick, talent.PersistentId, hero.PersistentId, 0 )
                    hero.removeTalentFromTalentSet(talentSetId, talent, talentInstanceId)
                else:
                    err("RemoveTalentFromTalentSet error, talent(%d) is null" % talentInstanceId)
                    return AccountManagementAPI.ttypes.RequestResult.TalentInstIdNotExist
            else:
                err("RemoveTalentFromTalentSet error, hero(%d) is null" % heroInstanceId)
                return AccountManagementAPI.ttypes.RequestResult.HeroInstIdNotExist
        else:
            err("RemoveTalentFromTalentSet error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success


    def GiveLamp( self, login, lampInfo, gmLogin, extra_comment=""):
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )

            oldLamp = acc.model.MarketingEventsInfo.LampEventInfo
            self.handler.I.STATS.addGMEditUser(acc.auid, gmLogin, "Lamp",
                                               (str(oldLamp.dbId[oldLamp.dbId.rfind('_') + 1:]) + ', ' + str(oldLamp.BonusLeft) + ', ' + str(oldLamp.TransactionsLeft) + ', ' + str(oldLamp.EndTime - oldLamp.StartTime)) if oldLamp is not None else 'None',
                                               str(lampInfo.Bonus) + ', ' + str(lampInfo.GoldBonus) + ', ' + str(lampInfo.Transaction) + ', ' + str(lampInfo.Duration))
            acc.model.replaceGoldLampEvent(lampInfo.Bonus, lampInfo.GoldBonus, lampInfo.Transaction, lampInfo.Duration)
            lampType = RuneRollSource.DumpTool if gmLogin == "dumptool" else RuneRollSource.GMTool
            rune = acc.model.getGoldLampType(acc.SD)
            self.handler.I.STATS.addLampRoll(acc.auid, rune, lampType)
        else:
            err("GiveLamp error, get acc by login(%s) fail", login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success


    def GetLampInfo( self, login ):
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            if acc.model.hasLamp():
                lampEventInfo = acc.model.MarketingEventsInfo.LampEventInfo
             
                bonus = int( lampEventInfo.dbId[len("/UI/Content/MarketingEvents/GoldLamp_"):] )
                lampModelInfo = AccountManagementAPI.ttypes.LampInfo(
                    Bonus=bonus, GoldBonus=lampEventInfo.BonusLeft, Transaction=lampEventInfo.TransactionsLeft,
                    Duration=int(lampEventInfo.EndTime-int( round( time.time() ) )))
            else:
                lampModelInfo = AccountManagementAPI.ttypes.LampInfo( Bonus=0, GoldBonus=0, Transaction=0, Duration=0 )
    
            return AccountManagementAPI.ttypes.LampInfoResponse( lampInfo = lampModelInfo, result = AccountManagementAPI.ttypes.RequestResult.Success )
        else:
            err("GiveLamp error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist

    def GiveUpgradeHeroTalents(self, login, lampInfo, gmLogin, extra_comment=""):
        acc = self.handler.I.WS.getUserAcc(login)
        if acc:
            acc.model.write(acc.pending)
            oldCount = int(acc.model.MarketingEventsInfo.UpgradeHeroTalentsInfo.UsesLeft)
            self.handler.I.STATS.addGMEditUser(acc.auid, gmLogin, "UpgHeroTal",
                                               str(oldCount),
                                               str(lampInfo.UsesLeft))
            acc.model.MarketingEventsInfo.UpgradeHeroTalentsInfo.UsesLeft = lampInfo.UsesLeft
            lampType = RuneRollSource.DumpToolUpgHeroTal if gmLogin == "dumptool" else RuneRollSource.GMToolUpgHeroTal
            self.handler.I.STATS.addLampRoll(acc.auid, acc.model.getUpgHeroLampType(), lampType, runescountold=oldCount, runescountnew=lampInfo.UsesLeft)
        else:
            err("GiveUpgradeHeroTalents error, get acc by login(%s) fail", login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success

    def GetUpgradeHeroTalentsInfo(self, login):
        acc = self.handler.I.WS.getUserAcc(login)
        if acc:
            if acc.model.MarketingEventsInfo.UpgradeHeroTalentsInfo.UsesLeft > 0:
                lampModelInfo = AccountManagementAPI.ttypes.UpgradeHeroTalentsInfo(
                    UsesLeft=acc.model.MarketingEventsInfo.UpgradeHeroTalentsInfo.UsesLeft)
            else:
                lampModelInfo = AccountManagementAPI.ttypes.UpgradeHeroTalentsInfo(UsesLeft=0)

            return AccountManagementAPI.ttypes.UpgradeHeroTalentsInfoResponse(upgradeHeroTalentsInfo=lampModelInfo,
                                                                result=AccountManagementAPI.ttypes.RequestResult.Success)
        else:
            err("GiveLamp error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist


    def DisjointSN(self, auid, snid):
        info("DisjointSN(%s, %s)", auid, snid)
        if hasattr(self, 'disjointSnResult'):
            if self.disjointSnResult == 0:
                return RequestResult.Success
            elif self.disjointSnResult == 29:
                return RequestResult.CantDisjointFsn
            elif self.disjointSnResult == 10:
                return RequestResult.AuidNotExist
            return RequestResult.BadResult

        self.auid = auid
        self.snid = snid

        acc = self.handler.I.WS.getUserAccByAuid(auid)
        if not acc:
            err("DisjointSN: no user account found for auid %s", auid)
            return RequestResult.AuidNotExist
        acc.banned = 1
        self.guildAuid = acc.db.guildAuid
        self.handler.I.AGG.deleteSn(auid, snid, callback=self.onAggregatorDeleteSn)
        # после запроса временно срубим исполнение thrift-обработчика специальным exception-ом
        raise AsyncThriftException("async aggregator call")


    def onAggregatorDeleteSn(self, agg_response):
        info("onAggregatorDeleteSn: agg-response %s", agg_response)
        if agg_response.get('error', None):
            err("delete_sn returned error: %s, %s", agg_response['error'], agg_response['message'])
            self.disjointSnResult = agg_response['error']

        else:
            self.disjointSnResult = 0
            snuid = agg_response.get('snuid', '')
            if self.snid and snuid:
                login = str("%s#%s" % ( self.snid, snuid ))
                self.handler.I.WS.serverSubLogin( login, persistent_callback=self.ChangeGuildMember)

        self.handler.process() # вызываем повторную обработку евента (теперь должно вернуть ответ)
        return

    def DeleteSAAccount(self, auid):
        info("DeleteSAAccount", auid)
        if hasattr(self, 'deleteSAAccountResult'):
            if self.deleteSAAccountResult == 0:
                return RequestResult.Success
            return RequestResult.BadResult

        self.auid = auid
        acc = self.handler.I.WS.getUserAccByAuid(auid)
        if acc:
            acc.ka = 0
            acc.banned = 1

        self.handler.I.AGG.deleteAccount(auid, callback=self.__onDeleteSAAccount)
        raise AsyncThriftException("async DeleteSAAccount call")

    def __onDeleteSAAccount(self, response):
        info("__onDeleteSAAccount: response %s", response)
        if response.get('error', None):
            err("delete_account returned error: %s, %s", response['error'], response['message'])
            self.deleteSAAccountResult = response['error']
            self.handler.process()
            return

        self.deleteSAAccountResult = 0
        # auid = response.get('auid', 0)
        self.handler.process()


    def ChangeGuildMember(self, acc):
        info( "DisjointSN.ChangeGuildMember acc.db.guildAuid=%s, guildAuid=%s (old_auid %s), acc is None: %s", acc.db.guildAuid, self.guildAuid, self.auid, acc is None )
        if acc and acc.model:
            acc.model.write( acc.pending )
            guildbuilding = acc.model.getGuildBuilding(acc.SD)
            if guildbuilding:
                if not acc.db.guildAuid:
                    acc.db.guildAuid = self.guildAuid
                acc.db.oldAuid = self.auid

        #self.handler.process()

    def ChangeFSN(self, auid, snid):
        info("ChangeFSN(%s, %s)", auid, snid)
        acc = self.handler.I.WS.getUserAccByAuid(auid)
        if not acc:
            err("ChangeFSN: no user account found for auid %s", auid)
            return RequestResult.AuidNotExist
        if hasattr(self, 'changeFSnResult'):
            info("ChangeFSN: success (fsn = %s, auid %s)" % (snid, auid))
            acc.ka = 0  # вызываем автоматический логаут аккаунта, причем из-за лока/бана никто не может нам помешать
            if self.changeFSnResult == 0:
                return RequestResult.Success
            elif self.changeFSnResult == 29:
                return RequestResult.CantDisjointFsn
            elif self.changeFSnResult == 10:
                return RequestResult.AuidNotExist
            return RequestResult.BadResult
        acc.banned = 1
        if not acc.db.guildAuid:
            acc.db.guildAuid = self.guildAuid
        acc.db.oldAuid = auid
        self.I.AGG.setProperty( acc.auid, "fsn", snid, callback=self.onAggregatorChangeFSn )
        # после запроса временно срубим исполнение thrift-обработчика специальным exception-ом
        raise AsyncThriftException("async aggregator call")


    def onAggregatorChangeFSn(self, agg_response):
        info("onAggregatorChangeFSn: agg-response %s" % agg_response)
        if agg_response.get('error', None):
            err("change_fsn returned error: %s, %s", agg_response['error'], agg_response['message'])
            self.changeFSnResult = agg_response['error']
        else:
            self.changeFSnResult = 0
        self.handler.process() # вызываем повторную обработку евента (теперь должно вернуть ответ)


    def EditTournamentInfo( self, login, tournamentInfo, gmLogin ):
        acc = self.handler.I.WS.getUserAcc( login )
 
        if acc:
            acc.model.write( acc.pending )

            ticket = acc.model.TournamentInfo.TournamentTicket
            # редактируем все поля на SST, а TicketPriseState на SS только PF-79526
            if ticket.Wins != tournamentInfo.Wins and cfg.TOURNAMENT_SERVER:
                ticket.Wins = tournamentInfo.Wins

            if ticket.Losses != tournamentInfo.Losses and cfg.TOURNAMENT_SERVER:
                ticket.Losses = tournamentInfo.Losses

            if ticket.LastGameTime != tournamentInfo.LastGameTime and cfg.TOURNAMENT_SERVER:
                ticket.LastGameTime = tournamentInfo.LastGameTime

            if ticket.TicketPriseState != tournamentInfo.TicketPriseState and not cfg.TOURNAMENT_SERVER:
                ticket.TicketPriseState = tournamentInfo.TicketPriseState

            if ticket.State != tournamentInfo.State and cfg.TOURNAMENT_SERVER:
                ticket.State = tournamentInfo.State

            if ticket.TicketBoughtType != tournamentInfo.TicketBoughtType and cfg.TOURNAMENT_SERVER:
                ticket.TicketBoughtType = tournamentInfo.TicketBoughtType

            if ticket.MissedGames != tournamentInfo.MissedGames and cfg.TOURNAMENT_SERVER:
              ticket.MissedGames = tournamentInfo.MissedGames

            ticket.IsSynchronized = False
            acc.model.TournamentInfo.sendTournamentTicket( acc, self.handler.I.HTTP )

        else:
            err("EditTournamentInfo error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success


    def GetAccountTournamentInfo( self, login ):
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            ticketInfo = acc.model.TournamentInfo.TournamentTicket
            tournamentModelInfo = AccountManagementAPI.ttypes.TournamentInfo( Wins=ticketInfo.Wins, Losses=ticketInfo.Losses, LastGameTime=ticketInfo.LastGameTime,
                                                           TicketPriseState=ticketInfo.TicketPriseState, State=ticketInfo.State, TicketBoughtType=ticketInfo.TicketBoughtType,
                                                           MissedGames=ticketInfo.MissedGames, IsSynchronized=ticketInfo.IsSynchronized )
            return AccountManagementAPI.ttypes.TournamentInfoResponse( TournamentInfo = tournamentModelInfo, Result = AccountManagementAPI.ttypes.RequestResult.Success )
        else:
            err("GetAccountTournamentInfo error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist

    def GiveTournamentTicket( self, login ):
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            if not cfg.TOURNAMENT_SERVER:
              self.BuyTournamentTicket(login, PayTicketType.Free)
              return AccountManagementAPI.ttypes.TournamentInfoResponse( Result = AccountManagementAPI.ttypes.RequestResult.Success )
            err("GiveTournamentTicket error, can't create account if you are on tournament server")
            return AccountManagementAPI.ttypes.RequestResult.BadResult
        else:
            err("GiveTournamentTicket error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist

    def GetAccountTournamentGames( self, login ):
        acc = self.handler.I.WS.getUserAcc( login )
        tournamentGames = []
        if acc:
            for gameInfo, gameDuration in map(None, acc.model.TournamentInfo.TournamentTicket.SessionInfo, acc.model.TournamentInfo.TournamentTicket.GameDurations):
                startTime, sessionId = gameInfo.split('#')
                tournamentGames.append( AccountManagementAPI.ttypes.TournamentGamesInfo( GameStartTime = int(startTime),
                                                                            GameDuration = gameDuration,
                                                                            SessionId = sessionId ))
            return AccountManagementAPI.ttypes.TournamentGamesInfoResponse( Result = AccountManagementAPI.ttypes.RequestResult.Success, TournamentGames = tournamentGames )
        else:
            err("GetAccountTournamentGames error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.TournamentGamesInfoResponse( Result = AccountManagementAPI.ttypes.RequestResult.LoginNotExist, TournamentGames = tournamentGames )


    def EditHero( self, login, heroEdit, gmLogin ):
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )
            hero = acc.model.getHeroByID( heroEdit.heroInstanceId )
            if hero:
                hero.setExperience( heroEdit.experience, self.handler.I.WS, acc, self.handler.I )

                start_league = acc.SD.getCurrentSeasonLegendLeague()
                if start_league and (heroEdit.rating >= start_league["minRating"] or hero.Rating >= start_league["minRating"]):
                    self.handler.I.EXPORT.updateLegendRatingInfo(acc.db.auid, hero.PersistentId, heroEdit.rating, acc.nick, acc.SD.getCurrentSeasonId())
                    self.handler.I.EXPORT.getLegendRatingInfo(hero.PersistentId, acc.db.auid, acc.SD.getCurrentSeasonId(), self.handler.I.WS.onReceiveLegendInfo)

                hero.Rating = heroEdit.rating

                hero.EpicWins = heroEdit.epicWins
                info( "EditHero done, acc.pending_changes now: %s" % acc.pending_changes )
            else:
                err("EditHero error, hero(%d) is null" % heroEdit.heroInstanceId)
                return AccountManagementAPI.ttypes.RequestResult.HeroInstIdNotExist
        else:
            err("EditHero error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success

    def UnlockHero( self, login, heroClassId, gmLogin, extra_comment=""):
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )
            for heroId in acc.model.Heroes:
                hero = acc.model.getHeroByID( heroId )
                if hero.PersistentId == heroClassId:
                    hero.Hired = True
                    self.handler.I.STATS.addGMUnlockHero( acc.auid, gmLogin, heroClassId )
                    return AccountManagementAPI.ttypes.RequestResult.Success
            acc.model.hireHero( heroClassId, acc.sex, self.handler.I.WS, acc, self.handler.I )
            self.handler.I.STATS.addGMUnlockHero( acc.auid, gmLogin, heroClassId )
            return AccountManagementAPI.ttypes.RequestResult.Success
        else:
            err("UnlockHero error, get acc by login(%s) fail", login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success

    def LockHero( self, login, heroInstanceId, gmLogin ):
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )
            hero = acc.model.getHeroByID( heroInstanceId )
            if hero and hero.Hired:
                # Проверим, не хочет ли кто-нибудь удалить дефолтного героя
                staticHero = acc.SD.data['Heroes'][hero.PersistentId]
                isDefaultHero = staticHero and ((acc.db.sex != ESex.FEMALE and staticHero['lobbyData']['IsHeroHiredByDefaultMale'])
                   or (acc.db.sex == ESex.FEMALE and staticHero['lobbyData']['IsHeroHiredByDefaultFemale']))
                if not isDefaultHero:
                    hero.Hired = False
                    for buildingId in acc.model.Buildings:
                        building = acc.model.getConstructionByID(buildingId)
                        if building:
                            if heroInstanceId in building.HeroesInBuilding:
                                building.removeHeroFromBuilding(  hero, acc, acc.SD )
                    for skinId in hero.HeroSkins.Skins.keys():
                        acc.model.deleteByID(skinId)
                    self.handler.I.STATS.addGMLockHero( acc.auid, gmLogin, hero.PersistentId )
                    acc.model.deleteByID(heroInstanceId)
                else:
                    err("LockHero error, hero(%d) is default for current user" % heroInstanceId)
                    return AccountManagementAPI.ttypes.RequestResult.CantRemoveClassHero
            else:
                err("LockHero error, hero(%d) is null or not hired" % heroInstanceId)
                return AccountManagementAPI.ttypes.RequestResult.HeroInstIdNotExist
        else:
            err("LockHero error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success

    def fill_awards_string_info(self, awards_info):
        return "Flag: %s, Perls: %s, Skin: %s, Talents: %s"%(str(awards_info.Flag), str(awards_info.RedPerls), str(awards_info.Skin), str(awards_info.Talents.keys()).strip('[]') )

    def fill_awards_fromGM(self, acc, awards_info, editAwards):
        awards_info.Flag = editAwards.flag
        awards_info.RedPerls = editAwards.perls
        del awards_info.Talents[:]
        if editAwards.talents and len(editAwards.talents):
            list_talents = editAwards.talents.split(', ')
            for talent_id in list_talents:
                awards_info.Talents.append(int(talent_id))
                staticTalent = acc.SD.getStaticTalentByTalentId( int(talent_id) )
                if staticTalent:
                    if staticTalent['rarity'] != "Class":
                        talent_id = acc.model.addNewTalent()
                        talent = acc.model.getTalentByID( talent_id )
                        talent.IsNew = True
                        talent.PersistentId = int(talent_id)
                        acc.model.UserInventory.add( talent_id )
        awards_info.IsShowedToUser = False

        acc.model.appendSeasonAwards(acc, awards_info.SeasonId, awards_info.Flag, [], [])
        acc.model.addResourcesForFree({"Perl": str(awards_info.RedPerls)})
        skin_id = editAwards.skin
        static_skin = acc.SD.getStaticSkinByPersistentId(crc32(skin_id))
        if static_skin:
            hero_for_skin = acc.model.getHeroForSkin(static_skin, acc.SD)
            if not hero_for_skin:
                hero_for_skin = acc.model.hireHero(crc32(static_skin['heroClassId']), acc.sex, self.handler.I.WS, acc, self.handler.I)
            if hero_for_skin:
                config = acc.getConfig()
                acc.model.addSkinForHero(crc32(skin_id), hero_for_skin, isDefault=True, wasBought=True,
                                         IsAnimatedAvatar=static_skin['persistentId'] not in config.SKIN_AVATAR_BLOCK)
                awards_info.Skin = crc32(skin_id)

    def EditSeasonAwards( self, login, editAwards, gmLogin ):
        acc = self.handler.I.WS.getUserAcc( login )

        if acc:
            acc.model.write( acc.pending )
            is_awards_info_exist = False
            for awards_id in acc.model.SeasonAwardsKeeper:
                awards_info = acc.model.getSeasonAwardsByID(awards_id)
                if awards_info.SeasonId == editAwards.seasonId:
                    is_awards_info_exist = True
                    str_prev_awards = self.fill_awards_string_info(awards_info)
                    self.fill_awards_fromGM(acc, awards_info, editAwards)
                    str_new_awards = self.fill_awards_string_info(awards_info)
                    data = "Change awards for season %s, was: %s, new: %s"%(str(awards_info.SeasonId), str_prev_awards, str_new_awards)
                    self.handler.I.STATS.addGMOperation(acc.auid, GMOperationType.SeasonAwardsChange, gmLogin, data )
                    break

            if not is_awards_info_exist:
                awards_info, season_awards_id = acc.model.newSeasonAwards()
                awards_info.SeasonId = editAwards.seasonId
                self.fill_awards_fromGM(acc, awards_info, editAwards)
                str_new_awards = self.fill_awards_string_info(awards_info)
                data = "Add awards for season %s: %s"%(str(awards_info.SeasonId), str_new_awards)
                acc.model.SeasonsAwardsInfo.add(editAwards.seasonId, awards_info)
                self.handler.I.STATS.addGMOperation(acc.auid, GMOperationType.SeasonAwardsAdd, gmLogin, data )

            info("EditSeasonAwards, data = %s"%data)

        else:
            err("EditSeasonAwards error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success

    def fill_season_string_info(self, season_info):
        return "LeagueIndex: %d, BestLeaguePlace: %d, SeasonRatings: %d"%(season_info.LeagueIndex, season_info.BestLeaguePlace, season_info.SeasonRating)

    def EditSeasonInfo( self, login, heroInstanceId, editSeason, gmLogin ):
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )
            hero = acc.model.getHeroByID( heroInstanceId )
            if hero and hero.Hired:
                change_season_info = None
                is_season_edit = True
                for seasonId in hero.SeasonsInfo:
                    season_info = acc.model.getSeasonInfoByID(seasonId)
                    if season_info:
                        if season_info.SeasonId == editSeason.seasonId:
                            change_season_info = season_info
                            break

                if change_season_info == None:
                    is_season_edit = False
                    change_season_info, _id = acc.model.newSeasonInfo()
                    change_season_info.SeasonId = editSeason.seasonId
                    hero.SeasonsInfo.add(_id, change_season_info)

                str_prev_info = self.fill_season_string_info(change_season_info)

                change_season_info.LeagueIndex = editSeason.leagueIndex
                change_season_info.BestLeaguePlace = editSeason.bestLeaguePlace
                change_season_info.SeasonRating = editSeason.seasonRating

                str_new_info = self.fill_season_string_info(change_season_info)

                if is_season_edit:
                    data = "Edit season info for hero %s, season %s, was: %s, new: %s"%(str(heroInstanceId), str(editSeason.seasonId), str_prev_info, str_new_info)
                    self.handler.I.STATS.addGMOperation(acc.auid, GMOperationType.SeasonInfoChange, gmLogin, data )
                else:
                    data = "Add season info for hero %s, season %s was: %s, new: %s"%(str(heroInstanceId), str(editSeason.seasonId), str_prev_info, str_new_info)
                    self.handler.I.STATS.addGMOperation(acc.auid, GMOperationType.SeasonInfoAdd, gmLogin, data )
                info("EditSeasonInfo, data = %s"%data)
        else:
            err("EditSeasonInfo error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success

    # ---------------------------------------------------------------------------------------------
    def EditNickname( self, login, gmLogin, nickname ):
        self.login = login
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )
            # смена nickname вполне может обломаться (если нам дают неуникальный или неправильный ник), поэтому операцию выполняем асинхронно
            if (nickname != None):
                if acc.nicknameChangeResult is None:
                    # начинаем асинхронную смену ника
                    if str(acc.nick) != str(nickname):
                        self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "nickname", str(acc.nick), str(nickname) )
                    subParams = ClassDict( nickname=[nickname] )
                    accountAction = SetNicknameAction( subParams, self.onChangeNickname, I=self.handler.I, acc=acc, uid=acc.uid )
                    accountAction.onStart()
                    
                    # ждем асинхронной обработки; временно срубим исполнение thrift-обработчика специальным exception-ом
                    raise AsyncThriftException("async change nickname")
                    
                else:
                    # асинхронная смена ника завершилась
                    result = acc.pop( "nicknameChangeResult" )
                    info( "EditNickname( login=%s, nickname=%s ) return result=%s" % (login, nickname, result) )
                    error = acc.pop( "nicknameChangeError" )
                    if result:
                        # временно блокируем и выпинываем клиента с сервера, т.к. у нас нет механизма апдейта ника через pending_changes
                        self.GMToolBan( acc )
                        acc.ka = 0
                        return StringDataResponse( RequestResult.Success )
                    else:
                        return StringDataResponse( RequestResult.BadResult, error )
        else:
            err("EditNickname error, get acc by login(%s) fail" % login)
            return StringDataResponse( RequestResult.LoginNotExist )
        
    def onChangeNickname(self, action_response):
        acc = self.handler.I.WS.getUserAcc( self.login )
        if acc:
            SubAction._postponeResponseChanges( action_response, acc )
            acc.model.write( acc.pending )
            acc.nicknameChangeResult = action_response.get("ok", 0)
            acc.nicknameChangeError = action_response.get("error", "")
            info( "onChangeNickname result for login(%s): %d (error: %s)" % (self.login, acc.nicknameChangeResult, acc.nicknameChangeError) )
        else:
            err( "onChangeNickname error, get acc by login(%s) fail" % self.login )
        self.handler.process() # вызываем повторную обработку евента (теперь должно вернуть ответ)        
        
        
    # ---------------------------------------------------------------------------------------------
    def PayEditNickname( self, login, nickname ):
        self.login = login
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )
            if acc.PayEditNickname_Result is None:
                # начинаем асинхронную смену ника
                ##request = ChangeNicknameRequest( self.modeldata, { "nickname" : ['Mr_Facker'] }, False ) )
                subParams = ClassDict( nickname=[nickname] )
                accountAction = Change_nickname( subParams, self.onPayEditNickname, I=self.handler.I, acc=acc, uid=acc.uid )
                accountAction.onStart()
                    
                # ждем асинхронной обработки; временно срубим исполнение thrift-обработчика специальным exception-ом
                raise AsyncThriftException("async change nickname")
                
            else:
                result = acc.pop("PayEditNickname_Result")
                info( "PayEditNickname( login=%s, nickname=%s ) return result.ok=%s" % (login, nickname, result.ok))
                if result.ok:
                    # временно блокируем и выпинываем клиента с сервера, т.к. у нас нет механизма апдейта ника через pending_changes
                    acc.banned = 1
                    acc.ka = 0
                    return ServerActionResponse( RequestResult.Success )
                else:
                    return ServerActionResponse( RequestResult.BadResult, str(result.error), \
                        toint(result.ec), str(result.error_args ))
        else:
            err("PayEditNickname error, get acc by login(%s) fail" % login)
            return ServerActionResponse( RequestResult.LoginNotExist )
    
    def onPayEditNickname(self, action_response):
        acc = self.handler.I.WS.getUserAcc( self.login )
        if acc:
            SubAction._postponeResponseChanges( action_response, acc )
            acc.PayEditNickname_Result = ClassDict(
                ok = action_response.get("ok", 0),
                error = action_response.get("error", ""),
                ec = action_response.get("ec", 0),
                error_args = action_response.get("error_args", {}),
            )
            info( "onPayEditNickname result for login(%s): %s" % (self.login, acc.PayEditNickname_Result) )
        else:
            err( "onPayEditNickname error, get acc by login(%s) fail" % self.login )
        self.handler.process() # вызываем повторную обработку евента (теперь должно вернуть ответ)        
        
    # ---------------------------------------------------------------------------------------------
    def PayChangeFraction( self, login, fraction ):
        self.login = login
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )
            if acc.PayChangeFraction_Result is None:
                # начинаем асинхронную смену фракции
                if fraction is not None:
                    if party_const.FRACTION_LIST[fraction] != acc.db.fraction and acc.online:
                        self.GMToolBan( acc )
                    fractionLetter = party_const.FRACTION_LIST[fraction]
                    info( "PayChangeFraction async start, login=%s, fraction=%s(int %s)" % (login, fractionLetter, fraction) )
                    subParams = ClassDict( fraction=[fractionLetter], rid=[1] )
                    accountAction = Change_fraction( subParams, self.onPayChangeFraction, I=self.handler.I, acc=acc, uid=acc.uid )
                    accountAction.onStart()
                    
                    # ждем асинхронной обработки; временно срубим исполнение thrift-обработчика специальным exception-ом
                    raise AsyncThriftException("async change fraction")
                
                else:
                    err("PayChangeFraction error, bad fraction(int)=%s for login(%s)" % (fraction, login))
                    return ServerActionResponse( RequestResult.BadResult, "bad fraction" )
            else:
                info( "PayChangeFraction( login=%s, fraction(int)=%s ) return result" % (login, fraction) )
                result = acc.pop("PayChangeFraction_Result")
                if result.ok:
                    return ServerActionResponse( RequestResult.Success )
                else:
                    return ServerActionResponse( RequestResult.BadResult, str(result.error), \
                        toint(result.ec), str(result.error_args ))
        else:
            err("PayChangeFraction error, get acc by login(%s) fail" % login)
            return ServerActionResponse( RequestResult.LoginNotExist )
    
    def onPayChangeFraction(self, action_response):
        acc = self.handler.I.WS.getUserAcc( self.login )
        if acc:
            SubAction._postponeResponseChanges( action_response, acc )
            acc.model.write( acc.pending )
            acc.PayChangeFraction_Result = ClassDict(
                ok = action_response.get("ok", 0),
                error = action_response.get("error", ""),
                ec = action_response.get("ec", 0),
                error_args = action_response.get("error_args", {}),
            )
            info( "onPayChangeFraction result for login(%s): %s" % (self.login, acc.PayChangeFraction_Result) )
            if acc.PayChangeFraction_Result.ok:
                self.handler.I.WS.updateGameDataToPersonServer( acc )
        else:
            err( "onPayChangeFraction error, get acc by login(%s) fail" % self.login )
        self.handler.process() # вызываем повторную обработку евента (теперь должно вернуть ответ)        
        
       
    # ---------------------------------------------------------------------------------------------
    def PayService( self, login, servicetype, paramValue, gmLogin, extra_comment=""):
        self.login = login
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )
            if servicetype == PayServiceType.PremiumAccount:
                secondsInDay = 86400
                before = 0
                if acc.model.IsPremiumAccount():
                    before = (acc.model.LordInfo.PremiumAccountEnd - acc.model.LordInfo.PremiumAccountStart) / secondsInDay
                subParams = ClassDict( duration=[paramValue] )
                accountAction = Buy_premium_account_gm( subParams, self.callbackFn, I=self.handler.I, acc=acc, uid=acc.uid )
                accountAction.onStart()
                after = before + paramValue # has added days

                self.handler.I.STATS.addGMEditUser(acc.auid, gmLogin, "Has added PremiumAccount",
                                                   str(before),
                                                   str(after))
            elif servicetype == PayServiceType.Unban:
                if acc.PayService_Unban_Result is None:
                    if acc.db.banned and ( time.time() < acc.db.bantime or acc.db.bantime == 0 ):
                        info( "PayServiceUnban( login=%s ) sends ws request", login )
                        subParams = ClassDict()
                        accountAction = Buy_unban_gm( subParams, self.onPayServiceUnban, I=self.handler.I, acc=acc, uid=acc.uid )
                        accountAction.onStart()
                        raise AsyncThriftException( "async payservice unban" )     
                    else:
                        return AccountManagementAPI.ttypes.RequestResult.Success
                else:
                    result = acc.pop("PayService_Unban_Result")
                    info( "PayServiceUnban( login=%s ) returns result %r" % ( login, result ) )
                    if not result.ok:
                        return AccountManagementAPI.ttypes.RequestResult.BadResult       
            else:
                err("PayService error, not supported service %r" % servicetype)
                return AccountManagementAPI.ttypes.RequestResult.BadServiceType
        else:
            err("PayService error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success
        
    def onPayServiceUnban( self, action_response ):
        acc = self.handler.I.WS.getUserAcc( self.login )
        if acc:
            SubAction._postponeResponseChanges( action_response, acc )
            acc.model.write( acc.pending )
            info( "onPayServiceUnban( login=%s ) gets result" % self.login )
            acc.PayService_Unban_Result = ClassDict(
                ok = action_response.get("ok", 0),
                error = action_response.get("error", ""),
                ec = action_response.get("ec", 0),
                error_args = action_response.get("error_args", {}),
            )
            self.handler.process() # вызываем повторную обработку евента (теперь должно вернуть ответ) 
        else:
            err( "onPayServiceUnban error, get acc by login(%s) fail" % self.login )

    def GetPrices( self, login, servicetype ):
        self.login = login
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )
            if acc.GetPrices_Result is None:
                # начинаем асинхронное получение цен
                if servicetype == PayServiceType.PremiumAccount:
                    info( "GetPrices async start, login=%s, servicetype=%s" % (login, servicetype) )
                    subParams = ClassDict( servicetype=[PayServiceType.PremiumAccount], rid=[1] )
                    accountAction = Get_prices( subParams, self.onGetPrices, I=self.handler.I, acc=acc, uid=acc.uid )
                    accountAction.onStart()
                    
                    # ждем асинхронной обработки; временно срубим исполнение thrift-обработчика специальным exception-ом
                    raise AsyncThriftException("async change fraction")
                
            else:
                info( "GetPrices( login=%s, servicetype(int)=%s ) return result" % (login, servicetype) )
                result = acc.pop("GetPrices_Result")
                if result.ok:
                    return PriceServiceDataResponse( result = ServerActionResponse( RequestResult.Success ), prInfoList = result.list )
                else:
                    return PriceServiceDataResponse( result = ServerActionResponse( RequestResult.BadResult, str(result.error), \
                        toint(result.ec), str(result.error_args ) ), prInfoList = None )
        else:
            err("GetPrices error, get acc by login(%s) fail" % login)
            return PriceServiceDataResponse( result = ServerActionResponse( RequestResult.LoginNotExist ), prInfoList = None )

    
    def onGetPrices(self, action_response):
        acc = self.handler.I.WS.getUserAcc( self.login )
        if acc:
            SubAction._postponeResponseChanges( action_response, acc )
            acc.model.write( acc.pending )
            acc.GetPrices_Result = ClassDict(
                ok = action_response.get("ok", 0),
                error = action_response.get("error", ""),
                ec = action_response.get("ec", 0),
                error_args = action_response.get("error_args", {}),
                list = [],
            )
            for el in action_response.get("prices", [] ):
                acc.GetPrices_Result.list.append( PriceServiceInfo( priceInGold = int(el["price"]), paramValue = int(el["duration"]) ) )
            info( "onGetPrices result for login(%s): %r" % (self.login, acc.GetPrices_Result) )
        else:
            err( "onGetPrices error, get acc by login(%s) fail" % self.login )
        self.handler.process() # вызываем повторную обработку евента (теперь должно вернуть ответ)        


    def BuyService( self, login, servicetype, paramValue ):
        self.login = login
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )
            if acc.BuyService_Result is None:
                # начинаем асинхронную покупку сервиса
                if servicetype == PayServiceType.PremiumAccount:
                    info( "BuyService async start, login=%s, servicetype=%s, paramValue=%r" % (login, servicetype, paramValue) )
                    subParams = ClassDict( type=[paramValue], rid=[1] )
                    accountAction = Buy_premium_account( subParams, self.onBuyService, I=self.handler.I, acc=acc, uid=acc.uid )
                    accountAction.onStart()
                    
                    # ждем асинхронной обработки; временно срубим исполнение thrift-обработчика специальным exception-ом
                    raise AsyncThriftException("async change fraction")
                
            else:
                info( "BuyService( login=%s, servicetype(int)=%s, paramValue=%r ) return result" % (login, servicetype, paramValue) )
                result = acc.pop("BuyService_Result")
                if result.ok:
                    return ServerActionResponse( RequestResult.Success )
                else:
                    return ServerActionResponse( RequestResult.BadResult, str(result.error), toint(result.ec), str(result.error_args ))
        else:
            err("BuyService error, get acc by login(%s) fail" % login)
            return ServerActionResponse( RequestResult.LoginNotExist )

    
    def onBuyService(self, action_response):
        acc = self.handler.I.WS.getUserAcc( self.login )
        if acc:
            SubAction._postponeResponseChanges( action_response, acc )
            acc.model.write( acc.pending )
            acc.BuyService_Result = ClassDict(
                ok = action_response.get("ok", 0),
                error = action_response.get("error", ""),
                ec = action_response.get("ec", 0),
                error_args = action_response.get("error_args", {}),
            )
            info( "onBuyService result for login(%s): %r" % (self.login, acc.BuyService_Result) )
        else:
            err( "onBuyService error, get acc by login(%s) fail" % self.login )
        self.handler.process() # вызываем повторную обработку евента (теперь должно вернуть ответ)        

        
    # ---------------------------------------------------------------------------------------------
    def GetAccountQuestsForTalentsByAuid(self, login):
        acc = self.handler.I.WS.getUserAcc(login)
        if acc:
            questsForTalentsInfo = []

            for questId, quest in acc.model.DynamicQuests.iteritems():

                reason = quest.Reason
                # meta vars
                idAwardWithTalent = -1
                objectiveId = -1

                # fill raw data
                rawQuestData = "===============QuestInfo: " + "\n"
                rawQuestData += pretty(quest.generateJsonDict()) + "\n"
                for id, _ in quest.Objectives.items():
                    objectiveId = objectiveId if objectiveId != -1 else id
                    rawQuestData += pretty(acc.model.getDynamicObjectiveByID(id).generateJsonDict()) + "\n"
                rawQuestData += "===============DynamicAwards: " + "\n"
                for id, _ in quest.Awards.items():
                    idAwardWithTalent = idAwardWithTalent if idAwardWithTalent != -1 else id
                    rawQuestData += pretty(acc.model.getDynamicQuestAwardByID(id).generateJsonDict()) + "\n"

                # get talent from award
                talentFromAwardPersistentId = -1
                talentFromAwardName = "None"
                staticTalent = None
                if idAwardWithTalent != -1:
                    award = acc.model.getDynamicQuestAwardByID(idAwardWithTalent)
                    if award.QuestAwardType == DynamicQuestAwardType.Talent:
                        talentPersistentId = award.PersistentId
                        talentFromAwardPersistentId = talentPersistentId
                        staticTalent = acc.SD.getStaticTalentByTalentId(talentPersistentId)
                        talentFromAwardName = staticTalent['persistentId']

                # get shards spent
                shardsSpent = 0
                if staticTalent != None:
                    overridenPriceMap = acc.SD.data['DynamicQuestForTalents']['OverridenPricesMap']
                    overridenPrice = overridenPriceMap[staticTalent['persistentId']] if staticTalent['persistentId'] in overridenPriceMap else None
                    if overridenPrice:
                        shardsSpent = acc.SD.copyPrice(overridenPrice).Shard
                    else:
                        priceMap = acc.SD.data['DynamicQuestForTalents']['PricesMap']
                        shardsSpent = acc.SD.copyPrice(priceMap[staticTalent['rarity']]).Shard

                # get current quest progress
                currentObjectiveData = ""
                objective = acc.model.getDynamicObjectiveByID(objectiveId)
                currentObjectiveValue = objective.CurrentValue

                # get total quest progress
                totalObjectiveData = ""
                if objective.QuestCheckType in [DynamicQuestCheckType.SessionInfo, DynamicQuestCheckType.SessionResult]:
                    totalObjectiveData += "SessionTotal: " + str(objective.SessionCondition.TotalValue)
                elif objective.QuestCheckType == DynamicQuestCheckType.Instant:
                    totalObjectiveData += "InstantTotal: " + str(objective.InstantCondition.TotalValue)
                elif objective.QuestCheckType == DynamicQuestCheckType.ModelData:
                    totalObjectiveData += "ModelDataTotal: " + str(objective.ModelDataCondition.TotalValue)

                questsForTalentsInfo.append(AccountManagementAPI.ttypes.QuestForTalentInfo(
                    questId=int(questId),
                    startTime=int(quest.QuestStartTime),
                    endTime=int(quest.QuestEndTime),
                    talentAwardPersistentId=int(talentFromAwardPersistentId),
                    talentAwardName=str(talentFromAwardName),
                    shardsSpent=int(shardsSpent),
                    currentObjectiveValue=int(currentObjectiveValue),
                    currentObjectiveData=str(currentObjectiveData),
                    currentObjectiveId=int(objectiveId),
                    currentAwardId=int(idAwardWithTalent),
                    fullDynamicQuestInfo=str(rawQuestData),
                    totalObjectiveData=str(totalObjectiveData),
                    reason=int(reason)
                ))

            return AccountManagementAPI.ttypes.QuestsForTalentsInfoResponse(questsForTalentsInfo=questsForTalentsInfo,
                                                                              result=AccountManagementAPI.ttypes.RequestResult.Success)
        else:
            err("GetAccountQuestsForTalentsByAuid fail - invalid auid")
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist

    def EditQuestForTalent( self, login, questForTalentEdit, gmLogin, extra_comment=""):
        acc = self.handler.I.WS.getUserAcc(login)
        if acc:
            acc.model.write(acc.pending)

            # init
            editQuest = acc.model.getDynamicQuestByID(questForTalentEdit.questId)
            talentAward = crc32(questForTalentEdit.talentAwardName)

            if not editQuest:
                return AccountManagementAPI.ttypes.RequestResult.BadResult

            if not acc.SD.getStaticTalentByTalentId(talentAward):
                return AccountManagementAPI.ttypes.RequestResult.BadResult

            editObjective = acc.model.getDynamicObjectiveByID(questForTalentEdit.editObjectiveId)
            editAward = acc.model.getDynamicQuestAwardByID(questForTalentEdit.editAwardId)

            # write old info
            oldInfo = "QuestId: " + str(questForTalentEdit.questId) + "\n"

            oldInfo += "StartTime: " + str(editQuest.QuestStartTime) + "\n"
            oldInfo += "EndTime: " + str(editQuest.QuestEndTime) + "\n"
            oldInfo += "ObjectiveProgressValue: " + str(editObjective.CurrentValue) + "\n"
            oldInfo += "Talent: " + str(acc.SD.getStaticTalentByTalentId(editAward.PersistentId)["persistentId"]) + "\n"

            # edit-logic
            editQuest.QuestStartTime = questForTalentEdit.startTime
            editQuest.QuestEndTime = questForTalentEdit.endTime
            editObjective.CurrentValue = questForTalentEdit.currentObjectiveValue
            editAward.PersistentId = talentAward

            # write new info
            newInfo = "QuestId: " + str(questForTalentEdit.questId) + "\n"

            newInfo += "StartTime: " + str(editQuest.QuestStartTime) + "\n"
            newInfo += "EndTime: " + str(editQuest.QuestEndTime) + "\n"
            newInfo += "ObjectiveProgressValue: " + str(editObjective.CurrentValue) + "\n"
            newInfo += "Talent: " + str(acc.SD.getStaticTalentByTalentId(editAward.PersistentId)["persistentId"]) + "\n"

            # send to stat
            self.handler.I.STATS.addGMEditUser(acc.auid, gmLogin, "EditQuestForTalent",
                                               oldInfo,
                                               newInfo)
        else:
            err("EditQuestForTalent error, get acc by login(%s) fail", login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success


    def EditAccount( self, login, accountEdit, gmLogin, extra_comment=""):
        self.login = login
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )
            if acc.db.fraction == 'N':
              newFraction = "B"
              if (accountEdit.fraction is not None):
                newFraction = party_const.FRACTION_LIST[accountEdit.fraction]
              self.GMToolBan( acc )
              subParams = ClassDict( fraction=[newFraction] )
              accountAction = SetFractionAction( subParams, self.callbackFn, I=self.handler.I, acc=acc, uid=acc.uid )
              accountAction.onStart()
            
            if (accountEdit.fraction is not None):
                if party_const.FRACTION_LIST[accountEdit.fraction] != acc.db.fraction and acc.online:
                    self.GMToolBan( acc )
                if str(acc.db.fraction) != str(party_const.FRACTION_LIST[accountEdit.fraction]):
                    self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "fraction", str(acc.db.fraction), str(party_const.FRACTION_LIST[accountEdit.fraction]) )
                subParams = ClassDict( fraction=[party_const.FRACTION_LIST[accountEdit.fraction]] )
                accountAction = Change_fraction_GM( subParams, self.callbackFn, I=self.handler.I, acc=acc, uid=acc.uid )
                accountAction.onStart()

            if (accountEdit.gender is not None) \
            and (accountEdit.gender in [AccountManagementAPI.ttypes.Gender.Male, AccountManagementAPI.ttypes.Gender.Female]):
                if str(acc.db.sex) != str(accountEdit.gender):
                    self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "gender", str(acc.db.sex), str(accountEdit.gender) )
                subParams = ClassDict( gender=[accountEdit.gender] )
                accountAction = SetGenderAction( subParams, None, I=self.handler.I, acc=acc, uid=acc.uid )
                accountAction.onStart()
                
            if (accountEdit.fame is not None) and str(acc.model.LordInfo.Fame) != str(accountEdit.fame):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "Fame", str(acc.model.LordInfo.Fame), str(accountEdit.fame) )
            acc.model.LordInfo.Fame = accountEdit.fame
            
            if (accountEdit.reliability is not None) and str(acc.model.LordInfo.Reliability) != str(accountEdit.reliability):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "Reliability", str(acc.model.LordInfo.Reliability), str(accountEdit.reliability) )
            acc.model.LordInfo.Reliability = accountEdit.reliability
            
            if (accountEdit.silver is not None) and str(acc.model.Resources.Silver) != str(accountEdit.silver):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "Silver", str(acc.model.Resources.Silver), str(accountEdit.silver) )
            acc.model.Resources.Silver = accountEdit.silver

            if (accountEdit.lordRating is not None) and str(acc.model.LordInfo.Ratings.LordRating) != str(accountEdit.lordRating):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "LordRating", str(acc.model.LordInfo.Ratings.LordRating), str(accountEdit.lordRating) )
            acc.model.LordInfo.Ratings.LordRating = accountEdit.lordRating

            if (accountEdit.guardRating is not None) and str(acc.model.LordInfo.Ratings.LordPublicRating) != str(accountEdit.guardRating):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "LordPublicRating", \
                    str(acc.model.LordInfo.Ratings.LordPublicRating), str(accountEdit.guardRating) )
            acc.model.changePublicRating( accountEdit.guardRating )
            
            if (accountEdit.numberOfWins is not None) and str(acc.model.LordInfo.GuardInfo.NumberOfWins) != str(accountEdit.numberOfWins):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "NumberOfWins", str(acc.model.LordInfo.GuardInfo.NumberOfWins), str(accountEdit.numberOfWins) )
            acc.model.LordInfo.GuardInfo.NumberOfWins = accountEdit.numberOfWins

            if (accountEdit.retiredTime is not None) and str(acc.model.LordInfo.GuardInfo.RetiredTime) != str(accountEdit.retiredTime):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "RetiredTime", str(acc.model.LordInfo.GuardInfo.RetiredTime), str(accountEdit.retiredTime) )
            acc.model.LordInfo.GuardInfo.RetiredTime = accountEdit.retiredTime

            if (accountEdit.dodges is not None) and str(acc.model.LordInfo.GuardInfo.Dodges) != str(accountEdit.dodges):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "Dodges", str(acc.model.LordInfo.GuardInfo.Dodges), str(accountEdit.dodges) )
                acc.model.LordInfo.GuardInfo.Dodges = 0
                acc.model.addDodges( accountEdit.dodges, self.handler.I.WS, acc )

            if (accountEdit.resource1 is not None) and str(acc.model.Resources.Resource1) != str(accountEdit.resource1):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "Resource1", str(acc.model.Resources.Resource1), str(accountEdit.resource1) )
            acc.model.Resources.Resource1 = accountEdit.resource1
            
            if (accountEdit.resource2 is not None) and str(acc.model.Resources.Resource2) != str(accountEdit.resource2):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "Resource2", str(acc.model.Resources.Resource2), str(accountEdit.resource2) )
            acc.model.Resources.Resource2 = accountEdit.resource2
            
            if (accountEdit.resource3 is not None) and str(acc.model.Resources.Resource3) != str(accountEdit.resource3):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "Resource3", str(acc.model.Resources.Resource3), str(accountEdit.resource3) )
            acc.model.Resources.Resource3 = accountEdit.resource3

            if (accountEdit.Shard is not None) and str(acc.model.Resources.Shard) != str(accountEdit.Shard):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "Shard", str(acc.model.Resources.Shard), str(accountEdit.Shard) )
            acc.model.Resources.Shard = accountEdit.Shard
            
            if (accountEdit.perl is not None) and str(acc.model.Resources.Perl) != str(accountEdit.perl):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "Perl", str(acc.model.Resources.Perl), str(accountEdit.perl) )
            acc.model.Resources.Perl = accountEdit.perl

            if (accountEdit.redPerl is not None) and str(acc.model.Resources.RedPerl) != str(accountEdit.redPerl):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "RedPerl", str(acc.model.Resources.RedPerl), str(accountEdit.redPerl) )
            acc.model.Resources.RedPerl = accountEdit.redPerl

            if (accountEdit.cwplayerpoints is not None) and str(acc.model.Resources.CWPoints_Player) != str(accountEdit.cwplayerpoints):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "CWPoints_Player", str(acc.model.Resources.CWPoints_Player), str(accountEdit.cwplayerpoints) )
            acc.model.Resources.CWPoints_Player = accountEdit.cwplayerpoints

            if accountEdit.currencies is not None and str(acc.model.Resources.Currencies) != str(accountEdit.currencies):
                for currencyName, currencyVal in accountEdit.currencies.iteritems():
                    if not currencyName in acc.model.Resources.Currencies:
                        continue
                    self.handler.I.STATS.addGMEditUser(acc.auid, gmLogin, "Currency:{}".format(currencyName), str(acc.model.Resources.Currencies[currencyName]),
                                                       str(accountEdit.currencies.get(currencyName, 0)))
                    acc.model.Resources.Currencies[currencyName] = accountEdit.currencies.get(currencyName, 0)

            if (accountEdit.isDeveloper is not None) and str(acc.db.IsDeveloper) != str(accountEdit.isDeveloper):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "IsDeveloper", str(acc.db.IsDeveloper), str(accountEdit.isDeveloper) )
            acc.db.IsDeveloper = accountEdit.isDeveloper

            if (accountEdit.isSpectator is not None) and str(acc.db.IsSpectator) != str(accountEdit.isSpectator):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "IsSpectator", str(acc.db.IsSpectator), str(accountEdit.isSpectator) )
            acc.db.IsSpectator = accountEdit.isSpectator

            if (accountEdit.canMute is not None) and str(acc.db.IsModerator) != str(accountEdit.canMute):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "IsModerator", str(acc.db.IsModerator), str(accountEdit.canMute) )
            acc.db.IsModerator = accountEdit.canMute

            if (accountEdit.isRegularMMAllowed is not None) and str(acc.db.isRegularMMAllowed) != str(accountEdit.isRegularMMAllowed):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "isRegularMMAllowed", str(acc.db.isRegularMMAllowed), str(accountEdit.isRegularMMAllowed) )
            acc.db.isRegularMMAllowed = accountEdit.isRegularMMAllowed

            self.handler.I.WS.updateGameDataToPersonServer( acc )

            if (accountEdit.guildBuildingLevel is not None) \
            and accountEdit.guildBuildingLevel != -1 and accountEdit.guildBuildingLevel != acc.model.getGuildBuildingLevel( acc.SD ):
                building = acc.model.getGuildBuilding( acc.SD )
                if building:
                    building.Level = accountEdit.guildBuildingLevel
                    for heroId in acc.model.Heroes:
                        hero = acc.model.getHeroByID(heroId)
                        if hero.Hired:
                            for tsId in hero.TalentSets.keys():
                                hero.resetHeroStatPoints( acc, tsId )
                                hero.CalcForce( acc.model, self.handler.I.WS, acc, tsId )

            if (accountEdit.lastPaymentTime is not None) and str(acc.model.Statistics.LastPaymentTime) != str(accountEdit.lastPaymentTime):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "LastPaymentTime", str(acc.model.Statistics.LastPaymentTime), str(accountEdit.lastPaymentTime) )
            acc.model.Statistics.LastPaymentTime = accountEdit.lastPaymentTime

            if (accountEdit.lastLampDropTime is not None) and str(acc.model.Statistics.LastLampDropTime) != str(accountEdit.lastLampDropTime):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "LastLampDropTime", str(acc.model.Statistics.LastLampDropTime), str(accountEdit.lastLampDropTime) )
            acc.model.Statistics.LastLampDropTime = accountEdit.lastLampDropTime

            pRating = acc.model.getPlayerRating()
            if (accountEdit.PlayerRating is not None) and str(pRating) != str(accountEdit.PlayerRating):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "PlayerRating", str(pRating), str(accountEdit.PlayerRating))
                debug("EditAccount accountEdit.PlayerRating %r", accountEdit.PlayerRating)
                acc.model.setPlayerRating( accountEdit.PlayerRating, acc.getConfig())

            if (accountEdit.numberOfWinsForPR is not None) and str(acc.model.LordInfo.Ratings.NumberOfWinsForPR) != str(accountEdit.numberOfWinsForPR):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "NumberOfWinsForPR", str(acc.model.LordInfo.Ratings.NumberOfWinsForPR), str(accountEdit.numberOfWinsForPR) )
            acc.model.LordInfo.Ratings.NumberOfWinsForPR = accountEdit.numberOfWinsForPR

            if (accountEdit.extraComplaints is not None) and str(acc.model.LordInfo.ExtraComplaints) != str(accountEdit.extraComplaints):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "ExtraComplaints", str(acc.model.LordInfo.ExtraComplaints), str(accountEdit.extraComplaints) )
                debug("EditAccount accountEdit.extraComplaints %r", accountEdit.extraComplaints)
                if accountEdit.extraComplaints < acc.model.LordInfo.ExtraComplaints:
                    acc.model.LordInfo.ComplaintsLeft -= acc.model.LordInfo.ExtraComplaints -accountEdit.extraComplaints
                    acc.model.LordInfo.ComplaintsLeft = 0 if acc.model.LordInfo.ComplaintsLeft < 0 else acc.model.LordInfo.ComplaintsLeft
                else:
                    acc.model.LordInfo.ComplaintsLeft += accountEdit.extraComplaints - acc.model.LordInfo.ExtraComplaints
                acc.model.LordInfo.ExtraComplaints = accountEdit.extraComplaints

            if (accountEdit.extraSessionComplaints is not None) and str(acc.model.LordInfo.ExtraComplaintsSession) != str(accountEdit.extraSessionComplaints):
                self.handler.I.STATS.addGMEditUser( acc.auid, gmLogin, "ExtraComplaintsSession", str(acc.model.LordInfo.ExtraComplaintsSession), str(accountEdit.extraSessionComplaints) )
                debug("EditAccount accountEdit.extraSessionComplaints %r", accountEdit.extraSessionComplaints)
                if accountEdit.extraSessionComplaints < acc.model.LordInfo.ExtraComplaintsSession:
                    acc.model.LordInfo.ComplaintsSessionLeft -= acc.model.LordInfo.ExtraComplaintsSession -accountEdit.extraSessionComplaints
                    acc.model.LordInfo.ComplaintsSessionLeft = 0 if acc.model.LordInfo.ComplaintsSessionLeft < 0 else acc.model.LordInfo.ComplaintsSessionLeft
                else:
                    acc.model.LordInfo.ComplaintsSessionLeft += accountEdit.extraSessionComplaints - acc.model.LordInfo.ExtraComplaintsSession
                acc.model.LordInfo.ExtraComplaintsSession = accountEdit.extraSessionComplaints

        else:
            err("EditAccount error, get acc by login(%s) fail", login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success

    def EditAccountResources(self, login, accountEdit, gmLogin, extra_comment=""):
        debug("EditAccountResources %r, %r, %r, %r",  login, accountEdit, gmLogin, extra_comment)
        self.login = login
        acc = self.handler.I.WS.getUserAcc(login)
        if acc:
            acc.model.write(acc.pending)
            if acc.db.fraction == 'N':
                newFraction = "B"
                if (accountEdit.fraction is not None):
                  newFraction = party_const.FRACTION_LIST[accountEdit.fraction]
                self.GMToolBan( acc )
                subParams = ClassDict(fraction=[newFraction])
                accountAction = SetFractionAction(subParams, self.callbackFn, I=self.handler.I, acc=acc, uid=acc.uid)
                accountAction.onStart()

            if accountEdit.fraction in [0, 1]:
                newFraction = party_const.FRACTION_LIST[accountEdit.fraction]
                if newFraction != acc.db.fraction and acc.online:
                    self.GMToolBan(acc)
                if str(acc.db.fraction) != str(newFraction):
                    self.handler.I.STATS.addGMEditUser(acc.auid, gmLogin,  "fraction" if not extra_comment else ("fraction (%r)" % extra_comment), str(acc.db.fraction),
                                                       str(newFraction))
                subParams = ClassDict(fraction=[newFraction])
                accountAction = Change_fraction_GM(subParams, self.callbackFn, I=self.handler.I, acc=acc, uid=acc.uid)
                accountAction.onStart()

            if accountEdit.silver is not None:
                self.handler.I.STATS.addGMEditUser(acc.auid, gmLogin, "Silver" if not extra_comment else ("Silver (%r)" % extra_comment), str(acc.model.Resources.Silver),
                                                   str(acc.model.Resources.Silver + accountEdit.silver))
                acc.model.Resources.Silver += accountEdit.silver
                acc.model.Resources.Silver = max(acc.model.Resources.Silver, 0)

            if accountEdit.resource1 is not None:
                self.handler.I.STATS.addGMEditUser(acc.auid, gmLogin, "Resource1" if not extra_comment else ("Resource1 (%r)" % extra_comment), str(acc.model.Resources.Resource1),
                                                   str(acc.model.Resources.Resource1 + accountEdit.resource1))
                acc.model.Resources.Resource1 += accountEdit.resource1
                acc.model.Resources.Resource1 = max(acc.model.Resources.Resource1, 0)

            if accountEdit.resource2 is not None:
                self.handler.I.STATS.addGMEditUser(acc.auid, gmLogin, "Resource2"  if not extra_comment else ("Resource2 (%r)" % extra_comment), str(acc.model.Resources.Resource2),
                                                   str(acc.model.Resources.Resource2 + accountEdit.resource2))
                acc.model.Resources.Resource2 += accountEdit.resource2
                acc.model.Resources.Resource2 = max(acc.model.Resources.Resource2, 0)

            if accountEdit.resource3 is not None:
                self.handler.I.STATS.addGMEditUser(acc.auid, gmLogin, "Resource3"  if not extra_comment else ("Resource3 (%r)" % extra_comment), str(acc.model.Resources.Resource3),
                                                   str(acc.model.Resources.Resource3 + accountEdit.resource3))
                acc.model.Resources.Resource3 += accountEdit.resource3
                acc.model.Resources.Resource3 = max(acc.model.Resources.Resource3, 0)

            if accountEdit.perl is not None:
                self.handler.I.STATS.addGMEditUser(acc.auid, gmLogin, "Perl" if not extra_comment else ("Perl (%r)" % extra_comment), str(acc.model.Resources.Perl),
                                                   str(acc.model.Resources.Perl + accountEdit.perl))
                acc.model.Resources.Perl += accountEdit.perl
                acc.model.Resources.Perl = max(acc.model.Resources.Perl, 0)

            if accountEdit.redPerl is not None:
                self.handler.I.STATS.addGMEditUser(acc.auid, gmLogin, "RedPerl" if not extra_comment else ("RedPerl (%r)" % extra_comment), str(acc.model.Resources.RedPerl),
                                                   str(acc.model.Resources.RedPerl + accountEdit.redPerl))
                acc.model.Resources.RedPerl += accountEdit.redPerl
                acc.model.Resources.RedPerl = max(acc.model.Resources.RedPerl, 0)

            if accountEdit.cwplayerpoints is not None:
                self.handler.I.STATS.addGMEditUser(acc.auid, gmLogin, "CWPoints_Player" if not extra_comment else ("CWPoints_Player (%r)" % extra_comment),
                                                   str(acc.model.Resources.CWPoints_Player),
                                                   str(acc.model.Resources.CWPoints_Player + accountEdit.cwplayerpoints))
                acc.model.Resources.CWPoints_Player += accountEdit.cwplayerpoints
                acc.model.Resources.CWPoints_Player = max(acc.model.Resources.CWPoints_Player, 0)

            if accountEdit.Shard is not None:
                self.handler.I.STATS.addGMEditUser(acc.auid, gmLogin, "Shard" if not extra_comment else ("Shard (%r)" % extra_comment),
                                                   str(acc.model.Resources.Shard),
                                                   str(acc.model.Resources.Shard + accountEdit.Shard))
                acc.model.Resources.Shard += accountEdit.Shard
                acc.model.Resources.Shard = max(acc.model.Resources.Shard, 0)

            if accountEdit.currencies is not None:
                for currencyName, currencyVal in accountEdit.currencies.iteritems():
                    plusVal = accountEdit.currencies.get(currencyName, 0)
                    oldValue = 0 if currencyName not in acc.model.Resources.Currencies else acc.model.Resources.Currencies[currencyName]
                    acc.model.Resources.Currencies[currencyName] = oldValue + plusVal
                    acc.model.Resources.Currencies[currencyName] = max(acc.model.Resources.Currencies[currencyName], 0)
                    self.handler.I.STATS.addGMEditUser(acc.auid, gmLogin,
                                                       "Currency:{}".format(currencyName),
                                                       str(oldValue),
                                                       str(acc.model.Resources.Currencies[currencyName]))

            self.handler.I.WS.updateGameDataToPersonServer(acc)
        else:
            err("EditAccountResources error, get acc by login(%s) fail", login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success
        

    def EditTalent( self, login, talentEdit, gmLogin ):
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )
            talent = acc.model.getTalentByID( talentEdit.talentInstanceId )
            if talent:
                # staticTalent = acc.SD.getStaticTalent( talent ) # PF-100683 (with next two lines)
                # if staticTalent['rarity'] == "Class":
                #    return AccountManagementAPI.ttypes.RequestResult.Success

                if talent.Points != talentEdit.refineRate:
                    data = "Refine, pointsBefore=%d, pointsAfter=%d" % (talent.Points, talentEdit.refineRate)
                    talent.Points = talentEdit.refineRate
                    self.handler.I.STATS.addGMOperation(acc.auid, GMOperationType.TalentEdit, gmLogin, data)

                telentBound = talent.Soulbound.get()
                talentBoundID = 0
                if telentBound:
                    talentBoundID = telentBound.getID()
                    if talentEdit.boundHeroInstanceId != talentBoundID and talent.id in telentBound.TalentSets[telentBound.ActiveTalentSet].Talents.values():
                        self.handler.I.STATS.addMoveTalentFromSet(acc.auid, acc.nick, talent.PersistentId, telentBound.PersistentId, 0)
                        telentBound.removeTalentFromTalentSet(telentBound.ActiveTalentSet, talent, talentEdit.talentInstanceId)
                  
                # если либо не было привязки и устанавливается, либо новая привязка отлична от старой
                if talentBoundID != talentEdit.boundHeroInstanceId and talent.canBeSoulbound(acc.SD):
                    talent.Soulbound = talentEdit.boundHeroInstanceId
                    newBound = talent.Soulbound.get()
                    self.handler.I.STATS.addTalentChange(acc.auid,
                        StatisticCore.ttypes.TalentInfo(talent.PersistentId, talentEdit.talentInstanceId, newBound.PersistentId if newBound else 0),
                        TalentChangeOperation.Soulbound)
                    data = "Soulbound, boundHeroBefore=%d, boundHeroAfter=%d" % (talentBoundID,
                                                                                 newBound.PersistentId if newBound else 0)
                    self.handler.I.STATS.addGMOperation(acc.auid, GMOperationType.TalentEdit, gmLogin, data)
            else:
                err("EditTalent error, talent(%d) is null" % talentEdit.talentInstanceId)
                return AccountManagementAPI.ttypes.RequestResult.TalentInstIdNotExist
        else:
            err("EditTalent error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success
 
    def AddTalent( self, login, talentClassId, gmLogin, extra_comment=""):
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )
            talent_id = acc.model.addNewTalent()
            talent = acc.model.getTalentByID( talent_id )
            talent.IsNew = True
            talent.PersistentId = talentClassId
            acc.model.UserInventory.add( talent_id )
            data = "classId=%r instanceId=%r boundHeroClassId=%r" % ( talentClassId, talent_id, 0,)
            self.handler.I.STATS.addGMOperation( acc.auid, GMOperationType.TalentAdd, gmLogin, data if not extra_comment else "{0} ({1})".format(data, extra_comment)  )
        else:
            err("AddTalent error, get acc by login(%s) fail", login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success


    def AddTalents( self, login, talentIds, gmLogin, extra_comment="" ):
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )
            for talentClassId in talentIds:
                talent_id = acc.model.addNewTalent()
                talent = acc.model.getTalentByID( talent_id )
                talent.IsNew = True
                talent.PersistentId = talentClassId
                acc.model.UserInventory.add( talent_id )
                data = "classId=%r instanceId=%r boundHeroClassId=%r" % ( talentClassId, talent_id, 0 )
                self.handler.I.STATS.addGMOperation( acc.auid, GMOperationType.TalentAdd, gmLogin, data if not extra_comment else "{0} ({1})".format(data, extra_comment)  )
        else:
            err("AddTalent error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success


    def DeleteTalent( self, login, talentInstanceId, gmLogin ):
        self.login = login
        acc = self.handler.I.WS.getUserAcc( self.login )
        if acc:
            acc.model.write( acc.pending )
            talent = acc.model.getTalentByID( talentInstanceId )
            if talent:
                isBounded = not (talent.Soulbound == IGuidGenerator.InvalidUID or talent.Soulbound.get() == None)
                if isBounded:
                    boundHeroId = talent.Soulbound.get().getID()
                    boundClassId = talent.Soulbound.get().PersistentId
                else:
                    boundHeroId = 0
                    boundClassId = 0
 
                data = "classId=%r instanceId=%r boundHeroClassId=%r" % ( talent.PersistentId, talent.getID(), boundClassId )
                self.handler.I.STATS.addGMOperation( acc.auid, GMOperationType.TalentDelete, gmLogin, data )
            subParams = ClassDict( talents=[str(talentInstanceId)], rid=[1] )
            accountAction = Remove_talents( subParams, self.callbackFn, I=self.handler.I, acc=acc, uid=acc.uid )
            accountAction.onStart()
        else:
            err("DeleteTalent error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success

    ## UserOperation handler and subhandlers - BEGIN -----------------------------------------

    def _performBanUser(self, acc, gmLogin, minutes, reason, claims, claimAuids, points):
        subParams = ClassDict(minutes=[minutes], reason=[reason], autoBan=[0], rid=[1])
        accountAction = Ban_account(subParams, partial(self.callbackFnAuid, auid=acc.auid), I=self.handler.I, acc=acc, uid=acc.uid)
        accountAction.onStart()
        self.handler.I.STATS.addBanUser(acc.auid, gmLogin, minutes, reason, claims)
        if claimAuids:
            for auid in claimAuids:
                self.handler.I.DATA.increment(CC.PUNISHED_BY_CLAIM, CC.PUNISHED_BY_CLAIM,
                                              {"_id": auid}, {"punishedPlayers": 1},
                                              params=None, callback=None)

    def _performUnbanUser(self, acc, gmLogin, *stub):
        acc.db.banned = False
        acc.db.bantime = 0
        acc.db.banreason = ""
        self.handler.I.STATS.addUnbanUser(acc.auid, gmLogin)

    def _performMuteUser(self, acc, gmLogin, minutes, reason, claims, claimAuids, points):
        subParams = ClassDict(minutes=[minutes], reason=[reason], rid=[1])
        accountAction = Mute_account(subParams, partial(self.callbackFnAuid, auid=acc.auid), I=self.handler.I, acc=acc, uid=acc.uid)
        accountAction.onStart()
        self.handler.I.STATS.addMuteUser(acc.auid, gmLogin, minutes, reason, claims)
        self.handler.I.PS.mute(acc.auid, 1)
        if acc.chat:
            self.handler.I.CHAT.muteUser(acc.chat['host'], acc.auid, 1, acc.db.mutetime, None)
        else:
            warn("MuteUser: no acc.chat for auid=%s", acc.auid)

    def _performUnmuteUser(self, acc, gmLogin, *stub):
        acc.db.muted = 0
        acc.db.mutetime = 0
        acc.db.mutereason = ""
        self.handler.I.STATS.addUnmuteUser(acc.auid, gmLogin)
        self.handler.I.PS.mute(acc.auid, 0)
        if acc.chat:
            self.handler.I.CHAT.unmuteUser(acc.chat['host'], acc.auid, None)
        else:
            warn("UnmuteUser: no acc.chat for auid=%s", acc.auid)

    def _performForgiveUser(self, acc, gmLogin, minutes, reason, claims, claimAuids, points):
        self.handler.I.STATS.addForgiveUser(acc.auid, gmLogin, reason, claims)

    def _performSetLeaveUser(self, acc, gmLogin, minutes, reason, claims, claimAuids, points):
        leaverStatusBefore = acc.model.LordInfo.GuardInfo.isLeaver
        _, leaverPointsChange = acc.model.changeLeaverStatus(acc, "", True, {}, self.handler.I, True, points)
        self.handler.I.STATS.addSetLeaveUser(acc.auid, gmLogin, reason, points, claims)

        self.handler.I.STATS.addLeaverPointsChange(acc.auid, enum2String(LeavePointReason, LeavePointReason.BADBEHAVIOUR_GM), leaverPointsChange,
                                                    acc.model.LordInfo.GuardInfo.LeavesPoint,
                                                    acc.model.LordInfo.GuardInfo.isLeaver != leaverStatusBefore,
                                                    acc.model.LordInfo.GuardInfo.isLeaver,
                                                    acc.model.LordInfo.GuardInfo.isBadBehaviour
                                                    )


    user_operations = {
        UserOperationType.Ban:     _performBanUser,
        UserOperationType.Unban:   _performUnbanUser,
        UserOperationType.Mute:    _performMuteUser,
        UserOperationType.Unmute:  _performUnmuteUser,
        UserOperationType.Forgive: _performForgiveUser,
        UserOperationType.SetLeave: _performSetLeaveUser,
    }

    def UserOperation(self, auid, optype, minutes, reason, claims, gmLogin, claimAuids, points):
        if optype in self.user_operations:
            acc = self.handler.I.WS.getUserAccByAuid(auid)
            if acc:
                acc.model.write(acc.pending)
                self.user_operations[optype](self, acc, gmLogin, minutes, reason, claims, claimAuids, points)
                return AccountManagementAPI.ttypes.RequestResult.Success
            else:
                err("UserOperation(%s) error, get acc by auid(%s) fail", optype, auid)
                return AccountManagementAPI.ttypes.RequestResult.AuidNotExist
        else:
            err("UserOperation error: unknown operation type %s", optype)
            return AccountManagementAPI.ttypes.RequestResult.UnknownOperationType

    # keep these 4 old methods to catch case if somwehere they are called
    #TODO: remove them later
    def BanUser( self, login, auid, minutes, reason, gmLogin ):
        err("Obsolete AccountManagementServerHandler.BanUser() called: " + traceback.format_stack())
        return AccountManagementAPI.ttypes.RequestResult.BadResult
    
    def UnbanUser( self, login, auid, gmLogin ):
        err("Obsolete AccountManagementServerHandler.UnbanUser() called: " + traceback.format_stack())
        return AccountManagementAPI.ttypes.RequestResult.BadResult

    def MuteUser( self, login, auid, minutes, reason, gmLogin ):
        err("Obsolete AccountManagementServerHandler.MuteUser() called: " + traceback.format_stack())
        return AccountManagementAPI.ttypes.RequestResult.BadResult

    def UnmuteUser( self, login, auid, gmLogin ):
        err("Obsolete AccountManagementServerHandler.UnmuteUser() called: " + traceback.format_stack())
        return AccountManagementAPI.ttypes.RequestResult.BadResult

    ## UserOperation handler and subhandlers - END ---------------------------------------

    def KickUser( self, login, gmLogin ):
        info("AccountManagementServerHandler.KickUser %s by %s", login, gmLogin)
        self.login = login
        acc = self.handler.I.WS.getUserAcc( self.login )
        if acc:
            acc.model.write( acc.pending )
            self.startLogoutProcess(acc)
            raise AsyncThriftException("async kickuser")
        else:
            if getattr(self, "logout_done", None):
                return AccountManagementAPI.ttypes.RequestResult.Success
            else:
                err("KickUser error, get acc by login(%s) fail", login)
                return AccountManagementAPI.ttypes.RequestResult.LoginNotExist

    def startLogoutProcess(self, acc):
        subParams = ClassDict(kick=[True])
        accountAction = LogoutAction(subParams, self.callbackFn, I=self.handler.I, acc=acc, uid=acc.uid)
        accountAction.onStart()
        AddLoopCallback(self.onKickUserPause, 1.5)

    def onKickUserPause(self):
        acc = self.handler.I.WS.getUserAcc(self.login)
        if not acc:
            self.logout_done = True;
            self.handler.process() # вызываем повторную обработку евента (теперь должно вернуть ответ)
        else: # still not logged out!
            self.startLogoutProcess(acc)

    def FixAccount( self, login, gmLogin ):
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )
            acc.model.fixAll( acc, acc.SD )
        else:
            err("FixAccount error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success

    def EditAccountDbValue(self, login, gmLogin, key, value):
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )
            if value:
                acc.db[key] = value
            else:
                acc.db.pop(key, None)
        else:
            err("EditAccountDbValue error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success

    def CheckAccountValidity( self, login ):
        self.login = login
        acc = self.handler.I.WS.getUserAcc( login )
        if acc:
            acc.model.write( acc.pending )
            ok, valid_info = acc.model.checkValidity( acc, acc.SD )
            if ok:
                return StringDataResponse( RequestResult.Success, valid_info )
            else:
                return StringDataResponse( RequestResult.BadResult, valid_info )
        else:
            err("CheckAccountValidity error, get acc by login(%s) fail" % login)
            return StringDataResponse( RequestResult.LoginNotExist, "LoginNotExist" )


    def RegisterPayment( self, auid, amount, source, txnid ):
        acc = self.handler.I.WS.getUserAccByAuid( auid )
        if acc and isinstance(acc.model, ModelData):
            acc.model.write( acc.pending )
            bonus_amount = acc.model.registerPayment( acc, self.handler.I, amount, source, txnid )
            return AccountManagementAPI.ttypes.RegisterPaymentResponse( RequestResult.Success, bonus_amount )
        else:
            err("RegisterPayment error, get acc by auid(%s) fail", auid)
            return AccountManagementAPI.ttypes.RegisterPaymentResponse( RequestResult.LoginNotExist, 0 )


    def ReplenishUserGold( self, auid, amount, payment_system ):
        acc = self.handler.I.WS.getUserAccByAuid( auid )
        if acc:
            payInfo = "From thrift ReplenishUserGold, payment_system = %r" % payment_system
            self.handler.I.BILL.replenish( auid, amount, payInfo, None, payment_system=payment_system )
        return AccountManagementAPI.ttypes.RequestResult.Success

    def UpdateUserGold( self, auid ):
        acc = self.handler.I.WS.getUserAccByAuid( auid )
        if acc:
            debug("From thrift UpdateUserGold, auid = %r", auid)
            acc.model.updateBalanceInfo(acc, self.handler.I.BILL, forced_update=True)
            return AccountManagementAPI.ttypes.RequestResult.Success

        return AccountManagementAPI.ttypes.RequestResult.AuidNotExist
        
    def GetPaymentBonusActions( self, auid ): 
        acc = self.handler.I.WS.getUserAccByAuid( auid )
        if acc and isinstance(acc.model, ModelData):
            acc.model.write( acc.pending )
            result = acc.model.getPaymentBonusActions()
            return AccountManagementAPI.ttypes.GetPaymentBonusActionsResponse( RequestResult.Success, result )
        else:
            err("GetPaymentBonusActions error, get acc by auid(%s) fail" % auid)
            return AccountManagementAPI.ttypes.GetPaymentBonusActionsResponse( RequestResult.LoginNotExist, None )


    def GetAccountBuildings( self, auid ):
        acc = self.handler.I.WS.getUserAccByAuid( auid )
        if acc and isinstance(acc.model, ModelData):
            buildings = []
            for constructionId in acc.model.ConstructionsKeeper:
                construction = acc.model.getConstructionByID( constructionId )
                buildings.append( AccountManagementAPI.ttypes.BuildingInfo( classid = construction.PersistentId,
                                                                            instanceid = construction.getID(),
                                                                            level = construction.Level,
                                                                            instorage = constructionId in acc.model.Pocket.keys() ) )
            return AccountManagementAPI.ttypes.BuildingsInfoResponse( RequestResult.Success, auid, buildings )
        else:
            err( "GetAccountBuildings error, get acc by auid(%s) fail" % auid )
            return AccountManagementAPI.ttypes.BuildingsInfoResponse( RequestResult.LoginNotExist, auid, 0 )


    def MoveBuildingToStorage( self, auid, buildingInstanceId, gmLogin ):
        acc = self.handler.I.WS.getUserAccByAuid( auid )
        if acc and isinstance(acc.model, ModelData):
            acc.model.write( acc.pending )
            subParams = ClassDict( building_id=[buildingInstanceId], rid=[1] )
            self.handler.I.STATS.addGMOperation( acc.auid, GMOperationType.BuildingMoveToStorage, gmLogin, "Building(%r) moved to storage" % buildingInstanceId )
            accountAction = Move_to_pocket( subParams, partial(self.callbackFnAuid, auid=acc.auid), I=self.handler.I, acc=acc, uid=acc.uid )
            accountAction.onStart()
        else:
            err( "MoveBuildingToStorage error, get acc by auid(%s) fail" % auid )
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success


    def AddBuilding( self, auid, buildingClassId, level, gmLogin, extra_comment="" ):
        acc = self.handler.I.WS.getUserAccByAuid( auid )
        if acc and isinstance(acc.model, ModelData):
            acc.model.write( acc.pending )
            staticConstruction = acc.SD.getStaticConstructionByPersistentId( buildingClassId )
            if staticConstruction:
                if acc.model.canPlaceBuilding( staticConstruction, acc.SD ):
                    data = "Building(%r:%r) added" % (buildingClassId,level)
                    self.handler.I.STATS.addGMOperation( acc.auid, GMOperationType.BuildingAdd, gmLogin,  data if not extra_comment else "{0} ({1})".format(data, extra_comment) )
                    construction_uid = acc.model.addNewConstruction()
                    construction = acc.model.getConstructionByID( construction_uid )
                    construction.PersistentId = buildingClassId
                    construction.Level = level
                    acc.model.Pocket.add( construction )
                else:
                    err( "AddBuilding error, too many buildings(%s), check limits!" % buildingClassId )
                    return AccountManagementAPI.ttypes.RequestResult.BadResult
            else:
                err( "AddBuilding error, staticConstruction(%s) not found" % buildingClassId )
                return AccountManagementAPI.ttypes.RequestResult.BadResult
        else:
            err( "AddBuilding error, get acc by auid(%s) fail" % auid )
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success


    def DeleteBuilding( self, auid, buildingInstanceId, gmLogin ):
        acc = self.handler.I.WS.getUserAccByAuid( auid )
        if acc and isinstance(acc.model, ModelData):
            acc.model.write( acc.pending )
            subParams = ClassDict( building_id=[buildingInstanceId], rid=[1] )
            self.handler.I.STATS.addGMOperation( acc.auid, GMOperationType.BuildingDelete, gmLogin, "Building(%r) deleted" % buildingInstanceId )
            accountAction = Building_remove( subParams, partial(self.callbackFnAuid, auid=acc.auid), I=self.handler.I, acc=acc, uid=acc.uid )
            accountAction.onStart()
        else:
            err( "DeleteBuilding error, get acc by auid(%s) fail" % auid )
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success


    def GetAccountSkins( self, auid ):
        acc = self.handler.I.WS.getUserAccByAuid( auid )
        if acc and isinstance(acc.model, ModelData):
            skins = []
            for skinId in acc.SD.data['Skins'].keys():
                skinSD = acc.SD.data['Skins'][skinId]
                if acc.db.fraction not in acc.SD.getFractions( skinSD['heroRace'] ):
                    continue
                hero = acc.model.getHeroForSkin( skinSD, acc.SD )
                if not hero:
                    continue

                heroClassId = acc.model.getHeroClassIdForSkin( skinSD, acc.SD )
                
                isOwned = False
                if acc.model.isSkinOwned(skinId, acc.SD):
                    isOwned = True

                validSkin = acc.model.isValidSkinByData( skinId, acc )
                skinCost = int(skinSD['cost'])
                if skinSD['persistentId'] in acc.getConfig().EventToolsChangeFields.SKIN_GOLD_PRICES:
                  skinCost = acc.getConfig().EventToolsChangeFields.SKIN_GOLD_PRICES[skinSD['persistentId']]
                skins.append( AccountManagementAPI.ttypes.SkinInfo( persistentId = skinSD['persistentId'],
                                                                    heroClassId = heroClassId,
                                                                    owned = isOwned,
                                                                    available = validSkin,
                                                                    cost = skinCost ) )
            return AccountManagementAPI.ttypes.SkinsResponse( RequestResult.Success, auid, skins )
        else:
            err( "GetAccountSkins error, get acc by auid(%s) fail" % auid )
            return AccountManagementAPI.ttypes.SkinsResponse( RequestResult.LoginNotExist, auid, 0 )


    def AddSkin( self, auid, skinPersistentId, gmLogin, extra_comment=""):
        acc = self.handler.I.WS.getUserAccByAuid( auid )
        if acc and isinstance(acc.model, ModelData):
            acc.model.write( acc.pending )
            persistentId = crc32( skinPersistentId )
            addedSkin, reason = acc.model.giveSkinForFree( persistentId, acc, wasBought = True, withoutCheck = True )
            data = "Add skin(%r)" % skinPersistentId
            self.handler.I.STATS.addGMOperation( acc.auid, GMOperationType.SkinAdd, gmLogin, data if not extra_comment else "{0} ({1})".format(data, extra_comment)  )
        else:
            err( "AddSkin error, get acc by auid(%s) fail" % auid )
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success


    def DeleteSkin( self, auid, skinPersistentId, gmLogin, extra_comment="" ):
        acc = self.handler.I.WS.getUserAccByAuid( auid )
        if acc and isinstance(acc.model, ModelData):
            acc.model.write( acc.pending )
            persistentId = crc32( skinPersistentId )
            static_skin = acc.SD.getStaticSkinByPersistentId( persistentId )
            hero = acc.model.getHeroForSkin( static_skin, acc.SD )
            if hero:
                hero.HeroSkins.CurrentSkin = IGuidGenerator.InvalidUID 
      
            for skinId in acc.model.SkinsKeeper.keys():
                skin = acc.model.getSkinByID( skinId )
                if skin.PersistentId == persistentId:
                    acc.model.deleteByID(skin.id)
                    data = "Delete skin(%r)" % skinPersistentId
                    self.handler.I.STATS.addGMOperation( acc.auid, GMOperationType.SkinDelete, gmLogin, data if not extra_comment else "{0} ({1})".format(data, extra_comment) )
        else:
            err( "DeleteSkin error, get acc by auid(%s) fail" % auid )
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success

    '''
    Return list of TalentUpgradeEntityInfo:
    1: string persistentId
    2: i32 chance
    3: TalentUpgradeEntityType type
    4: i32 talentLevelLimit
    '''
    def GetAccountTalentUpgradeEntities(self, auid):
        acc = self.handler.I.WS.getUserAccByAuid(auid)
        if acc and isinstance(acc.model, ModelData):
            entities = []
            for entId in acc.model.TalentUpgradeEntities:
                entity = acc.model.getTalentUpgradeEntityByID(entId)
                static_ent = acc.SD.getStaticTalentUpgradeEntityById(entity.PersistentId)
                if not static_ent:
                    warn("GetAccountTalentUpgradeEntities warning, get acc talent entity by persistentId(%d) fail" % entity.PersistentId)
                    continue

                entities.append(AccountManagementAPI.ttypes.TalentUpgradeEntityInfo(
                    instanceId=entId,
                    persistentId=static_ent['persistentId'],
                    chance=static_ent['probability'],
                    talentLevelLimit=static_ent['talentLevelLimit'],
                    type=static_ent['type']))
            return AccountManagementAPI.ttypes.TalentUpgradeEntitiesResponse(RequestResult.Success, auid, entities)
        else:
            err("GetAccountTalentUpgradeEntities error, get acc by auid(%s) fail" % auid)
            return AccountManagementAPI.ttypes.TalentUpgradeEntitiesResponse(RequestResult.LoginNotExist, auid, 0)

    def DeleteTalentUpgradeEntity(self, auid, instanceId, gmLogin, extra_comment=""):
        acc = self.handler.I.WS.getUserAccByAuid(auid)
        if acc and isinstance(acc.model, ModelData):
            acc.model.write(acc.pending)
            entity = acc.model.getTalentUpgradeEntityByID(instanceId)
            if entity:
                acc.model.TalentUpgradeEntities.remove(entity)
                data = "Delete talent upgrade entity(%r)" % instanceId
                self.handler.I.STATS.addGMOperation(acc.auid, GMOperationType.TalentUpgradeEntityDelete, gmLogin,
                                                    data if not extra_comment else "{0} ({1})".format(data,
                                                                                                      extra_comment))
        else:
            err("DeleteTalentUpgradeEntity error, get acc by auid(%s) fail" % auid)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success

    # ---------------------------------------------------------------------------------------------
    def TryToPayForGuildIconChange( self, leaderauid, changeiter ):
        self.logs_prefix = "Guild Icon Change Purchase leaderauid=%d:"%(leaderauid)
        info("%s TryToPayForGuildIconChange"%(self.logs_prefix))
        self.leaderauid = leaderauid
        acc = self.handler.I.WS.getUserAccByAuid( leaderauid )
        if acc:
            freeChanges = acc.getConfigValue("GUILD_FREE_ICON_CHANGES_COUNT")
            changeCost = acc.getConfigValue("GUILD_ICON_CHANGE_COST")

            info("%s free changes = %d, change cost = %d"%(self.logs_prefix,freeChanges,changeCost))

            self.isFreeOperation = changeiter < freeChanges
            if self.isFreeOperation:
                info("%s free operation %d/%d. Completed"%(self.logs_prefix,changeiter,freeChanges))
                return ServerActionResponse( RequestResult.Success )
            else:
                info("%s paid operation %d/%d"%(self.logs_prefix,changeiter,freeChanges))

                if acc.TryToPayForGuildIconChange_Result is None:
                    subParams = ClassDict( changeiter=[changeiter] )
                    accountAction = Purchase_guild_icon_change( subParams, self.onTryToPayForGuildIconChange, I=self.handler.I, acc=acc, uid=acc.uid )
                    accountAction.onStart()
                            
                    # ждем асинхронной обработки; временно срубим исполнение thrift-обработчика специальным exception-ом
                    raise AsyncThriftException("%s async TryToPayForGuildIconChange"%(self.logs_prefix))
                else:
                    info("%s operation completed"%self.logs_prefix)
                    result = acc.pop("TryToPayForGuildIconChange_Result")
                    if result.ok:
                        return ServerActionResponse( RequestResult.Success )
                    else:
                        return ServerActionResponse( RequestResult.BadResult, str(result.error), \
                            toint(result.ec), str(result.error_args ))
        else:
            errstr = "%s error, get leader acc by auid(%s) fail" % (self.logs_prefix, self.leaderauid)
            err( errstr )
            return ServerActionResponse( RequestResult.AuidNotExist, errstr )

    def onTryToPayForGuildIconChange(self, action_response):
        info( "%s onTryToPayForGuildIconChange" % (self.logs_prefix) )
        acc = self.handler.I.WS.getUserAccByAuid( self.leaderauid )
        if acc:
            acc.TryToPayForGuildIconChange_Result = ClassDict(
                ok = action_response.get("ok", 0),
                error = action_response.get("error", ""),
                ec = action_response.get("ec", 0),
                error_args = action_response.get("error_args", {}),
            )
            info( "%s result: %s" % (self.logs_prefix, acc.TryToPayForGuildIconChange_Result) )
        else:
            err( "%s error, get acc by auid(%s) fail" % (self.logs_prefix, self.leaderauid) )
        self.handler.process() # вызываем повторную обработку евента (теперь должно вернуть ответ)  


    def BuyTournamentTicket( self, login, pttype ):
        self.login = login
        acc = self.handler.I.WS.getUserAcc( self.login )
        if acc:
            if pttype == PayTicketType.Silver:
              subParams = ClassDict( paymentType=[TicketPaymentType.Silver] )
            elif pttype == PayTicketType.Gold:
              subParams = ClassDict( paymentType=[TicketPaymentType.Gold] )
            else:
              subParams = ClassDict( paymentType=[TicketPaymentType.Silver], force_free = [1] )

            buyTicketAction = Buy_tournament_ticket( subParams, self.callbackFn, I=self.handler.I, acc=acc, uid=acc.uid )
            buyTicketAction.onStart()
        else:
            err("BuyTournamentTicket error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success


    def UpdateGeoshowFlag(self, auid, isAllowed):
        info("UpdateGeoshowFlag %s: %s", auid, isAllowed)
        acc = self.handler.I.WS.getUserAccByAuid(auid)
        if acc and isinstance(acc.model, ModelData):
            acc.model.write( acc.pending )
            acc.db.gallow = bool(isAllowed)
            self.I.WS.saveUserData( acc )
        else:
            err("UpdateGeoshowFlag: No user with auid %s found!", auid)
            return RequestResult.AuidNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success


    def BindToGeolocation(self, auid, country, region, city, gmLogin):
        info("BindToGeolocation %s: %s, %s, %s", auid, country, region, city)
        if (country, region, city).count(None) not in (0, 3): # либо все None, либо все заданы!
            warn("BindToGeolocation: country, region, city must be all None or all not None!")
            return AccountManagementAPI.ttypes.RequestResult.BadResult
        acc = self.handler.I.WS.getUserAccByAuid(auid)
        if acc and isinstance(acc.model, ModelData):
            acc.model.write(acc.pending)
            old_ovr = acc.db.get("geo_ovr")
            if country is None:
                if old_ovr is not None:
                    del acc.db["geo_ovr"]
            else:
                acc.db.geo_ovr = ClassDict(country=country, region=region, city=city)
            self.handler.I.STATS.addGMEditUser(acc.auid, gmLogin, "geo_ovr", str(old_ovr), str(acc.db.geo_ovr) )
        else:
            err("BindToGeolocation: No user with auid %s found!", auid)
            return RequestResult.AuidNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success


    def GetLocaleInfoBySNUid(self, snid, snuid):
        acc = self.I.WS.getUserAccSN(snid, snuid)
        if acc:
            return _GetLocaleInfo(acc)
        else:
            err("GetLocaleInfoBySNUid: No user with login %s#%s found!", snid, snuid)
            return LocaleInfoResponse(RequestResult.SnUidNotExist, LocaleInfo())

    def GetLocaleInfoByAuid(self, auid):
        acc = self.I.WS.getUserAccByAuid(auid)
        if acc:
            return _GetLocaleInfo(acc)
        else:
            err("GetLocaleInfoByAuid: No user with auid %s found!", auid)
            return LocaleInfoResponse(RequestResult.AuidNotExist, LocaleInfo(   ))

    def GetQuests(self, auid):
        acc = self.handler.I.WS.getUserAccByAuid(auid)
        if acc and isinstance(acc.model, ModelData):
            quests = []
            for questLine in acc.SD.data['QuestsLine']['Item']:
                for staticQuest in questLine['quests']['Item']:
                    for questId in acc.model.QuestsKeeper:
                        quest = acc.model.getQuestByID(questId)
                        if quest and quest.persistentId == crc32(staticQuest['persistentId']):
                            quests.append(AccountManagementAPI.ttypes.QuestInfo(auid=auid,
                                                                              questid=quest.persistentId,
                                                                              name=staticQuest.get('persistentId') or "",
                                                                              status=quest.state + 1))
                            break
                    quests.append(AccountManagementAPI.ttypes.QuestInfo(auid=auid,
                                                                      questid=crc32(staticQuest['persistentId']),
                                                                      name=staticQuest.get('persistentId') or "",
                                                                      status=0))
            return AccountManagementAPI.ttypes.QuestsInfoResponse( RequestResult.Success, quests )
        else:
            err( "GetQuests error, get acc by auid(%s) fail" % auid )
            return AccountManagementAPI.ttypes.QuestsInfoResponse(RequestResult.LoginNotExist, 0)

    def ChangeQuest(self, auid, persistentId, action, gmLogin):
        acc = self.handler.I.WS.getUserAccByAuid(auid)
        if acc and isinstance(acc.model, ModelData):
            config = acc.getConfig()
            staticQuest = acc.SD.getStaticQuestById(persistentId)
            if staticQuest is not None:
                if action == AccountManagementAPI.ttypes.QuestChangeAction.Add:
                    questLine = acc.SD.getStaticQuestLineByStaticQuestId(staticQuest['persistentId'])
                    # Проверим все квесты, которые предшествуют нашему квесту в линейке:
                    if questLine != None:
                        for questFromLine in questLine['quests']['Item']:
                            if questFromLine['persistentId'] != staticQuest['persistentId'] and acc.model.getActiveStaticQuest(questFromLine) is not None:
                                activeQuest = acc.model.getActiveStaticQuest(questFromLine)
                                activeQuest.state = QuestState.Complete
                                acc.model.CompletedQuests.add(activeQuest)
                                acc.model.ActiveQuests.remove(activeQuest)
                            elif questFromLine['persistentId'] == staticQuest['persistentId']:
                                # Выполненными помечаем только предыдущие квесты
                                break
                    quest = acc.model.addQuest(staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS,
                                               config.ONE_TIME_QUESTS, True, self.handler.I.STATS, acc)
                    if quest is not None:
                        data = "Add quest %s" % staticQuest['persistentId']
                        self.handler.I.STATS.addGMOperation( acc.auid, GMOperationType.QuestAdd, gmLogin, data )
                        return ServerActionResponse(AccountManagementAPI.ttypes.RequestResult.Success, "", 0, "")
                    else:
                        err("ChangeQuest error, quest(%s) can't add quest" % persistentId)
                        return ServerActionResponse(AccountManagementAPI.ttypes.RequestResult.BadResult,
                                                    "Can't add quest (%s)" % persistentId, 0, "")
                elif action == AccountManagementAPI.ttypes.QuestChangeAction.Accept:
                    quest = acc.model.getActiveStaticQuest(staticQuest)
                    if quest is not None and quest.state == QuestState.New:
                        quest.state = QuestState.InProgress
                        data = "Accept quest %s" % staticQuest['persistentId']
                        self.handler.I.STATS.addGMOperation(acc.auid, GMOperationType.QuestAccept, gmLogin, data)
                        return ServerActionResponse(AccountManagementAPI.ttypes.RequestResult.Success, "", 0, "")

                    err("ChangeQuest error, can't accept quest (%s)" % persistentId)
                    return ServerActionResponse(AccountManagementAPI.ttypes.RequestResult.BadResult,
                                                "Can't accept quest (%s), quest info was not found in active quests or quest was not in 'New' state" % persistentId, 0, "")
                elif action == AccountManagementAPI.ttypes.QuestChangeAction.Complete:
                    quest = acc.model.getActiveStaticQuest(staticQuest)
                    if quest is not None and (quest.state == QuestState.New or quest.state == QuestState.InProgress):
                        questLine = acc.SD.getStaticQuestLineByStaticQuestId(staticQuest['persistentId'])
                        acc.model.CompletedQuests.add(quest)
                        acc.model.ActiveQuests.remove(quest)
                        quest.completeQuest( questLine, staticQuest, 0, acc, self.handler.I, acc.model.getRandom(acc.model.LordInfo.RandomSeed))
                        quest.state = QuestState.Complete
                        data = "Complete quest %s" % staticQuest['persistentId']
                        self.handler.I.STATS.addGMOperation(acc.auid, GMOperationType.QuestComplete, gmLogin, data)
                        return ServerActionResponse(AccountManagementAPI.ttypes.RequestResult.Success, "", 0, "")
                    err("ChangeQuest error, can't complete quest (%s)" % persistentId)
                    return ServerActionResponse(AccountManagementAPI.ttypes.RequestResult.BadResult,
                                                "Can't complete quest (%s), quest info was not found in active quests" % persistentId, 0, "")
                elif action == AccountManagementAPI.ttypes.QuestChangeAction.Delete:
                    if acc.model.justRemoveQuest(staticQuest):
                        questLine = acc.SD.getStaticQuestLineByStaticQuestId(staticQuest['persistentId'])
                        # Проверим все квесты, которые идут после нашего квеста в линейке:
                        if questLine != None:
                            idx = 0
                            for questFromLine in questLine['quests']['Item']:
                                if questFromLine['persistentId'] == staticQuest['persistentId']:
                                    for i in xrange(idx, len(questLine['quests']['Item'])):
                                        if questLine['quests']['Item'][i] is not None:
                                            acc.model.justRemoveQuest(questLine['quests']['Item'][i])
                                            break
                                idx += 1
                        data = "Remove quest %s" % staticQuest['persistentId']
                        self.handler.I.STATS.addGMOperation(acc.auid, GMOperationType.QuestDelete, gmLogin, data)
                        return ServerActionResponse(AccountManagementAPI.ttypes.RequestResult.Success, "", 0, "")
                    err("ChangeQuest error, can't remove quest (%s)" % persistentId)
                    return ServerActionResponse(AccountManagementAPI.ttypes.RequestResult.BadResult,
                                                "Can't remove quest (%s), quest info was not found in ModelData" % persistentId, 0, "")
                else:
                    err("ChangeQuest error, bad action(%s)" % action)
                    return ServerActionResponse(AccountManagementAPI.ttypes.RequestResult.BadResult,
                                            "Wrong QuestChangeAction action (%s)" % action, 0, "")
            else:
                err( "ChangeQuest error, quest(%s) not found in StaticData" % persistentId )
                return ServerActionResponse(AccountManagementAPI.ttypes.RequestResult.BadResult,
                                            "Quest(%s) not found in StaticData" % persistentId, 0, "")
        else:
            err( "ChangeQuest error, get acc by auid(%s) fail" % auid )
            return ServerActionResponse(AccountManagementAPI.ttypes.RequestResult.AuidNotExist,
                                        "get acc by auid(%s) fail" % auid, "", 0, "")

    def ApplyDLC( self, auid, dlcid ):
        info( "ApplyDLC %s: %s", auid, dlcid )
        acc = self.handler.I.WS.getUserAccByAuid( auid )
        if acc and isinstance(acc.model, ModelData):
            acc.model.write( acc.pending )
            acc.model.tryApplyDLCs( [dlcid], acc, self.handler.I )
        else:
            err("ApplyDLC: No user with auid %s found!", auid)
            return RequestResult.AuidNotExist
        return AccountManagementAPI.ttypes.RequestResult.Success

    def GetAccountFlags(self, login):
        acc = self.handler.I.WS.getUserAcc(login)
        ownedFlags = []
        notOwnedFlags = []
        adminFlags = []
        if acc:
            acc.model.write( acc.pending )
            # Заполним флаги, которые есть у игрока
            for flagId in acc.model.Flags:
                flag = acc.SD.getCustomFlagById(flagId)
                ownedFlags.append(AccountManagementAPI.ttypes.Flag(flagPersistentId=flag['id'],
                                                              flagPrice=flag['Price']))
            # Заполним оставшиеся флаги
            for customFlag in acc.SD.data['DBUIData']['customFlags']['Item']:
                if customFlag['id'] not in acc.model.Flags:
                    notOwnedFlags.append(AccountManagementAPI.ttypes.Flag(flagPersistentId=customFlag['id'],
                                                              flagPrice=customFlag['Price']))

            # Заполним админские флаги
            for adminFlag in acc.SD.data['DBUIData']['adminFlags']['Item']:
                if adminFlag['id'] not in acc.model.Flags:
                    adminFlags.append(AccountManagementAPI.ttypes.Flag(flagPersistentId=adminFlag['id'],
                                                              flagPrice=adminFlag['Price']))
            resInfo = AccountManagementAPI.ttypes.RequestResult.Success
        else:
            err("GetAccountFlags error, get acc by login(%s) fail" % login)
            resInfo = AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        return AccountManagementAPI.ttypes.FlagResponse(result=resInfo, ownedFlags=ownedFlags,
                                                        notOwnedFlags=notOwnedFlags, adminFlags=adminFlags)

    def UnlockFlag(self, login, flagPersistentId, gmLogin, extra_comment=""):
        acc = self.handler.I.WS.getUserAcc(login)
        if acc:
            acc.model.write(acc.pending)
            # Проверим, есть ли у пользователя такой флаг
            if flagPersistentId in acc.model.Flags:
                return AccountManagementAPI.ttypes.RequestResult.Success
            customFlag = acc.SD.getCustomFlagById(flagPersistentId)
            if customFlag:
                acc.model.Flags.append(flagPersistentId)
                data = "Added flag %s" % flagPersistentId
                self.handler.I.STATS.addGMOperation(acc.auid, GMOperationType.FlagUnlock, gmLogin, data if not extra_comment else "{0} ({1})".format(data, extra_comment) )
                return AccountManagementAPI.ttypes.RequestResult.Success
            else:
                err("UnlockFlag error, custom flag (%s) not found" % flagPersistentId)
                return AccountManagementAPI.ttypes.RequestResult.FlagNotExist
        else:
            err("UnlockFlag error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist

    def LockFlag(self, login, flagPersistentId, gmLogin, extra_comment=""):
        acc = self.handler.I.WS.getUserAcc(login)
        if acc:
            acc.model.write(acc.pending)
            if flagPersistentId in acc.model.Flags:
                data = "Removed flag %s" % flagPersistentId
                self.handler.I.STATS.addGMOperation(acc.auid, GMOperationType.FlagLock, gmLogin, data if not extra_comment else "{0} ({1})".format(data, extra_comment)  )
                acc.model.Flags.remove(flagPersistentId)
                # Не забудем поменяться на дефолтный, если у игрока флаг был активным
                if acc.model.FlagInfo.PersistentId == flagPersistentId:
                    acc.model.FlagInfo.FlagType = FlagType.Default
                    acc.model.FlagInfo.PersistentId = acc.SD.getDefaultFlagName()
                return AccountManagementAPI.ttypes.RequestResult.Success
            # Не нашли нужного флага, давайте поругаемся
            err("LockFlag error, flag %s is not owned" % flagPersistentId)
            return AccountManagementAPI.ttypes.RequestResult.FlagInstNotExist
        else:
            err("LockFlag error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist

    def AddResources(self, auid, resourceType, amount):
        acc = self.handler.I.WS.getUserAccByAuid( auid )
        if acc:
            acc.model.write(acc.pending)
            if resourceType == "Resource1":
                if (acc.model.Resources.Resource1 + amount) > 0:
                    acc.model.Resources.Resource1 += amount
                    return AccountManagementAPI.ttypes.RequestResult.Success
            elif resourceType == "Resource2":
                if (acc.model.Resources.Resource2 + amount) > 0:
                    acc.model.Resources.Resource2 += amount
                    return AccountManagementAPI.ttypes.RequestResult.Success
            elif resourceType == "Resource3":
                if (acc.model.Resources.Resource3 + amount) > 0:
                    acc.model.Resources.Resource3 += amount
                    return AccountManagementAPI.ttypes.RequestResult.Success
            elif resourceType == "Silver":
                if (acc.model.Resources.Silver + amount) > 0:
                    acc.model.Resources.Silver += amount
                    return AccountManagementAPI.ttypes.RequestResult.Success
            elif resourceType == "Perl":
                if (acc.model.Resources.Perl + amount) > 0:
                    acc.model.Resources.Perl += amount
                    return AccountManagementAPI.ttypes.RequestResult.Success
        else:
            err("AddResources: No user with auid %s found!", auid)
            return RequestResult.AuidNotExist
        return AccountManagementAPI.ttypes.RequestResult.BadResult

    # --------------------------------------------------------------------
    # Administration messages

    def SendMessageToUser(self, login, auid, messageTitle, messageText, gmLogin, extra_comment=""):
        acc = self.handler.I.WS.getUserAcc(login)
        if acc:
            acc.model.write(acc.pending)
            adminMessage, adminMessage_uid = acc.model.newAdminMessage()
            adminMessage.MessageText = messageText
            adminMessage.SentTime = int(time.time())
            acc.model.AdminMessages.add(adminMessage)
            timestamp = int(time.time())
            if len(acc.model.AdminMessages) > acc.getConfig().ADMIN_MESSAGES_TO_STORE:
                _id = sorted(acc.model.AdminMessages.iteritems(), key=lambda x: x[1].SentTime)[0][0]
                info("SendMessageToUser: id = %r", _id)
                acc.model.AdminMessages.remove(_id)
            # Положим в таблицу, для истории
            info("SendMessageToUser : adding to SQL")
            self.I.SQL.addAdminMessage(login, adminMessage_uid, messageTitle, messageText, gmLogin, timestamp, self.onMessageAddedToSql)
            return AccountManagementAPI.ttypes.RequestResult.Success
        else:
            err("SendMessageToUser error, get acc by login(%s) fail" % login)
            return AccountManagementAPI.ttypes.RequestResult.LoginNotExist

    def onMessageAddedToSql(self, sql_reply):
        info("onMessageAddedToSql sql reply: %s" % ( sql_reply))
        try:
            reply = sql_reply["r"]
            assert(reply)
        except:
            catch()

    def messageActionCallbackFn(self, response):
        if not response.get("ok"):
            err("SendMessageToUser call to chat server failed: response %s" % response)

    # --------------------------------------------------------------------

    # --------------------------------------------------------------------
    # Friends
    # --------------------------------------------------------------------
    def GetAccountFriends(self, auid):
        accFriends = []
        result = AccountManagementAPI.ttypes.RequestResult.BadResult

        acc = self.handler.I.WS.getUserAccByAuid(auid)
        if acc:
            if acc.friendsdata:
                for friendId, friend in acc.friendsdata.myFriends.iteritems():
                    if friendId != auid:
                        accFriends.append(AccountManagementAPI.ttypes.FriendInfo(
                                          auid=friendId,
                                          nickname=utf8convert(friend.nickName),
                                          guildShortName=utf8convert(friend.guildshortname)))
                result = RequestResult.Success
        else:
            err("GetAccountFriends: No user with auid %s found!", auid)
            result = RequestResult.AuidNotExist
        return AccountManagementAPI.ttypes.FriendInfoResponse(result=result, friends=accFriends)

    def RemoveFriend(self, auid, friendAuid):
        result = getattr(self.handler, "result", None)
        if result is None:
            acc = self.handler.I.WS.getUserAccByAuid(auid)
            if acc:
                # if friendAuid in acc.model.Friends.Favorites: # PF-98199
                #    return RequestResult.CantRemoveFavouriteFriend
                self.auid = auid
                self.friendAuid = friendAuid
                if acc.db.guildAuid:
                    self.handler.I.GS.isGuildMember(acc, friendAuid, acc.db.guildAuid, self.onFriendChecked)
                else:
                    self.handler.I.PS.deleteFriend(self.auid, self.friendAuid, self.onRemoveFriend)
                raise AsyncThriftException("%d async RemoveFriend" % auid)
            else:
                err("RemoveFriend: No user with auid %s found!", auid)
                return RequestResult.AuidNotExist
        else:
            return result

    def onFriendChecked(self, response):
        debug("onFriendChecked response: %r", response)
        self.handler.result = RequestResult.BadResult
        if response and "is_member" in response:
            if response["is_member"]:
                self.handler.result = RequestResult.CantRemoveGuildMemberFromFriends
            else:
                self.handler.I.PS.deleteFriend(self.auid, self.friendAuid, self.onRemoveFriend)
                return
        self.handler.process()

    def onRemoveFriend(self, response):
        self.handler.result = RequestResult.BadResult
        if response and response.get("ok", 0):
            self.handler.result = RequestResult.Success
        self.handler.process()

    # ####################################################################
    # region Bans

    def GetBruteForceAccount(self, email):
        result = getattr(self.handler, "result", None)
        if result is None:
            _callback = functools.partial(self.onGetBruteForceAccount, email)
            self.handler.I.DATA.find_one(CC.BANNED_BY_BRUTEFORCE, CC.BANNED_BY_BRUTEFORCE, {'_id': md5(email)}, callback=_callback)
            raise AsyncThriftException("%s async GetBruteForceAccount" % email )
        else:

            debug(" GetBruteForceAccount %r RequestResult= %r",email, self.handler.result )
            if hasattr(self, 'BruteForceAccountResult'):
                return self.handler.result
            else:
                return AccountManagementAPI.ttypes.BruteForceAccountShortInfo(result=RequestResult.BadResult, email=email, count=0, ip="",banTime=0 )

    def onGetBruteForceAccount(self, email, reply):
        debug("onGetBruteForceAccount %r reply= %r",email, reply )
        if reply and reply.get("r"):
            bf_acc = reply.get("r")
            self.BruteForceAccountResult = 0
            self.handler.result = AccountManagementAPI.ttypes.BruteForceAccountShortInfo( banTime = bf_acc.get('ban_timeout', 0),
                                                                    email = email,
                                                                    count = bf_acc.get('count', 0),
                                                                    ip = bf_acc.get('remote_ip', ""),
                                                                    result = RequestResult.Success
                                                                    )
        elif reply and reply.get("r") is None:
            self.BruteForceAccountResult = 1
            self.handler.result = AccountManagementAPI.ttypes.BruteForceAccountShortInfo(result=RequestResult.EmailNotExist, email=email, count=0, ip="",banTime=0 )
        else:
            self.disjointSnResult = 2
            self.handler.result = AccountManagementAPI.ttypes.BruteForceAccountShortInfo(result=RequestResult.BadResult, email=email, count=0, ip="",banTime=0 )
        self.handler.process()

    def UnBanBruteForceAccount(self, email):
        self.handler.I.DATA.remove(CC.BANNED_BY_BRUTEFORCE, CC.BANNED_BY_BRUTEFORCE, {'_id': md5(email)})
        return AccountManagementAPI.ttypes.RequestResult.Success

    def GetBannedIp(self, limit, skip):
        result = getattr(self.handler, "result", None)
        if result is None:
            _callback = functools.partial(self.onGetBannedIp, limit, skip)
            #self.handler.I.DATA.find(CC.BANNED_BY_IP, CC.BANNED_BY_IP, {}, callback=_callback, params={"limit":limit, "skip": skip})
            self.handler.I.DATA.find(CC.BANNED_BY_IP, CC.BANNED_BY_IP, {}, callback=_callback)
            raise AsyncThriftException("async GetBannedIp")
        else:
            if hasattr(self, 'BannedIpsResult'):
                return self.handler.result
            else:
                return AccountManagementAPI.ttypes.BannedIpFullListInfo(result=RequestResult.BadResult, IpList=[], Count=0 )

    def onGetBannedIp(self, limit, skip, reply):
        debug("onGetBannedIp limit=%r, skip=%r,  reply=%r",limit, skip, reply )
        if reply and reply.get("r"):
            b_ips = reply.get("r")
            l = b_ips.count()
            IpList =[]
            self.BannedIpsResult = 0
            ip_ap = IpList.append
            BannedIpSI = AccountManagementAPI.ttypes.BannedIpShortInfo
            for ip in b_ips.limit(limit).skip(skip):
                ip_ap(BannedIpSI(BanTime=ip["timeout"], Accounts=ip["accounts"], Tryes=ip["try"], Ip=ip["_id"]))

            self.handler.result = AccountManagementAPI.ttypes.BannedIpFullListInfo(Count=l, IpList=IpList, result=RequestResult.Success)
        elif reply and reply.get("r") is None:
            self.BannedIpsResult = 1
            self.handler.result = AccountManagementAPI.ttypes.BannedIpFullListInfo(result=RequestResult.BadResult, IpList=[], Count=0 )
        else:
            self.BannedIpsResult = 2
            self.handler.result = AccountManagementAPI.ttypes.BannedIpFullListInfo(result=RequestResult.BadResult, IpList=[], Count=0 )
        self.handler.process()

    def UnBanIp(self, ip):
        self.handler.I.DATA.remove(CC.BANNED_BY_IP, CC.BANNED_BY_IP, {'_id': ip})
        return AccountManagementAPI.ttypes.RequestResult.Success

    # endregion
    # ####################################################################

    # ####################################################################
    # region Wipe

    def __accountShortInfoFromResponse(self, response):
        account_short_info = AccountManagementAPI.ttypes.AccountShortInfo(snid=str(response.get('snid', "")),
                                                                          snuid=str(response.get('snuid', "")),
                                                                          login=str(response.get('login', "")),
                                                                          email=str(response.get('email', "")),
                                                                          nickname=str(response.get('nickname', "")))
        return account_short_info

    def FindPlayerByNickname(self, nickname):
        info("WIPE!FindPlayerByNickname : %r" % nickname)

        result = getattr(self.handler, 'findPlayerByNicknameResult', None)
        if result:
            return result
        action_args = dict(nickname=nickname)
        action = FindPlayerByNicknameAction(action_args, self.__onFindPlayerByNickname, I=self.I)
        action.onStart()
        raise AsyncThriftException("async FindPlayerByNickname")

    def __onFindPlayerByNickname(self, response):
        info("WIPE!__onFindPlayerByNickname : %r" % response)

        if not response.get('ok'):
            self.handler.findPlayerByNicknameResult = \
                AccountManagementAPI.ttypes.NickSnidResponse(result=RequestResult.BadResult)
            self.handler.process()
            return
        if response.get('found'):
            request_result = RequestResult.Success
        else:
            request_result = RequestResult.NicknameNotExist
        found_account = self.__accountShortInfoFromResponse(response)
        self.handler.findPlayerByNicknameResult = \
            AccountManagementAPI.ttypes.NickSnidResponse(result=request_result, foundAccount=found_account)
        self.handler.process()

    def FindPlayerByEmail(self, email):
        info("WIPE!FindPlayerByEmail : %r" % email)

        result = getattr(self.handler, 'findPlayerByEmailResult', None)
        if result:
            return result
        action_args = dict(email=email)
        action = FindPlayerByEmailAction(action_args, self.__onFindPlayerByEmail, I=self.I)
        action.onStart()
        raise AsyncThriftException("async FindPlayerByEmail")

    def __onFindPlayerByEmail(self, response):
        info("WIPE!__onFindPlayerByEmail : %r" % response)

        if not response.get('ok'):
            self.handler.findPlayerByEmailResult = \
                AccountManagementAPI.ttypes.NickSnidResponse(result=RequestResult.BadResult)
            self.handler.process()
            return
        if response.get('found'):
            request_result = RequestResult.Success
        else:
            request_result = RequestResult.EmailNotExist
        found_account = self.__accountShortInfoFromResponse(response)
        self.handler.findPlayerByEmailResult = \
            AccountManagementAPI.ttypes.NickSnidResponse(result=request_result, foundAccount=found_account)
        self.handler.process()

    def PlayerChangeEmail(self, email, newEmail, newPass):
        info("WIPE!PlayerChangeEmail : %r" % [email, newEmail, newPass])

        result = getattr(self.handler, 'playerChangeEmailResult', None)
        if result:
            return result
        action_args = dict(email=email, newEmail=newEmail, newPass=newPass)
        action = ChangePlayerCredentialsAction(action_args, self.__onPlayerChangeEmail, I=self.I)
        action.onStart()
        raise AsyncThriftException("async PlayerChangeEmail")

    def __onPlayerChangeEmail(self, response):
        info("WIPE!__onPlayerChangeEmail : %r" % response)

        if not response.get('ok'):
            self.handler.playerChangeEmailResult = \
                AccountManagementAPI.ttypes.NickSnidResponse(result=RequestResult.BadResult)
            self.handler.process()
            return
        action_result = response.get('action_result', ChangePlayerCredentialsAction.RESULT_FAIL)
        found_account = None
        if action_result == ChangePlayerCredentialsAction.RESULT_SUCCESS:
            request_result = RequestResult.Success
            found_account = self.__accountShortInfoFromResponse(response)
        elif action_result == ChangePlayerCredentialsAction.RESULT_WRONG_EMAIL:
            request_result = RequestResult.EmailNotExist
        elif action_result == ChangePlayerCredentialsAction.RESULT_WRONG_NEW_EMAIL:
            request_result = RequestResult.EmailAlreadyActivated
        elif action_result == ChangePlayerCredentialsAction.RESULT_WRONG_NEW_PASS:
            request_result = RequestResult.LoginNotExist
        else:
            request_result = RequestResult.BadResult
        self.handler.playerChangeEmailResult = \
            AccountManagementAPI.ttypes.NickSnidResponse(result=request_result, foundAccount=found_account)
        self.handler.process()

    def PlayerRemoveNickname(self, email, nickname):
        info("WIPE!PlayerRemoveNickname : %r" % [email, nickname])

        result = getattr(self.handler, 'playerRemoveNicknameResult', None)
        if result:
            return result
        action_args = dict(email=email, nickname=nickname)
        action = WipePlayerProgressionAction(action_args, self.__onPlayerRemoveNickname, I=self.I)
        action.onStart()
        raise AsyncThriftException("async PlayerRemoveNickname")

    def __onPlayerRemoveNickname(self, response):
        info("WIPE!__onPlayerRemoveNickname : %r" % response)

        if not response.get('ok'):
            self.handler.playerRemoveNicknameResult = \
                AccountManagementAPI.ttypes.NickSnidResponse(result=RequestResult.BadResult)
            self.handler.process()
            return
        action_result = response.get('action_result', WipePlayerProgressionAction.RESULT_FAIL)
        found_account = None
        if action_result == WipePlayerProgressionAction.RESULT_SUCCESS:
            request_result = RequestResult.Success
            found_account = self.__accountShortInfoFromResponse(response)
        elif action_result == WipePlayerProgressionAction.RESULT_WRONG_PAIR:
            request_result = RequestResult.NoUsersWithThatNickname
        else:
            request_result = RequestResult.BadResult
        self.handler.playerRemoveNicknameResult = \
            AccountManagementAPI.ttypes.NickSnidResponse(result=request_result, foundAccount=found_account)
        self.handler.process()

    # endregion
    # ####################################################################

def _GetLocaleInfo(acc):
    return LocaleInfoResponse(RequestResult.Success,
        LocaleInfo((acc.db.locale or '').encode("latin1"),(acc.db.muid or '').encode("latin1")))

