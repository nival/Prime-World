using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text.RegularExpressions;

namespace PF_EditorC
{
  public static class StringProcessor
  {
    public sealed class EvaluationException : Exception
    {
      public int Position { get; private set; }

      public EvaluationException( int _pos, string format, params object[] args )
        : base( string.Format( format, args ) )
      {
        Position = _pos;
      }
    }

    #region Operations

    private const int INVALID_PRIORITY = 0;
    private const int BRACE_PRIORITY = -1;
    private const int MATH_PRIORITY = -2;

    public enum ValueType
    {
      FloatType,
      StringType
    };

    public struct UniValue
    {
      public UniValue( float value )
      {
        bindedType = ValueType.FloatType;
        floatValue = value;
        stringValue = "";
      }

      public UniValue( string value )
      {
        bindedType = ValueType.StringType;
        stringValue = value;
        floatValue = 0.0f;
      }

      public readonly ValueType bindedType;
      public readonly float floatValue;
      public readonly string stringValue;
    };

    private interface IOperation
    {
      int Priority { get; }
      void Calculate( ref Stack<UniValue> values );
    };

    public delegate float VariableHandler( string variable );
    public delegate float FloatOperationHandler( float[] args );
    public delegate float UniOperationHandler( VariableHandler variables, UniValue[] args );

    private sealed class Value : IOperation
    {
      public int Priority { get { return MATH_PRIORITY; } }

      public Value( float _value )
      {
        value = new UniValue( _value );
      }

      public Value( string _value )
      {
        value = new UniValue( _value );
      }

      public void Calculate( ref Stack<UniValue> values )
      {
        values.Push( value );
      }

      private UniValue value;
    };

    private sealed class Variable : IOperation
    {
      public int Priority { get { return MATH_PRIORITY; } }

      public Variable( VariableHandler _handler, string _name )
      {
        handler = _handler;
        name = _name;
      }

      public void Calculate( ref Stack<UniValue> values )
      {
        values.Push( new UniValue( handler( name ) ) );
      }

      private event VariableHandler handler = null;
      private string name;
    }

    private abstract class Function : IOperation
    {
      public int Priority { get; private set; }

      protected byte ArgsCount { get; private set; }

      public Function( int _priority, byte _argsCount )
      {
        Priority = _priority;
        ArgsCount = _argsCount;
      }

      public abstract void Calculate( ref Stack<UniValue> values );
    }

    private class FloatFunction : Function
    {
      public FloatFunction( FloatOperationHandler _handler, int _priority, byte _argsCount )
        : base( _priority, _argsCount )
      {
        handler = _handler;
      }

      public FloatFunction( FloatOperationHandler _handler, byte _argsCount )
        : this( _handler, MATH_PRIORITY, _argsCount ) { }

      public override sealed void Calculate( ref Stack<UniValue> values )
      {
        float[] args = new float[ArgsCount];
        for ( int i = 0; i < ArgsCount; ++i )
        {
          if ( values.Count > 0 )
          {
            UniValue value = values.Pop();
            if ( value.bindedType == ValueType.FloatType )
            {
              args[ArgsCount - i - 1] = value.floatValue;
            }
            else
            {
              throw new ArgumentException( "Float Function can't have string operands!" );
            }
          }
        }

        values.Push( new UniValue( handler( args ) ) );
      }

      private event FloatOperationHandler handler = null;
    }

    private sealed class UnaryOperation : FloatFunction
    {
      public UnaryOperation( FloatOperationHandler _handler, int _priority ) : base( _handler, _priority, 1 ) { }
    }
    private sealed class BinaryOperation : FloatFunction
    {
      public BinaryOperation( FloatOperationHandler _handler, int _priority ) : base( _handler, _priority, 2 ) { }
    }
    private sealed class TernaryOperation : FloatFunction
    {
      public TernaryOperation( FloatOperationHandler _handler, int _priority ) : base( _handler, _priority, 3 ) { }
    }

    private sealed class UniFunction : Function
    {
      public UniFunction( UniOperationHandler _handler, byte _argsCount )
        : base( MATH_PRIORITY, _argsCount )
      {
        handler = _handler;
      }

