#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# (C) Danil "Eleneldil" Lavrentyuk, 2013-2014, Nival Network
#
# Configuration file for mysql_load.py
# All relative paths are based on the directory where mysql_load.py is located.

MYSQL_USER = 'root'
MYSQL_PASS = 'WRITE PASSWORD HERE!'

MYSQL_BIN = "C:\\Program Files (x86)\\MySQL\\MySQL Server 5.1\\bin\\mysql.exe"
#MYSQL_BIN = "C:\\Program Files\\MySQL\\MySQL Server 5.6\\bin\\mysql.exe"
MYSQL_OPTIONS = ('--default_character_set', 'utf8') # адрес, юзера, пароль и имя базы сюда не писать!

TABLES_DIR = 'dump/mysql' # путь, где расположены файлы таблиц

TABLE_FILES = (
    'tbl_brick.sql', 
    'tbl_broadcast.sql', 
    'tbl_ip_allowances.sql', 
    'tbl_log.sql',
    'tbl_login.sql', 
    'tbl_nick.sql', 
    'tbl_pwconnect.sql', 
    'tbl_servers.sql', 
    'tbl_user_restrictions.sql',
)
