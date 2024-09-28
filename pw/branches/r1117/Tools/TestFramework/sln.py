import os
import sys
import templates
import string
from ComponentsSystem import utils
import uuid
import componentAnalyzer
import BuildProject
import fnmatch
import re

from string import Template

def generateFilesText( files ):
    nodetemplatestart = templates.getNodeTemplateStart()
    nodetemplateend = templates.getNodeTemplateEnd()
        
    index = nodetemplatestart.find('pathtemp')
    if index == -1:
        sys.stderr.write( 'Error add cpp file\n' )
        return

    res = ''
    for file in files:
        template = "";
        template += nodetemplatestart[:index] + file.file + nodetemplatestart[index+8:]

        for configurationName in BuildProject.Configuration.configurationNames:
            if file.ignore: exclude = 'true'
            else: exclude = 'false'
            keys = file.getCompilerKeys( configurationName )
            template += templates.getConfiguration( exclude, configurationName, sorted( keys ) )
            if '.component' in file.file or '.application' in file.file:
                template += templates.getComponentBuildTool( file.file, configurationName, utils.calcMD5( file.file ) )
            else:
                template += templates.getCustomBuildTool( file.file, configurationName )
        
        template += nodetemplateend
        template += '\n'
        res += template

    return res


def generateFileFilterTreeText( res, root ):
    if root.filtername:
        res += templates.getFilterStart( root.filtername )
    res += generateFilesText( root.files )
    for child in root.children:
        res = generateFileFilterTreeText( res, child )
    if root.filtername:
        res += templates.getFilterTemplateEnd()
    return res


def addAdditionalCSProjectToSln( strtowrite, proj ):
    projfilename_base = os.path.split( proj.filename )[0] + '/' + proj.name
    strtowrite = addAdditionalProject( strtowrite, proj, projfilename_base, 'csproj', 'FAE04EC0-301F-11D3-BF4B-00C04F79EFBC' )
    return strtowrite


def addAdditionalVCProjectToSln( strtowrite, proj ):
    projfilename_base = os.path.split( proj.filename )[0] + '/' + proj.name
    strtowrite = addAdditionalProject( strtowrite, proj, projfilename_base, 'vcproj', '8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942' )
    return strtowrite


def addAdditionalProject( strtowrite, proj, projFilename, projType, projTypeUUID ):
    idx = strtowrite.find( 'EndProject' )
    lastidx = -1
    while idx != -1:
        lastidx = idx
        idx = strtowrite.find( 'EndProject', lastidx+1 )

    if lastidx == -1:
        idx = strtowrite.find( 'tudio 2008' )
        lastidx = idx

    if lastidx != -1:
        projectTemplate = templates.getProjectTemplateStart( projType, projTypeUUID )
        projectTemplate = Template( projectTemplate ).safe_substitute( py_projname = proj.name, py_uuidproj = proj.uuid.upper(), py_projfilename = projFilename )

        for deppr in proj.dependencies:
            depTemplate = ""
            if proj.platform == ".net":
                depTemplate = templates.getDependencies( deppr[1] )
            else:
                depTemplate = templates.getDependencies( deppr )
            projectTemplate += depTemplate

        projectTemplate += templates.getProjectTemplateEnd()
        strtowrite = strtowrite[:lastidx+10] + projectTemplate + strtowrite[lastidx+11:]
    else:
        sys.stderr.write( 'Error add project %r\n' % proj.name )
        return strtowrite

    lastidx = -1

    if lastidx == -1:
        idx = strtowrite.find( 'stSolution' )
        lastidx = idx

    if lastidx != -1:
        projectTemplate = templates.getBuildList( proj.uuid.upper() )
        strtowrite = strtowrite[:lastidx+10] + projectTemplate + strtowrite[lastidx+11:]
    else:
        sys.stderr.write( 'Error create build list for vcproj ' + proj.name + '\n' )
        return strtowrite

    return strtowrite


additionalProjTypes = {
    '*.csproj' : addAdditionalCSProjectToSln,
    '*.vcproj' : addAdditionalVCProjectToSln,
}


