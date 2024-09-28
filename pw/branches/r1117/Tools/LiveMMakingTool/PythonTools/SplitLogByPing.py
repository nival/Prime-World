import sys
import json
import random

print 'Matchmaking json log splitter'
if len(sys.argv) < 3:
  print 'Too few arguments!'
  quit()

infn = sys.argv[1]
outfn = sys.argv[2]

print 'Input file: ' + infn
print 'Output file: ' + outfn

f = open(infn, 'rb')
fout = open(outfn, 'wb')

for _line in f.readlines():
    line = _line.replace('\r', '').replace('\n', '')
    if line.startswith('{ "RequestQueued":'):
        d = json.loads(line)
        members = d["RequestQueued"]["members"]
        for member in members:
            addon = []
            for ping in member["pings"]:
                if ping["us0"] > 150:
                    addon.append( {'eu0' : random.randint(25, 125) } )
                else:     
                    addon.append( {'eu0' : random.randint(151, 300) } )
            member["pings"].extend(addon)    
        line = json.dumps(d)
	line += '\n'
    fout.write(line)
