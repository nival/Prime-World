#ifndef SHAPEDATA_H_INCLUDED
#define SHAPEDATA_H_INCLUDED

#include "SwfTypes.h"
#include "Natives/display/MeshSet.h"


namespace SWFParser
{
  struct TagInfo;
};

namespace flash
{

class SwfStreamReader;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ShapeData //i.e. SHAPEWITHSTYLE and/or SHAPE
{
  typedef nstl::list<SWF_SHAPERECORD> ShapeRecords;

  FillStyles    fillStyles;
  LineStyles    lineStyles;

  ShapeRecords  shapeRecords;

  void Load( SwfStreamReader & streamReader, TagInfo & tagInfo, bool withStyles, UI16 charcterID );
  void LoadShape( SwfStreamReader & swf, TagInfo & tagInfo, UI16 charcterID, bool withAlpha, bool lineStyle2 );
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ShapeDefinition : public ShapeData //i.e. DefineShape4 data
{
  SWF_RECT shapeBounds; // [TODO] implement functionality
  SWF_RECT edgeBounds; // [TODO] implement functionality

  bool usesFillWindingRule; // [TODO] implement functionality
  bool usesNonScalingStrokes; // [TODO] implement functionality
  bool usesScalingStrokes; // [TODO] implement functionality

  void Load( SwfStreamReader & streamReader, TagInfo & tagInfo, UI16 charcterID );

  const nstl::vector<flash::path>& GetPaths() const;
  void LerpPaths( const nstl::vector<flash::path>& paths1, const nstl::vector<flash::path>& paths2, float t );

  ShapeDefinition() :
    usesFillWindingRule(false),
    usesNonScalingStrokes(false),
    usesScalingStrokes(false),
    cached(false)
  {}

private:

  mutable nstl::vector<flash::path>	paths;
  mutable bool cached;
};

} //namespace flash

#endif //SHAPEDATA_H_INCLUDED
