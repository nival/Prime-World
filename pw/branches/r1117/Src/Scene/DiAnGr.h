/*
 * @file    DiAnGr.h
 * @memo    AnimationGraph support
 * @author  EugBel
 * @date    06.09.2003
 * @prefix  DiAn, DiAnGr
 * @library skeleton.lib
 */

#ifndef _DIANGR_H_
#define _DIANGR_H_

// *******************************************************************
// includes
#include "IAnimGraphBlender.h"

#include "DiAnGrUtils.h"
#include "DiAnGrAPI.h"
#include "DiAnGrMarker.h"
#include "DiAnGrSStorage.h"

#include "../Render/dbRenderResources.h"


#include "DiGraph.h"
#include "DiAnSol.h"

#include "../System/Ring.h"

#define BADNODENAME "badNodeName"
#define SUMMONNODE "summon"
#define REVIVENODE "revive"
#define IDLENODE "idle"
#define DEADNODE "dead"
#define UNSUMMONEDNODE "unsummoned"

#ifndef _SHIPPING
// uncomment this to see graph debug info. See DiAnGrDb.cpp for usage details.
// This define enables general debug-functionality. Until command Ctrl+Q is specified (or function DiAnimGraph::EnableLog() called) there will be no speed-down
// The only disavantage: there are a lot of strings
#define DIANGR_SCREEN_DEBUG_GENERAL

// uncomment this to see graph debug info. See DiAnGrDb.cpp for usage details.
// This define changes some functions (like RegisterCallback to same function but with callback's names)
// Common use: hard-debugging of AG. Not recommended for common users.
//#define DIANGR_SCREEN_DEBUG_ADVANCED

// uncomment this to have some functionality to test markers
//#define DIANGR_TEST_MARKERS

// uncomment this to enable user data (this was made by Matt not by EugBel! THINK TWICE BEFORE UNCOMMENTING!)
//#define GRAPH_NEED_USERDATA

#endif //_SHIPPING

///eugbelNSCENE///namespace NScene {



// Forward declarations
class DiAnimGraph;
class DiAnimNode;
class DiAnimMacronode;

class DiAnimFlTransaction;

namespace NScene
{
  static void _printDebugStatus(DiAnimGraph *animGraph, float dt);
  class AnimGraphBlender;
  class AnimGraphController;
}

// Include internal structures like DiAnimNode, DiAnimFlTransaction, etc. 
#define __DIANGR_INTERNAL_INCLUDE__
#include "DiAnGr.inl"
#undef __DIANGR_INTERNAL_INCLUDE__


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

struct SpeedUserData : public BaseObjectST
{
public:
  NI_DECLARE_REFCOUNT_CLASS_1( SpeedUserData, BaseObjectST );

public:
  DiAnimGraph *animGraph;
  DiFloat     prevGraphSpeed;

  DiAnimGraphElems elemType;
  DiUInt32         elemID;
  
  SpeedUserData(DiAnimGraphElems _elemType, DiUInt32 _elemID, 
                DiAnimGraph *_animGraph, DiFloat _prevSpeed) 
  : elemType(_elemType), elemID(_elemID)
  , animGraph(_animGraph), prevGraphSpeed(_prevSpeed) 
  { }

  seDECLARE_STRONG_RING( SpeedUserData, ringPart, Ring );
};


// This class is a basic structure that controls animation of the person
// One person - one animation graph
class DiAnimGraph : public DiGraph
{
  // Forward declarations 
  struct PreReadParams;
  struct PathSetupInfo;
  struct PathToMarker;

  nstl::string DBFileName;
  bool freezed;

public:
  //////////////////////////////////////////////////////////////////////////
  // PUBLIC             Main functionality
  //////////////////////////////////////////////////////////////////////////

  // Main function for AnimGraph creation (Static!)
  static  DiAnimGraph *CreateByData(const NDb::AnimGraphCreator *agCreator, const vector<NDb::Animation> &animations, 
                                    NScene::IAnimGraphBlender **cppComponents, 
                                    DiInt32 nComponents, const DiTChar *cpName = NULL,
                                    DiAnGrLoadCallback *lcCallback = NULL);
  // Copy of the function above but with only one component required
  static  DiAnimGraph *CreateByData(const NDb::AnimGraphCreator *agCreator, const vector<NDb::Animation> &animations, 
                                    NScene::IAnimGraphBlender *cpComponent, 
                                    const DiTChar *cpName = NULL,
                                    DiAnGrLoadCallback *lcCallback = NULL);
  // Main function for AnimGraph creation (Static!) This function creates "full" graph: with all nodes linked to each other and with all default parameters
  static  DiAnimGraph *CreateByData(const vector<NDb::Animation> &animations, NScene::IAnimGraphBlender *cppComponent);

  // Function for graph destroying (Static!)
  static  DiVoid      Destroy(DiAnimGraph *gGraph);

  // Restart graph (for example after "death" and at game start)
  DiBool      Restart( DiUInt32 nStartNodeID, bool needCallbacks );
  // Update graph
  DiBool      Update(DiFloat rUpdateDt);
  // Set target node (node to reach)
  DiBool      SetTargetNode(DiUInt32 nNode);
  DiBool      IsPathSpecified() { return bPathSpecified; }


  DiVoid Freeze();
  DiVoid UnFreeze();