def addAdditionalProjectToSln( strtowrite, proj ):
    for extention, cmd in additionalProjTypes.iteritems():
        if fnmatch.fnmatch( proj.filename, extention ):
            strtowrite = cmd( strtowrite, proj )
    return strtowrite


def addCSProjectToSLN( strtowrite, proj, options ):
    return addProjectToSLN( strtowrite, proj, 'csproj', 'FAE04EC0-301F-11D3-BF4B-00C04F79EFBC', options )


def addVCProjectToSLN( strtowrite, proj, options ):
    return addProjectToSLN( strtowrite, proj, 'vcproj', '8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942', options )


def addProjectToSLN( strtowrite, proj, projtype, guid, options ):
    studioMark = '2008'
    if options.compiler == 'msvc8':
        studioMark = '2005'
    
    idx = strtowrite.find( 'EndProject' )
    lastidx = -1
    while idx != -1:
        lastidx = idx
        idx = strtowrite.find( 'EndProject', lastidx+1 )

    if lastidx == -1:
        idx = strtowrite.find( 'tudio '+studioMark )
        lastidx = idx

    if lastidx != -1:
        projectTemplate = templates.getProjectTemplateStart( projtype, guid )
        projectTemplate = Template( projectTemplate ).safe_substitute( py_projname = proj.getProjectName(), py_uuidproj = proj.uuid.upper(), py_projfilename = proj.getProjectName() )

        for deppr in proj.dependencies:
            depTemplate = ""
            if proj.platform == ".net":
                depTemplate = templates.getDependencies( deppr[1] )
            else:
                depTemplate = templates.getDependencies( deppr )
            projectTemplate += depTemplate

        projectTemplate += templates.getProjectTemplateEnd()
        strtowrite = strtowrite[:lastidx+10] + projectTemplate + strtowrite[lastidx+11:]
    else:
        sys.stderr.write( 'Error add project %r\n' % proj.getProjectName())
        return strtowrite

    lastidx = -1

    if lastidx == -1:
        idx = strtowrite.find( 'stSolution' )
        lastidx = idx

    if lastidx != -1:
        projectTemplate = templates.getBuildList( proj.uuid.upper() )
        strtowrite = strtowrite[:lastidx+10] + projectTemplate + strtowrite[lastidx+11:]
    else:
        sys.stderr.write( 'Error create build list for vcproj ' + proj.getProjectName() + '\n' )
        return strtowrite

    return strtowrite


def generatePreBuildStepScript( scriptname, cppname, output, compilename, handleExceptions, startup, options, runArguments = "" ):
    string = 'import os\nimport sys\nimport subprocess\n\n'

    string += """def runSubprocess( args ):
    a = subprocess.Popen(
        ' '.join(args),
        shell = True,
        stdin = subprocess.PIPE,
        stderr = subprocess.PIPE,
        stdout = subprocess.PIPE)
    textout = a.stdout.read()
    texterr = a.stderr.read()
    a.wait()
    retcode = a.returncode

    return retcode, textout, texterr"""

    filetobuild = compilename
    if not filetobuild:
        filetobuild = cppname
        
    curDir = os.getcwd()
    curDir, temp = os.path.split(curDir)
    temp, autoDir = os.path.split(curDir)
    #string += 'print \"__D\", sys.argv[0]\n'
    string += '\n\nos.chdir( r"'+ os.path.normpath( os.path.abspath( '../..' ) ) +'" )\n'
    string += "verbose = {0}\n".format( options.verblevel )
    string += 'retcode, textout, texterr = runSubprocess( [\'run.cmd\', \'--arguments={0}/{1}.arguments\', {2} ] )\n'.format( autoDir, scriptname, "sys.argv[1]" )
    string += "if texterr:\n\tsys.stderr.write( texterr )\n\tsys.exit(1)\n"
    string += "if verbose >= 1 or retcode != 0: print textout\n"
    string += 'sys.exit(retcode)'

    file = open( scriptname, 'w' )
    file.write( string )
    file.close()
    
    # make argument file
    if not startup: projectOnly = "--projectOnly"
    else: projectOnly = ""
    
    argsList = []
    argsList.append( filetobuild )
    argsList.extend( runArguments )
    if handleExceptions: argsList.append( "--he" )
    if options.stdoutdumper: argsList.append("--stdoutdumper")
    if options.useAutoIncludes: argsList.append("--useAutoIncludes")
    argsList.append( '--generateOnly' )
    argsList.append( '--prebuild' )
    argsList.append( '--verbose={0}'.format( options.verblevel ) )
    argsList.append( '--output={0}'.format( utils.fixBackslashes( output ) ) )
    if options.count > 1:
        argsList.append( '--count={0}'.format( options.count ) )
    argsList.append( projectOnly )

    arguments = '\n'.join( argsList )
    f = open( "{script}.arguments".format( script = scriptname ), "w" )
    f.write( arguments )
    f.close()

    return os.path.normpath( os.path.abspath( '../' + scriptname ) )


