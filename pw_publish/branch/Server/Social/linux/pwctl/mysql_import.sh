#!/usr/bin/env sh

if [ -n "$1" ]
  then
    PASSWD=$1
  else
    echo "root password need \n"
    exit
fi

cd ../../tools
mysql -u root -p$PASSWD  < ../tools/pw_12_full.sql
#mysql -u root -p$PASSWD  < ../tools/pw_connect.sql
mysql -u root -p$PASSWD  < ../tools/pw_mirror_full.sql
mysql -u root -p$PASSWD  < ../tools/pw_exchange.sql
#mysql -u root -p$PASSWD  < ../tools/pw_procs.sql
mysql -u root -p$PASSWD  < ../tools/pw_stat_full.sql
#mysql -u root -p$PASSWD  < ../tools/pw.sql

echo "end\n"