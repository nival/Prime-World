using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.Reflection;
using DBCodeGen.SocialClientCodeGeneration;
using DBCodeGen.SocialClientGeneration;
using DBCodeGen.Utils;
using libdb.Animated;
using libdb.DB;
using libdb.IO;
using Microsoft.Build.BuildEngine;

namespace DBCodeGen.CodeGeneration
{
  internal sealed partial class Struct
  {
    #region FieldDef

    private struct FieldDef
    {
      public FieldDef( Type ownerType, Type origFieldType, FieldInfo field )
      {
        this.ownerType = ownerType; this.origFieldType = origFieldType; this.field = field;

        fieldType = origFieldType;
        if ( TypeUtils.HasAttribute<SrcFileAttribute>( field, true ) )
        {
          if ( fieldType == typeof( string ) )
            fieldType = typeof( SrcFile );
          else if ( fieldType == typeof( List<string> ) )
            fieldType = typeof( List<SrcFile> );
        }
      }

      public Type ownerType;
      public bool IsResourceType { get { return DBCodeGen.IsResource( ownerType ); } }

      public FieldInfo field;
      public Type origFieldType;
      public Type fieldType;
      public bool IsAssignable
      {
        get
        {
          return DBCodeGen.IsStruct( fieldType ) || TypeUtils.IsList( fieldType )
            || fieldType == typeof( TextRef ) || fieldType == typeof( SrcFile );
        }
      }

      public string Name { get { return field.Name; } }
    };

    #endregion

    private static string FormatObjectAsSigle( object value )
    {
      float f = (Single)value;
      string result = f.ToString( NumberFormatInfo.InvariantInfo );
      if ( result.IndexOf( '.' ) == -1 )
        result += ".0";
      result += 'f';

      return result;
    }

    /// <summary>
    /// Compare filed value in objects. Works only for simple types (int, string and float). For other types returns true.
    /// </summary>
    private static bool IsFieldEqual( FieldInfo field, object obj1, object obj2 )
    {
      object value1 = field.GetValue( obj1 );
      object value2 = field.GetValue( obj2 );
      if ( field.FieldType == typeof( int ) )
        return (int)value1 == (int)value2;
      else if ( field.FieldType == typeof( string ) )
        return (string)value1 == (string)value2;
      else if ( field.FieldType == typeof( float ) )
        return (float)value1 == (float)value2;
      else if ( field.FieldType == typeof( bool ) )
        return (bool)value1 == (bool)value2;
      else if ( field.FieldType.IsEnum )
        return (int)value1 == (int)value2;
      else
        return true;
    }

    private static string ConvertValueToString( object value, Type valueType )
    {
      if ( valueType == typeof( Guid ) )
        return "Guid.NewGuid()";
      else if ( valueType == typeof( string ) )
      {
        string valueStr = value as string;
        if ( string.IsNullOrEmpty( valueStr ) )
          return "string.Empty";
        else
          return "\"" + Utilities.Escape( valueStr ) + "\"";
      }
      else if ( valueType == typeof( bool ) )
        return value.ToString().ToLower();
      else if ( valueType == typeof( Single ) )
        return FormatObjectAsSigle( value );
      else if ( valueType.IsEnum )
        return DBCodeGen.GetCSEnumValue( valueType, value );
      else if ( valueType.IsClass )
        return "new " + valueType.Name + "()";
      else
        return value.ToString();
    }

    private static bool WriteCSStructInitializer( string customName, CodeWriter csCode, int indent, FieldInfo field, object constructedObject, FieldInfo rootField, string prefix, bool equalToDefault )
    {
      object defaultObject = field.FieldType.GetConstructor( Type.EmptyTypes ).Invoke( new object[0] );

      if ( constructedObject != null && defaultObject != null )
      {
        foreach ( FieldInfo subField in DBCodeGen.GetFields( field.FieldType, true, customName, null ) )
        {
          if ( DBCodeGen.IsStruct( subField.FieldType ) )
            equalToDefault = WriteCSStructInitializer( customName, csCode, indent, subField, subField.GetValue( constructedObject ), rootField, prefix + "." + subField.Name, equalToDefault );
          else if ( !IsFieldEqual( subField, constructedObject, defaultObject ) )
          {
            if ( equalToDefault )
              csCode.WriteLine( indent + 2, "{1} __{0} = new {1}(); // Construct default object for {0}", rootField.Name, DBCodeGen.GetCSTypeFieldeName( rootField.FieldType ) );
            csCode.WriteLine( indent + 2, "__{0}{1}.{2} = {3};", rootField.Name, prefix, subField.Name, ConvertValueToString( subField.GetValue( constructedObject ), subField.FieldType ) );
            equalToDefault = false;
          }
        }
      }

      return equalToDefault;
    }

    private static void AddSubscriptionCode( CodeWriter csCode, int indent, Type ownerType, List<FieldDef> csFields )
    {
      if ( ownerType.IsSubclassOf( typeof( DBResource ) ) )
        csCode.WriteLine( indent + 2, "___parent.Changed += FireChangedEvent;" );

      foreach ( FieldDef fd in csFields )
      {
        var fieldType = fd.origFieldType;
        if ( !TypeUtils.HasAttribute<DstFileAttribute>( fd.field, true ) && !TypeUtils.HasAttribute<AbstractAttribute>( fd.field, true ) )
        {
          csCode.WriteLine( indent + 2, "_{0}.Changed += FireChangedEvent;", fd.Name );
        }
        if ( NeedToGenerateChangedEvent( fd.field ) )
        {
          csCode.WriteLine( indent + 2, "_{0}.Changed += Fire_{0}_ChangedEvent;", fd.Name );
        }
      }
    }

    private static bool NeedToGenerateChangedEvent( FieldInfo field )
    {
      return
        !TypeUtils.HasAttribute<DstFileAttribute>( field, true ) &&
        TypeUtils.HasAttribute<GenerateChangedEventAttribute>( field, true );
    }

