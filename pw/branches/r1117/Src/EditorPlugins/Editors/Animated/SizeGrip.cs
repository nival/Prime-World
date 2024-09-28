using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace EditorPlugins.Editors.Animated
{
	public partial class SizeGrip : Control
	{
		public SizeGrip()
		{
			InitializeComponent();
		}

		public SizeGrip( IContainer container )
		{
			container.Add( this );

			InitializeComponent();
		}

		protected override void OnPaint( PaintEventArgs e )
		{
			e.Graphics.FillRectangle( new SolidBrush( BackColor ), e.ClipRectangle );

			int GripSize = Math.Min( ClientSize.Width, ClientSize.Height ) - 1;
			Rectangle GripRect = new Rectangle( ClientSize.Width - GripSize - 1, ClientSize.Height - GripSize - 1, GripSize, GripSize );
			ControlPaint.DrawSizeGrip( e.Graphics, BackColor, GripRect );
		}
	}
}
