#include "stdafx.h"

#include "RTTI.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//just make it known to compiler
extern "C" char * __unDName(char * outputString, const char * name, int maxStringLength, void * (* pAlloc )(size_t), void (* pFree )(void *), unsigned short disableFlags);
//extern "C" void* __cdecl __unDNameHelper(char * outputString, const char * name, int maxStringLength, unsigned short disableFlags);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NRTTI
{
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //internal parsing structures
  struct TypeDescriptor 
  {
    // vtable of type_info class
    const void * pVFTable;
    // used to keep the demangled name returned by type_info::name()
    void* spare;
    // mangled type name, e.g. ".H" = "int", ".?AUA@@" = "struct A", ".?AVA@@" = "class A"
    char name[1];
  };

  struct PMD
  {
    int mdisp;  //vftable offset of this base class
    int pdisp;  //vbtable displacement
    int vdisp;  //displacement inside vbtable
  };

  struct RTTIBaseClassDescriptor
  {
    struct TypeDescriptor* pTypeDescriptor; //type descriptor of the class
    DWORD numContainedBases; //number of direct bases of this base class
    PMD where;        //pointer-to-member displacement info
    DWORD attributes;        //flags, usually 0
    struct RTTIClassHierarchyDescriptor * pHier; // hierarchy of this class
  };

  typedef RTTIBaseClassDescriptor * RTTIBaseClassArray;

  struct RTTIClassHierarchyDescriptor
  {
    DWORD signature;      //always zero?
    DWORD attributes;     //bit 0 set = multiple inheritance, bit 1 set = virtual inheritance
    DWORD numBaseClasses; //number of classes in pBaseClassArray. Count includes class itself.
    RTTIBaseClassArray* pBaseClassArray;
  };
  struct RTTICompleteObjectLocator
  {
    DWORD signature; //always zero ?
    DWORD offset;    //offset of this vtable in the complete class
    DWORD cdOffset;  //constructor displacement offset
    struct TypeDescriptor* pTypeDescriptor; //TypeDescriptor of the complete class
    struct RTTIClassHierarchyDescriptor* pClassDescriptor; //describes inheritance hierarchy
  };
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  #define UNDNAME_COMPLETE                 (0x0000)
  #define UNDNAME_NO_LEADING_UNDERSCORES   (0x0001) /* Don't show __ in calling convention */
  #define UNDNAME_NO_MS_KEYWORDS           (0x0002) /* Don't show calling convention at all */
  #define UNDNAME_NO_FUNCTION_RETURNS      (0x0004) /* Don't show function/method return value */
  #define UNDNAME_NO_ALLOCATION_MODEL      (0x0008)
  #define UNDNAME_NO_ALLOCATION_LANGUAGE   (0x0010)
  #define UNDNAME_NO_MS_THISTYPE           (0x0020)
  #define UNDNAME_NO_CV_THISTYPE           (0x0040)
  #define UNDNAME_NO_THISTYPE              (0x0060)
  #define UNDNAME_NO_ACCESS_SPECIFIERS     (0x0080) /* Don't show access specifier (public/protected/private) */
  #define UNDNAME_NO_THROW_SIGNATURES      (0x0100)
  #define UNDNAME_NO_MEMBER_TYPE           (0x0200) /* Don't show static/virtual specifier */
  #define UNDNAME_NO_RETURN_UDT_MODEL      (0x0400)
  #define UNDNAME_32_BIT_DECODE            (0x0800)
  #define UNDNAME_NAME_ONLY                (0x1000) /* Only report the variable/method name */
  #define UNDNAME_NO_ARGUMENTS             (0x2000) /* Don't show method arguments */
  #define UNDNAME_NO_SPECIAL_SYMS          (0x4000)
  #define UNDNAME_NO_COMPLEX_TYPE          (0x8000)
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  static nstl::string UndecorateName(const char *decoratedName)
  {
    const char * const pName = decoratedName;
    nstl::string res;
    char * const pTmpUndName = __unDName(0, pName, 0, malloc, free, UNDNAME_NO_ARGUMENTS | UNDNAME_32_BIT_DECODE);
    if (pTmpUndName)
    {
      res = pTmpUndName;
      free(pTmpUndName);
    }
    return res;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  static nstl::string DecorateTypeName(const char *cleanName)
  {
    const char * const classPrefix = ".?AV";
    const char * const structPrefix = ".?AU";
    size_t cleanSize = strlen(cleanName) + 1;
    ScopedArray<char> classT(new char[cleanSize]);
    ScopedArray<char> spaceT(new char[cleanSize]);
    ScopedArray<char> nameT(new char[cleanSize]);
    int nRes = sscanf_s(cleanName, "%[^ ]%[ ]%[^ ]", &classT[0], cleanSize - 1, &spaceT[0], cleanSize - 1, &nameT[0], cleanSize - 1);
    if(nRes != 3)
    {
      return nstl::string(cleanName);
    }
    string sClass(Get(nameT));
    list<string> stack;
    do
    {
      nRes = sscanf_s(sClass.c_str(), "%[a-zA-Z0-9_]", &spaceT[0], cleanSize - 1);
      if(nRes != 1)
        break;
      stack.insert(stack.begin(), string(Get(spaceT)));
      sClass.erase(0, strstr(sClass.c_str(), Get(spaceT)) + strlen(Get(spaceT)) - sClass.c_str());
      nRes = sscanf_s(sClass.c_str(), "%[:]", &spaceT[0], cleanSize - 1);
      if(nRes != 1)
        break;
      sClass.erase(0, strstr(sClass.c_str(), Get(spaceT)) + strlen(Get(spaceT)) - sClass.c_str());
    }while(true);
    string dname("");
    for(list<string>::iterator it = stack.begin(); it != stack.end(); it++)
    {
       dname += *it;
       dname += "@";
    }
    if(strcmp(Get(classT), "struct") == 0)
    {
      dname  = structPrefix + dname;
    }
    else
    {
      dname  = classPrefix + dname;
    }
    dname += "@";
    return dname;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool VirtualClassWalker(void const *pObj, IDescriptorAction *pAction)
  {
    void *pVtbl = *(void **)pObj;
    if(pVtbl == NULL)
    {
      return false;
    }

    RTTICompleteObjectLocator * pCOL = *((RTTICompleteObjectLocator **)pVtbl - 1);
    if(pCOL->pClassDescriptor == NULL)
    {
      //no descriptor ?
      return false;
    }
    for (unsigned int i = 0; i < pCOL->pClassDescriptor->numBaseClasses; i++)
    {
      RTTIBaseClassArray pCurr = pCOL->pClassDescriptor->pBaseClassArray[i];
      NI_VERIFY(pCurr != NULL, "Descriptor is expected to be valid", return false;);
      if(!pAction->Act(pCurr))
        return false;
    }
    return true;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ParentChecker::ParentChecker(char const *pClassName): bResult(false), pOwnName(NULL)
  {
    //perform mangling here
    if(pClassName[0] == '.' && pClassName[1] == '?')
    {
      pOwnName = pClassName;
    }
    else
    {
      string sMangled = DecorateTypeName(pClassName);
      size_t nSize = strlen(sMangled.c_str()) + 1;
      ::Reset(mangledSearchName, new char[nSize]);
      strcpy_s(Get(mangledSearchName), nSize, sMangled.c_str());
    }
  }
  bool ParentChecker::Act(RTTIBaseClassDescriptor *pDesc)
  {
    NI_VERIFY(pDesc != NULL, "Invalid", return false;);
    if(pDesc->pTypeDescriptor == NULL)
    {
      return false;
    }
    bResult |= strcmp(pOwnName?pOwnName:&mangledSearchName[0], pDesc->pTypeDescriptor->name) == 0;
    return !bResult;
  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool HierBuilder::Act(RTTIBaseClassDescriptor *pDesc)
  {
    NI_VERIFY(pDesc != NULL, "Invalid", return false;);
    if(pDesc->pTypeDescriptor == NULL)
    {
      return false;
    }
    if(bMangled)
    {
      res.push_back(string(pDesc->pTypeDescriptor->name + 1));
    }
    else
    {
      res.push_back(UndecorateName(pDesc->pTypeDescriptor->name + 1));
    }
    return true;
  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
