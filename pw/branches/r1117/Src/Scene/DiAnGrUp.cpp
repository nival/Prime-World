/*
 * @file    DiAnGrUp.cpp
 * @memo    DiAnimGraph functions that deal with graph's updating
 * @author  EugBel
 * @date    04.02.2004
 * @prefix  DiAnGr
 * @header  DiAnGr.h
 * @library skeleton.lib
 */

// *******************************************************************
// includes
#include "stdafx.h"

#include "DiAnGrUtils.h"
#include "DiAnGr.h"

#include "../System/InlineProfiler.h"


///eugbelNSCENE///namespace NScene {

// *******************************************************************
// defines
#define DIANGRUP_IMPOSSIBLE_STARTPAR   (-2.0f)
#define DIANGRUP_IMPOSSIBLE_STOPPAR    (-1.0f)

// *******************************************************************
// local data

// *******************************************************************
// functions


/**
 * This function updates sequences in node using Node's virtual parameter
 *
 * @memo    Update sequences in node
 * @author  EugBel
 */
DiVoid DiAnimGraph::UpdateNodeSequences(DiUInt32 nNode)
{
  
  DiInt32         nI, nJ;
  DiAnimNode      *anpNode;
  DiAnimMacronode *amnpNode;

  DIFUNCTION("UpdateCurrentNodeSequences");

  anpNode = GetNodeData(nNode);
  
  if (anpNode->GetSpeed() != 0.0f)
  {
    if (FALSE == anpNode->IsMacronode())
    {
      for (nI = 0; nI < GetNumParts(); nI++)
      {
        anpNode->spSequences[nI].SetVPar(anpNode->rStartPar,
          anpNode->rStopPar,
          anpNode->rCurPar);
      }
    }
    else // cur node is Macronode
    {
      amnpNode = (DiAnimMacronode *)anpNode;
      // update all internal nodes
      for (nJ = 0; nJ < amnpNode->nNumInternalNodes; nJ++)
      {
        for (nI = 0; nI < GetNumParts(); nI++)
        {
          amnpNode->spSequences[nJ + nI * GetNumParts()].SetVPar(
            anpNode->rStartPar,
            anpNode->rStopPar,
            anpNode->rCurPar);
        }
      }
    }
  } // end of (rSpeed != 0)

  DIRETURNVOID();
} // end of UpdateCurrentNodeSequences

/**
 * This function sets first state in update()
 *
 * @memo    Set first state
 * @return  next state
 * @param   rDt   time for update
 */
DiAnGrUpdateState DiAnimGraph::UpdateBegin()
{
  DiAnimGraphElems geElem;

  // get current graph element
  geElem = GetCurElemType();

  // analyze graph state
  if (DIANGR_NODE == geElem || DIANGR_MACRONODE == geElem )
  {
    DiAnimNode* nextNode = GetNodeData(GetNextNode());
    if ( nextNode->IsSwitcher() )
    {
      DiUInt32 nodeID = SelectNextNodeByProbability( GetNextNode(), nextNode );
      if ( nodeID < GetNumNodes() )
      {
        SetNextNode( nodeID );
      }
      else
      {
        NI_ALWAYS_ASSERT("Can\'t find random node");
      }
    }
    DIRETURN (DIANGR_UPDATE_NODE_ACTIVE);
  }

  if (DIANGR_FLTRANSACTION == geElem)
    DIRETURN (DIANGR_UPDATE_FLTRANSACTION_ACTIVE);
  
  DIASSERT_ALOOF_CODE(GetDBFileName());
  DIRETURN (DIANGR_UPDATE_NA);
}

/**
 * This function updates given node. This node should be a node from FlTransaction,
 * that's why we do the following: if the node is looped than we update it
 * exactly like in UpdateNodeActiveLooped(). If the node is not looped than when we
 * come to the max 
 *
 * @memo    Update looped node
 * @return  next state
 * @param   rDt   time for update
 */
DiAnGrUpdateState DiAnimGraph::UpdateNodeActiveInFlTrans(DiUInt32 nNode, DiFloat &rDt, 
                                                         DiBool &bWrapped,
                                                         DiAnGrFlTransParam tpParam)
{
  DiAnimNode *anpNode;
  DiFloat    rSavedPar;
  DiFloat    rOrigDt;
  DiFloat    rSpeedCorrected;

  diUSE_PARAM(tpParam); // currently don't use but this might be useful in future

  //init
  anpNode         = GetNodeData(nNode);
  rOrigDt         = rDt;
  rSpeedCorrected = anpNode->GetSpeed() * GetGraphSpeedCoeff();

  DIASSERT(rDt >= 0.0f);
  // check simple case: speed == 0.0f
  if (DiFAbs(rSpeedCorrected) < DIANGR_MIN_SPEED)
  {
    rDt = 0.0f;
    DIRETURN(DIANGR_UPDATE_END);
  }

  rSavedPar            = anpNode->rCurPar;
  anpNode->rCurPar += rDt * rSpeedCorrected;

  if (0.0f <= anpNode->rCurPar && anpNode->rCurPar < 1.0f)
  {
    // everything is good. Parameter was updated. 
    rDt = 0.0f;
    DIRETURN(DIANGR_UPDATE_END);
  }

  // here we have overflow 
  if (anpNode->rCurPar >= 1.0f)              
  {
    // first: set cur par a valid value
    anpNode->rCurPar = 1.0f;

    // check case of not looped node
    if (FALSE == anpNode->bIsLooped)
    {
      // stop node updating here (at the end)
      rDt = 0.0f;
      DIRETURN(DIANGR_UPDATE_END);
    }

    // wrap looped node

    // change parameters
    rDt -= (1.0f - rSavedPar) / rSpeedCorrected; // we can loose precision here if anpNode->rCurPar almost == 1.0f
    rDt = DiFMax(rDt, 0.0f);  // prevent crash

    bWrapped = TRUE;
    if(rDt <= DIANGR_MIN_DT)
    {
      rDt = 0.0f;
      DIRETURN(DIANGR_UPDATE_END);
    }
    DIRETURN(DIANGR_UPDATE_NODE_ACTIVE);
  }

  // here we have underflow
  if (anpNode->rCurPar < 0.0f)
  {
    anpNode->rCurPar = 0.0f;
    
    // check case of not looped node
    if (FALSE == anpNode->bIsLooped)
    {
      // stop node updating here (at the end)
      rDt = 0.0f;
      DIRETURN(DIANGR_UPDATE_END);
    }

    // wrap looped node
    // change parameters
    rDt -= (rSavedPar - 0.0f) / rSpeedCorrected;// we can loose precision here if anpNode->rCurPar almost == 0.0f
    rDt = DiFMax(rDt, 0.0f);

    bWrapped = TRUE;
    if(rDt <= DIANGR_MIN_DT)
    {
      rDt = 0.0f;
      DIRETURN(DIANGR_UPDATE_END);
    }
    DIRETURN(DIANGR_UPDATE_NODE_ACTIVE);
  }

  DIASSERT_ALOOF_CODE(GetDBFileName());
  rDt = 0.0f;
  DIRETURN(DIANGR_UPDATE_NA);
}



