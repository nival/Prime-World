using System;
using System.Collections.Generic;
using System.Reflection;
using DBCodeGen.Utils;
using libdb.Animated;
using libdb.DB;
using Microsoft.Build.BuildEngine;

namespace DBCodeGen.CodeGeneration
{
  internal sealed partial class Struct
  {
    private static void WriteCppFile( Type type, bool resource, string customName, CodeWriter header, CodeWriter code, int indent, string structName, bool needChecksum, bool serializerOnly, List<FieldInfo> cppFields, object constructedObject )
    {
      Dictionary<string, FactoryImplAttribute> factoryImpls = new Dictionary<string, FactoryImplAttribute>();
      foreach ( var impl in TypeUtils.GetAttributes<FactoryImplAttribute>( type, false ) )
        factoryImpls.Add( impl.FactoryFunctionName, impl );

      List<FactoryBaseAttribute> factoryBases = new List<FactoryBaseAttribute>( TypeUtils.GetAttributes<FactoryBaseAttribute>( type, true ) );
      factoryBases.Sort( ( FactoryBaseAttribute a, FactoryBaseAttribute b ) => { int defineCompare = string.Compare( a.Define, b.Define ); return defineCompare != 0 ? defineCompare : string.Compare( a.FactoryFunctionName, b.FactoryFunctionName ); } );

      if ( !serializerOnly )
      {
        // write struct declaration to header
        if ( type.BaseType != typeof( Object ) && type.BaseType != typeof( DBResource ) )
          header.WriteLine( indent, "struct {0} : public {1}", structName, DBCodeGen.GetTypeName( type.BaseType ) );
        else
          if ( resource )
            header.WriteLine( indent, "struct {0} : public DbResource", structName );
          else
            header.WriteLine( indent, "struct {0}", structName );
        header.WriteLine( indent, "{" );

        if ( resource && TypeUtils.CanCreate( type ) )
          header.WriteLine( indent, "\tDBRESOURCE_METHODS( {0} );", structName );

        if ( TypeUtils.HasAttribute<HasStatesAttribute>( type, true ) && !TypeUtils.HasAttribute<HasStatesAttribute>( type.BaseType, true ) )
        {
          header.WriteLine( indent, "protected:" );
          header.WriteLine( indent + 1, "mutable DBResourceStateManager stateManager;", type.Name );
          header.WriteLine( indent + 1, "virtual DBResourceStateManager* GetStatesManager() const { return &stateManager; }" );
        }

        if ( needChecksum || TypeUtils.HasAttribute<DbRootAttribute>( type, false ) )
        {
          header.WriteLine( indent, "private:" );
          if ( needChecksum )
            header.WriteLine( indent + 1, "mutable DWORD __checkSum;" );
          if ( TypeUtils.HasAttribute<DbRootAttribute>( type, false ) )
          {
            header.WriteLine( indent + 1, "static Ptr< {0} > instance;", structName );
            header.WriteLine( indent + 1, "static bool instanceInitialized;" );
          }
        }

        header.WriteLine( indent, "public:" );

        if ( TypeUtils.HasAttribute<TypeIdAttribute>( type, false ) )
        {
          TypeIdAttribute typeIdAttribute = TypeUtils.GetAttribute<TypeIdAttribute>( type, false );
          if ( typeIdAttribute.HasID )
          {
            header.WriteLine( indent + 1, "enum {{ typeId = 0x{0:X8} }};", typeIdAttribute.ID );
            header.WriteLine( indent + 1, "virtual const DWORD GetObjectTypeID() const {{ return (DWORD){0}::typeId; }}", structName );
          }
          else
            header.WriteLine( indent + 1, "virtual const DWORD GetObjectTypeID() const = 0;" );
        }

        foreach ( FieldInfo field in cppFields )
        {
          header.WriteLine( indent + 1, "{0} {1};", DBCodeGen.GetTypeName( field.FieldType ), field.Name );
        }

        WriteCppStaticFields( type, header, indent, constructedObject );

        header.WriteLine();
        header.WriteLine( indent + 1, "{0}();", structName );

        foreach ( IncludeAttribute attr in TypeUtils.GetAttributes<IncludeAttribute>( type, false ) )
        {
          header.WriteLine( indent + 1, "#include \"{0}\"", attr.fileName );
        }
        header.WriteLine();

        WriteCppSerializeHeader( type, header, indent );

        if ( needChecksum )
          header.WriteLine( indent + 1, "DbResource::checksum_type CalcCheckSum() const;" );
        else
          header.WriteLine( indent + 1, "DbResource::checksum_type CalcCheckSum() const { return 0; }");

        WriteCppEqualAndAssignHeader( type, resource, header, indent, structName );

        if ( factoryBases.Count > 0 )
          WriteCppFactoryHeader( header, factoryBases );

        if ( TypeUtils.HasAttribute<DbRootAttribute>( type, false ) )
        {
          header.WriteLine( indent + 1, "static void InitRoot( const DBID& dbid );", structName );
          header.WriteLine( indent + 1, "static void InitRoot( const {0}* instance );", structName );
          header.WriteLine( indent + 1, "static const Ptr< {0} >& GetRoot();", structName );
        }

        header.WriteLine( indent, "};" );
        header.WriteLine();


        // write struct definition to code
        WriteCppConstructorSource( code, structName, needChecksum, cppFields, constructedObject );

        if ( needChecksum )
          WriteCppChecksumSource( code, indent, structName, cppFields );

        if ( TypeUtils.HasAttribute<DbRootAttribute>( type, false ) )
          WriteRootMethos( code, structName );
      }

      WriteCppSerializeSource( type, code, indent, structName, cppFields );

      WriteCppEqualAndAssignSource( type, customName, code, structName );

      if ( factoryBases.Count > 0 )
        WriteCppFactorySource( type, code, factoryImpls, factoryBases );
    }

