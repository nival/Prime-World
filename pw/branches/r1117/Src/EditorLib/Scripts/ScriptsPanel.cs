using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;
using EditorLib.Panels;
using libdb.Diagnostics;
using libdb.IO;

namespace EditorLib.Scripts
{
  public partial class ScriptsPanel : EditorPanel
  {
    private ScriptsConfig config = null;
    private ScriptMachine scriptMachine = null;

    public ScriptsPanel()
    {
      InitializeComponent();

      colFileName.Width = -1;//выравнивание по тексту элемента
			colFilePath.Width = -1;//выравнивание по тексту элемента
			colAbout.Width = -2;//на всю ширину

      lvScripts.SelectedIndexChanged += OnScriptsSelectedChanged;
      lvScripts.MouseDoubleClick += OnMouseDoubleClick;
    }

    private void InvalidateList()
    {
      List<string> files = new List<string>( config.scripts );
      files.Sort( ( a, b ) => string.Compare( Path.GetFileNameWithoutExtension( a ), Path.GetFileNameWithoutExtension( b ), StringComparison.InvariantCultureIgnoreCase ) );

      lvScripts.BeginUpdate();
      lvScripts.Items.Clear();

      foreach( string file in files )
      {
        FileInfo fileInfo = new FileInfo( file );
        ListViewItem lvItem = lvScripts.Items.Add( fileInfo.Name, fileInfo.Name );
        lvItem.Tag = file;
        lvItem.SubItems.Add( fileInfo.DirectoryName );
      	lvItem.SubItems.Add( GetAboutText(fileInfo.FullName) );
      }

      lvScripts.EndUpdate();
      
      UpdateToolbar();
    }

  	private static string GetAboutText(string _fileName)
  	{
			if(File.Exists(_fileName))
			{
				string[] lines = File.ReadAllLines( _fileName );

				foreach ( string s in lines )
				{
					if ( s.StartsWith( "#about " ) )
						return s.Substring( 7 ).Trim();
				}	
			}

  		return string.Empty;
  	}

  	protected override bool Initialize( IEditorWinApplication application )
    {
      config = application.Application.Settings.Get<ScriptsConfig>();
      scriptMachine = application.Application.Scripts;
      InvalidateList();
      return true;
    }

    private void OnAddClick( object sender, EventArgs e )
    {
      if ( openFileDialog.ShowDialog() != DialogResult.OK )
        return;

      string fullScriptFileName = openFileDialog.FileName;
      if ( config.scripts.Exists( fileName => string.Compare( Path.GetFullPath( fileName ), fullScriptFileName, StringComparison.InvariantCultureIgnoreCase ) == 0 ) )
      {
        Log.TraceWarning( "Script \"{0}\" already in list", openFileDialog.FileName );
        return;
      }

      string relativeScriptPath = FileUtils.GetRelativePath( Environment.CurrentDirectory, fullScriptFileName );
      if ( relativeScriptPath.StartsWith( ".." ) && !relativeScriptPath.StartsWith( ".." + FileUtils.PathSeparatorChar + ".." ) )
        fullScriptFileName = relativeScriptPath;

      config.scripts.Add( fullScriptFileName );
      InvalidateList();
    }

    private void OnRemoveClick( object sender, EventArgs e )
    {
      foreach( ListViewItem item in lvScripts.SelectedItems )
      {
        config.scripts.Remove( item.Tag as string );
      }

      InvalidateList();
    }

    private void OnScriptsSelectedChanged( object sender, EventArgs e )
    {
      UpdateToolbar();
    }

    private void UpdateToolbar()
    {
      buttonRemove.Enabled = lvScripts.SelectedItems.Count >= 0;
      buttonRun.Enabled = lvScripts.SelectedItems.Count == 1;
    }

    private void OnRunClick( object sender, EventArgs e )
    {
      Run();
    }

    private void OnMouseDoubleClick( object sender, MouseEventArgs e )
    {
      Run();
    }

    private void Run()
    {
      if(lvScripts.SelectedItems.Count == 1)
      {
        string path = lvScripts.SelectedItems[0].Tag as string;
        
        Log.Assert( !string.IsNullOrEmpty( path ), "File path can't be null or empty" );
        
        scriptMachine.LoadScript( Path.GetFullPath( path ), new string[]{} );        
      }
    }
  }
}
