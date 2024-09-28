using System;
using System.Collections.Generic;
using System.ComponentModel;
using libdb.Diagnostics;
using System.Text;
using System.Windows.Forms;
using libdb.DB;

namespace EditorLib.PropertiesEditor
{
	public partial class FlagsEnumControl : CheckedListBox
	{
		private readonly Type enumType = null;
		private readonly List<int> values = null;
		private int value = 0;
		private bool updateItems = false;

		public FlagsEnumControl()
		{
			InitializeComponent();
		}

		public FlagsEnumControl( IContainer container )
		{
			container.Add( this );

			InitializeComponent();
		}

    public FlagsEnumControl( Enum value, HideEnumValuesAttribute hideValues )
		{
			InitializeComponent();

			enumType = value.GetType();

			values = new List<int>();
			foreach( string name in Enum.GetNames( enumType ) )
			{
				int intValue = (int)Enum.Parse( enumType, name );
				if ( intValue == 0 || ( hideValues != null && hideValues.Contains( name ) ) )
					continue;
				values.Add( intValue );
				Items.Add( name, false );
			}

			this.value = (int)(object)value;
			CheckOnClick = true;
			IntegralHeight = false;
			UpdateItems();
		}

		private void UpdateItems()
		{
			updateItems = true;
			for( int i = 0; i < Items.Count; ++i )
				SetItemChecked( i, ( value & values[i] ) == values[i] );
			updateItems = false;
		}

		protected override void OnItemCheck( ItemCheckEventArgs ice )
		{
			if ( updateItems )
				return;

			if ( ice.CurrentValue != ice.NewValue )
			{
				if ( ice.NewValue == CheckState.Checked )
					value |= values[ice.Index];
				else
					value = ( value | values[ice.Index] ) ^ values[ice.Index];
				UpdateItems();
			}
			base.OnItemCheck( ice );
		}

		public Enum Value { get { return Enum.ToObject( enumType, value ) as Enum; } }
	}
}
