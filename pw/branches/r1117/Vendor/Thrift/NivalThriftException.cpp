#include <boost/throw_exception.hpp>
#include "System/config.h"

namespace boost
{

#if defined( NV_WIN_PLATFORM )
void __cdecl throw_exception(class std::exception const &)
#elif defined( NV_LINUX_PLATFORM )
void throw_exception(class std::exception const &)
#endif
{
}

void tss_cleanup_implemented()
{
}

}
