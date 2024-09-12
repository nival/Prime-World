/*
 * @file    DiGraph.cpp
 * @memo    Functions of DiGraph and DiGraphRepresentation classes
 * @author  EugBel
 * @date    03.09.2003
 * @prefix  DiGraph
 * @header  DiGraph.h
 * @library common.lib
 */
 
// *******************************************************************
// includes
#include "stdafx.h"

#include <stdio.h>
#include <string.h>

#include "DiAnGrUtils.h"
#include "DiGraph.h"
#include "DiAnGr.h"


///eugbelNSCENE///namespace NScene {
// *******************************************************************
// defines


// *******************************************************************
// local data

// *******************************************************************
// functions

/**
 * This function retrieves number of nodes in graph
 *
 * @memo    Get number of nodes
 * @return  number of nodes
 * @author  EugBel
 */
DiUInt32 DiGraphRepresentation::GetNumNodes() const 
{
  DIFUNCTION("GetNumNodes");
  DIASSERT(nNumNodes);
  DIRETURN(nNumNodes);
}

/**
 * This function retrieves number of edges in graph
 *
 * @memo    Get number of edges
 * @return  number of edges
 * @author  EugBel
 */
DiUInt32 DiGraphRepresentation::GetNumEdges() const 
{
  DIFUNCTION("GetNumEdges");

  DIASSERT(nNumEdges > 0 || 1 == nNumNodes);
  DIRETURN(nNumEdges);
}

/**
 * This is DiGraph constructor
 *
 * @memo    constructor
 * @param   nNumNodes      number of nodes in graph
 * @param   nNumEdges      number of edges in graph
 * @param   nNodesDataSize size of entire nodes data
 * @param   nEdgesDataSize size of entire edges data
 * @param   bResult        result of function(true - ok, false - otherwise)
 * @param   gtType         type of graph
 * @param   grtType        type of graph representation
 * @header  DiGraphCpp.h
 * @author  EugBel
 * @see     
 */
DiGraph::DiGraph(DiUInt32 nNumNodes,      DiUInt32 nNumEdges, 
                DiUInt32 nNodesDataSize, DiUInt32 nEdgesDataSize,
                DiBool &bResult,
                GraphType gtType,
                DiGraphRepresentation::ReprType grtType)
{
  DIFUNCTION("DiGraph");
  
  rpRepr = NULL;

  // asserts
  DIASSERT(diGT_DIRECTED == gtType);
  DIASSERT(DiGraphRepresentation::diGRT_ARRAY_OF_LISTS == grtType);
  

  // try-block of creating object of the class
  switch(grtType)
  {
    case DiGraphRepresentation::diGRT_ARRAY_OF_LISTS:
      if (diGT_DIRECTED != gtType)
      {
        // don't support this
        DIASSERT_ALOOF_CODE("-");
        rpRepr = NULL;
        bResult = FALSE;
        DIRETURNVOID();
      }
      rpRepr = DI_NEW(DiGraphListsArray(nNumNodes,      nNumEdges, 
                                     nNodesDataSize, nEdgesDataSize));
    break;
    
    default:
      DIASSERT_ALOOF_CODE("-");
      rpRepr   = NULL;
      bResult  = FALSE;
      DIRETURNVOID();
    break;
  }
  
  
  if (NULL == rpRepr)
  {
    bResult = FALSE;
    DIRETURNVOID();
  }
   
  // set parameters
  this->gtType               = gtType;
  
  // allocate max possible buffer for path in graph
  this->npShortestPath  = (DiUInt32  *)DiMemAllocate(nNumNodes * sizeof(DiUInt32));
  DIASSERTPTR(this->npShortestPath);
  this->nNumNodesOnPath = 0;

  bResult = TRUE;
}

DiGraph::~DiGraph() 
{ 
  if ( npShortestPath != NULL )
  {
    DiMemFree( npShortestPath );
    npShortestPath = NULL;
  }

  if ( rpRepr != NULL )
  {
    delete rpRepr;
    rpRepr = NULL;
  }
}
// set of functions that just call functions of the representation class
DiBool DiGraph::AddNode(DiVoid *pData, DiUInt32 nDataSize, DiUInt32 &nGivenID)
{
  DIFUNCTION("AddNode");
  DIRETURN(rpRepr->AddNode(pData, nDataSize, nGivenID));
}