    private static void WriteRootMethos( CodeWriter code, string structName )
    {
      code.WriteLine( FormatHelper.CommentLine );
      code.WriteLine( "Ptr< {0} > {0}::instance;", structName );
      code.WriteLine( "void {0}::InitRoot( const DBID& dbid ) {{ InitRoot( Get<{0}>( dbid ) ); }}", structName );
      code.WriteLine( "void {0}::InitRoot( const {0}* _instance ) {{ instance = _instance; }}", structName );
      code.WriteLine( FormatHelper.CommentLine );
      code.WriteLine( "const Ptr< {0} >& {0}::GetRoot()", structName );
      code.WriteLine( "{" );
      code.WriteLine( 1, "NI_ASSERT( IsValid( instance ), \"Root for type \\\"{0}\\\" not initialized\" );", structName );
      code.WriteLine( 1, "return instance;" );
      code.WriteLine( "}" );
    }

    private static void WriteCppStaticFields( Type type, CodeWriter header, int indent, object constructedObject )
    {
      string customName = string.Empty;
      foreach ( FieldInfo field in DBCodeGen.GetStaticFields( type, true, customName, typeof( NoCodeAttribute ) ) )
      {
        int value = 0;
        if ( TypeUtils.IsSubclassOf( field.FieldType, typeof( int ) ) )
          value = (int)field.GetValue( constructedObject );
        else if ( field.FieldType.IsEnum )
          value = (int)field.GetValue( constructedObject );
        else
          continue;

        header.WriteLine( indent, "\tenum {{ {0} = {1}, }};", field.Name, value );
      }
    }

