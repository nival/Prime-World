using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using libdb.DB;
using libdb.IO;
using System.Reflection;

namespace DBCodeGen
{
  internal sealed partial class DBCodeGen
  {
    private static Dictionary<Type, string> renameTable = new Dictionary<Type, string>();
    private static Dictionary<string, string> simpleTypes = new Dictionary<string, string>();

    public static void RegisterSimpleType( string typeName )
    {
      if ( !simpleTypes.ContainsKey( typeName ) )
        simpleTypes.Add( typeName, typeName );
    }

    public static void RegisterSimpleType( Type type )
    {
      RegisterSimpleType( type.Name.ToString() );
    }

    public static void RegisterRenameType( Type type, string name )
    {
      if ( renameTable.ContainsKey( type ) )
      {
        throw new ArgumentException( string.Format( "Type \"{0}\" already renamed", type.Name ) );
      }

      renameTable.Add( type, name );
    }

    public static void CheckTypeAttributes( Type type )
    {
      RenameTypeAttribute renameAttr = TypeUtils.GetAttribute<RenameTypeAttribute>( type, false );
      if ( renameAttr != null )
        RegisterRenameType( type, renameAttr.NewName );

      if ( TypeUtils.HasAttribute<SimpleTypeAttribute>( type, false ) )
        RegisterSimpleType( type.Name );
    }

    public static bool IsSimpleType( Type type )
    {
      return type == null || simpleTypes.ContainsKey( type.Name );
    }

    public static bool IsTypeFromDb( Type type )
    {
      return !simpleTypes.ContainsKey( type.Name ) && !TypeUtils.HasAttribute<NoCodeAttribute>( type, false );
    }

    public static bool IsResource( Type type )
    {
      return type.IsSubclassOf( typeof( libdb.DB.DBResource ) );
    }

    public static bool IsStruct( Type type )
    {
      return !type.IsEnum && !IsResource( type ) && !IsSimpleType( type ) && TypeUtils.GetTypeFromPtr( type ) == null && !TypeUtils.IsList( type );
    }

    public static string GetTypeName( Type type )
    {
      string name = string.Empty;

      if ( type.Name == "DBResource" )
        return "DbResource";

      if ( renameTable.TryGetValue( type, out name ) )
        return name;
      else
      {
        Type typeFromList = TypeUtils.GetTypeFromList( type );
        if ( typeFromList != null )
          return string.Format( "vector< {0} >", GetTypeName( typeFromList ) );
        else
        {
          Type typeFromPtr = TypeUtils.GetTypeFromPtr( type );
          if ( typeFromPtr != null )
            return string.Format( "Ptr< {0} >", GetTypeName( typeFromPtr ) );
          else
            return type.Name;
        }
      }
    }

    /// <summary>
    /// Returns C++ type name include NDb:: namespace prefix if neccessary
    /// </summary>
    /// <param name="type">Type</param>
    /// <returns>C++ type name</returns>
    public static string GetFullTypeName( Type type )
    {
      return string.Format( "{0}{1}", DBCodeGen.IsTypeFromDb( type ) ? "NDb::" : string.Empty, DBCodeGen.GetTypeName( type ) );
    }

    public static string GetCSSimpleTypeName( Type type )
    {
      if ( type == typeof( int ) )
        return "int";
      else if ( type == typeof( float ) )
        return "float";
      else if ( type == typeof( string ) )
        return "string";
      else if ( type == typeof( bool ) )
        return "bool";
      else if ( typeof( IList ).IsAssignableFrom( type ) )
        return String.Format( "List<{0}>", GetCSSimpleTypeName( type.GetGenericArguments()[0] ) );
      else if ( typeof( DBPtrBase ).IsAssignableFrom( type ) )
        return String.Format( "{0}", GetCSSimpleTypeName( type.GetGenericArguments()[0] ) );
      else
        return type.Name;
    }

