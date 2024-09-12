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
            ending = ' />'
        else:
            ending = '</' + str(self.name) + '>'
        res += '>'
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

g_filter_file = {
  'Buildings/A/Barrack/_.SOBJ.xdb': {'6BB90908-1FDD-4CD5-90CC-506B6E2CD49B':''},
  'Buildings/A/Shop/_.SOBJ.xdb': {'9113D609-ED53-418C-9AA3-2DC0DC75DEDF':''},
  'Buildings/A/Temple/_FXidle.PRXY.xdb': {'BD1F28A0-507B-454A-89C3-5CC5665ED107':'', 'CFDA9EA5-6E55-47D7-A85F-AFB6A34113E8':''},
  'Buildings/A/Tower/_.MTRL.xdb': {},
  'Buildings/A/Tower/_Crash.SOBJ.xdb': {'2B7E2860-94EF-4A1A-B1F8-CE1E337B8A00':''},
  'Buildings/A/Wall/wall.MTRL.xdb': {},
  'Buildings/B/Main/_FXAttackAOE.PRXY.xdb': {'C5E289A4-8414-4610-BCEE-4B39EA613C1A':''},
  'Buildings/B/MiniGame/_1.MTRL.xdb': {},
  'Buildings/B/Misc03/_.MTRL.xdb': {},
  'Buildings/B/Misc03/_.SOBJ.xdb': {'9EE6D163-EAB0-4A4B-A401-F6352B537106':''},
  'Buildings/B/Temple/_.SOBJ.xdb': {'17B295B9-E21D-47BD-A525-9D362410DE49':'', '7A5A1E2C-5136-49A0-9107-099BA5331A0B':'', '871C0923-4AE2-4143-AB40-F71109612088':''},
  'Buildings/B/Tower/_.MTRL.xdb': {},
  'Buildings/Temp/MarlettoTower/_crash.SOBJ.xdb': {'1256A863-1203-453E-A5D5-DEB78FA38237':''},
  'Glyphs/Chest/_.SOBJ.xdb': {'2EF19AFF-CD79-41B3-A8E2-ED787517B922':''},
  'Heroes/ManaWyrm/_.SOBJ.xdb': {'03211B80-06D2-4D2B-B8E9-BED9652D19FB':'', '93906740-A670-4313-8995-346226E8D97E':'', '9F48EADE-8F9A-4F71-8516-A597FA9604A3':''},
  'Heroes/WitchDoctor/_A.SOBJ.xdb': {'62862C61-B0E5-4B1B-AC6D-6A586B6BFD58':''},
  'Tech/Default/Bulb.SOBJ.xdb': {'8F18E838-B62B-4EE4-8D24-E961785EA2C9':''},
  'Tech/Default/Flag.SOBJ.xdb': {'8832725A-A71F-4AAE-8CB9-CFF88A38E888':''},
  'Terrain/Grass/_08A.SOBJ.xdb': {'456B7705-FB30-4547-BFDC-8C142D0FD9D6':''},
  'Terrain/Islands/_01.SOBJ.xdb': {'A5EA9745-B0E5-40F0-A8E7-FEF3A6345A77':'', 'A7D7B0B8-02C5-442D-9B9F-2BA4268AAB61':''},
  'Terrain/Islands/_02.SOBJ.xdb': {'CC58ADFD-CEB6-4A93-860E-57F31660401F':''},
  'Terrain/Islands/_03.SOBJ.xdb': {'0A43CBD5-1020-4EEE-9125-63504C3242FD':''},
  'Terrain/Minor/_01A.SOBJ.xdb': {'0FFE3D59-7AB1-43E9-ABD7-1EA87B8B25B3':''},
  'Terrain/Minor/_05A.SOBJ.xdb': {'34ED69B4-78BA-4F27-979F-6C393F772A04':''},
  'Terrain/RockyMountain/_.SOBJ.xdb': {'124F8C06-B8CB-4AE6-9FD5-29A02C97C7BB':'', '24684BF1-E8A3-482E-A881-23B322B0A9FD':'', 'CAC8F2B0-14C3-4838-B415-BCEA984E8AE3':''},
  'Terrain/Signs/_01A.SOBJ.xdb': {'03F4C786-13F3-4885-99E2-F5B408ECA481':''},
  'Terrain/Signs/_01B.SOBJ.xdb': {'A53610E4-1279-43BD-82EF-0DCAA11064A5':''},
  'Terrain/Signs/_01N.SOBJ.xdb': {'334BE543-0BE3-4328-84A1-3BE4832864CB':''},
  'Terrain/Signs/_02A.SOBJ.xdb': {'E2A9CFCE-D6F9-4DBF-A052-107804BF3D34':''},
  'Terrain/Signs/_02B.SOBJ.xdb': {'C013C73A-02FA-4637-A14F-6C446786C87B':''},
  'Terrain/Signs/_02N.SOBJ.xdb': {'BD48F527-5C90-4C8D-A18C-7B7AD0217A94':''},
  'Terrain/Signs/_03A.SOBJ.xdb': {'AD07EE5C-43FF-4240-BF8E-D110C4D5BB0F':''},
  'Terrain/Signs/_03B.SOBJ.xdb': {'8C70A7E8-78FD-4B2B-AEA5-5A04C0C794BF':''},
  'Terrain/Signs/_03N.SOBJ.xdb': {'0B6FEEE4-6629-448A-86D9-D346A3C10898':''},
  'Terrain/Signs/_04A.SOBJ.xdb': {'684F3EFB-8898-4566-B8C3-71D2A38295CF':''},
  'Terrain/Signs/_04B.SOBJ.xdb': {'1AAA2591-29A0-4109-B45B-3258AE280C65':''},
  'Terrain/Signs/_04N.SOBJ.xdb': {'EC7C4EEF-C0AC-41FB-8136-B5F65BC19FDB':''},
  'Terrain/Signs/_05A.SOBJ.xdb': {'97BC770F-6D07-4CCF-9C3E-705E9589CFD9':''},
  'Terrain/Signs/_05N.SOBJ.xdb': {'8BC81E73-875A-4F1F-BAC7-10AF3CDD6C0B':''},
  'Terrain/Signs/_06A.SOBJ.xdb': {'AA529490-1FE2-4DF8-9265-6A787B73373D':''},
  'Terrain/Signs/_06B.SOBJ.xdb': {'C79E8644-DA3D-45B2-A107-FE18C20FCA74':''},
  'Terrain/Signs/_06N.SOBJ.xdb': {'F2F809AD-993B-4E94-8B50-D01FEB59B756':''},
  'Terrain/Signs/_07A.SOBJ.xdb': {'49B0BFD5-4546-4493-A4B8-243EFB4DEE77':''},
  'Terrain/Signs/_07N.SOBJ.xdb': {'ED2BC7A5-E8D8-4A23-A730-D4E0098E6140':''},
  'Terrain/Signs/_08A.SOBJ.xdb': {'515F3384-9E98-4E85-A981-72304ED2B4D9':''},
  'Terrain/Signs/_08N.SOBJ.xdb': {'42B29012-E290-463A-B450-09C9AF09EC5F':''},
  'Terrain/Signs/_10A.SOBJ.xdb': {'A26C0837-EA07-40B7-92A7-2F120AD4D94A':''},
  'Terrain/Signs/_10B.SOBJ.xdb': {'31AA0D4E-3660-49A9-A18C-004E694A0A0C':''},
  'Terrain/Signs/_10N.SOBJ.xdb': {'9CEBBA4A-A8EA-467F-A5B5-9CE9D4F771AA':'', 'D73A29FE-26DD-49C4-8959-9E320ABD0ADF':''},
  'Terrain/Trees/MSO/_01A.MTRL.xdb': {},
  'Terrain/Trees/MSO/_01B.MTRL.xdb': {},
  'Terrain/Trees/MSO/_01N2.MTRL.xdb': {},
}        

