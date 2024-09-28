/*
 * @file    DiAnGrDb.cpp
 * @memo    Debug utilities for animation graph
 * @author  EugBel
 * @date    29.01.2004
 * @prefix  DiAnGr
 * @header  DiAnGr.h
 * @library skeleton.lib
 */

/* DEBUG CONTROLS
   next graph:                "]"
   prev graph:                "["
   change btw graph/cur_elem: "9"
   
   change speed delta:        "0"
   increase speed:            "="
   decrease speed:            "-"
*/


// *******************************************************************
// includes

// all code is available ONLY in debug mode with DIANGR_SCREEN_DEBUG_GENERAL
#include "stdafx.h"

#include <string.h>
#include "../Render/debugrenderer.h"

#include "DiAnGr.h"


namespace 
{
  DiAnimGraph *s_graphToLog = NULL;
  bool s_enableLog2Output   = false;
  bool s_enableLog2Screen   = false;
}

DiAnimGraph *DiAnimGraph::GetGraphToLog()
{
  return s_graphToLog;
}

bool DiAnimGraph::IsLog2OutputEnabled()
{
  return s_enableLog2Output;
}

bool DiAnimGraph::IsLog2ScreenEnabled()
{
  return s_enableLog2Screen;
}

void DiAnimGraph::EnableLog(bool enableLogging, DiAnimGraph *agToWatch, bool enableLogToOutput)
{
  s_enableLog2Screen = enableLogging;
  s_enableLog2Output = enableLogging && enableLogToOutput;
  s_graphToLog       = agToWatch;

  if (IsLog2OutputEnabled())
    DebugTrace("\n\n\n\nAG LOGGING ENABLED (will watch graph %x)\n\n\n\n", (void*)s_graphToLog);

#ifndef _SHIPPING
  if (IsLog2ScreenEnabled() && s_graphToLog != NULL)
    DebugSetGraph(s_graphToLog);
#endif
}

// This function will do something only if IsLog2OutputEnabled() == true
void DiAnimGraph::AGTrace( const char *pszFormat, ... )
{
#ifndef _SHIPPING
  if (IsLog2OutputEnabled() && (GetGraphToLog() == this || GetGraphToLog() == NULL))
  {
    char out1[1000], out2[1000];

    sprintf_s(out1, "AG_%x(spd=%5.3lf):", this, GetGraphSpeedCoeff());

    va_list va;
    va_start( va, pszFormat );
    vsnprintf_s( out2, 1000, 1000, pszFormat, va );
    va_end( va );

    strcat_s(out1, out2);

    systemLog( NLogg::LEVEL_DEBUG ) << out1;
  }
#endif
}



#ifdef DIANGR_SCREEN_DEBUG_GENERAL

#pragma warning( disable : 4996 )

// dummy vars for better visibility on UI
static NDebug::StringDebugVar  s_animgraph_graphInfo1   ( "01_GRAPH", "AG" );
static NDebug::StringDebugVar  s_animgraph_graph001     ( "01_",      "AG" );

static NDebug::StringDebugVar  s_animgraph_tweakInfo1   ( "02 TWEAK", "AG" );
static NDebug::StringDebugVar  s_animgraph_graph002     ( "02_",      "AG" );

static NDebug::StringDebugVar  s_animgraph_stateInfo1   ( "03_STATE", "AG" );
static NDebug::StringDebugVar  s_animgraph_stateInfo2   ( "04_STATE", "AG" );
static NDebug::StringDebugVar  s_animgraph_stateInfo3   ( "05_STATE", "AG" );
static NDebug::StringDebugVar  s_animgraph_graph005     ( "05_",      "AG" );

static NDebug::StringDebugVar  s_animgraph_nodeInfo1    ( "06_NODE",  "AG" );
static NDebug::StringDebugVar  s_animgraph_nodeInfo2    ( "07_NODE",  "AG" );
static NDebug::StringDebugVar  s_animgraph_graph003     ( "07_",      "AG" );

static NDebug::StringDebugVar  s_animgraph_transInfo1   ( "08_TRANS", "AG" );
static NDebug::StringDebugVar  s_animgraph_transInfo2   ( "09_TRANS", "AG" );
static NDebug::StringDebugVar  s_animgraph_transInfo3   ( "10_TRANS", "AG" );
static NDebug::StringDebugVar  s_animgraph_transInfo4   ( "11_TRANS", "AG" );
static NDebug::StringDebugVar  s_animgraph_graph004     ( "11_",      "AG" );

static NDebug::StringDebugVar  s_animgraph_clbInfo      ( "12_CLB",   "AG" );
static NDebug::StringDebugVar  s_animgraph_helpInfo1    ( "14_HELP",  "AG" );
static NDebug::StringDebugVar  s_animgraph_helpInfo2    ( "15_HELP",  "AG" );


#define _LEN 150
static char s_buf[_LEN] = "";
#define _LEN_ASSERT 80   // this value is relevant to DebugString buffer length


///eugbelNSCENE///namespace NScene {


// *******************************************************************
// defines


