#ifndef WEBCLIENT_H_INCLUDED
#define WEBCLIENT_H_INCLUDED

#include "System/nlist.h"
#include "System/nstring.h"
#include "System/Pointers/Pointers.h"


namespace webClient
{

typedef nstl::list<nstl::string>  TRequestProperties;

class IHttpClient : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IHttpClient, IBaseInterfaceMT );

public:
  virtual void SetRequestProperies( const TRequestProperties & reqProperties ) = 0;
  virtual bool PerformPOST( const char * url, const void * _postBody, size_t _postBodySize, nstl::string & answerHeader, nstl::string & answerBody ) = 0;
  virtual bool PerformGET( const char * url, nstl::string & answerHeader, nstl::string & answerBody ) = 0;
  virtual long GetResponseCode() const = 0;
};

IHttpClient * NewHttpClient();

} //namespace webClient

#endif //WEBCLIENT_H_INCLUDED