  // Register callback on almost any moment: node/transaction/update_start/update_end/...
  // nCallFlags could be: DIANGR_CF_UPDATE_BEGIN,  DIANGR_CF_UPDATE_END,
  //                      DIANGR_CF_ELEMENT_ENTER, DIANGR_CF_ELEMENT_LEAVE
  //                      DIANGR_CF_EXACT_PARAM
  //                      DIANGR_CF_UPDATE_ALWAYS (== all flags together)
  DiAnGrClbStorageElem *RegisterCallback(DiAnimGraphElems geElem, DiUInt32 nID,
                                       DiAnGrCallback fpCallback, 
                                       DiUInt32 nCallFlags, 
                                       DiVoid *vpUserData,// = NULL,
                                       DiFloat rExactParam = DIANGR_INVALID_FLOAT_VALUE,
                                       DiFloat probability = 100.f);

  // Register callback on marker
  DiAnGrClbStorageElem *RegisterCallback(const DiAnGrMarker &marker, DiAnGrCallback fpCallback, 
                          DiVoid *vpUserData, DiFloat probability = 100.f);
  // Register callback for all same markers
  DiBool RegisterCallbackForAllSameMarkers(const string &markerName, DiAnGrCallback fpCallback, 
                                           DiVoid *vpUserData, DiFloat probability = 100.f);

  
  #ifdef DIANGR_SCREEN_DEBUG_ADVANCED
  // Register callback with some name - to see this name while debugging
  DiAnGrClbStorageElem *RegisterCallbackWithName( DiTChar *cpName, DiAnimGraphElems geElem, DiUInt32 nID,
                                                DiAnGrCallback fpCallback, 
                                                DiUInt32 nCallFlags, 
                                                DiVoid *vpUserData,
                                                DiFloat rExactParam = DIANGR_INVALID_FLOAT_VALUE,
                                                DiFloat probability = 100.f);
  #endif //DIANGR_SCREEN_DEBUG_ADVANCED

  void   ForceLeaveNodeCallbacks(int nodeIdx);

         void AGTrace( const char *pszFormat, ... );
  static void EnableLog(bool enableLogging, DiAnimGraph *agToWatch, bool enableLogToOutput = false);
  static void EnablePathLogging(bool enableLogging);
  static DiAnimGraph *GetGraphToLog();
  static bool         IsLog2ScreenEnabled();
  static bool         IsLog2OutputEnabled();
  // Unregister callback to prevent it's future calling. Use userDataIfYouKnowIt if you register SAME function for SAME element but with different userdata (in other cases pass NULL as userDataIfYouKnowIt and feel good)
  DiBool              UnregisterCallback(DiAnimGraphElems geElem, DiUInt32 nID, DiAnGrCallback fpCallback, DiVoid *userDataIfYouKnowIt = NULL);
  DiBool              UnregisterCallback(DiAnimGraphElems geElem, DiUInt32 nID, DiAnGrClbStorageElem *pElemToDel);
  DiBool              UnregisterCallbackForAllSameMarkers(const string &markerName, DiAnGrCallback fpCallback, DiVoid *userDataIfYouKnowIt = NULL);



  //////////////////////////////////////////////////////////////////////////
  // PUBLIC             Additional functionality: Get()-methods
  //////////////////////////////////////////////////////////////////////////

  DiAnGrMarker        *FindMarkerByName(const string &markerName, int *idxToStartSearch = NULL, int *foundMarkerIdx = NULL);
  DiAnGrMarker        *FindMarkerByNameInCurNode(const string &markerName);
  DiAnGrMarker        *FindMarkerByNameInNextNodeAfterTrans(const string &markerName);
  DiAnGrMarker        *FindMarkerByNameInNode(const string &markerName, int nodeIdx);
  DiAnGrMarker        *GetRandomNodeMarker( DiAnGrMarker* marker );
  DiInt32             GetNumParts() const;
  DiInt32             GetNumMarkers() const;
  DiUInt32            GetCurNode() const;
  DiUInt32            GetCurNodeUnsafe() const;
  DiUInt32            GetNearestNode() const;
  DiUInt32            GetPrevNode() const;
  DiUInt32            GetNextNode() const;
  DiUInt32            GetDefNode() const;
  DiVoid              SetDefNode( DiUInt32 node );
  DiVec2              GetNodeSurfSpeed(int nodeIdx) const;
  DiUInt32            GetMTransactionID(DiUInt32 nNodeFrom, DiUInt32 nNodeTo);
  DiFloat             GetGraphSpeedCoeff() const;
  DiFloat             GetGraphSpeedUpCoeff() const;
  const SVector&      GetNodePosInEditor(int nodeIdx) const;
  const DiAnimNode    *GetNodeData(DiUInt32 nNodeID) const;
  bool                ReplaceSeqInNode(int nodeSrc, int seqIdxSrc, int nodeDst, int seqIdxDst);

  //////////////////////////////////////////////////////////////////////////
  // PUBLIC             Additional functionality: Set()-methods
  //////////////////////////////////////////////////////////////////////////
  
  void                ClearMarkers();
  // This function sets new markers (they will overwrite existent markers, if any). To add markers - use AddMarkers()
  void                SetMarkers(const vector<DiAnGrEditorMarker> &editorMarkers);
  // This function adds markers to AnimGraph. New markers will be added (existent markers will NOT be deleted)
  void                AddMarkers(const vector<DiAnGrEditorMarker> &editorMarkers);
  
  // Markers & events support. Return bool if marker is reachable, false - otherwise
  bool                ReachMarkerByTime(const string &markerName, int time, bool preferShortestPath = true, bool preferDefaultNextNode = false);
  void                SetGraphSpeedCoeff(DiFloat newSpeed);
  void                SetNodePosInEditor( int nodeIdx, SVector newPos );
  DiBool              SetNodeSpeed( DiUInt32 nodeId, DiFloat speedCoeff );


