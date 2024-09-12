# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *
from base.http_dumb import *

import httplib

#addModPath('tornado')

import tornado.httpserver
import tornado.ioloop
import tornado.options
import tornado.web
import tornado.httpclient

#from tornado.options import define, options

import isql
import imirror
import iexport
import idata
import imemcache
import ihttp
import iwebserver, imatchmaker
import iaggregator
import ismtp

sys.path.append('guild')

import cfg # конфиг кластера

##----------------------------------------------------------------------------------------------------------------------
class IfaceFactory:
    """ Фабрика интерфейсов для общения с внешними компонентами (isql, imemcache и т.п.) """
    
    @staticmethod
    def makeSqlInterface( options_sql, new_sql_list, num_threads=2, syncWait=4.0 ):
        """ Заводим новый ISql-интерфейс, сообразно options и заданному new_sql_list. """
        sql_list = new_sql_list or []
        if options_sql == "async" and sql_list:
            import cluster_sql
            SQL = isql.AsyncMysql()
            # заводим набор worker threads для кластерных sql-запросов
            cfg.resetSqlServers( sql_list )
            
            loop = tornado.ioloop.IOLoop.instance()
            loop.sql = []
            for sql_id,opts in enumerate( cfg.CLUSTER_SQL_CONFIG ):
                cOpts = ClassDict( opts )
                async = cluster_sql.AsyncSqlManager( cOpts, num_threads, sql_id+1, syncWait, instrument=True )
                loop.sql.append( async )
                #~ async.perform() # вешаем периодический хэндлер ответов (для перекладывания ответов от sql thread pool в главный IOLoop)
        elif options_sql == "sync" and new_sql_list:
            import cluster_sql
            SQL = cluster_sql.SyncSqlManager(ClassDict(new_sql_list[0]))
            SQL.openConnection()
        else: # options_sql == "none" или список sql-серверов пустой
            if options_sql == "async":
                bad_warn( "SQL SERVER LIST EMPTY! defaulting to dummy ISql interface" )
            SQL = isql.ISql()
            
        return SQL
        
    @staticmethod
    def makeMirrorInterface( options_tag, sql_config, num_threads=2, syncWait=4.0 ):
        """ Заводим новый mirror-queue-интерфейс, сообразно options. """
        if options_tag == "async" and sql_config:
            import cluster_sql
            IFACE = imirror.AsyncSqlMirrorQueue()
            cConfig = ClassDict( sql_config )
            loop = tornado.ioloop.IOLoop.instance()
            loop.mirror = cluster_sql.AsyncSqlManager( cConfig, num_threads, 1, syncWait, instrument=True )
            loop.mirror.CNAME = "mirror"
        else: # options_tag == "none" или список sql-серверов пустой
            if options_tag == "async":
                bad_warn( "NO MIRROR SQL CONFIG! defaulting to dummy IMirrorQueue interface" )
            IFACE = imirror.IMirrorQueue()            
        return IFACE

    @staticmethod
    def makeExportInterface( options_tag, sql_config, num_threads=2, syncWait=4.0 ):
        """ Заводим новый data-export интерфейс, сообразно options. """
        if options_tag == "async" and sql_config:
            import cluster_sql
            IFACE = iexport.AsyncSqlDataExport()
            cConfig = ClassDict( sql_config )
            loop = tornado.ioloop.IOLoop.instance()
            loop.export = cluster_sql.AsyncSqlManager( cConfig, num_threads, 1, syncWait, instrument=True )
            loop.export.CNAME = "export"
        else: # options_tag == "none" или список sql-серверов пустой
            if options_tag == "async":
                bad_warn( "NO EXPORT SQL CONFIG! defaulting to dummy IDataExport interface" )
            IFACE = iexport.IDataExport()
        return IFACE
        
    @staticmethod
    def makeMcInterface( options_mc, new_mc_list, num_threads=iwebserver.WS_MAX_MC_THREADS, syncWait=1.0 ):
        """ Заводим новый IMemcache-интерфейс, сообразно options и заданному new_sql_list. """
        if options_mc == "async":
            import cluster_memc
            # заводим набор worker threads для memcache-запросов (правильный набор mc-серверов должен прийти от координатора)
            MC = imemcache.AsyncMemcache()
            mc_list = new_mc_list or []
            cfg.resetMcServers( mc_list )
            
            loop = tornado.ioloop.IOLoop.instance()
            loop.mc = cluster_memc.AsyncMemcacheManager(cfg.CLUSTER_MC_SERVER_LIST, cfg.CLUSTER_MC_SERVER_CRC32, num_threads, syncWait)
            
        elif options_mc == "mocky":
            MC = imemcache.MemcacheMockYes() # болванка, эмулирует на все согласный memcache (всегда есть "ничей логин-ключ", всегда можно его залокать; uid возвращается всегда уникальный)
        else:
            MC = imemcache.IMemcache() # болванка, эмулирует совершенно пустой memcache (сплошные отказы)
            
        return MC
    
    
    @staticmethod
    def makeZZimaInterface( options_zz, wsdl, HTTP=None, service_name="pw", payment_system="CBT", num_threads=1, syncWait=10 ):
        """ Заводим новый IZZima-интерфейс, сообразно options и заданному wsdl. """
        info( "makeZZimaInterface" )
        import izzima
        loop = tornado.ioloop.IOLoop.instance()
        if options_zz == "http" and wsdl:
            # заводим набор worker threads для memcache-запросов (правильный набор mc-серверов должен прийти от координатора)
            ZZ = izzima.HttpZZima( HTTP, service_name=service_name, payment_system=payment_system, billing_url=wsdl )
            loop.zz = ZZ
            
        elif options_zz == "async" and wsdl:
            import cluster_zzima
            # заводим набор worker threads для memcache-запросов (правильный набор mc-серверов должен прийти от координатора)
            ZZ = izzima.AsyncZZima( HTTP, service_name, payment_system )
            loop.zz = cluster_zzima.AsyncZZimaManager(wsdl, num_threads, syncWait)
            
        else:
            ZZ = izzima.IZZima( HTTP, service_name, payment_system ) # болванка, эмулирует сплошные отказы
            
        return ZZ
        
        
    @staticmethod
    def makeSmtpInterface( options_smtp, options, dumpfilename="logs/SMTP.out.txt", num_threads=ismtp.WS_MAX_SMTP_THREADS, syncWait=10 ):
        """ Заводим новый SMTP-интерфейс, сообразно options.smtp """
        info( "makeSmtpInterface" )
        if options_smtp == "async":
            import cluster_smtp
            # заводим набор worker threads для memcache-запросов (правильный набор mc-серверов должен прийти от координатора)
            SMTP = ismtp.IRealSmtp()
            
            loop = tornado.ioloop.IOLoop.instance()
            loop.smtp = cluster_smtp.AsyncSmtpManager(options, num_threads, syncWait)
            
        else:
            SMTP = ismtp.IDummySmtp( dumpfilename=dumpfilename ) # болванка, эмулирует сплошные отказы
            
        return SMTP
        
    @staticmethod
    def makePvxMmInterface( options_pvx, HTTP=None ):
        """ Заводим новый PvxMatchmaker-интерфейс, сообразно options и заданному адресу. """
        if options_pvx == "dummy":
            PVX = imatchmaker.MockMatchmaker()
        elif options_pvx == "http":
            # не local, и адрес указан
            PVX = imatchmaker.HttpMatchmaker( HTTP=HTTP )
        elif options_pvx == "none":
            PVX = imatchmaker.IMatchmaker()
        else:
            raise "bad pvx option (should be none|dummy|http)"
        return PVX
    

    @staticmethod
    def makeSocAggInterface( options_agg, agg_addr, version, HTTP=None ):
        """ Заводим новый SocialAggregator-интерфейс, сообразно options и заданному адресу. """
        if options_agg == "dummy" or (not agg_addr):
            AGG = iaggregator.ISocialAggregator( version )
        elif options_agg == "http":
            # не local, и адрес указан
            AGG = iaggregator.IRealSocialAggregator( agg_addr, version, HTTP )
        else:
            raise "bad soc_agg option (should be dummy|http)"
        return AGG
        

    @staticmethod
    def makeIDataInterface( options_data, mongo_list, SQL, num_threads=idata.WS_MAX_MONGO_THREADS, syncWait=2.0 ):
        """ helper wrapping cfg.resetMongoServers() call for WS cluster-config """
        if options_data == "mongo" and mongo_list:
            # заводим набор worker threads для кластерных sql-запросов
            cfg.resetMongoServers( mongo_list )
            return IfaceFactory.makeIDataInterfaceSimple( options_data, cfg.CLUSTER_MONGO_CONFIG, SQL, num_threads, syncWait )
        return IfaceFactory.makeIDataInterfaceSimple( options_data, mongo_list, SQL, num_threads, syncWait )

    @staticmethod
    def makeIDataInterfaceSimple( options_data, mongo_list, SQL, num_threads=idata.WS_MAX_MONGO_THREADS, syncWait=2.0 ):
        """ Заводим новый нереляционный IData-интерфейс, сообразно options. """
        if options_data == "mongo" and mongo_list:
            import cluster_mongo
            DATA = idata.AsyncMongo( len(mongo_list) )
            loop = tornado.ioloop.IOLoop.instance()
            loop.mongo = []
            for mongo_id,opts in enumerate( mongo_list ):
                cOpts = ClassDict( opts )
                async = cluster_mongo.AsyncMongoManager( cOpts, num_threads, mongo_id+1, syncWait, instrument=True )
                loop.mongo.append( async )
            return DATA
        elif options_data == "sql":
            # fallback SQL-интерфейс
            return SQL
        elif options_data == "none":
            # пустая заглушка
            return idata.IData()
        else:
            raise "bad data option (should be none|sql|mongo)"
            return None

    @staticmethod
    def makeIStatsInterface(options_stats, url, iDict, resend_pool_limit = 10000):
        if options_stats == "thrift":
            from istats import StatsAgent
            DATA = StatsAgent(url, iDict, resend_pool_limit)
            return DATA
        elif options_stats == "none":
            from istats import IStats
            DATA = IStats(url, iDict)
            return DATA
        else:
            raise "bad data option (should be thrift|none)"
            return None


    @staticmethod
    def makePersonServerInterface(options_pers, address, HTTP, FRIENDS=None, PARTY=None):
        if options_pers == "none" or (not address) or (not HTTP):
            from ipersonserver import IPersonServer
            return IPersonServer()
        elif options_pers == "http":
            from ipersonserver import IHttpPersonServer
            return IHttpPersonServer( address, HTTP )
        elif options_pers == "scaled":
            from ipersonserver import IScaledPersonServer
            return IScaledPersonServer( address, HTTP=HTTP, FRIENDS=FRIENDS, PARTY=PARTY )
        else:
            raise "bad pers option (should be scaled|http|none)"

    @staticmethod
    def makeGuildServiceInterface(options_guilds, address, HTTP, request_limit=1000):
        if options_guilds == "none" or (not address) or (not HTTP):
            from iguildservice import IGuildService
            return IGuildService()
        elif options_guilds == "http":
            from iguildservice import IHttpGuildService
            return IHttpGuildService( address, HTTP, request_limit=request_limit )
        else:
            raise "bad guilds option (should be http|none)"

    @staticmethod
    def makeSiegeServiceInterface(options_siege, address, HTTP, request_limit=1000):
        if options_siege == "none" or (not address) or (not HTTP):
            from isiegeservice import ISiegeService
            return ISiegeService()
        elif options_siege == "http":
            from isiegeservice import IHttpSiegeService
            return IHttpSiegeService( address, HTTP, request_limit=request_limit )
        else:
            raise "bad guilds option (should be http|none)"


    @staticmethod
    def makeSerialModelInterface( options_smodel, iDict, server_version, num_threads=iwebserver.WS_MAX_SERIAL_THREADS, load_conversion_xml=True ):
        if options_smodel == "async":
            from cluster_serial import AsyncSerialModelManager
            from iserialmodel import IAsyncSerialModel
            loop = tornado.ioloop.IOLoop.instance()
            loop.smodel = AsyncSerialModelManager( iDict, server_version, num_threads )
            SMODEL = IAsyncSerialModel( iDict, server_version )
            return SMODEL
        elif options_smodel == "sync":
            from iserialmodel import ISyncSerialModel
            SMODEL = ISyncSerialModel( iDict, server_version, load_conversion_xml )
            return SMODEL
        

    @staticmethod
    def makeIPeerWebServerInterface(options_wsx, HTTP, request_limit=1000):
        if options_wsx == "none" or (not HTTP):
            from ipeerserver import IPeerWebServer
            WSX = IPeerWebServer()
            return WSX
        elif options_wsx == "fake":
            from ipeerserver import IFakePeerWebServer
            WSX = IFakePeerWebServer( HTTP )
            return WSX
        elif options_wsx == "http":
            from ihttp import ILimitedAsyncHttpFetcher
            WSX = ILimitedAsyncHttpFetcher( HTTP, request_limit )
            return WSX
        else:
            raise "bad wsx option (should be http|fake|none)"
            return None

    @staticmethod
    def makeIChatServerInterface(option, address, HTTP, request_limit=1000):
        import ichatserver
        if option == "none" or (not HTTP):
            return ichatserver.IChatServer()
        elif option == "fake":
            # fake-интерфейс: на любой запрос будет возвращать одинаковый ответ "все хорошо, прекрасная маркиза"
            class ChatHTTP(object):
                def __call__(self, args):
                    return {'ok' : 1, 'host' : 'chat0', 'key' : '1234'}
            return ichatserver.IFakeChatServer( ChatHTTP() )
        elif option == "http":
            return ichatserver.IRealChatServer(address, HTTP, request_limit=request_limit)
        else:
            raise "bad chat api option (should be http|fake|none)"
            return None

    @staticmethod
    def makeChatFilterInterface(option, address, HTTP, request_limit=1000):
        import ichatfilter
        if option == "fake" or (not HTTP):
            warn("chat filter option=%s, HTTP=%s, using IFakeChatFilter" % (option, HTTP))
            return ichatfilter.IFakeChatFilter()
        elif option == "cleanspeak":
            return ichatfilter.ICleanSpeakChatFilter(address, HTTP, request_limit=request_limit)
        else:
            raise "bad chat filter option (should be cleanspeak|fake)"
            return None

    @staticmethod
    def makeBillingInterface(options_billing, iDict):
        if options_billing == "zzima":
            from ibilling import ZzimaBilling
            BILL = ZzimaBilling( iDict )
            return BILL
        elif options_billing == "dummy":
            from ibilling import DummyBilling
            BILL = DummyBilling( iDict )
            return BILL
        elif options_billing == "none":
            from ibilling import IBilling
            BILL = IBilling()
            return BILL
        else:
            raise "bad billing option (should be zzima|dummy|none)"
            return None


    @staticmethod
    def makeSocialExchangeInterface(options_sex, HTTP, sex_url, ws_url, request_limit=1000):
        if options_sex == "async":
            from ixchange import IFakeSocialExchange
            SEX = IFakeSocialExchange( HTTP )
            return SEX
        elif options_sex == "dummy":
            from ixchange import IAsyncHttpSocialExchange
            SEX = IAsyncHttpSocialExchange( HTTP, sex_url, ws_url, request_limit=request_limit )
            return SEX
        else:
            raise "bad social exchange option (should be async|dummy)"
            return None

    @staticmethod
    def makeSteamPaymentsInterface(options_payments, HTTP, url, secret):
        if options_payments == "real":
            from ibilling import RealPayments
            PS = RealPayments( HTTP, url, secret, 'STEAM' )
            return PS
        elif options_payments == "none":
            from ibilling import IPayments
            PS = IPayments()
            return PS
        else:
            raise "bad Steam payments option (should be real|none)"
            return None

    @staticmethod
    def makeAeriaPaymentsInterface(options_payments, HTTP, url, secret):
        if options_payments == "real":
            from ibilling import RealPayments
            PS = RealPayments( HTTP, url, secret, 'AERIA' )
            return PS
        elif options_payments == "none":
            from ibilling import IPayments
            PS = IPayments()
            return PS
        else:
            raise "bad Aeria payments option (should be real|none)"
            return None

    @staticmethod
    def makeArcGamesPaymentsInterface(options_payments, HTTP, url, secret):
        if options_payments == "real":
            from ibilling import RealPayments
            PS = RealPayments( HTTP, url, secret, 'ARCGAMES' )
            return PS
        elif options_payments == "none":
            from ibilling import IPayments
            PS = IPayments()
            return PS
        else:
            raise "bad Aargames payments option (should be real|none)"
            return None

    @staticmethod
    def makeZZimacomPaymentsInterface(options_payments, HTTP, url, secret):
        if options_payments == "real":
            from ibilling import RealPayments
            PS = RealPayments( HTTP, url, secret, 'ZZIMA' )
            return PS
        elif options_payments == "none":
            from ibilling import IPayments
            PS = IPayments()
            return PS
        else:
            raise "bad zzima payments option (should be real|none)"
            return None

    @staticmethod
    def makeFriendServiceInterface(option, addresses=[""], HTTP=None):
        import ifriendservice
        if option == "none" or (not HTTP):
            return ifriendservice.IFriendService(addresses, None)
        elif option == "http":
            return ifriendservice.IHttpFriendService(addresses, HTTP)
        else:
            raise "bad chat api option (should be http|none)"
            return None