    private static void WriteCppConstructorSource( CodeWriter code, string structName, bool needChecksum, List<FieldInfo> cppFields, object constructedObject )
    {
      bool firstInitializer = true;
      code.WriteLine( FormatHelper.CommentLine );
      code.Writer.Write( "{0}::{0}()", structName );
      if ( needChecksum )
      {
        code.WriteLine( " :" );
        code.Writer.Write( "\t	__checkSum( 0 )", structName );
        firstInitializer = false;
      }
      foreach ( FieldInfo field in cppFields )
      {
        Type fieldType = field.FieldType;
        if (
          !DBCodeGen.IsStruct( fieldType ) &&
            !TypeUtils.IsList( fieldType ) &&
            TypeUtils.GetTypeFromPtr( fieldType ) == null &&
            !TypeUtils.IsSubclassOf( fieldType, typeof( IAnimated ) ) &&
            fieldType != typeof( TextRef ) )
        {
          string defaultValue = string.Empty;
          object value = field.GetValue( constructedObject );// : fieldType.GetConstructor( System.Type.EmptyTypes ).Invoke( new object[0] );
          if ( fieldType == typeof( string ) )
          {
            string valueStr = value as string;
            if ( string.IsNullOrEmpty( valueStr ) )
              defaultValue = "";
            else
              defaultValue = '\"' + Utilities.Escape( valueStr ) + '\"';
          }
          else if ( fieldType == typeof( bool ) )
            defaultValue = value.ToString().ToLower();
          else if ( fieldType == typeof( Single ) )
            defaultValue = FormatObjectAsSigle( value );
          else if ( fieldType.IsEnum )
            defaultValue = DBCodeGen.GetCPPEnumValue( fieldType, value );
          else
            defaultValue = value.ToString();

          if ( !string.IsNullOrEmpty( defaultValue ) )
          {
            if ( firstInitializer )
            {
              code.WriteLine( " :" );
              code.Writer.Write( "\t	" );
              firstInitializer = false;
            }
            else
            {
              code.WriteLine();
              code.Writer.Write( "\t, " );
            }

            code.Writer.Write( "{0}( {1} )", field.Name, defaultValue );
          }
        }
      }
      code.WriteLine();
      code.WriteLine( "{" );
      foreach ( FieldInfo field in cppFields )
      {
        Type listType = TypeUtils.GetTypeFromList( field.FieldType );
        if ( listType == null )
          continue;

        int minCount = 0;
        if ( TypeUtils.HasAttribute<EnumArrayAttribute>( field, true ) )
          minCount = TypeUtils.GetAttribute<EnumArrayAttribute>( field, true ).MaxCount;
        else if ( TypeUtils.HasAttribute<MinMaxSizeAttribute>( field, true ) )
          minCount = TypeUtils.GetAttribute<MinMaxSizeAttribute>( field, true ).min;

        if ( minCount == 0 )
          continue;

        if ( listType == typeof( bool ) || listType == typeof( int ) || listType == typeof( float ) )
          code.WriteLine( "\t{0}.resize( {1}, {2}() );", field.Name, minCount, DBCodeGen.GetTypeName( listType ) );
        else
          code.WriteLine( "\t{0}.resize( {1} );", field.Name, minCount );
      }
      code.WriteLine( "}" );
    }

    private static void WriteCppChecksumSource( CodeWriter code, int indent, string structName, List<FieldInfo> cppFields )
    {
      code.WriteLine( FormatHelper.CommentLine );
      code.WriteLine( indent, "DbResource::checksum_type {0}::CalcCheckSum() const", structName );
      code.WriteLine( indent, "{" );
      code.WriteLine( indent + 1, "if ( __checkSum == 0 )" );
      code.WriteLine( indent + 1, "{" );
      code.WriteLine( indent + 2, "CCheckSum checkSum;" );

      string checkSum = "checkSum";
      foreach ( FieldInfo field in cppFields )
      {
        checkSum += " << " + field.Name;
      }
      checkSum += ";";
      code.WriteLine( indent + 2, checkSum );
      code.WriteLine( indent + 2, "__checkSum = checkSum.GetCheckSum();" );
      code.WriteLine( indent + 2, "if ( __checkSum == 0 )" );
      code.WriteLine( indent + 3, "__checkSum = 0xFFFFFFFF;" );
      code.WriteLine( indent + 1, "}" );
      code.WriteLine();
      code.WriteLine( indent + 1, "return __checkSum;" );
      code.WriteLine( indent, "}" );
    }

    private static void WriteCppSerializeHeader( Type type, CodeWriter header, int indent )
    {
      header.WriteLine( indent + 1, "int operator&( IBinSaver &saver );" );
      header.WriteLine( indent + 1, "int operator&( IXmlSaver &saver );" );
      if ( TypeUtils.IsResourceType( type ) )
        header.WriteLine( indent + 1, "void SerializeSelf( IXmlSaver &saver );" );
      header.WriteLine();
    }

