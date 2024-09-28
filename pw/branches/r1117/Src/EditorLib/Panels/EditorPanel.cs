using System;
using System.Windows.Forms;
using WeifenLuo.WinFormsUI.Docking;

namespace EditorLib.Panels
{
	public class EditorPanel : DockContent
	{
		private bool isInitialized = false;
		protected IEditorWinApplication application = null;

		public EditorPanel()
		{
			FormBorderStyle = FormBorderStyle.SizableToolWindow;
			ShowIcon = false;
			ShowInTaskbar = false;
		}

		protected new bool ShowIcon { get { return base.ShowIcon; } set { base.ShowIcon = value; } }
		protected new bool ShowInTaskbar { get { return base.ShowInTaskbar; } set { base.ShowInTaskbar = value; } }
		protected new FormBorderStyle FormBorderStyle { get { return base.FormBorderStyle; } set { base.FormBorderStyle = value; } }

		public bool IsInitialized { get { return isInitialized; } }

		protected virtual bool Initialize( IEditorWinApplication application ) { return false; }
		public virtual void Terminate( IEditorWinApplication application ) { }

		internal bool InitializeInternal( IEditorWinApplication application )
		{
			this.application = application;
			if ( !Initialize( application ) )
				return false;

			isInitialized = true;
			return true;
		}

		protected override bool ProcessCmdKey( ref Message msg, Keys keyData )
		{
			if ( base.ProcessCmdKey( ref msg, keyData ) )
				return true;
			//if ( application != null )
			//  if ( application.MainMenu.ProcessCmdKey( ref msg, keyData ) )
			//    return true;
			return false;
		}

    protected override void OnVisibleChanged( EventArgs e )
    {
      base.OnVisibleChanged( e );
      if( application != null)
      {
        application.MainMenu.RecreateMenu();  
      }
      
    }
	}
}
