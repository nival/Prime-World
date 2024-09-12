using System;

namespace EditorLib.Utils
{
	[System.ComponentModel.EditorBrowsable( System.ComponentModel.EditorBrowsableState.Never )]
	public static class ListViewSortIconExtension
	{
		[System.Runtime.InteropServices.StructLayout( System.Runtime.InteropServices.LayoutKind.Sequential )]
		private struct LVCOLUMN
		{
			public Int32 mask;
			public Int32 cx;
			[System.Runtime.InteropServices.MarshalAs( System.Runtime.InteropServices.UnmanagedType.LPTStr )]
			public string pszText;
			public IntPtr hbm;
			public Int32 cchTextMax;
			public Int32 fmt;
			public Int32 iSubItem;
			public Int32 iImage;
			public Int32 iOrder;
		}

		private const Int32 HDI_FORMAT = 0x4;
		private const Int32 HDF_SORTUP = 0x400;
		private const Int32 HDF_SORTDOWN = 0x200;
		private const Int32 LVM_GETHEADER = 0x101f;
		private const Int32 HDM_GETITEM = 0x120b;
		private const Int32 HDM_SETITEM = 0x120c;

		[System.Runtime.InteropServices.DllImport( "user32.dll" )]
		private static extern IntPtr SendMessage( IntPtr hWnd, uint Msg, IntPtr wParam, IntPtr lParam );

		[System.Runtime.InteropServices.DllImport( "user32.dll", EntryPoint = "SendMessage" )]
		private static extern IntPtr SendMessageLVCOLUMN( IntPtr hWnd, Int32 Msg, IntPtr wParam, ref LVCOLUMN lPLVCOLUMN );

		public static void SetSortIcon( System.Windows.Forms.ListView ListViewControl, int ColumnIndex, System.Windows.Forms.SortOrder Order )
		{
			IntPtr ColumnHeader = SendMessage( ListViewControl.Handle, LVM_GETHEADER, IntPtr.Zero, IntPtr.Zero );

			for ( int ColumnNumber = 0; ColumnNumber <= ListViewControl.Columns.Count - 1; ColumnNumber++ )
			{
				IntPtr ColumnPtr = new IntPtr( ColumnNumber );
				LVCOLUMN lvColumn = new LVCOLUMN();
				lvColumn.mask = HDI_FORMAT;
				SendMessageLVCOLUMN( ColumnHeader, HDM_GETITEM, ColumnPtr, ref lvColumn );

				if ( !( Order == System.Windows.Forms.SortOrder.None ) && ColumnNumber == ColumnIndex )
				{
					switch ( Order )
					{
					case System.Windows.Forms.SortOrder.Ascending:
						lvColumn.fmt &= ~HDF_SORTDOWN;
						lvColumn.fmt |= HDF_SORTUP;
						break;
					case System.Windows.Forms.SortOrder.Descending:
						lvColumn.fmt &= ~HDF_SORTUP;
						lvColumn.fmt |= HDF_SORTDOWN;
						break;
					}
				}
				else
				{
					lvColumn.fmt &= ~HDF_SORTDOWN & ~HDF_SORTUP;
				}

				SendMessageLVCOLUMN( ColumnHeader, HDM_SETITEM, ColumnPtr, ref lvColumn );
			}
		}
	}
}
