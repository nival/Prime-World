#include "stdafx.h"
#include "PFDebug.h"
#include "../Render/debugrenderer.h"

#include "PFApplAura.h"
#include "PFBaseUnit.h"
#include "PFTargetSelector.h"
#include "System/InlineProfiler.h"

#include "../System/InlineProfiler.h"

namespace 
{
  static bool g_selectionOnly = false;
  static bool g_debugLogic = false;

  static NDebug::DebugVar<int> mainPerf_DO_Count( "DO Count", "PerfCnt" );
}

namespace NDebug
{
DebugObject::Ring         DebugObject::objectsRing;
DebugObject::SelectedRing DebugObject::selectRing;
  
//DebugUser::Ring          DebugUser::debugUsers;
//DebugUser::SelectionRing DebugUser::debugSelected;
//DebugUser::Ring          DebugUser::debugRegister;

#ifdef _SHIPPING

/*
DebugUser::DebugUser() {}
DebugUser::~DebugUser() {}
void DebugUser::Update( Render::IDebugRender* ) {}
void DebugUser::DU_Process( float dt, Render::IDebugRender* pRender ) {}
void DebugUser::DU_AddToSelection() const {}
void DebugUser::DU_RemoveFromSelection() const {}
bool DebugUser::DU_IsInSelection() const { return false; )
void DebugUser::DU_ClearSelection() {} 
void DebugUser::DU_ClearAll() {} 
*/

#else

namespace
{
  template <class R, class F> static void ForallRingSafe(R &elements, F &f)
  {
    R processed;
    while (!elements.empty())
    {
      DebugObject *app = elements.first();

      CObj<DebugObject> applObj(app);

      R::remove(app);
      processed.addLast(app);

      f(applObj);
    }

    while (!processed.empty())
    {
      DebugObject *app = processed.first();
      CObj<DebugObject> applObj(app);
      R::remove(app);
      elements.addLast(app);
    }
  }
}

DebugObject::DebugObject()
{ 
  mainPerf_DO_Count.AddValue(1);
  objectsRing.addLast(this); 
}

DebugObject::~DebugObject()
{
  mainPerf_DO_Count.DecValue(1);
}

void DebugObject::DeselectAll()
{
  struct DeselectObjects
  {
    void operator()(const CObj<DebugObject> &obj)
    {
      obj->Deselect();
    }
  } f;
  ForallRingSafe(selectRing, f);
}

void DebugObject::ProcessAll(Render::IDebugRender* pRender)
{
  NI_PROFILE_FUNCTION

  if ( !g_debugLogic )
    return;

  struct ProcessObjects
  {
    ProcessObjects(Render::IDebugRender* pRender) : pRender(pRender) {};

    void operator()(const CObj<DebugObject> &obj)
    {
      if (!obj->IsObjectValid())
      {
        SelectedRing::safeRemove(obj);
        Ring::safeRemove(obj);
        return;
      }
      if (!g_selectionOnly || obj->IsSelected())
        obj->Process(pRender);
    }
    Render::IDebugRender* pRender;
  } f(pRender);

  if( NULL == pRender )
    return;

  pRender->PushBuffer( Render::DRBUFFER_STEP );

  ForallRingSafe(objectsRing, f);

  pRender->PopBuffer();
}

void DebugObject::ClearAll()
{
  struct RemoveFromAllRings
  {
    void operator()(const CObj<DebugObject> &obj)
    {
      SelectedRing::safeRemove(obj);
      Ring::safeRemove(obj);
    }
  } f;
  ForallRingSafe(objectsRing, f);
}

// ----------------------------------------------------------------------------------------
// This class used for Range

class ShowApplAuraRange : public DebugObject
{
  OBJECT_METHODS(0xB757A80, ShowApplAuraRange);
public:
  explicit ShowApplAuraRange(CPtr<NWorld::PFApplAura> const &auraApplicator) : pAuraApplicator(auraApplicator) {}

  virtual bool IsObjectValid() const { return IsValid(pAuraApplicator) && IsValid(pAuraApplicator->GetAbilityOwner()->GetDebugObject()); }
  virtual bool IsSelected() const { return IsObjectValid() && pAuraApplicator->GetAbilityOwner()->GetDebugObject()->IsSelected(); }
  virtual bool Process( Render::IDebugRender* pRender )
  {
    if ( DebugObject::Process(pRender) )
      return true;
    if (IsValid(pAuraApplicator))
    {
      if (pAuraApplicator->IsEnabled())
      {
        float fRange = pAuraApplicator->GetDB().range(pAuraApplicator->GetAbilityOwner(), pAuraApplicator->GetReceiver(), pAuraApplicator, 0.0f);
        CVec3 vPos   = pAuraApplicator->AcquireApplicationPosition();

        NWorld::PFWorld *pWorld = pAuraApplicator->GetAbilityOwner()->GetWorld();

        const NScene::IScene *pScene = pWorld->GetScene();
        const NScene::IHeightsController& heights = pScene->GetHeightsController();

        heights.GetHeight(vPos.x, vPos.y, 1, &vPos.z, NULL);

        pRender->DrawCircle3D(vPos, fRange, 16, Render::Color(0, 0, 255), false);
      }
    }
    return false;
  }
protected:
  ShowApplAuraRange(){}
  CPtr<NWorld::PFApplAura> pAuraApplicator;
};

class ShowAreaTargetSelectorRange : public DebugObject
{
public:
  explicit ShowAreaTargetSelectorRange(CPtr<NWorld::PFBaseUnit> owner, CPtr<NWorld::PFAreaTargetSelector> const &targetSelector, CVec3 const &pos, float range)
    : pUnit(owner)
    , pTarget(targetSelector)
    , vPos(pos)
    , fRange(range)
  {
    const NScene::IScene *pScene = owner->GetWorld()->GetScene();
    const NScene::IHeightsController& heights = pScene->GetHeightsController();

    heights.GetHeight(vPos.x, vPos.y, 1, &vPos.z, NULL);
  }

