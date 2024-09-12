using System.Collections.Generic;
using System.Windows.Forms;
using EditorLib;

namespace EditorPlugins.Commands.UndoRedo
{
  public partial class BrowseUndoRedoForm : Form
  {
    private readonly IEditorWinApplication application;
    private int historySize;
    private int starts;
    private int commits;
    
    public BrowseUndoRedoForm( IEditorWinApplication _application )
    {
      InitializeComponent();
      application = _application;
    }

    private void FillHistory()
    {
      List<string> history = application.Application.UndoRedo.GetOperationHistory( 0 );
      
      foreach( string item in history )
      {
        lstHistory.Items.Add( item );
      }

      historySize = history.Count;
    }

    private void FillTrace()
    {
      lstUndoRedoTrace.Items.Clear();

      string[] trace = application.Application.UndoRedo.GetCommandsTrace();
      lstUndoRedoTrace.Items.AddRange( trace );

      starts = 0;
      commits = 0;

      foreach(string str in trace)
      {
        if( str.StartsWith( "start: " ) )
          starts++;
        else if( str.StartsWith( "commit: " ) )
          commits++;
      }
      
      if( lstUndoRedoTrace.Items.Count > 0)
        lstUndoRedoTrace.SelectedIndex = lstUndoRedoTrace.Items.Count - 1;
    }

    private void ClearTrace()
    {
      application.Application.UndoRedo.ClearCommandsTrace();
      lstUndoRedoTrace.Items.Clear();
      starts = 0;
      commits = 0;
      lblStstistic.Text = string.Format( "{0} starts {1} commits", starts, commits );
    }

    private void OnSelectedTabChanged( object sender, System.EventArgs e )
    {
      if(tabsContainer.SelectedTab == tabHistory)
      {
        lblStstistic.Text = string.Format( "{0} operations", historySize );
      }
      else if(tabsContainer.SelectedTab == tabTrace)
      {
        lblStstistic.Text = string.Format( "{0} starts {1} commits", starts, commits );
      }
    }

    private void BrowseUndoRedoForm_Load( object sender, System.EventArgs e )
    {
      FillHistory();
      FillTrace();
      lblStstistic.Text = string.Format( "{0} operations", historySize );
    }

    private void btnClearTrace_Click( object sender, System.EventArgs e )
    {
      ClearTrace();
    }
  }
}
