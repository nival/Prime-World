# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network
from binascii import crc32   # zlib version is not cross-platform
from base.helpers import json_dumps

##----------------------------------------------------------------------------------------------------------------------
## кластерные настройки mongoDB-серверов 
CLUSTER_MONGO_CONFIG = [
    { "mongo_addr":"localhost", "mongo_port":27017, "mongo_base":"pw1", "network_timeout":10 },
    { "mongo_addr":"localhost", "mongo_port":27017, "mongo_base":"pw2", "network_timeout":10 },
]
CLUSTER_MONGO_THREADS = 2
CLUSTER_MONGO_SERVER_COUNT = 2

##----------------------------------------------------------------------------------------------------------------------
## data mirroring config
MIRROR_QUEUE_CONFIG = \
    { "sql_host":"localhost:3306", "sql_base":"pw_mirror", "sql_user":"pwm", "sql_pass":"pwmdata" }
MIRROR_QUEUE_THREADS = 2

MIRROR_EXPORT_CONFIG = \
    { "sql_host":"localhost:3306", "sql_base":"pw_stat", "sql_user":"pws", "sql_pass":"pwsdata" }
MIRROR_EXPORT_THREADS = 2

# запросы, висящие в очереди более N секунд, считаем протухшими, и периодически чистим
MIRROR_QUEUE_CLEAN_PERIOD = 100 # как часто проверяем
MIRROR_QUEUE_TTL = 1000 # как скоро запрос протухает

# для вытаскивания персональной инфы (дата регистрации, логина-логауты, дата рождения) нужен доступ к соц.аггрегатору
HTTP_CURL_WORKERS = 16
#SOCIAL_AGGREGATOR_ADDRESS = "b373.nivalnetwork.com:88"
SOCIAL_AGGREGATOR_ADDRESS = "10.200.1.71:88"

##----------------------------------------------------------------------------------------------------------------------
# период запуска garbage collection
MIRROR_DEFAULT_GC_PERIOD = 30.0

## Время срабатывания исключения при длительной блокировке процесса
DEFAULT_MIRROR_BLOCKING_THRESHOLD = 16.0

# таймаут проверки очереди запросов
PENDING_GET_TIMEOUT = 1

# длина очереди запросов на удаление
REMOVE_TASKS_QUEUE_LEN = 100