#pragma once

#include "../UI/ScreenLogicBase.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{

class DynamicConsoleDumper;
_interface IFontStyle;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ConsoleLogic : public ScreenLogicBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( ConsoleLogic, ScreenLogicBase );

public:
	ConsoleLogic();
  virtual ~ConsoleLogic();

  virtual void OnLoadedScreenLayout();
  virtual void Step( float deltaTime );

  //Lua
	void GetPrevCommand();
	void GetNextCommand();
	void SetToLastCommand();
	void Scroll( int delta );
	void ScrollToLast();
	void AutoComplete( wstring cmd );

	void Show( bool show );

  void DrawText();

  //Logger
  void OnDump( NLogg::ELevel level, const char * text );
  void DumpLine( NLogg::ELevel level, const wchar_t * text, int length, float maxWidth );

  DECLARE_LUA_TYPEINFO(ConsoleLogic);
  DEFINE_LUA_PROPERTY(currentCommand, wstring, currentCommand);

private:
  void CheckFontStyle();

  struct SRecord
  {
    NLogg::ELevel   level;
    wstring         text;
    SRecord( NLogg::ELevel lvl = NLogg::LEVEL_UNDEFINED ) : level( lvl ) {}
  };

  typedef list<SRecord> TRecords;

	int currentCommandIndex;
	wstring currentCommand;

  StrongMT<DynamicConsoleDumper> dumper;

  TRecords  records;
  int scrollOffset;

  int minimalHeight;

  Weak<UI::IFontStyle> style;
  Weak<UI::Window> main;
  Weak<UI::Window> view;

  float consoleShowProgress;
  bool requiredVisibility;
};

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
