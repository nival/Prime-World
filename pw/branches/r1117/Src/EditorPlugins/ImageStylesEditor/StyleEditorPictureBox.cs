using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using DBTypes;
using System.Drawing.Drawing2D;

namespace EditorPlugins.ImageStylesEditor
{
	
	public partial class StyleEditorPictureBox : PictureBox
	{
		private Point uv;
		private Point uvl;
		private Point tuv;
		private Point tuvl;
		// private MapControl mapping;
		private ImageStylesEditorControl parent;
		private SizeF scaleCoef = new SizeF(1.0f, 1.0f);
		public StyleEditorPictureBox()
		{
			InitializeComponent();
		}

		protected override void OnResize( EventArgs e )
		{
			base.OnResize( e );
			Invalidate( new Rectangle( 0, 0, Width, Height ) );
		}

		protected override void OnPaint( PaintEventArgs pe )
		{
			System.Drawing.Font myFont = new System.Drawing.Font( "Times New Roman", 10 );
			
			if ( Image == null )
				return;

			int GridStep = 16 ;
			Pen pencilForGrid = new Pen( System.Drawing.Color.FromArgb( 255, 255, 255, 255 ) );
			LinearGradientBrush gridBrush = new LinearGradientBrush(
				ClientRectangle,
				System.Drawing.Color.FromArgb( 255, 200, 200, 200 ),
				System.Drawing.Color.FromArgb( 255, 200, 200, 200 ),
				LinearGradientMode.Horizontal
			);
			for ( int y = 0; y * Height / Image.Height < Height; y += GridStep )
				for ( int x = 0; x * Width / Image.Width + (((y % (GridStep * 2)) == GridStep) ? (GridStep * Width / Image.Width) : 0) < Width; x += 2 * GridStep )
					pe.Graphics.FillRectangle(
						gridBrush, 
						new Rectangle(
							x * Width / Image.Width + (((y % (GridStep * 2)) == GridStep) ? (GridStep * Width / Image.Width) : 0), 
							y * Height / Image.Height, 
							GridStep * Width / Image.Width,
							GridStep * Height / Image.Height
						) 
					);
			pe.Graphics.InterpolationMode = InterpolationMode.NearestNeighbor;
			base.OnPaint( pe );
			
			// if ( Mapping == MapControl.None ) return;
			
			if (UV != null && UV.X >= 0 && UV.Y >= 0 )
			{
				LinearGradientBrush myBrush = new LinearGradientBrush(
					ClientRectangle,
					System.Drawing.Color.FromArgb( 255, 255, 0, 0 ),
					System.Drawing.Color.FromArgb( 255, 255, 0, 0 ),
					LinearGradientMode.Horizontal
				);
				Pen pencil = new Pen( System.Drawing.Color.FromArgb( 255, 255, 0, 0 ) );
				pe.Graphics.DrawLine( pencil, new Point( UV.X, 0 ), new Point( UV.X, Height ) );
				pe.Graphics.DrawLine( pencil, new Point( 0, UV.Y ), new Point( Width, UV.Y ) );
				pe.Graphics.DrawString( "UV", myFont, myBrush, new RectangleF( UV.X, UV.Y, 300, 200 ) );
			}
			if ( UVL != null && UVL.X >= 0 && UVL.Y >= 0 )
			{
				LinearGradientBrush myBrush = new LinearGradientBrush(
					ClientRectangle,
					System.Drawing.Color.FromArgb( 255, 150, 0, 0 ),
					System.Drawing.Color.FromArgb( 255, 150, 0, 0 ),
					LinearGradientMode.Horizontal
				);
				Pen pencil = new Pen( System.Drawing.Color.FromArgb( 255, 150, 0, 0 ) );
				pe.Graphics.DrawLine( pencil, new Point( UVL.X, 0 ), new Point( UVL.X, Height ) );
				pe.Graphics.DrawLine( pencil, new Point( 0, UVL.Y ), new Point( Width, UVL.Y ) );
				pe.Graphics.DrawString( "UVL", myFont, myBrush, new RectangleF( UVL.X, UVL.Y, 300, 200 ) );
			}
			if ( TUV != null && TUV.X >= 0 && TUV.Y >= 0 )
			{
				LinearGradientBrush myBrush = new LinearGradientBrush(
					ClientRectangle,
					System.Drawing.Color.FromArgb( 255, 0, 255, 0 ),
					System.Drawing.Color.FromArgb( 255, 0, 255, 0 ),
					LinearGradientMode.Horizontal
				);
				Pen pencil = new Pen( System.Drawing.Color.FromArgb( 255, 0, 255, 0 ) );
				Point xCoord = new Point();
				if ( HTile )
				{
					pe.Graphics.DrawLine( pencil, new Point( TUV.X, 0 ), new Point( TUV.X, Height ) );
					xCoord.X = TUV.X;
				}
				if ( VTile )
				{
					pe.Graphics.DrawLine( pencil, new Point( 0, TUV.Y ), new Point( Width, TUV.Y ) );
					xCoord.Y = TUV.Y;
				}
				if ( HTile || VTile )
					pe.Graphics.DrawString( "TileUV", myFont, myBrush, new RectangleF( xCoord, new SizeF(300, 200) ) );
			}
			if ( TUVL != null && TUVL.X >= 0 && TUVL.Y >= 0 )
			{
				LinearGradientBrush myBrush = new LinearGradientBrush( 
					ClientRectangle,
					System.Drawing.Color.FromArgb( 255, 0, 150, 0 ),
					System.Drawing.Color.FromArgb( 255, 0, 150, 0 ), 
					LinearGradientMode.Horizontal 
				);
				Pen pencil = new Pen( System.Drawing.Color.FromArgb( 255, 0, 150, 0 ) );
				Point xCoord = new Point();
				if ( HTile )
				{
					pe.Graphics.DrawLine( pencil, new Point( TUVL.X, 0 ), new Point( TUVL.X, Height ) );
					xCoord.X = TUVL.X;
				}
				if ( VTile )
				{
					pe.Graphics.DrawLine( pencil, new Point( 0, TUVL.Y ), new Point( Width, TUVL.Y ) );
					xCoord.Y = TUVL.Y;
				}
				if ( HTile || VTile )
					pe.Graphics.DrawString( "TileUVL", myFont, myBrush, new RectangleF( xCoord, new SizeF( 300, 200 ) ) );
			}
		}