  //////////////////////////////////////////////////////////////////////////
  // PUBLIC             Special functionality - for tools/editor/utilities
  //////////////////////////////////////////////////////////////////////////
  static DiFloat      WrapIn( DiFloat rValue, DiFloat rMin, DiFloat rMax,
                              DiUInt32 *npNumWrapsHappened = NULL);

  bool                FillSimpleStorage(DiAnGrSimpleStorage &storageToFill, 
                                        const NScene::AnimationVector &_animations,
                                        DiAnGrExtPars &extPars);

  DiFloat             GetNodeDuration(DiUInt32 nNode) const;
  DiInt32             GetNumRegisteredCallbacks();
  DiBool              IsNodeIndexValid(int nodeIdx) const;
  DiBool              IsTransactionIndexValid(int transIdx) const;
  DiBool              IsSubTransactionIndexValid(int transIdx, int subTransIdx) const;
  DiBool              IsGraphValid() const; // special function to check integrity of the graph
  DiBool              IsInTransactionOrFLTransaction() const;
  DiBool              IsInNodeOrMacronode() const;



  NScene::IAnimGraphBlender **GetComponents(DiVoid);
  NScene::IAnimGraphBlender *GetComponent(DiInt32 nPartIdx);

  DiVoid              StoreDefaultValues(); 

  //////////////////////////////////////////////////////////////////////////
  // PUBLIC            Special functionality for the editor (for the special "second" animation graph for previewing animations)
  //                   "EO" means "EditorOnly"
  //////////////////////////////////////////////////////////////////////////

  bool EOPlayAnimation( int idx );
  bool EOPlayAnimation( string name );
  void EOSetGlobalAnimGraphSpeed( float globalSpeed, float *prevGlobalSpeed = NULL);
  bool EOPauseCurrentNode( InOut &dataToSave );
  bool EOGotoInCurrentNode( float virtualParameter );
  bool EOResumeCurrentNode( const InOut &savedData );
  bool EOSetAnimationRangeInCurrentNode( float virtParStart, float virtParStop );

  const nstl::string& GetDBFileName() const
  {
    return DBFileName;
  }


private:
  //////////////////////////////////////////////////////////////////////////
  // PRIVATE            Common functionality (INTERNAL!)
  //////////////////////////////////////////////////////////////////////////

  // constructor (used in editor)
  DiAnimGraph(DiUInt32 nNumNodes,      DiUInt32 nNumEdges, 
              DiUInt32 nNodesDataSize, DiUInt32 nEdgesDataSize, 
              DiBool &bResult, const DiTChar *cpName);

  // constructor (used in runtime)
  DiAnimGraph(DiUInt32 nNumNodes,      DiUInt32 nNumEdges, 
              DiUInt32 nNodesDataSize, DiUInt32 nEdgesDataSize, 
              DiBool &bResult,         const NDb::AnimGraphCreator &agCreator, const DiTChar *cpName);
  // destructor
  ~DiAnimGraph();

  
  
  //////////////////////////////////////////////////////////////////////////
  // PRIVATE             Additional functionality
  //////////////////////////////////////////////////////////////////////////


  bool                IsNodeMarkerNear(const DiAnGrMarker &marker);
  bool                IsNodeMarkerNearSwitcher(int nodeSwitcherIdx, int markerNode);
  bool                IsTransactionMarkerNear(const DiAnGrMarker &marker);
  int                 CalculateTimeFromNodeToNodeInMS(int nodeFrom, float nodeFromPar, int nodeTo, float nodeToPar, bool isInNode, vector<PathChange> &changesInPath, PathSetupInfo &pathInfo);
  void                CalculateTimeToNodeMarker(const DiAnGrMarker &marker, vector<PathToMarker> &pathsToMarker);
  int                 CalculateTimeToTransactionMarker(const DiAnGrMarker &marker);
  #ifdef DIANGR_TEST_MARKERS
    public:
  #endif
  // Markers & events support. Return bool if marker is reachable, false - otherwise
  bool                GetTimeTillNearestMarkerInMS(string markerName, int &time, DiAnGrMarker &markerToFill, bool preferShortestPath, int requestedTime, bool preferDefaultNextNode);
  #ifdef DIANGR_TEST_MARKERS
    private:
  #endif
  // Special callback for markers
  DiInt32 ResetGraphSpeedCallback(DiAnGrCallbackParams const &cpParams);
  DiVoid  ResetSpeedAndUnregCallbackAfterReachMarker(bool restoreGraphSpeed);

