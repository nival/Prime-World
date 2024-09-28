using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

namespace SimpleCalc
{
  public class Value
  {
    public enum ValueType
    {
      Double,
      Boolean,
      String,
    }

    private readonly ValueType _type = ValueType.String;
    private readonly object _value;

    public Value( double value )
    {
      _type = ValueType.Double;
      _value = value;
    }

    public Value( float value )
    {
      _type = ValueType.Double;
      _value = (double)value;
    }

    public Value( bool value )
    {
      _type = ValueType.Boolean;
      _value = value;
    }

    public Value( string value )
    {
      _type = ValueType.String;
      _value = value;
    }

    public ValueType Type { get { return _type; } }

    public double Double
    {
      get
      {
        if ( Type == ValueType.Double )
          return (double)_value;
        if ( Type == ValueType.Boolean )
          return Boolean ? 1.0 : 0.0;

        return 0.0;
      }
    }

    public float Float
    {
      get
      {
        return (float)Double;
      }
    }

    public int Int
    {
      get
      {
        return (int)Double;
      }
    }

    public bool Boolean
    {
      get
      {
        if ( Type == ValueType.Boolean )
          return (bool)_value;
        if ( Type == ValueType.Double )
          return Double != 0.0 ? true : false;

        return false;
      }
    }

    public string String
    {
      get
      {
        if ( Type == ValueType.String )
          return (string)_value;

        return _value.ToString();
      }
    }
  }

  public class FunctionsList
  {
    #region delegates

    public delegate TOutput Function0Handler<TOutput>();
    public delegate TOutput Function1Handler<TOutput, T1>( T1 p1 );
    public delegate TOutput Function2Handler<TOutput, T1, T2>( T1 p1, T2 p2 );
    public delegate TOutput Function3Handler<TOutput, T1, T2, T3>( T1 p1, T2 p2, T3 p3 );

    public delegate TOutput ContextFunction0Handler<TOutput, TContext>( TContext context ) where TContext : class;
    public delegate TOutput ContextFunction1Handler<TOutput, T1, TContext>( T1 p1, TContext context ) where TContext : class;
    public delegate TOutput ContextFunction2Handler<TOutput, T1, T2, TContext>( T1 p1, T2 p2, TContext context ) where TContext : class;
    public delegate TOutput ContextFunction3Handler<TOutput, T1, T2, T3, TContext>( T1 p1, T2 p2, T3 p3, TContext context ) where TContext : class;

    #endregion

    #region protected interface IOperation

    protected interface IOperation
    {
      void Calculate( ref Stack<Value> values, object[] context );
      int Priority { get; }
    }

    #endregion

    #region private abstract class TypedFunction and TypedFunctionHelpers

    protected class TypedFunctionHelpers
    {
      protected void CheckType( Type type, int index, string name )
      {
        if ( type == typeof( double ) || type == typeof( float ) || type == typeof( int ) || type == typeof( bool ) || type == typeof( string ) )
          return;

        if ( index == 0 )
          throw new InvalidOperationException( string.Format( "Cannot register function \"{0}\" with result's type \"{1}\"", name, type.Name ) );
        else
          throw new InvalidOperationException( string.Format( "Cannot register function \"{0}\" with argument {1} of type \"{2}\"", name, index, type.Name ) );
      }

      protected T Pop<T>( ref Stack<Value> values, int index, string name )
      {
        var value = values.Pop();
        var type = typeof( T );
        if ( type == typeof( double ) )
          return (T)(object)value.Double;
        if ( type == typeof( float ) )
          return (T)(object)value.Float;
        if ( type == typeof( int ) )
          return (T)(object)value.Int;
        if ( type == typeof( bool ) )
          return (T)(object)value.Boolean;
        if ( type == typeof( string ) )
          return (T)(object)value.String;

        throw new InvalidCastException( string.Format( "Cannot convert argument {0} to type \"{1}\" for function \"{2}\"", index, type, name ) );
      }

