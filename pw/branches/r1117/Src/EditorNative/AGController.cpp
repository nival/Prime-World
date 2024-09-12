#include "stdafx.h"
#include "AGController.h"

using namespace nstl;
using namespace System;
using namespace libdb::DB;
using namespace EditorNative;
using namespace EditorNative::SceneElements::SceneObjects;

struct ResetCurTimeComponent : public NScene::GenericTraverser, private NonCopyable
{
  void operator()( NScene::SceneComponent *sc )
  {
    NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>( sc );
    if ( asc )
    {
      asc->ResetCurAnimTime();
    }
  }
};

NDb::AnGrFlTransaction ConvertTransaction( DBTypes::AnGrFlTransaction^ partInfo )
{
  NDb::AnGrFlTransaction nativePartInfo;

  nativePartInfo.parA.value = partInfo->parA->value;
  for ( int i = 0; i < partInfo->parA->coeffs->Count; i++ )
  {
    NDb::AnGrExternalParameterCoeff nativeCoeff;
    nativeCoeff.value = partInfo->parA->coeffs[i]->value;
    nativeCoeff.name = ToMBCS( partInfo->parA->coeffs[i]->name );
    nativePartInfo.parA.coeffs.push_back( nativeCoeff );
  }

  nativePartInfo.parB.value = partInfo->parB->value;
  for ( int i = 0; i < partInfo->parB->coeffs->Count; i++ )
  {
    NDb::AnGrExternalParameterCoeff nativeCoeff;
    nativeCoeff.value = partInfo->parB->coeffs[i]->value;
    nativeCoeff.name = ToMBCS( partInfo->parB->coeffs[i]->name );
    nativePartInfo.parB.coeffs.push_back( nativeCoeff );
  }

  nativePartInfo.fromMin.value = partInfo->fromMin->value;
  for ( int i = 0; i < partInfo->fromMin->coeffs->Count; i++ )
  {
    NDb::AnGrExternalParameterCoeff nativeCoeff;
    nativeCoeff.value = partInfo->fromMin->coeffs[i]->value;
    nativeCoeff.name = ToMBCS( partInfo->fromMin->coeffs[i]->name );
    nativePartInfo.fromMin.coeffs.push_back( nativeCoeff );
  }

  nativePartInfo.fromMax.value = partInfo->fromMax->value;
  for ( int i = 0; i < partInfo->fromMax->coeffs->Count; i++ )
  {
    NDb::AnGrExternalParameterCoeff nativeCoeff;
    nativeCoeff.value = partInfo->fromMax->coeffs[i]->value;
    nativeCoeff.name = ToMBCS( partInfo->fromMax->coeffs[i]->name );
    nativePartInfo.fromMax.coeffs.push_back( nativeCoeff );
  }

  nativePartInfo.toParam.value = partInfo->toParam->value;
  for ( int i = 0; i < partInfo->toParam->coeffs->Count; i++ )
  {
    NDb::AnGrExternalParameterCoeff nativeCoeff;
    nativeCoeff.value = partInfo->toParam->coeffs[i]->value;
    nativeCoeff.name = ToMBCS( partInfo->toParam->coeffs[i]->name );
    nativePartInfo.toParam.coeffs.push_back( nativeCoeff );
  }

  nativePartInfo.duration = partInfo->duration;
  nativePartInfo.kind = (NDb::EAnGrTransactionKind)((int)(partInfo->kind));
  nativePartInfo.blending = (NDb::EAnGrTransactionUpdate)((int)(partInfo->blending));

  return nativePartInfo;
}

AGController::AGController( EditorSceneComponent^ _sc, AnimGraphType agType, EditorNative::SimpleEditorScene^ _scene )
{
  scene = _scene;
  esc = _sc;
  Reset( _sc->sceneComponent, agType );
}

AGController::AGController( NScene::AnimatedSceneComponent* _sc, AnimGraphType agType, EditorNative::SimpleEditorScene^ _scene )
{
  scene = _scene;
  Reset( _sc, agType );
}

