#include "stdafx.h"
#include "PFDispatchCursor.h"
#include "TileMap.h"
#include "PFDispatchCursorClient.h"
#include "PFBaseUnit.h"
#include "../Core/WorldCommand.h"
#include "PFHero.h"

namespace NWorld
{

PFDispatchCursor::PFDispatchCursor( CreateParams const &cp )
: Base(cp)
, lastTargetPos( cp.target.AcquirePosition().AsVec2D() )
{
  duration = RetrieveParam( GetDB().lifeTime );
  curPos = cp.source.AcquirePosition().AsVec2D();
  speed = RetrieveParam( GetDB().speed );
  maxSpeed = RetrieveParam( GetDB().maxSpeed );
  m_startTime = GetWorld()->GetTimeElapsed();
}

void PFDispatchCursor::Reset()
{
  //TODO!!!
}

void PFDispatchCursor::OnStart()
{
  UpdatePersistentApplicatorsPosition();
  Base::OnStart();
  lastTargetPos = target.AcquirePosition().AsVec2D();
  originalSenderPos = curPos;
}

void PFDispatchCursor::CreateClientDispatch()
{
  CreateClientObject<TClientObject>( GetWorld()->GetScene() );
}

void PFDispatchCursor::UpdatePersistentApplicatorsPosition()
{
  struct StepFunc : public NonCopyable
  {
    StepFunc(Target const &target): target(target) {}

    void operator()(CObj<PFBaseApplicator> &applicator) { applicator->SetTarget(target); }

    Target const &target;
  };

  // update target (position) for persistent applicators
  Target t(GetCurrentPosition());
  StepFunc sf(t);
  PFBaseApplicator::ForallRing( persistentApplicators, sf );
}

bool PFDispatchCursor::Step(float dtInSeconds)
{
  NI_PROFILE_FUNCTION

    if ( IsObjectDead() )
      return false;

  if (state == STATE_PROCEED)
  {
    bool time2Die = false;
    if (IsUnitValid(pSender))
    {
      if (duration <= 0)
      {
        // if negative lifetime was specified, check if there're any persistent applicators left
        time2Die = persistentApplicators.empty();
      }
      else
      {
        // if positive lifetime was specified, decrease it
        duration -= dtInSeconds;
        time2Die = (duration <= 0);
      }
    }
    else
    {
      time2Die = true; // Sender is dead. We have to die also.
    }

    if (time2Die)
    {
      Apply();
      return true;
    }

    float const linkRange = GetDB().linkRange;
    CVec2 const senderPos = source.AcquirePosition().AsVec2D();
    CVec2 receiverPos = target.AcquirePosition().AsVec2D();

    NI_ASSERT(curPos.IsFinite(), "Bad curpos");

    lastTargetPos = receiverPos;

    CVec2 const delta = receiverPos - curPos;
    float const deltaLength = fabs(delta);

    // calculate new world pos
    if ( deltaLength > EPS_VALUE )
    {
      float const maxMove = dtInSeconds * maxSpeed;

      float desiredMove = maxMove;
      if (deltaLength <= maxMove)
      {
        desiredMove = deltaLength;
      }

      CVec2 newPos = curPos + delta * ( desiredMove / deltaLength );
      NI_ASSERT( newPos.IsFinite(), "Bad curpos" );

      TileMap* pMap = GetWorld()->GetTileMap();
      SVector tile = pMap->GetTile( newPos );
      if ( !pMap->IsPointOutsideMap( tile.x, tile.y ) )
      {
        CVec2 dirFromSender = newPos - senderPos;
        if ( linkRange > EPS_VALUE && fabs2( dirFromSender ) > fabs2( linkRange ) )
        {
          Normalize( &dirFromSender );
          newPos = dirFromSender * linkRange + senderPos;
        }
        curPos = newPos;
      }
    }
    else if ( linkRange > EPS_VALUE && fabs2( curPos - senderPos ) > fabs2( linkRange ) )
    {
      CVec2 dirFromSender = receiverPos - senderPos;
      Normalize( &dirFromSender );
      curPos = dirFromSender * linkRange + senderPos;
    }
    // show logical dispatch pos
    //float terrainHeight;
    //GetWorld()->GetScene()->GetHeightsController().GetHeight( curPos.x, curPos.y, 1, &terrainHeight, NULL );
    //Render::DebugRenderer::DrawPoint3D( CVec3( curPos, terrainHeight) , 0.5, Render::Color( 0xFF ), false );
  }

  UpdatePersistentApplicatorsPosition();
  Base::Step(dtInSeconds);

  if ( IsObjectDead() )
    return false;

  return false;
}

void PFDispatchCursor::UpdateCursorPos( CVec2 pos )
{
  target.SetPosition( CVec3(pos.x,pos.y,0.0f) );
}

DEFINE_2_PARAM_CMD_CHECK( 0x8D85F480, CmdUpdateCursorPos, CPtr<PFDispatchCursor>, pDispatch, CVec2, pos);

NCore::WorldCommand* CreateCmdUpdateCursorPos(PFDispatchCursor *pDispatch, CVec2 pos)
{
  NI_VERIFY(NULL != pDispatch, "Dispatch object should exists", return 0);
  return new CmdUpdateCursorPos( pDispatch, pos );
}

bool CmdUpdateCursorPos::CanExecute() const
{
  if ( IsValid(pDispatch) )
    if ( NWorld::PFBaseHero* hero = dynamic_cast<NWorld::PFBaseHero*>( pDispatch->GetSender().GetPtr() ) )
      if ( const NWorld::PFPlayer * pPlayer = hero->GetPlayer() )
        if ( pPlayer->GetUserID() == GetId() || pPlayer->IsBot() )
          return true;

  return false;
}

void CmdUpdateCursorPos::Execute(NCore::IWorldBase *)
{
  if ( IsValid(pDispatch) )
    pDispatch->UpdateCursorPos(pos);
}

}

REGISTER_SAVELOAD_CLASS_NM( CmdUpdateCursorPos, NWorld )
REGISTER_WORLD_OBJECT_WITH_CLIENT_NM( PFDispatchCursor, NWorld)
