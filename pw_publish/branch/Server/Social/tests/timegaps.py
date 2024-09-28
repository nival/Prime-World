# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2012, Nival Network

import time, gc, sys, getopt, logging

from logging import info, warning as warn

gc.disable()

def parseLogTimestamp(stamp):
    point_index = stamp.find(",")
    if point_index < 0:
        point_index = len(stamp)
        msec = 0
    else:
        msec = int( stamp[point_index+1:] )
    sTime = time.strptime( stamp[:point_index], "%Y-%m-%d %H:%M:%S" )
    result = time.mktime(sTime) + msec/1000.0
    return result
        
        
def parseFile(filename, gap_limit=0.1, ignore_strings=None):
    f = open(filename, "rt")
    prev_ts = 0
    prev_line = ""
    
    lines_total = 0
    lines_parsed = 0
    gap_count = 0
    
    ignored_counts = {}
    if ignore_strings:
        for ign in ignore_strings:
            ignored_counts[ign] = 0
            
    t1 = time.clock()
    
    for line in f:
        lines_total += 1
        if line[0] == "[":
            space1 = line.find(" ")
            if space1 >= 0:
                space2 = line.find(" ", space1+1)
                if space2 >= 0:
                    str_stamp = line[1:space2]
                    ts = parseLogTimestamp(str_stamp)
                    lines_parsed += 1
                    
                    if prev_ts and ts-prev_ts >= gap_limit:
                        is_ignore = 0
                        if ignore_strings:
                            for ign in ignore_strings:
                                if line.find(ign) >= 0:
                                    #~ print "found ignore substring %r; ignoring line: %s" % (ign, line)
                                    is_ignore = 1
                                    ignored_counts[ign] += 1
                                    break
                            
                        if not is_ignore:
                            print "GAP FOUND: %5.3f seconds\n-line1:%s-line2:%s" % (ts-prev_ts, prev_line, line)
                            gap_count += 1
                        
                    prev_ts = ts
                    prev_line = line
                #~ else:
                    #~ print "WARNING: no 2nd space, skipping line: %s" % line
            #~ else:
                #~ print "WARNING: no 1st space, skipping line: %s" % line
        #~ else:
            #~ print "WARNING: no [, skipping line: %s" % line
    
    t2 = time.clock()
    print "DONE.\n time spent: %5.3f \n lines total: %s \n lines parsed: %s \n gaps_count: %s \n ignored counts: %s" % (t2-t1, lines_total, lines_parsed, gap_count, ignored_counts)
    
def test():
    print "parsed: %5.3f" % parseLogTimestamp("2012-11-01 07:59:27,598")
    print "now: %5.3f" % time.time()

    t1 = time.clock()

    PASSES = 10000
    for i in xrange(PASSES):
        result = parseLogTimestamp("2012-11-01 07:59:27,598")

    t2 = time.clock()
    print "time spent: %5.3f (%5.5f per call)" % (t2-t1, (t2-t1)/PASSES)


def main():
    arglist = sys.argv[1:]
    print "arglist: ", arglist
    opts, args = getopt.getopt( arglist, "", ["file=", "gap=", "ignore="] )
    
    logging.basicConfig( level="info", format='[%(asctime)s %(levelname)8s] %(message)s' )
    
    # разбор предварительных параметров (настройки)
    GAP_LIMIT = 0.1
    IGNORE_STRINGS = []
    for opt, arg in opts:
        if opt == "--gap":
            GAP_LIMIT = float(arg)
            print "GAP_LIMIT=%5.3f seconds" % GAP_LIMIT
        elif opt == "--ignore":
            IGNORE_STRINGS = arg.split("::")
            print "IGNORE_STRINGS=%s" % IGNORE_STRINGS
            
    # исполняемые опции:
    for opt, arg in opts:
        if opt == "--file":
            parseFile(arg, gap_limit=GAP_LIMIT, ignore_strings=IGNORE_STRINGS)


#test()

main()

