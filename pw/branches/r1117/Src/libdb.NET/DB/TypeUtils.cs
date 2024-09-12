using System;
using System.Collections.Generic;
using System.Reflection;

namespace libdb.DB
{
  public static class TypeUtils
  {

    /// <summary>
    /// Search for property in specified type its base types and its interfaces
    /// </summary>
    /// <param name="type">Type where search for property</param>
    /// <param name="name">Name of property to search</param>
    /// <returns>A PropertyInfo object representing the public property with the specified name, if found; otherwise, null</returns>
    public static System.Reflection.PropertyInfo GetProperty( Type type, string name )
    {
      System.Reflection.BindingFlags flags = System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.FlattenHierarchy;

      //try get property from classes hierarcy
      System.Reflection.PropertyInfo property = type.GetProperty( name, flags );
      if ( property != null )
        return property;

      //search property in implemented interfaces
      Type[] interfaces = type.GetInterfaces();
      foreach ( Type interfaceType in interfaces )
      {
        property = interfaceType.GetProperty( name, flags );
        if ( property != null )
          return property;
      }

      return null;
    }

    public static void Copy( object from, object to )
    {
      DBFieldInfo[] fields = TypeUtils.GetFields(to.GetType(), true);
      foreach (DBFieldInfo field in fields)
      {
        if (!field.CanRead || !field.CanWrite)
        {
          continue;
        }
        field.SetValue(to, field.GetValue(from));
      }
    }

    /// <summary>
    /// Search for method in specified type its base types and its interfaces
    /// </summary>
    /// <param name="type">Type where search for method</param>
    /// <param name="name">Name of method to search</param>
    /// <param name="types">An array of Type objects representing the number, order, and type of the parameters for the method to get</param>
    /// <returns>A MethodInfo object representing the public property with the specified name, if found; otherwise, null</returns>
    public static System.Reflection.MethodInfo GetMethod( Type type, string name, Type[] types )
    {
      System.Reflection.BindingFlags flags = System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.FlattenHierarchy;

      //try get method from classes hierarcy
      System.Reflection.MethodInfo method = type.GetMethod( name, flags, null, types, null );
      if ( method != null )
        return method;

      //search method in implemented interfaces
      Type[] interfaces = type.GetInterfaces();
      foreach ( Type interfaceType in interfaces )
      {
        method = interfaceType.GetMethod( name, flags, null, types, null );
        if ( method != null )
          return method;
      }

      return null;
    }

    public static DBFieldInfo[] GetFields( Type type, bool ProcessParent )
    {
      BindingFlags flags = BindingFlags.Public | BindingFlags.Instance;
      Dictionary<string, DBFieldInfo> fields = new Dictionary<string, DBFieldInfo>();

      if ( !ProcessParent )
        flags |= BindingFlags.DeclaredOnly;

      foreach ( FieldInfo field in type.GetFields( flags ) )
      {
        DBFieldInfo existingInfo = null;
        if ( fields.TryGetValue( field.Name, out existingInfo ) )
        {
          if ( field.DeclaringType == type ) //Add own, discard parent field
            fields.Add( field.Name, new DBFieldInfoField( field ) );
        }
        else
          fields.Add( field.Name, new DBFieldInfoField( field ) );
      }

      foreach ( PropertyInfo property in type.GetProperties( flags ) )
      {
        if ( property.PropertyType == typeof( DBID ) || property.GetIndexParameters().Length != 0 )
          continue;

        DBFieldInfo existingInfo = null;
        if ( fields.TryGetValue( property.Name, out existingInfo ) )
        {
          if ( property.DeclaringType == type ) //Add own, discard parent property
            fields.Add( property.Name, new DBFieldInfoProperty( property ) );
        }
        else
        {
          fields.Add( property.Name, new DBFieldInfoProperty( property ) );
        }
      }

      DBFieldInfo[] result = new DBFieldInfo[fields.Count];
      var fieldsEnum = fields.GetEnumerator();
      int idx = 0;
      while ( fieldsEnum.MoveNext() )
      {
        result[idx] = fieldsEnum.Current.Value;
        ++idx;
      }

      return result;
    }

    public static DBFieldInfo GetField( Type type, string fieldName, bool ProcessParent )
    {
      BindingFlags flags = BindingFlags.Public | BindingFlags.Instance;
      List<DBFieldInfo> fields = new List<DBFieldInfo>();

      if ( !ProcessParent )
        flags |= BindingFlags.DeclaredOnly;

      FieldInfo field = type.GetField( fieldName, flags );
      if ( field != null )
        return new DBFieldInfoField( field );

      PropertyInfo property = type.GetProperty( fieldName, flags );
      if ( property != null )
        return new DBFieldInfoProperty( property );

      return null;
    }

