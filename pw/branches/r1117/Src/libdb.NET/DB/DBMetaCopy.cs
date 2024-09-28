using System;
using System.Collections;
using System.Collections.Generic;
using System.Reflection;
using libdb.IO;
using libdb.Animated;
using libdb.UndoRedo;

namespace libdb.DB
{
  // Similar to DBCopy, but works more flexibly of objects of different types
  public static class DBCopy
  {
    private class CopyContext
    {
      public bool collecting = true;
      public Dictionary<DBID, DBID> inlineMap = new Dictionary<DBID, DBID>();
    }

    private static bool CopyList( object dest, object src, ICustomAttributeProvider field, CopyContext context )
    {
      if ( dest == null || src == null )
        return false;

      Type srcItemType = TypeUtils.GetTypeFromList( src.GetType() );
      Type dstItemType = TypeUtils.GetTypeFromList( dest.GetType() );
      IEnumerable srcList = src as IEnumerable;
      IEnumerable dstList = dest as IEnumerable;
      if ( srcItemType == null || srcList == null || dstList == null || dstItemType == null )
        return false;

      PropertyInfo countProperty = TypeUtils.GetProperty( dest.GetType(), "Count" );
      PropertyInfo itemProperty = TypeUtils.GetProperty( dest.GetType(), "Item" );
      MethodInfo addMethod = TypeUtils.GetMethod( dest.GetType(), "Add", new Type[1] { dstItemType } );
      MethodInfo clearMethod = TypeUtils.GetMethod( dest.GetType(), "Clear", new Type[0] );
      if ( countProperty == null || itemProperty == null || addMethod == null )
        return false;

      if ( clearMethod != null )
        clearMethod.Invoke( dest, new object[0] );

      int count = (int)countProperty.GetValue( dest, null );
      int index = 0;

      bool useInheritance = ( src is IRichList && dest is IRichList );

      foreach ( object srcItem in srcList )
      {

        if ( TypeUtils.IsSimpleType( srcItemType ) && srcItemType == dstItemType )
        {
          if ( index < count )
            itemProperty.SetValue( dest, srcItem, new object[1] { index } );
          else
            addMethod.Invoke( dest, new object[1] { srcItem } );
        }
        else if ( TypeUtils.IsSubclassOf( srcItemType, typeof( SrcFile ) ) && TypeUtils.IsSubclassOf( dstItemType, typeof( SrcFile ) ) )
        {
          SrcFile destItem = new SrcFile();
          CopySrcFileField( srcItem as SrcFile, destItem, dest, TypeUtils.GetAttribute<SrcFileAttribute>( field, false ) );

          if ( index < count )
            itemProperty.SetValue( dest, destItem, new object[1] { index } );
          else
            addMethod.Invoke( dest, new object[1] { destItem } );
        }
        else if ( TypeUtils.IsStruct( srcItemType ) )
        {
          object destItem = null;
          if ( index < count )
            destItem = itemProperty.GetValue( dest, new object[1] { index } );
          else
          {
            destItem = TypeUtils.CreateInstance( dstItemType );
            addMethod.Invoke( dest, new object[1] { destItem } );

            count = (int)countProperty.GetValue( dest, null );
            destItem = itemProperty.GetValue( dest, new object[1] { count - 1 } );
          }
          CopyFields( destItem, srcItem, context );
        }
        else if ( TypeUtils.IsList( srcItemType ) )
        {
          object destItem = null;
          if ( index < count )
            destItem = itemProperty.GetValue( dest, new object[1] { index } );
          else
          {
            destItem = TypeUtils.CreateInstance( dstItemType );
            addMethod.Invoke( dest, new object[1] { destItem } );

            count = (int)countProperty.GetValue( dest, null );
            destItem = itemProperty.GetValue( dest, new object[1] { count - 1 } );
          }
          CopyList( destItem, srcItem, field, context );
        }
        else if ( TypeUtils.GetTypeFromPtr( srcItemType ) != null && TypeUtils.GetTypeFromPtr( dstItemType ) != null )
        {
          DBPtrBase destItem = null;
          if ( index < count )
            destItem = itemProperty.GetValue( dest, new object[1] { index } ) as DBPtrBase;
          else
          {
            destItem = TypeUtils.CreateInstance( dstItemType ) as DBPtrBase;
            addMethod.Invoke( dest, new DBPtrBase[1] { destItem } );

            count = (int)countProperty.GetValue( dest, null );
            destItem = itemProperty.GetValue( dest, new object[1] { count - 1 } ) as DBPtrBase;
          }
          CopyDBPtrSimple( destItem, srcItem as DBPtrBase, context );
        }

        count = (int)countProperty.GetValue( dest, null );
        if ( useInheritance && ( src as IRichList ).IsElementDerivedFromParent( index ) && index < count )
          ( dest as IRichList ).ResetElement( index );

        ++index;
      }

      return true;
    }

