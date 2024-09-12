# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *
import signal
import gc
import functools

import tornado.options
from tornado.options import define, options
from tornado.log import LogFormatter

from base.http_dumb import httpClientRequest

import cfg
import coord_cfg

import handlers

from ext_pw.sexchange import DefaultMailAction

import tornado_patch

# несуществующий "якобы сервер" для тестов
# несуществующий "якобы сервер" для тестов
DUMMY_TEST_WS_ID = -1
DUMMY_TEST_WS_NAME = "test"

# несуществующий "якобы peer-сервер" для заглушек
DUMMY_PEER_WS_ID = -2
DUMMY_PEER_WS_NAME = "dummy"

# mock matchmaker
DUMMY_MM_ID = -3
DUMMY_MM_NAME = "mmm"

# mock social aggregator
DUMMY_SOCAGG_ID = -4
DUMMY_SOCAGG_NAME = "msa"

# social cluster coordinator
COORDINATOR_WS_ID = -5
COORDINATOR_WS_NAME = "coord"

# thrift agent
THRIFT_AGENT_ID = -6
THRIFT_AGENT_NAME = "thrift"

# person server
PERSON_SERVER_ID = -7
PERSON_SERVER_NAME = "pers"

# statistic agent
STATISTIC_SERVER_ID = -8
STATISTIC_SERVER_NAME = "stats"

# pw connect
PWCONNECT_SERVER_ID = -9
PWCONNECT_SERVER_NAME = "pwc"

# social exchange coordinator
XCOORDINATOR_WS_ID = -10
XCOORDINATOR_WS_NAME = "xcoord"

# guild server
GUILD_SERVER_ID = -11
GUILD_SERVER_NAME = "guild"

MIRROR_DAEMON_ID = -12
MIRROR_DAEMON_NAME = "mirror"

SIEGE_SERVER_ID = -13
SIEGE_SERVER_NAME = "siege"

##---------------------------------------------------------------------------------------------------

WS_MAX_MC_THREADS = 2
WS_MAX_SERIAL_THREADS = 1

WS_MAX_TICK_TIME = 0.1 # позволяем проводить не более чем столько времени в серверном тике (на "сохранении и выкидывании expired аккаунтов")

