using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Runtime.InteropServices;
using NUnit.ConsoleRunner;
using NUnit.Framework;

namespace EditorTests
{
  class Program
  {
    //CRAP{ Use Win32 library here
    public const int MB_ICONHAND = 0x10;

    [DllImport( "user32" )]
    private static extern int MessageBeep( uint uType );
    //CRAP}

    static string FindFixtureOrTest( string pattern )
    {
      foreach ( Type type in Assembly.GetEntryAssembly().GetTypes() )
      {
        if ( type.GetCustomAttributes( typeof( TestFixtureAttribute ), false ).Length == 0 )
          continue;
        if ( type.Name.StartsWith( pattern, StringComparison.InvariantCultureIgnoreCase ) )
          return type.FullName;

        foreach ( MethodInfo method in type.GetMethods( BindingFlags.Instance | BindingFlags.Public ) )
        {
          if ( method.GetCustomAttributes( typeof( TestAttribute ), false ).Length == 0 )
            continue;
          if ( method.Name.StartsWith( pattern, StringComparison.InvariantCultureIgnoreCase ) )
            return type.FullName + "." + method.Name;
        }
      }

      return string.Empty;
    }

    static int Main( string[] args )
    {
      List<string> customArgs = new List<string>();
      customArgs.Add( Assembly.GetEntryAssembly().Location );

      foreach ( string arg in args )
      {
        string fullTestName = FindFixtureOrTest( arg );
        if ( string.IsNullOrEmpty( fullTestName ) )
        {
          Console.WriteLine( "No test or fixture found with name starts with \"{0}\"", arg );
          Trace.WriteLine( string.Format( "No test or fixture find with name starts with \"{0}\"", arg ) );
          return -1;
        }

        customArgs.Add( "/run:" + fullTestName );
      }

      customArgs.Add( "/xml:" + "nunit.report.xml" );
      customArgs.Add( "/domain:None" );

      int result = Runner.Main( customArgs.ToArray() );
      if ( result != 0 )
        MessageBeep( MB_ICONHAND );
      return result;
    }
  }
}
