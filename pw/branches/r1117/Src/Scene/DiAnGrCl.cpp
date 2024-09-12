/*
 * @file    DiAnGrCl.cpp
 * @memo    DiAnimGraph functions that deal with callbacks
 * @author  EugBel
 * @date    04.02.2004
 * @prefix  DiAnGr
 * @header  DiAnGr.h
 * @library skeleton.lib
 */

// *******************************************************************
// includes
#include "stdafx.h"
#include "DiAnGr.h"

#ifdef DIANGR_SCREEN_DEBUG_ADVANCED
  #include <string.h>
  #include <stdio.h>
#endif

///eugbelNSCENE///namespace NScene {

// *******************************************************************
// defines


// *******************************************************************
// local data

// *******************************************************************
// functions

/**
 * This function just creates one structure from multiple params (this is a constructor actually)
 *
 * @memo    Create callback parameters (this is a constructor actually)
 * @return  none
 * @library skeleton.lib
 * @author  dim0n (base on EugBel's FillParams)
 * @see     DiAnGrCallbackParams
 */
DiAnGrCallbackParams::DiAnGrCallbackParams(DiUInt32 nCallFlags, DiAnimGraphElems geElement,
                                           DiFloat rTimeLeftForUpdate, DiVoid *vpElemPtr, 
                                           DiVoid *vpUserData, DiAnGrFlTransParam tpParam)
{
  this->nCallFlags          = nCallFlags;
  this->geElement           = geElement;
  this->rTimeLeftForUpdate  = rTimeLeftForUpdate;
  this->vpUserData          = vpUserData;
  this->tpParams            = tpParam;

  switch(geElement)
  {
  case DIANGR_NODE:
    {
      anpNode = (DiAnimNode *)vpElemPtr;
      break;
    }
  case DIANGR_FLTRANSACTION:
    {
      atpTrans = (DiAnimFlTransaction *)vpElemPtr;
      break;
    }
  case DIANGR_MACRONODE:
    {
      anmpMacronode = (DiAnimMacronode *)vpElemPtr;
      break;
    }
  default:
    {
      DIASSERT_ALOOF_CODE("-"); 
    }
  }
}

/**
 * This function registers user callback with user name. This name will be used
 *          in screen debugging mode. Available ONLY with DIANGR_SCREEN_DEBUG_ADVANCED define
 * @memo    Register callback with it's name
 * @return  TRUE on success, FALSE otherwise
 * @param   cpName   
 * @param   geElem
 * @param   nID
 * @param   fpCallback
 * @param   nCallFlags
 */
#ifdef DIANGR_SCREEN_DEBUG_ADVANCED
DiAnGrClbStorageElem *  DiAnimGraph::RegisterCallbackWithName(DiTChar *cpName, DiAnimGraphElems geElem, DiUInt32 nID,
                                             DiAnGrCallback fpCallback, 
                                             DiUInt32 nCallFlags, 
                                             DiVoid *vpUserData,
                                             DiFloat rExactParam,
                                             DiFloat probability)
{
  // name given by the user can't contain internal distinguisher
  DIASSERT(NULL == strstr(cpName,DIANGR_INT_CALLBACK_PREFIX));  

  return RegisterCallbackInt(cpName, geElem, nID, fpCallback, nCallFlags,
                             vpUserData, rExactParam, probability);
}
#endif  
  
/*
 *	Just function mapping
 */
DiAnGrClbStorageElem *  DiAnimGraph::RegisterCallback(DiAnimGraphElems geElem, DiUInt32 nID,
                                       DiAnGrCallback fpCallback, 
                                       DiUInt32 nCallFlags, 
                                       DiVoid *vpUserData,
                                       DiFloat rExactParam,
                                       DiFloat probability)
{
  DIASSERTPTR(fpCallback);

#ifdef DIANGR_SCREEN_DEBUG_ADVANCED
  DiTChar *cpName;
  DiInt32 nSize;
  
  // need to transform address of callback to string
  // To understand that it is internal name let "!" be the first char
  nSize = 12; // "_0x12345678" -> (11+ 1) chars
  cpName = (DiTChar *)DiMemAllocate(nSize * sizeof(DiTChar));
  DIASSERTPTR(cpName);
  sprintf_s(cpName, nSize, "%s0x%p",DIANGR_INT_CALLBACK_PREFIX,fpCallback);
  return RegisterCallbackInt(cpName, geElem, nID, fpCallback, nCallFlags,
                             vpUserData, rExactParam, probability);
#else
  
  // just call sub-function
  return RegisterCallbackInt(geElem, nID, fpCallback, nCallFlags,
                             vpUserData, rExactParam, probability);
#endif
}

void DiAnimGraph::ForceLeaveNodeCallbacks(int nodeIdx)
{
    DiAnimNode *node = GetNodeData(nodeIdx);
    NI_VERIFY(node, "Wrong node index specified for NodeLeave callback", return; );
    
    DiAnimGraphElems geElement(DIANGR_NODE);
    if (node->IsMacronode())
      geElement = DIANGR_MACRONODE;

    DiInt32 nRes                  = DIOBJMSG_CONTINUE;
    DiFloat dT                    = 0.0f;
    DiFloat elemVP                = node->GetVPar();
    DiAnGrClbStorageElem *sepClb  = node->GetClbStorage();

    while ((sepClb != NULL) && (DIOBJMSG_CONTINUE == nRes))
    {
      DIASSERTPTR(sepClb->fpCallback);

      if (sepClb->nCallFlags & DIANGR_CF_ELEMENT_LEAVE)
      {
        AGTrace("Calling callback_%x on NodeLeave (node=%i[%s], ElementVPar=%10.7f)", sepClb->fpCallback, nodeIdx, GetNodeNameByID(nodeIdx), elemVP);
        nRes = sepClb->fpCallback(DiAnGrCallbackParams(DIANGR_CF_ELEMENT_LEAVE,  geElement, dT, node, sepClb->vpUserData, DIANGR_FLTRANS_NA));
      }
      sepClb = sepClb->sepNext;
    }
}

