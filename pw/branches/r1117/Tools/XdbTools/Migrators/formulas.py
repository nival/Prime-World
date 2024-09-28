# -*- coding: utf-8 -*-

from os import path
from copy import deepcopy
import re
from xml.parsers.expat import ParserCreate
from codecs import open, encode


class Node(object):

    def __init__(self, name):
        self.name = name
        self.attrs = {}
        self.children = {}
	self.order = []
        self.data = ''
        self.parent = None
    
    def __getitem__(self, key):
        return self.children[key]        

    def __setitem__(self, key, child):
        child.parent = self
	if key not in self.children:
	    self.children[key] = []
            self.order.append(key)
	    
        self.children[key].append(child)
	if len(self.children[key]) > 2:
	    pass
    
    def __delitem__(self, key):
        del self.children[key]
	del self.order[self.order.index(key)]
        
    def to_xml(self, level = 0):
        res = '\n' + level * 8 * ' ' + '<' + str(self.name)
        if self.attrs != {}:
            for a in self.attrs.iteritems():
                res += ' ' + a[0] + ' = ' + '"' + a[1] + '"'
        res += '>'
        ending = ' />'
	if self.name == 'effect':
	    pass
        if self.data:
            ending = '</' + str(self.name) + '>'
            res += self.data
	    # hack
	    if self.name == 'compiledString':
		res += '\n'
        if self.children:
            ending = '\n' + level * 8 * ' ' + '</' + str(self.name) + '>'
	    for i in self.order:
##            for c in self.children.itervalues():

                c = self.children[i]   
		if len(c) > 2:
		    pass
		for cc in c:
		    res += cc.to_xml(level + 1)
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
	if name == 'Item':
	    pass
	
        if self.visit_state.node is None:
            self.visit_state.tree = self.visit_state.node = Node(name)
        else:
	    n = Node(name)
            self.visit_state.node[name] = n
            self.visit_state.node = n
        self.visit_state.node.attrs = attrs

class EndElement(XMLVisitor):
    
    def __call__(self, name):
        self.visit_state.node = self.visit_state.node.parent
##        print name


class CharData(XMLVisitor):
    def __call__(self, data):
        if data.lstrip():
            self.visit_state.node.data = data


def xdb_visit(visitor, dirname, names):
    for n in names:
        if n.endswith('xdb'):
            visitor(path.join(dirname, n))

class Field(object):
    def __init__(self, field_name, field_depth):
	self.name = field_name
	self.depth = field_depth
	
class NodeParser(object):
    def __init__(self, fields):
        self.count = 0
	self.fields = fields
        pass
    def __call__(self, match_obj):
        p = ParserCreate('utf-8')
        vs = VisitState()
        p.StartElementHandler = StartElement(vs)
        p.EndElementHandler = EndElement(vs)
        p.CharacterDataHandler = CharData(vs)
        text = match_obj.group(0)
        level = text.count('\t', 0, text.find('<'))
##	text = """<?xml version="1.0"?>
##<root>
##  <i1 />
##  <i1> - 2</i1>
##</root>"""

        p.Parse(encode(text, 'utf-8'))
        tree = handle_tree(vs.tree, self.fields)
##	tree = vs.tree
        self.count += 1
##	print tree.to_xml(level)
        return tree.to_xml(level)

class NodeParams(object):
    def __init__(self, node_name):
	self.name = node_name
	self.fields = []
	
    def add_field(self, field_name, field_depth):
	self.fields.append(Field(field_name, field_depth))
	
	
class Visitor(object):
    def __init__(self, nodes):
	self.nodes = nodes

    def __call__(self, file_name):
        print file_name
        fh = open(file_name, 'r', 'utf-8')
##	fh = open(file_name, 'r')
        text = fh.read()
        fh.close()
	count = 0
	for n in self.nodes:
	    pattern = re.compile(r'[\n\t]*<' + n.name + '>(.*?)</' + n.name + '>', re.DOTALL | re.MULTILINE)
	    np = NodeParser(n.fields)

            text = re.sub(pattern, np, text)
            if np.count:
		print np.count, n.name + "'s found"
		count += np.count
		
	if count:
##	    fh = open(file_name + '3', 'w', 'utf-8')
            fh = open(file_name, 'w', 'utf-8')
	    fh.write(text)
	    fh.close()


def handle_tree(in_tree, fields):
    def rec_handle(in_tree, depth, fields, out_tree):
	for node_name in in_tree.children:
	    for c_in, c_out in zip(in_tree[node_name], out_tree[node_name]):
		for f in fields:
		    if depth == f.depth and node_name == f.name:
			node = c_out
			if node.children:
			    continue
			node['compiledString'] = Node('compiledString')
			n = Node('returnType')
			node['returnType'] = n
			n.data = 'float'
			n = Node('sString')
			node['sString'] = n
			n.data = node.data
			node.data = ''
                rec_handle(c_in, depth + 1, fields, c_out)
	
    out_tree = deepcopy(in_tree)
    rec_handle(in_tree, 1, fields, out_tree)
    return out_tree


data_path = path.normpath(path.join(path.dirname(__file__), '../../../Data'))
##data_path = path.normpath(path.join(path.dirname(__file__), '../../../Data/Heroes/'))

print data_path

nodes = []
#nodes.append(NodeParams('DropTreeApplicator'))
#nodes[0].add_field('range', 1)
#nodes.append(NodeParams('ChainLightningApplicator'))
#nodes[0].add_field('range', 1)

#nodes.append(NodeParams('ModifyTerrainApplicator'))
#nodes[0].add_field('modifRadius', 1)
#nodes[0].add_field('spreadTime', 1)

#nodes.append(NodeParams('UnitShiftTarget'))
#nodes[0].add_field('distance', 1)

#nodes.append(NodeParams('PointTargetSelector'))
#nodes[4].add_field('range', 1)

nodes.append(NodeParams('StatsContainer'))
nodes[0].add_field('value', 3)
nodes[0].add_field('increment', 3)


path.walk(data_path, xdb_visit, Visitor(nodes))
print 'OK'