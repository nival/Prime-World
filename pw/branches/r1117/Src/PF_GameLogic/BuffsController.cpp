#include "StdAfx.h"
#include "BuffsController.h"

#include "../ui/FlashContainer2.h"

#include "PFApplMod.h"
#include "PFBaseUnit.h"
#include "PFApplUtils.h"
#include "PFAIWorld.h"
#include "PrecompiledTooltips.h"
#include "FlashFSCommands.h"
#include "AdventureTooltip.h"
#include "AdventureFlashInterface.h"

namespace
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class F> 
void ForallRingReverse( NWorld::PFBaseApplicator::AppliedRing const &applicators, F &f )
{
  if ( applicators.empty() )
    return;

  NWorld::PFBaseApplicator const *last = applicators.first();
  for (NWorld::PFBaseApplicator *applicator = applicators.prev( applicators.last() ); applicator != last;)
  {
    NWorld::PFBaseApplicator *applicatorNext = applicators.prev(applicator);
    f(applicator);
    applicator = applicatorNext;
  }
  f(last);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ApplicatorNameMap : public NNameMap::Map
{
  NAMEMAP_DECLARE;
public:
  ApplicatorNameMap( NWorld::PFAbilityData const *pAbility, NWorld::PFBaseUnit  const *pUnit ) :
      ability( pAbility ), unit( pUnit ), owner( pAbility->GetOwner().GetPtr() ) {}
protected:
  NWorld::PFAbilityData const *ability;
  NWorld::PFBaseUnit    const *unit;
  NWorld::PFBaseUnit    const *owner;

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ApplicatorFloatFormulaVariant : public NNameMap::Variant, NonCopyable
{
public:
  explicit ApplicatorFloatFormulaVariant( NWorld::PFBaseUnit const* pFirst_, NWorld::PFBaseUnit const* pSecond_, NWorld::PFBaseApplicator const* pMisc_, ExecutableFloatString const* formula )
    : pFirst(pFirst_), pSecond(pSecond_), pMisc(pMisc_), formula(formula), value(0.0f)
  {
  }

  explicit ApplicatorFloatFormulaVariant( const float& _value )
    : pFirst(0), pSecond(0), pMisc(0), formula(0), value(_value)
  {
  }

  virtual float GetFloat() const
  {
    if ( formula )
      return (*formula)( pFirst, pSecond, pMisc, 0.0f );
    else
      return value;
  }

  virtual NNameMap::VariantType::Enum GetType() const { return NNameMap::VariantType::Float; }
  virtual bool IsReadonly() const                     { return true; }

private:
  NWorld::PFBaseUnit const*       pFirst;
  NWorld::PFBaseUnit const*       pSecond;
  NWorld::PFBaseApplicator const* pMisc;
  ExecutableFloatString const*    formula;
  float                           value;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ApplicatorBoolFormulaVariant : public NNameMap::Variant, NonCopyable
{
public:
  ApplicatorBoolFormulaVariant( NWorld::PFBaseUnit const* pFirst_, NWorld::PFBaseUnit const* pSecond_, NWorld::PFBaseApplicator const* pMisc_, ExecutableBoolString const& formula )
    : pFirst(pFirst_), pSecond(pSecond_), pMisc(pMisc_), formula(formula)
  {
  }

  virtual bool GetBool() const
  {
    return formula( pFirst, pSecond, pMisc, 0.0f );
  }

  virtual NNameMap::VariantType::Enum GetType() const { return NNameMap::VariantType::Bool; }
  virtual bool IsReadonly() const                     { return true; }

private:
  NWorld::PFBaseUnit const*       pFirst;
  NWorld::PFBaseUnit const*       pSecond;
  NWorld::PFBaseApplicator const* pMisc;
  ExecutableBoolString const&    formula;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct StatusApplicatorNameMap : public ApplicatorNameMap
{
  NAMEMAP_DECLARE;
public:
  StatusApplicatorNameMap( NWorld::PFAbilityData const *pAbility, NWorld::PFBaseUnit  const *pUnit, NWorld::PFApplStatus const *pAppl, vector<NWorld::PFApplStatMod const*> const& statModsContainer )
    : ApplicatorNameMap( pAbility, pUnit )
    , pApplicator( pAppl )
    , constResolver( ability, unit, owner, pApplicator, statModsContainer ) 
    , conditionsResolver( ability, unit, owner, pApplicator ) 
    {}

protected:
  struct ConstantsResolver : NNameMap::Map, public NonCopyable
  {
    NAMEMAP_DECLARE;
  public:
    ConstantsResolver( NWorld::PFAbilityData const* pAbility, NWorld::PFBaseUnit const* pUnit, NWorld::PFBaseUnit const* pOwner, NWorld::PFBaseApplicator const* pApplicator, vector<NWorld::PFApplStatMod const*> const& _statModsContainer ) :
        pAbility(pAbility), pUnit(pUnit), pOwner(pOwner), pApplicator(pApplicator), statModsContainer(_statModsContainer) {}

     virtual NNameMap::Variant * ResolveVariant( const char * name, int length, const char * args, int argsLength, void* prms, bool readonly )
     {
       vector<NWorld::PFApplStatMod const*>::const_iterator it = statModsContainer.begin();
       vector<NWorld::PFApplStatMod const*>::const_iterator itEnd = statModsContainer.end();

       // find StatMod with statModName matching const name and get const
       for (; it != itEnd; ++it)
       {
         if ( (*it)->IsEnabled() && strcmp( name, (*it)->GetStatModName().c_str() ) == 0 )
         {
           float statModConstant = 0.0f;
           if ( (*it)->GetStatModConstant( statModConstant ) )
              return new ApplicatorFloatFormulaVariant( statModConstant );

           NDb::UnitConstant const* pConst = (*it)->GetConstant( name );
           if (NULL == pConst)
             return NULL;

           return new ApplicatorFloatFormulaVariant( (*it)->GetAbilityOwner(), pUnit, (*it), &pConst->var );
         }
       }

       NDb::UnitConstant const* pConst = pApplicator->GetConstant(name);
       if (NULL == pConst)
         return NULL;

       return new ApplicatorFloatFormulaVariant( pOwner, pUnit, pApplicator, &pConst->var );
     }
  private:
    NWorld::PFAbilityData const*    pAbility;
    NWorld::PFBaseUnit const*       pUnit;
    NWorld::PFBaseUnit const*       pOwner;
    NWorld::PFBaseApplicator const* pApplicator;
    vector<NWorld::PFApplStatMod const*> const& statModsContainer;
  };

  struct ConditionsResolver : NNameMap::Map, public NonCopyable
  {
    NAMEMAP_DECLARE;
  public:
    ConditionsResolver( NWorld::PFAbilityData const* pAbility, NWorld::PFBaseUnit const* pUnit, NWorld::PFBaseUnit const* pOwner, NWorld::PFBaseApplicator const* pApplicator ) :
        pAbility(pAbility), pUnit(pUnit), pOwner(pOwner), pApplicator(pApplicator) {}

    virtual NNameMap::Variant * ResolveVariant( const char * name, int length, const char * args, int argsLength, void* prms, bool readonly )
    {
      NI_VERIFY( IsValid(pOwner), "ConditionsResolver : ability owner is invalid!", return NULL; );

      for ( vector<NDb::Ptr<NDb::ConditionFormula>>::const_iterator iCond = pAbility->GetDBDesc()->conditionFormulas.begin(), iEnd = pAbility->GetDBDesc()->conditionFormulas.end(); iCond != iEnd; ++iCond )
        if ( (*iCond)->name == name )
          return new ApplicatorBoolFormulaVariant( pOwner, pUnit, pApplicator, (*iCond)->condition );

      NI_VERIFY( pOwner->GetWorld() && pOwner->GetWorld()->GetAIWorld(), "ConditionsResolver : World is invalid!", return NULL; )
        const NDb::AILogicParameters& aiParams = pOwner->GetWorld()->GetAIWorld()->GetAIParameters();

      for ( vector<NDb::Ptr<NDb::ConditionFormula>>::const_iterator iCond = aiParams.conditionFormulas.begin(), iEnd = aiParams.conditionFormulas.end(); iCond != iEnd; ++iCond )
        if ( (*iCond)->name == name )
          return new ApplicatorBoolFormulaVariant( pOwner, pUnit, pApplicator, (*iCond)->condition );

      NI_ALWAYS_ASSERT( NStr::StrFmt("Condition '%s' not found in vector 'conditionFormulas' in ability %s nor GameLogic/AILogic.AIPL!", name, pAbility->GetDBDesc()->GetDBID().GetFileName().c_str() ) );

      return NULL;
    }
  private:
    NWorld::PFAbilityData const*    pAbility;
    NWorld::PFBaseUnit const*       pUnit;
    NWorld::PFBaseUnit const*       pOwner;
    NWorld::PFBaseApplicator const* pApplicator;
  };
  NWorld::PFApplStatus const* pApplicator;
  ConstantsResolver           constResolver;
  ConditionsResolver          conditionsResolver;

  nstl::wstring const &GetStatusName() const { return pApplicator->GetDB().name.GetText(); }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct UIMessageApplicatorNameMap : public ApplicatorNameMap
{
  NAMEMAP_DECLARE;
public:
  UIMessageApplicatorNameMap( NWorld::PFAbilityData const *pAbility, NWorld::PFBaseUnit  const *pUnit, float fValue ) :
      ApplicatorNameMap( pAbility, pUnit ), value( fValue ) {}

protected:
  float value;
};




NAMEMAP_BEGIN(ApplicatorNameMap)
  NAMEMAP_CUSTOM_SUBMAP(ability, const_cast<NWorld::PFAbilityData*>(ability), ability);
  NAMEMAP_CUSTOM_SUBMAP(unit, const_cast<NWorld::PFBaseUnit*>(unit), unit);
  NAMEMAP_CUSTOM_SUBMAP(owner, const_cast<NWorld::PFBaseUnit*>(owner), owner);
NAMEMAP_END

NAMEMAP_BEGIN(StatusApplicatorNameMap)
  NAMEMAP_PARENT(ApplicatorNameMap)
  NAMEMAP_FUNC_RO(name, &StatusApplicatorNameMap::GetStatusName );
  NAMEMAP_CUSTOM_SUBMAP(const, &constResolver, &constResolver)
  NAMEMAP_CUSTOM_SUBMAP(if, &conditionsResolver, &conditionsResolver)
NAMEMAP_END

NAMEMAP_BEGIN(UIMessageApplicatorNameMap)
  NAMEMAP_PARENT(ApplicatorNameMap)
  NAMEMAP_VAR_RO(value);
NAMEMAP_END



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NAMEMAP_BEGIN(StatusApplicatorNameMap::ConstantsResolver)
NAMEMAP_END;

NAMEMAP_BEGIN(StatusApplicatorNameMap::ConditionsResolver)
NAMEMAP_END;


}


//////////////////////////////////////////////////////////////////////////
namespace NGameX
{

BuffsController::Status::Status( NWorld::PFApplStatus const *applicator_ ) 
  : applicator(applicator_), maxDurationApplicator(applicator_), count(1)
{
  // fill container with all StatMods
  applicator_->GetChildrenStatMods( statModsContainer );
}

BuffsController::BuffsController( UI::FlashContainer2* flashContainer, UI::ImageLabel * tooltipWnd, AdventureFlashInterface * _flashInterface, BuffsOwner::EBuffsOwner _buffsOwner )
: flashInterface(_flashInterface)
, lastBuffsCount(0)
, buffsOwner(_buffsOwner)
, ttIndex(-1)
{
  using namespace FlashFSCommands;

  flashContainer->AddFSListner(ConvertToString(buffsOwner == BuffsOwner::OurHero ? OurBuffTooltip: SelectionBuffTooltip), this);

  buffStatuses.resize(22);
  statuses.reserve(22);

  tooltip = new AdventureTooltip(tooltipWnd);
}

BuffsController::BuffStatus::BuffStatus()
: cooldown(0)
, count(0)
, isPositive(false)
, applicator(0)
{}

void BuffsController::SetUnit( const NWorld::PFBaseUnit * _unit)
{
  unit = _unit;

  for (int i = 0; i< lastBuffsCount; i++)
  {
    buffStatuses[i].applicator = 0;
    flashInterface->SetBuffIcon(buffsOwner==BuffsOwner::Selection, "", i, false);
  }
}

void BuffsController::Update( int mouseX, int mouseY )
{
  if (!IsValid(unit) || !IsValid(flashInterface))
    return;

  statuses.clear();
  
  ForallRingReverse( unit->GetAppliedApplicatorsRing(), *this );

  ApplyStatuses();

  if (tooltip->IsVisible())
  {
    tooltip->SetLocation(mouseX , mouseY);
  }
}

void BuffsController::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW  )
{
  int show, index;
  sscanf_s(args,"%d %d",&show, &index);

  if (index>=buffStatuses.size() || index<0)
    return;

  if (show)
  {
    tooltip->SetText(buffStatuses[index].tooltip);
    tooltip->Show(true);
    ttIndex = index;
  }
  else 
  {
    tooltip->Show(false);
    ttIndex = -1;
  }
}

void BuffsController::operator()( NWorld::PFBaseApplicator const* applicator )
{
  if ( applicator->GetTypeId() != NWorld::PFApplStatus::typeId ) // proceed only statuses
    return;

  NWorld::PFAbilityInstance const *pAbility = applicator->GetAbility();

  const NDb::Texture * dbImage = applicator->GetStatusImage();

  if ( !pAbility || !dbImage || !applicator->IsEnabled() )
    return;

  NWorld::PFApplStatus const *statusAppl = static_cast<NWorld::PFApplStatus const*>(applicator);

  // find same statuses
  for ( int i = 0, count = statuses.size(); i < count; ++i )
  {
    Status& status = statuses[i];
    if ( status.applicator->GetDBBase()->GetDBID() == statusAppl->GetDBBase()->GetDBID() ) // same status
    {
      if ( statusAppl->GetDB().stackableAcrossUnits != NDb::STACKINGRULE_FULLYSTACKABLE
        || status.applicator->GetAbilityOwner() == statusAppl->GetAbilityOwner() 
        || statusAppl->GetDB().flags & NDb::STATUSFLAGS_SHOWSINGLE )
      {
        if ( statusAppl->GetDB().stackCount + 1 > status.count ) // support new status logic
          ++status.count;

        // find the longest duration
        if ( status.maxDurationApplicator->GetDuration() < statusAppl->GetDuration() )
          status.maxDurationApplicator = statusAppl;

        // fill container with active StatMods
        statusAppl->GetChildrenStatMods( status.statModsContainer );

        return;
      }
    }
    else if ( NWorld::IsApplicatorInList(statusAppl->GetDBBase(), status.applicator->GetDB().unstackableWith) // unstackable status
           || NWorld::IsApplicatorInList(status.applicator->GetDBBase(), statusAppl->GetDB().unstackableWith) )
    {
      // find the longest duration
      if ( status.maxDurationApplicator->GetDuration() < statusAppl->GetDuration() )
        status.maxDurationApplicator = statusAppl;

      // fill container with active StatMods
      statusAppl->GetChildrenStatMods( status.statModsContainer );

      // find the most powerful status
      if ( statusAppl->GetDB().power > status.applicator->GetDB().power )
      {
        status.applicator = statusAppl;
        status.count = 1;
      }

      return;
    }
  }

  statuses.push_back( Status( statusAppl ) );
}

void BuffsController::ApplyStatuses()
{
  struct CompareStatuses
  {
    CompareStatuses( BuffsController* _buffsController ) : buffsController( _buffsController ) {}
    bool operator()( const Status& first, const Status& second )
    {
      const NWorld::PFApplStatus* appl1 = first.applicator;
      const NWorld::PFApplStatus* appl2 = second.applicator;
      const bool isFirstPositive  = buffsController->IsPositiveBuff( appl1 );
      const bool isSecondPositive = buffsController->IsPositiveBuff( appl2 );

      if ( isFirstPositive != isSecondPositive )
      {
        return isFirstPositive;
      }

      return appl1->GetDB().statusPosition < appl2->GetDB().statusPosition;
    }
    BuffsController* buffsController;
  }compareStatuses( this );

  // status order must be preserved, so using merge sort
  merge_sort( statuses.begin(), statuses.end(), compareStatuses );

  const int statusesCount = statuses.size();

  if ( buffStatuses.size() < statusesCount )
  {
    buffStatuses.resize( statusesCount );
  }

  for ( int i = 0; i < statusesCount; ++i )
  {
    FillBuffStatus( i, buffStatuses[i], &statuses[i] );
  }

  if ( lastBuffsCount > statusesCount )
  {
    for ( int i = statusesCount; i < lastBuffsCount; ++i )
    {
      buffStatuses[i].applicator = 0;
      flashInterface->SetBuffIcon( buffsOwner == BuffsOwner::Selection, "", i, buffStatuses[i].isPositive );
    }
  }

  lastBuffsCount = statusesCount;
}

bool BuffsController::IsPositiveBuff( NWorld::PFApplStatus const* applicator )
{
  if (!applicator || !IsValid(unit))
    return false;

  return ( applicator->GetAbilityOwner()->GetFaction() == unit->GetFaction() && (applicator->GetDB().flags & NDb::STATUSFLAGS_ISDEBUFF) == 0 )
      || ( applicator->GetAbilityOwner()->GetFaction() != unit->GetFaction() && (applicator->GetDB().flags & NDb::STATUSFLAGS_ISBUFF) != 0 );
}

void BuffsController::FillBuffStatus(int index, BuffStatus &buff, const Status * status )
{
  NWorld::PFApplStatus const *applicator = status->applicator;

  NWorld::PFAbilityInstance const *ability = applicator->GetAbility();
 
  bool isPositiveBuff = IsPositiveBuff( applicator );

  bool isChangedBuffImage = !buff.applicator || buff.applicator != applicator;

  bool needToUpdateBuff = isChangedBuffImage || buff.isPositive != isPositiveBuff || buff.statModsContainer != status->statModsContainer;

  if ( ttIndex == index || needToUpdateBuff )
  {
    NWorld::PFAbilityData const *pAbilityData = ability->GetData();

    wstring const & desc = applicator->GetDB().description.GetText();
    if (desc.length() > 0)
    {
      StatusApplicatorNameMap myMap(pAbilityData, unit, applicator, status->statModsContainer );
      NGameX::PrecompiledTooltip tooltip;

      tooltip.Init(&myMap, desc);

      tooltip.MakeText(buff.tooltip);
    }
    else
    {
      buff.tooltip = applicator->GetDB().name.GetText();
    }

    // update tooltip content if it is shown
    if ( ttIndex >= 0 )
    {
      tooltip->SetText(buff.tooltip);
    }
  }

  if ( needToUpdateBuff )
  {
    buff.applicator = applicator;
    buff.isPositive = isPositiveBuff;
    buff.image = applicator->GetStatusImage()->textureFileName;
    buff.statModsContainer = status->statModsContainer;
   
    flashInterface->SetBuffIcon(buffsOwner==BuffsOwner::Selection, buff.image.c_str(), index, buff.isPositive);
  }
  
  NWorld::PFApplStatus const *maxDurationApplicator = status->maxDurationApplicator;

  int count = status->count;
  float prog = 1.0f;

  float customProgress = applicator->RetrieveParam( applicator->GetDB().customProgress, -1.0f );
  if ( customProgress < 0.0f )
  {
    const float lt = maxDurationApplicator->GetLifetime();
    const float d = maxDurationApplicator->GetDuration();
    if ( lt > 1e-3f && d >= 0 )
      prog = d / lt;
  }
  else
  {
    prog = customProgress;
  }

  float cooldown = 1.0f - prog;

  int customCounter = applicator->RetrieveParam( applicator->GetDB().customCounter );
  count = customCounter < 1 ? count : customCounter;

  if (isChangedBuffImage || count!=buff.count || buff.cooldown!= cooldown)
  {
    buff.count = count;
    buff.cooldown = cooldown;
    
    flashInterface->SetBuffStatus(buffsOwner==BuffsOwner::Selection, index, buff.cooldown, buff.count);
  }
}

}