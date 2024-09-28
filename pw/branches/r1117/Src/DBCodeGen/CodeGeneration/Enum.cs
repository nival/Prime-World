using System;
using System.Reflection;
using DBCodeGen.Utils;
using libdb.DB;

namespace DBCodeGen.CodeGeneration
{
  internal static class Enum
  {
    public static void DeclareBuffer( CodeWriter code )
    {
      code.WriteLine( "namespace" );
      code.WriteLine( "{" );
      code.WriteLine( "\tchar enumToStrBuffer[12];" );
      code.WriteLine( "}" );
      code.WriteLine();
    }
    public static void Write( Type type, string customName, CodeWriter header, CodeWriter code, CodeWriter csCode, int indent )
    {
      Write( type, customName, header, code, csCode, indent, true );
    }

    public static void Write( Type type, CodeWriter csCode, int indent )
    {
      Write( type, string.Empty, null, null, csCode, indent, false );
    }

    public static void Write( Type type, string customName, CodeWriter header, CodeWriter code, CodeWriter csCode, int indent, bool writeAttributes )
    {
      string enumName = DBCodeGen.GetTypeName( type );
      string enumPrefix = enumName.ToUpper();
      if ( enumPrefix[0] == 'E' )
        enumPrefix = enumPrefix.Substring( 1 );

      FieldInfo[] fields = type.GetFields( BindingFlags.Public | BindingFlags.Static );

      //c# generation
      if ( csCode != null )
      {
        if ( !TypeUtils.HasAttribute<NoCSCodeAttribute>( type, false ) ||
            DBCodeGen.CheckCustomAttribute( type, customName, false ) )
        {
          // write enum to c# code
          if ( writeAttributes )
            CSCode.WriteAttributes( csCode, indent, TypeUtils.GetAttributes<Attribute>( type, false ) );
          csCode.WriteLine( indent, "public enum {0}", type.Name );
          csCode.WriteLine( indent, "{" );
          foreach ( FieldInfo fieldInfo in fields )
          {
            csCode.WriteLine( indent, "\t{0} = {1},", fieldInfo.Name, fieldInfo.GetRawConstantValue().ToString() );
          }
          csCode.WriteLine( indent, FormatHelper.FormatString( indent, "};" ) );
          csCode.WriteLine();
        }
      }

      //c++ generation
      if ( header != null && code != null )
      {
        if ( TypeUtils.HasAttribute<NoCodeAttribute>( type, false ) &&
          !DBCodeGen.CheckCustomAttribute( type, customName, false ) )
          return;

        // write enum declaration to header
        header.WriteLine( indent, "enum {0}", enumName );
        header.WriteLine( indent, "{" );
        foreach ( FieldInfo fieldInfo in fields )
        {
          header.WriteLine( indent, "\t{0}_{1} = {2},", enumPrefix, fieldInfo.Name.ToUpper(), fieldInfo.GetRawConstantValue().ToString() );
        }
        header.WriteLine( indent, FormatHelper.FormatString( indent, "};" ) );

        header.WriteLine();
        header.WriteLine( indent, "const char *EnumToString( const {0} value );", enumName );
        header.WriteLine( indent, "const {0} StringToEnum_{0}( const char* value );", enumName );

        header.WriteLine();
        header.WriteLine( indent, "template <>" );
        header.WriteLine( indent, "struct KnownEnum< {0} >", enumName );
        header.WriteLine( indent, "{" );
        header.WriteLine( indent, "\tenum { isKnown = 1 };" );
        header.WriteLine( indent, "\tenum {{ sizeOf = {0} }};", fields.Length );
        header.WriteLine( indent, "\tstatic const char *ToString( const {0} value ) {{ return EnumToString( value ); }}", enumName );
        header.WriteLine( indent, "\tstatic const {0} ToEnum( const char* value ) {{ return StringToEnum_{0}( value ); }}", enumName );
        header.WriteLine( indent, "\tstatic const {0} ToEnum( const string& value ) {{ return StringToEnum_{0}( value.c_str() ); }}", enumName );
        header.WriteLine( indent, "\tstatic const int SizeOf() {{ return {0}; }}", fields.Length );
        header.WriteLine( indent, "};" );
        header.WriteLine();

        // write enum definition to code
        code.WriteLine( FormatHelper.CommentLine );
        code.WriteLine( "const char *EnumToString( const {0} value )", enumName );
        code.WriteLine( "{" );
        code.WriteLine( "\tswitch( value )" );
        code.WriteLine( "\t{" );
        foreach ( FieldInfo fieldInfo in fields )
        {
          code.WriteLine( "\t\tcase {0}_{1}:", enumPrefix, fieldInfo.Name.ToUpper() );
          code.WriteLine( "\t\t\treturn \"{0}\";", fieldInfo.Name );
        }
        code.WriteLine( "\t};" );
        code.WriteLine();
        if ( !TypeUtils.HasAttribute<FlagsAttribute>( type, true ) )
          code.WriteLine( "\tNI_DATA_ALWAYS_ASSERT( NStr::StrFmt( \"Invalid value %d for enum {0}\", value ) );", enumName );
        code.WriteLine( "\tNStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); " );
        code.WriteLine( "\treturn enumToStrBuffer;" );
        code.WriteLine( "}" );

        code.WriteLine( FormatHelper.CommentLine );
        code.WriteLine( "const {0} StringToEnum_{0}( const char* value )", enumName );
        code.WriteLine( "{" );
        code.WriteLine( "\tif ( NStr::IsDecNumber( value ) )" );
        code.WriteLine( "\t\treturn ({0})(NStr::ToInt( value ));", enumName );
        foreach ( FieldInfo fieldInfo in fields )
        {
          code.WriteLine( "\tif ( strcmp( value, \"{0}\" ) == 0 || strcmp( value, \"{1}_{2}\" ) == 0 )", fieldInfo.Name, enumPrefix, fieldInfo.Name.ToUpper() );
          code.WriteLine( "\t\treturn {0}_{1};", enumPrefix, fieldInfo.Name.ToUpper() );
        }
        code.WriteLine();
        code.WriteLine( "\tNI_DATA_ALWAYS_ASSERT( NStr::StrFmt( \"Invalid value %s for enum {0}\", value ) );", enumName );
        code.WriteLine( "\treturn {0}_{1};", enumPrefix, fields[0].Name.ToUpper() );
        code.WriteLine( "}" );
      }
    }
  }
}