// max length of text line in the screen in graph-debug mode
#define DIANGRDB_MAX_TEXT_LEN  200 

#define DIANGRDB_MAX_SEQ_NAME  30


// *******************************************************************
// local data
typedef struct tagDiAnGrDbElem
{
  DiAnimGraph            *agpGraph;
  struct tagDiAnGrDbElem *geNext;
  struct tagDiAnGrDbElem *gePrev;
  int                    usedMem;
}DiAnGrDbElem;

// this enum represents available delta values (see _raDeltaCoeff)
// NOTE: don't change order! Don't forget about array _raDeltaCoeff[]
typedef enum 
{
  DIANGRDB_DELTA_NA         = -1,
  DIANGRDB_DELTA_FIRST,  
  DIANGRDB_DELTA_HUGE       = DIANGRDB_DELTA_FIRST,
  DIANGRDB_DELTA_BIG,
  DIANGRDB_DELTA_MIDDLE,
  DIANGRDB_DELTA_SMALL,
  DIANGRDB_DELTA_LAST       = DIANGRDB_DELTA_SMALL,
  DIANGRDB_DELTA_FORCEDWORD = 0x7fffffff
}DiAnGrDbDelta;

// this enum represents objects available for speed tweaking
typedef enum
{
  DIANGRDB_OBJ_NA            = -1,
  DIANGRDB_OBJ_ENTIRE_GRAPH,
  DIANGRDB_OBJ_CUR_ELEM,
  DIANGRDB_OBJ_LAST          = DIANGRDB_OBJ_CUR_ELEM,
  DIANGRDB_OBJ_FORCEDWORD    = 0x7fffffff
}DiAnGrDbTweakElem;


// input description structure
typedef struct tagDiAnGrDbIDesc
{
  DiUInt16     nMsg;
  DiInt32      nControl;
  DiUInt32     nControlFlag;
}DiAnGrDbIDesc;


// input messages IDs
typedef enum tagDiAnGrDbMsgID
{
  DIANGRDB_MSG_NA           = 5000,  // 5000 - magic number versus conflicts
  DIANGRDB_MSG_SHOW,
  DIANGRDB_MSG_PREVGRAPH,
  DIANGRDB_MSG_NEXTGRAPH,
  DIANGRDB_MSG_FASTER,
  DIANGRDB_MSG_SLOWER,
  DIANGRDB_MSG_CHANGEDELTA,
  DIANGRDB_MSG_CHANGEOBJ,
  DIANGRDB_MSG_FORCEDWORD   = 0x7fffffff
}DiAnGrDbMsgID;

           
static DiAnGrDbElem *_gepList          = NULL;
static DiAnGrDbElem *_gepCurElem       = NULL;
static DiInt32      _nNumGraphs        = 0;
static DiInt32      _nApproxMemAlloced = 0;
static DiInt32      _nMsgContext       = 0;

static DiFloat            _raDeltaCoeff[]   = {1.0f, 0.1f, 0.01f, 0.001f};
static DiAnGrDbDelta      _dCurDelta        = DIANGRDB_DELTA_BIG;
static DiAnGrDbTweakElem  _eCurObject       = DIANGRDB_OBJ_ENTIRE_GRAPH;

// *******************************************************************
// functions

/**
 * This function 
 *
 * @memo    
 * @return  none
 * @param   agpGraph
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiVoid DiAnimGraph::DebugRegisterGraph(DiAnimGraph *agpGraph, DiUInt32 approxMemAllocated)
{
  DiAnGrDbElem *geNew;

  DIASSERTPTR(agpGraph);

  geNew           = (DiAnGrDbElem *)DiMemAllocate(sizeof(DiAnGrDbElem));
  geNew->agpGraph = agpGraph;
  geNew->geNext   = NULL;
  geNew->gePrev   = NULL;
  geNew->usedMem  = approxMemAllocated;
  
  // add graph to the list
  if (_gepList != NULL)
  {
    geNew->geNext   = _gepList;
    _gepList->gePrev = geNew;
  }

  _gepList       = geNew;
  
  // set new current element (if not set yet)
  if (NULL == _gepCurElem)
    _gepCurElem = _gepList;

  _nNumGraphs++;
  _nApproxMemAlloced += geNew->usedMem;
}

DiVoid DiAnimGraph::DebugUnregisterGraph(const DiAnimGraph *agpGraph)
{
  DIASSERTPTR(agpGraph);

  // search list and remove the element
  DiAnGrDbElem *cur = _gepList;
  while (cur != NULL)
  {
    if (cur->agpGraph == agpGraph)
      break;
    cur = cur->geNext;
  }

  if (NULL == cur || cur->agpGraph != agpGraph)
  {
    DIASSERT_ALOOF_CODE(agpGraph->GetDBFileName());
    return;
  }

  if (cur == _gepCurElem)
  {
    DebugSetNextGraph();
  }

  if (cur == _gepList)
  {
    _gepList    = cur->geNext;
    _gepCurElem = cur->geNext;
  }
  else
  {
    if (cur->gePrev != NULL)
      cur->gePrev->geNext = cur->geNext;

    if (cur->geNext != NULL)
      cur->geNext->gePrev = cur->gePrev;
  }


  _nApproxMemAlloced -= cur->usedMem;
  _nNumGraphs--;
  DIASSERT(_nNumGraphs >= 0);

  DiMemFree(cur);
  cur = NULL;
}


/**
 * This function 
 *
 * @memo    
 * @return  none
 * @param   
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiVoid DiAnimGraph::DebugEmptyList()
{
  // All memory should be freed at DebugUnregisterGraph

  if (0 == _nNumGraphs)
  {
    DIASSERT(NULL == _gepList);
    DIASSERT(NULL == _gepCurElem); ///eugbel/// Please call EugBel when this assert fails!
    DIASSERT(0 == _nApproxMemAlloced);
  }
}


DiAnimNamesArray *DiAnimGraph::DebugGetDbSeqTables()
{
  return napDbSeqNames;
}

DiAnGrNodesMap *DiAnimGraph::DebugGetDbNodesMapTable()
{
  return nmpDbTable;
}

DiInt32 *DiAnimGraph::DebugGetDbNumSeqsInTables()
{
  return npDbNumSeqsInTables;
}

/*
 *  nPart - ID of part <=> ID of table <=> NumSeqsPerNode
 */