def addPreBuildStep( scriptname, strtowrite ):
    '''Add pre build step'''

    prebuildcmd = scriptname + " --configuration=$(ConfigurationName)"
    idx = strtowrite.find( 'Name=\"VCPreBuildEventTool\"' )
    while idx != -1:
        strtowrite = strtowrite[:idx+26] + '\n              CommandLine=\"' + prebuildcmd + "\"\n" + strtowrite[idx+27:]
        idx = strtowrite.find( 'Name=\"VCPreBuildEventTool\"', idx + 1 )

    return strtowrite


def addCsPreBuildStep( scriptname, strtowrite ):
    '''Add pre build step'''

    prebuildcmd = scriptname + " --configuration=$(Configuration)"
    strtowrite = Template( strtowrite ).safe_substitute( { 'py_prebuild' : prebuildcmd } )

    return strtowrite

def detemineSubTypes( files ):
    subTypes = {}
    for file in files:
        name = string.lower( file.file )
        pattern = ".designer."
        if name.find( pattern ) != -1:
            forms = subTypes.setdefault( "Form", set([]) )
            forms.add( string.replace( name, pattern, "." ) )
    return subTypes


def addCsFile( strtowrite, _files, verblevel = 0 ):
    
    subTypes = detemineSubTypes( _files )
    
    # sort files
    files = list( _files )
    files.sort()
    
    fileslist = ''
    for file in files:
        if file.file.find('.resx') != -1:
            filebasename = os.path.splitext(file.file.replace('/','\\'))[0]
            filebasename2 = os.path.split(os.path.splitext(file.file.replace('/','\\'))[0])[1]
            fileslist += "\n    <Compile Include=\"{name}.Designer.cs\">".format( name = filebasename )
            fileslist += "\n      <AutoGen>True</AutoGen>"
            fileslist += "\n      <DesignTime>True</DesignTime>"
            fileslist += "\n      <DependentUpon>{name}.resx</DependentUpon>".format( name = filebasename2 )
            if file.filter:
                fileslist += "\n      <Link>{filter}\\{name}.Designer.cs</Link>".format( filter = "\\".join( file.filter ), name = filebasename2 )
            fileslist += '\n    </Compile>'
            fileslist += "\n    <EmbeddedResource Include=\"{name}\">".format( name = file.file.replace('/','\\') )
            fileslist += "\n      <Generator>ResXFileCodeGenerator</Generator>"
            fileslist += "\n      <LastGenOutput>{name}.Designer.cs</LastGenOutput>".format( name = filebasename2 )
            fileslist += "\n      <SubType>Designer</SubType>"
            if file.filter:
                fileslist += "\n      <Link>{filter}\\{name}</Link>".format( filter = "\\".join( file.filter ), name = os.path.basename( file.file ) )
            fileslist += '\n    </EmbeddedResource>'
        
        elif file.file.find('.Designer.cs') != -1:
            basename = file.file.replace('.Designer.cs','.cs')
            filebasename = os.path.splitext(basename.replace('/','\\'))[0]
            filebasename2 = os.path.split(os.path.splitext(basename.replace('/','\\'))[0])[1]
            fileslist += "\n    <Compile Include=\"{name}.Designer.cs\">".format( name = filebasename )
            fileslist += "\n      <DependentUpon>{name}.cs</DependentUpon>".format( name = filebasename2 )
            if file.filter:
                fileslist += "\n      <Link>{filter}\\{name}.Designer.cs</Link>".format( filter = "\\".join( file.filter ), name = filebasename2 )
            fileslist += '\n    </Compile>'
            if os.path.isfile( basename.replace('.cs','.resx') ):
                fileslist += "\n    <EmbeddedResource Include=\"{name}.resx\">".format( name = filebasename )
                fileslist += "\n      <DependentUpon>{name}.cs</DependentUpon>".format( name = filebasename2 )
                if file.filter:
                    fileslist += "\n      <Link>{filter}\\{name}.resx</Link>".format( filter = "\\".join( file.filter ), name = filebasename2 )
                fileslist += '\n    </EmbeddedResource>'
                
        elif file.file.find('.cs') != -1:
            fileslist += "\n    <Compile Include=\"{name}\">".format( name = file.file.replace('/','\\') )
            if string.lower( file.file ) in subTypes.get( "Form", [] ):
                fileslist += "\n      <SubType>Form</SubType>"
            if file.filter:
                fileslist += "\n      <Link>{filter}\\{name}</Link>".format( filter = "\\".join( file.filter ), name = os.path.basename( file.file ) )
            fileslist += '\n    </Compile>'
        else:
            fileslist += '\n    <Content Include=\"' + file.file.replace('/','\\') + '\">'
            if string.lower( file.file ) in subTypes.get( "Form", [] ):
                fileslist += "\n      <SubType>Form</SubType>"
            if file.filter:
                fileslist += "\n      <Link>{filter}\\{name}</Link>".format( filter = "\\".join( file.filter ), name = os.path.basename( file.file ) )
            if file.file.find('.application') == -1 and file.file.find('.component') == -1:
                fileslist += '\n      <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>'
            fileslist += '\n    </Content>'

    strtowrite = Template( strtowrite ).safe_substitute( { 'py_fileslist' : fileslist } )
    return strtowrite


