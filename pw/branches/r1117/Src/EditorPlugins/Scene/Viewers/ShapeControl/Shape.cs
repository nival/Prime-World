using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace EditorPlugins.Scene.Viewers.ShapeControl
{
	public interface IShape
	{
		bool IsConnectedTo( IShape shape );

		void Resize();

		Point Location { get; }
		Size Size { get; }
		Rectangle Bounds { get; }

		object Tag { get; set; }
		bool Selected { get; }

		IEnumerable<IConnection> Outs { get; }
		IEnumerable<IConnection> Ins { get; }
	}
}
