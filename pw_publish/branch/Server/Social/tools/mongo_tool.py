#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# (C) Danil "Eleneldil" Lavrentyuk, 2013-2014, Nival Network
#
#FIXME: поправить описание!!! (вместе с другими правками, чтобы закоммитить в задачу)
# This script calls mongo index creation script appied to DB, specified in cfg/coord_cfg.py

"""
Использует mongo_cfg.py в текущем каталоге, который, в свою очередь, 
подгружает ../cfg/coord_cfg.py, из которого берёт адрес и порт сервера.

!!! Пока что большинство операций рассчитаны на то, что у нас используется
только один экземпляр сервера, и что в нём для SS используется только один
экземпляр базы. !!!

Доступные операции:
    start - запуск сервера, как указано в coord_cfg.py
    load  - загрузка в базу данных коллекций pers и guilds (настраивается в mongo_cfg.py), 
            затем выполняет fix
    fix   - (пере)создаёт необходимые индексы
    dump  - сохраняет дамп базы соцсервера (не реализовано)
    shell - запускает командный интерфейс mongo с соединением с базой соцсервера
    
Все настройки - в mongo_cfg.py, который также подгружает ../cfg/coord_cfg.py ради адреса и имени базы.
В частности, в настройках указывается, использовать ли 64- иил 32-битную версию mongo.
"""

import sys, os, os.path, subprocess, traceback, time, errno
import mongo_cfg as cfg

server_proc = None

def check_cfg(operation, single_only=True, check_load=False):
    try:
        if single_only and not cfg.SINGLE_BASE:
            raise EnvironmentError("Multiple DB instances not supported for %s operation!" % operation)
        for name in ('MONGO_ADDR', 'MONGO_PORT', 'MONGO_BASE'):
            if not getattr(cfg, name):
                raise EnvironmentError("Empty configuration parameter %s" % name)
        if not os.access(cfg.MONGO_CLIENT, os.X_OK):
            raise OSError("Mongo client %s doen't exists  or isn't executable" % cfg.MONGO_CLIENT)
        if check_load:
            if not os.access(cfg.MONGO_LOAD, os.X_OK):
                raise OSError("Mongo restore tool %s doen't exists or isn't executable" % cfg.MONGO_LOAD)
            for collection, path in cfg.COLLECTIONS.iteritems():
                if not os.access(path, os.R_OK):
                    raise OSError("Files %s doesn't exists or isn't readable" % path)
    except OSError as e:
        print >>sys.stderr, e
    except  AttributeError as e:
        print >>sys.stderr, "Configuration error:", e
    except EnvironmentError as e:
        print >>sys.stderr, "Configuration error:", e
    else:
        print "Configuration OK"
        return
    sys.exit(1)

    
def load_data(collection, out, err):
    rettcode = 0
    if not cfg.COLLECTIONS.get(collection, None):
        print >>sys.stderr, "WARNING: Collection %s not configured, skipped" % collection
        return
    try:
        fname = cfg.COLLECTIONS[collection]
        if not os.access(fname, os.X_OK):
            print >>sys.stderr, "WARNING: Collection %s data file '%s' not found. Skipped." % (collection, fname)
            return
        args = (cfg.MONGO_LOAD,
            '--host', cfg.MONGO_ADDR, 
            '--port', str(cfg.MONGO_PORT), 
            '--db', cfg.MONGO_BASE,
            '--drop',
            fname)
        print "Loading %s data" % collection
        print "Call: ", ' '.join(args)
        retcode = subprocess.call(args, bufsize=1, stdout=out, stderr=err)
    except Exception:
        traceback.print_exc()
    else:
        if retcode < 0:
            print >>sys.stderr, "ERROR: Mongo restore tool has been terminated by signal", -retcode
        elif retcode > 0:
            print >>sys.stderr, "ERROR: Mongo restore tool returned", retcode
        print "OK"

        
def try_read_lock(fname):
    try:
        open(fname).readline()
    except IOError as e:
        if e.errno == errno.EACCES:
            return False
        raise
    return True


def check_server():
    if cfg.MONGO_ADDR not in ("localhost", "127.0.0.1"):
        print "Server is not local, existance check skipped"
        return
    lockfile = getattr(cfg, 'MONGO_LOCK', '')
    if not lockfile:
        print "No lock file name configured, can't check server existance"
        return
    if os.access(lockfile, os.F_OK) and not (os.access(lockfile, os.R_OK) and try_read_lock(lockfile)):
        print "Mongo server already started"
    else:
        run_server()


def run_server():
    if not getattr(cfg, 'MONGO_LOG', ''):
        print >>sys.stderr, "Can't run mongo server: no MONGO_LOG"
        sys.exit(1)
    print "Starting server..."
    global server_proc
    server_proc = subprocess.Popen((cfg.MONGOD, '--dbpath', cfg.MONGO_DB_PATH, '--logpath', cfg.MONGO_LOG, '--logappend'))
    time.sleep(1)
    server_proc.poll()
    if server_proc.returncode is not None:
        print >>sys.stderr, "Can't start server. Return code:", server_proc.returncode
        sys.exit(1)
    print "Server PID:", server_proc.pid