DiInt32 DiAnimGraph::DebugGetDbNumSeqsInTable(DiInt32 nPart)
{
  return npDbNumSeqsInTables[nPart];
}

/*
 * This function gets speed of current element in active graph
 *
 * @memo    
 * @return  none
 * @param   
 * @author  EugBel
 */
DiFloat DiAnimGraph::_diAnGrDbGetCurElemSpeed()
{
  DiAnimGraphElems  geElem;

  // get current element
  geElem = _gepCurElem->agpGraph->GetCurElemType();

  switch(geElem)
  {
    case DIANGR_NODE: case DIANGR_MACRONODE:
      return _gepCurElem->agpGraph->GetNodeData(_gepCurElem->agpGraph->GetCurNode())->GetSpeed();

    case DIANGR_FLTRANSACTION:
      return _gepCurElem->agpGraph->GetTransactionData(_gepCurElem->agpGraph->GetCurTransaction(), 
                                                       _gepCurElem->agpGraph->GetCurSubTransaction())->GetSpeed();
      
  }

  DIASSERT_ALOOF_CODE(_gepCurElem->agpGraph->GetDBFileName());
  return DIANGR_INVALID_FLOAT_VALUE;
}

/*
 * This function gets virtual parameter of current element in active graph
 *
 * @memo    
 * @return  none
 * @param   
 * @author  EugBel
 */
DiFloat DiAnimGraph::_diAnGrDbGetCurElemVP()
{
  DiAnimGraphElems  geElem;

  // get current element
  geElem = _gepCurElem->agpGraph->GetCurElemType();

  switch(geElem)
  {
    case DIANGR_NODE: case DIANGR_MACRONODE:
      return _gepCurElem->agpGraph->GetNodeData(_gepCurElem->agpGraph->GetCurNode())->GetVPar();

    case DIANGR_FLTRANSACTION:
      return _gepCurElem->agpGraph->GetCurTransactionPar();
  }

  DIASSERT_ALOOF_CODE(_gepCurElem->agpGraph->GetDBFileName());
  return DIANGR_INVALID_FLOAT_VALUE;
}


