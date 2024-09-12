#include "stdafx.h"

//#include "System/NameMap.h"

#include "../UI/ImageLabel.h"
#include "../UI/Window.h"

#include "PrecompiledTooltips.h"

namespace
{
  /// This class parse tags if follow format
  /// <tagName=tagValue(tagValueParam1=1.0 tagValueParam2="abc") parameter1=value1 parameter2="value2">
  /// name  = tagName
  /// value = tagValue(tagValueParam1=1.0 tagValueParam2="abc")
  /// parameters
  class TextFragment : public NGameX::ITooltipFragment
  {
  public:
    virtual wchar_t const *Parse(wchar_t const *from, wchar_t const *to) { m_value = wstring(from, to - from); return to; }
    virtual wstring const &Value() { return m_value; }
    virtual bool HasChanged() { return false; }
    virtual bool ResolveVariants(NNameMap::Map const *) { return true; }
  protected:
    wstring m_value;
  };

  class ConcatFragment : public NGameX::ITooltipFragment
  {
  public:
    virtual wchar_t const * Parse(wchar_t const *from, wchar_t const *to);
    virtual bool ResolveVariants(NNameMap::Map const *pMap);
    virtual wstring const &Value();
    virtual bool HasChanged();
    virtual void AddParameter(NGameX::PrecompiledTooltipVariantParameters::Parameter const &parameter);
    virtual ~ConcatFragment();
  protected:
    vector<NGameX::PTooltipFragment> m_childs;
    wstring m_value;
  private:
    template <class T> wchar_t const *addFragment(wchar_t const *from, wchar_t const *to);

    wchar_t const *addValueTag(wchar_t const *from, wchar_t const *to);
    wchar_t const *readTextBeforeTag(wchar_t const *from);
  };

  class IfFragment : public NGameX::ITooltipFragment
  {
  public:
    IfFragment() : m_hasValue(false) {};

    virtual wchar_t const * Parse(wchar_t const *from, wchar_t const *to);
    virtual bool ResolveVariants(NNameMap::Map const *pMap);
    virtual wstring const &Value();
    virtual bool HasChanged();
    virtual void AddParameter(NGameX::PrecompiledTooltipVariantParameters::Parameter const &parameter);
protected:
    AutoPtr<ConcatFragment> m_if;
    AutoPtr<ConcatFragment> m_else;
    string                  m_condition;
    wstring                 m_empty;

    NGameX::PrecompiledTooltipVariantParameters m_parameters;

    CObj<NNameMap::ReadonlyVariant> m_ifValue;
    
    bool                    m_value;
    bool                    m_hasValue;
  };

  class ValueFragment : public NGameX::ITooltipFragment
  {
  public:
    ValueFragment() : m_hasValue(false) {}
    virtual wchar_t const *Parse(wchar_t const *from, wchar_t const *to);
    virtual bool ResolveVariants(NNameMap::Map const *pMap);
    virtual wstring const &Value();
    virtual bool HasChanged();
    virtual void AddParameter(NGameX::PrecompiledTooltipVariantParameters::Parameter const &parameter);
  protected:
    wstring m_value;
    string  m_formula;
    wstring m_format;

    NGameX::PrecompiledTooltipVariantParameters m_parameters;

    CObj<NNameMap::ReadonlyVariant> m_variant;

    bool    m_hasValue;
    float   m_floatValue;
    int     m_intValue;
    wstring m_wstrValue;
    string  m_strValue;

    char const *readFormulaName(const char *from, string &name);
    char const *readParameter(const char *from, string &name, string &value);
  };

  class JoinFragment : public NGameX::ITooltipFragment
  {
  public:
    JoinFragment() : m_value(L"@join@") {} //@todo Oleg
    virtual wchar_t const *Parse(wchar_t const *from, wchar_t const *to);
    virtual bool ResolveVariants(NNameMap::Map const *pMap);
    virtual wstring const &Value() { return m_value; }
    virtual bool HasChanged();
  protected:
    string  m_listName;
    string  m_separator;
    wstring m_format;
    wstring m_value;
  };

// -----------------------------------------------------------------------------

