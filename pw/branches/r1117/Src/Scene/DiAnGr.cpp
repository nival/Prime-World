/*
 * @file    DiAnGr.cpp
 * @memo    Animation Graph support
 * @author  EugBel
 * @date    06.09.2003
 * @prefix  DiAnGr
 * @header  DiAnGr.h
 * @library skeleton.lib
 */

// *******************************************************************
// includes

#include "stdafx.h"

#include "DiAnGr.h"
#include "../system/SystemLog.h"

///eugbelNSCENE///namespace NScene {

namespace
{
  // special user data for markers
  //static SpeedUserData *s_speedResetUserData = NULL;

  const int s_invalidTime = -1;

  struct EditorSliderData
  {
    struct SeqInOutData
    {
      float m_in;
      float m_out;

      SeqInOutData() : m_in(0.0f), m_out(1.0f) {}
      SeqInOutData(const SeqInOutData &seq) : m_in(seq.m_in), m_out(seq.m_out) {}
    };
    
    nstl::vector<SeqInOutData> m_internalNodes;
    nstl::string               m_nodeName;
    bool                       m_wasNodeLooped;
    int                        m_savedDefNextNode;
    bool                       m_pausedForPreview;

    EditorSliderData() : m_nodeName(""), m_wasNodeLooped(false), m_savedDefNextNode(-1), m_pausedForPreview(false) {}
    void Clear()
    {
      m_internalNodes.clear();
      m_nodeName.clear();
      m_wasNodeLooped    = false;
      m_savedDefNextNode = -1;
      m_pausedForPreview = false;
    }
  };

  static EditorSliderData s_editorDataSave;
  bool g_bEnablePathLogging = false;
}

// *******************************************************************
// defines

// *******************************************************************
// local data

#ifdef GRAPH_NEED_USERDATA
/**
* @memo    Read user data from file
* @return  true if read was successful
* @param   cpCsv    The name of main csv data file
* @author  Matthew
*/
bool DiAnimGraph::ReadUserDataFromFile(const char *cpCsv)
{
  bool bOk = KicksData::FromFileToGraph(cpCsv, &UDDAGWrapper(this));
  if (!bOk)
    KicksData::CreateEmpty(&UDDAGWrapper(this));
  return bOk;
}
/**
  @brief    Manually allocates memory to user data.
            We see such function because in game CAnimGraphDoc doesn't exist
            And in AnimGraph tool DiAnimGraph sometimes doesn't exist
            So memory automatically allocated in CAnimGraphDoc (because I begin work from it)
            But in game this function is called manually before ReadUserDataFromFile()

  @see      bool DiAnimGraph::ReadUserDataFromFile(const char *cpCsv)
  @author   Matthew
*/
void DiAnimGraph::CreateEmptyUserData()
{
  KicksData::CreateEmpty(&UDDAGWrapper(this));
}
void DiAnimGraph::DestroyUserData()
{
  KicksData::DestroyData(&UDDAGWrapper(this));
}
#endif //GRAPH_NEED_USERDATA

void DiAnimGraph::EnablePathLogging(bool enableLogging)
{
  g_bEnablePathLogging = enableLogging;
}

void DiAnimGraph::PreReadParams::clear()
{
  nNumNodes = nNumFlTransactions = 
  nNumMacronodes = nNumInternalNodes = nNumSequencesPerNode =
  nNumGeneralTransactions = nNumMultiFlTransactions = 0;
}

DiAnimGraph::PathSetupInfo::PathSetupInfo()
{
  Clear();
}

void DiAnimGraph::PathSetupInfo::Clear()
{
  bPathSpecified    = FALSE;
  nNextNode         = DIANGR_NO_SUCH_ELEMENT;
  nGPTargetNode     = DIANGR_NO_SUCH_ELEMENT;
  nGPPathLength     = 0;
  nGPCurIdxInPath   = DIANGR_NO_SUCH_ELEMENT;
  pGraph            = NULL;
  
  memset(npGPPath, 0, sizeof(npGPPath[0]) * DIANGR_MAX_MARKER_PATH_LENGTH);
}

bool DiAnimGraph::PathSetupInfo::operator == (const DiAnimGraph::PathSetupInfo &other) const
{
  // very specific comparison! If path exist - compare only path, if path is invalid - compare only nextNode
  if (bPathSpecified)
  {
    for (int i = 0; i < int(nGPPathLength); i++)
      if (npGPPath[i] != other.npGPPath[i])
      {
        bool nodeAfterSwitcher = (i > 0 && pGraph->GetNodeData(npGPPath[i - 1])->IsSwitcher());
        if (!nodeAfterSwitcher)
          return false;
      }

    return true;
  }
  else
  {
    return (nNextNode == other.nNextNode);
  }

}


void DiAnimGraph::PathSetupInfo::SetNothingToDo()
{
  bPathSpecified = FALSE;
  nNextNode      = DIANGR_NO_SUCH_ELEMENT;
}

void DiAnimGraph::PathSetupInfo::SetByNextNode(DiUInt32 nextNode)
{
  bPathSpecified      = FALSE;
  nNextNode           = nextNode;
  nGPTargetNode       = DIANGR_NO_SUCH_ELEMENT;
  nGPPathLength       = 0;
  nGPCurIdxInPath     = DIANGR_NO_SUCH_ELEMENT;
}

bool DiAnimGraph::PathSetupInfo::IsTarget(DiUInt32 targetToCheck) const
{
  if (bPathSpecified)
    return (nGPTargetNode == targetToCheck && npGPPath[nGPPathLength - 1] == targetToCheck);

  return (nNextNode == targetToCheck);
}

bool DiAnimGraph::PathSetupInfo::IsEmpty() const
{
  return (!bPathSpecified && nNextNode == DIANGR_NO_SUCH_ELEMENT);
}


void DiAnimGraph::PathSetupInfo::ChangeElemInPath(int idxInPath, DiUInt32 newValue)
{
  if (idxInPath == int(nGPPathLength) - 1)
  {
    nGPTargetNode = newValue;
  }
  if (idxInPath == 1)
  {
    nNextNode = newValue;
  }
  npGPPath[idxInPath] = newValue;
}

void DiAnimGraph::PathSetupInfo::SetByPath(DiUInt32 const *path, DiUInt32 length, bool skipFirstElement)
{
  NI_VERIFY(length < DIANGR_MAX_MARKER_PATH_LENGTH, "Increase pre-defined max length", return;);

  int startIdx = 0;
  if (skipFirstElement)
  {
    npGPPath[0] = DIANGR_NO_SUCH_ELEMENT;
    startIdx    = 1;
  }

  for (int i = 0; i < int(length); i++)
  {
    npGPPath[i + startIdx] = path[i];
  }
  nGPPathLength = length + startIdx;
  
  nGPCurIdxInPath = 0;
  nGPTargetNode   = npGPPath[nGPPathLength - 1];
  nNextNode       = npGPPath[1];
  bPathSpecified  = TRUE;
}

DiAnimGraph::PathToMarker::PathToMarker() : nTimeInMS(0)
{
}

void DiAnimGraph::AddPathIfUnique(const DiAnimGraph::PathToMarker &newPath, vector<DiAnimGraph::PathToMarker> &pathsToMarker)
{
  for (int i = 0; i < pathsToMarker.size(); i++)
  {
    if (newPath.pathInfo == pathsToMarker[i].pathInfo)
    {
      AGTrace("AddPathIfUnique: such path already exists! Will not be added to comparison.");
      return;
    }
  }

  pathsToMarker.push_back(newPath);
  AGTrace("AddPathIfUnique: added path (first four): %i-%i-%i-%i, nextNode=%i, time=%i", 
          newPath.pathInfo.npGPPath[0], newPath.pathInfo.npGPPath[1], newPath.pathInfo.npGPPath[2], newPath.pathInfo.npGPPath[3], 
          newPath.pathInfo.nNextNode, newPath.nTimeInMS);
}

/**
 * @memo    Set clumps array for animation graph
 * @return  None
 * @param   clppClumps
 * @param   nClumps
 * @author  Earnol
 * @see     Nothing
 */
DiVoid DiAnimGraph::SetBlender(NScene::IAnimGraphBlender **cppComponents, DiInt32 nComponents)
{
  DiUInt32       nNodeI;
  DiInt32        nNumSeqs, nClumpI, nSeqI;
  DiAnGrSequence *spSequences;
  DiAnimNode     *anpNode;

  DIFUNCTION("DiAnimGraph::SetBlender");
  //self check
  DIASSERT(nComponents == 0 || nNumSeqsPerNode == nComponents);
  DIASSERT(nNumSeqsPerNode <= DIANGR_MAX_NUM_SEQS_IN_NODE);

  for(nClumpI = 0; nClumpI < nNumSeqsPerNode; nClumpI++)
  {
    cpaSceneComponents[nClumpI] = cppComponents[nClumpI];
  
    // update speeds in nodes if value == INVALID
    // ASSUME sequences have consecutive indices
    for (nNodeI = 0; nNodeI < GetNumNodes(); nNodeI++)  
    {
      anpNode = GetNodeData(nNodeI);
      spSequences = anpNode->spSequences;

      if (anpNode->IsMacronode())
        nNumSeqs = nNumSeqsPerNode * ((DiAnimMacronode *)anpNode)->nNumInternalNodes;
      else // simple node
        nNumSeqs = nNumSeqsPerNode;

      for (nSeqI = 0; nSeqI < nNumSeqs; nSeqI++)
      {
        if (DIANGR_INVALID_FLOAT_VALUE == spSequences[nSeqI].rSpeed)
        {
          spSequences[nSeqI].rSpeed = 1.0f;
        }
      } // end of cycle by sequences
    
      if ( nNumSeqs > 0 )
      {
        if ( spSequences[0].rStopPar - spSequences[0].rStartPar > 0.0001f )
        {
          float InOutValues = spSequences[0].rStopPar - spSequences[0].rStartPar;
          anpNode->SetMultiplier( cpaSceneComponents[nClumpI]->GetAnimDuration(spSequences[0].nID) * InOutValues );
        }
        else
        {
          anpNode->SetMultiplier( 1.0f/30.0f );
        }
        anpNode->SetSpeed( spSequences[0].rSpeed / anpNode->GetMultiplier() );
        anpNode->SetLogicSpeed( 1.0f );
        spSequences[0].rSpeed = 1.0f;
      }
    }// end of cycle by nodes
  }// end of cycle by clumps
  
  DIRETURNVOID();
}// end of DiAnimGraph::SetClumps

NScene::IAnimGraphBlender *DiAnimGraph::GetBlender()
{
  DIASSERT(1 == nNumSeqsPerNode); // Use this function only in this case!

  return cpaSceneComponents[0];
}

/**
 * This function sets animation in node
 *
 * @memo    Set animation params in node (low level)
 * @return  none
 */
DiVoid DiAnimGraph::SetAnimationNode()
{
  DiInt32           nI;
  DiAnimNode        *npNode;   
  DiFloat           rWeight;
  
  npNode = GetNodeData(this->GetCurNode());
  DIASSERT(FALSE == npNode->bIsThisMacronode);
  // pass to low level
  for(nI = 0; nI < nNumSeqsPerNode; nI++)
  {
    rWeight = 1.0f;
    cpaSceneComponents[nI]->RegisterSequencesToMix(1, (int*)&((npNode->spSequences + nI)->nID), &rWeight); 
    cpaSceneComponents[nI]->SetVirtualParameterByMix(nI, DiFFitIn((npNode->spSequences + nI)->rCurPar, 0.f, 1.f)); 
  }
}

/**
 * This function sets animation in Macronode
 *
 * @memo    Set animation params in node (low level)
 * @return  none
 */
DiVoid DiAnimGraph::SetAnimationMacronode()
{
  DiInt32           nI, nJ, nNumIntNodes;
  DiAnimMacronode   *mnpNode;
  DiFloat           *raWeights;
  DiInt32           *naSeqs;

  mnpNode = (DiAnimMacronode *)GetNodeData(this->GetCurNode());
  DIASSERT(DiBool(TRUE) == mnpNode->bIsThisMacronode);
  nNumIntNodes = mnpNode->nNumInternalNodes;

  // allocate memory for sequence index buffer
  naSeqs    = (DiInt32 *)DiMemAllocateTmp(sizeof(DiInt32) * nNumIntNodes);
  raWeights = (DiFloat *)DiMemAllocateTmp(sizeof(DiFloat) * nNumIntNodes);
  if (NULL == naSeqs || NULL == raWeights)
  {
    DIASSERT_ALOOF_CODE(GetDBFileName());
    DiMemFreeTmp(raWeights);
    DiMemFreeTmp(naSeqs);
    DIRETURNVOID();
  }

  // pass to low level
  for(nI = 0; nI < nNumSeqsPerNode; nI++)
  {
    // fill arrays
    DiFloat rSum(0.0f);
    for (nJ = 0; nJ < nNumIntNodes; nJ++)
    {
      naSeqs[nJ]    = mnpNode->spSequences[nJ * nNumSeqsPerNode + nI].nID;
      raWeights[nJ] = mnpNode->spSequences[nJ * nNumSeqsPerNode + nI].rWeight;
      rSum += raWeights[nJ];
    }
    NI_ASSERT( fabs(rSum - 1.0f) < 0.0001f, "Weights!" ); 

    cpaSceneComponents[nI]->RegisterSequencesToMix(nNumIntNodes, (int*)naSeqs, raWeights); 
    // set virtual params for all sequences
    for (nJ = 0; nJ < nNumIntNodes; nJ++)
    {
      cpaSceneComponents[nI]->SetVirtualParameterByMix(nJ * nNumSeqsPerNode + nI,
                                DiFFitIn(mnpNode->spSequences[nJ * nNumSeqsPerNode + nI].rCurPar, 0.f, 1.f)); 
    }
  }
  //clean up
  DiMemFreeTmp(raWeights);
  DiMemFreeTmp(naSeqs);
}

/**
 * This function sets animation in transaction from node to node
 *
 * @memo    Set animation params in node (low level)
 * @return  none
 */
