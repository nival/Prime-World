using System;
using System.Collections.Generic;
using System.IO;
using System.Xml;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;

namespace EditorPlugins.Console
{
  [CommandName( "fixnames", "", "Fix names of all objects in DB, adding necessary extensions" )]
  class FixNameExtensionsCommand : IConsoleCommand
  {
    [CommandArgument( "dry-run", "", "Only diagnose problems, do not repair them" )]
    public bool dryRun = false;

    private DBPtr<DBResource> TryLoadResource( IEditorCommonApplication application, DBID dbid )
    {
      string fullFileName = dbid.GetFullFileName();
      Stream file = application.FileSystem.OpenFile( fullFileName );
      XmlDocument doc = new XmlDocument();

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

      DBPtr<DBResource> result = DataBase.Get<DBResource>( dbid );
      if ( result.Get() == null )
        return null;

      return result;
    }

    private void LoadObjects( IEditorCommonApplication application, ObjectsFolder folder, List<DBPtr<DBResource>> resources )
    {
      if ( folder == null )
        return;

      List<DBPtr<DBResource>> result = new List<DBPtr<DBResource>>();
      foreach ( DBID item in folder.Items )
      {
        DBPtr<DBResource> resource = TryLoadResource( application, item );
        if ( resource != null )
          result.Add( resource );
      }

      resources.AddRange( result );

      foreach ( ObjectsFolder subFolder in folder.Folders )
        LoadObjects( application, subFolder, resources );
    }

    public int Execute( IEditorCommonApplication application, string[] parameters )
    {
      List<DBPtr<DBResource>> resources = new List<DBPtr<DBResource>>();
      ObjectsFolder folder = ObjectsRootFolder.Root;
      LoadObjects( application, folder, resources );

      foreach ( DBPtr<DBResource> resPtr in resources )
      {
        DBID oldDBID = resPtr.DBId;
        if ( oldDBID.IsInlined )
          continue;

        DBResource res = resPtr.Get();
        Type resType = res.GetType();
        string oldFilename = FileUtils.GetFileName( oldDBID.FileName );
        string filePath = FileUtils.GetParentFolderPath( oldDBID.FileName );
        string oldFilenameCropped = string.Empty;
        string oldExtension = string.Empty;
        string newExtension = string.Empty;

        int indexDot = oldFilename.LastIndexOf( '.' );
        if ( indexDot >= 0 )
        {
          oldFilenameCropped = oldFilename.Substring( 0, indexDot );
          oldExtension = oldFilename.Substring( indexDot + 1 );
        }
        else
          oldFilenameCropped = oldFilename;

        UseTypeNameAttribute attr = TypeUtils.GetAttribute<UseTypeNameAttribute>( resType, true );
        if ( null != attr )
          newExtension = attr.alias;

        if ( oldExtension == newExtension )
          continue;

        string newFilename = oldFilenameCropped;
        //if ( newExtension.Length > 0 )
        //  newFilename += "." + newExtension;

        DBID newDBID = null;
        if ( !DBID.TryCreateDBID( filePath, newFilename, resType, out newDBID ) )
        {
          Log.TraceError( "Failed to convert \"{0}\" to new extension \"{1}\"", oldDBID, newExtension );
          continue;
        }
        if ( dryRun )
        {
          Log.TraceMessage( "Renaming \"{0}\" to new extension \"{1}\"", oldDBID, newExtension );
        }
        else
        {
          DataBase.Rename( newDBID, oldDBID );
        }
      }
      DataBase.Store();
      return 0;
    }
  }
}
