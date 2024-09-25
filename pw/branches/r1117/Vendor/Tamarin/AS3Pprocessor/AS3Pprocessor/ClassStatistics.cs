using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;


namespace AS3Pprocessor
{
  static class ClassStatistics
  {
    private static List<String> _avaliableClasses = new List<String>();
    static private List<String> _errors = new List<String>();
    static private Dictionary<String, String> _classFolders = new Dictionary<String, String>();
    
#region Dependency Statistics
    private static Dictionary<String, List<String>> _dependencies = new Dictionary<String, List<String>>();
    
    static public IList<String> GetDependenciesForClass(String className)
    {
      if ( !_dependencies.ContainsKey( className ) )
        return new List<String>();
      return _dependencies[className];
    }

    static public void AddDependencyForClass(String className, String dependencyClassName)
    {
      if ( !_dependencies.ContainsKey( className ) )
        _dependencies[className] = new List<String>();

      if (!_dependencies[className].Contains(dependencyClassName))
        _dependencies[className].Add( dependencyClassName );
    }
#endregion

    static public bool HasImplementation(String className)
    {
      return _avaliableClasses.Contains( className );
    }

    public static void BuildStatistics()
    {
      String curDir = Directory.GetCurrentDirectory();

      foreach ( String fileName in Directory.GetFiles( curDir, "*.as", SearchOption.AllDirectories ) )
      {
        _classFolders[Path.GetFileNameWithoutExtension( fileName )] = Path.GetDirectoryName( fileName ).Replace( curDir + "\\", "" ).Replace("\\","/");

        String fileContent = File.ReadAllText( fileName );
        if ( !RegExps.ObjectNameRegex.IsMatch( fileContent ) )
          continue;

        String objectClassName = RegExps.ObjectNameRegex.Match( fileContent ).Groups["ClassName"].Value;
        if ( _avaliableClasses.Contains( objectClassName ) )
          continue;

        String className = RegExps.ClassNameRegex.Match( fileContent ).Groups["ClassName"].Value;
        if ( _avaliableClasses.Contains( className ) )
          continue;

        _avaliableClasses.Add( objectClassName );
      }
     

      //add known classes as well. 
      _avaliableClasses.Add("ByteArrayObject");
      _avaliableClasses.Add("FunctionObject");
      _avaliableClasses.Add("ArrayObject");
      _avaliableClasses.Add("DateObject");
    }

    #region header resolving
    public static String ResolveHeaderForClass( String requiredClass, String forWhichClass )
    {
      String asRequiredClass = GetASClassName( requiredClass ), asForWhichClass = GetASClassName( forWhichClass );
      bool inTheSameFolder = _classFolders[asRequiredClass] == _classFolders[asForWhichClass];
     
      string esacapeToRoot = String.Empty;
      for ( int i = 0; i < GetDeep( _classFolders[asForWhichClass] ); i++ )
        esacapeToRoot += "../";

      String headerFolder = !inTheSameFolder ? esacapeToRoot + _classFolders[asRequiredClass] + '/' : String.Empty;
      return headerFolder + asRequiredClass + ".h";
    }

    private static String GetASClassName( string className )
    {
      return className.EndsWith( "Class" ) ? className.Remove( className.Length - "Class".Length ) : className.Remove( className.Length - "Object".Length );
    }

    private static int GetDeep( string folder )
    { 
      //if its folder deep is already 1
      int deep = 1;
      foreach ( char c in folder)
      {
        if ( c == '/' )
          deep++;
      }
      return deep;  
    }
    #endregion
       
    #region Errors Processing
    public static void DumpErrors()
    {
      if (_errors.Count>0)
      {
        File.WriteAllLines( "headers_errs.txt", _errors.ToArray() );
      }
    }

    public static void ReportError( String error )
    {
      if ( !_errors.Contains( error ) )
      {
        _errors.Add( error );
      }
    }
  }
  #endregion
}
