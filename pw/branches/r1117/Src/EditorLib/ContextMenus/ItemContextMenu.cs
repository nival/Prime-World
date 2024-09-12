using System;
using System.Collections.Generic;
using System.Windows.Forms;
using EditorLib.PropertiesEditor;
using libdb;
using libdb.DB;
using EditorLib.Extensions;
using EditorLib.ObjectsBrowser;

namespace EditorLib.ContextMenus
{
	public sealed class ItemContextMenu
	{
		private IEditorWinApplication application;

    private class AdditionalEditorEntry
    {
      public Type editorType;
      public DBID id;
    }

		public ItemContextMenu( IEditorWinApplication application ) { this.application = application; }

		private static MenuItem AddContextMenuItem( ContextMenu menu, string caption, EventHandler handler, object tag, bool enabled )
		{
			MenuItem result = menu.MenuItems.Add( caption, handler );
			result.Tag = tag;
			result.Enabled = enabled;

			return result;
		}

		private static void AddContextMenuSeparator( ContextMenu menu )
		{
			menu.MenuItems.Add( "-" );
		}

		public ContextMenu CreateContextMenu( object _selectedObject, DBResource owner)
		{
			ContextMenu menu = new ContextMenu();
      object selectedObject = _selectedObject;
      if (selectedObject is DBPtrBase)
      {
        selectedObject = (selectedObject as DBPtrBase).Get<DBResource>();
      }
			if ( selectedObject is DBResource )
			{
				DBResource resource = (selectedObject as DBResource);
				DBID id = resource.DBId;
				if ( !ReferenceEquals( resource, null ) )
				{
					Type resourseType = resource.GetType();

					AddContextMenuItem( menu, "Open", OpenDefaultEditor, id, application.Application.Extensions.GetEditorsCount( resourseType ) > 0 );
          CheckAdditionalEditors( menu, resource );
					AddContextMenuSeparator( menu );
					AddContextMenuItem( menu, "Import", Import, id, application.Application.Extensions.HasImporter( resourseType ) );
					AddContextMenuItem( menu, "Import Fast", ImportFast, id, application.Application.Extensions.HasImporter( resourseType ) );
					AddContextMenuItem( menu, "Check ...", Check, id, application.Application.Extensions.HasCheckers( resourseType ) );
          AddContextMenuItem( menu, "Recursive Import...", RecursiveImport, resource, true );
          AddContextMenuSeparator( menu );

					if ( id.IsInlined )
					{
						AddContextMenuItem( menu, "Uninline", Uninline, DataBase.Get<DBResource>( id, owner ), true );
					}
					else
					{
						AddContextMenuItem( menu, "Inline", Inline, DataBase.Get<DBResource>( id ), DataBase.Get<DBResource>( id ).CanInline() );
            if ( _selectedObject is DBPtrBase && owner != null )
              AddContextMenuItem( menu, "Inline child", InlineChild, _selectedObject as DBPtrBase, true );
          }

					AddContextMenuItem( menu, "Show backlinks ...", ShowBacklinks, DataBase.Get<DBResource>( id ), true );
				}
				else
				{
					AddContextMenuItem( menu, string.Format( "Cannot load \"{0}\"", id.Name ), null, null, false );
				}
			}
			else
			{
				if ( selectedObject is IOwnerable )
				{
					if ( menu.MenuItems.Count > 0 )
						AddContextMenuSeparator( menu );
					IOwnerable ownerable = selectedObject as IOwnerable;
          if ( ownerable != null && ownerable.GetOwner() != null )
          {
            AddContextMenuItem( menu, "Import", ImportStruct, ownerable, application.Application.Extensions.HasImporter( ownerable.GetOwner().GetType(), ownerable.GetType() ) );
            AddContextMenuItem( menu, "Import Fast", ImportStructFast, ownerable, application.Application.Extensions.HasImporter( ownerable.GetOwner().GetType(), ownerable.GetType() ) );
            AddContextMenuItem( menu, "Recursive Import...", RecursiveImport, ownerable.GetOwner(), true );
          }
        }
			}
			
			return menu;
		}

    private void CheckAdditionalEditors( ContextMenu menu, DBResource resource )
    {
      Type resourceType = resource.GetType();
      if ( application.Application.Extensions.GetEditorsCount( resourceType ) < 2 )
        return;

      List<Type> editorTypes = application.Application.Extensions.GetEditorTypes( resource );
      foreach ( Type item in editorTypes )
      {
        EditorAttribute attr = TypeUtils.GetAttribute<EditorAttribute>( item, true );
        if ( null == attr || attr.isDefault )
          continue;

        AdditionalEditorEntry info = new AdditionalEditorEntry();
        info.editorType = item;
        info.id = resource.DBId;
        string caption = "Open with " + attr.name;

        MenuItem result = menu.MenuItems.Add( caption, OpenAdditionalEditor );
        result.Tag = info;
        result.Enabled = true;
      }
    }

    private void OpenAdditionalEditor( object sender, EventArgs e )
    {
      MenuItem item = sender as MenuItem;
      if ( item == null )
        return;

      AdditionalEditorEntry info = item.Tag as AdditionalEditorEntry;
      if ( null == info )
        return;

      application.Application.Extensions.OpenEditor( info.id, application, info.editorType, false );
      application.Application.Settings.Get<FolderBookmarks>().RegisterOpenObject( info.id );
    }

