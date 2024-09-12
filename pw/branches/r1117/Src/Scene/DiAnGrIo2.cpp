/*
* @file    DiAnGrIo.cpp
* @memo    DiAnimGraph functions that deal with input/output
* @author  EugBel
* @date    04.02.2004
* @prefix  
* @header  
* @library 
*/

// *******************************************************************
// includes
#include "stdafx.h"

#include <string.h>

#include "DiAnGrUtils.h"
#include "DiAnGr.h"

#pragma warning (disable : 4996)

///eugbelNSCENE///namespace NScene {

namespace
{
  const int s_numAnimatedPartsInModel = 1; // synonym to "NumSequences"
  const DiInt32 ANIM_MAX_SEQS_PER_FILE = 60;

  struct CreateParams
  {
    CreateParams()
      : npSeqNum(NULL)
      , anpNamesArr(NULL)
      //, m_agpAnimGraph(NULL)
      //, nmpNodesNames(NULL)
    {}
    //DiInt32           nClumpsNum;
    DiInt32           *npSeqNum;
    //DiClump           **clpClumps;
    //DiEntireAnimBlock **eapAnim;
    //DiTChar           cpCSVName[_MAX_PATH];
    DiAnimNamesArray  *anpNamesArr;
    //DiAnGrNodesMap    *nmpNodesNames;
    //DiAnimGraph       *m_agpAnimGraph;
    //DiAnimFileNames   fnShortNames;
    //DiAnimFileNames   fnFullNames;
  };

void _diAnisLoadNamesArray2(const vector<NDb::Animation> &animations, 
                            DiInt32 nSeqsCount, DiTChar (*cppNamesArray)[diFRAMEID_NAMELENGTH])
{
  DIASSERT(animations.size() == nSeqsCount);
  for (int i = 0; i < animations.size(); i++)
  {
    if (0 == animations[i].name.length())
    {
      //DebugTrace("Animation with index #%i has no name! Name is changed to \"%i\"", i, i);
      sprintf(cppNamesArray[i], "%i", i);
    }
    else
    {
      strcpy(cppNamesArray[i], animations[i].name.begin());
    }
  }

}


void DiAniSLoadFramedAnimationExt2(const vector<NDb::Animation> &animations,
                                  DiAnimNamesArray cppSeqsNamesArray,
                                  DiInt32 *npNumSequencesUserAssumes)
{
  DiInt32           nSeqsCount;
  DiTChar           (*cppNamesArray)[diFRAMEID_NAMELENGTH];



  nSeqsCount = animations.size();
  DIASSERT(nSeqsCount > 0);

  // check size
  if (cppSeqsNamesArray != NULL && npNumSequencesUserAssumes != NULL)
  {
    if (*npNumSequencesUserAssumes < nSeqsCount)
    {
      DIASSERT(*npNumSequencesUserAssumes > 0);
      DIASSERTMSG(FALSE, "File contains more sequences that was assumed. Increase value");
    }
    *npNumSequencesUserAssumes = nSeqsCount;
  }

  // temp array for names
  // - alloc
  cppNamesArray = (DiTChar (*)[diFRAMEID_NAMELENGTH])DiMemAllocateTmp(sizeof(DiTChar) * diFRAMEID_NAMELENGTH * nSeqsCount);
  DIASSERTMSG(cppNamesArray, "anim: no tmp mem");
  // - fill
  _diAnisLoadNamesArray2(animations, nSeqsCount, cppNamesArray);

  // debug - log sequences names
  #ifdef DUMP_SEQUENCES_NAMES
  for (nI = 0; nI < nSeqsCount; nI++)
  {
    DiFormatMessageIssue("*** anim: file '%s', seq %i = %s", cpABFileName, (int)nI, cppNamesArray[nI]);
  }
  #endif

  // copy names to Output parameters
  if (cppSeqsNamesArray != NULL)
  {
    memcpy(cppSeqsNamesArray, cppNamesArray, 
           sizeof(DiTChar) * diFRAMEID_NAMELENGTH * nSeqsCount);
  }

  // clean up
  // - temp names array (we don't use it in this version)
  DiMemFreeTmp(cppNamesArray);
  cppNamesArray = NULL;
}

} // end of anonymous namespace

DiAnimGraph *DiAnimGraph::CreateByData(const vector<NDb::Animation> &animations, 
                                       NScene::IAnimGraphBlender *cppComponent)
{
  // Create "full" creator
  NDb::AnimGraphCreator creatorToFill;
  CreateCreatorWithAllNDBAnims(animations, creatorToFill);

  // Recall
  return CreateByData(&creatorToFill, animations, &cppComponent, 1, NULL, NULL);
}

DiAnimGraph *DiAnimGraph::CreateByData(const NDb::AnimGraphCreator *agCreator, const vector<NDb::Animation> &animations, 
                                  NScene::IAnimGraphBlender *cpComponent, 
                                  const DiTChar *cpName,
                                  DiAnGrLoadCallback *lcCallback)
{
  return DiAnimGraph::CreateByData(agCreator, animations, &cpComponent, 1, cpName, lcCallback);
}

