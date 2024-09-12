#include "stdafx.h"
#include "TransportAddress.h"
#include "AddressTranslator.h"
#include "System/StrUtils.h"

NI_DEFINE_REFCOUNT( Transport::IAddressTranslator );

namespace Transport
{
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  const char* AddressToString( const Address& address )
  {
    static char buf[256];
    if ( address.sender == autoAssignClientId )
    {
      NStr::Printf( buf, sizeof( buf ), "(%s->%s)", address.source.c_str(), address.target.c_str() );
    } 
    else
    {
      NStr::Printf( buf, sizeof( buf ), "(%s:%d->%d)", address.target.c_str(), address.sender, address.client );
    }
    return buf;
  };
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void GenerateServiceName( const TServiceId& serviceClass, int svcidx, TServiceId* result )
  {
    result->Printf( "%s/%d", serviceClass.c_str(), svcidx );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool IsServiceIdValid(Transport::TServiceId const & svcid)
  {
    if (!svcid.size())
      return false;

    if ('/' == svcid.At(0) || '/' == svcid.At(svcid.size()-1))
      return false;

    return true;
  }

  void findLastSlashes(char const * svcid, char const *& prevlast, char const *& last)
  {
    last = 0;
    prevlast = 0;

    if (!svcid || !strlen(svcid))
      return;

    char const * lastslash = svcid;
    char const * prevlastslash = 0;
    char const * curr = 0;

    while ((curr = NStr::FindFirstChar(lastslash + 1, '/')) != 0)
    {
      prevlastslash = lastslash;
      lastslash = curr;
    }

    if (lastslash != svcid)
    {
      last = lastslash;
      if (prevlastslash != svcid)
        prevlast = prevlastslash;
    }
  }

  int getServiceIndexPos( TServiceId const & service, int& indexPos )
  {
    indexPos = -1;

    char* idx = NStr::FindLastChar(service.c_str(), '/');
    if ( !idx )
      return -1;

    if (!NStr::IsDecNumber(idx + 1))
      return -1;

    indexPos = idx - service.c_str() + 1;
    return NStr::ToInt( idx + 1 );
  }

  int GetServerIndex( const TServiceId& service )
  {
    int indexPos;
    return getServiceIndexPos(service, indexPos);
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool GetServiceClass( const TServiceId& service, TServiceId* result )
  {
    if (!IsServiceIdValid(service))
      return false;

    char const * prevlastslash = 0;
    char const * lastslash = 0;
    findLastSlashes(service.c_str(), prevlastslash, lastslash);
    if (!prevlastslash && !lastslash)
    //  no slashes - input is class name
    {
      result->AssignN( service.c_str(), service.size() );
    }
    else
    if (prevlastslash)
    //  at least 2 slashes in svcid
    {
      if (NStr::IsDecNumber(lastslash + 1) || '*' == *(lastslash + 1))
        result->AssignN( prevlastslash + 1, lastslash - prevlastslash - 1 );
      else
        result->AssignN( lastslash + 1, service.c_str() + service.size() - lastslash );
    }
    else
    if (lastslash)
    {
      if (NStr::IsDecNumber(lastslash + 1) || '*' == *(lastslash + 1))
        result->AssignN( service.c_str(), lastslash - service.c_str());
      else
        result->AssignN( lastslash + 1, service.c_str() + service.size() - lastslash );
    }
    else
    {
      NI_ASSERT(false, "");
    }

    return true;
  }

  bool GetServiceClass( const TServiceId& service, TServiceId& result )
  {
    return GetServiceClass(service, &result);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool MakeFullServiceId(TServiceId const & svcpath, TServiceId const & svcls, int svcidx, TServiceId& fullsvcid)
  {
    if (!svcls.size())
      return false;

    string ssvcidx;
    size_t sz = 0;

    if (svcpath.size())
      sz += svcpath.size() + 1;

    sz += svcls.size();

    if (svcidx >= 0)
    {
      ssvcidx = NStr::IntToStr(svcidx);
      if (ssvcidx.length())
        sz += (1 + ssvcidx.length());
    }

    if (sz > fullsvcid.capacity())
      return false;

    fullsvcid = "";
    if (svcpath.size())
    {
      fullsvcid += svcpath.c_str();
      fullsvcid += "/";
    }
    fullsvcid += svcls.c_str();
    if (svcidx >= 0)
    {
      fullsvcid += "/";
      fullsvcid += ssvcidx.c_str();
    }

    return true;
  }


  bool MakeFullServiceId(TServiceId const & svcpath, TServiceId const & localsvcid, TServiceId& fullsvcid)
  {
    return MakeFullServiceId( svcpath, localsvcid, -1, fullsvcid );
  }


  void GetServicePath(TServiceId const & service, TServiceId & svcpath)
  {
    char const * lastslash = service.c_str();
    char const * prevlastslash = 0;
    char* svcidxslash = NStr::FindLastChar(lastslash, '/');
    if (svcidxslash && !NStr::IsDecNumber(svcidxslash + 1))
      svcidxslash = 0;

    do
    {
      prevlastslash = lastslash;
      lastslash = NStr::FindFirstChar(prevlastslash, '/');
    }
    while(lastslash > prevlastslash && lastslash != svcidxslash);

    if (prevlastslash == service.c_str())
      //  no svcpath
      return;

    NStr::CopyN(svcpath.Ptr(), service.c_str(), svcpath.capacity(), prevlastslash - service.c_str());
  }

  TServiceId GetServicePath(TServiceId const & service)
  {
    TServiceId svcpath;
    GetServicePath(service, svcpath);
    return svcpath;
  }

  bool GetLocalServiceId(TServiceId const & svcid, TServiceId& localsvcid)
  {
    Transport::TServiceId svcls;
    if (GetServiceClass(svcid, &svcls))
    {
      int idx = GetServerIndex(svcid);
      if (idx < 0)
        localsvcid = svcls;
      else
        GenerateServiceName(svcls, idx, &localsvcid);

      return true;
    }
    else
      return false;
  }

}