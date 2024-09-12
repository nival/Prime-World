using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace EditorPlugins.LayoutEditor
{
	public partial class LayoutEditorStatusPanel : UserControl
	{
		/*Window _CurrentWindow;*/

		public LayoutEditorControl editorControl;

		/*internal Window CurrentWindow
		{
			set
			{
				if ( _CurrentWindow != null )
					UnSubscribe();

				_CurrentWindow = value;

				if ( value != null )
				{
					Subscribe();
					OnMoveEventHandler( _CurrentWindow );
					OnResizeEventHandler( _CurrentWindow );
				}
				else
				{
					MouseX.Text = "";
					MouseY.Text = "";
					PosX.Text = "";
					PosY.Text = "";
					SizeX.Text = "";
					SizeY.Text = "";
				}
				Invalidate();
			}
		}

		public bool SnapingEnabled	{	set	{	checkBox1.Checked = value;	}	}

		void OnMoveEventHandler( Window window )
		{
			PosX.Text = window.GetWindowCorner().X.ToString();
			PosY.Text = window.GetWindowCorner().Y.ToString();
		}

		void OnResizeEventHandler( Window window )
		{
			SizeX.Text = window.GetWindowSize().Width.ToString();
			SizeY.Text = window.GetWindowSize().Height.ToString();
		}

		void MouseMoveEventHandler(object sender, MouseEventArgs e)
		{
			MouseX.Text = e.X.ToString();
			MouseY.Text = e.Y.ToString();
		}

		void DragOverEventHandler(object sender, DragEventArgs e)
		{
			Point clPoint = editorControl.PointToClient(new Point(e.X,e.Y));
			MouseX.Text = clPoint.X.ToString();
			MouseY.Text = clPoint.Y.ToString();
		}

		void Subscribe()
		{
			_CurrentWindow.MoveEvent += new Window.MoveEventHandler( OnMoveEventHandler );
			_CurrentWindow.ResizeEvent += new Window.ResizeEventHandler( OnResizeEventHandler );
			editorControl.MouseMove += new MouseEventHandler(MouseMoveEventHandler);
			editorControl.DragOver += new DragEventHandler(DragOverEventHandler);
		}


		void UnSubscribe()
		{
			_CurrentWindow.MoveEvent -= new Window.MoveEventHandler( OnMoveEventHandler );
			_CurrentWindow.ResizeEvent -= new Window.ResizeEventHandler( OnResizeEventHandler );
		}

		public LayoutEditorStatusPanel()
		{
			InitializeComponent();
		}*/

	}
}
