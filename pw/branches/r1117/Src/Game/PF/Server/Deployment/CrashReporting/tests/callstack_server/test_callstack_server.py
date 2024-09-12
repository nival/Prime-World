import os
import sys
import urllib2
import json
from poster.encode import multipart_encode
from poster.streaminghttp import register_openers

if not len(sys.argv) > 1:
    sys.stderr.write('Usage: %s <dump_file>\n' % os.path.split(sys.argv[0])[1])
    sys.exit(1)
register_openers()
CALLSTACK_SERVER = 'http://pw.SITE.com:8080/upload'
DUMP_FILE = sys.argv[1]
datagen, headers = multipart_encode({"crashreport": open(DUMP_FILE, "rb")})
request = urllib2.Request(CALLSTACK_SERVER.encode('utf-8'), datagen, headers)
output = urllib2.urlopen(request, timeout=500).read()
output = json.loads(output)
print output