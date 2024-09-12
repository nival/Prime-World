#pragma once

#include "Dumper.h"


namespace NLogg
{

class BasicTextFileDumper : public CDumper
{
  NI_DECLARE_REFCOUNT_CLASS_1( BasicTextFileDumper, CDumper );

public:
  explicit BasicTextFileDumper( CLogger * logger, const char * name ) :
  CDumper( logger, name )
  {}

  virtual string FileName() const = 0;

  static BasicTextFileDumper * New( CLogger * logger, const char * suffix, const char* folder = 0 );
  static void Setup( bool syncMode, unsigned bufferSize );
};

} //namespace NLogg
