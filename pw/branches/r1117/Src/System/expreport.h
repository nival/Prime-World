#ifndef __EXPREPORT_H__633124997137656250
#define __EXPREPORT_H__633124997137656250

/*
 *  CVS Revision:$Id: expreport.h,v 1.9 2007/06/01 17:02:56 earnol Exp $
 *
 */

/**
  @file
  @brief    This class generates the dump and xml overview files.
  @date     Created on 18/04/2007
  @project  NBSU
  @author   Earnol
*/
// *******************************************************************
// compiler specific

// *******************************************************************
// includes
// engine
// standard
#include <atlbase.h>
#include "Vendor/wtl/include/atlapp.h"
#include "Vendor/wtl/include/atlmisc.h"
#include <Imagehlp.h>
#include "nvector.h"
#include <MsXml.h>

//#include "_dllwalker.h"

// *******************************************************************
// defines & constants

//
// COM helper macros
//
#define CHECKHR(x) {HRESULT hr = x; if (FAILED(hr)) goto CleanUp;}
#define SAFERELEASE(p) {if (p) {(p)->Release(); p = NULL;}}

// *******************************************************************
// classes 
namespace NBSU
{


  // *******************************************************************
  // classes 

  // TElem -- a simple class to wrap up IXMLDomElement and iterat its children.
  //   name()    - in <item>stuff</item> it returns "item"
  //   val()     - in <item>stuff</item> it returns "stuff"
  //   attr(s)   - in <item s=L"hello">stuff</item> it returns "hello"
  //   subnode(b)- in <item><a>hello</a><b>there</b></item> it returns the TElem <b>there</b>
  //   subval(b) - in <item><a>hello</a><b>there</b></item> it returns "there"
  //   for (TElem c=e.begin(); c!=e.end(); c++) {...} - iterators over the subnodes
  struct TElem
  { 
    CComPtr<IXMLDOMElement> elem;
    CComPtr<IXMLDOMNodeList> nlist; 
    int pos; 
    long clen;
    //
    TElem(): elem(0), nlist(0), pos(-1), clen(0) {}
    TElem(int _clen): elem(0), nlist(0), pos(-1), clen(_clen) {}
    TElem(CComPtr<IXMLDOMElement> _elem): elem(_elem), nlist(0), pos(-1), clen(0) {get();}
    TElem(CComPtr<IXMLDOMNodeList> _nlist): elem(0), nlist(_nlist), pos(0), clen(0) {get();}
    void get()
    { 
      if(pos != -1)
      { 
        elem = 0;
        CComPtr<IXMLDOMNode> inode;
        nlist->get_item(pos, &inode);
        if(inode == 0) 
          return;
        DOMNodeType type; 
        inode->get_nodeType(&type);
        if(type != NODE_ELEMENT) 
          return;
        CComQIPtr<IXMLDOMElement> e(inode);
        elem = e;
      }
      clen = 0; 
      if(elem != 0)
      { 
        CComPtr<IXMLDOMNodeList> iNodeList;
        elem->get_childNodes(&iNodeList);
        iNodeList->get_length(&clen);  
      }
    }
    //
    nstl::wstring name() const
    { 
      if (!elem) 
        return L"";
      CComBSTR bn; 
      elem->get_tagName(&bn);
      return nstl::wstring(bn);
    }
    nstl::wstring attr(WCHAR const *name) const {return attr(nstl::wstring(name));}
    nstl::wstring attr(nstl::wstring const &name) const
    { 
      if(!elem) 
        return L"";
      CComBSTR bname(name.c_str());
      CComVariant val(VT_EMPTY);
      elem->getAttribute(bname, &val);
      if(val.vt == VT_BSTR) 
        return val.bstrVal;
      return L"";
    }
    template <typename T> bool addAttr(WCHAR const *name, T const &value)
    { 
      if(!elem) 
        return false;
      CComBSTR bname(name);
      CComVariant val(value);
      elem->setAttribute(bname, val);
      return true;
    }
    template <> bool addAttr(WCHAR const *name, bool const &value)
    { 
      if (!elem) 
        return false;
      CComBSTR bname(name);
      CComVariant val(value?L"TRUE":L"FALSE");
      elem->setAttribute(bname, val);
      return true;
    }
    TElem createChildNode(CComPtr<IXMLDOMDocument> pDoc, WCHAR const *name)
    { 
      CComPtr<IXMLDOMNode> childNode;
      CComBSTR bname(name);
      pDoc->createNode(CComVariant(NODE_ELEMENT), bname, NULL, &childNode);
      CComPtr<IXMLDOMNode> newNode;
      if(elem)
        elem->appendChild(childNode, &newNode);
      else
        pDoc->appendChild(childNode, &newNode);
      CComQIPtr<IXMLDOMElement>  pElement(newNode);
      return TElem(pElement);
    }
    bool attr(nstl::wstring const &name, bool def) const
    { 
      nstl::wstring a = attr(name);
      if (a == nstl::wstring(L"true") || a == nstl::wstring(L"TRUE")) 
        return true;
      else if (a == L"false" || a == L"FALSE") 
        return false;
      else return def;
    }
    int attr(nstl::wstring const &name, int def) const
    { 
      nstl::wstring a = attr(name);
      int i;
      int res = swscanf_s(a.c_str(), L"%i", &i);
      if(res == 1) 
        return i; 
      else 
        return def;
    }
    float attr(nstl::wstring const &name, float def) const
    { 
      nstl::wstring a = attr(name);
      float r; 
      int res = swscanf_s(a.c_str(), L"%f", &r);
      if(res == 1) 
        return r; 
      else 
        return def;
    }
    nstl::wstring val() const
    { 
      if(!elem) 
        return L"";
      CComVariant val(VT_EMPTY);
      elem->get_nodeTypedValue(&val);
      if(val.vt == VT_BSTR) 
        return val.bstrVal;
      return L"";
    }
    TElem subnode(WCHAR const *name) const {return subnode(nstl::wstring(name));}
    TElem subnode(nstl::wstring const &name) const
    { 
      if(!elem) 
        return TElem();
      for(TElem c = begin(); c != end(); c++)
      { 
        if(c.name() == name) 
          return c;
      }
      return TElem();
    }
    nstl::wstring subval(const nstl::wstring name) const
    { 
      if (!elem) 
        return L"";
      TElem c = subnode(name);
      return c.val();
    }
    TElem begin() const
    { 
      if (!elem) 
        return TElem();
      CComPtr<IXMLDOMNodeList> iNodeList;
      elem->get_childNodes(&iNodeList);
      return TElem(iNodeList);
    }
    TElem end() const
    { 
      return TElem(clen);
    }
    TElem operator++(int)
    { 
      if(pos != -1) 
      {
        pos++; 
        get();
      }
      return *this;
    }
    bool operator != (const TElem &e) const
    { 
      return pos != e.clen;
    }
    operator bool () const
    {
      return elem != NULL;
    }
  };

/**
  @brief    Module list entry structure
  @author   Earnol
*/
static struct _ModuleListEntry
{
  MINIDUMP_MODULE_CALLBACK item;
  struct _ModuleListEntry *next;
} start, *node = &start;

class DiExceptionCPP;
class SystemReport  
{
public:
  SystemReport();
    
