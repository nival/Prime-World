using System;
using System.IO;
using System.Xml;

namespace libdb.IO
{
	/// <summary>
	/// Interface for file systems
	/// </summary>
	public interface IFileSystem
	{
    /// <summary>
    /// Gets the names of subdirectories in a specified directory
    /// </summary>
    /// <param name="root">The path to search</param>
    /// <returns>A String array of directories</returns>
    string[] GetFolders( string root );

		/// <summary>
		/// Gets the names of subdirectories in a specified directory
		/// </summary>
		/// <param name="root">The path to search</param>
		/// <param name="mask">The search string to match against the names of files in path</param>
		/// <returns>A String array of directories matching the search pattern</returns>
		string[] GetFolders( string root, string mask );
		
		/// <summary>
		/// Gets the names of files in a specified directory
		/// </summary>
		/// <param name="root">The path to search</param>
		/// <param name="mask">The search string to match against the names of files in path</param>
		/// <returns>A String array of files matching the search pattern</returns>
		string[] GetFiles( string root, string mask );

		/// <summary>
		/// Gets FileInformation for specified file
		/// </summary>
		/// <param name="fileName">The name of file to get information</param>
		/// <returns>FileInformation for specified file</returns>
		FileInformation GetFileInfo( string fileName );

		/// <summary>
		/// Opens specified file
		/// </summary>
		/// <param name="fileName">The name of file to open</param>
		/// <returns>Stream object for specified file or null if file cannot be opened</returns>
		Stream OpenFile( string fileName );

		/// <summary>
		/// Creates specified file
		/// </summary>
		/// <param name="fileName">The name of file to open</param>
		/// <returns>Stream object for specified file or null if file cannot be created</returns>
		Stream CreateFile( string fileName );

		/// <summary>
		/// Create specified folder
		/// </summary>
		/// <param name="folderName"></param>
		void CreateFolder( string folderName );

		/// <summary>
		/// Deletes specified file
		/// </summary>
		/// <param name="fileName">The name of file to delete (only works if filesystem is writeable)</param>
		void DeleteFile( string fileName );

		/// <summary>
		/// Delete specified folder
		/// </summary>
		/// <param name="folderName"></param>
		void DeleteFolder( string folderName );

		/// <summary>
		/// False if this instance of file system is read-only
		/// </summary>
		bool CanCreateFile { get; }

		/// <summary>
		/// User friendly unique name for this instance of file system. Used only in user interfaces
		/// </summary>
		string UserFriendlyName { get; }

		/// <summary>
		/// Returns real file name of specified file. Needed for some external tools. If needed file can be packed back in IFileSystem destructor
		/// </summary>
		/// <param name="fileName">Filename</param>
		/// <returns>Name of real (on local disk maybe in temporary folder) file</returns>
		string GetRealFileName( string fileName );

		string RootPath { get; }

		void Store();
	};
}
