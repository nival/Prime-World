/*
#about Валидация бэклинков
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
*/
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Xml;
using EditorLib;
using EditorLib.IO;
using EditorLib.Operations;
using libdb.DB;
using libdb.Diagnostics;

namespace Scripts
{
  public class ValidateBackLinks
  {
    private int brokenBacklinks = 0;
    private int brokenFiles = 0;
    private int brokenLinks = 0;
    public bool dryRun = false;

    private IEditorCommonApplication application = null;
    private readonly Dictionary<DBID, List<KeyValuePair<DBID, int>>> allBacklinks = new Dictionary<DBID, List<KeyValuePair<DBID, int>>>();
    private readonly List<DBPtr<DBResource>> resources = new List<DBPtr<DBResource>>();

    public IEnumerable Main( IEditorCommonApplication app )
    {
      application = app;
      application.OperationExecutor.Start( Work );
      yield return true;
    }

    private bool Work( IOperationContext context )
    {
      context.Start( true, true );
      context.Progress( "Loading entire database... " );
      Log.TraceMessage( "Loading entire database... " );

      LoadResources( ObjectsRootFolder.Root );

      context.Progress( "Checks links integrity... " );
      Log.TraceMessage( "Checks links integrity... " );
      CheckLinksIntegrity();

      context.Progress( "Checks backlinks validity... " );
      Log.TraceMessage( "Checks backlinks validity... " );
      CheckBacklinksValidity();

      if ( !dryRun )
        DataBase.Store();

      string message = string.Format( "Items: {0}; Broken files: {1}; Broken links: {2}; Broken backlinks: {3}",
                                     resources.Count, brokenFiles, brokenLinks, brokenBacklinks );
      Log.TraceMessage( message );
      context.Progress( message );

      return true;
    }

    private void LoadResources( ObjectsFolder folder )
    {
      if ( folder == null )
        return;

      foreach ( DBID item in folder.Items )
      {
        DBPtr<DBResource> resource = TryLoadResource( item );
        if ( resource != null )
        {
          resources.Add( resource );
        }
        else
        {
          ++brokenFiles;
          if ( !dryRun )
          {
            string fileName = item.GetFullFileName();
            application.FileSystem.DeleteFile( fileName );
            Log.TraceError( "File \"{0}\" deleted", fileName );
          }
        }
      }

      foreach ( ObjectsFolder subFolder in folder.Folders )
        LoadResources( subFolder );
    }

    private DBPtr<DBResource> TryLoadResource( DBID dbid )
    {
      Stream file = application.FileSystem.OpenFile( dbid.GetFullFileName() );

      var doc = new XmlDocument();

      try
      {
        doc.Load( file );
      }
      catch ( XmlException e )
      {
        Log.TraceError( "\"{0}\" is not valid XML file. {1}", dbid, e.Message );
        return null;
      }
      finally
      {
        file.Close();
      }

      Type type = null;
      if ( !DataBase.TryGetType( doc.DocumentElement.Name, out type ) )
      {
        Log.TraceError( "\"{0}\" is not valid database file. Type \"{1}\" is undefined", dbid, doc.DocumentElement.Name );
        return null;
      }

      //@Ivn@TODO: Check for entire XML validity (maybe we need resave?!)
      DBPtr<DBResource> result = DataBase.Get<DBResource>( dbid );
      if ( result.Get() == null )
        return null;

      return result;
    }

    private void CheckLinksIntegrity()
    {
      foreach ( DBPtr<DBResource> resource in resources )
      {
        var visitor = new VisitLinks( application, resource.DBId );

        resource.ForAllStates(
          res => FieldsWalker.VisitFields( res, visitor.Functor,
                  new FieldsWalker.DepthController( 0, FieldsWalker.ObjectType.DBPtrUninlined, FieldsWalker.ObjectType.All ).Functor ) );

        if ( visitor.BrokenLinksCount > 0 && !dryRun )
          DataBase.ChangeCallback( resource.DBId );

        Dictionary<DBID, int> links = visitor.GetLinks();
        brokenLinks += visitor.BrokenLinksCount;

        foreach ( var link in links )
        {
          List<KeyValuePair<DBID, int>> backlinks = null;
          if ( !allBacklinks.TryGetValue( link.Key, out backlinks ) )
          {
            backlinks = new List<KeyValuePair<DBID, int>>();
            allBacklinks.Add( link.Key, backlinks );
          }
          backlinks.Add( new KeyValuePair<DBID, int>( resource.DBId, link.Value ) );
        }
      }
    }

    private void CheckBacklinksValidity()
    {
      foreach ( var resource in resources )
      {
        Dictionary<DBID, int> origBacklinks = resource.GetBackLinks();
        List<KeyValuePair<DBID, int>> backlinks = null;
        if ( !allBacklinks.TryGetValue( resource.DBId, out backlinks ) )
          backlinks = new List<KeyValuePair<DBID, int>>();

        bool invalidBacklinks = origBacklinks.Count != backlinks.Count;
        foreach ( var backlink in backlinks )
        {
          int count = 0;
          if ( origBacklinks.TryGetValue( backlink.Key, out count ) && count == backlink.Value )
            continue;

          invalidBacklinks = true;
          break;
        }

        if ( invalidBacklinks )
        {
          ++brokenBacklinks;
          Log.TraceError( "\"{0}\" backlinks not valid", resource.DBId );
          if ( !dryRun )
          {
            resource.SetBacklinks( backlinks );
            DataBase.ChangeCallback( resource.DBId );
          }
        }
      }
    }

    #region Nested type: VisitDstFiles

    private sealed class VisitDstFiles
    {
      private readonly DBID owner = null;
      private IEditorCommonApplication application = null;
      private int brokenDstFiles = 0;

      public VisitDstFiles( IEditorCommonApplication application, DBID owner )
      {
        this.application = application;
        this.owner = owner;
      }

      public int BrokenDstFiles
      {
        get { return brokenDstFiles; }
      }

      public bool Functor( ref object obj, DBFieldInfo field )
      {
        var dstFile = TypeUtils.GetAttribute<DstFileAttribute>( field, true );
        if ( dstFile == null || obj.GetType() != typeof( string ) )
          return true;

        if ( application.FileSystem.GetFileInfo( obj.ToString() ).IsFileExists )
          return true;

        ++brokenDstFiles;
        Log.TraceError( "\"{0}\" points to missed file \"{1}\"", owner, obj.ToString() );
        return true;
      }
    }

    #endregion

    #region Nested type: VisitLinks

    private sealed class VisitLinks
    {
      private readonly IEditorCommonApplication application = null;
      private readonly List<DBID> links = new List<DBID>();
      private readonly DBID owner = null;
      private int brokenLinksCount = 0;

      public VisitLinks( IEditorCommonApplication application, DBID owner )
      {
        this.application = application;
        this.owner = owner;
      }

      public int BrokenLinksCount
      {
        get { return brokenLinksCount; }
      }

      public bool Functor( ref object obj, DBFieldInfo field )
      {
        var ptr = obj as DBPtrBase;
        if ( ptr == null )
          return true;

        if ( DBID.IsNullOrEmpty( ptr.DBId ) || ptr.DBId.IsInlined )
          return true;

        if ( application.FileSystem.GetFileInfo( ptr.DBId.GetFullFileName() ).IsFileExists )
        {
          links.Add( ptr.DBId );
          return true;
        }

        Log.TraceError( "\"{0}\" points to missed object \"{1}\"", owner, ptr.DBId );
        ++brokenLinksCount;

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
    }

    #endregion
  }
}