  struct ProcessorArchitecture
  {
    DWORD nCode;
    WCHAR const *cpCodeText;
  };

  struct ProcessorFeature
  {
    DWORD nFeature;
    WCHAR const *cpFeatureText;
  };

  struct CPUIdFeatureTable
  {
    DWORD nBasicFeature;
    DWORD nExtendedFeature;
  };

  bool SystemReport::dumpSystemInfo(bool bNeedDEviceInformation = true);
private:
  nstl::vector<wstring> m_symFiles;
  static ProcessorArchitecture const _architecturesList[12];
  static ProcessorFeature      const _procFeaturesList[13];
  static CPUIdFeatureTable     const _cpuIDFeatureList[7];
  static ProcessorArchitecture const *GetProcessorArchitectureInfo(DWORD nCode);
  static void FillExceptionRecordNode(NBSU::TElem &pNode, EXCEPTION_RECORD const* pExceptionRecord);
  static void FillProcessorNode(NBSU::TElem &pNode);
  static void FillOSNode(NBSU::TElem &pNode);
  static void FillModulesNode(NBSU::TElem &pNode, CComPtr<IXMLDOMDocument> &pDoc);
  static void FillModuleNode(NBSU::TElem &pNode, CComPtr<IXMLDOMDocument> &pDoc, MINIDUMP_MODULE_CALLBACK const *pItem);
  static void FillMemoryNode(NBSU::TElem &pNode, CComPtr<IXMLDOMDocument> &pDoc);
  static void FillDirectXNode(NBSU::TElem &pNode, CComPtr<IXMLDOMDocument> &pDoc);
  static void FillDevicesNode(NBSU::TElem &pNode, CComPtr<IXMLDOMDocument> &pDoc);
  static bool FormatDOMDocument(CComPtr<IXMLDOMDocument> &pDoc);
};

// *******************************************************************
// functions 

}

#endif //__EXPREPORT_H__633124997137656250

