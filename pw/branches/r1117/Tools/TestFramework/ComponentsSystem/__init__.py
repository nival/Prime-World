import os
import string 
import utils
from installBuilder import InstallBuilder
from copyBuilder import CopyBuilder

def getDefaultSources( patterns, ignored = [], recursive = True ):
    start = globals().get( 'descriptorPath', '.' )
    sources = utils.collectFiles( start, patterns, recursive = recursive, ignored = ignored )
    
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

def getComponentsPathsFromEnvironment():
    paths = os.environ.get( 'ComponentsPath', "" )

    # remove duplicated items and save order
    scope = []
    paths = paths.split( ';' )
    for name in paths:
        if name and name not in scope:
            scope.append( name )
    
    return scope

def _getComponentsPaths( options ):
    globalScope = getComponentsPathsFromEnvironment()

    localScope = [os.getcwd()]
    if options.componentsPaths:
        paths = options.componentsPaths.split( ';' )
        for name in paths:
            if name and name not in globalScope and name not in localScope:
                localScope.append( name )

    return globalScope, localScope            

def getComponentsPaths( options ):
    globalScope, localScope = _getComponentsPaths(options)
    return ';'.join(globalScope), ';'.join(localScope)
    
class Component:

  def __init__(self, componentPath, configuration, options):
    self.componentPath = componentPath
    self.configuration = configuration
    self.options = options
    
  def Load(self, loader, queue):
    componentRoot = os.path.dirname( self.componentPath )
    localVars = {}
    variables = {
        'descriptorPath' : componentRoot,
        'workingDirectory' : os.getcwd(),
        'configuration' : self.configuration,
        'platform' : self.options.platform,
        'testRun' : self.options.testRun,
        'compiler': self.options.compiler,
    }
    globalVariables = globals()
    globalVariables.update( variables )
    savedDirectory = utils.Directory( componentRoot )
    execfile( self.componentPath, globalVariables, localVars )
    
    _components = self.CheckComponents(localVars.get('components', []))
    self.components = []
    for name in _components:
      path = loader.FindComponent(name)
      if path:
        component = loader.GetComponent(path)
        if not component:
          component = Component(path, self.configuration, self.options)
          queue.append(component)
          loader.SetComponent(path, component)
          self.components.append(component)
          
    self.sources = self.CheckSources(localVars.get('sources', []))
    self.moduleType = localVars.get('type', 'exe')
    
    self.localDefines = localVars.get('localDefines', [])
    self.inheritedDefines = localVars.get('defines', [])
    self.globalDefines = localVars.get('globalDefines', [])
    
    self.localCompilerKeys = localVars.get('localCompilerKeys', [])
    self.inheritedCompilerKeys = localVars.get('compilerKeys', [])
    self.globalCompilerKeys = localVars.get('globalCompilerKeys', [])
    
    self.inheritedIncludePaths = localVars.get('includePaths', [])
    self.localIncludePaths = localVars.get('localIncludePaths', [])
    
    self.libs = localVars.get('libs', [])+localVars.get('libDependencies', [])
    self.builders = localVars.get('builders', [])
    self.linkerKeys = localVars.get('linkerKeys', [])
    self.charset = localVars.get('charset', 'ansi')
    self.projectType = localVars.get('projectType', 'win32')
    self.libPaths = localVars.get('libPaths', [])
    
  def CheckSources(self, sources):
    result = []
    for source in sources:
      result.append(os.path.normpath(source))
    return result  
    
  def CheckComponents(self, components):
    return [ name.replace('\\', '/') for name in components ]
    
class ComponentLoader:

  descriptorTemplates = [
      string.Template( r'${path}/${name}.component' ),
      string.Template( r'${path}/${name}.application' ),
      string.Template( r'${path}/${name}/all.component' ),
      string.Template( r'${path}/${name}/${shortName}.component')
  ]
  
  def __init__(self, globalScope, localScope):
    self.globalScope = globalScope
    self.localScope = localScope
    self.cache = {}          
               
  def _FindComponent(self, name, scope):        
    for path in scope:
        mapping = dict( path = path, name = name, shortName = utils.shortName( name ) )
        for template in ComponentLoader.descriptorTemplates:
            instanse = template.substitute( mapping )
            descriptor = os.path.normpath( instanse )
            if os.path.isfile( descriptor ):
                return descriptor
    return None
        
  def FindComponent(self, name):
    path = self._FindComponent(name, self.localScope)
    if not path:
      path = self._FindComponent(name, self.globalScope)
    return path        
    
  def GetComponent(self, path):
    if path in self.cache:
      return self.cache[path]

  def SetComponent(self, path, component):
    self.cache[path] = component               

def ProcessComponent(source, options):
  configurations = ['debug', 'release']
  globalScope, localScope = _getComponentsPaths(options)
  loader = ComponentLoader(globalScope, localScope)
  roots = []
  for configuration in configurations:
		root = Component(source, configuration, options)
		roots.append(root)
		queue = [root]
		while len(queue) > 0:
			component = queue.pop(0)
			component.Load(loader, queue)
  
def ProcessComponents(sources, options):
  for source in sources:
	  ProcessComponent(source.filename, options)
	