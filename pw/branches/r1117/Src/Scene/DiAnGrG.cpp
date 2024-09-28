/*
 * @file    DiAnGrG.cpp
 * @memo    General functions moved from DiAnGr.cpp
 * @author  EugBel
 * @date    26.09.2003
 * @prefix  DiAnGr
 * @header  DiAnGr.h
 * @library skeleton.lib
 */

// *******************************************************************
// includes
#include "stdafx.h"

#include <string.h>
#include <stdio.h>

#include "DiAnGr.h"
#include "DiMath.h"
#include "DiAnGrAPI.h"


///eugbelNSCENE///namespace NScene {

#pragma warning( disable : 4996 )

// *******************************************************************
// defines

// *******************************************************************
// local data

// init static pointer
DiAnGrNodesMap DiAnimGraph::nmpaTableOnConstructorOnly[64];
DiInt32 DiAnimGraph::numEntries = 0;

// *******************************************************************
// functions


/**
 * This function returns internal parameters
 *
 * @memo    Return internal values
 * @return  none
 * @param   rStartPar     min start transaction param
 * @param   rStopPar      max start transaction param
 * @author  EugBel
 */
DiVoid DiAnimFlTransaction::GetStartStopParams(DiFloat &rStartPar, 
                                             DiFloat &rStopPar)
{
  DIFUNCTION("GetStartStopParams");

  DIASSERT(0.0f <= rFromParamMin && rFromParamMin <= 1.0f);
  DIASSERT(0.0f <= rFromParamMax && rFromParamMax <= 1.0f);
  rStartPar = rFromParamMin;
  rStopPar  = rFromParamMax;
  
  DIRETURNVOID();
}

/**
 * This function is DiAnimGraph constructor
 *
 * @memo    Constructor of DiAnimGraph
 * @param   nNumNodes       number of nodes in graph
 * @param   nNumEdges       number of edges in graph
 * @param   nNodesDataSize  size of all node's data
 * @param   nEdgesDataSize  size of all transaction's (edge's) data
 * @param   bResult         result of graph constructing
 * @author  EugBel
 * @see     DiGraph::DiGraph()
 */
DiAnimGraph::DiAnimGraph(DiUInt32 nNumNodes, DiUInt32 nNumEdges, 
                         DiUInt32 nNodesDataSize, DiUInt32 nEdgesDataSize, 
                         DiBool &bResult, const DiTChar *cpName) :
                         DiGraph(nNumNodes, nNumEdges, 
                                 nNodesDataSize, nEdgesDataSize, 
                                 bResult, diGT_DIRECTED,
                                 DiGraphRepresentation::diGRT_ARRAY_OF_LISTS)
{
  DIFUNCTION("DiAnimGraph");

  // clear everything and set default node to 0 (always exists)
  // set all params to their default values
  nPrevNode             = DIANGR_NO_SUCH_ELEMENT;       
  nCurNode              = DIANGR_NO_SUCH_ELEMENT;
  nNextNode             = DIANGR_NO_SUCH_ELEMENT;
  nCurTrans             = DIANGR_NO_SUCH_ELEMENT; 
  nCurSubTrans          = DIANGR_NO_SUCH_ELEMENT; 
  rCurParInTransaction  = 0.0f;
  rLinParInTransaction  = 0.0f;
  rGraphSpeedCoeff      = 1.0f; // set default value

  bPathSpecified        = FALSE;
  bIsForced = FALSE;
  freezed = FALSE;
  gpPath.nCurIdxInPath  = DIANGR_NO_SUCH_ELEMENT;
  gpPath.nPathLength    = 0;
  gpPath.nTargetNode    = DIANGR_NO_SUCH_ELEMENT;
  // allocate memory for the path. Use max number of nodes + 2 (due to return back to first node and +1 - for sure)
  gpPath.npPath         = (DiUInt32 *)DiMemAllocate((nNumNodes + 2)* sizeof(DiUInt32));
    
  nNumSeqsPerNode       = 0;
  DiMemSet(cpaSceneComponents, NULL, DIANGR_MAX_NUM_SEQS_IN_NODE * sizeof(int *));

  sepClbStorage             = NULL;
  bNeedElementEnterCallback = TRUE;  // we need ENTER callback because we enter some element 
  bNeedElementLeaveCallback = FALSE;

  PrepareCallbacksStorage();

  mMarkers.clear();
  nmpaTableRuntime.clear();

#ifdef DIANGR_SCREEN_DEBUG_GENERAL
  // save graph's name
  DIASSERTPTR(cpName);
  caName[sizeof(caName) - 1] = '\0';
  strncpy(caName,cpName,DiIMin(strlen(cpName), sizeof(caName) - 1));

  nmpDbTable              = NULL;
  napDbSeqNames           = NULL;
  npDbNumSeqsInTables     = NULL;

  // Register Graph
  int pathSize = (nNumNodes + 1)* sizeof(DiUInt32);
  int callbackStorageSize = DIANGR_MAX_NUM_CALLBACKS * sizeof(DiAnGrClbStorageElem);
  DebugRegisterGraph(this, nNodesDataSize + nEdgesDataSize + pathSize + callbackStorageSize);
#else
  diUSE_PARAM(cpName);
#endif

#ifdef DIANGR_SCREEN_DEBUG_ADVANCED 
  // init callbacks-specific debug info
  nUsedCallbacksCells = 0;
  nCallbackCellToFill = 0;
#endif


  DIRETURNVOID();
}


/**
 * This function is DiAnimGraph destructor
 *
 * @memo    Destructor of DiAnimGraph
 * @author  EugBel
 * @see     DiAnimGraph
 */
DiAnimGraph::~DiAnimGraph()
{
  DIFUNCTION("~DiAnimGraph");

  if (gpPath.npPath != NULL)
  {
    DiMemFree(gpPath.npPath);
  }
  
  ResetSpeedAndUnregCallbackAfterReachMarker(true);
	Clear( markersData );

#ifdef DIANGR_SCREEN_DEBUG_GENERAL
  // Unregister Graph
  DebugUnregisterGraph(this);
  DebugFreeNamesTable();
#endif

  DIRETURNVOID();
} // end of DiAnimGraph  

/**
 * This function is standard get()-method
 standard* @memo    Standard get method
 * @return  internal value (by function name)
 */
DiUInt32 DiAnimGraph::GetPrevNode() const
{
  DIFUNCTION("GetPrevNode");
  DIASSERT(nPrevNode < GetNumNodes());
  DIRETURN(nPrevNode);
}

/**
 * This function is standard get()-method
 *
 * @memo    standard get method
 * @return  internal value (by function name)
 */
DiUInt32 DiAnimGraph::GetCurNode() const
{
  DIFUNCTION("GetCurNode");
  DIASSERT(nCurNode < GetNumNodes());
  DIRETURN(nCurNode);
}

/**
 * This function is standard get()-method but without an assert as in GetCurNode().
 * Common use: check for a concrete node in callback
 *
 * @memo    standard get method
 * @return  internal value (by function name)
 */
DiUInt32 DiAnimGraph::GetCurNodeUnsafe() const
{
  DIFUNCTION("GetCurNodeUnsafe");
  DIRETURN(nCurNode);
}


/**
 * This function is standart get()-mathod
 *
 * @memo    Standart get method
 * @return  internal value (by function name)
 */
DiUInt32 DiAnimGraph::GetNextNode() const
{
  DIFUNCTION("GetNextNode");
  DIASSERT(nNextNode < GetNumNodes());
  DIRETURN(nNextNode);
}

/**
 * This function is standart get()-method 
 *
 * @memo    Standart get method
 * @return  internal value (by function name)
 */
