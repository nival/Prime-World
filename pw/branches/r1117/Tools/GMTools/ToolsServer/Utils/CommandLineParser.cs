using System;
using System.Collections.Generic;
using System.Globalization;
using System.Reflection;

namespace ToolsServer.Utils
{
  public static class CommandLineParser
  {
    #region public sealed class ArgumentAttribute : Attribute

    public sealed class ArgumentAttribute : Attribute
    {
      public readonly string longName = string.Empty;
      public readonly string shortName = string.Empty;
      public readonly string description = string.Empty;

      public ArgumentAttribute() { }

      public ArgumentAttribute( string shortName, string longName, string description )
      {
        this.shortName = shortName;
        this.longName = longName;
        this.description = description;
      }
    }

    #endregion

    #region Attribute checkers and getters

    public static bool HasAttribute<T>( ICustomAttributeProvider provider, bool inherit ) where T : Attribute
    {
      return provider.IsDefined( typeof( T ), inherit );
    }

    public static T GetAttribute<T>( ICustomAttributeProvider provider, bool inherit ) where T : Attribute
    {
      T[] attributes = GetAttributes<T>( provider, inherit );
      if ( attributes.Length != 1 )
        return null;
      return attributes[0];
    }

    public static T[] GetAttributes<T>( ICustomAttributeProvider provider, bool inherit ) where T : Attribute
    {
      object[] attributes = provider.GetCustomAttributes( typeof( T ), inherit );
      if ( attributes == null || attributes.Length == 0 )
        return new T[0];


      List<T> result = new List<T>();
      foreach ( object attr in attributes )
      {
        if ( attr is T )
          result.Add( attr as T );
      }
      return result.ToArray();
    }

    #endregion

    public static FieldInfo[] GetFields( Type type, BindingFlags flags )
    {
      return type.GetFields( flags | BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance );
    }

    private static Dictionary<string, FieldInfo> GetFields( Type type, bool staticFields )
    {
      Dictionary<string, FieldInfo> result = new Dictionary<string, FieldInfo>();
      FieldInfo[] fields = GetFields( type, staticFields ? BindingFlags.Static : BindingFlags.Default );
      foreach ( var field in fields )
      {
        ArgumentAttribute arg = GetAttribute<ArgumentAttribute>( field, true );
        if ( arg == null )
          continue;

        if ( string.IsNullOrEmpty( arg.shortName ) && string.IsNullOrEmpty( arg.longName ) )
          result.Add( string.Empty, field );

        if ( !string.IsNullOrEmpty( arg.shortName ) )
        {
          result.Add( "-" + arg.shortName, field );
          result.Add( "/" + arg.shortName, field );
        }
        if ( !string.IsNullOrEmpty( arg.longName ) )
        {
          result.Add( "--" + arg.longName.ToLowerInvariant(), field );
        }
      }

      return result;
    }

    private static bool TrySetField( FieldInfo field, object obj, string value )
    {
      if ( field.FieldType == typeof( bool ) )
      {
        if ( string.IsNullOrEmpty( value ) || string.Compare( value, "true", StringComparison.CurrentCultureIgnoreCase ) == 0 )
          field.SetValue( obj, true );
        else if ( string.Compare( value, "false", StringComparison.CurrentCultureIgnoreCase ) == 0 )
          field.SetValue( obj, false );
        else
          return false;
      }
      else if ( field.FieldType == typeof( int ) )
      {
        int i = 0;
        if ( int.TryParse( value, out i ) )
          field.SetValue( obj, i );
        else
          return false;
      }
      else if ( field.FieldType == typeof( float ) )
      {
        float f = 0;
        if ( float.TryParse( value, out f ) )
          field.SetValue( obj, f );
        else if ( float.TryParse( value, NumberStyles.Float, CultureInfo.InvariantCulture.NumberFormat, out f ) )
          field.SetValue( obj, f );
        else
          return false;
      }
      else if ( field.FieldType == typeof( string ) )
        field.SetValue( obj, value );
      else if ( field.FieldType == typeof( List<string> ) )
      {
        List<string> fieldValue = field.GetValue( obj ) as List<string>;
        if ( fieldValue != null )
          fieldValue.Add( value );
      }

      return true;
    }

    public delegate bool InvalidArgument( string arg );
    public delegate bool InvalidValue( string arg, string value );

    private static bool FillFields( Dictionary<string, FieldInfo> fields, object obj, IEnumerable<string> args, InvalidArgument invalidArgument, InvalidValue invalidValue )
    {
      foreach ( string arg in args )
      {
        // we don't support empty arguments
        if ( string.IsNullOrEmpty( arg ) )
          continue;

        FieldInfo field = null;
        if ( arg[0] != '-' && arg[0] != '/' )
        {
          if ( !fields.TryGetValue( string.Empty, out field ) )
          {
            if ( invalidArgument != null && !invalidArgument( arg ) )
              return false;
          }
          else if ( !TrySetField( field, obj, arg ) )
          {
            if ( invalidValue != null && !invalidValue( arg, arg ) )
              return false;
          }
          continue;
        }

        string key = arg;
        string value = string.Empty;
        int divPos = arg.IndexOf( '=' );
        if ( divPos >= 0 )
        {
          key = arg.Substring( 0, divPos );
          value = arg.Substring( divPos + 1 );
        }

        if ( key.StartsWith( "--" ) )
          key = key.ToLowerInvariant();

        if ( !fields.TryGetValue( key, out field ) )
        {
          if ( invalidArgument != null && !invalidArgument( arg ) )
            return false;
        }
        else if ( !TrySetField( field, obj, value ) )
        {
          if ( invalidValue != null && !invalidValue( arg, value ) )
            return false;
        }
      }

      return true;
    }

    public static bool FillObject( object obj, IEnumerable<string> args, InvalidArgument invalidArgument, InvalidValue invalidValue )
    {
      Dictionary<string, FieldInfo> fields = GetFields( obj.GetType(), false );
      return FillFields( fields, obj, args, invalidArgument, invalidValue );
    }

    public static bool FillObject( Type type, IEnumerable<string> args, InvalidArgument invalidArgument, InvalidValue invalidValue )
    {
      Dictionary<string, FieldInfo> fields = GetFields( type, true );
      return FillFields( fields, null, args, invalidArgument, invalidValue );
    }

    public delegate string DescriptionFormatter( string key );

    public static void ShowHelp( Type type, bool staticFields, DescriptionFormatter descFormatter )
    {
      FieldInfo[] fields = GetFields( type, staticFields ? BindingFlags.Static : BindingFlags.Default );

      foreach ( var field in fields )
      {
        ArgumentAttribute arg = GetAttribute<ArgumentAttribute>( field, true );
        if ( arg == null || ( string.IsNullOrEmpty( arg.shortName ) && string.IsNullOrEmpty( arg.longName ) ) )
          continue;

        Console.Write( "  " );
        if ( !string.IsNullOrEmpty( arg.longName ) )
          Console.Write( "--" + arg.longName );

        if ( !string.IsNullOrEmpty( arg.shortName ) )
        {
          if ( !string.IsNullOrEmpty( arg.longName ) )
            Console.Write( " (-" + arg.shortName + ")" );
          else
            Console.Write( "-" + arg.shortName );
        }

        if ( descFormatter == null )
          Console.WriteLine( ": " + arg.description );
        else
          Console.WriteLine( ": " + descFormatter( arg.description ) );
      }
    }
  }
}