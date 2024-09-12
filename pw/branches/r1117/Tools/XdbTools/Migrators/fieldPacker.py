from os import path
from copy import deepcopy
import re
import sys
from xml.parsers.expat import ParserCreate
from codecs import open
from uuid import uuid4

objectName = "DBWaterSceneComponent"
packed_field= "geometry"
packed_name = "DBStaticGeometry"
pack_nodes = "srcFileName", "mayaFileName", "geometryFileName", "selection", "uvSetCount", "aabb"

class Node(object):

    def __init__(self, name):
        self.name = name
        self.attrs = {}
        self.children = {}
        self.data = ''
        self.parent = None

    def __getitem__(self, key):
	if len(self.children[key]) == 1:
	    return self.children[key][0]
	print 'INCORRECT CASE!!!'
	return None

    def __setitem__(self, key, child):
        child.parent = self
	self.add_child(child)
    
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
		for cc in c: # now c is a list of nodes
		    res += cc.to_xml(level + 1)
        if ending == ' />':
            res = res[:-1]
        res += ending
        return res

    def add_child(self, child):
	if not child.name in self.children:
	    self.children[child.name] = []
	self.children[child.name].append(child)
	
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
	    new_node = Node(name)
            self.visit_state.node[name] = new_node
            self.visit_state.node = new_node
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


def handle_object(in_tree, file_name):
    out_tree = deepcopy(in_tree)
    out_tree[packed_field] = Node(packed_field)
    out_tree[packed_field].attrs = {'href' : file_name, 'id' : str(uuid4()).upper()}
    out_tree[packed_field][packed_name] = Node(packed_name)
    for node_name in pack_nodes:
	if not in_tree.has_child(node_name):
	    print "ERROR: there is no", node_name, "in", objectName
	else:
	    out_tree[packed_field][packed_name][node_name] = in_tree[node_name]
	    del out_tree[node_name]
    
    return out_tree


data_path = path.normpath(path.join(path.dirname(__file__), '../../../Data'))

print data_path
path.walk(data_path, xdb_visit, Visitor())
print 'OK'