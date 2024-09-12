using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;
using EditorLib;
using libdb.DB;
using libdb.Diagnostics;

namespace Scripts
{
  public class CheckReimport
  {
    public IEnumerable Main( IEditorWinApplication application )
    {
      application.Application.Extensions.OpenEditor( DBID.FromString( "/Tech/Default/Default.SOBJ" ), application, null, false );
      Log.TraceMessage( application.Application.SourceFileSystem.RootPath );

      yield return true;
    }
  }
}