		public new ImageStylesEditorControl Parent
		{
			set
			{
				parent = value;
			}
		}

// 		public MapControl Mapping
// 		{
// 			set
// 			{
// 				mapping = value;
// 				Invalidate();
// 				Update();
// 			}
// 			get
// 			{
// 				return mapping;
// 			}
// 		}
		
		private bool HTile
		{
			get
			{
				return parent.HTile;
			}
		}

		private bool VTile
		{
			get
			{
				return parent.VTile;
			}
		}

		internal Point UV
		{
			set
			{
				if ( Image == null ) return;

				Point p  = value; 
				p.X = (p.X > Width - 1) ? (Width - 1) : p.X;
				p.Y = (p.Y > Height - 1) ? (Height - 1) : p.Y;
				p.X = (p.X < 0) ? 0 : p.X;
				p.Y = (p.Y < 0) ? 0 : p.Y;
				p = new Point( p.X * Image.Width / Width, p.Y * Image.Height / Height );
	  
				// p.X = (p.X > uvl.X)? uvl.X : p.X;
				// p.Y = (p.Y > uvl.Y)? uvl.Y : p.Y;
				// p.X = (p.X > tuv.X) ? tuv.X : p.X;
				// p.Y = (p.Y > tuv.Y) ? tuv.Y : p.Y;
					uv = p;
			}
			get
			{
				if ( Image == null ) return new Point( -1, -1 );
				return new Point(uv.X  * Width/Image.Width, uv.Y  * Height/Image.Height);
			}
		}
		internal Point UVL
		{
			set
			{
				if ( Image == null ) return;

				Point p = value;
				p.X = (p.X > Width - 1) ? (Width - 1) : p.X;
				p.Y = (p.Y > Height - 1) ? (Height - 1) : p.Y;
				p.X = (p.X < 0) ? 0 : p.X;
				p.Y = (p.Y < 0) ? 0 : p.Y;
				p = new Point( p.X * Image.Width / Width  + 1, p.Y * Image.Height / Height + 1 );
	
				// p.X = (p.X < uv.X) ? uv.X : p.X;
				// p.Y = (p.Y < uv.Y) ? uv.Y : p.Y;
				// p.X = (p.X < tuvl.X) ? tuvl.X : p.X;
				// p.Y = (p.Y < tuvl.Y) ? tuvl.Y : p.Y;
			
				uvl = p;
			}
			get
			{
				if ( Image == null ) return new Point( -1, -1 );
				return new Point( uvl.X * Width / Image.Width - 1, uvl.Y * Height / Image.Height - 1);
			}
		}
		internal Point TUV
		{
			set
			{
				if ( Image == null ) return;

				Point p = value;
				p.X = (p.X > Width - 1) ? (Width - 1) : p.X;
				p.Y = (p.Y > Height - 1) ? (Height - 1) : p.Y;
				p.X = (p.X < 0) ? 0 : p.X;
				p.Y = (p.Y < 0) ? 0 : p.Y;
				p = new Point( p.X * Image.Width / Width, p.Y * Image.Height / Height );
	
	 			// p.X = (p.X < uv.X) ? uv.X : p.X;
				// p.Y = (p.Y < uv.Y) ? uv.Y : p.Y;
				// p.X = (p.X > tuv.X) ? tuv.X : p.X;
				// p.Y = (p.Y > tuv.Y) ? tuv.Y : p.Y;
				// p.X = (p.X > uvl.X) ? uvl.X : p.X;
				// p.Y = (p.Y > uvl.Y) ? uvl.Y : p.Y;

				tuv = p;
			}
			get
			{
				if ( Image == null ) return new Point( -1, -1 );
				return new Point( tuv.X * Width / Image.Width, tuv.Y * Height / Image.Height );
			}
		}
		internal Point TUVL
		{
			set
			{
				if ( Image == null ) return;

				Point p = value;
				p.X = (p.X > Width - 1) ? (Width - 1) : p.X;
				p.Y = (p.Y > Height - 1) ? (Height - 1) : p.Y;
				p.X = (p.X < 0) ? 0 : p.X;
				p.Y = (p.Y < 0) ? 0 : p.Y;
				p = new Point( p.X * Image.Width / Width, p.Y * Image.Height / Height );
	 
				// p.X = (p.X < uv.X) ? uv.X : p.X;
				// p.Y = (p.Y < uv.Y) ? uv.Y : p.Y;
				// p.X = (p.X < tuv.X) ? tuv.X : p.X;
				// p.Y = (p.Y < tuv.Y) ? tuv.Y : p.Y;
				// p.X = (p.X > uvl.X) ? uvl.X : p.X;
				// p.Y = (p.Y > uvl.Y) ? uvl.Y : p.Y;

				tuvl = p;
			}
			get
			{
				if ( Image == null ) return new Point( -1, -1 );
				return new Point( tuvl.X * Width / Image.Width , tuvl.Y * Height / Image.Height );
			}
		}
		internal Point OriginalUV
		{
			set
			{
				uv = value;
			}
			get
			{
				return uv;
			}
		}
		internal Point OriginalUVL
		{
			set
			{
				uvl = value;
			}
			get
			{
				return uvl;
			}
		}
		internal Point OriginalTUV
		{
			set
			{
				tuv = value;
			}
			get
			{
				return tuv;
			}
		}
		internal Point OriginalTUVL
		{
			set
			{
				tuvl = value;
			}
			get
			{
				return tuvl;
			}
		}

		public SizeF ScaleF
		{
			set
			{
				Scale( new SizeF( 1.0f / scaleCoef.Width, 1.0f / scaleCoef.Height ) );
				scaleCoef = value;
				Scale( scaleCoef );
			}
			get
			{
				return scaleCoef;
			}
		}
		
		public void MakeScaleF(SizeF size)
		{
			if ( scaleCoef.Width > 4 && size.Width > 1)
				return;
			if ( scaleCoef.Width < 0.2 && size.Width < 1 )
				return;
			scaleCoef.Width *= size.Width;
			scaleCoef.Height *= size.Height;
			Scale( size );
		}
	}
}