##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class IWebServer( object ):
    """ Заглушка, умеет выдавать GUID-ы и в целом притворяться WS-ом. """
    def __init__(self, test_mode=False, **kwargs):
        # inc-словарик, по которому будем выдавать GUID-ы
        #info( "IWS init" )
        self.guids = IncDict()
        self.TEST_MODE = test_mode
        self.operatorEvents = {"activeEvents": {}, "pendingEvents": {}, "toRevert": {}, "finishedEvents": {}, "disabledEvents": {}}
        
    def reset(self):
        self.guids = IncDict()
        
    # --------------- выдача GUID-ов -----------------
    #  основываемся на том, что 
    #    1) координатор всегда выдает нам глобально уникальный server_id
    #    2) все операции WebServer синхронны (выполняются из единственного IOLoop), и не требуют локов
    def nextUid(self, key):
        return self.guids.inc(key)
    
    # пока считаем, что 2B уникальных server_id нам хватит на обозримое будущее (даже если выдавать по 1000 новых sid каждую минуту, это ~500М server_id в год)
    def nextInt64GUID(self, key):
        uid = self.nextUid(key)
        guid = (long(options.server_id) << 32) | long(uid)
        ## guid = ( (int(options.server_id) << 20) | int(uid & 0xFFFFF) );
        return guid
        
    def nextStringGUID(self, key):
        uid = self.nextUid(key)
        return "%d_%d" % (options.server_id, uid)

    def nextNamedGUID(self, key):
        uid = self.nextUid(key)
        return "%s_%d_%d" % (key, options.server_id, uid)
        
    def nextNamedGUIDTuple(self, key):
        uid = self.nextUid(key)
        return "%s_%d_%d" % (key, options.server_id, uid), options.server_id, uid
        
    def repackGUID64to32(self, guid):
        # приводим guid к виду ( (int(options.server_id) << 20) | int(uid & 0xFFFFF) );
        #  при этом разрешается всего 1К разных server_id, а бит 0x40000000 (признак автогенеренного pvx-логина) гарантированно будет пустым
        #  каждый WS может выдать 1М таких 32-битных uid-ов
        return ((guid & 0x3FF00000000) >> 12) | (guid & 0xFFFFF)
        
    def repackGUID64to20by12(self, guid):
        # приводим guid к виду ( (int(options.server_id) << 12) | int(uid & 0xFFF) );
        #  при этом можно выдать всего 1К разных auid на данном WS
        return ((guid & 0x3FF00000000) >> 12) | (guid & 0xFFFFF)
        
    # -----------------------------------------------
    # ------------- various CALLBACKS ---------------
    
    def onUserLoginCas(self, mc_reply):
        pass
    def onUserDataCas(self, mc_reply):
        pass
    def onUserData(self, acc, data_json):
        pass
    def onUserCachedData(self, data_reply):
        pass
    def onUserPersistentData(self, data_reply):
        pass
        
    # -----------------------------------------------
    # ------------- OPERATIONS ---------------
    def resetUserSessions(self, acc):
        pass
    def instrumentAction(self, action, exec_time):
        pass
    def subscribeAccToPersonServer(self, acc, fame):
        pass
    def subscribeAccToGuildServer(self, acc):
        pass
    def onUserDataLoadedOk(self, serial_reply):
        pass
    def registerAuid(self, auid, uid):
        pass
    def saveUserData(self, acc):
        pass
        
    #-------------------------------------------------------------------------------------
    # OVERRIDE: приводим версию Model Data, отсылаемую клиенту, в ожидаемый клиентом вид 
    # (возможно, фиктивно добавляем к model change какие-то данные, на сервере хранящиеся отдельно; или убираем служебные серверные данные, которые клиент увидеть не должен)
    def modelFullUpdateFix(self, action_handler):
        pass

    def dumpAccount(self, acc, title_string):
        pass
        #~ copy_acc = ClassDict( acc ) # чисто для дампа acc
        #~ copy_acc.model = None
        #~ copy_acc.data = None
        #~ copy_acc.pending = None
        #~ copy_acc.friendsdata = None
        #~ copy_acc.on_loaded_callbacks = []
        #~ warn( "%s: acc %s" % (title_string, pretty(copy_acc)) )
        
    def refreshLoginToken(self, auid):
        pass
        
    def updateGameDataToPersonServer(self, acc, hero=None):
        pass

    def updateUserLeagueStat(self, acc):
        pass

    def updatePartyDodge(self, acc):
        pass

    def setLoginNick(self, auid, nickname_utf8):
        pass

    def setSnBonusCount(self, auid, sn_count, sn_prev_count, new_networks):
        pass
        
    def addForgeRoll(self, *args, **kwargs):
        pass

    def updateKeepaliveState(self, *args, **kwargs):
        pass

    def addDebugTimings(self, *args, **kwargs):
        pass
        
    def dumpDebugTimings(self):
        pass

    def getUserAccByAuid(self, auid):
        pass

    def tryApplyDLCs( self, dlcs, acc, I ):
        return acc.model.tryApplyDLCs( dlcs, acc, I )

    def tryApplyDLCsForMuid( self, muid, acc, I ):
        return acc.model.tryApplyDLCsForMuid( muid, acc, I )

    def checkDynamicQuests(self, acc):
        pass

    def updateGuildWarEvent(self, acc):
        pass

    def getGuildWarEventId(self, *args, **kwargs):
        pass

    def getGuildWarEventDataChanges(self, *args, **kwargs):
        pass

    def updateGuildWarEventDataFromJson(self, *args, **kwargs):
        pass

    def addNewGuildWarEvent(self, *args, ** kwargs):
        pass

    def canParticipateInGuildWarEvent(self, *args, ** kwargs):
        pass

    def updateTradeEventExperience(self, *args, **kwargs):
        if 'callback' not in kwargs:
            return
        kwargs['callback'](dict())

    def getTradeEventPlace(self, *args, **kwargs):
        if 'callback' not in kwargs:
            return
        kwargs['callback'](dict(r=[dict(place=1, experience=210)]))

    def updateSeasonEventProgress(self, *args, **kwargs):
        if 'callback' not in kwargs:
            return
        kwargs['callback'](dict())

    def getSeasonEventPlace(self, *args, **kwargs):
        if 'callback' not in kwargs:
            return
        kwargs['callback'](dict(r=[dict(place=1, experience=210)]))

