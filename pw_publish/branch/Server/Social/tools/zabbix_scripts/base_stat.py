#!/usr/bin/env python
# -"- coding: utf8 -"- 
# (C) Dmitry Kolb 2014, Nival Network 
__author__ = 'dmitry.kolb'
import os
import sys

def buildPath():
    path = os.path.dirname(os.path.abspath(__file__))
    spath = os.path.normpath(path).split(os.sep)
    del spath[-1]
    del spath[-1]
    p = os.sep.join(spath)
    sys.path.append(p)

buildPath()
from base.helpers import *

def parse_response(response, key, byname, bytype):
    path = key.split('/')
    val = path[-1]
    del path[-1]
    r = subFind(response, path, True)
    if r:
        value = r.get(val, None)
        if value is not None:
            if isinstance(value, list):
                if value:
                    print ",".join(value)
                else:
                    print []
            elif isinstance(value, dict):
                if value:
                    print ";".join("{0}:{1}".format(k, v) for k, v in value.iteritems())
                else:
                    print {}
            else:
                print value
        else:
            print 0
    else:
        print 0