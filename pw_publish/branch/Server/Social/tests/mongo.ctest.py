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
from helpers import *

import pymongo

def main():
    from pymongo import Connection
    connection = Connection('ec2-50-16-18-0.compute-1.amazonaws.com', 27017)
    db = connection.test_db
    foo = db.foo
    
    print "connection:%s, db:%s, foo:%s" % (connection, db, foo)
    
    #~ foo.drop()
    foo.ensure_index("id")
    
    #~ tries = 10000
    #~ t0 = time.time()
    
    #~ for i in range(1,tries):
        #~ foo.insert( dict( id=i, name="user%d"%i, pwd="pwd%d"%i ) )
    
    #~ t1 = time.time()
    #~ tTotal = t1-t0    
    #~ print "add total time:%.4f (tries: %d), avg time: %.6f" % (tTotal, tries, tTotal/tries)
    
    tTotal = 0
    tries = 100
    for i in range(tries):
        randomId = random.randint(1,10000)
        
        t0 = time.time()
        res = foo.find( dict(id=randomId) )[0]
        t1 = time.time()

        #print "[%d] find: %s, time:%.4f" % ( randomId, res, t1-t0)
        
        tTotal += t1-t0
        
    print "find total time:%.4f (tries: %d), avg time: %.6f" % (tTotal, tries, tTotal/tries)
        
        
        
    
    
    
if __name__ == "__main__":
    main()

    