DiVoid DiAnimGraph::SetAnimationTransactionNode2Node()
{
  DiInt32           nI;
  DiAnimNode        *npNextNode;   
  DiAnimNode        *npPrevNode;   
  DiAnimFlTransaction *tpTrans;
  DiFloat           raWeights[2];
  DiInt32           naSeqs[2];

  //more complex apporoach here.
  tpTrans = GetTransactionData(GetCurTransaction(), GetCurSubTransaction());
  npPrevNode = GetNodeData(this->GetPrevNode());
  npNextNode = GetNodeData(this->GetNextNode());
  //set next node to desired state
  
  SetupVParOfNextNodeInTransaction(npNextNode, tpTrans);

  // pass to low level
  for(nI = 0; nI < nNumSeqsPerNode; nI++)
  {
    //set params for target node
    naSeqs[0] = (npPrevNode->spSequences + nI)->nID;
    naSeqs[1] = (npNextNode->spSequences + nI)->nID;
    raWeights[0] = 1.0f - this->GetCurTransactionPar();
    raWeights[1] = this->GetCurTransactionPar();
    cpaSceneComponents[nI]->RegisterSequencesToMix(2, (int*)naSeqs, raWeights); 
    
    // set virtual parameters directly to remove "if"
    cpaSceneComponents[nI]->SetVirtualParameterByMix(0, DiFFitIn((npPrevNode->spSequences + nI)->rCurPar, 0.f, 1.f)); 
    cpaSceneComponents[nI]->SetVirtualParameterByMix(1, DiFFitIn((npNextNode->spSequences + nI)->rCurPar, 0.f, 1.f)); 
  }    
}

/**
 * This function sets animation in transaction from node to Macronode
 *
 * @memo    Set animation params in node (low level)
 * @return  none
 */
DiVoid DiAnimGraph::SetAnimationTransactionNode2Macronode()
{
  DiInt32           nI, nJ, nNumIntNodes;
  DiAnimMacronode   *mnpNextNode;   
  DiAnimNode        *npPrevNode;   
  DiAnimFlTransaction *tpTrans;
  DiFloat           *raWeights;
  DiInt32           *naSeqs;

  tpTrans       = GetTransactionData(GetCurTransaction(), GetCurSubTransaction());
  npPrevNode    = GetNodeData(this->GetPrevNode());
  mnpNextNode   = (DiAnimMacronode *)GetNodeData(this->GetNextNode());
  DIASSERT(DiBool(TRUE) == mnpNextNode->bIsThisMacronode);
  nNumIntNodes  = mnpNextNode->nNumInternalNodes;
  DIASSERT(nNumIntNodes > 0);

  //set next node to desired state
  SetupVParOfNextNodeInTransaction(mnpNextNode, tpTrans);
  
  // pass to low level
  for(nI = 0; nI < nNumSeqsPerNode; nI++)
  {
    //set params for target node
    naSeqs        = (DiInt32 *)DiMemAllocateTmp(sizeof(DiInt32) * (1 + nNumIntNodes));
    naSeqs[0]     = (npPrevNode->spSequences + nI)->nID;
    raWeights     = (DiFloat*)DiMemAllocateTmp(sizeof(DiFloat) * (1 + nNumIntNodes));
    raWeights[0]  = 1.0f - this->GetCurTransactionPar();    

    #ifdef DIDEBUG
      // check that sum of all weights == 1.0f
      DiFloat rSum = 0;
      DiInt32 nCurIntNode;
      for (nCurIntNode = 0; nCurIntNode < nNumIntNodes; nCurIntNode++)
      {
        rSum += mnpNextNode->spSequences[nI  + nCurIntNode * nNumSeqsPerNode].rWeight;
      }                                                                     
      DIASSERT(DiFAbs(rSum - 1.0f) < 0.001f);
    #endif

    // next node is macronode => more complex way
    for (nJ = 0; nJ < nNumIntNodes; nJ++)
    {
      naSeqs[nJ + 1] = mnpNextNode->spSequences[nJ * nNumSeqsPerNode + nI].nID;
      raWeights[nJ + 1] = this->GetCurTransactionPar() * mnpNextNode->spSequences[nJ * nNumSeqsPerNode + nI].rWeight;/// nNumIntNodes;
    }

    cpaSceneComponents[nI]->RegisterSequencesToMix(1 + nNumIntNodes, (int*)naSeqs, raWeights); 

    // set virtual parameters directly
    cpaSceneComponents[nI]->SetVirtualParameterByMix(0, 
                              DiFFitIn((npPrevNode->spSequences + nI)->rCurPar, 
                                       0.0f, 1.0f)); 
    for (nJ = 0; nJ < nNumIntNodes; nJ++)
      cpaSceneComponents[nI]->SetVirtualParameterByMix(nJ + 1, 
                                DiFFitIn(mnpNextNode->spSequences[nJ * nNumSeqsPerNode + nI].rCurPar, 
                                         0.0f, 1.0f)); 
        
    DiMemFreeTmp(raWeights);
    DiMemFreeTmp(naSeqs);
  }
}

/**
 * This function sets animation in transaction from Macronode to Macronode
 *
 * @memo    Set animation params in node (low level)
 * @return  none
 */
DiVoid DiAnimGraph::SetAnimationTransactionMacronode2Macronode()
{
  DiInt32           nI, nJ;
  DiInt32           nPrevNumIntNodes, nNextNumIntNodes;
  DiAnimMacronode   *mnpNextNode;   
  DiAnimMacronode   *mnpPrevNode;   
  DiAnimFlTransaction *tpTrans;
  DiFloat           *raWeights;
  DiInt32           *naSeqs;

  tpTrans       = GetTransactionData(GetCurTransaction(), GetCurSubTransaction());
  mnpPrevNode   = (DiAnimMacronode *)GetNodeData(this->GetPrevNode());
  mnpNextNode   = (DiAnimMacronode *)GetNodeData(this->GetNextNode());
  DIASSERT(DiBool(TRUE) == mnpNextNode->bIsThisMacronode);
  DIASSERT(DiBool(TRUE) == mnpPrevNode->bIsThisMacronode);
  nPrevNumIntNodes  = mnpPrevNode->nNumInternalNodes;
  nNextNumIntNodes  = mnpNextNode->nNumInternalNodes;
  DIASSERT(nNextNumIntNodes > 0);
  DIASSERT(nPrevNumIntNodes > 0);

  // set next node to desired state
  SetupVParOfNextNodeInTransaction(mnpNextNode, tpTrans);
  
  // pass to low level
  for(nI = 0; nI < nNumSeqsPerNode; nI++)
  {
    //set params for target node
    naSeqs        = (DiInt32 *)DiMemAllocateTmp(sizeof(DiInt32) * (nPrevNumIntNodes + nNextNumIntNodes));
    //naSeqs[0]     = (npPrevNode->spSequences + nI)->nID;
    raWeights     = (DiFloat*)DiMemAllocateTmp(sizeof(DiFloat) * (nPrevNumIntNodes + nNextNumIntNodes));
    //raWeights[0]  = 1.0f - this->GetCurTransactionPar();    

    #ifdef DIDEBUG
      // check that sum of all weights == 1.0f
      DiFloat rSum = 0.0f;
      DiInt32 nCurIntNode;
      // check prev macronode
      for (nCurIntNode = 0; nCurIntNode < nPrevNumIntNodes; nCurIntNode++)
      {
        rSum += mnpPrevNode->spSequences[nI  + nCurIntNode * nNumSeqsPerNode].rWeight;
      }                                                                     
      DIASSERT(DiFAbs(rSum - 1.0f) < 0.001f);
      
      // check next macronode
      rSum = 0.0f;
      for (nCurIntNode = 0; nCurIntNode < nNextNumIntNodes; nCurIntNode++)
      {
        rSum += mnpNextNode->spSequences[nI  + nCurIntNode * nNumSeqsPerNode].rWeight;
      }                                                                     
      DIASSERT(DiFAbs(rSum - 1.0f) < 0.001f);

    #endif

    // separate register sequences from macronodes
    for (nJ = 0; nJ < nPrevNumIntNodes; nJ++)
    {
      naSeqs[nJ]    = mnpPrevNode->spSequences[nJ * nNumSeqsPerNode + nI].nID;
      raWeights[nJ] = (1.0f - this->GetCurTransactionPar()) * mnpPrevNode->spSequences[nJ * nNumSeqsPerNode + nI].rWeight;
    }

    for (nJ = 0; nJ < nNextNumIntNodes; nJ++)
    {
      naSeqs[nJ + nPrevNumIntNodes]    = mnpNextNode->spSequences[nJ * nNumSeqsPerNode + nI].nID;
      raWeights[nJ + nPrevNumIntNodes] = this->GetCurTransactionPar() * mnpNextNode->spSequences[nJ * nNumSeqsPerNode + nI].rWeight;
    }

    cpaSceneComponents[nI]->RegisterSequencesToMix(nPrevNumIntNodes + nNextNumIntNodes, (int*)naSeqs, raWeights); 

    // set virtual parameters 
    for (nJ = 0; nJ < nPrevNumIntNodes; nJ++)
      cpaSceneComponents[nI]->SetVirtualParameterByMix(nJ, 
                                DiFFitIn(mnpPrevNode->spSequences[nJ * nNumSeqsPerNode + nI].rCurPar, 
                                         0.f, 1.f)); 

    for (nJ = 0; nJ < nNextNumIntNodes; nJ++)
      cpaSceneComponents[nI]->SetVirtualParameterByMix(nPrevNumIntNodes + nJ, 
                                DiFFitIn(mnpNextNode->spSequences[nJ * nNumSeqsPerNode + nI].rCurPar, 
                                         0.f, 1.f)); 
        
    DiMemFreeTmp(raWeights);
    DiMemFreeTmp(naSeqs);
  }
}

/**
 * This function sets animation in transaction from Macronode to node
 *
 * @memo    Set animation params in node (low level)
 * @return  none
 */
DiVoid DiAnimGraph::SetAnimationTransactionMacronode2Node()
{
  DiInt32           nI, nJ, nNumIntNodes;
  DiAnimNode        *npNextNode;   
  DiAnimMacronode   *mnpPrevNode;   
  DiAnimFlTransaction *tpTrans;
  DiFloat           *raWeights;
  DiInt32           *naSeqs;

  tpTrans       = GetTransactionData(GetCurTransaction(), GetCurSubTransaction());
  mnpPrevNode   = (DiAnimMacronode *)GetNodeData(this->GetPrevNode());
  npNextNode    = GetNodeData(this->GetNextNode());
  DIASSERT(DiBool(TRUE) == mnpPrevNode->bIsThisMacronode);
  nNumIntNodes  = mnpPrevNode->nNumInternalNodes;
  DIASSERT(nNumIntNodes > 0);

  //set next node to desired state
  SetupVParOfNextNodeInTransaction(npNextNode, tpTrans);
  
  // pass to low level
  for(nI = 0; nI < nNumSeqsPerNode; nI++)
  {
    //set params for target node
    naSeqs        = (DiInt32 *)DiMemAllocateTmp(sizeof(DiInt32) * (1 + nNumIntNodes));
    raWeights     = (DiFloat*)DiMemAllocateTmp(sizeof(DiFloat) * (1 + nNumIntNodes));

    #ifdef DIDEBUG
      // check that sum of all weights == 1.0f
      DiFloat rSum = 0;
      DiInt32 nCurIntNode;
      for (nCurIntNode = 0; nCurIntNode < nNumIntNodes; nCurIntNode++)
      {
        rSum += mnpPrevNode->spSequences[nI  + nCurIntNode * nNumSeqsPerNode].rWeight;
      }
      DIASSERT(DiFAbs(rSum - 1.0f) < 0.001f);
    #endif

    // prev node is macronode => complex way
    for (nJ = 0; nJ < nNumIntNodes; nJ++)
    {
      naSeqs[nJ]    = mnpPrevNode->spSequences[nJ * nNumSeqsPerNode + nI].nID;
      raWeights[nJ] = (1.0f - this->GetCurTransactionPar()) * mnpPrevNode->spSequences[nJ * nNumSeqsPerNode + nI].rWeight;/// nNumIntNodes;
    }
    naSeqs[nNumIntNodes]     = (npNextNode->spSequences + nI)->nID;
    raWeights[nNumIntNodes]  = this->GetCurTransactionPar();    

    cpaSceneComponents[nI]->RegisterSequencesToMix(1 + nNumIntNodes, (int*)naSeqs, raWeights); 

    // set virtual parameters directly
    for (nJ = 0; nJ < nNumIntNodes; nJ++)
      cpaSceneComponents[nI]->SetVirtualParameterByMix(nJ, 
                                DiFFitIn(mnpPrevNode->spSequences[nJ * nNumSeqsPerNode + nI].rCurPar, 
                                         0.f, 1.f)); 
    cpaSceneComponents[nI]->SetVirtualParameterByMix(nNumIntNodes, 
                              DiFFitIn((npNextNode->spSequences + nI)->rCurPar, 
                                       0.f, 1.f)); 
        
    DiMemFreeTmp(raWeights);
    DiMemFreeTmp(naSeqs);
  }
}

/**
 * This function sets transaction params (low level)
 *
 * @memo    Set low level parameters for transaction
 * @return  none
 */
DiVoid DiAnimGraph::SetAnimationTransaction()
{
  DiAnimNode *npPrev, *npNext;
  
  npPrev = GetNodeData(nPrevNode);
  npNext = GetNodeData(nNextNode);
  DIASSERT(npPrev);
  DIASSERT(npNext);

  // call different functions depending on node/macronode history
  if (FALSE == npPrev->bIsThisMacronode && FALSE == npNext->bIsThisMacronode)
    SetAnimationTransactionNode2Node();
  
  if (DiBool(TRUE)  == npPrev->bIsThisMacronode && FALSE == npNext->bIsThisMacronode)
    SetAnimationTransactionMacronode2Node();
  
  if (FALSE == npPrev->bIsThisMacronode && DiBool(TRUE)  == npNext->bIsThisMacronode)
    SetAnimationTransactionNode2Macronode();
  
  if (DiBool(TRUE)  == npPrev->bIsThisMacronode && DiBool(TRUE)  == npNext->bIsThisMacronode)
    SetAnimationTransactionMacronode2Macronode();
}

/**
 * detailed description
 *
 * @memo    Set embedded animation information according graph state
 * @return  None
 * @author  Earnol
 * @see     Nothing
 */