    private static void WriteCppSerializeSource( Type type, CodeWriter code, int indent, string structName, List<FieldInfo> cppFields )
    {
      code.WriteLine( FormatHelper.CommentLine );
      code.WriteLine( indent, "int {0}::operator&( IBinSaver &saver )", structName );
      code.WriteLine( indent, "{" );
      if ( type.BaseType != typeof( Object ) && type.BaseType != typeof( DBResource ) && type.BaseType != null )
        code.WriteLine( indent + 1, "saver.Add( 1, ({0}*)this );", DBCodeGen.GetTypeName( type.BaseType ) );
      int id = 2;
      foreach ( FieldInfo field in cppFields )
      {
        code.WriteLine( indent + 1, "saver.Add( {0}, &{1} );", id, field.Name );
        ++id;
      }
      code.WriteLine();
      code.WriteLine( indent + 1, "return 0;" );
      code.WriteLine( indent, "}" );


      code.WriteLine( FormatHelper.CommentLine );
      code.WriteLine( indent, "int {0}::operator&( IXmlSaver &saver )", structName );
      code.WriteLine( indent, "{" );

      if ( TypeUtils.IsResourceType( type ) )
      {
        if ( TypeUtils.HasAttribute<HasStatesAttribute>( type, true ) )
          code.WriteLine( indent + 1, "bool inheritedStates = false;" );

        code.WriteLine( indent + 1, "if ( saver.HasParentAttr() )" );
        code.WriteLine( indent + 1, "{" );
        code.WriteLine( indent + 2, "string parent_str = saver.GetParentAttrValue();" );
        code.WriteLine( indent + 2, "__parent = ReadResource( saver, DBID(parent_str) );", type.Name );
        code.WriteLine( indent + 2, "if ( __parent.GetPtr() )" );
        code.WriteLine( indent + 2, "{" );
        code.WriteLine( indent + 3, "{0}* parentPtr = ({0}*)__parent.GetPtr();", type.Name );
        code.WriteLine( indent + 3, "Assign( *parentPtr );" );
        if ( TypeUtils.HasAttribute<HasStatesAttribute>( type, true ) )
        {
          code.WriteLine( indent + 3, "StateSerializeHelper< {0} > parentStateCopier( this, stateManager.states, &{0}::New{0} );", type.Name );
          code.WriteLine( indent + 3, "parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );" );
          code.WriteLine( indent + 3, "inheritedStates = true;" );
        }
        code.WriteLine( indent + 2, "}" );
        code.WriteLine( indent + 1, "}" );

        code.WriteLine();
        code.WriteLine( indent + 1, "SerializeSelf( saver );" );

        if ( TypeUtils.HasAttribute<HasStatesAttribute>( type, true ) )
        {
          code.WriteLine( indent + 1, "if ( !inheritedStates )" );
          code.WriteLine( indent + 1, "{" );
          code.WriteLine( indent + 2, "StateSerializeHelper< {0} > reader( this, stateManager.states, &{0}::New{0} );", type.Name );
          code.WriteLine( indent + 2, "saver.AddPolymorphicBase( \"__states\", &reader );" );
          code.WriteLine( indent + 1, "}" );
        }
      }
      else
      {
        if ( type.BaseType != typeof( Object ) && type.BaseType != typeof( DBResource ) && type.BaseType != null )
          code.WriteLine( indent + 1, "saver.AddTypedSuper( ({0}*)this );", DBCodeGen.GetTypeName( type.BaseType ) );

        GenerateSerializator( code, indent + 1, cppFields );
        code.WriteLine();
      }

      code.WriteLine( indent, "\treturn 0;" );
      code.WriteLine( indent, "}" );

      if ( TypeUtils.IsResourceType( type ) )
      {
        code.WriteLine( indent, FormatHelper.CommentLine );
        code.WriteLine( indent, "void {0}::SerializeSelf( IXmlSaver &saver )", structName );
        code.WriteLine( indent, "{" );

        if ( type.BaseType != typeof( Object ) && type.BaseType != typeof( DBResource ) && type.BaseType != null )
        {
          code.WriteLine( indent + 1, "{0}::SerializeSelf( saver );", DBCodeGen.GetTypeName( type.BaseType ) );
        }
        GenerateSerializator( code, indent + 1, cppFields );
        code.WriteLine( "}" );
      }
    }