def setCsType( strtowrite, type, verblevel = 0 ):
    typestr = 'Exe'

    if type == 'console':
        typestr = 'Exe'
    elif type == 'windows':
        typestr = 'WinExe'
    elif type == 'library':
        typestr = 'Library'

    strtowrite = Template( strtowrite ).safe_substitute( { 'py_projtype' : typestr } )
    return strtowrite


def addCppFile( strtowrite, files, verblevel = 0 ):
    '''Add *.cpp files'''

    mainidx = strtowrite.find( '<Files>' )
    if mainidx == -1:
        sys.stderr.write( 'Error add cpp file\n' )
        return strtowrite

    #print "LLL", files
    ffs = utils.generateFileFilterTree( files )
    filesstr = ''
    filesstr = generateFileFilterTreeText( filesstr, ffs )

    strtowrite = strtowrite[:mainidx+8] + filesstr + strtowrite[mainidx+8:]

    return strtowrite


def addInclude( strtowrite, include, verblevel = 0 ):
    '''Add include path'''
    pathstr = ""
    for addstr in include:
        pathstr += '&quot;' + addstr + '&quot;' + ';'
        if verblevel >= 2:
            print 'Add include:', addstr

    if 'IncludePath' in os.environ:
        pathstr += '&quot;' + os.environ['IncludePath'] + '&quot;'
        if verblevel >= 2:
            print 'Add include:', os.environ['IncludePath']

    strtowrite = utils.replaceSubStr( strtowrite, 'aidtemp', pathstr )

    return strtowrite


def addIncludeLib( strtowrite, includeLib, verblevel = 0 ):
    '''Add include lib path'''

    pathstr = ""
    for addstr in includeLib:
        pathstr += '&quot;' + addstr + '&quot;' + ';'
        if verblevel >= 2:
            print 'Add include lib: ', addstr

    if 'IncludeLibPath' in os.environ:
        pathstr += '&quot;' + os.environ['IncludeLibPath'] + '&quot;'
        if verblevel >= 2:
            print 'Add include lib: ', os.environ['IncludeLibPath']

    strtowrite = utils.replaceSubStr( strtowrite, 'aldtemp', pathstr )

    return strtowrite


