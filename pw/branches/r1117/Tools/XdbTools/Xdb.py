import os
import XmlUtils

from construct import *  
import struct

header_struct = Struct("header",
    ULInt32("signature"),
    ULInt32("fragmentCount"),
    ULInt32("materialCount"),
    ULInt32("commonVertexBufferSizeInBytes"),
    ULInt32("commonIndexBufferSizeInBytes"),
    ULInt32("vbOffset"),
    ULInt32("ibOffset"),
    ULInt32("reindexOffset"),
    ULInt32("jointsCount"),
)

array_header_struct = Struct("array_header",
    ULInt32("array_count"),
    ULInt32("array_offset"),
)

fragment_header_struct = Struct("fragment_header",
    ULInt32("__align"),
    ULInt32("vertexStrideSizeInBytes"),
    ULInt32("baseVertexIndex"),
    ULInt32("minIndex"),
    ULInt32("numVertices"),
    ULInt32("startIndex"),
    ULInt32("primitiveCount"),
    ULInt32("materialID"),
    ULInt32("streamOffset"),
)
                        
class Parser:
    def __init__(self, content):
        self.start = 0
        self.content = content
        
    def parse(self, struct, size):
        result = struct.parse(self.content[self.start:self.start+size])
        self.start += size
        return result
       
       
class GeometryInfo:            

    def __init__(self):
        self.vertex_buffers_size = 0
        self.index_buffers_size = 0
        self.total_vertices_count = 0  
        self.total_primitives_count = 0
    
    def __add__(self, other):
        info = GeometryInfo()
        
        info.vertex_buffers_size = self.vertex_buffers_size+other.vertex_buffers_size
        info.index_buffers_size = self.index_buffers_size+other.index_buffers_size
        info.total_vertices_count = self.total_vertices_count+other.total_vertices_count
        info.total_primitives_count = self.total_primitives_count +other.total_primitives_count
        return info

    def out(self):
        for name, value in self.__dict__.items():
            print '%s %d' % (name, value)
            
class Counted:

    def __init__(self):
        self._items = {}
        
    def append(self, item):
        if item not in self._items:
            self._items[item] = 1
        else:    
            self._items[item] += 1    
            
    def items(self):
        return self._items.items()            
        
    def __len__(self):
        return len(self._items)        
        
class SectionCollector:

    def __init__(self, name):
        self.name = name
        self.result = []
        
    def process(self, section):
        if section.getName() == self.name:        
            self.result.append(section)

def isInlined(data):    
    try:
        data.id
    except KeyError:
        return False
    return True
            
def parseInlineTexture(texture, textures):
    path = str(texture.textureFileName)
    if path:
        textures.append(path)
                   
def parseInlineMaterial(root, item, textures):
    c1 = SectionCollector('texture')
    item.enum(c1)
    for texture in c1.result:
        if isInlined(texture):
            parseInlineTexture(texture.Texture, textures)
        else:            
            path = str(texture.href)
            if path:
                t = openLink(root, path)
                parseInlineTexture(t.Texture, textures)
    return len(c1.result)

        
material_types = [
    'TerrainMaterial',
    'BasicMaterial',
    'ParticleFXMaterial',
    'TreeLeavesMaterial',
    'WaterMaterial',
    'BasicWeatherMaterial',
]    

def parseMaterialData(root, c, textures):
    for material_type in material_types:
        if c.has(material_type):
            return parseInlineMaterial(root, c[material_type], textures)
            
    assert 0 
    
def parseMaterial(root, path, textures):
    c = openLink(root, path)
    parseMaterialData(root, c, textures)

def _getPath(_path):
    if _path[0] == '/':
        path = _path[1:]
    else:
        path = _path        
    return path
            
def getPath(_path):
    path = _getPath(_path)
    head, tail = os.path.splitext(path)
    if tail.lower() != '.xdb':
        path += '.xdb'
    return path        

def convertPath(root, _path):
    path = _getPath(_path)
    return os.path.join(root, path)        
    
