using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using EditorLib;
using EditorLib.IO;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;
using SharpSvn;

namespace EditorPlugins.Committer
{
  internal class DualCommitDataCollater
  {
    #region Private Fields

    private readonly SvnClient client = new SvnClient();
    private readonly FieldsWalker.DepthController depthControl = new FieldsWalker.DepthController( 0, FieldsWalker.ObjectType.None, FieldsWalker.ObjectType.All & ~FieldsWalker.ObjectType.DBPtrUninlined );

    private readonly List<ChangeItemInfo> xdbDataChanges = new List<ChangeItemInfo>();
    private readonly List<ChangeItemInfo> binDataChanges = new List<ChangeItemInfo>();
    private readonly List<ChangeItemInfo> dirDataChanges = new List<ChangeItemInfo>();

    private readonly List<ChangeItemInfo> fileSourceChanges = new List<ChangeItemInfo>();
    private readonly List<ChangeItemInfo> dirSourceChanges = new List<ChangeItemInfo>();

    private readonly List<KeyValuePair<SrcFile, SrcFileAttribute>> refsToSrcFiles = new List<KeyValuePair<SrcFile, SrcFileAttribute>>();

    private readonly List<string> dstFileNames = new List<string>();

    #endregion

    public Dictionary<string, AssetInfo> Process( BackgroundWorker _worker )
    {
      Dictionary<string, AssetInfo> result = new Dictionary<string, AssetInfo>();

      foreach ( var item in xdbDataChanges )
      {
        AssetInfo asset = new AssetInfo();
        asset.DataFiles.Add( item );
        result.Add( item.File, asset );
      }

      if ( !ProcessBinFiles( _worker, result ) )
        return null;

      ProcessSourceFiles( result );

      if ( _worker.CancellationPending )
        return null;

      ProcessFolders( result );

      return result;
    }

    public void FindSourceChanges( IEditorWinApplication _application )
    {
      string fullRootPath = FileUtils.FixFolderName( Path.GetFullPath( _application.Application.SourceFileSystem.RootPath ) );

      Collection<SvnStatusEventArgs> statuses = null;
      client.GetStatus( _application.Application.SourceFileSystem.RootPath, out statuses );

      foreach ( SvnStatusEventArgs s in statuses )
      {

        bool rightStatus =
          s.LocalContentStatus == SvnStatus.Added || s.LocalContentStatus == SvnStatus.Merged ||
          s.LocalContentStatus == SvnStatus.Replaced || s.LocalContentStatus == SvnStatus.Deleted ||
          s.LocalContentStatus == SvnStatus.Modified || s.LocalContentStatus == SvnStatus.NotVersioned;

        if ( !rightStatus )
          continue;

        string fullPath = Path.GetFullPath( s.Path );
        string relPathAndName = fullPath.Substring( fullRootPath.Length );
        string localFileName = FileUtils.GetFileName( fullPath );
        bool isDirectory = IsDirectory( s.FullPath );
        string relPath = isDirectory ? relPathAndName : FileUtils.GetParentFolderPath( relPathAndName );

        relPath = FileUtils.FixFolderName( relPath );

        if ( relPath.Length == 0 || relPath[0] != FileUtils.PathSeparatorChar )
          relPath = FileUtils.PathSeparatorString + relPath;

        if ( isDirectory )
        {
          AddUnversionedRecursiveSource( fullRootPath, FileUtils.FixFolderName( fullPath ) );
        }
        else
        {
          fileSourceChanges.Add( new ChangeItemInfo( FileUtils.Combine( relPath, localFileName ), s ) );
        }
      }
    }

    private bool IsDirectory( string path )
    {
      FileAttributes attr = File.GetAttributes( path );
      return ( attr & FileAttributes.Directory ) == FileAttributes.Directory;
    }

