/*
#about Переименование и копирование нод в AG
*/
using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;
using libdb.DB;
using DBTypes;
using libdb.Diagnostics;

namespace Scripts
{
  public class DupNode
  {
    private void RenameNode( DBID animGraphDbid, string name, string newName )
    {
      Log.TraceMessage( "Rename node \"{0}\" to \"{1}\" in animation graph \"{2}\"", name, newName, animGraphDbid );
      AnimGraphCreator animGraph = DataBase.Get<AnimGraphCreator>( animGraphDbid ).Get();
      if ( animGraph.defaultNode == name )
        animGraph.defaultNode = newName;
      foreach ( var node in animGraph.macroNodes )
      {
        if ( node.nodeName == name )
          node.nodeName = newName;
        if ( node.nextNode == name )
          node.nextNode = name;
        foreach ( var link in node.simpleTransactions )
        {
          if ( link.targetNode == name )
            link.targetNode = newName;
        }
      }
    }

    private void CopyNode( DBID animGraphDbid, string srcName, string destName )
    {
      Log.TraceMessage( "Copy node \"{0}\" to \"{1}\" in animation graph \"{2}\"", srcName, destName, animGraphDbid );
      AnimGraphCreator animGraph = DataBase.Get<AnimGraphCreator>( animGraphDbid ).Get();
      AnGrMacronode srcNode = null;
      foreach ( var node in animGraph.macroNodes )
      {
        if ( node.nodeName == srcName )
        {
          srcNode = node;
          break;
        }
      }

      if ( srcNode == null )
      {
        Log.TraceWarning( "Node \"{0}\" not found in \"{1}\"", srcName, animGraphDbid );
        return;
      }

      animGraph.macroNodes.Add( new AnGrMacronode( animGraph, srcNode ) );
      AnGrMacronode destNode = animGraph.macroNodes[animGraph.macroNodes.Count - 1];
      destNode.nodeName = destName;
      if ( srcNode.nextNode == srcNode.nodeName )
        destNode.nextNode = destNode.nodeName;

      foreach ( var node in animGraph.macroNodes )
      {
        if ( node == srcNode )
          continue;

        AnGrFlMultiTransaction linkSrcNode = null;
        foreach ( var link in node.simpleTransactions )
        {
          if ( link.targetNode == srcNode.nodeName )
          {
            linkSrcNode = link;
            break;
          }
        }
        if ( linkSrcNode == null )
          continue;

        if ( node == destNode )
          linkSrcNode.targetNode = destNode.nodeName;
        else
        {
          node.simpleTransactions.Add( new AnGrFlMultiTransaction( animGraph, linkSrcNode ) );
          AnGrFlMultiTransaction linkDestNode = node.simpleTransactions[node.simpleTransactions.Count - 1];
          if ( linkDestNode == null )
          {
            Log.TraceWarning( "Added link not found" );
            return;
          }
          linkDestNode.targetNode = destNode.nodeName;
        }
      }
    }

    public IEnumerable Main( EditorLib.IEditorCommonApplication app )
    {
      DBID dbid = DBID.FromString( @"/Heroes/Female/_.ANGR" );

      CopyNode( dbid, "ability2", "ability2_1" );
      CopyNode( dbid, "ability2", "ability2_2" );
      RenameNode( dbid, "ability2", "ability2_3" );

      yield return true;
    }
  }
}
