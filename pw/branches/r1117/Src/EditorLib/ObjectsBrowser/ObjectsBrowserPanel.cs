using EditorLib.IO;
using EditorLib.Panels;
using EditorLib.PropertiesEditor;
using libdb.DB;

namespace EditorLib.ObjectsBrowser
{
	public partial class ObjectsBrowserPanel : EditorPanel
	{
    internal delegate void ChangeSelectedFolderEventHandler( ObjectsBrowserPanel panel, ObjectsFolder folder );
    internal event ChangeSelectedFolderEventHandler ChangeSelectedFolderEvent = null;
    public delegate void ChangeSelectedItemEventHandler( ObjectsBrowserPanel panel, DBID item );
    public event ChangeSelectedItemEventHandler ChangeSelectedItemEvent = null;

    public string CurrentFolder
		{
			get { return objectsBrowser.CurrentFolder; }
			set { objectsBrowser.CurrentFolder = value; }
		}

		public ObjectsBrowserPanel()
		{
			InitializeComponent();

      objectsBrowser.ChangeSelectedFolderEvent += OnChangeSelectedFolder;
      objectsBrowser.ChangeSelectedItemEvent += OnChangeSelectedItem;

		}

    private void OnChangeSelectedFolder( ObjectsBrowser control, ObjectsFolder folder )
    {
      if( ChangeSelectedFolderEvent != null )
        ChangeSelectedFolderEvent( this, folder );
    }

    private void OnChangeSelectedItem( ObjectsBrowser coltrol, DBID dbid )
    {
      if( ChangeSelectedItemEvent != null )
        ChangeSelectedItemEvent( this, dbid );

      application.Panels.GetSingletonPanel<PropertiesEditorPanel>().SelectedObject =
                      DBID.IsNullOrEmpty( dbid ) ? null : DataBase.Get<DBResource>( dbid ).Get();
    }

		protected override bool Initialize( IEditorWinApplication app )
		{
			return true;
		}

		public override void Terminate( IEditorWinApplication app )
		{
			return;
		}

    public DBID SelectedObject()
    {
      return objectsBrowser.SelectedObject;
    }

		public void SelectItem( DBID dbid )
		{
		  objectsBrowser.SelectItem(dbid);
		}

    public void ReselectCurrentItem()
    {
      objectsBrowser.ReselectCurrentItem();
    }

		public void Reset()
		{
			objectsBrowser.Reset();
		}

    private void OnOpenItem( object sender, DBIDEventArgs args )
    {
      DBResource resource = DataBase.Get<DBResource>( args.dbid ).Get();
      if( ReferenceEquals( resource, null ) )
        return;

      if( EditorCommonApplication.ApplicationSingleton.Extensions.GetEditorsCount( resource.GetType() ) > 0 )
        EditorCommonApplication.ApplicationSingleton.Extensions.OpenEditor( args.dbid, application, null, args.newInstance );
    }

	}
}