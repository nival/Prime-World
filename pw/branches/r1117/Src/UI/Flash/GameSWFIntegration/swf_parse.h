#pragma once
#include "SwfStreamReader.h"

namespace avmplus
{
  class ScriptBuffer;
  class DomainEnv;
  class Toplevel;
  class CodeContext;
  class ReadOnlyScriptBufferImpl;
}


namespace  SWFTags
{
  enum SWFTagType;
}

namespace flash
{

class SWFParser
{
public:

  static bool ParseSwf( Stream* stream, MMgc::GC * gc, nstl::list<TagInfo> & tagsToFill, SWFInfo & swfInfo, SwfStreamReader & streamReader );
  static bool ParseSwf( const char *filename, MMgc::GC * gc, nstl::list<TagInfo> & tagsToFill, SWFInfo & swfInfo, SwfStreamReader & streamReader );

private:

  static bool ParseSwfInternal( avmplus::ScriptBuffer scriptBuffer, MMgc::GC *gc, nstl::list<TagInfo> & tagsToFill, SWFInfo & swfInfo, SwfStreamReader & streamReader);
};

}