/**
 * This function show information about graph (name, etc.) and tweaking params
 *
 * @memo    Show basic graph information and tweaking parameters
 * @return  none
 * @param   agpGraph
 * @param   cpBuffer
 * @param   rpParams
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiVoid DiAnimGraph::DebugUpdateGraphInfo(DiAnimGraph *agpGraph)
{
  string out1("");

  // print graph's name
  sprintf_s(s_buf, sizeof(s_buf), "'%s' (Nds=%i, Trns=%i, Adr=%x). Total=%i (mem=%5.2lf Mb)", 
            agpGraph->caName, agpGraph->GetNumNodes(),agpGraph->GetNumEdges(), agpGraph,
            _nNumGraphs, float(_nApproxMemAlloced) / (1024.0f * 1024.0f) );
  out1.append(s_buf);
  
  DIASSERT(out1.length() < _LEN_ASSERT);
  s_animgraph_graphInfo1.SetValue(out1);
}

DiVoid DiAnimGraph::DebugUpdateTweakInfo(DiAnimGraph *agpGraph)
{
  string out1("");

  // print speed-tweaking parameter
  switch(_eCurObject)
  {
    case DIANGRDB_OBJ_ENTIRE_GRAPH:
      sprintf_s(s_buf, sizeof(s_buf), "GrSpdCoef: %5.3lf ", agpGraph->GetGraphSpeedCoeff());
      break;
    case DIANGRDB_OBJ_CUR_ELEM:
      sprintf_s(s_buf, sizeof(s_buf), "CurElSpd: %5.3lf ", _diAnGrDbGetCurElemSpeed());
      break;
    default:
      DIASSERT_ALOOF_CODE(agpGraph->GetDBFileName());
  }
  out1.append(s_buf);

  // print delta-value for tweaking graph's speed
  sprintf_s(s_buf, sizeof(s_buf), " (%5.3lf)", _raDeltaCoeff[_dCurDelta]);
  out1.append(s_buf);

  DIASSERT(out1.length() < _LEN_ASSERT);
  s_animgraph_tweakInfo1.SetValue(out1);
}


DiVoid DiAnimGraph::DebugUpdateStateInfo(DiAnimGraph *agpGraph)
{
  string out1(""), out2(""), out3("");

  DiAnimNode *anpNode;
  DiAnimGraphElems  geType;

  // print current element type
  geType = agpGraph->GetCurElemType();
  switch(geType)
  {
    case DIANGR_NODE:
      sprintf_s(s_buf, sizeof(s_buf), "CurEl: %s ('%s',%i)", DIANGR_NODE_NAME, 
                agpGraph->GetNodeNameByID(agpGraph->GetCurNode()),
                agpGraph->GetCurNode());
      break;
    case DIANGR_MACRONODE:
      sprintf_s(s_buf, sizeof(s_buf), "CurEl: %s ('%s'),%i", DIANGR_MACRONODE_NAME, 
                agpGraph->GetNodeNameByID(agpGraph->GetCurNode()),
                agpGraph->GetCurNode());
      break;
    case DIANGR_FLTRANSACTION:
      sprintf_s(s_buf, sizeof(s_buf), "CurEl: %s ('%s',%i->'%s',%i)", DIANGR_FLTRANSACTION_NAME,
                agpGraph->GetNodeNameByID(agpGraph->GetPrevNode()),
                agpGraph->GetPrevNode(),
                agpGraph->GetNodeNameByID(agpGraph->GetNextNode()),
                agpGraph->GetNextNode());
      break;
    default:
      DIASSERT_ALOOF_CODE(agpGraph->GetDBFileName());
  }
  out1.append(s_buf);

  sprintf_s(s_buf, sizeof(s_buf)," VP=%5.3lf",_diAnGrDbGetCurElemVP());
  out1.append(s_buf);

  // print name of next node
  if (agpGraph->nNextNode != DIANGR_NO_SUCH_ELEMENT)
  {
    anpNode = agpGraph->GetNodeData(agpGraph->nNextNode);
    sprintf_s(s_buf, sizeof(s_buf), "Next: %s(%i). VP: %4.3lf", 
            agpGraph->GetNodeNameByID(agpGraph->nNextNode), 
            agpGraph->nNextNode,
            agpGraph->GetNodeData(agpGraph->nNextNode)->GetVPar());    
  }
  else
  {
    sprintf_s(s_buf, sizeof(s_buf), "Next: N/A. ");
  }
  out2.append(s_buf);

  // print name of prev node
  if (agpGraph->nPrevNode != DIANGR_NO_SUCH_ELEMENT)
  {
    anpNode = agpGraph->GetNodeData(agpGraph->nPrevNode);
    sprintf_s(s_buf, sizeof(s_buf), "Prev: %s(%i). VP: %4.3lf", 
            agpGraph->GetNodeNameByID(agpGraph->nPrevNode),
            agpGraph->nPrevNode,          
            anpNode->GetVPar());    
  }
  else
  {
    sprintf_s(s_buf, sizeof(s_buf), "Prev: N/A. ");
  }
  out3.append(s_buf);

/*  
  // print name of target node
  if (agpGraph->bPathSpecified)
  {
    DIASSERTPTR(agpGraph->gpPath.npPath);
    sprintf_s(s_buf, sizeof(s_buf), "Target: %s(%i). VP: %4.3lf  ", 
            agpGraph->GetNodeNameByID(agpGraph->gpPath.nTargetNode), 
            agpGraph->gpPath.nTargetNode,
            agpGraph->GetNodeData(agpGraph->gpPath.nTargetNode)->GetVPar());      
    out2.append(s_buf);
  
    sprintf_s(s_buf, sizeof(s_buf), "PATH: ");
    out2.append(s_buf);

    // add nodes from the path to the text-line
    // "+1": first node is INVALID
    DIASSERT(agpGraph->gpPath.nPathLength < 10);
    for (DiUInt32  nK = agpGraph->gpPath.nCurIdxInPath + 1; nK < agpGraph->gpPath.nPathLength; nK++)
    {
      sprintf_s(s_buf, sizeof(s_buf), " %s (%i);",
              agpGraph->GetNodeNameByID(agpGraph->gpPath.npPath[nK]),
              agpGraph->gpPath.npPath[nK]);
      out2.append(s_buf);
    }
  }
  else 
  {
    // target node == next node
    sprintf_s(s_buf, sizeof(s_buf), "Target(%i)==Next(%i)", agpGraph->GetTargetNode(), agpGraph->GetNextNode());
    out2.append(s_buf);
  } // end of forming path-line
*/
  
  DIASSERT(out1.length() < _LEN_ASSERT);
  DIASSERT(out2.length() < _LEN_ASSERT);
  DIASSERT(out3.length() < _LEN_ASSERT);
  s_animgraph_stateInfo1.SetValue(out1);
  s_animgraph_stateInfo2.SetValue(out2);
  s_animgraph_stateInfo3.SetValue(out3);
}