  wchar_t const *readTag(wchar_t const *from)
  {
    NI_VERIFY(*from == L'<', "readTag: Parse error '<'", return NULL);

    wchar_t const *ch = from;
    while (*ch != L'>')
    {
      ++ch;
      NI_VERIFY(*ch != L'<', "readTag: wrong syntax", return NULL);
      NI_VERIFY(*ch != 0, "readTag: unexpected end of text", return NULL);
    }
    ++ch; // Skip '>'
    return ch;
  }

  /// read: ' name=aa.bb.cc(qq.ww(ee, rr)) '
  wchar_t const *readProperty(wchar_t const *from, wstring &name, wstring &value)
  {
    wchar_t const *begin;
    wchar_t const *ch = from;

    // Read name
    while (*ch == L' ') // Skip Lead spaces
      ++ch;
    begin = ch;
    while (*ch != 0 && *ch !=L'>' && *ch != L'=' && *ch != L':' && *ch != L' ') //@todo isalpha
      ++ch;
    NI_VERIFY(ch != begin, "readProperty: Property name is empty", return NULL);
    name = wstring(begin, ch - begin);

    // Read =
    while (*ch != 0 && *ch != L'>' && *ch != L'=' && *ch != L':')
      ++ch;
    if (*ch != 0) // Skip '>' and '='
      ++ch;
    // Read value
    while (*ch == L' ') // Skip Lead spaces
      ++ch;

    begin = ch;

    int bracket = 0;
    while (!(bracket == 0 && *ch == L' ') && *ch != L'>' && *ch != 0)
    {
      if (*ch == L'(')
        bracket += 1;
      if (*ch == L')')
        bracket -= 1;
      NI_VERIFY(bracket >= 0, "readProperty: Wrong syntax", return NULL);
      ++ch;
    }
    NI_VERIFY(0 == bracket, "readProperty: Wrong syntax",   return NULL);
    NI_VERIFY(ch != begin,  "readProperty: Value is empty", return NULL);
    value = wstring(begin, ch - begin);

    return ch;
  }

  // '<  someTag=someValue  >' -> 'name = someTag'
  wchar_t const *readTagName(wchar_t const *from, wstring &name)
  {
    name.clear();

    NI_VERIFY(*from == L'<', "readTagName: First symbol must be '<'", return NULL);
    wchar_t const *ch = from + 1;
    while (*ch == L' ') // Skip lead spaces
      ++ch;

    wchar_t const *tagBegin = ch;

    while (*ch != L' ' && *ch != L':' && *ch != L'=' && *ch!=L'>')
    {
      ++ch;
      NI_VERIFY(*ch != 0, "readTagName: unexpected end of text", return NULL);
    }
    NI_VERIFY(ch != tagBegin, "readTagName: tag name is empty", return NULL);
    name = wstring(tagBegin, ch - tagBegin);

    return ch;
  }

//------------------------------------------------------------------------------

  wchar_t const *readTagOrBrackets(wchar_t const *from)
  {
    int counter = 0;

    wchar_t const *ch = from;
    NI_ASSERT(*ch == L'<' || *ch == L'(', "Wrong symbol");
    while (*ch != 0 && *ch != L'>' && (*ch != ')' || counter > 1))
    {
      if (*ch == L'(')
        ++counter;
      if (*ch == L')')
        --counter;
      ++ch;
    }
    NI_ASSERT(*ch != 0, "Wrong syntax");
    ++ch; // skip last symbol
    return ch;
  }

//------------------------------------------------------------------------------

