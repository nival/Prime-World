import os
from ComponentsSystem import utils
from string import Template

class CompilerOptions:
    def __init__( self, exceptionHandling = None ):
        self.pchUsage = None
        self.pchHeader = None
        self.pchOutput = None
        self.directories = None
        self.obj = None
        self.defines = None
	self.compilerKeys = []
        self.exceptionHandling = exceptionHandling
        self.functionLevelLinking = None
        self.additionalLibraryDirectories = None
        
def getBuildListTemplate():
	return """
		{${py_uuidproj}}.Debug|Win32.ActiveCfg = Debug|Win32
		{${py_uuidproj}}.Debug|Win32.Build.0 = Debug|Win32
		{${py_uuidproj}}.Release|Win32.ActiveCfg = Release|Win32
		{${py_uuidproj}}.Release|Win32.Build.0 = Release|Win32
"""
def getBuildList( py_uuidproj ):
	return Template( getBuildListTemplate() ).safe_substitute( py_uuidproj = py_uuidproj )


def getDependenciesTemplate():
	return """	ProjectSection(ProjectDependencies) = postProject
		{${py_projuuid}} = {${py_projuuid}}
	EndProjectSection
"""
def getDependencies( py_projuuid ):
	return Template( getDependenciesTemplate() ).safe_substitute( py_projuuid = py_projuuid )


def getProjectTemplateStart( projtype = 'vcproj', guid = '8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942' ):
	return """
Project("{""" + guid + """}") = "${py_projname}", "${py_projfilename}.""" + projtype + """", "{${py_uuidproj}}"
"""
def getProjectStart( py_projname, py_uuidproj ):
	return Template( getProjectTemplateStart() ).safe_substitute( py_projname = py_projname, py_uuidproj = py_uuidproj )


def getProjectTemplateEnd():
	return """EndProject
"""


def getFilterTemplate():
	return """
		<Filter
			Name="${py_filtername}"
			>
		</Filter>
"""

def getFilter( py_filtername ):
	return Template( getFilterTemplate() ).safe_substitute( py_filtername = py_filtername )

def getCSProjectConfiguration( configurationName ):
	if configurationName == "debug": return '''
  <PropertyGroup Condition=" '$(Configuration)|$(Platform)' == 'Debug|Win32' ">
    <DebugSymbols>true</DebugSymbols>
    <DebugType>full</DebugType>
    <Optimize>false</Optimize>
    <OutputPath>${py_outputdir}</OutputPath>
    <DefineConstants>DEBUG;TRACE</DefineConstants>
    <ErrorReport>prompt</ErrorReport>
    <WarningLevel>4</WarningLevel>
    <PlatformTarget>x86</PlatformTarget>
    <UseVSHostingProcess>false</UseVSHostingProcess>
  </PropertyGroup>'''
	else: return '''
  <PropertyGroup Condition=" '$(Configuration)|$(Platform)' == 'Release|Win32' ">
    <DebugType>pdbonly</DebugType>
    <Optimize>true</Optimize>
    <OutputPath>${py_outputdir}</OutputPath>
    <DefineConstants>TRACE</DefineConstants>
    <ErrorReport>prompt</ErrorReport>
    <WarningLevel>4</WarningLevel>
    <PlatformTarget>x86</PlatformTarget>
    <UseVSHostingProcess>false</UseVSHostingProcess>
  </PropertyGroup>'''

