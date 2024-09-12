#pragma once

#include "SwfTypes.h"
#include "ShapeData.h"

#include "Natives/display/MorphShape.h"

namespace SWFParser
{
  struct TagInfo;
};

namespace flash
{

class SwfStreamReader;

struct Graphics: public MMgc::GCRoot
{
  Graphics(MMgc::GC * gc, avmplus::GraphicsObject * _graphicsObject): MMgc::GCRoot(gc)
  {
    graphicsObject = _graphicsObject;
  }
  DRC(avmplus::GraphicsObject*) graphicsObject;
};

typedef avmplus::GCRootWrapper<Graphics> GraphicsWrapper;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MorphData : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( MorphData, BaseObjectST );

public:

  void Load( SwfStreamReader & streamReader, TagInfo & tagInfo, UI16 _characterID );

  const ShapeDefinition& GetShapeAtRatio( UI16 _ratio );
  avmplus::GraphicsObject* GetGraphicsAtRatio( UI16 _ratio, flash::FlashMovieAvmCore* _core );

  ShapeDefinition& GetStartShape() { return startShape; } 
  ShapeDefinition& GetEndShape() { return endShape; } 

private:

  ShapeDefinition startShape;
  ShapeDefinition endShape;

  typedef nstl::hash_map<UI16, ShapeDefinition> ShapeChache; 
  ShapeChache shapeChache;

  typedef nstl::hash_map<flash::UI16, Strong<GraphicsWrapper>> GraphicAtRates;
  GraphicAtRates graphicAtRates;

  UI16 characterID;
};

} //namespace flash