    public static string GetCSTypeFieldeName( Type type )
    {
      Type tempType = null;
      if ( ( tempType = TypeUtils.GetTypeFromList( type ) ) != null )
      {
        Type ptrType = TypeUtils.GetTypeFromPtr( tempType );
        if ( ptrType != null )
          return string.Format( "UndoRedoAssignableList<DBPtr<{0}>>", GetCSSimpleTypeName( ptrType ) );
        else
        {
          if ( IsStruct( tempType ) || tempType == typeof( TextRef ) || tempType == typeof( SrcFile ) )
            return string.Format( "UndoRedoAssignableList<{0}>", GetCSSimpleTypeName( tempType ) );
          else
            return string.Format( "UndoRedoList<{0}>", GetCSSimpleTypeName( tempType ) );
        }
      }
      else if ( ( tempType = TypeUtils.GetTypeFromPtr( type ) ) != null )
        return string.Format( "UndoRedoDBPtr<{0}>", GetCSSimpleTypeName( tempType ) );
      else if ( !IsStruct( type ) && type != typeof( TextRef ) && type != typeof( SrcFile ) )
        return string.Format( "UndoRedo<{0}>", GetCSSimpleTypeName( type ) );
      else
        return GetCSSimpleTypeName( type );
    }

    public static string GetCSTypePropertyName( Type type )
    {
      Type tempType = null;
      if ( ( tempType = TypeUtils.GetTypeFromList( type ) ) != null )
      {
        Type ptrType = TypeUtils.GetTypeFromPtr( tempType );
        if ( ptrType != null )
          return string.Format( "libdb.IChangeableList<DBPtr<{0}>>", GetCSSimpleTypeName( ptrType ) );
        else
          return string.Format( "libdb.IChangeableList<{0}>", GetCSSimpleTypeName( tempType ) );
      }
      else if ( ( tempType = TypeUtils.GetTypeFromPtr( type ) ) != null )
        return string.Format( "DBPtr<{0}>", GetCSSimpleTypeName( tempType ) );
      else
        return GetCSSimpleTypeName( type );
    }

    public static string GetCPPEnumValue( Type enumType, object enumValue )
    {
      string enumName = DBCodeGen.GetTypeName( enumType );
      string enumPrefix = enumName.ToUpper();
      if ( enumPrefix[0] == 'E' )
        enumPrefix = enumPrefix.Substring( 1 );
      enumPrefix += "_";

      List<KeyValuePair<int, string>> values = new List<KeyValuePair<int, string>>();
      foreach ( string name in System.Enum.GetNames( enumType ) )
        values.Add( new KeyValuePair<int, string>( (int)System.Enum.Parse( enumType, name ), name.ToUpper() ) );
      values.Sort( ( KeyValuePair<int, string> x, KeyValuePair<int, string> y ) => { return y.Key - x.Key; } );

      int intValue = (int)enumValue;
      int tempValue = intValue;
      string result = string.Empty;
      foreach ( KeyValuePair<int, string> value in values )
      {
        if ( value.Key == intValue )
          return string.Format( "{0}{1}", enumPrefix, value.Value );
        else if ( ( tempValue & value.Key ) == value.Key )
        {
          if ( !string.IsNullOrEmpty( result ) )
            result += " | ";
          result += string.Format( "{0}{1}", enumPrefix, value.Value );
          tempValue -= value.Key;
          if ( tempValue == 0 )
            return string.Format( "{0}( {1} )", enumName, result );
        }
      }

      return string.Format( "{0}( {1} )", enumName, intValue );
    }

    public static string GetCSEnumValue( Type enumType, object enumValue )
    {
      List<KeyValuePair<int, string>> values = new List<KeyValuePair<int, string>>();
      foreach ( string name in System.Enum.GetNames( enumType ) )
        values.Add( new KeyValuePair<int, string>( (int)System.Enum.Parse( enumType, name ), name ) );
      values.Sort( ( KeyValuePair<int, string> x, KeyValuePair<int, string> y ) => { return y.Key - x.Key; } );

      int intValue = (int)enumValue;
      int tempValue = intValue;
      string result = string.Empty;
      foreach ( KeyValuePair<int, string> value in values )
      {
        if ( value.Key == intValue )
          return string.Format( "{0}.{1}", enumType.Name, value.Value );
        else if ( ( tempValue & value.Key ) == value.Key )
        {
          if ( !string.IsNullOrEmpty( result ) )
            result += " | ";
          result += string.Format( "{0}.{1}", enumType.Name, value.Value );
          tempValue -= value.Key;
          if ( tempValue == 0 )
            return result;
        }
      }

      return string.Format( "({0}){1}", enumType.Name, intValue );
    }

    public delegate List<Type> DependenciesCollector( Type type );

