import os
import string
import sys
import XmlUtils

def splitPath(path):
    drive, tail = os.path.splitdrive(path)
    folders = string.split(path, '\\')
    if drive:
        folders[0] = drive+'/'
    return folders
    
def compareRelativePath(source, target):
    src_folders = splitPath(source)
    tgt_folders = splitPath(target)

    compare_dirs = map(None, tgt_folders, src_folders)

    for (index, (tgt, src)) in enumerate(compare_dirs):
        if src == None or tgt.lower() != src.lower():
            return index, src_folders, tgt_folders
    return -1, src_folders, tgt_folders

def getRelativePath(source, target):
    index, src_folders, tgt_folders = compareRelativePath(source, target)
    if index > 0:
        paths = tgt_folders[index:]
        for i in range(len(src_folders)-index):
            paths.insert(0, '..')
        return os.path.normpath(os.path.join(*paths))
    elif index == 0:
        return target
    return '.'
   
class Processor:

    def __init__(self):
        self.level = 0
        self.path = []
        self.components = {}

    def process(self, item):
        if item.getName() == 'File':                
            key = '/'.join(self.path)
            if key not in self.components:
                self.components[key] = []
            path = item.RelativePath
            if path.startswith('.\\'):
                path = path[2:]
            self.components[key].append(path)
        
    def incLevel(self, item):
        self.level += 1
        if item.getName() == 'Filter':
            self.path.append(item.Name.replace(' ', '_'))
                
    def decLevel(self, item):
        self.level -= 1
        if item.getName() == 'Filter':
            self.path.pop()
            
class Component:

    def __init__(self, name):
        self.name = name
        self.items = []

    def append(self, path, files):
        self.items.append( (path, files) )
        
class Writer:

    def __init__(self, name):        
        self.f = open(name, 'wb')
        
    def write(self, text):
        self.f.write(text+'\n')        
            
def main(vcproj_path, components_path):        
    text = open(vcproj_path, 'rb').read()
    c = XmlUtils.parseString2(text)


    p = Processor()
    c.VisualStudioProject.Files.enum(p)
    all_components = []
    all_files = []
    components = {}
    for path, files in p.components.items():
        tokens = path.split('/')
        if len(tokens) > 0  and tokens[0]:
            all_components.append(tokens[0])
            if tokens[0] not in components:
                components[tokens[0]] = Component(tokens[0])
            components[tokens[0]].append(tokens[1:], files)    
        else:
            all_files = files

    head, tail = os.path.split(os.path.abspath(vcproj_path))
    component_header = getRelativePath(components_path, head).replace('\\', '/')
    if component_header:
        component_header += '/'
                           
    f = Writer('all.component')        
    f.write('sources = [')
    f.write(',\n'.join([' '*4+"'"+name+"'" for name in all_files]))
    f.write(']')

    f.write('components = [')
    f.write(',\n'.join([' '*4+"'"+component_header+name+"'" for name in list(set(all_components))]))
    f.write(']')

    def generateFiles(files, margin):
        return ',\n'.join([' '*4*margin+"'"+name+"'" for name in files])
       
    for name, component in components.items():
        f = Writer(name+'.component')        
        if len(component.items) == 1 and component.items[0][0] == []:
            f.write('sources = [')
            f.write(generateFiles(component.items[0][1], 1))
            f.write(']')
        else:
            f.write('sources = {')
            for path, files in component.items:
                f.write(' '*4*1+"'"+'/'.join(path).replace('&', '_')+"'"+' : [')
                f.write(generateFiles(files, 2))
                f.write(' '*4*1+'],')
            f.write('}')