def addLibs( strtowrite, libDependencies, verblevel = 0 ):
    '''Add libs'''

    pathstr = ""
    for addstr in libDependencies:
        pathstr += addstr + ' '
        if verblevel >= 2:
            print 'Add lib: ', addstr

    if 'LibDependencies' in os.environ:
        pathstr += os.environ['LibDependencies']
        if verblevel >= 2:
            print 'Add lib: ', os.environ['LibDependencies']

    strtowrite = utils.replaceSubStr( strtowrite, 'adtemp', pathstr )

    return strtowrite


def writeVCProjFile( strtowrite, vcprojname ):
    '''Write vcproj file'''
    vcprojfile = open( vcprojname+'.vcproj', 'w' )
    vcprojfile.write( strtowrite )
    vcprojfile.close()


def writeCSProjFile( strtowrite, csprojname ):
    '''Write vcproj file'''
    csprojfile = open( csprojname+'.csproj', 'w' )
    csprojfile.write( strtowrite )
    csprojfile.close()


def setType( strtowrite, typename ):
    typename = typename.lower()

    if typename == 'exe':
        strtowrite = utils.replaceSubStr( strtowrite, 'pyConfigType', '1' )
    elif typename == 'dll':
        strtowrite = utils.replaceSubStr( strtowrite, 'pyConfigType', '2' )
    elif typename == 'lib':
        strtowrite = utils.replaceSubStr( strtowrite, 'pyConfigType', '4' )
    elif typename == 'utility':
        strtowrite = utils.replaceSubStr( strtowrite, 'pyConfigType', '10' )

    return strtowrite


def addCompilerOptions( strtowrite, options = '' ):
    includeDirectories = ""
    compilerOptions = templates.CompilerOptions()
   
    if len( options ):
        compilerOptions = templates.getCompilerOptions( options )
        includeDirectories = templates.getIncludeDirectories( compilerOptions.directories )
    
    if not compilerOptions.exceptionHandling:
        compilerOptions.exceptionHandling = "0"
    

    compilerKeysText, unknownCompilerKeys = templates.GetCompilerKeysInformation( compilerOptions.compilerKeys )
    mapping = { 
        'CompilerAdditionalOptions' : templates.getAdditionalOptions( unknownCompilerKeys ), 
        'AdditionalIncludeDirectories' : includeDirectories,
        'PreprocessorDefinitions' : templates.getPreprocessorDefinitions( compilerOptions.defines ),
        'ExceptionHandling' : templates.getExceptionHandling( compilerOptions.exceptionHandling ),
        'EnableFunctionLevelLinking' : templates.getEnableFunctionLevelLinking( compilerOptions.functionLevelLinking ),
        'CompilerKeysInformation' : compilerKeysText,
        }
    
    return Template( strtowrite ).safe_substitute( mapping )


def addLinkerOptions( strtowrite, options = '' ):
    compilerOptions = templates.getCompilerOptions( options )        
    
    mapping = { 
        'LinkerAdditionalOptions' : templates.getAdditionalOptions( compilerOptions.compilerKeys ),
        'py_additionallibrarydirectories' : compilerOptions.additionalLibraryDirectories
        }

    return Template( strtowrite ).safe_substitute( mapping )


def setCharset( strtowrite, charset ):
    charset_dict = { 'ansi' : '0', 'unicode' : '1', 'multi-byte' : '2' }
    return Template( strtowrite ).safe_substitute( { 'py_charset' : charset_dict[charset] } )


def addClrSupport( strtowrite ):
    idx = strtowrite.find( 'CharacterSet=\"0\"' )
    if idx == -1:
        return strtowrite
    
    strtowrite = strtowrite[:idx+17] + '\t\t\tManagedExtensions="1"\n' + strtowrite[idx+17:]
    
    idx = strtowrite.find( 'CharacterSet=\"0\"', idx+17 )
    if idx == -1:
        return strtowrite

    strtowrite = strtowrite[:idx+17] + '\t\t\tManagedExtensions="1"\n' + strtowrite[idx+17:]

    strtowrite = strtowrite.replace( 'EnableEnhancedInstructionSet=\"2\"', 'EnableEnhancedInstructionSet=\"0\"' )
    strtowrite = strtowrite.replace( 'EnableEnhancedInstructionSet=\"1\"', 'EnableEnhancedInstructionSet=\"0\"' )

    return strtowrite