DiBool DiGraph::AddEdge(DiUInt32 nNodeFromID, DiUInt32 nNodeToID, DiUInt16 nWeight,
                        DiVoid *pData, DiUInt32 nDataSize, 
                        DiUInt32 &nGivenID)
{
  DIFUNCTION("AddEdge");
  DIRETURN(rpRepr->AddEdge(nNodeFromID, nNodeToID, nWeight, pData, nDataSize, nGivenID));
}

DiVoid *DiGraph::GetNodeData(DiUInt32 nID)
{
  DIFUNCTION("GetNodeData");
  DIRETURN(rpRepr->GetNodeData(nID));
}

const DiVoid *DiGraph::GetNodeData(DiUInt32 nID) const
{
  DIFUNCTION("GetNodeData");
  DIRETURN(rpRepr->GetNodeData(nID));
}

DiVoid *DiGraph::GetEdgeData(DiUInt32 nID)
{
  DIFUNCTION("GetEdgeData");
  DIRETURN(rpRepr->GetEdgeData(nID));
}

const DiVoid *DiGraph::GetEdgeData(DiUInt32 nID) const
{
  DIFUNCTION("GetEdgeData");
  DIRETURN(rpRepr->GetEdgeData(nID));
}

DiUInt16 DiGraph::GetEdgeWeight(DiUInt32 nID) const
{
  DIFUNCTION("GetEdgeWeight");
  DIRETURN(rpRepr->GetEdgeWeight(nID));
}

void DiGraph::SetEdgeWeight(DiUInt32 nID, DiUInt16 weight)
{
  rpRepr->SetEdgeWeight(nID, weight);
}

DiBool DiGraph::ForAllNeighbours(DiUInt32 nNodeID, INeiFunctor* functor) const
{
  DIFUNCTION("ForAllNeighbours");
  DIRETURN(rpRepr->ForAllNeighbours(nNodeID, functor));
}

/**
 * This function clears path found by FindShortestWay()
 *
 * @memo    Clear found path
 * @return  none
 * @param   
 * @header  DiGraph.h
 * @library common.lib
 * @author  EugBel
 * @see     FindShortestWay()
 */
DiVoid DiGraph::ClearPath() const
{
  nNumNodesOnPath = 0;
}

/**
 * This function finds shortest way between 2 nodes in graph
 *
 * @memo    Find shortest way between 2 nodes
 * @return  TRUE on success, FALSE otherwise
 * @param   nNodeFromID           start node
 * @param   nNodeToID             end node
 * @param   nNumNodesInFoundPath  number of nodes in path
 * @param   npFirstNodeID         first node in path
 * @author  EugBel
 */