    private static Dictionary<Type, Dictionary<Type, Type>> BuildDependencies( List<Type> types, DependenciesCollector dependenciesCollector )
    {
      Dictionary<Type, Dictionary<Type, Type>> result = new Dictionary<Type, Dictionary<Type, Type>>();
      foreach ( Type type in types )
      {
        if ( result.ContainsKey( type ) )
          continue;

        List<Type> dependencies = dependenciesCollector( type );
        if ( dependencies == null || dependencies.Count == 0 )
          result.Add( type, null );
        else
        {
          Dictionary<Type, Type> typeDependencies = new Dictionary<Type, Type>();
          foreach ( Type typeDependence in dependencies )
          {
            if ( !typeDependencies.ContainsKey( typeDependence ) )
              typeDependencies.Add( typeDependence, typeDependence );
          }
          result.Add( type, typeDependencies );
        }
      }

      foreach ( KeyValuePair<Type, Dictionary<Type, Type>> resultType in result )
      {
        bool finished = resultType.Value == null || resultType.Value.Count == 0;
        while ( !finished )
        {
          List<Type> addDependencies = new List<Type>();
          foreach ( Type dependense1 in resultType.Value.Keys )
          {
            Dictionary<Type, Type> dependencies2 = null;
            if ( !result.TryGetValue( dependense1, out dependencies2 ) )
              continue;
            if ( dependencies2 == null )
              continue;
            foreach ( Type dependense2 in dependencies2.Keys )
            {
              if ( !resultType.Value.ContainsKey( dependense2 ) )
                addDependencies.Add( dependense2 );
            }
          }
          finished = addDependencies.Count == 0;
          foreach ( Type dependense2 in addDependencies )
          {
            if ( !resultType.Value.ContainsKey( dependense2 ) )
              resultType.Value.Add( dependense2, dependense2 );
          }
        }
      }

      return result;
    }

    private class DependensyComparer : IComparer<Type>
    {
      private readonly Dictionary<Type, Dictionary<Type, Type>> dependencies = null;

      public DependensyComparer( Dictionary<Type, Dictionary<Type, Type>> dependencies ) { this.dependencies = dependencies; }

      public bool IsTypeDepend( Type type1, Type type2 )
      {
        Dictionary<Type, Type> dependenciesForType = null;
        if ( !dependencies.TryGetValue( type1, out dependenciesForType ) )
          return false;
        if ( dependenciesForType == null )
          return false;

        return dependenciesForType.ContainsKey( type2 );
      }

      public int Compare( Type type1, Type type2 )
      {
        if ( IsTypeDepend( type1, type2 ) )
          return 1;
        else if ( IsTypeDepend( type2, type1 ) )
          return -1;
        else
          return 0;
      }
    }

    /// <summary>
    /// Sort list of types using specified dependencies collector. Also checks for circular dependencies
    /// </summary>
    /// <param name="types">List of types for sortind</param>
    /// <param name="dependenciesCollector">Dependencies collector delegate</param>
    /// <returns>false if circular dependencies found otherwise returns true</returns>
    public static bool SortTypesByDependencies( List<Type> types, DependenciesCollector dependenciesCollector )
    {
      Dictionary<Type, Dictionary<Type, Type>> dependencies = BuildDependencies( types, dependenciesCollector );
      DependensyComparer comparer = new DependensyComparer( dependencies );

      foreach ( Type type in types )
      {
        if ( comparer.IsTypeDepend( type, type ) )
          return false;
      }

      types.Sort( TypeUtils.Compare );
      //types.Sort( comparer );

      for ( int i = 0; i < types.Count - 1; ++i )
      {
        for ( int j = i + 1; j < types.Count; ++j )
        {
          if ( comparer.Compare( types[i], types[j] ) > 0 )
          {
            Type tempType = types[i];
            types[i] = types[j];
            types[j] = tempType;
          }
        }
      }

      return true;
    }

    private static FieldInfo[] GetFields( Type type, BindingFlags flags, string customName, Type noCodeAttribute )
    {
      string filteredCustom = customName;
      if ( !string.IsNullOrEmpty( customName ) )
      {
        noCodeAttribute = null; //ignore NoCode/NoCsCode attribute is customName specified

        if ( !String.IsNullOrEmpty( filteredCustom ) && DBCodeGen.CheckCustomAttribute( type, customName, false ) )
          filteredCustom = string.Empty;

        //CustomAttribute custom = TypeUtils.GetAttribute<CustomAttribute>(type, false);
        //if (custom != null && custom.IsMatch(customName))
        //  customName = string.Empty;
      }

      Dictionary<string, FieldInfo> fields = new Dictionary<string, FieldInfo>();

      foreach ( FieldInfo field in type.GetFields( flags ) )
      {
        if ( !string.IsNullOrEmpty( customName ) )
        {
          if ( !String.IsNullOrEmpty( filteredCustom ) && !DBCodeGen.CheckCustomAttribute( field, filteredCustom, false ) )
            continue;
        }
        if ( noCodeAttribute != null )
        {
          if ( field.IsDefined( noCodeAttribute, true ) )
            continue;
        }

        if ( !fields.ContainsKey( field.Name ) )
          fields.Add( field.Name, field );
        else if ( field.DeclaringType == type )
          fields[field.Name] = field;
      }

      List<string> names = new List<string>( fields.Keys );
      //names.Sort(); // this produce wrong code in materials, need more investigation

      FieldInfo[] result = new FieldInfo[fields.Count];
      for ( int i = 0; i < names.Count; ++i )
        result[i] = fields[names[i]];

      return result;
    }