    public void FindDataChanges( IEditorWinApplication _application )
    {
      string fullRootPath = Path.GetFullPath( _application.Application.FileSystem.RootPath );
      Collection<SvnStatusEventArgs> st = null;
      client.GetStatus( DataBase.FileSystem.RootPath, out st );

      foreach ( var s in st )
      {
        if ( s.LocalContentStatus == SvnStatus.Added ||
             s.LocalContentStatus == SvnStatus.Merged ||
             s.LocalContentStatus == SvnStatus.Replaced ||
             s.LocalContentStatus == SvnStatus.Deleted ||
             s.LocalContentStatus == SvnStatus.Modified )
        {
          string fullPath = Path.GetFullPath( s.Path );
          string relPathAndName = fullPath.Substring( fullRootPath.Length );
          string localFileName = FileUtils.GetFileName( fullPath );
          string relPath = ( ( s.NodeKind == SvnNodeKind.Directory ) ? relPathAndName : FileUtils.GetParentFolderPath( relPathAndName ) );
          relPath = FileUtils.FixFolderName( relPath );
          if ( relPath.Length == 0 || relPath[0] != '/' )
            relPath = "/" + relPath;

          string ext = Path.GetExtension( s.Path ).ToLower();

          if ( ext == ".xdb" )
          {
            xdbDataChanges.Add( new ChangeItemInfo( FileUtils.Combine( relPath, localFileName ), s ) );
          }
          else if ( s.NodeKind == SvnNodeKind.Directory )
          {
            dirDataChanges.Add( new ChangeItemInfo( relPath, s ) );
          }
          else
          {
            binDataChanges.Add( new ChangeItemInfo( FileUtils.Combine( relPath, localFileName ), s ) );
          }

        }
      }
    }

    private void ProcessFolders( Dictionary<string, AssetInfo> result )
    {
      foreach ( var item in dirDataChanges )
      {
        if ( item.LocalContentStatus == SvnStatus.Deleted )
          continue;

        foreach ( var xdbItem in result )
        {
          if ( xdbItem.Key.StartsWith( item.File, StringComparison.InvariantCultureIgnoreCase ) )
            xdbItem.Value.DataFiles.Insert( 0, item );
        }
      }

      foreach ( var item in dirSourceChanges )
      {
        if ( item.LocalContentStatus == SvnStatus.Deleted )
          continue;

        foreach ( var xdbItem in result )
        {
          if ( xdbItem.Key.StartsWith( item.File, StringComparison.InvariantCultureIgnoreCase ) )
            xdbItem.Value.SourceFiles.Insert( 0, item );
        }
      }
    }

    private void ProcessSourceFiles( Dictionary<string, AssetInfo> result )
    {
      foreach ( var asset in result )
      {
        if ( asset.Value.DataFiles.Count > 0
         && asset.Value.DataFiles[0].File == asset.Key
         && asset.Value.DataFiles[0].LocalContentStatus == SvnStatus.Deleted )
          continue;

        DBPtr<DBResource> objPtr = DataBase.Get<DBResource>( DBID.FromFileName( asset.Key, false ) );
        DBResource obj = objPtr.Get();
        if ( obj == null )
          continue;

        refsToSrcFiles.Clear();
        FieldsWalker.VisitFields<SrcFile, SrcFileAttribute>( obj, SrcFileFunctor, depthControl.Functor );

        foreach ( var item in refsToSrcFiles )
        {
          string fileName = item.Key.FileName;

          bool alreadyAdded = false;

          foreach ( var addedFile in asset.Value.SourceFiles )
          {
            if ( addedFile.File == fileName )
            {
              alreadyAdded = true;
              break;
            }
          }

          if ( alreadyAdded )
            continue;

          foreach ( var srcFile in fileSourceChanges )
          {
            if ( srcFile.File == fileName )
            {
              asset.Value.SourceFiles.Add( srcFile );
              break;
            }
          }
        }
      }
    }

