import sys
import os

def ConvertPath(path):
    return path.replace('\\', '/') 

class Component:

    def __init__(self, name, path, minPath):
        self.globalCompilerKeys = []
        self.localCompilerKeys = []
        self.includePaths = []
        self.inheritCompilerKeys = []
        self.sources = []
        self.headers = []
        self.libraries = []
        self.name = name
        self.components = []
        self.linkerKeys = []
        self.path = os.path.normpath(path)
        self.fullName = os.path.join(os.path.relpath(self.path, minPath), self.name).replace('/', '\\')
        self.fullNameQual = self.fullName.replace('\\', '_').replace('.', '_')

    def Process(self, g, l):
        self.globalCompilerKeys.extend(l.get('globalCompilerKeys', [])+['/D '+name for name in l.get('globalDefines', [])])
        self.localCompilerKeys.extend(l.get('localCompilerKeys', [])+['/D '+name for name in l.get('localDefines', [])])
        self.inheritCompilerKeys.extend(l.get('compilerKeys', [])+['/D '+name for name in l.get('defines', [])])
        self.includePaths.extend([os.path.abspath(p) for p in l.get('includePaths', [])+['.']])
        self.linkerKeys.extend(l.get('linkerKeys', []))
 
        libs = l.get('libs', [])+l.get('libDependencies', [])
        self.libraries = [name.replace('.lib', '') for name in libs]
        self.components = [name.replace('\\', '/') for name in l.get('components', [])]
        _sources = l.get('sources', [])
        if type(_sources) == list:
            sources = _sources
        elif type(_sources) == dict:
            sources = []
            for key, values in _sources.items():
                for value in values:
                    sources.append(value)
        for name in sources:
            tail, ext = os.path.splitext(name)
            self.sources.append(name)


def LoadComponent(path, minPath):
    head, tail = os.path.split(path)
    name, ext = os.path.splitext(tail)
    cname = name.replace(' ', '_')    

    cwd = os.getcwd()

    class Settings:
        def get(self, name):
            return None
    class Features:
        def __init__(self, param):
            pass
    class RPCBuilder:
        def __init__(self, *param):
            pass
    class CodeGen:
        def __init__(self, *param):
            pass
    class ThriftBuilder:
        def __init__(self, path, lang, output=''):
            pass
    class InstallBuilder:
        def __init__(self, path, folder=None):
            pass
    settings = Settings()
        
    p = {
        'settings' : settings,
        'configuration' : 'debug',
        'platform' : 'win32',
        'Win32Features' : Features,
        'RPCBuilder' : RPCBuilder,
        'CodeGen' : CodeGen,
        'testRun' : False,
        'ThriftBuilder' : ThriftBuilder,
        'InstallBuilder' :  InstallBuilder,
        'descriptorPath' : path,
        'getDefaultSources' : getDefaultSources,
    }
    g = globals()
    g.update(p)

    l = {}

    os.chdir(head)
    execfile(path, g, l)

    c = Component(cname, head, minPath)
    c.Process(g, l)

    os.chdir(cwd)
    return c

class ComponentFinder:

    def __init__(self):
        path = '..'
        fpath = None
        rpath = None
        while True: 
            rpath = os.path.abspath(path)
            fpath = os.path.join(rpath, 'unittest.cfg') 
            if os.path.isfile(fpath):
                break
            else:
                path += '/..'
        l = {}  

        class Env:      
            def __init__(self):
                self.items = {}

            def Append(self, name, value):
                pvalue = self.items.get(name, None)
                if pvalue is None:
                    self.items[name] = value
                else:
                    self.items[name] += ';'+value
    
            def SetValue(self, name, value):
                pass

            def Set(self, name, value):
                pass

        env = Env()
        execfile(fpath, {'env' : env}, l)

        self.paths = []
        self.minPath = ''
        self.minLen = 1000
        for name in env.items.get('ComponentsPath', '').split(';'):
            fpath = os.path.abspath(os.path.join(rpath, name))
            self.paths.append(fpath)
            if len(fpath) < self.minLen:
                self.minPath = fpath
                self.minLen = len(fpath)

    def Find(self, rpath, name):
        paths = [os.path.abspath(rpath)]+self.paths
        head, tail = os.path.split(name)
        for path in paths:
            cpath = os.path.join(path, name)+'.component'
            if os.path.isfile(cpath):
                return os.path.normpath(cpath)
            cpath = os.path.join(path, name, 'all')+'.component'
            if os.path.isfile(cpath):
                return os.path.normpath(cpath)
            cpath = os.path.join(path, name, tail)+'.component'
            if os.path.isfile(cpath):
                return os.path.normpath(cpath)

        return None

def collectFiles(path, patterns, ignored = [], recursive=True, add_root=True):
    result = []
    for root, dirs, files in os.walk(path):
        for name in files:
            relativePath = os.path.join( root, name )[len(path)+1:]
            if matchPatterns(relativePath, patterns, ignored):
                value = os.path.join(root, name)
                if not add_root:
                    value = value[len(path)+1:]    
                result.append(value)
        if not recursive:
            break                    
    return result

def getDefaultSources( patterns, ignored = [], recursive = True ):
    start = globals().get( 'descriptorPath', '.' )
    sources = collectFiles( start, patterns, recursive = recursive, ignored = ignored )
    
    result = {}
    for source in sources:
        if os.path.isfile( source ):
            key = string.replace( os.path.dirname( source ), ".\\", "" )
            key = string.replace( key, ".", "" )
            key = string.replace( key, "\\\\", "\\" )
            key = string.replace( key, "\\", "/" )

            if key in result: result[key].append( source )
            else: result[key] = [ source ]
    
    return result