void AGController::SetNodeInfo( int nodeIdx, DBTypes::AnGrMacronode^ nodeInfo )
{
  if ( agc == 0 ) return;
  NDb::AnGrMacronode nativeNodeInfo;
  nativeNodeInfo.nodeName = ToMBCS( nodeInfo->nodeName );
  nativeNodeInfo.nextNode = ToMBCS( nodeInfo->nextNode );
  nativeNodeInfo.surfSpeedX = nodeInfo->surfSpeedX;
  nativeNodeInfo.surfSpeedY = nodeInfo->surfSpeedY;

	// Temporary disabled (EugBel: 2009-08-26)
  /*
  nativeNodeInfo.startPar.value = nodeInfo->startPar->value;
	for ( int i = 0; i < nodeInfo->startPar->coeffs->Count; i++ )
	{
		NDb::AnGrExternalParameterCoeff nativeCoeff;
		nativeCoeff.value = nodeInfo->startPar->coeffs[i]->value;
		nativeCoeff.name = ToMBCS( nodeInfo->startPar->coeffs[i]->name );
		nativeNodeInfo.startPar.coeffs.push_back( nativeCoeff );
	}

	nativeNodeInfo.stopPar.value = nodeInfo->stopPar->value;
	for ( int i = 0; i < nodeInfo->stopPar->coeffs->Count; i++ )
	{
		NDb::AnGrExternalParameterCoeff nativeCoeff;
		nativeCoeff.value = nodeInfo->stopPar->coeffs[i]->value;
		nativeCoeff.name = ToMBCS( nodeInfo->stopPar->coeffs[i]->name );
		nativeNodeInfo.stopPar.coeffs.push_back( nativeCoeff );
	}
  */

	agc->SetNodeInfo( nodeIdx, nativeNodeInfo );
}

void AGController::SetSequenceInfo( int nodeIdx, int seqIdx, DBTypes::AnGrFormula^ startPar, DBTypes::AnGrFormula^ stopPar, 
                                   DBTypes::AnGrFormula^ speed, String^ name )
{
  if ( agc == 0 ) return;
  NDb::AnGrFormula nativeStartPar;
  NDb::AnGrFormula nativeStopPar;
  NDb::AnGrFormula nativeSpeed;

	nativeStartPar.value = startPar->value;
	for ( int i = 0; i < startPar->coeffs->Count; i++ )
	{
		NDb::AnGrExternalParameterCoeff nativeCoeff;
		nativeCoeff.value = startPar->coeffs[i]->value;
		nativeCoeff.name = ToMBCS( startPar->coeffs[i]->name );
		nativeStartPar.coeffs.push_back( nativeCoeff );
	}

	nativeStopPar.value = stopPar->value;
	for ( int i = 0; i < stopPar->coeffs->Count; i++ )
	{
		NDb::AnGrExternalParameterCoeff nativeCoeff;
		nativeCoeff.value = stopPar->coeffs[i]->value;
		nativeCoeff.name = ToMBCS( stopPar->coeffs[i]->name );
		nativeStopPar.coeffs.push_back( nativeCoeff );
	}

	nativeSpeed.value = speed->value;
	for ( int i = 0; i < speed->coeffs->Count; i++ )
	{
		NDb::AnGrExternalParameterCoeff nativeCoeff;
		nativeCoeff.value = speed->coeffs[i]->value;
		nativeCoeff.name = ToMBCS( speed->coeffs[i]->name );
		nativeSpeed.coeffs.push_back( nativeCoeff );
	}

  nstl::string sequenceName = ToMBCS( name );
  agc->SetSequenceInfo( nodeIdx, seqIdx, nativeStartPar, nativeStopPar, nativeSpeed, sequenceName );
}