DiVoid DiAnimGraph::SetAnimation()
{
  DiAnimGraphElems  geWhere;

  DIFUNCTION("DiAnimGraph::SetAnimation");

  //where we are?
  geWhere = GetCurElemType();
  DIASSERT(DIANGR_NA != geWhere);
  
  switch(geWhere)
  {
    case DIANGR_NODE:
      SetAnimationNode();
    break;

    case DIANGR_MACRONODE:
      SetAnimationMacronode();
    break;

    case DIANGR_FLTRANSACTION: 
      SetAnimationTransaction();
    break;

    default: 
      DIASSERT_ALOOF_CODE(GetDBFileName());
  }

  /*for(nI = 0; nI < nNumSeqsPerNode; nI++)
  {
    NI_VERIFY(cpaSceneComponents[nI] != NULL, "Suxx!", DIRETURNVOID(););
    NScene::AnimGraphApplicator *pApp = cpaSceneComponents[nI]->GetGraphApplicator();
    NI_VERIFY(pApp != NULL, "Suxx!", DIRETURNVOID(););
    //pApp->ApplyToObject();
  } */

  DIRETURNVOID();
} // end of DiAnimGraph::SetAnimation







/**
 * This function sets node as active element in graph
 *
 * @memo    Set given node as active element
 * @return  TRUE on success, FALSE otherwise
 * @param   nNode
 * @param   rVPar
 * @author  EugBel
 */

DiBool DiAnimGraph::SetNode(DiUInt32 nNode, DiFloat rVPar)
{
  DiAnimNode *anpNode;
  DiBool     bSetDefaultNextNode;

  DIFUNCTION("SetNode");
  
  DIASSERT(nNode < GetNumNodes());
  anpNode = GetNodeData(nNode);
  DIASSERT(anpNode);

  nCurTrans           = DIANGR_NO_SUCH_ELEMENT;
  nCurSubTrans        = DIANGR_NO_SUCH_ELEMENT;
  nCurNode            = nNode;
  bIsCurNodeMacronode = anpNode->bIsThisMacronode;

  // set VPar
  if (rVPar != DIANGR_INVALID_FLOAT_VALUE)
  {
    DIASSERT(0.0f <= rVPar && rVPar <= 1.0f);
    anpNode->rCurPar = rVPar;
  }
  else
  {
    anpNode->rCurPar = anpNode->rStartPar; 
  }
  DIASSERT(0.0f <= anpNode->rCurPar && anpNode->rCurPar <= 1.0f);

  bSetDefaultNextNode = TRUE;
  // if we have some path to go than use it
  if (bPathSpecified && gpPath.nCurIdxInPath < (gpPath.nPathLength - 2))
  {
    // check: nNode should be under (CurIdx + 1)
    if ( gpPath.npPath[gpPath.nCurIdxInPath + 1] != nNode )
    {
      DiAnimNode* node1 = GetNodeData(nNode);
      DiAnimNode* node2 = GetNodeData(gpPath.npPath[gpPath.nCurIdxInPath + 1]);
      if ( !node1->IsSubNode() || !node2->IsSubNode() )
      {
        NI_ALWAYS_ASSERT(  NStr::StrFmt( "Try to set incorrect next node: "
          "try set next node: %s, next node in path: %s, ag: %s", GetNodeNameByID(nNode), GetNodeNameByID(gpPath.npPath[gpPath.nCurIdxInPath + 1]),
          DBFileName.c_str() ) );
      }
      else
      {
        NI_ASSERT( node1->GetDispatcherNodeID() == node2->GetDispatcherNodeID(), NStr::StrFmt( "Try to set incorrect next node: "
          "try set next node: %s, next node in path: %s, ag: %s", GetNodeNameByID(nNode), GetNodeNameByID(gpPath.npPath[gpPath.nCurIdxInPath + 1]),
          DBFileName.c_str() ) );
      }
    }
    gpPath.nCurIdxInPath++;
    nNextNode           = gpPath.npPath[gpPath.nCurIdxInPath + 1];
    bSetDefaultNextNode = FALSE;

    if (gpPath.nPathLength - 1 == gpPath.nCurIdxInPath)
    {
      gpPath.nTargetNode = DIANGR_NO_SUCH_ELEMENT;
    }
  }

  if (bSetDefaultNextNode)
  {
    // set default next node 
    nNextNode = anpNode->nDefNext;
  }

  DIRETURN(TRUE);
} // end of SetNode


/**
 * This function wraps current virtual parameter in given node depending on 
 *          bWrapped and speed
 * @memo    Wrap current virtual parameter if needed
 * @return  none
 * @param   bWrapped        history: was node wrapped or not
 * @param   anpCurNode
 * @author  EugBel
 */
DiVoid DiAnimGraph::WrapCurParIfNeeded(DiBool bWrapped, DiAnimNode *anpNode, DiUInt32 nodeIdx)
{
  if (bWrapped)
  {
    AGTrace("Wrapping node (function WrapCurParIfNeeded)");
    if (anpNode->GetSpeed() > 0.0f)
    {
      if (FALSE == anpNode->bIsLooped && bIsForced )
      {
        bIsForced = 0;
        if ( anpNode->IsSubNode() )
        {
          DiUInt32 newCurNode = SelectNextNodeByProbability( anpNode->GetDispatcherNodeID(), GetNodeData( anpNode->GetDispatcherNodeID() ) );
					SetTargetNodeInternal( newCurNode );
          ResetCallbacksOnParFlag(DIANGR_NODE,anpNode);
          anpNode = GetNodeData( newCurNode );
          ResetCallbacksOnParFlag(DIANGR_NODE,anpNode);
					SetNextNode( anpNode->GetDispatcherNodeID() );
        }
        else
        {
          anpNode->rPrevPar = 0.0f;
          anpNode->rCurPar  = 0.0f;
          ResetCallbacksOnParFlag(DIANGR_NODE,anpNode);
        }
      }
      else if ( FALSE == anpNode->bIsLooped )
      {
        SetNextNode( anpNode->GetDefNextNode() );
      }
      else
      {
        anpNode->rPrevPar = 0.0f;
        anpNode->rCurPar  = 0.0f;
        ResetCallbacksOnParFlag(DIANGR_NODE,anpNode);
      }
    }
    if (anpNode->GetSpeed() < 0.0f)
    {
      if (FALSE == anpNode->bIsLooped && bIsForced )
      {
        bIsForced = 0;
        if ( anpNode->IsSubNode() )
        {
          DiUInt32 newCurNode = SelectNextNodeByProbability( anpNode->GetDispatcherNodeID(), GetNodeData( anpNode->GetDispatcherNodeID() ) );
          SetNode( newCurNode, 1.0f );
          ResetCallbacksOnParFlag(DIANGR_NODE,anpNode);
          anpNode = GetNodeData( newCurNode );
          ResetCallbacksOnParFlag(DIANGR_NODE,anpNode);
          SetNextNode( anpNode->GetDefNextNode() );
        }
        else if ( FALSE == anpNode->bIsLooped )
        {
          SetNextNode( anpNode->GetDefNextNode() );
        }
        else
        {
          anpNode->rPrevPar = 1.0f;
          anpNode->rCurPar  = 1.0f;
          ResetCallbacksOnParFlag(DIANGR_NODE,anpNode);
        }
      }
      else
      {
        anpNode->rPrevPar = 1.0f;
        anpNode->rCurPar  = 1.0f;
        ResetCallbacksOnParFlag(DIANGR_NODE,anpNode);
      }
    }
  }
}

DiVoid DiAnimGraph::ResetSpeedAndUnregCallbackAfterReachMarker(bool restoreGraphSpeed)
{
  SpeedUserData* const last = markersData.last();
  for (SpeedUserData * marker = markersData.first(); marker != last;)
  {
    SpeedUserData *markerNext = markersData.next(marker);

    if(this == marker->animGraph)
    {
      AGTrace("Unregistering callback on marker and resetting speed");
      
      if (restoreGraphSpeed)
        SetGraphSpeedCoeff(marker->prevGraphSpeed);

      UnregisterCallback(marker->elemType, marker->elemID, _resetGraphSpeedCallback, (SpeedUserData *)marker);
      markersData.remove(marker);
      
      // DO NOT place 'break' here: perhaps there are several elements on this graph
    }
    marker = markerNext;
  }
}

/**
 * This function sets given node as target node. This means that it calculates
 *          path to it and remembers it to reach node ASAP
 *
 * @memo    Set target node
 * @return  TRUE on success, FALSE otherwise
 * @param   nNode        node to reach
 * @author  EugBel
 */
DiBool DiAnimGraph::SetTargetNode(DiUInt32 nNode)
{
  AGTrace("=================AG_SET_TARGET_NODE(%i[%s])  (prev target was %i[%s], cur node: %i)", nNode, GetNodeNameByID(nNode), GetTargetNode(), GetNodeNameByID(GetTargetNode()), GetCurNodeUnsafe());

  if ( freezed )
    DIRETURN(TRUE);

  //if ( GetDBFileName().find("/Witch/") != nstl::string::npos )
  //{
  //  if ( GetCurNodeUnsafe() < GetNumNodes() )
  //  {
  //    DiAnimNode* node = GetNodeData( GetCurNode() );
  //    DebugTrace( "CurNode: %s %f\n", GetNodeNameByID( GetCurNode() ), node->GetVPar() );
  //  }
		//DebugTrace( "SetTargetNode: %f %s \n", NHPTimer::GetScalarTime(), GetNodeNameByID(nNode) );
  //}

  ResetSpeedAndUnregCallbackAfterReachMarker(true);

  int nRetInternal = SetTargetNodeInternal(nNode);
  DiBool bRet = nRetInternal;
  if (2 == nRetInternal)
    bRet = FALSE;

  AGTrace("=================AG_SET_TARGET_NODE returned %i (internal ret.value=%i, nextNode=%i[%s])  [1 - is ok, 2 or 0 is error]", 
          int(bRet), nRetInternal, nNextNode, GetNodeNameByID(nNextNode));

  return bRet;
}


void DiAnimGraph::ApplyPath(const PathSetupInfo &pathInfo)
{
  AGTrace("Applying path...");

  if (!pathInfo.bPathSpecified && pathInfo.nNextNode == DIANGR_NO_SUCH_ELEMENT)
  {
    AGTrace("Nothing to apply!");
    return; // nothing to do
  }

  NI_VERIFY(pathInfo.nGPPathLength <= GetNumNodes() + 1, "Too long path", return;);
  NI_ASSERT(!pathInfo.bPathSpecified || (pathInfo.nGPTargetNode == pathInfo.npGPPath[pathInfo.nGPPathLength - 1]), "Wrong path params!");

  bPathSpecified        = pathInfo.bPathSpecified;
  bIsForced = TRUE;
  nNextNode             = pathInfo.nNextNode;

  gpPath.nTargetNode    = pathInfo.nGPTargetNode;
  gpPath.nPathLength    = pathInfo.nGPPathLength;
  gpPath.nCurIdxInPath  = pathInfo.nGPCurIdxInPath;

  memcpy(gpPath.npPath, pathInfo.npGPPath, pathInfo.nGPPathLength * sizeof(gpPath.npPath[0]) );

  AGTrace("Applying path. NextNode=%i[%s], pathLen=%i, path(first 3)=%i[%s], %i[%s], %i[%s]", nNextNode, GetNodeNameByID(nNextNode), gpPath.nPathLength,
          gpPath.npPath[0], GetNodeNameByID(gpPath.npPath[0]), gpPath.npPath[1], GetNodeNameByID(gpPath.npPath[1]), gpPath.npPath[2], GetNodeNameByID(gpPath.npPath[2]));
}

DiBool DiAnimGraph::SetTargetNodeInternal(DiUInt32 nNode)
{
  DiBool            bOk;
  DiUInt32          nFirstNode;
  DiUInt32          nPathLen;
  DiUInt32          nPseudoCurNode;
  DiBool            bInTransaction;
  DiUInt32          nAddition;
  DiBool            bPathInvalid;
  DiAnimGraphElems  geElem;

  DIFUNCTION("SetTargetNode");
  DIASSERT(nNode < GetNumNodes());

  bInTransaction  = FALSE;
  nAddition       = 0;

  geElem = GetCurElemType();
  if (geElem == DIANGR_FLTRANSACTION)
  {
    // nCurNode doesn't exist => set NodeTO from Transaction
    nPseudoCurNode = nNextNode;
    bInTransaction = TRUE;
    nAddition      = 1;
    
    AGTrace("=================AG_SET_TARGET_NODE if#1");
  }
  else
  {
    DIASSERT(geElem == DIANGR_NODE || geElem == DIANGR_MACRONODE );
    nPseudoCurNode = nCurNode;

    AGTrace("=================AG_SET_TARGET_NODE if#2");
  }

  // check trivial cases
  bPathInvalid = FALSE;
  if (nNode == nPseudoCurNode)
  {
    bPathInvalid = TRUE;
    nNextNode    = nNode;
    if (geElem != DIANGR_FLTRANSACTION && !GetNodeData(nNode)->IsLooped())
    {
      //DIASSERT_ALOOF_CODE(GetDBFileName()); // It is wrong to set a non-looped as a target while we are already in it!
      nNextNode = GetNodeData(nNode)->GetDefNextNode();

      AGTrace("=================AG_SET_TARGET_NODE FAILED! Wanted node is non-looped! Wanted=%i, set=%i",nNode, nNextNode);
    }
    AGTrace("=================AG_SET_TARGET_NODE if#3");
  }
  if (nNode == nNextNode)
  {
    AGTrace("=================AG_SET_TARGET_NODE if#4");
    bPathInvalid = TRUE;
  }

  if ((DiBool)TRUE == bPathInvalid)
  {
    AGTrace("=================AG_SET_TARGET_NODE if#5");

    gpPath.nPathLength = 0;
    bPathSpecified     = FALSE;
    gpPath.nTargetNode = DIANGR_NO_SUCH_ELEMENT;

    if (nNode != nNextNode)
      DIRETURN(2);    

    bIsForced = TRUE;
    DIRETURN(1);
  }

  if (bPathSpecified && gpPath.nTargetNode == nNode)
  {
    AGTrace("=================AG_SET_TARGET_NODE if#6");

    //DIRETURN(2);
    bIsForced = TRUE;
    DIRETURN(1);
  }

  // try to find path to reach target node
  bOk = FindShortestWay(nPseudoCurNode,nNode,nPathLen,GetDBFileName(),&nFirstNode);
  if (!bOk)
  {
    DIRETURN(FALSE); // failed to find path to target node
  }

  DIASSERT(nPathLen > 0);
  
  // simple case (target node is neighbor of current node)
  if (!bInTransaction && 2 == nPathLen)
  {
    AGTrace("=================AG_SET_TARGET_NODE if#7");
		
    DIASSERT(0 <= nFirstNode && nFirstNode < GetNumNodes());
    nNextNode = nFirstNode;
    // clear path
    gpPath.nPathLength = 0;
    bPathSpecified     = FALSE;
    gpPath.nTargetNode = DIANGR_NO_SUCH_ELEMENT;
    bIsForced = TRUE;
    DIRETURN(TRUE);
  }

  bOk = GetNodesOfShortestPath(gpPath.npPath + nAddition);
  if (!bOk)
  {
    DIASSERT_ALOOF_CODE(GetDBFileName()); // some problems in DiGraph...
    DIRETURN(FALSE);
  }
  if (bInTransaction)
    gpPath.npPath[0]     = DIANGR_NO_SUCH_ELEMENT; // debug set

  gpPath.nPathLength   = nPathLen + nAddition;
  gpPath.nCurIdxInPath = 0;
  gpPath.nTargetNode   = nNode;

  // set next node (0-current, 1-next)
  nNextNode = gpPath.npPath[1];
  bPathSpecified = TRUE;
  bIsForced = TRUE;
  
  AGTrace("=================AG_SET_TARGET_NODE if#8");

  DIRETURN(TRUE);
} // end of SetTargetNode