      protected void Push<T>( ref Stack<Value> values, T value, string name )
      {
        Value result = null;
        var type = typeof( T );
        if ( type == typeof( double ) )
          result = new Value( (double)(object)value );
        else if ( type == typeof( float ) )
          result = new Value( (float)(object)value );
        else if ( type == typeof( int ) )
          result = new Value( (int)(object)value );
        else if ( type == typeof( bool ) )
          result = new Value( (bool)(object)value );
        else if ( type == typeof( string ) )
          result = new Value( (string)(object)value );

        if ( result != null )
          values.Push( result );
        else
          throw new InvalidCastException( string.Format( "Cannot convert result from type \"{0}\" for function \"{1}\"", type.Name, name ) );
      }
    }

    private abstract class TypedFunction : TypedFunctionHelpers
    {
      private readonly string _name;

      protected TypedFunction( string name, params Type[] types )
      {
        _name = name;
        for ( int i = 0; i < types.Length; ++i )
          CheckType( types[i], i, _name );
      }


      protected T Pop<T>( ref Stack<Value> values, int index )
      {
        return Pop<T>( ref values, index, _name );
      }

      protected void Push<T>( ref Stack<Value> values, T value )
      {
        Push<T>( ref values, value, _name );
      }

      public abstract void Calculate( ref Stack<Value> values, object context );

      public string Name { get { return _name; } }
    }

    #endregion

    #region private class Function : IOperation

    /// <summary>
    /// Selects correct implementation of function among realization with same name and arguments counts but different contexts
    /// </summary>
    private class Function : IOperation
    {
      private readonly string _name;
      private TypedFunction _function;
      private Dictionary<Type, TypedFunction> _contextFunctions;

      public Function( string name ) { _name = name; }

      public void AddFunction( TypedFunction f )
      {
        if ( _function != null )
          throw new InvalidOperationException( string.Format( "Function \"{0}\" already registred", f.Name ) );
        _function = f;
      }

      public void AddFunction( TypedFunction f, Type contextType )
      {
        if ( _contextFunctions == null )
          _contextFunctions = new Dictionary<Type, TypedFunction>();
        else if ( _contextFunctions.ContainsKey( contextType ) )
          throw new InvalidOperationException( string.Format( "Function \"{0}\" with context \"{1}\" already registred", f.Name, contextType.Name ) );

        _contextFunctions.Add( contextType, f );
      }

      public void Calculate( ref Stack<Value> values, object[] context )
      {
        if ( context.Length == 0 || _contextFunctions == null )
        {
          if ( _function == null )
            throw new InvalidOperationException( string.Format( "Cannot find implementation for function \"{0}\" without context", _name ) );

          _function.Calculate( ref values, null );
          return;
        }

        TypedFunction function;
        foreach ( var obj in context )
        {
          if ( obj == null )
            continue;
          if ( _contextFunctions.TryGetValue( obj.GetType(), out function ) )
          {
            function.Calculate( ref values, obj );
            return;
          }
        }

        if ( _function == null )
          throw new InvalidOperationException( string.Format( "Cannot find implementation for function \"{0}\" with contexts", _name ) );

        _function.Calculate( ref values, context );
      }

      public int Priority { get { return 0; } }

      public override string ToString() { return _name; }
    }

    #endregion

    #region Function implementation

    private class Function0<TOutput> : TypedFunction
    {
      private Function0Handler<TOutput> _handler;
      public Function0( string name, Function0Handler<TOutput> handler ) : base( name, typeof( TOutput ) ) { _handler = handler; }

      public override void Calculate( ref Stack<Value> values, object context )
      {
        Push( ref values, _handler() );
      }
    }

    private class Function1<TOutput, T1> : TypedFunction
    {
      private Function1Handler<TOutput, T1> _handler;
      public Function1( string name, Function1Handler<TOutput, T1> handler ) : base( name, typeof( TOutput ), typeof( T1 ) ) { _handler = handler; }

      public override void Calculate( ref Stack<Value> values, object context )
      {
        var p1 = Pop<T1>( ref values, 1 );
        Push( ref values, _handler( p1 ) );
      }
    }

    private class Function2<TOutput, T1, T2> : TypedFunction
    {
      private Function2Handler<TOutput, T1, T2> _handler;
      public Function2( string name, Function2Handler<TOutput, T1, T2> handler ) : base( name, typeof( TOutput ), typeof( T1 ), typeof( T2 ) ) { _handler = handler; }

      public override void Calculate( ref Stack<Value> values, object context )
      {
        var p2 = Pop<T2>( ref values, 2 );
        var p1 = Pop<T1>( ref values, 1 );
        Push( ref values, _handler( p1, p2 ) );
      }
    }

