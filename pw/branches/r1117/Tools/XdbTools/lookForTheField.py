from os import path
import sys
import re
from xml.parsers.expat import ParserCreate
from codecs import open

class Visitor(object):
    def __init__(self):
        pass
    def __call__(self, file_name):
		fh = open(file_name, 'r', 'utf-8')
		text = fh.read()
		fh.close()
		found = re.findall(pattern, text)
		if print_all or len(found) > 0:
			print file_name
		for l in found:
			print l

def xdb_visit(visitor, dirname, names):
    for n in names:
        if n.endswith('xdb'):
            visitor(path.join(dirname, n))



pattern = re.compile(r'[\n\t]*<%s>(.*?)</%s>' % (sys.argv[1], sys.argv[1]), re.DOTALL | re.MULTILINE)

data_path = path.normpath(path.join(path.dirname(__file__), '../../Data'))

print_all = len(sys.argv) > 2 and sys.argv[2] == '--allxdbnames'

print data_path
path.walk(data_path, xdb_visit, Visitor())
print 'OK'