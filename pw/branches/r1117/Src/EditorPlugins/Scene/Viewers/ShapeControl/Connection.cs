using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace EditorPlugins.Scene.Viewers.ShapeControl
{
	public interface IConnection
	{
		IShape From { get; }
		IShape To { get; }

		object Tag { get; set; }
		bool Selected { get; }
	}
}
