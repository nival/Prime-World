/*
#about Скрипт ищет во всех объектах ссылки на файлы исходников и проверяет файлы на наличие.
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
*/

using System.Collections;
using System.Collections.Generic;
using DBTypes;
using EditorLib;
using EditorLib.IO;
using EditorLib.Operations;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;

namespace Scripts
{
  class SourceFilesChecker
  {
    class FileSource
    {
      public SrcFile File { get; set; }
      public SrcFileAttribute FileAttribute { get; set; }
    }

    private IEditorCommonApplication application;
    private readonly List<FileSource> refsToFiles = new List<FileSource>();

    private bool Functor( ref SrcFile srcFile, SrcFileAttribute attr, string s )
    {
      if( !string.IsNullOrEmpty( srcFile.FileName ) )
      {
        //игнорируем файлы лежащие в папке UI
        if( !IgnoreThis( srcFile.FileName ) )
        {
          refsToFiles.Add( new FileSource
          {
            File = srcFile, 
            FileAttribute = attr
          });
        }
      }

      return true;
    }

    private bool IgnoreThis( string fileName )
    {
      return fileName.ToUpper().Contains( @"/UI/" ) || fileName.Contains( @"\UI\" );
    }

    public IEnumerable Main( IEditorCommonApplication _application )
    {
      this.application = _application;
      this.application.OperationExecutor.Start( Work );

      yield return true;
    }

    private bool Work( IOperationContext _context )
    {
      _context.Start( false, true );
      _context.Progress( "SourceFilesChecker.cs started" );
      Log.TraceMessage( "SourceFilesChecker.cs started" );
      
      refsToFiles.Clear();

      List<DBID> types;
      Log.TraceMessage( "Collecting objects" );
      ObjectsSelector.CollectObjects( application, "/", typeof( DBResource ), true, true, out types );

      FieldsWalker.DepthController depth = new FieldsWalker.DepthController( 0, FieldsWalker.ObjectType.DBPtr,
                                                                             FieldsWalker.ObjectType.All );
      foreach( DBID t in types )
      {
        DBResource res = DataBase.Get<DBResource>( t ).Get();

        if( res is Texture && !string.IsNullOrEmpty( ( res as Texture ).generatedFileName ) )
          continue;

        FieldsWalker.VisitFields<SrcFile, SrcFileAttribute>( res, Functor, depth.Functor );
      }

      _context.Progress( "Searching for missing files" );
      Log.TraceMessage( "Searching for missing files" );
      int cnt = 0;

      foreach( FileSource item in refsToFiles )
      {
        if( !application.SourceFileSystem.IsFileExists( item.File.FileName ) )
        {
          string suggestedName;
          if( item.FileAttribute != null && string.IsNullOrEmpty( item.FileAttribute.SourceFolder ) )
          {
            suggestedName = FileUtils.Combine( FileUtils.GetFolderName( item.File.GetOwner().DBId.FileName ),
                                               FileUtils.GetFileName( item.File.FileName ) );
          }
          else
          {
            suggestedName = FileUtils.Combine( FileUtils.GetFolderName( item.FileAttribute.SourceFolder ),
                                               FileUtils.GetFileName( item.File.FileName ) );
          }


          string fileName = item.File.FileName;
          string ownerName = item.File.GetOwner().DBId.FileName;

          if( suggestedName == item.File.FileName || !application.SourceFileSystem.IsFileExists( suggestedName ) )
          {         
            if( !IgnoreThis( ownerName ) )
            {
              Log.TraceError( "File missing: {0} | referred: {1} ", fileName, ownerName ); 
            }
            cnt++;
          }
          else
          {
            Log.TraceWarning( "Correcting {0} to {1} in {2}",
                              fileName,
                              suggestedName,
                              ownerName );

            item.File.SetFileName( suggestedName );
          }
        } 
      }

      DataBase.Store();
      _context.Progress( string.Format("TOTAL MISSING FILES COUNT: {0}", cnt) );
      Log.TraceMessage( "TOTAL MISSING FILES COUNT: {0}", cnt );
      
      return true;
    }
  }
}
