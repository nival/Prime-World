#include "stdafx.h"
#include "NewLoginTypes.h"

namespace newLogin
{

SERIALIZE_FACTORY( LoginHello );
SERIALIZE_FACTORY( LoginReply );
SERIALIZE_FACTORY( ServiceRequest )
SERIALIZE_FACTORY( ServiceReqReply );
SERIALIZE_FACTORY( FrontendHello );
SERIALIZE_FACTORY( FrontendHelloReply );


NI_ENUM_BEGIN_STD( ESvcConnectionResult );
  NI_ENUM_ITEM( Ok );
  NI_ENUM_ITEM( UnknownSvc );
  NI_ENUM_ITEM( Timeout );
  NI_ENUM_ITEM( OutOfSvcResources );
  NI_ENUM_ITEM( ServerFault );
  NI_ENUM_ITEM( WrongFrontendKey );
NI_ENUM_END_STD;

}
