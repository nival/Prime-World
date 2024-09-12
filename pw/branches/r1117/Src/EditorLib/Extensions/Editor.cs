using System;
using libdb.DB;
using libdb.Diagnostics;

namespace EditorLib.Extensions
{
  public class Editor<T> : AbstractEditor where T : DBResource, new()
	{
		internal override bool InitializeInternal( DBID id, IEditorWinApplication application )
		{
			base.InitializeInternal( id, application );
			try
			{
				DBPtr<T> ptrResource = DataBase.Get<T>( id );
				return Initialize( ptrResource, application );
			}
			catch ( Exception e )
			{
				Log.TraceError( "Cannot execute editor \"{0}\" for \"{1}\". Exception {2}: {3}", ToString(), id.Name, e.ToString(), e.Message );
				return false;
			}
		}

		protected virtual bool Initialize( DBPtr<T> resource, IEditorWinApplication editor ) { return false; }
	}
}
