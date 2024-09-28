#!/bin/bash
NGINX=$(nginx -c pw.conf)
echo $NGINX
/etc/init.d/nginx start