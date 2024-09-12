# -*- coding: utf-8 -*-
#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, time, pickle, os

from base.helpers import *
from xdb.xml2obj import xml2obj

import tornado.options
from tornado.options import define, options

define("xdb_path", default="xdb", help="path to PW.Data folder")


def getStaticData( xdb_path ):
    info("Loading static data from %s" % os.path.realpath(xdb_path))
    StaticData, DBID = xml2obj(open(xdb_path, mode='r'))
    return StaticData, DBID