DiUInt32 DiAnimGraph::GetTargetNode() const
{
  DIFUNCTION("GetTargetNode");
  
  if (bPathSpecified)
  {
    DIASSERT(gpPath.nTargetNode < GetNumNodes());
    DIRETURN(gpPath.nTargetNode);
  }

  NI_ASSERT(nNextNode < GetNumNodes(), "Next node is invalid!"); 
  DIRETURN(nNextNode);
}


/**
 * This function is standart get()-mathod
 *
 * @memo    Standard get method
 * @return  internal value (by function name)
 */
DiUInt32 DiAnimGraph::GetCurTransaction()
{
  DIFUNCTION("GetCurTransaction");
  DIASSERT(nCurTrans < GetNumEdges());
  DIRETURN(nCurTrans);
}

/**
 * This function is standart get()-mathod (NOTE: no assert!)
 *
 * @memo    Standard get method
 * @return  internal value (by function name)
 */
DiUInt32 DiAnimGraph::GetCurTransactionUnsafe()
{
  DIFUNCTION("GetCurTransaction");
  DIRETURN(nCurTrans);
}


/**
 * This function is standart get()-mathod
 *
 * @memo    Standard get method
 * @return  internal value (by function name)
 */
DiUInt32 DiAnimGraph::GetCurSubTransaction()
{
  DIFUNCTION("GetCurTransaction");

  DIASSERT(nCurSubTrans < GetTransactionData(nCurTrans)->nNumIntervals);

  DIRETURN(nCurSubTrans);
}

/**
 * This function is standard get()-method
 *
 * @memo    Standard get method
 * @return  internal value (by function name)
 */
DiFloat DiAnimGraph::GetCurTransactionPar()
{
  DIFUNCTION("GetCurTransactionPar");
  DIASSERT(rCurParInTransaction >= 0.0f && rCurParInTransaction <= 1.0f);
  DIRETURN(rCurParInTransaction);
}

/**
 * This function is standard get()-method
 *
 * @memo    Standard get method
 * @return  internal value: linear parameter
 */
DiFloat DiAnimGraph::GetCurLinTransactionPar()
{
  DIFUNCTION("GetCurLinTransactionPar");
  DIASSERT(rLinParInTransaction >= 0.0f && rLinParInTransaction <= 1.0f);
  DIRETURN(rLinParInTransaction);
}

/**
 * @doc This function checks whether we are in transaction or FLTransaction
 *
 * @memo    
 * @return  
 * @author  EugBel
 */
DiBool DiAnimGraph::IsInTransactionOrFLTransaction() const
{
  DiAnimGraphElems  nCurEl;
  
  DIFUNCTION("IsInTransactionOrFLTransaction");
  
  nCurEl = GetCurElemType();
  DIRETURN(nCurEl == DIANGR_FLTRANSACTION);
} // end of IsInTransactionOrFLTransaction

/**
 * @doc This function checks whether we are in node or macronode
 *
 * @memo    
 * @return  
 * @author  EugBel
 */
DiBool DiAnimGraph::IsInNodeOrMacronode() const
{
  DiAnimGraphElems  nCurEl;
  
  DIFUNCTION("IsInNodeOrMacronode");
  
  nCurEl = GetCurElemType();
  DIRETURN((nCurEl == DIANGR_NODE) || (nCurEl == DIANGR_MACRONODE));
} // end of IsInNodeOrMacronode


/**
 * This function is standard get()-method
 *
 * @memo    Standard get method
 * @return  internal value (by function name)
 */
DiAnimGraphElems DiAnimGraph::GetCurElemType() const
{
  DIFUNCTION("GetCurElemType");
  DIASSERT(nCurNode        != DIANGR_NO_SUCH_ELEMENT ||
           nCurTrans       != DIANGR_NO_SUCH_ELEMENT);
  DIASSERT(!(nCurNode        != DIANGR_NO_SUCH_ELEMENT &&
             nCurTrans       != DIANGR_NO_SUCH_ELEMENT    ));
  
  if (nCurNode != DIANGR_NO_SUCH_ELEMENT)
  {
    if (bIsCurNodeMacronode)
      DIRETURN(DIANGR_MACRONODE);
    else
      DIRETURN(DIANGR_NODE);
  }
  if (nCurTrans       != DIANGR_NO_SUCH_ELEMENT)
  {
    DIASSERT(nCurSubTrans < GetTransactionData(nCurTrans)->nNumIntervals);
    DIRETURN(DIANGR_FLTRANSACTION);
  }
  
  DIRETURN(DIANGR_NA);
}

/**
 * This function is standard get()-method
 *
 * @memo    Standard get method
 * @return  internal value (by function name)
 */
DiInt32 DiAnimGraph::GetNumParts() const
{
  DIFUNCTION("GetNumParts");
  DIASSERT(nNumSeqsPerNode > 0 && 
          nNumSeqsPerNode <= DIANGR_MAX_NUM_SEQS_IN_NODE);
  DIRETURN(nNumSeqsPerNode);
}

DiInt32 DiAnimGraph::GetNumMarkers() const
{
  return mMarkers.size();
}


/**
 * This function is standard set()-method
 *
 * @memo    Standard set method
 * @param   value to set
 * @return  nothing
 */
DiVoid DiAnimGraph::SetPrevNode(DiUInt32 nID)
{
  DIFUNCTION("SetPrevNode");
  DIASSERT(nID < GetNumNodes());
  nPrevNode = nID;
  DIRETURNVOID();
}

/**
 * This function is standard set()-method
 *
 * @memo    Standard set method
 * @param   value to set
 * @return  nothing
 */
DiVoid DiAnimGraph::SetCurNode(DiUInt32 nID)
{
  DIFUNCTION("SetCurNode");
  DIASSERT(nID < GetNumNodes());
  nCurNode = nID;
  DIRETURNVOID();
}

DiVoid DiAnimGraph::SetNodeVPar(DiAnimNode *npNode, 
                                DiFloat rVPar)
{
  DiAnimMacronode *amnpNode;

  DIFUNCTION("SetNodeVPar");

  DIASSERT(0.0f <= rVPar && rVPar <= 1.0f);

  if (npNode->bIsThisMacronode)
  {
    amnpNode = (DiAnimMacronode *)npNode;
    amnpNode->SetVPar(nNumSeqsPerNode ,rVPar);
  }
  else
  {
    npNode->SetVPar(nNumSeqsPerNode ,rVPar);
  }
  
  DIRETURNVOID();
}
  
DiVoid DiAnimGraph::SetNodeVPar(DiInt32 nNodeID, 
                                DiFloat rVPar) 
{ 
  DIFUNCTION("SetNodeVPar");
  SetNodeVPar((DiAnimNode *)GetNodeData(nNodeID), rVPar);
  DIRETURNVOID();
}

/**
 * This function is a cover-function to SetNodeVPar. It checks special case of
 *          FlTransaction, perhaps change VPar, call SetNodeVPar()
 * @memo    Setup VPar of 2-nd node in transaction
 * @return  none
 * @param   npNode    2nd node in transaction
 * @param   tpTrans   pointer to transaction
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiVoid DiAnimGraph::SetupVParOfNextNodeInTransaction(DiAnimNode *npNode, 
                                        DiAnimFlTransaction *tpTrans)
{
  DiAnimFlTransaction *ftpTrans;

  // check FlTransaction
  //DIASSERT(DIANGR_SYNCH_NODES_IN_FLTRANS_F == tpTrans->rToParam);
  ftpTrans = (DiAnimFlTransaction *)tpTrans;
  
  if (ftpTrans->nUpdFlags & DIANGR_FLKIND_SECOND)
  {
    // use VPar of node
    
    // EugBel. 17.02.2005. Do not update node if speed is zero.
    // Perhaps it's not right but we need this for WaterSki project (because we update
    // VPars _directly_ from the program. What is good is that node's speed is zero
    if (npNode->GetSpeed() != 0.0f)
    {
      SetNodeVPar(npNode, npNode->rCurPar);
    }
    return;
  }

  // set NodePar == target parameter of transaction
  SetNodeVPar(npNode, tpTrans->rToParam);
}

/**
 * This function is standard set()-method
 *
 * @memo    Standard set method
 * @param   value to set
 * @return  nothing
 */
