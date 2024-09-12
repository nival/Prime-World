using System;
using System.Drawing;
using System.Windows.Forms;
using DBTypes;
using EditorLib;
using EditorPlugins.UIScene;
using EditorPlugins.LayoutEditor;
using libdb.DB;
using System.Threading;
using libdb.Diagnostics;
using EditorNative;

namespace EditorPlugins.ImageStylesEditor
{
	
	public partial class ImageStyleView :  Editor2DSceneControl
	{
		private int zoom = 100;
		private const int MAX_ZOOM = 400;
		private const int MIN_ZOOM = 25;

    private int samplerWidth = 300;
    private int samplerHeight = 100;

    private EditorMaterialScene scene = null;
    protected override Editor2DSceneBase Scene { get { return scene; } }

		internal int Zoom
		{
			set
			{
				zoom = (Math.Min( MAX_ZOOM, Math.Max( MIN_ZOOM, value ) ));
				ScrollUpdate();

        scene.SetTextureRect( dX, dY, scene.GetWidth() * Zoom / 100, scene.GetHeight() * Zoom / 100 );
				Invalidate();
			}
			get
			{
				return zoom;
			}
    }

    public int TextureWidth
    {
      get
      { return scene.GetWidth(); }
    }

    public int TextureHeight
    {
      get
      { return scene.GetHeight(); }
    }

    private void ScrollUpdate()
		{
			int sizeX = Math.Max(TextureSizeX - TextureX + 1, TextureWidth);
			int sizeY = Math.Max(TextureSizeY - TextureY + 1, TextureHeight);
			AutoScrollMinSize = new System.Drawing.Size(sizeX * Zoom / 100, sizeY * Zoom / 100);
		}

		public ImageStyleView()
		{
      scene = new EditorMaterialScene( Handle );
      InitializeComponent();
			DataBase.ChangeDBResourceEvent += new DataBase.ChangeDBResourceEventHandler( DataBase_ChangeDBResourceEvent );
			this.Scroll += new ScrollEventHandler( ImageStyleView_Scroll );
		}

		void ImageStyleView_Scroll( object sender, ScrollEventArgs e )
		{
			UpdateTextureRect();
		}

		protected override void OnSizeChanged( EventArgs e )
		{
			base.OnSizeChanged( e );
			UpdateTextureRect();
		}
		private void UpdateTextureRect()
		{
      scene.SetTextureRect( dX, dY, scene.GetWidth() * Zoom / 100, scene.GetHeight() * Zoom / 100 );
      scene.SetSampleRect( ViewSampleX, ViewSampleY, ViewSampleWidth, ViewSampleHeight );
		}

    public void SetShapeVisible( bool _visible )
    {
      scene.SetShapeVisible( _visible );
    }

		protected override void OnPaint( PaintEventArgs e )
		{
			DrawUV();
			base.OnPaint(e);
		}

		private void DrawUV()
		{
			if ( style != null )
			{
				DrawRectangle( new Rectangle( ViewedUVX, ViewedUVY, ViewedUVLX-ViewedUVX, ViewedUVLY-ViewedUVY ), System.Drawing.Color.White );
		
				DrawRectangle( new Rectangle( ViewedUVX-1, ViewedUVY-1, ViewedUVLX-ViewedUVX+2, ViewedUVLY-ViewedUVY+2 ), System.Drawing.Color.Black );
        if (style.horizontalDrawMode == EUIImageDrawMode.Tile || style.horizontalDrawMode == EUIImageDrawMode.StretchedTile )
				{
					DrawLine( ViewedTUVX, ViewedUVY, ViewedTUVX, ViewedUVLY, System.Drawing.Color.Green );
					DrawLine( ViewedTUVLX, ViewedUVY, ViewedTUVLX, ViewedUVLY, System.Drawing.Color.Green );
				}
        if (style.verticalDrawMode == EUIImageDrawMode.Tile || style.verticalDrawMode == EUIImageDrawMode.StretchedTile)
				{
					DrawLine( ViewedUVX, ViewedTUVY, ViewedUVLX, ViewedTUVY, System.Drawing.Color.Green );
					DrawLine( ViewedUVX, ViewedTUVLY, ViewedUVLX, ViewedTUVLY, System.Drawing.Color.Green );
				}

				DrawRectangle( new Rectangle( ViewSampleX, ViewSampleY, ViewSampleWidth, ViewSampleHeight ), System.Drawing.Color.White );
      }
		}

