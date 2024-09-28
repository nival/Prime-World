import os, sys, binascii

if len(sys.argv) > 1:
  print binascii.crc32( sys.argv[1] )
