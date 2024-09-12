using System;
using System.Collections.Generic;
using libdb.DB;

namespace EditorLib.Extensions
{
  public static class EditorsPool
  {
    private static readonly Dictionary<DBID, AbstractEditor> poolForInstances = new Dictionary<DBID, AbstractEditor>();
    private static readonly Dictionary<Guid, AbstractEditor> poolForTypes = new Dictionary<Guid, AbstractEditor>();

    public static AbstractEditor GetEditorForObject( DBID id )
    {
      AbstractEditor val = null;
      poolForInstances.TryGetValue( id, out val );
      return val;
    }

    public static AbstractEditor GetEditorByType( Guid guid )
    {
      AbstractEditor val = null;
      poolForTypes.TryGetValue( guid, out val );
      return val;
    }

    public static void RegisterEditor( DBID id, AbstractEditor editor )
    {
      poolForInstances.Add( id, editor );

      EditorAttribute editorAttr = TypeUtils.GetAttribute<EditorAttribute>( editor.GetType(), true );
      if ( editorAttr.guid != Guid.Empty && !poolForTypes.ContainsKey( editorAttr.guid ) )
        poolForTypes.Add( editorAttr.guid, editor );
    }

    public static void UnregisterEditor( DBID id, AbstractEditor editor )
    {
      poolForInstances.Remove( id );
      EditorAttribute editorAttr = TypeUtils.GetAttribute<EditorAttribute>( editor.GetType(), true );
      if ( editorAttr.guid != Guid.Empty )
        poolForTypes.Remove( editorAttr.guid );
    }

    static Type GetType( DBID id )
    {
      DBResource r = DataBase.Get<DBResource>( id ).Get();
      return r.GetType();
    }

    public static IEnumerable<AbstractEditor> GetAllEditors() { return poolForTypes.Values; }

    public static IEnumerable<AbstractEditor> GetAllEditorInstances() { return poolForInstances.Values; }

    public static int Count { get { return poolForInstances.Count; } }
  }
}