def _openLink(full_path):
    head, tail = os.path.splitext(full_path)
    if os.path.isfile(full_path):
        ccc = XmlUtils.parseString2(open(full_path, 'rb').read())
        return ccc
        
def openLink(root, _path):
    path = getPath(_path)        
    full_path = os.path.join(root, str(path))
    return _openLink(full_path)

def parseMaterials(root, data, materials, textures):
    added = 0
    for item in data.materialsReferences:
        if not isInlined(item):
            material_path = str(item.href)
            assert '.STAT' not in material_path
            materials.append(material_path)
            added += 1
        else:    
            added += parseMaterialData(root, item, textures)
                    
    return added                    
    
def parseMesh(root, path):    
    content = open(convertPath(root, str(path)), 'rb').read()
    info = GeometryInfo()
    p = Parser(content)
    header = p.parse(header_struct, 9*4)                       
    array_header = p.parse(array_header_struct, 2*4)
    
    info.vertex_buffers_size = header.commonVertexBufferSizeInBytes
    info.index_buffers_size = header.commonIndexBufferSizeInBytes

    for i in range(header.fragmentCount):
        fragment_header = p.parse(fragment_header_struct, 9*4)
        info.total_vertices_count += fragment_header.numVertices
        info.total_primitives_count += fragment_header.primitiveCount
    return info        
            
def parseInlinedStaticMesh(root, data, materials, textures):
    parseMaterials(root, data, materials, textures)
    return parseMesh(root, data.geometryFileName)
    
def parseStaticMesh(root, path, materials, textures):
    m = openLink(root, path)
    if m.has('StaticMesh'):
        return parseInlinedStaticMesh(root, m.StaticMesh, materials, textures)
    elif m.has('WaterStaticMesh'):    
        return parseInlinedStaticMesh(root, m.WaterStaticMesh, materials, textures)
    else:
        assert 0        

def parseParticle(root, p, textures):
    if p.material.href:
        parseMaterialData(root, p.material, textures)
        
def parseEffect(root, path, materials, textures):
    e = openLink(root, path)
    for item in e.Effect.effects:
        parseParticle(root, item.particle, textures)
        if item.model.model.href:
            parseAnimatedMesh(root, item.model.model.href, materials, textures)
#        print p
#    assert 0, path
    return GeometryInfo()
    
def parseAnimatedMesh(root, path, materials, textures):
    m = openLink(root, path)
    total_info = GeometryInfo()
    for item in m.Skeleton.skins:
        parseMaterials(root, item, materials, textures)
        info = parseMesh(root, item.geometryFileName)
        total_info += info
    return total_info
    
def parseEntity(root, data, entities, processor):
    path = str(data.href)
    info = None
    if path:
        if not isInlined(data):    
            info = processor.process(root, path)
        else:
            path = path+'_inlined'
            info = processor.processInlined(root, data)
        if info:
            if path not in entities:
                entities[path] = info
        else:
            assert 0                
    return info                
            
class StaticMeshParser:

    def __init__(self, materials, textures):            
        self.materials = materials
        self.textures = textures
        
    def process(self, root, path):
        return parseStaticMesh(root, path, self.materials, self.textures)                
                
    def processInlined(self, root, data):
        return parseInlinedStaticMesh(root, data.StaticMesh, self.materials, self.textures)

class EffectParser:

    def __init__(self, materials, textures):            
        self.materials = materials
        self.textures = textures
        
    def process(self, root, path):
        return parseEffect(root, path, self.materials, self.textures)                
                
    def processInlined(self, root, data):
        assert 0

class AnimatedMeshParser:
                    
    def __init__(self, materials, textures):            
        self.materials = materials
        self.textures = textures
        
    def process(self, root, path):
        return parseAnimatedMesh(root, path, self.materials, self.textures)                
                
    def processInlined(self, root, data):
        assert 0
        