  wchar_t const *readTagWithParameters(wchar_t const *from, wchar_t const *to, NGameX::PrecompiledTooltipVariantParameters &params)
  {
    wchar_t const *ch     = from + 1;
    wchar_t const *chLast = readTagOrBrackets(from);

    wstring name, value;

    params.rgPrms.clear();

    while (ch < chLast)
    {
      ch = readProperty(ch, name, value);
      NI_VERIFY(NULL != ch, "General parse error", return NULL);
      
      NGameX::PrecompiledTooltipVariantParameters::Parameter param;
      param.name = NStr::ToMBCS(name);
      param.value= NStr::ToMBCS(value);

      params.rgPrms.push_back(param);

      while ((ch < to) && ((*ch == L' ') || (*ch == L'>') || (*ch==L')'))) //Skip spaces and  e.t.c.
      {
        if ((*ch == L'>') || (*ch == L')')) //End of tag
        {
          ++ch;
          break;
        }
        ++ch;
      }
    }
    return ch;
 }

//------------------------------------------------------------------------------

  template <class T>
  wchar_t const *ConcatFragment::addFragment(wchar_t const *from, wchar_t const *to)
  {
    if (from == to) // Nothing to add
      return to;    

    T *pFragment = new T();
    wchar_t const * ch = pFragment->Parse(from, to);
    m_childs.push_back(pFragment);
    return ch;
  }

  wchar_t const *ConcatFragment::readTextBeforeTag(wchar_t const *from)
  {
    wchar_t const *ch = from;
    while (*ch != L'<' && *ch != 0)
      ++ch;
    return ch;
  }

  wchar_t const * ConcatFragment::Parse(wchar_t const *from, wchar_t const *to)
  {
    m_childs.clear(); /// Reset child list

    wchar_t const *ret       = NULL;
    wchar_t const *ch        = from;
    wchar_t const *textBegin = ch;

    bool skipCastleTagContent = false;

    while (ch < to)
    {
      ch = readTextBeforeTag(ch);
      NI_VERIFY(NULL != ch, "General parse error", return NULL);

      if (0 != *ch) // We have a tag
      {
        wchar_t const *tagBegin = ch;

        wstring tagName;
        ret = readTagName(tagBegin, tagName);
        NI_VERIFY(NULL != ret, "General parse error", return NULL);

        if ( skipCastleTagContent )
        {
          if ( tagName == L"/castle" )
            skipCastleTagContent = false;

          ch = readTag(tagBegin);
        }
        else
        {
          if (tagName == L"castle")
          {
            skipCastleTagContent = true;
            ch = readTag(tagBegin);
          }
          else if (tagName == L"value")
          {
            ret       = addFragment<TextFragment>(textBegin, ch);
            ch        = addFragment<ValueFragment>(tagBegin, to);
            textBegin = ch;

            NI_VERIFY(NULL != ch, "General parse error", return NULL);
          }
          else if (tagName == L"if")
          {
            ret       = addFragment<TextFragment>(textBegin, ch);
            ch        = addFragment<IfFragment>(tagBegin, to);
            textBegin = ch;

            NI_VERIFY(NULL != ret && NULL != ch, "General parse error", return NULL);
          }
          else if (tagName == L"else" || tagName == L"/if")
          {
            // Stop here
            addFragment<TextFragment>(textBegin, ch);
            return ch; // Tag begin
          }
          else if (tagName == L"join")
          {
            ret       = addFragment<TextFragment>(textBegin, ch);
            ch        = addFragment<JoinFragment>(tagBegin, to);
            textBegin = ch;

            NI_VERIFY(NULL != ch, "General parse error", return NULL);
          }
          else if (tagName == L"image")
          {
            // treat image tag content as plain text
            ch = ret;
          }
          else
          {
            //This is unknown tag, skip it for the next system
            ch = readTag(tagBegin);
            NI_VERIFY(NULL != ret && NULL != ch, "General parse error", return NULL);
          }
        }
      }
    }
    ret = addFragment<TextFragment>(textBegin, ch);
    NI_VERIFY(NULL != ch, "General parse error", return NULL);

    return to;
  }

  bool ConcatFragment::ResolveVariants(NNameMap::Map const *pMap)
  {
    bool bRet = true;

    for (int i = 0; i < m_childs.size(); ++i)
    {
      bRet = m_childs[i]->ResolveVariants(pMap) && bRet; // The order is important
    }

    return bRet;
  }