    private class Function3<TOutput, T1, T2, T3> : TypedFunction
    {
      private Function3Handler<TOutput, T1, T2, T3> _handler;
      public Function3( string name, Function3Handler<TOutput, T1, T2, T3> handler ) : base( name, typeof( TOutput ), typeof( T1 ), typeof( T2 ), typeof( T3 ) ) { _handler = handler; }

      public override void Calculate( ref Stack<Value> values, object context )
      {
        var p3 = Pop<T3>( ref values, 3 );
        var p2 = Pop<T2>( ref values, 2 );
        var p1 = Pop<T1>( ref values, 1 );
        Push( ref values, _handler( p1, p2, p3 ) );
      }
    }

    #endregion

    #region ContextFunction implementation

    private class ContextFunction0<TOutput, TContext> : TypedFunction where TContext : class
    {
      private ContextFunction0Handler<TOutput, TContext> _handler;
      public ContextFunction0( string name, ContextFunction0Handler<TOutput, TContext> handler ) : base( name, typeof( TOutput ) ) { _handler = handler; }

      public override void Calculate( ref Stack<Value> values, object context )
      {
        Push( ref values, _handler( context as TContext ) );
      }
    }

    private class ContextFunction1<TOutput, T1, TContext> : TypedFunction where TContext : class
    {
      private ContextFunction1Handler<TOutput, T1, TContext> _handler;
      public ContextFunction1( string name, ContextFunction1Handler<TOutput, T1, TContext> handler ) : base( name, typeof( TOutput ), typeof( T1 ) ) { _handler = handler; }

      public override void Calculate( ref Stack<Value> values, object context )
      {
        var p1 = Pop<T1>( ref values, 1 );
        Push( ref values, _handler( p1, context as TContext ) );
      }
    }

    private class ContextFunction2<TOutput, T1, T2, TContext> : TypedFunction where TContext : class
    {
      private ContextFunction2Handler<TOutput, T1, T2, TContext> _handler;
      public ContextFunction2( string name, ContextFunction2Handler<TOutput, T1, T2, TContext> handler ) : base( name, typeof( TOutput ), typeof( T1 ), typeof( T2 ) ) { _handler = handler; }

      public override void Calculate( ref Stack<Value> values, object context )
      {
        var p2 = Pop<T2>( ref values, 2 );
        var p1 = Pop<T1>( ref values, 1 );
        Push( ref values, _handler( p1, p2, context as TContext ) );
      }
    }

    private class ContextFunction3<TOutput, T1, T2, T3, TContext> : TypedFunction where TContext : class
    {
      private ContextFunction3Handler<TOutput, T1, T2, T3, TContext> _handler;
      public ContextFunction3( string name, ContextFunction3Handler<TOutput, T1, T2, T3, TContext> handler ) : base( name, typeof( TOutput ), typeof( T1 ), typeof( T2 ), typeof( T3 ) ) { _handler = handler; }

      public override void Calculate( ref Stack<Value> values, object context )
      {
        var p3 = Pop<T3>( ref values, 3 );
        var p2 = Pop<T2>( ref values, 2 );
        var p1 = Pop<T1>( ref values, 1 );
        Push( ref values, _handler( p1, p2, p3, context as TContext ) );
      }
    }

    #endregion

    private readonly Dictionary<string, Function>[] _functions = new Dictionary<string, Function>[4];
    private readonly Dictionary<string, Function> _variables = new Dictionary<string, Function>();
    private readonly Dictionary<string, string> _aliases = new Dictionary<string, string>();

    public FunctionsList()
    {
      for ( int i = 0; i < _functions.Length; ++i )
        _functions[i] = new Dictionary<string, Function>();
    }

    private Function GetFunction( string name, Dictionary<string, Function> functions )
    {
      Function result;
      if ( !functions.TryGetValue( name, out result ) )
      {
        result = new Function( name );
        functions.Add( name, result );
      }

      return result;
    }

    private Function GetFunction( string name, int argsCount )
    {
      if ( argsCount < 0 || argsCount > _functions.Length )
        throw new ArgumentOutOfRangeException( "argsCount", argsCount, "Invalid arguments count" );

      return GetFunction( name, _functions[argsCount] );
    }

