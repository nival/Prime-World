using System;
using System.Collections.Generic;
using System.ComponentModel;
using libdb.Diagnostics;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace EditorPlugins.Scene.Viewers.ShapeControl
{
	public partial class ShapeChart : Control
	{
		private readonly List<Shape> shapes = new List<Shape>();
		private readonly List<Connection> connections = new List<Connection>();
		private Point center = new Point( 0, 0 );
		private float scale = 1.0f;

		private ConnectionConstructor connectionCotr = null;

		public ShapeChart() : this( null ) { }

		public ShapeChart( IContainer container )
		{
			if ( container != null )
				container.Add( this );

			SetStyle( ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer | ControlStyles.ResizeRedraw |
				ControlStyles.Selectable | ControlStyles.UserPaint, true );

			InitializeComponent();
		}

		#region Canvas from/to Client coordinates converters

		private Size ScaleSize( Size sz, float scale )
		{
			return new Size( (int)Math.Round( sz.Width * scale ), (int)Math.Round( sz.Height * scale ) );
		}

		private Point CanvasToClient( Point pt )
		{
			SizeF offset = new SizeF( pt.X - center.X, pt.Y - center.Y );
			offset.Width /= scale;
			offset.Height /= scale;
			return new Point( ClientSize.Width / 2, ClientSize.Height / 2 ) + offset.ToSize();
		}

		private Rectangle RectagleToClient( Rectangle rect )
		{
			return new Rectangle( CanvasToClient( rect.Location ), ScaleSize( rect.Size, 1.0f / scale ) );
		}

		private Point PointToCanvas( Point pt )
		{
			SizeF offset = new SizeF( pt.X - ClientSize.Width / 2, pt.Y - ClientSize.Height / 2 );
			offset.Width *= scale;
			offset.Height *= scale;
			return center + offset.ToSize();
		}

		private Rectangle RectangleToCanvas( Rectangle rect )
		{
			return new Rectangle( PointToCanvas( rect.Location ), ScaleSize( rect.Size, scale ) );
		}

		#endregion

		#region ShapeOwnerDraw support

		public sealed class MeasureShapeEventArgs : EventArgs
		{
			private readonly IShape shape = null;
			private Size size = new Size( 70, 20 );

			internal MeasureShapeEventArgs( IShape shape ) { this.shape = shape; }

			public IShape Shape { get { return shape; } }
			public Size Size { get { return size; } set { size = value; } }
		}

		public delegate void MeasureShapeEventHandler( object sender, MeasureShapeEventArgs e );

		public event MeasureShapeEventHandler MeasureShape = null;

		protected virtual void OnMeasureShape( MeasureShapeEventArgs e )
		{
			if ( MeasureShape != null )
				MeasureShape( this, e );
		}

		public sealed class FindConnectorEventArgs : EventArgs
		{
			private readonly IShape from = null;
			private readonly IShape to = null;
			private readonly Point toPoint;
			private readonly bool backward = false;
			private Point location;

			internal FindConnectorEventArgs( IShape from, IShape to, bool backward )
			{
				this.from = from;
				this.to = to;
				this.backward = backward;
				toPoint = this.to.Location;
				Size offset = GetLocationOffset( this.From.Location, this.to.Location, 4.0f );
				if ( backward )
				{
					offset.Width = -offset.Width;
					offset.Height = -offset.Height;
				}
				if ( !TryFindIntersection( from.Bounds, this.from.Location + offset, this.to.Location + offset, out location ) )
					location = this.from.Location;
			}

			internal FindConnectorEventArgs( IShape from, Point toPoint )
			{
				this.from = from;
				this.toPoint = toPoint;
				if ( !TryFindIntersection( from.Bounds, this.from.Location, this.toPoint, out location ) )
					location = this.from.Location;
			}

			public Size GetLocationOffset( Point from, Point to, float offset )
			{
				SizeF dir = new SizeF( to.X - from.X, to.Y - from.Y );
				float len = (float)Math.Sqrt( dir.Width * dir.Width + dir.Height * dir.Height );
				if ( len < 0.1f )
					return new Size();

				return new Size( (int)Math.Round( offset * dir.Height / len ), (int)Math.Round( -( offset * dir.Width / len ) ) );
			}

			private bool IsInside( int value, int left, int right )
			{
				return left <= value && value <= right;
			}

			private bool IsInside( int value, int left, int right, int? x, int? y, out Point intersection )
			{
				intersection = new Point();
				if ( !IsInside( value, left, right ) )
					return false;

				intersection.X = x ?? value;
				intersection.Y = y ?? value;
				return true;
			}

			private bool IsInside( int value, int left1, int right1, int left2, int right2, int? x, int? y, out Point intersection )
			{
				intersection = new Point();
				if ( !IsInside( value, left1, right1 ) || !IsInside( value, left2, right2 ) )
					return false;

				intersection.X = x ?? value;
				intersection.Y = y ?? value;
				return true;
			}

			public bool TryFindIntersection( Rectangle rect, Point a, Point b, out Point intersection )
			{
				Point min = new Point( Math.Min( a.X, b.X ), Math.Min( a.Y, b.Y ) );
				Point max = new Point( Math.Max( a.X, b.X ), Math.Max( a.Y, b.Y ) );

				if ( a.Y == b.Y )
				{
					if ( IsInside( rect.Left, min.X, max.X, null, a.Y, out intersection ) )
						return true;
					else if ( IsInside( rect.Right, min.X, max.X, null, a.Y, out intersection ) )
						return true;
				}
				else if ( a.X == b.X )
				{
					if ( IsInside( rect.Top, min.Y, max.Y, a.X, null, out intersection ) )
						return true;
					else if ( IsInside( rect.Bottom, min.Y, max.Y, a.X, null, out intersection ) )
						return true;
				}
				else
				{
					PointF aF = a;
					PointF bF = b;
					RectangleF rectF = rect;

					float kx = ( aF.Y - bF.Y ) / ( aF.X - bF.X );
					float cx = aF.Y - kx * aF.X;

					if ( IsInside( rect.Left, min.X, max.X ) &&
						IsInside( (int)Math.Round( kx * rectF.Left + cx ), min.Y, max.Y, rect.Top, rect.Bottom, rect.Left, null, out intersection ) )
						return true;

					if ( IsInside( rect.Right, min.X, max.X ) &&
						IsInside( (int)Math.Round( kx * rectF.Right + cx ), min.Y, max.Y, rect.Top, rect.Bottom, rect.Right, null, out intersection ) )
						return true;

					float ky = ( aF.X - bF.X ) / ( aF.Y - bF.Y );
					float cy = aF.X - ky * aF.Y;

					if ( IsInside( rect.Top, min.Y, max.Y ) &&
						IsInside( (int)Math.Round( ky * rectF.Top + cy ), min.X, max.X, rect.Left, rect.Right, null, rect.Top, out intersection ) )
						return true;

					if ( IsInside( rect.Bottom, min.Y, max.Y ) &&
						IsInside( (int)Math.Round( ky * rectF.Bottom + cy ), min.X, max.X, rect.Left, rect.Right, null, rect.Bottom, out intersection ) )
						return true;
				}

				intersection = new Point();
				return false;
			}

			public IShape From { get { return from; } }
			public IShape To { get { return to; } }
			public bool Backward { get { return backward; } }
			public Point ToPoint { get { return toPoint; } }
			public Point Location { get { return location; } set { location = value; } }
		}

		public delegate void FindConnectorEventHandler( object sender, FindConnectorEventArgs e );

		public event FindConnectorEventHandler FindConnector = null;

		protected virtual void OnFindConnector( FindConnectorEventArgs e )
		{
			if ( FindConnector != null )
				FindConnector( this, e );
		}

		public sealed class DrawShapeEventArgs : EventArgs
		{
			private readonly Graphics graphics = null;
			private readonly IShape shape = null;
			private readonly Rectangle bounds;
			private readonly bool highlighted = false;

			internal DrawShapeEventArgs( Graphics graphics, IShape shape, Rectangle bounds, bool highlighted )
			{
				this.graphics = graphics;
				this.shape = shape;
				this.bounds = bounds;
				this.highlighted = highlighted;
			}

			public void FillShape( Color fillColor )
			{
				using ( SolidBrush brush = new SolidBrush( fillColor ) )
				{
					Graphics.FillRectangle( brush, Bounds );
				}
			}

			public void DrawFrame( Color frameColor )
			{
				using ( Pen pen = new Pen( frameColor ) )
				{
					Graphics.DrawRectangle( pen, Bounds );
				}
			}

			public Graphics Graphics { get { return graphics; } }
			public IShape Shape { get { return shape; } }
			public Rectangle Bounds { get { return bounds; } }
			public bool Highlighted { get { return highlighted; } }
		}

		public delegate void DrawShapeEventHandler( object sender, DrawShapeEventArgs e );

		public event DrawShapeEventHandler DrawShape = null;

		protected virtual void OnDrawShape( DrawShapeEventArgs e )
		{
			if ( DrawShape != null )
				DrawShape( this, e );
		}

		#endregion

		#region ConnectionOwnerDraw support

		public sealed class DrawConnectionEventArgs : EventArgs
		{
			private readonly Graphics graphics = null;
			private readonly IConnection connection = null;
			private readonly Point from;
			private readonly Point to;
			private readonly bool highlighted = false;

			internal DrawConnectionEventArgs( Graphics graphics, IConnection connection, Point from, Point to, bool highlighted )
			{
				this.graphics = graphics;
				this.connection = connection;
				this.from = from;
				this.to = to;
				this.highlighted = highlighted;
			}

			private Point[] GetArrowPoint( Point from, Point to, float length )
			{
				PointF dir = new PointF( to.X - from.X, to.Y - from.Y );
				float len = (float)Math.Sqrt( dir.X * dir.X + dir.Y * dir.Y );
				if ( len < 0.1f )
					return null;

				dir.X /= len;
				dir.Y /= len;

				Point[] points = new Point[] { to,
					new Point( to.X - (int)( length * dir.X + 0.3f * length * dir.Y ), to.Y - (int)( length * dir.Y - 0.3f * length * dir.X ) ),
					new Point( to.X - (int)( length * dir.X - 0.3f * length * dir.Y ), to.Y - (int)( length * dir.Y + 0.3f * length * dir.X ) ) };

				return points;
			}

			public void DrawLine( Color color, int width )
			{
				using ( Pen pen = new Pen( color, (float)width ) )
				{
					Graphics.DrawLine( pen, From, To );
				}
			}

			public void DrawArrows( float length, Color color )
			{
				using ( SolidBrush brush = new SolidBrush( color ) )
				{
					Point[] points = GetArrowPoint( From, To, length );
					if ( points != null )
						Graphics.FillPolygon( brush, points );
				}
			}

			public void OutlineArrows( float length, Color color, int width )
			{
				if ( width <= 0 )
					return;

				using ( Pen pen = new Pen( color, (float)width ) )
				{
					Point[] points = GetArrowPoint( From, To, length );
					if ( points != null )
						Graphics.DrawPolygon( pen, points );
				}
			}

			public Graphics Graphics { get { return graphics; } }
			public IConnection Connection { get { return connection; } }
			public Point From { get { return from; } }
			public Point To { get { return to; } }
			public bool Highlighted { get { return highlighted; } }
		}

		public delegate void DrawConnectionEventHandler( object sender, DrawConnectionEventArgs e );

		public event DrawConnectionEventHandler DrawConnection = null;

		protected virtual void OnDrawConnection( DrawConnectionEventArgs e )
		{
			if ( DrawConnection != null )
				DrawConnection( this, e );
		}

		#endregion

		#region OnPaint and appropriate virtual methods and events

		private void DrawSingleConnection( Graphics g, IConnection connection, Point from, Point to, bool highlighted )
		{
			DrawConnectionEventArgs drawConnectionArgs = new DrawConnectionEventArgs( g, connection, from, to, highlighted );
			if ( ConnectionOwnerDraw )
				OnDrawConnection( drawConnectionArgs );
			else
			{
				drawConnectionArgs.DrawLine( highlighted ? HighlightedColor : ConnectionColor, 1 );
				drawConnectionArgs.DrawArrows( 15.0f, connection.Selected ? SelectedShapeColor : ConnectionColor );
				if ( highlighted )
					drawConnectionArgs.OutlineArrows( 15.0f, HighlightedColor, 1 );
			}
		}

		private void DrawSingleShape( Graphics g, IShape shape, Rectangle bounds, bool highlighted )
		{
			DrawShapeEventArgs drawShapeArgs = new DrawShapeEventArgs( g, shape, bounds, highlighted );
			if ( ShapeOwnerDraw )
				OnDrawShape( drawShapeArgs );
			else
			{
				drawShapeArgs.FillShape( shape.Selected ? SelectedShapeColor : ShapeColor );
				drawShapeArgs.DrawFrame( highlighted ? HighlightedColor : ShapeFrameColor );
			}
		}

		protected override void OnPaint( PaintEventArgs e )
		{
			e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;

			using ( SolidBrush backBrush = new SolidBrush( BackColor ) )
				e.Graphics.FillRectangle( backBrush, e.ClipRectangle );

			// draw connections
			List<Connection> highlightedConnections = new List<Connection>();
			List<Connection> selectedConnections = new List<Connection>();
			foreach ( var connection in connections )
			{
				Point from = CanvasToClient( connection.FromPoint );
				Point to = CanvasToClient( connection.ToPoint );
				Rectangle bounds = new Rectangle( Math.Min( from.X, to.X ), Math.Min( from.Y, to.Y ), Math.Abs( from.X - to.X ), Math.Abs( from.Y - to.Y ) );
				if ( !e.ClipRectangle.IntersectsWith( bounds ) )
					continue;

				bool highlighted = false;
				if ( HighlightOutConnections && connection.From.Selected )
					highlighted = true;

				if ( highlighted )
				{
					highlightedConnections.Add( connection );
					continue;
				}

				if ( connection.Selected )
				{
					selectedConnections.Add( connection );
					continue;
				}

				DrawSingleConnection( e.Graphics, connection, from, to, false );
			}

			foreach ( var connection in selectedConnections )
				DrawSingleConnection( e.Graphics, connection, CanvasToClient( connection.FromPoint ), CanvasToClient( connection.ToPoint ), false );

			foreach ( var connection in highlightedConnections )
				DrawSingleConnection( e.Graphics, connection, CanvasToClient( connection.FromPoint ), CanvasToClient( connection.ToPoint ), true );

			if ( connectionCotr != null && connectionCotr.From != connectionCotr.To )
				DrawSingleConnection( e.Graphics, connectionCotr, CanvasToClient( connectionCotr.FromPoint ), CanvasToClient( connectionCotr.ToPoint ), false );

			// draw shapes
			foreach ( var shape in shapes )
			{
				Rectangle bounds = RectagleToClient( shape.Bounds );
				if ( !e.ClipRectangle.IntersectsWith( bounds ) )
					continue;

				bool highlighted = false;
				if ( !selectionRect.IsEmpty && HighlightPreselected && selectionRect.IntersectsWith( bounds ) )
					highlighted = true;
				if ( connectionCotr != null && HighlightPreconnected && connectionCotr.To == shape )
					highlighted = true;
				DrawSingleShape( e.Graphics, shape, bounds, highlighted );
			}

			// draw selection rectangle
			if ( !selectionRect.IsEmpty && e.ClipRectangle.IntersectsWith( selectionRect ) )
			{
				if ( SelectionAlpha > 0 )
				{
					using ( SolidBrush selectionBrush = new SolidBrush( Color.FromArgb( SelectionAlpha, SelectionColor ) ) )
						e.Graphics.FillRectangle( selectionBrush, selectionRect );
				}
				using ( Pen selectionPen = new Pen( SelectionColor, 1.0f ) )
					e.Graphics.DrawRectangle( selectionPen, selectionRect );
			}
		}

		#endregion

		#region private measurement functions

		private Size MeasureShapeInternal( IShape shape )
		{
			MeasureShapeEventArgs e = new MeasureShapeEventArgs( shape );
			if ( ShapeOwnerDraw )
				OnMeasureShape( e );

			return e.Size;
		}

		private Point FindConnectorInternal( IShape from, IShape to, bool backward )
		{
			FindConnectorEventArgs e = new FindConnectorEventArgs( from, to, backward );
			if ( ShapeOwnerDraw )
				OnFindConnector( e );

			return e.Location;
		}

		private Point FindConnectorInternal( IShape from, Point toPoint )
		{
			FindConnectorEventArgs e = new FindConnectorEventArgs( from, toPoint );
			if ( ShapeOwnerDraw )
				OnFindConnector( e );

			return e.Location;
		}

		#endregion

		#region Selection support

		public enum ApplySelectionAction
		{
			Select,
			Add,
			Exclude,
		}

		private Rectangle selectionRect = new Rectangle();

		public void SelectShape( IShape shape, ApplySelectionAction action )
		{
			SelectShapes( new IShape[] { shape }, action );
		}

		public void SelectShapes( IEnumerable<IShape> shapes, ApplySelectionAction action )
		{
			Dictionary<IShape, bool> shapesToSelect = new Dictionary<IShape, bool>();
			foreach ( var shape in shapes )
				if ( !shapesToSelect.ContainsKey( shape ) )
					shapesToSelect.Add( shape, true );

			foreach ( var shape in this.shapes )
			{
				switch ( action )
				{
				case ApplySelectionAction.Add:
					shape.Selected = true;
					break;
				case ApplySelectionAction.Select:
					shape.Selected = shapesToSelect.ContainsKey( shape );
					break;
				case ApplySelectionAction.Exclude:
					shape.Selected = shape.Selected && !shapesToSelect.ContainsKey( shape );
					break;
				}
			}

			Invalidate();
		}

		[Browsable( false )]
		public IEnumerable<IShape> Selected
		{
			get
			{
				List<IShape> selected = new List<IShape>();
				foreach ( var shape in shapes )
				{
					if ( shape.Selected )
						selected.Add( shape );
				}
				return selected;
			}
		}

		#endregion

		#region MouseMove actions

		public enum MouseMoveAction
		{
			None,
			Pan,
			Zoom,
			Select,
			Drag,
			Connect,
		}

		private MouseMoveAction mouseMoveAction = MouseMoveAction.None;
		private Point mouseMoveActionStart;
		private Point mouseMoveActionLast;

		protected override void OnMouseMove( MouseEventArgs e )
		{
			base.OnMouseMove( e );

			switch ( mouseMoveAction )
			{
			case MouseMoveAction.Pan:
				center -= ScaleSize( new Size( e.X - mouseMoveActionLast.X, e.Y - mouseMoveActionLast.Y ), scale );
				break;
			case MouseMoveAction.Zoom:
				{
					float delta = (float)( e.X - mouseMoveActionLast.X );
					float factor = delta < 0.0f ? ( 1.0f / ( 1.0f - delta * 0.005f ) ) : ( 1.0f + delta * 0.005f );
					scale *= factor;
				}
				break;
			case MouseMoveAction.Select:
				selectionRect = new Rectangle( Math.Min( e.X, mouseMoveActionStart.X ), Math.Min( e.Y, mouseMoveActionStart.Y ), Math.Abs( e.X - mouseMoveActionStart.X ), Math.Abs( e.Y - mouseMoveActionStart.Y ) );
				break;
			case MouseMoveAction.Drag:
				{
					Size shift = ScaleSize( new Size( e.X - mouseMoveActionLast.X, e.Y - mouseMoveActionLast.Y ), scale );
					foreach ( var shape in shapes )
					{
						if ( shape.Selected )
							shape.Location += shift;
					}
				}
				break;
			case MouseMoveAction.Connect:
				connectionCotr.SetToPoint( e.Location );
				break;
			default:
				return;
			}

			mouseMoveActionLast = e.Location;
			Invalidate();
		}

		protected override void OnMouseUp( MouseEventArgs e )
		{
			base.OnMouseUp( e );

			if ( mouseMoveAction == MouseMoveAction.Select )
				SelectShapes( FindShapesAtRectangle( selectionRect ), ApplySelectionAction.Select );
			else if ( mouseMoveAction == MouseMoveAction.Connect && connectionCotr.To != null )
				AddConnection( connectionCotr.From, connectionCotr.To, null );
			CancelMouseMoveAction();
		}

		public void StartMouseMoveAction( MouseMoveAction action, Point pt )
		{
			mouseMoveAction = action;
			mouseMoveActionLast = pt;
			mouseMoveActionStart = pt;

			if ( action == MouseMoveAction.None )
				CancelMouseMoveAction();
			else if ( action == MouseMoveAction.Connect )
			{
				IShape from = FindShapeAtPoint( pt );
				if ( from == null )
					CancelMouseMoveAction();
				else
					connectionCotr = new ConnectionConstructor( this, from );
			}
		}

		public void CancelMouseMoveAction()
		{
			mouseMoveAction = MouseMoveAction.None;
			selectionRect.Width = 0;
			selectionRect.Height = 0;
			connectionCotr = null;

			Invalidate();
		}

		#endregion

		#region public chart element controlleres

		public IShape AddShapeAtPoint( Point pt, object tag )
		{
			Shape result = new Shape( this, PointToCanvas( pt ), tag );
			shapes.Add( result );
			Invalidate();

			return result;
		}

		public IConnection AddConnection( IShape from, IShape to, object tag )
		{
			Shape fromShape = from as Shape;
			Shape toShape = to as Shape;

			Connection connection = new Connection( this, fromShape, toShape, tag );
			connections.Add( connection );
			fromShape.AddOut( connection );
			toShape.AddIn( connection );

			Invalidate();
			return connection;
		}

		public IShape FindShapeAtPoint( Point pt )
		{
			Point canvas = PointToCanvas( pt );
			foreach ( var shape in shapes )
				if ( shape.Bounds.Contains( canvas ) )
					return shape;

			return null;
		}

		public IShape[] FindShapesAtRectangle( Rectangle rect )
		{
			Rectangle canvas = RectangleToCanvas( rect );
			List<IShape> result = new List<IShape>();
			foreach ( var shape in shapes )
				if ( shape.Bounds.IntersectsWith( canvas ) )
					result.Add( shape );

			return result.ToArray();
		}

		private SizeF Mult( SizeF sz, float f )
		{
			return new SizeF( sz.Width * f, sz.Height * f );
		}

		public void OptimizeLayout()
		{
			float k = 10.0f;
			float t = 10.0f;

			PointF[] locations = new PointF[shapes.Count];
			for ( int i = 0; i < shapes.Count; ++i )
				locations[i] = shapes[i].Location;

			for ( int it = 0; it < 100; ++it )
			{
				SizeF[] disps = new SizeF[shapes.Count];
				for( int i =0 ; i < disps.Length; ++i )
					disps[i] = new SizeF( 0, 0 );

				for ( int vi = 0; vi < shapes.Count; ++vi )
				{
					Shape v = shapes[vi];
					for ( int ui = 0; ui < shapes.Count; ++ui )
					{
						Shape u = shapes[ui];
						if ( v == u )
							continue;

						SizeF d = new SizeF( v.Location.X - u.Location.X, v.Location.Y - u.Location.Y );
						float l = (float)Math.Sqrt( d.Width * d.Width + d.Height * d.Height );
						if ( l < 0.1f )
							continue;

						d = Mult( d, 1 / l );
						float r = 2500*k*k / l;

						disps[vi] += Mult( d, r );
						if ( v.IsConnectedTo( u ) )
						{
							float a = l * l / k;
							disps[vi] -= Mult( d, a );
							disps[ui] += Mult( d, a );
						}
					}
				}

				for ( int vi = 0; vi < shapes.Count; ++vi )
				{
					SizeF d = disps[vi];
					float l = (float)Math.Sqrt( d.Width * d.Width + d.Height * d.Height );
					if ( l < 0.1f )
						continue;

					if ( l > t )
						d = Mult( d, t / l );
					shapes[vi].Location += d.ToSize();
				}
			}

			Invalidate();
		}

		#endregion

		#region public view properties

		public Point Center { get { return center; } }
		public new float Scale { get { return scale; } }

		#endregion

		#region Control properties

		private Color selectionColor = Color.FromKnownColor( KnownColor.Highlight );
		[Category( "Appearance" )]
		[DefaultValue( typeof( Color ), "Highlight" )]
		public Color SelectionColor { get { return selectionColor; } set { selectionColor = value; Invalidate(); } }

		private int selectionAlpha = 48;
		[Category( "Appearance" )]
		[DefaultValue( 128 )]
		public int SelectionAlpha { get { return selectionAlpha; } set { selectionAlpha = value; Invalidate(); } }

		private Color shapeColor = Color.FromKnownColor( KnownColor.LightGray );
		[Category( "Appearance" )]
		[DefaultValue( typeof( Color ), "LightGray" )]
		public Color ShapeColor { get { return shapeColor; } set { shapeColor = value; Invalidate(); } }

		private Color shapeFrameColor = Color.FromKnownColor( KnownColor.Black );
		[Category( "Appearance" )]
		[DefaultValue( typeof( Color ), "Black" )]
		public Color ShapeFrameColor { get { return shapeFrameColor; } set { shapeFrameColor = value; Invalidate(); } }

		private Color selectedShapeColor = Color.FromKnownColor( KnownColor.Highlight );
		[Category( "Appearance" )]
		[DefaultValue( typeof( Color ), "Highlight" )]
		public Color SelectedShapeColor { get { return selectedShapeColor; } set { selectedShapeColor = value; Invalidate(); } }

		private Color connectionColor = Color.FromKnownColor( KnownColor.Black );
		[Category( "Appearance" )]
		[DefaultValue( typeof( Color ), "Black" )]
		public Color ConnectionColor { get { return connectionColor; } set { connectionColor = value; Invalidate(); } }

		private Color highlightedColor = Color.FromKnownColor( KnownColor.Highlight );
		[Category( "Appearance" )]
		[DefaultValue( typeof( Color ), "Highlight" )]
		public Color HighlightedColor { get { return highlightedColor; } set { highlightedColor = value; Invalidate(); } }

		[Category( "Behaviour" )]
		[DefaultValue( false )]
		public bool ShapeOwnerDraw = false;

		[Category( "Behaviour" )]
		[DefaultValue( false )]
		public bool ConnectionOwnerDraw = false;

		[Category( "Appearance" )]
		[DefaultValue( true )]
		public bool HighlightPreselected = true;

		[Category( "Appearance" )]
		[DefaultValue( true )]
		public bool HighlightPreconnected = true;

		[Category( "Appearance" )]
		[DefaultValue( true )]
		public bool HighlightOutConnections = true;

		#endregion
	}
}
