/*
#about Правит длительность нод
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

namespace Scripts
{
  class FixNodesDuration
  {
    private const string TARGET_NODE_NAME = "idle";//название ноды, линки в которую надо править
    private const string FROM_NODE_NAME = "attack";//название ноды, линки из которой надо править ( "" - из всех )
    private const float MIN_FROM = 1.0f;

    private IEditorCommonApplication application;

    public IEnumerable Main( IEditorCommonApplication _application )
    {
      application = _application;
      application.OperationExecutor.Start( Work );

      yield return true;
    }

    private bool Work( IOperationContext context )
    {
      int linksProcessed = 0;

      context.Start( true, true );
      context.Progress( "Searching for links..." );
      Log.TraceMessage( "Searching for links..." );

      List<DBID> dbids;

      ObjectsSelector.CollectObjects( application, "/", typeof( AnimGraphCreator ), true, true, out dbids );

      foreach ( DBID dbid in dbids )
      {
        AnimGraphCreator animGraphCreator = DataBase.Get<AnimGraphCreator>( dbid ).Get();

        foreach ( var node in animGraphCreator.macroNodes )
        {
          if ( string.IsNullOrEmpty( FROM_NODE_NAME ) || node.nodeName.IndexOf( FROM_NODE_NAME, System.StringComparison.InvariantCultureIgnoreCase ) >= 0 )
          {
            for ( int i = 0; i < node.simpleTransactions.Count; ++i )
            {
              var link = node.simpleTransactions[i];

              if ( link.targetNode.Equals( TARGET_NODE_NAME, System.StringComparison.InvariantCultureIgnoreCase ) )
              {
                link.parameters.fromMin.value = MIN_FROM;
                linksProcessed++;
                context.Progress( string.Format( "{0} links processed", linksProcessed ) );
              }
            }
          }
        }
      }

      if ( linksProcessed > 0 )
        DataBase.Store();

      context.Progress( string.Format( "Operation completed successfuly. {0} links processed.", linksProcessed ) );
      Log.TraceMessage( "Operation completed successfuly. {0} links processed.", linksProcessed );

      return true;
    }
  }
}