DiBool DiAnimGraph::RegisterCallbackForAllSameMarkers(const string &markerName, DiAnGrCallback fpCallback, 
                                                      DiVoid *vpUserData, DiFloat probability)
{
  bool markerExists(false);
  bool ok(false);
  int  startIdx(0), foundIdx(-1);
  DiAnGrMarker *marker(NULL);

  while (true)
  {
    marker = FindMarkerByName(markerName, &startIdx, &foundIdx);
    markerExists = markerExists || (marker != NULL);
    if (NULL == marker)
      break;

    ok = RegisterCallback(*marker, fpCallback, vpUserData, probability);
    NI_ASSERT(ok, "Failed to register callback on marker");
    startIdx = foundIdx + 1;
  }

  //NI_ASSERT(markerExists, "Wrong marker name specified");
  return markerExists;
}

DiAnGrClbStorageElem *DiAnimGraph::RegisterCallback(const DiAnGrMarker &marker, DiAnGrCallback fpCallback, 
                                     DiVoid *vpUserData, DiFloat probability)
{
  DiAnimGraphElems geType(DIANGR_NA);
  DiUInt32         elemID(DIANGR_NO_SUCH_ELEMENT);

  // get information from marker and then use native AnimGraph callback
  switch (marker.owner)
  {
  case EditorGraphParamAddress::VT_NODE:
    geType = DIANGR_NODE;
    elemID = marker.nodeIdx;
    break;
  case EditorGraphParamAddress::VT_TRANSACTION:
    geType = DIANGR_FLTRANSACTION;
    elemID = marker.transIdx;
    break;
  default: DIASSERT_ALOOF_CODE(GetDBFileName()); // unsupported marker for callback!
  }

  DiAnGrClbStorageElem *pClb = RegisterCallback( geType, elemID, fpCallback, DIANGR_CF_EXACT_PARAM, 
                                vpUserData, marker.virtPar, probability);
  DIASSERT(pClb);

  return pClb;
}

  
/**
 * This function registers callback for node/Macronode/transaction
 *
 * @memo    Register callbsck
 * @return  TRUE on success, FALSE otherwise
 * @param   geElem     type of graph element: node/Macronode/transaction
 * @param   nID        ID of element, given by AddNode/AddEdge
                       In case of geElem == DIANGR_ENTIREGRAPH, ID should be DIANGR_NO_SUCH_ELEMENT
 * @param   fpCallback pointer to function
 * @author  EugBel
 */
#ifdef DIANGR_SCREEN_DEBUG_ADVANCED
DiAnGrClbStorageElem *DiAnimGraph::RegisterCallbackInt(DiTChar *cpName,
                                        DiAnimGraphElems geElem, DiUInt32 nID,
                                        DiAnGrCallback fpCallback, 
                                        DiUInt32 nCallFlags, DiVoid *vpUserData,
                                        DiFloat rExactParam,
                                        DiFloat probability)
#else
DiAnGrClbStorageElem *DiAnimGraph::RegisterCallbackInt(DiAnimGraphElems geElem, DiUInt32 nID,
                                        DiAnGrCallback fpCallback, 
                                        DiUInt32 nCallFlags, DiVoid *vpUserData,
                                        DiFloat rExactParam,
                                        DiFloat probability)
#endif
{
  DiAnimNode             *pNode;
  DiAnimMacronode        *pMacronode;
  DiAnimMTransaction     *pEdge;
  DiAnGrClbStorageElem   *sepCurClbStorage = NULL;

  DIFUNCTION("RegisterCallbackInt");

  if (nNumRegisteredCallbacks >= DIANGR_MAX_NUM_CALLBACKS)
  {
    DIASSERT_ALOOF_CODE(GetDBFileName()); // increase value of DIANGR_MAX_NUM_CALLBACKS
    return FALSE;
  }

#ifdef _DEBUG
  if ((nCallFlags & DIANGR_CF_EXACT_PARAM) == 0)
    rExactParam = -1.0f;
#endif // _DEBUG

  switch(geElem)
  {
    case DIANGR_NODE:
      AGTrace("Registering callback %x for node %i(%10s). ExactPar: %3s(% 7.5lf) | ElemEnter: %3s | ElemLeave: %3s | UPD_BEGIN: %3s | UPD_END: %3s | UPD_ALWAYS: %3s", 
              fpCallback, nID, GetNodeNameByID(nID), 
              (nCallFlags & DIANGR_CF_EXACT_PARAM)    != 0 ? "yes" : "no", rExactParam,
              (nCallFlags & DIANGR_CF_ELEMENT_ENTER)  != 0 ? "yes" : "no",
              (nCallFlags & DIANGR_CF_ELEMENT_LEAVE)  != 0 ? "yes" : "no", 
              (nCallFlags & DIANGR_CF_UPDATE_BEGIN)   != 0 ? "yes" : "no", 
              (nCallFlags & DIANGR_CF_UPDATE_END)     != 0 ? "yes" : "no", 
              (nCallFlags == DIANGR_CF_UPDATE_ALWAYS)      ? "yes" : "no");

      DIASSERT(nID < GetNumNodes());
      pNode             = GetNodeData(nID);
      DIASSERTPTR(pNode);

      #ifdef DIANGR_SCREEN_DEBUG_ADVANCED
        pNode->sepClbStorage = FillCallbackStorage(pNode->sepClbStorage, vpUserData, fpCallback, 
                                                   probability, nCallFlags, cpName, rExactParam, &sepCurClbStorage);
      #else
        pNode->sepClbStorage = FillCallbackStorage(pNode->sepClbStorage, vpUserData, fpCallback, 
                                                   probability, nCallFlags, NULL, rExactParam, &sepCurClbStorage);
      #endif
      break;

    case DIANGR_MACRONODE:
      AGTrace("Registering callback %x for MACROnode %i(%s) with flags %i (exactPar? %i)", fpCallback, nID, GetNodeNameByID(nID), nCallFlags, (nCallFlags & DIANGR_CF_EXACT_PARAM));

      DIASSERT(nID < GetNumNodes());
      pMacronode             = (DiAnimMacronode *)GetNodeData(nID);
      DIASSERTPTR(pMacronode);
      
      #ifdef DIANGR_SCREEN_DEBUG_ADVANCED
        pMacronode->sepClbStorage = FillCallbackStorage(pMacronode->sepClbStorage, vpUserData, 
                                                        fpCallback, probability, nCallFlags, cpName, rExactParam, &sepCurClbStorage);
      #else
        pMacronode->sepClbStorage = FillCallbackStorage(pMacronode->sepClbStorage, vpUserData, 
                                                        fpCallback, probability, nCallFlags, NULL, rExactParam, &sepCurClbStorage);
      #endif
    break;

    case DIANGR_FLTRANSACTION:
      AGTrace("Registering callback %x for FLtransaction %i with flags %i (exactPar? %i)", fpCallback, nID, nCallFlags, (nCallFlags & DIANGR_CF_EXACT_PARAM));

      DIASSERT(nID < GetNumEdges());
      pEdge             = GetTransactionData(nID);
      DIASSERT(pEdge);
      #ifdef DIANGR_SCREEN_DEBUG_ADVANCED
        pEdge->sepClbStorage = FillCallbackStorage(pEdge->sepClbStorage, vpUserData, fpCallback, 
                                                   probability, nCallFlags, cpName, rExactParam, &sepCurClbStorage);
      #else
        pEdge->sepClbStorage = FillCallbackStorage(pEdge->sepClbStorage, vpUserData, fpCallback, 
                                                   probability, nCallFlags, NULL, rExactParam, &sepCurClbStorage);
      #endif
    break;
    
    case DIANGR_ENTIREGRAPH:
      AGTrace("Registering callback %x for entire graph with flags %i", fpCallback, nCallFlags);

      DIASSERT(DIANGR_NO_SUCH_ELEMENT == nID);

      // graph can't have callback on parameter
      DIASSERT(0 == (nCallFlags & DIANGR_CF_EXACT_PARAM));
      #ifdef DIANGR_SCREEN_DEBUG_ADVANCED
        this->sepClbStorage = FillCallbackStorage(this->sepClbStorage, vpUserData, fpCallback, 
                                                  probability, nCallFlags, cpName, rExactParam, &sepCurClbStorage);
      #else
        this->sepClbStorage = FillCallbackStorage(this->sepClbStorage, vpUserData, fpCallback, 
                                                  probability, nCallFlags, NULL, rExactParam, &sepCurClbStorage);
      #endif
    break;

    default:
      // some unsupported type of graph element
      DIASSERT_ALOOF_CODE(GetDBFileName());
      DIRETURN(sepCurClbStorage);
  }

  DIRETURN(sepCurClbStorage);
} // end of RegisterCallbackInt