/*
 * This function renders nodes-specific information
 *
 * @memo    Show nodes-specific information
 * @return  none
 * @param   agpGraph    pointer to the active graph
 * @param   cpBuffer    buffer for text to show
 * @author  EugBel
 */
DiVoid DiAnimGraph::DebugUpdateNodesInfo(DiAnimGraph *agpGraph)
{
  string out1(""), out2("");

  DiAnimNode       *anpNode;
  DiUInt32         nCurNode;
  DiInt32          nNumSubNodes;
  DiInt32          nI, nJ, *npNumSeqs; 
  DiAnimNamesArray *anpDbSeqNames;
  DiAnGrSequence   *aspSeq;

  DIASSERTPTR(agpGraph);

  // print name of the node
  nCurNode = agpGraph->GetCurNode();
  anpNode = agpGraph->GetNodeData(nCurNode);

  sprintf_s(s_buf, sizeof(s_buf), "Node: %10s(%i). VP: %4.3lf ", 
          agpGraph->GetNodeNameByID(nCurNode), 
          nCurNode,
          anpNode->GetVPar());  
  out1.append(s_buf);

  // print speed of the node
  sprintf_s(s_buf, sizeof(s_buf), "Spd: %5.3lf", anpNode->GetSpeed());    
  out1.append(s_buf);

  // print info about sequences
  if (anpNode->IsMacronode())
  {
    nNumSubNodes = ((DiAnimMacronode *)anpNode)->GetNumIntNodes();
  }
  else
  {
    nNumSubNodes = 1;
  }

  // print info about sequence
  anpDbSeqNames     = agpGraph->DebugGetDbSeqTables();
  npNumSeqs         = agpGraph->DebugGetDbNumSeqsInTables();
  if (anpDbSeqNames != NULL && npNumSeqs > 0)
  {
    for (nJ = 0; nJ < nNumSubNodes; nJ++)
    {
      for(nI = 0; nI < agpGraph->GetNumParts(); nI++)
      {
        aspSeq = (anpNode->spSequences + nJ * agpGraph->nNumSeqsPerNode + nI);
        sprintf_s(s_buf, sizeof(s_buf), "Seq  : %10s(%i). VP: %4.3lf", 
                agpGraph->GetSeqNameByIdx(anpDbSeqNames[nI], npNumSeqs[nI], aspSeq->nID), 
                                          aspSeq->nID, aspSeq->rCurPar);
        out2.append(s_buf);
      }                                              
    }
  }

  DIASSERT(out1.length() < _LEN_ASSERT);
  DIASSERT(out2.length() < _LEN_ASSERT);
  s_animgraph_nodeInfo1.SetValue(out1);
  s_animgraph_nodeInfo2.SetValue(out2);
}

/**
 * This function shows edge-specific information
 *
 * @memo    Show information about current transaction
 * @return  none
 * @param   agpGraph
 * @param   cpBuffer       buffer for text
 * @param   rpParams       render parameters
 * @author  EugBel
 */
DiVoid DiAnimGraph::DebugUpdateEdgesInfo(DiAnimGraph *agpGraph)
{
  string            out1(""), out2(""), out3(""), out4("");

  DiAnimFlTransaction *atpEdge;

  atpEdge = agpGraph->GetTransactionData(agpGraph->nCurTrans, agpGraph->nCurSubTrans);

  // print names of nodes

  // first: node From
  sprintf_s(s_buf, sizeof(s_buf), "From:  %10s(%i); VP: %4.3lf; Spd: %4.2lf", 
          agpGraph->GetNodeNameByID(agpGraph->nPrevNode),
          agpGraph->nPrevNode,
          agpGraph->GetNodeData(agpGraph->nPrevNode)->GetVPar(),
          agpGraph->GetNodeData(agpGraph->nPrevNode)->GetSpeed());    
  out1.append(s_buf);  
       
  // node To
  sprintf_s(s_buf, sizeof(s_buf), "To    :  %10s(%i). VP: %4.3lf; Spd: %4.2lf", 
          agpGraph->GetNodeNameByID(agpGraph->nNextNode),
          agpGraph->nNextNode,
          agpGraph->GetNodeData(agpGraph->nNextNode)->GetVPar(),
          agpGraph->GetNodeData(agpGraph->nNextNode)->GetSpeed());    
  out2.append(s_buf);

  // print transaction params
  // NOTE: in FLTrans parameter rToParam doesn't make sense
  sprintf_s(s_buf, sizeof(s_buf), "FromMin:  %4.3lf;  FromMax:  %4.3lf; FlTransKind : %u", 
            atpEdge->rFromParamMin,atpEdge->rFromParamMax, 
            (DiUInt32)(((DiAnimFlTransaction *)atpEdge)->nUpdFlags));    
  out3.append(s_buf);

  // print transaction speed
  sprintf_s(s_buf, sizeof(s_buf), "Spd:  %4.3lf;  VP:  %4.3lf", 
          atpEdge->rSpeed, agpGraph->rCurParInTransaction);
  out4.append(s_buf);

  DIASSERT(out1.length() < _LEN_ASSERT);
  DIASSERT(out2.length() < _LEN_ASSERT);
  DIASSERT(out3.length() < _LEN_ASSERT);
  DIASSERT(out4.length() < _LEN_ASSERT);
  s_animgraph_transInfo1.SetValue(out1);
  s_animgraph_transInfo2.SetValue(out2);
  s_animgraph_transInfo3.SetValue(out3);
  s_animgraph_transInfo4.SetValue(out4);
}


