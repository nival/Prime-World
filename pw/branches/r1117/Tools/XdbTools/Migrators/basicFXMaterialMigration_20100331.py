from os import path
from copy import deepcopy
import re
from xml.parsers.expat import ParserCreate
from codecs import open

g_sort_counter = 0

class Node(object):

    def __init__(self, name):
        global g_sort_counter
        self.name = name
        self.attrs = {}
        self.children = []
        self.data = ''
        self.parent = None
        self.counter = g_sort_counter
        g_sort_counter += 1
    
    def addChild(self, node):
        node.parent = self
        self.children.append(node)

    def removeChildByName(self, name):
        for n in self.children[:]:
            if n.name == name:
                self.children.remove(n)
        
    def to_xml(self, level = 0):
        res = '\r\n' + level * '\t' + '<' + str(self.name)
        if self.attrs != {}:
            for a in self.attrs.iteritems():
                res += ' ' + a[0] + '=' + '"' + a[1] + '"'
            ending = ' />'
        else:
            ending = '</' + str(self.name) + '>'
        res += '>'
        if self.data:
            ending = '</' + str(self.name) + '>'
            res += self.data
        if self.children:
            ending = '\r\n' + level * '\t' + '</' + str(self.name) + '>'
            v = self.children
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
            n = Node(name)
            self.visit_state.node.addChild(n)
            self.visit_state.node = n
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
        pattern = re.compile(r'[\r\n\t]*<BasicFXMaterial>(.*?)</BasicFXMaterial>', re.DOTALL | re.MULTILINE)
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
    for node in in_tree.children:
        if node.name in g_functions_register:
            g_functions_register[node.name](node, in_tree, out_tree)
##            in_tree = deepcopy(out_tree)
    if '_add' in g_functions_register:
        g_functions_register['_add'](in_tree, out_tree)
    if '_rename' in g_functions_register:
        rename_fields(out_tree, g_functions_register['_rename'])
    return out_tree

def rename_fields(tree, rename_list):
    for old_name, new_name in rename_list.iteritems():
        for n in tree.children:
            if n.name == old_name:
                n.name = new_name

def register(name, func):
    g_functions_register[name] = func
    

### Current work. ###    
def removeChild(node, in_tree, out_tree):
    out_tree.removeChildByName(node.name)

register('Diffuse2Map', removeChild)
register('Diffuse2Mul', removeChild)
register('Diffuse2Add', removeChild)
register('uOffset2', removeChild)
register('vOffset2', removeChild)
register('DiffuseMapCountPinValue', removeChild)
register('DiffuseColorMixPinValue', removeChild)
register('DiffuseAlphaMixPinValue', removeChild)

register('_rename', {'Diffuse1Map' : 'DiffuseMap', 'Diffuse1Mul' : 'DiffuseMul', 'Diffuse1Add' : 'DiffuseAdd', 'uOffset1' : 'uOffset', 'vOffset1' : 'vOffset'})

data_path = path.normpath(path.join(path.dirname(__file__), '../../../Data'))

print data_path
path.walk(data_path, xdb_visit, Visitor())
print 'OK'