  //////////////////////////////////////////////////////////////////////////
  // PRIVATE            Update()-functionality (INTERNAL!)
  //////////////////////////////////////////////////////////////////////////
  DiAnGrUpdateState UpdateBegin();
  DiAnGrUpdateState UpdateNode(DiUInt32 nNodeCur, DiUInt32 nNodeNext, DiFloat &rDt, 
                               DiAnGrFlTransParam tpParam);
  DiUInt32          SelectNextNodeByProbability(DiUInt32 nNodeID, DiAnimNode *anpCurNode);
  DiAnGrUpdateState UpdateCurNodeSetting( DiBool isNeedResetCallbacks ); // this function changes AnimGraph => it can't be called abstractly as UpdateNode()
  DiAnGrUpdateState UpdateNodeActive(DiUInt32 nNodeCur, DiUInt32 nNodeNext, 
                                     DiFloat &rDt, DiBool &bWrapped,
                                     DiAnGrFlTransParam tpParam);
  DiAnGrUpdateState UpdateNodeActiveLooped(DiUInt32 nNode, DiFloat &rDt, DiBool &bWrapped,
                                           DiAnGrFlTransParam tpParam);
  DiAnGrUpdateState UpdateNodeActiveNotLooped(DiUInt32 nNodeCur, DiUInt32 nNodeNext, 
                                              DiFloat &rDt, DiBool &bWrapped,
                                              DiAnGrFlTransParam tpParam);
  DiAnGrUpdateState UpdateNodeActiveInFlTrans(DiUInt32 nNode, DiFloat &rDt, 
                                              DiBool &bWrapped,
                                              DiAnGrFlTransParam tpParam);
  DiAnGrUpdateState UpdateTransactionInt(DiAnimFlTransaction *atpTrans, DiAnGrFlTransParam tpParam, 
                                         DiFloat &rDt);
  DiAnGrUpdateState UpdateTransactionSetting();
  DiAnGrUpdateState UpdateTransactionActive(DiFloat &rDt);
  DiAnGrUpdateState UpdateFlTransaction(DiFloat &rDt);

  // special update() of *one* node
  DiBool            UpdateOnlyOneNode( DiUInt32 nNodeToUpdate, DiUInt32 nNodeNext, 
                                       DiFloat rDt, DiBool &bIsNodeWaiting,
                                       DiAnGrFlTransParam tpParam);

  
  DiVoid            WrapCurParIfNeeded(DiBool bWrapped, DiAnimNode *anpNode, DiUInt32 nodeIdx);
  DiVoid            UpdateNodeSequences(DiUInt32 nNode);
  DiFloat           GetTimeTillNearestClbOnPar(DiAnGrClbStorageElem *sepRoot, DiFloat curVP, DiFloat defaultTime, DiFloat elemSpeed);
  DiFloat           SplitTimeTillNextClbOnParInElement(DiFloat rDtLeft);


  //////////////////////////////////////////////////////////////////////////
  // PRIVATE            Working with matrices/bones - using animation sequences
  //////////////////////////////////////////////////////////////////////////
  DiVoid            SetAnimation();
  DiVoid            SetAnimationNode();
  DiVoid            SetAnimationMacronode();
  DiVoid            SetAnimationTransaction();
  DiVoid            SetAnimationTransactionNode2Node();
  DiVoid            SetAnimationTransactionNode2Macronode();
  DiVoid            SetAnimationTransactionMacronode2Node();
  DiVoid            SetAnimationTransactionMacronode2Macronode();


  //////////////////////////////////////////////////////////////////////////
  // PRIVATE            Callbacks-functionality (INTERNAL!)
  //////////////////////////////////////////////////////////////////////////

  #ifdef DIANGR_SCREEN_DEBUG_ADVANCED
    DiAnGrClbStorageElem *RegisterCallbackInt(DiTChar *cpName,DiAnimGraphElems geElem, DiUInt32 nID,
                                            DiAnGrCallback fpCallback,  DiUInt32 nCallFlags,  DiVoid *vpUserData,
                                            DiFloat rExactParam = DIANGR_INVALID_FLOAT_VALUE,
                                            DiFloat probability = 100.f);
  #else // release version
    DiAnGrClbStorageElem *RegisterCallbackInt(DiAnimGraphElems geElem, DiUInt32 nID,
                                            DiAnGrCallback fpCallback, DiUInt32 nCallFlags, DiVoid *vpUserData,
                                            DiFloat rExactParam = DIANGR_INVALID_FLOAT_VALUE,
                                            DiFloat probability = 100.f);
  #endif //DIANGR_SCREEN_DEBUG_ADVANCED

  DiVoid                ResetCallbacksOnParFlag(DiAnimGraphElems geElement, DiVoid *vpElement);

  DiInt32               DiAnGrClCallCallbackOnPar(DiAnGrClbStorageElem *sepClb, DiFloat rElementVPar, DiBool bIsSpeedPositive,
                                                  DiUInt32 nCurCallFlags, DiAnimGraphElems geElement, DiFloat rTimeLeftForUpdate, 
                                                  DiVoid *vpElemPtr, DiAnGrFlTransParam tpParam);

  DiInt32               CallCallbackByFlags(DiAnGrClbStorageElem *sepClb, DiAnimGraphElems geElement, DiUInt32 nCurCallFlags,
                                            DiVoid *vpElemPtr, DiFloat rTimeLeftForUpdate, DiBool bInFlTransaction,
                                            DiAnimFlTransaction *atpFlTrans, DiAnGrFlTransParam tpParam, DiBool bGraphUpdate,
                                            DiFloat rElementVPar, DiBool  bIsSpeedPositive);

  DiInt32               CallCallbacks(DiUInt32 nCurCallFlags, DiAnimGraphElems geElement, DiFloat rTimeLeftForUpdate, 
                                      DiVoid *vpElemPtr,  DiAnGrFlTransParam tpParam = DIANGR_FLTRANS_NA);

  DiAnGrClbStorageElem  *FillCallbackStorage(DiAnGrClbStorageElem *sepRoot, DiVoid  *vpUserData,
                                            DiAnGrCallback fpCallback, DiFloat probability, DiUInt32 nCallFlags,
                                            DiTChar *cpName, DiFloat rExactParam, DiAnGrClbStorageElem  **pCreatedEl);

