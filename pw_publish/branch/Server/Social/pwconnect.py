# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# принимаем HTTPS (SSL) траффик для PW Connect
# (C) Dan Vorobiev 2012, Nival Network

import sys, os, time, json, logging

import tornado.options
from tornado.options import define, options

from base.helpers import *

sys.path.append('cfg')
import coord_cfg, cfg

from iwebserver import *
from ifactory import IfaceFactory
from iuserdata import IDataManager

from handlers import * # JsonHandler, IfaceFactory
from subaction import SubAction, action_timing, separate_timing, parseGeoLocation

import EC
import CC

from geolocation import GeoLocator

from ext_main.pwc_actions import PWConfirmAction, PWConfirmRedirectAction, PWCRegisterAction, PWResetPasswordAction, \
    PWResetPasswordLinkAction, PWChangePasswordAction, PWChangePasswordLinkAction, PWRetryConfirmAction, PWCChangeEmailAction  # возможно, будем здесь обрабатывать (а не на WS), чтобы по логам было проще смотреть PWC-операции

## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------
def md5( arg ):
    return hashlib.md5( str(arg) ).hexdigest()



## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------


class PwConnectHandler( JsonHandler ):
    """ main http request mapper (раскидываем запросы по handler methods, в зависимости от "/subaddr" и "action=") """

    unloggedActionMap = {
        # команды, открытые для любого внешнего клиента (правда, вход ограничен SSL-шифрованием)
        'pwc_register': PWCRegisterAction,
        'pwc_confirm': PWConfirmAction,
        'pwc_confirm_pretty': PWConfirmRedirectAction,
        'pwc_reset_pwd': PWResetPasswordAction,
        'pwc_reset_pwd_link': PWResetPasswordLinkAction,
        'pwc_change_pwd': PWChangePasswordAction,
        'pwc_change_pwd_link': PWChangePasswordLinkAction,
        'pwc_resend_confirm': PWRetryConfirmAction,
        'pwc_change_email': PWCChangeEmailAction,
    }

    internalActionMap = {
        # внутрикластерные команды; закрыты для внешних клиентов
        # --- служебное ----
        'check_alive': 'onCheckWebServerAlive', # base JsonHandler: проверяем, жив ли PersonServer
    }

    def __init__( self, application, request, I, SERVICES={}, **kwargs):
        JsonHandler.__init__( self, application, request, **kwargs )
        self._SERVICES = SERVICES
        self.I = I # server interface dict

## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

class PwConnectServer( ICSVActionTimingWriter, ITornadoServer ):
    """ TODO """
    server_type_name = "pwc"

    # ----------------------------------------------------------------------------------------------
    # ----------------------------------------------------------------------------------------------

    def __init__(self, **kwargs):
        super(PwConnectServer, self).__init__( **kwargs )


    # -----------------------------------------------
    def initHandlers(self, application):
        application.add_handlers( r"(.*)", [
            ( r"/", PwConnectHandler, dict(SUBADDR=SUBADDR_BALANCED, I=self.I) ),
            ( r"/x", PwConnectHandler, dict(SUBADDR=SUBADDR_INTERNAL, I=self.I) ),
            ## ( r"/%s" % server_name, PwConnectHandler, dict(SUBADDR=SUBADDR_SELF, I=self.I) ),
        ] )


    # -----------------------------------------------
    # return True if startup enviroment is bad
    @staticmethod
    def checkStartupFail():
        # проверяем, не слушает ли на нашем порту кто-то еще (защита от повторного запуска координатора)
        self_addr = "127.0.0.1:"+str(options.port)
        res = httpClientRequest( addr=self_addr, server="x", params="action=check_alive&name=_pw_connect_server_" )
        if res and res.get("ok") != None:
            fatal( "DUPLICATE PW CONNECT SERVER: already listening on " + self_addr + "\n(reply was %s)" % str(res) )
            return True # обламываемся, уже запущена копия веб-сервера на этом порту

        print( "check startup environment: ok, port free (" + self_addr + ")" )


    # -----------------------------------------------
    @staticmethod
    def initOptions():
        # поскольку нам надо выдавать fake auid-ы, пусть server_id выдается по таймстэмпу; auid будет иметь вид auid64 = [timestamp32 | autoinc32]
        PWC_EPOCH = toint( time.mktime( time.strptime("1 Jan 2012", "%d %b %Y") ) )
        timestamp = toint( (time.time() - PWC_EPOCH) / 60) # server_id ~ время старта с точностью до минуты

        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.server_id = timestamp
            options.server_name = PWCONNECT_SERVER_NAME
            options.server_class = "pwconnect"
        else:
            options["server_id"].set(timestamp)
            options["server_name"].set(PWCONNECT_SERVER_NAME)
            options["server_class"].set("pwconnect")

    # -----------------------------------------------
    @staticmethod
    def initInterfaces( classOf=None ):
        iDict = ClassDict()

        iDict.MD = IDataManager()
        iDict.HTTP = tornado.httpclient.AsyncHTTPClient( max_clients=coord_cfg.COORDINATOR_HTTP_CURL_WORKERS )

        geo_path = getattr(coord_cfg, "COORDINATOR_GEO_DATA_PATH", getattr(cfg, "GEO_DATA_PATH"))
        iDict.GEO = GeoLocator(geo_path)
        info( "I.GEO interface: path=%r", geo_path)

        iDict.SQL = IfaceFactory.makeSqlInterface( options.sql, coord_cfg.COORDINATOR_SQL_CONFIG, num_threads=coord_cfg.COORDINATOR_SQL_THREADS )
        info( "I.SQL interface: " + str(iDict.SQL) )

        iDict.AGG = IfaceFactory.makeSocAggInterface( options.soc_agg, coord_cfg.COORDINATOR_SOCIAL_AGGREGATOR_ADDRESS, SOCAGG_VERSION, HTTP=iDict.HTTP )
        info( "I.AGG interface: " + str(iDict.AGG) )

        iDict.SMTP = IfaceFactory.makeSmtpInterface( options.smtp, options, num_threads=coord_cfg.COORDINATOR_PWC_SMTP_THREADS )
        info( "I.SMTP interface: " + str(iDict.SMTP) )

        iDict.STATS = IfaceFactory.makeIStatsInterface( options.stats, coord_cfg.COORDINATOR_STATS_AGENT_URL, iDict, cfg.STATS_RESEND_POOL_LIMIT )
        info( "I.STATS interface: " + str(iDict.STATS) )

        return iDict

    # -----------------------------------------------
    def tick(self):
        SEC = toint(time.time())

        # inherited
        super(PwConnectServer, self).tick()

        try:
            self.I.STATS.Send()
        except:
            catch()

        if SEC % 60 == 0:
            self.updateInstrumentedActions()


## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

def main():
    ITornadoServer.main( PwConnectServer )

if __name__ == "__main__":
    #tornado 3.4 fix
    if options.__class__.__name__ == "OptionParser":
        options.port = 8710
    else:
        options["port"].set(8710)
    main()
