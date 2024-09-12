# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *
import imp
from binascii import crc32   # zlib version is not cross-platform
import zlib, bz2 ## TEST
import gc

from config.MultiConfig import MultiConfig
from iwebserver import IWebServer
from modeldata.MultiStaticData import MultiStaticData
from modeldata.ModelData import ModelData # чисто для проверки типа
from iserialmodel import ISyncSerialModel
from ifactory import IfaceFactory
from modeldata.datamanager import PwNewModelManager

from tornado.options import define, options
from handlers import PWSOC_VERSION
from geo_cfg import DEFAULT_GEO_LOCATION, GEO_LOCATIONS
from MM import ESex, ROLL_DB_VERSION
from party_const import FRACTION

""" 
    Здесь мы не занимаемся вопросами содержимого записи user persistent data (ModelData и т.п.), для этого есть SMODEL;
    мы задаем только общую структуру и формат данных, на самом верхнем уровне (acc, cached_data, persistent_data).
"""

TAIL_MARKER = "::"
TAIL_MARKER_LEN = len(TAIL_MARKER)
TAIL_MARKER_RECORD_LEN = 8 + TAIL_MARKER_LEN

## --------------------------------------------------------------------------------------
## --------------------------------------------------------------------------------------

class IPersistentDataManager(object):
    
    # на всякий случай получим интерфейсы
    def __init__(self, ifaceDict):
        self.I = ifaceDict
    
    # задаем правильную структуру данных на пользовательском аккаунте (в качестве такового может выступать любой объект, по умолчанию это наш helpers.ClassDict)
    def createAccountData(self, acc):
        pass    
    
    # парсим строку из persistent, прописываем необходимые поля на аккаунт; дальше, по идее, должен следовать дальнейший парсинг/восстановление acc.model
    def loadAccountData(self, acc, persistent_data_string):
        pass
        
        
## --------------------------------------------------------------------------------------
## --------------------------------------------------------------------------------------
    