  static DiVoid         ReleaseCallbacksStorage(nstl::list<DiAnGrClbStorageElem>*& sepClbArray);
  DiBool                PrepareCallbacksStorage();
  DiAnGrClbStorageElem  *UnregisterCallbackInElem(DiAnGrClbStorageElem *sepRoot, DiAnGrCallback fpCallback, DiVoid *userDataIfYouKnowIt = NULL);
  DiAnGrClbStorageElem  *UnregisterCallbackInElemByClb(DiAnGrClbStorageElem *sepRoot, DiAnGrClbStorageElem *sepDel, DiAnGrClbStorageElem *_sepPrev = NULL);
  void                  RegisterReachMarkerCallback(const DiAnGrMarker &marker);
  void                  UnregisterReachMarkerCallback(DiAnimGraphElems elemType, DiUInt32 elemID);
  void                  clearCallback(DiAnGrClbStorageElem *sepClb);

  
  //////////////////////////////////////////////////////////////////////////
  // PRIVATE            Creation-functionality (INTERNAL!)
  //////////////////////////////////////////////////////////////////////////
  static DiAnimGraph *FillFromCreator(  const NDb::AnimGraphCreator *agCreator, 
                                      const vector<NDb::Animation> &animations,
                                      DiAnimNamesArray  *napSeqsTables,
                                      DiInt32 *npNumSequencesInTables,
                                      DiAnGrNodeSrchList *slp,
                                      const DiTChar *cpName,
                                      DiAnGrLoadCallback *lcCallback = NULL);
  static void         CreateCreatorWithAllAnims(const vector<string> &animations, NDb::AnimGraphCreator &creatorToFill);
  static void         CreateCreatorWithAllNDBAnims(const vector<NDb::Animation> &animations, NDb::AnimGraphCreator &creatorToFill);
  static void         CreateCreatorWithDummyData(NDb::AnimGraphCreator &creatorToFill, const nstl::string &sampleSeqName);

  // static functions
  static   DiBool   PreReadFile(const NDb::AnimGraphCreator &agCreator, PreReadParams &pParams);
  
  static   DiBool   AddNodeToTableOnConstructor(const DiTChar *cpName);

  static   DiTChar  *GetNodeNameFromTableOnConstructor(int nodeIdx); // (DO NOT USE at runtime!)
  static   DiUInt32 GetNodeIDByNameOnConstructor(const DiTChar *cpName);  // (DO NOT USE at runtime!)
  
  // own functionality  
  DiBool   FillGraph(const NDb::AnimGraphCreator &agCreator,
                       const vector<NDb::Animation> &animations,
                       DiAnimNamesArray  *napSeqsTables,
                       DiInt32 *npNumSequencesInTables);

  DiBool   CreateAndAddMacronode(const NDb::AnGrMacronode &macronode, 
                                 DiAnimNamesArray  *napSeqsTables,
                                 DiInt32 *npNumSequencesInTables);

  DiBool   CreateAndAddNode( const NDb::AnGrMacronode &node, 
                              DiAnimNamesArray  *napSeqsTables,
                              DiInt32 *npNumSequencesInTables );

  DiBool   CreateAndAddTransaction(DiTChar *cpBuf, DiInt32 nLen,
                                   DiUInt32 nNodeFromID, DiAnimGraphElems geElem);
  DiBool   CreateAndAddFlTransaction(DiTChar *cpBuf, DiInt32 nBufLength,
                                     DiUInt32 nNodeFromID, DiAnimGraphElems geElem);
  DiBool   CreateAndAddGeneralTransaction(const NDb::AnGrFlMultiTransaction multiUniTrans,
                                          DiUInt32 nNodeFromID, int normalizedProbability);

  DiBool   CreateAndAddMarker(const NDb::AnGrMarker &marker, EditorGraphParamAddress::OwnerType owner, int nodeIdx, int transIdx, int subTransIdx);

  //////////////////////////////////////////////////////////////////////////
  // PRIVATE            INTERNAL(!) Get()-methods
  //////////////////////////////////////////////////////////////////////////
  DiAnimGraphElems      GetCurElemType() const;
  DiUInt32              GetTargetNode() const;
  DiUInt32              GetCurTransaction();
  DiUInt32              GetCurTransactionUnsafe();
  DiUInt32              GetCurSubTransaction();
  DiFloat               GetCurTransactionPar();
  DiFloat               GetCurLinTransactionPar();
  
  DiAnGrClbStorageElem*     GetClbStorage();
  DiAnimMTransaction*       GetTransactionData(DiUInt32 nTransID);
  DiAnimMTransaction const* GetTransactionData(DiUInt32 nTransID) const;
  DiUInt32                  GetTransactionNumIntervals(DiUInt32 nTransID) const;
  DiAnimFlTransaction*      GetTransactionData(DiUInt32 nTransID, DiUInt32 nSubTransID, DiUInt32 nodeFrom = 0, DiUInt32 nodeTo = 0);

  DiFloat               GetCurVPar(DiVoid);
public: 
  DiAnimNode*               GetNodeData(DiUInt32 nNodeID);
  const DiTChar         *GetNodeNameByID(DiUInt32 nID);
  DiUInt32              GetNodeIDByNameSlow(const DiTChar *cpName) const; 
  DiInt32               GetNodeIDByNameSlowQuite(const char *cpName) const;   // This function differs from GetNodeIDByNameSlow with returning value DIANGR_NO_SUCH_ELEMENT instead of 0 and lack of assert if no such node
  DiInt32               GetNextNodeIDByEdge(DiInt32 nodeFromID, DiInt32 edgeID); // returns -1 if fails