/**
 * This function updates current looped node 
 *
 * @memo    Update looped node
 * @return  next state
 * @param   rDt   time for update
 */
DiAnGrUpdateState DiAnimGraph::UpdateNodeActiveLooped(DiUInt32 nNode, DiFloat &rDt, 
                                                      DiBool &bWrapped,
                                                      DiAnGrFlTransParam tpParam)
{
  DiAnimNode *anpNode;
  DiFloat    rSavedPar;
  DiFloat    rOrigDt;
  DiFloat    rSpeedCorrected;

  //init
  anpNode         = GetNodeData(nNode);
  rOrigDt         = rDt;
  rSpeedCorrected = anpNode->GetSpeed() * GetGraphSpeedCoeff();
  AGTrace("N_UPD_LPD VP=%5.3lf (dT=%5.3lf)", anpNode->rCurPar, rDt);

  DIASSERT(rDt >= 0.0f);
  // check simple case: speed == 0.0f
  if (DiFAbs(rSpeedCorrected) < DIANGR_MIN_SPEED)
  {
    rDt = 0.0f;
    DIRETURN(DIANGR_UPDATE_END);
  }

  rSavedPar            = anpNode->rCurPar;
  anpNode->rCurPar += rDt * rSpeedCorrected;

  if (0.0f <= anpNode->rCurPar && anpNode->rCurPar < 1.0f)
  {
    // everything is good. Parameter was updated. 
    rDt = 0.0f;
    DIRETURN(DIANGR_UPDATE_END);
  }

  // here we have overflow 
  if (anpNode->rCurPar >= 1.0f)
  {
    // change parameters
    anpNode->rCurPar = 1.0f;
    rDt -= (1.0f - rSavedPar) / rSpeedCorrected; // we can loose precision here if anpNode->rCurPar almost == 1.0f
    rDt = DiFMax(rDt, 0.0f);

    bWrapped = TRUE;
    AGTrace("Set node to wrap. Dt left=%10.7f", rDt);
    if(rDt <= DIANGR_MIN_DT)
    {
      rDt = 0.0f;
      AGTrace("Asking to stop update because Dt is zero.");
      DIRETURN(DIANGR_UPDATE_END);
    }
    DIRETURN(DIANGR_UPDATE_NODE_ACTIVE);
  }

  // here we have underflow
  if (anpNode->rCurPar < 0.0f)
  {
    // change parameters
    anpNode->rCurPar = 0.0f;
    rDt -= (rSavedPar - 0.0f) / rSpeedCorrected;// we can loose precision here if anpNode->rCurPar almost == 0.0f
    rDt = DiFMax(rDt, 0.0f);

    bWrapped = TRUE;
    if(rDt <= DIANGR_MIN_DT)
    {
      rDt = 0.0f;
      DIRETURN(DIANGR_UPDATE_END);
    }
    DIRETURN(DIANGR_UPDATE_NODE_ACTIVE);
  }

  DIASSERT_ALOOF_CODE(GetDBFileName());
  rDt = 0.0f;
  DIRETURN(DIANGR_UPDATE_NA);
}

/**
 * This function updates node if next node is not current node
 *
 * @memo    Update node
 * @return  next state
 * @param   rDt   time for update
 */
