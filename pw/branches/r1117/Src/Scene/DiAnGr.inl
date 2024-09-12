/*
 * @file    DiAnGr.inl
 * @memo    AnimationGraph small structures and classes
 * @author  EugBel
 * @date    05.12.2008
 * @prefix  DiAn, DiAnGr
 */

#ifndef _DIANGR_INL_
#define _DIANGR_INL_


#ifndef __DIANGR_INTERNAL_INCLUDE__
  #error File DiAnGr.inl could be included ONLY from DiAnGr.h! Use DiAnGr.h directly!
#endif // __DIANGR_INTERNAL_INCLUDE__


// max number of callbacks for whole graph
#define DIANGR_MAX_NUM_CALLBACKS              300

// maximum number of sequences in node
#define DIANGR_MAX_NUM_SEQS_IN_NODE           2

// maximum number of nodes in path till specified marker (in function ReachMarkerByTime())
#define DIANGR_MAX_MARKER_PATH_LENGTH          10

// ID that never exists in graph
#define DIANGR_NO_SUCH_ELEMENT                1000000
#define DIANGR_INVALID_FLOAT_VALUE            MAX_FLOAT
#define DIANGR_BIG_INT                        100000
#define DIANGR_MIN_FLOAT_VALUE                MIN_FLOAT
#define DIANGR_MIN_SPEED                      0.0001f
#define DIANGR_MIN_DT                         0.00001f

#define DIANGR_INVALID_PRIORITY               123456

// defines that deals with default or auto values
//#define DIANGR_SYNCH_NODES_IN_FLTRANS_F       (MAX_FLOAT / 3.0f)
#define DIANGR_DEFAULT_SEQUENCE_SPEED         1.0f
#define DIANGR_DEFAULT_TRANSACTION_SPEED      1.0f

// These values (for start/stop parameters) are used because start/stop pars for NODES are not used now in data: user specify only start/sopt parameters for sequences
#define DIANGR_DEFAULT_NODE_START_PAR         0.0f 
#define DIANGR_DEFAULT_NODE_STOP_PAR          1.0f

#define DIANGR_MAX_SEQ_NAME                   50
#define DIANGR_NODE_NAME                      "Node"
#define DIANGR_MACRONODE_NAME                 "Macronode"
#define DIANGR_TRANSACTION_NAME               "Transaction"
#define DIANGR_FLTRANSACTION_NAME             "FLTransaction"
#define DIANGR_MULTITRANSACTION_NAME          DIANGR_TRANSACTION_NAME   //"MultiTransaction"
#define DIANGR_MULTIFLTRANSACTION_NAME        DIANGR_FLTRANSACTION_NAME //"MultiFLTransaction"

// callback call flags
#define DIANGR_CF_UPDATE_BEGIN                (1L << 1)
#define DIANGR_CF_UPDATE_END                  (1L << 2)
#define DIANGR_CF_ELEMENT_ENTER               (1L << 3)
#define DIANGR_CF_ELEMENT_LEAVE               (1L << 4)
#define DIANGR_CF_EXACT_PARAM                 (1L << 8)

#define DIANGR_CF_UPDATE_ALWAYS               (DIANGR_CF_UPDATE_BEGIN |     \
                                              DIANGR_CF_UPDATE_END    |     \
                                              DIANGR_CF_ELEMENT_ENTER |     \
                                              DIANGR_CF_ELEMENT_LEAVE )

                                      
// flow-transaction update flags
#define DIANGR_FLKIND_NONE                    (1L << 0)  // none of nodes will be updated. This could be used in case of program update of some transaction's parameters.
                                                         // Plain Transaction will assert on these program changes => you should use FLTransaction
#define DIANGR_FLKIND_FIRST                   (1L << 1)  // update 1st node. second is stopped (like in normal transaction)
#define DIANGR_FLKIND_SECOND                  (1L << 2)  // update 2d  node. first  is stopped (like in normal transaction)
#define DIANGR_FLKIND_BOTH                    (DIANGR_FLKIND_FIRST | DIANGR_FLKIND_SECOND) 