def getVCProjectConfiguration( configurationName ):
	if configurationName == "debug":
		return '''
		<Configuration
			Name="Debug|Win32"
			OutputDirectory="${py_outputdir}"
			IntermediateDirectory="$(ConfigurationName)\$(ProjectName)"
			ConfigurationType="pyConfigType"
			CharacterSet="${py_charset}"
			WholeProgramOptimization="0"
			>
			<Tool
				Name="VCPreBuildEventTool"
			/>
			<Tool
				Name="VCCustomBuildTool"
			/>
			<Tool
				Name="VCXMLDataGeneratorTool"
			/>
			<Tool
				Name="VCWebServiceProxyGeneratorTool"
			/>
			<Tool
				Name="VCMIDLTool"
			/>
			<Tool
				Name="VCCLCompilerTool"${CompilerAdditionalOptions}
				Optimization="0"${AdditionalIncludeDirectories}${PreprocessorDefinitions}${ExceptionHandling}${EnableFunctionLevelLinking}
				WarningLevel="4"${CompilerKeysInformation}
				DisableSpecificWarnings="4530"
			/>
			<Tool
				Name="VCManagedResourceCompilerTool"
			/>
			<Tool
				Name="VCResourceCompilerTool"
			/>
			${py_prelinktool}
			<Tool
				Name="VCLinkerTool"${LinkerAdditionalOptions}
				LinkIncremental="2"
				AdditionalLibraryDirectories="${py_additionallibrarydirectories}"
				${py_moduledeffile}
				GenerateDebugInformation="true"
				SubSystem="0"
				TargetMachine="1"
			/>
			<Tool
				Name="VCALinkTool"
			/>
			<Tool
				Name="VCManifestTool"
			/>
			<Tool
				Name="VCXDCMakeTool"
			/>
			<Tool
				Name="VCBscMakeTool"
			/>
			<Tool
				Name="VCFxCopTool"
			/>
			<Tool
				Name="VCAppVerifierTool"
			/>
			<Tool
				Name="VCPostBuildEventTool"
			/>
		</Configuration>'''
	else:
		return  '''
		<Configuration
			Name="Release|Win32"
			OutputDirectory="${py_outputdir}"
			IntermediateDirectory="$(ConfigurationName)\$(ProjectName)"
			ConfigurationType="pyConfigType"
			CharacterSet="${py_charset}"
			WholeProgramOptimization="1"
			>
			<Tool
				Name="VCPreBuildEventTool"
			/>
			<Tool
				Name="VCCustomBuildTool"
			/>
			<Tool
				Name="VCXMLDataGeneratorTool"
			/>
			<Tool
				Name="VCWebServiceProxyGeneratorTool"
			/>
			<Tool
				Name="VCMIDLTool"
			/>
			<Tool
				Name="VCCLCompilerTool"${CompilerAdditionalOptions}
				Optimization="2"
				EnableIntrinsicFunctions="true"
				WholeProgramOptimization="false"${AdditionalIncludeDirectories}${PreprocessorDefinitions}${ExceptionHandling}${EnableFunctionLevelLinking}
				BufferSecurityCheck="false"
				EnableEnhancedInstructionSet="2"
				WarningLevel="4"${CompilerKeysInformation}
				DisableSpecificWarnings="4530"
			/>
			<Tool
				Name="VCManagedResourceCompilerTool"
			/>
			<Tool
				Name="VCResourceCompilerTool"
			/>
			${py_prelinktool}
			<Tool
				Name="VCLinkerTool"${LinkerAdditionalOptions}
				LinkIncremental="1"
				AdditionalLibraryDirectories="${py_additionallibrarydirectories}"
				${py_moduledeffile}
				GenerateDebugInformation="true"
				SubSystem="0"
				OptimizeReferences="2"
				EnableCOMDATFolding="2"
				TargetMachine="1"
			/>
			<Tool
				Name="VCALinkTool"
			/>
			<Tool
				Name="VCManifestTool"
			/>
			<Tool
				Name="VCXDCMakeTool"
			/>
			<Tool
				Name="VCBscMakeTool"
			/>
			<Tool
				Name="VCFxCopTool"
			/>
			<Tool
				Name="VCAppVerifierTool"
			/>
			<Tool
				Name="VCPostBuildEventTool"
			/>
		</Configuration>'''
	

def getAdditionalOptionsTemplate():
	return """
				AdditionalOptions="${AdditionalOptions}\""""

def getAdditionalOptions( compilerKeys  = [] ):
    value = '&#x0D;&#x0A;'.join( sorted( compilerKeys ) )
    if value:
       return Template( getAdditionalOptionsTemplate() ).safe_substitute( { 'AdditionalOptions' : value } )
    else:
       return ""
					
