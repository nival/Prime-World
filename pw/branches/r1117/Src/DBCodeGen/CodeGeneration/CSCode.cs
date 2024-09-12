using System;
using System.Collections.Generic;
using System.ComponentModel;
using DBCodeGen.Utils;
using DBCodeGen.VisualStudioSupport;
using libdb.DB;
using libdb.Animated;

namespace DBCodeGen.CodeGeneration
{
  internal sealed class CSCode
  {
    public static void WriteHeader( CodeWriter csCode, string nsName, bool includeLibDB )
    {
      WriteHeader( csCode, nsName, includeLibDB, string.Empty );
    }

    public static void WriteHeader( CodeWriter csCode, string nsName,
      bool includeLibDB, params string[] additionalNamespaces )
    {
      csCode.WriteLine( "// Automatically generated file, don't change it manually!" );
      csCode.WriteLine( "using System;" );
      csCode.WriteLine( "using System.Collections.Generic;" );
      csCode.WriteLine( "using System.ComponentModel;" );

      foreach ( string ns in additionalNamespaces )
        if ( !string.IsNullOrEmpty( ns ) )
          csCode.WriteLine( "using {0};", ns );

      csCode.WriteLine();
      if ( includeLibDB )
      {
        csCode.WriteLine( "using libdb;" );
        csCode.WriteLine( "using libdb.DB;" );
        csCode.WriteLine( "using libdb.IO;" );
        csCode.WriteLine( "using libdb.UndoRedo;" );
        csCode.WriteLine( "using libdb.Diagnostics;" );
        csCode.WriteLine( "using libdb.Animated;" );
      }
      csCode.WriteLine();

      csCode.WriteLine( string.Format( "namespace {0}", nsName ) );
      csCode.WriteLine( "{" );
    }

    public static void WriteHeader( CodeWriter csCode )
    {
      WriteHeader( csCode, "DBTypes", true );
    }

    public static void WriteCloseNamespace( CodeWriter csCode, string nsName )
    {
      csCode.WriteLine( "};" + string.Format( " // namespace {0}", nsName ) );
    }

    public static void WriteCloseNamespace( CodeWriter csCode )
    {
      WriteCloseNamespace( csCode, "DBTypes" );
    }

    public static void WriteAttributes( CodeWriter csCode, int indent, Attribute[] attributes )
    {
      List<string> resultAttributes = new List<string>();

      foreach ( Attribute attr in attributes )
      {

        if ( attr is FieldCategoryAttribute )
          resultAttributes.Add( string.Format( "[Category( \"{0}\" )]", ( attr as FieldCategoryAttribute ).category ) );
        else if ( attr is ReadOnlyAttribute )
          resultAttributes.Add( string.Format( "[ReadOnly( {0} )]", ( attr as ReadOnlyAttribute ).IsReadOnly.ToString().ToLower() ) );
        else if ( attr is BrowsableAttribute )
          resultAttributes.Add( string.Format( "[Browsable( {0} )]", ( attr as BrowsableAttribute ).Browsable.ToString().ToLower() ) );
        else if ( attr is DescriptionAttribute )
          resultAttributes.Add( string.Format( "[Description( \"{0}\" )]", ( attr as DescriptionAttribute ).Description ) );
        else
        {
          string attrTypeName = attr.GetType().Name;
          if ( attrTypeName.EndsWith( "Attribute", StringComparison.InvariantCultureIgnoreCase ) )
            attrTypeName = attrTypeName.Substring( 0, attrTypeName.Length - 9 );

          string constructorParams = string.Empty;

          if ( attr is DBAttribute )
          {
            constructorParams = ( attr as DBAttribute ).ConstructorParameters ?? string.Empty;
            if ( !string.IsNullOrEmpty( constructorParams ) )
              constructorParams = "(" + constructorParams + ")";
          }

          resultAttributes.Add( string.Format( "[{0}{1}]", attrTypeName, constructorParams ) );
        }
      }

      resultAttributes.Sort( string.Compare );
      foreach ( string resultAttribute in resultAttributes )
        csCode.WriteLine( indent, resultAttribute );
    }

    private static string GetGenericTypeName( Type type )
    {
      if ( !type.IsGenericType )
        return type.Name;

      string typeName = type.GetGenericTypeDefinition().Name;
      int divPos = typeName.IndexOf( '`' );
      if ( divPos < 0 )
        return typeName;

      return typeName.Substring( 0, divPos );
    }

