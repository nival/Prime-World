using System;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using EditorLib.Panels;
using libdb.Diagnostics;
using EditorLib.Utils;

namespace EditorLib.OutputPanel
{
	public partial class OutputPanel : EditorPanel
	{
		private static OutputTraceListener traceListener = null;
		private readonly int[] counts = new int[3] { 0, 0, 0 };
		private readonly bool[] filter = new bool[3] { true, true, true };

		public static void InitializeTraceListener()
		{
			if ( traceListener != null )
				return;
			traceListener = new OutputTraceListener();
			Log.AttachDumper( traceListener );
		}

		public OutputPanel() 
		{
			InitializeComponent();

			headerMessage.Width = -2;

			listView.SmallImageList = new ImageList();
			listView.SmallImageList.Images.Add( EditorLibResources.errorA );
			listView.SmallImageList.Images.Add( EditorLibResources.warningA );
			listView.SmallImageList.Images.Add( EditorLibResources.infoA );
			listView.SmallImageList.ImageSize = EditorLibResources.errorA.Size;

			buttonErrors.Tag = 0;
			buttonWarnings.Tag = 1;
			buttonMessages.Tag = 2;
		}

		private int GetLogLevelIndex( Log.Level level )
		{
			switch ( level )
			{
			case Log.Level.Error:
      case Log.Level.Assert:
				return 0;
			case Log.Level.Warning:
				return 1;
			case Log.Level.Information:
				return 2;
			default:
				return -1;
			}
		}

		protected override void OnClientSizeChanged( EventArgs e )
		{
			base.OnClientSizeChanged( e );
			headerMessage.Width = -2;
		}

		protected override bool Initialize( IEditorWinApplication application )
		{
			OutputPanelConfig config = application.Application.Settings.Get<OutputPanelConfig>();
			filter[0] = config.errorButtonPressed;
			filter[1] = config.warningButtonPressed;
			filter[2] = config.infoButtonPressed;

      buttonErrors.Checked = filter[0];
      buttonWarnings.Checked = filter[1];
      buttonMessages.Checked = filter[2];

			UpdateCounts();
			UpdateFilter();
			traceListener.AttachPanel( this );
			return true;
		}

		public override void Terminate( IEditorWinApplication application )
		{
			traceListener.DetachPanel();
			OutputPanelConfig config = application.Application.Settings.Get<OutputPanelConfig>();
			config.errorButtonPressed = filter[0];
			config.warningButtonPressed = filter[1];
			config.infoButtonPressed = filter[2];
		}

		private void UpdateCounts()
		{
			buttonErrors.Text = string.Format( "{0} Errors", counts[0] );
			buttonWarnings.Text = string.Format( "{0} Warnings", counts[1] );
			buttonMessages.Text = string.Format( "{0} Messages", counts[2] );
		}

		private void UpdateFilter()
		{
			Color highlight = Color.FromKnownColor( KnownColor.Highlight );
			Color control = Color.FromKnownColor( KnownColor.Control );
			Color background = FormUtils.MixColors( highlight, control, 0.6f );

			buttonErrors.BackColor = filter[0] ? background : control;
			buttonWarnings.BackColor = filter[1] ? background : control;
			buttonMessages.BackColor = filter[2] ? background : control;
		}

		private void OnFilterClick( object sender, EventArgs e )
		{
			int index = (int)( ( sender as ToolStripButton ).Tag );
			filter[index] = !filter[index];
			UpdateFilter();
			listView.BeginUpdate();
			listView.Items.Clear();
			traceListener.ResyncWithPanel();
			listView.EndUpdate();
		}

		private void OnClearClick( object sender, EventArgs e )
		{
			listView.BeginUpdate();
			listView.Items.Clear();
			listView.EndUpdate();
			counts[0] = 0;
			counts[1] = 0;
			counts[2] = 0;
			UpdateCounts();
			traceListener.Clear();
		}

		private void OnSaveClick( object sender, EventArgs e )
		{
			if ( saveFileDialog1.ShowDialog() == DialogResult.OK )
				traceListener.SaveToFile( saveFileDialog1.FileName );
		}

		public void Trace( OutputMessage msg, bool updateCounts )
		{
			int levelIndex = GetLogLevelIndex( msg.level );
			if ( levelIndex < 0 || levelIndex >= counts.Length )
				return;

			if ( updateCounts )
			{
				++counts[levelIndex];
				UpdateCounts();
			}

			if ( !filter[levelIndex] )
				return;

		  string message;

      if (msg.level == Log.Level.Debug)
        message = string.Format( "[Debug] {0}", msg.message );
      else if (msg.level == Log.Level.Assert)
        message = string.Format( "[Assert] {0}", msg.message );
      else
        message = msg.message;     

      ListViewItem lvItem = listView.Items.Add(string.Empty, levelIndex);

      lvItem.SubItems.AddRange(new []
      {
        msg.time.ToLongTimeString(), 
        message
      });

      listView.EnsureVisible( listView.Items.Count - 1 );
		}

    private void copyToolStripMenuItem_Click( object sender, EventArgs e )
    {
      if ( listView.SelectedItems == null || listView.SelectedItems.Count == 0 )
        return;

      StringBuilder sb = new StringBuilder();
      foreach(ListViewItem s in listView.SelectedItems)
        sb.AppendLine( s.SubItems[2].Text );
      try
      {
        Clipboard.SetText( sb.ToString(), TextDataFormat.UnicodeText );
      } 
      catch(Exception )
      {
        // Clipboard туп и всегда генерит эксепшн, который надо игнорить
      }
    }

    private void selectAllToolStripMenuItem_Click( object sender, EventArgs e )
    {
      if ( listView.Items == null || listView.SelectedItems.Count == 0 )
        return;

      StringBuilder sb = new StringBuilder();
      foreach ( ListViewItem s in listView.Items )
        sb.AppendLine( s.SubItems[2].Text );
      try
      {
        Clipboard.SetText( sb.ToString(), TextDataFormat.UnicodeText );
      }
      catch ( Exception )
      {
        // Clipboard туп и часто генерит эксепшн не по делу, который надо игнорить
        // https://connect.microsoft.com/VisualStudio/feedback/ViewFeedback.aspx?FeedbackID=92689
      }
    }

	}
}