DiVoid DiAnimGraph::DebugUpdateClbInfo(DiAnimGraph *agpGraph)
{
  string out1("");

  //DiInt32 nI, nJ;

  sprintf_s(s_buf, sizeof(s_buf), "Callbacks. MaxN: %i;  CurN: %i",
            DIANGR_MAX_NUM_CALLBACKS, agpGraph->nNumRegisteredCallbacks);
  out1.append(s_buf);  

#ifdef DIANGR_SCREEN_DEBUG_ADVANCED  
  for (nI = 0; nI < agpGraph->nUsedCallbacksCells; nI++)
  {
    // count index in queue
    if (agpGraph->nUsedCallbacksCells < DIANGR_DEBUG_MAX_LAST_CALLBACKS)
    {
      // simple cpBuffere
      nJ = nI;
    }
    else // queue is wrapped
    {
      nJ = (agpGraph->nCallbackCellToFill + nI) % DIANGR_DEBUG_MAX_LAST_CALLBACKS;
    }
    DIASSERT(nJ >= 0 && nJ < DIANGR_DEBUG_MAX_LAST_CALLBACKS);

    // form string and render it
    DIASSERTPTR(agpGraph->seapLatestCallbacks[nJ]->cpName);
    sprintf_s(s_buf, sizeof(s_buf),"%s",agpGraph->seapLatestCallbacks[nJ]->cpName);
    
    
    // mark first and last called callbacks
    if (0 == nI)
      strcat(cpBuffer,"-old"); // the oldest callback
    if (agpGraph->nUsedCallbacksCells - 1 == nI)
      strcat(cpBuffer,"-new"); // last called callback (the newest)
  }
#endif

  // Help
  s_animgraph_helpInfo1.SetValue("Prev/next graph: ']','['");
  s_animgraph_helpInfo2.SetValue("Elem/delta/speed-/speed+: '9','0','-','+'");
}



/**
 * This function prints to screen information about anim graph
   Graph's name
   Current state: 
     type
     name of node/trans + VPar
     sequence name(s)
   Next state: 
   Target state + path if such exists
   Prev state
   Called callbacks

 *
 * @memo    Print debug info to screen
 * @return  none
 * @param   
 * @header  DiAnGr.h
 */
DiVoid DiAnimGraph::DebugUpdateInfo()
{
  if (!IsLog2ScreenEnabled())
    return;

  DiAnimGraph           *agpGraph;
  DiAnimGraphElems      geType;  

  agpGraph = _gepCurElem->agpGraph;
  if (NULL == agpGraph)
  {
    DIASSERT_ALOOF_CODE("-");
    return;
  }

  // print graph info and tweaking parameters
  DebugUpdateGraphInfo(agpGraph);
  DebugUpdateTweakInfo(agpGraph);  

  geType = agpGraph->GetCurElemType();
  
  // print nodes-specific info
  if (geType == DIANGR_NODE || geType == DIANGR_MACRONODE)
  {
    DebugUpdateNodesInfo(agpGraph);
  }

  // print transaction specific information
  if (geType == DIANGR_FLTRANSACTION)
  {
    DebugUpdateEdgesInfo(agpGraph);        
  }
  
  // print state-specific information: prev node, next node, target node (+ path)
  DebugUpdateStateInfo(agpGraph);
  
  // show callbacks info
  DebugUpdateClbInfo(agpGraph);
}

/**
 * This function 
 *
 * @memo    Navigation by the list of all registered graphs
 * @return  none
 * @param   
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiVoid DiAnimGraph::DebugSetNextGraph()
{
  if (_gepCurElem->geNext != NULL)
  {
    _gepCurElem = _gepCurElem->geNext;
  }
  else
  {
    // set first element
    _gepCurElem = _gepList;
  }
}

DiVoid DiAnimGraph::DebugSetGraph(DiAnimGraph *graph)
{
  // search whole list
  DiAnGrDbElem *curElem(_gepList);
  while (curElem != NULL)
  {
    if (curElem->agpGraph == graph)
    {
      _gepCurElem = curElem;
      break;
    }
      
    curElem = curElem->geNext;
  }

  NI_ASSERT(curElem != NULL, "Failed to find specified graph");
}


/**
 * This function 
 *
 * @memo    Navigation by the list of all registered graphs
 * @return  none
 * @param   
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiVoid DiAnimGraph::DebugSetPrevGraph()
{
  DiAnGrDbElem *gepTemp;  

  if (_gepCurElem->gePrev != NULL)
  {
    _gepCurElem = _gepCurElem->gePrev;
  }
  else
  {
    // set last element
    gepTemp = _gepList;
    while (gepTemp->geNext != NULL)
      gepTemp = gepTemp->geNext;

    _gepCurElem = gepTemp;
  }
}


/*
 * This function detects cur element in active graph and changes it's speed
 *
 * @memo    
 * @return  none
 * @param   rDelta: if it is "+" than we increase abs value of speed, otherwize - decrease
 * @author  EugBel
 */