def getCompilerOptions( options = '' ):
    compilerOptions = CompilerOptions()

    if options:
        compilerKeys = options.split( "&#x0D;&#x0A;" )
        
        #  { to make compatibility with MSVVC
        removed = set( [] )
        
        for key in compilerKeys:
            if key.find( "/Yc" ) != -1: 
                compilerOptions.pchUsage = "1"
                compilerOptions.pchHeader = key[3:]
                removed.add( key )
            elif key.find( "/Yu" ) != -1:
                compilerOptions.pchUsage = "2"
                compilerOptions.pchHeader = key[3:]
                removed.add( key )
            elif key.find( "/Fp" ) != -1:
                compilerOptions.pchOutput = key[3:]
                removed.add( key )
            elif key.find( "/I" ) != -1:
                #directory = key[len("/I&quot;"):-len("&quot;")]
                directory = key[len("/I"):]
                if not compilerOptions.directories: compilerOptions.directories = [ directory ]
                elif directory not in compilerOptions.directories: compilerOptions.directories.append( directory )
                removed.add( key )
            elif key.find( "/D" ) != -1:
                define = key[len("/D"):].replace( '&quot;', '' )
                define = define.replace( '"', '' )
                if not compilerOptions.defines: compilerOptions.defines = [ define ]
                elif define not in compilerOptions.defines: compilerOptions.defines.append( define )
                removed.add( key )
            elif key.find( "/LIBPATH:" ) != -1:
                libpath = key[len("/LIBPATH:"):].replace( '&quot;', '' )
                if not compilerOptions.additionalLibraryDirectories: compilerOptions.additionalLibraryDirectories = [ libpath ]
                elif libpath not in compilerOptions.additionalLibraryDirectories: compilerOptions.additionalLibraryDirectories.append( libpath )
                removed.add( key )
            elif key.find( "/Fo" ) != -1:
                compilerOptions.obj = key[len("/Fo&quot;"):-len("&quot;")]                
                removed.add( key )
            elif key.find( "/EHsc" ) != -1:
                compilerOptions.exceptionHandling = "1"
                removed.add( key )
            elif key.find( "/EHa" ) != -1:
                compilerOptions.exceptionHandling = "2"
                removed.add( key )
            elif key.find( "/Gy" ) != -1:
                compilerOptions.functionLevelLinking = "true"
                removed.add( key )
            # elif key.find( "/Z7" ) != -1 or key.find( "/Zd" ) != -1 or key.find( "/Zi" ) != -1 or key.find( "/Z" ) != -1:
                # value = key[len("/Z7&quot;"):-len("&quot;")]
                # removed.add( key )
                
        for key in removed: compilerKeys.remove( key )
        # }

        compilerOptions.compilerKeys = compilerKeys
        if compilerOptions.directories: compilerOptions.directories = ";".join( compilerOptions.directories )
        if compilerOptions.defines: compilerOptions.defines = ";".join( compilerOptions.defines )
        if compilerOptions.additionalLibraryDirectories: compilerOptions.additionalLibraryDirectories = ";".join( compilerOptions.additionalLibraryDirectories )

    return compilerOptions


def getFilterTemplateStart():
	return """
		<Filter
			Name="${py_filtername}"
			>
"""


def getFilterTemplateEnd():
	return """		</Filter>
"""


def getFilterStart( py_filtername ):
	return Template( getFilterTemplateStart() ).safe_substitute( py_filtername = py_filtername )


def getCustomBuildTool( filename, configurationName ):
	configurationName == configurationName.capitalize()
	if '.asm64' in filename:
	    if configurationName == "DEBUG":
		text = '''					
				    <FileConfiguration
					    Name="{1}|Win32"
					    >
					    <Tool
						    Name="VCCustomBuildTool"
						    Description="{0}"
						    CommandLine="ml64.exe /c /nologo /Zi /DDEBUG &quot;$(InputPath)&quot;"
						    Outputs="$(IntDir)\$(InputName).obj"
					    />
				    </FileConfiguration>'''.format( "Custom build step: "+utils.fixBackslashes(filename), configurationName )
		return text
	    else:
		text = '''					
				    <FileConfiguration
					    Name="{1}|Win32"
					    >
					    <Tool
						    Name="VCCustomBuildTool"
						    Description="{0}"
						    CommandLine="ml64.exe /c /nologo /Zi &quot;$(InputPath)&quot;"
						    Outputs="$(IntDir)\$(InputName).obj"
					    />
				    </FileConfiguration>'''.format( "Custom build step: "+utils.fixBackslashes(filename), configurationName )
		return text
	elif '.asm' in filename:
	    text = '''					
				<FileConfiguration
					Name="{1}|Win32"
					>
					<Tool
						Name="VCCustomBuildTool"
						Description="{0}"
						CommandLine="ml /c /Zi /coff /nologo /Fo$(IntDir)\$(InputName).obj $(InputPath)"
						Outputs="$(IntDir)\$(InputName).obj"
					/>
				</FileConfiguration>'''.format( "Custom build step: "+utils.fixBackslashes(filename), configurationName )
	    return text
	else:
	    return ""
	    

