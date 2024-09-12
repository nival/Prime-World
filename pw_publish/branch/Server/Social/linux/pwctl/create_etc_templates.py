#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import socket

fromPath='./etc/default/example/'
toPath="./etc/default/prepare/"
hostname=socket.gethostname()

if not os.path.exists(toPath):
    os.mkdir(toPath)

ip='127.0.0.1'
wk_dir = os.path.dirname(os.path.realpath('../../__file__'))

for i in os.listdir(fromPath):
    if i != 'prepare_etc.py' and os.path.isdir(i)==False:
        with open(fromPath+i) as f:
            to=toPath + os.path.splitext(os.path.basename(f.name))[0]
            print "try convert " + to
            with open(to, "wt+") as fout:
                for line in f:
                    line = line.replace('192.168.50.2',"{{ conf['ip'] }}")
                    line = line.replace('192.168.50.6',"{{ conf['ip'] }}")
                    line = line.replace('/var/log/pwlobby/',"{{ conf['logging'] }}")
                    line = line.replace('/opt/pwcastle',"{{ conf['rundir'] }}")
                    line = line.replace('PYTHON="/usr/bin/python"',"PYTHON=\"{{ conf[''] }}\"")
                    line = line.replace('v161',hostname)
                    fout.write(line)

# nginx
with open(wk_dir+'/linux/pwctl/nginx.conf') as f:
    to=wk_dir+'/linux/pwctl/pw.conf'
    print "nginx: try convert " + to
    with open(to, "wt+") as fout:
        for line in f:
            line = line.replace('192.168.50.2',"{{ conf['ip'] }}")
            line = line.replace('/var/log/pwlobby/',"{{ conf['logging'] }}")
            line = line.replace('/opt/pwcastle',"{{ conf['rundir'] }}")
            line = line.replace('listen       88;','listen       98;')
            line = line.replace('listen       888 default  ssl;','listen       888 default  ssl;')
            line = line.replace('listen       8888;','listen       8888;')
            fout.write(line)