  wstring const& ConcatFragment::Value()
  {
    m_value.clear();

    for (int i = 0; i < m_childs.size(); ++i)
    {
      m_value += m_childs[i]->Value();
    }

    return m_value;
  }

  bool ConcatFragment::HasChanged()
  {
    for (int i = 0; i < m_childs.size(); ++i)
    {
      if (m_childs[i] && m_childs[i]->HasChanged())
        return true;
    }
    return false;
  }

  void ConcatFragment::AddParameter(NGameX::PrecompiledTooltipVariantParameters::Parameter const &parameter)
  {
    for (int i = 0; i < m_childs.size(); ++i)
    {
      m_childs[i]->AddParameter(parameter);
    }
  }

  ConcatFragment::~ConcatFragment()
  {
    for (int i = m_childs.size() - 1; i >= 0; --i)
    {
      delete m_childs[i];
    }
  }


  char const *ValueFragment::readFormulaName(const char *from, string &name)
  {
    char const *ch = from;
    while (*ch != '(' && *ch != 0)
    {
      ++ch;
    }
    name = string(from, ch);
    return ch;
  }

  char const *ValueFragment::readParameter(const char *from, string &name, string &value)
  {
    char const *ch = from;

    // Skip lead spaces
    while ((*ch == '(' || *ch == ' ' || *ch == ',') && *ch != 0)
    {
      ++ch;
    }
    char const *nameBegin = ch;
    while (*ch != 0 && *ch!=' ' && *ch != '=')
    {
      ++ch;
    }
    name = string(nameBegin, ch);
    
    // skip = and spaces
    while ((*ch == ' ' || *ch == '=') && *ch != 0)
    {
      ++ch;
    }
    char const *valueBegin = ch;
    while (*ch != 0 && *ch != ',' && *ch!= ' ' && *ch != ')')
      ch++;
    value = string(valueBegin, ch);

    return ch;
  }

  wchar_t const *ValueFragment::Parse(wchar_t const *from, wchar_t const *to)
  {
    wchar_t const *ch = from + 1;
    wchar_t const *chLast = readTag(from);

    wstring name, value;

    m_parameters.rgPrms.clear();

    while (ch < chLast)
    {
      ch = readProperty(ch, name, value);
      NI_VERIFY(NULL != ch, "General parse error", return NULL);

      if (name==L"value")
      {
        string formula = NStr::ToMBCS(value);
        char const * fCh = formula.begin();
        
        fCh = readFormulaName(fCh, m_formula);
        if ('(' == *fCh)
        {
          NGameX::PrecompiledTooltipVariantParameters::Parameter param;
          while (*fCh != ')' && *fCh != 0)
          {
            fCh = readParameter(fCh, param.name, param.value);
            m_parameters.rgPrms.push_back(param);
          }
        }
      }
      else if (name==L"format")
      {
        m_format  = value;
      }

      while ((ch < to) && ((*ch == L' ') || (*ch == L'>'))) //Skip spaces and  e.t.c.
      {
        if (*ch == L'>') //End of tag
        {
          ++ch;
          break;
        }
        ++ch;
      }
    }

    return ch;
  }

  bool ValueFragment::ResolveVariants(NNameMap::Map const *pMap)
  {
    NI_VERIFY(pMap, "ResolveVariants : invalid name map", return false);
    m_variant = pMap->GetVariant( m_formula.c_str(), reinterpret_cast<void*>(&m_parameters) );
    return m_variant != NULL;
  }