		private Point PointToVieportCS(IntPoint p) { return PointToVieportCS(p.x, p.y); }
		private Size SizeToVieportCS(IntPoint s) { return SizeToVieportCS(s.x, s.y); }
		private Point PointToVieportCS(int x, int y)
		{
			Point converted = new Point();
			converted.X = x;
			converted.Y = y;
			converted.X -= HorizontalScroll.Value;
			converted.Y -= VerticalScroll.Value;
			converted.X = converted.X * Zoom / 100;
			converted.Y = converted.Y * Zoom / 100;
			return converted;
		}
		private Size SizeToVieportCS(int x, int y)
		{
			Size converted = new Size();
			converted.Width = x;
			converted.Height = y;
			converted.Width = converted.Width * Zoom / 100;
			converted.Height = converted.Height * Zoom / 100;
			return converted;
		}
		private void TrimByFrameSize()
		{

		}

		private BaseUIMaterial style = null;

    internal BaseUIMaterial Style
		{
			get
			{
				return style;
			}
			set
			{
				style = value;
				if (style != null)
				{
          scene.LoadMaterial( style.DBId );
					UpdateTextureRect();
					ScrollUpdate();
					Invalidate();
				}
				else
				{
          scene.LoadMaterial( DBID.Empty );
					UpdateTextureRect();
					ScrollUpdate();
					Invalidate();
				}
			}
		}
		internal bool IsAlphaChanged = false;
		private void DataBase_ChangeDBResourceEvent(  DBID dbid )
		{
			if ( style != null )
			{
        scene.ReloadMaterial( dbid );
				Invalidate();
			}
		}

		internal void Import ( IEditorCommonApplication _application , DBPtr<UITexture> _texture )
		{
			if ( _application.Extensions.HasImporter( _texture.Get().GetType() ) )
			{
				_application.Extensions.Import( _texture.DBId, _application, false );
			}
		}

		private int dX
		{
			get
			{
				return -HorizontalScroll.Value - (TextureX < 0 ? TextureX : 0) * Zoom / 100;// ;// (Width - TextureWidth * Zoom / 100) / 2;
			}
		}
		private int dY
		{
			get
			{
				return -VerticalScroll.Value - (TextureY < 0 ? TextureY : 0) * Zoom / 100; ;// (Height - TextureHeight * Zoom / 100) / 2;
			}
		}

		public delegate void ChangeUVsEventHandler( );
		public event ChangeUVsEventHandler ChangeUVsEvent = null;

		private void ChangeUVs()
		{
			ScrollUpdate();
			UpdateTextureRect();
			if ( ChangeUVsEvent != null ) 
				ChangeUVsEvent();
			Invalidate();
		}

		internal Size UVSIZE
		{
			get
			{
				return new Size(TextureSizeX - TextureX, TextureSizeY - TextureY);
			}
		}

