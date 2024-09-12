using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
using EditorLib;
using EditorLib.Panels;
using EditorNative;

namespace EditorPlugins.Minimap
{
	public partial class MinimapPanel : EditorPanel
	{
		private Image mapImage;

		public Image MapImage
		{
			get { return mapImage; }
			set
			{
				mapImage = value;
				picMinimap.Visible = mapImage != null;
				ResizeMinimap();	
			}
		}

		public SizeF MapSize { get; set; }
 
		private Camera camera;

		public MinimapPanel()
		{
			InitializeComponent();
		}

		protected override bool Initialize( IEditorWinApplication app )
		{
			TabText = "Minimap";
			return true;
		}
 
		private PointF ToMapPoint(int _x, int _y)
		{
			Size minimapSize = picMinimap.Size;

			float coeffX = MapSize.Width / minimapSize.Width;
			float coeffY = MapSize.Height / minimapSize.Height;

			return new PointF( _x * coeffX, MapSize.Height - ( _y * coeffY ) );//инвертируем Y
		}

		private Point ToMinimapPoint( float _x, float _y )
		{
			Size minimapSize = picMinimap.Size;

			float coeffX = minimapSize.Width / MapSize.Width;
			float coeffY = minimapSize.Height / MapSize.Height;

			return new Point( (int)( _x * coeffX ), minimapSize.Height - (int)( _y * coeffY ) );//инвертируем Y
		}

		private Size GetMinimapSize()
		{
			if ( mapImage == null )
				return Size.Empty;

			int sourceWidth = mapImage.Width;
			int sourceHeight = mapImage.Height;

			float nPercentW = 0;
			float nPercentH = 0;

			nPercentW = ( ( Width - ( picMinimap.Left * 2 ) ) / (float)sourceWidth );//picMinimap.Left*2 - отступы от краев формы
			nPercentH = ( ( Height - ( tsControls.Height + 4 + 4 ) ) / (float)sourceHeight );//высота панели - отступы от краев формы

			float nPercent = nPercentH < nPercentW ? nPercentH : nPercentW;

			int destWidth = (int)( sourceWidth * nPercent );
			int destHeight = (int)( sourceHeight * nPercent );

			return new Size( destWidth, destHeight );
		}

		private void ResizeMinimap()
		{
			if( mapImage != null )
			{
				Size minimapSize = GetMinimapSize();

				if(minimapSize.Width <= 0 || minimapSize.Height <= 0)
					return;

				picMinimap.Size = minimapSize;
				picMinimap.Image = ResizeImage( mapImage, minimapSize );
				picMinimap.Refresh();
			}
		}

		#region Camera

		public void SetCamera( Camera _camera )
		{
			if( camera != null )
				camera.ParametersChanged -= CameraParametersChanged;

			camera = _camera;

			if( camera != null )
				camera.ParametersChanged += CameraParametersChanged;
		}

		private void ZoomIn()
		{
			if( camera != null )
			{
				camera.Rod -= 10;
			}
		}

		private void ZoomOut()
		{
			if( camera != null )
			{
				camera.Rod += 10;
			}
		}

		private void MoveCamera( int x, int y )
		{
			if( camera == null )
				return;

			PointF pt = ToMapPoint( x, y );

			Vector3 vec = camera.Anchor;
			vec.X = pt.X;
			vec.Y = pt.Y;
			camera.Anchor = vec;
		}

		#endregion

		#region Event Handlers

		private void CameraParametersChanged( object sender, System.EventArgs e )
		{
			Refresh();
		}

		private void picMinimap_MouseClick( object sender, MouseEventArgs e )
		{
			MoveCamera( e.X, e.Y );
		}

		private void picMinimap_Paint( object sender, PaintEventArgs e )
		{
      //DrawFrustum( e.Graphics );
		}

		private void MinimapPanel_Resize( object sender, System.EventArgs e )
		{
			ResizeMinimap();
		}

		private void btnZoomIn_Click( object sender, System.EventArgs e )
		{
			ZoomIn();
		}

		private void btnZoomOut_Click( object sender, System.EventArgs e )
		{
			ZoomOut();
		}

		#endregion

		private void DrawFrustum( Graphics graphics )
		{
			if (camera == null) return;

			//DateTime dt = DateTime.Now;

			EditorScene scene = camera.GetEditorScene();
			if(scene == null) return;

			Point[] points = scene.GetCameraFrustum();
   	
			if ( points.Length > 0 )
			{
				for ( int i = 0; i < points.Length; i++ )
				{
					points[i] = ToMinimapPoint( points[i].X, points[i].Y );
				}

				GraphicsPath graphPath = new GraphicsPath();
				graphPath.AddLines(points);
				graphPath.SetMarkers();
				graphPath.CloseAllFigures();
				graphics.DrawPath( Pens.Red, graphPath);
			}

			//System.Diagnostics.Debug.Print( "DrawFrustum: {0} ms", (DateTime.Now - dt).TotalMilliseconds );
		}

		private static Image ResizeImage( Image _imageToResize, Size _size )
		{
			int sourceWidth = _imageToResize.Width;
			int sourceHeight = _imageToResize.Height;

			float nPercent = 0;
			float nPercentW = 0;
			float nPercentH = 0;

			nPercentW = ( (float)_size.Width / sourceWidth );
			nPercentH = ( (float)_size.Height / sourceHeight );

			if ( nPercentH < nPercentW )
				nPercent = nPercentH;
			else
				nPercent = nPercentW;

			int destWidth = (int)( sourceWidth * nPercent );
			int destHeight = (int)( sourceHeight * nPercent );

			Bitmap b = new Bitmap( destWidth, destHeight );
			Graphics g = Graphics.FromImage( (Image)b );
			g.InterpolationMode = InterpolationMode.HighQualityBicubic;

			g.DrawImage( _imageToResize, 0, 0, destWidth, destHeight );
			g.Dispose();

			return (Image)b;
		}
	}
}