    private bool ProcessBinFiles( BackgroundWorker worker, Dictionary<string, AssetInfo> result )
    {
      foreach ( var item in binDataChanges )
      {
        string binPath = FileUtils.GetParentFolderPath( item.File );

        DataBase.FileSystem.GetFiles( binPath, "*.xdb" );
        List<DBID> resources;
        ObjectsSelector.CollectObjects( EditorWinApplication.ApplicationSingleton, binPath, typeof( DBResource ), false, true, out resources );

        foreach ( var resDBID in resources )
        {
          if ( worker.CancellationPending )
            return false;

          if ( resDBID.IsInlined )
            continue;

          DBResource res = DataBase.Get<DBResource>( resDBID ).Get();
          if ( null == res )
            continue;

          ProcessDstFileList( result, item, res );

          ProcessTextRefList( result, item, res );
        }
      }

      return true;
    }

    private void ProcessDstFileList( Dictionary<string, AssetInfo> result, ChangeItemInfo item, DBResource res )
    {
      dstFileNames.Clear();
      FieldsWalker.VisitFields<string, DstFileAttribute>( res, DstFileFunctor, depthControl.Functor );

      ProcessCollectedDstFilenames( result, item, res );
    }

    private void ProcessTextRefList( Dictionary<string, AssetInfo> result, ChangeItemInfo item, DBResource res )
    {
      dstFileNames.Clear();
      FieldsWalker.VisitFields<TextRef>( res, TextRefFunctor, depthControl.Functor );

      ProcessCollectedDstFilenames( result, item, res );
    }

    private void ProcessCollectedDstFilenames( Dictionary<string, AssetInfo> result, ChangeItemInfo item, DBResource res )
    {
      string resFileName = res.DBId.FileName + ".xdb";

      foreach ( var dstFile in dstFileNames )
      {
        if ( dstFile != item.File )
          continue;

        AssetInfo asset = null;
        if ( result.ContainsKey( resFileName ) )
        {
          asset = result[resFileName];

          // Ignore resources to be deleted
          if ( asset.DataFiles.Count > 0
            && asset.DataFiles[0].File == resFileName
            && asset.DataFiles[0].LocalContentStatus == SvnStatus.Deleted )
            break;
        }
        else
        {
          asset = new AssetInfo();
          result.Add( resFileName, asset );
        }

        bool dstFileFound = false;
        foreach ( var dataFile in asset.DataFiles )
        {
          if ( dataFile.File == item.File )
          {
            dstFileFound = true;
            break;
          }
        }

        if ( !dstFileFound )
          asset.DataFiles.Add( item );
      }
    }

    private void AddUnversionedRecursiveSource( string _fullRootPath, string _fullPath )
    {
      string relPath = _fullPath.Substring( _fullRootPath.Length );

      if ( relPath.Length == 0 || relPath[0] != FileUtils.PathSeparatorChar )
        relPath = FileUtils.PathSeparatorString + relPath;

      dirSourceChanges.Add( new ChangeItemInfo( relPath, _fullPath ) );

      foreach ( var dir in Directory.GetDirectories( _fullPath ) )
      {
        AddUnversionedRecursiveSource( _fullRootPath, FileUtils.FixFolderName( dir ) );
      }

      foreach ( var file in Directory.GetFiles( _fullPath ) )
      {
        string fileName = FileUtils.FixFileName( file );
        string relFileName = fileName.Substring( _fullRootPath.Length );

        if ( relFileName.Length == 0 || relFileName[0] != FileUtils.PathSeparatorChar )
          relFileName = FileUtils.PathSeparatorString + relFileName;

        fileSourceChanges.Add( new ChangeItemInfo( relFileName, fileName ) );

      }
    }

    #region Functors

    private bool SrcFileFunctor( ref SrcFile value, SrcFileAttribute attr, string s )
    {
      if ( !string.IsNullOrEmpty( value.FileName ) )
        refsToSrcFiles.Add( new KeyValuePair<SrcFile, SrcFileAttribute>( value, attr ) );

      return true;
    }

    private bool DstFileFunctor( ref string value, DstFileAttribute attr, string s )
    {
      if ( !string.IsNullOrEmpty( value ) )
        dstFileNames.Add( value );

      return true;
    }

    private bool TextRefFunctor( ref TextRef value )
    {
      if ( !string.IsNullOrEmpty( value.FileName ) )
        dstFileNames.Add( value.FileName );

      return true;
    }

    #endregion

  }
}
