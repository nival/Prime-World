# -*- coding: utf-8 -*-
__author__ = 'danil.lavrentyuk'
import sys
import socket

if len(sys.argv) < 2:
    print "No argument! URL required."
    sys.exit(1)

import urllib2

# в аргументе должен лежать нормальный http://address
try:
    response = urllib2.urlopen(sys.argv[1], timeout=5)
    print "http response:", response.read()
except socket.timeout:
    print "HTTP request timed out!"


