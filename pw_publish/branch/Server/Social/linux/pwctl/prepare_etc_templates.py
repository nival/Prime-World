#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys
import socket
import json
import re

sys.path.append(os.path.abspath('../../'))

from tornado import template

def noParse(x):
    return x

def Parse(fromPath, toPath):
    loader = template.Loader(fromPath)
    # template.execute(noParse=noParse)
    for i in os.listdir(fromPath):
        if i=='.svn':
            continue
        print fromPath+i
        t = loader.load(i).generate(conf=conf,noParse=noParse)
        #print t
        to=toPath + os.path.splitext(os.path.basename(fromPath+i))[0]
        print "try convert " + to
        fout=open(to, "wt+")
        fout.write(t)
        fout.close()

hostname=socket.gethostname()

try:
    json_data=open('config.json')
    json_str = json_data.read()
    json_data.close()
    json_str=re.sub(r'\n',r' ',json_str)
    conf = json.loads(json_str)
except IOError as e:
    print e
except ValueError as v:
    print v

if not os.path.exists(conf['toPath']):
    os.mkdir(conf['toPath'])

# print conf['mysql']
wk_dir = os.path.dirname(os.path.realpath('../../__file__'))
Parse(conf['fromPath'] + 'default/', conf['toPath'] + "default/prepare/")
Parse(conf['fromPath'] + 'init.d/', conf['toPath'] + "init.d/prepare/")

# nginx
loader = template.Loader(conf['fromPath'] + 'nginx/')
t = loader.load(wk_dir+'/linux/pwctl/etc_templates/nginx/nginx.alone.templates.conf').generate(conf=conf,noParse=noParse)
to= './pw.conf'
print "[SS] nginx conf save to:", to
fout=open(to, "wt+")
fout.write(t)
fout.close()

t = loader.load(wk_dir+'/linux/pwctl/etc_templates/nginx/nginx.templates.conf').generate(conf=conf,noParse=noParse)
to= './etc/nginx/nginx.conf'
print "[SS] nginx.conf conf save to:", to
fout=open(to, "wt+")
fout.write(t)
fout.close()

t = loader.load(wk_dir+'/linux/pwctl/etc_templates/nginx/nginx.ss.templates.conf').generate(conf=conf,noParse=noParse)
to= './etc/nginx/sites-enabled/ss.conf'
print "[SS] nginx conf save to:", to
fout=open(to, "wt+")
fout.write(t)
fout.close()

t = loader.load(wk_dir+'/linux/pwctl/etc_templates/nginx/nginx.sa.templates.conf').generate(conf=conf,noParse=noParse)
to= './etc/nginx/sites-enabled/sa.conf'
print "[SA] nginx conf save to:", to
fout=open(to, "wt+")
fout.write(t)
fout.close()