    public static FieldInfo[] GetFields( Type type, bool inherit, string customName, Type noCodeAttribute )
    {
      BindingFlags flags = BindingFlags.Public | BindingFlags.Instance;
      if ( !inherit )
        flags |= BindingFlags.DeclaredOnly;

      return GetFields( type, flags, customName, noCodeAttribute );
    }

    public static FieldInfo[] GetEnums( Type type )
    {
      List<FieldInfo> result = new List<FieldInfo>();
      foreach ( FieldInfo field in type.GetFields() )
      {
        if ( field.FieldType.IsEnum )
          result.Add( field );
      }
      return result.ToArray();
    }

    public static FieldInfo[] GetFieldsAndEnums( Type type, bool inherit, string customName, Type noCodeAttribute )
    {
      FieldInfo[] r = GetFields( type, inherit, customName, noCodeAttribute );
      List<FieldInfo> result = new List<FieldInfo>( r );
      result.AddRange( GetEnums( type ) );
      return result.ToArray();
    }

    public static FieldInfo[] GetStaticFields( Type type, bool inherit, string customName, Type noCodeAttribute )
    {
      BindingFlags flags = BindingFlags.Public | BindingFlags.Static;
      if ( !inherit )
        flags |= BindingFlags.DeclaredOnly;
      else
        flags |= BindingFlags.FlattenHierarchy;

      return GetFields( type, flags, customName, noCodeAttribute );
    }

    public static Type[] GetFieldsTypes( Type type, string customName )
    {
      Dictionary<Type, object> types = new Dictionary<Type, object>();
      foreach ( var field in GetFields( type, true, customName, null ) )
      {
        var fieldType = field.FieldType;
        for ( var listType = TypeUtils.GetTypeFromList( fieldType ); listType != null; listType = TypeUtils.GetTypeFromList( fieldType ) )
          fieldType = listType;

        if ( DBCodeGen.IsSimpleType( fieldType ) || type.Namespace == typeof( DBPtrBase ).Namespace )
          continue;

        if ( !types.ContainsKey( fieldType ) )
          types.Add( fieldType, null );
      }

      List<Type> result = new List<Type>( types.Keys );
      result.Sort( TypeUtils.Compare );
      return result.ToArray();
    }

    private static Type GetFieldTypeFromListOrPtr( FieldInfo fieldInfo )
    {
      Type fieldType = fieldInfo.FieldType;
      for ( Type listType = TypeUtils.GetTypeFromList( fieldType );
           listType != null;
           listType = TypeUtils.GetTypeFromList( fieldType ) )
        fieldType = listType;

      if ( fieldType.IsSubclassOf( typeof( DBPtrBase ) ) )
        fieldType = TypeUtils.GetTypeFromPtr( fieldType );

      return fieldType;
    }

    public static bool CheckCustomAttribute( ICustomAttributeProvider provider, string customName, bool inherit )
    {
      if ( string.IsNullOrEmpty( customName ) )
        return false;
      CustomAttribute custom = TypeUtils.GetAttribute<CustomAttribute>( provider, inherit );
      if ( custom == null )
        return false;
      return custom.IsMatch( customName );
    }

    public static Attribute[] GetSocialTypesAttributes()
    {
      Attribute[] result = new Attribute[] { new CustomAttribute( "Social" ) };
      return result;
    }

    public static bool IsSocialType( Type checkType )
    {
      if ( _socialTypes.Contains( checkType ) )
        return true;
      if ( _isSocialTypesProject )
        return true;
      CustomAttribute[] attribs = TypeUtils.GetAttributes<CustomAttribute>( checkType, false );
      foreach ( CustomAttribute it in attribs )
      {
        if ( it.IsMatch( "Social" ) )
        {
          return true;
        }
      }

      return false;
    }
  }
}