    public void AddVariable<TOutput>( string name, Function0Handler<TOutput> f )
    {
      GetFunction( name, _variables ).AddFunction( new Function0<TOutput>( name, f ) );
    }

    public void AddContextVariable<TOutput, TContext>( string name, ContextFunction0Handler<TOutput, TContext> f ) where TContext : class
    {
      GetFunction( name, _variables ).AddFunction( new ContextFunction0<TOutput, TContext>( name, f ), typeof( TContext ) );
    }

    public void AddFunction<TOutput>( string name, Function0Handler<TOutput> f )
    {
      GetFunction( name, 0 ).AddFunction( new Function0<TOutput>( name, f ) );
    }

    public void AddContextFunction<TOutput, TContext>( string name, ContextFunction0Handler<TOutput, TContext> f ) where TContext : class
    {
      GetFunction( name, 0 ).AddFunction( new ContextFunction0<TOutput, TContext>( name, f ), typeof( TContext ) );
    }

    public void AddAlias( string name, string expression )
    {
      if ( _aliases.ContainsKey( name ) )
        throw new ArgumentException( string.Format( "Alias with name \"{0}\" already defined", name ), "name" );
      _aliases.Add( name, expression );
    }

    #region AddFunction and AddContextFunction for different arguments count

    public void AddFunction<TOutput, T1>( string name, Function1Handler<TOutput, T1> f )
    {
      GetFunction( name, 1 ).AddFunction( new Function1<TOutput, T1>( name, f ) );
    }

    public void AddFunction<TOutput, T1, T2>( string name, Function2Handler<TOutput, T1, T2> f )
    {
      GetFunction( name, 2 ).AddFunction( new Function2<TOutput, T1, T2>( name, f ) );
    }

    public void AddFunction<TOutput, T1, T2, T3>( string name, Function3Handler<TOutput, T1, T2, T3> f )
    {
      GetFunction( name, 3 ).AddFunction( new Function3<TOutput, T1, T2, T3>( name, f ) );
    }

    public void AddContextFunction<TOutput, T1, TContext>( string name, ContextFunction1Handler<TOutput, T1, TContext> f ) where TContext : class
    {
      GetFunction( name, 1 ).AddFunction( new ContextFunction1<TOutput, T1, TContext>( name, f ), typeof( TContext ) );
    }

    public void AddContextFunction<TOutput, T1, T2, TContext>( string name, ContextFunction2Handler<TOutput, T1, T2, TContext> f ) where TContext : class
    {
      GetFunction( name, 2 ).AddFunction( new ContextFunction2<TOutput, T1, T2, TContext>( name, f ), typeof( TContext ) );
    }

    public void AddContextFunction<TOutput, T1, T2, T3, TContext>( string name, ContextFunction3Handler<TOutput, T1, T2, T3, TContext> f ) where TContext : class
    {
      GetFunction( name, 3 ).AddFunction( new ContextFunction3<TOutput, T1, T2, T3, TContext>( name, f ), typeof( TContext ) );
    }

    #endregion

    protected IOperation TryGetFunction( string name, int argsCount, FunctionsList[] functions )
    {
      if ( functions != null )
      {
        foreach ( var function in functions )
        {
          var operation = function.TryGetFunction( name, argsCount, null );
          if ( operation != null )
            return operation;
        }
      }

      if ( argsCount < 0 || argsCount > _functions.Length )
        return null;

      Function result;
      if ( !_functions[argsCount].TryGetValue( name, out result ) )
        return null;

      return result;
    }

    protected IOperation TryGetVariable( string name, FunctionsList[] functions )
    {
      if ( functions != null )
      {
        foreach ( var function in functions )
        {
          var operation = function.TryGetVariable( name, null );
          if ( operation != null )
            return operation;
        }
      }

      Function result;
      if ( !_variables.TryGetValue( name, out result ) )
        return null;

      return result;
    }

    protected string TryGetAlias( string name, FunctionsList[] functions )
    {
      if ( functions != null )
      {
        foreach ( var function in functions )
        {
          var alias = function.TryGetAlias( name, null );
          if ( !string.IsNullOrEmpty( alias ) )
            return alias;
        }
      }

      string result;
      if ( !_aliases.TryGetValue( name, out result ) )
        return string.Empty;

      return result;
    }
  }