// names for the flags above
#define DIANGR_FLKIND_NAME_NONE                "NONE"
#define DIANGR_FLKIND_NAME_FIRST               "FIRST"
#define DIANGR_FLKIND_NAME_SECOND              "SECOND"
#define DIANGR_FLKIND_NAME_BOTH                "BOTH"

// debug internal defines
#ifdef DIANGR_SCREEN_DEBUG_ADVANCED
  // internal callback's name distinguisher
  #define DIANGR_INT_CALLBACK_PREFIX            "_"
  // max visible callbacks in debug mode
  #define DIANGR_DEBUG_MAX_LAST_CALLBACKS       6
#endif
#ifdef DIANGR_SCREEN_DEBUG_GENERAL
  // max length of graph's name
  #define DIANGR_DEBUG_MAX_NAME_LEN             10
#endif


// transaction priorities
#define DIANGR_PRIORITY_MIN                     (1.0f)
#define DIANGR_PRIORITY_NORM                    (10.0f) // recommended default priority
#define DIANGR_PRIORITY_MAX                     (100.0f)

// enum of reading-states
enum DiAnimGraphElems
{
  DIANGR_NA    = -1,
  DIANGR_NODE,
  DIANGR_MACRONODE,
  DIANGR_FLTRANSACTION,
  DIANGR_ENTIREGRAPH,
  DIANGR_LAST,
  DIANGR_FORCEDWORD  = 0x7FFFFFFF
};

// this enum represents states of DiAnimGraph::Update()
enum DiAnGrUpdateState
{
  DIANGR_UPDATE_NA    = -1,
  DIANGR_UPDATE_BEGIN,
  DIANGR_UPDATE_END,
  DIANGR_UPDATE_NODE_SETTING,
  DIANGR_UPDATE_NODE_SETTING2,
  DIANGR_UPDATE_NODE_ACTIVE,
  DIANGR_UPDATE_TRANSACTION_SETTING,
  DIANGR_UPDATE_FLTRANSACTION_ACTIVE,
  DIANGR_UPDATE_FORCEDWORD = 0x7FFFFFFF
};

// this enum is used for updating FLTransaction
enum DiAnGrFlTransParam
{
  DIANGR_FLTRANS_NA         = -1,
  DIANGR_FLTRANS_NODE1,
  DIANGR_FLTRANS_NODE2,
  DIANGR_FLTRANS_TRANSACTION,
  DIANGR_FLTRANS_FORCEDWORD = 0x7fffffff
};

// This structure is used
// while reading csv-file to create array of NodesMap. Index in array is 
// node's ID
struct DiAnGrNodesMap
{
  DiTChar  cpNodeName[DIANGR_MAX_SEQ_NAME];

  DiAnGrNodesMap(DiTChar *_name)
  {
    strcpy_s(cpNodeName, DIANGR_MAX_SEQ_NAME, _name);
  }

  DiAnGrNodesMap()
  {
    strcpy_s(cpNodeName, DIANGR_MAX_SEQ_NAME, "");
  }
};

// interface function structure (to save OB and AB filenames)
struct DiAnimFileNames
{
  DiTChar             *capNamesOB[DIANGR_MAX_NUM_SEQS_IN_NODE];
  DiTChar             *capNamesAB[DIANGR_MAX_NUM_SEQS_IN_NODE];
};

// callback parameters
struct DiAnGrCallbackParams
{
  DiUInt32            nCallFlags;
  DiAnimGraphElems    geElement;
  DiAnGrFlTransParam  tpParams;
  DiFloat             rTimeLeftForUpdate;
  union 
  {
    DiAnimNode        *anpNode;
    DiAnimMacronode   *anmpMacronode;
    DiAnimFlTransaction *atpTrans;
  };
  DiVoid              *vpUserData;       

  DiAnGrCallbackParams(DiUInt32 nCallFlags, DiAnimGraphElems geElement,
                       DiFloat rTimeLeftForUpdate, DiVoid *vpElemPtr, 
                       DiVoid *vpUserData, DiAnGrFlTransParam tpParams);
};