void DiAnimGraph::clearCallback(DiAnGrClbStorageElem *sepClb)
{
  AGTrace("Cleaning callback %x", sepClb->fpCallback);

  DIASSERT(sepClb != NULL);

#ifdef DIANGR_SCREEN_DEBUG_ADVANCED
  if (sepClb->cpName != NULL)
  {
    DiMemFree(sepClb->cpName);
    sepClb->cpName = NULL;
  }
#endif
  sepClb->fpCallback = NULL;
  sepClb->nCallFlags = 0;
  sepClb->nPriority  = DIANGR_INVALID_PRIORITY;
  sepClb->rClbParam  = DIANGR_INVALID_FLOAT_VALUE;
  sepClb->sepNext    = NULL;
  sepClb->vpUserData = NULL;
  sepClb->bIsClbCalledSinceElemStarted = FALSE;
  callBacksToDel.push_back( sepClb );
}

static int _nClbDeletes = 0;
DiAnGrClbStorageElem::~DiAnGrClbStorageElem()
{
  nCallFlags = 0;
  rClbParam = DIANGR_INVALID_FLOAT_VALUE;
  bIsClbCalledSinceElemStarted = FALSE;
  nPriority = DIANGR_INVALID_PRIORITY;
  fpCallback = NULL;
  vpUserData = NULL;
  sepNext    = NULL;
  _nClbDeletes++;
}
DiInt32 DiAnimGraph::GetNumRegisteredCallbacks()
{
  return nNumRegisteredCallbacks;
}

DiAnGrClbStorageElem  *DiAnimGraph::UnregisterCallbackInElemByClb(DiAnGrClbStorageElem *sepRoot, DiAnGrClbStorageElem *sepDel, DiAnGrClbStorageElem *_sepPrev)
{
  DiAnGrClbStorageElem *sepPrev = _sepPrev;
  DiAnGrClbStorageElem *sepTemp;
  if(sepPrev == NULL)
  {
    sepTemp = sepRoot;
    while(sepTemp != NULL && sepTemp != sepDel)
    {
      sepPrev = sepTemp;
      sepTemp = sepTemp->sepNext;
    }
  }

  // clear callback but save pointer to next
  DiAnGrClbStorageElem *sepSave = sepDel->sepNext;
  clearCallback(sepDel);

  // Do not change number of registered callbacks - currently array of callbacks can only add new callbacks!
  this->nNumRegisteredCallbacks--;
  DIASSERT(this->nNumRegisteredCallbacks >= 0);

  if (sepDel == sepRoot)
  {
    return sepSave;
  }
  else
  {
    NI_VERIFY(sepPrev != NULL, "Logic", return sepRoot);
    sepPrev->sepNext = sepSave;
    return sepRoot;
  }

}
DiAnGrClbStorageElem *DiAnimGraph::UnregisterCallbackInElem(DiAnGrClbStorageElem *sepRoot, DiAnGrCallback fpCallback, DiVoid *userDataIfYouKnowIt)
{
  AGTrace("Unregistering callback internal %x (UDifKnown: %x)", fpCallback, userDataIfYouKnowIt);

  DiAnGrClbStorageElem *sepTemp, *sepPrev;
  DIASSERT(sepRoot != NULL);

  sepTemp = sepRoot;
  sepPrev = NULL;
  

  if (userDataIfYouKnowIt != NULL)
  {
    //count elements
    int nElems = 0;
    while(sepTemp != NULL)
    {
      if(sepTemp->fpCallback == fpCallback && sepTemp->vpUserData == userDataIfYouKnowIt)
      {
        nElems++;
      }
      sepTemp = sepTemp->sepNext;
    }
    NI_ASSERT(nElems == 1, "The same callback was registered for one node twice, yet deletion does not specify valid user data resulting random deletion.");
    sepTemp = sepRoot;

    while(sepTemp != NULL && (sepTemp->fpCallback != fpCallback || sepTemp->vpUserData != userDataIfYouKnowIt))
    {
      sepPrev = sepTemp;
      sepTemp = sepTemp->sepNext;
    }
  }
  else
  {
    //count elements
    int nElems = 0;
    while(sepTemp != NULL)
    {
      if(sepTemp->fpCallback == fpCallback)
      {
        nElems++;
      }
      sepTemp = sepTemp->sepNext;
    }
    NI_ASSERT(nElems == 1, "The same callback was registered for one node twice, yet deletion does not specify valid user data resulting random deletion.");
    sepTemp = sepRoot;
    while(sepTemp != NULL && sepTemp->fpCallback != fpCallback)
    {
      sepPrev = sepTemp;
      sepTemp = sepTemp->sepNext;
    }
  }


  if (NULL == sepTemp)
  {
    DIASSERT_ALOOF_CODE(GetDBFileName()); // nothing to unregister
    return sepRoot;
  }
  return UnregisterCallbackInElemByClb(sepRoot, sepTemp, sepPrev);
}

