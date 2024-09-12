#include "TamarinPCH.h"

#include "avmshell.h"
#include "genericzlib.h"
#include "swf_parse.h"

#include "SwfStreamReader.h"
#include "FlashMovieAvmCore.h"

namespace avmshell
{

	/**
	 * isSwf() - return true if the swf magic # is present, ignoring version.
	 */
	bool isSwf(ScriptBuffer swf) {
		if (swf.getSize() < 4)
			return false;
		uint32_t magic = swf[0] | swf[1]<<8 | swf[2]<<16;
		const uint32_t SWF = 'S'<<16 | 'W'<<8 | 'F';
		const uint32_t SWC = 'S'<<16 | 'W'<<8 | 'C';
		return magic == SWF || magic == SWC;
	}
  
	

	/*
	 * Execute a swf as follows:
	 * skip the header
	 * for each DoABC2 tag
	 *   if lazy, parse it but don't run it:  parseActionBlock()
	 * else
	 *   run it via handleActionBlock() just as if it were on the commandline
	 */
}

namespace flash
{
  using namespace avmshell;

  bool SWFParser::ParseSwf( Stream* stream, MMgc::GC * gc, nstl::list<TagInfo> & tagsToFill, SWFInfo & swfInfo, SwfStreamReader & streamReader )
  {
    if ( !stream )
      return false;

    size_t fileSize = stream->GetSize();
    ScriptBuffer code = new (gc, fileSize) BasicScriptBufferImpl(fileSize);

    stream->Read( code.getBuffer(), fileSize );

    return ParseSwfInternal( code, gc, tagsToFill, swfInfo, streamReader);
  }

  bool SWFParser::ParseSwf( const char *filename, MMgc::GC *gc, nstl::list<TagInfo> & tagsToFill, SWFInfo & swfInfo, SwfStreamReader & streamReader )
  {
    FILE * file = fopen(filename, "rb");
    fseek( file, 0L, SEEK_END );
    size_t fileSize = ftell( file );
    rewind( file );

    ScriptBuffer code = new (gc, fileSize) BasicScriptBufferImpl(fileSize);
    fread(code.getBuffer(), 1, fileSize, file);

    fclose( file );

    return ParseSwfInternal( code, gc, tagsToFill, swfInfo, streamReader );
  }

  bool SWFParser::ParseSwfInternal( ScriptBuffer scriptBuffer, MMgc::GC *gc, nstl::list<TagInfo> & tagsToFill, SWFInfo & swfInfo, SwfStreamReader & streamReader )
  {
    streamReader.SetStreamBuffer(scriptBuffer);
    streamReader.SetPos( 4 ); // skip magic #
    uint32_t swflen = streamReader.readUI32();
    
    if (scriptBuffer[0] == 'C') 
    {
      // decompress the swf
      swflen -= 8;
      BasicScriptBufferImpl* newswfbuf = new (gc, swflen) BasicScriptBufferImpl(swflen);
      ScriptBuffer newswf(newswfbuf);
      uLongf dlen = swflen;
      int e = uncompress((Bytef*)&newswf[0], &dlen, (Bytef*)&scriptBuffer[8], (uLongf)scriptBuffer.getSize()-8);
      if (e != Z_OK)
        return false;
      
      scriptBuffer = newswf;
      streamReader.SetStreamBuffer(newswf);
      streamReader.SetPos( 0 );
    }

    if (swflen != scriptBuffer.getSize()) 
      return false;

    swfInfo.swflen = swflen;

    //read header
    streamReader.readRect( swfInfo.rect );

    swfInfo.frameRate = streamReader.readUI16()/256.0f;
    swfInfo.frameCount = streamReader.readUI16();
    
    while (streamReader.GetPos() < swflen) 
    {
      TagInfo tagInfo;

      streamReader.readTagInfo( tagInfo );
      streamReader.ignore( tagInfo.tagLen );

      tagsToFill.push_back(tagInfo);

//      DebugTrace( "Found flash tag '%s' of length %d", SWFTags::EnumToString((SWFTags::SWFTagType)tagInfo.tagType), tagInfo.tagLen );
    }

    return true;
  }
}

