from os import path
import re
import sys
import pickle

formulaName = sys.argv[1]
fileName = sys.argv[2]

def xdb_visit(visitor, dirname, names):
    for n in names:
        if n.endswith('xdb'):
            visitor(path.join(dirname, n))

class Visitor(object):
    def __init__(self):
        pass
    def __call__(self, file_name):
		fh = open(file_name, 'r', 'utf-8')
		text = fh.read()
		fh.close()
		
		result = re.findall(r'[\n\t]*<%s>(.*?)</%s>' % ( formulaName, formulaName ), text, re.DOTALL | re.MULTILINE)

		for r in result:
			moStr = re.search(r'<sString>(.*?)</sString>', r, re.DOTALL)
			strVal = moStr.group(1)
			moCode = re.search(r'<compiledString>(.*?)</compiledString>', r, re.DOTALL)
			if moCode and len(moCode.group(1)) > 0:
				if strVal not in formulasDict:
					formulasDict[strVal] = moCode.group(1)

data_path = path.normpath(path.join(path.dirname(__file__), '../../../Data'))

# Load dictionary
if (not os.path.exists(fileName)):
	formulasDict = {}
else:
	f = open(fileName, "r")
	pickle.load(formulasDict, f)
	f.close()

# Perform walking
path.walk(data_path, xdb_visit, Visitor())

# Output dictionary
for iter in formulasDict.iteritems():
	print iter[0], iter[1]

# Save dictionary	
f = open(fileName, "w")
pickle.dump(formulasDict, f)
f.close()
