#include "stdafx.h"
#include "LoginTypes.h"

namespace Login
{

NI_ENUM_BEGIN_STD( ELoginResult );
  NI_ENUM_ITEM( NoResult );
  NI_ENUM_ITEM( NoConnection );
  NI_ENUM_ITEM( Refused );
  NI_ENUM_ITEM( AlreadyIn );
  NI_ENUM_ITEM( ServerError );
  NI_ENUM_ITEM( Success );
  NI_ENUM_ITEM( ClientOutdated );
  NI_ENUM_ITEM( ServerOutdated );
  NI_ENUM_ITEM( UndefinedSex );
  NI_ENUM_ITEM( AccessDenied );
  NI_ENUM_ITEM( AsyncWait );
  NI_ENUM_ITEM( AsyncTimeout );
  NI_ENUM_ITEM( AsyncSuccess );
  NI_ENUM_ITEM( AsyncFail );
NI_ENUM_END_STD;


NI_ENUM_BEGIN_STD( LoginType );
  NI_ENUM_ITEM( ORDINARY );
  NI_ENUM_ITEM( FAST_RECONNECT );
  NI_ENUM_ITEM( PARTIAL_RECONNECT );
NI_ENUM_END_STD;
  
} //namespace Login
