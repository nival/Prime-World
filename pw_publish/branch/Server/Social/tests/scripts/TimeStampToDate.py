import os, sys, datetime

if len(sys.argv) > 1:
  d = datetime.datetime.fromtimestamp( int(sys.argv[1]) )
  print d.ctime()
