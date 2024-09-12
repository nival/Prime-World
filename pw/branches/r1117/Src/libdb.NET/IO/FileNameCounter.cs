using System;
using System.Collections.Generic;
using System.Text;
using System.Globalization;
using System.IO;

namespace libdb.IO
{
	/// <summary>
	/// Enumerate files by mask. Extract digits part from file at increment it count times. I.e. from c:\temp\test002.png with count equals 5 we've get c:\temp\test002.png, c:\temp\test003.png, ... c:\temp\test007.png
	/// </summary>
	public sealed class FileNameCounter : IEnumerable<string>
  {
    #region private class FileNameEnumerator : IEnumerator<string>

    private class FileNameEnumerator : IEnumerator<string>
		{
			private readonly FileNameCounter owner;
			private int index = 0;

			public FileNameEnumerator( FileNameCounter owner )
			{
				this.owner = owner;
				index = this.owner.min;
			}

			public string Current
			{
				get { return owner.Format( index ); }
			}

			public void Dispose()
			{

			}

			object System.Collections.IEnumerator.Current
			{
				get { return Current; }
			}

			public bool MoveNext()
			{
				if ( index >= owner.max )
					return false;
				++index;
				return true;
			}

			public void Reset()
			{
				index = owner.min;
			}
		}

		#endregion

		private readonly string fileName;
		private readonly string extension;
		private readonly int max;
		private readonly int min;
    private readonly int digitsCount;

		public FileNameCounter( string fileName, int count )
		{
			this.fileName = FileUtils.Combine( FileUtils.GetParentFolderPath( fileName ), FileUtils.GetFileNameWithoutExtension( fileName ) );
			this.extension = Path.GetExtension( fileName );
			this.digitsCount = 0;
      while ( this.digitsCount < this.fileName.Length && char.IsDigit( this.fileName[this.fileName.Length - this.digitsCount - 1] ) )
        ++this.digitsCount;

      this.min = int.Parse( this.fileName.Substring( this.fileName.Length - this.digitsCount ) );
			this.max = this.min + count - 1;
      this.fileName = this.fileName.Substring( 0, this.fileName.Length - this.digitsCount );
		}

		public IEnumerator<string> GetEnumerator()
		{
			return new FileNameEnumerator( this );
		}

		System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
		{
			return GetEnumerator();
		}

		public string Format( int index )
		{
      string result = index.ToString();
      while ( result.Length < digitsCount )
        result = "0" + result;

      return fileName + result + extension;
		}

		public int Min { get { return min; } }
		public int Max { get { return max; } }
	}
}