/**
 * These two functions converts weight <-> priority of the edge in graph
 *
 * @memo    Convertions between priority and edge weight
 * @return  
 * @param   rPriority
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiUInt16  DiAnimFlTransaction::ConvertPriorToWeight(DiFloat rPriority)
{
  DIASSERT(0.0f <= rPriority && rPriority <= DIANGR_PRIORITY_MAX);
  return (DiUInt16)(DIANGR_PRIORITY_MAX / rPriority);
}
DiFloat   DiAnimFlTransaction::ConvertWeightToPrior(DiUInt16 nWeight)
{
  #ifdef DIDEBUG

    DiFloat rPrior;
    rPrior = (DIANGR_PRIORITY_MAX / DiL2F(nWeight));
    DIASSERT(0.0f <= rPrior && rPrior <= DIANGR_PRIORITY_MAX);

    return rPrior;

  #else

    return (DIANGR_PRIORITY_MAX / DiL2F(nWeight));

  #endif
}

DiVoid DiAnimMTransaction::SetProbability( DiUInt32 _nProbability )
{ 
  NI_ASSERT(0 <= _nProbability && _nProbability <= 100, "Priority: wrong interval!");
  nProbability = _nProbability; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DiAnimGraph::ClearMarkers()
{
  mMarkers.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This function sets new markers (they will overwrite existent markers, if any). To add markers - use AddMarkers()
void DiAnimGraph::SetMarkers(const vector<DiAnGrEditorMarker> &editorMarkers)
{
  mMarkers.clear();

  AddMarkers(editorMarkers);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This function adds markers to AnimGraph. New markers will be added (existent markers will NOT be deleted)
void DiAnimGraph::AddMarkers(const vector<DiAnGrEditorMarker> &editorMarkers)
{
  mMarkers.reserve(mMarkers.size() + editorMarkers.size());
  for (int i = 0; i < editorMarkers.size(); i++)
  {
    // check the marker
    const DiAnGrEditorMarker &cur = editorMarkers[i];
    NI_ASSERT(cur.name.length() > 0, "Empty marker name");
    NI_ASSERT(0.0f <= cur.virtPar && cur.virtPar <= 1.0f, "Virtual parameter out of [0..1]");
    if (EditorGraphParamAddress::VT_NODE == cur.address.type)
    {
      NI_ASSERT(0 <= cur.address.nodeIdx && cur.address.nodeIdx <= int(GetNumNodes()), "Invalid node idx");
    }
    else if (EditorGraphParamAddress::VT_TRANSACTION == cur.address.type)
    {
      NI_ASSERT(0 <= cur.address.nodeIdx && cur.address.nodeIdx <= int(GetNumNodes()), "Invalid node idx");
      NI_ASSERT(0 <= cur.address.nextNodeIdx && cur.address.nextNodeIdx <= int(GetNumNodes()), "Invali node idx");
      NI_ASSERT(0 <= cur.address.subTransIdx, "Invalid sub-transaction idx");
    }
    else
    {
      NI_ALWAYS_ASSERT("Wrong marker owner type"); // wrong owner type! Uninitialized?
    }

    // add marker to the storage
    mMarkers.push_back(DiAnGrMarker(editorMarkers[i], *this));
  }

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DiVoid  DiAnimGraph::SetNumParts(DiInt32 nNumParts) 
{ 
  this->nNumSeqsPerNode = nNumParts; 
} 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DiAnimGraph::AddNodeToStorage(DiUInt32 nNodeID, DiAnGrSimpleStorage::Macronode &macronode,
                                   const NScene::AnimationVector &_animations)
{
  DiAnimNode    *anpNode;
  int						len(0);

  DiAnGrSequence *gspSeqs;

  anpNode = GetNodeData(nNodeID);

  // save node name
  const char *nodeName = GetNodeNameByID(nNodeID);
  if ( nodeName != NULL )
  {
		len = strlen(nodeName) + 1;
		len = len > NODE_NAME_SIZE ? NODE_NAME_SIZE : len;
		
		macronode.nodeName = new char[len];
		strcpy_s(macronode.nodeName, len, nodeName);		
  }

  // save next node name
  const char *nextNodeName = GetNodeNameByID(anpNode->GetDefNextNode());
  if ( nextNodeName != NULL )
  {
		len = strlen(nextNodeName) + 1;
		len = len > NODE_NAME_SIZE ? NODE_NAME_SIZE : len;
		
		macronode.nextNodeName = new char[len];		
		strcpy_s(macronode.nextNodeName, len, nextNodeName);
  }

  // save speed/startPar/stopPar
  macronode.speed       = anpNode->GetSpeed();
  macronode.surfSpeedX  = anpNode->GetSurfSpeed().x;
  macronode.surfSpeedY  = anpNode->GetSurfSpeed().y;

  macronode.startPar    = anpNode->GetStartPar();
  macronode.stopPar     = anpNode->GetStopPar();

  // save sequence(s)
  gspSeqs = anpNode->GetSequences();
  DIASSERT(GetNumParts() == 1);
  macronode.sequences = new DiAnGrSimpleStorage::Sequence[1];
  macronode.numSeqs = 1;

  const char *seqName = _animations[gspSeqs[0].nID].animName.begin();
  len = strlen(seqName) + 1;
  macronode.sequences[0].sequenceName = new char[len];
  strcpy_s(macronode.sequences[0].sequenceName, len, seqName);

  macronode.sequences[0].speed    = gspSeqs[0].rSpeed;
  macronode.sequences[0].startPar = gspSeqs[0].rStartPar;
  macronode.sequences[0].stopPar  = gspSeqs[0].rStopPar;
  macronode.sequences[0].weight   = 1.0f;

  DiUInt32 nNumEdges = anpNode->GetNumNeighbours();
  if ( nNumEdges > 0 )
  {
    macronode.numTransactions = nNumEdges;
    macronode.multiTransactions = new DiAnGrSimpleStorage::MultiTransaction[macronode.numTransactions];
    class Adder : public INeiFunctor
    {
      int idx;
      DiAnimGraph* ag;
      DiAnGrSimpleStorage::MultiTransaction* multiTransactions;
      DiUInt32 nNodeID;
    public:
      Adder( DiAnimGraph* ag, DiAnGrSimpleStorage::MultiTransaction* multiTransactions, DiUInt32 nNodeID ) 
      : ag(ag), multiTransactions(multiTransactions), idx(0), nNodeID(nNodeID)
      { }
      virtual void operator()( DiUInt32 nodeId )
      {
        DiUInt32 nEdgeID = ag->GetEdgeID(nNodeID, nodeId);
        bool ok = ag->AddTransactionToStorage(nodeId, nEdgeID, multiTransactions[idx]);
        DIASSERT(ok);
        idx++;
      }
    } ad(this, macronode.multiTransactions, nNodeID);
    ForAllNeighbours( nNodeID, &ad );
  }
  else
  {
    // Node has no outgoing edges => it should be looped!
    DIASSERT(strcmp(macronode.nextNodeName, macronode.nodeName) == 0);
  }

  macronode.posX = nodesPos[nNodeID].x;
  macronode.posY = nodesPos[nNodeID].y;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DiAnimGraph::AddMacronodeToStorage(DiUInt32 nMacronodeID, DiAnGrSimpleStorage::Macronode &macronode,
                                        const NScene::AnimationVector &_animations)
{
  DiAnimNode    *anpNode;
  DiAnimMacronode *ampMacronode;
  int						len(0);

  DiAnGrSequence *gspSeqs;

  anpNode = GetNodeData(nMacronodeID);
  DIASSERT(anpNode->IsMacronode());
  ampMacronode = ((DiAnimMacronode *)anpNode);
  //anpNode->GetNumIntNodes();

  // save node name
  const char *nodeName = GetNodeNameByID(nMacronodeID);
  if ( nodeName != NULL )
  {
    len = strlen(nodeName) + 1;
    len = len > NODE_NAME_SIZE ? NODE_NAME_SIZE : len;

    macronode.nodeName = new char[len];
    strcpy_s(macronode.nodeName, len, nodeName);		
  }

  // save next node name
  const char *nextNodeName = GetNodeNameByID(ampMacronode->GetDefNextNode());
  if ( nextNodeName != NULL )
  {
    len = strlen(nextNodeName) + 1;
    len = len > NODE_NAME_SIZE ? NODE_NAME_SIZE : len;

    macronode.nextNodeName = new char[len];		
    strcpy_s(macronode.nextNodeName, len, nextNodeName);
  }

  // save speed/startPar/stopPar
  macronode.speed       = ampMacronode->GetSpeed();
  macronode.surfSpeedX  = ampMacronode->GetSurfSpeed().x;
  macronode.surfSpeedY  = ampMacronode->GetSurfSpeed().y;
  macronode.startPar    = ampMacronode->GetStartPar();
  macronode.stopPar     = ampMacronode->GetStopPar();

  // save sequence(s)
  int numIntNodes = ampMacronode->GetNumIntNodes();
  gspSeqs = anpNode->GetSequences();
  DIASSERT(GetNumParts() == 1);
  DIASSERT( numIntNodes > 1 );
  
  macronode.sequences = new DiAnGrSimpleStorage::Sequence[numIntNodes];
  macronode.numSeqs = numIntNodes;

  float checkWeight = 0.0f;
  for (int i = 0; i < numIntNodes; i++)
  {
    const char *seqName = _animations[gspSeqs[i].nID].animName.begin();
    len = strlen(seqName) + 1;
    macronode.sequences[i].sequenceName = new char[len];
    strcpy_s(macronode.sequences[i].sequenceName, len, seqName);

    macronode.sequences[i].speed    = gspSeqs[i].rSpeed;
    macronode.sequences[i].startPar = gspSeqs[i].rStartPar;
    macronode.sequences[i].stopPar  = gspSeqs[i].rStopPar;
    macronode.sequences[i].weight   = gspSeqs[i].rWeight;
    
    checkWeight += macronode.sequences[i].weight;
  }
  DIASSERT( DiFAbs(checkWeight - 1.0f) < 0.0001f );

  DiUInt32 nNumEdges = anpNode->GetNumNeighbours();
  if ( nNumEdges > 0 )
  {
    macronode.numTransactions = nNumEdges;
    macronode.multiTransactions = new DiAnGrSimpleStorage::MultiTransaction[macronode.numTransactions];
    class Adder : public INeiFunctor
    {
      int idx;
      DiAnimGraph* ag;
      DiAnGrSimpleStorage::MultiTransaction* multiTransactions;
      DiUInt32 nNodeID;
    public:
      Adder( DiAnimGraph* ag, DiAnGrSimpleStorage::MultiTransaction* multiTransactions, DiUInt32 nNodeID ) 
        : ag(ag), multiTransactions(multiTransactions), idx(0), nNodeID(nNodeID)
      { }
      virtual void operator()( DiUInt32 nodeId )
      {
        DiUInt32 nEdgeID = ag->GetEdgeID(nNodeID, nodeId);
        bool ok = ag->AddTransactionToStorage(nodeId, nEdgeID, multiTransactions[idx]);
        DIASSERT(ok);
        idx++;
      }
    } ad(this, macronode.multiTransactions, nMacronodeID);
    ForAllNeighbours( nMacronodeID, &ad );
  }
  else
  {
    // Node has no outgoing edges => it should be looped!
    DIASSERT(strcmp(macronode.nextNodeName, macronode.nodeName) == 0);
  }

  macronode.posX = nodesPos[nMacronodeID].x;
  macronode.posY = nodesPos[nMacronodeID].y;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DiBool DiAnimGraph::AddTransactionToStorage(DiUInt32 nNodeTo, DiUInt32 nEdgeID, 
                                            DiAnGrSimpleStorage::MultiTransaction &multiTrans)
{
  DiAnimFlTransaction  *atpTrans;
  DiAnimMTransaction *mtpEdge;
  DiUInt32           nJ;

  multiTrans.priority = DiAnimFlTransaction::ConvertWeightToPrior(GetEdgeWeight(nEdgeID));
  const char *nodeToName = GetNodeNameByID(nNodeTo);
  DIASSERT(nodeToName != NULL);
  int len = strlen(nodeToName) + 1;
  multiTrans.targetNodeName = new char[len];
  strcpy_s(multiTrans.targetNodeName, len, nodeToName);

  mtpEdge  = GetTransactionData(nEdgeID);
  DIASSERT(mtpEdge != NULL);
  multiTrans.probability = mtpEdge->nProbability;
  multiTrans.numTimes = mtpEdge->nNumIntervals;
  DIASSERT(multiTrans.numTimes > 0);
  multiTrans.timesAndParams = new DiAnGrSimpleStorage::Transaction[multiTrans.numTimes];

  for (nJ = 0; nJ < mtpEdge->nNumIntervals; nJ++)
  {
    DiAnGrSimpleStorage::Transaction &tr = multiTrans.timesAndParams[nJ];

    atpTrans = mtpEdge->GetSubTransaction(nJ);
    
    tr.kind               = int(atpTrans->GetKind());
    tr.speed              = atpTrans->GetSpeed();
    tr.fromMin            = atpTrans->GetMinFromPar();
    tr.fromMax            = atpTrans->GetMaxFromPar();
    tr.toParam            = atpTrans->GetToParam();
    
    tr.parA = atpTrans->GetAParam();
    tr.parB = atpTrans->GetBParam();
    
    switch(atpTrans->GetUpdateFlags())
    {
      case DIANGR_FLKIND_NONE:   tr.updateType = 0; break;
      case DIANGR_FLKIND_FIRST:  tr.updateType = 1; break;
      case DIANGR_FLKIND_SECOND: tr.updateType = 2; break;
      case DIANGR_FLKIND_BOTH:   tr.updateType = 3; break;
      default: DIASSERT_ALOOF_CODE(GetDBFileName()); tr.updateType = 0; break;
    }
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DiBool DiAnimGraph::AddMarkerToStorage(DiUInt32 markerId, DiAnGrSimpleStorage::Marker &marker) const
{
  int len(0);
  DiAnGrMarker const &markerG = mMarkers[markerId];

  // name
  if (markerG.markerName.length() > 0)
  {
    len = markerG.markerName.length() + 1;
    len = len > NODE_NAME_SIZE ? NODE_NAME_SIZE : len;

    marker.name = new char[len];
    strcpy_s(marker.name, len, markerG.markerName.c_str());		
  }
  else
  {
    marker.name = new char[10];
    strcpy_s(marker.name, 10, "INVALID!");		
  }

  
  marker.markerOwner  = int(markerG.owner); // owner type
  marker.nodeIdx      = markerG.nodeIdx; // node idx
  marker.transIdx     = markerG.transIdx; // nodeTo idx
  marker.subTransIdx  = markerG.subTransIdx;// subTransIdx
  marker.virtPar      = markerG.virtPar;// virtPar

  return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DiBool DiAnimGraph::AddExtParCoeffToStorage(DiAnGrExtPars::EditorExternalParamLink const &srcExtParCoeff, 
                                            DiAnGrSimpleStorage::ExternalParameterCoeff &extParCoeff) const
{
  int len(0);

  // name
  if (srcExtParCoeff.name.length() > 0)
  {
    len = srcExtParCoeff.name.length() + 1;
    len = len > NODE_NAME_SIZE ? NODE_NAME_SIZE : len;

    extParCoeff.paramName = new char[len];
    strcpy_s(extParCoeff.paramName, len, srcExtParCoeff.name.c_str());		
  }
  else
  {
    extParCoeff.paramName = new char[10];
    strcpy_s(extParCoeff.paramName, 10, "INVALID!");		
  }

  extParCoeff.coeff = srcExtParCoeff.coeff;
  return TRUE;
}
//////////////////////////////////////////////////////////////////////////

DiBool DiAnimGraph::AddExtParToStorage(DiAnGrExtPars::EditorExternalParam const &extParSrc, DiAnGrSimpleStorage::ExternalParameter &extPar) const
{
  int len(0);
  
  // name
  if (extParSrc.name.length() > 0)
  {
    len = extParSrc.name.length() + 1;
    len = len > NODE_NAME_SIZE ? NODE_NAME_SIZE : len;

    extPar.paramName = new char[len];
    strcpy_s(extPar.paramName, len, extParSrc.name.c_str());		
  }
  else
  {
    extPar.paramName = new char[10];
    strcpy_s(extPar.paramName, 10, "INVALID!");		
  }

  extPar.defaultValue = extParSrc.initialValue;
  return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DiBool DiAnimGraph::AddExtDepToStorage(DiAnGrExtPars::EditorDependency const &extDepSrc, DiAnGrSimpleStorage::ExternalDependency &extDep) const
{
  int len(0);

  // name
  if (extDepSrc.internalParam.paramName.length() > 0)
  {
    len = extDepSrc.internalParam.paramName.length() + 1;
    len = len > NODE_NAME_SIZE ? NODE_NAME_SIZE : len;

    extDep.paramName = new char[len];
    strcpy_s(extDep.paramName, len, extDepSrc.internalParam.paramName.c_str());		
  }
  else
  {
    extDep.paramName = new char[10];
    strcpy_s(extDep.paramName, 10, "INVALID!");		
  }

  extDep.dependencyOwner = int(extDepSrc.internalParam.type); // owner type
  extDep.nodeIdx      = extDepSrc.internalParam.nodeIdx; // node idx
  extDep.nextNode     = extDepSrc.internalParam.nextNodeIdx; // nodeTo idx
  extDep.subTransIdx  = extDepSrc.internalParam.subTransIdx;// subTransIdx
  extDep.subNodeIdx   = extDepSrc.internalParam.subNodeIdx;// virtPar

  extDep.numElemsInFormula = extDepSrc.externalParams.size();
  if (extDep.numElemsInFormula > 0)
  {
    extDep.formula = new DiAnGrSimpleStorage::ExternalParameterCoeff[extDep.numElemsInFormula];
    for (int j = 0; j < extDep.numElemsInFormula; j++)
    {
      AddExtParCoeffToStorage(extDepSrc.externalParams[j], extDep.formula[j]);
    }
  }
  

  return TRUE;
}
//////////////////////////////////////////////////////////////////////////
bool DiAnimGraph::FillSimpleStorage(DiAnGrSimpleStorage &storageToFill, 
                                    const NScene::AnimationVector &_animations,
                                    DiAnGrExtPars &extPars)
{
  storageToFill.numParts = GetNumParts();

  // write all nodes/macronodes in cycle
  storageToFill.numMacronodes = GetNumNodes();
  NI_ASSERT( storageToFill.numMacronodes > 0, "No nodes to save!" );
  storageToFill.macronodes = new DiAnGrSimpleStorage::Macronode[storageToFill.numMacronodes];
  for (int nNodeID = 0; nNodeID < storageToFill.numMacronodes; nNodeID++)
  {
    //@todo! Support macronodes!
    DiAnimNode *anpNode = GetNodeData(nNodeID);
    if (anpNode->IsMacronode())
      AddMacronodeToStorage(nNodeID, storageToFill.macronodes[nNodeID], _animations);
    else
      AddNodeToStorage(     nNodeID, storageToFill.macronodes[nNodeID], _animations);
  }

  // write all markers
  storageToFill.numMarkers = mMarkers.size();
  if (storageToFill.numMarkers > 0)
  {
    storageToFill.markers    = new DiAnGrSimpleStorage::Marker[storageToFill.numMarkers];
    for (int i = 0; i < storageToFill.numMarkers; i++)
    {
      AddMarkerToStorage(i, storageToFill.markers[i]);
    }
  }

  // write all external parameters and external dependencies
  storageToFill.numExtParams = extPars.getEditorExternalParams()->size();
  if (storageToFill.numExtParams > 0)
  {
    storageToFill.extParams    = new DiAnGrSimpleStorage::ExternalParameter[storageToFill.numExtParams];
    for (int i = 0; i < storageToFill.numExtParams; i++)
    {
      AddExtParToStorage((*(extPars.getEditorExternalParams()))[i], storageToFill.extParams[i]);
    }
  }

  storageToFill.numExtDeps   = extPars.getEditorDependencies()->size();
  if (storageToFill.numExtDeps > 0)
  {
    storageToFill.extDeps      = new DiAnGrSimpleStorage::ExternalDependency[storageToFill.numExtDeps];
    for (int i = 0; i < storageToFill.numExtDeps; i++)
    {
      AddExtDepToStorage((*(extPars.getEditorDependencies()))[i], storageToFill.extDeps[i]);
    }
  }

  return true;
}

// This function is kind of a hack - for Editor ONLY! (For View->Show Animations menu)
/*DiVoid DiAnimGraph::SetConcreteAnimSeqInCurrentLoopedNodeEDITORONLY(int seqIdx)
{
  // get current node
  DiAnimNode *npNode = GetNodeData(this->GetCurNode());

  // check that it is looped (if not - make it looped)
  if (!npNode->IsLooped())
    npNode->SetLooped(true);

  DiInt32 nNewSeqTime;
  DiAnimGetTimesBySeqIdx(cpaSceneComponents[0], seqIdx, NULL, &nNewSeqTime);
  npNode->rSpeed = 1000.0f / nNewSeqTime;

  // change sequence ID in it
  // if it's a macronode - force seq#0 to have weight 1.0
  DiAnGrSequence &seq = npNode->spSequences[0];
  seq.nID       = seqIdx;
  seq.rStartPar = 0.0f;
  seq.rStopPar  = 1.0f;
  seq.rSpeed    = 1.0f;
  seq.rWeight   = 1.0f;
}*/