def ParseTestFile(finder, root, path):
    root.sources.append(path)
    f = open(os.path.join(root.path, path), 'rb')
    for _line in f.readlines():
        line = _line.strip()
        if line:
            if line.startswith('//'):
                if line.startswith('//!Component('):
                    line = line.replace('//!Component(', '').replace(')', '').replace('\'', '')
                    root.components.append(line)
            else:
                break
    root.components.append('Tools/TestFramework/cxxtest')

def Main():
    app = os.path.abspath(sys.argv[1])
    if not os.path.isfile(app):
        print 'Error: file %r not found' % app
        return False

    head, tail = os.path.split(app)
    name, ext = os.path.splitext(tail)

    application = False
    if ext.lower() in ['.application', '.component']:
        application = True

    project = name.replace(' ', '_')    
    print 'Project: %r' % project

    appPath = os.path.abspath(os.path.join(head, project+'.auto'))
    if not os.path.isdir(appPath):
        os.makedirs(appPath)

    finder = ComponentFinder()
    print 'Source root: %r' % finder.minPath    

    if application:
        root = LoadComponent(app, finder.minPath)
    else:   
        root = Component(project, head, finder.minPath)
        ParseTestFile(finder, root, tail)

    components = {}
    components[None] = root
    
    processed = []
    queue = [ name for name in root.components]
    pqueue = [ root for name in root.components]
    count = 0
    while len(queue) > 0:
        name = queue.pop()
        parent = pqueue.pop()
        processed.append(name)
        path = finder.Find(parent.path, name)
        print 'Searching component %r' % name,
        
        if path:
            print '-> %r' % path
            assert path not in components
            c = LoadComponent(path, finder.minPath)
            components[c.fullName] = c
            for name in c.components:
                if name not in queue and name not in processed:
                    queue.append( name )
                    pqueue.append( c )
        else:
            print
            raise Exception('Component %r not found' % name)
        count += 1

    mainTmpl = '''cmake_minimum_required(VERSION 2.8)
project(${project})

${components}

${sources} 

set(LIBRARIES ${libraries})

SET(COMPILE_FLAGS "${compiler_keys}")
add_definitions(${COMPILE_FLAGS})

${include_paths}

set(CMAKE_EXE_LINKER_FLAGS "${linker_keys}")

add_executable(${project} ${SOURCES})   
TARGET_LINK_LIBRARIES(${project} ${LIBRARIES})
'''

    componentTmpl = '''
set(SOURCES_${component} ${sources})
set(LIBRARIES_${component} ${libraries})
'''

    srcTmpl = '''
set(SOURCES_${cname}_ROOT ${crelpath})
foreach(f ${SOURCES_${cname}} )
    LIST(APPEND SOURCES ${SOURCES_${cname}_ROOT}/${f};)
    LIST(APPEND SOURCES_${cname}_gen ${SOURCES_${cname}_ROOT}/${f};)
endforeach()
source_group(${folder} FILES ${SOURCES_${cname}_gen})
'''
    from string import Template
    sources = ''
    for c in components.values():
        path = ConvertPath(os.path.relpath(c.path, appPath))
        folder = c.fullName.replace('\\', '\\\\')
        params = {
            'cname' : c.fullNameQual,
            'crelpath' : path,
            'folder' : folder,
        }
        sources += Template(srcTmpl).safe_substitute(params)    

    for name, c in components.items():
        params = {
            'component' : c.fullNameQual,
            'sources' : ' '.join([ConvertPath(name) for name in c.sources]),
            'libraries' : ' '.join(c.libraries),
        }
        code = Template(componentTmpl).safe_substitute(params)    
        cpath = os.path.join(c.path, c.name)+'.cmake'
        open(cpath, 'wb').write(code)
        print 'Component script written to %r' % cpath

    globalCompilerKeys = []
    includePaths = []
    linkerKeys = []
    for c in components.values():
        globalCompilerKeys.extend(c.globalCompilerKeys)
        includePaths.extend(c.includePaths)
        linkerKeys.extend(c.linkerKeys)
    globalCompilerKeys = set(globalCompilerKeys)
    includePaths = set(includePaths+finder.paths)
    linkerKeys = set(linkerKeys)    
    if globalCompilerKeys:
        print 'Global compiler keys: %r' %  list(globalCompilerKeys)
    if linkerKeys:
        print 'Linker keys: %r' %  list(linkerKeys)
    if includePaths:
        print 'Include paths: %r' %  list(includePaths)

    params = {
        'project' : root.name,
        'compiler_keys' : ' '.join(globalCompilerKeys),
        'include_paths' : '\n'.join(['include_directories(%s)' % ConvertPath(os.path.relpath(c, appPath)) for c in includePaths]),
        'sources' : sources,     
        'libraries' : ' '.join(['${LIBRARIES_%s}' % c.name for c in components.values()]),     
        'components' : '\n'.join(['include(%s.cmake)' % ConvertPath(os.path.relpath(os.path.join(c.path, c.name), appPath)) for c in components.values()]),
        'linker_keys' : ' '.join(linkerKeys),
    }
    code = Template(mainTmpl).safe_substitute(params)    
    open(os.path.join(appPath, 'CMakeLists.txt'), 'wb').write(code)
    print 'Application script written to %r' % appPath
    
Main()