DiAnimGraph *DiAnimGraph::CreateByData(const NDb::AnimGraphCreator *agCreator, const vector<NDb::Animation> &animations, 
                                       NScene::IAnimGraphBlender **cppComponents, DiInt32 nComponents,
                                       const DiTChar *cpName,
                                       DiAnGrLoadCallback *lcCallback)
{
  NI_VERIFY(animations.size() > 0, "Supplied 0 animations for AnimGraph constructor - error!", return NULL;);
  NI_VERIFY(cppComponents != NULL || nComponents <= 0, "No anim components supplied for AnimGraph - creation failed!", return NULL; );
  for (int i=0;i<nComponents;++i)
  {
    NI_VERIFY(cppComponents[i] != NULL, "Anim components can't be NULL - creation failed!", return NULL; );
  }

  // Prepare native information about sequences: fill m_cpParams.anpNamesArr, m_cpParams.npSeqNum
  DiInt32             nI;
  DiTChar             *cpSeqNames;
  DiAnimNamesArray    *anpNamesArr;

  CreateParams m_cpParams;
  m_cpParams.npSeqNum = (DiInt32 *)DiMemAllocateAligned(sizeof(DiInt32) * s_numAnimatedPartsInModel, 16);

  // first: memory for pointers themselves
  cpSeqNames = (DiTChar *)DiMemAllocateAligned((sizeof(DiTChar) * diFRAMEID_NAMELENGTH * ANIM_MAX_SEQS_PER_FILE + sizeof(DiAnimNamesArray))* s_numAnimatedPartsInModel, 16);

  anpNamesArr = (DiAnimNamesArray *)(cpSeqNames);
  DIASSERTPTR(anpNamesArr);
  anpNamesArr[0] = (DiAnimNamesArray)((DiByte *)anpNamesArr + sizeof(DiAnimNamesArray) * s_numAnimatedPartsInModel);
  // set pointers
  for(nI = 1; nI < s_numAnimatedPartsInModel; nI++)
  {
    anpNamesArr[nI] = (DiAnimNamesArray)((DiTChar *)anpNamesArr[nI - 1] + sizeof(DiTChar) * diFRAMEID_NAMELENGTH * ANIM_MAX_SEQS_PER_FILE);
  }

  // read files
  for(nI = 0; nI < s_numAnimatedPartsInModel; nI++)
  {
    m_cpParams.npSeqNum[nI]  = ANIM_MAX_SEQS_PER_FILE;
    DiAniSLoadFramedAnimationExt2(animations, anpNamesArr[nI], &m_cpParams.npSeqNum[nI]);
  }
  m_cpParams.anpNamesArr = anpNamesArr;


  DiAnimGraph *newGraph(NULL);
  newGraph = DiAnimGraph::FillFromCreator(agCreator, animations, m_cpParams.anpNamesArr, m_cpParams.npSeqNum, NULL, cpName, lcCallback);
  DIASSERT(newGraph != NULL);

  DiMemFreeAligned(cpSeqNames);
  DiMemFreeAligned(m_cpParams.npSeqNum);

  // Link to skeleton
  newGraph->SetBlender(cppComponents, nComponents);

  for ( uint i = 0; i < newGraph->GetNumNodes(); i++ )
  {
    DiAnimNode* node = newGraph->GetNodeData(i);
    if ( node->IsSubNode() )
      node->SetDispatcherNodeID( node->CalcDispatcherNodeID() );
  }
  for ( uint i = 0; i < newGraph->GetNumNodes(); i++ )
  {
    class Calcer : public INeiFunctor
    {
      DiUInt32 num;
    public:
      Calcer() : num(0) {}
      virtual void operator()( DiUInt32 )
      {
        num++;
      }
      DiUInt32 GetRes() const { return num; }
    } cl;

    newGraph->ForAllNeighbours( i, &cl );
    DiAnimNode* node = newGraph->GetNodeData(i);
    node->SetNumNeighbours( cl.GetRes() );
  }
  return newGraph;
}

void DiAnimGraph::CreateCreatorWithAllAnims(const vector<string> &animations, NDb::AnimGraphCreator &creatorToFill)
{
  DIASSERT(creatorToFill.macroNodes.size() == 0);

  int numNodes = animations.size();

  creatorToFill.macroNodes.reserve(numNodes);

  NDb::AnGrMacronode node;
  NDb::AnGrFlTransaction timesAndPars;
  NDb::AnGrFlMultiTransaction simpleTrans;
  string invalid("FILL ME!");

  // Fill common sequence data : we will use almost equal parameters for all nodes
  node.sequenceName.assign(invalid);
  node.startPar.value     = 0.0f;
  node.stopPar.value      = 1.0f;
  node.speed.value        = DIANGR_INVALID_FLOAT_VALUE; //Use DIANGR_INVALID_FLOAT_VALUE instead of 1.0f - for auto speed-setup by Maya duration

  // Fill common node data
  node.nodeName.assign(invalid);
  node.nextNode.assign(invalid);
  //node.startPar.value = 0.0f;
  //node.stopPar.value  = 1.0f;

  // Fill common transaction data (times and params)
  timesAndPars.blending   = NDb::ANGRTRANSACTIONUPDATE_POSETOPOSE;
  timesAndPars.kind     = NDb::ANGRTRANSACTIONKIND_UNIFORM;
  timesAndPars.parA.value     = 0.0f;
  timesAndPars.parB.value     = 0.0f;
  timesAndPars.fromMin.value  = 0.0f;
  timesAndPars.fromMax.value  = 1.0f;
  timesAndPars.toParam.value  = 0.0f;
  timesAndPars.duration    = 1.0f/10000.f; // this will cause instant transaction

  // Fill common transaction params (simpleTrans)
  simpleTrans.targetNode.assign(invalid);
  simpleTrans.probability = 0;
  simpleTrans.parameters = timesAndPars;
  
  node.simpleTransactions.reserve(numNodes - 1);
  for (int i = 0; i < numNodes - 1; i++)
  {
    node.simpleTransactions.push_back(simpleTrans);
  }
  
  for (int i = 0; i < numNodes; i++)
  {
    nstl::string curName = animations[i];
    
    if (0 == curName.length())
    {
      //DebugTrace("Animation with index #%i has no name! Node will have name \"%i\"", i, i);
      curName.assign( NStr::IntToStr(i) );
    }
    
    node.nodeName.assign(curName);
    node.nextNode.assign(curName);
    node.sequenceName.assign(curName);

    // link this node to all others
    for (int j = 0, idx = 0; j < numNodes; j++)
    {
      if (i == j)
        continue;
      
      if (0 == animations[j].length())
        node.simpleTransactions[idx].targetNode.assign(NStr::IntToStr(j));
      else
        node.simpleTransactions[idx].targetNode.assign(animations[j]);

      idx++;
    }

    creatorToFill.macroNodes.push_back(node);
  }
}