DiVoid DiAnimGraph::SliderPauseAtNodeAtVParEDITORONLY(int nodeID, float virtPar)
{
  //static int c=0;
  //AGTrace("Pause %i", c++);

  // check call order
  //NI_VERIFY(!s_editorDataSave.m_pausedForPreview, "Call order failed", return; );
  if (s_editorDataSave.m_pausedForPreview)
    return;

  // find node
  DiAnimNode *anpNode = GetNodeData(nodeID);
  NI_VERIFY(anpNode != NULL, "Logic failed in names!", return; );

  // save in-out info
  s_editorDataSave.m_nodeName = GetNodeNameByID(nodeID);
  if (anpNode->IsMacronode())
  {
    // support macronodes
    DiAnimMacronode *ampMNode = (DiAnimMacronode *)anpNode;
    for (int i = 0; i < ampMNode->GetNumIntNodes(); i++)
    {
      EditorSliderData::SeqInOutData seqData;
      seqData.m_in  = anpNode->GetSequences()[i].GetStartPar();
      seqData.m_out = anpNode->GetSequences()[i].GetStopPar();

      s_editorDataSave.m_internalNodes.push_back(seqData);
      EditorSliderData::SeqInOutData& seqData1 = s_editorDataSave.m_internalNodes.back();
      seqData.m_in = seqData1.m_in;

      // set in and out to specified param
      anpNode->GetSequences()[i].SetStartPar(virtPar);
      anpNode->GetSequences()[i].SetStopPar(virtPar);
    }
  }
  else
  {
    EditorSliderData::SeqInOutData seqData;
    seqData.m_in  = anpNode->GetSequences()[0].GetStartPar();
    seqData.m_out = anpNode->GetSequences()[0].GetStopPar();

    s_editorDataSave.m_internalNodes.push_back(seqData);

    // set in and out to specified param
    anpNode->GetSequences()[0].SetStartPar(virtPar);
    anpNode->GetSequences()[0].SetStopPar(virtPar);
  }

  // Loop node if needed
  s_editorDataSave.m_wasNodeLooped = anpNode->IsLooped();
  if (!s_editorDataSave.m_wasNodeLooped)
  {
    int dummy(-1);
    s_editorDataSave.m_savedDefNextNode = anpNode->GetDefNextNode();
    anpNode->SetLooped(true, nodeID, dummy);
    //DebugTrace("Looped = true");
  }

  // Activate this node
  if (int(GetCurNodeUnsafe()) != nodeID)
  {
    Restart( nodeID, true );
  }

  // set flag "preview in editor"
  s_editorDataSave.m_pausedForPreview = true;

}

DiVoid DiAnimGraph::SliderPauseAtNodeAtVParEDITORONLY(const string &nodeName, float virtPar)
{
  SliderPauseAtNodeAtVParEDITORONLY(GetNodeIDByNameSlow(nodeName.c_str()), virtPar);
}

DiVoid DiAnimGraph::SliderContinueEDITORONLY()
{
  AGTrace("Continue");
  if ( s_editorDataSave.m_pausedForPreview )
  {  
    // restore information
    DiUInt32 nodeID = GetNodeIDByNameSlow(s_editorDataSave.m_nodeName.c_str());
    DiAnimNode *anpNode = GetNodeData(nodeID);
    NI_VERIFY(anpNode != NULL, "Logic failed in names!", return; );

    if (anpNode->IsMacronode())
    {
      // support macronodes
      DiAnimMacronode *ampMNode = (DiAnimMacronode *)anpNode;
      for (int i = 0; i < ampMNode->GetNumIntNodes(); i++)
      {
        ampMNode->GetSequences()[i].SetStartPar(s_editorDataSave.m_internalNodes[i].m_in);
        ampMNode->GetSequences()[i].SetStopPar(s_editorDataSave.m_internalNodes[i].m_out);
      }
    }
    else
    {
      anpNode->GetSequences()[0].SetStartPar(s_editorDataSave.m_internalNodes[0].m_in);
      anpNode->GetSequences()[0].SetStopPar(s_editorDataSave.m_internalNodes[0].m_out);
    }    

    // restore loop-status
    anpNode->SetLooped(s_editorDataSave.m_wasNodeLooped, nodeID, s_editorDataSave.m_savedDefNextNode);
    //DebugTrace("Looped restored");
    Restart( nodeID, true );
  }
  else
  {
    // check call order
    //NI_ASSERT(s_editorDataSave.m_pausedForPreview, "Call order failed!");
  }

  // reset flag "preview in editor"
  s_editorDataSave.Clear();
}

DiAnGrMarker *DiAnimGraph::FindMarkerByNameInNode(const string &markerName, int nodeIdx)
{
  for (int i = 0; i < mMarkers.size(); i++)
    if (markerName == mMarkers[i].markerName && mMarkers[i].nodeIdx == nodeIdx)
      return &mMarkers[i];

  return NULL;
}

DiAnGrMarker *DiAnimGraph::FindMarkerByNameInCurNode(const string &markerName)
{
  NI_ASSERT(GetCurElemType() == DIANGR_NODE, "FindMarkerByNameInCurNode called not in node");

  return FindMarkerByNameInNode(markerName, GetCurNode());
}

DiAnGrMarker *DiAnimGraph::FindMarkerByNameInNextNodeAfterTrans(const string &markerName)
{
  if (GetCurElemType() == DIANGR_FLTRANSACTION)
    return FindMarkerByNameInNode(markerName, GetNextNode());
  
  AGTrace("FindMarkerByNameInNextNodeAfterTrans: Not in transaction now!");
  return NULL;
}


DiAnGrMarker *DiAnimGraph::FindMarkerByName(const string &markerName, int *idxToStartSearch, int *foundMarkerIdx)
{
  // Non-optimal code.
  // While number of markers is 1-5 it is ok, if more - this code should be optimized
  NI_ASSERT( mMarkers.size() < 15, "Such number of markers needs better code!" );

  int startIdx(0);
  if (idxToStartSearch != NULL)
    startIdx = *idxToStartSearch;

  for (int i = startIdx; i < mMarkers.size(); i++)
    if (markerName == mMarkers[i].markerName)
    {
      if (foundMarkerIdx != NULL)
        *foundMarkerIdx = i;
      return &mMarkers[i];
    }

  if (foundMarkerIdx != NULL)
    *foundMarkerIdx = -1;  
  return NULL;
}