DiAnGrUpdateState DiAnimGraph::UpdateNodeActiveNotLooped(DiUInt32 nNodeCur, DiUInt32 nNodeNext, DiFloat &rDt,
                                                         DiBool &bWrapped, DiAnGrFlTransParam tpParam)
{
  DiAnimNode         *anpNodeCur;
  DiAnimFlTransaction  *atpTrans;
  DiAnimMTransaction *mtpMTrans;
  DiUInt32           nEdgeID, nSubTransID;
  DiFloat            rTransStartPar, rTransStopPar;
  DiFloat            rDeltaNodePar, rSavedPar;
  DiFloat            rSpeedCorrected;

  anpNodeCur      = GetNodeData(nNodeCur);
  rSpeedCorrected = anpNodeCur->GetSpeed() * GetGraphSpeedCoeff();

  DIASSERT(rDt >= 0.0f);
  // check simple case: speed == 0.0f
  if (DiFAbs(rSpeedCorrected) < DIANGR_MIN_SPEED)
  {
    rDt = 0.0f;
    DIRETURN(DIANGR_UPDATE_END);
  }

  DiAnimNode* nextNode = GetNodeData( nNodeNext );
  if ( nextNode->IsSubNode() )
  {
    DiUInt32 dispatchNodeID = nextNode->GetDispatcherNodeID();
    NI_ASSERT( dispatchNodeID < GetNumNodes(), "Bad dispatcher node" );
    DiAnimNode* dispatchNode = GetNodeData( dispatchNodeID );
    NI_ASSERT( dispatchNode->IsSwitcher(), "Bad dispatcher node" );
    nEdgeID = GetEdgeID(nNodeCur, dispatchNodeID);
  }
  else
  {
    nEdgeID = GetEdgeID(nNodeCur, nNodeNext);
    if (diGR_NO_SUCH_ELEMENT == nEdgeID)
    {
      nstl::string from( GetNodeNameByID(nNodeCur) ? GetNodeNameByID(nNodeCur) : "null" );
      nstl::string to( GetNodeNameByID(nNodeNext) ? GetNodeNameByID(nNodeNext) : "null" );
      nstl::string result( NStr::StrFmt("%s, transaction from %s to %s", GetDBFileName().c_str(),from.c_str(),to.c_str()) );
      DIASSERT_ALOOF_CODE(result); // common reason: transaction doesn't exist in file
      rDt = 0.0f;
      AGTrace("UPD_NOTLOOPED:#0");
      DIRETURN(DIANGR_UPDATE_END);
    }
  }

  // get all transactions between these nodes
  mtpMTrans = GetTransactionData(nEdgeID);
  if ( !mtpMTrans )
  {
    rDt = 0.0f;
    DIRETURN(DIANGR_UPDATE_END);
  }

  // find nearest transaction to current node parameter
  DiFloat temp(0.f);
  nSubTransID = mtpMTrans->GetTransactionNearestToPar(anpNodeCur->rCurPar, temp);

  if (DIANGR_NO_SUCH_ELEMENT == nSubTransID)
  {
    atpTrans = NULL;
    // invalidate data: make it impossible to start transaction after current parameter
    
    rTransStartPar = DIANGRUP_IMPOSSIBLE_STARTPAR;
    rTransStopPar  = DIANGRUP_IMPOSSIBLE_STOPPAR;
  }
  else
  {
    atpTrans = GetTransactionData(nEdgeID, nSubTransID);
    DIASSERTPTR(atpTrans);

    // get transaction parameters
    atpTrans->GetStartStopParams(rTransStartPar, rTransStopPar);
  }
  
  rDeltaNodePar = DiFAbs(rDt * rSpeedCorrected);
  
  if (rSpeedCorrected > 0.0f)
  {
    if (anpNodeCur->rCurPar + rDeltaNodePar < rTransStartPar || ( !bIsForced && anpNodeCur->rCurPar + rDeltaNodePar < 1.0f ) )
    {
      AGTrace("UPD_NOTLOOPED: common way (curPar=%5.3lf,dP=%5.3lf,start=%5.3lf)",anpNodeCur->rCurPar, rDeltaNodePar, rTransStartPar);
      anpNodeCur->rCurPar += rDeltaNodePar;
      rDt = 0.0f;
      DIRETURN(DIANGR_UPDATE_END);
    }

    if (anpNodeCur->rCurPar > rTransStopPar)
    {
      AGTrace("UPD_NOTLOOPED: missed trans (curPar=%5.3lf,dP=%5.3lf,stop=%5.3lf)",anpNodeCur->rCurPar, rDeltaNodePar, rTransStopPar);
      if (anpNodeCur->rCurPar + rDeltaNodePar <= 1.0f)
      {
        AGTrace("UPD_NOTLOOPED:#1");
        anpNodeCur->rCurPar += rDeltaNodePar;        
        rDt = 0.0f;
        DIRETURN(DIANGR_UPDATE_END);
      }

      if (FALSE == anpNodeCur->bIsLooped)
      {
        nstl::string from( GetNodeNameByID(nNodeCur) ? GetNodeNameByID(nNodeCur) : "null" );
        nstl::string to( GetNodeNameByID(nNodeNext) ? GetNodeNameByID(nNodeNext) : "null" );
        nstl::string result( NStr::StrFmt("%s, transaction from %s to %s", GetDBFileName().c_str(),from.c_str(),to.c_str()) );
        DIASSERT_ALOOF_CODE(result); // we need to leave current node but we can't
        rDt = 0.0f;
        AGTrace("UPD_NOTLOOPED:#2");
        DIRETURN(DIANGR_UPDATE_END);
      }

      // here node is looped
      rSavedPar = anpNodeCur->rCurPar;
      anpNodeCur->rCurPar = 1.0f;
      bWrapped = TRUE;
      DIASSERT(rSpeedCorrected >= DIANGR_MIN_SPEED);
      rDt -= (1.0f - rSavedPar) / rSpeedCorrected;
      rDt = DiFMax(rDt, 0.0f);  // prevent crash
      DIASSERT(rDt >= 0.0f);
      AGTrace("UPD_NOTLOOPED:#3");
      DIRETURN(DIANGR_UPDATE_NODE_ACTIVE);
    }

    DIASSERT(anpNodeCur->rCurPar + rDeltaNodePar >= rTransStartPar);

    // start transaction ASAP
    
    // set cur VPar to min possible value to start transaction
    rSavedPar           = anpNodeCur->rCurPar;
    if (anpNodeCur->rCurPar < rTransStartPar)
    {
      anpNodeCur->rCurPar = rTransStartPar;
      
      DIASSERT(rSpeedCorrected >= DIANGR_MIN_SPEED);
      if (DiFAbs(rSpeedCorrected) >= DIANGR_MIN_SPEED)
      {
        rDt -= (rTransStartPar - rSavedPar) / rSpeedCorrected;
        rDt = DiFMax(0.f, rDt);
      }
      DIASSERT(rDt >= 0.0f);
    }

  } // end of positive speed

  if (rSpeedCorrected < 0.0f)
  {
    // correct impossible values here because negative speed is rather rare
    if (DIANGR_NO_SUCH_ELEMENT == nSubTransID)
    {
      rTransStartPar = -DIANGRUP_IMPOSSIBLE_STARTPAR;
      rTransStopPar  = -DIANGRUP_IMPOSSIBLE_STOPPAR;
    }

    if (anpNodeCur->rCurPar - rDeltaNodePar > rTransStopPar)
    {
      anpNodeCur->rCurPar -= rDeltaNodePar;
      rDt = 0.0f;
      AGTrace("UPD_NOTLOOPED:#4");
      DIRETURN(DIANGR_UPDATE_END);
    }

    if (anpNodeCur->rCurPar < rTransStartPar)
    {
      if (FALSE == anpNodeCur->bIsLooped)
      {
        DIASSERT_ALOOF_CODE(GetDBFileName()); // we need to leave current node but we can't
        rDt = 0.0f;
        AGTrace("UPD_NOTLOOPED:#5");
        DIRETURN(DIANGR_UPDATE_END);
      }
    
      if (anpNodeCur->rCurPar - rDeltaNodePar >= 0.0f)
      {
        anpNodeCur->rCurPar -= rDeltaNodePar;
        rDt = 0.0f;
        AGTrace("UPD_NOTLOOPED:#6");
        DIRETURN(DIANGR_UPDATE_END);
      }
      // here node is looped
      rSavedPar = anpNodeCur->rCurPar;
      anpNodeCur->rCurPar = 0.0f;
      rDt -= (rSavedPar - 0.0f) / rSpeedCorrected;
      DIASSERT(rDt >= 0.0f);
      AGTrace("UPD_NOTLOOPED:#7");
      DIRETURN(DIANGR_UPDATE_NODE_ACTIVE);
    }
  

    DIASSERT(anpNodeCur->rCurPar - rDeltaNodePar <= rTransStopPar);

    // start transaction ASAP
    AGTrace("UPD_NOTLOOPED: starting transaction ASAP: curPar=%5.3lf,dP=%5.3lf,stop=%5.3lf",anpNodeCur->rCurPar, rDeltaNodePar, rTransStopPar);
  
    // set cur VPar to min possible value to start transaction
    rSavedPar           = anpNodeCur->rCurPar;
    if (anpNodeCur->rCurPar > rTransStopPar)
    {
      AGTrace("UPD_NOTLOOPED:#8");
      anpNodeCur->rCurPar = rTransStopPar;
      if (DiFAbs(rSpeedCorrected) >= DIANGR_MIN_SPEED)
        rDt -= (rSavedPar - rTransStopPar) / rSpeedCorrected;
      DIASSERT(rDt >= 0.0f);
    }

  } // end of negative speed

  // set special global flag that we leave node
  this->bNeedElementLeaveCallback = TRUE;

  AGTrace("UPD_NOTLOOPED:#9");
  DIRETURN(DIANGR_UPDATE_TRANSACTION_SETTING);
}

