using System;
using System.Collections.Generic;
using EditorLib.Operations;
using libdb;
using libdb.DB;
using libdb.Diagnostics;

namespace EditorLib.Extensions
{
  public interface IImporter
  {
    void Initialize( DBID id, IEditorCommonApplication application, bool fast );
    bool Import( IOperationContext context );
  }

  public abstract class Importer<T> : IImporter
    where T : DBResource, new()
  {
    private IOperationContext context = null;
    private DBPtr<T> resource = null;
    private IEditorCommonApplication application = null;
    private bool fast = false;

    protected IOperationContext Context { get { return context; } }

    public void Initialize( DBID id, IEditorCommonApplication application, bool fast )
    {
      resource = DataBase.Get<T>( id );
      if ( ReferenceEquals( resource, null ) )
      {
        Log.TraceError( "Import of \"{0}\" resource \"{1}\" failed", 
                        id.IsInlined ? "inlined" : "",
                        DBID.FromDBID( id, false ).Name );

        return;
      }

      this.application = application;
      this.fast = fast;
    }

    private class CollectImportersForStructs
    {
      private List<IStructImporter> importers = new List<IStructImporter>();

      private IEditorCommonApplication application = null;
      private bool fast = false;
      private Dictionary<Type, bool> subTypes = new Dictionary<Type, bool>();

      private bool Visit( ref object obj, DBFieldInfo field )
      {
        IOwnerable ownerable = obj as IOwnerable;
        if ( ownerable != null && subTypes.ContainsKey( obj.GetType() ) )
          importers.Add( application.Extensions.CreateImporter( ownerable, application, fast ) );

        return true;
      }

      public bool Collect( T resource, IEditorCommonApplication application, bool fast )
      {
        subTypes.Clear();
        this.application = application;
        this.fast = fast;
        Type[] _subTypes = application.Extensions.GetStructImporters( typeof( T ) );
        foreach ( Type subType in _subTypes )
          subTypes.Add( subType, false );

        importers.Clear();
        FieldsWalker.DepthController depthController = new FieldsWalker.DepthController( 0, FieldsWalker.ObjectType.DBPtr, FieldsWalker.ObjectType.All );
        FieldsWalker.VisitFields( resource, Visit, depthController.Functor );

        return importers.Count > 0;
      }

      public void DoImport( IOperationContext context )
      {
        foreach ( IStructImporter importer in importers )
          importer.Import( context );
      }
    }

    private void ImportSubStructures()
    {
      CollectImportersForStructs importers = new Importer<T>.CollectImportersForStructs();
      if ( !importers.Collect( resource.Get(), application, fast ) )
        return;

      importers.DoImport( context );
    }

    public bool Import( IOperationContext _context )
    {     
      try
      {
        if( _context == null )
        {
          _context = new NullOperationContext();
        }

        context = _context;
        context.Start( KnownDuration, true );

        application.UndoRedo.Start( "Importer.cs: " + GetType().Name );
              
        int startTime = Environment.TickCount;

        if( Process( resource, application, fast ) )
        {
          ImportSubStructures();
          
          Log.TraceMessage( "Import of \"{0}\" resource \"{1}\" succeded in \"{2}\" ms",
                resource.DBId.IsInlined ? "inlined" : "",
                DBID.FromDBID( resource.DBId, false ).Name,
                Environment.TickCount - startTime );

          application.UndoRedo.Commit();

          if( !DataBase.UndoRedoManager.IsCommandStarted )
            DataBase.ChangeCallback( resource.DBId );

          return true;
        }

        Log.TraceError( "Import of \"{0}\" resource \"{1}\" failed",
                        resource.DBId.IsInlined ? "inlined" : "",
                        DBID.FromDBID( resource.DBId, false ).Name );

      }
      catch ( Exception err )
      {
        Log.TraceError( "Import of \"{0}\" resource \"{1}\" failed. Exception {2}: {3}",
                resource.DBId.IsInlined ? "inlined" : "",
                DBID.FromDBID( resource.DBId, false ).Name, 
                err.ToString(), 
                err.Message );
      }

      if( application.UndoRedo.IsCommandStarted )
        application.UndoRedo.Cancel();  

      return false;
    }

    protected void Progress( string message ) { context.Progress( message ); }
    protected void Progress( string message, int progress ) { context.Progress( message, progress ); }

    protected abstract bool KnownDuration { get; }
    protected abstract bool Process( DBPtr<T> resource, IEditorCommonApplication application, bool fast );
  }

  public class NullOperationContext : IOperationContext
  {
    public void Start( bool knownDuration, bool blockInterface )
    {
    }

    public void Progress( string message )
    {
      if(!String.IsNullOrEmpty( message ))
        Log.TraceMessage( message );
    }

    public void Progress( string message, int progress )
    {
      if( !String.IsNullOrEmpty( message ) )
        Log.TraceMessage( "{0} [{1}%]", message, progress );
    }
  }
}
