using System;

namespace libdb.IO
{
	public sealed class FileInformation
	{
		readonly private bool isFileExists = false;
		readonly private bool isFolderExists = false;
		readonly private DateTime time = DateTime.FromBinary( 0 );
		readonly private int size = 0;
		readonly private IFileSystem ownerFileSystem = null;

		/// <summary>
		/// Default constructor for FileInformation. Means file doesn't exist
		/// </summary>
		public FileInformation() { }

		/// <summary>
		/// Constructor for FileInformation. Means file exists
		/// </summary>
		/// <param name="_time">Time for this file. Meaning of this value depends on IFileSystem</param>
		/// <param name="_ownerFileSystem">IFileSystem thru this file accessed</param>
		public FileInformation( DateTime _time, int _size, IFileSystem _ownerFileSystem )
		{
			isFolderExists = false;
			isFileExists = true;
			time = _time;
			size = _size;
			ownerFileSystem = _ownerFileSystem;
		}
		public FileInformation( DateTime _time, int _size, IFileSystem _ownerFileSystem, bool _isFolder )
		{
			isFolderExists = _isFolder;
			isFileExists = !_isFolder;
			time = _time;
			size = _size;
			ownerFileSystem = _ownerFileSystem;
		}

		/// <summary>
		/// Does file folder
		/// </summary>
		public bool IsFolderExists { get { return isFolderExists; } }

		/// <summary>
		/// Does file exist
		/// </summary>
		public bool IsFileExists { get { return isFileExists; } }

		/// <summary>
		/// Time for this file. Meaning of this value depends on IFileSystem
		/// </summary>
		public DateTime Time { get { return time; } }

		/// <summary>
		/// Size of file
		/// </summary>
		public int Size { get { return size; } }

		/// <summary>
		/// IFileSystem thru this file accessed
		/// </summary>
		public IFileSystem OwnerFileSystem { get { return ownerFileSystem; } }
	};

}