/**
 * This function updates active node
 *
 * @memo    Update active node
 * @return  next state
 * @param   rDt  time for update
 */
DiAnGrUpdateState DiAnimGraph::UpdateNodeActive(DiUInt32 nNodeCur, DiUInt32 nNodeNext, 
                                                DiFloat &rDt, DiBool &bWrapped,
                                                DiAnGrFlTransParam tpParam)
{
  // change function to work due to situation
  if (tpParam != DIANGR_FLTRANS_NA)
  {
    AGTrace("==AG_UPD_NODE_FL==(cur=%i,next=%i)", nCurNode, nNodeNext);
    DIRETURN(UpdateNodeActiveInFlTrans(nNodeCur, rDt, bWrapped, tpParam));
  }

  if (nNodeNext == nNodeCur)
  {
    AGTrace("==Calling UpdateNodeLooped (cur=%i[%s],next=%i[%s])", nCurNode, GetNodeNameByID(nCurNode), nNodeNext, GetNodeNameByID(nNodeNext));
    DIRETURN(UpdateNodeActiveLooped(nNodeCur, rDt, bWrapped, tpParam));
  }
  else
  {
    AGTrace("==Calling UpdateNode(!)NOT(!)Looped (cur=%i[%s],next=%i[%s])", nCurNode, GetNodeNameByID(nCurNode), nNodeNext, GetNodeNameByID(nNodeNext));
    DIRETURN(UpdateNodeActiveNotLooped(nNodeCur, nNodeNext, rDt, bWrapped, tpParam));
  }
}

/**
 * This function sets transaction 
 *
 * @memo    Set transaction
 * @return  next state
 * @param   rDt time for update
 */
DiAnGrUpdateState DiAnimGraph::UpdateTransactionSetting()
{
  DiAnimNode         *anpCurNode, *anpNextNode;
  DiAnimFlTransaction  *atpTrans;
  DiAnimMTransaction *mtpTrans;
  DiFloat            temp(0.f);

  anpCurNode        = GetNodeData(nCurNode);
  anpNextNode       = GetNodeData(nNextNode);

  if ( anpNextNode->IsSwitcher() )
  {
    nNextNode = SelectNextNodeByProbability(nNextNode, anpNextNode);
    anpNextNode = GetNodeData(nNextNode);
  }

  AGTrace("AG:%x, TRANS SET: from %i to %i", this, nCurNode, nNextNode);
  
  // transactions

  DiAnimNode* nextNode = GetNodeData( nNextNode );
  if ( nextNode->IsSubNode() )
  {
    DiUInt32 dispatchNodeID = nextNode->GetDispatcherNodeID();
    NI_ASSERT( dispatchNodeID < GetNumNodes(), "Bad dispatcher node" );
    DiAnimNode* dispatchNode = GetNodeData( dispatchNodeID );
    NI_ASSERT( dispatchNode->IsSwitcher(), "Bad dispatcher node" );
    nCurTrans = GetEdgeID(nCurNode, dispatchNodeID);
  }
  else
  {
    nCurTrans       = GetEdgeID(nCurNode, nNextNode);
  }

  mtpTrans          = GetTransactionData(nCurTrans);
  nCurSubTrans      = mtpTrans->GetTransactionNearestToPar(anpCurNode->rCurPar, temp);
  atpTrans          = GetTransactionData(nCurTrans, nCurSubTrans);
  DIASSERTPTR(atpTrans);
  
  anpNextNode->rCurPar  = atpTrans->rToParam;

  // set transaction parameter
  rLinParInTransaction  = 0.0f;
  rCurParInTransaction  = 0.0f; //save a bit atpTrans->CalcCurPar(rLinParInTransaction, rCurParInTransaction);

//   DIASSERT(nCurNode != nNextNode);
//   DIASSERT(atpTrans->rFromParamMin <= anpCurNode->rCurPar && 
//            anpCurNode->rCurPar <= atpTrans->rFromParamMax);
  DIASSERT(0 <= nCurTrans && nCurTrans <= GetNumEdges());
  
  // set new state in graph: active transaction
  nPrevNode       = nCurNode;
  nCurNode        = DIANGR_NO_SUCH_ELEMENT;
  
  bNeedElementEnterCallback = TRUE;

  // transaction has started => clear callbacks flag
  ResetCallbacksOnParFlag(DIANGR_FLTRANSACTION, mtpTrans);

  DIRETURN(DIANGR_UPDATE_FLTRANSACTION_ACTIVE);
}