DiBool DiAnimGraph::UnregisterCallbackForAllSameMarkers(const string &markerName, DiAnGrCallback fpCallback, DiVoid *userDataIfYouKnowIt)
{
  bool markerExists(false), ok(true);
  int  startIdx(0), foundIdx(-1);
  DiAnGrMarker *marker(NULL);

  while (true)
  {
    marker = FindMarkerByName(markerName, &startIdx, &foundIdx);
    markerExists = markerExists || (marker != NULL);
    if (NULL == marker)
      break;

    // TODO! EugBel!
    ok = UnregisterCallback(DIANGR_NODE, marker->nodeIdx, fpCallback, userDataIfYouKnowIt);
    NI_ASSERT(ok, "Failed to unregister callback on marker");
    startIdx = foundIdx + 1;
  }

  //NI_ASSERT(markerExists, "Wrong marker name specified");
  return markerExists;
}

DiBool DiAnimGraph::UnregisterCallback(DiAnimGraphElems geElem, DiUInt32 nID, DiAnGrCallback fpCallback, DiVoid *userDataIfYouKnowIt)
{
  DiAnimNode            *pNode;
  DiAnimMacronode       *pMacronode;
  DiAnimMTransaction     *pEdge;

  switch(geElem)
  {
    case DIANGR_NODE:
      DIASSERT(nID < GetNumNodes());
      pNode = GetNodeData(nID);
      DIASSERTPTR(pNode);
      if(pNode->sepClbStorage != NULL)
      {
        AGTrace("Unregistering callback %x in node %i(%s) with flags %i (exactPar? %i), userDataIfKnown=%x", fpCallback, nID, GetNodeNameByID(nID), pNode->sepClbStorage->nCallFlags, (pNode->sepClbStorage->nCallFlags & DIANGR_CF_EXACT_PARAM), userDataIfYouKnowIt);
        pNode->sepClbStorage = UnregisterCallbackInElem(pNode->sepClbStorage, fpCallback, userDataIfYouKnowIt);      
      }
      break;
    case DIANGR_MACRONODE:
      DIASSERT(nID < GetNumNodes());
      pMacronode = (DiAnimMacronode *)GetNodeData(nID);
      DIASSERTPTR(pMacronode);
      if(pMacronode->sepClbStorage != NULL)
      {
        AGTrace("Unregistering callback %x in MACROnode %i(%s) with flags %i (exactPar? %i), userDataIfKnown=%x", fpCallback, nID, GetNodeNameByID(nID), pMacronode->sepClbStorage->nCallFlags, (pMacronode->sepClbStorage->nCallFlags & DIANGR_CF_EXACT_PARAM), userDataIfYouKnowIt);
        pMacronode->sepClbStorage = UnregisterCallbackInElem(pMacronode->sepClbStorage, fpCallback, userDataIfYouKnowIt);      
      }
      break;

    case DIANGR_FLTRANSACTION:
      DIASSERT(nID < GetNumEdges());
      pEdge = GetTransactionData(nID);
      DIASSERT(pEdge);
      AGTrace("Unregistering callback %x in FLtransaction %i with flags %i (exactPar? %i), userDataIfKnown=%x", fpCallback, nID, pEdge->sepClbStorage->nCallFlags, (pEdge->sepClbStorage->nCallFlags & DIANGR_CF_EXACT_PARAM), userDataIfYouKnowIt);      
      pEdge->sepClbStorage = UnregisterCallbackInElem(pEdge->sepClbStorage, fpCallback, userDataIfYouKnowIt);      
      break;
    
    case DIANGR_ENTIREGRAPH:
      DIASSERT(DIANGR_NO_SUCH_ELEMENT == nID);
      AGTrace("Unregistering callback %x in entire graph with flags %i, userDataIfKnown=%x", fpCallback, this->sepClbStorage->nCallFlags, userDataIfYouKnowIt);            
      this->sepClbStorage = UnregisterCallbackInElem(this->sepClbStorage, fpCallback, userDataIfYouKnowIt);      
      break;

    default:
      // some unsupported type of graph element
      DIASSERT_ALOOF_CODE(GetDBFileName());
      DIRETURN(FALSE);
  }

  return true;
}

