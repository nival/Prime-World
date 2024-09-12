using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using DBCodeGen.CodeGeneration;
using DBCodeGen.SourceCompiler;
using DBCodeGen.Utils;
using DBCodeGen.VisualStudioSupport;

namespace DBCodeGen
{
  internal sealed partial class DBCodeGen
  {
    private enum Result
    {
      Ok = 0,
      Error = -1,
      InvalidArgs = -2,
    }

    private static string srcProjectName = string.Empty;
    private static List<string> srcProjectNames = new List<string>();

    private static List<string> srcFiles = new List<string>();

    private static string solutionFileName = string.Empty;
    private static string destProject = string.Empty;

    private static bool dryRun = false;
    private static bool generateMaterials = false;
    private static string finalMaterialProjectName = string.Empty;

    //Social client code generation
    private const string SOCIAL_TYPES_PROJECT_NAME = "SocialTypes";
    private static bool generateSocialClientCode = false;
    private static string socialClientCodeResultPath = string.Empty;

    //Target component name
    private static string componentDescriptor = string.Empty;
    private static string target = string.Empty;

    private static List<string> hashFiles = new List<string>();
    private static SearchFolders searchFolders = new SearchFolders();

    private static string custom = string.Empty;
    private static string outFolder = ".\\";

    static DBCodeGen()
    {
      RegisterSimpleType( typeof( int ) );
      RegisterSimpleType( typeof( long ) );
      RegisterSimpleType( typeof( float ) );
      RegisterSimpleType( typeof( string ) );
      RegisterSimpleType( typeof( double ) );
      RegisterSimpleType( typeof( bool ) );
      RegisterSimpleType( typeof( Guid ) );
      RegisterRenameType( typeof( int ), "int" );
      RegisterRenameType( typeof( long ), "long" );
      RegisterRenameType( typeof( float ), "float" );
      RegisterRenameType( typeof( string ), "string" );
      RegisterRenameType( typeof( double ), "double" );
      RegisterRenameType( typeof( bool ), "bool" );
    }

    private static int ShowHelp()
    {
      Trace.TraceInformation( "Syntax: DBCodeGen.exe <src_project>|<src_file> [<src_file>...] [options]" );
      Trace.TraceInformation( "	<src_project>: source project with from specified solution. Compatible only with \"solution\" parameter" );
      Trace.TraceInformation( "	<src_file>:	source files with c# resource definitions" );
      Trace.TraceInformation( "Options:" );
      Trace.TraceInformation( "	--solution=<solution>: solutions file with all afected projects. Not compatible with \"out\" parameter" );
      Trace.TraceInformation( "	--project=<project>: project for generated c# code. Compatible only with \"solution\" parameter" );
      Trace.TraceInformation( " --materials[=<final_project>]: genereate materials' code, <final_project> - where material implementation" );
      Trace.TraceInformation( "	--component=<component name>" );
      Trace.TraceInformation( "	--target=<cpp|cs>: generate only specified types of files" );
      Trace.TraceInformation( " --hash=<file_name>: store md5 hash for generated types, this option can be specified many times, format depends on extension" );
      Trace.TraceInformation( " --folders=<folders>: specify folder to search source and include files, use \";\" to specify multiply folders" );
      Trace.TraceInformation( "	--dry-run: do not remove, rename or modify any files" );
      Trace.TraceInformation( "	--custom=<name>: Generate types only with specified custom attribute" );
      Trace.TraceInformation( "	--out=<folder>: Specify output folder" );
      return (int)Result.Ok;
    }

    private static bool TryParaseCommad( string argument, out string command, out string value )
    {
      command = string.Empty;
      value = string.Empty;

      if ( string.IsNullOrEmpty( argument ) )
        return false;

      if ( !argument.StartsWith( "--" ) )
        return false;

      int eqSignPos = argument.IndexOf( '=' );
      if ( eqSignPos < 0 )
      {
        command = argument.Substring( 2 ).ToLower();
        return true;
      }

      command = argument.Substring( 2, eqSignPos - 2 ).ToLower();
      value = argument.Substring( eqSignPos + 1 );
      return true;
    }