/**
 * This function updates transaction's params
 *
 * @memo    Update transaction's params
 * @return  next state
 * @param   rDt time for update
 */
DiAnGrUpdateState DiAnimGraph::UpdateTransactionActive(DiFloat &rDt)
{
  DiAnimFlTransaction *atpTrans;
  DiFloat           rDeltaPar;
  DiFloat           rSpeedCorrected;

  atpTrans        = GetTransactionData(nCurTrans, nCurSubTrans);
  rSpeedCorrected = atpTrans->rSpeed * GetGraphSpeedCoeff();

  rDeltaPar = rDt * rSpeedCorrected;

  AGTrace("TR_UPD: prevPar=%5.3lf, delta=%5.3lf, ", rLinParInTransaction, rDeltaPar);

  if (rLinParInTransaction + rDeltaPar < 1.0f)
  {
    rDt = 0.0f;
    rLinParInTransaction += rDeltaPar;
    rCurParInTransaction  = atpTrans->CalcCurPar(rLinParInTransaction, rCurParInTransaction, GetDBFileName());
    DIRETURN(DIANGR_UPDATE_END);
  }
  
  // here we have overflow
  rDt -= (1.0f - rLinParInTransaction)/rSpeedCorrected;
  rLinParInTransaction = 1.0f;
  rCurParInTransaction = 1.0f; //we can save a bit atpTrans->CalcCurPar(rLinParInTransaction);
  rDt = DiFMax(0.0f, rDt);
  
  // set special global flag that we leave transaction
  this->bNeedElementLeaveCallback = TRUE;

  DIRETURN(DIANGR_UPDATE_NODE_SETTING);
}

/**
 * This function updates floating transaction
 *
 * @memo    
 * @return  
 * @param   
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiAnGrUpdateState DiAnimGraph::UpdateFlTransaction(DiFloat &rDt)
{
  DiAnimFlTransaction *atpTrans;
  DiAnimNode          *anpNodeFrom, *anpNodeTo;
  DiUInt32            nNodeFrom, nNodeTo;
  DiFloat             rSavedDt;
  DiAnGrUpdateState   usState;  
  DiBool              bNodeFromIsWaiting, bNodeToIsWaiting;

  nNodeFrom = this->nPrevNode;
  nNodeTo   = this->nNextNode;

  anpNodeFrom = GetNodeData(nNodeFrom);
  DIASSERT(anpNodeFrom);
  anpNodeTo   = GetNodeData(nNodeTo);
  DIASSERT(anpNodeTo);

  // perhaps we support other combinations but this should be tested
  //DIASSERT((DiBool)TRUE == anpNodeFrom->bIsLooped && (DiBool)TRUE == anpNodeTo->bIsLooped);

  // get current transaction
  atpTrans = (DiAnimFlTransaction *)GetTransactionData(nCurTrans, nCurSubTrans);
  DIASSERT(atpTrans);

  AGTrace( "TR_UPD: dT=%5.3lf, targetNode=%i[%s], trSpeed=%5.3lf. TRANS (ID=%i, VP=%5.3lf,from=%i[%s],to=%i[%s])",
           rDt, GetTargetNode(), GetNodeNameByID(GetTargetNode()), atpTrans->GetSpeed(), GetCurTransaction(), atpTrans->GetPrevPar(),  GetPrevNode(), GetNodeNameByID(GetPrevNode()), GetNextNode(), GetNodeNameByID(GetNextNode()));

  // init local data
  bNodeFromIsWaiting = FALSE; // currently not used
  bNodeToIsWaiting   = FALSE; // currently not used
  usState            = DIANGR_UPDATE_NA;
  rSavedDt           = rDt;

  DiBool savedNeedElementEnterCallback = bNeedElementEnterCallback;

  usState = UpdateTransactionInt(atpTrans, DIANGR_FLTRANS_TRANSACTION, rDt);

  DiFloat delta = rSavedDt - rDt;
  
  // update node without changing anything else
  if (atpTrans->nUpdFlags & DIANGR_FLKIND_FIRST)
  {
    UpdateOnlyOneNode(nNodeFrom, nNodeFrom, delta, bNodeFromIsWaiting, DIANGR_FLTRANS_NODE1);
  }
  if (atpTrans->nUpdFlags & DIANGR_FLKIND_SECOND)
  {
    if ( savedNeedElementEnterCallback && !bNeedElementEnterCallback )
    {
      ResetCallbacksOnParFlag(DIANGR_NODE, anpNodeTo);
      bNeedElementEnterCallback = TRUE;
    }
    UpdateOnlyOneNode(nNodeTo, nNodeTo, delta, bNodeToIsWaiting, DIANGR_FLTRANS_NODE2);
    if ( usState == DIANGR_UPDATE_NODE_SETTING )
      usState = DIANGR_UPDATE_NODE_SETTING2;
  }

  DIRETURN(usState);
}


DiUInt32 DiAnimGraph::SelectNextNodeByProbability(DiUInt32 nNodeID, DiAnimNode *anpCurNode)
{
  DIASSERT(anpCurNode->IsSwitcher());

  AGTrace( "AG:%x, SelByProb. NodeID: %i", this, nNodeID);

  class Selecter : public INeiFunctor
  {
    int randProb;
    DiUInt32 res;
    DiUInt32 nNodeID;
    DiAnimGraph* ag;
  public:
    Selecter( DiUInt32 nNodeID, DiAnimGraph* ag ) 
    : randProb( rand()%100 ), res(DIANGR_NO_SUCH_ELEMENT), nNodeID(nNodeID), ag(ag)
    {}
    virtual void operator()( DiUInt32 nodeId )
    {
      if ( res == DIANGR_NO_SUCH_ELEMENT )
      {
        DiUInt32 nEdgeID = ag->GetMTransactionID(nNodeID, nodeId);
        DiAnimMTransaction *mtpEdge = ag->GetTransactionData(nEdgeID);
        randProb -= mtpEdge->GetProbability();
        if (randProb < 0)
        {
          res = nodeId;
        }
      }
    }
    DiUInt32 GetRes() const { return res; }
  } sl(nNodeID, this);

  ForAllNeighbours(nNodeID, &sl);
  DiUInt32 res = sl.GetRes();
  if ( res == GetCurNodeUnsafe() )
  {
    Selecter sl2( nNodeID, this );
    ForAllNeighbours(nNodeID, &sl2);
    res = sl2.GetRes();
  }
  NI_VERIFY( res != DIANGR_NO_SUCH_ELEMENT, NStr::StrFmt("SelectNextNodeByProbability: can not find next node for %s", GetNodeNameByID(nNodeID) ), return anpCurNode->GetDefNextNode() );
  return res;
}

/**
 * This function sets node params after transaction
 *
 * @memo    Set node active
 * @return  next state
 * @param   rDt           time for update
 */
