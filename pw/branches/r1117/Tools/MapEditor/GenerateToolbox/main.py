import os
import sys
import re

item = '''      <ToolBoxItemData>
        <name>%s</name>
        <category>%s</category>
        <dbIdName>%s</dbIdName>
      </ToolBoxItemData>'''

            
class ComplexConverter:

    def __init__(self, name, tag_name=None):
        self.name = name.lower()
        if tag_name:
            self.tag_name = tag_name
        else:
            self.tag_name = name
    
    def isMatched(self, content, head):
        return '<%s>' % self.tag_name in content
        
    def do(self, tokens, head):
        head = os.path.splitext(head)[0]
        saved_head = head
        has_alphas = re.search('[a-zA-Z]*', head).group(0)
        result = re.search('.*[0-9]', head)
        if result:
            has_numbers = result.group(0)
        else:
            has_numbers = None
        has_name = self.name in head.lower()    
        if has_name or not has_alphas:
            index = len(tokens)-2
            if index <= 0:
                index = 0
            category = tokens[index]
            head = tokens[-1]
            if not has_alphas and has_numbers:
                head += saved_head
                
            if has_name:
                xxx = saved_head.lower().replace(self.name.lower(), '')
                if xxx:
                    head += '_'+xxx
                            
        else:
            category = tokens[-1]
            if category == head:
                category = tokens[-2]
                head = tokens[-1]
        return (category, head)
            
class SimpleConverter:

    def __init__(self, name):
        self.name = name

    def isMatched(self, content, head):
        return '<%s>'% self.name in content
        
    def do(self, tokens, head):
        category = tokens[-1]
        return (category, head)
        
class TerrainConverter:

    def isMatched(self, content, head):
        return '<StaticMesh>' in content
        
    def do(self, tokens, head):
        category = tokens[0]
        if '.' in head:
            head = os.path.splitext(head)[0]                
        return (category, head)
        
def getEntities(root_folder, sub_folder, converters):      
    cwd = os.getcwd()

    os.chdir(root_folder)

    result = []
          
    for root, dirs, files in os.walk(sub_folder):
        for name in files:
            head, tail = os.path.splitext(name)
            if tail.lower() == '.xdb':
                full_path = os.path.normpath(os.path.join(root, name))
                content = open(full_path, 'rb').read()
                tokens = root.split('\\')
                is_found = False
                for converter in converters:
                    if converter.isMatched(content, head):
                        category, head = converter.do(tokens, head)
                        result.append( (category, head, full_path.replace('\\', '/')) )
                        is_found = True
                if not is_found:
                    pass
    os.chdir(cwd)
    return result                
    
def formatEntities(entities):
    result = ''
    for (category, head, full_path) in entities:
        result += item % (head, category, full_path)
    return result        
    
if __name__ == '__main__':    
    if len(sys.argv) >= 2:
        root_folder = os.path.join(sys.argv[1], 'Data')
        print 'Data folder:', root_folder 
        converters = [ComplexConverter('Building'), SimpleConverter('Monster')]
        result = getEntities(root_folder, r'Buildings', converters)\
            +getEntities(root_folder, r'Resources', converters)\
            +getEntities(root_folder, r'Creatures', converters)\
            +getEntities(root_folder, r'Test\SpeedTree', converters)\
            +getEntities(root_folder, r'Terrain\Elements', [TerrainConverter()])\
            +getEntities(root_folder, r'Artifacts', [ComplexConverter('ArtifactResource', 'Building')])\
            +getEntities(root_folder, r'Buildings', [ComplexConverter('Teleport')])\
            +getEntities(root_folder, r'Creatures', [ComplexConverter('Creature')])\
            +getEntities(root_folder, r'Towns', [ComplexConverter('Town')])\
            +getEntities(root_folder, r'Terrain', [ComplexConverter('Building')])
            
        
        config_path = os.path.join(sys.argv[1], 'Profiles', 'H6_Editor.config')
        config = open(config_path, 'rb')
        text = config.read()
        
        start_index = text.find('<toolBoxItems>')+len('<toolBoxItems>')
        end_index = text.find('</toolBoxItems>')
        
        config = open(config_path, 'wb')
        config.write(text[:start_index]+formatEntities(result)+text[end_index:])
        print 'Result: %d entities found, saved to %s' % (len(result), config_path)
    else:
        print 'Usage: main.py <path to the root game folder>'    
