/*
#about Правит неправильно заданные NextNode
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
	class FixNextNode
	{
		private IEditorCommonApplication application;

		public IEnumerable Main(IEditorCommonApplication _application)
		{
			application = _application;
			application.OperationExecutor.Start(Work);

			yield return true;
		}

		private bool Work(IOperationContext context)
		{
			int nodesProcessed = 0;

			context.Start(true, true);
			context.Progress("Searching nodes...");
			Log.TraceMessage("Searching nodes...");

			List<DBID> dbids;

			ObjectsSelector.CollectObjects(application, "/", typeof(AnimGraphCreator), true, true, out dbids);
			
			foreach(DBID dbid in dbids)
			{
				AnimGraphCreator animGraphCreator = DataBase.Get<AnimGraphCreator>(dbid).Get();

        string animGraphName = animGraphCreator.DBId.Name;
			  bool isPrinted = false;

				foreach(var node in animGraphCreator.macroNodes)
				{
          if(node.nodeType == EAnGrNodeType.Dispatcher)
          {
            string nextNodeValue = string.Empty;//будет содержать nextNode первой сабноды диспатчера

            foreach( var link in node.simpleTransactions )
            {
              var subnode = GetNodeByName( animGraphCreator.macroNodes, link.targetNode );

              if( subnode != null && subnode.nodeType == EAnGrNodeType.SubNode )
              {
                if(string.IsNullOrEmpty( nextNodeValue ))
                {
                  nextNodeValue = subnode.nextNode;//это первая сабнода диспатчера  
                  continue;
                }

                if(subnode.nextNode != nextNodeValue)
                {
                  if(!isPrinted)
                  {
                    //выводим название анимграфа, если оно еще не выведено
                    Log.TraceMessage( "AnimGraph: " + animGraphName );
                    isPrinted = true;
                  }                 

                  Log.TraceMessage( string.Format( "NextNode for '{0}' fixed from '{1}' to '{2}'", subnode.nodeName, subnode.nextNode, nextNodeValue ) );
                  subnode.nextNode = nextNodeValue;
                  nodesProcessed++;
                }
              }
            }
          }
				}
			}

			if(nodesProcessed > 0)
				DataBase.Store();

			context.Progress(string.Format("Operation completed successfuly. {0} SubNodes processed.", nodesProcessed));
      Log.TraceMessage( "Operation completed successfuly. {0} SubNodes processed.", nodesProcessed );

			return true;
		}

    private AnGrMacronode GetNodeByName(IList<AnGrMacronode> nodes, string _name)
    {
      foreach( var node in nodes )
      {
        if(node.nodeName == _name)
          return node;
      }

      return null;
    }
	}
}
