/*
#about Добавляет переход из одной ноды в другую
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
    private const string TARGET_NODE_NAME = "death";//название ноды, линки в которую надо править
    private const string FROM_NODE_NAME = "revive";//название ноды, линки из которой надо править ( "" - из всех )
    private const float MIN_FROM = 1.0f;

    private IEditorCommonApplication application;

    public IEnumerable Main( IEditorCommonApplication _application )
    {
      application = _application;
      application.OperationExecutor.Start( Work );

      yield return true;
    }

    private bool IsOurNode( string nodeName )
    {
	  // начинается на FROM_NODE_NAME
      //return nodeName.IndexOf( FROM_NODE_NAME, System.StringComparison.InvariantCultureIgnoreCase ) == 0;
	  // точное соответствие
	  return nodeName==FROM_NODE_NAME;
    }

    private bool Work( IOperationContext context )
    {
      int linksProcessed = 0;

      context.Start( true, true );
      context.Progress( "Searching for links..." );
      Log.TraceMessage( "Searching for links..." );

      List<DBID> dbids;

      ObjectsSelector.CollectObjects( application, "/", typeof( AnimGraphCreator ), true, true, out dbids );

      context.Progress( "Found, create links..." );
      Log.TraceMessage( "Found, create links..." );

      foreach ( DBID dbid in dbids )
      {
        AnimGraphCreator animGraphCreator = DataBase.Get<AnimGraphCreator>( dbid ).Get();

        foreach ( var node in animGraphCreator.macroNodes )
        {
          if ( IsOurNode(node.nodeName) )
          {
            foreach ( var targetNode in animGraphCreator.macroNodes )
            {
              if ( targetNode.nodeName == TARGET_NODE_NAME )
              {
                bool isFound = false;
                foreach ( var transaction in node.simpleTransactions )
                {
                  if ( transaction.targetNode == targetNode.nodeName )
                  {
                    isFound = true;
                  }
                }

                if ( !isFound )
                {
                  var result = new AnGrFlMultiTransaction
                  {
                    targetNode = targetNode.nodeName,
                    probability = 0
                  };

                  result.parameters.fromMin.value = 0;
                  result.parameters.fromMax.value = 1;
                  result.parameters.duration = 1.0f / 10.0f;
                  node.simpleTransactions.Add( result );

                  linksProcessed++;
                  context.Progress( string.Format( "{0} links processed", linksProcessed ) );
                }
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