    private static List<FieldInfo> GetSortedDstFileArgProperties( Type type )
    {
      FieldInfo[] fields = DBCodeGen.GetFields( type, true, string.Empty, null );
      var dstFileArgProperties = new Dictionary<FieldInfo, DstFileArgAttribute>();
      foreach ( FieldInfo field in fields )
      {
        var props = TypeUtils.GetAttributes<DstFileArgAttribute>( field, true );
        if ( props != null && props.Length > 0 )
        {
          dstFileArgProperties.Add( field, (DstFileArgAttribute)props[0] );
        }
      }

      var result = new List<FieldInfo>( dstFileArgProperties.Keys );
      result.Sort( ( left, right ) => dstFileArgProperties[left].Position.CompareTo( dstFileArgProperties[right].Position ) );
      return result;
    }

    private static void WriteCSFile( Type type, bool resource, string customName, CodeWriter csCode,
      int indent, List<FieldInfo> csFields, object constructedObject, Attribute[] addingAttributes )
    {
      CSCode.WriteAttributes( csCode, indent, TypeUtils.GetAttributes<Attribute>( type, false ) );

      if ( addingAttributes != null )
        CSCode.WriteAttributes( csCode, indent, addingAttributes );


      bool hasAbstractField = false;
      foreach ( var field in csFields )
      {
        if ( TypeUtils.HasAttribute<AbstractAttribute>( field, false ) )
        {
          hasAbstractField = true;
          break;
        }
      }

      WriteCSClassHeader( type, resource, csCode, indent, hasAbstractField );

      List<FieldInfo> sortedDstArgFields = GetSortedDstFileArgProperties( type );
      List<FieldDef> csFieldDefs = new List<FieldDef>();

      foreach ( FieldInfo field in csFields )
      {
        csFieldDefs.Add( new FieldDef( type, field.FieldType, field ) );
      }

      foreach ( FieldDef field in csFieldDefs )
      {
        WriteCSField( field, csCode, indent );
      }
      csCode.WriteLine();

      foreach ( FieldDef field in csFieldDefs )
      {
        WriteCSProperty( field, csCode, indent, sortedDstArgFields );
      }

      foreach ( FieldDef field in csFieldDefs )
      {
        if ( NeedToGenerateChangedEvent( field.field ) )
        {
          csCode.WriteLine( indent + 1, "public event EventHandler {0}_Changed;", field.Name );
          csCode.WriteLine();
          csCode.WriteLine( indent + 1, "private void Fire_{0}_ChangedEvent( object sender, EventArgs e )", field.Name );
          csCode.WriteLine( indent + 1, "{" );
          csCode.WriteLine( indent + 2, "if ( {0}_Changed != null ) {0}_Changed( sender, e );", field.Name );
          csCode.WriteLine( indent + 1, "}" );
          csCode.WriteLine();
        }
      }

      if ( !IsDerivedFromAnimatedTracks( type ) )
      {
        // write Initialize method
        WriteInitializeMethod( type, customName, csCode, indent, constructedObject, csFieldDefs );
      }

      WriteCSConstructors( type, csCode, indent, csFieldDefs, constructedObject );
      WriteCSAssignMethods( type, csCode, indent, csFieldDefs );

      if ( !TypeUtils.IsSubclassOf( type, typeof( AnimatedTracks<,> ) ) )
        WriteCSComplexDBValueMethods( type, csCode, indent + 1, csFieldDefs );

      csCode.WriteLine( indent, "}" );
      csCode.WriteLine();
    }

    private static void WriteInitializeMethod( Type type, string customName, CodeWriter csCode, int indent, object constructedObject, List<FieldDef> csFieldDefs )
    {
      csCode.WriteLine( indent + 1, "private void Initialize( DBResource owner )" );
      csCode.WriteLine( indent + 1, "{" );
      if ( type.IsSubclassOf( typeof( DBResource ) ) )
        csCode.WriteLine( indent + 2, "___parent = new UndoRedoDBPtr<{0}>(owner);", type.Name );

      foreach ( FieldDef fd in csFieldDefs )
      {

        if ( TypeUtils.HasAttribute<DstFileAttribute>( fd.field, false ) || TypeUtils.HasAttribute<AbstractAttribute>( fd.field, false ) )
          continue;

        if ( TypeUtils.IsSubclassOf( fd.fieldType, typeof( IAnimated ) ) )
        {
          IAnimated animatedObject = fd.field.GetValue( constructedObject ) as IAnimated;
          if ( animatedObject == null || animatedObject.TracksCount == 0 )
            csCode.WriteLine( indent + 2, "_{0} = new {1}( owner );", fd.Name, DBCodeGen.GetCSTypeFieldeName( fd.fieldType ) );
          else
          {
            List<string> animatedArgs = new List<string>();

            if ( animatedObject.TracksCount == 1 )
              animatedArgs.Add( ConvertValueToString( animatedObject.GetObjectValue( 0 ), animatedObject.TrackValueType ) );
            else
            {
              AnimatedComplexConverterAttribute animatedAttr = TypeUtils.GetAttribute<AnimatedComplexConverterAttribute>( fd.fieldType, false );
              for ( int i = 0; i < animatedAttr.Args.Length; ++i )
                animatedArgs.Add( ConvertValueToString( animatedObject.GetObjectTrackValue( 0, i ), animatedObject.TrackValueType ) );
            }

            csCode.WriteLine( indent + 2, "_{0} = new {1}( owner, {2} );", fd.Name, DBCodeGen.GetCSTypeFieldeName( fd.fieldType ), string.Join( ", ", animatedArgs.ToArray() ) );
          }
        }
        else if ( DBCodeGen.IsStruct( fd.fieldType ) )
        {
          if ( WriteCSStructInitializer( customName, csCode, indent, fd.field, fd.field.GetValue( constructedObject ), fd.field, string.Empty, true ) )
            csCode.WriteLine( indent + 2, "_{0} = new {1}( owner );", fd.Name, DBCodeGen.GetCSTypeFieldeName( fd.fieldType ) );
          else
            csCode.WriteLine( indent + 2, "_{0} = new {1}( owner, __{0} );", fd.Name, DBCodeGen.GetCSTypeFieldeName( fd.fieldType ) );
        }
        else if ( TypeUtils.GetTypeFromPtr( fd.fieldType ) != null )
        {
          csCode.WriteLine( indent + 2, "_{0} = new {1}( owner );", fd.Name, DBCodeGen.GetCSTypeFieldeName( fd.fieldType ) );
        }
        else if ( TypeUtils.IsList( fd.fieldType ) )
        {
          EnumArrayAttribute enumAttr = TypeUtils.GetAttribute<EnumArrayAttribute>( fd.field, true );
          MinMaxSizeAttribute minMaxAttr = TypeUtils.GetAttribute<MinMaxSizeAttribute>( fd.field, true );

          if ( enumAttr != null )
            csCode.WriteLine( indent + 2, "_{0} = new {1}( owner, typeof( {2} ) );", fd.Name, DBCodeGen.GetCSTypeFieldeName( fd.fieldType ), enumAttr.enumType.Name );
          else if ( minMaxAttr != null )
            csCode.WriteLine( indent + 2, "_{0} = new {1}( owner, {2}, {3} );", fd.Name, DBCodeGen.GetCSTypeFieldeName( fd.fieldType ), minMaxAttr.min, minMaxAttr.max );
          else
            csCode.WriteLine( indent + 2, "_{0} = new {1}( owner );", fd.Name, DBCodeGen.GetCSTypeFieldeName( fd.fieldType ) );
        }
        else
          csCode.WriteLine( indent + 2, "_{0} = new {1}( owner, {2} );", fd.Name, DBCodeGen.GetCSTypeFieldeName( fd.fieldType ), ConvertValueToString( fd.field.GetValue( constructedObject ), fd.fieldType ) );
      }
      AddSubscriptionCode( csCode, indent, type, csFieldDefs );
      csCode.WriteLine( indent + 1, "}" );
      csCode.WriteLine();
    }