    private static bool TryParseArguments( string[] args )
    {
      foreach ( string arg in args )
      {
        string command = string.Empty;
        string value = string.Empty;

        if ( TryParaseCommad( arg, out command, out value ) )
        {
          if ( command == "solution" )
            solutionFileName = value;
          else if ( command == "project" )
            destProject = value;
          else if ( command == "dry-run" )
            dryRun = true;
          else if ( command == "materials" )
          {
            generateMaterials = true;
            finalMaterialProjectName = value;
          }
          else if ( command == "generatesocial" )
          {
            generateSocialClientCode = true;
            socialClientCodeResultPath = value;
          }
          else if ( command == "component" )
            componentDescriptor = value;
          else if ( command == "target" )
            target = value.ToLowerInvariant();
          else if ( command == "hash" )
            hashFiles.Add( value );
          else if ( command == "folders" )
          {
            if ( !searchFolders.AddSearchFolders( value.Split( ';' ) ) )
              return false;
          }
          else if ( command == "custom" )
            custom = value;
          else if ( command == "out" )
            outFolder = value;
        }
        else if ( ( Path.GetExtension( arg ).ToLower() == "" || Path.GetExtension( arg ).ToLower() == ".csproj" ) && string.IsNullOrEmpty( srcProjectName ) )
        {
          srcProjectName = arg;
          srcProjectNames.AddRange( arg.Split( ';' ) );
        }
        else if ( Path.GetExtension( arg ).ToLower() == ".cs" )
          srcFiles.Add( arg );
      }

      if ( string.IsNullOrEmpty( srcProjectName ) && srcFiles.Count == 0 )
      {
        Trace.TraceWarning( "Source files not defined" );
        return false;
      }

      return true;
    }