def getComponentBuildTool( filename, configurationName, hash_code ):
	configurationName == configurationName.capitalize()
	text = '''					
				<FileConfiguration
					Name="{3}|Win32"
					>
					<Tool
						Name="VCCustomBuildTool"
						Description="{2}"
						CommandLine="@echo {1} &gt; $(SolutionDir).components\\{0}&#x0D;&#x0A;"
						Outputs="$(SolutionDir).components\\{0}"
					/>
				</FileConfiguration>'''.format( hash_code, filename, "Updating component "+utils.fixBackslashes(filename)+"...", configurationName )
	return text
	
def getNodeTemplateStart():
	return """
			<File
				RelativePath="pathtemp"
				>"""

def getNodeTemplateEnd():
	return """
			</File>"""
			
def getPCHTemplate():
	return """
						UsePrecompiledHeader="{0}"
						PrecompiledHeaderThrough=\"{1}\"
						PrecompiledHeaderFile=\"{2}\""""
						
def getPCH( pchUsage, pchHeader, pchOutput ):
	if pchUsage and pchHeader and pchOutput: return getPCHTemplate().format( pchUsage, pchHeader, pchOutput )
	else: return ""
    
def getObjectFileTemplate():
    return '''
						ObjectFile=\"{0}\"'''
                        
def getObjectFile( obj ):
    if obj: return getObjectFileTemplate().format( obj )
    else: return ""
                       
def getIncludeDirectoriesTemplate():
	return """
						AdditionalIncludeDirectories=\"{0}\""""

def getIncludeDirectories( directories = "" ):
	if directories: 
		return getIncludeDirectoriesTemplate().format( directories )
	else:
		return ""
        
def getPreprocessorDefinitionsTemplate():
	return """
						PreprocessorDefinitions=\"{0}\""""

def getPreprocessorDefinitions( value = "" ):
    if value: return getPreprocessorDefinitionsTemplate().format( value )
    else: return ""

def getExceptionHandlingTemplate():
    return """
						ExceptionHandling=\"{0}\""""

def getExceptionHandling( value = "" ):
    if value: return getExceptionHandlingTemplate().format( value )
    else: return ""

class Option:

    def __init__(self, name, value):
        self.name = name
        self.value = value
        
    def __call__(self):
        return """
						{0}=\"{1}\"""".format(self.name, self.value)
                        
keysTransition = {
    '/RTCc' : Option("SmallerTypeCheck", True),
    '/GF' : Option("StringPooling", True),
    '/Gm' : Option("MinimalRebuild", True),
    '/RTC1' : Option("BasicRuntimeChecks", 3),
    '/RTCs' : Option("BasicRuntimeChecks", 1),
    '/RTCu' : Option("BasicRuntimeChecks", 2),
    '/RTCsu' : Option("BasicRuntimeChecks", 3),
    '/Z7' : Option("DebugInformationFormat", 1),
    '/Zi' : Option("DebugInformationFormat", 3),
    '/ZI' : Option("DebugInformationFormat", 4),
    '/Gd' : Option("CallingConvention", 0),
    '/Gr' : Option("CallingConvention", 1),
    '/Gz' : Option("CallingConvention", 2),
    '/MT' : Option("RuntimeLibrary", 0),
    '/MTd' : Option("RuntimeLibrary", 1),
    '/MD' : Option("RuntimeLibrary", 2),
    '/MDd' : Option("RuntimeLibrary", 3),
}
                        
def GetCompilerKeysInformation(keys):
    text = ''
    unknownKeys = []
    for key in keys:
        if key in keysTransition:
            text += keysTransition[key]()
#        elif key.startswith('/wd'):
#            print key
        else:
            unknownKeys.append(key)
            
    return text, unknownKeys
    
def getEnableFunctionLevelLinkingTemplate():
    return """
						EnableFunctionLevelLinking=\"{0}\""""


def getEnableFunctionLevelLinking( value = "" ):
    if value: return getEnableFunctionLevelLinkingTemplate().format( value )
    else: return ""
    

