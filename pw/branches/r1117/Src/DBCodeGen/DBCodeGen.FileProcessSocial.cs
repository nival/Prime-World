using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using DBCodeGen.CodeGeneration;
using DBCodeGen.SocialClientCodeGeneration;
using DBCodeGen.Utils;
using DBCodeGen.VisualStudioSupport;
using libdb.DB;

namespace DBCodeGen
{
  internal sealed partial class DBCodeGen
  {
    const string customName = "Social";

    private static IEnumerable<string> ProcessAssemblySocial( Assembly assembly, List<Type> predefinedTypes, string resultPath )
    {
      Dictionary<CodeFile, List<Type>> sourceFiles = new Dictionary<CodeFile, List<Type>>();

      Trace.TraceInformation( "Loading files from assembly {0} with Custom('{1}') attribute.", assembly.FullName, customName );
      LoadTypesFromAssembly( assembly, ref sourceFiles, customName );
      Trace.TraceInformation( "{0} files loaded.", sourceFiles.Count );
      List<string> files = new List<string>();
      Dictionary<Type, List<FieldInfo>> typesWithCustomFields = new Dictionary<Type, List<FieldInfo>>();
      Dictionary<Type, List<FieldInfo>> referencedTypesWithoutCustomAttr = new Dictionary<Type, List<FieldInfo>>();
      Dictionary<Type, List<FieldInfo>> typesWithCustomAttribute = new Dictionary<Type, List<FieldInfo>>();

      //Adding predefined types
      foreach ( var type in predefinedTypes )
        typesWithCustomAttribute.Add( type, new List<FieldInfo>( GetFields( type, false, string.Empty, null ) ) );

      //Collecting types
      foreach ( KeyValuePair<CodeFile, List<Type>> f in sourceFiles )
      {
        CodeFile file = f.Key;
        List<Type> types = f.Value;

        Trace.TraceInformation( "Generate types ({3}) for file {0} from project {1} for component {2}...",
          file.Name, file.Project, componentDescriptor, string.IsNullOrEmpty( target ) ? "all" : target );

        if ( types == null || types.Count == 0 )
        {
          Trace.TraceWarning( "No types for file {0} from project {1}", file.Name, file.Project );
          return files;
        }

        //Collecting types with custom attrbites and with fields marked with custom attributes
        foreach ( Type type in types )
        {
          //Adding all types with Custom attribute);
          if ( IsSocialType( type ) )
          {
            TryToAdd( typesWithCustomAttribute, type, new List<FieldInfo>( GetFields( type, false, string.Empty, null ) ) );

            //Adding enums inside Custom defined types
            foreach ( FieldInfo en in GetEnums( type ) )
              TryToAdd( typesWithCustomAttribute, en.FieldType, new List<FieldInfo>() );
          }
          else
          {
            //Adding all types with custom attribute marked fields
            List<FieldInfo> fieldsWithCustomAttr = new List<FieldInfo>( GetFields( type, false, customName, null ) );
            if ( fieldsWithCustomAttr.Count > 0 )
            {
              TryToAdd( typesWithCustomFields, type, fieldsWithCustomAttr );
            }
          }
        }
      }

      Dictionary<Type, List<FieldInfo>> allCollectedTypes = CombineDictionaries( typesWithCustomFields,
                                                                                 typesWithCustomAttribute ) as Dictionary<Type, List<FieldInfo>>;

      Dictionary<Type, List<FieldInfo>> excludedDBResources = new Dictionary<Type, List<FieldInfo>>();
      //Collecting types, referenced in fields of collected types (Without custom attribute));
      foreach ( var pair in allCollectedTypes )
      {
        Type type = pair.Key;
        foreach ( FieldInfo field in pair.Value )
        {
          Type fieldType = field.FieldType;

          if ( fieldType.IsSubclassOf( typeof( DBResource ) ) )
          {
            Trace.TraceError( "Field {1} of class {0} contains DBResource type without DBPtr.", type.Name,
                              field.Name );
            return files;
          }
          fieldType = GetFieldTypeFromListOrPtr( field );

          //Collection not simple(system) types, that are not inherites DBResource
          if ( !allCollectedTypes.ContainsKey( fieldType ) && !referencedTypesWithoutCustomAttr.ContainsKey( fieldType ) )
          {
            //Excluding DBResources wihout custom attribute or fields with custom attributes
            if ( !TypesReplacement.IsReplaceType( fieldType.Name ) )
              if ( IsResource( fieldType ) )
              {
                TryToAdd( excludedDBResources, type, new List<FieldInfo>() );
                AddKeyToList( excludedDBResources[type], field );
              }
              else
                if ( !IsSimpleType( fieldType ) )
                  referencedTypesWithoutCustomAttr.Add( fieldType, new List<FieldInfo>() );
          }
        }
      }

      //Excluding DBResources without custom attributes or fields with custom attributes
      foreach ( var pair in excludedDBResources )
        foreach ( FieldInfo fi in pair.Value )
          allCollectedTypes[pair.Key].Remove( fi );


      allCollectedTypes = CombineDictionaries( allCollectedTypes, referencedTypesWithoutCustomAttr ) as Dictionary<Type, List<FieldInfo>>;
      List<Type> enums = new List<Type>();
      List<Type> classes = new List<Type>();

      int csTypes = 0;
      foreach ( Type type in allCollectedTypes.Keys )
      {
        if ( type.IsEnum )
          enums.Add( type );

        if ( type.IsClass )
          classes.Add( type );

        if ( !string.IsNullOrEmpty( customName ) || !TypeUtils.HasAttribute<NoCSCodeAttribute>( type, false ) )
          ++csTypes;
      }

      if ( enums.Count == 0 && classes.Count == 0 )
        return files;

      enums.Sort( TypeUtils.Compare );
      if ( !SortTypesByDependencies( classes, CollectHierarcyDependencies ) )
      {
        Trace.TraceError( "Found circular dependencies in structures for classes" );
        return files;
      }

      files.Add( resultPath );

      CodeWriter csFile = new CodeWriter( resultPath );

      //NivalCLI.NameMaps using for generated NameMapValue attributes support
      CSCode.WriteHeader( csFile, "CastleTypes", false, "NivalCLI.NameMaps" );
      csFile.WriteLine( "#region Enums" );
      foreach ( Type type in enums )
        CodeGeneration.Enum.Write( type, csFile, 0 );
      csFile.WriteLine( "#endregion" );

      //Writing types with custom attribute
      csFile.WriteLine( "#region Types with custom attribute" );
      foreach ( Type type in classes )
      {
        if ( !typesWithCustomAttribute.ContainsKey( type ) ) continue;
        CodeGeneration.Struct.WriteForSocial( type, IsResource( type ),
          allCollectedTypes.ContainsKey( type.BaseType ) && !referencedTypesWithoutCustomAttr.ContainsKey( type.BaseType ),
          csFile, 0, typesWithCustomAttribute[type] );
      }
      csFile.WriteLine( "#endregion" );

      //Writing types with partial field set
      csFile.WriteLine( "#region Types with fields, marked by custom attribute" );
      foreach ( Type type in classes )
      {
        if ( !typesWithCustomFields.ContainsKey( type ) ) continue;
        CodeGeneration.Struct.WriteForSocial( type, IsResource( type ),
          allCollectedTypes.ContainsKey( type.BaseType ) && !referencedTypesWithoutCustomAttr.ContainsKey( type.BaseType ),
          csFile, 0, typesWithCustomFields[type] );
      }
      csFile.WriteLine( "#endregion" );

      //Writing referenced types without custom attributes or fields with custom attributes
      csFile.WriteLine( "#region Referenced in code generation process types" );
      foreach ( Type type in referencedTypesWithoutCustomAttr.Keys )
      {
        //Is base type involved in generation and contains some abstract fields - overrided fields must be included for compilation success
        //Else type could be included without fields
        if ( !classes.Contains( type ) )
          continue;
        if ( classes.Contains( type.BaseType ) )
        {
          FieldInfo[] fields = GetFields( type, false, string.Empty, null );
          foreach ( FieldInfo fieldInfo in fields )
            if ( IsFieldRequired( type, fieldInfo ) )
              AddKeyToList( referencedTypesWithoutCustomAttr[type], fieldInfo );
        }
        CodeGeneration.Struct.WriteForSocial( type, IsResource( type ),
          allCollectedTypes.ContainsKey( type.BaseType ) && !referencedTypesWithoutCustomAttr.ContainsKey( type.BaseType ),
          csFile, 0, referencedTypesWithoutCustomAttr[type] );
      }
      csFile.WriteLine( "#endregion" );
      CodeGeneration.CSCode.WriteCloseNamespace( csFile );
      csFile.Close( dryRun || csTypes == 0 );

      return files;
    }