def stop_if_server():
    if server_proc:
        print "Stopping server"
        call_mongo_client('admin', '--eval', 'printjson(db.shutdownServer())')
        server_proc.wait()
        print >>sys.stderr, "Server retcode:", server_proc.returncode


def call_mongo_client(db, *args, **call_args):
    try:
        retcode = subprocess.call((cfg.MONGO_CLIENT, '--host', cfg.MONGO_ADDR, '--port', str(cfg.MONGO_PORT), db) + args, **call_args)
    except Exception:
        print >>sys.stderr, "Execution failed:", traceback.format_exc()
    else:
        if retcode < 0:
            print >>sys.stderr, "ERROR: Mongo client has been terminated by signal", -retcode
        elif retcode > 0:
            print >>sys.stderr, "ERROR: Mongo client returned", retcode
        print "OK"


def fix(script=cfg.MONGO_FIX_SCRIPT):
    dbs = (cfg.MONGO_BASE,) if cfg.SINGLE_BASE else cfg.MONGO_BASE
    for dbname in dbs:
        print "Fixing db", dbname
        try:
            call_mongo_client(dbname, script)
        except Exception, e:
            print >>sys.stderr, "Execution failed:", e

        
def load():
    check_cfg("load", check_load=True)
    drop()
    check_server()
    try:
        out = None if cfg.LOG_FILE is None else open(cfg.LOG_FILE, "w") 
        err = None if cfg.ERROR_FILE is None else open(cfg.ERROR_FILE, "w")
        for name in cfg.COLLECTIONS.iterkeys():
            load_data(name, out, err)
    finally:
        if out:
            out.close()
        if err:
            err.close()
    fix()
    stop_if_server()

def load_other():
    check_cfg("load_other", check_load=True)
    check_server()
    try:
        out = None if cfg.LOG_FILE is None else open(cfg.LOG_FILE, "w") 
        err = None if cfg.ERROR_FILE is None else open(cfg.ERROR_FILE, "w")
        load_data('sieges', out, err)
        load_data('quests', out, err)
        load_data('techs', out, err)
        load_data('pgreq', out, err)
    finally:
        if out:
            out.close()
        if err:
            err.close()
    fix("mongo_other.js")
    stop_if_server()

def dump():
    print "--dump isn't implevented yet, sorry."

def drop():
    check_cfg("drop")
    stop_if_server()
    for x in os.listdir(cfg.MONGO_DB_PATH):
        try:
            p = os.path.join(cfg.MONGO_DB_PATH, x)
            if os.path.exists(p) and os.path.isfile(p):
                print "Removing of the file %s" % p
                os.remove(p)
            elif os.path.exists(p):
                print "Removing of the folder %s" % p
                os.rmdir(p)
        except Exception:
            traceback.print_exc()
            continue

    
if __name__ == '__main__':
    os.chdir(os.path.dirname(sys.argv[0]))
    if len(sys.argv) > 1:
        if sys.argv[1] == 'start':
            check_cfg("start")
            run_server()
            server_proc.wait()
        elif sys.argv[1] == 'load':
            load()
        elif sys.argv[1] == 'load-other': # version 10.1 qa deployment hotfix
            load_other()
        elif sys.argv[1] == 'dump':
            dump()
        elif sys.argv[1] == 'fix':
            check_cfg("fix")
            check_server()
            fix()
            stop_if_server()
        elif sys.argv[1] == 'shell':
            check_cfg("shell")
            check_server()
            call_mongo_client(cfg.MONGO_BASE, stdin=sys.stdin)
            stop_if_server()
        elif sys.argv[1] == 'drop':
            drop()
            stop_if_server()
        else:
            print >>sys.stderr, "Unknown command: %s", sys.argv[1]
            sys.exit(1)
    else:
        print >>sys.stderr, """Usage: python %s COMMAND
Commands:
\tstart -- start mongo server here
\tfix   -- fix indexes
\tload  -- load previously dumped data into mongo db
\tdump  -- dump current database content
\tshell -- run mongo shell
All commands use mongo_cfg.py 
"""
        sys.exit(1)

# Монго-запрос для поиска дупликатов пользователя в базе (если после наката дампа базы не строятся индексы)
# При этом для разруливания проблемы надо временно построить неуникальные индексы вместо уникальных,
# иначе операции поиска и удаления по ключу будут оооочень долгие.
# db.pers.aggregate([
# { $group: {_id: "$key",count: { $sum: 1 } } },
# { $match: {count: { $gt: 1 }} },
# { $project: {key: "$key", name: "$key", count: 1}}
# ])