		internal IntRect UVRECT
		{
			set
			{
				if (style == null || value == null)
					return;

				if (TextureX != value.x1 || TextureY != value.y1 || TextureSizeX != value.x2 || TextureSizeY != value.y2)
				{
					style.textureShift.x = value.x1;
					style.textureShift.y = value.y1;
					style.imageSize.x = value.x2 - value.x1;
					style.imageSize.y = value.y2 - value.y1;
					if (TileLeftMargin < TextureX) TileLeftMargin = TextureX;
					if (TileLeftMargin > TextureSizeX) TileLeftMargin = TextureSizeX;
					if (TileTopMargin < TextureY) TileTopMargin = TextureY;
					if (TileTopMargin > TextureSizeY) TileTopMargin = TextureSizeY;
					if (TileRightMargin > TextureSizeX) TileRightMargin = TextureSizeX;
					if (TileRightMargin < TextureX) TileRightMargin = TextureX;
					if (TileBottomMargin > TextureSizeY)	TileBottomMargin = TextureSizeY;
					if (TileBottomMargin < TextureY) TileBottomMargin = TextureY;
					ChangeUVs();
				}
			}
		}
		internal IntRect TUVRECT
		{
			set
			{
				if (style == null || value == null)
					return;

				if (TileLeftMargin != value.x1 || TileTopMargin != value.y1 || TileRightMargin != value.x2 || TileBottomMargin != value.y2)
				{
					style.imageTileShift.x = value.x1;
					style.imageTileShift.y = value.y1;
					style.imageTileSize.x = value.x2 - value.x1;
					style.imageTileSize.y = value.y2 - value.y1;
					if (TileLeftMargin < TextureX) TileLeftMargin = TextureX;
					if (TileLeftMargin > TextureSizeX) TileLeftMargin = TextureSizeX;
					if (TileTopMargin < TextureY) TileTopMargin = TextureY;
					if (TileTopMargin > TextureSizeY) TileTopMargin = TextureSizeY;
					if (TileRightMargin > TextureSizeX) TileRightMargin = TextureSizeX;
					if (TileRightMargin < TextureX) TileRightMargin = TextureX;
					if (TileBottomMargin > TextureSizeY)	TileBottomMargin = TextureSizeY;
					if (TileBottomMargin < TextureY) TileBottomMargin = TextureY;
					ChangeUVs();
				}
			}
		}
    internal int SamplerWidth
    {
      get
      {
        return samplerWidth;
      }
      set
      {
        samplerWidth = value;
        ChangeUVs();
      }
    }
    internal int SamplerHeight
    {
      get
      {
        return samplerHeight;
      }
      set
      {
        samplerHeight = value;
        ChangeUVs();
      }
    }
    internal int TextureX
		{
			get
			{
				if ( style == null )
					return 0;

				return style.textureShift.x;
			}
			set
			{
				if ( style == null)
					return;

				if (style.textureShift.x != value)
				{
          style.imageSize.x += style.textureShift.x - value;
					style.textureShift.x = value;

					if (TileLeftMargin < TextureX)
						TileLeftMargin = TextureX;

					ChangeUVs();
				}
			}
		}
		internal int TextureY
		{
			get
			{
				if ( style == null )
					return 0;

				return style.textureShift.y;
			}
			set
			{
				if (style == null)
					return;

				if (style.textureShift.y != value)
				{
          style.imageSize.y += style.textureShift.y - value;
					style.textureShift.y = value;

					if (TileTopMargin < TextureY)
						TileTopMargin = TextureY;

					ChangeUVs();
				}
			}
		}

		internal int TextureSizeX
		{
			get
			{
				if (style == null)
					return 0;

				return style.imageSize.x;
			}
			set
			{
				if (style == null)
					return;

				if (style.imageSize.x != value)
				{
					style.imageSize.x = value;

					ChangeUVs();
				}
			}
		}

		internal int TextureSizeY
		{
			get
			{
				if ( style == null )
					return 0;

				return style.imageSize.y;
			}
			set
			{
				if ( style == null )
					return;
		
				if ( style.imageSize.y != value)
				{
					style.imageSize.y = value;

					ChangeUVs();
				}
			}
		}

		internal int TileLeftMargin
		{
			get
			{
				if ( style == null )
					return 0;

				return style.imageTileShift.x;
			}
			set
			{
				if (style == null)
					return;

        if (value >= TextureX && value <= style.imageSize.x - TileRightMargin)
				{
          style.imageTileSize.x += style.imageTileShift.x - value;
					style.imageTileShift.x = value;
					ChangeUVs();
				}
			}
		}

    internal int TileRightMargin
    {
      get
      {
        if (style == null)
          return 0;

        return style.imageSize.x - style.imageTileShift.x - style.imageTileSize.x;
      }
      set
      {
        if (style == null)
          return;

        if (value >= 0 && value <= style.imageSize.x - TileLeftMargin)
        {
          style.imageTileSize.x = style.imageSize.x - style.imageTileShift.x - value;
          ChangeUVs();
        }
      }
    }

    internal int TileTopMargin
		{
			get
			{
				if ( style == null )
					return 0;

				return style.imageTileShift.y;
			}
			set
			{
				if ( style == null )
					return;

        if (value >= TextureY && value <= style.imageSize.y - TileBottomMargin)
				{
          style.imageTileSize.y += style.imageTileShift.y - value;
          style.imageTileShift.y = value;
					ChangeUVs();
				}
			}
		}
		internal int TileBottomMargin
		{
      get
      {
        if (style == null)
          return 0;

        return style.imageSize.y - style.imageTileShift.y - style.imageTileSize.y;
      }
      set
      {
        if (style == null)
          return;

        if (value >= 0 && value <= style.imageSize.y - TileTopMargin)
        {
          style.imageTileSize.y = style.imageSize.y - style.imageTileShift.y - value;
          ChangeUVs();
        }
      }
    }