class PersistentDataManager( IPersistentDataManager ):
    
    # на всякий случай получим интерфейсы
    def __init__( self, ifaceDict ):
        self.I = ifaceDict
        self.accs = {}
    
    # ---------------------------------------------------------------------------------
    # задаем правильную структуру данных на пользовательском аккаунте (в качестве такового может выступать любой объект, по умолчанию это наш helpers.ClassDict)
    def createAccountData(self, acc):
        # устанавливаем нормальную структуру данных аккаунта: 
        # три словаря 
        #  1) acc.data для cached-данных (memcache-уровень)
        #  2) acc.db для persistent-данных (database-уровень)
        #  3) acc.model для клиентской Model Data (у клиентщиков всё убого: и temp, и persistent, и static данные -- все вперемешку в одной куче. поэтому увы, всё сохраняем в database)
        acc.data = ClassDict()
        acc.db = ClassDict()
        
        # все-таки нужно создать пустой pending-writer 
        self.I.MD.resetPendingChanges(acc)
        
        
    # ---------------------------------------------------------------------------------
    # парсим строку из persistent, прописываем необходимые поля на аккаунт; дальше, по идее, должен следовать дальнейший парсинг/восстановление acc.model
    @staticmethod
    def loadSimpleData(acc, persistent_str):
        # ----
        # TODO: предусмотреть gzip-паковку?..
        # ----
        # парсим данные
        persistent_dict = {}
        
        if persistent_str:
            # строка может быть зазипована
            str_head = persistent_str[:4]
            if str_head in ["ZLIB", "BZIP"]:
                t0 = time.clock()
                ##info( "type(persistent_str): %s, persistent_str: %r" % (type(persistent_str), persistent_str) )
                encoded_persistent = persistent_str[4:].encode('latin1')
                ##info( "type(encoded): %s, encoded: %r" % (type(encoded_persistent), encoded_persistent) )
                
                if persistent_str[:4] == "ZLIB":
                    persistent_str = zlib.decompress( encoded_persistent )
                elif persistent_str[:4] == "BZIP":
                    persistent_str = bz2.decompress( encoded_persistent )
                    
                del encoded_persistent  # сразу освободить строчный буфер
                
                t1 = time.clock()
                info( "persistent archive (%s) decompress time: %.3f, decompressed len: %s" % (str_head, t1-t0, len(persistent_str)) )
        
            persistent_dict = json_loads( persistent_str )
            
            del persistent_str # сразу освободить строчный буфер
            
        # устанавливаем нормальную структуру данных аккаунта: 
        # три словаря 
        #  1) acc.data для cached-данных (memcache-уровень)
        #  2) acc.db для persistent-данных (database-уровень)
        #  3) acc.model для клиентской Model Data (у клиентщиков и temp, и persistent, и static данные -- все вперемешку в одной куче. поэтому увы, всё вместе сохраняем в database)
        data_dict = persistent_dict.pop("data", {})
        db_dict = persistent_dict.pop("db", {})
        model_source = db_dict.pop("model", "")
        
        acc.data = createClassDict( data_dict )
        acc.db = createClassDict( db_dict.pop("db", {}) )
        acc.db.load_auid = acc.db.auid
        if model_source:
            if isinstance( model_source, dict ):
                acc.model = model_source # модель пока кладем в виде сырого, нераспарсенного словаря
            else:
                acc.model = json_loads( model_source ) # модель пока кладем в виде сырого, нераспарсенного словаря

    # ---------------------------------------------------------------------------------
    # этот вариант создает новый пустой аккаунт, и грузит туда "простые данные"
    @staticmethod
    def newSimpleDataAcc( persistent_data_string, uid=0, sex=ESex.MALE ):
        acc = ClassDict( uid=uid, sex=sex )
        PersistentDataManager.loadSimpleData( acc, persistent_data_string )
        return acc
        
    @staticmethod
    def makeSaveDict(acc):
        if isinstance( acc.model, ModelData ):
            store_model = acc.model.generateJsonDict()
        else:
            store_model = acc.model
                
        save_dict = ClassDict(data=acc.data, db=ClassDict( db=acc.db, model=store_model ))
        return save_dict
                
    @staticmethod
    def saveReadyDict(save_dict):
        save_json = json_dumps( save_dict )
        # ----
        #TODO: предусмотреть gzip?..
        # ----
        return save_json
        
    @staticmethod
    def saveData(acc, zip=True):
        t0 = time.clock() # ----------------------
        save_dict = PersistentDataManager.makeSaveDict( acc )
        t1 = time.clock() # ----------------------
        json_data = PersistentDataManager.saveReadyDict( save_dict )
        t2 = time.clock() # ----------------------
        
        # и упакуем данные gzip-ом
        #json_data = "BZIP" + bz2.compress( json_data, 3 )
        if zip:
            zlib_data = "ZLIB" + zlib.compress( json_data, 3 )
            t3 = time.clock() # ----------------------
            json_data = unicode(zlib_data, "latin1")
            #json_data = "ZLIB" + encode(zlib.compress( json_data, 3 ), "utf8")
            t4 = time.clock()
            ##info( "compressed zlib_data=%r, type %s" % (zlib_data, type(zlib_data)) )
            ##info( "encoded json_data=%r, type %s" % (json_data, type(json_data)) )
            debug( "save time: %.3f, json time: %.3f, zlib compression time: %.3f, encode time: %.3f" % (t1-t0, t2-t1, t3-t2, t4-t3) )
        else:
            debug( "save time: %.3f, json time: %.3f" % (t1-t0, t2-t1) )
        
        ## raise "xxx"
        
        return json_data

    # ---------------------------------------------------------------------------------
    # helper: если соц.данные (auid, snid, snuid, registration_date) есть на аккаунте - берем оттуда; если на аккаунте нету - берем из персистент
    def setSocialValue(self, acc, name, default=None):
        value = getattr(acc, name, default) or getattr(acc.db, name, default) or default # None вместо "" нас совсем не устраивает
        setattr(acc, name, value)
        setattr(acc.db, name, value)
        
    # ---------------------------------------------------------------------------------
    # парсим строку из persistent, прописываем необходимые поля на аккаунт, полностью разбираем ModelData (до состояния иерарахии объектов)
    # acc может быть любым объектом (обычно используется ClassDict)
    def loadAccountData(self, acc, persistent_data_string):
        t0 = time.clock()
        
        PersistentDataManager.loadSimpleData( acc, persistent_data_string )
        
        acc.fraction = acc.db.fraction or FRACTION.NONE
        acc.db.original_uid = acc.db.original_uid or acc.uid
        acc.photoUrl = acc.photoUrl or ""
        acc.db.sn_nick = acc.sn_nick
        
        # если соц.данные есть на аккаунте - берем оттуда; если на аккаунте нету - берем из персистент
        info( "loadAccountData (uid=%s): acc.auid=%s" % (acc.uid, acc.auid) )
        self.setSocialValue(acc, "auid", 0)
        self.setSocialValue(acc, "snid", "")
        self.setSocialValue(acc, "snuid", "")
        self.setSocialValue(acc, "registration_date", 0)
        self.setSocialValue(acc, "photoUrl", "")
        
        if acc.db.nick:
            acc.nick = utf8convert( acc.db.nick )
        elif (not acc.guest):
            acc.nick = ""
        if acc.db.sn_nick:
            acc.sn_nick = acc.sn_nick or utf8convert( acc.db.sn_nick )

        if acc.geo_info:
            acc.db.gcountry = acc.geo_info.get('country_code', '')
            acc.db.gregion = latin2utf(acc.geo_info.get('region_name', ''))
            acc.db.gcity = latin2utf(acc.geo_info.get('city', ''))
        else:
            err("loadAccountData: empty acc.geo_info!")

        self.fixLoadedData(acc) # приводим в порядок прочие загруженные данные (на случай нехватки в persistent data полей и т.п.)

        t1 = time.clock()
        
        if acc.model:
            # лочим аккаунт (на время асинхронной загрузки ModelData запрещаем прочие запросы)
            debug("loadAccountData acc.model")
            acc.locked = 1 
            self.accs[ acc.uid ] = acc
            self.I.SMODEL.loadSerialModel( acc.uid, acc.model, acc.fraction, acc.sex, ClassDict(acc.db), acc.sn_count, \
                acc.Config, acc.SD, acc.userlocale, acc.country_code, self.onUserDataLoadedOk )
        else:
            # ладно, emptyModel можно и синхронно сделать
            self.I.MD.emptyModel(acc, self.I, PWSOC_VERSION)
            info( "onUserData: no persistent data (uid=%s), setting loaded=1, locked=0" % acc.uid )
            acc.loaded = 1
            acc.locked = 0
            
            # поскольку загрузки persistent данных не будет, сразу выполняем пост-действия
            ## self.I.WS.onUserLoadFinished( acc ) # оттуда же делается STATS.addLogin
            self.doOnLoadedCallbacks( acc ) # onUserLoadFinished всегда вешается в OnLoadedCallbacks
        
        t2 = time.clock()
        
        info( "onUserData timing: json&fix %.3f, loadSerial %.3f" % (t1-t0, t2-t1) )

        
    # ------------------------------------------
    # OVERRIDE: приводим в порядок загруженные данные (на случай нехватки в persistent data полей и т.п.)
    def fixLoadedData( self, acc ):       
        acc.db.pop("rating", None) # этот рейтинг убрали, теперь на каждом герое отдельный
        acc.db.pop("silver", None)
        acc.db.pop("uid", None) # заменил на original_uid
        acc.db.pop("reliability", None) 
        acc.db.pop("resourceX", None)
        acc.db.pop("resourceY", None)
    
        acc.db.seed = acc.db.seed or random.randint(1, 1000000000)
        acc.db.win_lose_hist = acc.db.win_lose_hist or ''
        
        # новый формат session_roll: словарь вместо "запеченной json-строчки" (если у нас строчка -- распаковываем)
        acc.db.session_roll = acc.db.session_roll or {}
        if isinstance(acc.db.session_roll, basestring):
            roll_dict = {}
            try:
                roll_dict = json_loads( acc.db.session_roll )
            except:
                catch()
            acc.db.session_roll = roll_dict
            info( "converted session_roll table (auid=%s): %s" % (acc.auid, acc.db.session_roll) )
        
        # все ролл-словари с несоответствующей ROLL_DB_VERSION нужно выкинуть
        roll_keys = acc.db.session_roll.keys()[:]
        for key in roll_keys:
            table = acc.db.session_roll[key]
            if table and isinstance(table, dict) and (table.get("db_version", 0) != ROLL_DB_VERSION):
                acc.db.session_roll.pop(key)
                info( "removing stale roll subtable (auid=%s): key=%s, table=%s (ROLL_DB_VERSION=%s)" % (acc.auid, key, table, ROLL_DB_VERSION) )

        acc.db.muted = acc.db.muted or 0
        acc.db.mutetime = acc.db.mutetime or 0
        acc.db.banned = acc.db.banned or False
        acc.db.autoban = acc.db.autoban or False
        acc.db.bantime = acc.db.bantime or 0
        acc.db.banreason = acc.db.banreason or ""
        if acc.db.banned:
            if acc.db.bantime != 0:
                if time.time() > acc.db.bantime:
                    acc.db.banned = False
                    acc.db.bantime = 0
                    acc.db.banreason = ""
                    acc.db.autoban = False
    
        # sex кэшируется (сохраняется в persistent только один раз, дальше берется из persistent -- т.к. в facebook слишком легко сменить пол)
        acc.db.sex = acc.db.sex or acc.sex
        acc.sex = acc.db.sex
        
        acc.db.fractionChanged = acc.db.fractionChanged or 0
        acc.db.nickChanged = acc.db.nickChanged or 0
        
        # isDeveloper
        if not hasattr(acc.db, "IsDeveloper"):
            acc.db.IsDeveloper = False
            
        acc.geolocation = acc.db.geolocation or acc.geolocation or acc.db.last_geolocation or DEFAULT_GEO_LOCATION
        if acc.geolocation not in GEO_LOCATIONS: # набор разрешенных локаций в конфиге может поменяться после выбора локации юзером
            acc.geolocation = DEFAULT_GEO_LOCATION 
        acc.db.last_geolocation = acc.geolocation    
        
        acc.db.snid = acc.snid
        acc.db.snuid = acc.snuid
        acc.db.auid = acc.auid
        acc.db.registration_date = acc.registration_date
        acc.db.photoUrl = acc.photoUrl or ""
        if acc.locale:
            acc.db.locale = acc.locale
        acc.db.original_snid = acc.original_snid
        if acc.muid and not acc.db.muid and (acc.muid != 'invalid'):
            acc.db.muid = acc.muid

        if acc.ruid and not acc.db.ruid and (acc.ruid != 'invalid'):
            acc.db.ruid = acc.ruid

        acc.db.guildAuid = acc.db.guildAuid or 0

        acc.db.oldAuid = acc.db.oldAuid or 0

        acc.db.dlcs = acc.db.dlcs or []

        if acc.db.nick:
            acc.nick = acc.db.nick.encode( 'utf8' )
        acc.db.CountOfAllFriends = 0
        acc.db.CurrBeginOfFriendsPage = 0

        try:
            acc.db.currentGuildWarEvent = long(acc.db.currentGuildWarEvent)
        except:
            warn("wrong currentGuildWarEvent index = %s, reset it to 0", acc.db.currentGuildWarEvent)
            acc.db.currentGuildWarEvent = 0

    # ------------------------------------------------------------------------------------------------------------------------------
    # скрипты могли внести изменения в reply_acc.db; эти изменения нужно аккуратно перенести в настоящий acc 
    # (не поломав возможных изменений в настоящем acc)
    def applyModelDataDbChanges(self, acc, reply_acc):
        if reply_acc.db.goldEventDone:
            acc.db.goldEventDone = reply_acc.db.goldEventDone
        if reply_acc.db.eventsApplied:
            acc.db.eventsApplied = reply_acc.db.eventsApplied[:]
        if reply_acc.db.NivalLastBonusTime:
            acc.db.NivalLastBonusTime = reply_acc.db.NivalLastBonusTime
        if reply_acc.db.IsSpectator:
            acc.db.IsSpectator = reply_acc.db.IsSpectator
        acc.db.guildAuid = reply_acc.db.guildAuid
        if reply_acc.db.isRegularMMAllowed:
            acc.db.isRegularMMAllowed = reply_acc.db.isRegularMMAllowed
        if reply_acc.db.locale:
            acc.db.locale = reply_acc.db.locale
        if reply_acc.db.muid and not acc.db.muid:
            acc.db.muid = reply_acc.db.muid
        if reply_acc.db.ruid and not acc.db.ruid:
            acc.db.ruid = reply_acc.db.ruid
        if reply_acc.db.castle_roll and isinstance(reply_acc.db.castle_roll, dict):
            acc.db.castle_roll = {}
            for key in reply_acc.db.castle_roll.keys():
                acc.db.castle_roll[key] = reply_acc.db.castle_roll[key]
        acc.db.oldAuid = reply_acc.db.oldAuid

        acc.db.currentGuildWarEvent = 0
        if reply_acc.db.currentGuildWarEvent:
            acc.db.currentGuildWarEvent = reply_acc.db.currentGuildWarEvent

        #info("applyModelDataDbChanges: %s" % acc.db)

    def doOnLoadedCallbacks(self, acc):
        if acc.on_loaded_callbacks:
            for callback in acc.on_loaded_callbacks:
                try:
                    callback( acc )
                except:
                    catch()
                    warn( "failed calling on_loaded_callbacks[] callback=%s for acc=%s" % ( str(callback), str(acc) ) )
        acc.on_loaded_callbacks = []

    # ------------------------------------------
    def onUserDataLoadedOk(self, serial_reply):
        try:
            uid = serial_reply.get("p")
            reply_acc = serial_reply.get("r")
            acc = None
            if uid in self.accs:
                acc = self.accs.pop( uid )


            debug("onUserDataLoadedOk  uid=%r acc=%r", uid, acc)
            if acc:
                if reply_acc:
                    if reply_acc.model and (not reply_acc.failed):
                        if str(acc.auid) != str(acc.db.load_auid):
                            warn("Inconsistent auid and load_auid (auid=%s load_auid=%s)", acc.auid, acc.db.load_auid)

                        acc.model = reply_acc.model
                        # commented as attempt to fix PF-81538
                        # acc.friendsdata = reply_acc.friendsdata
                        acc.partydata = reply_acc.partydata
                        acc.guilddata = reply_acc.guilddata
                        acc.siegedata = reply_acc.siegedata
                        self.applyModelDataDbChanges( acc, reply_acc )
                        acc.loaded = 1
                        
                        self.I.WS.dumpAccount(acc, "onDataLoadedOk")

                        info( "persistent user[%d] db: %s", acc.uid, str(acc.db) )
                        
                        self.doOnLoadedCallbacks( acc )
                        self.I.WS.updateUserLeagueStat(acc)
                        self.I.WS.updateGameDataToPersonServer( acc )
                    
                    else:
                        acc.failed = 1
                       
                else:
                    warn( "bad onUserDataLoadedOk reply_acc (uid=%s)" % uid )
                
                # отпускаем аккаунт; с загрузкой разобрались, можно исполнять прочие запросы
                acc.locked = 0 
                
            else:
                warn( "bad onUserDataLoadedOk acc (uid=%s)" % uid )
        
        except:
            catch()
            warn( "bad onUserDataLoadedOk reply: %s" % str(serial_reply) )
            
            
## --------------------------------------------------------------------------------------
## --------------------------------------------------------------------------------------

def createStandalonePersistentInterface( iDict, xdb_path, modeldata_path ):
    """ для случаев, когда у нас нет рабочего кластера и особо некого оповещать, делаем dummy self.I, адекватно реагирующий на вызовы из PersistentDataManager """
    iDict.Config = MultiConfig()
    iDict.MSD = MultiStaticData( xdb_path + "/ExportedSocialData.xml", iDict.Config.getMainConfig() )
    iDict.SD = iDict.SD or iDict.MSD.mainStaticData
    iDict.Config.fillStaticDataDependendValues(iDict.MSD)
    iDict.SMODEL = ISyncSerialModel( iDict, PWSOC_VERSION )
    iDict.MD = PwNewModelManager( ifaceDict=iDict, load_events=False )
    iDict.WS = IWebServer()
    iDict.PDM = PersistentDataManager( iDict )
    iDict.STATS = IfaceFactory.makeIStatsInterface( "none", "", iDict ) # пустая болванка
    iDict.BILL = IfaceFactory.makeBillingInterface( "dummy", iDict )

