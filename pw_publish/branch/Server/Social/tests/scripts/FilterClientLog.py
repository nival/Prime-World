import sys
from binascii import crc32
import fnmatch
import os
import shutil

for root, dirnames, filenames in os.walk( "./" ):
  for filename in fnmatch.filter(filenames, '*.log'):
    print filename
    logFileName = os.path.join( root, filename )
    print logFileName

    with open(logFileName) as f:
      content = f.readlines()
  
    hasFilter = False
    if len(sys.argv) > 1:
      newFilter = sys.argv[1]
      hasFilter = True

    filterLines = []
    for line in content:
      if line.find( "Send: " ) != -1:
        if not hasFilter or line.find( newFilter ) != -1:
          filterLines.append( line )
      elif line.find( "Packet: " ) != -1:
        if not hasFilter or line.find( newFilter ) != -1:
          filterLines.append( line )
          filterLines.append( "\n" )

    with open( os.path.join( root, 'result.txt'), 'w') as f:
      f.writelines(filterLines)