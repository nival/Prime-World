using System;
using System.Collections.Generic;
using System.Text;

namespace EditorLib.Menu
{
	class MenuGroup: MenuItem
	{
		private Guid guid = Guid.Empty;
		public MenuGroup( Guid _guid, int _sortIndex, string _name ):base(_sortIndex, _name)
		{
			guid = _guid;
		}
		public override bool Visible
		{
			get
			{
				if( Name != null && Name != string.Empty )
				{
					return true;
				}
				if ( Items.Count == 0 )
				{
					return false;
				}
				for ( int i = 0; i < Items.Count; i++ )
				{
					if ( Items[i].Visible  )
					{
						return true;
					}
				}
				return false;
			}
		}
		public override bool Enabled
		{
			get
			{
				if ( Items.Count > 0 )
				{
					return true;
				}
				return false;
			}
		}

	}
}
