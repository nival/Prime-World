#ifndef __PRECOMPILEDTOOLTIPS_H__2436450174
#define __PRECOMPILEDTOOLTIPS_H__2436450174

#include "System/NameMap.h"
#include "UI/Root.h"

namespace NNameMap
{
  class Map;
}

namespace UI
{
  class ImageLabel;
  class Window;
  _interface ICustomSubstitutes;
}

namespace NGameX
{

struct PrecompiledTooltipVariantParameters
{
  struct Parameter
  {
    string name;
    string value;
  };
  vector<Parameter> rgPrms;
};

struct ITooltipFragment
{
  virtual wchar_t const *Parse(wchar_t const *from, wchar_t const *to) = 0;
  virtual bool ResolveVariants(NNameMap::Map const *pMap) = 0;
  virtual wstring const &Value() = 0;
  virtual bool HasChanged() = 0;
  virtual void AddParameter(PrecompiledTooltipVariantParameters::Parameter const &parameter) {};
  virtual ~ITooltipFragment(){};
};
typedef ITooltipFragment* PTooltipFragment;


class SConstUISubst : public UI::ICustomSubstitutes, public NonCopyable
{
public:
  SConstUISubst() {}

  void Add( const wchar_t * _name, const wstring & _value )
  {
    substMap[_name] = &_value;
  }

  virtual const wstring * GetSubstitute( const wstring & name )
  {
    TSubstMap::const_iterator it = substMap.find( name );
    if ( it != substMap.end() )
      return it->second;

    return 0;
  }

private:
  typedef map<wstring, const wstring *> TSubstMap;
  TSubstMap substMap;
};



class PrecompiledTooltip : public CObjectBase
{
  OBJECT_BASIC_METHODS( PrecompiledTooltip )

public:
  PrecompiledTooltip();
  ~PrecompiledTooltip();

  /// Init tooltip
  bool Init( const NNameMap::Map * pMap, const wstring & str, UI::ICustomSubstitutes * customSubst = 0 );
  /// Make text
  void MakeText(wstring &sout) const;
  /// Is tooltip changed
  bool HasChanged() const;
  
  //Low-level interface
  bool Parse(wstring const &str);
  bool ResolveVariants(NNameMap::Map  const*pMap);
  void AddParameter(PrecompiledTooltipVariantParameters::Parameter const &parameter);
protected:
  AutoPtr<ITooltipFragment> m_tooltip;
};

class WindowValueManager
{
public:
  void Init(UI::Window *pBaseWindow, bool bRecursive = false);
  void ResolveVariants(NNameMap::Map const *pMap);
  void Update();
private:
  void InitInternal(UI::Window *pBaseWindow, bool bRecursive = false);
  struct WndTooltip
  {
    WndTooltip() : pWnd(NULL) {}
    WndTooltip(WndTooltip const &a) : pWnd(a.pWnd) { Swap(pTooltip, (const_cast<WndTooltip&>(a)).pTooltip); }
    WndTooltip(UI::ImageLabel *pWnd, PrecompiledTooltip *pTooltip) : pWnd(pWnd), pTooltip(pTooltip) {};
    WndTooltip const &operator=(WndTooltip const &a) { pWnd = a.pWnd; Swap(pTooltip, (const_cast<WndTooltip &>(a)).pTooltip); return *this; }
    UI::ImageLabel              *pWnd;
    AutoPtr<PrecompiledTooltip> pTooltip;
  };
  vector<WndTooltip> m_items;
  bool               resolved;
  bool               changed;
};

}

#endif