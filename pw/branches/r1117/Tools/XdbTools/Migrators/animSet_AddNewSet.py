# http://SITE
from os import path
from copy import deepcopy
import re
from xml.parsers.expat import ParserCreate
from codecs import open
from collections import defaultdict


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
            for a in self.attrs.iteritems():
                res += ' ' + a[0] + ' = ' + '"' + a[1] + '"'
        res += '>'
        ending = ' />'
        if self.data:
            ending = '</' + str(self.name) + '>'
            res += self.data
        if self.children:
            ending = '\n' + level * '\t' + '</' + str(self.name) + '>'
            for c in self.children.itervalues():
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
##        print name


class CharData(XMLVisitor):
    def __call__(self, data):
        if data.lstrip():
            self.visit_state.node.data = data.lstrip()


def xdb_visit(visitor, dirname, names):
    for n in names:
        if n.endswith('xdb'):
            visitor(path.join(dirname, n))

class AnimSetParser(object):
    def __init__(self):
        self.count = 0
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
        tree = handle_material(vs.tree)
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
        pattern = re.compile(r'[\n\t]*<AnimSet>(.*?)</AnimSet>', re.DOTALL | re.MULTILINE)
        asp = AnimSetParser()
        text = re.sub(pattern, asp, text)
        if asp.count:
            print asp.count, 'AnimSets found'
            fh = open(file_name, 'w', 'utf-8')
            fh.write(text)
            fh.close()


g_functions_register = {}


def handle_material(in_tree):
    out_tree = deepcopy(in_tree)
    for node_name in in_tree.children:
        if node_name in g_functions_register:
            g_functions_register[node_name](node_name, in_tree, out_tree)
##            in_tree = deepcopy(out_tree)
    if '_add' in g_functions_register:
        g_functions_register['_add'](in_tree, out_tree)
    if '_rename' in g_functions_register:
        rename_fields(out_tree, g_functions_register['_rename'])
    return out_tree

def rename_fields(tree, rename_list):
    for old_name, new_name in rename_list.iteritems():
		tree[new_name] = tree[old_name]
		tree[new_name].name = new_name
		del tree[old_name]

def register(name, func):
    g_functions_register[name] = func
    
### Current work. ###    
    
def statesId(node_name, in_tree, out_tree):
    for i in out_tree['states']:
        size = len(i['Item'])
        l = []
        for idx in range(16):
            l.append(i['Item'][idx])
        
        l.append( i['Item'][size-1] )
        l.append( i['Item'][size-1] )
        
        for idx in range(16, size):
            l.append(i['Item'][idx])
        i.children['Item'] = i['Items'][:16] + l + i['Items'][16:]
        
        
register('states', statesId)

#data_path = "."
#data_path = path.normpath(path.join(path.dirname(__file__), '../../../Data/Buildings/BorderGuard'))
data_path = path.normpath(path.join(path.dirname(__file__), '../../../Data'))


print data_path
path.walk(data_path, xdb_visit, Visitor())
print 'OK'