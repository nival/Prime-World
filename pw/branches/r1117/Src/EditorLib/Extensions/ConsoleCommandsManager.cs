using System;
using System.Collections.Generic;
using System.Text;
using libdb.Diagnostics;
using System.Reflection;
using System.IO;
using libdb.DB;
using libdb.IO;

namespace EditorLib.Plugin
{
  public class ConsoleCommandsManager
  {
    private Dictionary<string, Type> fullNames = new Dictionary<string, Type>();
    private Dictionary<string, Type> shortNames = new Dictionary<string, Type>();

    private static void ReplaceMacro( ref string value )
    {
      Dictionary<string, string> dict = new Dictionary<string, string>();
      dict.Add( "$(BinaryPath)", Path.GetDirectoryName( Assembly.GetEntryAssembly().Location ) + "\\" );
      foreach ( string key in dict.Keys )
      {
        int firstIndex = 0;
        int lastIndex = 0;
        for ( firstIndex = value.IndexOf( key, 0 ), lastIndex = value.LastIndexOf( key, 0 ); value.Contains( key ); firstIndex = value.IndexOf( key, 0 ), lastIndex = value.LastIndexOf( key, 0 ) )
        {

          if ( firstIndex == 0 )
            value = dict[key] + value.Substring( key.Length );
          else if ( lastIndex == value.Length - 1 )
            value = value.Substring( 0, firstIndex ) + dict[key];
          else
            value = value.Substring( 0, firstIndex ) + dict[key] + value.Substring( lastIndex, value.Length - lastIndex );
        }
      }
    }

    private static bool ExtractParameterAndValue( string _argument, out string parameter, out string value )
    {
      parameter = string.Empty;
      value = string.Empty;

      string argument = string.Empty;

      if ( _argument.StartsWith( "--" ) && _argument.Length > 2 )
        argument = _argument.Substring( 2 );
      else if ( _argument.StartsWith( "-" ) && _argument.Length > 1 )
        argument = _argument.Substring( 1 );

      if ( string.IsNullOrEmpty( argument ) )
      {
        Console.WriteLine( "ERROR: Invalid argument \"{0}\"", _argument );
        return false;
      }

      int eqPos = argument.IndexOf( '=' );
      if ( eqPos >= argument.Length - 1 )
      {
        Console.WriteLine( "ERROR: Invalid argument \"{0}\"", _argument );
        return false;
      }

      if ( eqPos >= 0 )
      {
        value = argument.Substring( eqPos + 1 );
        if ( value[0] == '"' && ( value.Length == 1 || value[value.Length - 1] != '"' ) )
        {
          Console.WriteLine( "ERROR: Close quote not found in value in argument \"{0}\"", _argument );
          return false;
        }
        parameter = argument.Substring( 0, eqPos );
        value.Replace( "\\\"", "\"" );
        ReplaceMacro( ref value );
      }
      else
      {
        parameter = argument;
      }

      return true;
    }

    private static FieldInfo FindField( Type type, string fieldName )
    {
      foreach ( FieldInfo field in type.GetFields() )
      {
        object[] commandArgAttrs = field.GetCustomAttributes( typeof( CommandArgumentAttribute ), false );
        if ( commandArgAttrs != null && commandArgAttrs.Length == 1 && commandArgAttrs[0] is CommandArgumentAttribute )
        {
          CommandArgumentAttribute commandArgAttr = commandArgAttrs[0] as CommandArgumentAttribute;
          if ( commandArgAttr.fullName == fieldName || commandArgAttr.shortName == fieldName )
            return field;
        }
      }

      return null;
    }

    public void RegisterCommand( Type type )
    {
      if ( !type.IsAbstract )
      {
        object[] commandNameAttrs = type.GetCustomAttributes( typeof( CommandNameAttribute ), false );
        if ( commandNameAttrs != null && commandNameAttrs.Length == 1 && commandNameAttrs[0] is CommandNameAttribute )
        {
          CommandNameAttribute commandNameAttr = commandNameAttrs[0] as CommandNameAttribute;
          fullNames.Add( commandNameAttr.fullName, type );
          if ( !string.IsNullOrEmpty( commandNameAttr.shortName ) )
            shortNames.Add( commandNameAttr.shortName, type );
        }
      }
    }