    private int ViewSampleX
    {
      get { return dX; }
    }
    
    private int ViewSampleY
    {
      get { return dY + scene.GetHeight() * Zoom / 100 + 30; }
    }

    private int ViewSampleWidth
    {
      get { return samplerWidth * Zoom / 100; }
    }

    private int ViewSampleHeight
    {
      get { return samplerHeight * Zoom / 100; }
    }

		private int ViewedUVX
		{
			get
			{
				if ( style == null )
					return 0;
				return (IsMoved ? drawUV.X : TextureX) * Zoom / 100 + dX;
			}
		}
		private int ViewedUVY
		{
			get
			{
				if ( style == null )
					return 0;
				return (IsMoved? drawUV.Y:TextureY) * Zoom / 100 + dY;

				
			}
		}
		private int ViewedUVLX
		{
			get
			{
				if ( style == null )
					return 0;
        int x = IsMoved ? drawUVL.X : TextureSizeX + TextureX;
				int zoom = Zoom / 100;
				if ( zoom > 0 )
					zoom--;
				x = x * Zoom / 100;
				return x + dX;
			}
		}
		private int ViewedUVLY
		{
			get
			{
				if ( style == null )
					return 0;
        int y = IsMoved ? drawUVL.Y : TextureSizeY + TextureY;
				int zoom = Zoom / 100;
				if ( zoom > 0 )
					zoom--;
				y = y * Zoom / 100;
				return y + dY;
				//return (IsMoved? drawUVL.Y:UVLY) * Zoom / 100 + dY;
			}
		}

		private int ViewedTUVX
		{
			get
			{
				if ( style == null )
					return 0;
				return (IsMoved ? drawTUV.X : TileLeftMargin) * Zoom / 100 + dX;
			}
		}
		private int ViewedTUVY
		{
			get
			{
				if ( style == null )
					return 0;
				return (IsMoved ? drawTUV.Y : TileTopMargin) * Zoom / 100 + dY;


			}
		}
		private int ViewedTUVLX
		{
			get
			{
				if ( style == null )
					return 0;
        return (IsMoved ? drawTUVL.X : TextureSizeX - TileRightMargin) * Zoom / 100 + dX;
			}
		}
		private int ViewedTUVLY
		{
			get
			{
				if ( style == null )
					return 0;
        return (IsMoved ? drawTUVL.Y : TextureSizeY - TileBottomMargin) * Zoom / 100 + dY;
			}
		}

  	private bool IsMoved
		{
			get
			{
				return action != Action.None;
			}
		}
		private Point wherePushed = new Point();
		private enum Action
		{
			None,
			UVX,
			UVY,
			UVLX,
			UVLY,
			TUVX,
			TUVY,
			TUVLX,
			TUVLY,
			DRAGUV,
			DRAGTUV,
		}
    private Action action = Action.None;

		private Point UV = new Point();
		private Point UVL = new Point();
		private Point drawUV = new Point();
		private Point drawUVL = new Point();
		private Point TUV = new Point();
		private Point TUVL = new Point();
		private Point drawTUV = new Point();
		private Point drawTUVL = new Point();
		private const int SENSIVITY = 3;

		private Action GetAction(Point e, bool bShiftPressed)
		{
			if ( style == null )
				return Action.None;

      if ( bShiftPressed )
      {
        if ( style.horizontalDrawMode == EUIImageDrawMode.Tile || style.horizontalDrawMode == EUIImageDrawMode.StretchedTile )
			  {
				  if ( Math.Abs( ViewedTUVX - e.X ) < SENSIVITY )
					  return Action.TUVX;

          if ( Math.Abs( ViewedTUVLX - e.X ) < SENSIVITY )
					  return Action.TUVLX;
			  }

        if ( style.verticalDrawMode == EUIImageDrawMode.Tile || style.verticalDrawMode == EUIImageDrawMode.StretchedTile )
			  {
				  if ( Math.Abs( ViewedTUVY - e.Y ) < SENSIVITY )
					  return Action.TUVY;

				  if ( Math.Abs( ViewedTUVLY - e.Y ) < SENSIVITY )
					  return Action.TUVLY;
			  }

        if ( e.X > ViewedTUVX && e.X < ViewedTUVLX && e.Y > ViewedTUVY && e.Y < ViewedTUVLY )
          return Action.DRAGTUV;
      }
      else
      {
        if ( Math.Abs( ViewedUVX - e.X ) < SENSIVITY )
          return Action.UVX;

        if ( Math.Abs( ViewedUVY - e.Y ) < SENSIVITY )
          return Action.UVY;

        if ( Math.Abs( ViewedUVLX - e.X ) < SENSIVITY )
          return Action.UVLX;

        if ( Math.Abs( ViewedUVLY - e.Y ) < SENSIVITY )
          return Action.UVLY;

        if (e.X > ViewedUVX && e.X < ViewedUVLX && e.Y > ViewedUVY && e.Y < ViewedUVLY )
          return Action.DRAGUV;
      }

			return Action.None;
		}

