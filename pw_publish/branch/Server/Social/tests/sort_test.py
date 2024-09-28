#!/usr/bin/env python
# -*- coding: utf-8 -*-

import urllib, ujson, json, sys, zlib, gzip, cStringIO, os, gc, random

# чтобы питон правильно понимал относительные пути модулей:
def _addPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)

os.chdir('..')
_addPath('.')
from base.helpers import *

servers = {
"one": 1,
"two": 1,
"three": 1,
}

servers2 = {
"three": 1,
"two": 1,
"one": 1,
}

servers3 = {
    "one": { "addr":"192.168.78.4:8008", "on":1, "ka":0, "max_users":1100 },
       "two": { "addr":"192.168.78.5:8008", "on":1, "ka":0, "max_users":1100  },
       "three": { "addr":"192.168.78.6:8008", "on":1, "ka":0, "max_users":1100  },
       "four": { "addr":"192.168.78.4:8009", "on":1, "ka":0, "max_users":1100  },
       "five": { "addr":"192.168.78.5:8009", "on":1, "ka":0, "max_users":1100  },
       "six": { "addr":"192.168.78.6:8009", "on":1, "ka":0, "max_users":1100  },
       "seven": { "addr":"192.168.78.4:8010", "on":1, "ka":0, "max_users":1100  },
       "eight": { "addr":"192.168.78.5:8010", "on":1, "ka":0, "max_users":1100  },
       "nine": { "addr":"192.168.78.6:8010", "on":1, "ka":0, "max_users":1100  },
       "ten": { "addr":"192.168.78.4:8011", "on":1, "ka":0, "max_users":1100  },
       "eleven": { "addr":"192.168.78.5:8011", "on":1, "ka":0, "max_users":1100  },
       "twelve": { "addr":"192.168.78.6:8011", "on":1, "ka":0, "max_users":1100  },
       "thirteen": { "addr":"192.168.78.4:8012", "on":1, "ka":0, "max_users":1100  },
       "fourteen": { "addr":"192.168.78.5:8012", "on":1, "ka":0, "max_users":1100  },
       "fifteen": { "addr":"192.168.78.6:8012", "on":1, "ka":0, "max_users":1100  },
       "sixteen": { "addr":"192.168.78.4:8013", "on":1, "ka":0, "max_users":1100  },
       "seventeen": { "addr":"192.168.78.5:8013", "on":1, "ka":0, "max_users":1100  },
       "eighteen": { "addr":"192.168.78.6:8013", "on":1, "ka":0, "max_users":1100  },
       "nineteen": { "addr":"192.168.78.4:8014", "on":1, "ka":0, "max_users":1100  },
       "twenty": { "addr":"192.168.78.5:8014", "on":1, "ka":0, "max_users":1100  },
       "twentyone": { "addr":"192.168.78.6:8014", "on":1, "ka":0, "max_users":1100  },
       "twentytwo": { "addr":"192.168.78.4:8015", "on":1, "ka":0, "max_users":1100  },
       "twentythree": { "addr":"192.168.78.5:8015", "on":1, "ka":0, "max_users":1100  },
       "twentyfour": { "addr":"192.168.78.6:8015", "on":1, "ka":0, "max_users":1100  },    

}
print "first UNsorted (1):", getFirstPair(servers)
print "first UNsorted (2):", getFirstPair(servers2)

print "first sorted (1):", getFirstSortedPair(servers)
print "first sorted (2):", getFirstSortedPair(servers2)
print "first sorted (3):", getFirstSortedPair(servers3)

#~ servers = {
#~ "one": 1,
#~ "two": 1,
#~ "three": 1,
#~ "four": 1,
#~ "five": 1,
#~ "six": "123",
#~ "seven": { 1: 1},
#~ "eight": 1,
#~ "nine": 1,
#~ "ten": 1,
#~ "eleven": 1,
#~ "twelve": 1,
#~ "thirteen": 1,
#~ "fourteen": 1,
#~ "fifteen": 1,
#~ "sixteen": 1,

#~ #"485159027": 1,
#~ }


json_servers = json_dumps( servers )
unjson_servers = json_loads( json_servers )

for name,value in unjson_servers.iteritems():
	print "name=", name
	break



#~ for i in xrange(10000):

	#~ key = str( random.randint(1000000,999999999) )
	#~ servers[key] = 1
	
	#~ for name,value in servers.iteritems():
		#~ if name == key:
			#~ print "name=", name
			#~ exit(0)
		#~ break
		
	#~ servers.pop( key )
	