  wstring const &ValueFragment::Value()
  {
    if (m_formula.length() > 0)
    {
      if ( !m_variant )
      {
        m_value = NStr::ToUnicode(m_formula);//  L"#Name!#";
        return m_value;
      }

      switch (m_variant->GetType())
      {
      case NNameMap::VariantType::Float:
        m_floatValue  = m_variant->GetFloat();
        break;
      case NNameMap::VariantType::Int:
        m_intValue  = m_variant->GetInt();
        break;
      case NNameMap::VariantType::WString:
        m_wstrValue = m_variant->GetWString();
        break;
      case NNameMap::VariantType::String:
        m_strValue = m_variant->GetString();
        break;
      default:
        NI_ALWAYS_ASSERT("Unsupported value type");
      }
      m_hasValue = true;

      m_value    = m_variant->Format( m_format.c_str() );
    }

    return m_value;
  }

  bool ValueFragment::HasChanged()
  {
    if (NULL == m_variant)
      return false;
    if (!m_hasValue)
      return true;

    switch (m_variant->GetType())
    {
    case NNameMap::VariantType::Float:
      return m_variant->GetFloat() != m_floatValue;
    case NNameMap::VariantType::Int:
      return m_variant->GetInt() != m_intValue;
    case NNameMap::VariantType::WString:
      return 0 != NStr::WCmp(m_variant->GetWString(), m_wstrValue.c_str());
    case NNameMap::VariantType::String:
      return 0 != NStr::Cmp(m_variant->GetString(), m_strValue.c_str());
    default:
      NI_ALWAYS_ASSERT("Unsupported value type");
      return false;
    }
  }

  void ValueFragment::AddParameter(NGameX::PrecompiledTooltipVariantParameters::Parameter const &parameter)
  {
    for (int i = 0; i < m_parameters.rgPrms.size(); ++i)
    {
      if (parameter.name == m_parameters.rgPrms[i].name)
        return;
    }
    m_parameters.rgPrms.push_back(parameter);
  }

  wchar_t const *IfFragment::Parse(wchar_t const *from, wchar_t const *to)
  {
    wchar_t const *ret= NULL;
    wchar_t const *ch = from;

    wstring name, value;

    m_parameters.rgPrms.clear();

    ret = readProperty(ch + 1, name, value);
    NI_VERIFY(NULL != ret, "General parse error", return NULL);
    m_condition = NStr::ToMBCS(value);

    NI_VERIFY(name == L"if", "IfFragment::Parse : Wrong syntax", return NULL);
    ch = readTag(ch);
    NI_VERIFY(NULL != ch, "General parse error", return NULL);

    {
      AutoPtr<ConcatFragment> tmpFragment(new ConcatFragment());
      Swap(m_if, tmpFragment);

      ch = m_if->Parse(ch, to);
      NI_VERIFY(NULL != ch, "General parse error", return NULL);
    }
    NI_VERIFY(*ch == L'<', "IfFragment::Parse : Expected '<'", return NULL);

    wstring tagName;
    ret = readTagName(ch, tagName);
    ch  = readTag(ch);
    NI_VERIFY(NULL != ret && NULL != ch, "General parse error", return NULL);
    
    if (L"else" == tagName)
    {
      AutoPtr<ConcatFragment> tmpFragment(new ConcatFragment());
      Swap(m_else, tmpFragment);

      ch = m_else->Parse(ch, to);
      NI_VERIFY(NULL != ch, "General parse error", return NULL);

      ret = readTagName(ch, tagName);
      ch  = readTag(ch);
      NI_VERIFY(NULL != ret && NULL != ch, "General parse error", return NULL);
    }
    else // Clear else statement if is
    {
      AutoPtr<ConcatFragment> tmpFragment(NULL);
      Swap(m_else, tmpFragment);
    }

    NI_VERIFY(L"/if" == tagName, "IfFragment::Parse : Expected '</if>'", return NULL);

    return ch;
  }