		private void ImageStyleView_MouseDown( object sender, MouseEventArgs e )
		{
			bool bShiftPressed = (Control.ModifierKeys & Keys.Shift) == Keys.Shift;
			if( e.Button == MouseButtons.Left)
			{
				wherePushed = e.Location;

				UV.X = TextureX;
				UV.Y = TextureY;
        UVL.X = TextureX + TextureSizeX;
        UVL.Y = TextureY + TextureSizeY;

				drawUV.X = TextureX;
				drawUV.Y = TextureY;
        drawUVL.X = TextureX + TextureSizeX;
        drawUVL.Y = TextureY + TextureSizeY;

				TUV.X = TileLeftMargin;
				TUV.Y = TileTopMargin;
        TUVL.X = TextureSizeX - TileRightMargin;
        TUVL.Y = TextureSizeY - TileBottomMargin;

				drawTUV.X = TileLeftMargin;
				drawTUV.Y = TileTopMargin;
        drawTUVL.X = TextureSizeX - TileRightMargin;
        drawTUVL.Y = TextureSizeY - TileBottomMargin;

				action = GetAction( new Point(e.X, e.Y), bShiftPressed );
			}
		}

		private Cursor GetCursor(Point e,bool bShiftPressed)
		{
			Action localAction = (this.action != Action.None) ? this.action : GetAction( new Point( e.X, e.Y ),bShiftPressed );
      switch ( localAction )
			{
				case Action.UVX:
				case Action.UVLX:
				case Action.TUVX:
				case Action.TUVLX:
					{
						return Cursors.VSplit;
					}
				case Action.UVY:
				case Action.UVLY:
				case Action.TUVY:
				case Action.TUVLY:
					{
						return Cursors.HSplit;
					}
				case Action.DRAGUV:
				case Action.DRAGTUV:
					{
						return Cursors.SizeAll;
					}

				default:
					{
						return Cursors.Default;
					}
			}
		}

		private void ImageStyleView_MouseUp( object sender, MouseEventArgs e )
		{
			if ( IsMoved && e.Button == MouseButtons.Left )
			{
				switch ( action )
				{
					case Action.UVX:
          case Action.UVLX:
          case Action.TUVX:
          case Action.TUVLX:
            {
							TextureX = drawUV.X;
              TextureSizeX = drawUVL.X - TextureX;
              TileLeftMargin = drawTUV.X;
              TileRightMargin = TextureSizeX - drawTUVL.X;
              break;
            } 
          case Action.UVY:
          case Action.UVLY:
          case Action.TUVY:
          case Action.TUVLY:
            {
              TextureY = drawUV.Y;
              TextureSizeY = drawUVL.Y - TextureY;
              TileTopMargin = drawTUV.Y;
              TileBottomMargin = TextureSizeY - drawTUVL.Y;
              break;
            }
					case Action.DRAGUV:
						{
								IntRect rc = new IntRect();
								rc.x1 = drawUV.X;
								rc.y1 = drawUV.Y;
								rc.x2 = drawUVL.X;
								rc.y2 = drawUVL.Y;
								UVRECT = rc;
								
								IntRect trc = new IntRect();
								trc.x1 = drawTUV.X;
								trc.y1 = drawTUV.Y;
								trc.x2 = drawTUVL.X;
								trc.y2 = drawTUVL.Y;
								TUVRECT = trc;
						} break;
					case Action.DRAGTUV:
						{
								IntRect rc = new IntRect();
								rc.x1 = drawTUV.X;
								rc.y1 = drawTUV.Y;
								rc.x2 = drawTUVL.X;
								rc.y2 = drawTUVL.Y;
								TUVRECT = rc;
						} break;
					default:
						break;
				}
				action = Action.None;
				
				Invalidate();
			}
		}