DiBool DiAnimGraph::UnregisterCallback(DiAnimGraphElems geElem, DiUInt32 nID, DiAnGrClbStorageElem *pElemToDel)
{
  DiAnimNode            *pNode;
  DiAnimMacronode       *pMacronode;
  DiAnimMTransaction     *pEdge;

  switch(geElem)
  {
  case DIANGR_NODE:
    DIASSERT(nID < GetNumNodes());
    pNode = GetNodeData(nID);
    DIASSERTPTR(pNode);
    if(pNode->sepClbStorage != NULL)
    {
      AGTrace("Unregistering callback %x in node %i(%s) with flags %i (exactPar? %i), userDataIfKnown=%x", pElemToDel->fpCallback, nID, GetNodeNameByID(nID), pNode->sepClbStorage->nCallFlags, (pNode->sepClbStorage->nCallFlags & DIANGR_CF_EXACT_PARAM), pElemToDel->vpUserData);
      pNode->sepClbStorage = UnregisterCallbackInElemByClb(pNode->sepClbStorage, pElemToDel);      
    }
    break;
  case DIANGR_MACRONODE:
    DIASSERT(nID < GetNumNodes());
    pMacronode = (DiAnimMacronode *)GetNodeData(nID);
    DIASSERTPTR(pMacronode);
    if(pMacronode->sepClbStorage != NULL)
    {
      AGTrace("Unregistering callback %x in MACROnode %i(%s) with flags %i (exactPar? %i), userDataIfKnown=%x", pElemToDel->fpCallback, nID, GetNodeNameByID(nID), pMacronode->sepClbStorage->nCallFlags, (pMacronode->sepClbStorage->nCallFlags & DIANGR_CF_EXACT_PARAM), pElemToDel->vpUserData);
      pMacronode->sepClbStorage = UnregisterCallbackInElemByClb(pMacronode->sepClbStorage, pElemToDel);      
    }
    break;

  case DIANGR_FLTRANSACTION:
    DIASSERT(nID < GetNumEdges());
    pEdge = GetTransactionData(nID);
    DIASSERT(pEdge);
    AGTrace("Unregistering callback %x in FLtransaction %i with flags %i (exactPar? %i), userDataIfKnown=%x", pElemToDel->fpCallback, nID, pEdge->sepClbStorage->nCallFlags, (pEdge->sepClbStorage->nCallFlags & DIANGR_CF_EXACT_PARAM), pElemToDel->vpUserData);      
    pEdge->sepClbStorage = UnregisterCallbackInElemByClb(pEdge->sepClbStorage, pElemToDel);      
    break;

  case DIANGR_ENTIREGRAPH:
    DIASSERT(DIANGR_NO_SUCH_ELEMENT == nID);
    AGTrace("Unregistering callback %x in entire graph with flags %i, userDataIfKnown=%x", pElemToDel->fpCallback, this->sepClbStorage->nCallFlags, pElemToDel->vpUserData);            
    this->sepClbStorage = UnregisterCallbackInElemByClb(this->sepClbStorage, pElemToDel);      
    break;

  default:
    // some unsupported type of graph element
    DIASSERT_ALOOF_CODE(GetDBFileName());
    DIRETURN(FALSE);
  }

  return true;
}

/**
 * This function clears call-after-exact-parameter flag. This function should be called 
 * when element (ex. node,transaction,etc.) has started or has wrapped
 *
 * @memo    Clear special update-flag
 * @return  none
 * @param   geElement       type of given element
 * @param   vpElement       pointer to started/wrapped element
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 */
DiVoid DiAnimGraph::ResetCallbacksOnParFlag(DiAnimGraphElems geElement, DiVoid *vpElement)
{
  DiAnGrClbStorageElem *sepClbRoot;

  // cast pointer depending on element
  switch(geElement)
  {
    case DIANGR_NODE: case DIANGR_MACRONODE:
      sepClbRoot = ((DiAnimNode *)vpElement)->GetClbStorage();
    break;
    
    case DIANGR_FLTRANSACTION:
      sepClbRoot = ((DiAnimMTransaction *)vpElement)->GetClbStorage();
    break;

    case DIANGR_ENTIREGRAPH:
      return; // graph can't have callback on parameter  
    break;
    default:
      DIASSERT_ALOOF_CODE(GetDBFileName());
      DIRETURNVOID();
  }

  // reset bIsClbCalledSinceElemStarted flag 
  // <=> say :"callback wasn't called since element was started or wrapped"
  while (sepClbRoot != NULL)
  {
    sepClbRoot->bIsClbCalledSinceElemStarted = FALSE;
    sepClbRoot = sepClbRoot->sepNext;
  }

}