DiAnGrMarker* DiAnimGraph::GetRandomNodeMarker( DiAnGrMarker* marker )
{
  DiAnGrMarker* res = 0;

  if ( marker->nodeIdx < 0 || (DiUInt32)marker->nodeIdx >= GetNumNodes() )
    return marker;

  DiAnimNode* node = GetNodeData( marker->nodeIdx );
  if ( !node->IsSubNode() )
    return marker;

  DiUInt32 randomNode = SelectNextNodeByProbability( node->GetDispatcherNodeID(), GetNodeData(node->GetDispatcherNodeID()) );
  res = FindMarkerByNameInNode( marker->markerName, randomNode );
  if ( res == 0 )
    return marker;
  
  return res;
}

// this function should be used for switcher-nodes only. It will work for all nodes but it's not good to search markers
// in all neighbours in any cases!
bool DiAnimGraph::IsNodeMarkerNearSwitcher(int nodeSwitcherIdx, int markerNode)
{
  DIASSERT(GetNodeData(nodeSwitcherIdx)->IsSwitcher());

  class Probe : public INeiFunctor
  {
    DiBool res;
    DiUInt32 markerNode;
  public:
    Probe( DiUInt32 markerNode ) 
    : markerNode(markerNode), res(false)
    {}
    virtual void operator()( DiUInt32 nodeId )
    {
      if (nodeId == markerNode)
      {
        res = true;
      }
    }
    DiBool GetRes() const { return res; }
  } p(markerNode);

  ForAllNeighbours(nodeSwitcherIdx, &p);
  return p.GetRes();
}

bool DiAnimGraph::IsNodeMarkerNear(const DiAnGrMarker &marker)
{
  DIASSERT(EditorGraphParamAddress::VT_NODE == marker.owner);

  // get current graph element
  DiAnimGraphElems geElem = GetCurElemType();

  // analyze graph state
  if (DIANGR_NODE == geElem || DIANGR_MACRONODE == geElem )
  {
    DiUInt32 edgeID = GetEdgeID(nCurNode, marker.nodeIdx);
    if (edgeID != diGR_NO_SUCH_ELEMENT || int(nCurNode) == marker.nodeIdx)
      return true;

    // check switcher-case (like attack1-attack-attack2 or idle1-idle-idle2). We don't support non-switcher case: do not search all neighbours!
    DiAnimNode *anpNode = GetNodeData(nCurNode);
    if (!anpNode->IsLooped())
    {
      // use default next node
      int nDefNextNode = anpNode->GetDefNextNode();
      anpNode = GetNodeData(nDefNextNode);
      if (anpNode->IsSwitcher())
        return IsNodeMarkerNearSwitcher(nDefNextNode, marker.nodeIdx);        
    }
    return false;
  }
  else if (DIANGR_FLTRANSACTION == geElem)
  {
    if (nNextNode == DiUInt32(marker.nodeIdx))
      return true;

    // check switcher-case (like attack1-attack-attack2 or idle1-idle-idle2). We don't support non-switcher case: do not search all neighbours!
    if (GetNodeData(nNextNode)->IsSwitcher())
      return IsNodeMarkerNearSwitcher(nNextNode, marker.nodeIdx);
    else
      return false;
  }

  DIASSERT_ALOOF_CODE(GetDBFileName()); // unknown state
  return false;
}

bool DiAnimGraph::IsTransactionMarkerNear(const DiAnGrMarker &marker)
{
  DIASSERT(EditorGraphParamAddress::VT_TRANSACTION == marker.owner);

  // get current graph element
  DiAnimGraphElems geElem = GetCurElemType();

  // analyze graph state
  if (DIANGR_NODE == geElem || DIANGR_MACRONODE == geElem )
  {
    return (int(nCurNode) == marker.nodeIdx);
  }
  else if (DIANGR_FLTRANSACTION == geElem)
  {
    return (int(nCurTrans) == marker.transIdx && int(nCurSubTrans) == marker.subTransIdx);
  }

  DIASSERT_ALOOF_CODE(GetDBFileName()); // unknown state
  return false;
}

int DiAnimGraph::CalculateTimeFromNodeToNodeInMS(int nodeFrom, float nodeFromPar, int nodeTo, float nodeToPar, bool isInNode, 
                                                 vector<PathChange> &changesInPath, PathSetupInfo &pathInfo)
{
  AGTrace("Calculating time from node %i(%s),%5.3lf to %i(%s),%5.3lf", nodeFrom, GetNodeNameByID(nodeFrom), nodeFromPar, nodeTo, GetNodeNameByID(nodeTo), nodeToPar);

  // 1. build path
  DiUInt32 pathLen;
  const DiUInt32 maxPathLen(DIANGR_MAX_MARKER_PATH_LENGTH);
  DiUInt32 path[maxPathLen];

  if (nodeFrom != nodeTo)
  {
    AGTrace("if#1");
    bool ok = FindShortestWay(nodeFrom, nodeTo, pathLen, GetDBFileName());
    if (!ok)
      return -1;
    
    DIASSERT(pathLen < maxPathLen);
    
    ok = GetNodesOfShortestPath(path);
    if (!ok)
      return -1;
  }
  else if (nodeFrom == nodeTo && !GetNodeData(nodeFrom)->IsLooped() && nodeFromPar > nodeToPar)
  {
    AGTrace("if#2");
    path[0] = nodeFrom;
    pathLen = 1;
  }
  else
  {
    AGTrace("if#3");
    pathLen = 1;
    path[0] = nodeFrom;
  }

  AGTrace("Path after FindShortestWay: Length:%i, path(first six):%i[%s]-%i[%s]-%i[%s]-%i[%s]-%i[%s]-%i[%s]-%i[%s]", 
    pathLen, path[0], GetNodeNameByID(path[0]), path[1], GetNodeNameByID(path[1]), path[2], GetNodeNameByID(path[2]), 
      path[3], GetNodeNameByID(path[3]), path[4], GetNodeNameByID(path[4]), path[5], GetNodeNameByID(path[5]), path[6], GetNodeNameByID(path[6]));

  // Check path: perhaps there is a switcher node on the path and we should use SelectByProbability() function
  // NB: check all elements in path WITHOUT last one
//   changesInPath.clear();
//   for (int i = 0; i < (int)pathLen - 1; i++)
//   {
//     DiAnimNode *node = GetNodeData(path[i]);
//     NI_VERIFY(node != NULL, "wrong idx", continue;);
//     if (node->IsSwitcher())
//     {
//       NI_VERIFY(i <= (int)pathLen - 2, "Logic error", continue;);
//       DiUInt32 nextNodeIdx = SelectNextNodeByProbability(path[i], node);
//       if (nextNodeIdx != path[i+1])
//       {
//         changesInPath.push_back(PathChange(path[i + 1], nextNodeIdx));
//         AGTrace("Changing element in path from %i[%s]to %i[%s]", path[i+1], GetNodeNameByID(path[i+1]), nextNodeIdx, GetNodeNameByID(nextNodeIdx));
//         path[i + 1] = nextNodeIdx;
//       }
//     }
//   }

  // 2. calculate time of all parts along the path
  float activeNodePar = nodeFromPar;
  int totalTime = 0;
  for (int i = 0; i < (int)pathLen - 1; i++)
  {
    // check transaction
    DiUInt32 edgeID = GetEdgeID(path[i], path[i + 1]);
    NI_VERIFY(edgeID != -1, "logic failed!", return -1);

    DiAnimMTransaction *mtrans = GetTransactionData(edgeID);
    DiFloat deltaBeforeTrans = 0.0f;
    DiUInt32 subTransID = mtrans->GetTransactionNearestToPar(activeNodePar, deltaBeforeTrans);
    DiAnimFlTransaction *trans = GetTransactionData(edgeID, subTransID, path[i], path[i+1]);
    NI_VERIFY(trans != NULL, "logic failed!", return -1);

    // time in node before transaction
    totalTime += int((deltaBeforeTrans / GetNodeData(path[i])->GetSpeed()) * 1000.0f);

    // time in transaction
    if ( trans->GetUpdateFlags() == DIANGR_FLKIND_NONE )
      totalTime += int(1.0f / trans->GetSpeed() * 1000.f);    

    activeNodePar = trans->GetToParam();
  }

  // time in node from last transaction till needed parameter
  DiAnimNode *lastNode = GetNodeData(path[pathLen - 1]);
  DIASSERT(lastNode != NULL);
  if (activeNodePar <= nodeToPar)
  {
    AGTrace("#if4");
    totalTime += int((nodeToPar - activeNodePar) / lastNode->GetSpeed() * 1000.f);
  }
  else
  {
    AGTrace("#if5");
    //DIASSERT(lastNode->IsLooped());
    float tempTime = (1.0f - activeNodePar) + nodeToPar;
    totalTime += int(tempTime / lastNode->GetSpeed() * 1000.f);
  }

  // build path for AnimGraph: prepare setup-info
  pathInfo.Clear();
  pathInfo.SetGraph(this);
  if (isInNode && pathLen == 2)
  {
    AGTrace("#if6");
    pathInfo.SetByNextNode(path[1]);
  }
  else if (!isInNode && pathLen == 1)
  {
    AGTrace("#if7");
    pathInfo.SetByNextNode(path[0]);
  }
  else if ( pathLen == 1 && lastNode->IsLooped() )
  {
    // nothing to do - we are at this node
    AGTrace("#if8");
    pathInfo.SetNothingToDo();
  }
  else if ( pathLen == 1 && !lastNode->IsLooped() )
  {
    SetNextNode(path[0]);
    bIsForced = true;
  }
  else
  {
    NI_ASSERT(pathLen > 1, "");

    pathInfo.SetByPath(path, pathLen, !isInNode);

    AGTrace("Set new path. Length:%i, path(first four):%i-%i-%i-%i. NextNode=%i[%s]", 
            pathInfo.nGPPathLength, pathInfo.npGPPath[0], pathInfo.npGPPath[1], pathInfo.npGPPath[2], pathInfo.npGPPath[3], pathInfo.nNextNode, GetNodeNameByID(pathInfo.nNextNode));
  }

  return totalTime;
}

void DiAnimGraph::CalculateTimeToNodeMarker(const DiAnGrMarker &marker, vector<PathToMarker> &pathsToMarker)
{
  int totalTime = 0;
  vector<PathChange> changesInPath;
  PathSetupInfo      pathSetupInfo;

  DIASSERT(marker.owner == EditorGraphParamAddress::VT_NODE);

  // analyze graph state
  DiAnimGraphElems geElem = GetCurElemType();
  if (DIANGR_NODE == geElem || DIANGR_MACRONODE == geElem )
  {
    DiAnimNode *anpNodeCur = GetNodeData(nCurNode);
    DIASSERT(anpNodeCur != NULL);

    totalTime += CalculateTimeFromNodeToNodeInMS(nCurNode, anpNodeCur->GetVPar(), marker.nodeIdx, marker.virtPar, true, changesInPath, pathSetupInfo);
  }
  else if (DIANGR_FLTRANSACTION == geElem)
  {
    DiAnimFlTransaction *trans = GetTransactionData(nCurTrans, nCurSubTrans);
    DIASSERT(trans != NULL);

    // 1. time in transaction
    if ( trans->GetUpdateFlags() == DIANGR_FLKIND_NONE )
      totalTime += int((1.0f - rCurParInTransaction) / trans->GetSpeed() * 1000.f);

    // 2. time after first transaction
    totalTime += CalculateTimeFromNodeToNodeInMS(nNextNode, trans->GetToParam(), marker.nodeIdx, marker.virtPar, false, changesInPath, pathSetupInfo);
  }

  for ( unsigned int i = 0; i < pathSetupInfo.nGPPathLength; i++ )
  {
    if ( pathSetupInfo.npGPPath[i] < GetNumNodes() && GetNodeData( pathSetupInfo.npGPPath[i] )->bIsSwitcher )
    {
      for ( int k = i; k < DIANGR_MAX_MARKER_PATH_LENGTH-1; k++ )
      {
        pathSetupInfo.npGPPath[k] = pathSetupInfo.npGPPath[k+1];
      }
      pathSetupInfo.nGPPathLength--;
      i--;
    }
  }


  // add built path to all paths
  PathToMarker pathToMarker;

  pathToMarker.mMarker    = marker;
  pathToMarker.nTimeInMS  = totalTime;
  pathToMarker.pathInfo   = pathSetupInfo;

  // Check changes: perhaps index of node with marker has changed
  NI_ASSERT(changesInPath.size() <= 2, "Strange behaviour! Check logic"); //very strange that there were more than 2 dispatcher nodes on the path (common case: idle and attack)
  for (int i = 0; i < changesInPath.size(); i++)
  {
    if (changesInPath[i].prevNodeIdxInPath == marker.nodeIdx)
    {
      AGTrace("ATTENTION: changing index of node with target marker from %i [%s] to %i [%s]", marker.nodeIdx, GetNodeNameByID(marker.nodeIdx), changesInPath[i].newNodeIdxInPath, GetNodeNameByID(changesInPath[i].newNodeIdxInPath));
      pathToMarker.mMarker.nodeIdx = changesInPath[i].newNodeIdxInPath;
      break;
    }
  }
  AddPathIfUnique(pathToMarker, pathsToMarker);

  // if there are changes in path - add other path with big-big time. This path is needed to prevent duplication of paths while searching for all markers
  for (int i = 0; i < changesInPath.size(); i++)
  {
    for (int j = 1; j < int(pathToMarker.pathInfo.nGPPathLength); j++)
    {
      if (changesInPath[i].newNodeIdxInPath == int(pathToMarker.pathInfo.npGPPath[j]))
      {
        pathToMarker.pathInfo.ChangeElemInPath(j, changesInPath[i].prevNodeIdxInPath);
        pathToMarker.nTimeInMS = DIANGR_BIG_INT;
        AddPathIfUnique(pathToMarker, pathsToMarker);
        break; // one difference -> one more path
      }
    }
  }

}

