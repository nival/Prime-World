using System.Collections.Generic;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using libdb.DB;

namespace EditorPlugins.Console
{
  public abstract class TypeConverterAbstractCommand<TOld, TNew> : IConsoleCommand
    where TOld : DBResource, new()
    where TNew : DBResource, new()
	{
		public int Execute( IEditorCommonApplication application, string[] parameters )
		{
			List<DBID> items;
			ObjectsSelector.CollectObjects( application, "", typeof( TOld ), true, false, out items );

			foreach ( var dbId in items )
			{
				DBPtr<TOld> oldResource = DataBase.Get<TOld>( dbId );
				if ( !ReferenceEquals( oldResource, null ) )
				{
					TNew newResource;
					if ( Convert( application, oldResource, out newResource ) )
					{
						DataBase.ChangeResource( dbId, newResource );
					}
					else
					{
						application.UndoRedo.Undo();
						DataBase.ClearModified();
						break;
					}
				}
			}

			DataBase.Store();
      return 0;
		}

    protected abstract bool Convert( IEditorCommonApplication application, DBPtr<TOld> oldResource, out TNew newResource );
	}
}
