using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.IO;

namespace AS3Pprocessor
{
  class FunctionTemplate
  {
    public FunctionTemplate()  
    {
      _classesWithoutPointer.Add("bool");
      _classesWithoutPointer.Add("double");
      _classesWithoutPointer.Add("void");
      _classesWithoutPointer.Add("int");
      _classesWithoutPointer.Add("uint");
      _classesWithoutPointer.Add( "AvmBox" );
      _classesWithoutPointer.Add( "AvmString" );
    }
    
    private List<String> _classesWithoutPointer = new List<String>();
    private List<String> _currentDependencies = new List<String>();
 
    /// <summary>
    /// converts as3 type to the corresponding c++ type
    /// </summary>
    /// <param name="asType"></param>
    /// <returns></returns>
    private string AS3Type2CPPType(String asType, String typeSpec)
    {
      if ( String.IsNullOrEmpty( asType ) )
        return "AvmBox";  
      String resolvedClassName = ClassNameResolver.ResolveClassName( asType, typeSpec, false);
      if (!_classesWithoutPointer.Contains(resolvedClassName))
      {
        //we have to declare this class in header
        _currentDependencies.Add( ClassNameResolver.TrimComments(resolvedClassName) );
        resolvedClassName += "*";
      }
      return resolvedClassName;
    }

   

    //arguments regex
    //"(?<argumentName>(\\w+))\\s*\\:\\s*(?<argumentType>(\\w+))(\\.\\<(?<TypeSpec>\\w+)\\>)?",
    private String ConvertArguments( String arguments )
    {
      String cppArguments = String.Empty;
      foreach ( Match match in RegExps.ArgumentsRegex.Matches(arguments))
      {
        if (!String.IsNullOrEmpty(match.Groups["VariableArgList"].Value))
        {
          //means we have a variable arg list here. so process it exclusively
          cppArguments += "..., ";
          continue;
        }
        String argName = match.Groups["argumentName"].Value;
        String typeSpec = match.Groups["TypeSpec"].Value;
        String argType = AS3Type2CPPType( match.Groups["argumentType"].Value, typeSpec);
        cppArguments += argType + " " + argName + ", ";
      }

      if ( String.IsNullOrEmpty( cppArguments ) )
        return String.Empty;

      return cppArguments.Remove(cppArguments.Length-2);
    }

     //template
     //${Static}${ReturnType} ${GetSet}${FunctionName}(${Params})
     //{
	   //   trace("${ClassName}::${FunctionName}");
	   //   return (${ReturnType})0;
     //}

    //function regex
    //(public|private)\\s*(?<isStatic>static)?\\s*native\\s*function\\s* (?<set_get>(set|get))?\\s*(?<funcname>\\w+)\\
    //((?<arguments>(.*))\\)\\s*\\:\\s*(?<returnType>\\w+)
    public String GetFunctionBody( Match match, bool isStatic, String className)
    {
      String isStaticGroup = match.Groups["isStatic"].Value;

      //check that we have only static or nonstatic functions
      if ( String.IsNullOrEmpty( isStaticGroup ) == isStatic )
        return String.Empty ;

      String function = global::AS3Pprocessor.Properties.Resources.FunctionTemplate;
      //function = function.Replace( "${Static}", isStatic ? "static " : String.Empty );

      String setOrGet = match.Groups["set_get"].Value;
      if ( !String.IsNullOrEmpty( setOrGet ) ) setOrGet += "_";
      function = function.Replace( "${GetSet}", setOrGet);

      String returnType = match.Groups["returnType"].Value;
    
      function = function.Replace( "${ReturnType}", AS3Type2CPPType(returnType, String.Empty) );

      String funcName = match.Groups["funcname"].Value;
      function = function.Replace( "${FunctionName}", funcName );

      String arguments = match.Groups["arguments"].Value;
      function = function.Replace( "${Params}", ConvertArguments(arguments) );

      function = function.Replace( "${ClassName}", className);

      foreach (String dependency in _currentDependencies)
      {
        ClassStatistics.AddDependencyForClass( className, dependency );
      }

      return function;
    }
  }
}