  virtual bool IsObjectValid() const { return IsValid(pTarget) && IsValid(pUnit) && IsValid(pUnit->GetDebugObject()); }
  virtual bool IsSelected() const { return  IsObjectValid() && pUnit->GetDebugObject()->IsSelected(); }
  virtual bool Process( Render::IDebugRender* pRender )
  {
    if (DebugObject::Process(pRender))
      return true;
    if (IsValid(pTarget))
    {
      pRender->DrawCircle3D(vPos, fRange, 16, Render::Color(96, 192, 192), false);
    }
    return false;
  }
protected:
  ShowAreaTargetSelectorRange(){};
  CPtr<NWorld::PFBaseUnit>           pUnit;
  CPtr<NWorld::PFAreaTargetSelector> pTarget;
  CVec3                              vPos;
  float                              fRange;
};


void ShowAuraApplicatorRange(CPtr<NWorld::PFApplAura> const &pAura)
{
  CObj<ShowApplAuraRange> pObj = new ShowApplAuraRange(pAura);
}

void ShowTargetSelectorRange(CPtr<NWorld::PFBaseUnit> const &pUnit, CPtr<NWorld::PFAreaTargetSelector> const &ts, CVec3 const &pos, float range)
{
  CObj<ShowAreaTargetSelectorRange> pObj = new ShowAreaTargetSelectorRange(pUnit, ts, pos, range);
}


/*
DebugUser::DebugUser()
{
  // we are unable to make dynamic_cast<CObjectBase*>(this) in constructor, so
  // check this in Update later
  debugRegister.addLast(this);
}

DebugUser::~DebugUser()
{
  DebugUser::Ring::safeRemove(this);
  DebugUser::SelectionRing::safeRemove(this);
}

void DebugUser::Update( float dt, Render::IDebugRender* pRender )
{
  if( NULL == pRender )
    return;
  
  pRender->PushBuffer( Render::DRBUFFER_STEP );

  DebugUser * const lastUser = debugRegister.last();
  DebugUser * user = debugRegister.first();
  DebugUser * nextUser = user;
  while (nextUser != lastUser)
  {
    user = nextUser;
    nextUser = Ring::next(user);
    debugRegister.remove( user );
    CObjectBase *pObj = dynamic_cast<CObjectBase*>(user);
    if( !pObj || IsValid(pObj) )
      debugUsers.addLast( user );
  }

  for(ring::Range<DebugUser::Ring> it(debugUsers); it; )
  {
    if (!g_selectionOnly || it->DU_IsInSelection())
    {
      ring::Range<DebugUser::Ring> current = it;
      ++it;
      current->DU_Process( dt, pRender );
    }
  }

  pRender->PopBuffer();
}

void DebugUser::DU_Process( float dt, Render::IDebugRender* pRender )
{
  ProcessTable( pRender, GetCallbackTable() );
}

void DebugUser::ProcessTable( Render::IDebugRender* pRender, DebugTableEntry const* pTable ) const
{
  for( int i = 0 ; pTable && DebugTableEntry::Terminator != pTable[i].type; ++i)
  {
    if( DebugTableEntry::Table == pTable[i].type )
      ProcessTable( pRender, pTable[i].pTable );
    else
    if( DebugTableEntry::Callback == pTable[i].type )
    {
      CallbackDesc const& rCallback = pTable[i].callback;
      if( rCallback.IsValid() && rCallback.pCondition->IsTrue( this ) )
        ( this->*( rCallback.pCallback ) )( pRender );
    }
    else
    {
      NI_ALWAYS_ASSERT("Invalid DebugTableEntry type!");
    }
  }
}

void DebugUser::DU_AddToSelection() const
{
  debugSelected.addLast( const_cast<DebugUser*>(this) );
}

void DebugUser::DU_RemoveFromSelection() const
{
  DebugUser::SelectionRing::safeRemove(const_cast<DebugUser*>(this));
}

bool DebugUser::DU_IsInSelection() const 
{ 
  return dbgUserSelectionRingPart.isLinked(); 
}

void DebugUser::DU_ClearSelection() 
{
  debugSelected.reset();
} 

void DebugUser::DU_ClearAll()
{
  for(ring::Range<DebugUser::Ring> it(debugUsers); it; )
  {
    ring::Range<DebugUser::Ring> current = it;
    ++it;
    delete &(*current);
  }
}
*/

#endif

}

REGISTER_DEV_VAR("debug_logic", g_debugLogic, STORAGE_NONE);
REGISTER_DEV_VAR("debug_process_selected", g_selectionOnly, STORAGE_NONE);