using System;
using System.Collections.Generic;
using System.Windows.Forms;
using EditorLib.Settings;
using libdb.DB;
using libdb.IO;

namespace EditorLib.ObjectsBrowser
{
  [ConfigObject( true )]
  public class FolderBookmarks : SimpleConfigObject
	{
    public class BookmarkInfo
    {
      public BookmarkInfo() { }
      public BookmarkInfo( String _folderPath, Shortcut _hotKey )
      {
        folderPath = _folderPath;
        hotKey = _hotKey;
      }
      public string folderPath;
      public Shortcut hotKey;
    }

    public const int MAX_RECENT_FOLDERS = 10;

    public List<BookmarkInfo> bookmarks = new List<BookmarkInfo>();
    public List<BookmarkInfo> recentFolders = new List<BookmarkInfo>();

    public bool IsBookMarked( string _folder )
		{
      return bookmarks.Exists( b => b.folderPath.Equals( _folder, StringComparison.InvariantCultureIgnoreCase ) );
		}

		public void SetBookmark( string _folder, Shortcut _hotKey ) 
		{
			bool folderFound = false;

			for ( int i = 0; i < bookmarks.Count; ++i )
			{
				if ( bookmarks[i].hotKey == _hotKey )
				{
					BookmarkInfo info = bookmarks[i];
					info.hotKey = Shortcut.None;
					bookmarks.RemoveAt( i );
					bookmarks.Add( info );
          OnFolderBookmarksChanged();
				} 

				if ( bookmarks[i].folderPath.Equals( _folder, StringComparison.InvariantCultureIgnoreCase ) )
				{
					folderFound = true;
					BookmarkInfo info = bookmarks[i];
					info.hotKey = _hotKey;
					bookmarks.RemoveAt( i );
					bookmarks.Add( info );
          OnFolderBookmarksChanged();
				}
			}

			if ( !folderFound )
			{
				BookmarkInfo information = new BookmarkInfo( _folder, _hotKey );
				bookmarks.Add( information );
        OnFolderBookmarksChanged();
			}
		}

		public void RemoveBookmark( string _folder )
		{
			for ( int i = 0; i < bookmarks.Count; ++i )
			{
        if( bookmarks[i].folderPath.Equals( _folder, StringComparison.InvariantCultureIgnoreCase ) )
        {
          bookmarks.RemoveAt( i );
          OnFolderBookmarksChanged();
        } 
			}
		}

    private void OnFolderBookmarksChanged()
    {
      if ( FolderBookmarksChangedEvent != null )
        FolderBookmarksChangedEvent();
    }

    public void RegisterOpenObject( DBID dbid )
    {
      if ( dbid.IsEmpty )
        return;

      RegisterRecentFolder( FileUtils.GetFolderName( dbid.FileName ) );
    }

    public void RegisterRecentFolder( string folder )
    {
      if( !string.IsNullOrEmpty(folder) && folder[folder.Length - 1] != FileUtils.PathSeparatorChar)
      {
        folder += FileUtils.PathSeparatorChar;
      }

      BookmarkInfo newItem = null;
      foreach ( BookmarkInfo item in recentFolders )
      {
        if ( item.folderPath.Equals( folder, StringComparison.InvariantCultureIgnoreCase ) )
        {
          newItem = item;
          break;
        }
      }

      if ( null == newItem )
      {
        newItem = new BookmarkInfo( folder, Shortcut.None );
        if ( recentFolders.Count >= MAX_RECENT_FOLDERS )
          recentFolders.RemoveRange( MAX_RECENT_FOLDERS - 1, recentFolders.Count - MAX_RECENT_FOLDERS + 1 );
      }
      else
      {
        recentFolders.Remove( newItem );
      }
      recentFolders.Insert( 0, newItem );

      OnFolderBookmarksChanged();
    }

		#region FolderBoolmark Events
		public delegate void FolderBookmarksChangedEventHandler();
    public event FolderBookmarksChangedEventHandler FolderBookmarksChangedEvent;
		#endregion
	}

}