  //DiVoid                SetConcreteAnimSeqInCurrentLoopedNodeEDITORONLY(int seqIdx); //EDITOR ONLY ///eugbel/// Remove this when everything works on AnimGraph
  DiVoid                SliderPauseAtNodeAtVParEDITORONLY(const string &nodeName, float virtPar);
  DiVoid                SliderPauseAtNodeAtVParEDITORONLY(int nodeID, float virtPar);
  DiVoid                SliderContinueEDITORONLY();

private:
  vector <DiAnGrNodesMap> &GetRuntimeNamesTable() { return nmpaTableRuntime; }
  DiUInt32              GetSeqIdxByName(DiAnimNamesArray  napSeqsTable,
                                        DiUInt32 nNumSeqsInTable, const DiTChar *cpName);
  DiTChar               *GetSeqNameByIdx(DiAnimNamesArray  napSeqsTable,
                                         DiUInt32 nNumSeqsInTable, DiUInt32 nID);

 
  //////////////////////////////////////////////////////////////////////////
  // PRIVATE            INTERNAL(!) Set()-methods
  //////////////////////////////////////////////////////////////////////////
  DiVoid           SetBlender(NScene::IAnimGraphBlender **cppComponents, DiInt32 nComponents = 0);
  NScene::IAnimGraphBlender *GetBlender();
  DiVoid           SetNumParts(DiInt32 nNumParts);

  DiVoid           SetPrevNode(DiUInt32 nID); ///< This is an INTERNAL function!
  DiVoid           SetCurNode(DiUInt32 nID);  ///< This is an INTERNAL function!
  DiVoid           SetNextNode(DiUInt32 nID); ///< This is an INTERNAL function!
  //DiVoid         SetCurTransaction(DiUInt32 nID);
  //DiVoid         SetCurTransactionPar(DiFloat rPar);

  DiVoid           SetNodeVPar(DiAnimNode *npNode, DiFloat rVPar);
  DiVoid           SetNodeVPar(DiInt32 nNodeID, DiFloat rVPar);

  DiVoid           SetupVParOfNextNodeInTransaction(DiAnimNode *npNode, DiAnimFlTransaction *tpTrans);
  
  //////////////////////////////////////////////////////////////////////////
  // PRIVATE            Simple Storage support
  //////////////////////////////////////////////////////////////////////////

  // Special convertion functions for NEditor
  void    AddNodeToStorage( DiUInt32 nNodeID, DiAnGrSimpleStorage::Macronode &macronode,
                            const NScene::AnimationVector &_animations);
  void    AddMacronodeToStorage(DiUInt32 nMacronodeID, DiAnGrSimpleStorage::Macronode &macronode,
                                const NScene::AnimationVector &_animations);

  DiBool  AddTransactionToStorage(DiUInt32 nNodeTo, DiUInt32 nEdgeID, 
                                  DiAnGrSimpleStorage::MultiTransaction &multiTrans);
  DiBool  AddMarkerToStorage(DiUInt32 markerId, DiAnGrSimpleStorage::Marker &marker) const;
  DiBool  AddExtParCoeffToStorage(DiAnGrExtPars::EditorExternalParamLink const &srcExtParCoeff, DiAnGrSimpleStorage::ExternalParameterCoeff &extParCoeff) const;
  DiBool  AddExtDepToStorage(DiAnGrExtPars::EditorDependency const &extDepSrc, DiAnGrSimpleStorage::ExternalDependency &extDep) const;
  DiBool  AddExtParToStorage(DiAnGrExtPars::EditorExternalParam const &extParSrc, DiAnGrSimpleStorage::ExternalParameter &extPar) const;

  //////////////////////////////////////////////////////////////////////////
  // PRIVATE            Other internal functions
  //////////////////////////////////////////////////////////////////////////
  static DiVoid     FreeNodesTable();
  static DiVoid     CopyNodesTableToRuntimeTable(DiAnGrNodesMap *nmpSrc, DiAnimGraph *anpGraph, DiInt32 nNumNodes);

  DiVoid            FillSearchList(DiAnGrNodeSrchList *slp);
  DiBool            SetTargetNodeInternal(DiUInt32 nNode);
  DiBool            SetNode(DiUInt32 nNode, DiFloat rVPar = DIANGR_INVALID_FLOAT_VALUE);
  void              AddPathIfUnique(const DiAnimGraph::PathToMarker &newPath, vector<DiAnimGraph::PathToMarker> &pathsToMarker);
  void              ApplyPath(const PathSetupInfo &pathInfo);

  //////////////////////////////////////////////////////////////////////////
  // PRIVATE            Debug info on screen (not via console)
  //////////////////////////////////////////////////////////////////////////
  
  #ifdef DIANGR_SCREEN_DEBUG_GENERAL
    static DiVoid       DebugRegisterGraph(DiAnimGraph *agpGraph, DiUInt32 approxMemAllocated);
    static DiVoid       DebugUnregisterGraph(const DiAnimGraph *agpGraph);
    static DiVoid       DebugEmptyList();

    static DiVoid       DebugCopyNodesTable(DiAnGrNodesMap *nmpSrc, DiAnimGraph *anpGraph, DiInt32 nNumNodes);
    static DiVoid       DebugCopySeqNamesTables(DiAnimNamesArray *naSeqsTables, DiAnimGraph *anpGraph,
                                                DiInt32 *npNumSequencesInTables);

