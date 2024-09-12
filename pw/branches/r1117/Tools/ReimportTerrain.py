#!python -w

import os
import os.path
import re
import string

dirname, root = map(os.path.abspath, [r'..\Data\Terrain\Elements', r'..\Data'])
root = re.compile(re.sub(r'\\', r'\\\\', root + '\\'))

result = []
for name in os.listdir(dirname):
  if re.compile(".stat.xdb", re.IGNORECASE).search(name):
    path = os.path.join(dirname, name)
    result.append(root.sub('', path))

os.system(r'cd ..\Bin && ..\Src\_Debug\PF_EditorC.exe import --fast ' + string.join(result, ' '))