      public UniFunction( UniFunction function, VariableHandler _variables, UniValue[] _args )
        : base( MATH_PRIORITY, 0 )
      {
        handler = function.handler;
        variables = _variables;
        args = _args;
      }

      public override sealed void Calculate( ref Stack<UniValue> values )
      {
        UniValue[] args = new UniValue[ArgsCount];
        for ( int i = 0; i < ArgsCount; ++i )
        {
          args[ArgsCount - i - 1] = values.Pop();
        }

        values.Push( new UniValue( handler( variables, args ) ) );
      }

      private event UniOperationHandler handler = null;
      private event VariableHandler variables = null;
      private UniValue[] args;
    }

    private sealed class BraceOperation : IOperation
    {
      public int Priority { get { return BRACE_PRIORITY; } }

      public BraceOperation() { }

      public void Calculate( ref Stack<UniValue> values ) { }
    };

    #endregion

    public sealed class Expression
    {
      public Expression( string _expression, VariableHandler _variables )
      {
        expression = _expression;
        variables = _variables;
      }

      public float Calculate()
      {
        if ( operations == null )
        {
          operations = StringProcessor.Process( expression, variables ).ToArray();
        }

        Stack<UniValue> values = new Stack<UniValue>();
        foreach ( IOperation operation in operations )
        {
          operation.Calculate( ref values );
        }

        if ( values.Count != 1 )
        {
          throw new InvalidOperationException( "Invalid operation defined" );
        }

        UniValue result = values.Peek();
        if ( result.bindedType != ValueType.FloatType )
        {
          throw new InvalidOperationException( "Invalid operation defined" );
        }

        return result.floatValue;
      }

      private IOperation[] operations;
      private readonly string expression;
      private event VariableHandler variables;
    }

    private static Dictionary<char, FloatFunction> math = new Dictionary<char, FloatFunction>();
    private static Dictionary<string, Function> simple = new Dictionary<string, Function>();
    private static Dictionary<string, Function> functions = new Dictionary<string, Function>();
    private const string FUNC_ARGS_PATTERN = "{0}[{1}]";

    private static float Bool2Float( bool b ) { return b ? 1.0f : 0.0f; }

    static StringProcessor()
    {
      math['~'] = new UnaryOperation( ( float[] args ) => -args[0], 8 );
      math['!'] = new UnaryOperation( ( float[] args ) => Bool2Float( args[0] == 0.0f ), 8 );

      math['*'] = new BinaryOperation( ( float[] args ) => args[0] * args[1], 7 );
      math['/'] = new BinaryOperation( ( float[] args ) => args[0] / args[1], 7 );
      math['%'] = new BinaryOperation( ( float[] args ) => args[0] % args[1], 7 );

      math['+'] = new BinaryOperation( ( float[] args ) => args[0] + args[1], 6 );
      math['-'] = new BinaryOperation( ( float[] args ) => args[0] - args[1], 6 );

      math['<'] = new BinaryOperation( ( float[] args ) => Bool2Float( args[0] < args[1] ), 5 );
      math['>'] = new BinaryOperation( ( float[] args ) => Bool2Float( args[0] > args[1] ), 5 );
      math['≤'] = new BinaryOperation( ( float[] args ) => Bool2Float( args[0] <= args[1] ), 5 );
      math['≥'] = new BinaryOperation( ( float[] args ) => Bool2Float( args[0] >= args[1] ), 5 );

      math['='] = new BinaryOperation( ( float[] args ) => Bool2Float( args[0] == args[1] ), 4 );
      math['≠'] = new BinaryOperation( ( float[] args ) => Bool2Float( args[0] != args[1] ), 4 );

      math['&'] = new BinaryOperation( ( float[] args ) => Bool2Float( ( args[0] != 0.0f ) && ( args[1] != 0.0f ) ), 3 );

      math['|'] = new BinaryOperation( ( float[] args ) => Bool2Float( ( args[0] != 0.0f ) || ( args[1] != 0.0f ) ), 2 );

      math['?'] = new TernaryOperation( ( float[] args ) => ( args[0] != 0.0f ) ? args[1] : args[2], 1 );
    }

    public static void AddFunction( string name, byte argsCount, FloatOperationHandler handler )
    {
      simple.Add( string.Format( FUNC_ARGS_PATTERN, name, argsCount ), new FloatFunction( handler, argsCount ) );
    }

