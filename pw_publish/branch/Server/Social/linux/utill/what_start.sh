#!/usr/bin/env bash

#if ( length($0)<3 &&

PORT=8901
echo -e "\nMemcached 1 PORT:$PORT ..."
netstat -anp | grep $PORT | awk '{if ($0 ~ /memcached/) myprint = "..." $6 $7 " - OK"; print myprint} END {if ($0 !~ /memcached/ ) print "error"; else print myprint;}'
echo -e "\n\n"

PORT=8902
echo -n "Memcached 2 PORT:$PORT ..."
netstat -anp | grep $PORT | awk '{if ($0 ~ /memcached/) myprint = "..." $6 $7 " - OK"; print myprint} END {if ($0 !~ /memcached/ ) print "error"; else print myprint;}'
echo -e "\n\n"

PORT=11211
echo -n "main Memcached server PORT:$PORT ..."
netstat -anp | grep $PORT | awk '{if ($0 ~ /memcached/) myprint = "..." $6 $7 " - OK"; print myprint} END {if ($0 !~ /memcached/ ) print "error"; else print myprint;}'
echo -e "\n\n"

PORT=28017
echo -n "Mongo PORT:$PORT ... "
netstat -anp | grep $PORT | awk '{if ($0 ~ /mongod/) myprint = "..." $6 $7 " - OK"; print myprint} END {if ($0 !~ /mongod/ ) print "error"; else print myprint;}'
echo -e "\n\n"

echo -e "***********************************************************************\n"

PORT=8700
echo -e "Coordinator PORT:$PORT ...\n"
#netstat -anp | grep $PORT | awk '{if ($0 ~ /python/) myprint = "..." $4 $5 " - OK"; print myprint} END {if ($0 !~ /python/ ) print "error"; else print myprint;}'
netstat -anp | awk "/$PORT/"'{print "..." $3 $4}'

echo -e "\n\n"

PORT=8702
echo -n "Match maker PORT:$PORT ..."
netstat -anp | grep $PORT | awk '{if ($6 ~ /python/ || $7 ~ /python/ ) print "..." $6 " - OK"; $my=1;} END {if ($my!=1) print "error" }'
echo -e "\n\n"

PORT=8801
echo -n "WServer 1 PORT:$PORT ..."
netstat -anp | grep $PORT | awk '{if ($6 ~ /python/ || $7 ~ /python/ ) print "..." $6 " - OK"; $my=1;} END {if ($my!=1) print "error" }'
echo -e "\n\n"

PORT=8802
echo -n "WServer 2 PORT:$PORT ..."
netstat -anp | grep $PORT | awk '{if ($6 ~ /python/ || $7 ~ /python/ ) print "..." $6 " - OK"; $my=1;} END {if ($my!=1) print "error" }'
echo -e "\n\n"