DiBool DiGraph::FindShortestWay(DiUInt32 nNodeFromID, DiUInt32 nNodeToID,  
																DiUInt32 &nNumNodesInFoundPath, const nstl::string& filename,
                                DiUInt32 *npFirstNodeID) const
{

  DiUInt16  *naLengths;// naLength[2] - length of path from Start to vertice N2
  DiUInt32  *naPath;   // naPath[2] - vertice that stands before 2 in the path
  DiByte    *naVertsUsed; //naVerticesUsed[2]==1 <=> vertice 2 is used
  DiUInt32  nID, nNumNodes, nCurVert;
  DiUInt32  nNum, *npBuffer, nI, nTempVert;
  DiFloat   nMax;

  DIFUNCTION("FindShortestWay");

  nNumNodes = GetNumNodes();
  DIASSERT(nNumNodes > 0);
  
  if (nNodeFromID >= nNumNodes || nNodeToID   >= nNumNodes)
  {
    DIASSERT_ALOOF_CODE(NStr::StrFmt("%s try to go to bad node", filename.c_str()));
    ClearPath();
    DIRETURN(FALSE);
  }

  // check this at upper level: not here.
  if (nNodeFromID == nNodeToID)
  {
    DIASSERT_ALOOF_CODE(NStr::StrFmt("%s try to go to same node", filename.c_str()));
    ClearPath();
    DIRETURN(FALSE);
  }

  // simple and most often case: check neighbours of the node
  // @TODO: perhaps this can optimize function

  // main algorithm: Dijkstra's algorithm (see Novikov, Descreet Math, p.230)
  // we need 3 arrays with NumElems == NumNodes;
  // third array could be packed (it uses only TRUE/FALSE components)
  // @TODO: pack third array (best, if some class like BitArray will be 
  // written)

  // allocate arrays
  naPath   = (DiUInt32 *)DiMemAllocateTmp(nNumNodes * (sizeof(DiUInt32) + sizeof(DiByte) + sizeof(DiUInt16) ));
  if (NULL == naPath)
  {
    ClearPath();
    DIRETURN(FALSE);
  }
  naLengths      = (DiUInt16 *)(naPath + nNumNodes);
  naVertsUsed = (DiByte *)(naLengths + nNumNodes);

  // init arrays
  for (nID = 0; nID < nNumNodes; nID++)
  {
    naLengths[nID]   = diGR_INFINITY_N;
    naVertsUsed[nID] = 0;
  }
  // no vertice before Start in the path

  NI_ASSERT( nNodeFromID >= 0 && nNodeFromID < nNumNodes, NStr::StrFmt("I write in another's memory! idx = %d", nNodeFromID ) );
  naPath[nNodeFromID]      = diGR_NO_SUCH_ELEMENT; 

  naLengths[nNodeFromID]   = 0; // S->S length is 0
  naVertsUsed[nNodeFromID] = 1; // we now S->S path

  nCurVert = nNodeFromID; // set current vertice

  while(TRUE)
  {

    // get neighbours of current vertice
    nNum = ((DiAnimNode*)GetNodeData(nCurVert))->GetNumNeighbours();

    if (nNum == 0)
    {
      if (nCurVert == nNodeFromID)
      {
        //DIASSERT_ALOOF_CODE(GetDBFileName()); 
        // there is no path from start point (only death => no way out)=> return false
        if (naPath != NULL)
           DiMemFreeTmp(naPath);
        
        ClearPath();
        DIRETURN( FALSE );
      }
    }
    else
    {
      class DistanceGetter : public INeiFunctor
      {
        DiUInt16  *naLengths;
        DiUInt32  *naPath;
        DiByte    *naVertsUsed;
        DiUInt32 nCurVert;
        DiUInt32 nNumNodes;
        const DiGraph* g;
      public:
        DistanceGetter( DiUInt16* naLengths, DiUInt32* naPath, DiByte* naVertsUsed, DiUInt32 nCurVert, 
          const DiGraph* g, DiUInt32 nNumNodes )
          : naLengths(naLengths), naPath(naPath), naVertsUsed(naVertsUsed), nCurVert(nCurVert), g(g), nNumNodes(nNumNodes)
        {}
        virtual void operator()( DiUInt32 nodeId )
        {
          DiUInt16 dist = naLengths[nCurVert] + g->GetDistance(nCurVert,nodeId);

          if (0 == naVertsUsed[nodeId] && naLengths[nodeId] > dist)
          {
            NI_ASSERT( nodeId >= 0 && nodeId < nNumNodes, NStr::StrFmt("I write in another's memory! idx = %d", nodeId ) );

            // found more short path from Start to current vertice
            naLengths[nodeId] = dist;

            // remember this path
            naPath[nodeId] = nCurVert;
          }
        }
      } dg(naLengths, naPath, naVertsUsed, nCurVert, this, nNumNodes);
 
      ForAllNeighbours(nCurVert, &dg);
//was:
//       npBuffer = (DiUInt32 *)DiMemAllocateTmp(nNum * sizeof(DiUInt32));
//       DIASSERT(npBuffer);
// 
//       GetNeighbours(nCurVert, npBuffer);  
// 
//       for (nI = 0; nI < nNum; nI++)
//       {
//         nTempVert = npBuffer[nI];
// 
//         if (0 == naVertsUsed[nTempVert] &&
//             naLengths[nTempVert] > 
//             naLengths[nCurVert] + GetDistance(nCurVert,nTempVert))
//         {
//           // found more short path from Start to current vertice
//           naLengths[nTempVert] = 
//                             naLengths[nCurVert] + GetDistance(nCurVert,nTempVert);
// 
//           // remember this path
//           naPath[nTempVert] = nCurVert;
//         }
//       }
//       // TODO: optimize this new/delete
//       DiMemFreeTmp(npBuffer);
    }

    nCurVert = diGR_NO_SUCH_ELEMENT;
    nMax     = diGR_INFINITY_N;

    // search for the end of shortest path
    for (nTempVert = 0; nTempVert < nNumNodes; nTempVert++)
    {
      if (0 == naVertsUsed[nTempVert] && 
          naLengths[nTempVert] < nMax)
      {
        nCurVert = nTempVert;
        nMax     = naLengths[nTempVert];
      }
    }

    // check
    if (diGR_NO_SUCH_ELEMENT == nCurVert)
    {
      if (naPath != NULL)
         DiMemFreeTmp(naPath);
      // no path to the End
      ClearPath();
      DIRETURN( FALSE );
    }

    if (nCurVert == nNodeToID)
    {
      // path is found
      break;
    }

    NI_ASSERT( nCurVert >= 0 && nCurVert < nNumNodes, NStr::StrFmt("I write in another's memory! idx = %d", nCurVert ) );

    // we found shortest way from Start to current vertice
    naVertsUsed[nCurVert] = 1;

  } // end of while()

  // get sorted output array: go from the End and copy vertices
  // we need temporary array
  npBuffer = (DiUInt32 *)DiMemAllocateTmp(nNumNodes * sizeof(DiUInt32));
  DIASSERTPTR(npBuffer);
  nI       = 0;
  nCurVert = nNodeToID;
  while (nCurVert != diGR_NO_SUCH_ELEMENT)
  {
    NI_ASSERT( nI >= 0 && nI < nNumNodes, NStr::StrFmt("I write in another's memory! idx = %d", nI ) );
    npBuffer[nI++] = nCurVert;
    nCurVert = naPath[nCurVert];
  }
  // now we have back-sorted path in npBuffer[]
  nNumNodesInFoundPath = nI;
  nNumNodesOnPath    = nNumNodesInFoundPath; // save to internal var
  if (npFirstNodeID != NULL)
  {
    // don't forget that first vertex - is start
    *npFirstNodeID = npBuffer[(nNumNodesInFoundPath - 1) - 1];
  }

  // saving path...
  for (nI = 0; nI < nNumNodesInFoundPath; nI++)
    npShortestPath[nI] = npBuffer[nNumNodesInFoundPath - nI - 1];

  // cleanup memory
  DiMemFreeTmp(npBuffer);
  DiMemFreeTmp(naPath);

  DIRETURN( TRUE );
}