    public static bool IsStruct( Type type )
    {
      return !type.IsEnum 
        && !IsResourceType( type ) 
        && !IsSimpleType( type ) 
        && GetTypeFromPtr( type ) == null 
        && !IsList( type );
    }

    public static bool IsList( Type type )
    {
      return IsSubclassOf( type, typeof( IList<> ) );
    }

    public static bool IsDBPtr( Type type )
    {
      return IsSubclassOf( type, typeof( DBPtr<> ) );
    }

    public static bool IsResourceType( Type type )
    {
      return ( type != null && ( type.IsSubclassOf( typeof( DBResource ) ) || type == typeof( DBResource ) ) );
    }

    public static bool IsSubclassOf( Type type, Type pattern )
    {
      if ( type == null || pattern == null )
        return false;

			if ( pattern.IsInterface )
			{
				Type[] interfaces = type.GetInterfaces();
				foreach ( Type interfaceType in interfaces )
				{
					if ( interfaceType == pattern || ( interfaceType.IsGenericType && interfaceType.GetGenericTypeDefinition() == pattern ) )
						return true;
				}
			}
			else
			{
				for ( Type baseType = type; baseType != null; baseType = baseType.BaseType )
				{
					if ( pattern == baseType )
						return true;
					if ( baseType.IsGenericType && pattern == baseType.GetGenericTypeDefinition() )
						return true;
				}
			}

      return false;
    }

    private static bool IsImplementInterface( Type underTestType, Type patern )
    {
      if ( underTestType != null && patern != null )
      {
        if ( underTestType.IsGenericType && underTestType.GetGenericTypeDefinition().IsAssignableFrom( patern ) )
          return true;

        foreach ( Type inheritedInterface in underTestType.GetInterfaces() )
        {
          if ( inheritedInterface.IsGenericType )
          {
            if ( inheritedInterface.GetGenericTypeDefinition() == patern )
              return true;
          }
          else
          {
            if ( inheritedInterface == patern )
              return true;
          }
        }
      }

      return false;
    }

    private static bool IsSubclassOfOpenGeneric( Type underTestType, Type patern )
    {
      bool equality = underTestType == patern;
      if ( underTestType != null && patern != null && !equality )
      {
        if ( underTestType.BaseType != null && underTestType.BaseType.IsGenericType )
          return IsSubclassOfOpenGeneric( underTestType.BaseType.GetGenericTypeDefinition(), patern );
        else
          return IsSubclassOfOpenGeneric( underTestType.BaseType, patern );
      }
      else
        return equality;
    }

    public static Type GetTypeFromGeneric( Type type )
    {
      return GetTypeFromGeneric( type, 0 );
    }

    public static Type GetTypeFromGeneric( Type type, int index )
    {
      if ( type == null )
        return null;
      else if ( type.IsGenericType )
      {
        if ( type.GetGenericArguments().Length > index )
          return type.GetGenericArguments()[index];
        else
          return null;
      }
      else
        return GetTypeFromGeneric( type.BaseType, index );
    }

    public static Type GetTypeFromList( Type type )
    {
      if ( type == null || !type.IsGenericType )
        return null;

      if (IsList(type) && type.GetGenericArguments().Length >= 1)
        return type.GetGenericArguments()[0];

      return null;
    }

    public static Type GetTypeFromPtr( Type type )
    {
      if ( type == null )
        return null;

      if( !IsDBPtr(type) || type.GetGenericArguments().Length != 1 )
        return null;

      return type.GetGenericArguments()[0];
    }

    public static Type ExtractType( Type type )
    {
      Type listType = GetTypeFromList( type );
      if ( listType != null )
        return ExtractType( listType );
      Type ptrType = GetTypeFromPtr( type );
      if ( ptrType != null )
        return ExtractType( ptrType );

      return type;
    }

    public static int Compare( Type type1, Type type2 )
    {
      return string.Compare( type1.Name, type2.Name );
    }

    public static bool CanCreate( Type type )
    {
      if ( !type.IsSubclassOf( typeof( DBResource ) ) )
        return false;

      NonTerminalAttribute[] attributes = GetAttributes<NonTerminalAttribute>( type, false );
      return ( attributes == null ) || ( attributes.Length == 0 );
    }

    public static bool IsSimpleType( Type type )
    {
      if ( type == typeof( string ) )
        return true;
      else if ( type.IsPrimitive )
        return true;
      else if ( type == typeof( Guid ) )
        return true;
      else if ( type.IsEnum )
        return true;
      else if ( type == typeof( Type ) || IsSubclassOf( type, typeof( Type ) ) )
        return true;
      return false;
    }