		private void ShowBacklinks( object sender, EventArgs e )
		{
			MenuItem item = sender as MenuItem;
			if ( item == null )
				return;

			DBPtrBase ptr = item.Tag as DBPtrBase;
			if ( ptr != null )
			{
				Dictionary<DBID, int> links;
				Dictionary<DBID, int> backlinks;
				ptr.CollectLinks( out links, out backlinks );
				BacklinksInfo.BacklinksInfo info = new BacklinksInfo.BacklinksInfo( application, ptr.DBId, backlinks );
				application.Panels.Add( info );
			}
		}

		private void Inline( object sender, EventArgs e )
		{
			MenuItem item = sender as MenuItem;
			if ( item == null )
				return;

			DBPtrBase ptr = item.Tag as DBPtrBase;
			if ( ptr != null )
			{
				DataBase.Inline( ptr.DBId );
				//ptr.Inline();
				PropertiesEditorPanel propertiesEditor = application.Panels.GetSingletonPanel<PropertiesEditorPanel>();
				if ( propertiesEditor != null )
					propertiesEditor.RefreshView(true);
			}
		}
		private void InlineChild( object sender, EventArgs e )
		{
			MenuItem item = sender as MenuItem;
			if ( item == null )
				return;

			DBPtrBase ptr = item.Tag as DBPtrBase;
      if ( ptr == null )
        return;

      DBResource owner = ptr.GetOwner();
      DBResource res = ptr.Get<DBResource>();

      Type resType = res.GetType();

      libdb.UndoRedo.UndoRedoTransaction trans = new libdb.UndoRedo.UndoRedoTransaction( "Inline child" );
      DBPtr<DBResource> newDbPtr = DataBase.Create<DBResource>( DBID.FromDBID( owner.DBId, true ), (DBResource)resType.GetConstructor( Type.EmptyTypes ).Invoke( null ) );

      DataBase.AddOperation( new libdb.UndoRedo.DBPtrBaseChangeOperation( ptr, newDbPtr.DBId ) );
      newDbPtr.Get().SetParent( res );

      trans.Commit();

			PropertiesEditorPanel propertiesEditor = application.Panels.GetSingletonPanel<PropertiesEditorPanel>();
			if ( propertiesEditor != null )
				propertiesEditor.RefreshView(true);
		}

		private void Uninline( object sender, EventArgs e )
		{
			MenuItem item = sender as MenuItem;
			if ( item == null )
				return;

			DBPtrBase ptr = item.Tag as DBPtrBase;
			if ( ptr != null )
			{
				UninlineFileAsker dialog = new UninlineFileAsker( ptr.DBId, ptr.Get<DBResource>().GetType() );

				if(dialog.ShowDialog() == DialogResult.OK)
				{
					DBID newDbId = DBID.FromFileName(dialog.FileName, false);
					DataBase.Uninline( ptr.DBId,  newDbId);

					PropertiesEditorPanel propertiesEditor = application.Panels.GetSingletonPanel<PropertiesEditorPanel>();
					if ( propertiesEditor != null )
						propertiesEditor.RefreshView(true);	
				}
			}
		}

		private void OpenDefaultEditor( object sender, EventArgs e )
		{
			MenuItem item = sender as MenuItem;
			if ( item == null )
				return;

			DBID dbid = item.Tag as DBID;
			application.Application.Extensions.OpenEditor( dbid, application, null, false );
      application.Application.Settings.Get<FolderBookmarks>().RegisterOpenObject( dbid );
    }

		private void Import( object sender, EventArgs e )
		{
			MenuItem item = sender as MenuItem;
			if ( item == null )
				return;

			DBID dbid = item.Tag as DBID;
			application.Application.Extensions.Import( dbid, application.Application, false );
		}

		// CRAP {
		private void ImportFast( object sender, EventArgs e )
		{
			MenuItem item = sender as MenuItem;
			if ( item == null )
				return;

			DBID dbid = item.Tag as DBID;
			application.Application.Extensions.Import( dbid, application.Application, true );
		}
		// CRAP }

		private void ImportStruct( object sender, EventArgs e )
		{
			if ( sender is MenuItem )
			{
				var item = (MenuItem)sender;
				if ( item.Tag != null && item.Tag is IOwnerable )
				{
					application.Application.Extensions.Import( item.Tag as IOwnerable, application.Application, false );
				}
			}
		}

		private void ImportStructFast( object sender, EventArgs e )
		{
			if ( sender is MenuItem )
			{
				var item = (MenuItem)sender;
				if ( item.Tag != null && item.Tag is IOwnerable )
				{
					application.Application.Extensions.Import( item.Tag as IOwnerable, application.Application, true );
				}
			}
		}

    private void RecursiveImport( object sender, EventArgs e )
    {
      MenuItem item = sender as MenuItem;
      if ( item == null )
        return;

      DBResource res = item.Tag as DBResource;
      if ( res != null )
      {
        ImportRecursive form = new ImportRecursive( res );
        form.ShowDialog();
      }
    }

		private void Check( object sender, EventArgs e )
		{
			MenuItem item = sender as MenuItem;
			if ( item == null )
				return;

			DBID dbid = item.Tag as DBID;
			application.Application.Extensions.Check( dbid, application.Application, false );
		}
	}
}
