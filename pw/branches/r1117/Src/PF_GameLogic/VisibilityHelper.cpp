#include "stdafx.h"
#include "VisibilityHelper.h"

namespace NGameX
{

void VisibilityHelper::SetVisibility( NScene::SceneObject* so, bool bVisible_ )
{
  if (bVisible == bVisible_)
    return;

  bVisible = bVisible_;
  if ( so && ( !bVisible || !so->getVoxelGrid() ) )
  {
    so->EnableRender(bVisible);
  }
}

void VisibilityHelper::InitVisibility(NScene::SceneObject* so)
{
  if ( so && !bVisible )
  {
    so->EnableRender(false);
  }
}

}