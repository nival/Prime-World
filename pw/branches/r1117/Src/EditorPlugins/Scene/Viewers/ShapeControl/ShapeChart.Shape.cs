using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace EditorPlugins.Scene.Viewers.ShapeControl
{
	public partial class ShapeChart
	{
		private class Shape : IShape
		{
			private readonly ShapeChart owner = null;
			private readonly List<Connection> outs = new List<Connection>();
			private readonly List<Connection> ins = new List<Connection>();

			private object tag = null;
			private bool selected = false;

			private Point location = new Point( 0, 0 );
			private Size size = new Size( 0, 0 );

			private Rectangle bounds = new Rectangle( 0, 0, 0, 0 );

			public Shape( ShapeChart owner, Point location, object tag )
			{
				this.owner = owner;
				this.location = location;
				this.tag = tag;

				Resize();
			}

			private void RecalculateBounds()
			{
				bounds.X = location.X - size.Width / 2;
				bounds.Y = location.Y - size.Height / 2;
				bounds.Width = size.Width;
				bounds.Height = size.Height;
			}

			private void ReconnectConnections()
			{
				foreach ( var connection in outs )
					connection.Reconnect();
				foreach ( var connection in ins )
					connection.Reconnect();
			}

			public bool AddOut( Connection connection )
			{
				if ( connection.From != this )
					return false;

				foreach ( var con in outs )
					if ( con.To == connection.To )
						return false;

				outs.Add( connection );
				return true;
			}

			public bool AddIn( Connection connection )
			{
				if ( connection.To != this )
					return false;

				foreach ( var con in ins )
					if ( con.From == connection.From )
						return false;

				ins.Add( connection );
				return true;
			}

			public bool IsConnectedTo( IShape shape )
			{
				foreach ( var con in outs )
					if ( con.To == shape )
						return true;

				return false;
			}

			public void Resize()
			{
				size = owner.MeasureShapeInternal( this );
				RecalculateBounds();
			}

			public Point Location { get { return location; } set { location = value; ReconnectConnections(); RecalculateBounds(); } }
			public Size Size { get { return size; } }
			public Rectangle Bounds { get { return bounds; } }

			public object Tag { get { return tag; } set { tag = value; } }
			public bool Selected { get { return selected; } set { selected = value; } }

			public IEnumerable<IConnection> Outs { get { return outs as IEnumerable<IConnection>; } }
			public IEnumerable<IConnection> Ins { get { return ins as IEnumerable<IConnection>; } }
		}
	}
}