DiVoid DiAnimGraph::SetNextNode(DiUInt32 nID)
{
  DIFUNCTION("SetNextNode");
  DIASSERT(nID < GetNumNodes());
  nNextNode = nID;
  DIRETURNVOID();
}

/**
 * This function is standard set()-method
 *
 * @memo    Standard set method
 * @param   value to set
 * @return  nothing
 */
/*
DiVoid DiAnimGraph::SetCurTransaction(DiUInt32 nID)
{
  DIFUNCTION("SetCurTransaction");
  DIASSERT(nID < GetNumEdges());
  nCurTransaction = nID;
  DIRETURNVOID();
}
*/

/**
 * This function is standard set()-method
 *
 * @memo    Standard set method
 * @param   value to set
 * @return  nothing
 */
/*
DiVoid DiAnimGraph::SetCurTransactionPar(DiFloat rPar)
{
  DIFUNCTION("SetCurTransactionPar");
  diUSE_PARAM(rPar);
  DIASSERT(rPar >= 0.0f && rPar <= 1.0f);
  DIRETURNVOID();
}
*/

/**
 * This function retrieves AnimNode data
 *
 * @memo    Get DiAnimNode data
 * @return  pointer to data
 * @param   nNodeID
 * @author  EugBel
 */
DiAnimNode *DiAnimGraph::GetNodeData(DiUInt32 nNodeID)
{
  DiAnimNode *anpNode;
  
  DIFUNCTION("GetNodeData");
  DIASSERT(nNodeID < GetNumNodes());

  anpNode = (DiAnimNode *)DiGraph::GetNodeData(nNodeID);
    
  // setup pointer
  if(!anpNode->bIsThisMacronode)
    anpNode->spSequences = (DiAnGrSequence *)(anpNode + 1);
  else
    anpNode->spSequences = (DiAnGrSequence *)(((DiAnimMacronode *)anpNode) + 1);

  DIRETURN(anpNode);
} // end of GetNodeData

const DiAnimNode *DiAnimGraph::GetNodeData(DiUInt32 nNodeID) const
{
  DiAnimNode *anpNode;

  DIFUNCTION("GetNodeData");
  DIASSERT(nNodeID < GetNumNodes());

  anpNode = (DiAnimNode *)DiGraph::GetNodeData(nNodeID);

  // setup pointer
  if(!anpNode->bIsThisMacronode)
    anpNode->spSequences = (DiAnGrSequence *)(anpNode + 1);
  else
    anpNode->spSequences = (DiAnGrSequence *)(((DiAnimMacronode *)anpNode) + 1);

  DIRETURN(anpNode);
} // end of GetNodeData

DiUInt32 DiAnimGraph::GetMTransactionID(DiUInt32 nNodeFrom, DiUInt32 nNodeTo)
{
  DiUInt32 edgeID = GetEdgeID(nNodeFrom, nNodeTo);
  DIASSERT(edgeID != diGR_NO_SUCH_ELEMENT);
    
  return edgeID;
}

DiUInt32 DiAnimGraph::GetTransactionNumIntervals(DiUInt32 nTransID) const
{
  DIASSERT(nTransID < GetNumEdges());

  const DiAnimMTransaction *mtpTemp = (const DiAnimMTransaction *)DiGraph::GetEdgeData(nTransID);

  return mtpTemp->nNumIntervals;
}

DiAnimMTransaction *DiAnimGraph::GetTransactionData(DiUInt32 nTransID)
{
  DiAnimMTransaction *mtpTemp;
  DiAnimFlTransaction  *atpTransDataStart;
  DiUInt32           nI;
  
  NI_VERIFY( nTransID < GetNumEdges(), NStr::StrFmt( "Transaction %d out of range 0..%d", nTransID, GetNumEdges() ), return 0 );
  
  mtpTemp = (DiAnimMTransaction *)DiGraph::GetEdgeData(nTransID);

  // setup pointers
  mtpTemp->atppTransactions = (DiAnimFlTransaction **)(mtpTemp + 1);
  atpTransDataStart = (DiAnimFlTransaction *)((DiByte *)mtpTemp + sizeof(DiAnimMTransaction) + mtpTemp->nNumIntervals * sizeof(DiAnimFlTransaction *));
  
  // fill sub-transactions in cycle
  for (nI = 0; nI < mtpTemp->nNumIntervals; nI++)
  {
    // get the pointer
    mtpTemp->atppTransactions[nI] = atpTransDataStart + nI;
  }

  return mtpTemp;
}

DiAnimMTransaction const* DiAnimGraph::GetTransactionData(DiUInt32 nTransID) const
{
  DiAnimMTransaction *mtpTemp;
  DiAnimFlTransaction  *atpTransDataStart;
  DiUInt32           nI;

  DIASSERT(nTransID < GetNumEdges());

  mtpTemp = (DiAnimMTransaction *)DiGraph::GetEdgeData(nTransID);

  // setup pointers
  mtpTemp->atppTransactions = (DiAnimFlTransaction **)(mtpTemp + 1);
  atpTransDataStart = (DiAnimFlTransaction *)((DiByte *)mtpTemp + sizeof(DiAnimMTransaction) + mtpTemp->nNumIntervals * sizeof(DiAnimFlTransaction *));

  // fill sub-transactions in cycle
  for (nI = 0; nI < mtpTemp->nNumIntervals; nI++)
  {
    // get the pointer
    mtpTemp->atppTransactions[nI] = atpTransDataStart + nI;
  }

  return mtpTemp;
}

/**
 * This function returns needed sub-transaction
 *
 * @memo    
 * @return  
 * @param   nTransID
 * @param   nSubTransID
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiAnimFlTransaction *DiAnimGraph::GetTransactionData(DiUInt32 nTransID, DiUInt32 nSubTransID, DiUInt32 nodeFrom/* = 0*/, DiUInt32 nodeTo/* = 0*/ )
{
  DiAnimMTransaction *mtpMTrans;
  DiAnimFlTransaction  *atpTransDataStart;
  
  DIASSERT(nTransID    < GetNumEdges());

  mtpMTrans = (DiAnimMTransaction *)DiGraph::GetEdgeData(nTransID);
  
  if (nSubTransID >= mtpMTrans->nNumIntervals)
  {
    string NodeFrom( GetNodeNameByID( nodeFrom ) );
    string NodeTo( GetNodeNameByID( nodeTo ) );
    //TODO Assert
    DIASSERT_ALOOF_CODE( NStr::StrFmt( "%s NodeFrom = %s, NodeTo = %s", GetDBFileName(), NodeFrom.c_str(), NodeTo.c_str() ) );
    return NULL;
  }

  // setup pointers
  mtpMTrans->atppTransactions = (DiAnimFlTransaction **)(mtpMTrans + 1);
  
  atpTransDataStart = (DiAnimFlTransaction *)((DiByte *)mtpMTrans + sizeof(DiAnimMTransaction) + 
                       mtpMTrans->nNumIntervals * sizeof(DiAnimFlTransaction *));
  
  // common check
  DIASSERT(((atpTransDataStart + nSubTransID)->rToParam >= 0.0f &&
           (atpTransDataStart + nSubTransID)->rToParam <= 1.0f   ) );            
  
  return atpTransDataStart + nSubTransID;
}