  public class StringProcessor : FunctionsList
  {
    #region public interface IExpression

    public interface IExpression
    {
      Value Calculate( params object[] context );
    }

    #endregion

    #region private class Expression : IExpression

    private class Expression : IExpression
    {
      private readonly string _expression;
      private readonly List<IOperation> _operations = new List<IOperation>();

      public Expression( string expression )
      {
        _expression = expression;
      }

      public void Add( IOperation operation )
      {
        _operations.Add( operation );
      }

      public Value Calculate( params object[] context )
      {
        var values = new Stack<Value>();
        foreach ( var operation in _operations )
          operation.Calculate( ref values, context );

        if ( values.Count != 1 )
          throw new InvalidOperationException( string.Format( "Invalid expression defined \"{0}\"", _expression ) );

        return values.Pop();
      }
    }

    #endregion

    #region private class Token

    private class Token
    {
      public enum TokenType
      {
        Entity,			// Name of entity (starts with _, A-Z, a-z)
        Number,			// Integer, hexadecimal (starts with 0x) or float with possible '.' (starts with 0-9)
        String,			// Text between double quotas (starts with ")
        Operator,		// +, -, *, /, %, ^, &, &&, |, ||, =, !, >, <, >=, <=, !=, ?
        Delemiter,  // braces, comma or :
      }

      private readonly TokenType _type;
      private readonly string _value;
      private readonly int _position;

      private Token( TokenType type, string value, int position )
      {
        _type = type;
        _value = value;
        _position = position;
      }

      public TokenType Type { get { return _type; } }
      public string Value { get { return _value; } }
      public int Position { get { return _position; } }

      private const string OPERATORS = "+-*/%^&|!<=>?";
      private const string DOUBLE_OPERATORS = "&|"; // operators that exists in double form (like & and &&)
      private const string EQUAL_OPERATORS = "!<=>"; // operators that exists with additional equal sign (line > and >=)
      private const string DELEMITERS = ",():";

      private static bool IsNameChar( char c )
      {
        return c == '_' || ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' );
      }

      private static bool IsNumber( char c, bool hex )
      {
        if ( c >= '0' && c <= '9' || c == '.' )
          return true;
        if ( hex && ( ( c >= 'A' && c <= 'F' ) || ( c >= 'a' && c <= 'f' ) ) )
          return true;

        return false;
      }

      private static bool IsNameChar2( char c )
      {
        return c == '_' || ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) || IsNumber( c, false );
      }

      public static Token GetNextToket( string expression, int index, out int nextIndex )
      {
        var length = expression.Length;
        while ( index < length && char.IsWhiteSpace( expression[index] ) )
          ++index;
        if ( index >= length )
        {
          nextIndex = index;
          return null;
        }

        var c = expression[index];

        if ( OPERATORS.IndexOf( c ) >= 0 )
        {
          var c2 = ' ';
          if ( index < length - 1 )
            c2 = expression[index + 1];

          nextIndex = index + 1;
          if ( (c == c2 && DOUBLE_OPERATORS.IndexOf( c ) >= 0) || (c2 == '=' && EQUAL_OPERATORS.IndexOf( c ) >= 0) )
            return new Token( TokenType.Operator, c.ToString() + c2.ToString(), index );

          return new Token( TokenType.Operator, c.ToString(), index );
        }
        else if ( DELEMITERS.IndexOf( c ) >= 0 )
        {
          nextIndex = index + 1;
          return new Token( TokenType.Delemiter, c.ToString(), index );
        }
        else if ( IsNameChar( c ) )
        {
          int pos = index;
          ++index;
          while ( index < expression.Length && IsNameChar2( expression[index] ) )
            ++index;

          nextIndex = index;
          return new Token( TokenType.Entity, expression.Substring( pos, index - pos ), pos );
        }
        else if ( IsNumber( c, false ) )
        {
          bool hex = c == '0' && index < length - 1 && (expression[index + 1] == 'x' || expression[index + 1] == 'X');
          if ( hex )
            ++index;
          bool dot = c == '.';
          int pos = index;
          ++index;
          while ( index < expression.Length && IsNumber( expression[index], hex ) )
          {
            if ( (dot || hex) && expression[index] == '.' )
              throw new FormatException( string.Format( "Unexpected '.' in expression \"{0}\" at position {1}", expression, index ) );
            dot = expression[index] == '.';
            ++index;
          }

          nextIndex = index;
          if ( !hex && index < expression.Length && (expression[index] == 'f' || expression[index] == 'F') )
            ++nextIndex;

          return new Token( TokenType.Number, expression.Substring( pos, index - pos ), pos );
        }
        else if ( c == '"' )
        {
          int pos = index;
          ++index;
          bool special = false;
          while ( index < length && (!special && expression[index] != '"') )
          {
            if ( !special && expression[index] == '\\' )
              special = true;
            ++index;
          }

          if ( index == length )
            throw new FormatException( string.Format( "Unexpected end of line in expression \"{0}\"", expression ) );

          ++index;
          nextIndex = index;
          return new Token( TokenType.String, expression.Substring( pos, index - pos ), pos );
        }
        else
          throw new FormatException( string.Format( "Invalid character '{0}' in expression \"{1}\" at position {2}", c, expression, index ) );
      }
    }

