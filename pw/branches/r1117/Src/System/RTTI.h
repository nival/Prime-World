#ifndef RTTI_H_4352365466632asddxf34534
#define RTTI_H_4352365466632asddxf34534

#include <typeinfo>
#include "nvector.h"
#include "nstring.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NRTTI
{
  #pragma warning( disable : 4512 )

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<typename T>
  bool IsObjectHasVFPTR(T *pObj)
  {
    if(pObj == NULL)
    {
      return false;
    }
    //".PAUHINSTANCE__@@"	HINSTANCE
    //".?AVCTextFileDumper@NLogg@@" }	NLogg::CTextFileDumper
    const type_info& ti = typeid(*pObj);
    if(strncmp(ti.raw_name() + 1, "?AV", 3) == 0 || strncmp(ti.raw_name() + 1, "?AU", 3) == 0)
    {
      return true;
    }
    return false;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct IDescriptorAction 
  {
    virtual bool Act(struct RTTIBaseClassDescriptor *pDesc) = 0;
    virtual ~IDescriptorAction() {} 
  };
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct ParentChecker: public IDescriptorAction
  {
    ScopedArray<char> mangledSearchName;
    char const *pOwnName;
    bool bResult;
    ParentChecker(char const *pClassName);
    bool Act(struct RTTIBaseClassDescriptor *pDesc);
  };
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct HierBuilder: public IDescriptorAction
  {
    bool bMangled;
    nstl::vector<string> &res;
    HierBuilder(nstl::vector<string> &hl, bool mangled): bMangled(mangled), res(hl) {res.clear();};
    bool Act(struct RTTIBaseClassDescriptor *pDesc);
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool VirtualClassWalker(void const *pObj, IDescriptorAction *pAction);


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<typename T>
  bool IsInParentList(T const *pObj, char const *pClassName)
  {
    if(IsObjectHasVFPTR(pObj))
    {
      ParentChecker checker(pClassName);
      VirtualClassWalker(pObj, &checker);
      return checker.bResult;
    }
    else
    {
      return strcmp(typeid(*pObj).name(), pClassName) == 0;
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<typename T>
  bool BuildParentsList(T const *pObj, nstl::vector<string> &list, bool mangled = true)
  {
    if(!IsObjectHasVFPTR(pObj))
    {
      if(pObj)
      {
        list.push_back(string(typeid(*pObj).raw_name()));
        return true;
      }
      return false;
    }
    else
    {
      HierBuilder builder(list, mangled);
      bool bRes = VirtualClassWalker(pObj, &builder);
      return bRes;
    }
  }

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif RTTI_H_4352365466632asddxf34534