##---------------------------------------------------------------------------------------------------

class IServerStatistic:
    def getServers(self):
        return {}

##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class ICSVActionTimingWriter:
    server_type_name = "ws"
    is_active = False
    """ умеем писать тайминги разных actions в CSV-файл """

    def createActionsCSV(self, stype, sname, sid, test_mode=False):
        self.instrActions = IncDict() # здесь будем мониторить времена исполнения action за последнюю минуту
        self.instrActionsHistory = IncDict() # а здесь храним историю (средние значения за все время работы текущего WS)
        self.is_active = True
        if not test_mode:
            curDir = os.path.dirname( os.path.realpath(__file__) )
            TIMING_FILENAME = curDir + "/logs/%s.timing.%s.%s.csv" % (stype, sname, sid)
            success("creating timing file %r" % TIMING_FILENAME)
            self.timing_file = open( TIMING_FILENAME, "wt" )
        else:
            self.timing_file = None
        
    def closeActionsCSV(self):
        self.is_active = False
        if self.timing_file:
            self.timing_file.close()
        
    def printActionsCSV(self, nametag, action_dict ):
        if not self.is_active:
            warn( "Trying to write action timings when writer is closed. Skipping." )
            return
        if self.timing_file:
            if action_dict:
                self.timing_file.write("\n<%s.%s> [%s] %s\nName;AvgTime;Count;TotalTime;\n" % (options.server_name, options.server_id, time.ctime(), nametag) )
                # теперь то же самое, но в удобном табличном csv-формате
                for action in sorted( action_dict.keys() ):
                    if action.find(":") < 0:
                        # базовое имя action
                        total = action_dict.get( action )
                        count = action_dict.get( action + ":count" )
                        avg = action_dict.get( action + ":avg" )
                        self.timing_file.write("%s;%5.5f;%d;%5.5f;\n" % (action, avg, count, total) )
                self.timing_file.flush()
                
    # ----------------------------------------------------------------------------------------------
    def instrumentAction(self, action, exec_time):
        action_count_tag = action + ":count"
        action_avg_tag = action + ":avg"
        total_time = self.instrActions.add( action, exec_time )
        total_count = self.instrActions.inc( action_count_tag )
        self.instrActions[action_avg_tag] = total_time / total_count


    def updateInstrumentedActions(self):
        if self.timing_file:
            for action,v in self.instrActions.iteritems():
                if action.find(":") < 0:
                    # базовое имя action
                    action_count_tag = action + ":count"
                    action_avg_tag = action + ":avg"
                    count = self.instrActions.pick(action_count_tag)
                    sum = self.instrActionsHistory.add( action, v )
                    count = self.instrActionsHistory.add( action_count_tag, count )
                    self.instrActionsHistory[action_avg_tag] = sum / count
                    
            #info( "TOTAL action times: %s" % pretty( times2msec( self.instrActionsHistory )) )

            self.printActionsCSV( "RECENT TIMES", self.instrActions )
            self.printActionsCSV( "TOTAL TIMES", self.instrActionsHistory )
            
            # после чего сбрасываем "текущую статистику"
            self.instrActions = IncDict()
                
