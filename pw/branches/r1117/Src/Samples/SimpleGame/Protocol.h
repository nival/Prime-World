#ifndef PROTOCOL_H_0DD7CA57_0C20_478A_A3
#define PROTOCOL_H_0DD7CA57_0C20_478A_A3

#include "Network/TransportAddress.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Protocol 
{ 
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  typedef int ObjectID;
  typedef float Time;
  typedef double AbsoluteTime;

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  const int groundObjectId = -2;
  const int invalidObjectId = -1; 

  static const int LOGIC_FRAME_TIME_MSEC = 100; // msec
  static const float LOGIC_FRAME_TIME_SEC = static_cast<float>( LOGIC_FRAME_TIME_MSEC ) / 1000.f; // sec

  static const Transport::TServiceId locationServerId = "location";
  static const Transport::TServiceId battleServerId = "battle";

  static const char* LOCATION_CLIENT_RPC_NAME = "location_client";
  static const char* LOCATION_SERVER_RPC_NAME = "location_server";
  static const char* BATTLE_SERVER_RPC_NAME = "battle_server";

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace LocationProtocol
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //#define PROTOCOL_H_0DD7CA57_0C20_478A_A3