/**
 * This function returns sub-transaction hich is nearest to given VPar
 *
 * @memo    
 * @return  
 * @param   rVPar
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiUInt32 DiAnimMTransaction::GetTransactionNearestToPar(DiFloat rVPar, DiFloat &deltaVPar)
{
  DiFloat  rNearestStart;
  DiUInt32 nNearestID, nI;
  DiFloat  rTMin, rTMax;

  rNearestStart = MAX_FLOAT;
  nNearestID    = DIANGR_NO_SUCH_ELEMENT;
  // search for nearest transaction: either find transaction with nearest StartMin value
  // or transaction where rVPar is in [StartMin, StartMax]
  for (nI = 0; nI < this->nNumIntervals; nI++)
  {
    this->atppTransactions[nI]->GetStartStopParams(rTMin, rTMax);
    
    if (rTMin <= rVPar)    
    {
      if (rTMax >= rVPar)
      {
        // given parameter is inside start parameters
        deltaVPar = 0.0f;
        return nI;
      }
    }
    else // rVPar < rFromParamMin
    {
      // remember this transaction
      if (rNearestStart > rTMin)
      {
        deltaVPar     = rTMin - rVPar;
        rNearestStart = rTMin;
        nNearestID    = nI;
      }
    }
  }

  DIASSERT((rNearestStart != MAX_FLOAT && nNearestID != DIANGR_NO_SUCH_ELEMENT) ||
           (rNearestStart == MAX_FLOAT && nNearestID == DIANGR_NO_SUCH_ELEMENT)   );         

  return nNearestID;
}

/*
 *  Check transaction for not overlapping
 */
DiBool DiAnimMTransaction::IsCorrect()
{
  DiUInt32 nI, nJ;
  // use simple algorithm because of small number of sub-transactions
  for (nI = 0; nI < this->nNumIntervals - 1; nI++)
  {
    for (nJ = nI + 1; nJ < this->nNumIntervals; nJ++)    
    {
      // check overlapping
      if (! (atppTransactions[nI]->GetMinFromPar() > 
             atppTransactions[nJ]->GetMaxFromPar()   ||
             atppTransactions[nI]->GetMaxFromPar() < 
             atppTransactions[nJ]->GetMinFromPar()     ) )
        return FALSE;
    }
  }

  return TRUE;
}

/**
 * @memo    Propagate VPar into the node
 * @return  None
 * @param   rVPar   -- virtual parameter to enforce: if default set data to embedded
 * @author  Earnol
 * @see     Nothing
 */
DiVoid DiAnimNode::SetVPar(DiInt32 nSeqNum, DiFloat rVPar)
{
  DiInt32 nI;

  DIFUNCTION("DiAnimNode::SetVPar");

  DIASSERT(0.0f <= rVPar && rVPar <= 1.0f);
  DIASSERT(nSeqNum == gpGraph->GetNumParts());

  //propagate to sequences
  for(nI = 0; nI < nSeqNum; nI++)
  {
    (this->spSequences + nI)->DiAnGrSequence::SetVPar(rStartPar, rStopPar, /*rV*/rVPar);
  }

  DIRETURNVOID();
} // end of DiAnimNode::SetVPar;

// Common methods
DiVoid  DiAnimNode::SetCurVPar(DiFloat rCurPar)       
{ 
  DIASSERT(0.0f <= rCurPar && rCurPar <= 1.0f); 
  this->rCurPar =  rCurPar; 
}
DiVoid  DiAnimNode::SetSpeed(DiFloat rSpeed)          
{ 
  this->rSpeed = rSpeed; 
}
DiVoid  DiAnimNode::SetSurfSpeed(DiVec2 rSurfSpeed)          
{ 
  this->rSurfSpeed = rSurfSpeed; 
}
DiVoid  DiAnimNode::SetDefaultSpeed(DiFloat rSpeed)
{
  this->rDefaultSpeed = rSpeed;
}
DiVoid  DiAnimNode::SetSwitcher(DiBool bIsSwitcher)          
{ 
  this->bIsSwitcher = bIsSwitcher; 
}
DiVoid  DiAnimNode::SetLooped(DiBool bLooped, DiUInt32 thisNodeID, DiUInt32 nDefNextNode)
{ 
  this->bIsLooped = bLooped; 
  if (!bLooped)
  {
    SetDefNextNode(nDefNextNode);
    NI_VERIFY(nDefNextNode < this->gpGraph->GetNumNodes(), "Wrong next node!", SetDefNextNode(0); );
  }
  else
  {
    SetDefNextNode(thisNodeID);
    NI_VERIFY(thisNodeID < this->gpGraph->GetNumNodes(), "Wrong node ID!", SetDefNextNode(0); );
  }
}
DiVoid  DiAnimNode::SetDefNextNode(DiUInt32 nNode)    
{ 
  //AGTrace("SetDefNode: %i", nNode);
  DIASSERT(nNode < this->gpGraph->GetNumNodes());
  this->nDefNext = nNode; 
}
DiVoid  DiAnimNode::SetMacronodeFlag(DiBool bIsMacro) 
{ 
  this->bIsThisMacronode =bIsMacro; 
}
DiVoid  DiAnimNode::SetStartPar(DiFloat rPar)         
{ 
  DIASSERT(0.0f <= rPar && rPar <= 1.0f);
  this->rStartPar = rPar; 
}
DiVoid  DiAnimNode::SetStopPar(DiFloat rPar)          
{ 
  DIASSERT(0.0f <= rPar && rPar <= 1.0f);
  this->rStopPar = rPar; 
}
DiVoid  DiAnimNode::SetClbStorageToNull()             
{ 
  this->sepClbStorage = NULL; 
}
DiVoid  DiAnimNode::SetGraph(DiAnimGraph *agpGr)      
{ 
  DIASSERTPTR(agpGr);
  this->gpGraph = agpGr; 
}

DiFloat DiAnimNode::GetVPar() const                   
{ 
  DIASSERT(0.0f <= rCurPar && rCurPar <= 1.0f)
  return rCurPar; 
}
DiFloat DiAnimNode::GetStartPar() const               
{ 
  DIASSERT(0.0f <= rStartPar && rStartPar <= 1.0f)
  return rStartPar; 
}
DiFloat DiAnimNode::GetStopPar() const                
{ 
  DIASSERT(0.0f <= rStopPar && rStopPar <= 1.0f)
  return rStopPar; 
}
DiUInt32 DiAnimNode::GetDefNextNode() const           
{ 
  DIASSERT(nDefNext < this->gpGraph->GetNumNodes());
  return nDefNext; 
}

DiFloat* DiAnimNode::GetNodeFieldAddress(const string& name)
{
  if (name == "speed") 
    return &rSpeed;
  if (name == "startPar") 
    return &rStartPar;
  if (name == "stopPar") 
    return &rStopPar;

  NI_ALWAYS_ASSERT( NStr::StrFmt( "Unknown field (%s) in AnimGraph node!", name.c_str() ) );
  return 0;
}

/**
 * This function sets VPars for nodes of the Macronode
 *
 * @memo    Set VPars for nodes of the Macronode
 * @return  none
 * @param   rpVPars pointer to an array of VPars
 * @param   nNum    number of elements in the array above. Used for assertion
 * @author  EugBel
 */