DiAnGrUpdateState DiAnimGraph::UpdateCurNodeSetting( DiBool isNeedResetCallbacks )
{
  DiAnimNode  *anpCurNode;
  DiBool      bSetDefaultNextNode;

  DIASSERT(DIANGR_NO_SUCH_ELEMENT == nCurNode);
  DIASSERT(nNextNode != DIANGR_NO_SUCH_ELEMENT);

  AGTrace( "CurNodeSettting ENTER: curN=%i, nxtN=%i, prvN=%i, curT=%i, PathSpecified=%i", nCurNode, nNextNode, nPrevNode, nCurTrans, bPathSpecified);

  // set node params
  nCurNode = nNextNode;
  anpCurNode = GetNodeData(nCurNode);
  
  bIsCurNodeMacronode = anpCurNode->bIsThisMacronode;
  nCurTrans           = DIANGR_NO_SUCH_ELEMENT;
  nCurSubTrans        = DIANGR_NO_SUCH_ELEMENT;

  // get next node

  bSetDefaultNextNode = TRUE;
  // if we have some path to go than use it
  if (bPathSpecified && gpPath.nCurIdxInPath < (gpPath.nPathLength - 2))
  { 
    // check: nNode should be under (CurIdx + 1)
    //DIASSERT(gpPath.npPath[gpPath.nCurIdxInPath + 1] == nCurNode);
    gpPath.nCurIdxInPath++;
    nNextNode           = gpPath.npPath[gpPath.nCurIdxInPath + 1];
    bSetDefaultNextNode = FALSE;

    if (gpPath.nPathLength - 2 == gpPath.nCurIdxInPath)
    {
      gpPath.nTargetNode = DIANGR_NO_SUCH_ELEMENT;
      bPathSpecified     = FALSE;
    }
  }

  if (bSetDefaultNextNode)
  {
    bIsForced = FALSE;
    if (!anpCurNode->IsSwitcher())
    {
      // set default next node 
      nNextNode = anpCurNode->nDefNext;
    }
    else
    {
      // select next node by probability
      nNextNode = SelectNextNodeByProbability(nCurNode, anpCurNode);
    }
    
  }

  if ( isNeedResetCallbacks )
  {
    bNeedElementEnterCallback = TRUE;

    // Node has started => clear callbacks flag
    ResetCallbacksOnParFlag(DIANGR_NODE, anpCurNode);
  }

  AGTrace( "CurNodeSettting LEAVE: curN=%i, nxtN=%i, prvN=%i, curT=%i, PathSpecified=%i", nCurNode, nNextNode, nPrevNode, nCurTrans, bPathSpecified);

  DIRETURN(DIANGR_UPDATE_NODE_ACTIVE);
}

/**
 * This function updates given node
 *
 * @memo    Update cuurent node
 * @return  next state
 * @param   rDt   time left for update
 */
DiAnGrUpdateState DiAnimGraph::UpdateNode(DiUInt32 nNodeCur, DiUInt32 nNodeNext, DiFloat &rDt, 
                                          DiAnGrFlTransParam tpParam)
{
  DiAnGrUpdateState usState;
  DiInt32           nRes;
  DiAnimNode        *anpNode;
  DiBool            bWrapped;
  DiUInt32          nCallFlags;

  anpNode = GetNodeData(nNodeCur);

  DIASSERT(anpNode);

  AGTrace("N_UPD(dt=%10.7lf): CurN:%i(%s), NxtN:%i(%s)", rDt, nNodeCur, GetNodeNameByID(nNodeCur), nNodeNext, GetNodeNameByID(nNodeNext));

  // save entrance VPar
  anpNode->SetPrevPar(anpNode->GetVPar());

  UpdateNodeSequences(nNodeCur);

  DIASSERT(rDt >= 0.0f);
  
  // set flags
  nCallFlags = DIANGR_CF_UPDATE_BEGIN;

  if (this->bNeedElementEnterCallback)
    nCallFlags |= DIANGR_CF_ELEMENT_ENTER;

  nRes = CallCallbacks(nCallFlags, DIANGR_NODE, rDt,
                       anpNode, tpParam);
  DIASSERT(rDt >= 0.0f);
  if (nRes != DIOBJMSG_CONTINUE)
  {
    rDt = 0.0f;
    AGTrace("Stopping update after pre-update callbacks!");
    DIRETURN(DIANGR_UPDATE_END);
  }

  // update node
  bWrapped = FALSE;
  DIASSERT(rDt >= 0.0f);

  int savedNextNode = this->nNextNode;

  //if(tpParam == DIANGR_FLTRANS_NA)
  {
    usState = UpdateNodeActive(nNodeCur, this->nNextNode, rDt, bWrapped, tpParam);
  }
  //else
  {
    //usState = UpdateNodeActiveLooped(nNodeCur, rDt, bWrapped);
  }

  DIASSERT(rDt >= 0.0f);
    
  UpdateNodeSequences(nNodeCur);
  
  DIASSERT(rDt >= 0.0f);

  // set flags
  nCallFlags = DIANGR_CF_UPDATE_END;
  if (this->bNeedElementLeaveCallback)    
    nCallFlags |= DIANGR_CF_ELEMENT_LEAVE;

  nRes = CallCallbacks(nCallFlags, DIANGR_NODE, rDt,
                       anpNode, tpParam);
  DIASSERT(rDt >= 0.0f);
  if (nRes != DIOBJMSG_CONTINUE)
  {
    rDt = 0.0f;
    AGTrace("Stopping update after post-update callbacks!");
    DIRETURN(DIANGR_UPDATE_END);
  }

  if (savedNextNode != int(this->nNextNode))
  {
    // Next node changed!!!
    //float forcedDt = rDt;
    AGTrace("RE-updating node %i[%s]because in post-update callback next node has changed from %i[%s] to %i[%s], rDt = %8.5lf", 
            nCurNode, GetNodeNameByID(nCurNode), savedNextNode, GetNodeNameByID(savedNextNode), nNextNode, GetNodeNameByID(nNextNode), rDt);
    usState = UpdateNodeActive(nNodeCur, this->nNextNode, rDt, bWrapped, tpParam);

    // Do not call callback now!
  }

  // check whether node was wrapped
  if (usState == DIANGR_UPDATE_NODE_ACTIVE)
    WrapCurParIfNeeded(bWrapped, anpNode, nNodeCur);  

  // clear callbacks flag if node was wrapped
  if (bWrapped)
  {
    ResetCallbacksOnParFlag(DIANGR_NODE, anpNode);
  }

  DIRETURN(usState);
}

