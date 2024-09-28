# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time # json, re, hashlib, urllib, httplib, logging

# чтобы питон правильно понимал относительные пути модулей:
def _addPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)

_addPath( r'..')
_addPath( r'../base')
_addPath( r'../libs/memcache')
from helpers import *

import memcache


def main():
    #servers = ['ec2-50-16-18-0.compute-1.amazonaws.com:8901', 'ec2-50-16-18-0.compute-1.amazonaws.com:8902']
    servers = ['ip-10-244-41-155.ec2.internal:8901', 'ip-10-244-41-155.ec2.internal:8902']

    mc = memcache.Client(servers)
    
    print "mc:%s" % ( str(mc) )
    
    mc.flush_all()
    
    tries = 1000
    t0 = time.time()
    
    for i in range(1,tries):
        mc.set( "user_%d"%i, "pwd%d"%i )
    
    t1 = time.time()
    tTotal = t1-t0    
    print "set total time:%.4f (tries: %d), avg time: %.6f" % (tTotal, tries, tTotal/tries)
    
    tTotal = 0
    tries = 100
    for i in range(tries):
        randomId = random.randint(1,10)
        
        t0 = time.time()
        res = mc.get( "user_%d"%randomId )
        t1 = time.time()

        print "[%d] get: %s, time:%.4f" % ( randomId, str(res), t1-t0)
        
        tTotal += t1-t0
        
    print "get total time:%.4f (tries: %d), avg time: %.6f" % (tTotal, tries, tTotal/tries)
                
        
    
    
    
if __name__ == "__main__":
    main()

    