    private static void WriteCSConstructors( Type type, CodeWriter csCode, int indent, List<FieldDef> csFields, object constructedObject )
    {
      if ( TypeUtils.IsResourceType( type ) )
      {
        csCode.WriteLine( indent + 1, "public {0}()", type.Name );
        csCode.WriteLine( indent + 1, "{" );
        csCode.WriteLine( indent + 2, "Initialize( this );" );
        if ( TypeUtils.HasAttribute<PostInitializeAttribute>( type, false ) )
          csCode.WriteLine( indent + 2, "PostInitialize();" );
        csCode.WriteLine( indent + 1, "}" );
      }
      else
      {
        if ( !IsDerivedFromAnimatedTracks( type ) )
        {
          csCode.WriteLine( indent + 1, "public {0}()", type.Name );
          csCode.WriteLine( indent + 1, "{" );

          csCode.WriteLine( indent + 2, "Initialize( GetOwner() );" );

          if ( TypeUtils.HasAttribute<PostInitializeAttribute>( type, false ) )
            csCode.WriteLine( indent + 2, "PostInitialize();" );

          csCode.WriteLine( indent + 1, "}" );
          csCode.WriteLine();
        }

        if ( IsDerivedStruct( type ) || IsDerivedFromAnimatedTracks( type ) )
          csCode.WriteLine( indent + 1, "public {0}( DBResource owner ) : base( owner )", type.Name );
        else
          csCode.WriteLine( indent + 1, "public {0}( DBResource owner )", type.Name );

        csCode.WriteLine( indent + 1, "{" );

        if ( !IsDerivedStruct( type ) && !IsDerivedFromAnimatedTracks( type ) )
          csCode.WriteLine( indent + 2, "this.owner = owner;" );

        if ( !IsDerivedFromAnimatedTracks( type ) )
          csCode.WriteLine( indent + 2, "Initialize( GetOwner() );" );
        if ( TypeUtils.HasAttribute<PostInitializeAttribute>( type, false ) )
          csCode.WriteLine( indent + 2, "PostInitialize();" );

        csCode.WriteLine( indent + 1, "}" );
        csCode.WriteLine();

        if ( TypeUtils.IsSubclassOf( type, typeof( IAnimated ) ) )
        {
          IAnimated animatedObject = constructedObject as IAnimated;
          AnimatedComplexConverterAttribute animatedAttr = TypeUtils.GetAttribute<AnimatedComplexConverterAttribute>( type, false );
          string args = string.Empty;
          if ( animatedObject.TracksCount == 1 )
            args = string.Format( "{0} value", DBCodeGen.GetCSSimpleTypeName( animatedObject.ValueType ) );
          else
          {
            List<string> trackNames = new List<string>();
            foreach ( string trackName in animatedAttr.Args )
              trackNames.Add( string.Format( "{0} {1}", DBCodeGen.GetCSSimpleTypeName( animatedObject.TrackValueType ), trackName ) );
            args = string.Join( ", ", trackNames.ToArray() );
          }

          csCode.WriteLine( indent + 1, "public {0}( DBResource owner, {1} )", type.Name, args );
          csCode.WriteLine( indent + 2, ": base( owner )", type.Name, args );
          csCode.WriteLine( indent + 1, "{" );
          //csCode.WriteLine( indent + 2, "this.owner = owner;" );
          //csCode.WriteLine( indent + 2, "Initialize( owner );" );
          if ( animatedObject.TracksCount == 1 )
            csCode.WriteLine( indent + 2, "Clear( value );" );
          else
          {
            for ( int i = 0; i < animatedAttr.Args.Length; ++i )
            {
              csCode.WriteLine( indent + 2, "this[{0}].Clear();", i );
              csCode.WriteLine( indent + 2, "this[{0}].SetValue( 0, {1} );", i, animatedAttr.Args[i] );
            }
          }
          if ( TypeUtils.HasAttribute<PostInitializeAttribute>( type, false ) )
            csCode.WriteLine( indent + 2, "PostInitialize();" );
          csCode.WriteLine( indent + 2, "Reset();" );
          csCode.WriteLine( indent + 1, "}" );
          csCode.WriteLine();
        }

        WriteCSCopyConstructor( type, csCode, indent, csFields );
      }
    }



