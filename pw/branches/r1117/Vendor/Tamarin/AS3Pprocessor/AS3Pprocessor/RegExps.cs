using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace AS3Pprocessor
{
  static class RegExps
  {
    //public static native function get rotation() : Number;
    public static Regex FunctionRegex = new Regex(
           "(public|private)?\\s*(?<isStatic>static)?\\s*native\\s*function\\s*" +
           "((?<set_get>(set|get))\\s)?\\s*(?<funcname>\\w+)\\((?<arguments>(.*))\\)\\s*(\\:\\s*(?<returnType>\\w+))?",
         RegexOptions.CultureInvariant
         | RegexOptions.Compiled
         );

    //use_xy:Boolean, x:Number = 0, y:Number = -1, useShape:Boolean, hitTestObject:DisplayObject
    public static Regex ArgumentsRegex = new Regex(
         "((?<argumentName>(\\w+))(\\s*\\:\\s*(?<argumentType>(\\w+))(" +
      "\\.\\<(?<TypeSpec>\\w+)\\>)?(\\s*\\=\\s*(\\\")?(\\-)?\\w+(\\\")" +
      "?)?)?|(?<VariableArgList>\\.\\.\\.\\w+))",
    RegexOptions.CultureInvariant
    | RegexOptions.Compiled
    );

    public static Regex ClassNameRegex = new Regex(
      "\\[native\\(cls=\\\"(?<ClassName>\\w+)\\\"",
    RegexOptions.CultureInvariant
    | RegexOptions.Compiled
    );


    public static Regex ObjectNameRegex = new Regex(
      "\\[native\\((.*)?instance=\\\"(?<ClassName>\\w+)",
    RegexOptions.CultureInvariant
    | RegexOptions.Compiled
    );


    public static Regex ClassCommentTrimmerRegex = new Regex(
      "(?<ClassName>\\w+)\\s*(/\\*.*\\*/)?",
    RegexOptions.CultureInvariant
    | RegexOptions.Compiled
    );

    public static Regex ParentClassRegex = new Regex(
      "extends\\s*(?<ParentClass>\\w+)",
    RegexOptions.CultureInvariant
    | RegexOptions.Compiled
    );

    //// Replace the matched text in the InputText using the replacement pattern
    // string result = regex.Replace(InputText,regexReplace);

    //// Split the InputText wherever the regex matches
    // string[] results = regex.Split(InputText);

    //// Capture the first Match, if any, in the InputText
    // Match m = regex.Match(InputText);

    //// Capture all Matches in the InputText
    // MatchCollection ms = regex.Matches(InputText);

    //// Test to see if there is a match in the InputText
    // bool IsMatch = regex.IsMatch(InputText);

    //// Get the names of all the named and numbered capture groups
    // string[] GroupNames = regex.GetGroupNames();

    //// Get the numbers of all the named and numbered capture groups
    // int[] GroupNumbers = regex.GetGroupNumbers();
  }
}