    DiVoid              DebugFreeDbTable();
    DiVoid              DebugFreeNamesTable();
    
    DiAnimNamesArray    *DebugGetDbSeqTables();
    DiAnGrNodesMap      *DebugGetDbNodesMapTable();
    DiInt32             *DebugGetDbNumSeqsInTables();
    DiInt32             DebugGetDbNumSeqsInTable(DiInt32 nPart);
  
  public:
    static DiVoid       DebugSetPrevGraph();
    static DiVoid       DebugSetNextGraph();
    static DiVoid       DebugSetGraph(DiAnimGraph *graph);
    static DiVoid       DebugIncSpeed();
    static DiVoid       DebugDecSpeed();
    static DiVoid       DebugChangeSpeedCoeffPrecision();
    static DiVoid       DebugChangeObject();
  private:

    DiTChar             *DebugGetNodeNameByID(DiUInt32 nID);

    DiVoid              DebugAddCallbackToQueue(DiAnGrClbStorageElem *sepCurCallback);

    // system open/close functions
    //static DiVoid       DebugSystemOpen(DiInt32 nContext);
    //static DiVoid       DebugSystemClose();
    // update 
    static DiVoid       DebugInputUpdate();
    static DiVoid       DebugUpdateInfo();
    static DiVoid       DebugUpdateNodesInfo(DiAnimGraph *agpGraph);
    static DiVoid       DebugUpdateEdgesInfo(DiAnimGraph *agpGraph);
    static DiVoid       DebugUpdateClbInfo  (DiAnimGraph *agpGraph);
    static DiVoid       DebugUpdateGraphInfo(DiAnimGraph *agpGraph);
    static DiVoid       DebugUpdateTweakInfo(DiAnimGraph *agpGraph);
    static DiVoid       DebugUpdateStateInfo(DiAnimGraph *agpGraph);

    static DiFloat      _diAnGrDbGetCurElemSpeed();
    static DiFloat      _diAnGrDbGetCurElemVP();
    static DiVoid       _diAnGrDbChangeCurElementSpeed(DiFloat rDelta);
  #endif DIANGR_SCREEN_DEBUG_GENERAL

  
  //////////////////////////////////////////////////////////////////////////
  // PRIVATE            User data support (use VERY CAREFULLY! NOT TESTED!!!)
  //////////////////////////////////////////////////////////////////////////

#ifdef GRAPH_NEED_USERDATA
  bool ReadUserDataFromFile(const char *cpCsv);
  void CreateEmptyUserData();
  void DestroyUserData();
#endif //GRAPH_NEED_USERDATA


  //////////////////////////////////////////////////////////////////////////
  // PRIVATE            Other staff. Use with care!
  //////////////////////////////////////////////////////////////////////////

  /* // @Matt!! Temporary functions
  void ReleaseTarget() { gpPath.nTargetNode = 0xFFFFFFFF; }
  bool ForceTargetNode(int nodeID);
  */
private:
  //////////////////////////////////////////////////////////////////////////
  // PRIVATE             Internal structs/classes
  //////////////////////////////////////////////////////////////////////////

  // this structure is used in pre-reading file (counting future data size)
  struct PreReadParams
  {
    DiUInt32 nNumNodes;
    DiUInt32 nNumFlTransactions;
    DiUInt32 nNumMacronodes;
    DiUInt32 nNumInternalNodes;
    DiInt32  nNumSequencesPerNode;
    
    // multi transactions specific
    DiInt32  nNumGeneralTransactions;  // number of all multi transactions in general case
    DiInt32  nNumMultiFlTransactions;  // total number of sub-FLtransactions in multi transactions

    void clear();
  };

  // this structure contains information about path that was calculated
  // in SetTargetNode()
  struct GraphPath
  {
    DiUInt32 nTargetNode;
    DiUInt32 *npPath;
    DiUInt32 nPathLength;
    DiUInt32 nCurIdxInPath;
  };

  struct PathSetupInfo
  {
    DiBool        bPathSpecified;
    DiUInt32      nNextNode;
    
    DiUInt32      nGPTargetNode;
    DiUInt32      npGPPath[DIANGR_MAX_MARKER_PATH_LENGTH];
    DiUInt32      nGPPathLength;
    DiUInt32      nGPCurIdxInPath;
    DiAnimGraph   *pGraph;

    PathSetupInfo();
    void SetGraph(DiAnimGraph *graph) { pGraph = graph; }
    void SetByNextNode(DiUInt32 nNextNode);
    void SetByPath(DiUInt32 const *path, DiUInt32 length, bool skipFirstElement);
    void SetNothingToDo();
    void ChangeElemInPath(int idxInPath, DiUInt32 newValue);
    bool IsTarget(DiUInt32 targetToCheck) const;
    bool IsEmpty() const;
    void Clear();
    bool operator == (const PathSetupInfo &other) const;
  };

  struct PathToMarker
  {
    int           nTimeInMS;
    DiAnGrMarker  mMarker;
    PathSetupInfo pathInfo;
    
    PathToMarker();
  };
  



  //////////////////////////////////////////////////////////////////////////
  // PRIVATE             Main data of the AnimGraph (DO NOT CHANGE ORDER!!!)
  //////////////////////////////////////////////////////////////////////////

  /// ATTENTION! DO NOT CHANGE ORDER!!! ADD NEW VARIABLES _TO_THE_END_ ONLY!!!
  /// AnimGraph has a memory-map structure and you can't add/remove/re-order it's members without re-writing the code!
  DiBool                bIsCurNodeMacronode;  // flag to determine Macronode