class DiAnGrLoadCallback
{

protected:
  DiAnimGraph           *m_agpGraph;
  DiAnGrNodesMap        *m_nmpNodesNames;

public:
  DiAnGrLoadCallback() : m_agpGraph(NULL), m_nmpNodesNames(NULL) {}

  virtual void LoadCallbackFunction() = 0;
  
  // This function is called automatically
  DiVoid SetGraph(DiAnimGraph *agpGraph)          { m_agpGraph      = agpGraph; }
  
  // Set of useful functions (NOT called automatically)
  DiVoid SetNodes(DiAnGrNodesMap *nmpNodesNames)  { m_nmpNodesNames = nmpNodesNames; }
  DiBool SaveNodesNames();

  DiAnimGraph    *GetGraph()                      { return m_agpGraph; }
  DiAnGrNodesMap *GetNodes()                      { return m_nmpNodesNames; }
};

// pointer to callback function
typedef DiInt32 (*DiAnGrCallback)(DiAnGrCallbackParams const &cpParams);


// this structure is used as element in SList where all callbacks are stored
struct DiAnGrClbStorageElem
{
  DiUInt32                  nCallFlags; // see DIANGR_CF_...

  // value of virtual parameter for Value-callback
  // Callback will be called at the first update where 
  // virt. parameter of element is >= rClbParam
  DiFloat                   rClbParam; 
  
  // this flag indicates whether this callback was called
  // since virtual parameter of element passed 0.0f when ElementSpeed > 0
  // and 1.0f when speed < 0
  DiBool                    bIsClbCalledSinceElemStarted;

  // priority of callback. Callbacks with priority 0 will be called first, 
  // than with priority 1 ...
  // If priority is not specified at registering callback than it will be automatically 
  // set by this rule: (FIFO) first registered => first called
  DiUInt32                  nPriority;
  
  // pointer to registered callback
  DiAnGrCallback            fpCallback;
  
  // use data
  DiVoid                    *vpUserData;

  DiFloat                   probability;

#ifdef DIANGR_SCREEN_DEBUG_ADVANCED
  DiTChar                   *cpName; 
#endif

  // next callback for current node
  // NOTE: when registering callbacks
  DiAnGrClbStorageElem      *sepNext;

  ~DiAnGrClbStorageElem();
#ifdef DIANGR_SCREEN_DEBUG_ADVANCED
  DiAnGrClbStorageElem(): nCallFlags(0), rClbParam(DIANGR_INVALID_FLOAT_VALUE),
                          bIsClbCalledSinceElemStarted(FALSE),
                          nPriority(DIANGR_INVALID_PRIORITY), fpCallback(NULL),
                          vpUserData(NULL), cpName(NULL), sepNext(NULL)
  {}
#else
  DiAnGrClbStorageElem(): nCallFlags(0), rClbParam(DIANGR_INVALID_FLOAT_VALUE),
                          bIsClbCalledSinceElemStarted(FALSE),
                          nPriority(DIANGR_INVALID_PRIORITY), fpCallback(NULL),
                          vpUserData(NULL), sepNext(NULL)
  {}
#endif

  bool IsEmpty() { return (NULL == fpCallback); }

};

struct PathChange
{
  int prevNodeIdxInPath;
  int newNodeIdxInPath;

  PathChange() : prevNodeIdxInPath(0), newNodeIdxInPath(0) {}
  PathChange(int prevVal, int newVal) : prevNodeIdxInPath(prevVal), newNodeIdxInPath(newVal) {}
};


// this is structure of sequence in DiAnimNode
struct DiAnGrSequence
{
  friend class DiAnGrExtPars;

  DiInt32                 nID;                   // sequence ID
  DiFloat                 rCurPar;               // current virtual parameter
  DiFloat                 rStartPar;             // min par
  DiFloat                 rStopPar;              // max par
  DiFloat                 rSpeed;                // sequence speed. Usually it is 1.0f
  DiFloat                 rWeight;               // sequence weight (by default 1.0f)
  
