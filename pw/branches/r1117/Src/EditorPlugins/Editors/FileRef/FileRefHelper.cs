using System;
using System.IO;
using System.Windows.Forms;
using libdb;
using libdb.DB;
using libdb.IO;

namespace EditorPlugins.Editors.FileRef
{
  internal static class FileRefHelper
  {
    public static string GetFile( object _instance, string _initFile, string _validExtension )
    {
      string dataPath = FileUtils.FixFileName( Path.GetFullPath( "..\\Data\\" ) );
      string initialPath = dataPath;
      string initialFileName = FileUtils.FixFileName( _initFile );

      if( string.IsNullOrEmpty( initialFileName ) )
      {
        if( _instance is DBResource )
          initialPath = Path.Combine( dataPath, Path.GetDirectoryName( ( _instance as DBResource ).DBId.FileName ) );
        else if( _instance is IOwnerable )
        {
          IOwnerable ownerable = _instance as IOwnerable;
          if( ownerable.GetOwner() != null )
            initialPath = Path.Combine( dataPath, Path.GetDirectoryName( ownerable.GetOwner().DBId.FileName ) );
        }
      }
      else
      {
        if( initialFileName.StartsWith( FileUtils.PathSeparatorString ) )
          initialFileName = Path.Combine( dataPath, initialFileName.Substring( 1 ) );
        else
          initialFileName = Path.GetFullPath( initialFileName );

        initialPath = Path.GetDirectoryName( initialFileName );
      }

      OpenFileDialog dlg = new OpenFileDialog()
      {
        Filter = string.Format( "{0}|{0}", _validExtension ),
        InitialDirectory = initialPath,
        Multiselect = false,
        RestoreDirectory = true
      };
      if( dlg.ShowDialog() == DialogResult.Cancel )
        return _initFile;

      string result = FileUtils.FixFileName( dlg.FileName );
      if( result.StartsWith( dataPath, StringComparison.InvariantCultureIgnoreCase ) )
        return FileUtils.PathSeparatorChar + result.Substring( dataPath.Length ); // keep first slash;

      if( MessageBox.Show( null, "Chosen file is outside Data folder. Do you really want to choose it?", 
          "File Outside Data Folder", 
          MessageBoxButtons.YesNo, 
          MessageBoxIcon.Question ) == DialogResult.No )
      {
        return _initFile;
      }

      return result;
    }
  }
}
