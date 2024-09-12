#include "stdafx.h"

extern "C"
{

#include "CAsserts.h"

void __cdecl ni_report_assert(const char* message, const char* file, int line)
{
  systemLogEx( NLogg::LEVEL_ASSERT, file, line ) << message;
}

};