  DiAnGrSequence() 
  { 
    Init(); 
  }   
  ~DiAnGrSequence() {}

  DiVoid SetVPar(DiFloat rStartNodePar, DiFloat rStopNodePar,DiFloat rNodePar);
  DiInt32 const GetID() const { return nID;       }
  DiVoid  SetID(DiInt32 _nID) { NI_ASSERT(0 <= _nID && _nID < 1000, "Wrong ID!"); nID = _nID; }
  DiFloat GetSpeed()          { return rSpeed;    }
  
  DiFloat GetStartPar()       
  { 
    DIASSERT(0.0f <= rStartPar && rStartPar <= 1.0f);
    return rStartPar; 
  }
  DiFloat GetStopPar()        
  { 
    DIASSERT(0.0f <= rStopPar && rStopPar <= 1.0f);
    return rStopPar;  
  }

  DiVoid SetStartPar(DiFloat startPar)
  {
    DIASSERT(0.0f <= startPar && startPar <= 1.0f);
    rStartPar = startPar;
  }
  DiVoid SetStopPar(DiFloat stopPar)
  {
    DIASSERT(0.0f <= stopPar && stopPar <= 1.0f);
    rStopPar = stopPar;
  }
  
  // small functions
  DiVoid  SetAutoSpeed() 
  { 
    // setup speed if not done yet
    if (DIANGR_INVALID_FLOAT_VALUE == rSpeed)
    {
      DIASSERT(rStopPar >= rStartPar); 
      rSpeed = 1.0f / (rStopPar - rStartPar); 
    }
  }
  DiVoid  Init()
  {
    nID       = 0; 
    rStartPar = 0.0f; 
    rStopPar  = 1.0f; 
    rCurPar   = 0.0f; 
    rWeight   = 1.0f;
    rSpeed    = DIANGR_INVALID_FLOAT_VALUE;
    SetAutoSpeed(); 
  }
  
};

// Earnol
struct DiAnGrNodeSrchEntry
{
  DiInt32           nNodeID;
  DiTChar           *cpNodeName;
  DiAnimGraphElems  geType;
};
struct DiAnGrNodeSrchList
{
  DiInt32             nNumEntries;
  DiAnGrNodeSrchEntry *seEntries;
};

class KicksData;
// DiAnimNode is node in AnimGraph
// NOTE: don't try to write constructor! (because of code structure
// we create not DiAnimNode but something else => constructor won't be called
class DiAnimNode
{
  // declare friends
  friend class DiAnimGraph;
  friend class DiAnGrExtPars;

  DiFloat              rSpeed;          // speed of animation
  DiBool               bIsThisMacronode;// flag to determine Macronodes
  DiFloat              rCurPar;         // current virtual parameter
  DiFloat              rPrevPar;        // virtual parameter at previous update()
  DiVec2               rSurfSpeed;      // surface speed for this node
  DiBool               bIsSwitcher;     // is this node a switcher (like "idle_in" with neighbours "idle1", "idle2", "idle3")
  DiBool               bIsSubNode;
  DiBool               bIsLooped;       // is animation looped
  DiAnGrClbStorageElem *sepClbStorage;  // callback's storage
  DiUInt32             nDefNext;        // Default next node
  DiUInt32             dispatcherID;
  DiFloat              speedMultiplier; //
  DiFloat              logicSpeedMultiplier;

  DiUInt32             numNeighbours;

