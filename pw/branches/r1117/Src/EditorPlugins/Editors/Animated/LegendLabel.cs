using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using System;

namespace EditorPlugins.Editors.Animated
{
	public partial class LegendLabel : Control
	{
		public LegendLabel()
		{
			InitializeComponent();
		}

		protected override void OnPaint( PaintEventArgs e )
		{
			e.Graphics.FillRectangle( new SolidBrush( IsChecked && Enabled ? Color.FromKnownColor(KnownColor.Highlight) : BackColor ), e.ClipRectangle );

			Rectangle ColorLabel = new Rectangle( 2, 2, ClientSize.Height - 5, ClientSize.Height - 5 );
			e.Graphics.FillRectangle( new SolidBrush( ( Enabled ? Color : Color.FromKnownColor( KnownColor.ControlDark ) ) ), ColorLabel );
			e.Graphics.DrawRectangle( new Pen( Color.Gray ), ColorLabel );

			//Rectangle SelectedLabel = new Rectangle( 2, 1, ClientSize.Height - 2, ClientSize.Height - 2 );
			//ControlPaint.DrawCheckBox( e.Graphics, SelectedLabel, ButtonState.Flat | ( IsChecked ? ButtonState.Checked : ButtonState.Normal ) |	( Enabled ? ButtonState.Normal : ButtonState.Inactive ) );

			Font font = isSelected ? new Font( Font, FontStyle.Bold ) : Font;
			TextRenderer.DrawText( e.Graphics, Text, font, new Point( 3 + ClientSize.Height, ClientSize.Height - Font.Height - 1 ), Enabled ? ForeColor : Color.FromKnownColor( KnownColor.ControlDark ) );
		}

		protected override void OnClick( System.EventArgs e )
		{
			base.OnClick( e );
			IsChecked = !IsChecked;

			if ( CheckedChanged != null )
				CheckedChanged( this, EventArgs.Empty );
		}

		private Color color = Color.FromKnownColor( KnownColor.White );
		[Category( "Appearance" )]
		public Color Color { get { return color; } set { color = value; Invalidate(); } }

		private bool isSelected = false;
		[Category( "Appearance" )]
		[DefaultValue( false )]
		public bool IsSelected { get { return isSelected; } set { isSelected = value; Invalidate(); } }

		private bool isChecked = false;
		[Category( "Appearance" )]
		[DefaultValue( false )]
		public bool IsChecked { get { return isChecked; } set { isChecked = value; Invalidate(); } }

		[Category( "Behavior" )]
		public event EventHandler CheckedChanged = null;
	}
}