    public bool TryExecute( IEditorCommonApplication application, string[] args, out int result )
    {
      result = 0;

      if ( args.Length < 1 )
        return false;

      Type commandType = null;
      if ( !fullNames.TryGetValue( args[0], out commandType ) )
      {
        if ( !shortNames.TryGetValue( args[0], out commandType ) )
          commandType = null;
      }

      if ( commandType == null )
      {
        Console.WriteLine( "ERROR: Unknown command \"{0}\"", args[0] );
        return true;
      }

      IConsoleCommand command = ( commandType.GetConstructor( Type.EmptyTypes ).Invoke( new object[0] ) ) as IConsoleCommand;
      if ( command == null )
      {
        Console.WriteLine( "ERROR: Cannot create command plugin of type \"{0}\" for command \"{1}\"", commandType.Name, args[0] );
        return true;
      }

      List<string> parameters = new List<string>();
      for ( int i = 1; i < args.Length; i++ )
      {
        if ( string.IsNullOrEmpty( args[i] ) )
          continue;

        if ( args[i][0] != '-' )
          parameters.Add( args[i] );
        else
        {
          string parameter = string.Empty;
          string value = string.Empty;

          if ( !ExtractParameterAndValue( args[i], out parameter, out value ) )
            return true;


          FieldInfo field = FindField( commandType, parameter );
          if ( field == null )
          {
            Console.WriteLine( "ERROR: Invalid parameter \"{0}\" for command \"{1}\"", parameter, args[0] );
            return true;
          }
          if ( string.IsNullOrEmpty( parameter ) )
          {
            Console.WriteLine( "ERROR: Invalid argument \"{0}\" for command \"{1}\"", args[i], args[0] );
            return true;
          }

          if ( field.FieldType == typeof( bool ) )
          {
            if ( string.IsNullOrEmpty( value ) )
              field.SetValue( command, true );
            else
            {
              Console.WriteLine( "ERROR: Invalid argument \"{0}\". Field \"{1}\" for command \"{2}\" is flag", args[i], parameter, args[0] );
              return true;
            }
          }
          else if ( field.FieldType == typeof( int ) )
          {
            int fieldValue = 0;
            if ( int.TryParse( value, out fieldValue ) )
            {
              field.SetValue( command, fieldValue );
            }
            else
            {
              Console.WriteLine( "ERROR: Invalid argument \"{0}\". Field \"{1}\" for command \"{2}\" is integer value", args[i], parameter, args[0] );
              return true;
            }
          }
          else if ( field.FieldType == typeof( float ) )
          {
            float fieldValue = 0;
            if ( float.TryParse( value, out fieldValue ) )
            {
              field.SetValue( command, fieldValue );
            }
            else
            {
              Console.WriteLine( "ERROR: Invalid argument \"{0}\". Field \"{1}\" for command \"{2}\" is float value", args[i], parameter, args[0] );
              return true;
            }
          }
          else if ( field.FieldType == typeof( string ) )
          {
            field.SetValue( command, value );
          }
          else if ( field.FieldType.IsEnum ) //пробуем распарсить енумы
          {
            int fieldValue = 0;
            if ( int.TryParse( value, out fieldValue ) )
              field.SetValue( command, fieldValue );
            else
            {
              Console.WriteLine( "ERROR: Invalid argument \"{0}\" for command \"{1}\"", args[i], args[0] );
              return true;
            }
          }
          else
          {
            Console.WriteLine( "ERROR: Invalid argument \"{0}\" for command \"{1}\"", args[i], args[0] );
            return true;
          }
        }
      }

      result = command.Execute( application, parameters.ToArray() );
      return true;
    }

    public void ShowHelp()
    {
      Console.WriteLine( "PF_EditorC.exe <command> [<arguments>]" );
      Console.WriteLine( "Registred commands:" );

      List<Type> commands = new List<Type>();
      foreach ( Type command in fullNames.Values )
        commands.Add( command );

      commands.Sort( TypeUtils.Compare );
      foreach ( Type command in commands )
      {
        object[] attrs = null;
        attrs = command.GetCustomAttributes( typeof( CommandNameAttribute ), false );
        if ( attrs != null && attrs.Length == 1 && attrs[0] is CommandNameAttribute )
        {
          CommandNameAttribute commandNameAttr = attrs[0] as CommandNameAttribute;
          Console.Write( "  {0}", commandNameAttr.fullName );
          if ( !string.IsNullOrEmpty( commandNameAttr.shortName ) )
            Console.Write( " ({0})", commandNameAttr.shortName );

          Console.WriteLine( ": {0}", commandNameAttr.description );
          foreach ( FieldInfo field in command.GetFields() )
          {
            attrs = field.GetCustomAttributes( typeof( CommandArgumentAttribute ), false );
            if ( attrs == null || attrs.Length != 1 || !( attrs[0] is CommandArgumentAttribute ) )
              continue;

            CommandArgumentAttribute commandArgAttr = attrs[0] as CommandArgumentAttribute;
            if ( field.FieldType == typeof( bool ) )
            {
              Console.Write( "    --{0}", commandArgAttr.fullName );
              if ( !string.IsNullOrEmpty( commandArgAttr.shortName ) )
                Console.Write( " (-{0})", commandArgAttr.shortName );
              Console.WriteLine( ": {0}", commandArgAttr.description );
            }
            else if ( field.FieldType == typeof( int ) || field.FieldType == typeof( float ) || field.FieldType == typeof( string ) )
            {
              Console.Write( "    --{0}=<value>", commandArgAttr.fullName );
              if ( !string.IsNullOrEmpty( commandArgAttr.shortName ) )
                Console.Write( " (-{0})", commandArgAttr.shortName );
              Console.WriteLine( ": {0}", commandArgAttr.description );
            }
          }
        }
      }
    }
  }
}