  bool IfFragment::ResolveVariants(NNameMap::Map const *pMap)
  {
    NI_VERIFY(pMap, "ResolveVariants : invalid name map", return false);
    m_ifValue   = pMap->GetVariant(m_condition.c_str(), reinterpret_cast<void*>(&m_parameters));
    bool allowedResolve = IsValid(m_ifValue) 
      && ( m_ifValue->GetType() == NNameMap::VariantType::Bool
        || m_ifValue->GetType() == NNameMap::VariantType::Int
        || m_ifValue->GetType() == NNameMap::VariantType::Float );
    NI_VERIFY(allowedResolve, NStr::StrFmt("Wrong variant: %s",m_condition.c_str()), return false);
    if (NULL != Get(m_if))
      m_if->ResolveVariants(pMap);
    if (NULL != Get(m_else))
      m_else->ResolveVariants(pMap);
    return true;
  }

  wstring const &IfFragment::Value()
  {
    if (m_condition.length() > 0) // If condition is non-empty string
    {
      if (m_ifValue != NULL )
      {        
        if ( m_ifValue->GetType() == NNameMap::VariantType::Bool )
          m_value = m_ifValue->GetBool();
        else if ( m_ifValue->GetType() == NNameMap::VariantType::Float )
          m_value = m_ifValue->GetFloat() != 0.0f;
        else if ( m_ifValue->GetType() == NNameMap::VariantType::Int )
          m_value = m_ifValue->GetInt() != 0;
        else
          return m_empty;

        m_hasValue = true;

        if (m_value && Get(m_if))
          return m_if->Value();
        if (!m_value && Get(m_else))
          return m_else->Value();
      }
    }

    return m_empty;
  }

  bool IfFragment::HasChanged()
  {
    NI_VERIFY(m_condition.length() > 0, "Wrong condition", return false); // Not changed
    NI_VERIFY(IsValid(m_ifValue), "Wrong variant", return false);

    bool bCond    = m_ifValue->GetBool();

    bool bChanged = (bCond ^ m_value) || (!m_hasValue);
    
    if (m_if)
      bChanged = bChanged || m_if->HasChanged();
    if (m_else)
      bChanged = bChanged || m_else->HasChanged();

    return bChanged;
  }

  void IfFragment::AddParameter(NGameX::PrecompiledTooltipVariantParameters::Parameter const &parameter)
  {
    for (int i = 0; i < m_parameters.rgPrms.size(); ++i)
    {
      if (parameter.name == m_parameters.rgPrms[i].name)
        return;
    }
    m_parameters.rgPrms.push_back(parameter);

    if (NULL != Get(m_if))
    {
      m_if->AddParameter(parameter);
    }
    if (NULL != Get(m_else))
    {
      m_else->AddParameter(parameter);
    }
  }

  wchar_t const * JoinFragment::Parse(wchar_t const *from, wchar_t const *to)
  {
    NGameX::PrecompiledTooltipVariantParameters params;
    
    wchar_t const * ch = readTagWithParameters(from, to, params);
    NI_ASSERT(params.rgPrms.size() > 0, "Wrong tag");
    NI_ASSERT(params.rgPrms[0].name == "join", "Wrong tag name");    

    m_listName = params.rgPrms[0].value;
    for (int i = 1, size = params.rgPrms.size(); i < size; ++i )
    {
      if ("separator" == params.rgPrms[i].name)
        m_separator = params.rgPrms[i].value;
    }
    
    return ch;
  }

  bool JoinFragment::ResolveVariants(NNameMap::Map const *pMap)
  {
    //@todo Oleg
    return true;
  }

  bool JoinFragment::HasChanged()
  {
    return false;
  };
}

