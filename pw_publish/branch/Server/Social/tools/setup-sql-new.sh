#!/bin/bash
PASSWORD="yoanCewseg9"
mysql -uroot --password=$PASSWORD <pw_12_full.sql
mysql -uroot --password=$PASSWORD <pw_exchange.sql
mysql -uroot --password=$PASSWORD <pw_stat_full.sql
mysql -uroot --password=$PASSWORD <pw_mirror_full.sql
#mysql -uroot --password=yoanCewseg9 <