  DiFloat              rDefaultSpeed;

protected:
  DiAnimGraph          *gpGraph;        // pointer to graph
  // next 2 params are now not used: just add their reading from file 
  // and they will (should) be supported                            
  DiFloat              rStartPar; // start value of parameter in node seq when we can play
  DiFloat              rStopPar;  // end value of parameter -//-

public:
  mutable DiAnGrSequence    *spSequences;    // sequence indices (in Node:nNumSequencesPerNode, 
                                     // in Macronode: nNumSequencesPerNode*nNumInternalNodes)
                                     // This member is mutable to have GetNodeData() as a const-function
  KicksData          *pUserData;      // Pointer to user data

public:
  DiAnimNode() : bIsThisMacronode(false), rCurPar(-1.f), rPrevPar(-1.f), rSpeed(0.f), rSurfSpeed(0.f, 0.f), bIsSwitcher(false),
                 bIsLooped(true), gpGraph(NULL), sepClbStorage(NULL), nDefNext(0), pUserData(NULL), rDefaultSpeed(1.0f), 
                 dispatcherID(DIANGR_NO_SUCH_ELEMENT), numNeighbours(DIANGR_NO_SUCH_ELEMENT)
  { }

  DiBool          IsMacronode()  const              { return bIsThisMacronode; }

  DiVoid          SetVPar(DiInt32 nSeqNum, DiFloat rVPar = DIANGR_INVALID_FLOAT_VALUE);
  DiVoid          SetCurVPar(DiFloat rCurPar);
  DiVoid          SetSpeed(DiFloat rSpeed);
  DiVoid          SetSurfSpeed(DiVec2 rSurfSpeed);
  DiVoid          SetDefaultSpeed(DiFloat rSpeed);
  DiVoid          SetSwitcher(DiBool bIsSwitcher);
  DiVoid          SetLooped(DiBool bLooped, DiUInt32 thisNodeID, DiUInt32 nDefNextNode);
  DiVoid          SetDefNextNode(DiUInt32 nNode)  ;
  DiVoid          SetMacronodeFlag(DiBool bIsMacro);
  DiVoid          SetStartPar(DiFloat rPar);
  DiVoid          SetStopPar(DiFloat rPar);
  DiVoid          SetClbStorageToNull();
  DiVoid          SetGraph(DiAnimGraph *agpGr);

  DiFloat         GetLogicSpeed() { return logicSpeedMultiplier; }
  DiVoid          SetLogicSpeed( DiFloat mult ) { logicSpeedMultiplier = mult; }

  DiFloat         GetMultiplier() { return speedMultiplier; }
  DiVoid          SetMultiplier( DiFloat mult ) { speedMultiplier = mult; }

  DiVoid          SetSubNode( DiBool val ) { bIsSubNode = val; }
  DiBool          IsSubNode() { return bIsSubNode; }
    
  DiFloat         GetVPar() const;
  DiFloat const   GetPrevPar() const          {return rPrevPar; }
  DiFloat         GetStartPar() const;
  DiFloat         GetStopPar() const;
  DiUInt32        GetDefNextNode() const;

  DiVoid          SetDispatcherNodeID( DiUInt32 id ) { dispatcherID = id; }
  DiUInt32        GetDispatcherNodeID() { return dispatcherID; }

  DiFloat         GetSpeed(DiVoid) const            { return rSpeed; }
  DiVec2          GetSurfSpeed() const              { return rSurfSpeed; }
  DiFloat         GetDefaultSpeed() const           { return rDefaultSpeed; }
  
  DiBool          IsSwitcher() const                { return bIsSwitcher; }
  DiBool          IsLooped() const                  { return bIsLooped; }

  DiVoid          SetNumNeighbours( DiUInt32 num )  { numNeighbours = num; }
  DiUInt32        GetNumNeighbours() const          { return numNeighbours; }
  
  // getting callbacks
  DiAnGrClbStorageElem *GetClbStorage()     { return sepClbStorage; }
  DiAnGrSequence       *GetSequences()      { return spSequences; }

  DiFloat*        GetNodeFieldAddress(const string& name);

  operator DiAnimMacronode *() 
  {
    if(bIsThisMacronode) 
      return (DiAnimMacronode *)((DiVoid *)this); 
    else 
      return NULL;
  }

private:
  DiVoid        SetPrevPar(DiFloat const rPrevPar) {this->rPrevPar = rPrevPar;}
  DiBool        TestForDispatcher( DiUInt32 dispatcherID, DiUInt32 nodeID );
  DiUInt32      CalcDispatcherNodeID();
};