    private static DBID GetDBIDFromObject( object obj )
    {
      if ( obj == null )
        return DBID.Empty;
      if ( obj is DBResource )
        return ( obj as DBResource ).DBId;
      if ( obj is IOwnerable )
      {
        DBResource res = ( obj as IOwnerable ).GetOwner();
        if ( res != null )
          return res.DBId;
      }

      return DBID.Empty;
    }

    private static bool CopyDBPtrSimple( DBPtrBase dst, DBPtrBase src, CopyContext context )
    {
      if ( null == src || null == dst )
        return false;

			DataBase.AddOperation( new DBPtrBaseChangeOperation( dst, DBID.Empty ) );

			if ( src.DBId.IsEmpty )
        return true;

      Type srcType = TypeUtils.GetTypeFromPtr( src.GetType() );
      Type dstType = TypeUtils.GetTypeFromPtr( dst.GetType() );

      if ( TypeUtils.IsSubclassOf( srcType, dstType ) )
      {
        if ( src.DBId.IsInlined )
          CopyDBPtrProcessInline( dst, src, src.Get<DBResource>().GetType(), context );
        else
					DataBase.AddOperation( new DBPtrBaseChangeOperation( dst, src.DBId ) );
      }
      else
      {
        if ( src.DBId.IsInlined && !TypeUtils.HasAttribute<NonTerminalAttribute>( dstType, false ) )
          CopyDBPtrProcessInline( dst, src, dstType, context );
      }

      return true;
    }

    private static void CopyDBPtrProcessInline( DBPtrBase dst, DBPtrBase src, Type objType, CopyContext context )
    {
      if ( !context.collecting && context.inlineMap.ContainsKey( src.DBId ) )
      {
				DataBase.AddOperation( new DBPtrBaseChangeOperation( dst, context.inlineMap[src.DBId] ) );
        return;
      }

      DBID destDbid = DBID.FromDBID( dst.GetOwner().DBId, true );
      DBResource resource = TypeUtils.CreateInstance( objType ) as DBResource;
      DataBase.Create<DBResource>( destDbid, resource );
			DataBase.AddOperation( new DBPtrBaseChangeOperation( dst, destDbid ) );

      if ( context.collecting )
        context.inlineMap[src.DBId] = destDbid;

      CopyFields( resource, src.Get<DBResource>(), context );
    }

    private static void CopySrcFileField( SrcFile srcSrcFile, SrcFile destSrcFile, object owner, SrcFileAttribute srcFileAttr )
    {
      string destFolder = string.Empty;

      if ( srcFileAttr == null || string.IsNullOrEmpty( srcFileAttr.SourceFolder ) )
        destFolder = FileUtils.GetParentFolderPath( GetDBIDFromObject( owner ).FileName );
      else
        destFolder = srcFileAttr.SourceFolder;

      destFolder = FileUtils.PathSeparatorString + destFolder;

      destSrcFile.SetFileName( FileUtils.Combine( FileUtils.FixFolderName( destFolder ), FileUtils.GetFileName( srcSrcFile.FileName ) ) );
      destSrcFile.SetChecksum( 0 );
    }

    private static bool CopyFields( object dest, object src, CopyContext context )
    {
      if ( ReferenceEquals( dest, src ) || dest == null || src == null )
        return false;

      var srcFields = new Dictionary<string, DBFieldInfo>();
      Array.ForEach( TypeUtils.GetFields( src.GetType(), true ), field => srcFields.Add( field.Name, field ) );

      var destFields = TypeUtils.GetFields( dest.GetType(), true );

      if ( src is ICompositeDBValue && dest is ICompositeDBValue )
      {
        ICompositeDBValue srcRes = src as ICompositeDBValue;
        ICompositeDBValue dstRes = dest as ICompositeDBValue;
        if ( !srcRes.IsFieldDerivedFromParent( "__parent" ) )
        {
          foreach ( DBFieldInfo destField in destFields )
          {
            if ( destField.Name != "__parent" )
              continue;
            DBFieldInfo srcField;
            if ( srcFields.TryGetValue( destField.Name, out srcField ) )
            {
              CopySingleField( dest, src, destField, srcField, context );
              dstRes.SetParent( destField.GetValue( dest ) );
            }
            break;
          }
        }
      }

      foreach ( DBFieldInfo destField in destFields )
      {
        if ( destField.Name == "__parent" )
          continue;

        DBFieldInfo srcField;
        if ( srcFields.TryGetValue( destField.Name, out srcField ) && srcField.CanRead )
          CopySingleField( dest, src, destField, srcField, context );
      }

      if ( src is ICompositeDBValue && dest is ICompositeDBValue )
        ResetInheritedFields( dest as ICompositeDBValue, src as ICompositeDBValue, destFields, srcFields );

      return true;
    }

