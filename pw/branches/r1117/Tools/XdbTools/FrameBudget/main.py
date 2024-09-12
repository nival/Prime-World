import sys      
import os
sys.path.append(os.path.abspath('..'))

import Image
from construct import *  
import XmlUtils
import Xdb
        
def parseTerrain(root, terrain_path, textures, materials):
    elements = Xdb.Counted()
    
    total_elements_count = 0
    
    terrain = Xdb.openLink(root, terrain_path)
    
    for item in terrain.Terrain.geometry.terrainElements:
        elements.append(str(item.terrainObject.href))
        total_elements_count += 1
                
    info = Xdb.GeometryInfo()
    
    for name, count in elements.items():
        full_path = os.path.join(root, Xdb.getPath(name))
        print count, full_path 
        ccc = XmlUtils.parseString2(open(full_path, 'rb').read())
        
        for item in ccc.StaticMesh.materialsReferences:
            if len(item) > 0:
                Xdb.parseInlineMaterial(root, item.TerrainMaterial, textures)
            else:    
                material_path = str(item.href)
                assert '.STAT' not in material_path
                materials.append(material_path)
        # -----------------------------------
        geometry_name = str(ccc.StaticMesh.geometryFileName)
        content = open(Xdb.convertPath(root, geometry_name), 'rb').read()
                
        p = Xdb.Parser(content)
        header = p.parse(Xdb.header_struct, 9*4)                       
        array_header = p.parse(Xdb.array_header_struct, 2*4)
        fragment_header = p.parse(Xdb.fragment_header_struct, 9*4)
        fragment_header2 = p.parse(Xdb.fragment_header_struct, 9*4)
        #print header
        #print fragment_header
        assert 1 == header.fragmentCount
        assert header.commonVertexBufferSizeInBytes == fragment_header.numVertices*fragment_header.vertexStrideSizeInBytes
        assert header.commonIndexBufferSizeInBytes == fragment_header.primitiveCount*3*4
        
        print '    commonVertexBufferSizeInBytes:', header.commonVertexBufferSizeInBytes
        print '    commonIndexBufferSizeInBytes:', header.commonIndexBufferSizeInBytes
        print '    numVertices:', fragment_header.numVertices
        print '    primitiveCount:', fragment_header.primitiveCount
        info.total_vertices_count += fragment_header.numVertices
        info.total_primitives_count += fragment_header.primitiveCount
        info.vertex_buffers_size += header.commonVertexBufferSizeInBytes*count
        info.index_buffers_size += header.commonIndexBufferSizeInBytes*count
        # -----------------------------------
                        
    #    break    
        
        
    print 'Average elements types count', len(elements)    
    print 'Average elements count per map', total_elements_count
    print 'Average vertex count per element type', info.total_vertices_count/len(elements)
    print 'Average triangle count per element type', info.total_primitives_count/len(elements)

class Logger:

    def __init__(self):
        self.stdout = sys.stdout
        sys.stdout = self
        self.margin = 0
        
    def write(self, text):        
        self.stdout.write(' '*self.margin*4+text)
        
    def incMargin(self):        
        self.margin += 1
            
    def decMargin(self):        
        assert self.margin > 0
        self.margin -= 1
        
            
statics = {}
buildings = {}
effects = {}

logger = Logger()

textures = Xdb.Counted()
materials = Xdb.Counted()

root = 'C:\KVR\Data'

advmap = Xdb.openLink('.', sys.argv[1])

print 'Terrain:', advmap.AdvMap.terrain.href
logger.incMargin()
parseTerrain(root, advmap.AdvMap.terrain.href, textures, materials)
logger.decMargin()
    
print 'Objects:'
logger.incMargin()

total_objects_count = 0
objects = Xdb.Counted()
entities = {}    

for index, item in enumerate(advmap.AdvMap.objects):
    if Xdb.isInlined(item.gameObject):
        for name in item.gameObject.__dict__:
            if not name.startswith('_'):
                print index
                entities['inlined'+str(len(entities))] = Xdb._parseGameObject(root, 'inlined', item.gameObject, buildings, statics, effects, materials, textures)
    else:
        path = str(item.gameObject.href)
        objects.append(path)
    total_objects_count += 1

for index, (path, count) in enumerate(objects.items()):
    info = Xdb.parseGameObject(root, path, buildings, statics, effects, materials, textures)
    assert path not in entities
    entities[path] = info
logger.decMargin()

         
print 'Entities:'
logger.incMargin()
for path, info in entities.items():
    if path in objects._items:
        count = objects._items[path]
    else:
        count = 1        
    print '%2d %10s' % (count, path)
    logger.incMargin()
    if info:
        info.out()
    logger.decMargin()
print 'Total entities count:', total_objects_count
logger.decMargin()

print 'Statics:'
logger.incMargin()
total_info = Xdb.GeometryInfo()
for path, info in statics.items():
    total_info += info
    print path
    logger.incMargin()
    info.out()
    logger.decMargin()
print 'Overall: %d' % len(statics)
total_info.out()            
logger.decMargin()

print 'Materials:'
logger.incMargin()
for path, count in materials.items():
    print '%2d %s' % (count, path)
    Xdb.parseMaterial(root, path, textures)
logger.decMargin()

print 'Textures:'
logger.incMargin()
total_texture_size = 0
missed_textures = []
for path, count in sorted(list(textures.items())):
    print '%2d %s' % (count, path)
    full_path = Xdb.convertPath(root, path)
    if os.path.isfile(full_path):
        total_texture_size += os.path.getsize(full_path)*1.5
    else:
        missed_textures.append(path)    
print 'Total texture gpu size', total_texture_size    
logger.decMargin()

print effects
print 'Missed textures:'
logger.incMargin()
for name in missed_textures:
    print name
logger.decMargin()

