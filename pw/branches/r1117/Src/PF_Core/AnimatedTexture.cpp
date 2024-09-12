#include "stdafx.h"

#include "../Render/TextureManager.h"
#include "../Render/RenderComponent.h"
#include "../Render/MaterialSpec.h"
#include "../Render/smartrenderer.h"
#include "../Render/renderstates.h"
#include "../Render/renderer.h"
#include "../Render/ImmediateRenderer.h"
#include "../Scene/SceneObjectUtils.h"
#include "AnimatedTexture.h"
#include "../Render/NullRenderSignal.h"

namespace {

  bool NextFileName(string& fileName)
  {
    if (fileName.empty())
      return false;

    // find a sequence of digits
    int i = fileName.length() - 1;
    int const iend = -1;
    while (i != iend && !isdigit(fileName[i]))
      --i;
    int iLast = i;
    while (i != iend && isdigit(fileName[i]))
      --i;
    int iFirst = i;

    // increment it
    for (i = iLast; i != iFirst; --i)
    {
      string::reference ch = fileName[i];
      NI_ASSERT(isdigit(ch), "Digit expected");
      if (isdigit(++ch))
        return true;
      else
        ch = '0';
    }
    return false;
  }

} // anonymous namespace

namespace PF_Core
{

DECLARE_NULL_RENDER_FLAG

IUpdateableTexture::Ring IUpdateableTexture::s_objects;
IUpdateableTexture *IUpdateableTexture::s_pUpdateIterator = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IUpdateableTexture::ProceedUpdate(float renderTime)
{
  if (s_objects.empty())
    return;

  s_pUpdateIterator = s_objects.first();
  IUpdateableTexture *pTerminator = s_objects.last();
  do 
  {
    // Perform update
    s_pUpdateIterator->Update(renderTime);
    // s_pUpdateIterator could have been changed in update
    if (s_pUpdateIterator == pTerminator)
      break;
    // Get to the next
    s_pUpdateIterator = s_pUpdateIterator->part.next;
  } while (s_pUpdateIterator != pTerminator);

  s_pUpdateIterator = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IUpdateableTexture::ForcedClear()
{
  ring::Clear(s_objects);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IUpdateableTexture::Subscribe()
{
  s_objects.addLast(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IUpdateableTexture::Unsubscribe() 
{ 
  if (this == s_pUpdateIterator)
  {
    // Get to the next object
    s_pUpdateIterator = s_pUpdateIterator->part.next;
  }
  Ring::safeRemove(this); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnimatedTexture::AnimatedTexture(const NDb::TextureAnimated &dbTex)
  : Render::Texture2D( NULL, HANDLERPRIORITY_SUPER_LOW ) // we need to handle device lost AFTER cache
  , pDBObj(&dbTex)
  , curFrame(-1)
  , frameOffset(0.0f)
{
  if ( dbTex.textureFileName.empty() || RENDER_DISABLED )
  {
    frames.push_back(Render::GetWhiteTexture2D());
  }
  else
  {
    NI_VERIFY(dbTex.animCount > 0, "Illegal texture count", return );
    string fileName(dbTex.textureFileName);
    bool fileNameOk = true;
    for (int i = 0; i < dbTex.animCount; i++)
    {
      NI_VERIFY(fileNameOk, NStr::StrFmt("Couldn't produce next file name for %s", fileName.c_str()), break );
      Render::Texture2DRef tex = Render::Load2DTextureFromFile( fileName ); // cannot fail, at least default texture is returned
      frames.push_back(tex);
      fileNameOk = NextFileName(fileName);
    }
  }

  NI_ASSERT(!frames.empty(), "I thought at least one frame was added");
  curFrame = 0;
  ResetDXTexture();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatedTexture::ResetDXTexture()
{
  if ( RENDER_DISABLED )
    return;

  if (curFrame != -1)
  {
    NI_ASSERT(curFrame < frames.size(), "index out of bounds");
    SetTexture(*frames[curFrame]);
    NI_ASSERT(desc.Pool == D3DPOOL_MANAGED, "Dynamic animated textures not supported");
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatedTexture::Update(float renderTime)
{
  int frameCount = frames.size();
  if (frameCount < 1)
    return;

  int newFrame = (int)(pDBObj->animSpeed * renderTime) % frameCount;
  if (newFrame != curFrame)
  {
    curFrame = newFrame;
    ResetDXTexture();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Render::TextureRef LoadAnimatedTexture(const NDb::TextureAnimated &tex)
{
  return new Render::DeviceLostWrapper<AnimatedTexture>( tex );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Render::TextureRef LoadAnimatedTextureIntoPool( const NDb::TextureAnimated &tex, bool canBeVisualDegrade, void * texturePoolId )
{
	return LoadAnimatedTexture( tex );
}


}
