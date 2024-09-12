using System;
using EditorLib.Operations;
using libdb;
using libdb.DB;
using libdb.Diagnostics;

namespace EditorLib.Extensions
{
  public interface IStructImporter
  {
    void Initialize( IOwnerable resource, IEditorCommonApplication application, bool fast );
    bool Import( IOperationContext context );
  }

  public abstract class StructImporter<TOwner, TStruct> : IStructImporter
    where TOwner : DBResource, new()
    where TStruct : class, IOwnerable
  {
    private IOperationContext context = null;
    private DBPtr<TOwner> owner = null;
    private TStruct resource = null;
    private IEditorCommonApplication application = null;
    private bool fast = false;

    protected IOperationContext Context { get { return context; } }

    public void Initialize( IOwnerable _resource, IEditorCommonApplication application, bool fast )
    {
      if( !( _resource is TStruct ) )
      {
        Log.TraceError( "Struct importer \"{0}\" failed. Struct in not of type \"{1}\"", GetType().ToString(), typeof( TStruct ).Name );
        return;
      }

      resource = (TStruct)_resource;
      if( ReferenceEquals( _resource.GetOwner(), null ) )
      {
        Log.TraceError( "Struct importer \"{0}\" failed. Owner not defined", GetType().ToString() );
        return;
      }

      owner = DataBase.Get<TOwner>( _resource.GetOwner().DBId );
      if( ReferenceEquals( _resource.GetOwner(), null ) )
      {
        Log.TraceError( "Struct importer \"{0}\" failed. Cannot load owner \"{1}\" or owner is not of type \"{2}\"", GetType().ToString(), _resource.GetOwner().DBId.Name, typeof( TOwner ).Name );
        return;
      }

      this.application = application;
      this.fast = fast;
    }

    public bool Import( IOperationContext context )
    {
      if( context == null )
      {
        context = new NullOperationContext();
      }
      
      this.context = context;
      this.context.Start( KnownDuration, true );
      application.UndoRedo.Start( "StructImporter.cs: " + GetType().Name );
      try
      {
        int startTime = Environment.TickCount;

        if( Process( resource, owner, application, fast ))
        {
          Log.TraceMessage( "Import of struct \"{0}\" from {1} resource \"{2}\" succeded in \"{3}\" ms",
              resource.GetType().Name,
              owner.DBId.IsInlined ? "inlined" : "",
              DBID.FromDBID( owner.DBId, false ).Name,
              Environment.TickCount - startTime ); 

          application.UndoRedo.Commit();
          
          if(!DataBase.UndoRedoManager.IsCommandStarted)
            DataBase.ChangeCallback( owner.DBId );

          return true;
        }

        Log.TraceError( "Import of struct \"{0}\" from {1} resource \"{2}\" failed", 
                      resource.GetType().Name, 
                      owner.DBId.IsInlined ? "inlined" : "", 
                      DBID.FromDBID( owner.DBId, false ).Name );       
      }
      catch( Exception e )
      {
        Log.TraceError( "Import of struct \"{0}\" from {1} resource \"{2}\" failed. Exception {3}: {4}",
              resource.GetType().Name,
              owner.DBId.IsInlined ? "inlined" : "",
              DBID.FromDBID( owner.DBId, false ).Name, 
              e.ToString(), 
              e.Message );   
      }

      if( application.UndoRedo.IsCommandStarted )
        application.UndoRedo.Cancel();  

      return false;
    }

    protected void Progress( string message ) { context.Progress( message ); }
    protected void Progress( string message, int progress ) { context.Progress( message, progress ); }

    protected abstract bool KnownDuration { get; }
    protected abstract bool Process( TStruct importStruct, DBPtr<TOwner> resource, IEditorCommonApplication application, bool fast );
  }
}
