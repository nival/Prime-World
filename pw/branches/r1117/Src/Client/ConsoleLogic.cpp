#include "stdafx.h"
#include "ConsoleLogic.h"

#include "../UI/Window.h"

#include "../System/Dumper.h"
#include "../System/Logger.h"
#include "../System/SystemLog.h"

#include "../UI/FontRender.h"
#include "../UI/SkinStyles.h"

#include "MainTimer.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DynamicConsoleDumper : public NLogg::CDumper
{
public:
  DynamicConsoleDumper( NLogg::CLogger * logger ) :
  NLogg::CDumper( logger, "console" )
  {
  }

  virtual void OnDump( const NLogg::SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly )
  {
    threading::MutexLock lock( mutex );
    if ( queue.size() < 256 ) //Hardlimit the message queue length
      queue.push_back( SItem( entryInfo.level, textOnly ) );
  }

  bool PopMessage( NLogg::ELevel & level, string & message )
  {
    threading::MutexLock lock( mutex );

    if ( queue.empty() )
      return false;

    level = queue.front().level;
    message = queue.front().message;
    queue.pop_front();
    //FIXME: Тут можно было бы сэкономить аллокацию, разделив операции чтения из очереди
    //и удаления элемента из нее. Но это более рисовый вариант..
    return true;
  }

private:
  struct SItem
  {
    NLogg::ELevel level;
    string  message;
    SItem( NLogg::ELevel lvl, const char * msg ) : level( lvl), message( msg ) {}
  };
  threading::Mutex mutex;
  list<SItem> queue;
};








static int s_consoleLinesLimit = 100;
REGISTER_VAR_PRED( "console_limit", s_consoleLinesLimit, STORAGE_USER, NGlobal::MakeMinMaxVerifyPred(5, 1000) );

static float s_consoleSize = 0.5f;
REGISTER_VAR_PRED( "console_size", s_consoleSize, STORAGE_USER, NGlobal::MakeMinMaxVerifyPred(0.1f, 0.8f) );

static float s_consoleOpacity = 0.4f;
REGISTER_VAR_PRED( "console_opacity", s_consoleOpacity, STORAGE_USER, NGlobal::MakeMinMaxVerifyPred(0.1f, 1.0f) );

static bool s_consolePeep = 0;
REGISTER_VAR( "console_peep", s_consolePeep, STORAGE_USER );

static float s_consoleSweepTime = 0.25f;
REGISTER_VAR( "console_sweep_time", s_consoleSweepTime, STORAGE_USER );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_LUA_TYPEINFO(ConsoleLogic, ScreenLogicBase)
  LUA_METHOD(GetPrevCommand)
  LUA_METHOD(GetNextCommand)
  LUA_METHOD(SetToLastCommand)
  LUA_METHOD(Scroll)
  LUA_METHOD(ScrollToLast)
  LUA_METHOD(AutoComplete)
  LUA_PROPERTY(currentCommand)