DiVoid DiAnimGraph::_diAnGrDbChangeCurElementSpeed(DiFloat rDelta)
{
  DiAnimGraphElems  geElem;
  DiAnimNode        *anpNode;
  DiAnimFlTransaction *atpTrans;

  // get current element
  geElem = _gepCurElem->agpGraph->GetCurElemType();

  switch(geElem)
  {
    case DIANGR_NODE: case DIANGR_MACRONODE:
      anpNode = _gepCurElem->agpGraph->GetNodeData(_gepCurElem->agpGraph->GetCurNode());
      
      // speed could be both "+" and "-"
      if (anpNode->GetSpeed() > 0.0f)
        anpNode->SetSpeed(DiFMax(anpNode->GetSpeed() + rDelta, 0.0f)); 
      else
        anpNode->SetSpeed(DiFMin(anpNode->GetSpeed() - rDelta, 0.0f));     
      break;

    case DIANGR_FLTRANSACTION:
      atpTrans = _gepCurElem->agpGraph->GetTransactionData(_gepCurElem->agpGraph->GetCurTransaction(),
                                                           _gepCurElem->agpGraph->GetCurSubTransaction());
      
      // speed could be only "+"
      atpTrans->SetSpeed(DiFMax(atpTrans->GetSpeed() + rDelta, 0.0f));
      break;
    
    default:
      DIASSERT_ALOOF_CODE(_gepCurElem->agpGraph->GetDBFileName());
  }
}

/**
 * This function increases speed of current active graph
 *
 * @memo    
 * @return  none
 * @param   
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiVoid DiAnimGraph::DebugIncSpeed()
{
  DIASSERT(_dCurDelta >= DIANGRDB_DELTA_FIRST && _dCurDelta <= DIANGRDB_DELTA_LAST);
  DIASSERT(_eCurObject > DIANGRDB_OBJ_NA && _eCurObject < DIANGRDB_OBJ_FORCEDWORD);
  
  // increasing speed: don't check overflow  
  switch (_eCurObject)
  {
    case DIANGRDB_OBJ_ENTIRE_GRAPH:
      _gepCurElem->agpGraph->SetGraphSpeedCoeff(_gepCurElem->agpGraph->GetGraphSpeedCoeff() + _raDeltaCoeff[_dCurDelta]);  
      break;
    case DIANGRDB_OBJ_CUR_ELEM:
      // get type of current element in graph
      _diAnGrDbChangeCurElementSpeed(_raDeltaCoeff[_dCurDelta]);      
      break;
  }
}

/**
 * This function decreases speed of current active graph. Min value is 0
 *
 * @memo    
 * @return  none
 * @param   
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiVoid DiAnimGraph::DebugDecSpeed()
{
  DIASSERT(_dCurDelta >= DIANGRDB_DELTA_FIRST && _dCurDelta <= DIANGRDB_DELTA_LAST);
  DIASSERT(_eCurObject > DIANGRDB_OBJ_NA && _eCurObject < DIANGRDB_OBJ_FORCEDWORD);

  switch (_eCurObject)
  {
    case DIANGRDB_OBJ_ENTIRE_GRAPH:
      _gepCurElem->agpGraph->SetGraphSpeedCoeff(DiFMax(_gepCurElem->agpGraph->GetGraphSpeedCoeff() - _raDeltaCoeff[_dCurDelta], 0.0f));
      break;
    
    case DIANGRDB_OBJ_CUR_ELEM:
      // get type of current element in graph
      _diAnGrDbChangeCurElementSpeed(-_raDeltaCoeff[_dCurDelta]);      
      break;
    
    default:
      DIASSERT_ALOOF_CODE(_gepCurElem->agpGraph->GetDBFileName());
  }

}

/**
 * This function cyclically changes delta-value for graph speed tweaking
 *
 * @memo    
 * @return  none
 * @param   
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiVoid DiAnimGraph::DebugChangeSpeedCoeffPrecision()
{
  DIASSERT(_dCurDelta >= DIANGRDB_DELTA_FIRST && _dCurDelta <= DIANGRDB_DELTA_LAST);
  // need to set next precision: do it in simple & clear way
  
  // check differences
  DIASSERT(3 == DIANGRDB_DELTA_LAST);

  switch(_dCurDelta)
  {
    case DIANGRDB_DELTA_HUGE:
      _dCurDelta = DIANGRDB_DELTA_BIG;
      break;
    case DIANGRDB_DELTA_BIG:
      _dCurDelta = DIANGRDB_DELTA_MIDDLE;
      break;
    case DIANGRDB_DELTA_MIDDLE:
      _dCurDelta = DIANGRDB_DELTA_SMALL;
      break;
    case DIANGRDB_DELTA_SMALL:
      _dCurDelta = DIANGRDB_DELTA_HUGE;
      break;    
    default:
      DIASSERT_ALOOF_CODE("-");
  }
}


/**
 * This function changes object for speed tweaking (graph/cur_object)
 *
 * @memo    
 * @return  none
 * @param   
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiVoid DiAnimGraph::DebugChangeObject()
{
  DIASSERT(_eCurObject > DIANGRDB_OBJ_NA && _eCurObject < DIANGRDB_OBJ_FORCEDWORD);

  // check differences
  DIASSERT(1 == DIANGRDB_OBJ_LAST);

  switch(_eCurObject)
  {
    case DIANGRDB_OBJ_ENTIRE_GRAPH:
      _eCurObject = DIANGRDB_OBJ_CUR_ELEM;
      break;
    case DIANGRDB_OBJ_CUR_ELEM:
      _eCurObject =  DIANGRDB_OBJ_ENTIRE_GRAPH;
      break;
    default:
      DIASSERT_ALOOF_CODE("-");
  }
}


/**
 * This function saves names of sequences to show in debug mode
 *
 * @memo    
 * @return  none
 * @param   napSeqsTables
 * @param   napDbSeqNames
 * @param   nNumSequencesInTable
 * @header  DiAnGr.h
 * @library skeleton.lib
 * @author  EugBel
 * @see     
 */
