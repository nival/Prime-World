#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"
#include "../display/DisplayObject.h"


namespace flash
{
  class StaticTextTagData;
  _interface IFontInstance;
}


namespace avmplus
{

class StaticTextObject : public DisplayObjectObject
{
public:
  //FIX args
  StaticTextObject( StaticTextClass * classType );
  StaticTextObject( VTable * ivtable, ScriptObject * delegate );

  ~StaticTextObject() {}

  AvmString get_text()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "StaticTextObject", "get_text" );
    return (AvmString)0;
  }

  void SetData( flash::StaticTextTagData * _data );

  virtual const char* GetDumpName() { return "<StaticText>"; }

private:
  DECLARE_SLOTS_StaticTextObject;

  void InitializeStaticText();

  virtual void DoRender( Render::IFlashRenderer * _renderer, const flash::SWF_MATRIX & _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum _worldMode );
  virtual void GetBounds( flash::SWF_RECT& _rect );

  Strong<flash::StaticTextTagData>  data;
  vector<Strong<flash::IFontInstance>>  cachedFonts; //One for each STextTag_TEXTRECORD
};


DECLARE_AS_CLASS_WITH_CACHE( StaticTextClass, ClassClosure, StaticTextObject );

} //namespace avmplus
