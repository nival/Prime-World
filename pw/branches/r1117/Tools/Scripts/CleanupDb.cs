/*
#ref EditorNative.dll
#ref PF_Types.DBTypes.dll
*/
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using EditorNative;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;
using DBTypes;

namespace Scripts
{
	public class CleanupDb
	{
    private static string[] screens = { "Console", "Tooltips", "Combat", "FlyTexts", "ObjectsInfo2d",
                                        "MinigamePauseScreen", "EaselScreen", "Minigame02Results", "Minigame02Lobby",
                                        "Minigame02Fail", "Loading", "NetworkStatus" };

    #region private sealed class VisitDBPtr

    private sealed class VisitDBPtr
    {
      private readonly IEditorCommonApplication application = null;
      private readonly DBID owner = null;
      private readonly List<DBID> links = new List<DBID>();
      private readonly List<DBID> parents = new List<DBID>();

      public VisitDBPtr( IEditorCommonApplication application, DBID owner )
      {
        this.application = application;
        this.owner = owner;
      }

      private static libdb.DB.FieldsWalker.ObjectType GetObjectType( object obj )
      {
        DBPtrBase ptr = obj as DBPtrBase;
        if ( ptr != null )
          return ptr.DBId.IsInlined ? libdb.DB.FieldsWalker.ObjectType.DBPtrInlined : libdb.DB.FieldsWalker.ObjectType.DBPtrUninlined;
        else if ( TypeUtils.IsList( obj.GetType() ) )
          return libdb.DB.FieldsWalker.ObjectType.List;
        else if ( TypeUtils.IsStruct( obj.GetType() ) )
          return libdb.DB.FieldsWalker.ObjectType.Struct;

        return libdb.DB.FieldsWalker.ObjectType.None;
      }
      
      public static bool Depth( object obj, object fieldKeeper, DBFieldInfo field, ref int depth )
      {
        if ( null == obj )
          return false;

        if ( TypeUtils.HasAttribute<NoCodeAttribute>( field, true ) || TypeUtils.HasAttribute<NoCodeAttribute>( field.FieldType, true ) )
          return false;

        libdb.DB.FieldsWalker.ObjectType objType = GetObjectType( obj );
        DBPtrBase ptr = obj as DBPtrBase;

        if ( ptr == null )
          return true;

        return ptr.DBId.IsInlined;
      }

      public bool Functor( ref object obj, DBFieldInfo field )
      {
        if ( TypeUtils.HasAttribute<NoCodeAttribute>( field, true ) || TypeUtils.HasAttribute<NoCodeAttribute>( field.FieldType, true ) )
          return true;

        var ptr = obj as DBPtrBase;
        if ( ptr == null )
          return true;

        if ( DBID.IsNullOrEmpty( ptr.DBId ) || ptr.DBId.IsInlined )
          return true;

        if ( application.FileSystem.GetFileInfo( ptr.DBId.GetFullFileName() ).IsFileExists )
        {
          if ( field.Name == "__parent" )
            parents.Add( ptr.DBId );
          else
            links.Add( ptr.DBId );
          return true;
        }

        Log.TraceError( "\"{0}\" points to missed object \"{1}\"", owner, ptr.DBId );

        Type listType = TypeUtils.GetTypeFromList( field.FieldType );
        Type resourceType = TypeUtils.GetTypeFromPtr( listType ?? field.FieldType );
        ConstructorInfo cotr = field.FieldType.GetConstructor( new Type[] { typeof( DBID ), resourceType } );
        if ( cotr == null )
          return true;

        obj = cotr.Invoke( new object[] { DBID.Empty, null } );
        return true;
      }

      public Dictionary<DBID, int> GetLinks()
      {
        var result = new Dictionary<DBID, int>();
        foreach ( DBID link in links )
        {
          if ( result.ContainsKey( link ) )
            ++result[link];
          else
            result.Add( link, 1 );
        }

        return result;
      }

      public List<DBID> GetParents()
      {
        var collector = new Dictionary<DBID, bool>();
        foreach ( DBID link in parents )
        {
          if ( !collector.ContainsKey( link ) )
            collector.Add( link, false );
        }

        List<DBID> result = new List<DBID>( collector.Keys );
        return result;
      }
    }

    #endregion

    #region private sealed class TimeLogger

    private sealed class TimeLogger
    {
      private DateTime start;

      public void Start( string format, params object[] args )
      {
        start = DateTime.Now;
        Log.TraceMessage( format, args );
      }

      public void Stop( string format, params object[] args )
      {
        TimeSpan elapsed = DateTime.Now - start;
        string message = string.Format( format, args );
        Log.TraceMessage( "{0}. {1}s", message, elapsed.TotalSeconds );
      }
    }

    #endregion

