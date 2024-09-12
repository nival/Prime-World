namespace EditorPlugins.Scene.Editors.Drawing
{
	internal sealed class TerrainBrush
	{
		private bool[,] powers = new bool[0,0];

		internal bool this[int row, int column]
		{
			get { return powers[row, column]; }
		}

		internal int Width
		{
			get { return powers.GetLength( 1 ); }
		}
		
		internal int Height
		{
			get { return powers.GetLength( 0 ); }
		}

		internal int Size
		{
			set
			{
				powers = new bool[value, value];
				for ( int i = 0; i < value; ++i )
				{
					for ( int j = 0; j < value; ++j )
					{
						powers[i, j] = true;
					}
				}
			}
		}
	}
}
