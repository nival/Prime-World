#include "ClusterTypes.h"
#include <System/SafeTextFormatEx.h>


namespace Cluster
{
  const char * FmtGameId( TGameId _id )
  {
    return NI_STRFMT( "%016llx", _id );
  }
}
