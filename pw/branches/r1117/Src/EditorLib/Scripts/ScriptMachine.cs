using System;
using System.CodeDom.Compiler;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using libdb.DB;
using libdb.Diagnostics;
using Microsoft.Win32;

namespace EditorLib.Scripts
{
  public class ScriptMachine
  {
    private class MethodExecutor
    {
      public const string MethodName = "Main";

      private readonly MethodInfo method = null;
      private readonly Type type = null;
      private readonly string fileName;
      private readonly string[] arguments = null;

      public MethodExecutor( Type type, string fileName, string[] arguments )
      {
        this.type = type;
        this.fileName = fileName;
        this.arguments = arguments;

        var flags = BindingFlags.Public | BindingFlags.Instance | BindingFlags.FlattenHierarchy;

        if ( ( method = type.GetMethod( MethodName, flags, null, Type.EmptyTypes, null ) ) != null )
        { }
        else if ( ( method = type.GetMethod( MethodName, new Type[] { typeof( IEditorCommonApplication ) } ) ) != null )
        { }
        else if ( ( method = type.GetMethod( MethodName, new Type[] { typeof( IEditorWinApplication ) } ) ) != null )
        { }
        else if ( ( method = type.GetMethod( MethodName, new Type[] { typeof( IEditorCommonApplication ), typeof( string[] ) } ) ) != null )
        { }
        else if ( ( method = type.GetMethod( MethodName, new Type[] { typeof( IEditorWinApplication ), typeof( string[] ) } ) ) != null )
        { }

        if ( ( method != null && method.ReturnType != typeof( IEnumerable ) ) || !CheckForScriptAttribute() )
          method = null;

      }
      private bool CheckForScriptAttribute()
      {
        if ( method == null )
          return false;
        var attr = method.GetCustomAttributes( typeof( ScriptAttribute ), true );
        if ( attr != null && attr.Length > 0 )
        {
          return ( attr[0] as ScriptAttribute ).Contains( Path.GetFileName( fileName ) );
        }
        return true;
      }

      public IEnumerable Execute( IEditorCommonApplication application, IEditorWinApplication winApplication )
      {
        if ( !IsValid )
          return null;

        ParameterInfo[] parameters = method.GetParameters();
        if ( parameters == null || parameters.Length == 0 )
          return method.Invoke( TypeUtils.CreateObject( type ), null ) as IEnumerable;
        if ( parameters.Length == 1 && parameters[0].ParameterType == typeof( IEditorCommonApplication ) )
          return method.Invoke( TypeUtils.CreateObject( type ), new object[] { application } ) as IEnumerable;
        if ( parameters.Length == 1 && parameters[0].ParameterType == typeof( IEditorWinApplication ) )
          return method.Invoke( TypeUtils.CreateObject( type ), new object[] { winApplication } ) as IEnumerable;
        if ( parameters.Length == 2 && parameters[0].ParameterType == typeof( IEditorCommonApplication ) )
          return method.Invoke( TypeUtils.CreateObject( type ), new object[] { application, arguments } ) as IEnumerable;
        if ( parameters.Length == 2 && parameters[0].ParameterType == typeof( IEditorWinApplication ) )
          return method.Invoke( TypeUtils.CreateObject( type ), new object[] { winApplication, arguments } ) as IEnumerable;

        return null;
      }

      public bool IsValid { get { return method != null; } }
      public string FileName { get { return fileName; } }
    }

    private readonly string[] systemRefs = new string[] { "mscorlib.dll", "System.dll", "System.XML.dll", "System.Drawing.dll", "System.Windows.Forms.dll" };
    private readonly string[] editorRefs = new string[] { "libdb.Net.dll", "WeifenLuo.WinFormsUI.Docking.dll", "EditorLib.dll", "Types.DBTypes.dll" };

    private Queue<MethodExecutor> executors = new Queue<MethodExecutor>();
    private IEnumerator script = null;

    private readonly IEditorCommonApplication application = null;
    private readonly IEditorWinApplication winApplication = null;

    public ScriptMachine( IEditorCommonApplication application )
    {
      this.application = application;
      this.winApplication = application as IEditorWinApplication;
    }

    private bool TryGetFileNameFromTag( string line, string tag, out string fileName )
    {
      fileName = string.Empty;
      if ( !line.StartsWith( tag + " " ) )
        return false;

      fileName = line.Substring( tag.Length + 1 ).Trim();
      return true;
    }

    public IEnumerable<string> CopyText(string refFileName, string basePath)
    {
      using ( StreamReader reader = new StreamReader( new FileStream( Path.Combine( basePath, refFileName ), FileMode.Open, FileAccess.Read ) ) )
      {
        string line = string.Empty;
        while ( ( line = reader.ReadLine() ) != null )
        {
          if( line.Contains( "#insert_begin" ))
          {
            while (((line = reader.ReadLine()) != null) && (!line.Contains("#insert_end")))
            {
              yield return line;
            }
          }
        }
      }
      yield return string.Empty;
    }

