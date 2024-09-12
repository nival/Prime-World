using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace EditorPlugins.Scene.Viewers.ShapeControl
{
	public partial class ShapeChart
	{
		private class Connection : IConnection
		{
			private readonly ShapeChart owner = null;
			private readonly Shape from = null;
			private readonly Shape to = null;

			private object tag = null;
			private bool selected = false;

			private Point fromPoint;
			private Point toPoint;

			public Connection( ShapeChart owner, Shape from, Shape to, object tag )
			{
				this.owner = owner;
				this.from = from;
				this.to = to;
				this.tag = tag;

				Reconnect();
			}

			public void Reconnect()
			{
				fromPoint = owner.FindConnectorInternal( From, To, false );
				toPoint = owner.FindConnectorInternal( To, From, true );
			}

			public IShape From { get { return from; } }
			public IShape To { get { return to; } }

			public Point FromPoint { get { return fromPoint; } }
			public Point ToPoint { get { return toPoint; } }

			public object Tag { get { return tag; } set { tag = value; } }
			public bool Selected { get { return selected; } set { selected = value; } }
		}

		private class ConnectionConstructor : IConnection
		{
			private readonly ShapeChart owner = null;
			private readonly IShape from = null;
			private IShape to = null;

			private Point fromPoint;
			private Point toPoint;

			public ConnectionConstructor( ShapeChart owner, IShape from )
			{
				this.owner = owner;
				this.from = from;

				toPoint = from.Location;

				Reconnect();
			}

			public void Reconnect()
			{
				if ( to != null )
				{
					fromPoint = owner.FindConnectorInternal( From, To, false );
					toPoint = owner.FindConnectorInternal( To, From, true );
				}
				else
				{
					fromPoint = owner.FindConnectorInternal( From, ToPoint );
				}
			}

			public void SetToPoint( Point pt )
			{
				toPoint = owner.PointToCanvas( pt );
				to = owner.FindShapeAtPoint( pt );

				Reconnect();
			}

			public IShape From { get { return from; } }
			public IShape To { get { return to; } }

			public Point FromPoint { get { return fromPoint; } }
			public Point ToPoint { get { return toPoint; } }

			public object Tag { get { return null; } set { } }
			public bool Selected { get { return false; } }
		}
	}
}
