using System;
using System.Collections;
using System.Collections.Generic;
using System.Reflection;
using libdb.IO;
using libdb.Animated;
using libdb.UndoRedo;

namespace libdb.DB
{
  public static class DBConvertResourceType
  {
    public static bool CanConvert( DBID dbid, Type dstType )
    {
      if ( dbid.IsEmpty || dbid.IsInlined || !TypeUtils.IsSubclassOf( dstType, typeof( DBResource ) ) )
        return false;

      DBPtr<DBResource> resourcePtr = DataBase.Get<DBResource>( dbid );
      if ( null == resourcePtr.Get() )
        return false;

      return resourcePtr.IsBacklinkCompatible( dstType );
    }

    public static bool Convert( DBID dbid, Type dstType )
    {
      if ( !CanConvert( dbid, dstType ) )
        return false;
      DBPtr<DBResource> oldResourcePtr = DataBase.Get<DBResource>( dbid );
      DBResource oldResource = oldResourcePtr.Get();
      if ( null == oldResource )
        return false;

      using( UndoRedoTransaction trans = new UndoRedoTransaction( "DBConvertResourceType" ) )
      {
        DBResource newResource = TypeUtils.CreateInstance( dstType ) as DBResource;
        DBID tmpDbid = DBID.FromFileName( "/" + Guid.NewGuid().ToString( "N" ), false );
        DBPtr<DBResource> newResourcePtr = DataBase.Create<DBResource>( tmpDbid, newResource );
        DBCopy.Copy( newResource, oldResource );
        oldResourcePtr.RepointLinks( tmpDbid );
        DataBase.Rename( dbid, tmpDbid );
     
        trans.Commit();
      }

      return true;
    }

    public static bool ConvertWithoutCheck( DBID dbid, Type dstType )
    {
      DBPtr<DBResource> oldResourcePtr = DataBase.Get<DBResource>( dbid );
      DBResource oldResource = oldResourcePtr.Get();
      if ( null == oldResource )
        return false;

      using ( UndoRedoTransaction trans = new UndoRedoTransaction( "DBConvertResourceType" ) )
      {
        DBResource newResource = TypeUtils.CreateInstance( dstType ) as DBResource;
        DBID tmpDbid = DBID.FromFileName( "/" + Guid.NewGuid().ToString( "N" ), false );
        DBPtr<DBResource> newResourcePtr = DataBase.Create<DBResource>( tmpDbid, newResource );
        DBCopy.Copy( newResource, oldResource );
        oldResourcePtr.ClearBackLinks();
        DataBase.Rename( dbid, tmpDbid );

        trans.Commit();
      }

      return true;
    }
  }
}