DiVoid  DiAnimMacronode::SetDifferentVParsForIntNodes(DiFloat *rpVPars, DiInt32 nNum)
{
  DiInt32    nI, nJ, nNumSeqsPerNode = gpGraph->GetNumParts();

  DIFUNCTION("SetIntNodesVPars");

  DIASSERT(nNum == nNumInternalNodes);


  for (nJ = 0; nJ < nNumInternalNodes; nJ++)
  {
    //propagate to sequences
    for(nI = 0; nI < nNumSeqsPerNode; nI++)
    {
      (this->spSequences + nJ * nNumSeqsPerNode + nI)->DiAnGrSequence::SetVPar(rStartPar, rStopPar, rpVPars[nJ]);
    }
  }

  DIRETURNVOID();
} // end of SetIntNodesVPars

/**
 * @memo    Propagate rpW into the Macronode
 * @return  None
 * @param   rpW   -- array of weghts to be set. Should be properly balanced!
 * @author  EugBel
 */
DiVoid DiAnimMacronode::SetIntNodesWeights(DiFloat *rpW)
{
  DiInt32 nI, nJ;
  DiInt32 nNumSeqsPerNode = gpGraph->GetNumParts();

  DIFUNCTION("DiAnimNode::SetWeights");
  
#ifdef DIDEBUG
  DiFloat rSum = 0.0f;
  for(nI = 0; nI < nNumInternalNodes; nI++)
  {
    rSum += rpW[nI];
  }
  rSum -= 1.0f;
  DIASSERT(DiFAbs(rSum) < 0.001f);
#endif

  for (nJ = 0; nJ < nNumInternalNodes; nJ++)
  {
    //propagate to sequences
    for(nI = 0; nI < nNumSeqsPerNode; nI++)
    {
      (this->spSequences + nJ * nNumSeqsPerNode + nI)->rWeight = rpW[nJ];
    }
  }
} // end of DiAnimNode::SetWeights

DiFloat DiAnimMacronode::GetIntNodeWeight(DiInt32 nIntNode, DiInt32 nSeqIdx) const
{
  return  (this->spSequences + nIntNode * gpGraph->GetNumParts() + nSeqIdx)->rWeight;
}
  
/**
 * @memo    Propagate weights into the Macronode
 * @return  None
 * @param   rW   -- weight to balance
 * @author  EugBel
 */
DiVoid DiAnimMacronode::SetIntNodeWeight(DiInt32 nIntNode, DiFloat rW)
{
  DiFloat rLeft, rLeftSum, rRatio;
  DiInt32 nI, nJ;
  DiInt32 nNumSeqsPerNode = gpGraph->GetNumParts();

  DIFUNCTION("DiAnimNode::SetWeight");

  DIASSERT(0.0f <= rW && rW <= 1.0f);
  //rest for other
  rLeft = 1.0f - rW;
  //find current left sum
  rLeftSum = 0.0f;
  for (nJ = 0; nJ < nNumInternalNodes; nJ++)
  {
    if(nIntNode == nJ)
      continue;
    rLeftSum += (this->spSequences + nJ * nNumSeqsPerNode)->rWeight;
  }
  //handle special case
  if(rLeftSum == 0.0f)
  {
    for (nJ = 0; nJ < nNumInternalNodes; nJ++)
    {
      if(nIntNode == nJ)
        continue;
      for (nI = 0; nI < nNumSeqsPerNode; nI++)
      {
       (this->spSequences + nJ * nNumSeqsPerNode + nI)->rWeight = 0.5f;
      }
      rLeftSum += 0.5f;
    }
  }
  //propagate to selected
  for (nI = 0; nI < nNumSeqsPerNode; nI++)
  {
    (this->spSequences + nIntNode * nNumInternalNodes + nI)->rWeight = rW;
  }
  DIASSERT(nNumInternalNodes > 1);
  rRatio = rLeft / rLeftSum / DiL2F(nNumInternalNodes - 1);
  for (nJ = 0; nJ < nNumInternalNodes; nJ++)
  {
    if(nIntNode == nJ)
      continue;
    //propagate to sequences
    for(nI = 0; nI < nNumSeqsPerNode; nI++)
    {
      (this->spSequences + nJ * nNumSeqsPerNode + nI)->rWeight *= rRatio;
    }
  }

  DIRETURNVOID();
} // end of DiAnimNode::SetWeight

/**
 * @memo    Propagate VPar into the Macronode
 * @return  None
 * @param   nSeqNum   -- number of sequences in graph.
 * @param   rVPar     -- virtual parameter to enforce: if default set data to embedded
 * @author  EugBel
 */
DiVoid DiAnimMacronode::SetVPar(DiInt32 nSeqNum, DiFloat rVPar)
{
  DiInt32 nI, nJ;

  DIFUNCTION("DiAnimNode::SetVPar");

  DIASSERT(0.0f <= rVPar && rVPar <= 1.0f);
  DIASSERT(nSeqNum == gpGraph->GetNumParts());

  for (nJ = 0; nJ < nNumInternalNodes; nJ++)
  {
    //propagate to sequences
    for(nI = 0; nI < nSeqNum; nI++)
    {
      (this->spSequences + nJ * nSeqNum + nI)->DiAnGrSequence::SetVPar(rStartPar, rStopPar, /*rV*/rVPar);
    }
  }

  DIRETURNVOID();
} // end of DiAnimMacronode::SetVPar;

/**
 * @memo  Return number of internal nodes
 */
DiInt32 DiAnimMacronode::GetNumIntNodes()
{
  return nNumInternalNodes;
}

/**
 * @memo    Adopt rNodePar from [0;1] to sequence realities
 * @return  None
 * @param   rNormalizedPar
 * @author  EugBel, Earnol
 * @see     Nothing
 */
DiVoid DiAnGrSequence::SetVPar(DiFloat rStartNodePar, 
                               DiFloat rStopNodePar, DiFloat rNodePar)
{
  DIFUNCTION("DiAnGrSequence::SetVPar");

  if (DiFAbs(rSpeed) < DIANGR_MIN_SPEED)
    DIRETURNVOID();

  if (rStopPar - rStartPar < 0.0001f)
  {
    DIASSERT(rStopPar >= rStartPar);
    rCurPar = rStartPar;
    DIRETURNVOID();
  }

  if (rStopNodePar - rStartNodePar > 0.0001f)
  {
    if (rSpeed > 0)
    {
      rCurPar = rStartPar + 
                rSpeed * (rStopPar - rStartPar) * (rNodePar     - rStartNodePar)/
                                                  (rStopNodePar - rStartNodePar);
    }
    else
    {
      // NOTE: speed is negative
      rCurPar = rStopPar + 
                rSpeed * (rStopPar - rStartPar) * (rStopNodePar - (1.0f - rNodePar)) /
                                                  (rStopNodePar - rStartNodePar);
    }
  }
  else
  {
    DIASSERT(rStopNodePar >= rStartNodePar);
    rCurPar = rStartPar;
  }

  rCurPar = DiAnimGraph::WrapIn(rCurPar, rStartPar, rStopPar);
  DIASSERT(0.0f <= rCurPar && rCurPar <= 1.0f);

  DIRETURNVOID();
} // end of DiAnGrSequence::SetVPar

/**
 * This function clears list of "anim-NodeID"
 *
 * @memo    Cleanup memory
 * @author  EugBel
 */
DiVoid DiAnimGraph::FreeNodesTable()
{
  DIFUNCTION("FreeNodesTable");

  numEntries = 0;

  DIRETURNVOID();
} // end of FreeNodesTable

DiVoid DiAnimGraph::CopyNodesTableToRuntimeTable(DiAnGrNodesMap *nmpSrc, DiAnimGraph *anpGraph, DiInt32 nNumNodes)
{
  DiInt32 nI;

  DIASSERT(0 == anpGraph->nmpaTableRuntime.size());

  anpGraph->nmpaTableRuntime.reserve(nNumNodes);

  // copy data
  for (nI = 0; nI < nNumNodes; nI++, nmpSrc = nmpSrc + 1)
  {
    anpGraph->nmpaTableRuntime.push_back(DiAnGrNodesMap(nmpSrc->cpNodeName));
  }

} // end of FreeNodesTable


