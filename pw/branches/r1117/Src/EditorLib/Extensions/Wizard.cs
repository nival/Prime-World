using libdb.Diagnostics;
using libdb.DB;
using libdb.UndoRedo;

namespace EditorLib.Extensions
{
  #region Resource Creation Wizard

  public enum ResourceCreationResult
	{
		Succeeded,
		Failed_UserCanceled,
		Failed_InvalidName,
		Failed_Error
  }

  public interface IResourceCreationWizard
	{
		ResourceCreationResult CreateResource( IEditorWinApplication application, DBID dbId );
	}

	public abstract class ResourceCreationWizard<TResource> : IResourceCreationWizard
		where TResource : DBResource
	{
		public ResourceCreationResult CreateResource( IEditorWinApplication application, DBID dbId )
		{
      try
      {
        using( UndoRedoTransaction trans = new UndoRedoTransaction( string.Format( "\"{0}\" object creation", typeof( TResource ) ) ) )
        {
          ResourceCreationResult result = CreateResourceInternal( application, dbId );

          if( result == ResourceCreationResult.Succeeded )
          {
            trans.Commit();
          }

          return result;
        }
      }
      catch( System.Exception e )
      {
        Log.TraceError( e.Message );
        return ResourceCreationResult.Failed_Error;
      }
		}

		protected abstract ResourceCreationResult CreateResourceInternal( IEditorWinApplication application, DBID dbId );
  }

  #endregion

  public interface IImportWizard
  {
    string FileExtension { get; }
    string FileDescription { get; }

    bool Run( IEditorWinApplication application, string fileName );
  }
}