// Transaction markers are not fully supported now. If functionality is not enough - consider using CalculateTimeFromNodeToNodeInMS()
int DiAnimGraph::CalculateTimeToTransactionMarker(const DiAnGrMarker &marker)
{
  int totalTime = 0;

  DIASSERT(marker.owner == EditorGraphParamAddress::VT_TRANSACTION);

  // get current graph element
  DiAnimGraphElems geElem = GetCurElemType();

  DiAnimFlTransaction *trans = GetTransactionData(marker.transIdx, marker.subTransIdx);
  if (NULL == trans)
  {
    DIASSERT_ALOOF_CODE(GetDBFileName()); // wrong marker parameters!
    return s_invalidTime;
  }

  // analyze graph state
  if (DIANGR_NODE == geElem || DIANGR_MACRONODE == geElem )
  {
    DIASSERT(int(nCurNode) == marker.nodeIdx);
    DiAnimNode *anpNodeCur = GetNodeData(nCurNode);
    DIASSERT(anpNodeCur != NULL);

    // 1. time in node before transaction
    DiFloat deltaBeforeTrans = 0.0f;
    DiAnimFlTransaction *trans = GetTransactionData(marker.transIdx, marker.subTransIdx);
    DIASSERT(trans != NULL);
    
    DiFloat min = trans->GetMinFromPar();
    DiFloat max = trans->GetMaxFromPar();
    DiFloat curVP = anpNodeCur->GetVPar();
    if (curVP < min)
      deltaBeforeTrans = min - curVP;
    else if (min <= curVP && curVP <= max)
      deltaBeforeTrans = 0.0f;
    else
    {
      if (!anpNodeCur->IsLooped())
        return s_invalidTime;
      deltaBeforeTrans = 1.0f - curVP + min;
    }

    totalTime += int((deltaBeforeTrans / anpNodeCur->GetSpeed()) * 1000.0f);

    // 2. time in transaction from start till marker
    if ( trans->GetUpdateFlags() == DIANGR_FLKIND_NONE )
      totalTime += int((marker.virtPar / trans->GetSpeed()) * 1000.f);
  }
  else if (DIANGR_FLTRANSACTION == geElem)
  {
    // Here everything is very strong: either it is needed transaction or not
    if (int(nCurTrans) != marker.transIdx || int(nCurSubTrans) != marker.subTransIdx)
    {
      DIASSERT_ALOOF_CODE(GetDBFileName());
      return s_invalidTime;
    }

    if (rCurParInTransaction > marker.virtPar)
      return s_invalidTime;

    if ( trans->GetUpdateFlags() == DIANGR_FLKIND_NONE )
      totalTime += int(((marker.virtPar - rCurParInTransaction) / trans->GetSpeed()) * 1000.0f);
  }

  return totalTime;
}


// Markers & events support. Return true if marker is reachable, false - otherwise
bool DiAnimGraph::GetTimeTillNearestMarkerInMS(string markerName, int &time, DiAnGrMarker &markerToFill, bool preferShortestPath, int requestedTime, bool preferDefaultNextNode)
{
  // search nearest marker
  vector<PathToMarker> pathsToMarker;
  pathsToMarker.reserve(GetNumMarkers());

  time = s_invalidTime; // set invalid value

  // 1. get marker address
  DiAnGrMarker *marker(NULL);
  //if (GetCurElemType() == DIANGR_NODE && GetNodeData( GetCurNode() )->IsLooped() )
  //  marker = FindMarkerByNameInCurNode(markerName);
  //else
  // Try to find marker in nearest node (after transaction). Do not try to check current node - it's not correct.
  marker = FindMarkerByNameInNextNodeAfterTrans(markerName);

  if ( marker == NULL )
  {
    if ( GetCurNodeUnsafe() != GetNextNode() )
      marker = FindMarkerByNameInNode( markerName, GetNextNode() );
    if ( marker == NULL && GetCurElemType() == DIANGR_NODE )
    {
      marker = FindMarkerByNameInCurNode(markerName);
      if ( marker )
      {
        CalculateTimeToNodeMarker(*marker, pathsToMarker);
        markerToFill = pathsToMarker[0].mMarker;
        time         = pathsToMarker[0].nTimeInMS;
        NI_VERIFY(time >= 0, "Failed logic in calculating time till markers", return false;);

        return true;
      } 
    }
  }
  
  if (marker != NULL)
    AGTrace("Found marker in cur node or in node after transaction!");
  else
    AGTrace("No marker in current node or in node after transaction!");

  int bestPathIndex  = -1;
  if (!marker)
  {
    // 1. get marker address
    bool markerExists = false;
    int  startIdx(0), foundIdx(-1);
    while (true)
    {
      DiAnGrMarker *marker = FindMarkerByName(markerName, &startIdx, &foundIdx);
      markerExists = markerExists || (marker != NULL);
      if (NULL == marker)
        break;

      // process path to the node/transaction and sum times at all path's parts
      if (marker->owner == EditorGraphParamAddress::VT_NODE)
      {
        marker = GetRandomNodeMarker( marker );
        CalculateTimeToNodeMarker(*marker, pathsToMarker);
        
        AGTrace("Calculated time till node marker %s: %i ms (marker data: node %i(%s), VP=%5.3lf", 
          markerName.c_str(), time, marker->nodeIdx, GetNodeNameByID(marker->nodeIdx), marker->virtPar);
      }
      else if (markerToFill.owner == EditorGraphParamAddress::VT_TRANSACTION)
      {
        NI_ALWAYS_ASSERT("This mode needs tests after numerous refactorings of markers in nodes!"); // EugBel 2009/10/06
        CalculateTimeToTransactionMarker(*marker);
        AGTrace("Calculated time till transaction marker %s: %i ms (marker data: transaction %i(%s), VP=%5.3lf", 
          markerName.c_str(), time, marker->transIdx, GetNodeNameByID(marker->transIdx), marker->virtPar);
      }

      startIdx = foundIdx + 1;
    } // end of searching all markers and calculating reach-times for them
   
    if (!markerExists)
      return false;

    // compare times and select smallest
    int minTime        = DIANGR_BIG_INT; 
    int minSpareTime   = DIANGR_BIG_INT;
    int bestSparePath  = -1;

    for(int i = 0; i < pathsToMarker.size(); i++)
    { 
      PathSetupInfo const& path    = pathsToMarker[i].pathInfo;

      const unsigned startIdx      = path.IsEmpty() ? 0 : (unsigned)(DIANGR_NO_SUCH_ELEMENT == path.npGPPath[0]);
      const bool isDefaultNextNode = startIdx + 1 < path.nGPPathLength && path.npGPPath[startIdx + 1] == GetNodeData(path.npGPPath[startIdx])->GetDefNextNode(); 
      const bool isMainPath        = isDefaultNextNode || false == preferDefaultNextNode;  
      
      if( g_bEnablePathLogging )
      {
        string sPath = NStr::StrFmt("Path No: %i, ", i);
        const DiUInt32 count = path.nGPPathLength;
        if(0 <  count)
        {
          for( unsigned j = 0; j < count ; ++j)
          {
            if( 0 < j)
              sPath += " -> ";

            char const* sNodeName = GetNodeNameByID(path.npGPPath[j]);
            sPath += sNodeName ? sNodeName : "[invalid]";
          }
        }
        else
        {
          char const* sNodeName = GetNodeNameByID(path.nNextNode);
          sPath += " -> ";
          sPath += sNodeName ? sNodeName : "[invalid]";
        }

        sPath += NStr::StrFmt("; length = %i, isDefaultNextNode = %i, preferDefaultNextNode = %i", pathsToMarker[i].nTimeInMS, isDefaultNextNode, preferDefaultNextNode);

        systemLog( NLogg::LEVEL_DEBUG ) << endl << "Graph:" << this << ", " << sPath << endl;
      }

      
      // check main path
      if( isMainPath)
      {
        if( preferShortestPath)
        {
          if (pathsToMarker[i].nTimeInMS < minTime)
          {
            bestPathIndex = i;
            minTime       = pathsToMarker[i].nTimeInMS;
          }
        }
        else
        {
          const int dt = abs(pathsToMarker[i].nTimeInMS - requestedTime);
          if( dt < minTime )
          {
            bestPathIndex = i;
            minTime       = dt;
          }
        }
      }
      
      // check spare path
      if( preferShortestPath)
      {
        if (pathsToMarker[i].nTimeInMS < minSpareTime)
        {
          bestSparePath = i;
          minSpareTime  = pathsToMarker[i].nTimeInMS;
        }
      }
      else
      {
        const int dt = abs(pathsToMarker[i].nTimeInMS - requestedTime);
        if( dt < minSpareTime )
        {
          bestSparePath = i;
          minSpareTime  = dt;
        }
      }
    }
    NI_VERIFY(minSpareTime < DIANGR_BIG_INT, "Marker exists but with wrong time", return false;);

    if( g_bEnablePathLogging )
    {
      systemLog( NLogg::LEVEL_DEBUG ) << endl << "Graph:" << this << ", best path:" << bestPathIndex << ", best spare path:" << bestSparePath << endl;
    }

    bestPathIndex = bestPathIndex < 0 ? bestSparePath : bestPathIndex;
  }
  else // if already found marker - do not use search! Use found marker. 
  {
      NI_ASSERT(marker != NULL, "Invalid marker");

      // process path to the node/transaction and sum times at all path's parts
      if (marker->owner == EditorGraphParamAddress::VT_NODE)
      {
        CalculateTimeToNodeMarker(*marker, pathsToMarker);

        AGTrace("Calculated time till node marker %s: %i ms (marker data: node %i(%s), VP=%5.3lf", 
          markerName.c_str(), time, marker->nodeIdx, GetNodeNameByID(marker->nodeIdx), marker->virtPar);
      }
      else if (markerToFill.owner == EditorGraphParamAddress::VT_TRANSACTION)
      {
        NI_ALWAYS_ASSERT("This mode needs tests after numerous refactorings of markers in nodes!"); // EugBel 2009/10/06
        CalculateTimeToTransactionMarker(*marker);
        AGTrace("Calculated time till transaction marker %s: %i ms (marker data: transaction %i(%s), VP=%5.3lf", 
          markerName.c_str(), time, marker->transIdx, GetNodeNameByID(marker->transIdx), marker->virtPar);
      }

      bestPathIndex = 0;
  }

  const PathToMarker &bestPath = pathsToMarker[bestPathIndex];
  NI_ASSERT(bestPathIndex < pathsToMarker.size(), "Wrong best-path index");

  if (!bestPath.pathInfo.IsEmpty())
  {
    NI_ASSERT(bestPath.mMarker.transIdx != -1 || bestPath.pathInfo.IsTarget(bestPath.mMarker.nodeIdx), "Logic failed with targets");
    ApplyPath(pathsToMarker[bestPathIndex].pathInfo);
  }
  
  markerToFill = pathsToMarker[bestPathIndex].mMarker;
  time         = pathsToMarker[bestPathIndex].nTimeInMS;
  if ( time < 0 )
  {
    NI_ALWAYS_ASSERT( NStr::StrFmt( "Failed logic in calculating time %d till marker %s, path index %d, nearest node %s", 
      time, markerName.c_str(), bestPathIndex, GetNodeNameByID(GetNearestNode())) );
    return false;
  }

  return true;
}

DiInt32 _resetGraphSpeedCallback(DiAnGrCallbackParams const &cpParams)
{
  Strong<SpeedUserData> userData = (SpeedUserData *)cpParams.vpUserData;
  NI_VERIFY(userData != NULL, "Resetting NULL callback", DIRETURN(DIOBJMSG_CONTINUE););
  DIASSERT(userData->animGraph != NULL);
  //DIASSERT(userData->prevGraphSpeed != 0.0f); // Commented by EugBel because sometimes graph in game has zero speed
  userData->animGraph->SetGraphSpeedCoeff(userData->prevGraphSpeed);

  userData->animGraph->UnregisterCallback(userData->elemType, userData->elemID, _resetGraphSpeedCallback, (SpeedUserData *)userData);
  userData->animGraph->markersData.safeRemove(userData);

  DIRETURN(DIOBJMSG_CONTINUE);
} // end of _resetGraphSpeedCallback

void DiAnimGraph::UnregisterReachMarkerCallback(DiAnimGraphElems elemType, DiUInt32 elemID)
{
  //if (s_speedResetUserData != NULL)
  //{
    //UnregisterCallback(s_speedResetUserData->elemType, s_speedResetUserData->elemID, _resetGraphSpeedCallback);
    //delete s_speedResetUserData;
    //s_speedResetUserData = NULL;
  //}
}

void DiAnimGraph::RegisterReachMarkerCallback(const DiAnGrMarker &marker)
{
  // get type of the element 
  DiAnimGraphElems elType(DIANGR_NA);
  DiUInt32         elID(DIANGR_NO_SUCH_ELEMENT);
  if (marker.owner == EditorGraphParamAddress::VT_NODE)
  {
    DiAnimNode* node = GetNodeData(marker.nodeIdx);
    if ( node->IsSubNode() )
    {
      DiUInt32 dispatcherID = node->GetDispatcherNodeID();

      class Registrator : public INeiFunctor
      {
        DiAnimGraph* ag;
        DiUInt32 dispatcherID;
        SpeedUserData::Ring& markersData;
        const DiAnGrMarker &marker;
      public:
        Registrator( DiAnimGraph* ag, DiUInt32 dispatcherID, SpeedUserData::Ring& markersData, const DiAnGrMarker &marker ) 
        : ag(ag), dispatcherID(dispatcherID), markersData(markersData), marker(marker)
        {}
        Registrator& operator=(const Registrator&) { return *this; }
        virtual void operator()( DiUInt32 nodeId )
        {
          DiAnimNode* node = ag->GetNodeData(nodeId);
          if ( node->IsSubNode() && node->GetDispatcherNodeID() == dispatcherID )
          {
            DiAnimGraphElems elType(DIANGR_NA);
            DiUInt32         elID(DIANGR_NO_SUCH_ELEMENT);

            elID   = nodeId;
            elType = ag->GetNodeData(elID)->IsMacronode() ? DIANGR_MACRONODE : DIANGR_NODE;
            Strong<SpeedUserData> pSpeedData = new SpeedUserData(elType, elID, ag, ag->GetGraphSpeedCoeff());
            markersData.addLast(pSpeedData);

            DiAnGrMarker tempmarker = marker;
            tempmarker.nodeIdx = elID;

            ag->RegisterCallback(tempmarker, _resetGraphSpeedCallback, pSpeedData);
          }
        }
      } r(this, dispatcherID, markersData, marker);

      ForAllNeighbours(dispatcherID, &r);
    }
    else
    {
      elID   = marker.nodeIdx;
      elType = GetNodeData(elID)->IsMacronode() ? DIANGR_MACRONODE : DIANGR_NODE;
      Strong<SpeedUserData> pSpeedData = new SpeedUserData(elType, elID, this, GetGraphSpeedCoeff());
      markersData.addLast(pSpeedData);
      RegisterCallback(marker, _resetGraphSpeedCallback, pSpeedData);
    }
  }
  else if (marker.owner == EditorGraphParamAddress::VT_TRANSACTION)
  {
    elID   = marker.transIdx;
    elType = DIANGR_FLTRANSACTION;
    Strong<SpeedUserData> pSpeedData = new SpeedUserData(elType, elID, this, GetGraphSpeedCoeff());
    markersData.addLast(pSpeedData);
    RegisterCallback(marker, _resetGraphSpeedCallback, pSpeedData);
  }
  else
  {
    DIASSERT_ALOOF_CODE(GetDBFileName());
    return;
  }
}