    private static void WriteCSCopyConstructor( Type type, CodeWriter csCode, int indent, List<FieldDef> csFields )
    {
      if ( !IsDerivedStruct( type ) )
      {
        csCode.WriteLine( indent + 1, "public {0}( DBResource owner, {0} source )", type.Name );
        csCode.WriteLine( indent + 2, ": this(owner, source, true){}" );
        csCode.WriteLine();
        WriteCSProtectedCopyConstructor( csCode, indent, type, csFields, true );
      }
      else
      {
        WriteCSProtectedCopyConstructor( csCode, indent, type, csFields, false );
      }
    }

    private static void WriteCSProtectedCopyConstructor( CodeWriter csCode, int indent, Type type, List<FieldDef> csFields, bool isBase )
    {
      bool isAnimated = TypeUtils.IsSubclassOf( type, typeof( AnimatedTracks<,> ) );

      if ( isBase && !isAnimated )//base but not animated
        csCode.WriteLine( indent + 1, "protected {0}( DBResource owner, {0} source, bool fireEvent )", type.Name );
      else if ( isAnimated )//animated
        csCode.WriteLine( indent + 1, "private {0}( DBResource owner, {0} source, bool fireEvent ) : base (owner)", type.Name );
      else//child
        csCode.WriteLine( indent + 1, "public {0}( DBResource owner, {0} source ): base(owner, source, false)", type.Name );

      csCode.WriteLine( indent + 1, "{" );

      foreach ( FieldDef fd in csFields )
      {
        if ( TypeUtils.HasAttribute<DstFileAttribute>( fd.field, false ) || TypeUtils.HasAttribute<AbstractAttribute>( fd.field, false ) )
          continue;

        if ( TypeUtils.IsList( fd.fieldType ) )
        {
          EnumArrayAttribute enumAttr = TypeUtils.GetAttribute<EnumArrayAttribute>( fd.field, true );
          MinMaxSizeAttribute minMaxAttr = TypeUtils.GetAttribute<MinMaxSizeAttribute>( fd.field, true );

          if ( enumAttr != null )
            csCode.WriteLine( indent + 2, "_{0} = new {1}( owner, typeof( {2} ) );", fd.Name, DBCodeGen.GetCSTypeFieldeName( fd.fieldType ), enumAttr.enumType.Name );
          else if ( minMaxAttr != null )
            csCode.WriteLine( indent + 2, "_{0} = new {1}( owner, {2}, {3} );", fd.Name, DBCodeGen.GetCSTypeFieldeName( fd.fieldType ), minMaxAttr.min, minMaxAttr.max );
          else
            csCode.WriteLine( indent + 2, "_{0} = new {1}( owner );", fd.Name, DBCodeGen.GetCSTypeFieldeName( fd.fieldType ) );
          csCode.WriteLine( indent + 2, "_{0}.Assign( source.{0} );", fd.Name );
        }
        else
          csCode.WriteLine( indent + 2, "_{0} = new {1}( owner, source.{0} );", fd.Name, DBCodeGen.GetCSTypeFieldeName( fd.fieldType ) );
      }

      AddSubscriptionCode( csCode, indent, type, csFields );
      if ( TypeUtils.IsSubclassOf( type, typeof( IAnimated ) ) )
        csCode.WriteLine( indent + 2, "base.Assign( source );" );

      if ( isBase )
      {
        if ( !IsDerivedFromAnimatedTracks( type ) )
          csCode.WriteLine( indent + 2, "this.owner = owner;" );

        csCode.WriteLine( indent + 2, "if(fireEvent)" );
        csCode.WriteLine( indent + 3, "FireChangedEvent( this, EventArgs.Empty );" );
      }
      else
      {
        csCode.WriteLine( indent + 2, "FireChangedEvent( this, EventArgs.Empty );" );
      }


      csCode.WriteLine( indent + 1, "}" );
      csCode.WriteLine();
    }

    private static void WriteCSAssignMethods( Type type, CodeWriter csCode, int indent, List<FieldDef> csFieldDefs )
    {
      if ( TypeUtils.IsResourceType( type ) )
      {
        csCode.WriteLine( indent + 1, "private void AssignSelf( {0} source )", type.Name );
        csCode.WriteLine( indent + 1, "{" );
      }
      else
      {
        if ( TypeUtils.IsSubclassOf( type, typeof( IAnimated ) ) || IsDerivedStruct( type ) )
          csCode.WriteLine( indent + 1, "public override void Assign( object _source )" );
        else
          csCode.WriteLine( indent + 1, "public virtual void Assign( object _source )" );

        csCode.WriteLine( indent + 1, "{" );
        csCode.WriteLine( indent + 2, "{0} source = _source as {0};", type.Name );
        csCode.WriteLine( indent + 2, "if ( null == source || this == source )" );
        csCode.WriteLine( indent + 3, "return;" );
      }

      csCode.WriteLine( indent + 2, "DataBase.UndoRedoManager.Start( \"Assign for {0}\" );", type.Name );
      if ( TypeUtils.IsSubclassOf( type, typeof( IAnimated ) ) )
      {
        csCode.WriteLine( indent + 2, "base.Assign( source );" );
      }
      else
      {
        if ( IsDerivedStruct( type ) )
        {
          csCode.WriteLine();
          csCode.WriteLine( indent + 2, "base.Assign( source );" );
          csCode.WriteLine();
        }

        foreach ( FieldDef fd in csFieldDefs )
        {
          if ( TypeUtils.HasAttribute<DstFileAttribute>( fd.field, false ) || TypeUtils.HasAttribute<AbstractAttribute>( fd.field, false ) )
            continue;
          csCode.WriteLine( indent + 2, "{0} = source.{0};", fd.Name );
        }
      }
      csCode.WriteLine( indent + 2, "DataBase.UndoRedoManager.Commit();" );
      csCode.WriteLine( indent + 1, "}" );
      csCode.WriteLine();


      if ( TypeUtils.IsResourceType( type ) )
      {
        csCode.WriteLine( indent + 1, "public override void Assign( object _source )" );
        csCode.WriteLine( indent + 1, "{" );
        csCode.WriteLine( indent + 2, "{0} source = _source as {0};", type.Name );
        csCode.WriteLine( indent + 2, "if ( source == null || this == source )" );
        csCode.WriteLine( indent + 3, "return;" );
        csCode.WriteLine( indent + 2, "DataBase.UndoRedoManager.Start( \"Assign for {0}\" );", type.Name );
        if ( type.BaseType.IsSubclassOf( typeof( libdb.IBasicDBValue ) ) )
          csCode.WriteLine( indent + 2, "base.Assign( source );" );
        csCode.WriteLine( indent + 2, "AssignSelf( source );" );

        csCode.WriteLine( indent + 2, "DataBase.UndoRedoManager.Commit();" );
        csCode.WriteLine( indent + 1, "}" );
        csCode.WriteLine();
      }
    }