    #endregion

    #region private class Constant : IOperation

    private class Constant : IOperation
    {
      private readonly Value _value;
      
      public Constant( object value )
      {
        if ( value.GetType() == typeof( double ) )
          _value = new Value( (double)value );
        else if ( value.GetType() == typeof( bool ) )
          _value = new Value( (bool)value );
        else if ( value.GetType() == typeof( string ) )
          _value = new Value( (string)value );
      }

      public override string ToString() { return _value.String; }

      public void Calculate( ref Stack<Value> values, object[] context ) { values.Push( _value ); }
      public int Priority { get { return 0; } }
    }

    #endregion

    #region private abstract class Operation, BracketOperation, UnaryOperation, BinaryOperation, TernaryOperation

    private abstract class Operation : TypedFunctionHelpers, IOperation
    {
      private readonly int _priority;

      protected Operation( int priority ) { _priority = priority; }

      public abstract void Calculate( ref Stack<Value> values, object[] context );
      public int Priority { get { return _priority; } }
    }

    private class BracketOperation : IOperation
    {
      public void Calculate( ref Stack<Value> values, object[] context ) { }
      public int Priority { get { return -1; } }
    }

    private class UnaryOperation<TOutput, T1> : Operation
    {
      Function1Handler<TOutput, T1> _handler;
      public UnaryOperation( int priority, Function1Handler<TOutput, T1> handler ) : base( priority ) { _handler = handler; }

      public override void Calculate( ref Stack<Value> values, object[] context )
      {
        var p1 = Pop<T1>( ref values, 1, string.Empty );
        Push( ref values, _handler( p1 ), string.Empty );
      }
    }

    private class BinaryOperation<TOutput, T1, T2> : Operation
    {
      Function2Handler<TOutput, T1, T2> _handler;
      public BinaryOperation( int priority, Function2Handler<TOutput, T1, T2> handler ) : base( priority ) { _handler = handler; }

      public override void Calculate( ref Stack<Value> values, object[] context )
      {
        var p2 = Pop<T2>( ref values, 2, string.Empty );
        var p1 = Pop<T1>( ref values, 1, string.Empty );
        Push( ref values, _handler( p1, p2 ), string.Empty );
      }
    }

    private class TernaryOperation<TOutput, T1, T2, T3> : Operation
    {
      Function3Handler<TOutput, T1, T2, T3> _handler;
      public TernaryOperation( int priority, Function3Handler<TOutput, T1, T2, T3> handler ) : base( priority ) { _handler = handler; }

      public override void Calculate( ref Stack<Value> values, object[] context )
      {
        var p3 = Pop<T3>( ref values, 3, string.Empty );
        var p2 = Pop<T2>( ref values, 2, string.Empty );
        var p1 = Pop<T1>( ref values, 1, string.Empty );
        Push( ref values, _handler( p1, p2, p3 ), string.Empty );
      }
    }

    #endregion

    #region static default math operations

    private static BracketOperation bracket = new BracketOperation();
    private static Dictionary<string, IOperation>[] operations = new Dictionary<string, IOperation>[3] 
    { 
      new Dictionary<string, IOperation>(), 
      new Dictionary<string, IOperation>(), 
      new Dictionary<string, IOperation>() 
    };

