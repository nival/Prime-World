#pragma once

#include "DisplayList.h"

namespace avmplus
{
  class SpriteObject;
  class DisplayObjectObject;
}

namespace flash
{

class SwfStreamReader;
_interface ICharacter;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IDisplayTag : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IDisplayTag, IBaseInterfaceST );

  virtual void CountFrames( int& frameCounter ) = 0;
  virtual void Execute( avmplus::SpriteObject* _spriteObject, int frameID ) = 0;
};

typedef nstl::list<Strong<IDisplayTag>> DisplayTags;
typedef nstl::hash_map<int, DisplayTags> DisplayTagsByFrame;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PlaceObjectTag : public IDisplayTag, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( PlaceObjectTag, IDisplayTag, BaseObjectST );

public:
  PlaceObjectTag();

  virtual void CountFrames( int& frameCounter ) {}
  virtual void Execute( avmplus::SpriteObject* _spriteObject, int frameID );

  void Load( SwfStreamReader & streamReader, TagInfo & tagInfo );

  void InitalizeObject( avmplus::DisplayObjectObject* displayObject, avmplus::SpriteObject* _parentObject );
   
private:

  avmplus::DisplayObjectObject* CreateDisplayObject( int _characterId,  avmplus::SpriteObject* _spriteObject, int frameID );

  void LoadClipActions( SwfStreamReader & streamReader, TagInfo & tagInfo );
  void LoadFilters( SwfStreamReader & streamReader, TagInfo & tagInfo );

  bool PlaceFlagHasClipAction;
  bool PlaceFlagHasClipDepth;
  bool PlaceFlagHasName;
  bool PlaceFlagHasRatio;
  bool PlaceFlagHasColorTransform;
  bool PlaceFlagHasMatrix;
  bool PlaceFlagHasCharacter;
  bool PlaceFlagMove;

  bool PlaceFlagHasImage;
  bool PlaceFlagHasClassName;
  bool PlaceFlagHasCacheAsBit;
  bool PlaceFlagHasBlendMode;
  bool PlaceFlagHasFilterList;

  UI16 Depth;
  UI16 CharacterId;
  SWF_MATRIX Matrix;
  SWF_CXFORMWITHALPHA ColorTransform;
  UI16 Ratio;
  UI16 ClipDepth;
  nstl::string Name;
  nstl::string m_ClassName;
  // SWF_CLIPACTIONS ClipActions; TODO

  bool cacheAsBit;
  int blendMode;

  // Glow filter hack
  bool glowHack;
  SWF_RGBA glowColor;

  int debugFrameId;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RemoveObjectTag : public IDisplayTag, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( RemoveObjectTag, IDisplayTag, BaseObjectST );


public:

  RemoveObjectTag();

  virtual void CountFrames( int& frameCounter ) {}
  virtual void Execute( avmplus::SpriteObject* _spriteObject, int frameID );

  void Load( SwfStreamReader & streamReader, TagInfo & tagInfo );

private:

  bool removeByDepth;
  UI16 CharacterId;
  UI16 Depth;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ShowFrameTag : public IDisplayTag, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( ShowFrameTag, IDisplayTag, BaseObjectST );

public:

  ShowFrameTag() {}

  virtual void CountFrames( int & frameCounter ) { frameCounter++; }
  virtual void Execute( avmplus::SpriteObject* _spriteObject, int frameID ) {}
};

}