/**
 * This function calls callback-on-parameter if it should be called now. This means that
 * callback wasn't called yet, parameter is OK and so on.
 *
 * @memo    Call callback-on-parameter
 * @return  
 * @param   sepClb
 * @param   rElementVPar
 * @param   bIsSpeedPositive
 * @param   nCurCallFlags
 * @param   geElement
 * @param   rTimeLeftForUpdate
 * @param   vpElemPtr
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiInt32 DiAnimGraph::DiAnGrClCallCallbackOnPar(DiAnGrClbStorageElem *sepClb, 
                                               DiFloat rElementVPar, 
                                               DiBool bIsSpeedPositive,
                                               DiUInt32 nCurCallFlags, 
                                               DiAnimGraphElems geElement, 
                                               DiFloat rTimeLeftForUpdate, 
                                               DiVoid *vpElemPtr,
                                               DiAnGrFlTransParam tpParam)
{
  DiBool  bNeedCall;
  DiInt32 nRes = DIOBJMSG_CONTINUE;
  DiFloat rPrevVPar;

  // check that (if speed > 0) current VPar > VPar_needed
  if (DIANGR_NODE == geElement || DIANGR_MACRONODE == geElement)
  {
    rPrevVPar = ((DiAnimNode *)vpElemPtr)->GetPrevPar();
  }
  else
  {
    DIASSERT(DIANGR_FLTRANSACTION == geElement);
    rPrevVPar = ((DiAnimFlTransaction *)vpElemPtr)->GetPrevPar();
  }

  DIASSERT(0.0f <= rPrevVPar && rPrevVPar <= 1.0f);
  bNeedCall = (((rElementVPar >= sepClb->rClbParam && sepClb->rClbParam >= rPrevVPar) &&  bIsSpeedPositive) ||
               ((rElementVPar <= sepClb->rClbParam && sepClb->rClbParam <= rPrevVPar) && !bIsSpeedPositive)   );
  bNeedCall &= (!sepClb->bIsClbCalledSinceElemStarted);

  if (bNeedCall)
  {
    AGTrace("Calling callbackOnExactPar_%x (neededPar=%4.2lf, curPar=%4.2lf)", sepClb->fpCallback, sepClb->rClbParam, rElementVPar);
    nRes = sepClb->fpCallback(DiAnGrCallbackParams(nCurCallFlags, geElement, 
                                       rTimeLeftForUpdate, vpElemPtr, 
                                       sepClb->vpUserData,tpParam));
    sepClb->bIsClbCalledSinceElemStarted = TRUE;
  }

  return nRes;  
}


/**
 * This function calls callbacks that match given flags
 *
 * @memo    Call Callbacks using given flags
 * @return  
 * @param   sepClb             element in callbacks storage
 * @param   nCurCallFlags      callback flags for current graph state
 * @param   vpElemPtr          pointer to the element which called callback
 * @param   vpUserData         user data (see RegisterCallback())
 * @param   bInFlTransaction   is graph state == FLTransaction (-> special pdate of nodes)
 * @param   atpFlTrans         pointer to FLTransaction (used when we update its nodes)
 * @param   tpParam            parameter of FLTransaction
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiInt32 DiAnimGraph::CallCallbackByFlags(DiAnGrClbStorageElem *sepClb, 
                                         DiAnimGraphElems geElement,
                                         DiUInt32 nCurCallFlags,
                                         DiVoid *vpElemPtr, 
                                         DiFloat rTimeLeftForUpdate,
                                         DiBool bInFlTransaction,
                                         DiAnimFlTransaction *atpFlTrans,
                                         DiAnGrFlTransParam tpParam,
                                         DiBool bGraphUpdate,
                                         DiFloat rElementVPar,
                                         DiBool  bIsSpeedPositive)
{
  DiInt32 nRes;
  DiBool  bIsThisEntireGraphCallback;
  DiAnGrClbStorageElem *sepNext = NULL;
  DiAnGrClbStorageElem *sepCurr = NULL;
  
  nRes = DIOBJMSG_CONTINUE;
  
  if (this->GetClbStorage() == sepClb)
    bIsThisEntireGraphCallback = TRUE;
  else
    bIsThisEntireGraphCallback = FALSE;

  if (NULL == sepClb)
    return nRes;
  
  sepCurr = sepClb;
  if (bInFlTransaction)
  {
    while ((sepCurr != NULL) && (DIOBJMSG_CONTINUE == nRes))
    {
      DIASSERTPTR(sepCurr->fpCallback);
      //next ahead since sepCurr can be deleted in callback
      sepNext = sepCurr->sepNext;

      int randProb = rand()%100;
      if ( randProb < sepCurr->probability )
      {
        // check case of update at particular virtual parameter
        if ((sepCurr->nCallFlags & DIANGR_CF_EXACT_PARAM) && !bIsThisEntireGraphCallback)
        {
          nRes = DiAnGrClCallCallbackOnPar(sepCurr, rElementVPar, bIsSpeedPositive,
            nCurCallFlags, DIANGR_FLTRANSACTION, rTimeLeftForUpdate, 
            atpFlTrans,tpParam);

          if (nRes != DIOBJMSG_CONTINUE)
          {
            continue;
          }
        }

        if (sepCurr->fpCallback != NULL && sepCurr->nCallFlags & nCurCallFlags)
        {
          AGTrace("Calling common callback_%x in transaction (curNode=%i, nextNode=%i)", sepCurr->fpCallback, nCurNode, nNextNode);
          nRes = sepCurr->fpCallback(DiAnGrCallbackParams(nCurCallFlags,DIANGR_FLTRANSACTION, 
            rTimeLeftForUpdate, atpFlTrans, 
            sepCurr->vpUserData, tpParam));
          #ifdef DIANGR_SCREEN_DEBUG_ADVANCED
          DebugAddCallbackToQueue(sepCurr);
          #endif
        }
      }

      sepCurr = sepNext;
    }
  }
  else //!bInFlTransaction == in node (because not-FLtransactions now do not exist)
  {
    while ((sepCurr != NULL) && (DIOBJMSG_CONTINUE == nRes))
    {
      DIASSERTPTR(sepCurr->fpCallback);
      //next ahead since sepCurr can be deleted in callback
      sepNext = sepCurr->sepNext;
      int randProb = rand()%100;
      if ( randProb < sepCurr->probability )
      {
        // check case of update at particular virtual parameter
        if ((sepCurr->nCallFlags & DIANGR_CF_EXACT_PARAM) && !bIsThisEntireGraphCallback)
        {
          nRes = DiAnGrClCallCallbackOnPar(sepCurr, rElementVPar, bIsSpeedPositive,
                                            nCurCallFlags, geElement, rTimeLeftForUpdate, 
                                            vpElemPtr,tpParam);
          if (nRes != DIOBJMSG_CONTINUE)
          {
            continue;
          }
        }

        if (sepCurr->fpCallback != NULL && sepCurr->nCallFlags & nCurCallFlags)
        {
          AGTrace("Calling common callback_%x (curNode=%i[%s], nextNode=%i[%s], ElementVPar=%10.7f)", 
                   sepCurr->fpCallback, nCurNode, GetNodeNameByID(nCurNode), nNextNode, GetNodeNameByID(nNextNode), rElementVPar);
          nRes = sepCurr->fpCallback(DiAnGrCallbackParams(nCurCallFlags, geElement, 
                                               rTimeLeftForUpdate, vpElemPtr, 
                                               sepCurr->vpUserData,tpParam));
          #ifdef DIANGR_SCREEN_DEBUG_ADVANCED
          DebugAddCallbackToQueue(sepCurr);
          #endif
        }
      }
      sepCurr = sepNext;
    }
  }

  return nRes;
}


/**
 * This function calls all needed callbacks for graph/graph_elements
 *
 * @memo    Call all needed (existed) callbacks
 * @return  DIOBJMSG_STOP | DIOBJMSG_CONTINUE | DIOBJMSG_ERROR
 * @param   nCurCallFlags       callback's flags
 * @param   geElement           Node or Transaction
 * @param   rTimeLeftForUpdate  time left for update
 * @param   vpElemPtr           pointer to element
 * @param   vpUserData          element data
 * @author  EugBel
 */
