#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# (C) Danil "Eleneldil" Lavrentyuk, 2013-2014, Nival Network
import sys

USE_64_BIT = False # Использовать ли 64- или 32-битную версию mongo.
SINGLE_BASE = True # Использовать только одну базу монго, без шардинга

sys.path.append('../cfg')
from coord_cfg import COORDINATOR_MONGO_CONFIG
# Внимание! Мы здесь полагаем, что инстанс монги у нас запускается только один
MONGO_ADDR = COORDINATOR_MONGO_CONFIG[0]["mongo_addr"]
MONGO_PORT = COORDINATOR_MONGO_CONFIG[0]["mongo_port"]
if SINGLE_BASE:
    MONGO_BASE = COORDINATOR_MONGO_CONFIG[0]["mongo_base"]
else:
    MONGO_BASE = tuple(c["mongo_base"] for c in COORDINATOR_MONGO_CONFIG)

MONGO_PATH = '/usr/bin/'
MONGO_DB_PATH = '/var/lib/mongodb/'

MONGO_CLIENT = MONGO_PATH + "mongo"
MONGOD = MONGO_PATH + "mongod"

MONGO_DB_PATH = MONGO_DB_PATH + "database"
MONGO_LOCK = MONGO_DB_PATH + "/mongod.lock"
MONGO_LOAD = MONGO_PATH + "mongorestore"
MONGO_LOG = "../logs/mongod.log"
MONGO_FIX_SCRIPT = "mongo.js"

# Используются для операции "load".
# ВНИМАНИЕ! Это не логи сервера mongo, это логи вызовов клиента для загрузки данных на сервер.
LOG_FILE = "mongo.log"
ERROR_FILE = "mongo.error.log"

# Укажите здесь пути, где лежит дамп данных для заливки!
COLLECTIONS = {
    "pers": "dump/pw1/pers.bson",
    "guilds": "dump/pw1/guilds.bson",
}