		private void ImageStyleView_MouseMove( object sender, MouseEventArgs e )
		{
			if ( e.Button == MouseButtons.Left )
			{
				int dX = (wherePushed.X - e.X) * 100 / Zoom;
				int dY = (wherePushed.Y - e.Y) * 100 / Zoom;
				switch ( action )
				{
					case Action.UVX:
						{
							drawUV.X = UV.X - dX;
							CorrectTUVAndTUVL(ref drawTUV,ref drawTUVL,drawUV,drawUVL);
						} break;
					case Action.UVY:
						{
							drawUV.Y = UV.Y - dY;
							CorrectTUVAndTUVL(ref drawTUV,ref drawTUVL,drawUV,drawUVL);
						} break;
					case Action.UVLX:
						{
							drawUVL.X = UVL.X - dX;
							CorrectTUVAndTUVL(ref drawTUV,ref drawTUVL,drawUV,drawUVL);
						} break;
					case Action.UVLY:
						{
							drawUVL.Y = UVL.Y - dY;
							CorrectTUVAndTUVL(ref drawTUV,ref drawTUVL,drawUV,drawUVL);
						} break;
					case Action.TUVX:
						{
							drawTUV.X = TUV.X - dX;
							CorrectTUVAndTUVL(ref drawTUV,ref drawTUVL,drawUV,drawUVL);
						} break;
					case Action.TUVY:
						{
							drawTUV.Y = TUV.Y - dY;
							CorrectTUVAndTUVL(ref drawTUV,ref drawTUVL,drawUV,drawUVL);
						} break;
					case Action.TUVLX:
						{
							drawTUVL.X = TUVL.X - dX;
							CorrectTUVAndTUVL(ref drawTUV,ref drawTUVL,drawUV,drawUVL);
						} break;
					case Action.TUVLY:
						{
							drawTUVL.Y = TUVL.Y - dY;
							CorrectTUVAndTUVL(ref drawTUV,ref drawTUVL,drawUV,drawUVL);
						} break;
					case Action.DRAGUV:
						{
							drawUV.X = UV.X - dX;
							drawUV.Y = UV.Y - dY;
							drawUVL.X = UVL.X - dX;
							drawUVL.Y = UVL.Y - dY;

							drawTUV.X = TUV.X - dX;
							drawTUV.Y = TUV.Y - dY;
							drawTUVL.X = TUVL.X - dX;
							drawTUVL.Y = TUVL.Y - dY;
							CorrectTUVAndTUVL(ref drawTUV,ref drawTUVL,drawUV,drawUVL);
						} break;
					case Action.DRAGTUV:
						{
							drawTUV.X = TUV.X - dX;
							drawTUV.Y = TUV.Y - dY;
							drawTUVL.X = TUVL.X - dX;
							drawTUVL.Y = TUVL.Y - dY;
							CorrectTUVAndTUVL(ref drawTUV,ref drawTUVL,drawUV,drawUVL);
						} break;
					default:
						break;
				}
				if ( IsMoved )
				{
					Invalidate();
				}
			}
			else
			{
				bool bShiftPressed = (Control.ModifierKeys & Keys.Shift) == Keys.Shift;
				Cursor = GetCursor( new Point( e.X, e.Y ), bShiftPressed );
			}
		}

		private Point CorrectTUVAndTUVL( ref Point pointTUV, ref Point pointTUVL, Point pointUV, Point pointUVL )
		{
				if (pointTUV.X < pointUV.X)	pointTUV.X = pointUV.X;
				if (pointTUV.X > pointUVL.X) pointTUV.X = pointUVL.X;

				if (pointTUV.Y < pointUV.Y) pointTUV.Y = pointUV.Y;
				if (pointTUV.Y > pointUVL.Y)	pointTUV.Y = pointUVL.Y;

				if (pointTUVL.X > pointUVL.X) pointTUVL.X = pointUVL.X;
				if (pointTUVL.X < pointUV.X) pointTUVL.X = pointUV.X;

				if (pointTUVL.Y > pointUVL.Y) pointTUVL.Y = pointUVL.Y;
				if (pointTUVL.Y < pointUV.Y) pointTUVL.Y = pointUV.Y;

				return pointTUV;
		}

		private void ImageStyleView_MouseLeave( object sender, EventArgs e )
		{
			action = Action.None;
		}
		
	}
	
}