/**
 * This function returns array of nodes from the shortest path
 * found using FindShortestWay()
 *
 * @memo    Get found path
 * @return  TRUE on success, FALSE otherwise
 * @param   npBuf
 * @author  EugBel
 */
DiBool DiGraph::GetNodesOfShortestPath(DiUInt32 *npUserAllocatedBuffer) const
{
  DIFUNCTION("GetNodesOfShortestPath");

  if (NULL == npShortestPath || 0 == nNumNodesOnPath)
    DIRETURN( FALSE );

  DIASSERTPTR(npUserAllocatedBuffer);

  memcpy(npUserAllocatedBuffer, npShortestPath, 
         sizeof(DiUInt32) * nNumNodesOnPath);
  DIRETURN(TRUE);
}

/**
 * This function adds node to graph
 *
 * @memo    Add node to graph
 * @return  TRUE on success, FALSE otherwise
 * @param   pData      user data
 * @param   nDataSize  size of data
 * @param   npGivenID  ID that was given to added node
 */
DiBool DiGraphListsArray::AddNode(DiVoid *pData, DiUInt32 nDataSize, 
                                  DiUInt32 &nGivenID)
{
  DIFUNCTION("AddNode");

  // check income parameters
  DIASSERT(pData != NULL);
  DIASSERT(nDataSize > 0);

  // add data to graph: we now that nodes will never be deleted => we
  // change pointer to all lists
  memcpy(pNodeData,pData,nDataSize);
  
  DIASSERT(NULL == anpNodes[nFreeNodeID].pData);
  // remember it and get nodeID
  anpNodes[nFreeNodeID].pData   = pNodeData;
  anpNodes[nFreeNodeID].lnpRoot = NULL;
  nGivenID                      = nFreeNodeID;

  // change internal graph parameters
  pNodeData = (DiVoid *)((DiByte *)pNodeData + nDataSize);
  DIASSERT(pNodeData <= pEdgeData); // check line above
  nFreeNodeID++;

  DIRETURN( TRUE );
}

/**
 * This function retrieves node data
 *
 * @memo    Get node data
 * @return  none
 * @param   nID  - node ID
 * @author  EugBel
 */
