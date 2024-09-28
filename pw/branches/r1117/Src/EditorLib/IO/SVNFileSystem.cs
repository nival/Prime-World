using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Net;
using System.Windows.Forms;
using System.Xml;
using libdb.Diagnostics;
using libdb.IO;
using SharpSvn;
using SharpSvn.UI;

namespace EditorLib.IO
{
	public class SVNFileSystem : WinFileSystem
	{
		private static readonly SvnClient svnClient = new SvnClient();
		private string repositoryURL;

		public SVNFileSystem(string _fileSystemRoot, bool _writable)
			: base( _fileSystemRoot, _writable )
		{
		}

		public SVNFileSystem()
		{
		}

		/// <summary>
		/// Подключает встроенную в SharpSvn форму логина в SVN
		/// </summary>
		/// <param name="form">Родительская форма для модального диалога</param>
		public static void BindSVNAuthDialogToForm(IWin32Window form)
		{
			SvnUI.Bind( svnClient, form );
		}

		public void InitNonGuiMode(string user, string pass)
		{
			svnClient.Authentication.DefaultCredentials = new NetworkCredential( user, pass );
		}

		private bool IsDeleted( string path )
		{
			try
			{
				Collection<SvnStatusEventArgs> outp;
				svnClient.GetStatus( CombinePath( path ), new SvnStatusArgs() { Depth = SvnDepth.Empty }, out outp );
				if ( outp == null )
					return false;

				foreach (var s in outp)
					if (s.LocalContentStatus == SvnStatus.Deleted )
						return true;
			}catch(Exception ex)
			{
				Log.TraceWarning( ex.ToString() );
			}
			
			return false;
		}

		private bool IsVersioned(string path)
		{
		  try
		  {
        Collection<SvnStatusEventArgs> outp;
        svnClient.GetStatus( CombinePath( path ), out outp );
        if( outp == null )
          return false;

        foreach( var s in outp )
          if( s.LocalContentStatus == SvnStatus.NotVersioned
               || s.LocalContentStatus == SvnStatus.Missing
               || s.LocalContentStatus == SvnStatus.Deleted )
            return false;

        return true;
		  }
		  catch
		  {
		    
		  }

      return false;
		}

    private void DoSvnOperation( SVNOperation op, string path, string path2 )
    {
      bool isVersioned = IsVersioned( path );
      int attempt = 0;
      while( ++attempt < 3 )
      {
        try
        {
          switch( op )
          {
            case SVNOperation.Add:
              if( !isVersioned )
                svnClient.Add( CombinePath( path ) );
              break;
            case SVNOperation.Delete:
              if( isVersioned )
                svnClient.Delete( CombinePath( path ), new SvnDeleteArgs { Force = true } );
              break;
            case SVNOperation.Rename:
              if( isVersioned )
                svnClient.Move( CombinePath( path ), CombinePath( path2 ) );
              break;
          }
        }
        catch( SvnException ex )
        {
          if( ex.SvnErrorCode == SvnErrorCode.SVN_ERR_WC_LOCKED )
          {
            Log.TraceWarning( "Cleaning up working copy. Please wait." );
            svnClient.CleanUp( fileSystemRoot );
            continue;
          }
          
          if( ex.SvnErrorCode == SvnErrorCode.SVN_ERR_ENTRY_EXISTS )
            break;

          if( ex.SvnErrorCode == SvnErrorCode.SVN_ERR_WC_NOT_DIRECTORY )
          {
            AddToWorkingCopy( path );
            continue;
          }

          Log.TraceError( ex.ToString() );
        }
        break;
      }
    }

    private void AddToWorkingCopy(string path)
    {
        string[] dirs = Path.GetDirectoryName(path).Split( new [] {'\\', '/'}, StringSplitOptions.RemoveEmptyEntries );
        string currentDir = string.Empty;

        foreach(string dir in dirs)
        {
          try
          {
            currentDir += @"\" + dir;
            svnClient.Add( CombinePath(currentDir), SvnDepth.Empty );
            Log.TraceWarning( "Folder \"{0}\" added to working copy", currentDir );
          }
          catch( SvnException ex )
          {
            if( ex.SvnErrorCode == SvnErrorCode.SVN_ERR_ENTRY_EXISTS )
              continue;

            Log.TraceError( ex.Message );
          }
        } 
    }

		public void RenameFile(string oldName, string newName)
		{
			DoSvnOperation( SVNOperation.Rename, oldName, newName );
		}

		#region Overrided WinFileSystem members
	  public override string[] GetFolders(string root, string mask)
	  {
	  	List<string> ret = new List<string>();
	  	foreach(var s in base.GetFolders( root, mask ))
				if ( !IsDeleted( s ) )
					ret.Add( s );
	  	return ret.ToArray();
	  }

		new public string[] GetFiles(string root, string mask)
		{
			List<string> ret = new List<string>();
			foreach ( var s in base.GetFiles( root, mask ) )
				if ( !IsDeleted( s ) )
					ret.Add( s );
			return ret.ToArray();
		}

		public override bool Configure()
		{
			var form = new SVNFileSysConfigure();
			form.tbRepo.Text = repositoryURL;
			form.tbFSRoot.Text = fileSystemRoot;

			if ( form.ShowDialog() != DialogResult.OK )
				return false;

			fileSystemRoot = FileUtils.FixFolderName( form.tbFSRoot.Text );
			repositoryURL = form.tbRepo.Text;

			return true;
		}

		public override Stream CreateFile(string _fileName)
		{
			var stream = base.CreateFile( _fileName );
			if ( stream == null )
				return null;

			stream.Close();
			stream.Dispose();

			DoSvnOperation( SVNOperation.Add, _fileName, null );

			return new FileStream( CombinePath( _fileName ), FileMode.Open, FileAccess.ReadWrite, FileShare.ReadWrite );
		}

		public override void Serialize(XmlWriter writer)
		{
			base.Serialize( writer );
			writer.WriteStartElement( "SVNRepositoryUrl" );
			if ( repositoryURL != null )
				writer.WriteValue( repositoryURL );

			writer.WriteEndElement();
		}

		public override void Deserialize(XmlReader reader)
		{
			base.Deserialize( reader );
			reader.ReadStartElement( "SVNRepositoryUrl" );
			repositoryURL = reader.ReadString();
			reader.ReadEndElement();
		}

		public override void DeleteFile(string _fileName)
		{
			if ( File.Exists( CombinePath( _fileName ) ) )
				DoSvnOperation( SVNOperation.Delete, _fileName, null );
		}

		public override void CreatePhysicalDirectory(string folderName)
		{
      if ( !Directory.Exists( CombinePath( FileUtils.GetParentFolderPath( folderName ) ) ) )
        CreatePhysicalDirectory( FileUtils.GetParentFolderPath( folderName ) );

			base.CreatePhysicalDirectory( folderName );
			DoSvnOperation( SVNOperation.Add, folderName, null );
		}

		public override void DeletePhysicalDirectory(string folderName)
		{
			DoSvnOperation( SVNOperation.Delete, folderName, null );
		///	base.DeletePhysicalDirectory( folderName );
		}

		#endregion

		#region Nested type: SVNOperation

		private enum SVNOperation
		{
			Add,
			Delete,
			Rename
		}

		#endregion
	}
}