using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Text.RegularExpressions;
using DBCodeGen.CodeGeneration;
using DBCodeGen.Utils;
using DBCodeGen.VisualStudioSupport;
using libdb.DB;
using System.Diagnostics;

namespace DBCodeGen
{
  internal sealed partial class DBCodeGen
  {
    #region Dependencies collectors

    private static List<Type> CollectHierarcyDependencies( Type type )
    {
      if ( TypeUtils.IsResourceType( type ) && type.BaseType != typeof( DBResource ) )
        return new List<Type>( new Type[] { type.BaseType } );
      else
        return null;
    }

    private static List<Type> CollectFieldDependencies( Type type )
    {
      List<Type> result = new List<Type>();
      foreach ( FieldInfo field in GetFields( type, false, string.Empty, null ) )
      {
        Type fieldType = TypeUtils.ExtractType( field.FieldType );
        if ( !DBCodeGen.IsSimpleType( type ) && type.Namespace != typeof( DBPtr<> ).Namespace && fieldType != type )
          result.Add( fieldType );
      }

      if ( type.BaseType != null && type.BaseType != typeof( object ) )
        result.Add( type.BaseType );

      return result;
    }

    #endregion

    #region Components

    private static string GetPathToDescriptor( string descriptor )
    {
      if ( !string.IsNullOrEmpty( descriptor ) )
        return Path.GetDirectoryName( descriptor );
      else
        return ".";
      //return System.Environment.CurrentDirectory;
    }

    #endregion

    private static string ExtractTypeFromArgument( string arg )
    {
      Match m = Regex.Match( arg, @"(const|\*|\&|\s|class|struct|typename)*([A-Za-z0-9_:]+)\s*(const|\*|\&|\s)+[A-Za-z0-9_]*", RegexOptions.Compiled );
      if ( !m.Success || m.Groups.Count < 3 )
        return string.Empty;

      return m.Groups[2].Value;
    }

    private static IEnumerable<string> CollectFactoriesForwards( IEnumerable<Type> types )
    {
      Dictionary<string, bool> result = new Dictionary<string, bool>();
      foreach ( Type type in types )
      {
        FactoryBaseAttribute[] attributes = TypeUtils.GetAttributes<FactoryBaseAttribute>( type, true );
        if ( attributes == null || attributes.Length == 0 )
          continue;
        foreach ( var attribute in attributes )
        {
          if ( !result.ContainsKey( attribute.BaseClassName ) )
            result.Add( attribute.BaseClassName, true );
          foreach ( var arg in attribute.Args )
          {
            string argType = ExtractTypeFromArgument( arg );
            if ( string.IsNullOrEmpty( argType ) || argType.IndexOf( "::" ) < 0 )
              continue;
            if ( !result.ContainsKey( argType ) )
              result.Add( argType, true );
          }
        }
      }
      return result.Keys;
    }

    private static Dictionary<string, List<string>> CollectFactoriesIncludes( IEnumerable<Type> types )
    {
      Dictionary<string, List<string>> result = new Dictionary<string, List<string>>();
      foreach ( Type type in types )
      {
        FactoryImplAttribute[] factoryImpls = TypeUtils.GetAttributes<FactoryImplAttribute>( type, false );
        if ( factoryImpls == null || factoryImpls.Length == 0 )
          continue;

        Dictionary<string, FactoryBaseAttribute> factoryBases = new Dictionary<string, FactoryBaseAttribute>();
        foreach ( var factoryBase in TypeUtils.GetAttributes<FactoryBaseAttribute>( type, true ) )
          factoryBases.Add( factoryBase.FactoryFunctionName, factoryBase );

        foreach ( var factoryImpl in factoryImpls )
        {
          string define = string.Empty;
          FactoryBaseAttribute factoryBase = null;
          if ( factoryBases.TryGetValue( factoryImpl.FactoryFunctionName, out factoryBase ) )
            define = factoryBase.Define;

          List<string> includes = null;
          if ( !result.TryGetValue( define, out includes ) )
          {
            includes = new List<string>();
            result.Add( define, includes );
          }

          foreach ( string include in factoryImpl.Includes )
          {
            if ( includes.IndexOf( include ) < 0 )
              includes.Add( include );
          }
        }
      }

      foreach ( var includes in result.Values )
        includes.Sort();
      return result;
    }