def setPreLinkTool( strtowrite, verblevel = 0 ):
    strtowrite = Template( strtowrite ).safe_substitute( { 'py_prelinktool' : templates.getPreLinkTool() } )
    strtowrite = Template( strtowrite ).safe_substitute( { 'py_moduledeffile' : '' } )
    return strtowrite


def setPreLinkToolDll( strtowrite, verblevel = 0 ):
    if 'TestFrameworkPath' in os.environ:
        path = os.path.normpath( os.path.abspath( os.environ['TestFrameworkPath'] ) )+ '/'
    else:
        path = ''

    command = r"cd $(IntDir)&#x0D;&#x0A;{0}Vendors\BuildUtils\DefBuild.exe $(ProjectName).def&#x0D;&#x0A;if errorlevel 1 goto checklib&#x0D;&#x0A;:BuildImportLib&#x0D;&#x0A;lib /NOLOGO *.obj /def:$(ProjectName).def /MACHINE:X86 /out:&#x22;$(OutDir)/$(ProjectName).lib&#x22;&#x0D;&#x0A;goto end&#x0D;&#x0A;:checklib&#x0D;&#x0A;if not exist &#x22;$(OutDir)/$(ProjectName).lib&#x22; goto BuildImportLib&#x0D;&#x0A;:end&#x0D;&#x0A;dir&gt;nul&#x0D;&#x0A;".format( path )
    strtowrite = Template( strtowrite ).safe_substitute( { 'py_prelinktool' : templates.getPreLinkTool( command ) } )
    strtowrite = Template( strtowrite ).safe_substitute( { 'py_moduledeffile' : 'ModuleDefinitionFile=\"$(IntDir)\\$(ProjectName).def\"' } )
    return strtowrite


def getRealReference( dependence ):
    dict = { 
        'system.collections.generic' : 'system',
        'system.diagnostics' : 'system',
        'system.reflection' : 'system',
        'system.io' : 'system',
        'system.runtime.interopservices' : 'system',
        'system.text' : 'system',
        'system.xml.serialization' : 'system.xml',
        'microsoft.build.buildengine' : 'microsoft.build.engine',
        }

    for ( key, value ) in dict.iteritems():
        if dependence.lower() == key:
            return value

    return dependence.lower()


def generateReference( dependence ):
    if 'TestFrameworkPath' in os.environ:
        path = os.path.normpath( os.path.abspath( os.environ['TestFrameworkPath'] ) )+ '/'
    else:
        path = ''

    if dependence.lower().find( 'nunit.framework' ) != -1:
        return """\n    <Reference Include="nunit.framework, Version=2.4.8.0, Culture=neutral, PublicKeyToken=96d09a1eb7f44a77, processorArchitecture=MSIL">
      <SpecificVersion>False</SpecificVersion>
      <HintPath>""" + path + """NUnit/nunit.framework.dll</HintPath>
    </Reference>"""

    if dependence.lower().find( 'nunit.mocks' ) != -1:
        return """\n    <Reference Include="nunit.mocks, Version=2.4.8.0, Culture=neutral, PublicKeyToken=96d09a1eb7f44a77, processorArchitecture=MSIL">
      <SpecificVersion>False</SpecificVersion>
      <HintPath>""" + path + """NUnit/nunit.mocks.dll</HintPath>
    </Reference>"""

    if dependence.lower().find( 'nunit.consolerunner' ) != -1:
        return """\n    <Reference Include="nunit-console-runner, Version=2.4.8.0, Culture=neutral, PublicKeyToken=96d09a1eb7f44a77, processorArchitecture=MSIL">
      <SpecificVersion>False</SpecificVersion>
      <HintPath>""" + path + """NUnit/nunit-console-runner.dll</HintPath>
    </Reference>"""


    if dependence.lower().find( 'weifenluo.winformsui.docking') != -1:
        return """\n    <Reference Include="WeifenLuo.WinFormsUI.Docking, Version=2.2.3190.32241, Culture=neutral, processorArchitecture=x86">
      <SpecificVersion>False</SpecificVersion>
      <HintPath>""" + path + """Vendors\WinFormsUI\WeifenLuo.WinFormsUI.Docking.dll</HintPath>
    </Reference>"""

    return '\n    <Reference Include=\"' + dependence + '\" />'