void AGController::SetFlMultiTransactionsInfo( int fromNodeIdx, int toNodeIdx, DBTypes::AnGrFlMultiTransaction^ transactionInfo )
{
  if ( agc == 0 ) return;
  NDb::AnGrFlMultiTransaction nativeTransactionInfo;
  nativeTransactionInfo.targetNode = ToMBCS( transactionInfo->targetNode );
  nativeTransactionInfo.probability = transactionInfo->probability;
  nativeTransactionInfo.parameters = ConvertTransaction( transactionInfo->parameters );

  agc->SetFlMultiTransactionsInfo( fromNodeIdx, toNodeIdx, nativeTransactionInfo );
}

void AGController::SetFlTransactionsInfo( int fromNodeIdx, int toNodeIdx, int partIdx, DBTypes::AnGrFlTransaction^ partInfo )
{
  if ( agc == 0 ) return;
  NDb::AnGrFlTransaction nativePartInfo = ConvertTransaction(partInfo);
  agc->SetFlTransactionsInfo( fromNodeIdx, toNodeIdx, partIdx, nativePartInfo );
}

struct SpeedGetter : public INeiFunctor
{
	bool isFind;
	DiAnimNode* animNode;
	DiAnimGraph* pAG;

	SpeedGetter( DiAnimGraph* ag ) : isFind( false ), animNode( 0 ), pAG( ag ) {}
	virtual void operator()( DiUInt32 nodeId )
	{
		if ( isFind )
			return;

		DiAnimNode* node = pAG->GetNodeData( nodeId );
		if ( node->IsSubNode() )
		{
			animNode = node;
			isFind = true;
		}
	}
};

void AGController::PlayNodes( System::Collections::Generic::IList<int>^ nodeIndices, float loopTime )
{
  if ( agc == 0 ) return;
  vector<int> nativeNodeIndices;
  nativeNodeIndices.resize(nodeIndices->Count);
  for ( int i = 0; i < nodeIndices->Count; i++ )
  {
    nativeNodeIndices[i] = nodeIndices[i];
  }
  agc->PlayNodes( nativeNodeIndices, loopTime );
  if ( sc && sc->GetMainAnimGraph() && nativeNodeIndices.size() > 0 && sc->GetMainAnimGraph()->GetNodeData(nativeNodeIndices[0]) )
  {
		DiAnimNode* node = sc->GetMainAnimGraph()->GetNodeData(nativeNodeIndices[0]);

    int animIdx = node->spSequences->nID;
    sc->SetCurAnimIdx(animIdx);
    sc->ResetCurAnimTime();
    float realSpeed = 1.0f/sc->GetAnimDuration(animIdx);
    float nodeSpeed = node->GetSpeed();
		if ( node->IsSwitcher() )
		{
			SpeedGetter* f = new SpeedGetter( sc->GetMainAnimGraph() );
			sc->GetMainAnimGraph()->ForAllNeighbours( nativeNodeIndices[0], f );

			if ( f->isFind )
			{
				nodeSpeed = f->animNode->GetSpeed();
			}
			delete f;
		}

    sc->SetAnimSpeed( nodeSpeed/realSpeed );
  }
  if ( esc != nullptr)
  {
    ResetCurTimeComponent f;
    esc->sceneObject->Object->Traverse(f);
    scene->CalcFrameNumbers( esc->sceneObject );
  }
}

void AGController::SetGlobalSpeed( float speed )
{
  if ( agc == 0 ) return;
  agc->SetGlobalSpeed( speed );
}

void AGController::SetVirtualParameter( int nodeIdx, float value )
{
  if ( agc == 0 ) return;
  agc->SetVirtualParameter( nodeIdx, value );
}

void AGController::ResetVirtualParameter()
{
  if ( agc == 0 ) return;
  agc->ResetVirtualParameter();
}