    private static void ResetInheritedFields( ICompositeDBValue dst, ICompositeDBValue src, 
      DBFieldInfo[] dstFields, Dictionary<string, DBFieldInfo> srcFields )
    {
      if ( ReferenceEquals( dst, src ) || dst == null || src == null )
        return;

      foreach ( DBFieldInfo dstField in dstFields )
      {
        if ( dstField.Name == "__parent" )
          continue;

        DBFieldInfo srcField;
        if ( srcFields.TryGetValue( dstField.Name, out srcField ) && srcField.CanRead )
        {
          if ( src.IsFieldDerivedFromParent( dstField.Name ) && dstField.CanWrite )
            dst.ResetField( dstField.Name );
        }
      }
    }

    private static void CopySingleField( object dest, object src, DBFieldInfo destField, DBFieldInfo srcField, CopyContext context )
    {
      if ( destField.FieldType == typeof( SrcFile ) )
      {
        CopySrcFileField( (SrcFile)srcField.GetValue( src ), (SrcFile)destField.GetValue( dest ), dest, TypeUtils.GetAttribute<SrcFileAttribute>( srcField, false ) );
      }
      else if ( TypeUtils.IsSubclassOf( destField.FieldType, typeof( IAnimated ) ) )
      {
        MethodInfo assign = TypeUtils.GetMethod( destField.FieldType, "Assign", new Type[] { destField.FieldType } );
        if ( assign != null )
        {
          assign.Invoke( destField.GetValue( dest ), new object[] { srcField.GetValue( src ) } );
        }
      }
      else if ( TypeUtils.IsSubclassOf( destField.FieldType, typeof( TextRef ) ) )
      {
          (destField.GetValue(dest) as TextRef).AssignReCreateFileName(srcField.GetValue(src) as TextRef, new FieldPath().Push(dest, destField));
      }
      else if ( TypeUtils.IsStruct( destField.FieldType ) )
      {
        CopyFields( destField.GetValue( dest ), srcField.GetValue( src ), context );
      }
      else if ( TypeUtils.IsList( destField.FieldType ) )
      {
        CopyList( destField.GetValue( dest ), srcField.GetValue( src ), srcField, context );
      }
      else if ( TypeUtils.GetTypeFromPtr( destField.FieldType ) != null )
      {
        CopyDBPtrSimple( destField.GetValue( dest ) as DBPtrBase, srcField.GetValue( src ) as DBPtrBase, context );
      }
      else if ( TypeUtils.IsSubclassOf( destField.FieldType, typeof( TextRef ) ) )
      {
        ( destField.GetValue( dest ) as TextRef ).Assign( srcField.GetValue( src ) as TextRef );
      }
      else if ( TypeUtils.IsSimpleType( destField.FieldType ) )
      {
        if ( destField.CanWrite && destField.FieldType == srcField.FieldType )
        {
          destField.SetValue( dest, srcField.GetValue( src ) );
        }

        if ( TypeUtils.GetAttribute<DstFileAttribute>( destField, true ) != null && destField.FieldType == typeof( string ) )
        {
          FileUtils.CopyFile( DataBase.FileSystem, (string)srcField.GetValue( src ), (string)destField.GetValue( dest ) );
        }
      }
      else
      {
        // Do nothing.
      }
    }

    private static bool CopyStates( DBResource dst, DBResource src, CopyContext context )
    {
      if ( null == src || null == dst )
        return false;

      DBPtr<DBResource> srcPtr = DataBase.Get<DBResource>( src.DBId );
      DBPtr<DBResource> dstPtr = DataBase.Get<DBResource>( dst.DBId );

      if ( !srcPtr.IsValid || !dstPtr.IsValid )
        return false;

      List<string> dstStates = dstPtr.GetStates();
      foreach ( string stateName in dstStates )
      {
        if ( !string.IsNullOrEmpty( stateName ) )
          dstPtr.RemoveState( stateName );
      }

      List<string> srcStates = srcPtr.GetStates();
      foreach ( string stateName in srcStates )
      {
        if ( string.IsNullOrEmpty( stateName ) )
          continue;

        dstPtr.AddState( stateName );

        DBResource srcState = srcPtr.Get( stateName );
        DBResource dstState = dstPtr.Get( stateName );
        if ( !CopyFields( dstState, srcState, context ) )
          return false;

        dstState.SetParent( dstPtr.Get() );
      }

      return true;
    }

    public static bool Copy( object dest, object src )
    {
      using( UndoRedoTransaction trans = new UndoRedoTransaction( "DBMetaCopy" ) )
      {
        CopyContext context = new CopyContext();
        bool result = CopyFields( dest, src, context );

        if( TypeUtils.GetAttribute<HasStatesAttribute>( src.GetType(), true ) != null && TypeUtils.GetAttribute<HasStatesAttribute>( dest.GetType(), true ) != null )
        {
          context.collecting = false;
          result &= CopyStates( dest as DBResource, src as DBResource, context );
        }

        if( result )
          trans.Commit();
        else
          trans.Cancel();
        
        return result;
      }
    }
  }
}
