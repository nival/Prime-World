#pragma  once
#include "System/fixedString.h"

namespace Coordinator
{
  typedef FixedString<16> TServiceRole;
  const TServiceRole defaultServiceRole = "";
  const TServiceRole PrimarySvcRole = defaultServiceRole;
  const TServiceRole SecondarySvcRole = "secondary";
}
