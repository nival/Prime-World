/*
#about Скрипт проходится по всем объектам, и собирает ссылки на файлы. После этого выводит список неиспользуемых файлов и предлагает их удалить.
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
*/

using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using DBTypes;
using EditorLib;
using EditorLib.IO;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;

namespace Scripts
{
	class RemoveUnusedFiles
	{
	  private const string PATH = @"/";
    
    private readonly List<string> exts = new List<string> 
    { 
      ".mayapart", ".part", ".mayaskel", ".skel", 
      ".mayacoll", ".coll", ".mayaanim", ".anim", ".mayaskin", 
      ".skin", ".mayastat", ".stat", ".dds", ".txt" 
    };

    private IEditorCommonApplication application = null;

    private Dictionary<string, object> filesInUse = new Dictionary<string, object>();

    private bool Functor( ref string value, DstFileAttribute a, string fieldname )
    {
      AddToUsed( FileUtils.UnifyPathForComparison( value ) );
			return true;
    }

	  private bool FunctorTxtRef( ref TextRef value )
    {
      AddToUsed( value.FileName );
      return true;
    }

    private void AddToUsed( string fileName )
    {
      if( string.IsNullOrEmpty( fileName ) )
        return;

      string key = FileUtils.UnifyPathForComparison( fileName );//чтобы в key не было дубликатов

      if( !filesInUse.ContainsKey( key ) )
      {
        filesInUse.Add( key, null );
      }
    }

    private bool IsFileInUse(string fileName)
    {
      return filesInUse.ContainsKey(FileUtils.UnifyPathForComparison(fileName));
    }

	  public IEnumerable Main( IEditorCommonApplication app )
		{
	    application = app;

      filesInUse.Clear();
      referencesCount = 0;
      
      List<DBID> types;
      ObjectsSelector.CollectObjects( application, PATH, typeof( DBResource ), true, true, out types );

      FieldsWalker.DepthController depth = new FieldsWalker.DepthController( 0, FieldsWalker.ObjectType.DBPtrUninlined,
                                                                             FieldsWalker.ObjectType.All );
      foreach( DBID t in types )
      {
        DBResource res = DataBase.Get<DBResource>( t ).Get();

        #region TextureAnimated

        TextureAnimated ta = res as TextureAnimated;
        if( ta != null )
        {
          int startPos = 0;
          int endpos = 0;
          foreach( char c in ta.textureFileName )
          {
            if( "0123456789".Contains( c.ToString() ) )
            {
              endpos = startPos;
              foreach( char c2 in ta.textureFileName.Substring( startPos ) )
                if( "0123456789".Contains( c2.ToString() ) )
                  endpos++;
                else
                  break;

              break;
            }
            else
            {
              startPos++;
            }
          }

          string numericSubstr = ta.textureFileName.Substring( startPos, endpos - startPos );

          string formatstring = "{0:";
          foreach( var с in numericSubstr )
            formatstring += "0";
          formatstring += "}";

          int firstNum = int.Parse( numericSubstr );

          for( int i = 0; i < ta.animCount; i++ )
          {
            AddToUsed( FileUtils.UnifyPathForComparison(
               ta.textureFileName.Replace( numericSubstr, string.Format( formatstring, firstNum + i ) ) ) );
          }

          continue;
        }

        #endregion

        DataBase.Get<DBResource>( t ).ForAllStates( r => FieldsWalker.VisitFields<string, DstFileAttribute>( r, Functor, depth.Functor ) );
        DataBase.Get<DBResource>( t ).ForAllStates( r => FieldsWalker.VisitFields<TextRef>( r, FunctorTxtRef, depth.Functor ) );
      }

      //key = path, value = null
      //path - в SVN надо передавать path без изменений case, иначе удаляемые файлы станут missing
      Dictionary<string, object> filesToDelete = new Dictionary<string, object>();

      foreach( string folder in GetAllFolders( PATH ) )
      {
        foreach( string file in application.FileSystem.GetFiles( folder, "*.*" ) )
        {

          if( exts.Exists( ext => string.Equals( ext, Path.GetExtension( file ), StringComparison.InvariantCultureIgnoreCase ) ) )
          {
            if( !IsFileInUse( file ) )
            {
              FindReferences( folder, file );
            }

            if( !IsFileInUse( file ) )
            {
              if( !filesToDelete.ContainsKey( file ) )
              {
                filesToDelete.Add( file, null );
              }
            }
          }
        }
      }


      //Log.TraceMessage( "Files to delete: {0}", filesToDelete.Count);
      //foreach ( string s in filesToDelete )
      //  Log.TraceMessage( s );

      Log.TraceMessage( "Used files count: {0}", filesInUse.Count );
      //Log.TraceMessage( "Referenced files in XDB: {0}", referencesCount );

      int filesDeleted = 0;
      foreach( string s in filesToDelete.Keys )
      {
        application.FileSystem.DeleteFile( s );
        filesDeleted++;
      }

      Log.TraceMessage( "Files deleted: {0}", filesDeleted );

      yield return true;
		}

    int referencesCount = 0;

    private void FindReferences( string folder, string fileName )
    {
      foreach( string file in application.FileSystem.GetFiles( folder, "*.xdb" ) )
      {
        using( Stream fileStream = application.FileSystem.OpenFile( file ) )
        {
          using(StreamReader reader = new StreamReader( fileStream ))
          {
            string xdbText = reader.ReadToEnd().ToLower();
            
            string lowerFileName = fileName.ToLower();

            if( xdbText.Contains( lowerFileName ) ||
                xdbText.Contains( lowerFileName.Replace( FileUtils.PathSeparatorChar, FileUtils.AltPathSeparatorChar ) ) )
            {
              AddToUsed( fileName );//это файл используется (по ссылке)
              //Log.TraceMessage( "Reference to file '{0}' found in '{1}'", fileName, file );
              referencesCount++;
            } 
          }
        }
      }
    }

	  private IEnumerable<string> GetAllFolders( string root)
		{
			yield return root;
			foreach ( string file in application.FileSystem.GetFolders( root, "*" ) )
			{
        foreach( string s in GetAllFolders( file ) )
					yield return s;
			}
		}
	}
}