namespace SWFTags
{
const char * EnumToString( const SWFTagType value )
{
  switch( value )
  {
  case SWFTAGS_END:
    return "End";
  case SWFTAGS_SHOWFRAME:
    return "ShowFrame";
  case SWFTAGS_DEFINESHAPE:
    return "DefineShape";
  case SWFTAGS_PLACEOBJECT:
    return "PlaceObject";
  case SWFTAGS_REMOVEOBJECT:
    return "RemoveObject";
  case SWFTAGS_DEFINEBITS:
    return "DefineBits";
  case SWFTAGS_DEFINEBUTTON:
    return "DefineButton";
  case SWFTAGS_JPEGTABLES:
    return "JPEGTables";
  case SWFTAGS_SETBACKGROUNDCOLOR:
    return "SetBackgroundColor";
  case SWFTAGS_DEFINEFONT:
    return "DefineFont";
  case SWFTAGS_DEFINETEXT:
    return "DefineText";
  case SWFTAGS_DOACTION:
    return "DoAction";
  case SWFTAGS_DEFINEFONTINFO:
    return "DefineFontInfo";
  case SWFTAGS_DEFINESOUND:
    return "DefineSound";
  case SWFTAGS_STARTSOUND:
    return "StartSound";
  case SWFTAGS_DEFINEBUTTONSOUND:
    return "DefineButtonSound";
  case SWFTAGS_SOUNDSTREAMHEAD:
    return "SoundStreamHead";
  case SWFTAGS_SOUNDSTREAMBLOCK:
    return "SoundStreamBlock";
  case SWFTAGS_DEFINEBITSLOSSLESS:
    return "DefineBitsLossless";
  case SWFTAGS_DEFINEBITSJPEG2:
    return "DefineBitsJPEG2";
  case SWFTAGS_DEFINESHAPE2:
    return "DefineShape2";
  case SWFTAGS_DEFINEBUTTONCXFORM:
    return "DefineButtonCxform";
  case SWFTAGS_PROTECT:
    return "Protect";
  case SWFTAGS_PLACEOBJECT2:
    return "PlaceObject2";
  case SWFTAGS_REMOVEOBJECT2:
    return "RemoveObject2";
  case SWFTAGS_DEFINESHAPE3:
    return "DefineShape3";
  case SWFTAGS_DEFINETEXT2:
    return "DefineText2";
  case SWFTAGS_DEFINEBUTTON2:
    return "DefineButton2";
  case SWFTAGS_DEFINEBITSJPEG3:
    return "DefineBitsJPEG3";
  case SWFTAGS_DEFINEBITSLOSSLESS2:
    return "DefineBitsLossless2";
  case SWFTAGS_DEFINEEDITTEXT:
    return "DefineEditText";
  case SWFTAGS_DEFINESPRITE:
    return "DefineSprite";
  case SWFTAGS_PRODUCTINFO:
    return "ProductInfo";
  case SWFTAGS_FRAMELABEL:
    return "FrameLabel";
  case SWFTAGS_SOUNDSTREAMHEAD2:
    return "SoundStreamHead2";
  case SWFTAGS_DEFINEMORPHSHAPE:
    return "DefineMorphShape";
  case SWFTAGS_DEFINEFONT2:
    return "DefineFont2";
  case SWFTAGS_EXPORTASSETS:
    return "ExportAssets";
  case SWFTAGS_IMPORTASSETS:
    return "ImportAssets";
  case SWFTAGS_ENABLEDEBUGGER:
    return "EnableDebugger";
  case SWFTAGS_DOINITACTION:
    return "DoInitAction";
  case SWFTAGS_DEFINEVIDEOSTREAM:
    return "DefineVideoStream";
  case SWFTAGS_VIDEOFRAME:
    return "VideoFrame";
  case SWFTAGS_DEFINEFONTINFO2:
    return "DefineFontInfo2";
  case SWFTAGS_DEBUGID:
    return "DebugID";
  case SWFTAGS_ENABLEDEBUGGER2:
    return "EnableDebugger2";
  case SWFTAGS_SCRIPTLIMITS:
    return "ScriptLimits";
  case SWFTAGS_SETTABINDEX:
    return "SetTabIndex";
  case SWFTAGS_FILEATTRIBUTES:
    return "FileAttributes";
  case SWFTAGS_PLACEOBJECT3:
    return "PlaceObject3";
  case SWFTAGS_IMPORTASSETS2:
    return "ImportAssets2";
  case SWFTAGS_DEFINEFONTALIGNZONES:
    return "DefineFontAlignZones";
  case SWFTAGS_CSMTEXTSETTINGS:
    return "CSMTextSettings";
  case SWFTAGS_DEFINEFONT3:
    return "DefineFont3";
  case SWFTAGS_SYMBOLCLASS:
    return "SymbolClass";
  case SWFTAGS_METADATA:
    return "Metadata";
  case SWFTAGS_DEFINESCALINGGRID:
    return "DefineScalingGrid";
  case SWFTAGS_DOABC:
    return "DoABC";
  case SWFTAGS_DEFINESHAPE4:
    return "DefineShape4";
  case SWFTAGS_DEFINEMORPHSHAPE2:
    return "DefineMorphShape2";
  case SWFTAGS_DEFINESCENEANDFRAMELABELDATA:
    return "DefineSceneAndFrameLabelData";
  case SWFTAGS_DEFINEBINARYDATA:
    return "DefineBinaryData";
  case SWFTAGS_DEFINEFONTNAME:
    return "DefineFontName";
  case SWFTAGS_STARTSOUND2:
    return "StartSound2";
  case SWFTAGS_DEFINEBITSJPEG4:
    return "DefineBitsJPEG4";
  case SWFTAGS_DEFINEFONT4:
    return "DefineFont4";
  };

  return "Error!";
}
}