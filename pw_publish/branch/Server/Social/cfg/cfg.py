# -*- coding: cp1251 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network
from binascii import crc32   # zlib version is not cross-platform
from base.helpers import json_dumps

##----------------------------------------------------------------------------------------------------------------------
## общедоступный (внешний) адрес балансера, на который могут ломиться снаружи клиенты
BALANCER_EXTERNAL = "127.0.0.1:88"

##----------------------------------------------------------------------------------------------------------------------
## общедоступный (внешний) адрес балансера, на который по SSL могут ломиться клиенты, с запросами к PW Connect
BALANCER_PWCONNECT = "127.0.0.1:888"

##----------------------------------------------------------------------------------------------------------------------
## внутренний (закрытый) адрес балансера, на который можно ломиться только изнутри кластера (например, чтобы попасть со служебной командой на свой же чат-сервер)
BALANCER_INTERNAL = "127.0.0.1:8888"

##----------------------------------------------------------------------------------------------------------------------
## кластерные настройки memcache-серверов -- их сообщает при старте координатор
CLUSTER_MC_SERVER_LIST = []
CLUSTER_MC_SERVER_CRC32 = [] # поскольку список MC-серверов может динамически меняться, здесь будем хранить [ crc(CLUSTER_MC_SERVER_LIST) ], чтобы mc-threads видели, когда список меняется

CLUSTER_MC_SERVER_COUNT = 0

def resetMcServers( mc_list=None ):
    global CLUSTER_MC_SERVER_COUNT
    global CLUSTER_MC_SERVER_CRC32
    if mc_list != None:
        CLUSTER_MC_SERVER_LIST[:] = mc_list[:]
    CLUSTER_MC_SERVER_COUNT = len(CLUSTER_MC_SERVER_LIST)
    CLUSTER_MC_SERVER_CRC32[:] = [ crc32( ",".join(CLUSTER_MC_SERVER_LIST) ) ] # в sql-threads будем передавать как бы указатель на это значение
    

##----------------------------------------------------------------------------------------------------------------------
## кластерные настройки sql-серверов -- их сообщает при старте координатор
CLUSTER_SQL_SERVER_COUNT = 0
CLUSTER_SQL_CONFIG = []
CLUSTER_SQL_SERVER_CRC32 = [] # поскольку список SQL-серверов/баз может динамически меняться, здесь будем хранить [ crc(SERVER_LIST) ], чтобы видеть, когда список меняется

def resetSqlServers( sql_list=None ):
    global CLUSTER_SQL_SERVER_COUNT
    global CLUSTER_SQL_SERVER_CRC32
    if sql_list != None:
        CLUSTER_SQL_CONFIG[:] = sql_list[:]
    CLUSTER_SQL_SERVER_COUNT = len(CLUSTER_SQL_CONFIG)
    json_list = json_dumps(sql_list)
    CLUSTER_SQL_SERVER_CRC32[:] = [ crc32( json_list ) ] # в sql-threads будем передавать как бы указатель на это значение


##----------------------------------------------------------------------------------------------------------------------
## кластерные настройки mongoDB-серверов -- их сообщает при старте координатор
CLUSTER_MONGO_SERVER_COUNT = 0
CLUSTER_MONGO_CONFIG = [
    { "mongo_addr":"localhost", "mongo_port":27017, "mongo_base":"pw1", "network_timeout":10 },
    { "mongo_addr":"localhost", "mongo_port":27017, "mongo_base":"pw2", "network_timeout":10 },
]
CLUSTER_MONGO_SERVER_CRC32 = [] # поскольку список серверов/баз может динамически меняться, здесь будем хранить [ crc(SERVER_LIST) ], чтобы видеть, когда список меняется

def resetMongoServers( mongo_list=None ):
    global CLUSTER_MONGO_SERVER_COUNT
    global CLUSTER_MONGO_SERVER_CRC32
    if mongo_list != None:
        CLUSTER_MONGO_CONFIG[:] = mongo_list[:]
    CLUSTER_MONGO_SERVER_COUNT = len(CLUSTER_MONGO_CONFIG)
    json_list = json_dumps(mongo_list)
    CLUSTER_MONGO_SERVER_CRC32[:] = [ crc32( json_list ) ] # в thread-pool будем передавать как бы указатель на это значение


##----------------------------------------------------------------------------------------------------------------------
## количество рабочих ниток/коннектов
HTTP_CURL_WORKERS = 128
HTTP_CURL_CONNECTIONS = 64

HTTP_REQUEST_LIMIT = 64

ZZIMA_BILLING_THREADS = 20

SQL_THREADS = 2
MEMCACHE_THREADS = 2
MONGO_THREADS = 2

PWC_SMTP_THREADS = 8

SERIAL_MODEL_DATA_THREADS = 2

##----------------------------------------------------------------------------------------------------------------------
## data mirroring config
MIRROR_QUEUE_CONFIG = \
    { "sql_host":"localhost:3306", "sql_base":"pw_mirror", "sql_user":"pwm", "sql_pass":"pwmdata" }
MIRROR_QUEUE_THREADS = 2