def addReferences( strtowrite, project, verblevel = 0 ):

    dependencies = ''
    #TODO
    for csproj in project.dependencies:
        if csproj:
            if csproj[0].find('#CS#') == -1:
                dependencies += '\n    <ProjectReference Include=\"' + csproj[0] + '.vcproj\">'
                dependencies += '\n      <Project>{' + csproj[1] + '}</Project>'
                dependencies += '\n      <Name>' + csproj[0] + '</Name>'
                dependencies += '\n    </ProjectReference>'
            else:
                dependencies += '\n    <ProjectReference Include=\"' + csproj[0].replace('#CS#','') + '.csproj\">'
                dependencies += '\n      <Project>{' + csproj[1] + '}</Project>'
                dependencies += '\n      <Name>' + csproj[0].replace('#CS#','') + '</Name>'
                dependencies += '\n    </ProjectReference>'

    strtowrite = Template( strtowrite ).safe_substitute( { 'py_dependencies' : dependencies } )

    #project.references.add( 'nunit.consolerunner' )
    
    references = ''
    depsSet = set([])
    for dep in project.references:
        realDep = getRealReference( dep )
        if not realDep in depsSet:
            references += generateReference( realDep )
            depsSet.add( realDep )
    
    strtowrite = Template( strtowrite ).safe_substitute( { 'py_references' : references } )
    
    return strtowrite


def createCSProj( project, options, sources = None, runArguments = "" ):

    if options.verblevel >= 2:
        print 'Create csproj: ', project.getProjectName()
    strtowrite = templates.getCSProjTemplate()
    mapping = { 'py_projname' : project.getProjectName(), 'py_uuidproj' : project.uuid.upper(), 'py_version' : project.getFrameWorkVersion() }
    strtowrite = Template( strtowrite ).safe_substitute( mapping )
    strtowrite = Template( strtowrite ).safe_substitute( { 'py_devenv_version' : options.devenvversion } )
    
    # configuration
    configurations = ""
    type = None
    for configurationName in BuildProject.Configuration.configurationNames:
        configuration = project.getConfiguration( configurationName )
        
        text = templates.getCSProjectConfiguration( configurationName )
        mapping = { 'py_outputdir' : utils.fixBackslashes(project.output) }
        text = Template( text ).safe_substitute( mapping )
        type = configuration.type
        configurations += text

    strtowrite = Template( strtowrite ).safe_substitute( { 'configurations' : configurations } )
    
    strtowrite = addCsFile( strtowrite, project.files, options.verblevel )
    strtowrite = setCsType( strtowrite, type, options.verblevel )
    strtowrite = addReferences( strtowrite, project, options.verblevel )

    scriptname = project.getProjectName() + '.py'

    if project.startup or sources:
        if project.filterName: 
            runArguments = [ project.filterName ] + runArguments
        fullscriptpath = generatePreBuildStepScript( scriptname, sources, project.output, project.compilename, options.exceptions, project.startup, options, runArguments = runArguments )
        strtowrite = addCsPreBuildStep( fullscriptpath, strtowrite )
    else:
        strtowrite = Template( strtowrite ).safe_substitute( { 'py_prebuild' : '' } )

    writeCSProjFile( strtowrite, project.getProjectName() )


