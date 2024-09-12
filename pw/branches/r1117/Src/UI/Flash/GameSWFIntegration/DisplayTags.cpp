#include "TamarinPCH.h"

#include "DisplayTags.h"
#include "FlashMovie.h"

#include "Natives/display/DisplayObject.h"
#include "Natives/display/Sprite.h"
#include "Natives/display/Stage.h"

#include "swf_parse.h"

#include "System/InlineProfiler.h"

namespace flash {

PlaceObjectTag::PlaceObjectTag() :
  PlaceFlagHasClipAction(false),
  PlaceFlagHasClipDepth(false),
  PlaceFlagHasName(false),
  PlaceFlagHasRatio(false),
  PlaceFlagHasColorTransform(false),
  PlaceFlagHasMatrix(false),
  PlaceFlagHasCharacter(false),
  PlaceFlagMove(false),
  PlaceFlagHasImage(false),
  PlaceFlagHasClassName(false),
  PlaceFlagHasCacheAsBit(false),
  PlaceFlagHasBlendMode(false),
  PlaceFlagHasFilterList(false),
  cacheAsBit(false),
  blendMode(1),
  glowHack(false),
  debugFrameId(-1)
{

}

void PlaceObjectTag::Execute( avmplus::SpriteObject* _spriteObject, int frameID )
{
  NI_PROFILE_FUNCTION

  debugFrameId = frameID;

  avmplus::DisplayObjectObject* displayObject = _spriteObject->GetDisplayObjectAtDepth( Depth );

  bool newObject = false;

  if ( PlaceFlagMove == 0 && PlaceFlagHasCharacter == 1 )
  {
    if ( !displayObject )
      displayObject = CreateDisplayObject( CharacterId, _spriteObject, frameID );

    newObject = true;

    if ( displayObject )
      _spriteObject->SetDisplayObjectAtDepth( Depth, displayObject );
  }
  else if ( PlaceFlagMove == 1 && PlaceFlagHasCharacter == 0 )
  {
    NI_ASSERT( displayObject != 0, "Wrong order in Display List" );
  }
  else if ( PlaceFlagMove == 1 && PlaceFlagHasCharacter == 1 )
  {
    NI_ASSERT( displayObject != 0, "Wrong order in Display List" );

    displayObject = CreateDisplayObject( CharacterId, _spriteObject, frameID );
    newObject = true;

    if ( displayObject )
    {
      avmplus::DisplayObjectObject* oldObject = _spriteObject->GetDisplayObjectAtDepth( Depth );

      if ( oldObject )
        displayObject->SetMatrix( oldObject->GetMatrix() );

      _spriteObject->SetDisplayObjectAtDepth( Depth, displayObject );
    }
  }
  else
  {
    NI_ALWAYS_ASSERT( "Wrong flags in Display List" );
  }

  if ( !newObject )
    InitalizeObject( displayObject, _spriteObject );
}

void PlaceObjectTag::InitalizeObject( avmplus::DisplayObjectObject* displayObject, avmplus::SpriteObject* _parentObject )
{
  NI_PROFILE_FUNCTION

  if ( displayObject )
  {
    displayObject->SetDepth( Depth );

    if ( PlaceFlagHasClipDepth )
      displayObject->SetClippingDepth( ClipDepth );

    if ( PlaceFlagHasMatrix )
      displayObject->SetMatrix( Matrix );

    if ( PlaceFlagHasColorTransform )
      displayObject->SetColorTransform( ColorTransform );

    if ( PlaceFlagHasRatio )
      displayObject->SetRatio( Ratio );

    if ( PlaceFlagHasName )
    {
      avmplus::Stringp charcterName = displayObject->core()->internConstantStringLatin1( Name.c_str() );
      displayObject->set_name( charcterName );
      _parentObject->SetPropertyByName( charcterName, displayObject->atom() );
    }

    if ( PlaceFlagHasBlendMode )
      displayObject->GetBlendMode()->SetValue( EFlashBlendMode::Enum( blendMode ) );

    if ( glowHack )
      displayObject->SetGlowHack( true, glowColor );
  }
}

avmplus::DisplayObjectObject* PlaceObjectTag::CreateDisplayObject( int _characterId,  avmplus::SpriteObject* _spriteObject, int frameID )
{
  FlashMovieAvmCore* flashCore = (FlashMovieAvmCore*) _spriteObject->core();
  avmplus::DisplayObjectObject* displayObject = flashCore->GetMovie()->CreateObjectByCharacter( _characterId, this, _spriteObject );
  displayObject->SetCreationFrame( frameID );
  return displayObject;
}

void PlaceObjectTag::Load( SwfStreamReader & streamReader, TagInfo & tagInfo )
{
  streamReader.clearBitreader( true );

  if ( tagInfo.tagType == SWFTags::SWFTAGS_PLACEOBJECT2 || 
       tagInfo.tagType == SWFTags::SWFTAGS_PLACEOBJECT3 )
  {
    PlaceFlagHasClipAction = streamReader.readUBits(1);
    PlaceFlagHasClipDepth = streamReader.readUBits(1);
    PlaceFlagHasName = streamReader.readUBits(1);
    PlaceFlagHasRatio = streamReader.readUBits(1);
    PlaceFlagHasColorTransform = streamReader.readUBits(1);
    PlaceFlagHasMatrix = streamReader.readUBits(1);
    PlaceFlagHasCharacter = streamReader.readUBits(1);
    PlaceFlagMove = streamReader.readUBits(1);

    if ( tagInfo.tagType == SWFTags::SWFTAGS_PLACEOBJECT3 )
    {
      streamReader.readUBits(3); // Reserved

      PlaceFlagHasImage = streamReader.readUBits(1);
      PlaceFlagHasClassName = streamReader.readUBits(1);
      PlaceFlagHasCacheAsBit = streamReader.readUBits(1);
      PlaceFlagHasBlendMode = streamReader.readUBits(1);
      PlaceFlagHasFilterList = streamReader.readUBits(1);
    }

    Depth = streamReader.readUI16();

    if ( PlaceFlagHasClassName ) // || ( PlaceFlagHasImage && PlaceFlagHasCharacter) )
    {
      streamReader.readString( m_ClassName );
      NI_ALWAYS_ASSERT("Not yet implemented");
    }

    if ( PlaceFlagHasCharacter )
      CharacterId = streamReader.readUI16();

    if ( PlaceFlagHasMatrix )
      streamReader.readMatrix( Matrix );

    if ( PlaceFlagHasColorTransform )
      streamReader.readCXForm( ColorTransform );

    if ( PlaceFlagHasRatio )
      Ratio = streamReader.readUI16();

    if ( PlaceFlagHasName )
    {
      streamReader.readString( Name );
      //DebugTrace(" -------------------------------> PLACE NAME: %s ( %d )", Name.c_str(), CharacterId );
    }

    if ( PlaceFlagHasClipDepth )
      ClipDepth = streamReader.readUI16();

    if ( PlaceFlagHasFilterList )
      LoadFilters( streamReader, tagInfo );

    if ( PlaceFlagHasBlendMode )
    {
      blendMode = streamReader.readUI8();

      if ( blendMode == 0 )
        blendMode = 1; // 0 & 1 are both NORMAL blending mode
    }

    if ( PlaceFlagHasCacheAsBit )
      cacheAsBit = (streamReader.readUI8() != 0);

    if ( PlaceFlagHasClipAction )
      LoadClipActions( streamReader, tagInfo );
  }
  else if ( tagInfo.tagType == SWFTags::SWFTAGS_PLACEOBJECT )
  {
    int pos1 = streamReader.GetPos();

    CharacterId = streamReader.readUI16();
    Depth = streamReader.readUI16();
    streamReader.readMatrix( Matrix );

    int pos2 = streamReader.GetPos();

    if ( pos2 - pos1 < tagInfo.tagLen )
    {
      streamReader.readCXForm( ColorTransform );
      PlaceFlagHasColorTransform = 1;
    }

    PlaceFlagMove = 0; 
    PlaceFlagHasCharacter = 1;
    PlaceFlagHasMatrix = 1;
    PlaceFlagHasClipDepth = 1;
  }
  else
  {
    NI_ALWAYS_ASSERT("Wrong tag type");
  }

  streamReader.clearBitreader( false );
}

void PlaceObjectTag::LoadClipActions( SwfStreamReader & streamReader, TagInfo & tagInfo )
{
  UI16 Reserved = streamReader.readUI16();
  UI32 AllEventFlags = streamReader.readUI32();

  Reserved;
  AllEventFlags;

  while ( 1 )
  {
    UI32 EventFlags = streamReader.readUI32();

    if ( EventFlags == 0 )
      break;

    UI32 ActionRecordSize = streamReader.readUI32();

    // TODO implement
    streamReader.ignore( ActionRecordSize );
  }
}

void PlaceObjectTag::LoadFilters( SwfStreamReader & streamReader, TagInfo & tagInfo )
{
  // TODO implement
  int filters = streamReader.readUI8();

  for ( int i = 0; i < filters; i++ )
  {
    int filter_id = streamReader.readUI8();

    switch (filter_id)
    {
    case 0 : // DropShadowFilter
      {
        SWF_RGBA drop_shadow_color;
        streamReader.readRGBA( drop_shadow_color, true );
        float blur_x = streamReader.readFixed();	// Horizontal blur amount
        float blur_y = streamReader.readFixed();	// Vertical blur amount
        float angle = streamReader.readFixed();	// Radian angle of the drop shadow
        float distance = streamReader.readFixed();	// Distance of the drop shadow
        float strength = streamReader.readFixed8();	// hack, must be FIXED8 Strength of the drop shadow
        bool inner_shadow = streamReader.readSingleBit();	// Inner shadow mode
        bool knockout = streamReader.readSingleBit();	// Knockout mode
        bool composite_source = streamReader.readSingleBit();	// Composite source Always 1
        int passes = streamReader.readUBits(5); // passes

        blur_x;
        blur_y;
        angle;
        distance;
        strength;
        inner_shadow;
        knockout;
        composite_source;
        passes;

        break;
      }

    case 1 : // BlurFilter
      {
        float blur_x = streamReader.readFixed(); // Horizontal blur amount
        float blur_y = streamReader.readFixed(); // Vertical blur amount
        int passes = streamReader.readUBits(5);	// Number of blur passes
        streamReader.readUBits(3);	// Reserved UB[3] Must be 0

        blur_x;
        blur_y;
        passes;

        break;
      }

    case 2 : // GlowFilter
      {
        streamReader.readRGBA( glowColor, true );
        glowHack = true;

        float blur_x = streamReader.readFixed();	// Horizontal blur amount
        float blur_y = streamReader.readFixed();	// Vertical blur amount
        float strength = streamReader.readFixed8();	// hack, must be FIXED8 Strength of the drop shadow
        bool inner_glow = streamReader.readSingleBit();	// Inner glow mode
        bool knockout = streamReader.readSingleBit();	// Knockout mode
        bool composite_source = streamReader.readSingleBit();	// Composite source Always 1
        streamReader.readUBits(5); // passes

        blur_x;
        blur_y;
        strength;
        inner_glow;
        knockout;
        composite_source;

        break;
      }

    case 3 : // BevelFilter
      {
        SWF_RGBA shadow_color;
        streamReader.readRGBA( shadow_color, true );

        SWF_RGBA highlight_color;
        streamReader.readRGBA( highlight_color, true );

        float blur_x = streamReader.readFixed();	// Horizontal blur amount
        float blur_y = streamReader.readFixed();	// Vertical blur amount
        float angle = streamReader.readFixed();	// Radian angle of the drop shadow
        float distance = streamReader.readFixed();	// Distance of the drop shadow
        float strength = streamReader.readFixed8();	// hack, must be FIXED8 Strength of the drop shadow
        bool inner_shadow = streamReader.readSingleBit();	// Inner shadow mode
        bool knockout = streamReader.readSingleBit();	// Knockout mode
        bool composite_source = streamReader.readSingleBit();	// Composite source Always 1
        bool on_top = streamReader.readSingleBit();	// Composite source Always 1
        int passes = streamReader.readUBits(4); // passes

        blur_x;
        blur_y;
        angle;
        distance;
        strength;
        inner_shadow;
        knockout;
        composite_source;
        on_top;
        passes;

        break;
      }

    case 4 : // GradientGlowFilter
      {
        int num_colors = streamReader.readUI8();		// Number of colors in the gradient

        for (int i = 0; i < num_colors; i++)
        {
          SWF_RGBA gradient_colors;
          streamReader.readRGBA( gradient_colors, true );
        }

        for (int i = 0; i < num_colors; i++)
        {
          int gradient_ratio = streamReader.readUI8();	// UI8[NumColors] Gradient ratios
          gradient_ratio;
        }

        float blur_x = streamReader.readFixed();	// Horizontal blur amount
        float blur_y = streamReader.readFixed();	// Vertical blur amount
        float angle = streamReader.readFixed();	// Radian angle of the drop shadow
        float distance = streamReader.readFixed();	// Distance of the drop shadow
        float strength = streamReader.readFixed8();	// hack, must be FIXED8 Strength of the drop shadow
        bool inner_shadow = streamReader.readSingleBit();	// Inner shadow mode
        bool knockout = streamReader.readSingleBit();	// Knockout mode
        bool composite_source = streamReader.readSingleBit();	// Composite source Always 1
        bool on_top = streamReader.readSingleBit();	// Composite source Always 1
        int passes = streamReader.readUBits(4); // passes

        blur_x;
        blur_y;
        angle;
        distance;
        strength;
        inner_shadow;
        knockout;
        composite_source;
        on_top;
        passes;

        break;
      }

    case 5 : // ConvolutionFilter
      {
        int matrix_x = streamReader.readUI8();	// Horizontal matrix size
        int matrix_y = streamReader.readUI8();	// Vertical matrix size
        float divisor = streamReader.readFloat();	// Divisor applied to the matrix values
        float bias = streamReader.readFloat();	// Bias applied to the matrix values
        for (int k = 0; k < matrix_x * matrix_y; k++)
        {
          streamReader.readFloat();	// Matrix values
        }
        SWF_RGBA default_color;
        streamReader.readRGBA( default_color, true );
        streamReader.readUBits(6);		// Reserved UB[6] Must be 0
        bool clamp = streamReader.readSingleBit();	// UB[1] Clamp mode
        bool preserve_alpha = streamReader.readSingleBit();	// UB[1]

        divisor;
        bias;
        clamp;
        preserve_alpha;

        break;
      }

    case 6 : // ColorMatrixFilter
      // matrix is float[20]
      for (int k = 0; k < 20; k++)
      {
        streamReader.readFloat();
      }
      break;

    case 7 : // GradientBevelFilter
      {
        int num_colors = streamReader.readUI8();		// Number of colors in the gradient

        for (int i = 0; i < num_colors; i++)
        {
          SWF_RGBA gradient_colors;
          streamReader.readRGBA( gradient_colors, true );
        }

        for (int i = 0; i < num_colors; i++)
        {
          int gradient_ratio = streamReader.readUI8();	// UI8[NumColors] Gradient ratios
          gradient_ratio;
        }

        float blur_x = streamReader.readFixed();	// Horizontal blur amount
        float blur_y = streamReader.readFixed();	// Vertical blur amount
        float angle = streamReader.readFixed();	// Radian angle of the drop shadow
        float distance = streamReader.readFixed();	// Distance of the drop shadow
        float strength = streamReader.readFixed8();	// hack, must be FIXED8 Strength of the drop shadow
        bool inner_shadow = streamReader.readSingleBit();	// Inner shadow mode
        bool knockout = streamReader.readSingleBit();	// Knockout mode
        bool composite_source = streamReader.readSingleBit();	// Composite source Always 1
        bool on_top = streamReader.readSingleBit();	// Composite source Always 1
        int passes = streamReader.readUBits(4); // passes
        streamReader.readUI8();// If not present, when parsing several filters, filter type is not correct

        blur_x;
        blur_y;
        angle;
        distance;
        strength;
        inner_shadow;
        knockout;
        composite_source;
        on_top;
        passes;

        break;
      }

    default:
      NI_ALWAYS_ASSERT("Invalid input");
    }
  }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RemoveObjectTag::RemoveObjectTag() : 
  removeByDepth(false)
{

}

void RemoveObjectTag::Execute( avmplus::SpriteObject* _spriteObject, int frameID )
{
  _spriteObject->SetDisplayObjectAtDepth( Depth, 0 );
}

void RemoveObjectTag::Load( SwfStreamReader & streamReader, TagInfo & tagInfo )
{
  if ( tagInfo.tagType == SWFTags::SWFTAGS_REMOVEOBJECT )
  {
    removeByDepth = false;    
    CharacterId = streamReader.readUI16();
    Depth = streamReader.readUI16();
  }
  else // SWFTags::SWFTAGS_REMOVEOBJECT2
  {
    removeByDepth = true;
    Depth = streamReader.readUI16();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

NI_DEFINE_REFCOUNT(flash::IDisplayTag);