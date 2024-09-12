/*
#about Правит параметры переходов рандомных нот
*/
using System.Collections;
using System.Collections.Generic;
using DBTypes;
using EditorLib.IO;
using libdb.DB;
using libdb.Diagnostics;

public class FixRandomNodes
{
  //private int dispathcerToRandom = 0;
	private int randomToDispatcher = 0;

	private void DoFromDispatcherToRandom( AnGrFlMultiTransaction link )
	{
    //++dispathcerToRandom;
	}

	private void DoFromRandomToDispatcher( AnGrFlMultiTransaction link )
	{
		++randomToDispatcher;
    link.parameters.blending = EAnGrTransactionUpdate.PoseToAnim;
    link.parameters.duration = 0.1f;
	}

	private bool HasLinkTo( AnGrMacronode node, string to )
	{
		foreach ( var link in node.simpleTransactions )
		{
			if ( link.targetNode == to )
				return true;
		}

		return false;
	}

	public IEnumerable Main( EditorLib.IEditorCommonApplication app )
	{
		List<DBID> dbids;
		ObjectsSelector.CollectObjects( app, "/", typeof( AnimGraphCreator ), true, true, out dbids );
		foreach ( DBID dbid in dbids )
		{
      //dispathcerToRandom = 0;
			randomToDispatcher = 0;
			AnimGraphCreator obj = DataBase.Get<AnimGraphCreator>( dbid ).Get();
			Dictionary<string, AnGrMacronode> nodes = new Dictionary<string, AnGrMacronode>();
			foreach ( var node in obj.macroNodes )
			{
				nodes.Add( node.nodeName, node );
			}

			foreach ( var node in obj.macroNodes )
			{
				if ( node.nodeType != EAnGrNodeType.Dispatcher )
					continue;

				// process all lnks from dispathcer to its subnodes
				foreach ( var link in node.simpleTransactions )
				{
					DoFromDispatcherToRandom( link );
					var subNode = nodes[link.targetNode];
					foreach ( var subLink in subNode.simpleTransactions )
					{
						if ( subLink.targetNode == node.nodeName )
						{
							DoFromRandomToDispatcher( subLink );
							break;
						}
					}
				}
			}

			Log.TraceMessage( "AG: \"{0}\": RandomToDispatcher = {1}", dbid, randomToDispatcher );
		}

		DataBase.Store();

		yield return true;
	}
}