def createVCProj( project, options, sources = None, runArguments = "" ):

    if options.verblevel >= 2:
        print 'Create vcproj: ', project.getProjectName()
    strtowrite = templates.getVCProjTemplate(options)

    mapping = { 'py_projname' : project.getProjectName(), 'py_uuidproj' : project.uuid.upper() }
    strtowrite = Template( strtowrite ).safe_substitute( mapping )
    
    # configuration
    configurations = ""
    for configurationName in BuildProject.Configuration.configurationNames:
        text = templates.getVCProjectConfiguration( configurationName )
        
        mapping = { 'py_outputdir' : utils.fixBackslashes(project.output) }
        text = Template( text ).safe_substitute( mapping )
        
        configuration = project.getConfiguration( configurationName )
        text = addCompilerOptions( text, project.getCompilerKeys( configurationName ) )
        text = addLinkerOptions( text, project.getLinkerKeys( configurationName ) )
        text = setType( text, configuration.type )
        
        if configuration.type == 'dll' and not project.isClr:
            text = setPreLinkToolDll( text, options.verblevel )
        else:
            text = setPreLinkTool( text, options.verblevel )
            
        configurations += text
    
    strtowrite = Template( strtowrite ).safe_substitute( { 'configurations' : configurations } )
    # strtowrite = addCompilerOptions( strtowrite, project.getCompilerKeys() )
    # strtowrite = addLinkerOptions( strtowrite, project.getLinkerKeys() )
    # strtowrite = setType( strtowrite, project.type )
    strtowrite = setCharset( strtowrite, project.charset )
    
    strtowrite = addCppFile( strtowrite, project.files, options.verblevel )    
    if project.isClr:
        strtowrite = addClrSupport( strtowrite )

    scriptname = project.getProjectName() + '.py'

    if sources or project.startup:
        if project.filterName: runArguments = [ project.filterName ] + runArguments
        generatePreBuildStepScript( scriptname, sources, project.output, project.compilename, options.exceptions, project.startup, options, runArguments = runArguments )
        strtowrite = addPreBuildStep( scriptname, strtowrite )
    

    writeVCProjFile( strtowrite, project.getProjectName() )


def startpredicate( a, b ):
    if a.startup:
        return -1
    elif b.startup:
        return 1
    else:
        return 0


def getSolutionFiles( files = [] ):
    if not files:
        return ''

    filesstr = ''

    for file in files:
        filesstr += file + ' = ' + file + '\n'

    return templates.getSolutionFilesTemplate( filesstr )


def createProjects( options, projects = [], sources = None, runArguments = "" ):
    if len(projects) == 0:
        sys.stderr.write( "Bad project list" + projects + "\n" )
        return
    
    projects.sort( startpredicate )

    for idx in xrange( 0, len( projects ) ):
        stringtoexec = utils.getPlatformCmd( 'createProj', projects[idx].platform )
        stringtoexec +=  '( projects[idx], options, sources, runArguments = runArguments )'
        exec( stringtoexec )

        if options.verblevel >= 2:
            print 'Create project: ', projects[idx].getProjectName()


def createSLN( slnname, options, projects = [], sources = None, solutionfiles = [], runArguments = "", additionalProjects = [] ):
    if len(projects) == 0:
        sys.stderr.write( "Bad project list" + projects + "\n" )
        return

    if options.verblevel >= 2:
        print 'Create sln: ', slnname

    slntemplate = templates.getSLNTemplate(options)

    slntemplate = Template( slntemplate ).safe_substitute( { 'py_solutionfiles' : getSolutionFiles(solutionfiles) } )

    projects.sort( startpredicate )

    for idx in xrange( 0, len( projects ) ):
        stringtoexec = 'slntemplate = '
        stringtoexec += utils.getPlatformCmd( 'addProjectToSLN', projects[idx].platform )
        stringtoexec +=  '( slntemplate, projects[idx], options )'
        exec( stringtoexec )

        stringtoexec = utils.getPlatformCmd( 'createProj', projects[idx].platform )
        stringtoexec +=  '( projects[idx], options, sources, runArguments = runArguments )'
        exec( stringtoexec )

        if options.verblevel >= 2:
            print 'Add project: ', projects[idx].getProjectName()

    for idx in xrange( 0, len( additionalProjects ) ):
        slntemplate = addAdditionalProjectToSln( slntemplate, additionalProjects[idx] )

    slnname += '.sln'
    slnfile = open( slnname, 'w' )
    slnfile.write( slntemplate )
    slnfile.close()