##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class ISocialExchangeUser:
    """ умеем логиниться на почтовый сервис (готовый callback onSocialExchangeLogin), 
        принимать и мапить обработчики почтовых сообщений (handleSocialExchangeMessages) 
    """
       
    mailActions = {
        # тип почтового сообщения - строка не более 15 символов!
    } 
       
    def onSocialExchangeLogin(self, response, acc=None):
        if response and acc:
            info("onSocialExchangeLogin(auid=%s): response %s" % (acc.auid, response))
            if response.get("ok"):
                acc.sex_sid = response.get("sid", "")
                acc.sex_server = response.get("server", "")
                messages = response.get("messages")
                if messages:
                    purge_msg_ids = self.handleSocialExchangeMessages( messages, acc )
                    _callback = functools.partial(self.onPurgeLoginMessages, acc=acc )
                    self.I.SEX.purgeMail( acc.auid, acc.sex_sid, acc.sex_server, purge_msg_ids, _callback )
                    
                ## DEBUG
                ##self.requestForgeRoll( acc, roll_count=2 )
        else:
            warn("bad onSocialExchangeLogin: response %s, acc %s",response, acc)
    
    def onPurgeLoginMessages(self, response, acc=None):
        info("onPurgeLoginMessages (auid=%s) response: %s", acc.auid, response)
        
    def handleSocialExchangeMessages(self, messages, acc):
        info("handleSocialExchangeMessages(acc.auid=%s): messages %r", acc.auid, messages)
        purge_msg_ids = []
        if messages and acc:
            # нужно будет проверить, не получали ли уже такое сообщение
            now_ts = toint( time.time() )
            acc.db.sex_msgs = acc.db.sex_msgs or {}
            # и отсортировать сообщения по дате получения
            sorted_messages = []
            for _msg_id, msg_dict in messages.iteritems():
                msg_id = toint(_msg_id)
                str_msg_id = str(_msg_id) # при сериализации в JSON ключи все равно станут строчными, поэтому сразу заводим ключи msg_id в строчном виде
                prev_ts = acc.db.sex_msgs.get( str_msg_id ) # уже получали такой msg_id?
                if not prev_ts:
                    acc.db.sex_msgs[ str_msg_id ] = now_ts
                    dt_rcv = toint( msg_dict.get("dt_rcv") )
                    sorted_messages.append( (msg_id, dt_rcv, msg_dict) )
                else:
                    warn("handleSocialExchangeMessages: msg_id %s already received (prev_ts %s, now %s) for auid %s" % (msg_id, prev_ts, now_ts, acc.auid))
                    purge_msg_ids.append( msg_id )
                
            if sorted_messages:
                sorted_messages.sort( key=lambda item: item[1] )
                # скармливаем отсортированные:
                for msg_id, dt_rcv, msg_dict in sorted_messages:
                    ## info("receive exchange mail for auid=%s, msg_id=%s, dt_rcv=%s, msg=%s" % (acc.auid, msg_id, dt_rcv, msg_dict))
                    try:
                        # handle received message
                        ActionClass = self.mailActions.get(msg_dict.get("type", "default")) or DefaultMailAction
                        intaction = ActionClass( acc=acc, I=self.I, msg_id=msg_id, msg=msg_dict )
                        intaction.onStart() 
                        purge_msg_ids.append( msg_id )
                    except:
                        catch()

                # раз уж чего-то новое получили, давайте заодно повыкинем протухшие "ярлыки о получении сообщений"
                self.weedTimestamps(acc.db.sex_msgs, "sex_msgs", acc.auid, expire_period=24*60*60)
            
        else:
            warn("bad handleSocialExchangeMessages: messages %s, acc %s" % (messages, acc))
        return purge_msg_ids


    def weedTimestamps(self, messages, collection_name, auid, expire_period=24*60*60):
        if messages:
            now = toint( time.time() )
            purged = []
            for msg_id in messages.keys():
                ts = toint( messages.get(msg_id) )
                if ts + expire_period < now:
                    messages.pop( msg_id )
                    purged.append( msg_id )
            if purged:
                info("weedTimestamps(%s): purged ids %s for auid %s" % (collection_name, purged, auid))