AGEntity^ AGController::GetActiveEntity()
{
  AGEntity^ entity = gcnew AGEntity();
  if ( agc == 0 ) return entity;
  int pNodeIdx;
  int pFromNodeIdx;
  int pToNodeIdx;

  agc->GetActiveEntity( &pNodeIdx, &pFromNodeIdx, &pToNodeIdx );

  entity->pNodeIdx = pNodeIdx;
  entity->pFromNodeIdx = pFromNodeIdx;
  entity->pToNodeIdx = pToNodeIdx;

  return entity;
}

int AGController::GetCurTargetNode()
{
  if ( agc == 0 ) return 0;
  return agc->GetCurTargetNode();
}

DBTypes::Vec2^ AGController::GetCurNodeSurfSpeed()
{
  DBTypes::Vec2^ surfSpeed = gcnew DBTypes::Vec2(nullptr);
  if ( agc == 0 || !isAGMode) return surfSpeed;
  
  CVec2 res(0.0f,0.0f);
  if ( agc->GetCurNodeSurfSpeed( res ) )
  {
    surfSpeed->x = res.x;
    surfSpeed->y = res.y;
  }
  else
  {
    surfSpeed->x = 0.0f;
    surfSpeed->y = 0.0f;
  }

  return surfSpeed;
}

void AGController::SwitchToAnims()
{
  if ( isAGMode )
  {
    fakeAG = DiAnimGraph::CreateByData( sc->GetDBAnimations(), sc->GetGraphBlender() );
    fakeAG->StoreDefaultValues();
    sc->SetFakeAnimGraphs( fakeAG, 0, 0 );
    isAGMode = false;
  }
}

void AGController::SwitchToAG()
{
  if ( !isAGMode )
  {
    sc->SetFakeAnimGraphs( mainAG, additionalAG, extPars );
    DiAnimGraph::Destroy( fakeAG );
    isAGMode = true;
  }
}


void AGController::Reset( NScene::SceneComponent* _sc, AnimGraphType agType )
{
  delete agc;
  agc = 0;
  NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>( _sc );
  if ( !asc )
  {
    sc = 0;
    agc = 0;
    dbid = libdb::DB::DBID::Empty;
    isValid = false;
    return;
  }

  sc = asc;
  mainAG = sc->GetMainAnimGraph();
  additionalAG = sc->GetAdditionalAnimGraph();
  extPars = sc->GetExtPars();
  isAGMode = true;

  agc = sc->CreateAnimGraphController((int)agType);
  if ( !agc )
  {
    sc = 0;
    agc = 0;
    dbid = libdb::DB::DBID::Empty;
    isValid = false;
    return;
  }

  const NDb::DBID& scDBID = sc->GetDBID();

  libdb::DB::DBPtr<DBTypes::DBAnimatedSceneComponent^>^ dbsc = libdb::DB::DataBase::Get<DBTypes::DBAnimatedSceneComponent^>( libdb::DB::DBID::FromString( FromMBCS( NDb::GetFormattedDbId( scDBID ) ) ) );
  animatedSceneComponentdbid = dbsc->DBId;
  dbid = libdb::DB::DBID::Empty;
	if ( agType == AnimGraphType::Main )
  {
    if ( dbsc->Get() != nullptr )
    {
      dbid = dbsc->Get()->animGraph->DBId;
    }
  }
  else if ( agType == AnimGraphType::Additional )
  {
    if ( dbsc->Get() != nullptr )
    {
      NI_ASSERT(dbsc->Get()->additionalGraph != nullptr, "Empty additional graph in second component!");
      dbid = dbsc->Get()->additionalGraph->DBId;
    }
  }


  isValid = true;

  animInfos = gcnew System::Collections::Generic::List<AnimInfo^>();
  nstl::vector<nstl::string> animations = sc->GetAnimations();
  for ( int i = 0; i < animations.size(); i++ )
  {
    AnimInfo^ animInfo = gcnew AnimInfo();
    animInfo->animName = FromMBCS( animations[i] );
    animInfo->animLength = sc->GetAnimDuration( i );
    animInfo->animFrames = sc->GetAnimDurationInFrames( i );
    animInfos->Add( animInfo );
  }
}