def getConfigurationTemplate( configurationName ):
	if configurationName == "debug": return '''
				<FileConfiguration
					Name="Debug|Win32"
					${exclude}
					>
					<Tool
						Name="VCCLCompilerTool"${AdditionalOptions}${PCH}${AdditionalIncludeDirectories}${ObjectFile}${PreprocessorDefinitions}${ExceptionHandling}${EnableFunctionLevelLinking}${CompilerKeysInformation}
					/>
				</FileConfiguration>'''
	else: return '''
				<FileConfiguration
					Name="Release|Win32"
					${exclude}
					>
					<Tool
						Name="VCCLCompilerTool"${AdditionalOptions}${PCH}${AdditionalIncludeDirectories}${ObjectFile}${PreprocessorDefinitions}${ExceptionHandling}${EnableFunctionLevelLinking}${CompilerKeysInformation}
					/>
				</FileConfiguration>'''

def getConfiguration( exclude, configurationName, compilerKeys ):
    if exclude == 'false' and not compilerKeys: 
        return ''
    else:
        #print "WWW", configurationName, compilerKeys
        compilerOptions = getCompilerOptions( "&#x0D;&#x0A;".join( compilerKeys ) )
        
        # print "QQQ"
        # print utils.instance2string( compilerOptions )
        # print "---"
        #print "QQQ", compilerOptions.defines
        compilerTextKeys, unknownCompilerKeys = GetCompilerKeysInformation(compilerKeys)

        mapping = { 
            'PCH' : getPCH( compilerOptions.pchUsage, compilerOptions.pchHeader, compilerOptions.pchOutput ),
            'AdditionalOptions' : getAdditionalOptions( unknownCompilerKeys ),
            'AdditionalIncludeDirectories' : getIncludeDirectories( compilerOptions.directories ),
            'ObjectFile' : getObjectFile( compilerOptions.obj ),
            'PreprocessorDefinitions' : getPreprocessorDefinitions( compilerOptions.defines ),
            'ExceptionHandling' : getExceptionHandling( compilerOptions.exceptionHandling ),
            'EnableFunctionLevelLinking' : getEnableFunctionLevelLinking( compilerOptions.functionLevelLinking ),
            'CompilerKeysInformation' : compilerTextKeys,
        }
        if exclude != 'false':
            mapping['exclude'] = 'ExcludedFromBuild="'+exclude+'"'
        else:
            mapping['exclude'] = ''
        #print "QQQ", configurationName, mapping
        return Template( getConfigurationTemplate( configurationName ) ).substitute( mapping )

def getVCProjTemplate(options):
    f = None
    name = 'vcprojtemplate'
    if options.compiler == 'msvc8':
        name = 'vcprojtemplate.8'
    if 'TestFrameworkPath' in os.environ:
        f = open( os.path.abspath( os.environ['TestFrameworkPath'] ) + '/'+name, 'r' )
    else:
        f = open( name, 'r' )
    return f.read()

def getPreLinkTool( commandLine = "" ):
	if commandLine:
		commandLine = """
				commandLine=\"{0}\"""".format( commandLine )
	return """<Tool
				Name="VCPreLinkEventTool"{0}
			/>""".format( commandLine )


def getCSProjTemplate():
    f = None
    if 'TestFrameworkPath' in os.environ:
        f = open( os.path.abspath( os.environ['TestFrameworkPath'] ) + '/csprojtemplate', 'r' )
    else:
        f = open( 'csprojtemplate', 'r' )
    return f.read()


def getSLNTemplate(options):
    f = None
    name = 'slntemplate'
    if options.compiler == 'msvc8':
        name = 'slntemplate.8'
    if 'TestFrameworkPath' in os.environ:
        f = open( os.path.abspath( os.environ['TestFrameworkPath'] ) + '/'+name, 'r' )
    else:
        f = open( name, 'r' )
    return f.read()

def getSolutionFilesTemplate( filesstr ):
	text = """Project("{2150E333-8FDC-42A3-9474-1A3956D46DE8}") = "Solution Items", "Solution Items", "{347E3938-DA04-4170-8C6A-F0D8B65EC728}"
	ProjectSection(SolutionItems) = preProject
		${py_filesstr}	
	EndProjectSection
EndProject
"""
	return Template( text ).safe_substitute( py_filesstr = filesstr )
