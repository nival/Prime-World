using System;
using System.Collections.Generic;
using System.Text;
using libdb.DB;
using EditorLib.Extensions;
using libdb.IO;
using libdb.Diagnostics;
using System.IO;
using EditorLib;
using DBTypes;

namespace EditorPlugins.DataCheckers
{
  public class FixerSourceFiles : Checker<DBResource>
  {
    protected override bool KnownDuration { get { return false; } }

    public override bool CanFixErrors { get { return true; } }

    private readonly List<KeyValuePair<SrcFile, SrcFileAttribute>> refsToFiles = new List<KeyValuePair<SrcFile, SrcFileAttribute>>();

    private bool Functor( ref SrcFile value, SrcFileAttribute attr, string s )
    {
      if ( !string.IsNullOrEmpty( value.FileName ) )
        refsToFiles.Add( new KeyValuePair<SrcFile, SrcFileAttribute>( value, attr ) );

      return true;
    }

    protected override bool Process( DBPtr<DBResource> resource, IEditorCommonApplication application )
    {
      var obj = resource.Get();

      if ( ReferenceEquals( obj, null ) )
        return true;

      if ( obj is Texture && !string.IsNullOrEmpty( ( obj as Texture ).generatedFileName ) )
        return true;

      FieldsWalker.DepthController depth = new FieldsWalker.DepthController( 0, FieldsWalker.ObjectType.DBPtr, FieldsWalker.ObjectType.All );
      FieldsWalker.VisitFields<SrcFile, SrcFileAttribute>( obj, Functor, depth.Functor );

      int cnt = 0;
      foreach ( var f in refsToFiles )
      {
        if ( !application.SourceFileSystem.IsFileExists( f.Key.FileName ) )
        {
          string suggestedName;
          if ( f.Value != null && string.IsNullOrEmpty( f.Value.SourceFolder ) )
            suggestedName = FileUtils.Combine( FileUtils.GetFolderName( f.Key.GetOwner().DBId.FileName ), FileUtils.GetFileName( f.Key.FileName ) );
          else
            suggestedName = FileUtils.Combine( FileUtils.GetFolderName( f.Value.SourceFolder ), FileUtils.GetFileName( f.Key.FileName ) );


          if ( suggestedName == f.Key.FileName && !application.SourceFileSystem.IsFileExists( suggestedName ) )
          {
            Log.TraceError( "File missing: {0} | refferer: {1} ", f.Key.FileName, f.Key.GetOwner().DBId.FileName );
            cnt++;
          }
          else
          {
            Log.TraceWarning( "Correcting {0} to {1} in {2}", f.Key.FileName, suggestedName, f.Key.GetOwner().DBId.FileName );
            f.Key.SetFileName( suggestedName );
          }
        }
      }


      return ShouldFixErrors;
    }
  }
}
