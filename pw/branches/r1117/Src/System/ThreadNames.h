#pragma once

namespace threading
{

void SetDebugThreadName( const char * name );
const char * GetDebugThreadName( DWORD threadId );

}; //namespace threading