DiInt32 DiAnimGraph::CallCallbacks(DiUInt32 nCurCallFlags, 
                                   DiAnimGraphElems geElement,
                                   DiFloat rTimeLeftForUpdate, 
                                   DiVoid *vpElemPtr, 
                                   DiAnGrFlTransParam tpParam)
{
  DiInt32            nRes;
  DiAnimFlTransaction  *atpFlTrans;
  //DiAnimMTransaction *mtpMTrans;
  DiBool             bInFlTransaction;
    
  nRes = DIOBJMSG_CONTINUE;

  // check special case of callbacks: we are in Floating transaction =>
  // we update both nodes (From and To) and transaction between them =>
  // we shouldn't call callbacks for nodes!
  bInFlTransaction = FALSE;
  atpFlTrans         = NULL;
  if (DIANGR_FLTRANSACTION == GetCurElemType())
  {
    bInFlTransaction = TRUE;
    atpFlTrans = this->GetTransactionData(nCurTrans, nCurSubTrans);
    DIASSERT(atpFlTrans);
  }

  // callbacks themselves
  if (nCurCallFlags & DIANGR_CF_UPDATE_END)
  {
    // call graphs' callback first
    nRes = CallCallbackByFlags(sepClbStorage, geElement, nCurCallFlags, vpElemPtr, 
                               rTimeLeftForUpdate, bInFlTransaction, atpFlTrans, 
                               tpParam,TRUE, DIANGR_INVALID_FLOAT_VALUE, TRUE);
  }
  if (nRes != DIOBJMSG_CONTINUE)
    DIRETURN(nRes);

  switch(geElement)
  {
    case DIANGR_NODE: case DIANGR_MACRONODE:
    
      // set atpFlTrans to NULL to show that we don't need update in FlTransaction  
      nRes = CallCallbackByFlags(((DiAnimNode *)vpElemPtr)->sepClbStorage, geElement, nCurCallFlags, 
                                 vpElemPtr, rTimeLeftForUpdate,
                                 FALSE, atpFlTrans, tpParam, FALSE,
                                 ((DiAnimNode *)vpElemPtr)->GetVPar(), 
                                 ((DiAnimNode *)vpElemPtr)->GetSpeed() > 0);
      break;

    case DIANGR_FLTRANSACTION:
      
      nRes = CallCallbackByFlags(GetTransactionData(GetCurTransaction())->sepClbStorage, geElement, nCurCallFlags, 
                                 vpElemPtr, rTimeLeftForUpdate,
                                 TRUE, atpFlTrans, tpParam, FALSE,
                                 this->rCurParInTransaction, TRUE);

      /*
      nRes = CallCallbackByFlags(((DiAnimMTransaction *)vpElemPtr)->sepClbStorage, geElement, nCurCallFlags, 
                                 vpElemPtr, rTimeLeftForUpdate,
                                 TRUE, atpFlTrans, tpParam, FALSE);
      */
      break;
  }
  if (nRes != DIOBJMSG_CONTINUE)
    DIRETURN(nRes);
  
  if (nCurCallFlags & DIANGR_CF_UPDATE_BEGIN)
  {
    // call graphs' callback 
    nRes = CallCallbackByFlags(sepClbStorage, geElement, nCurCallFlags, vpElemPtr, 
                               rTimeLeftForUpdate, bInFlTransaction, atpFlTrans, 
                               tpParam, TRUE, DIANGR_INVALID_FLOAT_VALUE, TRUE);
  }

  // clear flags
  this->bNeedElementEnterCallback = FALSE;
  this->bNeedElementLeaveCallback = FALSE;

  DIRETURN(nRes);  
}

