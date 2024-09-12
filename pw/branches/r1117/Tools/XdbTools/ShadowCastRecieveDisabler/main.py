import os
import sys
sys.path.append(os.path.abspath('..'))

import Xdb


def parseModels(full_path, files):
    o = Xdb._openLink(full_path)
    if o.has('Effect'):
        print 'parsing', full_path
        for item in o.Effect.effects:
            if item.model.model.href:
                files.append(str(item.model.model.href))
            if item.has('staticmodel'):    
                if item.staticmodel.model.href:
                    files.append(str(item.staticmodel.model.href))
                

if len(sys.argv) > 1:                    
    root = sys.argv[1]
    f = []
    for r, dirs, files in os.walk(root):
        for name in files:
            full_path = os.path.join(r, name)
            head, tail = os.path.splitext(full_path)
            if tail.lower() == '.xdb':
                parseModels(full_path, f)
    for _name in f:
        if _name[0] == '/':
            name = _name[1:]
        else:
            name = name
        path = os.path.join(root, name)
        head, tail = os.path.splitext(path)
        if tail.lower() != '.xdb':
            path += '.xdb'
        if os.path.isfile(path):
            f = open(path, 'rb')
            code = f.read()
            c = code.replace('<ShadowReciverPinValue>ShadowReciver</ShadowReciverPinValue>', '<ShadowReciverPinValue>None</ShadowReciverPinValue>')
            new_code = c.replace('<ShadowCasterPinValue>ShadowCaster</ShadowCasterPinValue>', '<ShadowCasterPinValue>None</ShadowCasterPinValue>')
            if code != new_code:
                print 'replacing', path
                f = open(path, 'wb')
                f.write(new_code)
                f.close()
        else:
            print 'Missed file', path
else:
    print 'Usage: <root>'