    public static void AddFunction( string name, byte argsCount, UniOperationHandler handler )
    {
      functions.Add( string.Format( FUNC_ARGS_PATTERN, name, argsCount ), new UniFunction( handler, argsCount ) );
    }

    private static int FindFirstOfAny( string str, params string[] values )
    {
      int result = -1;
      foreach ( var value in values )
      {
        int valueIndex = str.IndexOf( value );
        if ( valueIndex >= 0 && ( result == -1 || result > valueIndex ) )
        {
          result = valueIndex;
        }
      }

      return result;
    }

    private static string ProcessTernarns( string text )
    {
      string body = @"([^\?:]+)";
      Regex ternExpression = new Regex( body + "\\?" + body + ":" + body );
      MatchCollection ternMatches = ternExpression.Matches( text );
      if ( ternMatches.Count == 0 )
      {
        return text;
      }

      foreach ( Match match in ternMatches )
      {
        string operand1 = match.Groups[1].Value;
        string operand2 = match.Groups[2].Value;
        string operand3 = match.Groups[3].Value;

        text = text.Replace( match.Value, "(" + operand1 + ")?(" + operand2 + ")(" + operand3 + ")" );
      }

      return ProcessTernarns( text );
    }

    private static string PrepareExpression( string expression )
    {
      if ( string.IsNullOrEmpty( expression ) )
      {
        return string.Empty;
      }

      int endPos = FindFirstOfAny( expression, ";", "//" );
      if ( endPos == -1 )
      {
        endPos = expression.Length;
      }

      string result = "";
      for ( int i = 0; i < endPos; ++i )
      {
        if ( expression[i] != ' ' && expression[i] != '\t' )
        {
          result += expression[i];
        }
      }

      #region floating point processing
      {
        if ( result.Length > 1 )
        {
          if ( ( result[0] == '.' ) && IsNumber( result[1] ) )
          {
            result = '0' + result;
          }

          endPos = result.Length;
          if ( IsNumber( result[endPos - 2] ) && ( result[endPos - 1] == '.' ) )
          {
            result = result + '0';
          }
        }

        result = Regex.Replace( result, @"\b(\d+)((\.\d+)|\.)?f?", "${1}${3}" );
      }
      #endregion

      result = result.Replace( ">=", "≥" );
      result = result.Replace( "<=", "≤" );
      result = result.Replace( "!=", "≠" );
      result = result.Replace( "==", "=" );
      result = result.Replace( "&&", "&" );
      result = result.Replace( "||", "|" );

      math['≠'] = new BinaryOperation( ( float[] args ) => Bool2Float( args[0] != args[1] ), 2 );
      math['<'] = new BinaryOperation( ( float[] args ) => Bool2Float( args[0] < args[1] ), 2 );
      math['>'] = new BinaryOperation( ( float[] args ) => Bool2Float( args[0] > args[1] ), 2 );
      math['≤'] = new BinaryOperation( ( float[] args ) => Bool2Float( args[0] <= args[1] ), 2 );
      math['≥'] = new BinaryOperation( ( float[] args ) => Bool2Float( args[0] >= args[1] ), 2 );

      result = result.Replace( "mObjectParent->", "" );
      result = Regex.Replace( result, @"\b[cm]([A-Z][\w_]*)\b", "curtalconst(\"$1\")" );

      result = result.Replace( "ABILITYTYPE_INVALID", "curtalconst(\"ABILITYTYPE__INVALID\")" );
      result = result.Replace( "ABILITYTYPE_MULTIACTIVE", "curtalconst(\"ABILITYTYPE__MULTIACTIVE\")" );
      result = result.Replace( "ABILITYTYPE_ACTIVE", "curtalconst(\"ABILITYTYPE__ACTIVE\")" );
      result = result.Replace( "ABILITYTYPE_PASSIVE", "curtalconst(\"ABILITYTYPE__PASSIVE\")" );
      result = result.Replace( "ABILITYTYPE_AUTOCASTABLE", "curtalconst(\"ABILITYTYPE__AUTOCASTABLE\")" );
      result = result.Replace( "ABILITYTYPE_SWITCHABLE", "curtalconst(\"ABILITYTYPE__SWITCHABLE\")" );
      result = result.Replace( "ABILITYTYPE_CHANNELLING", "curtalconst(\"ABILITYTYPE__CHANNELLING\")" );
      result = result.Replace( "sNaftaLevel", "curtalconst(\"HeroLevel\")" );
      result = result.Replace( "sNafta", "curtalconst(\"NaftaCost\")" );
      result = result.Replace( "sDevPoints", "curtalconst(\"DevPoints\")" );
      result = result.Replace( "sender.vInventor_Details", "curtalconst(\"A0_MaxDetails\")" );
      result = result.Replace( "pFirst->IsRecommended", "IsRecommended" );
      result = result.Replace( "()->", "." );
      result = result.Replace( "->", "." );

      return ProcessTernarns( result );
    }