    private static void GenerateSerializator( CodeWriter code, int indent, List<FieldInfo> cppFields )
    {
      foreach ( FieldInfo field in cppFields )
      {
        Type listType = TypeUtils.GetTypeFromList( field.FieldType );
        if ( listType != null )
        {
          int minCount = 0;
          if ( TypeUtils.HasAttribute<EnumArrayAttribute>( field, true ) )
            minCount = TypeUtils.GetAttribute<EnumArrayAttribute>( field, true ).MaxCount;
          else if ( TypeUtils.HasAttribute<MinMaxSizeAttribute>( field, true ) )
            minCount = TypeUtils.GetAttribute<MinMaxSizeAttribute>( field, true ).min;
          if ( minCount > 0 )
            code.WriteLine( indent, "{0}.resize( {1} );", field.Name, minCount );
        }

        code.WriteLine( indent, "saver.Add( \"{0}\", &{0} );", field.Name );

        if ( field.FieldType == typeof( List<float> ) && TypeUtils.HasAttribute<TraceArray2Attribute>( field, true ) )
        {
          code.WriteLine(indent, "DebugTrace(\"Trace <{0}> of %s\", GetDBID().GetFormatted().c_str()); ", field.Name);

          code.WriteLine(indent, "nstl::string traceString;");
          code.WriteLine(indent, "char floatString[256];");
          code.WriteLine(indent, "for ( int i = 0; i < {0}.size(); ++i )", field.Name);
          code.WriteLine(indent, "{");
          code.WriteLine(indent, " sprintf_s( floatString, \"%.2f \", {0}[i] );", field.Name);
          code.WriteLine(indent, " traceString +=  floatString;");
          code.WriteLine(indent, "}");
          code.WriteLine(indent, "DebugTrace( traceString.c_str() );");
        }
      }
    }

    private static void WriteCppEqualAndAssignHeader( Type type, bool resource, CodeWriter header, int indent, string structName )
    {
      string paramStructName = "_" + char.ToLower( structName[0] ) + structName.Substring( 1 );
      if ( TypeUtils.HasAttribute<NeedEqualOperatorAttribute>( type, true ) )
      {
        header.WriteLine();
        header.WriteLine( indent + 1, "bool operator==( const {0} &{1} ) const {{ return IsEqual( {1} ); }}", structName, paramStructName );
        header.WriteLine( indent + 1, "bool operator!=( const {0} &{1} ) const {{ return !IsEqual( {1} ); }}", structName, paramStructName );
        header.WriteLine( indent + 1, "bool IsEqual ( const {0} &{1} ) const;", structName, paramStructName );
      }
      if ( TypeUtils.HasAttribute<NeedAssignOperatorAttribute>( type, true ) || TypeUtils.IsResourceType( type ) )
      {
        header.WriteLine();
        header.WriteLine( indent + 1, "{0}& operator = ( const {0} &{1} ) {{ Assign( {1} ); return *this; }}", structName, paramStructName );
        header.WriteLine( indent + 1, "{0}( const {0} &{1} ) {{ Assign( {1} ); }}", structName, paramStructName );

        header.WriteLine( indent + 1, "virtual void Assign( const {0} &{1} );", structName, paramStructName );

        if ( resource )
        {
          header.WriteLine( indent + 1, "virtual void OverridableAssign( const DbResource * _pResource )" );
          header.WriteLine( indent + 1, "{" );
          header.WriteLine( indent + 2, "const {0} * pOther = dynamic_cast< const {0} * > ( _pResource );", structName );
          header.WriteLine( indent + 2, "if ( pOther ) {0}::Assign( *pOther );", structName );
          header.WriteLine( indent + 1, "}" );
        }
      }
    }
    private static void WriteCppEqualAndAssignSource( Type type, string customName, CodeWriter code, string structName )
    {
      string paramStructName = "_" + char.ToLower( structName[0] ) + structName.Substring( 1 );

      if ( TypeUtils.HasAttribute<NeedEqualOperatorAttribute>( type, true ) )
      {
        code.WriteLine( FormatHelper.CommentLine );
        code.WriteLine( "bool {0}::IsEqual( const {0}& {1} ) const", structName, paramStructName );
        code.WriteLine( "{" );
        code.Writer.Write( "\treturn " );
        GenerateEqualOperator( code, type, customName, String.Empty, paramStructName + ".", true );
        code.WriteLine( ";" );
        code.WriteLine( "}" );
      }

      if ( TypeUtils.HasAttribute<NeedAssignOperatorAttribute>( type, true ) || TypeUtils.IsResourceType( type ) )
      {
        code.WriteLine( FormatHelper.CommentLine );
        code.WriteLine( "void {0}::Assign( const {0}& {1} )", structName, paramStructName );
        code.WriteLine( "{" );
        GenerateAssignOperator( code, type, customName, String.Empty, paramStructName + "." );
        code.WriteLine( "}" );
      }
    }