    /// <summary>
    /// Checks that base type doesn't contains abstract fields, which must be overrided
    /// </summary>
    /// <param name="type"></param>
    /// <param name="fieldInfo"></param>
    /// <returns></returns>
    private static bool IsFieldRequired( Type type, FieldInfo fieldInfo )
    {
      FieldInfo baseField = type.BaseType.GetField( fieldInfo.Name, BindingFlags.Public | BindingFlags.Instance | BindingFlags.DeclaredOnly );
      return ( baseField != null && TypeUtils.HasAttribute<AbstractAttribute>( baseField, false ) );
    }

    private static bool AddKeyToList<T>( List<T> list, T key )
    {
      if ( !list.Contains( key ) )
      {
        list.Add( key );
        return true;
      }
      return false;
    }

    private static bool TryToAdd<T1, T2>( Dictionary<T1, T2> dict, T1 key, T2 value )
    {
      if ( !dict.ContainsKey( key ) )
      {
        dict.Add( key, value );
        return true;
      }
      return false;
    }

    private static ICollection<T> CombineCollections<T>( ICollection<T> sourceListA, ICollection<T> sourceListB )
    {
      List<T> result = new List<T>();
      result.AddRange( sourceListA );
      foreach ( T element in sourceListB )
      {
        if ( element != null && !result.Contains( element ) )
          result.Add( element );
      }
      return result;
    }

    private static IDictionary<T1, T2> CombineDictionaries<T1, T2>( IDictionary<T1, T2> sourceDA, IDictionary<T1, T2> sourceDB )
    {
      Dictionary<T1,T2> result = new Dictionary<T1, T2>();

      foreach ( var pair in sourceDA )
        result.Add( pair.Key, pair.Value );

      foreach ( var pair in sourceDB )
        TryToAdd<T1, T2>( result, pair.Key, pair.Value );

      return result;
    }
  }
}