    private static void RegisterOperation<TOutput, T1>( string name, int priority, Function1Handler<TOutput, T1> handler )
    {
      operations[0].Add( name, new UnaryOperation<TOutput, T1>( priority, handler ) );
    }

    private static void RegisterOperation<TOutput, T1, T2>( string name, int priority, Function2Handler<TOutput, T1, T2> handler )
    {
      operations[1].Add( name, new BinaryOperation<TOutput, T1, T2>( priority, handler ) );
    }

    private static void RegisterOperation<TOutput, T1, T2, T3>( string name, int priority, Function3Handler<TOutput, T1, T2, T3> handler )
    {
      operations[2].Add( name, new TernaryOperation<TOutput, T1, T2, T3>( priority, handler ) );
    }

    private static IOperation GetOperation( string name, int argsCount )
    {
      if ( argsCount < 1 || argsCount > operations.Length )
        throw new ArgumentException( string.Format( "{0} is not valid amount of arguments for internal operation", argsCount ), "argsCount" );

      IOperation result;
      if ( !operations[argsCount-1].TryGetValue( name, out result ) )
        throw new ArgumentException( string.Format( "Internal operation \"{0}\" for {1} arguments not defined", name, argsCount ), "name" );

      return result;
    }

    static StringProcessor()
    {
      RegisterOperation( "-",  17, ( double x ) => -x );
      RegisterOperation( "!",  17, ( bool x ) => !x );
      RegisterOperation( "*",  16, ( double x, double y ) => x * y );
      RegisterOperation( "/",  16, ( double x, double y ) => x / y );
      RegisterOperation( "%",  16, ( double x, double y ) => x % y );
      RegisterOperation( "+",  15, ( double x, double y ) => x + y );
      RegisterOperation( "-",  15, ( double x, double y ) => x - y );
      RegisterOperation( "<",  14, ( double x, double y ) => x < y );
      RegisterOperation( ">",  14, ( double x, double y ) => x > y );
      RegisterOperation( "<=", 14, ( double x, double y ) => x <= y );
      RegisterOperation( ">=", 14, ( double x, double y ) => x >= y );
      RegisterOperation( "==", 13, ( double x, double y ) => x == y );
      RegisterOperation( "!=", 13, ( double x, double y ) => x != y );
      RegisterOperation( "&&", 12, ( bool x, bool y ) => x && y );
      RegisterOperation( "||", 11, ( bool x, bool y ) => x || y );
      RegisterOperation( "?",  10, ( bool z, double x, double y ) => z ? x : y );
    }

    #endregion

    #region private class ExpressionOperation : IOperation

    private class ExpressionOperation : IOperation
    {
      private IExpression _expression;

      public ExpressionOperation( IExpression expression )
      {
        _expression = expression;
      }

      public void Calculate( ref Stack<Value> values, object[] context )
      {
        values.Push( _expression.Calculate( context ) );
      }

      public int Priority { get { return 0; } }
    }

    #endregion

    private List<Token> ParseTokens( string expression )
    {
      var tokens = new List<Token>();
      int index;
      Token token = Token.GetNextToket( expression, 0, out index );
      while ( token != null )
      {
        tokens.Add( token );
        int nextIndex;
        token = Token.GetNextToket( expression, index, out nextIndex );
        index = nextIndex;
      }

      return tokens;
    }

    private int GetArgumentsCount( List<Token> tokens, int startIndex )
    {
      int brackets = 0;
      int result = 0;
      for ( int i = startIndex; i < tokens.Count; ++i )
      {
        var token = tokens[i];

        if ( token.Type == Token.TokenType.Delemiter )
        {
          switch ( token.Value )
          {
          case "(":
            brackets++;
            break;
          case ")":
            brackets--;
            if ( brackets == 0 )
              return result;
            break;
          case ",":
            if ( brackets == 1 )
              result++;
            break;
          }
        }

        if ( brackets == 1 && result == 0 && ( token.Type != Token.TokenType.Delemiter || token.Value == "(" ) )
          result = 1;
      }

      return result;
    }

    private IOperation GetFunction( string name, int argsCount, FunctionsList[] functions )
    {
      var result = TryGetFunction( name, argsCount, functions );
      if ( result == null )
        throw new ArgumentException( string.Format( "Function \"{0}\" with {1} argument(s) not defined", name, argsCount ) );

      return result;
    }