void DiAnimGraph::CreateCreatorWithAllNDBAnims(const vector<NDb::Animation> &animations, NDb::AnimGraphCreator &creatorToFill)
{
  // convert NDb::Animation to vector<string>
  vector<string> animNames;
  animNames.reserve(animations.size());

  vector<NDb::Animation>::const_iterator it = animations.begin(), end = animations.end();
  for (; it != end; it++)
  {
    animNames.push_back( (*it).name );
  }

  CreateCreatorWithAllAnims(animNames, creatorToFill);
}


// This function creates creator of dummy animation graph: one looped node
void DiAnimGraph::CreateCreatorWithDummyData(NDb::AnimGraphCreator &creatorToFill, const nstl::string &sampleSeqName)
{
  DIASSERT(creatorToFill.macroNodes.size() == 0);
  creatorToFill.macroNodes.reserve(1);
  
  NDb::AnGrMacronode node;

  // Fill sequence data
  node.sequenceName = sampleSeqName;
  node.startPar.value     = 0.0f;
  node.stopPar.value      = 1.0f;
  node.speed.value        = DIANGR_INVALID_FLOAT_VALUE; //1.0f;

  // Node #0
  {
    node.nodeName = "fake_IDLE";
    node.nextNode = "fake_IDLE";
    
    creatorToFill.macroNodes.push_back(node);
  }
}

/**
 * This function creates animation graph by creator
 *
 * @author  EugBel
 */
DiAnimGraph * DiAnimGraph::FillFromCreator( const NDb::AnimGraphCreator *agCreator, 
                                          const vector<NDb::Animation> &animations,
                                          DiAnimNamesArray  *napSeqsTables,
                                          DiInt32 *npNumSequencesInTables,
                                          DiAnGrNodeSrchList *slp,
                                          const DiTChar *cpName,
                                          DiAnGrLoadCallback *lcCallback)
{
  DiBool          bOk;
  DiAnimGraph     *agpAnimGraph(NULL);
  PreReadParams   pParams;
  DiUInt32        nNodesDataSize;
  DiUInt32        nEdgesDataSize;
  DiUInt32        nMultiEdgesDataSize;

  // STEP#0: if (numNodes == 0) - this means that we are in Editor 
  //         and graph has been just created => to prevent crashes and non-stable work we should 
  //         fill it with some dummy-example data.
  const NDb::AnimGraphCreator *curCreator(agCreator);  
  NDb::AnimGraphCreator dummyCreator;
  if (curCreator == NULL || curCreator->macroNodes.size() == 0)
  {
    string seqName = animations[0].name;
    if (0 == seqName.length())
      seqName = NStr::IntToStr(0);
    CreateCreatorWithDummyData(dummyCreator, seqName);
    curCreator = &dummyCreator;
  }

  // STEP#1(PreRead)  We need to count size needed for graph
  bOk = PreReadFile(*curCreator, pParams);
  if (!bOk)
  {
    DIRETURN(NULL);
  }

  // STEP#2 create object of DiAnimGraph
  
  // count size of all nodes data separately
  nNodesDataSize = 0;
  // data of DiAnimNode
  nNodesDataSize += pParams.nNumNodes * 
                    (sizeof(DiAnimNode) + pParams.nNumSequencesPerNode * sizeof(DiAnGrSequence));
  // data of DiAnimMacronode
  nNodesDataSize += pParams.nNumInternalNodes * 
                    (sizeof(DiFloat) + sizeof(DiAnGrSequence) * pParams.nNumSequencesPerNode) + 
                    pParams.nNumMacronodes * sizeof(DiAnimMacronode);

  // count size of edges separately
  nEdgesDataSize = 
                   pParams.nNumFlTransactions * sizeof(DiAnimFlTransaction);

  // count size of multi-edges
  nMultiEdgesDataSize = pParams.nNumGeneralTransactions * sizeof(DiAnimMTransaction) +
                        
                        pParams.nNumMultiFlTransactions * (sizeof(DiAnimFlTransaction) + sizeof (DiAnimFlTransaction *));


  agpAnimGraph = DI_NEW(DiAnimGraph(
                        pParams.nNumNodes + pParams.nNumMacronodes, 
                        pParams.nNumFlTransactions + 
                        pParams.nNumGeneralTransactions,
                        nNodesDataSize, nEdgesDataSize + nMultiEdgesDataSize,
                        bOk, *curCreator, cpName));

  if ( agCreator )
    agpAnimGraph->DBFileName = agCreator->GetDBID().GetFileName();
  else
    agpAnimGraph->DBFileName = "none";

  
  // set number of sequences per node in graph (known from PreRead() )
  agpAnimGraph->nNumSeqsPerNode = pParams.nNumSequencesPerNode;

  // fill graph
  bOk = agpAnimGraph->FillGraph(*curCreator, animations, napSeqsTables, npNumSequencesInTables);


  if (!bOk)
  {
    DIASSERT_ALOOF_CODE(agpAnimGraph->GetDBFileName());
    DiAnimGraph::Destroy(agpAnimGraph);
    DIRETURN(NULL);
  }

  // callback before nodes table exists
  if(slp != NULL)
  {
    agpAnimGraph->FillSearchList(slp);
  }

  // ///eugbel/// make this look better!
  CopyNodesTableToRuntimeTable(agpAnimGraph->nmpaTableOnConstructorOnly, agpAnimGraph, 
                               agpAnimGraph->GetNumNodes());


#ifdef DIANGR_SCREEN_DEBUG_GENERAL
  // save table  
  DebugCopySeqNamesTables(napSeqsTables, agpAnimGraph,
                     npNumSequencesInTables);
#endif

  // use callback if supplied
  if (lcCallback != NULL)
  {
    lcCallback->SetGraph(agpAnimGraph);
    lcCallback->LoadCallbackFunction();
  }

#ifdef GRAPH_NEED_USERDATA
  // Read user data
  bOk = agpAnimGraph->ReadUserDataFromFile(cpCsv);
  // Simple anim graph should not have user data
  // DIASSERTMSG(bOk, "Strange: there is no user data for animation graph");
#endif //GRAPH_NEED_USERDATA

  // free list "Name-ID"
  FreeNodesTable();

  // prepare graph for update
  
  DiUInt32 defaultNode = agpAnimGraph->GetNodeIDByNameSlowQuite( curCreator->defaultNode.c_str() );
  if ( defaultNode == DIANGR_NO_SUCH_ELEMENT )
  {
    //agpAnimGraph->Restart(0);
    agpAnimGraph->SetDefNode(0);
  }
  else
  {
    //agpAnimGraph->Restart( defaultNode );
    agpAnimGraph->SetDefNode(defaultNode);
  }

  DIRETURN(agpAnimGraph);
}


