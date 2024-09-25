using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.IO;

namespace AS3Pprocessor
{
  class ClassTemplate
  {
    private const String CLASS_CLOSURE = "ClassClosure";
    private const String SCRIPT_OBJECT = "ScriptObject";

    private String _fileContent;
    private String _className;
    private String _objectClassName;
    List<String> _requiredHeaders = new List<String>();
    
    public ClassTemplate( String FileContent )
    {
      _fileContent = FileContent;
    }
    
    public String ClassName
    {
      get { return _className; }
    }

    public String ObjectClassName
    {
      get { return _objectClassName; }
    }

    public IEnumerable<String> RequiredHeaders
    {
      get {return _requiredHeaders;}
    }

    public String GetClassBody() 
    {
      String classBody = GetBody( RegExps.ClassNameRegex, global::AS3Pprocessor.Properties.Resources.ClassTemplate, true, out _className );
      String objectClassName = RegExps.ObjectNameRegex.Match( _fileContent ).Groups["ClassName"].Value;
      return classBody.Replace( "${ObjectName}", objectClassName );
    }

    public String GetObjecClasstBody()
    {
      return GetBody(RegExps.ObjectNameRegex, global::AS3Pprocessor.Properties.Resources.ObjectTemplate, false, out _objectClassName );
    }

    private String GetBody( Regex classNameRegex, String template, bool isStatic, out String className)
    {
      if ( !classNameRegex.IsMatch( _fileContent ) )
      {
        return className = String.Empty;
      }

      String body = template;

      String parentClass = RegExps.ParentClassRegex.Match( _fileContent ).Groups["ParentClass"].Value;
      
      String functions = String.Empty;
      FunctionTemplate funcTemplate = new FunctionTemplate();
      className = classNameRegex.Match( _fileContent ).Groups["ClassName"].Value;

      String resolvedParentClass = ClassNameResolver.TrimComments( ClassNameResolver.ResolveClassName( parentClass, String.Empty, isStatic ) );
      resolvedParentClass = resolvedParentClass.Replace( "AvmBox", "ScriptObject" ); //replace it in case of inheritance
      body = body.Replace( "${ParentClass}", resolvedParentClass );

      if ( resolvedParentClass != ( isStatic ? CLASS_CLOSURE : SCRIPT_OBJECT ) )
        _requiredHeaders.Add( ClassStatistics.ResolveHeaderForClass( resolvedParentClass, className ) );

      foreach ( Match match in RegExps.FunctionRegex.Matches( _fileContent ) )
      {
        String functionBody = funcTemplate.GetFunctionBody( match, isStatic, className );
        if ( String.IsNullOrEmpty( functionBody ) )
          continue;
        functions += functionBody + "\n\n";
      }

      body = body.Replace( "${ClassName}", className );
      body = body.Replace( "${ClassFunctions}", functions );

      return body;
    }
  }
}