namespace NGameX
{

PrecompiledTooltip::PrecompiledTooltip()
  : m_tooltip(NULL)
{
}

PrecompiledTooltip::~PrecompiledTooltip()
{
}

bool PrecompiledTooltip::Init( const NNameMap::Map * pMap, const wstring & str, UI::ICustomSubstitutes * customSubst )
{
  wstring buffer;
  UI::SubstituteText( buffer, str.c_str(), customSubst );

  AutoPtr<ITooltipFragment> tempPtr(new ConcatFragment());
  Swap(m_tooltip, tempPtr);

  wchar_t const * pRes = m_tooltip->Parse( buffer.begin(), buffer.end() );
  
  if ( pRes != buffer.end() ) // Unable to parse tooltips
  {
    //@todo [Oleg] We need to do something if parse failed
    return false;
  }

  m_tooltip->ResolveVariants(pMap);

  return true;
}

void PrecompiledTooltip::MakeText(wstring &sout) const
{
  if (Get(m_tooltip))
    sout = m_tooltip->Value();
  else
    sout.clear();
}

bool PrecompiledTooltip::HasChanged() const 
{ 
  if (Get(m_tooltip))
  {
    return m_tooltip->HasChanged();
  }
  return false; 
}

bool PrecompiledTooltip::Parse(wstring const &str)
{
  wstring buffer;
  UI::SubstituteText( buffer, str.c_str() );

  AutoPtr<ITooltipFragment> tempPtr(new ConcatFragment());
  Swap(m_tooltip, tempPtr);

  wchar_t const * pRes = m_tooltip->Parse( buffer.begin(), buffer.end() );

  if ( pRes != buffer.end() ) // Unable to parse tooltips
  {
    //@todo [Oleg] We need to do something if parse failed
    return false;
  }

  return true;
}

bool PrecompiledTooltip::ResolveVariants(NNameMap::Map const *pMap)
{
  if (Get(m_tooltip))
    return m_tooltip->ResolveVariants(pMap);

  return false;
}

void PrecompiledTooltip::AddParameter(PrecompiledTooltipVariantParameters::Parameter const &parameter)
{
  if (Get(m_tooltip))
    m_tooltip->AddParameter(parameter);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void WindowValueManager::InitInternal(UI::Window *pBaseWindow, bool bRecursive /*= false*/)
{
  for (int i = 0, count = pBaseWindow->GetChildrenCount(); i < count; ++i)
  {
    UI::Window *pWindow = pBaseWindow->GetChild(i);
    if (bRecursive && pWindow)
      InitInternal(pWindow, bRecursive);
    UI::ImageLabel *pImageLabel = dynamic_cast<UI::ImageLabel*>(pWindow);
    if (NULL == pImageLabel)
      continue;
    wstring const &text = pImageLabel->GetCaptionTextW();
    if (wcsstr(text.c_str(), L"<value") != NULL)
    {
      WndTooltip pTooltip(pImageLabel, new PrecompiledTooltip());
      pTooltip.pTooltip->Parse(text);
      m_items.push_back(pTooltip);
    }
  }
}

void WindowValueManager::Init(UI::Window *pBaseWindow, bool bRecursive /*= false*/)
{
  m_items.clear();

  if (UI::ImageLabel *pImageLabel = dynamic_cast<UI::ImageLabel*>(pBaseWindow))
  {
    wstring const &text = pImageLabel->GetCaptionTextW();
    if (wcsstr(text.c_str(), L"<value") != NULL)
    {
      WndTooltip pTooltip(pImageLabel, new PrecompiledTooltip());
      pTooltip.pTooltip->Parse(text);
      m_items.push_back(pTooltip);
    }
  }

  InitInternal(pBaseWindow, bRecursive);

  resolved = false;
  changed  = false;
}

void WindowValueManager::ResolveVariants(NNameMap::Map const *pMap)
{
  for (int i = 0, count = m_items.size(); i < count; ++i)
  {
    m_items[i].pTooltip->ResolveVariants(pMap);
  }
  resolved = true;
  changed  = true;
}

void WindowValueManager::Update()
{
  if (!resolved)
    return;
  for (int i = 0, count = m_items.size(); i < count; ++i)
  {
    if (changed)
    {
      wstring text;
      m_items[i].pTooltip->MakeText(text);
      m_items[i].pWnd->SetCaptionTextW(text);
    }
    else
    {
      if ( m_items[i].pWnd->IsVisible() )
        if (m_items[i].pTooltip->HasChanged())
        {
          wstring text;
          m_items[i].pTooltip->MakeText(text);
          m_items[i].pWnd->SetCaptionTextW(text);
        }
    }
  }
  changed = false;
}

}