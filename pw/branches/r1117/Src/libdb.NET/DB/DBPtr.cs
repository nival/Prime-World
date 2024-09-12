using System;
using System.Collections.Generic;
using System.Text;
using libdb.Diagnostics;
using System.Reflection;

namespace libdb.DB
{
  public delegate void DBPtrOperation<T>( T resource ) where T : DBResource, new();

  public class DBPtr<T> : DBPtrBase where T : DBResource, new()
  {
    public DBPtr( DBResource owner ) : base( owner ) { }
    public DBPtr( DBResource owner, DBPtr<T> resource ) : base( owner ) { Set( resource ); }
    public DBPtr( DBID dbid, T resource ) : base( dbid, resource ) { }
    public DBPtr( DBID dbid, T resource, DBResource owner ) : base( dbid, resource, owner ) { }

    public T Get() { return base.Get<T>(); }
    public T Get( string stateName ) { return base.Get<T>( stateName ); }
    public DBPtr<T1> GetPtr<T1>() where T1 : DBResource, new() { return new DBPtr<T1>( DBId, Get<T1>() ); }
    public void Set<T1>( DBPtr<T1> resource ) where T1 : DBResource, new() { base.Set( resource.DBId ); }

    public void ForAllStates( DBPtrOperation<T> operation )
    {
      foreach ( string state in GetStates() )
        operation( Get( state ) );
    }

    protected override void OnSetParent( DBPtrBase parent )
    {
      if ( parent == null && !DBID.IsNullOrEmpty( DBId ) && DBId.IsInlined )
      {
        if ( GetOwner() != null && !DBID.IsNullOrEmpty( GetOwner().DBId ) && GetOwner().DBId.FileName != DBId.FileName )
        {
          ConstructorInfo cotr = Get().GetType().GetConstructor( Type.EmptyTypes );
          if ( cotr == null )
            return;

          T res = Get();
          Set( DataBase.Create<T>( DBID.FromDBID( GetOwner().DBId, true ), cotr.Invoke( null ) as T ) );
          DBCopy.Copy( Get(), res );
        }
      }
    }

    public static implicit operator T( DBPtr<T> reference ) { return reference.Get<T>(); }
  }
}
