import sys
import os
import copy

class Envo:

    def __init__(self, path = '', env=os.environ):
        self.path = path
        if self.path: self.path += '/'
        self.env = env

    def __getitem__(self, key):
        return self.env[key]
        
    def __setitem__( self, key, item ):
        self.Set( key, item )
        
    def __contains__( self, item ):
        return item in self.env

    def normilizePath( self, path ):
        if not os.path.isabs( path ):
            path = os.path.normpath( self.path + path )
        return path

    def Prepend( self, b, c ):
        c = self.normilizePath( c )
        if b in self.env: self.env[b] = c + ';' + self.env[b]
        else: self.env[b] = c + ';'

    def Append( self, b, c ):
        c = self.normilizePath( c )
        if b in self.env: self.env[b] = self.env[b] + c + ';'
        else: self.env[b] = c + ';'

    def Remove( self, b, c ):
        c = self.normilizePath( c )

        c = c + ';'
        start = self.env[b].find( c )
        if start != -1:
            if start == 0 or self.env[b][start-1] == ';':
                end = start + len( c )
                self.env[b] = self.env[b][:start] + self.env[b][end:]

    def Set( self, b, c, normFlag=True):
        if normFlag:
            self.env[b] = self.normilizePath( c )
        else:
            self.env[b] = c

    def SetValue( self, b, c ):
        self.Set(b, c, False)

    def Get(self):
        return self.env


class ContainerHolder:

    def __init__( self, new, old ):
        self.current = new
        self.old = copy.copy( old )
        old = self.current      
    
    def __del__( self ):
        self.current = copy.copy( self.old )        
        
def InitializeEnvironment():
    env = Envo( env = copy.copy( os.environ ) )
    env['INCLUDE'] = ""
    env['LIB'] = ""
    
    pathHolder = ContainerHolder( new = copy.copy( sys.path ), old = sys.path )
    if "TestFrameworkPath" in env:
        sys.path.append( os.path.abspath( env['TestFrameworkPath'] ) )
    return ContainerHolder( new = env.Get(), old = os.environ ), pathHolder
        