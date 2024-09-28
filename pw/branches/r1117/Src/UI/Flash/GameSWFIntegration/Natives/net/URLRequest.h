#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"

namespace avmplus
{
class ArrayObject;


class URLRequestObject: public ScriptObject
{
public:
  URLRequestObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~URLRequestObject(void) {}

  AvmString get_method()
  {
    NI_ALWAYS_ASSERT("Not yet implemented");
    return (AvmString)0;
  }

  void set_method(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented");
    return (void)0;
  }

  AvmString get_digest()
  {
    NI_ALWAYS_ASSERT("Not yet implemented");
    return (AvmString)0;
  }

  void set_contentType(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented");
    return (void)0;
  }

  void set_digest(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented");
    return (void)0;
  }

  AvmBox get_data()
  {
    NI_ALWAYS_ASSERT("Not yet implemented");
    return (AvmBox)0;
  }

  void set_requestHeaders(ArrayObject* value)
  {
    requestHeaders = value;
  }

  AvmString get_url()
  {
    return url;
  }

  void set_data(AvmBox value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented");
    return (void)0;
  }

  ArrayObject* get_requestHeaders()
  {
    return requestHeaders;
  }

  AvmString get_contentType()
  {
    NI_ALWAYS_ASSERT("Not yet implemented");
    return (AvmString)0;
  }

  void set_url(AvmString value)
  {
    url = value;
  }


private:
  DECLARE_SLOTS_URLRequestObject;

  DRCWB(AvmString) url;
  DRCWB(ArrayObject*) requestHeaders;
};
  
class URLRequestClass : public ClassClosure
{
public:
  URLRequestClass(VTable *vtable): ClassClosure(vtable){}
  ~URLRequestClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) URLRequestObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_URLRequestClass;
};

}