    private IOperation GetVariable( string name, FunctionsList[] functions )
    {
      var alias = TryGetAlias( name, functions );
      if ( !string.IsNullOrEmpty( alias ) )
        return new ExpressionOperation( Parse( alias, functions ) );

      var result = TryGetVariable( name, functions );
      if ( result == null )
        throw new ArgumentException( string.Format( "Variable \"{0}\" not defined", name ) );

      return result;
    }

    private bool IsBinaryOperator( Token prevToken )
    {
      if ( prevToken == null )
        return false;

      return prevToken.Type == Token.TokenType.Number || 
        prevToken.Type == Token.TokenType.String || 
        prevToken.Type == Token.TokenType.Entity || 
        ( prevToken.Type == Token.TokenType.Delemiter && prevToken.Value == ")" );
    }

    public IExpression Parse( string expression, params FunctionsList[] functions )
    {
      if ( expression == null )
        throw new ArgumentNullException( "expression" );

      var tokens = ParseTokens( expression );
      if ( tokens.Count == 0 )
        throw new ArgumentException( "Cannot parse empty expression", "expression" );

      var result = new Expression( expression );
      var stack = new Stack<IOperation>();

      for ( int i = 0; i < tokens.Count; ++i )
      {
        var prevToken = i > 0 ? tokens[i-1] : null;
        var token = tokens[i];
        var nextToken = i < tokens.Count - 1 ? tokens[i+1] : null;
        
        switch ( token.Type )
        {
        case Token.TokenType.Number:
          result.Add( new Constant( Double.Parse( token.Value, CultureInfo.InvariantCulture.NumberFormat ) ) );
          break;

        case Token.TokenType.String:
          result.Add( new Constant( token.Value.Substring( 1, token.Value.Length - 2 ) ) );
          break;

        case Token.TokenType.Entity:
          if ( nextToken != null && nextToken.Type == Token.TokenType.Delemiter && nextToken.Value == "(" )
            stack.Push( GetFunction( token.Value, GetArgumentsCount( tokens, i + 1 ), functions ) );
          else
            result.Add( GetVariable( token.Value, functions ) );

          //{
          //  string alias = TryGetAlias( token.Value );
          //  if ( !string.IsNullOrEmpty( alias ) )
          //    result.Add( new ExpressionOperation( Parse( alias ) ) );
          //  else
          //    result.Add( GetVariable( token.Value ) );
          //}
          break;

        case Token.TokenType.Delemiter:
          if ( token.Value == "(" )
            stack.Push( bracket );
          else if ( token.Value == ")" )
          {
            while ( stack.Count > 0 && stack.Peek().Priority != -1 )
              result.Add( stack.Pop() );
            if ( stack.Count == 0 )
              throw new ArgumentException( "Cannot find open brace", "expression" );

            stack.Pop();

            if ( stack.Count > 0 && stack.Peek().Priority == 0 )
              result.Add( stack.Pop() );
          }
          else if ( token.Value == "," )
          {
            while ( stack.Count > 0 && stack.Peek().Priority != -1 )
              result.Add( stack.Pop() );
            if ( stack.Count == 0 )
              throw new ArgumentException( "Cannot find operation for comma sign", "expression" );
          }
          else if ( token.Value == ":" )
          {
            while ( stack.Count > 0 && stack.Peek().Priority != 10 )
              result.Add( stack.Pop() );
            if ( stack.Count == 0 )
              throw new ArgumentException( "Cannot find trenary operator", "expression" );
          }
          break;

        case Token.TokenType.Operator:
          {
            IOperation operation = null;
            if ( token.Value == "?" )
              operation = GetOperation( token.Value, 3 );
            else if ( IsBinaryOperator( prevToken ) )
              operation = GetOperation( token.Value, 2 );
            else
              operation = GetOperation( token.Value, 1 );

            while ( stack.Count > 0 && ( stack.Peek().Priority >= operation.Priority ) )
              result.Add( stack.Pop() );
            stack.Push( operation );
          }
          break;
        }
      }

      while ( stack.Count > 0 )
      {
        var operation = stack.Pop();
        if ( operation.Priority == -1 )
          throw new ArgumentException( "Cannot find open brace", "expression" );
        result.Add( operation );
      }

      return result;
    }
  }
}