    private static void WriteCSComplexDBValueMethods( Type type, CodeWriter csCode, int indent, List<FieldDef> csFields )
    {
      bool resource = TypeUtils.IsResourceType( type );

      csCode.WriteLine( indent, "public " + VariableVirtualPrefix( type ) + "void SetParent( object _newParent )" );
      csCode.WriteLine( indent, "{" );
      csCode.WriteLine( indent + 1, "DataBase.UndoRedoManager.SerializeSuspend();" );
      if ( resource )
      {
        csCode.WriteLine( indent + 1, "DBPtrBase rawParent = _newParent as DBPtrBase;" );
        csCode.WriteLine( indent + 1, "{0} newParent = rawParent == null ? null : rawParent.Get<{0}>();", type.Name );
        csCode.WriteLine( indent + 1, "if ( newParent == null && _newParent is {0} )", type.Name );
        csCode.WriteLine( indent + 2, "newParent = _newParent as {0};", type.Name );
        csCode.WriteLine( indent + 1, "if ( newParent == null && this.__parent.IsValid )" );
        csCode.WriteLine( indent + 2, "AssignSelf( this );" );
        csCode.WriteLine( indent + 1, "this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );" );
        csCode.WriteLine( indent + 1, "base.SetParent( newParent );" );
      }
      else
      {
        if ( IsDerivedStruct( type ) )
        {
          csCode.WriteLine( indent + 1, "base.SetParent(_newParent);" );
          csCode.WriteLine();
        }

        csCode.WriteLine( indent + 1, "{0} newParent = _newParent as {0};", type.Name );
        csCode.WriteLine( indent + 1, "if ( newParent == null && this.__parent != null )" );
        csCode.WriteLine( indent + 2, "Assign( this );" );

        csCode.WriteLine( indent + 1, "this.__parent = newParent;" );
        if ( TypeUtils.IsSubclassOf( type, typeof( IAnimated ) ) )
        {
          csCode.WriteLine( indent + 1, "if ( newParent != null )" );
          csCode.WriteLine( indent + 2, "Assign( newParent );" );
        }
      }
      csCode.WriteLine();
      foreach ( var field in csFields )
      {
        if ( TypeUtils.HasAttribute<DstFileAttribute>( field.field, false ) || TypeUtils.HasAttribute<AbstractAttribute>( field.field, false ) )
          continue;
        csCode.WriteLine( indent + 1, "_{0}.SetParent( newParent == null ? null : newParent._{0} );", field.Name );
      }
      csCode.WriteLine( indent + 1, "DataBase.UndoRedoManager.SerializeResume();" );
      csCode.WriteLine( indent, "}" );
      csCode.WriteLine();

      csCode.WriteLine( indent, "public " + VariableVirtualPrefix( type ) + "void Reset()" );
      csCode.WriteLine( indent, "{" );

      foreach ( var field in csFields )
      {
        if ( TypeUtils.HasAttribute<DstFileAttribute>( field.field, false ) || TypeUtils.HasAttribute<AbstractAttribute>( field.field, false ) )
          continue;
        csCode.WriteLine( indent + 1, "_{0}.Reset();", field.Name );
      }

      if ( resource || IsDerivedStruct( type ) )
        csCode.WriteLine( indent + 1, "base.Reset();" );

      csCode.WriteLine( indent, "}" );
      csCode.WriteLine();


      csCode.WriteLine( indent, "public " + VariableVirtualPrefix( type ) + "bool IsDerivedFromParent()" );
      csCode.WriteLine( indent, "{" );
      if ( resource )
        csCode.WriteLine( indent + 1, "if ( __parent == null || __parent.Get() == null )" );
      else
        csCode.WriteLine( indent + 1, "if ( __parent == null )" );
      csCode.WriteLine( indent + 2, "return true;" );
      csCode.WriteLine( indent + 1, "return " );
      string prefix = string.Empty;
      int fieldCount = 0;
      foreach ( var field in csFields )
      {
        if ( TypeUtils.HasAttribute<DstFileAttribute>( field.field, false ) || TypeUtils.HasAttribute<AbstractAttribute>( field.field, false ) )
          continue;
        csCode.WriteLine( indent + 2, prefix + "_{0}.IsDerivedFromParent()", field.Name );
        prefix = "&& ";
        ++fieldCount;
      }
      if ( resource || IsDerivedStruct( type ) )
        csCode.WriteLine( indent + 2, prefix + "base.IsDerivedFromParent();" );
      else
      {
        if ( fieldCount > 0 )
          csCode.WriteLine( indent + 2, ";" );
        else
          csCode.WriteLine( indent + 2, "true;" );
      }
      csCode.WriteLine( indent, "}" );
      csCode.WriteLine();

      csCode.WriteLine( indent, "public " + VariableVirtualPrefix( type ) + "void ResetField( string fieldName )" );
      csCode.WriteLine( indent, "{" );
      fieldCount = 0;
      foreach ( var field in csFields )
      {
        if ( TypeUtils.HasAttribute<DstFileAttribute>( field.field, false ) || TypeUtils.HasAttribute<AbstractAttribute>( field.field, false ) )
          continue;
        if ( fieldCount > 0 )
          csCode.WriteLine( indent + 1, "else if ( fieldName == \"{0}\" )", field.Name );
        else
          csCode.WriteLine( indent + 1, "if ( fieldName == \"{0}\" )", field.Name );
        csCode.WriteLine( indent + 2, "_{0}.Reset();", field.Name );
        ++fieldCount;
      }
      if ( fieldCount > 0 )
        csCode.WriteLine( indent + 1, "else" );
      if ( resource || IsDerivedStruct( type ) )
        csCode.WriteLine( indent + 2, "base.ResetField( fieldName );" );
      else
        csCode.WriteLine( indent + 2, "Log.AlwaysAssert( \"Field with name {0} not found\", fieldName );" );
      csCode.WriteLine( indent, "}" );
      csCode.WriteLine();

      csCode.WriteLine( indent, "public " + VariableVirtualPrefix( type ) + "bool IsFieldDerivedFromParent( string fieldName )" );
      csCode.WriteLine( indent, "{" );
      if ( resource )
        csCode.WriteLine( indent + 1, "if ( __parent == null || __parent.Get() == null )" );
      else
        csCode.WriteLine( indent + 1, "if ( __parent == null )" );
      csCode.WriteLine( indent + 2, "return true;" );
      csCode.WriteLine( indent + 1, "if ( fieldName == \"__parent\" )" );
      if ( resource )
        csCode.WriteLine( indent + 2, "return __parent == null || __parent.Get() == null;" );
      else
        csCode.WriteLine( indent + 2, "return __parent == null;" );
      foreach ( var field in csFields )
      {
        if ( TypeUtils.HasAttribute<DstFileAttribute>( field.field, false ) || TypeUtils.HasAttribute<AbstractAttribute>( field.field, false ) )
          continue;

        csCode.WriteLine( indent + 1, "if ( fieldName == \"{0}\" )", field.Name );
        csCode.WriteLine( indent + 2, "return _{0}.IsDerivedFromParent();", field.Name );
      }
      csCode.WriteLine( indent + 1, "else" );
      if ( resource || IsDerivedStruct( type ) )
        csCode.WriteLine( indent + 2, "return base.IsFieldDerivedFromParent( fieldName );" );
      else
      {
        csCode.WriteLine( indent + 1, "{" );
        csCode.WriteLine( indent + 2, "Log.AlwaysAssert( \"Field with name {0} not found\", fieldName );" );
        csCode.WriteLine( indent + 2, "return true;" );
        csCode.WriteLine( indent + 1, "}" );
      }
      csCode.WriteLine( indent, "}" );

      csCode.WriteLine( indent, "public " + VariableVirtualPrefix( type ) + "bool HasParent()" );
      csCode.WriteLine( indent, "{" );
      csCode.WriteLine( indent + 1, "return __parent != null;" );
      csCode.WriteLine( indent, "}" );

      csCode.WriteLine();
    }

