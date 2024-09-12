import exceptions
import os
import fnmatch
from ComponentsSystem import utils
import re
import string
import platform

supportedPlatforms = [ 'win32', 'linux', '.net' ]

#
# Get OS index: 0 - Windows, 1 - Linux
#
def getOS() :
  if platform.system() == 'Linux' : return supportedPlatforms[1]
  elif platform.system() == 'Windows' : return supportedPlatforms[0]
  # Failed to identify, suppose it's Windows
  return supportedPlatforms[0]

def getDefaultCompiler() :
  if getOS() == 'linux' : return "cmake"
  return "msvc9"

def determinePlatform( name ):
    if name:
        if fnmatch.fnmatch( name, '*.cpp' ) or fnmatch.fnmatch( name, '*.h' ):
            return getOS()
        if fnmatch.fnmatch( name, '*.cs' ):
            return supportedPlatforms[2]
    return getOS()


decriptorPath = ''

class Feature:
    
    def __init__( self ):
        #self.root = utils.removeUnusedSeparator( root )
        self.root = decriptorPath
    
    def __str__( self ):
        return utils.instance2string( self )
        
    def __repr__( self ):
        return str( self )
        
    def Inline( self ):
        pass
        
    def Process( self, project ):
        '''Peform platform specific tasks befor project creation'''
        pass
        
    def Apply( self, component, configurationName, compilerKeys ):
        pass


class Win32Features( Feature ):
    
    def __init__( self, pch = "", isClr = False ):
        Feature.__init__( self )
        if os.path.isfile( pch ): pch = [ os.path.normpath( os.path.abspath( pch ) ) ]
        else: pch = []
        self.pchs = { ".all" : set( pch ) }
        self.isClr = isClr
        
    def Inline( self, feature ):
        assert type( feature ) == type( self )
        assert not self.isClr or not feature.isClr
        for key in feature.pchs.keys():
            self.pchs.setdefault( key, set( [] ) ).update( feature.pchs[key] )
            
    @staticmethod
    def createPCHCode( includes ):
        if includes:
            lines = [ "// !!! Auto generated file, do not edit !!!" ]
            lines.append( "#pragma once" )
            lines.append( "" )
            for item in includes:
                lines.append( "#include \"{0}\"".format( item ) )
                
            return "\n".join( lines )
        else:
            return ""

    def Process( self, project ):
        '''Call while files generation project files...'''
        for key, value in self.pchs.iteritems():            
            if key != ".all":
                text = Win32Features.createPCHCode( value )
                
                if os.path.isfile( key ):
                    hash = utils.calculateMD5ForFile( key )
                    if hash == utils.calcMD5( text ):
                        continue
                
                try: os.makedirs( os.path.dirname( key ) )
                except: pass
                file = open( key, 'wb' )
                file.write( text )
                file.close()
                
        if self.isClr: project.SetClr( True )
        
    def __repr__( self ):
        return str( self )
        
    def __str__( self ):
        return utils.instance2string( self )
        
    createdPCH = {}
    def DeteminePCH( self, componentName, compilerKeys ):
        componentName = string.replace( componentName, "/", "." )
        
        contentHash = 0
        for key in compilerKeys:
            contentHash ^= int( utils.calculateHash( key ), 16 )
        contentHash ^= int( utils.calculateHash( self.pchs.get( ".all", [] ), evaluateFiles = False ), 16 )
        
        #print "VVV", componentName, self.pchs.get( ".all", [] ), contentHash
        if contentHash in Win32Features.createdPCH:
            return Win32Features.createdPCH[contentHash]
        else:
            pch = os.path.abspath( ".pch/{0}.pch.h".format( componentName ) )
            pchcpp = os.path.abspath( ".pch/{0}.pch.cpp".format( componentName ) )
            pchobj = "$(IntDir)\{0}.pch".format( componentName )
            
            Win32Features.createdPCH[contentHash] = ( pch, pchcpp, pchobj )
            return pch, pchcpp, pchobj
        
    @staticmethod
    def IsPCHSetted( info, configurationName ):
        return info.HasCompileKey( configurationName, "/Fp" )
    
    @staticmethod
    def getPCHSource( component, pch, pchcpp ):
        pchInfo = None
        pchcppInfo = None
        
        for infos in component.sources.values():
            for info in infos:
                if info.file == pch:
                    pchInfo = info
                elif info.file == pchcpp:
                    pchcppInfo = info

        if not pchInfo: pchInfo = component.AddSource( pch, ".pch" )
        if not pchcppInfo: pchcppInfo = component.AddSource( pchcpp, ".pch" )
        
        return pchInfo, pchcppInfo
        
    def Apply( self, component, configurationName, compilerKeys ):
        if self.pchs[".all"]:
            pch, pchcpp, pchobj = self.DeteminePCH( component.name, compilerKeys )
            
            # if pchcpp.find( "System.PerfLog.pch.cpp" ) != -1:
                # print "NNN", component.name, compilerKeys
                
            pchInfo, pchcppInfo = Win32Features.getPCHSource( component, pch, pchcpp )
            pchcppInfo.addKey( configurationName, "/FI&quot;{0}&quot;".format( pch ) )
            pchcppInfo.addKey( configurationName, "/Fp&quot;{0}&quot;".format( pchobj ) )
            pchcppInfo.addKey( configurationName, "/Yc&quot;{0}&quot;".format( pch ) )

            for infos in component.sources.values():
                for info in infos:
                    if not Win32Features.IsPCHSetted( info, configurationName ):
                        info.addKey( configurationName, "/FI&quot;{0}&quot;".format( pch ) )
                        info.addKey( configurationName, "/Fp&quot;{0}&quot;".format( pchobj ) )
                        info.addKey( configurationName, "/Yu&quot;{0}&quot;".format( pch ) ) 

            self.pchs.setdefault( pchInfo.file, set( [] ) ).update( self.pchs[".all"] )
            self.pchs[pchcppInfo.file] = set( [] )
            
            #print self.pchs

class LinuxFeatures( Feature ):
    
    def __init__( self ):
        Feature.__init__( self )