##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class ITornadoServer( IWebServer ):
    """ generic веб-сервер (с периодическим таймером) """
    
    _Interfaces = dict( I=None ) # вытаскиваем себе только iDict
    
    SHUTDOWN_START = 1
    SHUTDOWN_BILLING = 2
    SHUTDOWN_USERS = 3    
    SHUTDOWN_SQL = 4
    SHUTDOWN_USERS_PROCESS = 5

    # ----------------------------------------------------------------------------------------------
    # для легкости unit-тестирования передаем интерфейсы типа memcache и sql будем передавать в конструктор
    def __init__(self, test_mode=False, **kwargs):
        log( "!" + str(self) + " interfaces:" + str(self._Interfaces) )

        # inherited (guids)
        IWebServer.__init__(self, test_mode=test_mode, **kwargs)

        self.gc_init()
        
        # мапим интерфейсы по списку _interfaces (если для одного из интерфейсов есть оверрайд в списке параметров, подставляем)
        for key, iBase in self._Interfaces.iteritems():
            if kwargs:
                # интерфейсы типа HTTP, MC, SQL можно оверрайдить через дополнительный словарик
                iface = kwargs.get(key)
                if iface is not None:
                    setattr(self, key, iface)
                    continue
                
            # по умолчанию -- берем default-ные заглушки
            setattr(self, key, iBase)
            
        self.wsShutdown = 0
        self.wsShutdownReloginUsers = 0
        self.tickCount = 0
        self.startTickTime = time.time()
        self.lastInstrumentedAction = int(time.time())
        self.shutdown_process = 0

        self.TICK_PERIOD = options.tick_period if options.tick_period else 1.0  # тикаем раз в столько секунд

        self.maintenanceMode = handlers.MAINTENANCE_NORMAL
        self.maintenanceTime = None
        
        self.peers = {} # [server_id] -> peer server info
        self.MAX_USERS = 10000 # по умолчанию позволяем не более N юзеров на сервер
        
        log( "startTickTime: %0.3f" % self.startTickTime );

        self.createActionsCSV( 'ws', options.server_name, options.server_id, test_mode=test_mode)
        
        self.ts_http_dump = 0

    # ----------------------------------------------------------------------------------------------
    # вызываем периодически из main tornado.IOLoop
    def _tick(self):
        loop = tornado.ioloop.IOLoop.instance()
        t0 = time.time()
        
        try: 
            try:
                ## сюда засунуть (ОВЕРРАЙД) полезную нагрузку
                self.tick()
            except:
                catch()
            
            # пытаемся отослать high-severity логи по http
            self.httpLogTick()
            self.httpStatusDump()
                
            t1 = time.time()
            if t1-t0 >= 0.001:
                log( "t:%0.3f tick %d" % (t1-t0, self.tickCount) )
        except:
            # есть подозрение, что при аномальной нагрузке на коробку могут зависать любые операции ввода-вывода, в т.ч. может повиснуть и вывод лога из catch();
            # но механизм маппинга новых тиков не должен ломаться вообще никогда (иначе WS перестанет делать логаут и собирать мусор, отчего выест память и сдохнет)
            pass
            
        # повторить через TICK_PERIOD:
        self.tickCount += self.TICK_PERIOD
        loop.add_timeout(self.startTickTime + self.tickCount, self._tick)
        
        if self.wsShutdown: 
            # мы в процессе shutdown
            if self.shutdownServerTick():
                if self.isDoneServer():
                    # активных юзеров не осталось; можно сваливать
                    loop.stop()

    def httpStatusDump(self):
        if self.I.HTTP:
            now = time.time()
            if self.ts_http_dump + 60.0 < now:
                info("httpStatusDump: %s active, %s queued, %s addrinfos cached" % ( len(self.I.HTTP.active), len(self.I.HTTP.queue), len(self.I.HTTP.addrinfo_mapping) ))
                self.ts_http_dump = now

    # ----------------------------------------------------------------------------------------------
    def gc_init(self):
        self.gc_timestamp = 0
        self.GC_PERIOD = getattr(coord_cfg, "COORDINATOR_DEFAULT_GC_PERIOD", 60.0) 

    def gcTick(self):
        gc.disable() # раз вызывают периодический механизм - можно отрубить постоянный автоматический gc питона
        now = time.time()
        if now > self.gc_timestamp + self.GC_PERIOD:
            # раз в N секунд: прогоняем полный garbage collection pass
            self.gc_timestamp = now
            gc.collect()
            after = time.time()
            info("gc counts: %s, garbage size: %d, gc time: %.3f", str(gc.get_count()), len(gc.garbage), after-now)
            
            # есть подозрение, что gc сбивает blocking alarm
            if hasattr(signal, "getitimer"):
                info("getitimer: %s" % str(signal.getitimer(signal.ITIMER_REAL)) )
                loop = tornado.ioloop.IOLoop.instance()
                tornado_patch.set_blocking_alarm(loop)
            
        else: # elif SEC % 1 == 0:
            info("gc counts: %s, garbage size: %d", gc.get_count(), len(gc.garbage))
                
    # ----------------------------------------------------------------------------------------------
    # закончен ли рабочий процесс (по wsShutdown сначала ждем выхода юзеров, завершения обработки incoming requests..)
    def isDoneServer(self):
        return True

    # ----------------------------------------------------------------------------------------------
    # выполняем действия по финализации состояния (доразбор очередей sql и т.п.);
    # когда совсем готовы умереть, возвращаем True
    def shutdownServerTick(self):
        return True
                        
    # ----------------------------------------------------------------------------------------------
    def fadeoutServer(self, **kwargs):
        bad_warn( "wsShutdown initiated, waiting for active users to finish requests.." )
        self.wsShutdown = self.SHUTDOWN_START
        if kwargs.get("reloginUsers"):
            self.wsShutdownReloginUsers = 1
        self.closeActionsCSV()

    def toggleMaintenance(self, mode, tm):
        self.maintenanceMode = mode
        self.maintenanceTime = tm

    # ----------------------------------------------------------------------------------------------
    def sig_handler(self, signum, frame):
        bad_warn( 'SIGNAL %d caught: initiating shutdown' % signum )
        self.fadeoutServer()

    # ----------------------------------------------------------------------------------------------
    # чтобы можно было использовать себя (Server-объект) в качестве словаря, например в insertSubDict( WS, ("key", ...), val )
    def get(self, key):
        return getattr(self, key, None)
    def __getitem__(self, key):
        return getattr(self, key, None)
    def __setitem__(self, key, value):
        setattr(self, key, value)
            
    ##---------------------------------------------------------------------------------------------------
    # OVERRIDE
    def onGetPeerServer(self, peer, peer_name, peer_id, status):
        if status == handlers.PEER_DELETED:
            return
        if peer["on"] and peer_id:
            self.peers[peer_id] = ClassDict(peer, name=peer_name)
            
    def getPeersFromCoordinator(self):
        self.peers = {}
        res = httpClientRequest( addr=options.coordinator, server="x", params="action=aux_ready&name=%s" % options.server_name )
        if res and res.get("ok"):
            _peers = res.get("peers")
            info( "got peers reply from coordinator: len %d" % len(_peers) )
            if _peers and isinstance(_peers, dict):
                for peer_name, peer in _peers.iteritems():
                    peer_id = toint( peer.get("server_id") )
                    info( "peer[%s]: %s, peer_id=%s" % (peer_name, peer, peer_id) )
                    self.onGetPeerServer( peer, peer_name, peer_id, handlers.PEER_ADDED )
                        
    def getPeerServerByName(self, peer_name):
        if self.peers:
            for peer_id, peer in self.peers.iteritems():
                if peer.get("name") == peer_name:
                    return peer
        
    # -----------------------------------------------
    @staticmethod
    def getCoordinatorConfig( classOf ):
        coord_res = {}
        if options.coordinator != "none":
            # начали слушать; сообщаем координатору, что готовы принимать http-send'ы на своем порту
            coord_res = httpClientRequest( addr=options.coordinator, server="x", params="action=ws_ready&name=%s" % options.server_name )
            if coord_res and coord_res.get("ok"):
                info( "Reported 'ready' state to coordinator: reply " + str(coord_res) )
                classOf.updateSpecificParamList( coord_res, getattr(classOf, "_SPECIFIC_CONFIG_PARAMS", {}), classOf.server_type_name )
            else:
                return fatal( "Cannot report to coordinator (addr:%s)\ncoordinator reply was:%s" % ( str(options.coordinator), str(coord_res) ) )
        
    ##---------------------------------------------------------------------------------------------------
    ## OVERRIDES

    @staticmethod
    def initOptions():
        pass
        
    @staticmethod
    def checkStartupFail():
        pass
        
    @staticmethod
    def updateSpecificParamList( coord_res, SPECIFIC_CONFIG_PARAMS={}, server_type_name="" ):
        if SPECIFIC_CONFIG_PARAMS:
            for key, fieldname in SPECIFIC_CONFIG_PARAMS.iteritems():
                val = coord_res.get( key, "" )
                setattr( cfg, fieldname, val )
                info( "%s updateSpecificParamList: %r=%r [cfg.%s]" % ( server_type_name, key, val, fieldname ))
    
    @staticmethod
    def initInterfaces( classOf ):
        return {}
        
    @staticmethod
    def destroyInterfaces( dictInterfaces ):
        pass
    
    def tick(self):
        pass

    def createActionsCSV(self, stype, sname, sid, test_mode=False):
        pass
    def closeActionsCSV(self):
        pass
    def printActionsCSV(self, nametag, action_dict ):
        pass
        
    def onBlockingAlarm(self, signal, frame):
        loop = tornado.ioloop.IOLoop.instance()
        tornado_patch.set_blocking_alarm(loop) # сразу же обновляем alarm (иначе зависание в callback-е на этом же тике (начиная с нашего же log_stack) окажется фатальным
        try:
            loop.log_stack( signal, frame )
        except:
            pass
        raise Exception("Blocking alarm")

    def httpLogTick(self):
        if options.log_http:
            try:
                loop = tornado.ioloop.IOLoop.instance()
                loop.http_log.send()
            except:
                catch()

    def mkStatDump(self):
        "Open a file to dump the overflown unsent stats buffer (used in by StatsAgent, istat.py)."
        if not getattr(self, 'statDumpPrefix', None):
            prefix = options.log_file_prefix
            if prefix.endswith('.log'):
                prefix = prefix[:-4]
            self.statDumpPrefix = ''.join((prefix, '.', str(options.server_id), '.statdump'))
        if not getattr(self, 'statDumpCounter', None):
            self.statDumpCounter = 0
        self.statDumpCounter += 1
        return open(self.statDumpPrefix + '-' + str(self.statDumpCounter), 'wt') # Possible exception should be catched by a caller

    ##---------------------------------------------------------------------------------------------------
    ##---------------------------------------------------------------------------------------------------
    
    @staticmethod
    def main( ServerClass ):
        """ старт generic торнадо-сервера """
        ServerClass.initOptions()
        tornado.options.parse_command_line()

        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            opts = options.as_dict().keys()
            opts.sort()
            for opt in opts:
                print( "--%s = %r" % (str(opt), options[opt]));
        else:
            opts = options.keys()
            opts.sort()
            for opt in opts:
                print( "--%s = %r" % (str(opt), options[opt].value()));

        # STARTUP log:
        logger = logging.getLogger()
        logger.setLevel( loggingSeverity( options.log_level ) )
        if options.log_file_prefix:
            # временный log handler, только чтобы записать лог стартовых запросов
            startup_handler = logging.FileHandler( options.log_file_prefix + "._startup", mode="w" )
            startup_handler.setFormatter( logging.Formatter("[%(asctime)s %(levelname)8s] %(message)s") )
            #startup_handler.setFormatter( LogFormatter() )
            logger.addHandler(startup_handler)
            
            logging.basicConfig( stream=logger )
            
            info( "--- Startup log ---" )
        else:
            # STDERR logging
            logging.basicConfig( filename=None, level=loggingSeverity( options.log_level ), format='[%(asctime)s %(levelname)8s] %(message)s' )
        
        #~ if options.log_scribe_host:
            #~ info( "init log_scribe_host" )
            #~ import cluster_logs
            #~ loop = tornado.ioloop.IOLoop.instance()
            #~ loop.logs = cluster_logs.AsyncLogsManager(options)

            #~ if options.log_file_prefix:
                #~ file_name = os.path.split(options.log_file_prefix)[1]
                #~ app_name = os.path.splitext(file_name)[0]
            #~ else:
                #~ app_name = 'default'
            #~ handler = cluster_logs.LogHandler(cluster_logs.AsyncLogsManager(options), category = app_name)
            #~ handler.setFormatter( logging.Formatter("[%(asctime)s %(levelname)8s] %(message)s") )
            #~ handler.setLevel( loggingSeverity( options.log_scribe_level ) )
            #~ logger.addHandler(handler)

        # проверим, можно ли вообще запускаться в существующих условиях (не занят ли порт и т.п.)
        if ServerClass.checkStartupFail():
            return
        
        application = tornado.web.Application( [
            # изначально не принимаем ничего
        ] )
        if options.ssl:
            ssl_options = {"certfile": options.ssl_cert, "keyfile": options.ssl_key, "cert_reqs": options.ssl_reqs, "ca_certs": options.ssl_cert}
            info( "using SSL: %s" % ssl_options )
            http_server = tornado.httpserver.HTTPServer( application, ssl_options=ssl_options )
        else:
            http_server = tornado.httpserver.HTTPServer( application )
            
        http_server.bind(options.port)
        http_server.start(options.nump)

        loop = tornado.ioloop.IOLoop.instance()

        if options.log_http:
            info( "init log_http (severity=%r)" % (options.log_http_level) )
            severity_level = loggingSeverity( options.log_http_level )
            import severe_logger
            loop = tornado.ioloop.IOLoop.instance()
            handler = severe_logger.PacketedJsonHttpLogHandler( level=severity_level, max_queue_size=options.log_http_max_count, channel_name=options.server_name,
                service_id=options.server_class, process_id=options.server_name )
            handler.setFormatter( logging.Formatter("%(message)s") )
            loop.http_log = handler
            logger.addHandler(handler)

        # LOG ROTATION:
        if options.log_file_prefix:
            logger = logging.getLogger()
            logger.removeHandler(startup_handler)
            #app_log = logging.getLogger("tornado.application")
            # а вот это уже постоянный rotating log, содержащий в названии полученный от координатора server_id
            if options.log_rotation == "external":
                sys.path.append('services/common/py')
                sys.path.append('../services/common/py')
                import System.logs
                handler = System.logs.SafeWatchedFileHandler( options.log_file_prefix )
                #handler.setFormatter( logging.Formatter("[%(asctime)s %(levelname)8s] %(message)s") )
                handler.setFormatter( LogFormatter() )
                logger.addHandler( handler )
            else:
                handler = logging.handlers.TimedRotatingFileHandler(options.log_file_prefix + "." + str(options.server_id), when='M', \
                    interval=tofloat(options.log_rotation_interval))
                #handler.setFormatter( logging.Formatter("[%(asctime)s %(levelname)8s] %(message)s") )
                handler.setFormatter( LogFormatter() )
                logger.addHandler( handler )
                if options.server_id < 0:
                    handler.doRollover()
            
            info( "--------------- Server [%s.%s] log started -------------" % ( str(options.server_name), str(options.server_id) ))
            info( "server ioloop: " + str(loop) )
            info( "http server listening (name=%r port=%d nump=%s)" % (options.server_name, options.port, options.nump) )
            info( "Log handler type: %s" % handler.__class__.__name__ )
        

        # --- интерфейсы ----
        dictInterfaces = ServerClass.initInterfaces( ServerClass )

        # --- инстанс веб-сервера ----
        WS = ServerClass( I=dictInterfaces, **dictInterfaces )
        dictInterfaces.WS = WS
        loop.ws = WS
        
        if options.log_http:
            # если получаем cfg от координатора, берем урлы оттуда; если нет - напрямую из coord_cfg
            urls = getattr(cfg, "EVENT_SERVICES", []) or getattr(coord_cfg, "COORDINATOR_EVENT_SERVICES", []) 
            loop.http_log.setHTTP( urls, dictInterfaces.HTTP )
        
        # Set the signal handler (чтобы корректно убить процесс, под linux отправляем ему Ctrl+C или "kill -s SIGINT pid")
        signal.signal( signal.SIGINT, WS.sig_handler )

        # добавляем handlers для реальных запросов (через load balancer, через внутри-кластерный порт, или по прямому имени сервера)
        if WS.initHandlers( application ):
            return
        
        ## ------------------------------
        WS._tick() # вешаем хэндлер периодических тиков нашего веб-сервера (раз в секунду)

        success( "Starting ioloop [server %d:%r].." % (options.server_id, options.server_name) )
        WS.onSetBlockingAlarm(loop)
        loop.start()
        
        # чистимся
        dictInterfaces.WS = None
        ServerClass.destroyInterfaces( dictInterfaces )
        
    def onSetBlockingAlarm(self, loop):
        loop.set_blocking_signal_threshold( options.blocking_threshold, self.onBlockingAlarm )