    public static string GetFrameworkDirectory()
    {
      // This is the location of the .Net Framework Registry Key
      string framworkRegPath = @"Software\Microsoft\.NetFramework";

      // Get a non-writable key from the registry
      RegistryKey netFramework = Registry.LocalMachine.OpenSubKey( framworkRegPath, false );

      // Retrieve the install root path for the framework
      string installRoot = netFramework.GetValue( "InstallRoot" ).ToString();

      // Retrieve the version of the framework executing this program
      string version = string.Format( @"v{0}.{1}.{2}\",
        Environment.Version.Major,
        Environment.Version.Minor,
        Environment.Version.Build );

      // Return the path of the framework
      return Path.Combine( installRoot, version );
    }

    public bool LoadScript( string fileName, string[] arguments )
    {
      List<string> references = new List<string>( editorRefs );
      List<string> files = new List<string>();

      string basePath = Path.GetDirectoryName( Path.GetFullPath( fileName ) );
      string tempPath = Path.Combine( Path.GetTempPath(), Path.GetRandomFileName() );
      Directory.CreateDirectory( tempPath );
      files.Add( Path.GetFileName( fileName ) );
      int index = 0;

      while ( index < files.Count )
      {
        try
        {
          using ( StreamReader reader = new StreamReader( new FileStream( Path.Combine( basePath, files[index] ), FileMode.Open, FileAccess.Read ) ) )
          {
            using ( StreamWriter writer = new StreamWriter( new FileStream( Path.Combine( tempPath, files[index] ), FileMode.Create, FileAccess.Write ) ) )
            {
              string line = string.Empty;
              while ( ( line = reader.ReadLine() ) != null )
              {
                string refFile = string.Empty;
                if ( TryGetFileNameFromTag( line, "#ref", out refFile ) )
                {
                  refFile = refFile.Replace( "{.net}", GetFrameworkDirectory() );
                  if ( references.FindIndex( ( string file ) => { return string.Compare( file, refFile, StringComparison.InvariantCultureIgnoreCase ) == 0; } ) == -1 )
                    references.Add( refFile );
                  line = string.Empty;
                }
                else if ( TryGetFileNameFromTag( line, "#include", out refFile ) )
                {
                  refFile = Path.GetFileName( refFile );
                  if ( references.FindIndex( ( string file ) => { return string.Compare( file, refFile, StringComparison.InvariantCultureIgnoreCase ) == 0; } ) == -1 )
                    files.Add( refFile );
                  line = string.Empty;
                }// we need to add some code strings from other file
                else if (TryGetFileNameFromTag(line, "#insert", out refFile))
                {
                  refFile = Path.GetFileName(refFile);
                  foreach( string copiedLine in CopyText( refFile, basePath ) )
                  {
                    writer.WriteLine(copiedLine);
                  }
                  line = string.Empty;
                }

                writer.WriteLine( line );
              }
            }
          }
        }
        catch
        {
          Log.TraceError( "Cannot load script from file \"{0}\"", fileName );
          return false;
        }
        ++index;
      }

      for ( int i = 0; i < files.Count; ++i )
        files[i] = Path.Combine( tempPath, files[i] );

      CompilerParameters compilerParameters = new CompilerParameters();
      compilerParameters.GenerateInMemory = true;
      compilerParameters.ReferencedAssemblies.AddRange( systemRefs );

      string entryAssemblyPath = Path.GetFullPath( Path.GetDirectoryName( Assembly.GetEntryAssembly().Location ) );
      foreach ( var reference in references )
        compilerParameters.ReferencedAssemblies.Add( Path.Combine( entryAssemblyPath, reference ) );

      CodeDomProvider provider;
      var providerOptions = new Dictionary<string, string> { { "CompilerVersion", "v3.5" } };
      provider = new Microsoft.CSharp.CSharpCodeProvider( providerOptions );
      CompilerResults results = provider.CompileAssemblyFromFile( compilerParameters, files.ToArray() );
      if ( results.Errors.HasErrors )
      {
        foreach ( CompilerError error in results.Errors )
          Log.TraceError( "{0}({1}): {2}: {3}", Path.Combine( basePath, Path.GetFileName( error.FileName ) ), error.Line, error.ErrorNumber, error.ErrorText );
        return false;
      }

      bool notFound = true;
      foreach ( Type type in results.CompiledAssembly.GetTypes() )
      {
        MethodExecutor executor = new MethodExecutor( type, fileName, arguments );
        if ( executor.IsValid )
        {
          notFound = false;
          executors.Enqueue( executor );
        }
      }

      if ( notFound )
        Log.TraceError( "Cannot find suitable \"{0}\" function in script file \"{1}\"", MethodExecutor.MethodName, fileName );

      return true;
    }

    public bool Step()
    {
      try
      {
        while ( ( script == null || !script.MoveNext() ) && executors.Count > 0 )
        {
          var executor = executors.Dequeue();
          script = executor.Execute( application, winApplication ).GetEnumerator();
        }

      }
      catch ( Exception e )
      {
        Log.TraceError( "Exception during script execution. {0}", e.ToString() );
      }

      return script != null && script.Current != null && executors.Count > 0;
    }

    public bool StepWithException()
    {
      while ( ( script == null || !script.MoveNext() ) && executors.Count > 0 )
      {
        var executor = executors.Dequeue();
        script = executor.Execute( application, winApplication ).GetEnumerator();
      }

      return script != null && script.Current != null && executors.Count > 0;
    }

    public bool IsIdle { get { return executors.Count == 0; } }
  }
}
