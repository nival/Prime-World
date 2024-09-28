using System;

namespace PWLocalizator
{
	public class Table
	{
		private string name;
		private int cols;
		private int rows;
		private int realCols;
		private int realRows;
		private string[,] data;

		public Table( string name, int reserveCols, int reserveRows )
		{
			this.name = name;
			realCols = reserveCols;
			realRows = reserveRows;
			cols = 0;
			rows = 0;
			data = new string[realCols, realRows];
		}

		public string Name { get { return name; } }
		public int Columns { get { return cols; } }
		public int Rows { get { return rows; } }
		public string this[int col, int row]
		{
			get
			{
				if ( col < 0 || col >= Columns || row < 0 || row >= Rows )
					throw new ArgumentException( String.Format( "Cannot get value for cell {0}x{1}, size of table {2}x{3}", col, row, Columns, Rows ) );
				return data[col, row];
			}
			set
			{
				if ( col < 0 || col >= realCols || row < 0 || row >= realRows )
					throw new ArgumentException( String.Format( "Cannot set value for cell {0}x{1}, size of table {2}x{3}", col, row, realCols, realRows ) );
				data[col, row] = value;
				if ( !string.IsNullOrEmpty( value ) )
				{
					if ( col >= Columns )
						cols = col + 1;
					if ( row >= Rows )
						rows = row + 1;
				}
			}
		}
	}
}