/**
 * This function adds node's name to table in inverse order
 *
 * @memo    Add table to list (NOTE: to head of the list)
 * @return  TRUE on success, FALSE otherwise
 * @param   cpName
 * @author  EugBel
 */
DiBool DiAnimGraph::AddNodeToTableOnConstructor(const DiTChar *cpName)
{
  DIASSERTMSG(0 <= numEntries && numEntries < DIM(nmpaTableOnConstructorOnly), "Crash");
  strcpy(nmpaTableOnConstructorOnly[numEntries].cpNodeName, cpName);
  numEntries++;

  DIRETURN(TRUE);
} // end of AddNodeToTableOnConstructor

DiTChar *DiAnimGraph::GetNodeNameFromTableOnConstructor(int nodeIdx)
{
  DIASSERT(0 <= nodeIdx && nodeIdx < numEntries);
  return nmpaTableOnConstructorOnly[nodeIdx].cpNodeName;
} // end of AddNodeToTableOnConstructor

DiUInt32 DiAnimGraph::GetNodeIDByNameOnConstructor(const DiTChar *cpName)
{
  for (int i = 0; i < numEntries; i++)
  {
    if (strcmp(cpName, nmpaTableOnConstructorOnly[i].cpNodeName) == 0)
      return i;
  }

  return DIANGR_NO_SUCH_ELEMENT;
}



/**
 * This function gets sequence index by sequence name
 *
 * @memo    Get sequence index by it's name
 * @return  index
 * @param   cpName name
 * @author  EugBel
 * @see     
 */
DiUInt32 DiAnimGraph::GetSeqIdxByName(DiAnimNamesArray  napSeqsTable,
                                      DiUInt32 nNumSeqsInTable,
                                      const DiTChar *cpName)
{
  DiUInt32 nI;

  DIFUNCTION("GetSeqIdxByName");
  
  DIASSERTPTR(napSeqsTable);
  DIASSERT(nNumSeqsInTable > 0);
  DIASSERTPTR(cpName);

  for (nI = 0; nI < nNumSeqsInTable; nI++)
    if (strcmp(cpName,napSeqsTable[nI]) == 0)
      DIRETURN(nI);
  
  char s[200];
  sprintf(s, "Sequence %s was not found in %s",cpName,GetDBFileName().c_str());
  DIASSERTMSG(FALSE, s);

  DIRETURN(DIANGR_NO_SUCH_ELEMENT);
} // end of GetSeqIdxByName


/**
 * This function gets sequence name by sequence ID
 *
 * @memo    Get sequence name by it's ID
 * @return  pointer to name
 * @param   cpName name
 * @author  EugBel
 * @see     
 */
DiTChar *DiAnimGraph::GetSeqNameByIdx(DiAnimNamesArray  napSeqsTable,
                                      DiUInt32 nNumSeqsInTable,
                                      DiUInt32 nID)
{
  DIASSERTPTR(napSeqsTable);
  DIASSERT(nNumSeqsInTable > 0);
  DIASSERT(nID < nNumSeqsInTable);

  DIASSERTPTR(napSeqsTable[nID]);
  return napSeqsTable[nID];
} // end of GetSeqIdxByName


/**
 * This function returns Node's or Macronode's ID by it's name
 *
 * @memo    Return Node's or Macronode's ID in graph by Name
 * @return  ID
 * @param   cpName
 * @author  EugBel
 */
DiUInt32 DiAnimGraph::GetNodeIDByNameSlow(const DiTChar *cpName) const
{
  DIFUNCTION("GetNodeIDByNameSlow");

  // find ID in prepared table
  int x = GetNodeIDByNameSlowQuite(cpName);
  if (x != DIANGR_NO_SUCH_ELEMENT)
    return x;
    
  char s[300];
  sprintf(s, "Node reference %s found, but such node (with such name) doesn't exist." , cpName);
  DIASSERTMSG(FALSE, s); // no node found by Name
  DIRETURN(0);
} // end of GetNodeIDByNameSlow

DiInt32 DiAnimGraph::GetNodeIDByNameSlowQuite(const char *cpName) const
{
  for (int i = 0; i < nmpaTableRuntime.size(); i++)
  {
    if (!strcmp(cpName, nmpaTableRuntime[i].cpNodeName))
    {
      DIRETURN(i);
    }
  }
  
  //DebugTrace("Node reference %s found, but such node (with such name) doesn't exist." , cpName);
  return DIANGR_NO_SUCH_ELEMENT;
}


// This function uses new structure: nmpaTableRuntime (used in Nival project for the first time)
const DiTChar *DiAnimGraph::GetNodeNameByID(DiUInt32 nID)
{
  if (nID < DiUInt32(nmpaTableRuntime.size()))
    return nmpaTableRuntime[nID].cpNodeName;

  return NULL;
}

DiInt32 DiAnimGraph::GetNextNodeIDByEdge(DiInt32 nodeFromID, DiInt32 edgeID)
{
  class Selecter : public INeiFunctor
  {
    DiInt32 edgeID;
    DiUInt32 res;
    DiUInt32 nodeFromID;
    DiAnimGraph* ag;
  public:
    Selecter( DiUInt32 nodeFromID, DiUInt32 edgeID, DiAnimGraph* ag ) 
      : edgeID(edgeID), res(DIANGR_NO_SUCH_ELEMENT), nodeFromID(nodeFromID), ag(ag)
    {}
    virtual void operator()( DiUInt32 nodeId )
    {
      if ( res == DIANGR_NO_SUCH_ELEMENT )
      {
        DiUInt32 nEdgeID = ag->GetEdgeID(nodeFromID, nodeId);
        if (edgeID == DiInt32(nEdgeID))
        {
          res = nodeId;
        }
      }
    }
    DiUInt32 GetRes() const { return res; }
  } sl(nodeFromID, edgeID, this);

  ForAllNeighbours(nodeFromID, &sl);
  DiUInt32 res = sl.GetRes();
  return res == DIANGR_NO_SUCH_ELEMENT ? -1 : res;
}

/*
 * @memo    Calculate parabola
 * @return  None
 * @param   rx
 * @param   vp
 * @author  Earnol
 * @see     Nothing
 */
static DiFloat _diAnGrCalc3Parab(DiFloat rx, DiVoid *vp)
{
  DiFloat rA;
  DiFloat rRes;
  DiFloat rx2, rx3;

  DIFUNCTION("_diAnGrCalc3Parab");

  rA = *((DiFloat *)vp);

  rx2 = rx * rx;
  rx3 = rx2 * rx;
  rRes = rA * rx3 - 1.5f * rA * rx2 + (1.0f + 0.5f * rA) * rx;

  DIRETURN(rRes);
} // end of _diAnGrCalc3Parab

/*
 * @memo    Calculate sine
 * @return  None
 * @param   rx
 * @param   vp
 * @author  Earnol
 * @see     Nothing
 */
static DiFloat _diAnGrCalcSine(DiFloat rx, DiVoid *vp)
{
  DiFloat rA;
  DiFloat rB;
  DiFloat rRes;

  DIFUNCTION("_diAnGrCalc3Parab");

  rA = *((DiFloat *)vp);
  rB = *((DiFloat *)vp + 1);

  rRes = rA * DiSin(rB * rx);

  DIRETURN(rRes);
} // end of _diAnGrCalc3Parab