    private static bool IsGoodPlaceForBinaryOperation( char prev )
    {
      return prev == ')' || prev == '"' || IsAlphaNumber( prev );
    }

    private static bool IsAlphaNumber( char c )
    {
      return IsAlpha( c ) || IsNumber( c );
    }

    private static bool IsAlpha( char c )
    {
      return c == '_' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
    }

    private static bool IsNumber( char c )
    {
      return c >= '0' && c <= '9';
    }

    private static bool IsAlphaNumberPoint( char c )
    {
      return IsAlpha( c ) || IsNumberPoint( c );
    }

    private static bool IsNumberPoint( char c )
    {
      return c == '.' || IsNumber( c );
    }

    private static List<IOperation> Process( string _expression, VariableHandler variables )
    {
      string expression = PrepareExpression( _expression );

      if ( string.IsNullOrEmpty( expression ) )
      {
        throw new EvaluationException( 0, "Cannot evaluate empty string" );
      }

      List<IOperation> result = new List<IOperation>();
      Stack<IOperation> stack = new Stack<IOperation>();

      int index = 0;
      while ( index < expression.Length )
      {
        char c0 = index == 0 ? ' ' : expression[index - 1];
        char c = expression[index];
        char c2 = index == expression.Length - 1 ? ' ' : expression[index + 1];
        if ( math.ContainsKey( c ) && IsGoodPlaceForBinaryOperation( c0 ) )
        {
          ++index;
          IOperation operation = math[c];
          while ( stack.Count > 0 && ( stack.Peek().Priority >= operation.Priority ) )
          {
            result.Add( stack.Pop() );
          }
          stack.Push( operation );
        }
        else if ( c == '-' )
        {
          ++index;
          IOperation operation = math['~'];
          while ( stack.Count > 0 && ( stack.Peek().Priority >= operation.Priority ) )
          {
            result.Add( stack.Pop() );
          }
          stack.Push( operation );
        }
        else if ( c == '+' )
        {
          ++index;
        }
        else if ( c == '!' )
        {
          ++index;
          IOperation operation = math['!'];
          while ( stack.Count > 0 && ( stack.Peek().Priority >= operation.Priority ) )
          {
            result.Add( stack.Pop() );
          }
          stack.Push( operation );
        }
        else if ( IsNumberPoint( c ) )
        {
          string value = string.Empty;
          bool eFound = false;
          while ( index < expression.Length && IsNumberPoint( expression[index] ) )
          {
            value += expression[index++];
            if ( index < expression.Length && !eFound && ( expression[index] == 'E' || expression[index] == 'e' ) )
            {
              value += expression[index++];
              eFound = true;
              if ( index < expression.Length && ( expression[index] == '-' || expression[index] == '+' ) )
                value += expression[index++];
            }
          }

          NumberFormatInfo numFormat = new NumberFormatInfo();
          numFormat.NumberDecimalSeparator = ".";
          numFormat.NumberGroupSeparator = "";
          result.Add( new Value( float.Parse( value, numFormat ) ) );
        }
        else if ( c == '(' )
        {
          ++index;
          stack.Push( new BraceOperation() );
        }
        else if ( c == '"' )
        {
          ++index;
          int nameStart = index;
          while ( index < expression.Length && expression[index] != '"' )
          {
            if ( expression[index] == '\\' )
            {
              ++index;
            }
            ++index;
          }
          if ( index >= expression.Length )
          {
            throw new EvaluationException( nameStart - 1, "Cannot find close quote" );
          }
          int nameEnd = index;
          if ( nameEnd > nameStart )
          {
            string name = expression.Substring( nameStart, nameEnd - nameStart );
            result.Add( new Value( name ) );
          }
          ++index;
        }
        else if ( IsAlpha( c ) )
        {
          string operation = "";
          while ( index < expression.Length && ( IsAlphaNumberPoint( expression[index] ) ) )
          {
            operation += expression[index++];
          }

          if ( ( index < expression.Length - 1 ) && ( expression[index] == '(' ) )
          {
            /// get string in format 'function(arg1, arg2, ...) ...'
            int argsCount = GetArgsCount( operation + expression.Substring( index ) );

            ++index;
            Function func;
            if ( TryGetFunction( operation, argsCount, out func ) )
              stack.Push( func );
            else
              throw new EvaluationException( index, "Unknown operation \"{0}\"", operation );
          }
          else
          {
            result.Add( new Variable( variables, operation ) );
          }
        }
        else if ( c == ',' )
        {
          while ( stack.Count > 0 && ( stack.Peek().Priority > INVALID_PRIORITY ) )
            result.Add( stack.Pop() );
          if ( stack.Count == 0 || stack.Peek().Priority == BRACE_PRIORITY )
            throw new EvaluationException( index, "Cannot find operation for '{0}'", c );

          ++index;
        }
        else if ( c == ')' )
        {
          while ( stack.Count > 0 && ( stack.Peek().Priority > INVALID_PRIORITY ) )
          {
            IOperation temp = stack.Pop();
            result.Add( temp );
          }
          if ( stack.Count == 0 )
            throw new EvaluationException( index, "Cannot find open brace" );

          IOperation operation = stack.Pop();
          if ( operation.Priority == MATH_PRIORITY )
            result.Add( operation );

          ++index;
        }
        else
        {
          throw new EvaluationException( index, "Invalid character '{0}'", c );
        }
      }

      while ( stack.Count > 0 )
      {
        IOperation temp = stack.Pop();
        if ( temp.Priority < INVALID_PRIORITY )
          throw new EvaluationException( 0, "Cannot find close brace" );
        result.Add( temp );
      }

      return result;
    }

    
    private static bool TryGetFunction( string name, int argsCount, out Function func )
    {
      var stringWithArgs = string.Format( FUNC_ARGS_PATTERN, name, argsCount );
      bool found = false;
      found = TryGetFunction( name, out func );
      if ( !found )
        found = TryGetFunction( stringWithArgs, out func );

      return found;
    }