DiVoid *DiGraphListsArray::GetNodeData(DiUInt32 nID)
{
  DIFUNCTION("GetNodeData");
  
  if (nID >= nNumNodes)
  {
    DIASSERT_ALOOF_CODE("-");
    DIRETURN( NULL );
  }
  
  DIRETURN( anpNodes[nID].pData );
}

const DiVoid *DiGraphListsArray::GetNodeData(DiUInt32 nID) const
{
  DIFUNCTION("GetNodeData");

  if (nID >= nNumNodes)
  {
    DIASSERT_ALOOF_CODE("-");
    DIRETURN( NULL );
  }

  DIRETURN( anpNodes[nID].pData );
}


/**
 * This function adds edge to graph
 *
 * @memo    Add edge to graph
 * @return  TRUE on success, FALSE otherwise
 * @param   pData      user data
 * @param   nDataSize  size of data
 * @param   npGivenID  ID that was given to added edge
 */
DiBool DiGraphListsArray::AddEdge(DiUInt32 nNodeFromID, DiUInt32 nNodeToID, DiUInt16 nWeight,
                                  DiVoid *pData, DiUInt32 nDataSize, 
                                  DiUInt32 &nGivenID)
{
  ListNode  *npCur, *npPrev;

  DIFUNCTION("AddEdge");
  
  // check income parameters
  DIASSERT(pData != NULL);
  DIASSERT(nDataSize > 0);
  DIASSERT(nWeight   > 0.0f);

  // add data to graph: we now that edges will never be deleted => we
  // change pointer to all lists
  memcpy(pEdgeData,pData,nDataSize);
  
  DIASSERT(NULL == aepEdges[nFreeEdgeID].pData);
  // remember data and get edgeID
  aepEdges[nFreeEdgeID].pData   = pEdgeData;
  aepEdges[nFreeEdgeID].nWeight = nWeight;
  nGivenID                      = nFreeEdgeID;

  // add edge to NodeFrom's list
  npCur  = anpNodes[nNodeFromID].lnpRoot;
  npPrev = NULL;

  while (npCur != NULL)
  {
    npPrev = npCur;
    npCur = npCur->lnpNext;
  }

  if (NULL == npPrev)
    anpNodes[nNodeFromID].lnpRoot = lnpFreeSpace;
  else
    npPrev->lnpNext         = lnpFreeSpace;
  
  //npCur                   = m_lnpFreeSpace;
  //npPrev->lnpNext         = m_lnpFreeSpace;
  lnpFreeSpace->nNodeID = nNodeToID;
  lnpFreeSpace->nEdgeID = nGivenID;
  lnpFreeSpace->lnpNext = NULL;


  // change internal graph parameters
  nFreeEdgeID++;
  lnpFreeSpace++;
  pEdgeData = (DiVoid *)((DiByte *)pEdgeData + nDataSize);
  DIASSERT(lnpFreeSpace <= pNodeData);

  DIRETURN( TRUE );
}

/**
 * This function retrieves edge data
 *
 * @memo    Get edge data
 * @return  none
 * @param   nID  - edge ID
 * @author  EugBel
 */
DiVoid *DiGraphListsArray::GetEdgeData(DiUInt32 nID)
{
  DIFUNCTION("GetEdgeData");

  if (nID >= nNumEdges)
  {
    DIASSERT_ALOOF_CODE("-");
    DIRETURN( NULL );
  }
  
  DIRETURN(aepEdges[nID].pData);
}
const DiVoid *DiGraphListsArray::GetEdgeData(DiUInt32 nID) const
{
  DIFUNCTION("GetEdgeData");

  if (nID >= nNumEdges)
  {
    DIASSERT_ALOOF_CODE("-");
    DIRETURN( NULL );
  }

  DIRETURN(aepEdges[nID].pData);
}


/**
 * This function retrieves weigtht of the edge
 *
 * @memo    Get edge weight
 * @return  none
 * @param   nID  - edge ID
 * @author  EugBel
 */
DiUInt16 DiGraphListsArray::GetEdgeWeight(DiUInt32 nID) const 
{
  DIFUNCTION("GetEdgeWeight");

  if (nID >= nNumEdges)
  {
    DIASSERT_ALOOF_CODE("-");
    DIRETURN(0);
  }
  
  DIRETURN(aepEdges[nID].nWeight);
}