    //bool HasParent();

    private static string VariableVirtualPrefix( Type type )
    {
      if ( TypeUtils.IsSubclassOf( type, typeof( IAnimated ) ) )
        return "override ";

      if ( DBCodeGen.IsStruct( type ) )
      {
        if ( type.BaseType != typeof( Object ) )
          return "override ";
        else
          return "virtual ";
      }

      if ( !TypeUtils.IsResourceType( type ) )
        return "";

      return "override ";
    }

    private static bool IsDerivedStruct( Type _type )
    {
      return DBCodeGen.IsStruct( _type ) &&
             _type.BaseType != typeof( Object ) &&
             ( !TypeUtils.IsSubclassOf( _type, typeof( AnimatedTracks<,> ) ) );
    }

    private static bool IsDerivedFromAnimatedTracks( Type _type )
    {
      return TypeUtils.IsSubclassOf( _type, typeof( AnimatedTracks<,> ) );
    }

    private static void WriteCSClassHeader( Type type, bool resource, CodeWriter csCode, int indent, bool hasAbstractField )
    {
      if ( !resource )
      {
        bool isAnimated = TypeUtils.IsSubclassOf( type, typeof( AnimatedTracks<,> ) );
        AnimatedComplexConverterAttribute attr = TypeUtils.GetAttribute<AnimatedComplexConverterAttribute>( type, false );
        bool partialDef = attr != null && !attr.CreateConverter;
        partialDef |= TypeUtils.HasAttribute<PostInitializeAttribute>( type, false );

        string dbValueParent = isAnimated ? "libdb.IBasicDBValue" : "libdb.ICompositeDBValue";
        csCode.WriteLine( indent, "public {2}{4}class {0} : {1}{3}, libdb.IChangeable", type.Name, CSCode.GetParents( csCode, indent, type ), partialDef ? "partial " : string.Empty, dbValueParent, hasAbstractField ? "abstract " : string.Empty );
        csCode.WriteLine( indent, "{" );

        if ( attr != null && attr.CreateConverter )
          CSCode.WriteAnimatedComplexConverter( csCode, indent, type, attr );

        if ( !isAnimated )
        {
          if ( !IsDerivedStruct( type ) )
          {
            csCode.WriteLine( indent + 1, "private DBResource owner = null;" );
            csCode.WriteLine( indent + 1, "public DBResource GetOwner() { return owner; }" );
          }

          csCode.WriteLine();

          csCode.WriteLine( indent + 1, "private {0} __parent = null;", type.Name );
          csCode.WriteLine();

          if ( !IsDerivedStruct( type ) )
          {
            csCode.WriteLine( indent + 1, "public event EventHandler Changed;" );
            csCode.WriteLine();

            csCode.WriteLine( indent + 1, "protected void FireChangedEvent( object sender, EventArgs e )" );

            csCode.WriteLine( indent + 1, "{" );
            csCode.WriteLine( indent + 1 + 1, "if ( Changed != null ) Changed( sender, e );" );
            csCode.WriteLine( indent + 1, "}" );
            csCode.WriteLine();
          }
        }
      }
      else
      {
        csCode.WriteLine( indent, "public {2}{3}class {0} : {1}", type.Name, type.BaseType.Name, TypeUtils.HasAttribute<PostInitializeAttribute>( type, false ) ? "partial " : string.Empty, hasAbstractField ? "abstract " : string.Empty );
        csCode.WriteLine( indent, "{" );

        csCode.WriteLine( indent + 1, "private UndoRedoDBPtr<{0}> ___parent;", type.Name );
        csCode.WriteLine( indent + 1, "[HideInOutliner]" );
        csCode.WriteLine( indent + 1, "public new DBPtr<{0}> __parent {{ get {{ return ___parent.Get(); }}", type.Name );
        csCode.WriteLine( indent + 2, "set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }" );
        csCode.WriteLine();
      }
    }

