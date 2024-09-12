/*
 * @file    DiGraph.h
 * @memo    General class DiGraph 
 * @author  EugBel
 * @date    03.09.2003
 * @prefix  DiGraph
 * @header  DiGraph.h
 * @library common.lib
 */

#ifndef _DIGRAPHCPP_H_
#define _DIGRAPHCPP_H_

// *******************************************************************
// includes

///eugbelNSCENE///namespace NScene {

// *******************************************************************
// defines

// uncomment this to enable some debug functions
//#define diGR_DEBUG

// max number of graph elements in the shortest path btw 2 nodes
// used in FindShortestWay(). Equal to infinity
#define diGR_INFINITY_N       (10000)
#define diGR_NO_SUCH_ELEMENT  (diGR_INFINITY_N + 1)     

// *******************************************************************
// types

// *******************************************************************
// classes

class INeiFunctor
{
public:
  virtual void operator()( DiUInt32 ) = 0;
};

/**
 * This is graph representation class
 * Graph representation (Ex.: adjacency matrix, adjacency list, etc.)
 * Class is abstract. Functions should be implemented in classes
 * with representations themselves
 * 
 * @memo    Graph representation
 * @author  EugBel
 */
class DiGraphRepresentation
{
public:
  
  friend class DiGraph;
  
  enum ReprType
  {
    diGRT_NA              = -1,
    diGRT_ARRAY_OF_LISTS,
    diGRT_FORCEDWORD      = 0x7FFFFFFF
  };

  DiGraphRepresentation() { }
  virtual ~DiGraphRepresentation() { }

protected:

  ReprType rtType;

  DiVoid *pNodeData;
  DiVoid *pEdgeData;

  DiUInt32  nNumNodes;
  DiUInt32  nNumEdges;

  virtual DiBool AddNode(DiVoid *pData, 
                         DiUInt32 nDataSize, DiUInt32 &nGivenID) = 0;
  virtual DiBool AddEdge(DiUInt32 nNodeFromID, DiUInt32 nNodeToID,
                         DiUInt16 nWeight,
                         DiVoid *pData, DiUInt32 nDataSize, 
                         DiUInt32 &nGivenID) = 0;

  virtual       DiVoid   *GetNodeData(DiUInt32 nID) = 0;
  virtual const DiVoid   *GetNodeData(DiUInt32 nID) const = 0;
  virtual       DiVoid   *GetEdgeData(DiUInt32 nID) = 0;
  virtual const DiVoid   *GetEdgeData(DiUInt32 nID) const = 0;
  virtual       DiUInt16 GetEdgeWeight(DiUInt32 nID) const = 0;
  virtual       void     SetEdgeWeight(DiUInt32 nID, DiUInt16 weight) = 0;
  
  virtual DiBool   ForAllNeighbours(DiUInt32 nNodeID, INeiFunctor* functor) = 0;
  virtual DiUInt16 GetDistance(DiUInt32 nNodeFromID, DiUInt32 nNodeToID) const = 0;
  virtual DiUInt32 GetEdgeID(DiUInt32 nNodeFromID, DiUInt32 nNodeToID) const = 0;

  DiUInt32 GetNumNodes() const;
  DiUInt32 GetNumEdges() const;
  
  #ifdef diGR_DEBUG
    virtual DiBool PrintToConsole()  = 0;
  #endif
};

/**
 * This class implemets graph's representation 
 * 
 * @memo    graph representation implementation
 * @author  EugBel
 */
//  ___ ___ ___
// |___|___|___|
//   |   |   |
//   V   V   V
//  |_| |_| |_|
//   |   |   |
//   V   V   V
//  |_| |_| |_|
//   |   |   |
//   V   V   V
//      ... 
// NOTE: deleting of nodes is NOT supported, because
// we have ENTIRE graph as ONE piece in memory => we can delete but
// after that we can't add data bigger then it was in deleted element
// This representation is used for animation graph DiAnimGraph
class DiGraphListsArray : public DiGraphRepresentation
{
private:
  struct ListNode
  {
    DiUInt32        nNodeID;
    DiUInt32        nEdgeID;
    struct ListNode *lnpNext;
  };

  struct ArrayNode
  {
    DiVoid    *pData;
    ListNode  *lnpRoot;
  };

  struct ArrayEdge
  {
    DiUInt16 nWeight;
    DiVoid   *pData;
  };

  // constant pointers
  ArrayNode *anpNodes;
  ArrayEdge *aepEdges;

