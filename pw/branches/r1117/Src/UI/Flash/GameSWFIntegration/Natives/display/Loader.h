#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"
#include "DisplayObjectContainer.h"

namespace avmplus
{
class LoaderInfoObject;
class URLRequestObject;
class ApplicationDomainObject;
class SecurityDomainObject;
class ByteArrayObject;
class DisplayObjectObject;


class LoaderObject: public DisplayObjectContainerObject
{
public:

  LoaderObject( LoaderClass * classType );
  LoaderObject( VTable* ivtable, ScriptObject* prototype );
  ~LoaderObject();

  LoaderInfoObject* get_contentLoaderInfo();

  void _load(URLRequestObject* request, bool checkPolicyFile, ApplicationDomainObject* applicationDomain, SecurityDomainObject* securityDomain, double deblockingFilter);
  void _unload(bool halt, bool gc);
  void _loadBytes(ByteArrayObject* bytes, bool checkPolicyFile, ApplicationDomainObject* applicationDomain, SecurityDomainObject* securityDomain, double deblockingFilter);

  double _getJPEGLoaderContextdeblockingfilter(AvmBox context);

  void close();
  DisplayObjectObject* get_content() 
  { 
    return content; 
  }

  virtual const char* GetDumpName() { return "<Loader>"; }

private:
  DECLARE_SLOTS_LoaderObject;

  DRCWB( LoaderInfoObject* ) contentLoaderInfo;
  DRCWB( DisplayObjectObject*) content;
};
  
DECLARE_AS_CLASS( LoaderClass, DisplayObjectContainerClass, LoaderObject )

}