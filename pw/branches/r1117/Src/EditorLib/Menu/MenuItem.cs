using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace EditorLib.Menu
{
	internal abstract class MenuItem
	{
    public abstract bool Enabled { get; }

    public abstract bool Visible { get; }
		public virtual string Name
		{
			get { return _name; }
		}

    public ToolStripMenuItem Control = null;

		public int SortIndex { get { return sortIndex; } }
		public List<MenuItem> Items { get { return _items; } }
		public MenuItem(  int _sortIndex, string _text )
		{
			_name = _text;
			sortIndex = _sortIndex;
		}
		private int sortIndex = 0;
		private string _name;
		private List<MenuItem> _items = new List<MenuItem>();
	}
}
