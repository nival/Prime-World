# -*- encoding: utf8 -*-
import sys
import argparse
import codecs
import ujson
from pymongo import Connection as MongoClient
from pymongo.cursor import Cursor
import sys, traceback
import logging
HOST = "b698.nivalnetwork.com"
PORT = 27017
info = logging.info
error = logging.error

def printException(exceptionInfoList):
    exceptionType, exceptionValue, exceptionTraceback = exceptionInfoList
    strList = traceback.format_exception(exceptionType, exceptionValue, exceptionTraceback)
    error("catch: " + (''.join(strList)))

def getCollection():
    info("connecting to %r:%r", HOST, PORT)
    client = MongoClient(HOST, PORT)
    db = client.sa9080
    return db.friends

def dump(auid, dump):
    info("dumping for auid %r to %r", auid, dump)
    try:
        coll = getCollection()
        curs = coll.find({'auid':auid})
        res = {"auid":[], "friend_auid": []}
        for x in curs:
            res["auid"].append(x)

        curs = coll.find({'friend_auid':auid})
        for x in curs:
            res["friend_auid"].append(x)

        fp = codecs.open(dump,'w', encoding="utf8")
        fp.write(ujson.dumps(res))
        fp.close()
    except Exception:
        printException(sys.exc_info())

def delete(auid, delauids, excludeauids="", isAll=False):
    info("removing for auid %r delauids %r excludeauids %r isAll %r", auid, delauids, excludeauids, isAll)
    coll = getCollection()

    if isAll and not excludeauids:
        try:
            coll.remove({"auid": auid})
            coll.remove({"friend_auid": auid})
        except Exception:
            printException(sys.exc_info())

    elif isAll and excludeauids:
        excludeauids = [long(x) for x in excludeauids.split(',')]
        print excludeauids
        coll.remove({'friend_auid':{"$nin" : excludeauids}, "auid": auid})
        coll.remove({'auid':{"$nin" : excludeauids}, "friend_auid": auid})
    elif isAll and delauids:
        auids = [long(x) for x in delauids.split(',')]
        coll.remove({'friend_auid':{"$in" : auids}, "auid": auid})
        coll.remove({'auid':{"$in" : auids}, "friend_auid": auid})


def load(auid, fname):
    info("loading for auid %r from %r", auid, fname)
    coll = getCollection()
    fp = codecs.open(fname,'r', encoding="utf8")
    data = ujson.loads(fp.read())
    fp.close()
    for k, v in data.iteritems():
        for rec in v:
            try:
                coll.insert(rec)
            except Exception:
                printException(sys.exc_info())
                continue

if __name__ == "__main__":
    logging.basicConfig(filename='manage_sa_friends.log', level=logging.INFO ,format='%(asctime)s %(levelname)s:%(message)s')

    parser = argparse.ArgumentParser(prog = 'manage_sa_friends', argument_default=argparse.SUPPRESS)
    parser.add_argument('--auid', help = "User's auid", type=int, default=0)
    parser.add_argument('--dump', help = "Dump user's friends", type=str, default='' )
    parser.add_argument('--delauids', help="Remove user's friends. You need to give list of auids. Format list of auids: 1,2,3,4",
         type=str, default='' )
    parser.add_argument('--delall', help="Remove all user's friends", action="store_true", default=False)
    parser.add_argument('--excludeauids', help="Exclude auids Format list of excludeauids: 1,2,3,4", type=str, default="")

    parser.add_argument('--load', help = "Load user's friends", type=str, default=''  )
    args = parser.parse_args()

    print args
    if not args.auid:
        parser.print_help()
        sys.exit(0)

    if args.dump:
        dump(args.auid, args.dump)
    elif args.delauids:
        delete(args.auid, args.delauids)
    elif args.delall and args.excludeauids:
        delete(args.auid, args.delauids, excludeauids=args.excludeauids, isAll=True)
    elif args.delall:
        delete(args.auid, '', '', isAll=True)
    elif args.load:
        load(args.auid, args.load)
    else:
        parser.print_help()
        sys.exit(0)