// Markers & events support. Return bool if marker is reachable, false - otherwise
bool DiAnimGraph::ReachMarkerByTime(const string &markerName, int time, bool preferShortestPath, bool preferDefaultNextNode)
{
  AGTrace("=================ReachMarkerByTime(marker=%s, time=%i)", markerName.c_str(), time); 

  if ( freezed )
    DIRETURN(TRUE);

  float additionalTime = 0.0f;
  if ( IsInTransactionOrFLTransaction() )
  {
    DiAnimFlTransaction *trans = GetTransactionData(nCurTrans, nCurSubTrans);
    additionalTime = trans->GetSpeed() < EPS_VALUE ? 0.0f : 1.0f / trans->GetSpeed();
    additionalTime *= (1.0f-trans->GetPrevPar()) * 1000.0f;
  }

  //if ( GetDBFileName().find("/Witch/") != nstl::string::npos )
  //{
  //  if ( GetCurNodeUnsafe() < GetNumNodes() )
  //  {
  //   DiAnimNode* node = GetNodeData( GetCurNode() );
  //   DebugTrace( "CurNode: %s %f\n", GetNodeNameByID( GetCurNode() ), node->GetVPar() );
  //  }
		//DebugTrace( "ReachMarkerByTime: %f %s %d \n", NHPTimer::GetScalarTime(), markerName.c_str(), time );
  //}

  DIASSERT(time > 0);

  int defaultTime(0);
  DiAnGrMarker markerToFill;
  bool ok = GetTimeTillNearestMarkerInMS(markerName, defaultTime, markerToFill, preferShortestPath, time, preferDefaultNextNode);
  if ( additionalTime != 0.0f && GetNextNode() != (unsigned)markerToFill.nodeIdx )
    defaultTime += additionalTime;
                                       
  if (!ok)
  {
    AGTrace("=================AG_REACH_MARKER FAILED (marker=%s, time=%i, usualTime=%i) (nodeID=%i(%s),nodePar=%5.3lf,trID=%i,trPar=%5.3lf,nextNodeID=%i)", 
      markerName.begin(), time, defaultTime, nCurNode, (GetCurElemType() != DIANGR_FLTRANSACTION ? GetNodeNameByID(nCurNode) : ""), nCurTrans, GetCurLinTransactionPar(), nNextNode);
    return false;
  }

  if (0 == defaultTime)
  {
    AGTrace("We ARE at marker position (or <1 ms is left till marker) and so we can't go to it (i.e. execute ReachMarkerByTime). Returning false from ReachMarkerByTime. "
		    "AG state: curNode=%i(%s),Vp_of_trans=%5.3lf,neededMarker=%s,foundMarkerVP=%5.3lf,foundMarkerNode=%i(%s)",
            GetCurNodeUnsafe(), GetNodeNameByID(GetCurNodeUnsafe()), GetCurLinTransactionPar(), markerName.c_str(), markerToFill.virtPar, markerToFill.nodeIdx, GetNodeNameByID(markerToFill.nodeIdx));
    return false;
  }

  //DIASSERT(defaultTime >= 0);

  AGTrace("=================AG_REACH_MARKER (marker=%s, time=%i, usualTime=%i) (nodeID=%i(%s),nodePar=%5.3lf,trID=%i,trPar=%5.3lf,nextNodeID=%i)", 
    markerName.begin(), time, defaultTime, nCurNode, (GetCurElemType() != DIANGR_FLTRANSACTION ? GetNodeNameByID(nCurNode) : ""), nCurTrans, GetCurLinTransactionPar(), nNextNode);

  // add callback on that marker - to reset graph's speed back when marker is reached
  ResetSpeedAndUnregCallbackAfterReachMarker(true);
  RegisterReachMarkerCallback(markerToFill);

  // set graph's speed to match the required time (AFTER registering reset-callback!)
  NI_ASSERT(float(defaultTime) / float(time) > 0.0f, "Wrong reach-marker behaviour!");
  SetGraphSpeedCoeff(float(defaultTime) / float(time));

  AGTrace("=================AG_REACH_MARKER END OF FUNC (marker=%s)", markerName.begin());

  return true;
}

const SVector& DiAnimGraph::GetNodePosInEditor( int nodeIdx ) const
{
  DIASSERT( 0 <= nodeIdx && nodeIdx < nodesPos.size() );
  return nodesPos[nodeIdx];
}

DiVec2 DiAnimGraph::GetNodeSurfSpeed(int nodeIdx) const
{
  if (nodeIdx < 0 || nodeIdx >= int(GetNumNodes()) )
  {
    DIASSERT_ALOOF_CODE(GetDBFileName());
    return DiVec2(MAX_FLOAT, MAX_FLOAT);
  }

  const DiAnimNode *anpNode = GetNodeData(nodeIdx);
  DIASSERT(anpNode != NULL);

  return anpNode->GetSurfSpeed();
}

void DiAnimGraph::SetNodePosInEditor( int nodeIdx, SVector newPos )
{
  DIASSERT( 0 <= nodeIdx && nodeIdx < nodesPos.size() );
  nodesPos[ nodeIdx ] = newPos;
}

NScene::IAnimGraphBlender **DiAnimGraph::GetComponents(DiVoid) 
{ 
  return cpaSceneComponents; 
}
NScene::IAnimGraphBlender *DiAnimGraph::GetComponent(DiInt32 nPartIdx) 
{ 
  NI_ASSERT( nPartIdx == 0, "Don't support multi-part characters now" );
  return cpaSceneComponents[nPartIdx]; 
}

DiAnGrClbStorageElem  *DiAnimGraph::GetClbStorage() 
{ 
  return sepClbStorage; 
}

DiBool DiAnGrLoadCallback::SaveNodesNames()
{
  NI_ALWAYS_ASSERT("Do not call this function - use nmpaTableRuntime and GetNodeNameByID at any time");
  return FALSE;
}

void DiAnimGraph::SetGraphSpeedCoeff(DiFloat newSpeed)
{
  //DIASSERT(newSpeed != 0.0f); // not good idea to stop graph in such way! Ask EugBel
  if (fabs(newSpeed - GetGraphSpeedCoeff()) > 0.0001f)
  {
    AGTrace("New graph speed coeff: %6.3lf (was: %6.3lf)", newSpeed, GetGraphSpeedCoeff());
  }
  rGraphSpeedCoeff = newSpeed;
}

DiFloat DiAnimGraph::GetGraphSpeedCoeff() const
{
  return rGraphSpeedCoeff;
}

DiFloat DiAnimGraph::GetGraphSpeedUpCoeff() const
{
  DiFloat result = rGraphSpeedCoeff;
  DiAnimGraphElems const type = GetCurElemType();

  if (DIANGR_NODE == type || DIANGR_MACRONODE == type )
  {
    if( DiAnimNode const* pNode = GetNodeData(nCurNode) )
    {
      const float defaultSpeed = pNode->GetDefaultSpeed();
      if( 0.0f < defaultSpeed )
        result /= defaultSpeed;
      else
      {
        DIASSERT("Invalid default speed value!");
      }
      result *= pNode->GetSpeed();
    }
    else
    {
      DIASSERT(!"Missing current node data!");
    }
  }

  return result;
}

DiVoid DiAnimGraph::StoreDefaultValues()
{
  for( DiUInt32 i = 0, count = GetNumNodes(); i < count; ++i)
  {
    if( DiAnimNode* pNode = GetNodeData(i) )
      pNode->SetDefaultSpeed( pNode->GetSpeed() );
    else
    {
      DIASSERT(!"Missing node data");
    }
  }
}

DiBool DiAnimGraph::IsNodeIndexValid(int nodeIdx) const
{
  return (0 <= nodeIdx && nodeIdx < int(GetNumNodes()));
}
DiBool DiAnimGraph::IsTransactionIndexValid(int transIdx) const
{
  return (0 <= transIdx && transIdx < int(GetNumEdges()));
}
DiBool DiAnimGraph::IsSubTransactionIndexValid(int transIdx, int subTransIdx) const
{
  return (0 <= transIdx    && transIdx < int(GetNumEdges()) && 
          0 <= subTransIdx && subTransIdx < int(GetTransactionNumIntervals(transIdx)));
}

bool DiAnimGraph::ReplaceSeqInNode(int nodeSrc, int seqIdxSrc, int nodeDst, int seqIdxDst)
{
  DiAnimNode *src = GetNodeData(nodeSrc);
  DiAnimNode *dst = GetNodeData(nodeDst);
  NI_VERIFY(src != NULL && dst != NULL, "Invalid node indices", return false; );

  dst->GetSequences()[seqIdxDst].SetID(src->GetSequences()[seqIdxDst].GetID());

  return true;
}

DiUInt32 DiAnimGraph::GetNearestNode() const
{
  DiUInt32 curNode = GetCurNodeUnsafe();
  if ( curNode < GetNumNodes() )
    return curNode;
  else if ( IsInTransactionOrFLTransaction() )
  {
    curNode = GetNextNode();
    if ( curNode < GetNumNodes() )
      return curNode;
    else
      return 0;
  }
  else
    return 0;
}

DiUInt32 DiAnimGraph::GetDefNode() const
{
  return nDefNode;
}

DiVoid DiAnimGraph::SetDefNode( DiUInt32 node )
{
  nDefNode = node;
}

DiBool DiAnimGraph::SetNodeSpeed( DiUInt32 nodeId, DiFloat speedCoeff )
{
  if ( nodeId != DIANGR_NO_SUCH_ELEMENT )
  {
    DiAnimNode* node = GetNodeData( nodeId );
    if ( node )
    {
      DiFloat curLogicSpeed = node->GetLogicSpeed();
      DiFloat curRawNodeSpeed = node->GetSpeed()*node->GetMultiplier()/curLogicSpeed;
      node->SetLogicSpeed( speedCoeff );
      node->SetSpeed( curRawNodeSpeed/node->GetMultiplier()*node->GetLogicSpeed() );
      if ( node->IsSwitcher() )
      {
        class Setter : public INeiFunctor
        {
          DiUInt32 nodeID;
          DiFloat speedCoeff;
          DiAnimGraph* gpGraph;
        public:
          Setter(  DiAnimGraph* gpGraph, DiUInt32 nodeID, DiFloat speedCoeff ) 
          : gpGraph(gpGraph), nodeID(nodeID), speedCoeff(speedCoeff)
          {}
          virtual void operator()( DiUInt32 nodeId )
          {
            DiUInt32 nEdgeID = gpGraph->GetMTransactionID(nodeID, nodeId);
            DiAnimMTransaction *mtpEdge = gpGraph->GetTransactionData(nEdgeID);
            if ( mtpEdge->GetProbability() != 0.0f )
            {
              gpGraph->SetNodeSpeed( nodeId, speedCoeff );
            }
          }
        } st(this, nodeId, speedCoeff);

        ForAllNeighbours(nodeId, &st);
      }
    }
  }
  return false;
}

DiVoid DiAnimGraph::Freeze()
{
  freezed = TRUE;
}

DiVoid DiAnimGraph::UnFreeze()
{
  freezed = FALSE;
}
///eugbelNSCENE///} // end of namespace NScene


DiUInt32 DiAnimNode::CalcDispatcherNodeID()
{
  if ( !IsSubNode() )
    return DIANGR_NO_SUCH_ELEMENT;
  DiUInt32 nodeId = DIANGR_NO_SUCH_ELEMENT;

  for ( DiUInt32 i = 0; i < gpGraph->GetNumNodes(); i++ )
  {
    if ( this == gpGraph->GetNodeData(i) )
    {
      nodeId = i;
    }
  }

  class Tester : public INeiFunctor
  {
    DiUInt32 res;
    DiUInt32 nodeID;
    DiAnimGraph* gpGraph;
  public:
    Tester( DiUInt32 nodeID, DiAnimGraph* gpGraph ) 
    : nodeID(nodeID), res(DIANGR_NO_SUCH_ELEMENT), gpGraph(gpGraph)
    {}
    virtual void operator()( DiUInt32 nodeId )
    {
      if ( res == DIANGR_NO_SUCH_ELEMENT )
      {
        DiAnimNode* node = gpGraph->GetNodeData(nodeId);
        if ( node->IsSwitcher() )
        {
          if ( node->TestForDispatcher( nodeId, nodeID ) )
          {
            res = nodeId;
          }
        }
      }
    }
    DiUInt32 GetRes() const { return res; }
  } t(nodeId, gpGraph);

  gpGraph->ForAllNeighbours(nodeId, &t);
  return t.GetRes();
}

DiBool DiAnimNode::TestForDispatcher( DiUInt32 dispatcherID, DiUInt32 nodeID )
{
  class Tester : public INeiFunctor
  {
    DiBool res;
    DiUInt32 nodeID;
    DiAnimGraph* gpGraph;
  public:
    Tester( DiUInt32 nodeID, DiAnimGraph* gpGraph ) 
      : nodeID(nodeID), res(false), gpGraph(gpGraph)
    {}
    virtual void operator()( DiUInt32 nodeId )
    {
      if ( !res )
      {
        if ( gpGraph->GetNodeData(nodeId)->IsSubNode() )
        {
          if ( nodeId == nodeID )
          {
            res = true;
          }
        }
      }
    }
    DiBool GetRes() const { return res; }
  } t(nodeID, gpGraph);

  gpGraph->ForAllNeighbours(dispatcherID, &t);
  return t.GetRes();
}