/**
 * @doc This function is internal function for transaction update
 *
 * @memo    Internal function for transaction's update
 * @return  update-state
 * @param   [in/out] atpTrans    pointer to transaction that needs update
 * @param   [in]     tpParam     flag of FLTransaction
 * @param   [in]     rDt         time for update
 * @author  EugBel
 */
DiAnGrUpdateState DiAnimGraph::UpdateTransactionInt(DiAnimFlTransaction *atpTrans, 
                                                    DiAnGrFlTransParam tpParam,
                                                    DiFloat &rDt)
{
  DiInt32           nRes;
  DiAnGrUpdateState usState;
  DiUInt32          nCallFlags;

  DIFUNCTION("UpdateTransactionInt");
  
  // save current VPar
  atpTrans->SetPrevPar(this->GetCurVPar());

  // set flags
  nCallFlags = DIANGR_CF_UPDATE_BEGIN;

  if (this->bNeedElementEnterCallback)
    nCallFlags |= DIANGR_CF_ELEMENT_ENTER;

  nRes = CallCallbacks(nCallFlags, DIANGR_FLTRANSACTION, rDt,
                       atpTrans, tpParam);
  if (nRes != DIOBJMSG_CONTINUE)
  {
    rDt = 0.0f;
    DIRETURN(DIANGR_UPDATE_END);
  }

  // update transaction
  usState = UpdateTransactionActive(rDt);
   
  // set flags
  nCallFlags = DIANGR_CF_UPDATE_END;
  if (this->bNeedElementLeaveCallback)    
    nCallFlags |= DIANGR_CF_ELEMENT_LEAVE;

  nRes = CallCallbacks(nCallFlags, DIANGR_FLTRANSACTION, rDt,
            atpTrans, tpParam);
  if (nRes != DIOBJMSG_CONTINUE)
  {
    rDt = 0.0f;
    DIRETURN(DIANGR_UPDATE_END);
  }

  DIRETURN(usState);
} // end of UpdateTransactionInt

// This function returns time till nearest callback on Parameter or rFullUpdateTime if there are no callbacks earlier than rFullUpdateTime
DiFloat DiAnimGraph::SplitTimeTillNextClbOnParInElement(DiFloat rDtLeft)
{
  if (0.0f == rDtLeft)
    return 0.0f;

  DiFloat timeTillClb = rDtLeft;

  // get current graph element
  DiAnimGraphElems geElem = GetCurElemType();

  if (DIANGR_FLTRANSACTION == geElem)
  {
    // get transaction data
  }

  // analyze graph state
  if (DIANGR_NODE == geElem || DIANGR_MACRONODE == geElem )
  {
    // get node data
    DiAnimNode *pNode = GetNodeData(GetCurNode());

    timeTillClb = GetTimeTillNearestClbOnPar(pNode->GetClbStorage(), pNode->GetVPar(), rDtLeft, pNode->GetSpeed() * GetGraphSpeedCoeff());

//     if (nNextNode != nCurNode)
//     {
//       DiUInt32 nEdgeID = GetEdgeID(nCurNode, nNextNode);
//       if (diGR_NO_SUCH_ELEMENT != nEdgeID)
//       {
//         DiFloat start, stop;
//         GetTransactionData(nEdgeID, 0)->GetStartStopParams(start, stop);
//         DiFloat timeTillExit = start - pNode->GetVPar();
//         if (timeTillExit > 0.f && timeTillExit < )
//       }
//     }
    if (timeTillClb < rDtLeft)
      AGTrace("Splitting update dT. Was: %10.7lf, splitted into %10.7lf (till callback) and %10.7lf", rDtLeft, timeTillClb, rDtLeft - timeTillClb);

    rDtLeft -= timeTillClb;

  }
//   else
//   {
//     timeTillClb = (1.0f - GetCurLinTransactionPar())/(GetTransactionData(GetCurTransaction())->GetSpeed() * GetGraphSpeedCoeff());
//   }


  
  NI_VERIFY(rDtLeft >= 0.0f, "Calculations failed!", rDtLeft = 0.0f);
  NI_VERIFY(timeTillClb > 0.0f, "Calculations failed(2)", timeTillClb = rDtLeft);

  return timeTillClb;
}

/**
 * This function updates animation graph
 *
 * @memo    AnimGraph update
 * @return  TRUE on success, FALSE otherwise
 * @param   rDt   time change
 * @author  EugBel
 */