/*
 * @memo    Calculate sine
 * @return  None
 * @param   rx
 * @param   vp
 * @author  Earnol
 * @see     Nothing
 */
static DiFloat _diAnGrCalcSpline(DiFloat rx, DiVoid *vp)
{
  DiFloat rA;
  DiFloat rB;
  DiFloat rC;
  DiFloat rRes;
  DiFloat rx2, rx3;

  DIFUNCTION("_diAnGrCalcSpline");

  rA = *((DiFloat *)vp);
  rB = *((DiFloat *)vp + 1);
  rC = 1.0f - rA - rB;

  rx2 = rx * rx;
  rx3 = rx2 * rx;
  rRes = rA * rx3 + rB * rx2 + rC * rx;

  DIRETURN(rRes);
} // end of _diAnGrCalcSpline

/**
 * @memo    Calculate params upon given kind 
 * @return  None
 * @param   rCurPar
 * @author  Earnol
 * @see     Nothing
 */
DiFloat DiAnimFlTransaction::CalcCurPar(DiFloat rCurLinPar, DiFloat rOldCurPar, const nstl::string& dbfilename)
{
  DiFloat rRet = 0.0f;

  DIFUNCTION("DiAnimFlTransaction::CalcCurPar");
  
  DIASSERT(0.0f <= rCurLinPar && rCurLinPar <= 1.0f);
  
  switch(kKind)
  {
    case DIAN_TRKIND_UNIFORM:
    {
      //as is
      rRet = rCurLinPar;
      break;
    }
    case DIAN_TRKIND_3PARABOLIC   :
    {
      rRet = _diAnGrCalc3Parab(rCurLinPar, &rParA);
      rRet = DiFFitIn(rRet, 0.0f, 1.0f);
      break;
    }
    case DIAN_TRKIND_3RECPARABOLIC:
    {
      DiAlSolveEquationParams ep;
      ep.rAccuracy  = 1e-4f;
      ep.rFrom      = 0.0f;
      ep.rTo        = 1.0f;
      ep.rGuessRoot = rOldCurPar;
      ep.rStep      = 0.1f; //just magic
      ep.rY         = rCurLinPar;
      rRet = DiAlSolveEquationIntectionally(&ep, _diAnGrCalc3Parab, &rParA, dbfilename);
      rRet = DiFFitIn(rRet, 0.0f, 1.0f);
      break;
    }
    case DIAN_TRKIND_SINE         :
    {
      DiFloat ra[2];
      ra[0] = rParA;
      ra[1] = rParB;
      rRet = _diAnGrCalcSine(rCurLinPar,  &(ra[0]));
      break;
    }
    case DIAN_TRKIND_RECSINE      :
    {
      DiAlSolveEquationParams ep;
      DiFloat ra[2];
      ep.rAccuracy  = 1e-4f;
      ep.rFrom      = 0.0f;
      ep.rTo        = 1.0f;
      ep.rGuessRoot = rOldCurPar;
      ep.rStep      = 0.1f; //just magic
      ep.rY         = rCurLinPar;
      ra[0] = rParA;
      ra[1] = rParB;
      rRet = DiAlSolveEquationIntectionally(&ep, _diAnGrCalcSine, &(ra[0]), dbfilename);
      rRet = DiFFitIn(rRet, 0.0f, 1.0f);
      break;
    }
    case DIAN_TRKIND_SPLINE    :
    {
      DiFloat ra[2];
      ra[0] = rParA;
      ra[1] = rParB;
      rRet = _diAnGrCalcSpline(rCurLinPar,  &(ra[0]));
      rRet = DiFFitIn(rRet, 0.0f, 1.0f);
      break;
    }
    case DIAN_TRKIND_RECSPLINE :
    {
      DiFloat ra[2];
      DiAlSolveEquationParams ep;
      ra[0] = rParA;
      ra[1] = rParB;
      ep.rAccuracy  = 1e-4f;
      ep.rFrom      = 0.0f;
      ep.rTo        = 1.0f;
      ep.rGuessRoot = rOldCurPar;
      ep.rStep      = 0.1f; //just magic
      ep.rY         = rCurLinPar;
      rRet = DiAlSolveEquationIntectionally(&ep, _diAnGrCalcSpline, &(ra[0]), dbfilename);
      rRet = DiFFitIn(rRet, 0.0f, 1.0f);      
      break;
    }
    default:
    {
      DIASSERTMSG(FALSE,"Unknown kind of transaction");
    }
  }

  DIRETURN(rRet);
} // end of DiAnimFlTransaction::CalcCurPar



/**
 * This function 
 *
 * @memo    
 * @return  none
 * @param   kKind
 * @param   rAIn
 * @param   rBIn
 * @param   rAOut
 * @param   rBOut
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiVoid DiAnimFlTransaction::ConvertExtParsToIntPars(Kind kKind, 
                                                  DiFloat rAIn, DiFloat rBIn,
                                                  DiFloat &rAOut, DiFloat &rBOut)
{
  rAOut = DIANGR_INVALID_FLOAT_VALUE;
  rBOut = DIANGR_INVALID_FLOAT_VALUE;

  switch(kKind)
  {
    case DIAN_TRKIND_UNIFORM:
    {
      break;
    }
    case DIAN_TRKIND_3PARABOLIC   :
    case DIAN_TRKIND_3RECPARABOLIC:
    {
      rAOut = rAIn;
      break;
    }
    case DIAN_TRKIND_SINE         :
    case DIAN_TRKIND_RECSINE      :
    {
      //check validness
      DIASSERT(1.0f <= rAIn);

      //prevent crash
      rAOut = DiFMax(1.0f, rAIn);

      rBOut = (DiFloat)asin(1.0f / rAOut);
      break;
    }
    case DIAN_TRKIND_SPLINE    :
    case DIAN_TRKIND_RECSPLINE :
    {
      // NOTE: if you change something here don't forget to change 
      // function WriteKindParams()
      rAOut = 9.0f * (3.0f * rAIn - 3.0f * rBIn + 1.0f) * 0.5f;
      rBOut = -9.0f * (5.0f * rAIn - 4.0f * rBIn + 1.0f) * 0.5f;
      break;
    }
    default:
    {
      DIASSERTMSG(FALSE,"Unknown kind of transaction");
    }
  }

}


/**
 * This function prepares internal transaction parameters to be used out-of-graph
 *
 * @memo    
 * @return  none
 * @param   kKind
 * @param   rAIn
 * @param   rBIn
 * @param   rAOut
 * @param   rBOut
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiVoid DiAnimFlTransaction::ConvertIntParsToExtPars(Kind kKind, 
                                                  DiFloat rAIn, DiFloat rBIn,
                                                  DiFloat &rAOut, DiFloat &rBOut)
{
  rAOut = DIANGR_INVALID_FLOAT_VALUE;
  rBOut = DIANGR_INVALID_FLOAT_VALUE;

  switch(kKind)
  {
    case DIAN_TRKIND_UNIFORM:
    {
      break;
    }
    case DIAN_TRKIND_3PARABOLIC   :
    case DIAN_TRKIND_3RECPARABOLIC:
    case DIAN_TRKIND_SINE         :
    case DIAN_TRKIND_RECSINE      :
    {
      rAOut = rAIn;
      break;
    }
    case DIAN_TRKIND_SPLINE    :
    case DIAN_TRKIND_RECSPLINE :
    {
      // count rA and rB
      rAOut = DiFloat(-(8./9. * rAIn - 6. / 9. * rBIn - 1.) / 3.);
      rBOut = DiFloat(-(11./9. * rAIn - 6./9. * rBIn - 2.) / 3.);
      break;
    }
    default:
    {
      DIASSERTMSG(FALSE,"Unknown kind of transaction");
    }
  }
}



/**
 * This function returns VPar for any current element since current element always exists it always returns 
 * but watch for cur element
 *
 * @memo    This function returns VPar
 * @return  VPar
 * @param   Node
 * @author  Earnol
 */
