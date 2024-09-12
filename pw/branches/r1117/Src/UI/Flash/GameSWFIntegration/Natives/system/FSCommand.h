#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"

namespace avmplus
{


class FSCommandObject: public ScriptObject
{
public:
  FSCommandObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~FSCommandObject(void) {}


private:
  DECLARE_SLOTS_FSCommandObject;
};
  
class FSCommandClass : public ClassClosure
{
public:
  FSCommandClass(VTable *vtable): ClassClosure(vtable){}
  ~FSCommandClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) FSCommandObject(ivtable, prototype);
  }  
  
  void _fscommand(AvmString command, AvmString args);

private:
  DECLARE_SLOTS_FSCommandClass;
};

}