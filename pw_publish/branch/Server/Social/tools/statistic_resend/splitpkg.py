#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys, re, time, traceback
from collections import namedtuple
sys.path.append('thrift_pw/statistics/gen-py')
from StatisticCore.ttypes import * # LoginInfo, ...

ifname = 'collected-unsent'
ofname = 'splited-unsent'

linere = re.compile(r'^(\d+): (\w+): (\[.+\])')

outfile = open(ofname, "wt")
try:
    with open(ifname) as infile:
        for line in infile:
            m = linere.match(line)
            if m:
                p_id, tt, data_str = m.group(1,2,3)
                data = eval(data_str)
                for v in data:
                    print >>outfile, "%s: %s" % (tt, v)
            else:
                print "WARN: wrong line %s" % line,
except:
    print traceback.print_exc()
    
outfile.close()