void DiGraphListsArray::SetEdgeWeight(DiUInt32 nID, DiUInt16 weight)
{
  if (nID >= nNumEdges)
  {
    DIASSERT_ALOOF_CODE("-");
  }

  aepEdges[nID].nWeight = weight;
}

DiGraphListsArray::DiGraphListsArray(DiUInt32 nNumNodes,      
                                     DiUInt32 nNumEdges, 
                                     DiUInt32 nNodesDataSize, 
                                     DiUInt32 nEdgesDataSize)
{
  DiUInt32 nNodesArraySize, nEdgesArraySize, nListsSize;
  DiUInt32 nNodeDataArraySize, nEdgeDataArraySize;
  DiUInt32 nTotalSize;
  DiUInt32 nI;

  DIFUNCTION("DiGraphListsArray");
  
  // allocate memory
  // Structure in memory:
  // 
  // NodeID | pData | list           nNodesArraySize
  // EdgeID | pData                  nEdgesArraySize
  // All lists from main structure   nListsSize
  // NodeDataArray                   nNodeDataArraySize
  // EdgeDataArray                   nEdgeDataArraySize
  
  // count total memory
  nNodesArraySize    = sizeof(ArrayNode) * nNumNodes;
  nEdgesArraySize    = sizeof(ArrayEdge) * nNumEdges;
  nListsSize         = sizeof(ListNode)  * nNumEdges;
  nNodeDataArraySize = sizeof(DiByte)    * nNodesDataSize;
  nEdgeDataArraySize = sizeof(DiByte)    * nEdgesDataSize;

  nTotalSize = nNodesArraySize + nEdgesArraySize + nListsSize +
               nNodeDataArraySize + nEdgeDataArraySize;
  
  // setup pointers
  
  anpNodes = (ArrayNode *)(DI_NEW(DiByte)[nTotalSize]);
  if (NULL == anpNodes)
  {
    DIASSERTMSG(FALSE,"Failed to allocate memory");
    // pseudo-init pointers to have crash :(
    anpNodes     = NULL;
    aepEdges     = NULL;
    lnpFreeSpace = NULL;
    pNodeData    = NULL;
    pEdgeData    = NULL;
    DIRETURNVOID();
  }

  aepEdges = (ArrayEdge *)((DiByte *)anpNodes + nNodesArraySize);

  lnpFreeSpace = (ListNode  *)((DiByte *)aepEdges + nEdgesArraySize);

  pNodeData = (DiVoid *)((DiByte *)lnpFreeSpace + nListsSize);

  pEdgeData = (DiVoid *)((DiByte *)pNodeData + nNodeDataArraySize);

  // init data
  this->nFreeNodeID = 0;
  this->nFreeEdgeID = 0;
  this->nNumNodes   = nNumNodes;
  this->nNumEdges   = nNumEdges;
  this->rtType      = diGRT_ARRAY_OF_LISTS; 

  // init arrays
  for (nI = 0; nI < nNumNodes; nI++)
    anpNodes[nI].pData = NULL;
  for (nI = 0; nI < nNumEdges; nI++)
    aepEdges[nI].pData = NULL;

  DIRETURNVOID();
}

/**
 * This function is destructor
 *
 * @memo    destructor
 */
DiGraphListsArray::~DiGraphListsArray()
{
  DIFUNCTION("~DiGraphListsArray");
  // cleanup memory (delete allocated memory) NOTE: only ONE pointer
  delete [] anpNodes;

  DIRETURNVOID();
}

/**
 * This function get array of neighbours' IDs
 *
 * @memo    get neighbours
 * @return  TRUE on success, FALSE otherwise
 * @param   npUserAllocatedBuffer
 * @header  
 * @library 
 * @author  EugBel
 * @see     
 */
DiBool DiGraphListsArray::ForAllNeighbours(DiUInt32 nNodeID, INeiFunctor* functor)
{
  DIFUNCTION("");
  
  DiUInt32 nNum = 0;

  ListNode *lnpCur;

  DIASSERT(nNodeID < nNumNodes);
  lnpCur = anpNodes[nNodeID].lnpRoot;

  while (lnpCur != NULL)
  {
    (*functor)( lnpCur->nNodeID );
    lnpCur = lnpCur->lnpNext;
    nNum++;
  }

  return nNum;
}