DiFloat  DiAnimGraph::GetCurVPar(DiVoid)
{
  DiAnimGraphElems   geCur;
  DiInt32            nCurIdx;
  DiFloat            rCur;
  DiAnimNode         *anpNode;
  DiAnimMacronode    *amnpNode;

  DIFUNCTION("DiAnimGraph::GetCurVPar");

  //init
  geCur = GetCurElemType();

  switch(geCur)
  {
    case DIANGR_NODE:
    {
      nCurIdx = GetCurNode();
      anpNode = (DiAnimNode *)GetNodeData(nCurIdx);
      rCur    = anpNode->rCurPar;
      break;
    }
    case DIANGR_MACRONODE:
    {
      nCurIdx  = GetCurNode();
      amnpNode = (DiAnimMacronode *)GetNodeData(nCurIdx);
      rCur     = amnpNode->rCurPar;
      break;
    }
    case DIANGR_FLTRANSACTION:
    {
      //just relay
      rCur = GetCurTransactionPar();
      break;
    }
    default:
    {
      DIASSERT_ALOOF_CODE(GetDBFileName());
      rCur = MAX_FLOAT;
    }
  }

  DIRETURN(rCur);
} // end of GetCurrentVPar

/**
 * This function should be called when graph should be destroyed 
 *
 * @memo    Cleanup memory used by graph (~ destructor)
 * @return  none
 * @param   gGraph
 * @author  EugBel
 */
DiVoid DiAnimGraph::Destroy(DiAnimGraph *gGraph)
{
  DIFUNCTION("Destroy");

  //gGraph->DestroyUserData();
  nstl::list<DiAnGrClbStorageElem>* pStorage = gGraph->sepClbArray;
  delete gGraph;  
  DiAnimGraph::ReleaseCallbacksStorage(pStorage);

  DIRETURNVOID();
} // end of Destroy

/**
 * This function wraps value in [rMin, rMax]
 *
 * @memo    Wrap value
 * @return  Wrapped value
 * @param   rValue
 * @author  EugBel
 */
DiFloat DiAnimGraph::WrapIn(DiFloat rValue, DiFloat rMin, DiFloat rMax,
                            DiUInt32 *npNumWrapsHappened)
{
  DiFloat rLength;
  DiBool  bCount;
  DIFUNCTION("Wrap");

  //DIASSERT(rMin < rMax);
  rLength = rMax - rMin;
  
  bCount = FALSE;
  if (npNumWrapsHappened != NULL)
  {
    *npNumWrapsHappened = 0;
    bCount = TRUE;
  }

  if (rValue > rMax)
  {
    while (rValue > rMax)
    {
      rValue -= rLength;
      if (bCount)
        (*npNumWrapsHappened)++;
    }
  }
  else
  {
    if (rValue < rMin)
    {
      while (rValue < rMin)
      {
        rValue += rLength;
        if (bCount)
          (*npNumWrapsHappened)++;
      }
    }
  }

  DIASSERT(rMin <= rValue && rValue <= rMax);
  DIRETURN(rValue);
} // end of WrapIn

/**
 * This function restarts graph, i.e. make it valid for update
 *
 * @memo    Restart graph
 * @return  TRUE on success, FALSE otherwise
 * @param   nStartNodeID
 * @author  EugBel
 * @see     Update()
 */
DiBool  DiAnimGraph::Restart( DiUInt32 nStartNodeID, bool needCallbacks )
{
  DIFUNCTION("Restart");

  if ( freezed )
    DIRETURN(TRUE);

  //if ( GetDBFileName().find("/Witch/") != nstl::string::npos )
  //{
  //  if ( GetCurNodeUnsafe() < GetNumNodes() )
  //  {
  //    DiAnimNode* node = GetNodeData( GetCurNode() );
  //    DebugTrace( "CurNode: %s %f\n", GetNodeNameByID( GetCurNode() ), node->GetVPar() );
  //  }
		//DebugTrace( "Restart: %f %s \n", NHPTimer::GetScalarTime(), GetNodeNameByID(nStartNodeID) );
  //}

  // При рестарте AG вызываем callback'и на OnNodeLeave NUM_TASK
  if ( needCallbacks && GetCurNodeUnsafe() < GetNumNodes() )
  {
    ForceLeaveNodeCallbacks( GetCurNode() );
  }

  AGTrace("=================AG_RESTART(%i)", nStartNodeID);

  DiAnimNode* node = GetNodeData(nStartNodeID);
  if ( node->IsSwitcher() )
  {
    DiUInt32 nodeID = SelectNextNodeByProbability( nStartNodeID, node );
    if ( nodeID < GetNumNodes() )
    {
      Restart( nodeID, true );
      DIRETURN(TRUE);
    }
    else
    {
      NI_ALWAYS_ASSERT("Can\'t find random node");
    }
  }

  // set all params to their default values
  nPrevNode                 = DIANGR_NO_SUCH_ELEMENT;       
  nCurNode                  = DIANGR_NO_SUCH_ELEMENT;
  nNextNode                 = DIANGR_NO_SUCH_ELEMENT;
  nCurTrans                 = DIANGR_NO_SUCH_ELEMENT; 
  nCurSubTrans              = DIANGR_NO_SUCH_ELEMENT;
  rLinParInTransaction      = 0.0f;
  rCurParInTransaction      = 0.0f;

  bNeedElementEnterCallback = TRUE;
  bNeedElementLeaveCallback = FALSE;

	ResetCallbacksOnParFlag(DIANGR_NODE, GetNodeData(nStartNodeID));
  
  bPathSpecified            = FALSE;
  bIsForced = FALSE;
  gpPath.nCurIdxInPath      = DIANGR_NO_SUCH_ELEMENT;
  gpPath.nPathLength        = 0;
  gpPath.nTargetNode        = DIANGR_NO_SUCH_ELEMENT;
  
  // this function sets default node and graph is ready for update
  SetNode(nStartNodeID);

  DIRETURN(TRUE);
} // end of 

DiFloat DiAnimGraph::GetNodeDuration(DiUInt32 nNode) const
{
  // hack: 
  DiAnimGraph* pSelf = const_cast<DiAnimGraph*>(this);
  if( DiAnimNode* pNode = pSelf->GetNodeData( nNode ) )
  {
    return pNode->GetSpeed() < EPS_VALUE ? 
      0.0f : ( pNode->GetStopPar() - pNode->GetStartPar() ) / pNode->GetSpeed();
  }

  return 0.0f;
}

// This function checks graph's integrity
// Please note that even if this function returns TRUE - it's not 100% guaranteed that graph is valid
// This function is rather high-level checking, not low-level!
DiBool DiAnimGraph::IsGraphValid() const
{
  DiAnimGraph *ths = const_cast<DiAnimGraph *>(this);

  bool ok(true);

  ok = ok && (ths->GetNumNodes() < 50);
  ok = ok && (ths->GetNumEdges() < 100);
  ok = ok && (ths->GetNumParts() == 1);
  ok = ok && (ths->GetCurNodeUnsafe() < 100 || ths->GetCurNodeUnsafe() == DIANGR_NO_SUCH_ELEMENT);

  if (!ok)
  {
    // intentionally made a block of code - to put breakpoint here
    NI_ASSERT(ok, "AnimGraph is invalid!");
  }

  return ok;
}

///eugbelNSCENE///} // end of namespace NScene

#pragma warning( default : 4996 )