    private static void LoadResources( out List<DBID> dbids )
    {
      dbids = new List<DBID>();

      List<ObjectsFolder> folders = new List<ObjectsFolder>();
      folders.Add( ObjectsRootFolder.Root );
      int index = 0;
      while ( index < folders.Count )
      {
        foreach ( var item in folders[index].Items )
        {
          DBPtr<DBResource> resource = DataBase.Get<DBResource>( item );
          if ( resource != null && resource.Get() != null )
          {
            dbids.Add( item );
          }
        }

        folders.AddRange( folders[index].Folders );
        ++index;
      }
    }

    private static void CleanupHeroes( HeroesDB heroes )
    {
      for ( int i = 0; i < heroes.heroes.Count; ++i )
      {
        var hero = heroes.heroes[i].Get<Hero>();
        if ( hero == null || !hero.legal )
        {
          if ( hero != null ) Log.TraceMessage( "Remove illegal hero {0}", hero.DBId );
          heroes.heroes.RemoveAt( i );
          --i;
        }
        else
        {
          for ( int j = 0; j < hero.heroSkins.Count; ++j )
          {
            var skin = hero.heroSkins[j].Get<HeroSkin>();
            if ( skin == null || !skin.legal )
            {
              if ( skin != null ) Log.TraceMessage( "Remove illegal skin {0} for hero {1}", skin.DBId, hero.DBId );
              hero.heroSkins.RemoveAt( j );
              --j;
            }
          }
        }
      }
    }

    private static void CleanupScreens( libdb.IChangeableList<UIScreenDesc> screens, IEnumerable<string> names )
    {
      var namesDict = new Dictionary<string, object>();
      foreach ( var name in names )
        namesDict.Add( name, null );

      for ( int i = 0; i < screens.Count; ++i )
      {
        var screen = screens[i];
        if ( screen == null || !namesDict.ContainsKey( screen.screenId ) )
        {
          screens.RemoveAt( i );
          --i;
        }
      }
    }

    private static void RemoveNonShippingData()
    {
      CleanupHeroes( DataBase.Get<HeroesDB>( DBID.FromString( "/Heroes/_.HRDB" ) ) );
      //CleanupScreens( DataBase.Get<UIRoot>( DBID.FromFileName( "/UI/UIRoot", false ) ).Get().screens, screens );
    }

    private static void BuildLinks( IEditorCommonApplication application, List<DBID> dbids, out Dictionary<DBID, List<DBID>> links )
    {
      links = new Dictionary<DBID, List<DBID>>();
      Dictionary<DBID, List<DBID>> parents = new Dictionary<DBID, List<DBID>>();

      var depth = new FieldsWalker.DepthController( 0, FieldsWalker.ObjectType.DBPtrUninlined, FieldsWalker.ObjectType.All );
      var backlinks = new Dictionary<DBID, List<KeyValuePair<DBID, int>>>();
      foreach ( var dbid in dbids )
      {
        var resoruce = DataBase.Get<DBResource>( dbid );
        if ( resoruce == null || resoruce.Get() == null )
          continue;

        var visitor = new VisitDBPtr( application, resoruce.DBId );
        resoruce.ForAllStates( res => FieldsWalker.VisitFields( res, visitor.Functor, VisitDBPtr.Depth ) );

        var thisLinks = visitor.GetLinks();

        List<DBID> allLinks = new List<DBID>( thisLinks.Keys );
        allLinks.AddRange( visitor.GetParents() );
        links.Add( resoruce.DBId, allLinks );

        foreach ( var link in thisLinks )
        {
          List<KeyValuePair<DBID, int>> thisBacklinks = null;
          if ( !backlinks.TryGetValue( link.Key, out thisBacklinks ) )
          {
            thisBacklinks = new List<KeyValuePair<DBID, int>>();
            backlinks.Add( link.Key, thisBacklinks );
          }
          thisBacklinks.Add( new KeyValuePair<DBID, int>( resoruce.DBId, link.Value ) );
        }
      }

      foreach ( var thisBacklinks in backlinks )
      {
        DBPtr<DBResource> resource = DataBase.Get<DBResource>( thisBacklinks.Key );
        resource.SetBacklinks( thisBacklinks.Value );
      }
    }

    private static IEnumerable<DBID> CollectRootsFromFolder( string folder )
    {
      List<DBID> result = new List<DBID>();
      List<ObjectsFolder> folders = new List<ObjectsFolder>();
      folders.Add( ObjectsRootFolder.Root.GetFolder( folder ) );
      int index = 0;
      while ( index < folders.Count )
      {
        result.AddRange( folders[index].Items );
        folders.AddRange( folders[index].Folders );
        ++index;
      }

      return result;
    }

