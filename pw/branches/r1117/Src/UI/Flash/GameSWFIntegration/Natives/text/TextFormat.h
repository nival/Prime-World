 #pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"

namespace avmplus
{
class ArrayObject;


class TextFormatObject: public ScriptObject
{
public:
  TextFormatObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) , 
    fontSize(12),
    bold(false),
    italic(false),
    underline(false)
  {}
  ~TextFormatObject(void) {}


  AvmBox get_size()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "get_size" );
    return (AvmBox)0;
  }

  AvmBox get_bullet()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "get_bullet" );
    return (AvmBox)0;
  }

  void set_bullet(AvmBox value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "set_bullet" );
    return (void)0;
  }

  AvmString get_align()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "get_align" );
    return (AvmString)0;
  }

  void set_color(AvmBox value)
  {
    //NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "set_color" );
    return (void)0;
  }

  AvmString get_display()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "get_display" );
    return (AvmString)0;
  }

  void set_bold(AvmBox value)
  {
    bold = (avmplus::AtomConstants::trueAtom == value);
  }

  void set_display(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "set_display" );
    return (void)0;
  }

  AvmBox get_bold()
  {
    return bold ? avmplus::AtomConstants::trueAtom : avmplus::AtomConstants::falseAtom;
  }

  AvmBox get_leading()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "get_leading" );
    return (AvmBox)0;
  }

  AvmString get_font()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "get_font" );
    return (AvmString)0;
  }

  void set_align(AvmString value)
  {
//    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "set_align" );
//    return (void)0;
  }

  void set_leading(AvmBox value)
  {
//     NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "set_leading" );
//     return (void)0;
  }

  void set_rightMargin(AvmBox value)
  {
//     NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "set_rightMargin" );
//     return (void)0;
  }

  AvmBox get_leftMargin()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "get_leftMargin" );
    return (AvmBox)0;
  }

  void set_indent(AvmBox value)
  {
//     NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "set_indent" );
//     return (void)0;
  }

  AvmBox get_blockIndent()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "get_blockIndent" );
    return (AvmBox)0;
  }

  int GetSize()
  {
    return fontSize;
  }

  void set_size(AvmBox value)
  {
    if (core()->isNullOrUndefined(value))
    {
      fontSize = 12;
      return;
    }

    fontSize = core()->integer(value);
  }

  AvmBox get_kerning()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "get_kerning" );
    return (AvmBox)0;
  }

  ArrayObject* get_tabStops()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "get_tabStops" );
    return (ArrayObject*)0;
  }

  void set_font(AvmString value)
  {
    //NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "set_font" );
  }

  void set_kerning(AvmBox value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "set_kerning" );
    return (void)0;
  }

  void set_italic(AvmBox value)
  {
    italic = (avmplus::AtomConstants::trueAtom == value);
  }

  void set_target(AvmString value)
  {
    target = value;
  }

  AvmBox get_color()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "get_color" );
    return (AvmBox)0;
  }

  AvmBox get_underline()
  {
    return underline ? avmplus::AtomConstants::trueAtom : avmplus::AtomConstants::falseAtom;
  }

  void set_url(AvmString value)
  {
    url = value;
  }

  void set_underline(AvmBox value)
  {
    underline = (avmplus::AtomConstants::trueAtom == value);
  }

  AvmString get_target()
  {
    return target;
  }

  void set_leftMargin(AvmBox value)
  {
    //NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "set_leftMargin" );
    //return (void)0;
  }

  AvmBox get_indent()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "get_indent" );
    return (AvmBox)0;
  }

  AvmString get_url()
  {
    return url;
  }

  AvmBox get_italic()
  {
    return italic ? avmplus::AtomConstants::trueAtom : avmplus::AtomConstants::falseAtom;
  }

  AvmBox get_rightMargin()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "get_rightMargin" );
    return (AvmBox)0;
  }

  void set_blockIndent(AvmBox value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "set_blockIndent" );
    return (void)0;
  }

  void set_tabStops(ArrayObject* value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "set_tabStops" );
    return (void)0;
  }

  void set_letterSpacing(AvmBox value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "set_letterSpacing" );
    return (void)0;
  }

  AvmBox get_letterSpacing()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFormatObject", "get_letterSpacing" );
    return (AvmBox)0;
  }


private:
  DECLARE_SLOTS_TextFormatObject;

  int fontSize;

  bool bold;
  bool italic;
  bool underline;

  DRCWB(AvmString) url;
  DRCWB(AvmString) target;
};
  
class TextFormatClass : public ClassClosure
{
public:
  TextFormatClass(VTable *vtable): ClassClosure(vtable){}
  ~TextFormatClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) TextFormatObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_TextFormatClass;

};

}