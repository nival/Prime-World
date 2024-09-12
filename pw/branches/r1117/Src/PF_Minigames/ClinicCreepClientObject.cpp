#include "stdafx.h"

#include "ClinicCreepClientObject.h"

#include "Clinic.h"
#include "ClinicCreep.h"
#include "ClinicPlace.h"
#include "../UI/ImageLabel.h"
#include "../UI/ProgressBar.h"

#include "MovingUnitController.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicCreepClientObject::ClinicCreepClientObject() :
visible(true), mouseOver(false)
{
  animNodes[eIdle]            = "idle";
  animNodes[eFriendshipIdle]  = "friendship";
  animNodes[eLazy]            = "sleep";
  animNodes[eUnsatisfied]     = "sad";
  animNodes[eSatisfied]       = "happy";
  animNodes[eUsingTable]      = "table";
  animNodes[eUsingBed]        = "gym";
  animNodes[eUsingWashtab]    = "washtab";
  animNodes[eUsingGamePlace]  = "playground";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicCreepClientObject::~ClinicCreepClientObject()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicCreepClientObject::SetVisible( bool _visible )
{
  visible = _visible;
  MovingUnitClientObject::SetVisible(_visible);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicCreepClientObject::Update(float deltaTime, bool gameOnPause)
{
  MovingUnitClientObject::Update(deltaTime, gameOnPause);

  //update animation
  if(IsValid(clinicCreep))
  {
    ECreepAnimNodes anim = clinicCreep->CheckFriendIsNear() ? eFriendshipIdle : eIdle;

    if(clinicCreep->IsSleeping())
      anim = eLazy;
    else
    {
      float cooldown = 0.0f;
      if(IsValid(clinicCreep->GetClinicPlace()))
        if(clinicCreep->GetClinicPlace()->IsCreepWorking(cooldown))
          switch(clinicCreep->GetClinicPlaceType())
          {
            case NDb::PLACETYPE_TABLE:
              anim = eUsingTable;
              break;
            case NDb::PLACETYPE_BAD:
              anim = eUsingBed;
              break;
            case NDb::PLACETYPE_WASHTAB:
              anim = eUsingWashtab;
              break;
            case NDb::PLACETYPE_GAMEPLACE:
              anim = eUsingGamePlace;
              break;
          }
    }

    //TODO: remove this when Priestess animation will be done
    //systemLog(NLogg::LEVEL_DEBUG).Trace(">>>Creep: Updated anim to %i", anim);
    SetMovingAnimNode(false, anim);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicCreepClientObject::InitClinicCreep( ClinicCreep * creep )
{
  NI_ASSERT( IsValid( clinic ), "" );
  clinicCreep = creep;

  creep->SetClientNotify(this);

  for(int i = 0; i < eLastAnimNode; ++i)
    animNodes[i].nodeId = GetController()->GetAnimNodeId(animNodes[i].nodeName);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicCreepClientObject::SetupOvertipLayout(UI::Window * pWindow, const Overtips::SOvertipId & overtipId)
{
  MovingUnitClientObject::SetupOvertipLayout(pWindow, overtipId);

  CheckControlOut(&wndName,         pWindow, "Name");
  CheckControlOut(&wndProgress,     pWindow, "Progress");
  CheckControlOut(&wndWish,         pWindow, "Wish");
  CheckControlOut(&wndFriendship,   pWindow, "Friendship");

  if(IsValid(wndName) && IsValid(clinicCreep))
    wndName->SetCaptionTextW(clinicCreep->GetName());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicCreepClientObject::UpdateOvertipLayout(UI::Window * pWindow, const Overtips::SOvertipId & overtipId)
{
  MovingUnitClientObject::UpdateOvertipLayout(pWindow, overtipId);

  if(!IsValid(clinicCreep) || !IsValid(clinic))
    return;

  if(IsValid(wndProgress))
  {
    wndProgress->Show(mouseOver);
    wndProgress->SetProgressValue(clinicCreep->GetBarValue());
  }

  if(IsValid(wndName))
    wndName->Show(mouseOver);

  if(IsValid(wndWish))
  {
    NDb::Ptr<NDb::BaseUIMaterial> material = GetWishUIMaterial();

    if ( !IsValid( material ) )
      wndWish->Show(false);
    else
    {
      wndWish->Show(true);
      wndWish->SetBackgroundMaterial( material );

      float waitRatio = 0;
      bool waiting = clinicCreep->IsCreepWaiting(waitRatio);
      CVec4 color = (waiting && waitRatio > 0.7f) ? CVec4(1.0f, 0.0f, 0.0f, 1.0f) : CVec4(1.0f, 1.0f, 1.0f, 1.0f);
      wndWish->SetBackgroundColor( color.r, color.g, color.b, color.a );
    }
  }

  if(IsValid(wndFriendship))
  {
    NDb::Ptr<NDb::BaseUIMaterial> material = GetFriendshipUIMaterial();

    if ( !IsValid( material ) )
    {
      wndFriendship->Show(false);
    }
    else
    {
      wndFriendship->Show(true);
      wndFriendship->SetBackgroundMaterial( material );
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MinigameClientObject * ClinicCreepClientObject::RedirectMouseOver()
{
  return this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicCreepClientObject::OnMouseEnter()
{
  MinigameClientObject::OnMouseEnter();
  mouseOver = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicCreepClientObject::OnMouseLeave()
{
  MinigameClientObject::OnMouseLeave();
  mouseOver = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicCreepClientObject::NeedHighlight() const
{
  return ( EClinicGameMode::Shop != clinic->GetGameMode() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Render::HDRColor& ClinicCreepClientObject::GetHighlightColor() const
{
  return clinic->GetClinicDesc()->preselection.colorPreselect;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::DBMinigame_Clinic & ClinicCreepClientObject::GetClinicDesc() const
{
  return *clinic->GetClinicDesc();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::BaseUIMaterial* ClinicCreepClientObject::GetWishUIMaterial() const
{
  float progress;

  if ( clinicCreep->IsSleeping() )
    return GetClinicDesc().uiStyles.creepStateMaterials[NDb::CREEPSTATE_SLEEPING];
  
  if( clinicCreep->IsCreepWaiting( progress ) )
  {
    ClinicPlace * place = clinicCreep->GetClinicPlace();
    if ( IsValid(place) && clinicCreep->GetCreepWish() != NDb::CREEPWISH_EXIT && clinicCreep->IsInPlaceCreepWants() )
    {
      if ( place->GetSoil() >= 1.f )
        return GetClinicDesc().uiStyles.creepStateMaterials[NDb::CREEPSTATE_NEEDWASH];
    }

    return GetClinicDesc().uiStyles.creepWishMaterials[clinicCreep->GetCreepWish()];
  }

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::BaseUIMaterial* ClinicCreepClientObject::GetFriendshipUIMaterial() const
{
  if ( clinicCreep->GetFriendshipID() >= 0 )
    return GetClinicDesc().uiStyles.creepFriendshipMaterials[clinicCreep->GetFriendshipID() % 5];

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicCreepClientObject::OnClientNotification(const char * eventId)
{
  //TODO: remove this when Priestess animation will be done
  systemLog(NLogg::LEVEL_DEBUG).Trace("Creep notification '%s'", eventId);

  string event(eventId);

  if (event == "creepWishUnsatisfied")
  {
    PlayAnimNode(eUnsatisfied);
  }
  else if (event == "creepWishSatisfied")
  {
    PlayAnimNode(eSatisfied);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicCreepClientObject::SetMovingAnimNode(bool moving, ECreepAnimNodes node)
{
  //TODO: remove this when Priestess animation will be done
  //systemLog(NLogg::LEVEL_DEBUG).Trace(">>>Creep: SetMovingAnim: %s, node = %i", moving ? "moving" : "idle", (int)node);

  NI_ASSERT(node >= 0 && node < eLastAnimNode, "");
  GetController()->SetAnimationName(moving ? EMoveAnimationNode::Move : EMoveAnimationNode::Idle, animNodes[node].nodeId);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicCreepClientObject::PlayAnimNode(ECreepAnimNodes node)
{
  //TODO: remove this when Priestess animation will be done
  //systemLog(NLogg::LEVEL_DEBUG).Trace(">>>Creep: PlayAnim: %i", (int)node);

  NI_ASSERT(node >= 0 && node < eLastAnimNode, "");
  GetController()->PlayAnimNode(animNodes[node].nodeId, EMoveAnimationBlockType::IdleOnly);
}

} // namespace PF_Minigames

BASIC_REGISTER_CLASS(PF_Minigames::ClinicCreepClientObject)
