#include "stdafx.h"

#include "FlyTexts.h"
#include "SingleFlyText.h"

#include "Client/ScreenUILogicBase.h"
#include "PrecompiledTooltips.h"
#include "PFBaseUnit.h"


namespace NGameX
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UIFlyTextsLogic : public UI::ClientScreenUILogicBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( UIFlyTextsLogic, UI::ClientScreenUILogicBase );

public:
  UIFlyTextsLogic() : m_counter(0) {}

  UI::Window *CreateFlyOffWindow(char const *layout);
  unsigned int m_counter;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UI::Window *UIFlyTextsLogic::CreateFlyOffWindow(char const *layout)
{
  UI::Window *pWnd = NULL;

  if (pBaseWindow)
  {
    pWnd = pBaseWindow->CreateChild(NStr::StrFmt("%u", m_counter), layout, 0, 0, -1, -1, 0, 0);
    ++m_counter;
  }

  return pWnd;
}









///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UIFlyTexts
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIFlyTexts::UIFlyTexts()
{		
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIFlyTexts::Init( UI::User * uiUser )
{
  pLogic = new UIFlyTextsLogic;
  pLogic->SetUser( uiUser );
  pLogic->LoadScreenLayout( "FlyTexts" );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIFlyTexts::AddFlyText( const NWorld::PFBaseUnit * unit, const NDb::FlyOffText * dbDesc, const NNameMap::Map * nmMap, const SHMatrix & sceneToScreen )
{
  if ( !IsValid( unit ) )
    return;

  if ( dbDesc)
  {
    if ( UI::Window * window = pLogic->CreateFlyOffWindow( dbDesc->layout.c_str() ) )
    {
      if ( nmMap )
      {
        WindowValueManager wvMan;
        wvMan.Init( window );
        wvMan.ResolveVariants( nmMap );
        wvMan.Update();
      }

      pushFlyOff( new FlyText( unit, dbDesc, window ), sceneToScreen );
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIFlyTexts::pushFlyOff( FlyText * pText, const SHMatrix & sceneToScreen )
{
  if ( !pText )
    return;

  // Find Unit
  int unitId;
  for (unitId = 0; unitId < flyTextsArray.size(); ++unitId)
  {
    if ( pText->GetOwner() == flyTextsArray[unitId].unit )
      break;
  }
  // If we haven't such Unit in vector - add new record
  if (unitId == flyTextsArray.size())
  {
    UnitFlyTexts newUnitFlyTexts;
    newUnitFlyTexts.unit = pText->GetOwner();
    newUnitFlyTexts.flyTexts.push_back( pText );
    flyTextsArray.push_back( newUnitFlyTexts );
    // resolve collisions
    Update( 0.0f, sceneToScreen );
    return;
  }

  // Set properly window position right now
//   NScene::ICamera * cam = NGameX::AdventureScreen::Instance()->GetScene()->GetCamera();
//   SHMatrix mtx = cam->GetProjectiveMatrix() * cam->GetViewMatrix();
//   pText->Update(0, mtx);
//   pText->UpdatePosition();

  // Insert new text to vector
  TFlyTexts & curFlyVector = flyTextsArray[unitId].flyTexts; 
  curFlyVector.push_back(pText);
  int vecSize = curFlyVector.size(); 
  NI_ASSERT(vecSize > 1, "It should be at least two texts in vector in this point");

  // Resolve collisions
  Update( 0.0f, sceneToScreen );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIFlyTexts::Update( float deltaTime, const SHMatrix & sceneToScreen )
{
  NI_PROFILE_FUNCTION

  for (int unitId = 0, unitIdCount = flyTextsArray.size(); unitId < unitIdCount; ++unitId)
  {
    TFlyTexts & curFlyVector = flyTextsArray[unitId].flyTexts;

    // 1st step: update projection and opacity
    for (int i = 0, iCount = curFlyVector.size(); i < iCount; ++i)
    {
      curFlyVector[i]->Update( deltaTime, sceneToScreen );
      curFlyVector[i]->UpdatePosition();
    }

    // Collision detection
    // This code evaluating only once, so it may be in UIFlyTexts::pushFlyOff() function,
    // but due to problems with initial window position I move it here. It costs one extra intersect operation per frame.
    int i = curFlyVector.size() - 2;
    if (i >= 0)
    {
      UI::Rect a = curFlyVector[i + 1]->GetRect();
      UI::Rect b = curFlyVector[i]->GetRect();
      UI::Rect intersection = a;
      intersection.Intersect(b);

      if (intersection.IsEmpty() == false)
      {
        int deltaY = (intersection.Height() + 1) / 2;

        // All nonMovable texts should be in the end of vector - so skip them
        int extraY = 0;
        while (i >= 0 && curFlyVector[i]->GetVelocity() == VNULL2)
        {
          extraY += curFlyVector[i]->GetRect().Height();
          nstl::swap( curFlyVector[i], curFlyVector[i + 1] );
          i--;
        }

        // If we really have nonMovable Texts
        if (extraY > 0)
        {
          curFlyVector[i+1]->GetOffset().y -= extraY;
          deltaY = a.Height();
          curFlyVector[i+1]->UpdatePosition();
        }

        // For all other movable texts
        for (; i >= 0 ; --i)
        {
          curFlyVector[i]->GetOffset().y -= deltaY;
          curFlyVector[i]->UpdatePosition();
        }
      }
    }
    
    
    // 3rd step: Remove unused texts
    for (int i = 0, iCount = curFlyVector.size(); i < iCount; ++i)
    {
      if ( !curFlyVector[i]->IsVisible() )
      {
        if ( IsValid( curFlyVector[i]->GetWindow() ) )
          curFlyVector[i]->GetWindow()->Close();
        curFlyVector.eraseByIndex( i );
        i--;
        iCount--;
      }
    }
    if ( curFlyVector.empty() )
    {
      flyTextsArray.eraseByIndex(unitId);
      unitId--;
      unitIdCount--;
    }
  }
  
  // Last step
  pLogic->StepWindows(deltaTime);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIFlyTexts::Render()
{
  pLogic->RenderWindows();
}

} //namespace NGameX
