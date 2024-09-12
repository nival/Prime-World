from os import path
from copy import deepcopy
import re
from xml.parsers.expat import ParserCreate
from codecs import open
from collections import defaultdict
import uuid
import cgi

# use this function to get ids for nodes
def GetId_GUID():
    return str(uuid.uuid1())

#def cmpIgnoreCase(x, y):
#    if type(x) is tuple:
#        return cmp(x[0].lower(), y[0].lower())
#    return cmp(x.lower(), y.lower())

class Node(object):
    def __init__(self, name):
        self.name = name
        self.attrs = {}
        self.children = defaultdict(lambda : [])
        self.data = ''
        self.parent = None

    def __getitem__(self, key):
        return self.children[key]

    def __setitem__(self, key, child):
        child.parent = self
        self.children[key].append(child)

    def __delitem__(self, key):
        del self.children[key]

    def to_xml(self, level = 0):
        res = '\n' + level * 8 * ' ' + '<' + str(self.name)
        res = '\n' + level * '\t' + '<' + str(self.name)
        if self.attrs != {}:
            for a in sorted(self.attrs.items()):
                res += ' ' + a[0] + '=' + '"' + a[1] + '"'
        res += '>'
        ending = ' />'
        if self.data:
            ending = '</' + str(self.name) + '>'
            res += cgi.escape(self.data)
        if self.children:
            ending = '\n' + level * '\t' + '</' + str(self.name) + '>'
            for c in sorted(self.children.items()):
                for cc in c[1]:
                    res += cc.to_xml(level + 1)
#        else:
#            ending = '</' + str(self.name) + '>'
        if ending == ' />':
            res = res[:-1]
        res += ending
        return res


class VisitState(object):
    def __init__(self):
        self.tree = None
        self.node = None

class XMLVisitor(object):
    def __init__(self, visit_state):
        self.visit_state = visit_state

class StartElement(XMLVisitor):
    def __call__(self, name, attrs):
        new_node = Node(name)
        new_node.attrs = attrs
        if self.visit_state.node is None:
            self.visit_state.tree = self.visit_state.node = new_node
        else:
            self.visit_state.node[name] = new_node
            self.visit_state.node = self.visit_state.node[name][-1]

class EndElement(XMLVisitor):
    def __call__(self, name):
        self.visit_state.node = self.visit_state.node.parent


class CharData(XMLVisitor):
    def __call__(self, data):
        stripdata = data.lstrip()
        if len(stripdata) > 0:
            if len(self.visit_state.node.data) > 0:
                self.visit_state.node.data += data
            else:
                self.visit_state.node.data = stripdata

class Parser(object):
    def __init__(self, parserFunc):
        self.count = 0
        self.parserFunc = parserFunc

    def __call__(self, match_obj):
        p = ParserCreate('utf-8')
        vs = VisitState()
        p.StartElementHandler  = StartElement(vs)
        p.EndElementHandler    = EndElement(vs)
        p.CharacterDataHandler = CharData(vs)
        text = match_obj.group(0)
        level = text.count('\t', 0, text.find('<'))
        p.Parse(text.encode('utf-8'))
        tree = self.parserFunc(vs.tree)
        self.count += 1
        return tree.to_xml(level)

curFileProcessing = ''
class Visitor(object):
    def __init__(self, nodeName, parserFunc):
        self.nodeNames = nodeName if type(nodeName) == list else [nodeName]
        self.parserFunc = parserFunc

    def __call__(self, file_name):
        global curFileProcessing
        curFileProcessing = file_name
        print file_name
        with open(file_name, 'r', 'utf-8') as fileObj:
            text = fileObj.read()

        count = 0
        for nodeName in self.nodeNames:
            pattern = re.compile(r'[\n\t]*<%s>(.*?)</%s>' % (nodeName, nodeName), re.DOTALL | re.MULTILINE)
            parserObj = Parser(self.parserFunc)
            text = re.sub(pattern, parserObj, text)
            if parserObj.count > 0:
                print parserObj.count, 'total', nodeName, 'items found'
                count = count + parserObj.count
        if count > 0:
            with open(file_name, 'w', 'utf-8') as fileObj:
                fileObj.write(text)

def xdb_visit(visitor, dirname, names):
    for fileName in names:
        if fileName.endswith('xdb'):
            visitor(path.join(dirname, fileName))

def defaultDataPath():
  return path.normpath(path.join(path.dirname(__file__), '../../../Data'))

def dataPath(dirname):
  return path.normpath(path.join(path.dirname(__file__), '../../../Data', dirname))

def relativePath(dirname):
  return path.normpath(path.join(path.dirname(__file__), dirname))

def run(nodeName, parserFunc, data_path = defaultDataPath()):
    print data_path
    path.walk(data_path, xdb_visit, Visitor(nodeName, parserFunc))
    print 'OK'