    public static object CreateInstance( Type type )
    {
      if ( type == typeof( string ) )
        return string.Empty;
      else if ( type == typeof( int ) )
        return ( int )0;
      else if ( type == typeof( long ) )
        return (long)0;
      else if ( type == typeof( float ) )
        return ( float )0.0f;
      else if ( type == typeof( Guid ) )
        return Guid.Empty;
      else if ( type == typeof( bool ) )
        return ( bool )false;
      else if ( type.IsEnum )
        return Enum.GetValues( type ).GetValue( 0 );
      else if ( IsDBPtr(type) ) 
        return type.GetConstructor( new Type[1] { typeof( DBResource ) } ).Invoke( new Object[1] { null } );
      else
        return type.GetConstructor( Type.EmptyTypes ).Invoke( new object[0] );
    }

    public static bool HasAttribute<T>( ICustomAttributeProvider type, bool inherit ) where T : Attribute
    {
			return type != null && type.IsDefined( typeof( T ), inherit );
    }

		public static T GetAttribute<T>( ICustomAttributeProvider type, bool inherit ) where T : Attribute
    {
      T[] attributes = GetAttributes<T>( type, inherit );
      if ( attributes.Length != 1 )
        return null;
      return attributes[0];
    }

		public static T[] GetAttributes<T>( ICustomAttributeProvider type, bool inherit ) where T : Attribute
    {
      List<T> result = new List<T>();

      if ( type != null )
      {
        object[] allAttributes = type.GetCustomAttributes( typeof( T ), inherit );
        if ( allAttributes != null )
        {
          foreach ( object attr in allAttributes )
          {
            if ( attr is T )
              result.Add( attr as T );
          }
        }
      }

      return result.ToArray();
    }

    public static string GetFormattedListCaption( int index, object value )
    {
      string res = index.ToString();
      res += ". ";

      if (HasAttribute<IndexFieldAttribute>(value.GetType(), true) )
      {
        IndexFieldAttribute indexFieldAttr = TypeUtils.GetAttribute<IndexFieldAttribute>(value.GetType(), true);
        if (null != indexFieldAttr)
        {
          DBFieldInfo field = TypeUtils.GetField(value.GetType(), indexFieldAttr.FieldName, true);
          if (field != null)
          {
            res += field.GetValue(value);
          }
        }
      }

      return res;
    }

    #region Some primitive types parsers

    public static bool TryParse( string value, out Guid result )
    {
      char[] guidValue = new char[32];
      int guidIndex = 0;
      foreach ( char c in value )
      {
        if ( c >= '0' && c <= '9' || c >= 'A' && c <= 'F' || c >= 'a' && c <= 'f' )
        {
          if ( guidIndex >= guidValue.Length )
          {
            result = Guid.Empty;
            return false;
          }
          guidValue[guidIndex++] = c;
        }
        else if ( c == '-' || c == '{' || c == '}' || c == '(' || c == ')' )
          continue;
        else
        {
          result = Guid.Empty;
          return false;
        }
      }

      if ( guidIndex < 32 )
      {
        result = Guid.Empty;
        return false;
      }

      result = new Guid( new string( guidValue ) );
      return true;
    }

    public static bool TryParse( string value, out bool result )
    {
      result = false;
      if ( string.Compare( value, "1" ) == 0 || string.Compare( value, bool.TrueString, StringComparison.InvariantCultureIgnoreCase ) == 0 )
        result = true;
      else if ( string.Compare( value, "0" ) != 0 && string.Compare( value, bool.FalseString, StringComparison.InvariantCultureIgnoreCase ) != 0 )
        return false;

      return true;
    }

    #endregion

    #region Universal constructors and initializers

    public static object CreateObject( Type type )
    {
      System.Reflection.ConstructorInfo cotr = type.GetConstructor( Type.EmptyTypes );
      if ( cotr == null )
        return null;

      return cotr.Invoke( new object[0] );
    }

    public static object CreateObject<T1>( Type type, T1 param1 )
    {
      System.Reflection.ConstructorInfo cotr = type.GetConstructor( new Type[1] { typeof( T1 ) } );
      if ( cotr == null )
        return null;

      return cotr.Invoke( new object[1] { param1 } );
    }

    public static object CreateObject<T1, T2>( Type type, T1 param1, T2 param2 )
    {
      System.Reflection.ConstructorInfo cotr = type.GetConstructor( new Type[2] { typeof( T1 ), typeof( T2 ) } );
      if ( cotr == null )
        return null;

      return cotr.Invoke( new object[2] { param1, param2 } );
    }

    public static bool TryCreateObject( Type type, out object obj )
    {
      obj = CreateObject( type );
      return obj != null;
    }

    public static bool TryCreateObject<T1>( Type type, T1 param1, out object obj )
    {
      obj = CreateObject<T1>( type, param1 );
      return obj != null;
    }

    public static bool TryCreateObject<T1, T2>( Type type, T1 param1, T2 param2, out object obj )
    {
      obj = CreateObject<T1, T2>( type, param1, param2 );
      return obj != null;
    }

    #endregion
  }
}
