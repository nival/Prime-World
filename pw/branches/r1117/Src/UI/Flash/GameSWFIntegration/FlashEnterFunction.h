#pragma once

#include <Vendor/Tamarin/source/core/avmplus.h>

namespace flash
{

class FlashEnterFunction
{
public:

  FlashEnterFunction();
  ~FlashEnterFunction();

private:
  void SaveFloatState();
  void LoadFloatState();

  DWORD nFPUStatus;
};

} //namespace flash

#define FLASH_ENTER_FUNCTION_RETURN( _gc, _retVal ) \
  flash::FlashEnterFunction flashEnterFunction; \
  MMGC_ENTER_RETURN( _retVal ) \
  MMGC_GCENTER( _gc )

#define FLASH_ENTER_FUNCTION_VOID( _gc ) \
  flash::FlashEnterFunction flashEnterFunction; \
  MMGC_ENTER_VOID \
  MMGC_GCENTER( _gc )
