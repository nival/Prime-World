from os import path
from copy import deepcopy
import re
import sys
from xml.parsers.expat import ParserCreate
from codecs import open
from uuid import uuid4

objectName = "timeMutator"
packed_field= "timeController"
packed_name = "TimeController"

class Node(object):

    def __init__(self, name):
        self.name = name
        self.attrs = {}
        self.children = {}
        self.data = ''
        self.parent = None

    def __getitem__(self, key):
        return self.children[key]        

    def __setitem__(self, key, child):
        child.parent = self
        self.children[key] = child
    
    def __delitem__(self, key):
        del self.children[key]        

    def to_xml(self, level = 0):
        res = '\n' + level * 8 * ' ' + '<' + str(self.name)
        if self.attrs != {}:
            for a in self.attrs.iteritems():
                res += ' ' + a[0] + ' = ' + '"' + a[1] + '"'
        res += '>'
        ending = ' />'
        if self.data:
            ending = '</' + str(self.name) + '>'
            res += self.data
        if self.children:
            ending = '\n' + level * 8 * ' ' + '</' + str(self.name) + '>'
            for c in self.children.itervalues():
                res += c.to_xml(level + 1)
        if ending == ' />':
            res = res[:-1]
        res += ending
        return res

    def has_child(node, key):
    	return (key in node.children)

class VisitState(object):
    def __init__(self):
        self.tree = None
        self.node = None

class XMLVisitor(object):

    def __init__(self, visit_state):
        self.visit_state = visit_state
        
class StartElement(XMLVisitor):

    def __call__(self, name, attrs):
        if self.visit_state.node is None:
            self.visit_state.tree = self.visit_state.node = Node(name)
        else:
            self.visit_state.node[name] = Node(name)
            self.visit_state.node = self.visit_state.node[name]
        self.visit_state.node.attrs = attrs

class EndElement(XMLVisitor):
    
    def __call__(self, name):
        self.visit_state.node = self.visit_state.node.parent
##        print name


class CharData(XMLVisitor):
    def __call__(self, data):
        if data.lstrip():
            self.visit_state.node.data = data.lstrip()


def xdb_visit(visitor, dirname, names):
    for n in names:
        if n.endswith('xdb'):
            visitor(path.join(dirname, n))

class ObjectParser(object):
    def __init__(self, file_name):
        self.count = 0
	self.file_name = file_name
        pass
    def __call__(self, match_obj):
        p = ParserCreate('utf-8')
        vs = VisitState()
        p.StartElementHandler = StartElement(vs)
        p.EndElementHandler = EndElement(vs)
        p.CharacterDataHandler = CharData(vs)
        text = match_obj.group(0)
        level = text.count('\t', 0, text.find('<'))
        p.Parse(text)
        tree = handle_object(vs.tree, self.file_name)
        self.count += 1
        return tree.to_xml(level)
        
        
class Visitor(object):
    def __init__(self):
        pass
    def __call__(self, file_name):
        print file_name
        fh = open(file_name, 'r', 'utf-8')
        text = fh.read()
        fh.close()
        pattern = re.compile(r'[\n\t]*<%s>(.*?)</%s>' % ( objectName, objectName ), re.DOTALL | re.MULTILINE)
        mp = ObjectParser(file_name[file_name.find('Data\\'):])
        text = re.sub(pattern, mp, text)
        if mp.count:
            print mp.count, 'objects found'
##            fh = open(file_name + '3', 'w', 'utf-8')

            fh = open(file_name, 'w', 'utf-8')
            fh.write(text)
            fh.close()


g_functions_register = {}

def copy_field(dstNode, dstField, srcNode, srcField):
	dstNode[dstField] = Node(dstField)
	dstNode[dstField].data = srcNode[srcField].data



def handle_object(in_tree, file_name):

	if (in_tree["speed"].data == "1") and (in_tree["offset"].data == "0") and (in_tree["cycleLength"].data == "0") and (in_tree["cycleCount"].data == "0"):
		return in_tree

	print "TimeMutator is not default!"

	out_tree = Node(packed_field)
	out_tree.attrs = {'href' : file_name, 'id' : str(uuid4()).upper()}
	
	dstNode = Node(packed_name)
	
	copy_field(dstNode, "speed", in_tree, "speed")
	copy_field(dstNode, "firstCycleOffset", in_tree, "offset")
	copy_field(dstNode, "cycleLength", in_tree, "cycleLength")
	copy_field(dstNode, "cycleCount", in_tree, "cycleCount")
	copy_field(dstNode, "fadein", in_tree, "fadein")
	copy_field(dstNode, "fadeout", in_tree, "fadeout")
	
	out_tree[packed_field] = dstNode

	return out_tree

data_path = path.normpath(path.join(path.dirname(__file__), '../../../Data'))

print data_path
path.walk(data_path, xdb_visit, Visitor())
print 'OK'