MIRROR_EXPORT_CONFIG = \
    { "sql_host":"localhost:3306", "sql_base":"pw_stat", "sql_user":"pws", "sql_pass":"pwsdata" }
MIRROR_EXPORT_THREADS = 2

##----------------------------------------------------------------------------------------------------------------------
PVX_LOGIN_ADDRESS = "127.0.0.1:35001"

MATCHMAKER_LOCALES = {
    # "RU": ["127.0.0.1:34000", "127.0.0.1:34001"], # в боевых вариантах по умолчанию 2 gateway
    "RU": ["127.0.0.1:34000"], # в тестах 1, чтобы не делилось между двумя fake mathmaker-ами
}
MATCHMAKER_DEFAULT_LOCALE = "RU"

##----------------------------------------------------------------------------------------------------------------------
## адрес zzima billing/authorization (обычно узнаём у координатора)
ZZIMA_WSDL = ""
ZZIMA_SERVICE_NAME = ""
ZZIMA_SERVICE_PASSWORD = ""
ZZIMA_PAYMENT_SYSTEM = ""

AGG_BILLING_PREFIX = ""

BILLING_CHECK_BALANCE_PERIOD = 30 # примерно раз в N секунд переcпрашиваем баланс юзера

##----------------------------------------------------------------------------------------------------------------------
## IP и ключи для обращения через HTTP POST к ZZimaAPI
ZZIMA_API_URL = ""
ZZIMA_API_KEY = ""
ZZIMA_API_SECRET = ""

##----------------------------------------------------------------------------------------------------------------------
## адрес social aggregator (обычно узнаём у координатора)
SOCIAL_AGGREGATOR_ADDRESS = "127.0.0.1:8703"

##----------------------------------------------------------------------------------------------------------------------
## адрес person server (обычно узнаём у координатора)
PERSON_SERVER_ADDRESS = "127.0.0.1:8704"

##----------------------------------------------------------------------------------------------------------------------
## адрес сервера статистики (обычно узнаём у координатора) -- статистика логинов/логаутов и т.п.
STATS_AGENT_URL = "127.0.0.1:8709"


##----------------------------------------------------------------------------------------------------------------------
## (обычно узнаём у координатора, здесь значение в осн. для тестов)
PVX_CAN_RECONNECT = 1

##----------------------------------------------------------------------------------------------------------------------
## Нужно ли шифровать трафик
#TODO:LOFIK:ENCIPHER_TRAFFIC
#ENCIPHER_TRAFFIC = 0

##----------------------------------------------------------------------------------------------------------------------
## срок активации PWC-аккаунта, в днях
PWC_ACTIVATION_DAYS = 2
## ... в секундах
PWC_ACTIVATION_TERM = PWC_ACTIVATION_DAYS*(24*60*60) ## двое суток

##----------------------------------------------------------------------------------------------------------------------
## не чаще чем раз в столько времени можно высылать новый код активации для PWC
PWC_RETRY_CONFIRM_PERIOD = 60*60 ## час

##----------------------------------------------------------------------------------------------------------------------
## не чаще чем раз в столько времени можно ресетить PWC password
PWC_RESET_PWD_PERIOD = 60*60 ## час

##----------------------------------------------------------------------------------------------------------------------
## DEBUG: разрешаем ли выдачу fake pwc auid-ов (когда под рукой нет умеющего это делать соц.аггрегатора)
PWC_ALLOW_FAKE_AUIDS = 1

##----------------------------------------------------------------------------------------------------------------------
## DEBUG: разрешаем логин через pwconnect без проверки подписи
PWC_SKIP_SIGNATURE_CHECK = 0

##----------------------------------------------------------------------------------------------------------------------
## сессии, по которым нет подтвержденных mm-пингов в течении стольки секунд, считаем !valid
MM_VALIDATION_SECONDS = 300

##----------------------------------------------------------------------------------------------------------------------
## после N фейлов подряд на конкретном gateway_addr -- считаем этот гейт нерабочим, и впредь беспокоим его только запросами статуса 
## (остальной matchmaking трафик отправляем на рабочие гейты)
MM_MAX_INDIVIDUAL_GATEWAY_FAILS = 1000000

##----------------------------------------------------------------------------------------------------------------------
## адрес social exchange service (balancer)
SOCIAL_EXCHANGE_URL = "127.0.0.1:88"

GUILD_SERVICES = []

##-----------------------------------------------------------------------------------------------------------------------
## Maximum number of stat records stored while being resended.
STATS_RESEND_POOL_LIMIT = 10000

RESTRICT_FACEBOOK_USERS = False
RESTRICT_LOCATIONS = False

SKIP_LIMIT_CHECK = True
TOURNAMENT_SERVER = False

GEO_DATA_PATH = 'vendor/pygeoip/data/GeoIPCity.dat'
BILLING_MERGE_DISABLED_PS = []

COORDINATOD_PREDEFINED_LOCALES = {'fb#9999999999999': 'US'}

META_MUIDS = ['mailru', 'zzima', 'aeria', 'amazon', 'cenega', 'steam', 'arcgames']

MERGE_REFUND_GOLD_ALLOWED = False
MERGE_TRANSFER_GOLD_ALLOWED = False