/**
 * This function returns distance btw two nodes
 *
 * @memo    Get distance btw two nodes
 * @return  distance btw two nodes
 * @param   nNodeFromID
 * @param   nNodeToID
 * @header  DiGraphCpp.h
 * @author  EugBel
 */
DiUInt16 DiGraphListsArray::GetDistance(DiUInt32 nNodeFromID, 
                                        DiUInt32 nNodeToID) const 
{
  DiUInt32 nEdgeID;

  //ListNode *lnpCur = anpNodes[nNodeFromID].lnpRoot;

  DIFUNCTION("GetDistance");

  if (nNodeFromID >= GetNumNodes() || nNodeToID >= GetNumNodes())
  {
    DIASSERT_ALOOF_CODE("-");
    DIRETURN(diGR_INFINITY_N);
  }
  // dummy case
  if (nNodeFromID == nNodeToID)
  {
    DIRETURN(0);
  }
  
  nEdgeID = GetEdgeID(nNodeFromID, nNodeToID);
  if (diGR_NO_SUCH_ELEMENT == nEdgeID)
  {
    DIRETURN(diGR_INFINITY_N);  
  }

  // return distance
  DIRETURN(aepEdges[nEdgeID].nWeight);
}

#ifdef diGR_DEBUG
// temporary debug function
DiBool DiGraphListsArray::PrintToConsole()
{
  DiUInt32 nNodeID;
  ListNode *lnpCur;

  printf("\nGraph: ");
  for (nNodeID = 0; nNodeID < GetNumNodes(); nNodeID++)
  {
    printf("\nNodeID = %u; Data = '%i';\n\tList: ",nNodeID,
           (*((DiInt32 *)anpNodes[nNodeID].pData)));
    
    lnpCur = anpNodes[nNodeID].lnpRoot;
    while (lnpCur != NULL)
    {
      printf("(%u,%u)",lnpCur->nNodeID,lnpCur->nEdgeID);
      lnpCur = lnpCur->lnpNext;
    }
  }

  return TRUE;
}
#endif

/**
 * This function gets ID of edge that connects two given nodes
 *
 * @memo    Get edge's ID 
 * @return  ID of the edge on success, diGR_NO_SUCH_ELEMENT if fail
 * @param   nNodeFromID  start node
 * @param   nNodeToID    end node
 * @header  DiGraph.h
 * @library common.lib
 * @author  EugBel
 */
DiUInt32 DiGraphListsArray::GetEdgeID(DiUInt32 nNodeFromID, DiUInt32 nNodeToID) const 
{
  ListNode *lnpCur;

  DIFUNCTION("GetEdgeID");

  if (nNodeFromID >= GetNumNodes() || nNodeToID >= GetNumNodes())
  {
    DIASSERT_ALOOF_CODE("-");
    DIRETURN(diGR_NO_SUCH_ELEMENT);
  }

  lnpCur = anpNodes[nNodeFromID].lnpRoot;
  while (lnpCur != NULL)
  {
    if (lnpCur->nNodeID == nNodeToID)
      DIRETURN(lnpCur->nEdgeID);
    lnpCur = lnpCur->lnpNext;
  }
    
  DIRETURN(diGR_NO_SUCH_ELEMENT);
} // end of GetEdgeID


DiUInt32 DiGraph::GetNumNodes() const
{ 
  return rpRepr->GetNumNodes();
}

DiUInt32 DiGraph::GetNumEdges() const
{
  return rpRepr->GetNumEdges();
}

DiBool DiGraph::NodeExist(DiUInt32 nID) const
{
  return (nID < GetNumNodes());
}

DiBool DiGraph::EdgeExist(DiUInt32 nID) const
{
  return (nID < GetNumEdges());
}

DiUInt32 DiGraph::GetEdgeID(DiUInt32 nNodeFromID, DiUInt32 nNodeToID) const
{
  return rpRepr->GetEdgeID(nNodeFromID, nNodeToID);
}

DiUInt16 DiGraph::GetDistance(DiUInt32 nNodeFromID, DiUInt32 nNodeToID) const
{
  return rpRepr->GetDistance(nNodeFromID, nNodeToID);
}

#ifdef diGR_DEBUG
DiBool DiGraph::PrintToConsole()
{
  return rpRepr->PrintToConsole();
}
#endif

///eugbelNSCENE///} // end of namespace NScene