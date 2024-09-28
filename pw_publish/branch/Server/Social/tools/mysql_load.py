#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# (C) Danil "Eleneldil" Lavrentyuk, 2013-2014, Nival Network
#
# This script loads SQL data into MySQL DB, specified in cfg/coord_cfg.py

import sys, os, os.path, subprocess, traceback, time, errno
import MySQLdb

if __name__ == '__main__':
    my_dir = os.path.dirname(sys.argv[0])
    if my_dir:
        os.chdir(my_dir)

sys.path.append('../cfg')
from coord_cfg import COORDINATOR_SQL_CONFIG as SQL_CONFIG
from mysql_load_cfg import *

if len(SQL_CONFIG) > 1:
    print >>sys.stderr, "MySQL DB sharding is not supported yet"
    sys.exit(1)
    
SQL_HOST, SQL_PORT = SQL_CONFIG[0]['sql_host'].split(':')
SQL_BASE = SQL_CONFIG[0]['sql_base']
SQL_USER = MYSQL_USER # from mysql_load_cfg.py     ### SQL_CONFIG[0]['sql_user']
SQL_PASS = MYSQL_PASS # from mysql_load_cfg.py     ### SQL_CONFIG[0]['sql_pass']

def check_mysql_binary():
    if not os.access(MYSQL_BIN, os.X_OK):
        print >>sys.stderr, "Can't execute MySQL client '%s'" % MYSQL_BIN
        sys.exit(1)

def check_data_path():
    if not os.access(TABLES_DIR, os.X_OK):
        print >>sys.stderr, "Can't execute MySQL client '%s'" % MYSQL_BIN
        sys.exit(1)

def call_mysql(fname, params):
    try:
        f = open(fname, 'r')
        retcode = subprocess.call(params, bufsize=1, stdin=f)
        f.close()
    except Exception:
        traceback.print_exc()
        return False
    return True

def check_file(fname):
    if not os.access(fname, os.R_OK):
        print "Can't access", fname
        return False
    return True

def fix_tables():
    """
    1. Очищаем tbl_servers
    2. Сбрасываем в 0 колонку server_id в tbl_login
    """
    print "Fixing tales..."
    db = MySQLdb.connect(host=SQL_HOST, port=int(SQL_PORT), user=SQL_USER, passwd=SQL_PASS, db=SQL_BASE)
    cr = db.cursor()
    print "Clearing `tbl_servers`"
    cr.execute("DELETE FROM `tbl_servers`")
    print "Clearing `server_id` column in `tbl_login`"
    cr.execute("UPDATE `tbl_login` SET `server_id` = 0")
    cr.close()
    db.commit()
    

if __name__ == '__main__':
    check_mysql_binary()
    check_data_path()
    SQLS = tuple(os.path.join(TABLES_DIR, fn) for fn in TABLE_FILES)
    if tuple(None for fname in SQLS if not check_file(fname)):
        sys.exit(1)
    params = (MYSQL_BIN, '--host', SQL_HOST, '--port', SQL_PORT, '--user', SQL_USER, '-p'+SQL_PASS) + MYSQL_OPTIONS + (SQL_BASE, )
    print "Running:", ' '.join(params)
    for fname in SQLS:
        print "\tfor", fname
        if not call_mysql(fname, params):
            print >>sys.stderr, "Data load interrupted on file %s" % fname
            break
    fix_tables()

# сообщение Warning: Using a password on the command line interface can be insecure. - игнорировать