/**
 * This function allocates memory for callbacks storage
 *
 * @memo    
 * @return  TRUE on success, FALSE otherwise
 * @param   
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiBool DiAnimGraph::PrepareCallbacksStorage()
{
  //DiInt32 nI;

  // allocate memory
  sepClbArray = new list<DiAnGrClbStorageElem>();
  DIASSERT(sepClbArray);

  int a = sepClbArray->size();
  DIASSERT(!a);

  // init data with invalid data
  //for (nI = 0; nI < DIANGR_MAX_NUM_CALLBACKS; nI++)
  //{
  //  DiAnGrClbStorageElem &cur = sepClbArray[nI];

  //  cur.nCallFlags                    = 0;
  //  cur.rClbParam                     = DIANGR_INVALID_FLOAT_VALUE;
  //  cur.bIsClbCalledSinceElemStarted  = FALSE;
  //  cur.nPriority                     = DIANGR_INVALID_PRIORITY;
  //  cur.fpCallback                    = NULL;
  //  cur.vpUserData                    = NULL;
  //  #ifdef DIANGR_SCREEN_DEBUG_ADVANCED
  //  cur.cpName                        = NULL;; 
  //  #endif
  //  cur.sepNext                       = NULL;
  //}

  nNumRegisteredCallbacks = 0;
  nPrevRegisteredCallback = -1; // "-1" is important!

  return TRUE;
}

/**
 * This function 
 *
 * @memo    Cleanup memory
 * @return  none
 * @param   
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiVoid DiAnimGraph::ReleaseCallbacksStorage(nstl::list<DiAnGrClbStorageElem>*& sepClbArray)
{
  // free debug-specific information (internal callback's names)
  #ifdef DIANGR_SCREEN_DEBUG_ADVANCED
    DiInt32 nI;

    if(sepClbArray != NULL)
    {
      // free internal callbacks names if such exist: check all elems
      typedef nstl::list<DiAnGrClbStorageElem>::iterator It;
      for (It it = sepClbArray->begin(); it != sepClbArray->end(); it++)
      {
        if (it->fpCallback != NULL && it->cpName != NULL)
        {
          if (strstr(it->cpName,DIANGR_INT_CALLBACK_PREFIX) != NULL)
          {
            DiMemFree(it->cpName);
          }
        }
      }
    }
  #endif

  if (sepClbArray != NULL)
  {
    delete sepClbArray;
    sepClbArray = NULL;
  }
}

DiFloat DiAnimGraph::GetTimeTillNearestClbOnPar(DiAnGrClbStorageElem *sepRoot, DiFloat curVP, DiFloat defaultTime, DiFloat elemSpeed)
{
  if (NULL == sepRoot || fabs(elemSpeed) < DIANGR_MIN_SPEED)
    return defaultTime;

  // @todo (EugBel): optimize this search: add callbacks sorted by time!
  DiFloat rNearestClbOnParTime = MAX_FLOAT;

  DiAnGrClbStorageElem *sepTemp = sepRoot;
  DiAnGrClbStorageElem *sepPrev = NULL;
  while (sepTemp != NULL)
  {
    NI_ASSERT(!sepTemp->IsEmpty(), "Logic failed in clb-storage");
    if ((sepTemp->nCallFlags & DIANGR_CF_EXACT_PARAM) && (sepTemp->rClbParam > curVP) && (sepTemp->rClbParam < rNearestClbOnParTime))
      rNearestClbOnParTime = sepTemp->rClbParam;

    sepPrev = sepTemp;
    sepTemp = sepTemp->sepNext;
  }

  if (rNearestClbOnParTime < MAX_FLOAT)
  {
    
    DiFloat rTimeTillClb = min( (rNearestClbOnParTime - curVP + (DIANGR_MIN_DT / 3.0f)) / elemSpeed, defaultTime);

    NI_VERIFY(rTimeTillClb > 0.0f, "Check logic", rNearestClbOnParTime = defaultTime;);
    return rTimeTillClb;
  }

  return defaultTime;
}

/**
 * This function fills concrete callback storage
 *
 * @memo    
 * @return  pointer to Root (doesn't change if root already existed)
 * @param   nPriority
 * @param   fpCallback
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiAnGrClbStorageElem *DiAnimGraph::FillCallbackStorage(DiAnGrClbStorageElem *sepRoot, 
                                                       DiVoid  *vpUserData,
                                                       DiAnGrCallback fpCallback,
                                                       DiFloat probability,
                                                       DiUInt32 nCallFlags,
                                                       DiTChar *cpName,
                                                       DiFloat rExactParam, 
                                                       DiAnGrClbStorageElem  **pCreatedEl)
{
  DiAnGrClbStorageElem *sepElemToAdd, *sepTemp, *sepPrev;
  
  DIASSERTPTR(fpCallback);
  DIASSERTPTR(pCreatedEl);
  
  #ifdef DIDEBUG
  // check virtual parameters if it is specified
  if (nCallFlags & DIANGR_CF_EXACT_PARAM)
  {
    DIASSERT(0.0f <= rExactParam && rExactParam <= 1.0f);
  }
  else
  {
    DIASSERT(DIANGR_INVALID_FLOAT_VALUE == rExactParam);
  }
  #endif

  sepTemp  = sepRoot;
  while(sepTemp != NULL && !(sepTemp->fpCallback == fpCallback && sepTemp->vpUserData == vpUserData))
  {
    sepTemp = sepTemp->sepNext;
  }

  //HACK to avoid below verify trigger too much...
  //if(sepTemp != NULL) 
  //  return sepRoot;
  //NI_VERIFY(sepTemp == NULL, "Attempt to register callback which is already registered for this element with exactly same user data. Addition averted.", return sepRoot);

  DIASSERT(this->nNumRegisteredCallbacks < DIANGR_MAX_NUM_CALLBACKS);
  //DiInt32 place = (this->nPrevRegisteredCallback + 1) % DIANGR_MAX_NUM_CALLBACKS;
  //if (!(this->sepClbArray[place].IsEmpty()))
  //{
  //  // search 
  //  //@todo [eugbel] make this more optimal if there are many calls of this function in the game
  //  for (int i = 1; i < DIANGR_MAX_NUM_CALLBACKS; i++)
  //  {
  //    int curIdx = (place + i) % DIANGR_MAX_NUM_CALLBACKS;
  //    if (this->sepClbArray[curIdx].IsEmpty())
  //    {
  //      place = curIdx;
  //      break;
  //    }
  //  }
  //}
  //if (!(this->sepClbArray[place].IsEmpty()))
  //{
  //  DIASSERT_ALOOF_CODE(GetDBFileName()); // this means that nNumRegisteredCallbacks is incorrect
  //  return sepRoot;
  //}

  
  sepElemToAdd            = &(this->sepClbArray->push_back());
  nPrevRegisteredCallback = -1;

  sepElemToAdd->fpCallback = fpCallback;
  sepElemToAdd->vpUserData = vpUserData;
  sepElemToAdd->nPriority = DIANGR_INVALID_PRIORITY;
  sepElemToAdd->probability  = probability;
  sepElemToAdd->nCallFlags = nCallFlags;
  sepElemToAdd->sepNext    = NULL;
  sepElemToAdd->rClbParam  = rExactParam;
#ifdef DIANGR_SCREEN_DEBUG_ADVANCED
  sepElemToAdd->cpName     = cpName;  
#else
  diUSE_PARAM(cpName);
#endif
  //save elem to unform caller
  *pCreatedEl = sepElemToAdd;

  // add given callback to the end of all callbacks for given graph element 
  // (if any other callbacks have already been registered)
  sepTemp = sepRoot;
  sepPrev = NULL;
  while (sepTemp != NULL)
  {
    sepPrev = sepTemp;
    sepTemp = sepTemp->sepNext;
  }

  if (NULL == sepRoot)
    sepRoot = sepElemToAdd;
  else
    sepPrev->sepNext = sepElemToAdd;

  this->nNumRegisteredCallbacks++;

  DIASSERTPTR(sepRoot);
  return sepRoot;
}

#ifdef DIANGR_SCREEN_DEBUG_ADVANCED
/**
 * This function adds callback to the "Last called callbacks list".
 *
 * @memo    Add callback to the queue (perhaps delete the oldest callback)
 * @return  none
 * @param   cepCurCallback
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiVoid DiAnimGraph::DebugAddCallbackToQueue(DiAnGrClbStorageElem *sepCurCallback)
{
  // add calbback to the queue
  DIASSERT(nCallbackCellToFill >= 0 && nCallbackCellToFill < DIANGR_DEBUG_MAX_LAST_CALLBACKS);
  this->seapLatestCallbacks[nCallbackCellToFill] = sepCurCallback;

  // maintain queue integrity
  nUsedCallbacksCells = DiIMin(nUsedCallbacksCells + 1, DIANGR_DEBUG_MAX_LAST_CALLBACKS);

  nCallbackCellToFill++;
  // check overflow
  if (nCallbackCellToFill >= DIANGR_DEBUG_MAX_LAST_CALLBACKS)
  {
    nCallbackCellToFill = 0;
  }
}

#endif

///eugbelNSCENE///} // end of namespace NScene

