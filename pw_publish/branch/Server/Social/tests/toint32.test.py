# -*- coding: utf-8 -*-

import socket, ssl, pprint, time, sys, os
import hashlib
import urllib2
import random
import logging

os.chdir('..')
sys.path.append('.')

from base.helpers import *

def test_convert( str_x ):
    x = toint32( str_x )
    j = json_dumps({"key":x})
    uj = json_loads(j)
    assert( uj.get("key") == x )
    print "toint32(%s)=%r (type %s), json:%s, unjson:%s" % (str_x, x, x.__class__, j, uj)
    return x

x = test_convert( "4431531070" )
assert( x == 0 )

x = test_convert( "2431531070" )
assert( x == 0 )

x = test_convert( "-2431531070" )
assert( x == 0 )

x = test_convert( 0xFFFFFFFF )
assert( x == 0 )

x = test_convert( -0x7FFFFFFF-1 )
assert( x == -0x7FFFFFFF-1 )

x = test_convert( "2131531070" )
assert( x == 2131531070 )

x = test_convert( 0x7FFFFFFF )
assert( x == 0x7FFFFFFF )

x = test_convert( "-2131531070" )
assert( x == -2131531070 )