g_filter_id = {}
g_root = ''

def check_filter(name):
    file_name = re.sub(r'\\', '/', name)
    if file_name.startswith(g_root):
        file_name = file_name[len(g_root)+1:len(file_name)]
#    print 'CHECK - ' + file_name
    if len(g_filter_file) > 0 and file_name not in g_filter_file:
        return None
    return g_filter_file[file_name]
        
class Visitor(object):
    def __init__(self):
        pass
    def __call__(self, file_name):
        g_filter_id = check_filter(file_name)
        if not g_filter_id:
            return
        print file_name
        fh = open(file_name, 'r', 'utf-8')
        text = fh.read()
        fh.close()
        pattern = re.compile(r'[\r\n\t]*<Item [^<>]*>\s*<BasicMaterial>(.*?)</BasicMaterial>\s*</Item>', re.DOTALL | re.MULTILINE)
        mp = MaterialParser()
        text = re.sub(pattern, mp, text)
        if mp.count:
            print mp.count, 'materials found'
##            fh = open(file_name + '3', 'w', 'utf-8')

            fh = open(file_name, 'w', 'utf-8')
            fh.write(text)
            fh.close()


g_functions_register = {}


def handle_material(in_tree_total):
    out_tree_total = deepcopy(in_tree_total)
    id_name = out_tree_total.attrs['id']
    if len(g_filter_id) > 0 and id_name not in g_filter_id:
        return out_tree_total
    print id_name
    in_tree = in_tree_total['BasicMaterial']
    out_tree = out_tree_total['BasicMaterial']
    for node_name in in_tree.children:
        if node_name in g_functions_register:
            g_functions_register[node_name](node_name, in_tree, out_tree)
##            in_tree = deepcopy(out_tree)
    if '_add' in g_functions_register:
        g_functions_register['_add'](in_tree, out_tree)
    if '_rename' in g_functions_register:
        rename_fields(out_tree, g_functions_register['_rename'])
    return out_tree_total

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

#def removeMultiplierAdd(node_name, in_tree, out_tree):
#    del out_tree[node_name]['Multiplier']
#    del out_tree[node_name]['Add']
	
#def changeSamplerIndexTo2(node_name, in_tree, out_tree):
#    out_tree['SpecularMap']['samplerIndex'].data = '2'

#register('ambientColor', removeChild)
#register('diffuse2Color', removeChild)
#register('_rename', {'diffuse1Color' : 'diffuseColor'})
#register('_add', addFields)

def addNode(tree, name, data):
    node = Node(name)
    node.data = data
    tree[name] = node

def addFields(in_tree, out_tree):
	addNode(out_tree, 'LightingPinValue', 'LightingBaked')
    
register('_add', addFields)

g_root = '../../../Data'
data_path = path.normpath(path.join(path.dirname(__file__), g_root))

print data_path
path.walk(data_path, xdb_visit, Visitor())
print 'OK'
