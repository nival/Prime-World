using System.Windows.Forms;
using System.Collections.Generic;

namespace EditorLib.Binds
{
	public sealed class BindConfig
	{
		public float deltaSpeed = 0;
		public MouseAxis mouseAxis = MouseAxis.None;
		public MouseButtons mouseButtons = MouseButtons.None;
		public List<Keys> keys = new List<Keys>();
		public bool invertMouse = false;
		public bool invertKey = false;
    public bool ignoreKeys = false;
    public List<Keys> badKeys = new List<Keys>();
	}
}