DiBool DiAnimGraph::Update(DiFloat rUpdateDt)
{
  NI_PROFILE_FUNCTION;

  DIASSERT(rUpdateDt >= 0.0f);
  AGTrace("//////Update(%8.5lf)", rUpdateDt);

  if ( freezed )
  {
    rUpdateDt = 0.0f;
  }

  DiAnGrUpdateState usState;

  DiFloat rDtLeft = rUpdateDt;

  while ( callBacksToDel.size() )
  {
    typedef nstl::list<DiAnGrClbStorageElem>::iterator It;
    for ( It it = sepClbArray->begin(); it != sepClbArray->end(); it++ )
    {
      if ( it.operator ->() == callBacksToDel[0] )
      {
        it = sepClbArray->erase( it );
      }
    }
    callBacksToDel.eraseByIndex(0);
  }

  do
  {
    DiFloat rDt = SplitTimeTillNextClbOnParInElement(rDtLeft);
    NI_ASSERT(rDt <= rDtLeft, "AG logic");
    rDtLeft -= rDt;
    NI_ASSERT(rDtLeft >= 0.0f, "AG logic(2)");

    usState = DIANGR_UPDATE_BEGIN;
    while (usState != DIANGR_UPDATE_END)
    {
      switch(usState)
      {
        case DIANGR_UPDATE_BEGIN:
        {
          // set next state
          DIASSERT(rDt >= 0.0f);
          usState = UpdateBegin();
          DIASSERT((nCurNode != DIANGR_NO_SUCH_ELEMENT && usState == DIANGR_UPDATE_NODE_ACTIVE) ||
                   (nCurTrans != DIANGR_NO_SUCH_ELEMENT && nCurSubTrans != DIANGR_NO_SUCH_ELEMENT &&
                    (usState == DIANGR_UPDATE_FLTRANSACTION_ACTIVE )));
        
          DIASSERT(rDt >= 0.0f);
          break;
        }
        case DIANGR_UPDATE_END:
        {
          // nothing to do
          DIASSERT(0.0f == rDt); // some function has forgotten to set rDt = 0
          break;
        }
        case DIANGR_UPDATE_NODE_SETTING:
        {
          DIASSERT(rDt >= 0.0f);
          // set node
          usState = UpdateCurNodeSetting( true );
          // check current logic
          DIASSERT(DIANGR_UPDATE_NODE_ACTIVE == usState);
          DIASSERT(rDt >= 0.0f);

          // force new search for callbacks-on-par in new node
          rDtLeft += rDt;
          rDt = 0.0f;
          usState = DIANGR_UPDATE_END;
          break;
        }
        case DIANGR_UPDATE_NODE_SETTING2:
          {
            DIASSERT(rDt >= 0.0f);
            // set node
            usState = UpdateCurNodeSetting( false );
            // check current logic
            DIASSERT(DIANGR_UPDATE_NODE_ACTIVE == usState);
            DIASSERT(rDt >= 0.0f);

            // force new search for callbacks-on-par in new node
            rDtLeft += rDt;
            rDt = 0.0f;
            usState = DIANGR_UPDATE_END;
            break;
          }
        case DIANGR_UPDATE_NODE_ACTIVE:
        {
          DIASSERT(rDt >= 0.0f);
          usState = UpdateNode(this->nCurNode, this->nNextNode, rDt, DIANGR_FLTRANS_NA);
          DIASSERT(DIANGR_UPDATE_NODE_ACTIVE == usState ||
                   DIANGR_UPDATE_TRANSACTION_SETTING == usState ||
                   DIANGR_UPDATE_END == usState);
          DIASSERT(rDt >= 0.0f);
          break;
        }
        case DIANGR_UPDATE_TRANSACTION_SETTING:
        {
          DIASSERT(rDt >= 0.0f);
          // set transaction
          usState = UpdateTransactionSetting();
          DIASSERT( DIANGR_UPDATE_FLTRANSACTION_ACTIVE == usState );
          DIASSERT(rDt >= 0.0f);
          break;
        }

        case DIANGR_UPDATE_FLTRANSACTION_ACTIVE:
        {
          DIASSERT(rDt >= 0.0f);
          usState = UpdateFlTransaction(rDt);
          DIASSERT(DIANGR_UPDATE_FLTRANSACTION_ACTIVE == usState ||
                    DIANGR_UPDATE_NODE_SETTING == usState ||
                    DIANGR_UPDATE_NODE_SETTING2 == usState ||
                   DIANGR_UPDATE_END == usState);

          DIASSERT(rDt >= 0.0f);
          break;
        }
        default:
        {
          DIASSERT_ALOOF_CODE(GetDBFileName());
        }
      }
    }
    DIASSERT(0.0f == rDt);

    DIASSERT(DIANGR_UPDATE_END == usState);
  } while ( rDtLeft > DIANGR_MIN_DT );


  DIASSERT(fabs(rDtLeft) < DIANGR_MIN_DT);

  // pass update into animation system
  SetAnimation();

#ifdef DIANGR_SCREEN_DEBUG_GENERAL
  DebugUpdateInfo();
#endif;

  DIRETURN(TRUE);
} // end of Update


/**
 * This function is used to update only one node. If it is looped than it
 * could be wrapped. If not - it will stop at the end.
 *
 * @memo    Update particular node
 * @return  TRUE on success, FALSE otherwise
 * @param   nNodeToUpdate
 * @param   nNodeNext
 * @param   rDt             time for update
 * @param   bIsNodeWaiting
 * @param   tpParam
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiBool DiAnimGraph::UpdateOnlyOneNode(DiUInt32 nNodeToUpdate, DiUInt32 nNodeNext, 
                                      DiFloat rDt, DiBool &bIsNodeWaiting,
                                      DiAnGrFlTransParam tpParam)
{
  DiAnGrUpdateState usState;

  do 
  {
    usState = UpdateNode(nNodeToUpdate, nNodeNext, rDt, tpParam);
    // check logic
    DIASSERT(DIANGR_UPDATE_END == usState || DIANGR_UPDATE_NODE_ACTIVE == usState ||
             DIANGR_UPDATE_TRANSACTION_SETTING == usState);
    
    // suppress update if we need to go into transaction
    if (DIANGR_UPDATE_TRANSACTION_SETTING == usState)
    {
      bIsNodeWaiting = TRUE;
      usState            = DIANGR_UPDATE_END;
    }
    
  } while (usState != DIANGR_UPDATE_END);

  return TRUE;
}

///eugbelNSCENE///} // end of namespace NScene
