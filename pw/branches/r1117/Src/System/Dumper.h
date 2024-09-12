#pragma once

#include "Logger.h"
#include "Thread.h"

namespace NLogg
{

const unsigned long GetLevelMask( const NLogg::ELevel eLevel );
const unsigned long GetFromMinLevelMask( const NLogg::ELevel eMinLevel );

// default invalue for filter mask; means we should inherit filter mask if possible (from base class or some sort of config)
const unsigned long LEVEL_NONE =    0x00000000;
const unsigned long LEVEL_ALL =     0x7FFFFFFF;
const unsigned long LEVEL_INHERIT = 0xFFFFFFFF;


class CDumper : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( CDumper, BaseObjectMT );

public:
  CDumper( CLogger * pDefaultLogger, const char * szDumperName = "" );

  //by default dumper dump all messages, but first call of AddLevel( ... ) removes all levels except specified
  void AddLevel( const ELevel eLevel );
  void AddMinLevel( const ELevel eLevel );
  void RemoveLevel( const ELevel eLevel );

  void Dump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly );

  const char *GetName() const { return szDumperName; };

  static int RotationPeriod();
  static void SetRotationPeriod( int _hours );

protected:
  virtual void OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly ) = 0;

private:
  unsigned long     dwLevelFilter;
  const char  *     szDumperName; // should be static
};

} //namespace NLogg
