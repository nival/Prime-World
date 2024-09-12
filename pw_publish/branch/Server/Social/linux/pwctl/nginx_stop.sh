#!/bin/bash
/etc/init.d/nginx stop
ps ax -o pid,command | grep 'nginx -c pw.conf' | grep -v "grep" | awk '{print $1}' | xargs kill -9
ps ax -o pid,command | grep 'nginx' | grep -v "grep" | awk '{print $1}' | xargs kill -9
pstree -a | grep 'nginx -c pw.conf' | grep -v "grep"