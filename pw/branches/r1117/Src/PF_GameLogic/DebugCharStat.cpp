#include "StdAfx.h"
#include "DebugCharStat.h"
#include "../ui/Window.h"
#include "../UI/ImageLabel.h"
#include "PFBaseUnit.h"

namespace
{
  bool g_showAllStats = false;
  REGISTER_DEV_VAR( "show_debug_all_stats", g_showAllStats, STORAGE_NONE );

  bool g_showDebugStats = false;
  REGISTER_DEV_VAR( "show_debug_stats", g_showDebugStats, STORAGE_NONE );
}

namespace NGameX
{

DebugCharStat::DebugCharStat( UI::Window * _window, NDb::Ptr<NDb::DBUIData> _statNames)
: dbStatParams(_statNames)
, styleNormal("TT_Body")
, styleBonus("TT_Bonus")
, stylePenalty("TT_Penalty")
, window(_window)
{
  advancedParams.Init(window);
}

void DebugCharStat::Update()
{
  if (!g_showDebugStats || !IsValid(unit) || !IsValid(window))
  {
    window->Show(false);
    return;
  }

  UpdateAdvancedParams();
  advancedParams.UpdateVisibility();
  window->Show(true);
}

void DebugCharStat::SetUnit( const NWorld::PFBaseUnit * _unit )
{
  unit = _unit;
}



void DebugCharStat::AdvancedParams::Init( UI::Window * _statWindow )
{
  statCount = 0;
  background  = NULL;
  int i = 1;

  if ( !_statWindow )
    return;

  background = UI::GetChildChecked<UI::Window>( _statWindow, "Background", false );

  while ( UI::ImageLabel *pParam = UI::GetChildChecked<UI::ImageLabel>( background , NStr::IntToStr( i++ ).c_str(), false ) )
    statWindows.push_back( TStatType( pParam, UI::GetChildChecked<UI::ImageLabel>( pParam, "Value", false ) ) );

  if ( statWindows.size() > 0 )
    statHeight = statWindows[ 0 ].first->GetSize().y;
}

void DebugCharStat::AdvancedParams::UpdateVisibility(  )
{
  
  bool show = statCount != 0;

  if ( show )
  {
    background->SetSize( -1, statHeight * ( statCount + 1 ), false );

    for ( int i = 0; i != statCount; ++i )
    {
      statWindows[ i ].first->Show( true );
      statWindows[ i ].second->Show( true );
    }

    for ( int i = statCount, endI = statWindows.size(); i != endI; ++i )
    {
      statWindows[ i ].first->Show( false );
      statWindows[ i ].second->Show( false );
    }
  }

  statCount = 0;
}

void DebugCharStat::AdvancedParams::Add( wstring const &name, wstring const &value, string const & valueStyle )
{
  if ( statCount >= statWindows.size() )
    return;

  TStatType &namedValue = statWindows[ statCount ];
  namedValue.first ->SetCaptionTextW( name );
  namedValue.second->SetCaptionStyle( valueStyle.c_str() );
  namedValue.second->SetCaptionTextW( value );

  ++statCount;
}


void DebugCharStat::UpdateAdvancedParams()
{
  if ( unit->HasAtackAbility() )
  {
    NDb::EApplicatorDamageType applDT = unit->GetBaseAttackDamageType();
    if ( applDT == NDb::APPLICATORDAMAGETYPE_NATIVE )
      applDT = unit->GetNativeDamageType();

    wstring attackType;
    if ( applDT == NDb::APPLICATORDAMAGETYPE_MATERIAL )
      attackType = dbStatParams->attackType.phisicalAttackName.GetText();
    else if ( applDT == NDb::APPLICATORDAMAGETYPE_ENERGY )
      attackType = dbStatParams->attackType.energyAttackName.GetText();
    else if ( applDT == NDb::APPLICATORDAMAGETYPE_PURE )
      attackType = dbStatParams->attackType.pureAttackName.GetText();

    advancedParams.Add( dbStatParams->attackType.statName.GetText(), attackType, styleNormal );
  }

  for ( int i = NDb::STAT_LIFE, count = NDb::KnownEnum<NDb::EStat>::SizeOf(); i < count; ++i )
  {
    const NDb::EStat stat = static_cast<NDb::EStat>(i);

    if ( dbStatParams->elements[ i ].visualStyle == NDb::VISUALSTYLE_DONTSHOW)
      continue;

    if ( NWorld::StatValueWithModifiers const* pValue = unit->GetStat(stat) )
    {
      float fValue     = pValue->GetValue();
      float fBaseValue = pValue->GetUnmodifiedValue();

      if (NDb::STAT_LIFEREGENERATIONABSOLUTE == stat)
      {
        NWorld::StatValueWithModifiers const *pPercentValue = unit->GetStat(NDb::STAT_LIFEREGENERATION);
        fValue     += pPercentValue->GetValue() * unit->GetMaxHealth() / 100.f;
        fBaseValue += pPercentValue->GetUnmodifiedValue() * unit->GetMaxHealth() / 100.f;
      }
      if (NDb::STAT_ENERGYREGENERATIONABSOLUTE == stat)
      {
        NWorld::StatValueWithModifiers const *pPercentValue = unit->GetStat(NDb::STAT_ENERGYREGENERATION);
        fValue     += pPercentValue->GetValue() * unit->GetMaxEnergy() / 100.f;
        fBaseValue += pPercentValue->GetUnmodifiedValue() * unit->GetMaxEnergy() / 100.f;
      }

      if((NDb::STAT_CRITICALMULTIPLIER == stat) &&
        (unit->GetStat(NDb::STAT_CRITICALMULTIPLIER)->GetValue() < EPS_VALUE))
        continue;


      if(
        (unit->GetStat(NDb::STAT_ATTACKSPEED)->GetValue() < EPS_VALUE)&&
        ( (NDb::STAT_ATTACKSPEED        == stat) ||
        (NDb::STAT_CRITICALCHANCE     == stat) ||
        (NDb::STAT_CRITICALMULTIPLIER == stat)   )
        )
        continue;


      bool isDefValue = fabs( fValue - dbStatParams->elements[ i ].defValue  ) < EPS_VALUE;

      if (dbStatParams->elements[ i ].visualStyle == NDb::VISUALSTYLE_CHANGED && isDefValue && !g_showAllStats )
        continue;

      string * valueStyle = &styleNormal;

      if ( pValue->HasModifiers() )
      {
        if ( fValue - fBaseValue >= 0 )
          valueStyle = &styleBonus;
        else
          valueStyle = &stylePenalty;
      }

      wstring statName  = IsValid( dbStatParams ) ? dbStatParams->elements[ i ].name.GetText() : NStr::ToUnicode( NDb::EnumToString(stat) ); 

      static wchar_t* formats[5] = {L"%.0f", L"%.1f", L"%.2f", L"%.0f%%", L"%.1f%%"};
      static float scale[5] = {10.0f, 100.0f, 1000.0f, 10.f, 100.f};
      NI_VERIFY(0 <= dbStatParams->elements[i].format && dbStatParams->elements[i].format < 5, "Wrong or unknown format", continue);

      float value = fValue * scale[dbStatParams->elements[i].format];
      value += 0.5f;
      value = floorf(value);
      value /= scale[dbStatParams->elements[i].format];

      wstring val = NStr::StrFmtW( formats[dbStatParams->elements[i].format], value );

      advancedParams.Add( statName, val, *valueStyle );
    }	
  }

}

}