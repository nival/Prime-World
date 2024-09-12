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
_addPath( r'../tornado')
from helpers import *

import tornado.database # sql query result as iterator

def main():
    #db = tornado.database.Connection('ec2-50-16-18-0.compute-1.amazonaws.com:3306', 'pw1', 'pw', 'pwdata')
    db = tornado.database.Connection('ip-10-244-41-155.ec2.internal:3306', 'pw1', 'pw', 'pwdata')
    print "db:%s" % ( str(db) )

    db.execute('TRUNCATE TABLE tbl_brick')
    
    tries = 10
    t0 = time.time()
    
    for i in range(1,tries):
        db.execute( "INSERT INTO tbl_brick (key,data) VALUES(%r,%r)" % ( "user_%d"%i, "pwd%d"%i ) )
    
    t1 = time.time()
    tTotal = t1-t0    
    print "insert total time:%.4f (tries: %d), avg time: %.6f" % (tTotal, tries, tTotal/tries)
    
    tTotal = 0
    tries = 10
    for i in range(tries):
        randomId = random.randint(1,10)
        
        t0 = time.time()
        res = db.query( "SELECT * FROM tbl_brick WHERE key=%r" % ( "user_%d"%randomId ) )
        t1 = time.time()

        print "[%d] select: %s, time:%.4f" % ( randomId, str(res), t1-t0)
        
        tTotal += t1-t0
        
    print "select total time:%.4f (tries: %d), avg time: %.6f" % (tTotal, tries, tTotal/tries)
                
        
    
    
    
if __name__ == "__main__":
    main()

    