    private static void WriteCppFactoryHeader( CodeWriter header, List<FactoryBaseAttribute> factoryBases )
    {
      header.WriteLine();
      string define = string.Empty;
      foreach ( var factoryBase in factoryBases )
      {
        if ( define != factoryBase.Define )
        {
          if ( !string.IsNullOrEmpty( define ) )
            header.WriteLine( "#endif // #if{0}def {1}", define[0] == '!' ? "n" : "", define.TrimStart( '!' ) );
          define = factoryBase.Define;
          if ( !string.IsNullOrEmpty( define ) )
            header.WriteLine( "#if{0}def {1}", define[0] == '!' ? "n" : "", define.TrimStart( '!' ) );
        }
        Header.WriteFactoryDeclaration( header, factoryBase );
      }
      if ( !string.IsNullOrEmpty( define ) )
        header.WriteLine( "#endif // #if{0}def {1}", define[0] == '!' ? "n" : "", define.TrimStart( '!' ) );
    }
    private static void WriteCppFactorySource( Type type, CodeWriter code, Dictionary<string, FactoryImplAttribute> factoryImpls, List<FactoryBaseAttribute> factoryBases )
    {
      string define = string.Empty;
      foreach ( var factoryBase in factoryBases )
      {
        code.WriteLine( FormatHelper.CommentLine );
        FactoryImplAttribute factoryImpl = null;
        if ( !factoryImpls.TryGetValue( factoryBase.FactoryFunctionName, out factoryImpl ) )
          factoryImpl = null;
        if ( define != factoryBase.Define )
        {
          if ( !string.IsNullOrEmpty( define ) )
            code.WriteLine( "#endif // #if{0}def {1}", define[0] == '!' ? "n" : "", define.TrimStart( '!' ) );
          define = factoryBase.Define;
          if ( !string.IsNullOrEmpty( define ) )
            code.WriteLine( "#if{0}def {1}", define[0] == '!' ? "n" : "", define.TrimStart( '!' ) );
        }
        Code.WriteFactoryImplementation( code, type, factoryBase, factoryImpl );
      }
      if ( !string.IsNullOrEmpty( define ) )
        code.WriteLine( "#endif // #if{0}def {1}", define[0] == '!' ? "n" : "", define.TrimStart( '!' ) );
    }

    private static void GenerateEqualOperator( CodeWriter code, Type type, string customName, string leftPrefix, string rightPrefix, bool firstLine )
    {
      FieldInfo[] fields = DBCodeGen.GetFields( type, true, customName, typeof( NoCodeAttribute ) );
      foreach ( FieldInfo field in fields )
      {
        if ( DBCodeGen.IsStruct( field.FieldType ) )
          GenerateEqualOperator( code, field.FieldType, customName, leftPrefix + field.Name + ".", rightPrefix + field.Name + ".", firstLine );
        else
        {
          if ( !firstLine )
          {
            code.WriteLine();
            code.Writer.Write( "\t\t&& " );
          }
          code.Writer.Write( "{0}{2} == {1}{2}", leftPrefix, rightPrefix, field.Name );
        }
        firstLine = false;
      }
    }

    private static void GenerateAssignOperator( CodeWriter code, Type type, string customName, string leftPrefix, string rightPrefix )
    {
      FieldInfo[] fields = DBCodeGen.GetFields( type, true, customName, typeof( NoCodeAttribute ) );
      foreach ( FieldInfo field in fields )
      {
        if ( DBCodeGen.IsStruct( field.FieldType ) && !TypeUtils.IsSubclassOf( field.FieldType, typeof( IAnimated ) ) && !TypeUtils.HasAttribute<NoCodeAttribute>( field.FieldType, false ) )
          GenerateAssignOperator( code, field.FieldType, customName, leftPrefix + field.Name + ".", rightPrefix + field.Name + "." );
        else
          code.WriteLine( 1, "{0}{2} = {1}{2};", leftPrefix, rightPrefix, field.Name );
      }
    }
  }

}