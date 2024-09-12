from os import path
from copy import deepcopy
from codecs import open
import re
import sys
import pickle
import string

if len(sys.argv) < 2:
	print "Not enough arguments"
	sys.exit();

# Save parameters
structName = sys.argv[1]
fieldName = sys.argv[2]

formulasDict = {}
# Load dictionary
if (len(sys.argv) > 3):
	if (path.exists(sys.argv[3])):
		f = open(sys.argv[3], "r")
		formulasDict = pickle.load(f)
		f.close()
	
# Check replace formula
if (len(sys.argv) > 4):
	replaceFormula = sys.argv[4]
else:
	replaceFormula = ''

class StructParser(object):
	def __init__(self):
		self.count = 0
		self.pattern = re.compile(r'[\n\t]*<%s>(.*?)</%s>' % ( fieldName, fieldName ), re.DOTALL)
		pass
		
	def __call__(self, match_obj):
		text = match_obj.group(0) # Text to work with
		
		# Search for the field
		mo = re.search(self.pattern, text)
		if not mo:
			return text
			
		# Find compiled code for the formula
		formulaText = mo.group(1)
		if len(replaceFormula) > 0:
			formulaText = replaceFormula
		compiledFunc = ""
		if formulaText in formulasDict:
			compiledFunc = formulasDict[formulaText]
			print "Formula", formulaText, "with compilation found"
		else:
			print "ATTENTION! Formula", formulaText, "need to be compiled"
			
		# Make text
		offs = string.rfind(text, '\n', 0, mo.start(1))
		offs1 = string.rfind(text, '<', 0, mo.start(1))
		shiftString = text[offs:offs1]
		substText = shiftString + '<%s>' % fieldName
		substText += shiftString + '\t' + '<sString>%s</sString>' % formulaText
		substText += shiftString + '\t' + '<compiledString>%s</compiledString>' % compiledFunc
		substText += shiftString + '\t' + '<returnType>float</returnType>'
		substText += shiftString + '</%s>' % fieldName
		
		self.count += 1
		
		newText = text[:offs-1] + substText + text[mo.end(0):]
		return newText
		
		
class Visitor(object):
    def __init__(self):
        pass
    def __call__(self, file_name):
        print file_name
        fh = open(file_name, 'r', 'utf-8')
        text = fh.read()
        fh.close()

        pattern = re.compile(r'[\n\t]*<%s>(.*?)</%s>' % ( structName, structName ), re.DOTALL | re.MULTILINE)
        sp = StructParser()
        text = re.sub(pattern, sp, text)
        if sp.count:
            print sp.count, 'struct found total'
            fh = open(file_name, 'w', 'utf-8')
            fh.write(text)
            fh.close()

def xdb_visit(visitor, dirname, names):
    for n in names:
        if n.endswith('xdb'):
            visitor(path.join(dirname, n))

data_path = path.normpath(path.join(path.dirname(__file__), '../../../Data'))

print data_path
path.walk(data_path, xdb_visit, Visitor())
print 'OK'