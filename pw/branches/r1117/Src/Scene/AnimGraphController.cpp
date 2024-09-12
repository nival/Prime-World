// Author: EugBel
// Date:   14/05/2009

#include "stdafx.h"
#include "AnimGraphController.h"

namespace NScene
{

int GetCurrentNodeIdx(AnimGraphController *ctrl)
{
  int nodeIdx(-1), fromIdx(-1), toIdx(-1);
  if ( ctrl->GetRandomNodeSelectType() == RNST_SubNode )
    ctrl->GetActiveEntity(&nodeIdx, &fromIdx, &toIdx, true);
  else
    ctrl->GetActiveEntity(&nodeIdx, &fromIdx, &toIdx);
  if ( nodeIdx == -1 )
    nodeIdx = toIdx;
  if ( ctrl->m_nodesToPlay.size() > 1 )
  {
    DiAnimNode* node = ctrl->m_graph->GetNodeData( nodeIdx );
    if ( node->IsSubNode() )
      nodeIdx = node->GetDispatcherNodeID();
  }

  return nodeIdx;
}

void UnregisterCallbacksForLoopedNode( AnimGraphController *ctrl, int nodeIdx )
{
  DiAnimNode* mainanimnode = ctrl->m_graph->GetNodeData( nodeIdx );
  if ( mainanimnode->IsSwitcher() )
  {
    //Dispatcher - надо сделать unregister всем sub нодам
    class UnRegistrator : public INeiFunctor
    {
      AnimGraphController* ctrl;
    public:
      UnRegistrator( AnimGraphController* ctrl )
        : ctrl( ctrl )
      {}
      UnRegistrator& operator=( const UnRegistrator& ) { return *this; }
      virtual void operator()( DiUInt32 nodeId )
      {
        DiAnimNode* node = ctrl->m_graph->GetNodeData( nodeId );
        if ( node->IsSubNode() )
        {
          ctrl->m_graph->UnregisterCallback(DIANGR_NODE, nodeId, LoopNodeCallbackFunction, ctrl);
        }
      }
    } f( ctrl );
    ctrl->m_graph->ForAllNeighbours( nodeIdx, &f );
  }
  else
  {
    ctrl->m_graph->UnregisterCallback(DIANGR_NODE, nodeIdx, LoopNodeCallbackFunction, ctrl);
  }
}

float CalcRegTime( AnimGraphController *ctrl, float nodeLength )
{
  // Найти место и поставить callback, который сработает через ctrl->loopTime времени в секундах
  // Если нода меньше длинной, чем этот loopTime, то проиграть ноду numLoopCycle раз а потом вызвать callback
  NI_ASSERT( nodeLength != 0.0f, "Bad node length" );
  float regTime = 0.0f;
  if ( ctrl->loopTime <= nodeLength )
  {
    ctrl->numLoopCycle = 0;
    regTime = ctrl->loopTime / nodeLength;
  }
  else
  {
    ctrl->numLoopCycle = (int)(ctrl->loopTime / nodeLength);
    regTime = fmod( ctrl->loopTime, nodeLength ) / nodeLength;
  }
  return regTime;
}

bool PlayDispatcherLoopedNodeTime( AnimGraphController *ctrl, int nodeIdx )
{
  DiAnimNode* animnode = ctrl->m_graph->GetNodeData( ctrl->m_graph->GetNearestNode() );
  NI_ASSERT( animnode->IsSubNode(), "Fail to play subnode in dispatcher" );

  bool isLoopNode = animnode->GetDispatcherNodeID() == animnode->GetDefNextNode();
  if ( isLoopNode )
  {
    float nodeLength = ctrl->m_graph->GetNodeDuration( ctrl->m_graph->GetNearestNode() );
    float regTime = CalcRegTime( ctrl, nodeLength );
    class Registrator : public INeiFunctor
    {
      AnimGraphController* ctrl;
      float regTime;
    public:
      Registrator( AnimGraphController* ctrl, float regTime )
        : ctrl( ctrl ), regTime( regTime )
      {}
      Registrator& operator=( const Registrator& ) { return *this; }
      virtual void operator()( DiUInt32 nodeId )
      {
        DiAnimNode* node = ctrl->m_graph->GetNodeData( nodeId );
        if ( node->IsSubNode() )
        {
          ctrl->m_graph->RegisterCallback(DIANGR_NODE, nodeId, LoopNodeCallbackFunction, DIANGR_CF_EXACT_PARAM, ctrl, regTime);
        }
      }
    } f( ctrl, regTime );
    ctrl->m_graph->ForAllNeighbours( nodeIdx, &f );
    return true;
  }
  return false;
}

bool PlayNormalLoopedNodeTime( AnimGraphController *ctrl, int nodeIdx )
{
  DiAnimNode* animnode = ctrl->m_graph->GetNodeData( nodeIdx );
  bool isLoopNode = animnode->IsLooped();
  if ( isLoopNode )
  {
    float nodeLength = ctrl->m_graph->GetNodeDuration( nodeIdx );
    float regTime = CalcRegTime( ctrl, nodeLength );
    ctrl->m_graph->RegisterCallback(DIANGR_NODE, nodeIdx, LoopNodeCallbackFunction, DIANGR_CF_EXACT_PARAM, ctrl, regTime);
    return true;
  }
  return false;
}

bool PlayLoopedNodeTime( AnimGraphController *ctrl, int nodeIdx )
{
  DiAnimNode* mainanimnode = ctrl->m_graph->GetNodeData( nodeIdx );
  if ( ctrl->loopTime == 0.0f || ctrl->numLoopCycle != -1 )
    return false;
  if ( mainanimnode->IsSwitcher() )
  {
    return PlayDispatcherLoopedNodeTime( ctrl, nodeIdx );
  }

  return PlayNormalLoopedNodeTime( ctrl, nodeIdx );
}

DiInt32 LoopNodeCallbackFunction(const DiAnGrCallbackParams& params)
{
  AnimGraphController *ctrl = (AnimGraphController *)params.vpUserData;
  int nodeIdx = GetCurrentNodeIdx(ctrl);

  ctrl->numLoopCycle--;

  if ( ctrl->numLoopCycle < 0 )
  {
    UnregisterCallbacksForLoopedNode( ctrl, nodeIdx );
    if (ctrl->m_curTargetIdx + 1 < ctrl->m_nodesToPlay.size())
    {
      ctrl->m_curTargetIdx++;
      ctrl->m_graph->SetTargetNode(ctrl->m_nodesToPlay[ctrl->m_curTargetIdx]);
    }
    ctrl->numLoopCycle = -1;
  }

  return DIOBJMSG_CONTINUE;
}

DiInt32 EndNodeCallbackFunction1(const DiAnGrCallbackParams& params)
{
  return EndNodeCallbackFunction(params);
}
DiInt32 EndNodeCallbackFunction(const DiAnGrCallbackParams& params)
{
  AnimGraphController *ctrl = (AnimGraphController *)params.vpUserData;
  int nodeIdx = GetCurrentNodeIdx(ctrl);

  // if this is the last node to play - restart graph
  if (ctrl->m_curTargetIdx == ctrl->m_nodesToPlay.size() - 1 && nodeIdx == ctrl->m_nodesToPlay[ctrl->m_curTargetIdx])
  {
    if ( ctrl->numLoopCycle != -1 )
      return DIOBJMSG_CONTINUE;
    ctrl->m_curTargetIdx = 0;
    NI_VERIFY(ctrl->m_nodesToPlay.size() > 0, "Invalid array of target nodes", return DIOBJMSG_CONTINUE; );
    if ( ctrl->m_nodesToPlay.size() == 1 )
    {
      DiAnimNode* node = ctrl->m_graph->GetNodeData( ctrl->m_graph->GetNearestNode() );
      if ( node->IsSubNode() )
      {
				if ( ctrl->GetRandomNodeSelectType() == RNST_SubNode )
				{
					ctrl->m_graph->Restart(ctrl->m_nodesToPlay[ctrl->m_curTargetIdx], false);
					return DIOBJMSG_STOP; // because Restart() has been called
				}
				if ( node->GetDefNextNode() == node->GetDispatcherNodeID() )
					return DIOBJMSG_CONTINUE;
				else
				{
					ctrl->m_graph->SetTargetNode(ctrl->m_nodesToPlay[ctrl->m_curTargetIdx]);
					return DIOBJMSG_CONTINUE;
				}
      }
    }

    ctrl->m_graph->Restart(ctrl->m_nodesToPlay[ctrl->m_curTargetIdx], false);
    return DIOBJMSG_STOP; // because Restart() has been called
  }

  return DIOBJMSG_CONTINUE;
}

DiInt32 EnterNodeCallbackFunction(const DiAnGrCallbackParams& params)
{
  AnimGraphController *ctrl = (AnimGraphController *)params.vpUserData;
  int nodeIdx = GetCurrentNodeIdx(ctrl);

  if (nodeIdx == ctrl->m_nodesToPlay[ctrl->m_curTargetIdx])
  {
    if ( PlayLoopedNodeTime( ctrl, nodeIdx ) )
    {
      return DIOBJMSG_CONTINUE;
    }
    // set next target node if such exist or do nothing - wait for this node's end
    if (ctrl->m_curTargetIdx + 1 < ctrl->m_nodesToPlay.size() && ctrl->numLoopCycle == -1)
    {
      ctrl->m_curTargetIdx++;
      ctrl->m_graph->SetTargetNode(ctrl->m_nodesToPlay[ctrl->m_curTargetIdx]);
    }
    // else: nothing to do (just wait for this node end - then graph will be restarted)
  }
  // else: nothing to do (graph is moving to target node and current node is a transit node

  return DIOBJMSG_CONTINUE;
}


AnimGraphController::AnimGraphController(DiAnimGraph *graphToControl, const vector<NDb::Animation> &animations)
: m_graph(graphToControl)
, m_animations(animations)
, m_curTargetIdx(-1)
, isSavedTransactionParams(false)
, loopTime(0.0f)
, numLoopCycle(-1)
{
  // register callbacks to have functionality PlayNodes()
  RegisterPlayNodesCallbacks();

  // call PlayNodes by ourself: to follow common pipeline
  vector<int> playNodes;

  DiUInt32 nodeId = m_graph->GetNearestNode();
  DiAnimNode* node = m_graph->GetNodeData( nodeId );
  if ( node->IsSubNode() )
  {
    nodeId = node->GetDispatcherNodeID();
  }

  playNodes.push_back( nodeId );
  PlayNodes(playNodes, 0.0f);
}

AnimGraphController::~AnimGraphController()
{
  UnregisterPlayNodesCallbacks();
}
  
void AnimGraphController::RegisterPlayNodesCallbacks()
{
  NI_VERIFY(m_graph != NULL, "Invalid graph!", return; );

  for(UINT i = 0; i < m_graph->GetNumNodes(); i++)
  {
    DiBool ok(TRUE);
    // Don't register Dispatcher Node
    DiAnimNode* node = m_graph->GetNodeData( i );
    if ( !node->IsSwitcher() )
    {
      ok = ok && m_graph->RegisterCallback(DIANGR_NODE, i, EnterNodeCallbackFunction, DIANGR_CF_EXACT_PARAM, this, m_graph->GetNodeData(i)->GetStartPar());
      ok = ok && m_graph->RegisterCallback(DIANGR_NODE, i, EndNodeCallbackFunction, DIANGR_CF_ELEMENT_LEAVE, this);
      ok = ok && m_graph->RegisterCallback(DIANGR_NODE, i, EndNodeCallbackFunction1, DIANGR_CF_EXACT_PARAM, this, m_graph->GetNodeData(i)->GetStopPar());
    }
    NI_ASSERT(ok, "Callbacks regestering failed!");
  }
}

void AnimGraphController::UnregisterPlayNodesCallbacks()
{
  NI_VERIFY(m_graph != NULL, "Invalid graph!", return; );

  for(UINT i = 0; i < m_graph->GetNumNodes(); i++)
  {
    DiBool ok(TRUE);
    DiAnimNode* node = m_graph->GetNodeData( i );
    if ( !node->IsSwitcher() )
    {
      ok = ok && m_graph->UnregisterCallback(DIANGR_NODE, i, EnterNodeCallbackFunction, this);
      ok = ok && m_graph->UnregisterCallback(DIANGR_NODE, i, EndNodeCallbackFunction, this);
      ok = ok && m_graph->UnregisterCallback(DIANGR_NODE, i, EndNodeCallbackFunction1, this); // it's not a copy-paste bug!
    }
    NI_ASSERT(ok, "Callbacks unregestering failed!");
  }
}

void AnimGraphController::SetNodeInfo( int nodeIdx, const NDb::AnGrMacronode& nodeInfo )
{
  NI_VERIFY(nodeIdx < int(m_graph->GetNumNodes()), "Wrong index!", return; );

  DiAnimNode *node = m_graph->GetNodeData(nodeIdx);
  NI_VERIFY(node != NULL, "Node not found", return; );

  strcpy_s(m_graph->GetRuntimeNamesTable()[nodeIdx].cpNodeName, nodeInfo.nodeName.c_str());
  node->SetDefNextNode(m_graph->GetNodeIDByNameSlowQuite(nodeInfo.nextNode.c_str()));
  node->SetSurfSpeed(DiVec2(nodeInfo.surfSpeedX, nodeInfo.surfSpeedY));
  node->SetStartPar(DIANGR_DEFAULT_NODE_START_PAR);
  node->SetStopPar(DIANGR_DEFAULT_NODE_STOP_PAR);

  // 1. sequences changes not supported!
  // 2. transactions changes are not supported!
  // 3. positions changes not supported!
  // 4. markers changes not supported (all the more they are not needed in editor)
}

void AnimGraphController::SetSequenceInfo( int nodeIdx, int seqIdx, const NDb::AnGrFormula& startPar, 
                                          const NDb::AnGrFormula& stopPar, const NDb::AnGrFormula& speed, 
                                          const nstl::string& name )
{
  NI_VERIFY(nodeIdx < int(m_graph->GetNumNodes()), "Wrong index!", return; );

  DiAnimNode *node = m_graph->GetNodeData(nodeIdx);
  NI_VERIFY(node != NULL, "Node not found", return; );

  DiAnGrSequence *seq(NULL);
  if (node->IsMacronode())
  {
    DiAnimMacronode *macronode = (DiAnimMacronode *)node;
    NI_VERIFY(seqIdx < macronode->GetNumIntNodes(), "macronodes error", return; );

    seq = &macronode->spSequences[seqIdx];
  }
  else
  {
    NI_VERIFY(0 == seqIdx, "sequences error", return; );

    seq = &node->spSequences[0];
  }

  seq->nID       = GetSeqIDByNameSlow(name);
  seq->rStartPar = startPar.value;
  seq->rStopPar  = stopPar.value;
  seq->rSpeed    = speed.value;
  seq->rWeight   = 1.0f;
}

void AnimGraphController::SetFlMultiTransactionsInfo( int fromNodeIdx, int toNodeIdx, const NDb::AnGrFlMultiTransaction& transactionInfo )
{
  DiUInt32 edgeID = m_graph->GetEdgeID(fromNodeIdx, toNodeIdx);
  DiAnimMTransaction *mtrans = m_graph->GetTransactionData(edgeID);
  NI_VERIFY(mtrans != NULL, "Invalid edge data!", return; );

  if (strcmp(m_graph->GetNodeNameByID(toNodeIdx), transactionInfo.targetNode.c_str()) != 0)
    return; // do not support such changes!

  m_graph->SetEdgeWeight(edgeID, DiAnimFlTransaction::ConvertPriorToWeight(1.0f));

  // transactions changes not supported!
}


void AnimGraphController::SetFlTransactionsInfo( int fromNodeIdx, int toNodeIdx, int partIdx, const NDb::AnGrFlTransaction& partInfo )
{
  DiUInt32 edgeID = m_graph->GetEdgeID(fromNodeIdx, toNodeIdx);
  DiAnimMTransaction *mtrans = m_graph->GetTransactionData(edgeID);
  NI_VERIFY(mtrans != NULL, "Invalid edge data!", return; );

  DiAnimFlTransaction *ftrans = m_graph->GetTransactionData(edgeID, partIdx);
  
  ftrans->SetUpdateFlags(partInfo.blending);
  ftrans->SetKind(DiAnimFlTransaction::Kind(int(partInfo.kind)));
  ftrans->SetAddParams(partInfo.parA.value, partInfo.parB.value);
  ftrans->SetParamFromMin(partInfo.fromMin.value);
  ftrans->SetParamFromMax(partInfo.fromMax.value);
  ftrans->SetToParam(partInfo.toParam.value);
}

// перезагрузить AG из базы данных
void AnimGraphController::ReloadAG()
{
  // ask IVN!
  NI_ALWAYS_ASSERT("Now this functionality is not supported!");

  UnregisterPlayNodesCallbacks();

  // reload AG

  RegisterPlayNodesCallbacks();
}

// проиграть node's в указанном порядке
void AnimGraphController::PlayNodes( const vector<int> &nodeIndices, float _loopTime ) 
{
  NI_VERIFY( nodeIndices.size() > 0, "Empty set of nodes!", return; );

  if ( numLoopCycle != -1 )
  {
    int nodeIdx = GetCurrentNodeIdx( this );
    UnregisterCallbacksForLoopedNode( this, nodeIdx );
    numLoopCycle = -1;
  }

  // loopTime только для цепочек нод
  if ( nodeIndices.size() > 1 )
    loopTime = _loopTime;
  else
    loopTime = 0.0f;

  if ( isSavedTransactionParams )
  {
    for ( int i = 0; i < savedInfos.size(); i++ )
      SetTransactionParams( savedInfos[i].nodeFromID, savedInfos[i].nodeToID, savedInfos[i].minStartPar, savedInfos[i].maxStartPar );
    savedInfos.clear();
    isSavedTransactionParams = false;
  }

  // call LeaveNode-callbacks 
  if (m_nodesToPlay.size() != 0)
  {
    NI_VERIFY(0 <= m_curTargetIdx && m_curTargetIdx < m_nodesToPlay.size(), "Wrong node index in NodesToPlay", return; );
    m_graph->ForceLeaveNodeCallbacks(m_nodesToPlay[m_curTargetIdx]);
  }

  m_nodesToPlay = nodeIndices;
  m_curTargetIdx = 0;
  randomNodeSelectType = RNST_Normal;
  if ( m_nodesToPlay.size() == 1 )
  {
    DiAnimNode* node = m_graph->GetNodeData( m_nodesToPlay[0] );
    if ( node )
    {
      if ( node->IsSwitcher() )
      {
        randomNodeSelectType = RNST_Dispatcher;
      }
      else if ( node->IsSubNode() )
      {
        randomNodeSelectType = RNST_SubNode;
      }
    }
  }

  if ( m_nodesToPlay.size() == 1 )
  {
    if ( randomNodeSelectType == RNST_Dispatcher )
    {
      class Saver : public INeiFunctor
      {
        DiAnimGraph* m_graph;
        AnimGraphController* ctrl;
        bool* isSavedTransactionParams;
        nstl::vector<SavedTransactionInfo>& savedInfos;
      public:
        Saver( DiAnimGraph* m_graph, AnimGraphController* ctrl, bool* isSavedTransactionParams, nstl::vector<SavedTransactionInfo>& savedInfos )
        : m_graph(m_graph), ctrl(ctrl), isSavedTransactionParams(isSavedTransactionParams), savedInfos(savedInfos)
        {}
        Saver& operator=( const Saver& ) { return *this; }
        virtual void operator()( DiUInt32 nodeId )
        {
          DiAnimNode* node = m_graph->GetNodeData( nodeId );
          if ( node->IsSubNode() )
          {
            SavedTransactionInfo savedInfo;
            ctrl->GetTransactionParams( nodeId, node->GetDefNextNode(), &savedInfo.minStartPar, &savedInfo.maxStartPar );
            savedInfo.nodeFromID = nodeId;
            savedInfo.nodeToID = node->GetDefNextNode();
            *isSavedTransactionParams = true;
            ctrl->SetTransactionParams( nodeId, node->GetDefNextNode(), 0.99f, 1.0f );
            savedInfos.push_back( savedInfo );
          }
        }
      } s(m_graph, this, &isSavedTransactionParams, savedInfos);
      m_graph->ForAllNeighbours( m_nodesToPlay[0], &s );
    }
    else
    {
      DiAnimNode* node = m_graph->GetNodeData( m_nodesToPlay[0] );
      if ( (DiUInt32)m_nodesToPlay[0] != node->GetDefNextNode() )
      {
        SavedTransactionInfo savedInfo;
        GetTransactionParams( m_nodesToPlay[0], node->GetDefNextNode(), &savedInfo.minStartPar, &savedInfo.maxStartPar );
        savedInfo.nodeFromID = m_nodesToPlay[0];
        savedInfo.nodeToID = node->GetDefNextNode();
        isSavedTransactionParams = true;
        SetTransactionParams( m_nodesToPlay[0], node->GetDefNextNode(), 0.99f, 1.0f );
        savedInfos.push_back( savedInfo );
      }
    }
  }

  m_graph->Restart( m_nodesToPlay[0], true );
}

// установить глобальную скорость проигрывания анимаций
void AnimGraphController::SetGlobalSpeed( float speed ) 
{
  m_graph->SetGraphSpeedCoeff(speed);
}

// установить анимацию из node в "позицию" float. НЕ ЗАБУДЬТЕ ResetVirtualParameter перед следующим вызовом!
void AnimGraphController::SetVirtualParameter( int nodeIdx, float value )
{
  m_graph->SliderPauseAtNodeAtVParEDITORONLY(nodeIdx, value);
}

void AnimGraphController::ResetVirtualParameter() // вернуться к нормальному воспроизведению AG
{
  m_graph->SliderContinueEDITORONLY();
}

// пишет -1, если не в ноде/не в транзакции
void AnimGraphController::GetActiveEntity( int* pNodeIdx, int* pFromNodeIdx, int* pToNodeIdx, bool isGetDispatcher ) const
{
  NI_VERIFY(pNodeIdx != NULL && pFromNodeIdx != NULL && pToNodeIdx != NULL, "invalid ptrs", return ; );

  DiAnimGraphElems  geWhere = m_graph->GetCurElemType();
  DIASSERT(DIANGR_NA != geWhere);

  switch(geWhere)
  {
  case DIANGR_NODE:
  case DIANGR_MACRONODE:
    {
      DiAnimNode* node = m_graph->GetNodeData( m_graph->GetCurNode() );
      if ( node->IsSubNode() && !isGetDispatcher )
      {
        *pNodeIdx = node->GetDispatcherNodeID();
      }
      else
        *pNodeIdx = m_graph->GetCurNode();
      break;
    }

  case DIANGR_FLTRANSACTION: 
    *pFromNodeIdx = m_graph->GetPrevNode();
    *pToNodeIdx   = m_graph->GetNextNode();
    break;

  default: 
    DIASSERT_ALOOF_CODE(m_graph->GetDBFileName());
  }

}

int AnimGraphController::GetSeqIDByNameSlow(const string &name)
{
  for (int i = 0; i < m_animations.size(); i++)
    if (m_animations[i].name == name)
      return i;
  
  NI_ALWAYS_ASSERT("No such sequence!");
  return -1;
}

const char *AnimGraphController::GetSeqNameByID(int ID)
{
  NI_VERIFY(0 <= ID && ID < m_animations.size(), "Invalid index", return NULL; );

  return m_animations[ID].name.c_str();
}

bool AnimGraphController::GetCurNodeSurfSpeed(CVec2 &surfSpeed)
{
  int nodeIdx(-1), fromIdx(-1), toIdx(-1);
  GetActiveEntity(&nodeIdx, &fromIdx, &toIdx, true);

  if (-1 == nodeIdx)
  {
    if ( -1 != toIdx)
    {
      DiAnimNode *node = m_graph->GetNodeData(toIdx);
      surfSpeed = node->GetSurfSpeed();
      surfSpeed *= m_graph->GetGraphSpeedCoeff();
      return true;
    }
    return false;
  }

  DiAnimNode *node = m_graph->GetNodeData(nodeIdx);
  surfSpeed = node->GetSurfSpeed();
  surfSpeed *= m_graph->GetGraphSpeedCoeff();

  return true;
}

void AnimGraphController::SetTransactionParams( uint from, uint to, float min, float max )
{
  DiUInt32 edgeID = m_graph->GetEdgeID( from, to );
  DiAnimFlTransaction *ftrans = m_graph->GetTransactionData(edgeID, 0);
  ftrans->SetParamFromMin(min);
  ftrans->SetParamFromMax(max);
}

void AnimGraphController::GetTransactionParams( uint from, uint to, float* min, float* max )
{
  DiUInt32 edgeID = m_graph->GetEdgeID( from, to );
  DiAnimFlTransaction *ftrans = m_graph->GetTransactionData(edgeID, 0);
  *min = ftrans->GetMinFromPar();
  *max = ftrans->GetMaxFromPar();
}
} // namespace NScene