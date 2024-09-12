from os import path
from copy import deepcopy
import re
from xml.parsers.expat import ParserCreate
from codecs import open

g_sort_counter = 0
g_old_name = 'InstancingMaterial'
g_new_name = 'BasicMaterial'

class Node(object):

    def __init__(self, name):
        global g_sort_counter
        self.name = name
        self.attrs = {}
        self.children = {}
        self.data = ''
        self.parent = None
        self.counter = g_sort_counter
        g_sort_counter += 1
    
    def __getitem__(self, key):
        return self.children[key]        

    def __setitem__(self, key, child):
        child.parent = self
        self.children[key] = child
    
    def __delitem__(self, key):
        del self.children[key]        

    def to_xml(self, level = 0):
        res = '\r\n' + level * '\t' + '<' + str(self.name)
        if self.attrs != {}:
            for a in self.attrs.iteritems():
                res += ' ' + a[0] + '=' + '"' + a[1] + '"'
        res += '>'
        ending = ' />'
        if self.data:
            ending = '</' + str(self.name) + '>'
            res += self.data
        if self.children:
            ending = '\r\n' + level * '\t' + '</' + str(self.name) + '>'
            v = self.children.values()
            v.sort(key = lambda x: x.counter)
            for c in v:
                res += c.to_xml(level + 1)
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

class MaterialParser(object):
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
        pattern = re.compile(r'[\n\t]*<%s>(.*)</%s>' % ( g_old_name, g_old_name ), re.DOTALL | re.MULTILINE)
        mp = MaterialParser()
        text = re.sub(pattern, mp, text)
        if mp.count:
            print mp.count, 'materials found'
##            fh = open(file_name + '3', 'w', 'utf-8')

            fh = open(file_name, 'w', 'utf-8')
            fh.write(text)
            fh.close()


g_functions_register = {}


def handle_material(in_tree):
    out_tree = deepcopy(in_tree)
    out_tree.name = g_new_name

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
    

#def addColorNode(name, r_val, g_val, b_val, a_val):
#	node = Node(name)
#	node['R'] = Node('R')
#	node['R'].data = r_val
#	node['G'] = Node('G')
#	node['G'].data = g_val
#	node['B'] = Node('B')
#	node['B'].data = b_val
#	node['A'] = Node('A')
#	node['A'].data = a_val
#	return node

### Current work. ###    
def removeChild(node_name, in_tree, out_tree):
    del out_tree[node_name]

def removeChild(node_name, in_tree, out_tree):
    del out_tree[node_name]

def addNode(tree, name, data):
    node = Node(name)
    node.data = data
    tree[name] = node
    return node

def addSampler(tree, name):
    subtree = addNode(tree, name, '')
    node = addNode(subtree, 'samplerState', '')
    addNode(node, 'minFilter', 'Linear')
    addNode(node, 'magFilter', 'Linear')
    addNode(node, 'mipFilter', 'Linear')
    addNode(node, 'addressU', 'Wrap')
    addNode(node, 'addressV', 'Wrap')
    addNode(node, 'addressW', 'Wrap')
    node2 = addNode(subtree, 'texture', '')
    node2.attrs['href'] = ''

def addChildren(in_tree, out_tree):
    addSampler(out_tree, 'NormalMap')
    addSampler(out_tree, 'SpecularMap')
    addSampler(out_tree, 'ReflectionMap')
    addNode(out_tree, 'ReflectivityPinValue', 'ReflectivityOff')
    addNode(out_tree, 'reflectivity', '1')
    addNode(out_tree, 'specularPower', '0')
    addNode(out_tree, 'EmissivePinValue', 'EmissiveOff')
    addNode(out_tree, 'LightingPinValue', 'LightingInstancedSH')
    
   

register('OpacityAndEmissiveModePinValue', removeChild)
register('opacity', removeChild)
register('_add', addChildren)


data_path = path.normpath(path.join(path.dirname(__file__), '../../../Data'))

print data_path
path.walk(data_path, xdb_visit, Visitor())
print 'OK'