    private static void WriteCSField( FieldDef def, CodeWriter csCode, int indent )
    {
      if ( TypeUtils.HasAttribute<DstFileAttribute>( def.field, false ) || TypeUtils.HasAttribute<AbstractAttribute>( def.field, false ) )
        return;

      csCode.WriteLine( indent + 1, "private {0} _{1};", DBCodeGen.GetCSTypeFieldeName( def.fieldType ), def.field.Name );
    }

    private static void WriteCSProperty( FieldDef def, CodeWriter csCode, int indent, List<FieldInfo> sortedDstArgFields )
    {
      if ( TypeUtils.HasAttribute<DstFileAttribute>( def.field, true ) )
      {
        CSCode.WriteAttributes( csCode, indent + 1, TypeUtils.GetAttributes<Attribute>( def.field, false ) );
        csCode.WriteLine( indent + 1, "public string {0} {{ get {{", def.Name );
        csCode.WriteLine( indent + 2, "return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(" );
        csCode.WriteLine( indent + 3, def.IsResourceType ? "  DBId" : "  GetOwner().DBId" );
        csCode.WriteLine( indent + 3, ", \"{0}\"", TypeUtils.GetAttribute<DstFileAttribute>( def.field, true ).Extension.Trim() );

        foreach ( FieldInfo dstArgField in sortedDstArgFields )
        {
          if ( TypeUtils.HasAttribute<SrcFileAttribute>( dstArgField, true ) )
            csCode.WriteLine( indent + 3, ", libdb.DB.GeneratedCodeUtilities.GetOnlyFileName( {0}.ToString() )", dstArgField.Name );
          else
            csCode.WriteLine( indent + 3, ", {0}.ToString()", dstArgField.Name );
        }

        csCode.WriteLine( indent + 1, "); } }" );

        return;
      }

      //property

      CSCode.WriteAttributes( csCode, indent + 1, TypeUtils.GetAttributes<Attribute>( def.field, false ) );
      string fieldName = def.Name;

      bool isOverride = false;
      if ( def.ownerType.BaseType != null )
      {
        FieldInfo baseField = def.ownerType.BaseType.GetField( def.Name, BindingFlags.Public | BindingFlags.Instance | BindingFlags.DeclaredOnly );
        isOverride = baseField != null && TypeUtils.HasAttribute<AbstractAttribute>( baseField, false );
      }
      if ( TypeUtils.HasAttribute<AbstractAttribute>( def.field, false ) )
      {
        csCode.WriteLine( indent + 1, "public abstract {0} {1} {{ get; set; }}", DBCodeGen.GetCSTypePropertyName( def.fieldType ), def.field.Name );
      }
      else if ( def.IsAssignable )
      {
        csCode.WriteLine( indent + 1, "public {2}{0} {1} {{ get {{ return _{1}; }} set {{ _{1}.Assign( value ); }} }}", DBCodeGen.GetCSTypePropertyName( def.fieldType ), def.field.Name, isOverride ? "override " : string.Empty );
      }
      else
      {
        csCode.WriteLine( indent + 1, "public {2}{0} {1} {{ get {{ return _{1}.Get(); }} set {{ _{1}.Set( value ); }} }}", DBCodeGen.GetCSTypePropertyName( def.fieldType ), def.field.Name, isOverride ? "override " : string.Empty );
      }
      csCode.WriteLine();
    }


    public static void Write( Type type, bool resource, string customName, CodeWriter header, CodeWriter code, CodeWriter csCode, int indent, Attribute[] addingAttributes )
    {
      string structName = DBCodeGen.GetTypeName( type );
      bool needChecksum = false;
      bool serializerOnly = false;

      List<FieldInfo> cppFields = new List<FieldInfo>( DBCodeGen.GetFields( type, false, customName, typeof( NoCodeAttribute ) ) );
      List<FieldInfo> csFields = new List<FieldInfo>( DBCodeGen.GetFields( type, false, customName, typeof( NoCSCodeAttribute ) ) );

      // we need object to get default values
      ConstructorInfo defaultConstructorInfo = type.GetConstructor( System.Type.EmptyTypes );
      if ( defaultConstructorInfo == null )
      {
        Trace.TraceWarning( "Type {0} doesn't has default constructor", type.Name );
        return;
      }
      object constructedObject = type.GetConstructor( System.Type.EmptyTypes ).Invoke( new object[0] );

      // write struct to cs code
      if ( !string.IsNullOrEmpty( customName ) || !TypeUtils.HasAttribute<NoCSCodeAttribute>( type, false ) )
      {
        WriteCSFile( type, resource, customName, csCode, indent, csFields, constructedObject, addingAttributes );
      }

      if ( !string.IsNullOrEmpty( customName ) || !TypeUtils.HasAttribute<NoCodeAttribute>( type, false ) && !TypeUtils.HasAttribute<CrapTypeNameAttribute>( type, false ) )
      {
        WriteCppFile( type, resource, customName, header, code, indent, structName, needChecksum, serializerOnly, cppFields, constructedObject );
      }
    }