  DiUInt32              nCurTrans;      // <=> current edge
  DiUInt32              nCurSubTrans;   // - index of sub-transaction in current transaction. 
                            // if interval is 1 (<=> 1 sub-transaction) => index is 0
  DiFloat               rCurParInTransaction;
  DiFloat               rLinParInTransaction;

  DiFloat               rGraphSpeedCoeff; // speed coeff for WHOLE graph. By default it is equal to 1.0f

  DiUInt32              nPrevNode;       
  DiUInt32              nCurNode;
  DiUInt32              nNextNode;
  DiUInt32              nDefNode;

  DiBool                bPathSpecified;
  DiBool                bIsForced;
  GraphPath             gpPath;
  
  DiInt32                          nNumSeqsPerNode;
  NScene::IAnimGraphBlender   *cpaSceneComponents[DIANGR_MAX_NUM_SEQS_IN_NODE];

  DiInt32                   nNumRegisteredCallbacks;
  nstl::list<DiAnGrClbStorageElem>* sepClbArray; // array of ALL callbacks (for nodes, trans-s, graph)
  
  DiAnGrClbStorageElem      *sepClbStorage; // entire graph callback

  // special data to realize first update callback of node or sequence
  DiBool                    bNeedElementEnterCallback;
  DiBool                    bNeedElementLeaveCallback;

  // New data (after DiEngine)
  DiInt32                   nPrevRegisteredCallback;

  // Markers (appeared only in Nival engine)
  vector <DiAnGrMarker>     mMarkers;
  // Table of nodes names (specially for Nival usability) This table exists in Runtime but DO NOT USE IT regularly! Use indices only!
  vector <DiAnGrNodesMap>   nmpaTableRuntime;

  SpeedUserData::Ring       markersData;

  static    DiAnGrNodesMap  nmpaTableOnConstructorOnly[];   // used ONLY FOR READING => static (NOTE!!! Table doesn't exist IN RUNTIME!) This table is not empty only while constructor is running! When AnimGraph is constructed this table is empty!
  static    DiInt32         numEntries;
  vector<SVector>           nodesPos; // positions of nodes (in Editor ONLY!)

  nstl::vector<DiAnGrClbStorageElem*> callBacksToDel;

  //////////////////////////////////////////////////////////////////////////
  // PRIVATE             Data for DEBUG ONLY
  //////////////////////////////////////////////////////////////////////////
#ifdef DIANGR_SCREEN_DEBUG_GENERAL

  // variables to print in console (in debug)
  #define DIANGR_SET_TN_DEFAULT       0
  #define DIANGR_SET_TN_1             1
  #define DIANGR_SET_TN_2             2
  #define DIANGR_SET_TN_3             3

  public: // should be public to be accessible from Console
    static DiFloat  rMHCurParInTrans;
    static DiBool   bIsMHInTransaction;
    static DiFloat  rMHCurParInNode;
    static DiFloat  rMHCurParInSeq;
    static DiFloat  rMHNextNodePar;
    static DiUInt32 nMHTargetNode;
    static DiUInt32 nMHCurNode;
    static DiUInt32 nMHNextNode;

  private:
    DiTChar          caName[DIANGR_DEBUG_MAX_NAME_LEN];
    DiAnGrNodesMap   *nmpDbTable;     // saved table for EVERY graph
    DiAnimNamesArray *napDbSeqNames;  // pointer to an array of names of sequences
    DiInt32          *npDbNumSeqsInTables; // number of sequences in tables (for each ".ab")
    static DiInt32   nNumGraphs;      // number of registered graphs
#endif

#ifdef DIANGR_SCREEN_DEBUG_ADVANCED
    // variables for callbacks-debug

    // array of pointers to callbacks storages
    DiAnGrClbStorageElem *seapLatestCallbacks[DIANGR_DEBUG_MAX_LAST_CALLBACKS];
    DiInt32              nUsedCallbacksCells;
    DiInt32              nCallbackCellToFill;

#endif DIANGR_SCREEN_DEBUG_GENERAL



  // Friends (to hide special public functions of DiAnimGraph from other classes)
  friend struct DiAnGrSimpleStorage;
  friend class  DiAnGrExtPars;
  friend class  DiAnGrMarker;
  friend class  CAnimGraphDoc;
  friend class  UDDAGWrapper;
  friend class  DiAnGrLoadCallback;
  friend class  NScene::AnimGraphBlender;
  friend class  NScene::AnimGraphController;

  template <class T> friend class DiAnGrNamesIDLinker;

  friend static void NScene::_printDebugStatus(DiAnimGraph *animGraph, float dt);
  friend DiInt32 _resetGraphSpeedCallback(DiAnGrCallbackParams const &cpParams);
  
  // Editor functions
  friend DiVoid GetPlayingNodeG(DiBool& bNode, DiUInt32& nFirstNode, DiUInt32& nSecondNode);
  friend DiInt32 EnterCallbackFunction(const DiAnGrCallbackParams& params);
  friend DiInt32 LeaveCallbackFunction(const DiAnGrCallbackParams& params);
  friend static LRESULT OnSetGraphToEngine(HWND hwnd);
  friend DiAnimGraph *convertDocToGraph();
  friend DiInt32 _wholeGraph2UpdateCallback(DiAnGrCallbackParams const &cpParams);
};

///eugbelNSCENE///} // end of namespace NScene

#endif // ifndef _DIANGR_H_