    private static bool TryGetFunction( string name, out Function func )
    {
      bool found = false;
      found = simple.TryGetValue( name, out func );
      if ( !found )
        found = functions.TryGetValue( name, out func );

      return found;
    }

    /// <summary>
    /// Gets arguments count from first function in string
    /// </summary>
    /// <param name="functionString">function(arg1, arg2, ..., argN)...</param>
    /// <returns></returns>
    private static int GetArgsCount( string functionString )
    {
      /// http://social.msdn.microsoft.com/Forums/en-US/b3c7d94b-b32e-4e21-b389-2ff19e21ae78/pattern-for-parsing-function-parameters?forum=regexp
      const string regex = @"^(?<member>(?>[^(]+))\(
        (?:
         (?<parameter>
           (?:
            (?>[^,()""']+)|
            ""(?>[^\\""]+|\\"")*""|
            @""(?>[^""]+|"""")*""|
            '(?:[^']|\\')'|
            \(
              (?:
               (?<nest>\()|
               (?<-nest>\))|
               (?>[^()]+)
              )*
              (?(nest)(?!))
            \)
           )+
         )
         \s*
         (?(?=,),\s*|(?=\)))
        )+
        \)";

      MatchCollection matches = Regex.Matches( functionString, regex, RegexOptions.IgnorePatternWhitespace );
      var argsCount = 0;
      if ( matches.Count > 0 )
      {
        Group group = matches[0].Groups["parameter"];
        CaptureCollection captures = group.Captures;
        argsCount = captures.Count;
      }
      return argsCount;
    }
  }
}
