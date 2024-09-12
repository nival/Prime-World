from os import path
from copy import deepcopy
import re
import sys
from xml.parsers.expat import ParserCreate
from codecs import open

materialName = sys.argv[1]

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

def hasChild(node, key):
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
        pattern = re.compile(r'[\n\t]*<%s>(.*?)</%s>' % ( materialName, materialName ), re.DOTALL | re.MULTILINE)
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
    

def addColorNode(name, r_val, g_val, b_val, a_val):
	node = Node(name)
	node['R'] = Node('R')
	node['R'].data = r_val
	node['G'] = Node('G')
	node['G'].data = g_val
	node['B'] = Node('B')
	node['B'].data = b_val
	node['A'] = Node('A')
	node['A'].data = a_val
	return node

### Current work. ###    
def removeChild(node_name, in_tree, out_tree):
    del out_tree[node_name]

def removeMultiplierAdd(node_name, in_tree, out_tree):
    del out_tree[node_name]['Multiplier']
    del out_tree[node_name]['Add']
	
def changeSamplerIndexTo2(node_name, in_tree, out_tree):
    out_tree['SpecularMap']['samplerIndex'].data = '2'

def addFields(in_tree, out_tree):
	# Create node
	outNode = Node('renderState')
	out_tree['renderState'] = outNode
	
	# Analize alpha state node
	if hasChild(in_tree, 'default_AlphaState'):
		# Alpha test value
		outNode['alphaTest'] = Node('alphaTest')
		if in_tree['default_AlphaState']['alphaTestIsEnabled'].data == 'false':
			outNode['alphaTest'].data = 'Off'
		else:
			outNode['alphaTest'].data = 'On'
		# Alpha ref value
		outNode['alphaTestRef'] = Node('alphaTestRef')
		outNode['alphaTestRef'].data = in_tree['default_AlphaState']['alphaReferenceValue'].data
		
	# Analize blend state node
	if hasChild(in_tree, 'default_BlendState'):
		outNode['blendMode'] = Node('blendMode')
		blendStateNode = in_tree['default_BlendState']
		if blendStateNode['blendIsEnabled'].data == 'true':
			if (blendStateNode['sourceFactor'].data == 'SRCALPHA') and (blendStateNode['destinationFactor'].data == 'ONE'):
				outNode['blendMode'].data = 'AddColorMulAlpha'
			elif (blendStateNode['sourceFactor'].data == 'SRCALPHA') and (blendStateNode['destinationFactor'].data == 'INVSRCALPHA'):
				outNode['blendMode'].data = 'LerpByAlpha'
			elif (blendStateNode['sourceFactor'].data == 'ONE') and (blendStateNode['destinationFactor'].data == 'ONE'):
				outNode['blendMode'].data = 'AddColor'
			else:
				print 'Invalid blend combination found', blendStateNode['sourceFactor'].data, blendStateNode['destinationFactor'].data
				outNode['blendMode'].data = 'Off'
		else:
			outNode['blendMode'].data = 'Off'

	# Analize culling state node
	if hasChild(in_tree, 'default_CullingState'):
		outNode['culling'] = Node('culling')
		if in_tree['default_CullingState']['cullingMode'].data == 'CW':
			outNode['culling'].data = 'On'
		else:
			outNode['culling'].data = 'Off'
    
    
register('default_BlendState', removeChild)
register('default_AlphaState', removeChild)
register('default_CullingState', removeChild)

# register('_rename', {'uvspeed' : 'uvSpeed'})
register('_add', addFields)

data_path = path.normpath(path.join(path.dirname(__file__), '../../../Data'))

print data_path
path.walk(data_path, xdb_visit, Visitor())
print 'OK'