END_LUA_TYPEINFO(ConsoleLogic)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ConsoleLogic::ConsoleLogic() :
currentCommandIndex( -1 ),
scrollOffset( 0 ),
minimalHeight( 0 ),
consoleShowProgress( 0 ),
requiredVisibility( false )
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ConsoleLogic::~ConsoleLogic()
{
  if ( dumper )
  {
    GetSystemLog().RemoveDumper( dumper );
    dumper = 0;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsoleLogic::CheckFontStyle()
{
  if ( !style.Valid() )
    style = UI::GetFontRenderer()->GetFontStyle( UI::SkinStyles::GetFontStyle( "console" ) );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsoleLogic::OnLoadedScreenLayout()
{
  style = UI::GetFontRenderer()->GetFontStyle( UI::SkinStyles::GetFontStyle( "console" ) );

  main = UI::GetChildChecked<UI::Window>( pBaseWindow, "Main", true );
  view = UI::GetChildChecked<UI::Window>( pBaseWindow, "View", true );
  UI::Window * input = UI::GetChildChecked<UI::Window>( pBaseWindow, "Input", true );

  NI_ASSERT( main && view && input, "Console windows not found!" );

  minimalHeight = input->GetSize().y * 2;

  NI_ASSERT( !dumper, "" );
  dumper = new DynamicConsoleDumper( &GetSystemLog() );

  pBaseWindow->Show( requiredVisibility );

  UI::ScreenLogicBase::OnLoadedScreenLayout();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsoleLogic::Step( float deltaTime )
{
	if ( !pBaseWindow || !main || !view )
		return;

  for ( int i = 0; i < 32; ++i ) //Hardlimit messages count
  {
    NLogg::ELevel level = NLogg::LEVEL_UNDEFINED;
    string message;
    if ( dumper->PopMessage( level, message ) )
      OnDump( level, message.c_str() );
    else
      break;
  }

  //Static opacity
  view->SetOpacity( s_consoleOpacity );

  //Process static console resize
  const int scrHeight = pBaseWindow->GetSize().y;
  int newHeight = Clamp( (int)( scrHeight * s_consoleSize ), minimalHeight, scrHeight );
  newHeight;
  main->SetSize( -1, newHeight, false );

  float timeScale = NMainLoop::GetTimeScale() > 0 ? NMainLoop::GetTimeScale() : 1.0f;

  //Process console sweep
  float newProgress = consoleShowProgress + ( requiredVisibility ? 1.0f : -1.0f ) * ( s_consoleSweepTime ? deltaTime / (s_consoleSweepTime * timeScale): 1.0f );

  newProgress = Clamp( newProgress, 0.0f, 1.0f );

  if ( newProgress != consoleShowProgress )
  {
    consoleShowProgress = newProgress;
    pBaseWindow->Show( consoleShowProgress > 0 ? true : false );
    main->SetLocation( 0, s_consolePeep ? 0 : (int)( newHeight * ( consoleShowProgress - 1.0f ) ) );
  }

  //opacity
  main->SetOpacity( s_consolePeep ? consoleShowProgress : 1.0f );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsoleLogic::GetPrevCommand()
{
	currentCommandIndex = Max( currentCommandIndex + 1, 0 );
	currentCommand = NGlobal::GetCommandHistory( currentCommandIndex );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsoleLogic::GetNextCommand()
{
	currentCommandIndex = Max( currentCommandIndex - 1, -1 );
	currentCommand = currentCommandIndex >= 0 ? NGlobal::GetCommandHistory( currentCommandIndex ) : L"";
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsoleLogic::SetToLastCommand()
{
	currentCommandIndex = -1;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsoleLogic::Scroll( int delta )
{
	scrollOffset += delta;

  scrollOffset = Min( scrollOffset, records.size() - 1 );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsoleLogic::ScrollToLast()
{
	scrollOffset = 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsoleLogic::AutoComplete( wstring cmd )
{
	NStr::TrimRight( cmd );

	vector<wstring> matches; 
	NGlobal::MatchCommands( &matches, cmd );

	if ( matches.empty() )
	{
		currentCommand = cmd;	
		return;
	}

	if ( matches.size() == 1 )
	{
		currentCommand = matches.front() + L" ";
		return;
	}

	sort( matches.begin(), matches.end() );

  systemLog( NLogg::LEVEL_MESSAGE ) << "Commands( " << matches.size() << " ):";

	wstring wsSamePart( matches.front() );

	for ( vector<wstring>::const_iterator it = matches.begin(); it != matches.end(); it++ )
	{
		// determine common part of all listed commands
		wstring wsNewSame( wsSamePart );
		for ( int i = 0; i < Min( it->length(), wsSamePart.length() ); i++ )
		{
			if ( (*it)[i] == wsSamePart[i] )
				continue;

			wsNewSame = wsSamePart.substr( 0, i );
			break;
		}
		wsSamePart = wsNewSame;

		string szVar = NStr::ToMBCS( *it );

		systemLog( NLogg::LEVEL_MESSAGE ) << "    ";
		NGlobal::PrintVarWithValue( szVar );
	}

	currentCommand = wsSamePart;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsoleLogic::Show( bool show )
{
  requiredVisibility = show;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsoleLogic::DrawText()
{
  CheckFontStyle();

  if ( !view || !style )
    return;

  Rect rect = view->GetWindowRect();

  if ( s_consolePeep )
    rect.Set( 0, 0, rect.GetSizeX(), rect.GetSizeY() );
  else
    if ( !main->IsFullyVisible() )
      return;

  float lineHeight = style->GetMetric().RowStep();

  const float minOffs = rect.top - 1e-4f;
  float offs = rect.bottom - lineHeight;

  TRecords::iterator it = records.begin();
  for ( int i = 0; i < scrollOffset; ++i )
    if ( it != records.end() )
      ++it;

  for ( ; ( it != records.end() ) && ( offs >= minOffs ); ++it )
  {
    static Render::HDRColor normalClr( 1, 1, 1, 1 );
    static Render::HDRColor debugClr( 0.0, 1.0, 1.0f, 1 );
    static Render::HDRColor warningClr( 1, 1, 0, 1 );
    static Render::HDRColor assertClr( 1, 0, 0, 1 );
    static Render::HDRColor critClr( 1, 0, 1, 1 );

    const Render::HDRColor * color = &normalClr;
    if ( it->level == NLogg::LEVEL_DEBUG )
      color = &debugClr;
    else if ( it->level == NLogg::LEVEL_WARNING )
      color = &warningClr;
    else if ( it->level == NLogg::LEVEL_ASSERT )
      color = &assertClr;
    else if ( it->level == NLogg::LEVEL_CRITICAL )
      color = &critClr;

    style->DrawString( it->text.c_str(), it->text.length(), rect.left, offs, *color, UI::GetFontRenderer()->GetNoCropRect() );
    offs -= lineHeight;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsoleLogic::OnDump( NLogg::ELevel level, const char * text )
{
  CheckFontStyle();

  if ( !view || !style )
    return;

  NI_ASSERT( style->GetAlphabet(), "" );

  Point size = view->GetSize();

  wstring buff;
  NStr::ToUnicode( &buff, string( text ) );

  int from = 0, i = 0;
  while( i < buff.size() )
  {
    //We search line endings
    int newLnSize = 0;
    if ( ( i + 1 < buff.size() ) && buff[i] == L'\r' && buff[i + 1] == L'\n' )
      newLnSize = 2;
    else if ( buff[i] == L'\r' || buff[i] == L'\n' )
      newLnSize = 1;

    if ( newLnSize )
    {
      DumpLine( level, buff.c_str() + from, i - from, (float)size.x );
      i += newLnSize;
      from = i;
      continue;
    }

    //If this is the last char
    if ( i + 1 >= buff.size() )
    {
      DumpLine( level, buff.c_str() + from, buff.size() - from, (float)size.x );
      break;
    }

    ++i;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsoleLogic::DumpLine( NLogg::ELevel level, const wchar_t * text, int length, float maxWidth )
{
  CheckFontStyle();

  while ( true )
  {
    unsigned charsFit = 0;
    style->GetAlphabet()->GetStringLength( text, length, maxWidth, &charsFit, SFontRenderTweaks() );

    if ( records.size() >= s_consoleLinesLimit )
      records.pop_back();

    records.push_front( SRecord( level ) );
    records.front().text.assign( text, charsFit );

    length -= (int)charsFit;
    text += charsFit;

    if ( length <= 0 )
      break;
  }
}

} //namespace UI