    private static void SaveGeneratedFiles( string assembly, IEnumerable<string> files )
    {
      try
      {
        string fileName = string.Format( "{0}.generated.sources", assembly );

        StreamWriter stream = new StreamWriter( fileName );
        foreach ( string file in files )
        {
          // make path absolute
          string componentDirectory = GetPathToDescriptor( componentDescriptor );
          stream.WriteLine( Path.Combine( componentDirectory, file ) );
        }
        stream.Close();
      }
      catch ( System.Exception e )
      {
        Trace.TraceError( "Exception {0}: {1}", e.ToString(), e.Message );
      }
    }
    private static List<Type> _socialTypes = null;
    private static bool _isSocialTypesProject  = false;
    static int Main( string[] args )
    {
      Trace.Listeners.Remove( "Default" );
      Trace.Listeners.Add( new ShortConsoleListener( ShortConsoleListener.VerboseLevel.All ) );
      Trace.Listeners.Add( new DebugTraceListener() );

      Trace.TraceInformation( string.Join( " ", args ) );
      Trace.TraceInformation( "C++/C# code generator utility for resource types and materials, (c) 2007-2011, Nival Network" );
      if ( args.Length == 0 )
        return ShowHelp();
      else if ( !TryParseArguments( args ) )
        return (int)Result.InvalidArgs;

      try
      {
        if ( !generateSocialClientCode )
        {
          //RegisterDefaultTypes();
          LoadSolution();
          VCSProject resultProject = null;
          if ( !string.IsNullOrEmpty( destProject ) )
          {
            resultProject = solution.GetProject( destProject ) as VCSProject;
            if ( resultProject == null && !solution.IsEmpty )
            {
              Trace.TraceError( "Cannot find C# project \"{0}\" in solution \"{1}\"", destProject, solutionFileName );
              return (int)Result.Error;
            }
          }

          Assembly assembly = null;
          if ( !string.IsNullOrEmpty( srcProjectName ) )
          //if ( srcProjectNames.Count != 0 )
          {
            string projectName = srcProjectName;

            VCSProject srcProject = null;
            if ( srcProjectName.EndsWith( ".csproj", StringComparison.InvariantCultureIgnoreCase ) )
              srcProject = new VCSProject( projectName );
            else if ( solution != null && !solution.IsEmpty )
              srcProject = solution.GetProject( projectName ) as VCSProject;

            if ( srcProject == null )
            {
              Trace.TraceError( "Cannot find source project project \"{0}\" in solution \"{1}\"", destProject, solutionFileName );
              return (int)Result.Error;
            }

            searchFolders.AddSearchFolder( srcProject.ProjectPath );
            searchFolders.AddSearchFolder( ".\\" );

            assembly = SourceCompiler.SourceCompiler.Compile( srcProject.Files, searchFolders );
            _isSocialTypesProject = srcProject.ProjectName == SOCIAL_TYPES_PROJECT_NAME;

          }
          else
          {
            searchFolders.AddSearchFolder( ".\\" );
            assembly = SourceCompiler.SourceCompiler.Compile( srcFiles, searchFolders );
          }

          if ( assembly == null )
            return (int)Result.Error;

          Dictionary<CodeFile, List<Type>> files = new Dictionary<CodeFile, List<Type>>();
          LoadTypesFromAssembly( assembly, ref files, custom );

          List<string> generatedFiles = new List<string>();

          foreach ( KeyValuePair<CodeFile, List<Type>> file in files )
            generatedFiles.AddRange( ProcessFile( file.Key, file.Value, resultProject, custom, outFolder ) );

          if ( generateMaterials )
            MaterialsGeneration.MaterialCompiler.GenerateMaterialSpecs( solution, assembly, finalMaterialProjectName, dryRun );

          if ( hashFiles.Count > 0 )
            TypesCrc.StoreHash( files, hashFiles, srcProjectName, solution, dryRun );

          //SaveGeneratedFiles( srcAssembly, generatedFiles );
          StoreSolution();
        }
        //Generate social types case
        else
        {
          if ( srcProjectNames.Count == 0 )
          {
            Trace.TraceError( "No projects selected for code generation. Check launch arguments. Projects list example: project1.csproj;project2.csproj..." );
            return 0;
          }

          List<string> _files = new List<string>();

          foreach ( string projectName in srcProjectNames )
          {
            VCSProject project = null;
            if ( projectName.EndsWith( ".csproj", StringComparison.InvariantCultureIgnoreCase ) )
              project = new VCSProject( projectName );

            searchFolders.AddSearchFolder( project.ProjectPath );
            searchFolders.AddSearchFolder( ".\\" );

            if ( project.ProjectName == SOCIAL_TYPES_PROJECT_NAME )
            {
              Assembly socialTypesAssembly = SourceCompiler.SourceCompiler.Compile( project.Files, searchFolders );
              _socialTypes = new List<Type>( socialTypesAssembly.GetTypes() );
            }
            _files.AddRange( project.Files );
          }

          Assembly assembly = SourceCompiler.SourceCompiler.Compile( _files, searchFolders );

          //Cross assemblies types synchronization
          #region
          Dictionary<string, Type> namesToType = new Dictionary<string, Type>();
          foreach ( Type type in _socialTypes )
          {
            namesToType.Add( type.FullName, type );
          }

          foreach ( Type type in assembly.GetTypes() )
            if ( namesToType.ContainsKey( type.FullName ) )
            {
              _socialTypes.Remove( namesToType[type.FullName] );
              _socialTypes.Add( type );
            }
          #endregion
          ProcessAssemblySocial( assembly, _socialTypes, socialClientCodeResultPath );
        }
        return 0;
      }
      catch ( Exception e )
      {
        Trace.TraceError( "Exception {0}: {1}", e.ToString(), e.Message );
        return (int)Result.Error;
      }
    }
  }
}