    private static IEnumerable<string> ProcessFile( CodeFile file, List<Type> types, VCSProject resultProject, string customName, string outFolder )
    {
      Trace.TraceInformation( "Generate types ({3}) for file {0} from project {1} for component {2}...",
        file.Name, file.Project, componentDescriptor, string.IsNullOrEmpty( target ) ? "all" : target );

      List<string> files = new List<string>();
      if ( types == null || types.Count == 0 )
      {
        Trace.TraceWarning( "No types for file {0} from project {1}", file.Name, file.Project );
        return files;
      }
      //load dependencies
      List<CodeFile> dependencies = new List<CodeFile>();
      List<CodeFile> forwardFiles = new List<CodeFile>();
      List<Type> forwardTypes = new List<Type>();
      Assembly fileAssembly = types[0].Assembly;

      foreach ( Type type in types )
      {
        foreach ( FieldInfo field in GetFields( type, false, customName, null ) )
        {
          Type fieldType = field.FieldType;
          for ( Type listType = TypeUtils.GetTypeFromList( fieldType ); listType != null; listType = TypeUtils.GetTypeFromList( fieldType ) )
            fieldType = listType;

          if ( fieldType.IsSubclassOf( typeof( DBResource ) ) )
          {
            Trace.TraceError( "Field {1} of class {0} contains DBResource type without DBPtr.", type.Name, field.Name );
            return files;
          }

          if ( fieldType.IsSubclassOf( typeof( DBPtrBase ) ) )
          {
            Type ptrType = TypeUtils.GetTypeFromPtr( fieldType );

            CodeFile forwardFile = CodeFile.CreateFile( ptrType );
            if ( string.IsNullOrEmpty( customName ) && forwardFile != null && forwardFile != file && !forwardFiles.Contains( forwardFile ) )
              forwardFiles.Add( forwardFile );

            if ( ptrType != null && !forwardTypes.Contains( ptrType ) )
              forwardTypes.Add( ptrType );
          }
          else if ( string.IsNullOrEmpty( customName ) && !DBCodeGen.IsSimpleType( type ) && !DBCodeGen.IsSimpleType( fieldType ) && type.Namespace != typeof( DBPtr<> ).Namespace && !TypeUtils.HasAttribute<NoCodeAttribute>( fieldType, false ) )
          {
            CodeFile dependenceFile = CodeFile.CreateFile( fieldType );
            if ( dependenceFile != null && dependenceFile != file && !dependencies.Contains( dependenceFile ) )
              dependencies.Add( dependenceFile );
          }
        }

        if ( string.IsNullOrEmpty( customName ) )
        {
          for ( Type baseType = type.BaseType; baseType != null && !DBCodeGen.IsSimpleType( baseType ); baseType = baseType.BaseType )
          {
            CodeFile dependenceFile = CodeFile.CreateFile( baseType );
            if ( dependenceFile != null && dependenceFile != file && !dependencies.Contains( dependenceFile ) && baseType.Namespace != typeof( DBPtr<> ).Namespace )
              dependencies.Add( dependenceFile );
          }
        }
      }
      dependencies.Sort( CodeFile.Compare );

      //split all types from file to enums, structs and classes
      List<Type> enums = new List<Type>();
      List<Type> structs = new List<Type>();
      List<Type> classes = new List<Type>();

      int csTypes = 0;
      int cppTypes = 0;
      foreach ( Type type in types )
      {
        if ( type.IsEnum )
          enums.Add( type );
        else if ( DBCodeGen.IsResource( type ) )
          classes.Add( type );
        else if ( DBCodeGen.IsStruct( type ) )
          structs.Add( type );

        if ( !string.IsNullOrEmpty( customName ) || !TypeUtils.HasAttribute<NoCSCodeAttribute>( type, false ) )
          ++csTypes;
        if ( !string.IsNullOrEmpty( customName ) || !TypeUtils.HasAttribute<NoCodeAttribute>( type, false ) )
          ++cppTypes;
      }

      if ( enums.Count == 0 && structs.Count == 0 && classes.Count == 0 )
        return files;

      enums.Sort( TypeUtils.Compare );
      if ( !SortTypesByDependencies( structs, CollectFieldDependencies ) )
      {
        Trace.TraceError( "Found circular dependencies in structures for file {0}\\{1}", file.Project, file.Name );
        return files;
      }

      if ( !SortTypesByDependencies( classes, CollectHierarcyDependencies ) )
      {
        Trace.TraceError( "Found circular dependencies in structures for file {0}\\{1}", file.Project, file.Name );
        return files;
      }

      string componentDirectory = GetPathToDescriptor( componentDescriptor );
      string hFileName = Path.Combine( componentDirectory, file.Name + ".h" );
      string cppFileName = Path.Combine( componentDirectory, file.Name + ".cpp" );
      string csFileName = Path.Combine( componentDirectory, file.Name + ".cs" );

      Project project = null;
      if ( solution != null && !solution.IsEmpty && target != "cs" )
      {
        project = solution.GetProject( file.Project );
        if ( project == null )
        {
          Trace.TraceError( "Cannot find project \"{0}\" for file \"{1}\"", file.Project, file.Name );
          return files;
        }
      }

      if ( target != "cs" )
      {
        files.Add( file.Name + ".h" );
        files.Add( file.Name + ".cpp" );
      }
      if ( target != "cpp" )
        files.Add( file.Name + ".cs" );

      string projectPath = outFolder;
      if ( project != null && cppTypes > 0 )
      {
        project.AddFile( hFileName );
        project.AddFile( cppFileName );
        projectPath = project.ProjectPath;
      }

      string resultProjectPath = projectPath;
      if ( resultProject != null && csTypes > 0 )
      {
        resultProject.AddFile( csFileName );
        resultProjectPath = resultProject.ProjectPath;
      }

      CodeWriter hFile = new CodeWriter( Path.Combine( projectPath, hFileName ) );
      CodeWriter cppFile = new CodeWriter( Path.Combine( projectPath, cppFileName ) );
      CodeWriter csFile = new CodeWriter( Path.Combine( resultProjectPath, csFileName ) );

      Header.WriteHeader( hFile );
      Code.WriteHeader( cppFile, file, forwardFiles );
      CSCode.WriteHeader( csFile );

      Header.WriteIncludes( hFile, dependencies );
      Header.WriteFactoryForwardDeclarations( hFile, CollectFactoriesForwards( classes ) );

      Header.WriteOpenNamespace( hFile );
      if ( enums.Count > 0 )
        CodeGeneration.Enum.DeclareBuffer( cppFile );
      Code.WriteRegistration( cppFile, classes, customName );
      Code.WriteFactoryIncludes( cppFile, CollectFactoriesIncludes( classes ) );

      Code.WriteOpenNamespace( cppFile );

      forwardTypes.Sort( TypeUtils.Compare );
      Header.WriteForwardDeclarations( hFile, forwardTypes );

      foreach ( Type type in enums )
        CodeGeneration.Enum.Write( type, customName, hFile, cppFile, csFile, 0 );

      foreach ( Type type in structs )
      {
        if ( !_isSocialTypesProject )
          Struct.Write( type, false, customName, hFile, cppFile, csFile, 0, null );
        else
          Struct.Write( type, false, customName, hFile, cppFile, csFile, 0, GetSocialTypesAttributes() );

      }

      foreach ( Type type in classes )
      {
        if ( !_isSocialTypesProject )
          Struct.Write( type, true, customName, hFile, cppFile, csFile, 0, null );
        else
          Struct.Write( type, true, customName, hFile, cppFile, csFile, 0, GetSocialTypesAttributes() );

      }

      Header.WriteCloseNamespace( hFile );
      Code.WriteCloseNamespace( cppFile );
      CSCode.WriteCloseNamespace( csFile );

      hFile.Close( dryRun || cppTypes == 0 || target == "cs" );
      cppFile.Close( dryRun || cppTypes == 0 || target == "cs" );
      csFile.Close( dryRun || csTypes == 0 || target == "cpp" );

      return files;
    }
  }
}
