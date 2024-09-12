#include "stdafx.h"

#include "BaseOvertipsScreenLogic.h"

#include "../UI/Window.h"
#include "../UI/Resolution.h"

#include "../Render/AABB.h"
#include "../Scene/SceneObject.h"
#include "../Scene/Camera.h"

#include "../Render/debugrenderer.h"


namespace UI
{

static bool s_showOvertipsBoxes = false;
REGISTER_DEV_VAR( "overtips_draw_boxes", s_showOvertipsBoxes, STORAGE_NONE );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BaseOvertipsScreenLogic::BaseOvertipsScreenLogic() :
nextId(1)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BaseOvertipsScreenLogic::~BaseOvertipsScreenLogic()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BaseOvertipsScreenLogic::InitOvertips(NScene::IScene * pScene)
{
  scene = pScene;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BaseOvertipsScreenLogic::StepOvertips()
{
  if( !IsValid( scene ) )
    return;

  SHMatrix projViewMtx = scene->GetCamera()->GetProjectiveMatrix() * scene->GetCamera()->GetViewMatrix();

  for(TOvertipsData::iterator it = overtips.begin(); it != overtips.end(); )
  {
    UpdateOvertip(it->first, it->second, projViewMtx, false);

    TOvertipsData::iterator next = it;
    ++next;
    if( it->second.itHadTarget && !IsValid( it->second.target ) )
    {
      CleanupOvertip(it->first, it->second);
      overtips.erase(it);
    }
    it = next;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BaseOvertipsScreenLogic::CreateOvertip( const NDb::UIObjectOvertips * pOvertips, Overtips::ITarget * pTarget )
{
  NI_VERIFY( IsValid( scene ), "Uninitialized overtips manager!", return Overtips::InvalidId );

  int id = nextId++;

  pair<TOvertipsData::iterator, bool> insertionResult = 
    overtips.insert(TOvertipsData::value_type(id, SOvertipData(pOvertips, pTarget)));
  NI_ASSERT(insertionResult.second, "");

  SOvertipData & overtip = insertionResult.first->second;

  //plain overtips
  for(int i = 0; i < pOvertips->plain.size(); ++i)
  {
    const NDb::UIPlainOvertipDesc & plainDesc = pOvertips->plain[i];
    NI_VERIFY(plainDesc.layout, "NULL overtips layout", continue);
    Window * pWnd = UI::CreateUIWindow( plainDesc.layout, 0, this, pBaseWindow, NStr::StrFmt("overtip%i_plain%i", id, i), true );
    overtip.layouts[Overtips::SOvertipId(true, i)] = SOvertipLayout(pWnd, plainDesc.bindPoint);
  }

  //3d overtips
  for(int i = 0; i < pOvertips->threeDimensional.size(); ++i)
  {
    const NDb::UI3DOvertipDesc & threeDDesc = pOvertips->threeDimensional[i];
    NI_VERIFY(threeDDesc.layout, "NULL overtips layout", continue);
    Window * pWnd = UI::CreateUIWindow( threeDDesc.layout, 0, this, pBaseWindow, NStr::StrFmt("overtip%i_3d%i", id, i), true );
    overtip.layouts[Overtips::SOvertipId(false, i)] = SOvertipLayout(pWnd);
  }

  SHMatrix projViewMtx = scene->GetCamera()->GetProjectiveMatrix() * scene->GetCamera()->GetViewMatrix();
  UpdateOvertip(id, overtip, projViewMtx, true);

  return id;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool BaseOvertipsScreenLogic::RemoveOvertip(int id)
{
  TOvertipsData::iterator it = overtips.find(id);
  if(it == overtips.end())
    return false;

  CleanupOvertip(id, it->second);
  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BaseOvertipsScreenLogic::CleanupOvertip(int id, SOvertipData & overtip)
{
  if( IsValid( overtip.target ) )
    overtip.target->OnOvertipRemoval();

  for(TLayouts::iterator wnd = overtip.layouts.begin(); wnd != overtip.layouts.end(); ++wnd)
    if( wnd->second.window )
      wnd->second.window->Close();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UI::Window * BaseOvertipsScreenLogic::GetOvertipWindow(int id, const Overtips::SOvertipId & overtipId)
{
  TOvertipsData::iterator it = overtips.find(id);
  if(it == overtips.end())
    return NULL;

  SOvertipData & overtip = it->second;

  TLayouts::iterator wnd = overtip.layouts.find(overtipId);
  return (wnd == overtip.layouts.end()) ? NULL : wnd->second.window;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool BaseOvertipsScreenLogic::UpdateOvertipWorldPosition(int id, const SHMatrix & matrix)
{
  TOvertipsData::iterator it = overtips.find(id);
  if(it == overtips.end())
    return false;
  it->second.worldMatrix = matrix;
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool BaseOvertipsScreenLogic::UpdateOvertipAabb(int id, const CVec3 & center, const CVec3 & halfsize)
{
  TOvertipsData::iterator it = overtips.find(id);
  if(it == overtips.end())
    return false;
  it->second.aabbCenter = center;
  it->second.aabbHalfsize = halfsize;
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec2 BaseOvertipsScreenLogic::GetBindPointAlign(NDb::EUIOvertipBindPoint point)
{
  switch(point)
  {
    case NDb::UIOVERTIPBINDPOINT_CENTER:        return CVec2(0.5f, 0.5f);
    case NDb::UIOVERTIPBINDPOINT_LEFTTOP:       return CVec2(0.0f, 0.0f);
    case NDb::UIOVERTIPBINDPOINT_CENTERTOP:     return CVec2(0.5f, 0.0f);
    case NDb::UIOVERTIPBINDPOINT_RIGHTTOP:      return CVec2(1.0f, 0.0f);
    case NDb::UIOVERTIPBINDPOINT_LEFTCENTER:    return CVec2(0.0f, 0.5f);
    case NDb::UIOVERTIPBINDPOINT_RIGHTCENTER:   return CVec2(1.0f, 0.5f);
    case NDb::UIOVERTIPBINDPOINT_LEFTBOTTOM:    return CVec2(0.0f, 1.0f);
    case NDb::UIOVERTIPBINDPOINT_CENTERBOTTOM:  return CVec2(0.5f, 1.0f);
    case NDb::UIOVERTIPBINDPOINT_RIGHTBOTTOM:   return CVec2(1.0f, 1.0f);
    case NDb::UIOVERTIPBINDPOINT_NONE:          NI_ALWAYS_ASSERT("Invalid overtip bind point"); break;
  }
  return CVec2(0.0f, 0.0f);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BaseOvertipsScreenLogic::UpdateOvertip(int id, SOvertipData & data, const SHMatrix & projViewMatrix, bool initialSetup)
{
  //visibility callback
  bool visibilityChanged = false;
  if( IsValid( data.target ) )
  {
    bool vis = data.target->IsOvertipVisible();
    if(vis != data.visibility)
    {
      data.visibility = vis;
      visibilityChanged = true;
    }
  }

  for(TLayouts::iterator it = data.layouts.begin(); it != data.layouts.end(); ++it)
  {
    if ( !it->second.window )
      continue;

    Window * pWindow = it->second.window;

    if( data.visibility )
      if( it->first.isPlain )
      {
        if( !UpdatePlainOvertip( id, data, it->first, pWindow, projViewMatrix ) )
          if( data.visibility )
          {
            data.visibility = false;
            visibilityChanged = true;
          }
      }
      else
        Update3DOvertip(id, data, it->first, pWindow);

    if( visibilityChanged )
      pWindow->Show( data.visibility );

    if( data.visibility || initialSetup )
      if( IsValid( data.target ) )
        if( initialSetup )
          data.target->SetupOvertipLayout( pWindow, it->first );
        else
          data.target->UpdateOvertipLayout( pWindow, it->first );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool BaseOvertipsScreenLogic::UpdatePlainOvertip(int id, const SOvertipData & data, const Overtips::SOvertipId & overtipId, Window * pWindow, const SHMatrix & projViewMatrix)
{
  NI_ASSERT(overtipId.isPlain, "");

  const Render::AABB & box = IsValid( data.target ) ?
    data.target->GetOvertipAabb() :
    Render::AABB(data.aabbCenter, data.aabbHalfsize);

  const NDb::UIPlainOvertipDesc & desc = data.pDbOvertips->plain[overtipId.dbIndex];

  if ( desc.useDepth )
    pWindow->SetWorldPosition( SHMatrix( box.center ), CVec2( 1.0f, 1.0f ), CVec2( 1.0f, 1.0f ), desc.depthBias, E3DWindowMode::DepthOnly );

  Rect bounds;
  bool infront = UI::GetWindowPlacement( &bounds, box, projViewMatrix );
  if ( infront )
  {
    CVec2 align = GetBindPointAlign( desc.bindPoint );
    Point wndSize = desc.layout->size;

    Point newPos(0, 0);
    newPos.x = (int)(0.5f + bounds.minx + bounds.Width() * align.x - wndSize.x * (1.0f - align.x));
    newPos.y = (int)(0.5f + bounds.miny + bounds.Height() * align.y - wndSize.y * (1.0f - align.y));
    newPos += desc.offset;
    pWindow->SetLocation( newPos.x, newPos.y );
  }

  if(s_showOvertipsBoxes)
    Render::DebugRenderer::DrawAABB( box, Render::Color(96, 96, 255), false );

  return infront;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BaseOvertipsScreenLogic::Update3DOvertip(int id, const SOvertipData & data, const Overtips::SOvertipId & overtipId, Window * pWindow)
{
  const SHMatrix & worldMtx = IsValid( data.target ) ? data.target->GetOvertipWorldPosition() : data.worldMatrix;

  const NDb::UI3DOvertipDesc & desc = data.pDbOvertips->threeDimensional[overtipId.dbIndex];

  E3DWindowMode::Enum mode3d = E3DWindowMode::Nope;
  switch(desc.mode)
  {
    case NDb::UI3DOVERTIPMODE_WORLD:
      mode3d = E3DWindowMode::World;
      break;
    case NDb::UI3DOVERTIPMODE_BILLBOARD:
      mode3d = E3DWindowMode::Billboard;
      break;
    case NDb::UI3DOVERTIPMODE_AXISBILLBOARD:
      mode3d = E3DWindowMode::AxisBillboard;
      break;
  }
  NI_ASSERT(mode3d != E3DWindowMode::Nope, "Invalid window 3d mode");

  pWindow->SetWorldPosition(worldMtx, desc.worldSize, desc.align, desc.depthBias, mode3d);
}


} //namespace UI

NI_DEFINE_REFCOUNT( UI::BaseOvertipsScreenLogic );
BASIC_REGISTER_CLASS(Overtips::ITarget);
NI_DEFINE_REFCOUNT( Overtips::IManager );
