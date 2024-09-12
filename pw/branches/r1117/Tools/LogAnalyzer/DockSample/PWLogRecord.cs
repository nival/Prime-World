using System;
using CodeEngine.Framework.QueryBuilder.Enums;
using System.Linq.Expressions;
using System.Reflection;
using System.Collections.Generic;

namespace DockSample
{
  public static class Extension
  {
    public static string ReplaceFirst( this string text, string search, string replace )
    {
      int pos = text.IndexOf( search, StringComparison.InvariantCultureIgnoreCase );
      if ( pos < 0 )
      {
        return text;
      }
      return text.Substring( 0, pos ) + replace + text.Substring( pos + search.Length );
    }

    public static string IntTo2Signs( this int i )
    {
      return i.ToString().Length == 1 ? "0" + i.ToString() : i.ToString();
    }

    public static Expression ComparisonToExpression( this Comparison input, Expression left, Expression right )
    {
      if ( input == Comparison.Equals) 
        return Expression.Equal(left, right);
      if ( input == Comparison.NotEquals )
        return Expression.NotEqual( left, right );
      if ( input == Comparison.Contains )
      {
        MethodInfo containsMethod = typeof( string ).GetMethod( "Contains" );
        return Expression.Call( left, containsMethod, right );
      }
      if ( input == Comparison.NotContains )
      {
        MethodInfo containsMethod = typeof( string ).GetMethod( "Contains" );
        return Expression.Not( Expression.Call( left, containsMethod, right ));
      }
      return Expression.Equal( left, right );
    }
    public static Expression AddConjuncts( this Expression result, List<Expression> input )
    {
      foreach ( Expression current in input )
      {
        if ( current != null )
        {
          if ( result == null )
            result = current;
          else
            result = Expression.AndAlso( result, current );
        }
      }
      return result;
    }
  }
  public class PWLogRecord
  {
    public string Thread { get; set; }
    public string Time { get; set; }
    public string Channel { get; set; }
    public string Level { get; set; }
    public string Message { get; set; }

    public PWLogRecord( string thread, string time, string channel, string level, string message )
    {
      Thread = thread;
      Time = time;
      Channel = channel;
      Level = level;
      Message = message;
    }
    public PWLogRecord() { }

    public void Clear()
    {
      Thread = null;
      Time = null;
      Channel = null;
      Level = null;
      Message = null;
    }
  }
}