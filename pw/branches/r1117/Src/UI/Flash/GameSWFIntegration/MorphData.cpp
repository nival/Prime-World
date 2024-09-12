#include "TamarinPCH.h"

#include "MorphData.h"

#include "swf_parse.h"

namespace flash
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MorphData::Load( SwfStreamReader & swf, TagInfo & tagInfo, UI16 _characterID )
{
  characterID = _characterID;

  swf.readRect( startShape.shapeBounds );
  swf.readRect( endShape.shapeBounds );

  if ( tagInfo.tagType ==  SWFTags::SWFTAGS_DEFINEMORPHSHAPE2 )
  {
    swf.readRect( startShape.edgeBounds );
    swf.readRect( endShape.edgeBounds );

    // skip 6 bits
    swf.clearBitreader( true );
    swf.readUBits(6);

    startShape.usesNonScalingStrokes = swf.readUBits(1);
    startShape.usesScalingStrokes = swf.readUBits(1);
  }
  
  UI32 offset = swf.readUI32();
  offset;

  const bool lineStyle2 = ( tagInfo.tagType ==  SWFTags::SWFTAGS_DEFINEMORPHSHAPE2 );

  swf.readMorphFillstyles( startShape.fillStyles, endShape.fillStyles, characterID );
  swf.readMorphLinestyles( startShape.lineStyles, endShape.lineStyles, lineStyle2, characterID );

  startShape.LoadShape( swf, tagInfo, characterID, true, lineStyle2 );
  endShape.LoadShape( swf, tagInfo, characterID, true, lineStyle2 );

  {
    ShapeData::ShapeRecords endShapeCorrected;

    ShapeData::ShapeRecords::iterator it1 = startShape.shapeRecords.begin();
    ShapeData::ShapeRecords::iterator last1 = startShape.shapeRecords.end();
    ShapeData::ShapeRecords::iterator it2 = endShape.shapeRecords.begin();

    for ( ; it1 != last1; ++it1 )
    {
      SWF_SHAPERECORD& record = endShapeCorrected.push_back();

      if ( !it1->edgeRecord && it2->edgeRecord )
      {
        record = *it1;

        if ( it1->StateMoveTo )
        {
          record.StateMoveTo = false;
          record.MoveDeltaX = 0.f;
          record.MoveDeltaY = 0.f;
        }
      }
      else
      {
        NI_ASSERT( it2 != endShape.shapeRecords.end(), "Bad morph shape");

        record = *it2;

        ++it2;
      }
    }

    endShape.shapeRecords = endShapeCorrected;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ShapeDefinition& MorphData::GetShapeAtRatio( UI16 _ratio )
{
  ShapeChache::iterator it = shapeChache.find( _ratio );

  if ( it != shapeChache.end() )
    return it->second;

  ShapeDefinition& _shapeDef = shapeChache[ _ratio ];

  float ratioNormed = float( _ratio ) / 65535.f;

  _shapeDef.shapeBounds.Lerp( startShape.shapeBounds, endShape.shapeBounds, ratioNormed );
  _shapeDef.edgeBounds.Lerp( startShape.edgeBounds, endShape.edgeBounds, ratioNormed );

  _shapeDef.usesFillWindingRule = startShape.usesFillWindingRule;
  _shapeDef.usesNonScalingStrokes = startShape.usesNonScalingStrokes;
  _shapeDef.usesScalingStrokes = startShape.usesScalingStrokes;

  // fill styles
  {
    NI_ASSERT( startShape.fillStyles.size() ==  endShape.fillStyles.size(), "startShape and endShape should have equal size" );

    int numFillstyles = startShape.fillStyles.size();
    _shapeDef.fillStyles.resize( numFillstyles );

    for ( int i = 0; i < numFillstyles; ++i )
    {
      _shapeDef.fillStyles[i].Lerp( startShape.fillStyles[i], endShape.fillStyles[i], ratioNormed );
    }
  }

  // line styles
  {
    NI_ASSERT( startShape.lineStyles.size() ==  endShape.lineStyles.size(), "startShape and endShape should have equal size" );

    int numLineStyles = startShape.lineStyles.size();
    _shapeDef.lineStyles.resize( numLineStyles );

    for ( int i = 0; i < numLineStyles; ++i )
    {
      _shapeDef.lineStyles[i].Lerp( startShape.lineStyles[i], endShape.lineStyles[i], ratioNormed );
    }
  }

  // shape
  _shapeDef.LerpPaths( startShape.GetPaths(), endShape.GetPaths(), ratioNormed );

  return _shapeDef;
}

avmplus::GraphicsObject* MorphData::GetGraphicsAtRatio( UI16 _ratio, flash::FlashMovieAvmCore* _core )
{
  GraphicAtRates::iterator it = graphicAtRates.find( _ratio );    

  if ( it == graphicAtRates.end() )
  {
    avmplus::Atom args[] = {0};

    avmplus::GraphicsClass * graphicsClass = _core->GetClassCache().GetClass<avmplus::GraphicsClass>( EFlashClassID::GraphicsClass );
    avmplus::GraphicsObject * newGraphics = (avmplus::GraphicsObject *)_core->atomToScriptObject(graphicsClass->construct(0, args));

    const flash::ShapeDefinition& shapeDef = GetShapeAtRatio( _ratio );

    newGraphics->SetCharacterID( characterID, _ratio );
    newGraphics->SetShape( shapeDef );
    newGraphics->SetMorphData( this );

    graphicAtRates[ _ratio ] = new GraphicsWrapper( new Graphics(_core->GetGC(), newGraphics) );

    return newGraphics;
  }
  else
  {
    return it->second->Get()->graphicsObject;
  }
}

} //namespace flash

NI_DEFINE_REFCOUNT(flash::MorphData);
NI_DEFINE_REFCOUNT(flash::GraphicsWrapper);
