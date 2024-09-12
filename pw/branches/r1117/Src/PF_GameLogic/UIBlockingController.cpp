#include "StdAfx.h"

#include "UI/FlashContainer2.h"

#include "UIBlockingController.h"
#include "AdventureFlashInterface.h"
#include "PFPostFXParams.h"

namespace NGameX
{

UIBlockingController::UIBlockingController() :
  isUIBlocked(false),
  fadeOut(false),
  fadeTime(1.f),
  currentFadeTime(0.f),
  saturationColor(1.f,1.f,1.f,1.f)
{

}

void UIBlockingController::BeginBlockSection()
{
  unblockedItems.clear();

  AddNonBlockedElement( "EscapeMenuBar", false );
  AddNonBlockedElement( "OptionsWindow", false );
  AddNonBlockedElement( "MessageBox", false );
}

void UIBlockingController::AddNonBlockedElement( const char* id, bool bubble )
{
  UnblockDesc& desc = unblockedItems.push_back( UnblockDesc( EUnblockType::Simple, id, bubble ) );
  SetNonBlockedElement( desc, true );
}

void UIBlockingController::AddNonBlockedElementTalentBar( int column, int row, bool bubble )
{
  UnblockDesc& desc = unblockedItems.push_back( UnblockDesc( EUnblockType::TalentBar, column, row, bubble ) );
  SetNonBlockedElement( desc, true );
}

void UIBlockingController::AddNonBlockedElementActionBar( int slot, bool bubble )
{
  UnblockDesc& desc = unblockedItems.push_back( UnblockDesc( EUnblockType::ActionBar, slot, bubble ) );
  SetNonBlockedElement( desc, true );
}

void UIBlockingController::AddNonBlockedElementInventory( int slot, bool bubble )
{
  UnblockDesc& desc = unblockedItems.push_back( UnblockDesc( EUnblockType::Inventory, slot, bubble ) );
  SetNonBlockedElement( desc, true );
}

void UIBlockingController::AddNonBlockedElementShop( int slot, bool bubble )
{
  UnblockDesc& desc = unblockedItems.push_back( UnblockDesc( EUnblockType::Shop, slot, bubble ) );
  SetNonBlockedElement( desc, true );
}


void UIBlockingController::AddNonBlockedElementHero( int playerId, bool bubble )
{
  UnblockDesc& desc = unblockedItems.push_back( UnblockDesc( EUnblockType::Hero, playerId, bubble ) );
  SetNonBlockedElement( desc, true );
}

void UIBlockingController::SetNonBlockedElement( const UnblockDesc& _desc, bool nonBlocked )
{
  if ( adventureFlashInterface )
  {
    avmplus::Atom atom = 0; 
    avmplus::Atom bubbleAtom = 0; 
    
    switch( _desc.type )
    {
    case EUnblockType::Simple :
      atom = adventureFlashInterface->GetNamedDisplayObject( _desc.name.c_str(), false );
      bubbleAtom = _desc.bubble ? adventureFlashInterface->GetNamedDisplayObject( _desc.name.c_str(), true ) : 0;
      break;
    case EUnblockType::TalentBar :
      atom = adventureFlashInterface->GetTalentBarItemDisplayObject( _desc.column, _desc.row, false );
      bubbleAtom = _desc.bubble ? adventureFlashInterface->GetTalentBarItemDisplayObject( _desc.column, _desc.row, true ) : 0;
      break;
    case EUnblockType::ActionBar :
      atom = adventureFlashInterface->GetActionBarItemDisplayObject( _desc.slot, false );
      bubbleAtom = _desc.bubble ? adventureFlashInterface->GetActionBarItemDisplayObject( _desc.slot, true ) : 0;
      break;
    case EUnblockType::Hero :
      atom = adventureFlashInterface->GetHeroDisplayObject( _desc.slot, false );
      bubbleAtom = _desc.bubble ? adventureFlashInterface->GetHeroDisplayObject( _desc.slot, true ) : 0;
      break;
    case EUnblockType::Shop :
      atom = adventureFlashInterface->GetShopItemDisplayObject( _desc.slot, false );
      bubbleAtom = _desc.bubble ? adventureFlashInterface->GetShopItemDisplayObject( _desc.slot, true ) : 0;
      break;
    case EUnblockType::Inventory :
      atom = adventureFlashInterface->GetInventoryItemDisplayObject( _desc.slot, false );
      bubbleAtom = _desc.bubble ? adventureFlashInterface->GetInventoryItemDisplayObject( _desc.slot, true ) : 0;
      break;
    }

    if ( flashContainer )
    {
      if ( atom && !_desc.bubble )
        flashContainer->SetNonBlockedDisplayObject( atom, nonBlocked );

      if ( bubbleAtom && bubbleAtom != atom )
        flashContainer->SetNonBlockedDisplayObject( bubbleAtom, nonBlocked );
    }
  }
}


void UIBlockingController::EndBlockSection( float _fadeTime )
{
  fadeTime = ( _fadeTime > 0.f ? _fadeTime : 1.f );
  currentFadeTime = 0.f;
  isUIBlocked = true;
  fadeOut = false;

  if ( flashContainer )  
    flashContainer->SetUIBlocked( true );
}

void UIBlockingController::ClearBlocking( float _fadeTime )
{
  fadeTime = ( _fadeTime > 0.f ? _fadeTime : 1.f );
  currentFadeTime = 0.f;
  fadeOut = true;
}

void UIBlockingController::Update( float deltaTime )
{
  currentFadeTime += deltaTime;

  if ( flashContainer )  
    flashContainer->SetBlockingFade( GetFadeValue(), saturationColor );

  { // dynamical hierarhy support
    UnblockedItems::iterator it = unblockedItems.begin();
    UnblockedItems::iterator last = unblockedItems.end();

    for ( ; it != last; ++it )
    {
      SetNonBlockedElement( *it, true );
    }
  }

  if ( fadeOut && currentFadeTime > fadeTime )
  {
    if ( flashContainer )  
      flashContainer->SetUIBlocked( false );

    UnblockedItems::iterator it = unblockedItems.begin();
    UnblockedItems::iterator last = unblockedItems.end();

    for ( ; it != last; ++it )
    {
      SetNonBlockedElement( *it, false );
    }

    unblockedItems.clear();

    isUIBlocked = false;
    fadeOut = false;
  }
}

float UIBlockingController::GetFadeValue()
{
  if ( fadeOut )
    return Clamp( currentFadeTime / fadeTime, 0.f, 1.f );
  else
    return Clamp( 1.f - currentFadeTime / fadeTime, 0.f, 1.f );
}

}

NI_DEFINE_REFCOUNT(NGameX::UIBlockingController)