/**
 * This function counts total size that is needed for graph
 *
 * @memo    Count memory size for graph
 * @return  TRUE on success, FALSE otherwise
 * @param   
 * @author  EugBel
 */
DiBool DiAnimGraph::PreReadFile(const NDb::AnimGraphCreator &agCreator, PreReadParams &pParams)
{
  // init variables
  pParams.clear();

  // get number of sequences per node
  pParams.nNumSequencesPerNode = 1;
  DIASSERT(s_numAnimatedPartsInModel == pParams.nNumSequencesPerNode); // AnimGraph was check to work only with 1 component. Support of two and more components should be checked!
  DIASSERT(1 == s_numAnimatedPartsInModel);

  DIASSERT(agCreator.macroNodes.size() > 0); // empty graph? Why?
  for (int nodeID = 0; nodeID < agCreator.macroNodes.size(); nodeID++)
  {
    const NDb::AnGrMacronode &macroNode = agCreator.macroNodes[nodeID];
    AddNodeToTableOnConstructor(macroNode.nodeName.begin());
    
    pParams.nNumNodes++;

    // Process transactions
    for (int floatTrIdx = 0; floatTrIdx < macroNode.simpleTransactions.size(); floatTrIdx++)
    {
      pParams.nNumGeneralTransactions++;
      pParams.nNumMultiFlTransactions++;
    }
  }

  DIRETURN(TRUE);
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
                         DiBool &bResult, const NDb::AnimGraphCreator &agCreator, const DiTChar *cpName) :
                         DiGraph(nNumNodes, nNumEdges, 
                                 nNodesDataSize, nEdgesDataSize, 
                                 bResult, diGT_DIRECTED,
                                 DiGraphRepresentation::diGRT_ARRAY_OF_LISTS)
{
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
  // allocate memory for the path. Use max number of nodes + 1 (due to possible transaction)
  gpPath.npPath         = (DiUInt32 *)DiMemAllocate((nNumNodes + 1)* sizeof(DiUInt32));
    
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
  if (NULL == cpName)
  {
    //DIASSERTMSG(false, "It is much better to specify graph's name - you will find problems faster!");
    
    // User didn't provide any name - so, we will generate some dummy name
    static int s_counter = 0;
    sprintf_s(caName, sizeof(caName), "AG#%i", s_counter++);
  }
  else
  {
    DIASSERT(strlen(cpName) > 0); // if one use debug info - please specify valid names 
    caName[sizeof(caName) - 1] = '\0';
    strncpy(caName, cpName, DiIMin(strlen(cpName), sizeof(caName) - 1));
  }

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

DiBool DiAnimGraph::FillGraph(const NDb::AnimGraphCreator &agCreator,
                               const vector<NDb::Animation> &animations,
                               DiAnimNamesArray  *napSeqsTables,
                               DiInt32 *npNumSequencesInTables)
{
  DiBool         bOk(TRUE);

  // Fill nodes with transactions
  for (int nodeIdx = 0; nodeIdx < agCreator.macroNodes.size(); nodeIdx++)
  {
    DIASSERT(1 == nNumSeqsPerNode); // If not - correct working with sequenceData and sequenceData.size()
    bOk = CreateAndAddNode(agCreator.macroNodes[nodeIdx], napSeqsTables, npNumSequencesInTables );
    DIASSERT(bOk);
  }

  ///eugbel/// Detect editor and fill positions only in editor!
  nodesPos.reserve( agCreator.macroNodes.size() );
  for (int i = 0; i < agCreator.macroNodes.size(); i++)
  {
    nodesPos.push_back( CVec2(agCreator.macroNodes[i].posX, agCreator.macroNodes[i].posY ) );
  }

  DIRETURN(bOk);
} // end of ReadModelFileNames


// This function adds given marker to graph
DiBool DiAnimGraph::CreateAndAddMarker(const NDb::AnGrMarker &marker, EditorGraphParamAddress::OwnerType owner, 
                                       int nodeIdx, int transIdx, int subTransIdx)
{
  DiAnGrMarker newM;
  
  newM.markerName   = marker.name; // name
  newM.owner        = owner; // owner
  newM.nodeIdx      = nodeIdx; // node idx
  newM.transIdx     = transIdx; // trans idx
  newM.subTransIdx  = subTransIdx; // subTransIdx
  newM.virtPar      = marker.virtPar; // virtPar

  // check given data
  DiBool ok(TRUE);
  ok = ok && (newM.markerName.length() > 0);
  ok = ok && (EditorGraphParamAddress::VT_NODE == newM.owner || EditorGraphParamAddress::VT_TRANSACTION == newM.owner);
  if (EditorGraphParamAddress::VT_NODE == newM.owner)
  {
    ok = ok && IsNodeIndexValid(newM.nodeIdx);
  }
  else
  {
    ok = ok && IsTransactionIndexValid(newM.transIdx);
    ok = ok && IsSubTransactionIndexValid(newM.transIdx, newM.subTransIdx);
  }
  ok = ok && (0.0f <= newM.virtPar && newM.virtPar <= 1.0f);

  mMarkers.push_back(newM);

  return ok;
}

/**
 * This function reads  node and saves it to graph
 *
 * @memo    Read  node
 * @return  TRUE on success, FALSE otherwise
 * @author  EugBel
 */
DiBool DiAnimGraph::CreateAndAddNode( const NDb::AnGrMacronode &node, 
                                      DiAnimNamesArray  *napSeqsTables,
                                      DiInt32 *npNumSequencesInTables )
{
  DiAnimNode        *anpNode;
  DiBool            bOk(TRUE);
  DiInt32           nSize, nI;
  DiUInt32          nGivenID;
  DiUInt32          nCurNodeID;
  DiAnGrSequence    *spSeq;

  // save node name
  nCurNodeID = GetNodeIDByNameOnConstructor(node.nodeName.begin());

  // we can count size of memory needed
  nSize = sizeof(DiAnGrSequence) * nNumSeqsPerNode + sizeof(DiAnimNode);

  anpNode = (DiAnimNode *)DiMemAllocateTmpAligned(sizeof(DiByte) * nSize, 16);
  if (NULL == anpNode)
    DIRETURN(FALSE);
  // setup pointers
  anpNode->spSequences = (DiAnGrSequence *)(anpNode + 1);
 
  anpNode->rSurfSpeed = CVec2(node.surfSpeedX, node.surfSpeedY);
  anpNode->nDefNext = GetNodeIDByNameOnConstructor(node.nextNode.begin());

  // check loop
  if (anpNode->nDefNext == nCurNodeID)
    anpNode->bIsLooped = TRUE;
  else
    anpNode->bIsLooped = FALSE;

  // read sequences
  for (nI = 0; nI < nNumSeqsPerNode; nI++)
  {
    // convert sequence name to index
    spSeq = &(anpNode->spSequences[nI]);
    spSeq->nID = GetSeqIdxByName(napSeqsTables[nI], npNumSequencesInTables[nI], node.sequenceName.begin()); 
    DIASSERT(spSeq->nID != DIANGR_NO_SUCH_ELEMENT);
    spSeq->rStartPar = node.startPar.value;
    spSeq->rStopPar  = node.stopPar.value;    
    spSeq->rSpeed    = node.speed.value;
    
    // init other values
    spSeq->rCurPar = spSeq->rStartPar;

    DIASSERT(spSeq->rStartPar >= 0.0f && spSeq->rStopPar <= 1.0f);
    DIASSERT(spSeq->rStopPar >= spSeq->rStartPar);
    
    bool noError = node.speed.value != 0.0f;
    for(int i=0; i<node.speed.coeffs.size(); ++i)
    {
      if(node.speed.coeffs[i].value != 0.0f)
      {
        noError = true;
        break;
      }
    }

    //if ( node.speed.value == 0 && node.speed.coeff == 0 )
    //{
    //  error;
    //}
    //NI_DATA_ASSERT( node.speed.value != 0.f, NStr::StrFmt( "Node %s in file %s has zero speed!", node.nodeName.c_str(), filename.c_str() )
    NI_DATA_ASSERT( noError, NStr::StrFmt( "Node %s in file %s has zero speed!", node.nodeName.c_str(), DBFileName.c_str() ));
  }

  // init params with default values
  anpNode->bIsThisMacronode = FALSE;
  anpNode->rStartPar        = DIANGR_DEFAULT_NODE_START_PAR;
  anpNode->rStopPar         = DIANGR_DEFAULT_NODE_STOP_PAR;
  anpNode->rCurPar          = anpNode->rStartPar;
  anpNode->gpGraph          = this;
  anpNode->sepClbStorage    = NULL;
  //anpNode->pUserData        = new KicksData;

  // set flag "switcher": process only simple (!) transactions
  anpNode->bIsSwitcher      = false;
  float totalProbSum        = 0.0f;
  for (int i = 0; i < node.simpleTransactions.size(); i++)
  {
    totalProbSum += node.simpleTransactions[i].probability;
  }

  anpNode->bIsSwitcher = (totalProbSum > 0.0f);
  anpNode->SetSubNode( node.nodeType == NDb::ANGRNODETYPE_SUBNODE );

  // add node to graph
  bOk = AddNode(anpNode, nSize, nGivenID);
  DIASSERT(nGivenID >= 0 && nGivenID < GetNumNodes() && nGivenID == nCurNodeID);
  DiMemFreeTmpAligned(anpNode);

  // read and save all node markers
  for (int markerIdx = 0; markerIdx < node.markers.size(); markerIdx++)
  {
    bOk = CreateAndAddMarker(node.markers[markerIdx], EditorGraphParamAddress::VT_NODE, nGivenID, -1, -1);
    DIASSERT(bOk);
  }

  // read and save all transactions
  int probabilitiesSum(0);
  float probabilitiesCoeff(1.0f);
  if (totalProbSum > 0.0f)
    probabilitiesCoeff = 100.0f / totalProbSum;
  
  // remaining probability
  float remProb(0.f);
  for (int i = 0; i < node.simpleTransactions.size(); i++)
  {
    float curProb = node.simpleTransactions[i].probability * probabilitiesCoeff + remProb;
    int normalizedProbability = floor(curProb);
    remProb = curProb - normalizedProbability;

    if (i == node.simpleTransactions.size() - 1 && totalProbSum > 0.f)
    {
      int correctedProbability = 100 - probabilitiesSum; // to ensure that sum will be 100
      NI_ASSERT(abs(correctedProbability - normalizedProbability) < 2, "Probabilities sum logic failed");
      normalizedProbability = correctedProbability; 
    }

    probabilitiesSum += normalizedProbability;

    NI_ASSERT(normalizedProbability > 0 || fabs(totalProbSum) < 1e-5, NStr::StrFmt( "Probability of %i transaction in node %s is equal to zero: this transaction will never go.", 
              i, node.nodeName.begin()) );
    CreateAndAddGeneralTransaction(node.simpleTransactions[i], nGivenID, normalizedProbability);
  }
  DIASSERT(100 == probabilitiesSum || 0 == probabilitiesSum);

  DIRETURN(bOk);
} // end of ReadNode

/**
 * This function reads macro node and saves it to graph
 *
 * @memo    Read macro node
 * @return  TRUE on success, FALSE otherwise
 * @author  EugBel
 */
DiBool DiAnimGraph::CreateAndAddMacronode(const NDb::AnGrMacronode &macronode, 
                                         DiAnimNamesArray  *napSeqsTables,
                                         DiInt32 *npNumSequencesInTables)
{
  DiAnimMacronode   *amnpNode;
  DiBool            bOk;
  DiInt32           nI, nSize, nJ;
  DiUInt32          nGivenID;
  DiInt32           nNumInternalNodes;
  DiUInt32          nCurNodeID;
  DiAnGrSequence    *spSeq;
  DiFloat           *raWeightSum;

  // save node name
  nCurNodeID = GetNodeIDByNameOnConstructor(macronode.nodeName.begin());

  // read Macronode params
  nNumInternalNodes = 1;
  DIASSERT(nNumInternalNodes > 0);

  // now we can count size of memory needed
  nSize = nNumInternalNodes * 
          sizeof(DiAnGrSequence) * nNumSeqsPerNode + 
          sizeof(DiAnimMacronode);

  amnpNode = (DiAnimMacronode *)DiMemAllocateTmpAligned(sizeof (DiByte) * nSize, 16);
  if (NULL == amnpNode)
    DIRETURN(FALSE);
  
  // setup pointers
  amnpNode->spSequences = (DiAnGrSequence *)(amnpNode + 1);

  // copy parameter
  amnpNode->nNumInternalNodes = nNumInternalNodes;

  amnpNode->rSurfSpeed  = CVec2(macronode.surfSpeedX, macronode.surfSpeedY);

  amnpNode->nDefNext = GetNodeIDByNameOnConstructor(macronode.nextNode.begin());
  if (amnpNode->nDefNext == nCurNodeID)
    amnpNode->bIsLooped = TRUE;
  else
    amnpNode->bIsLooped = FALSE;

  // read sequences of all internal nodes
  raWeightSum = (DiFloat *)DiMemAllocateTmp(sizeof(DiFloat) * nNumSeqsPerNode);
  for (nI = 0; nI < nNumSeqsPerNode; nI++)
  {
    raWeightSum[nI] = 0.0f;
  }
  for (nJ = 0; nJ < amnpNode->nNumInternalNodes; nJ++)
  {
    // read sequence of current internal node
    for (nI = 0; nI < nNumSeqsPerNode; nI++)
    {
      // convert sequence name to index
      spSeq = &(amnpNode->spSequences[nNumSeqsPerNode * nJ + nI]);
      spSeq->nID = GetSeqIdxByName(napSeqsTables[nI],npNumSequencesInTables[nI], macronode.sequenceName.begin()); 
      
      spSeq->rStartPar = macronode.startPar.value;
      spSeq->rStopPar  = macronode.stopPar.value;
      spSeq->rSpeed    = macronode.speed.value;
      spSeq->rWeight   = 1.0f;
      
      raWeightSum[nI] += spSeq->rWeight; // check (sum of weights == 1.0f)
      DIASSERT(0.0f <= spSeq->rWeight && spSeq->rWeight <= 1.0f);

      // init other values
      spSeq->rCurPar = spSeq->rStartPar;

      DIASSERT(spSeq->rStartPar >= 0.0f && spSeq->rStopPar <= 1.0f);
      DIASSERT(spSeq->rStopPar > spSeq->rStartPar);
    }
  }// end of cycle by internal nodes
  
  #ifdef DIDEBUG
    // check weights
    for (nI = 0; nI < nNumSeqsPerNode; nI++)
    {
      DIASSERT(0.999f <= raWeightSum[nI] && raWeightSum[nI] <= 1.001f);
    }
  #endif

  DiMemFreeTmp(raWeightSum);
  
  // init params with default values
  amnpNode->bIsThisMacronode  = TRUE;
  amnpNode->rStartPar         = DIANGR_DEFAULT_NODE_START_PAR;
  amnpNode->rStopPar          = DIANGR_DEFAULT_NODE_STOP_PAR;
  amnpNode->rCurPar           = amnpNode->rStartPar;
  amnpNode->gpGraph           = this;
  amnpNode->sepClbStorage     = NULL;

  // set flag "switcher": process only simple (!) transactions
  amnpNode->bIsSwitcher      = false;
  float totalProbSum        = 0.0f;
  for (int i = 0; i < macronode.simpleTransactions.size(); i++)
  {
    totalProbSum += macronode.simpleTransactions[i].probability;
  }

  amnpNode->bIsSwitcher = (totalProbSum > 0.0f);
  amnpNode->SetSubNode( macronode.nodeType == NDb::ANGRNODETYPE_SUBNODE );

  // add Macronode to graph
  bOk = AddNode(amnpNode, nSize, nGivenID);
  DIASSERT(nGivenID >= 0 && nGivenID < GetNumNodes() && nGivenID == nCurNodeID);
  DiMemFreeTmpAligned(amnpNode);

  // read and save all macronode markers
  for (int markerIdx = 0; markerIdx < macronode.markers.size(); markerIdx++)
  {
    bOk = CreateAndAddMarker(macronode.markers[markerIdx], EditorGraphParamAddress::VT_NODE, nGivenID, -1, -1);
    DIASSERT(bOk);
  }


  // read and save all transactions
  int probabilitiesSum(0);
  float probabilitiesCoeff(1.0f);
  if (totalProbSum > 0.0f)
    probabilitiesCoeff = 100.0f / totalProbSum;

  for (int i = 0; i < macronode.simpleTransactions.size(); i++)
  {
    int normalizedProbability = floor(macronode.simpleTransactions[i].probability * probabilitiesCoeff + 0.5f);
    probabilitiesSum += normalizedProbability;
    CreateAndAddGeneralTransaction(macronode.simpleTransactions[i], nGivenID, normalizedProbability);
  }
  DIASSERT(100 == probabilitiesSum || 0 == probabilitiesSum);

  DIRETURN(bOk);
} // end of ReadMacronode

/**
 * This function reads and saves transaction that could consist of several transactions
 *
 * @memo    Read and save multi transaction
 * @return  TRUE on success, FALSE otherwise
 * @param   nNodeFromID   outgoing node
 * @param   geElem        type of current element
 * @author  EugBel
 */
DiBool DiAnimGraph::CreateAndAddGeneralTransaction(const NDb::AnGrFlMultiTransaction multiUniTrans,
                                                  DiUInt32 nNodeFromID, int normalizedProbability)
{
  DiAnimMTransaction *mtpMTrans;
  DiAnimFlTransaction  *atpTransDataStart;
  DiUInt32           nNodeToID, nGivenID, nSize;
  DiInt32            nNumTrans;
  DiUInt32           nSubTransSize;
  DiBool             bOk;
  DiUInt16           nWeight;
  DiFloat            rPriority;

  nGivenID = 0; 

  nSubTransSize = sizeof(DiAnimFlTransaction);

  // read number of internal transactions (== number of start intervals)
  nNumTrans = 1;
  DIASSERT(nNumTrans >= 1);

  // allocate tmp memory for MultiTrans (don't forget about diffs btw Tr & FlTr)
  // and sub-transes in ONE block
  DIASSERT(nSubTransSize > 0);
  nSize = sizeof(DiAnimMTransaction) + 
          nNumTrans * (sizeof(DiAnimFlTransaction *) + nSubTransSize);
  mtpMTrans = (DiAnimMTransaction *)DiMemAllocateTmpAligned(nSize, 16);
  DIASSERTPTR(mtpMTrans);

  // save number
  mtpMTrans->nNumIntervals = nNumTrans;
  // init pointer
  mtpMTrans->sepClbStorage = NULL;
                                                                
  // setup pointers
  mtpMTrans->atppTransactions = (DiAnimFlTransaction **)(mtpMTrans + 1);
  atpTransDataStart = (DiAnimFlTransaction *)((DiByte *)mtpMTrans + sizeof(DiAnimMTransaction) + 
                       mtpMTrans->nNumIntervals * sizeof(DiAnimFlTransaction *));

  atpTransDataStart->SetPrevPar( 0.0f );
  
  // read common parameter: NodeTo
  nNodeToID = GetNodeIDByNameOnConstructor(multiUniTrans.targetNode.begin());
  DIASSERT(nNodeToID != nNodeFromID && nNodeToID < 1000 && nNodeFromID < 1000);

  // read priority and convert it to edge weight
  rPriority = 10.0f;
  DIASSERT(DIANGR_PRIORITY_MIN <= rPriority && rPriority <= DIANGR_PRIORITY_MAX);
  nWeight = DiAnimFlTransaction::ConvertPriorToWeight(rPriority);

  // read probability
  mtpMTrans->nProbability = normalizedProbability;
  DIASSERT(0 <= mtpMTrans->nProbability && mtpMTrans->nProbability <= 100);

  // fill sub-transactions in cycle
  // get the pointer
  mtpMTrans->atppTransactions[0] = atpTransDataStart;
      
  bOk = mtpMTrans->atppTransactions[0]->FillMainParamsFromFile(multiUniTrans.parameters, &nWeight, GetDBFileName());
  DIASSERT(bOk);

  // check that transactions don't overlap
  DIASSERT(mtpMTrans->IsCorrect());
  
  // add edge to graph
  bOk = AddEdge(nNodeFromID, nNodeToID, nWeight, mtpMTrans, nSize, nGivenID);  
  DIASSERT(bOk);

  // read and save all edge markers
  for (int markerIdx = 0; markerIdx < multiUniTrans.parameters.markers.size(); markerIdx++)
  {
    bOk = CreateAndAddMarker(multiUniTrans.parameters.markers[markerIdx], EditorGraphParamAddress::VT_TRANSACTION, -1, nGivenID, 0);
    DIASSERT(bOk);
  }

  // free MultiTrans memory
  DiMemFreeTmpAligned(mtpMTrans);

  DIRETURN(TRUE);  
}

/*
 * This function reads and fills basic transaction parameters
 *
 * @memo    Read and fill basic parameters
 * @return  TRUE on success, FALSE otherwise
 * @param   atpTransaction
 * @author  EugBel
 */
DiBool DiAnimFlTransaction::FillMainParamsFromFile(const NDb::AnGrFlTransaction &uniTrans,
                                                  DiUInt16 *npWeight, const nstl::string& dbfilename)
{
  DiUInt32 nUpdateFlags(0);

  this->rSpeed        = 1.0f/uniTrans.duration;
  this->rFromParamMin = uniTrans.fromMin.value;
  this->rFromParamMax = uniTrans.fromMax.value;

  switch(uniTrans.kind)
  {
    case NDb::ANGRTRANSACTIONKIND_UNIFORM :       kKind = DIAN_TRKIND_UNIFORM;       break;
    case NDb::ANGRTRANSACTIONKIND_PARABOLIC3 :    kKind = DIAN_TRKIND_3PARABOLIC;    rParA = uniTrans.parA.value; break;
    case NDb::ANGRTRANSACTIONKIND_RECPARABOLIC3 : kKind = DIAN_TRKIND_3RECPARABOLIC; rParA = uniTrans.parA.value; break;
    case NDb::ANGRTRANSACTIONKIND_SINE :          kKind = DIAN_TRKIND_SINE;          rParA = uniTrans.parA.value; break;
    case NDb::ANGRTRANSACTIONKIND_RECSINE :       kKind = DIAN_TRKIND_RECSINE;       rParA = uniTrans.parA.value; break;
    case NDb::ANGRTRANSACTIONKIND_SPLINE :        kKind = DIAN_TRKIND_SPLINE;        rParA = uniTrans.parA.value; rParB = uniTrans.parB.value; break;
    case NDb::ANGRTRANSACTIONKIND_RECSPLINE :     kKind = DIAN_TRKIND_RECSPLINE;     rParA = uniTrans.parA.value; rParB = uniTrans.parB.value; break;
    default: DIASSERT_ALOOF_CODE(dbfilename);
  }
  
  if (kKind == DIAN_TRKIND_SPLINE || kKind == DIAN_TRKIND_RECSPLINE)
  {
    DIASSERT(0.0f < rParA && rParA < 1.0f);
    DIASSERT(0.0f < rParB && rParB < 1.0f);
  }

  // convert params
  ConvertExtParsToIntPars(kKind, rParA, rParB, rParA, rParB);


  // here we need error handling: because of DIANGR_SYNCH_NODES_IN_FLTRANSACTION
//   if (uniTrans.update == NDb::ANGRTRANSACTIONUPDATE_FIRSTNODEONLY ||
//       uniTrans.update == NDb::ANGRTRANSACTIONUPDATE_SECONDNODEONLY   ||
//       uniTrans.update == NDb::ANGRTRANSACTIONUPDATE_BOTHNODES   )
//     this->rToParam = DIANGR_SYNCH_NODES_IN_FLTRANS_F;
//   else
    this->rToParam = uniTrans.toParam.value;

  switch(uniTrans.blending)
  {
    case NDb::ANGRTRANSACTIONUPDATE_POSETOPOSE: nUpdateFlags = DIANGR_FLKIND_NONE;    break;
    case NDb::ANGRTRANSACTIONUPDATE_ANIMTOPOSE: nUpdateFlags = DIANGR_FLKIND_FIRST;   break;
    case NDb::ANGRTRANSACTIONUPDATE_POSETOANIM:   nUpdateFlags = DIANGR_FLKIND_SECOND;  break;
    case NDb::ANGRTRANSACTIONUPDATE_ANIMTOANIM: nUpdateFlags = DIANGR_FLKIND_BOTH;    break;
    default: DIASSERT_ALOOF_CODE(dbfilename);
  }

  ((DiAnimFlTransaction *)this)->SetUpdateFlags(nUpdateFlags); 


  // check params
  //DIASSERT(this->rSpeed > 0.0f);
  DIASSERT(0.0f <= this->rFromParamMin && this->rFromParamMin <= 1.0f);
  DIASSERT(0.0f <= this->rFromParamMax && this->rFromParamMax <= 1.0f);
  DIASSERT(0.0f <= this->rToParam && this->rToParam <= 1.0f/* || 
           this->rToParam == DIANGR_SYNCH_NODES_IN_FLTRANS_F*/  ); 
  
  DIRETURN(TRUE);
}

/**
* @memo    Fill search list if supplied
* @return  None
* @param   agp
* @param   vp
* @author  Earnol
* @see     Nothing
*/
DiVoid DiAnimGraph::FillSearchList(DiAnGrNodeSrchList *slp)
{
  DiAnGrNodeSrchEntry      *sepEntries;
  DiInt32                  nI;

  DIFUNCTION("DiAnimGraph::FillSearchList");

  //
  DIASSERTPTR(slp);
  //access
  sepEntries = slp->seEntries;
  DIASSERTPTR(sepEntries);

  for(nI = 0; nI < slp->nNumEntries; nI++)
  {
    DIASSERTPTR((sepEntries + nI)->cpNodeName);
    (sepEntries + nI)->nNodeID = this->GetNodeIDByNameOnConstructor((sepEntries + nI)->cpNodeName);
    (sepEntries + nI)->geType  = DIANGR_NODE;
  }
  DIRETURNVOID();
} // end of DiAnimGraph::FillSearchList;


#pragma warning (default : 4996)

///eugbelNSCENE///} // end of namespace NScene
