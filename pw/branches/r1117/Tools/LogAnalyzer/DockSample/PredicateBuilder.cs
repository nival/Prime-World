//using System;
//using System.Collections.Generic;
//using System.Text;
//using System.Text.RegularExpressions;
//using System.Reflection;
//using System.CodeDom.Compiler;
//using Microsoft.CSharp;

//namespace DockSample
//{
//  public class PredicateBuilder
//  {
//    public static Predicate<T> Build<T>( string expression )
//    {
//      //Func<T, bool> func = expression.Compile();
//      //Predicate<T> predicate = new Predicate<T>( func );
//      Type type = typeof( T );

//      //parse the expression
//      //minor transforms performed here on the input expression:
//      //    = in the expression goes to == for C# 
//      //    remove any quotation marks from the expression (they will be put in automatically if the 
//      //                                                    property is a string)
//      //    if the property is a string, insert quotation marks in the code
      
//      //foreach ( string strExpression in expressions )
//      //{
//        Regex reg = new Regex( " " );
//        string[] tokens = reg.Split( expression );

//        if ( tokens.Length != 3 )
//          throw new ApplicationException( "Invalid Expression.  Must be in form <property name> <operator> <value> i.e. Salary > 10000.00" );

//        string lhs = tokens[0];
//        string operAtor = tokens[1];
//        if ( operAtor == "=" )
//          operAtor = "==";

//        string rhs = tokens[2];

//        PropertyInfo prop = type.GetProperty( lhs );
//        bool bString = ( prop.PropertyType.FullName == "System.String" );

//        //strip out any quotation marks the user might put in the expression
//        rhs = rhs.Replace( "\"", "" );

//        if ( bString )
//          rhs = string.Format( "\"{0}\"", rhs );

//      //}

//      //build the dynamic assembly for the predicate
//      string predicateTypeName = string.Format( "Predicate<{0}>", type.FullName );
//      string code = "using System; using System.Collections.Generic; namespace DynAsm { public class Match { public static bool MatchFunc(" + type.FullName + " f) { return f." + lhs + " " + operAtor + " " + rhs + "; } public static Predicate<" + type.FullName + "> MatchPred = new Predicate<" + type.FullName + ">(Match.MatchFunc); public static Predicate<" + type.FullName + "> GetPredicate() { return Match.MatchPred; } } }";
//      Assembly dynAsm = BuildAssembly( code );

//      //call the GetPredicate method to get an instance of the predicate
//      Type matchClassType = dynAsm.GetType( "DynAsm.Match" );
//      MethodInfo[] methods = matchClassType.GetMethods();
//      MethodInfo getPredicateInfo = null;

//      foreach ( MethodInfo mi in methods )
//      {
//        if ( mi.Name == "GetPredicate" )
//        {
//          getPredicateInfo = mi;
//          break;
//        }
//      }

//      return (Predicate<T>)getPredicateInfo.Invoke( null, null );
//    }

//    private static Assembly BuildAssembly( string code )
//    {
//      Microsoft.CSharp.CSharpCodeProvider provider = new CSharpCodeProvider();
//      CompilerParameters compilerparams = new CompilerParameters();
//      compilerparams.GenerateExecutable = false;
//      compilerparams.GenerateInMemory = true;
//      AssemblyName[] asms = Assembly.GetExecutingAssembly().GetReferencedAssemblies();
//      foreach ( AssemblyName asName in asms )
//        compilerparams.ReferencedAssemblies.Add( asName.Name + ".dll" );

//      //Add reference to the current application in case types are defined in the .exe
//      //rather than a class library
//      compilerparams.ReferencedAssemblies.Add( Assembly.GetEntryAssembly().ManifestModule.Name );

//      CompilerResults results = provider.CompileAssemblyFromSource( compilerparams, code );

//      if ( results.Errors.HasErrors )
//      {
//        StringBuilder errors = new StringBuilder( "Compiler Errors :\r\n" );
//        foreach ( CompilerError error in results.Errors )
//        {
//          errors.AppendFormat( "Line {0},{1}\t: {2}\n",
//              error.Line, error.Column, error.ErrorText );
//        }
//        throw new ApplicationException( errors.ToString() );
//      }
//      else
//      {
//        return results.CompiledAssembly;
//      }
//    }
//  }
//}