DiVoid DiAnimGraph::DebugCopySeqNamesTables(DiAnimNamesArray *naSeqsTables, 
                                       DiAnimGraph *anpGraph,
                                       DiInt32 *npNumSeqsInTables)
{
  
  DiInt32             nPart, nNumParts;
  DiInt32             nNamesSize, nInfoSize;
  DiInt32             nI;
  DiUInt32            nTotalSeqNum;
  
  // first: count total number of sequences
  nNumParts    = anpGraph->GetNumParts();
  nTotalSeqNum = 0;

  for (nI = 0; nI < anpGraph->GetNumParts(); nI++)
    nTotalSeqNum += npNumSeqsInTables[nI];

  nNamesSize = nTotalSeqNum * diFRAMEID_NAMELENGTH * sizeof(DiTChar);
  nInfoSize  = nNumParts * sizeof(DiInt32);

  // second allocate memory for data and pointers
  anpGraph->npDbNumSeqsInTables = (DiInt32 *)DiMemAllocate(nInfoSize + nNamesSize + 
                                                           sizeof(DiAnimNamesArray) * nNumParts);
  DIASSERTPTR(anpGraph->npDbNumSeqsInTables );
  
  // set pointers
  anpGraph->napDbSeqNames    = (DiAnimNamesArray *)(anpGraph->npDbNumSeqsInTables + nNumParts);
  anpGraph->napDbSeqNames[0] = (DiAnimNamesArray)((DiByte *)anpGraph->napDbSeqNames + 
                                                  sizeof(DiAnimNamesArray) * nNumParts);
  //set rest pointers
  for(nI = 1; nI < nNumParts; nI++)
  {
    anpGraph->napDbSeqNames[nI] = (DiAnimNamesArray)(
                                  (DiTChar *)anpGraph->napDbSeqNames[nI - 1] + 
                                  sizeof(DiTChar) * diFRAMEID_NAMELENGTH * 
                                  npNumSeqsInTables[nI - 1]);
  }
  
  // fill tables
  for (nPart = 0; nPart < nNumParts; nPart++)
  {
    for (nI = 0; nI < npNumSeqsInTables[nPart]; nI++)
    {
      strcpy(anpGraph->napDbSeqNames[nPart][nI], naSeqsTables[nPart][nI]);  
    }
    
    // save number
    anpGraph->npDbNumSeqsInTables[nPart] = npNumSeqsInTables[nPart];
  }

}

/*
 *  Just cleanup memory
 */
DiVoid DiAnimGraph::DebugFreeNamesTable()
{
  //DIASSERTPTR(this->npDbNumSeqsInTables); // This assert may work ONLY in AnimGraph utility!
  
  if (this->npDbNumSeqsInTables != NULL)
  {
    DiMemFree(this->npDbNumSeqsInTables);
  }
}

///eugbelNSCENE///} // end of namespace NScene

#pragma warning( default : 4996 )

#endif DIANGR_SCREEN_DEBUG_GENERAL


bool AgEnableLog( const char *name, const vector<wstring> &params )
{
  bool enableLog(false);
  DiAnimGraph *graphToWatch(NULL);

  if (params.size() != 1)
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << "<enable_flag: 0 or 1>" << endl;
    return true;
  }
  else
  {
    enableLog = (bool)NGlobal::VariantValue( params[0] ).GetFloat();
    graphToWatch     = NULL; // watch all graphs
  }
  DiAnimGraph::EnableLog(enableLog, graphToWatch);

  return true;
}  

REGISTER_CMD( ag_enable_log, AgEnableLog );