// This class is node in DiAnimGraph and is used
// for interpolating animations (e.g. between LowJump and HighJump)
class DiAnimMacronode : public DiAnimNode
{
  // declare friends
  friend class DiAnimGraph;

  DiInt32 nNumInternalNodes;  // number of animations to interpolate
public:
  DiAnimMacronode() : DiAnimNode(), nNumInternalNodes(-1)
  { }

  DiVoid  SetVPar(DiInt32 nSeqNum, DiFloat rVPar);
  DiVoid  SetIntNodeWeight(DiInt32 nIntNode, DiFloat rW);
  DiVoid  SetIntNodesWeights(DiFloat *rpW);
  DiVoid  SetDifferentVParsForIntNodes(DiFloat *rpVPars, DiInt32 nNum);
  DiVoid  SetNumIntNodes(DiInt32 nNum) { nNumInternalNodes = nNum;}
  

  DiFloat GetIntNodeWeight(DiInt32 nIntNode, DiInt32 nSeqIdx) const;
  DiInt32 GetNumIntNodes();
};


// DiAnimFlTransaction is edge in DiAnimGraph;
// Transaction is mixing between two animations (two nodes)
class DiAnimFlTransaction
{
  friend class DiAnimGraph;
  friend class DiAnGrExtPars;

public:
  // kind of transaction
  enum Kind
  {
    DIAN_TRKIND_NA = -1,
    DIAN_TRKIND_UNIFORM,
    DIAN_TRKIND_3PARABOLIC,
    DIAN_TRKIND_3RECPARABOLIC,
    DIAN_TRKIND_SINE,
    DIAN_TRKIND_RECSINE,
    DIAN_TRKIND_SPLINE,
    DIAN_TRKIND_RECSPLINE,
    DIAN_TRKIND_FORCEDWORD = 0x7FFFFFFF
  };

private:
  DiFloat              rSpeed;        // speed of transaction
  Kind                 kKind;         // kind of transaction
  DiFloat              rParA;
  DiFloat              rParB;
  DiFloat              rFromParamMin; // min value of VPar when we can start mix
  DiFloat              rFromParamMax; // max value of VPar when we can stop mix
  DiFloat              rToParam;      // value of VPar in target animation
  DiFloat              rPrevPar;      // virtual parameter at previous update()
  DiUInt32             nUpdFlags; // kind of updating. See DIANGR_FLKIND_
  
public:
  DiAnimFlTransaction() : rSpeed(MAX_FLOAT), kKind(DIAN_TRKIND_NA), rParA(MAX_FLOAT), rParB(MAX_FLOAT),
                        rFromParamMin(MAX_FLOAT), rFromParamMax(MAX_FLOAT), rToParam(MAX_FLOAT), rPrevPar(MAX_FLOAT),
                        nUpdFlags(DIANGR_FLKIND_NONE)
  { }
                                    
  // get-function
  DiVoid  GetStartStopParams(DiFloat &rStartPar, DiFloat &rStopPar);
  DiFloat CalcCurPar(DiFloat rCurLinPar, DiFloat rOldCurPar, const nstl::string& dbfilename);
  
  DiBool  FillMainParamsFromFile(const NDb::AnGrFlTransaction &uniTrans, DiUInt16 *npWeight, const nstl::string& dbfilename);

  
  DiVoid  SetSpeed(DiFloat const rSpeed) {this->rSpeed = rSpeed;}
  DiVoid  SetToParam(DiFloat const rToParam) {this->rToParam = rToParam;}
  DiVoid  SetParamFromMin(DiFloat const rPar) {this->rFromParamMin = rPar; }
  DiVoid  SetParamFromMax(DiFloat const rPar) {this->rFromParamMax = rPar; }
  DiVoid  SetAddParams(DiFloat rA, DiFloat rB) { rParA = rA; rParB = rB; }
  
  DiVoid  SetKind(Kind const kNewKind) { this->kKind = kNewKind; }

