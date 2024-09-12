using System.IO;
using System.Windows.Forms;
using EditorLib.IO;
using libdb.IO;

namespace EditorLib.PropertiesEditor
{
	internal sealed class BrowseSourceFileQueryObject : BrowseQueryObject
	{
		#region Private members.

		private readonly SourceFileSystem sourceFileSystem;
		private readonly string description;
		private readonly string extensions;
		private readonly string relativeDirectoryPath;

		#endregion

		#region Intialization.

		internal BrowseSourceFileQueryObject(
			SourceFileSystem _sourceFileSystem,
			string _description,
			string _extensions,
			string _relativeDirectoryPath
			)
		{
			description = _description;
			extensions = _extensions;
			sourceFileSystem = EditorCommonApplication.ApplicationSingleton.SourceFileSystem;
			relativeDirectoryPath = _relativeDirectoryPath;
		}

		#endregion

		#region Public methods.

		public override object PerformBrowsing()
		{
			OpenFileDialog dialog = new OpenFileDialog();
			dialog.RestoreDirectory = true;
			dialog.Filter = description + "|" + extensions;
			dialog.InitialDirectory = SourceDirectory;

			if ( dialog.ShowDialog() == DialogResult.OK )
			{
				if ( Path.GetDirectoryName( dialog.FileName ).StartsWith( RootDirectory ) )
				{
					return FileFromRootDirectorySelected( dialog.FileName );
				}
				else
				{
					return FileFromNonRootDirectorySelected( dialog.FileName );
				}
			}
			else
			{
				return null;
			}
		}

		#endregion

		#region Private helper methods.

		private object FileFromRootDirectorySelected( string fileName )
		{
			if ( SourceDirectory == Path.GetDirectoryName( fileName ) )
			{
				// Other file from the same directory.
				return GetRelativePath( fileName );
			}
			else
			{
				// File from the other source directory.
				MessageBox.Show(
					string.Format(
						"Cannot select file from directory \"{0}\"." +
						"You cannot select files from another source directories but " +
						"you can get files from any non source directory or from " +
						"source directory correspond to the current destination directory " +
						"(now it is: \"{1}\").",
						fileName,
						SourceDirectory
						),
					"Error",
					MessageBoxButtons.OK,
					MessageBoxIcon.Error
					);
				return PerformBrowsing();
			}
		}

		private object FileFromNonRootDirectorySelected( string fileName )
		{
			var pathToCopy = FileUtils.Combine( SourceDirectory, Path.GetFileName( fileName ) );

			if ( sourceFileSystem.IsFileExists( GetRelativePath( pathToCopy ) ) )
			{
				return ReplaceFileNeeded( fileName );
			}
			else
			{
				return CopyFileNeeded( fileName );
			}
		}

		private object ReplaceFileNeeded( string fileName )
		{
			var result = MessageBox.Show(
				string.Format(
					"You selected file from non source directory \"{0}\". " +
					"But there is a file with the same name in the source directory (\"{1}\"). " +
					"Do you want to replace it?",
					fileName,
					SourceDirectory
					),
				"Question",
				MessageBoxButtons.YesNo,
				MessageBoxIcon.Question
				);
			if ( result == DialogResult.Yes )
			{
				return AddFileToSourceFileSystem( fileName, true );
			}
			else
			{
				return null;
			}
		}

		private object CopyFileNeeded( string fileName )
		{
			var result = MessageBox.Show(
				string.Format(
					"You selected file from non source directory \"{0}\". " +
					"Do you want to copy file to the source directory (\"{1}\")?",
					fileName,
					SourceDirectory
					),
				"Question",
				MessageBoxButtons.YesNo,
				MessageBoxIcon.Question
				);
			if ( result == DialogResult.Yes )
			{
				return AddFileToSourceFileSystem( fileName, false );
			}
			else
			{
				return null;
			}
		}

		private string AddFileToSourceFileSystem( string path, bool overwrite )
		{
			var pathToCopy = FileUtils.Combine( SourceDirectory, Path.GetFileName( path ) );

			if ( !Directory.Exists( Path.GetDirectoryName( pathToCopy ) ) )
			{
				Directory.CreateDirectory( Path.GetDirectoryName( pathToCopy ) );
			}

			var relativePath = GetRelativePath( pathToCopy );
			sourceFileSystem.AddFile( relativePath, path, overwrite );

			return relativePath;
		}

		public override string ToString()
		{
			return BROWSE_STRING;
		}

		private string GetRelativePath( string path )
		{
			return sourceFileSystem.GetRelativePath( path );
		}

		private string RootDirectory
		{
			get { return sourceFileSystem.RootPath; }
		}

		private string SourceDirectory
		{
			get { return sourceFileSystem.GetFullDirectory( relativeDirectoryPath ); }
		}

		#endregion
	}
}
