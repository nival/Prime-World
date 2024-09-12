using System;
using System.Collections.Generic;
using System.Text;
using libdb.DB;

namespace EditorLib.IO
{
  public static class ObjectsWalker
  {
    public delegate bool VisitObject( DBResource obj );
    public delegate bool DepthFolderController( string parent, string folder, int level );

    private static Dictionary<Type, bool> CollectTypes( IEnumerable<KeyValuePair<Type, bool>> types )
    {
      List<Type> lookForDeiven = new List<Type>();
      Dictionary<Type, bool> result = new Dictionary<Type, bool>();
      foreach ( KeyValuePair<Type, bool> type in types )
      {
        if ( !result.ContainsKey( type.Key ) )
        {
          result.Add( type.Key, true );
          if ( type.Value )
            lookForDeiven.Add( type.Key );
        }
      }

      foreach ( Type type in DataBase.KnownResources )
      {
        foreach ( Type parentType in lookForDeiven )
        {
          if ( TypeUtils.IsSubclassOf( type, parentType ) && type != parentType && !result.ContainsKey( type ) )
            result.Add( type, true );
        }
      }

      return result;
    }

    //private static bool VisitInlined( DBResource resource, Dictionary<Type, bool> typesLookup, VisitObject visitor )
    //{
    //  FieldsWalker.VisitFields<DBPtrBase>( resource,
    //    ( ref DBPtrBase ptr ) =>
    //    {
    //      if ( ptr == null || ptr.Get<DBResource>() == null || !typesLookup.ContainsKey( ptr.Get<DBResource>().GetType() ) )
    //        return true;

    //      return visitor( ptr.Get<DBResource>() );
    //    },
    //    new FieldsWalker.DepthController( 0, FieldsWalker.ObjectType.DBPtrUninlined, FieldsWalker.ObjectType.All ).Functor );

    //  return true;
    //}

    //private static bool VisitStates( DBPtr<DBResource> ptr, Dictionary<Type, bool> typesLookup, VisitObject visitor )
    //{
    //  foreach ( string state in ptr.GetStates() )
    //  {
    //    DBResource resource = ptr.Get( state );
    //    if ( !visitor( resource ) )
    //      return false;
    //    if ( VisitInlined( resource, typesLookup, visitor ) )
    //      return false;
    //  }

    //  return true;
    //}

    public static bool VisitObjects( ObjectsFolder folder, bool recursive, IEnumerable<KeyValuePair<Type, bool>> types, VisitObject visitor, DepthFolderController depth )
    {
      Dictionary<Type, bool> typesLookup = CollectTypes( types );
      Queue<KeyValuePair<ObjectsFolder, int>> folders = new Queue<KeyValuePair<ObjectsFolder, int>>();
      folders.Enqueue( new KeyValuePair<ObjectsFolder, int>( folder, 0 ) );
      while ( folders.Count > 0 )
      {
        KeyValuePair<ObjectsFolder, int> current = folders.Dequeue();

        foreach ( ObjectsFolder subFolder in current.Key.Folders )
        {
          if ( depth( current.Key.Name, subFolder.Name, current.Value + 1 ) )
            folders.Enqueue( new KeyValuePair<ObjectsFolder, int>( subFolder, current.Value + 1 ) );
        }

        foreach ( DBID item in current.Key.Items )
        {
          DBPtr<DBResource> ptr = DataBase.Get<DBResource>( item );
          if ( ptr == null || ptr.Get() == null || !typesLookup.ContainsKey( ptr.Get().GetType() ) )
            continue;
          //if ( !VisitStates( ptr, visitor ) )
          //  return false;
        }
      }

      return true;
    }
  }
}