  // set/get methods
  DiVoid   SetUpdateFlags(DiUInt32 nUpdateFlags) { nUpdFlags = nUpdateFlags; }
  DiUInt32 GetUpdateFlags()                      { return nUpdFlags; }


  DiFloat const GetToParam(DiVoid) const { return rToParam;}
  DiFloat const GetPrevPar()       const {return rPrevPar; }
  DiFloat const GetAParam(DiVoid)  const { return rParA;}
  DiFloat const GetBParam(DiVoid)  const { return rParB;}
  DiFloat const GetSpeed(DiVoid)   const { return rSpeed;}
  Kind    const GetKind()          const { return kKind; }
  DiFloat const GetMinFromPar()    const { return rFromParamMin; }
  DiFloat const GetMaxFromPar()    const { return rFromParamMax; }

  // convertions
  static  Kind     ConvertKind(DiTChar *cpKind);
  static  DiTChar *ConvertKind(Kind kKind);

  static  DiVoid  ConvertExtParsToIntPars(Kind kKind, DiFloat rAIn, DiFloat rBIn,
                                          DiFloat &rAOut, DiFloat &rBOut);
  static  DiVoid  ConvertIntParsToExtPars(Kind kKind, DiFloat rAIn, DiFloat rBIn,
                                          DiFloat &rAOut, DiFloat &rBOut);


  static DiUInt16  ConvertPriorToWeight(DiFloat  rPriority);
  static DiFloat   ConvertWeightToPrior(DiUInt16 nWeight);

  //static DiFloat   GetSpecialVParAsFlagOfFLTransaction() { return DIANGR_SYNCH_NODES_IN_FLTRANS_F; }
  
private:
  DiVoid        SetPrevPar(DiFloat const rPrevPar) {this->rPrevPar = rPrevPar;}
};

// This class is general class for EdgeData in AnimGraph
// It could contain either trans-s or FLtrans-s
class DiAnimMTransaction
{
  // declare friends
  friend class DiAnimGraph;

public:
  DiUInt32             nNumIntervals;  // number of start intervals
  DiUInt32             nProbability;
  DiAnGrClbStorageElem *sepClbStorage; // callbacks
  DiAnimFlTransaction  **atppTransactions; // pointer to an array of pointers to transactions
  
public:
  DiAnimMTransaction() : nNumIntervals(0), sepClbStorage(NULL), atppTransactions(NULL), nProbability(0)
  { }

  DiUInt32          GetTransactionNearestToPar(DiFloat rVPar, DiFloat &deltaVPar);
  DiBool            IsCorrect(); // check integrity
  DiVoid            SetNumIntervals(DiUInt32 nNum) { this->nNumIntervals = nNum; }
  DiVoid            SetClbStorageToNull()          { this->sepClbStorage = NULL; }

  DiAnimFlTransaction *GetSubTransaction(DiUInt32 nSubTransID) 
  { 
    return atppTransactions[nSubTransID]; 
  }
  
  // getting callbacks
  DiAnGrClbStorageElem *GetClbStorage() { return sepClbStorage; }
  DiUInt32             GetNumIntervals() const { return nNumIntervals; }
  DiUInt32             GetProbability() const { return nProbability; }
  DiVoid               SetProbability( DiUInt32 _nProbability);
};

// Special structure to be used in Editor for Pause/Resume interface
struct InOut
{
  float m_in;
  float m_out;
  bool  m_valid;
  int   m_curNodeIdx;

  InOut() : m_in(0.0f), m_out(1.0f), m_valid(false), m_curNodeIdx(0)
  {} 

  InOut(const InOut &_copy) : m_in(_copy.m_in), m_out(_copy.m_out), m_valid(_copy.m_valid), m_curNodeIdx(_copy.m_curNodeIdx)
  {}

  void Clear()
  { 
    m_in          = 0.0f; 
    m_out         = 1.0f;
    m_valid       = false;
    m_curNodeIdx  = 0;
  }
};


#endif // ifndef _DIANGR_INL_
