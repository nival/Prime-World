# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network
import sys, os, time
import getopt
import pymongo
import urllib, urllib2
import gc

from binascii import crc32   # zlib version is not cross-platform

def utf8convert( value, encoding="utf8" ):
    if isinstance(value, unicode):
        return value.encode(encoding)
    else:
        return str(value)

# python sa_admin.py --dump_users --mongo_config="{\"mongo_addr\":\"127.0.0.1\",\"mongo_port\":27017,\"mongo_base\":\"sa\"}
# python sa_admin.py --dump_users=<filename> --mongo_config="{\"mongo_addr\":\"127.0.0.1\",\"mongo_port\":27017,\"mongo_base\":\"sa\"}"
MONGO_CONFIG = {"mongo_addr":"127.0.0.1","mongo_port":27017,"mongo_base":"sa"}
COLL_NAME = 'users'
ENCODING = "utf8"
            
# --------------------------------------

def dumpAggregatorUsers(filename):
    opt = MONGO_CONFIG
    connection = pymongo.Connection( opt["mongo_addr"], opt["mongo_port"])
    db = getattr(connection, opt["mongo_base"], None)
    dump_file = open(filename, "wb")
    dump_str = "auid;nickname;email;snid;snuid;\n"
    dump_file.write( dump_str )
    
    count = 0
    
    if db:
        coll = getattr(db, COLL_NAME, None )
        if coll:
            reply = coll.find()
            total = reply.count()
            print "(base %s) users find count: %s" % ( opt["mongo_base"], total )
            for user in reply:
                #print "user: %s" % user
                count += 1
                
                try:
                    auid = int( user.get("_id", 0) )
                    nickname = utf8convert( user.get("nick", ""), ENCODING )
                    
                    fsn = user.get("fsn", "fb")
                    sn_info = user.get(fsn, {})
                    snuid = sn_info.get("snuid", "")
                    email = utf8convert( sn_info.get("email", ""), ENCODING )
                    
                    dump_str = str(auid) + ";" + nickname + ";" + email + ";" + str(fsn) + ";" + str(snuid) + ";\n"
                    dump_file.write( dump_str )
                    
                except:
                    print "error dumping user: %r" % user
                    raise
                    
                if (count % 1000) == 0:
                    print "%d/%d... " % (count, total)
                
        else:
            print "ERROR, can't get collection %r" % COLL_NAME
    else:
        print "ERROR, can't connect to mongo base %r" % opt
            
# --------------------------------------

def main():
    gc.disable()
    
    arglist = sys.argv[1:]
    print "arglist: ", arglist
    opts, args = getopt.getopt( arglist, "", [
        "dump_users=", 
        "mongo_config=", "encoding="
    ] )
    
    # разбор предварительных параметров (настройки)
    for opt, arg in opts:
        if opt == "--mongo_config":
            global MONGO_CONFIG
            try:
                MONGO_CONFIG = json_loads(arg)
                print "parsed mongo_config: %s" % (MONGO_CONFIG)
            except:
                raise
                
        elif opt == "--encoding":
            global ENCODING
            try:
                ENCODING = arg
                print "parsed encoding: %s" % (ENCODING)
            except:
                raise

    for opt, arg in opts:
        if opt == "--dump_users":
            dumpAggregatorUsers(arg)
            
# --------------------------------------

if __name__ == "__main__":
    main()
    