  // variable params
  ListNode  *lnpFreeSpace;
  DiUInt32  nFreeNodeID;
  DiUInt32  nFreeEdgeID;
  
  
public:
  // constructor
  DiGraphListsArray(DiUInt32 nNumNodes,      
                                     DiUInt32 nNumEdges, 
                                     DiUInt32 nNodesDataSize, 
                                     DiUInt32 nEdgesDataSize);
  ~DiGraphListsArray();

private:
  DiBool   AddNode(DiVoid *pData, DiUInt32 nDataSize, DiUInt32 &nGivenID);
  DiBool   AddEdge(DiUInt32 nNodeFromID, DiUInt32 nNodeToID, DiUInt16 nWeight,
                   DiVoid *pData, DiUInt32 nDataSize, 
                   DiUInt32 &nGivenID);

        DiVoid   *GetNodeData(DiUInt32 nID);
  const DiVoid   *GetNodeData(DiUInt32 nID) const;
        DiVoid   *GetEdgeData(DiUInt32 nID);
  const DiVoid   *GetEdgeData(DiUInt32 nID) const;
        DiUInt16 GetEdgeWeight(DiUInt32 nID) const;
        void     SetEdgeWeight(DiUInt32 nID, DiUInt16 weight);

  DiBool   ForAllNeighbours(DiUInt32 nNodeID, INeiFunctor* functor);
  DiUInt16 GetDistance(DiUInt32 nNodeFromID, DiUInt32 nNodeToID) const ;
  DiUInt32 GetEdgeID(DiUInt32 nNodeFromID, DiUInt32 nNodeToID) const ;
  
  #ifdef diGR_DEBUG
    DiBool   PrintToConsole();
  #endif
};

/**
 * This class is general class for graphs
 * 
 * @memo    graph
 * @author  EugBel
 */

//#ifndef ANIMGRAPH_DLL_LINKAGE
//#define ANIMGRAPH_DLL_LINKAGE  __declspec(dllexport)
//#endif
class /*ANIMGRAPH_DLL_LINKAGE*/ DiGraph
{
  friend class DiGraphRepresentation;

public:  
  enum GraphType
  {
    diGT_NA          = -1,
    diGT_DIRECTED,
    diGT_UNDIRECTED,
    diGT_FORCEDWORD  = 0x7FFFFFFF
  };

private:
  // Graph representation (contains all data)
  DiGraphRepresentation *rpRepr;

  GraphType gtType;

public:
  // general
  DiGraph(DiUInt32 nNumNodes,      DiUInt32 nNumEdges, 
                DiUInt32 nNodesDataSize, DiUInt32 nEdgesDataSize,
                DiBool &bResult,
                GraphType gtType = diGT_DIRECTED,
                DiGraphRepresentation::ReprType grtType = 
                DiGraphRepresentation::diGRT_ARRAY_OF_LISTS);
  ~DiGraph();

    // graph use
  DiBool AddNode(DiVoid *pData, DiUInt32 nDataSize, DiUInt32 &nGivenID);
  DiBool AddEdge(DiUInt32 nNodeFromID, DiUInt32 nNodeToID, DiUInt16 nWeight,
                 DiVoid *pData, DiUInt32 nDataSize, 
                 DiUInt32 &nGivenID);
  

  DiVoid        *GetNodeData(DiUInt32 nID);
  const DiVoid  *GetNodeData(DiUInt32 nID) const;
  DiVoid        *GetEdgeData(DiUInt32 nID);
  const DiVoid  *GetEdgeData(DiUInt32 nID) const;
  DiUInt16      GetEdgeWeight(DiUInt32 nID) const;
  void          SetEdgeWeight(DiUInt32 nID, DiUInt16 weight);

  // getting node neighbors
  DiBool   ForAllNeighbours(DiUInt32 nNodeID, INeiFunctor* functor) const;
  
  DiBool FindShortestWay(DiUInt32 nNodeFromID, DiUInt32 nNodeToID,  
													DiUInt32 &nNumNodesInFoundPath, const nstl::string& filename,
													DiUInt32 *npFirstNodeID = NULL) const;

  DiBool GetNodesOfShortestPath(DiUInt32 *npUserAllocatedBuffer) const;
  DiVoid ClearPath() const;

  // simple methods

  DiUInt32 GetNumNodes() const;
  DiUInt32 GetNumEdges() const;
  DiBool NodeExist(DiUInt32 nID) const;
  DiBool EdgeExist(DiUInt32 nID) const;
  DiUInt32 GetEdgeID(DiUInt32 nNodeFromID, DiUInt32 nNodeToID) const;
  DiUInt16 GetDistance(DiUInt32 nNodeFromID, DiUInt32 nNodeToID) const;

  #ifdef diGR_DEBUG
    DiBool PrintToConsole();
  #endif

private:
  DiUInt32  *npShortestPath; // pointer to shortest path if needed
  mutable DiUInt32  nNumNodesOnPath; // number of nodes on this path. Intentionally mutable to have const-functions ClearPath() and FindShortestWay() - logically they should be const functions
};


// *******************************************************************
// prototypes

///eugbelNSCENE///} // end of namespace NScene

#endif // ifndef _DIGRAPHCPP_H_
