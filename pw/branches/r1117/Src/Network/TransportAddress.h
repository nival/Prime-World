#pragma once
#include "TransportTypes.h"

namespace Transport
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  namespace ENetInterface
  {
    const TServiceId Invalid = "";
    // TODO: why these adresses are located here ?
    // common net interfaces
    const TServiceId Coordinator = "coordinator";   // coordinator server interface 
    const TServiceId Client = "client";        // client-to-client uplink and inter-server trafic
    const TServiceId FrontEnd = "frontend";      // client-to-client downlink
  };
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct Address 
  {
    TServiceId target;
    TServiceId source;
    TClientId client;
    TClientId sender;

    bool IsClientConnection() const { return client != autoAssignClientId; }

    Address() : target( ENetInterface::Invalid ), source( ENetInterface::Invalid ), client( -1 ), sender( -1 ) {}
    Address( TServiceId _target, TClientId _client ) : target( _target ), client( _client ), sender( autoAssignClientId ) {}
    Address( TServiceId _target, TClientId _client, TClientId _sender ) : target( _target ), client( _client ), sender( _sender ) {}
    Address( TServiceId _source,  TServiceId _target, TClientId _client ) : source(_source), target( _target ), client( _client ), sender( autoAssignClientId ) {}
  };
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct AddressIsLess 
  { 
    inline bool operator()( const Address& a, const Address& b ) const 
    { 
      if ( a.client < b.client )
        return true;
      if ( a.client > b.client ) 
        return false;
      if ( a.sender < b.sender )
        return true;
      if ( a.sender > b.sender ) 
        return false;
      if ( a.target < b.target )
        return true;
      if ( a.target > b.target ) 
        return false;

      return a.source < b.source;
    };
  };

  struct ServiceIdHash 
  { 
    inline unsigned int operator()( const TServiceId& a ) const
    {
      return nstl::__stl_hash_string( a.c_str() );
    }
  };
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void GenerateServiceName( const TServiceId& serviceClass, int svcidx, TServiceId* result );
  int GetServerIndex( const TServiceId& service );
  bool GetServiceClass( const TServiceId& service, TServiceId* result );
  bool GetServiceClass( const TServiceId& service, TServiceId& result );
  void GetServicePath(TServiceId const & service, TServiceId & svcpath);
  bool GetLocalServiceId(TServiceId const & service, TServiceId& localsvcid);
  Transport::TServiceId GetServicePath(TServiceId const & service);
  bool MakeFullServiceId(TServiceId const & svcpath, TServiceId const & svcls, int svcidx, TServiceId& fullsvcid);
  bool MakeFullServiceId(TServiceId const & svcpath, TServiceId const & localsvcid, TServiceId& fullsvcid);
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  const char* AddressToString( const Address& address ); // for logging
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}