    private static void CollectResources( IEnumerable<DBID> roots, Dictionary<DBID, List<DBID>> links, out List<DBID> dbids )
    {
      Dictionary<DBID, bool> result = new Dictionary<DBID, bool>();
      foreach ( var root in roots )
        result.Add( root, true );

      List<DBID> dbidsToLook = new List<DBID>( roots );
      int index = 0;
      while ( index < dbidsToLook.Count )
      {
        List<DBID> thisLinks = null;
        if ( links.TryGetValue( dbidsToLook[index], out thisLinks ) )
        {
          foreach ( var link in thisLinks )
          {
            if ( !result.ContainsKey( link ) )
            {
              result.Add( link, true );
              dbidsToLook.Add( link );
            }
          }
        }
        ++index;
      }

      dbids = new List<DBID>( result.Keys );
    }

    private static void AddUniqueFileName( string file, Dictionary<string, object> files )
    {
      if ( string.IsNullOrEmpty( file ) )
        return;
      if ( !DataBase.FileSystem.GetFileInfo( file ).IsFileExists )
        return;
      if ( !files.ContainsKey( file ) )
        files.Add( file, null );
    }

    private static void CollectLinkedFiles( IEnumerable<DBID> dbids, out List<string> _files, out List<string> _texts )
    {
      Dictionary<string, object> files = new Dictionary<string, object>();
      Dictionary<string, object> texts = new Dictionary<string, object>();

      foreach ( var dbid in dbids )
      {
        DataBase.Get<DBResource>( dbid ).ForAllStates(
          state => FieldsWalker.VisitFields<string, DstFileAttribute>( state,
            ( ref string value, DstFileAttribute a, DBFieldInfo field ) =>
            {
              if ( TypeUtils.HasAttribute<NoCodeAttribute>( field, true ) )
                return true;
              AddUniqueFileName( value, files );
              return true;
            },
            VisitDBPtr.Depth ) );
        DataBase.Get<DBResource>( dbid ).ForAllStates(
          state => FieldsWalker.VisitFields<TextRef>( state,
            ( ref TextRef value ) => { AddUniqueFileName( value.FileName, texts ); return true; },
            VisitDBPtr.Depth ) );
      }

      _files = new List<string>( files.Keys );
      _texts = new List<string>( texts.Keys );
    }

    public void CollectNonDbFiles( IFileSystem fileSystem, string root, string mask, List<string> files )
    {
      foreach ( var file in fileSystem.GetFiles( root, mask ) )
        files.Add( file );
      foreach ( var folder in fileSystem.GetFolders( root ) )
        CollectNonDbFiles( fileSystem, folder, mask, files );
    }

    public IEnumerable Main( IEditorCommonApplication application, string[] parameters )
    {
      TimeLogger timer = new TimeLogger();

      List<DBID> resources;
      timer.Start( "Loading resources..." );
      LoadResources( out resources );
      timer.Stop( "...done. {0} resources", resources.Count );

      timer.Start( "Deleting nonshipping data..." );
      RemoveNonShippingData();
      timer.Stop( "...done" );

      Dictionary<DBID, List<DBID>> links;
      timer.Start( "Collect links and fix backlinks..." );
      BuildLinks( application, resources, out links );
      timer.Stop( "...done" );

      int totalResources = resources.Count;
      List<DBID> roots = new List<DBID>();

      timer.Start( "Collecting roots ant theirs dependencies..." );
      foreach ( var name in parameters[0].Split( new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries ) )
      {
        if ( name.EndsWith( FileUtils.PathSeparatorChar.ToString() ) || name.EndsWith( FileUtils.AltPathSeparatorChar.ToString() ) )
          roots.AddRange( CollectRootsFromFolder( name ) );
        else
          roots.Add( DBID.FromFileName( name, false ) );
      }

      CollectResources( roots, links, out resources );
      timer.Stop( "...done. {0} resources ({1}%)", resources.Count, 100 * resources.Count / totalResources );

      List<string> files;
      List<string> texts;
      timer.Start( "Collecting non db files from resources..." );
      CollectLinkedFiles( resources, out files, out texts );
      timer.Stop( "...done ({0} files and {1} text files).", files.Count, texts.Count );

      timer.Start( "Collecting externals non db files..." );
      foreach ( var name in parameters[1].Split( new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries ) )
        CollectNonDbFiles( application.FileSystem, FileUtils.GetParentFolderPath( name ), FileUtils.GetFileName( name ), files );
      timer.Stop( "...done ({0} files).", files.Count );

      timer.Start( "Store resources..." );
      foreach ( var res in resources )
      {
        DataBase.Get<DBResource>( res ).Store( false );
        files.Add( res.GetFullFileName() );
      }
      timer.Stop( "...done" );

      if ( parameters.Length > 2 )
      {
        timer.Start( "Store list of files {0}...", parameters[2] );
        files.Sort();
        File.WriteAllLines( parameters[2], files.ToArray() );
        timer.Stop( "...done" );
      }

      if ( parameters.Length > 3 )
      {
        EditorUIScene.StoreTextsCache( parameters[3], texts );
      }

      yield return true;
    }
	}
}
