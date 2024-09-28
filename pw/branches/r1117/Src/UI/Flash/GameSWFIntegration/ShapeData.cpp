#include "TamarinPCH.h"
#include "ShapeData.h"

#include "swf_parse.h"

namespace flash
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ShapeData::Load( SwfStreamReader & swf, TagInfo & tagInfo, bool withStyles, UI16 charcterID )
{
  const bool withAlpha = ( tagInfo.tagType ==  SWFTags::SWFTAGS_DEFINESHAPE4 ) || ( tagInfo.tagType ==  SWFTags::SWFTAGS_DEFINESHAPE3 );
  const bool lineStyle2 = ( tagInfo.tagType ==  SWFTags::SWFTAGS_DEFINESHAPE4 );

  if ( withStyles )
  {
    swf.readFillstyles( fillStyles, withAlpha, charcterID );
    swf.readLinestyles( lineStyles, lineStyle2, withAlpha, charcterID );
  }

  LoadShape( swf, tagInfo, charcterID, withAlpha, lineStyle2 );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ShapeData::LoadShape( SwfStreamReader & swf, TagInfo & tagInfo, UI16 charcterID, bool withAlpha, bool lineStyle2 )
{
  swf.clearBitreader( true );

  int NumFillBits = swf.readUBits(4);
  int NumLineBits = swf.readUBits(4);

  int fillOffset = 0;
  int lineOffset = 0;

  swf.clearBitreader( true );

  while( true )
  {
    SWF_SHAPERECORD shapeRecord;
    swf.readShape( shapeRecord, NumFillBits, NumLineBits, fillOffset, lineOffset, fillStyles, lineStyles, lineStyle2, withAlpha, charcterID );
    shapeRecords.push_back( shapeRecord );

    if ( !shapeRecord.IsFunctional() )
      break;
  }

  swf.clearBitreader( false );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ShapeDefinition::Load( SwfStreamReader & swf, TagInfo & tagInfo, UI16 charcterID )
{
  swf.readRect( shapeBounds );

  if ( tagInfo.tagType ==  SWFTags::SWFTAGS_DEFINESHAPE4 )
  {
    swf.readRect( edgeBounds );

    // skip 5 bits
    swf.clearBitreader( true );
    swf.readUBits(5);

    usesFillWindingRule = swf.readUBits(1);
    usesNonScalingStrokes = swf.readUBits(1);
    usesScalingStrokes = swf.readUBits(1);
  }

  ShapeData::Load( swf, tagInfo, true, charcterID );
}

const nstl::vector<flash::path>& ShapeDefinition::GetPaths() const
{
  if ( !cached )
  {
    NI_ASSERT( paths.empty(), "Paths not empty" );

    float	x = 0, y = 0;
    flash::path	current_path;

    flash::ShapeData::ShapeRecords::const_iterator it = shapeRecords.begin();  
    flash::ShapeData::ShapeRecords::const_iterator last = shapeRecords.end();  

    for ( ; it != last; ++it )
    {
      if ( !it->edgeRecord )
      {
        if ( it->StateMoveTo || it->StateFillStyle0 || it->StateFillStyle1 || it->StateLineStyle || it->StateNewStyles )
        {
          if ( !current_path.is_empty() )
          {
            paths.push_back(current_path);

            if ( it->StateNewStyles )
            {
              paths.push_back( flash::path() );
              paths.back().m_new_shape = true;
            }

            current_path.m_edges.resize(0);
            current_path.m_ax = x;
            current_path.m_ay = y;
          }
        }

        if ( it->StateMoveTo )
        {
          x = (float) it->MoveDeltaX;
          y = (float) it->MoveDeltaY;

          // Set the beginning of the path.
          current_path.m_ax = x;
          current_path.m_ay = y;
        }

        if ( it->StateFillStyle0 )
          current_path.m_fill0 = it->FillStyle0;

        if ( it->StateFillStyle1 )
          current_path.m_fill1 = it->FillStyle1;

        if ( it->StateLineStyle )
          current_path.m_line = it->LineStyle;

        if ( it->StateNewStyles )
        {
          current_path.m_fill0 = 0;
          current_path.m_fill1 = 0;
          current_path.m_line = 0;
        }
      }
      else
      {
        if ( it->StraightFlag )
        {
          current_path.m_edges.push_back(flash::edge(x + it->DeltaX, y + it->DeltaY, x + it->DeltaX, y + it->DeltaY));

          x += it->DeltaX;
          y += it->DeltaY;

          //        DebugTrace("StraightEdge BUILD\n");
        }
        else
        {
          float	cx = x + it->ControlDeltaX;
          float	cy = y + it->ControlDeltaY;
          float	ax = cx + it->AnchorDeltaX;
          float	ay = cy + it->AnchorDeltaY;

          current_path.m_edges.push_back(flash::edge(cx, cy, ax, ay));

          x = ax;
          y = ay;
        }
      }
    }

    if ( !current_path.is_empty() )
    {
      paths.push_back(current_path);
      current_path.m_edges.resize(0);
    }

    cached = true;
  }

  return paths;
}

void ShapeDefinition::LerpPaths( const nstl::vector<flash::path>& paths1, const nstl::vector<flash::path>& paths2, float t )
{
  cached = true;

  NI_ASSERT( paths1.size() == paths2.size(), "Path should have equal length" );

  if ( paths1.size() < 1 )
    return;

  paths.resize( paths1.size() );

  for ( int i = 0; i < paths.size(); ++i )
  {
    flash::path& nextPath = paths[i];

    nextPath.m_fill1 = paths1[i].m_fill1;
    nextPath.m_fill0 = paths1[i].m_fill0;

    nextPath.m_line = paths1[i].m_line;

    nextPath.m_ax = paths1[i].m_ax * (1.f - t) + paths2[i].m_ax * t;
    nextPath.m_ay = paths1[i].m_ay * (1.f - t) + paths2[i].m_ay * t;

    nextPath.m_new_shape = paths1[i].m_new_shape;

    nextPath.m_edges.resize( paths1[i].m_edges.size() );

    for ( int j = 0; j < paths1[i].m_edges.size(); ++j )
    {
      nextPath.m_edges[j].lerp( paths1[i].m_edges[j], paths2[i].m_edges[j], t );
    }
  }
}

} //namespace flash
