/*
 * @file    DiAnGrEditor.cpp
 * @memo    DiAnimGraph functions that should be called only in Editor (not for run-time!)
 * @author  EugBel
 * @date    24.04.2009
 */

// *******************************************************************
// includes
#include "stdafx.h"

#include "DiAnGr.h"

///eugbelNSCENE///namespace NScene {

// *******************************************************************
// local data


// *******************************************************************
// functions
bool DiAnimGraph::EOPlayAnimation( int idx )
{
  NI_VERIFY( 0 <= idx && idx < int(GetNumNodes()), "Wrong index of animation!", return false; );

  return Restart( idx, true );
}

bool DiAnimGraph::EOPlayAnimation( string name )
{
  NI_VERIFY( name.length() > 0, "Zero-length animation name passed!", return false; );

  int idx = GetNodeIDByNameSlow( name.c_str() );
  NI_VERIFY( 0 <= idx && idx < int(GetNumNodes()), "Wrong index of animation!", return false; );  

  return EOPlayAnimation( idx );
}

void DiAnimGraph::EOSetGlobalAnimGraphSpeed( float globalSpeed, float *prevGlobalSpeed )
{
  if (prevGlobalSpeed != NULL)
    *prevGlobalSpeed = GetGraphSpeedCoeff();

  SetGraphSpeedCoeff(globalSpeed);
}

bool DiAnimGraph::EOPauseCurrentNode( InOut &dataToSave )
{
  // Save in-out information of the node
  DiUInt32 curNode = GetCurNodeUnsafe();
  if (DIANGR_NO_SUCH_ELEMENT == curNode)
    return false;

  DiAnimNode *nodeData = GetNodeData(curNode);
  NI_ASSERT(nodeData != NULL, "Logic failed");
  DiAnGrSequence *seq  = nodeData->GetSequences(); // seq #0
  NI_ASSERT(seq != NULL, "Seq failed");

  if (DiFAbs(seq->GetStartPar() - seq->GetStopPar()) < 0.0001f)
  {
    NI_ALWAYS_ASSERT("Called Pause without calling Resume!");
    return false;
  }

  dataToSave.Clear();
  dataToSave.m_in         = seq->GetStartPar();
  dataToSave.m_out        = seq->GetStopPar();
  dataToSave.m_valid      = true;
  dataToSave.m_curNodeIdx = curNode; // for assertions

  seq->SetStartPar(nodeData->GetVPar());
  seq->SetStopPar(nodeData->GetVPar());

  return true;
}

bool DiAnimGraph::EOGotoInCurrentNode( float virtualParameter )
{
  // Save in-out information of the node
  DiUInt32 curNode = GetCurNodeUnsafe();
  if (DIANGR_NO_SUCH_ELEMENT == curNode)
    return false;

  DiAnimNode *nodeData = GetNodeData(curNode);
  NI_ASSERT(nodeData != NULL, "Logic failed");
  DiAnGrSequence *seq  = nodeData->GetSequences(); // seq #0
  NI_ASSERT(seq != NULL, "Seq failed");

  if (DiFAbs(seq->GetStartPar() - seq->GetStopPar()) > 0.0001f)
  {
    NI_ALWAYS_ASSERT("Forgot to call Pause?");
    return false;
  }

  seq->SetStartPar(virtualParameter);
  seq->SetStopPar(virtualParameter);
  return true;
}

bool DiAnimGraph::EOResumeCurrentNode( const InOut &savedData )
{
  if ( !savedData.m_valid || savedData.m_curNodeIdx != int(GetCurNodeUnsafe()) )
  {
    NI_ALWAYS_ASSERT("Forgot to call Pause?");
    return false;
  }

  // Restore in-out information of the node
  DiUInt32 curNode = GetCurNodeUnsafe();
  if (DIANGR_NO_SUCH_ELEMENT == curNode)
    return false;

  DiAnimNode *nodeData = GetNodeData(curNode);
  NI_ASSERT(nodeData != NULL, "Logic failed");
  DiAnGrSequence *seq  = nodeData->GetSequences(); // seq #0
  NI_ASSERT(seq != NULL, "Seq failed");

  if (DiFAbs(seq->GetStartPar() - seq->GetStopPar()) > 0.0001f)
  {
    NI_ALWAYS_ASSERT("Called Resume without calling Pause!");
    return false;
  }

  seq->SetStartPar(savedData.m_in);
  seq->SetStopPar(savedData.m_out);
  
  return true;
}

bool DiAnimGraph::EOSetAnimationRangeInCurrentNode( float virtParStart, float virtParStop )
{
  DiUInt32 curNode = GetCurNodeUnsafe();
  if (DIANGR_NO_SUCH_ELEMENT == curNode)
    return false;

  DiAnimNode *nodeData = GetNodeData(curNode);
  NI_ASSERT(nodeData != NULL, "Logic failed");
  DiAnGrSequence *seq  = nodeData->GetSequences(); // seq #0
  NI_ASSERT(seq != NULL, "Seq failed");

  if (DiFAbs(seq->GetStartPar() - seq->GetStopPar()) < 0.0001f)
  {
    NI_ALWAYS_ASSERT("Node is in pause? Do not mix Pause-Continue with SetAnimationRange!");
    return false;
  }

  seq->SetStartPar(virtParStart);
  seq->SetStopPar(virtParStop);

  return true;
}


///eugbelNSCENE///} // end of namespace NScene