    public static string GetParents( CodeWriter csCode, int indent, Type type )
    {
      if ( TypeUtils.IsSubclassOf( type, typeof( AnimatedDiscrete<> ) ) )
      {
        return FormatHelper.FormatString( 0, "{0}<{1}>, ", GetGenericTypeName( typeof( AnimatedDiscrete<> ) ),
          DBCodeGen.GetCSSimpleTypeName( TypeUtils.GetTypeFromGeneric( type, 0 ) ) );
      }
      else if ( TypeUtils.IsSubclassOf( type, typeof( AnimatedLinear<,> ) ) )
      {
        return FormatHelper.FormatString( 0, "{0}<{1}, {2}>, ", GetGenericTypeName( typeof( AnimatedLinear<,> ) ),
          DBCodeGen.GetCSSimpleTypeName( TypeUtils.GetTypeFromGeneric( type, 0 ) ),
          DBCodeGen.GetCSSimpleTypeName( TypeUtils.GetTypeFromGeneric( type, 1 ) ) );
      }
      else if ( TypeUtils.IsSubclassOf( type, typeof( AnimatedComplex<,,,> ) ) )
      {
        return FormatHelper.FormatString( 0, "{0}<{1}, {2}, {3}, {4}.Converter>, ", GetGenericTypeName( typeof( AnimatedComplex<,,,> ) ),
          DBCodeGen.GetCSSimpleTypeName( TypeUtils.GetTypeFromGeneric( type, 0 ) ),
          DBCodeGen.GetCSSimpleTypeName( TypeUtils.GetTypeFromGeneric( type, 1 ) ),
          DBCodeGen.GetCSSimpleTypeName( TypeUtils.GetTypeFromGeneric( type, 2 ) ),
          type.Name );
      }
      else if ( DBCodeGen.IsStruct( type ) && type.BaseType != typeof( Object ) )
      {
        return FormatHelper.FormatString( 0, "{0}, ", DBCodeGen.GetTypeName( type.BaseType ) );
      }

      return string.Empty;
    }

    public static void WriteAnimatedComplexConverter( CodeWriter csCode, int indent, Type type, AnimatedComplexConverterAttribute attr )
    {
      csCode.WriteLine( indent + 1, "public struct Converter : IComplexConverter<{0}, {1}>",
        DBCodeGen.GetCSSimpleTypeName( TypeUtils.GetTypeFromGeneric( type, 0 ) ),
        DBCodeGen.GetCSSimpleTypeName( TypeUtils.GetTypeFromGeneric( type, 1 ) ) );
      csCode.WriteLine( indent + 1, "{" );

      csCode.WriteLine( indent + 2, "public {0} ConvertTo( {1}[] tracks )",
        DBCodeGen.GetCSSimpleTypeName( TypeUtils.GetTypeFromGeneric( type, 0 ) ),
        DBCodeGen.GetCSSimpleTypeName( TypeUtils.GetTypeFromGeneric( type, 1 ) ) );
      csCode.WriteLine( indent + 2, "{" );

      string[] getters = new string[attr.Args.Length];
      for ( int i = 0; i < attr.Args.Length; ++i )
        getters[i] = string.Format( "tracks.GetValue( time, {0} )", i );

      csCode.WriteLine( indent + 3, "{0} result = new {0}();", DBCodeGen.GetCSSimpleTypeName( TypeUtils.GetTypeFromGeneric( type, 0 ) ) );
      for ( int i = 0; i < attr.Args.Length; ++i )
        csCode.WriteLine( indent + 3, "result.{1} = tracks[{0}];", i, attr.Args[i] );
      //csCode.WriteLine( indent + 3, "result.{1} = tracks.GetTrackValue( time, {0} );", i, attr.Args[i] ) );

      csCode.WriteLine( indent + 3, "return result;" );
      csCode.WriteLine( indent + 2, "}" );

      csCode.WriteLine( indent + 2, "public void ConvertFrom<TAlgorithm>( int index, {0} value, AnimatedTracks<{1}, TAlgorithm> tracks ) where TAlgorithm : IAnimatedAlgorithm<{1}>",
        DBCodeGen.GetCSSimpleTypeName( TypeUtils.GetTypeFromGeneric( type, 0 ) ),
        DBCodeGen.GetCSSimpleTypeName( TypeUtils.GetTypeFromGeneric( type, 1 ) ) );
      csCode.WriteLine( indent + 2, "{" );
      for ( int i = 0; i < attr.Args.Length; ++i )
        csCode.WriteLine( indent + 3, "tracks[{0}].SetValue( index, value.{1} );", i, attr.Args[i] );
      csCode.WriteLine( indent + 2, "}" );

      csCode.WriteLine( indent + 2, "public int TrackCount {{ get {{ return {0}; }} }}", attr.Args.Length );

      csCode.WriteLine( indent + 1, "}" );
      csCode.WriteLine();
    }
  }
}
