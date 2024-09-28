import json
import zlib
import sys 

f = open(sys.argv[1], 'rb')
text = f.read()
data = json.loads(text)
t = open(sys.argv[1]+'.txt', 'wb')
content = zlib.decompress(data['data'][4:].encode('latin1'))
data = json.loads(content)
t.write(json.dumps(data, indent=4))