def parseModels(root, data, materials, textures, statics, effects):
    total_info = GeometryInfo()
    for item in data.models:
        info = parseEntity(root, item.staticMesh, statics, StaticMeshParser(materials, textures))
        if info:    
            total_info += info
        info = parseEntity(root, item.effect, effects, EffectParser(materials, textures))
        if info:    
            total_info += info
        info = parseEntity(root, item.animatedMesh, effects, AnimatedMeshParser(materials, textures))
        if info:    
            total_info += info
    return total_info            
                
def parseDestructibleVisualObject(root, data, statics, effects, materials, textures):
    for item in data.destructionStages:
        parseEntity(root, item.model.staticMesh, statics, StaticMeshParser(materials, textures))
        parseEntity(root, item.model.effect, effects, EffectParser(materials, textures))
        parseEntity(root, item.model.animatedMesh, effects, AnimatedMeshParser(materials, textures))
    return parseModels(root, data, materials, textures, statics, effects)

def parseMonsterVisualObject(root, data, statics, effects, materials, textures):
    return parseModels(root, data, materials, textures, statics, effects)
    
def parseBuilding(root, path, buildings, statics, effects, materials, textures):
    b = openLink(root, path)
    if b.has("BaseVisualObject"):
        return parseModels(root, b.BaseVisualObject, materials, textures, statics, effects)
    elif b.has("DestructibleVisualObject"):    
        return parseDestructibleVisualObject(root, b.DestructibleVisualObject, statics, effects, materials, textures)
    elif b.has("MonsterVisualObject"):    
        return parseMonsterVisualObject(root, b.MonsterVisualObject, statics, effects, materials, textures)
    else:
        assert 0        
    
def parseHero(root, path, materials, textures, statics, effects):
    b = openLink(root, path)
    return parseModels(root, b.HeroVisualObject, materials, textures, statics, effects)

def parseMonster(root, path, materials, textures, statics, effects):
    b = openLink(root, path)
    if b.has("MonsterVisualObject"):    
        return parseMonsterVisualObject(root, b.MonsterVisualObject, statics, effects, materials, textures)
    elif b.has("BaseVisualObject"):
        return parseModels(root, b.BaseVisualObject, materials, textures, statics, effects)
    else:
        assert 0        
    
def _parseGameObject(root, path, o, buildings, statics, effects, materials, textures):
    if o.has('Building'):
        return parseBuilding(root, o.Building.visual.href, buildings, statics, effects, materials, textures)
    elif o.has('Hero'):
        return parseHero(root, o.Hero.visual.href, materials, textures, statics, effects) 
    elif o.has('Town'):
        return parseTown(root, o.Town.pBuildingPlan.href, buildings, statics, effects, materials, textures) 
    elif o.has('Teleport'):
        return parseBuilding(root, o.Teleport.visual.href, buildings, statics, effects, materials, textures) 
    elif o.has('TownBuilding'):
        return parseBuilding(root, o.TownBuilding.visual.href, buildings, statics, effects, materials, textures) 
    elif o.has('StatedGameObject'):
        return parseBuilding(root, o.StatedGameObject.visual.href, buildings, statics, effects, materials, textures) 
    elif o.has('VisualGameObject'):
        return parseBuilding(root, o.VisualGameObject.visual.href, buildings, statics, effects, materials, textures) 
    elif o.has('Monster'):
        return parseMonster(root, o.Monster.visual.href, materials, textures, statics, effects) 
    elif o.has('AdvMapTown'):
        return None
        #return parseTown(root, o.AdvMapTown.town.href, buildings, statics, effects, materials, textures) 
    elif o.has('AdvMapHero'):
        return None
    else:
        assert 0, 'Unknown game object: %r' % path
    
def parseGameObject(root, path, buildings, statics, effects, materials, textures):
    o = openLink(root, path)
    return _parseGameObject(root, path, o, buildings, statics, effects, materials, textures)
        
def parseTown(root, path, buildings, statics, effects, materials, textures):
    b = openLink(root, path)
    total_info = GeometryInfo()
    for item in b.BuildingPlan.buildings:
        info = parseGameObject(root, item.href, buildings, statics, effects, materials, textures)
        if info:
            total_info += info 
    return total_info
        