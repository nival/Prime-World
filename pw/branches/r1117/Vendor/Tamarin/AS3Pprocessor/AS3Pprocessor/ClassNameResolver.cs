using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AS3Pprocessor
{
  static class ClassNameResolver
  {
    private static Dictionary<String, String> _typeMap = new Dictionary<String, String>();

    private static void InitTypeMap()
    {
      _typeMap["Boolean"] = "bool";
      _typeMap["Number"] = "double";
      _typeMap["String"] = "String";
      _typeMap["void"] = "void";
      _typeMap["int"] = "int";
      _typeMap["uint"] = "uint";
      _typeMap["Object"] = "AvmBox";
      _typeMap["Class"] = "ClassClosure";
      _typeMap["String"] = "AvmString";
    }

    /// <summary>
    /// removes comments from class name
    /// </summary>
    /// <param name="className"></param>
    /// <returns></returns>
    public static String TrimComments( String className )
    {
      return RegExps.ClassCommentTrimmerRegex.Match( className ).Groups["ClassName"].Value;
    }

    /// <summary>
    /// Returns a resolved class name. a little bit messy cause of static option
    /// </summary>
    /// <param name="asType"></param>
    /// <param name="typeSpec"></param>
    /// <param name="isStatic"></param>
    /// <returns></returns>
    static public String ResolveClassName( String asType, String typeSpec, bool isStatic )
    {
      //initialize if its empty.
      if ( _typeMap.Keys.Count == 0 )
        InitTypeMap();


      String checkInMapName = ( asType == "Object" && isStatic ) ? "Class" : asType;

      //simple types
      if ( _typeMap.ContainsKey( checkInMapName ) )
        return _typeMap[checkInMapName];

      //build vector spec
      if ( asType == "Vector" )
        return BuildVectorClassName( typeSpec );

      //we have to have an implementation for it
      String implementationClass = asType + (isStatic? "Class":"Object");
      if ( !ClassStatistics.HasImplementation( implementationClass ) )
      {
        //ClassStatistics.ReportError( asType );
        return ( isStatic ? "ClassClosure" : "ScriptObject" ) + "/*" + asType + "*/ ";
      }

      return implementationClass;
    }

    private static String BuildVectorClassName( String typeSpec )
    {
      switch ( typeSpec )
      {
      case "int":
        return "IntVectorObject";
      case "uint":
        return "UIntVectorObject";
      case "Number":
        return "DoubleVectorObject";
      default:
        return "ObjectVectorObject";
      }
    }
  }
}
