# -*- coding: cp1251 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2012, Nival Network

##----------------------------------------------------------------------------------------------------------------------
## ������������� (�������) ����� ���������, �� ������� ����� �������� ������� �������
COORDINATOR_BALANCER_EXTERNAL = "127.0.0.1:88"

##----------------------------------------------------------------------------------------------------------------------
## ������������� (�������) ����� ���������, �� ������� �� SSL ����� �������� �������, � ��������� � PW Connect
COORDINATOR_BALANCER_PWCONNECT = "127.0.0.1:888"

##----------------------------------------------------------------------------------------------------------------------
## ���������� (��������) ����� ���������, �� ������� ����� �������� ������ ������� �������� (��������, ����� ������� �� ��������� �������� �� ���� �� ���-������)
COORDINATOR_BALANCER_INTERNAL = "127.0.0.1:8888"


##----------------------------------------------------------------------------------------------------------------------
## ��������� "�������� ��������" [name] -> server_id, port...
COORDINATOR_WS_SERVERS = {
    "ein": { "addr":"127.0.0.1:8811", "on":1, "ka":0 },
    "zwei": { "addr":"127.0.0.1:8812", "on":1, "ka":0 },
}

##----------------------------------------------------------------------------------------------------------------------
## ���������� ��������� sql-��������
COORDINATOR_SQL_CONFIG = [
    { "sql_host":"localhost:3306", "sql_base":"se1", "sql_user":"se", "sql_pass":"sedata" },
]

##----------------------------------------------------------------------------------------------------------------------
## ������ events-�������� (��� ������ ���������� ��� �������� high-severity ����� �� http)
COORDINATOR_EVENT_SERVICES = [ "127.0.0.1:8722" ]

##----------------------------------------------------------------------------------------------------------------------
## ���������� ������� �����/���������
COORDINATOR_HTTP_CURL_WORKERS = 32
COORDINATOR_HTTP_CURL_CONNECTIONS = 16

COORDINATOR_SQL_THREADS = 2

COORDINATOR_HTTP_REQUEST_LIMIT = 256

COORDINATOR_FRIEND_SERVICES = [ "127.0.0.1:8714", "127.0.0.1:8715" ]
COORDINATOR_GUILD_SERVICES = [ "127.0.0.1:8718", "127.0.0.1:8719" ]