    #region Social
    private static void WriteCSFileForSocial( Type type, bool resource, bool inherited,
      CodeWriter csCode, int indent, List<FieldInfo> csFields )
    {
      bool hasAbstractField = false;
      foreach ( var field in csFields )
        if ( TypeUtils.HasAttribute<AbstractAttribute>( field, false ) )
        {
          hasAbstractField = true;
          break;
        }

      string adaptiveItems = String.Empty;
      bool isAdaptiveClass = AdaptiveItemsInserter.CollectAdaptiveAccessors( csFields, ref adaptiveItems );
      //nameMap attributes. If NameMap attribute declared for class - in generated code
      //class must inherit INameMap interface
      bool isNameMap = TypeUtils.HasAttribute<NameMapValueAttribute>( type, false );

      WriteCSClassHeaderForSocial( type, resource, inherited, csCode,
        indent, hasAbstractField, isAdaptiveClass, isNameMap );

      if ( isAdaptiveClass )
      {
        csCode.WriteLine( AdaptiveItemsInserter.AdaptMethodText );
        csCode.WriteLine( adaptiveItems );
      }

      if ( isNameMap )
      {
        csCode.WriteLine( NameMapItemInsterter.NameMapInterfaceImplementation );
        csCode.WriteLine();
      }

      List<FieldDef> csFieldDefs = new List<FieldDef>();

      foreach ( FieldInfo field in csFields )
      {
        csFieldDefs.Add( new FieldDef( type, field.FieldType, field ) );
      }

      foreach ( FieldDef field in csFieldDefs )
      {
        WriteCSFieldForSocial( field, csCode, indent );
      }
      csCode.WriteLine();

      foreach ( FieldDef field in csFieldDefs )
      {
        WriteCSPropertyForSocial( field, csCode, indent );
      }

      csCode.WriteLine( indent, "}" );
      csCode.WriteLine();
    }

    private static void WriteCSClassHeaderForSocial( Type type, bool resource, bool inherited,
      CodeWriter csCode, int indent, bool hasAbstractField, bool isAdaptive, bool isNameMap )
    {
      csCode.WriteLine( indent, "public {1} {2} class {0}", type.Name,
        typeof( DBResource ).IsAssignableFrom( type ) ? "partial" : string.Empty,
        hasAbstractField ? "abstract" : string.Empty
      );

      string baseTypeString = String.Empty;
      string adaptiveInterfaceName = "IAdaptiveItem";
      string nameMapInterfaceName = "INameMap";
      List<string> parents = new List<string>();

      if ( inherited )
        baseTypeString = type.BaseType.Name;
      else
        if ( resource )
          baseTypeString = "CastleDB_BaseItem";

      if ( !string.IsNullOrEmpty( baseTypeString ) )
        parents.Add( baseTypeString );
      if ( isAdaptive )
        parents.Add( adaptiveInterfaceName );
      if ( isNameMap )
        parents.Add( nameMapInterfaceName );

      if ( parents.Count > 0 )
      {
        string parentsString = " : ";
        for ( int i = 0; i < parents.Count; i++ )
          parentsString += parents[i] + ( i != parents.Count - 1 ? ", " : " " );
        csCode.WriteLine( parentsString );
      }

      csCode.WriteLine( indent, "{" );

      csCode.WriteLine();
    }

    private static void WriteCSFieldForSocial( FieldDef def, CodeWriter csCode, int indent )
    {
      //Commented by zulman because [DstFile( "dds" )] in Texture stop writing textureFileName field.
      //TypeUtils.HasAttribute<DstFileAttribute>(def.field, false) ||
      if ( TypeUtils.HasAttribute<AbstractAttribute>( def.field, false ) )
        return;

      if ( typeof( IList ).IsAssignableFrom( def.fieldType ) )
        csCode.WriteLine( indent + 1, "private {0} _{1} = new {0}();", TypesReplacement.TryToReplace( DBCodeGen.GetCSSimpleTypeName( def.fieldType ) ), def.field.Name );
      else

        csCode.WriteLine( indent + 1, "private {0} _{1};", TypesReplacement.TryToReplace( DBCodeGen.GetCSSimpleTypeName( def.fieldType ) ), def.field.Name );
    }

    private static void WriteCSPropertyForSocial( FieldDef def, CodeWriter csCode, int indent )
    {
      //property
      string fieldName = def.Name;

      bool isOverride = false;
      if ( def.ownerType.BaseType != null )
      {
        FieldInfo baseField = def.ownerType.BaseType.GetField( def.Name, BindingFlags.Public | BindingFlags.Instance | BindingFlags.DeclaredOnly );
        isOverride = baseField != null && TypeUtils.HasAttribute<AbstractAttribute>( baseField, false );
      }

      NameMapValueAttribute[] nameMapAttrs = TypeUtils.GetAttributes<NameMapValueAttribute>( def.field, false );
      foreach ( NameMapValueAttribute a in nameMapAttrs )
        if ( string.IsNullOrEmpty( a.Name ) )
        {
          a.Name = def.Name;
          a.Description = "This NameMap's Name setted automatically with field name value";
        }
      CSCode.WriteAttributes( csCode, indent + 1, nameMapAttrs );

      if ( TypeUtils.HasAttribute<AbstractAttribute>( def.field, false ) )
      {
        csCode.WriteLine( indent + 1, "public abstract {0} {1} {{ get; set; }}", TypesReplacement.TryToReplace( DBCodeGen.GetCSSimpleTypeName( def.fieldType ) ), def.field.Name );
      }
      else
      {
        csCode.WriteLine( indent + 1, "public {2}{0} {1} {{ get {{ return _{1}; }} set {{ _{1} = value; }} }}", TypesReplacement.TryToReplace( DBCodeGen.GetCSSimpleTypeName( def.fieldType ) ), def.field.Name, isOverride ? "override " : string.Empty );
      }
      csCode.WriteLine();
    }

    public static void WriteForSocial( Type type, bool resource, bool inherited, CodeWriter csCode, int indent, List<FieldInfo> fields )
    {
      string structName = DBCodeGen.GetTypeName( type );

      // write struct to cs code
      if ( !TypeUtils.HasAttribute<NoCSCodeAttribute>( type, false ) )
      {
        WriteCSFileForSocial( type, resource, inherited, csCode, indent, fields );
      }
    }
    #endregion
  }
}
