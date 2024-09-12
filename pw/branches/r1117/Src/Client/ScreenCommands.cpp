#include "stdafx.h"
#include "ScreenCommands.h"
#include "MainLoop.h"
#include "UI/Root.h"
#include "System/InlineProfiler.h"

#include <float.h>

namespace NMainLoop
{
	TScreenList &GetScreens();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScreenCommands
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef hash_map<string, CreateFun> ScreenFactory;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static ScreenFactory& GetScreenFactory()
{
  static ScreenFactory screenFactory;

  return screenFactory;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RegisterInScreensFactory(const string& name, CreateFun fn)
{
  GetScreenFactory()[name] = fn;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NMainLoop::IScreenBase* CreateScreen(const string& name)
{
  hash_map<string, CreateFun>::iterator found = GetScreenFactory().find(name);
  if(found != GetScreenFactory().end())
    return found->second();

  if(GetScreenFactory().size())
    return GetScreenFactory().begin()->second();

  return 0;
}
NMainLoop::IScreenBase* FindScreen(const string& name)
{
  for ( TScreenList::iterator it = NMainLoop::GetScreens().begin(); it != NMainLoop::GetScreens().end(); ++it)
  {
    if( (*it)->ClassName() == name )
      return *it;
  }

  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//стеки команд на добавление/удаление интерфейсов
static TScreenCommandsList g_commandsOdd;
static TScreenCommandsList g_commandsEven;
static bool g_bUseOddCommands = true;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClearCommands()
{
  g_commandsOdd.clear();
  g_commandsEven.clear();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Возвращение текущего стека команд
TScreenCommandsList &GetScreenCmds()
{
  if ( g_bUseOddCommands )
  {
    return g_commandsEven;
  }
  return g_commandsOdd;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Возвращение следующего стека команд
TScreenCommandsList &GetNextScreenCmds()
{
  if ( !g_bUseOddCommands )
  {
    return g_commandsEven;
  }
  return g_commandsOdd;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PushScreenCommand
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PushScreenCommand : public IScreenCommand
{
  NI_DECLARE_REFCOUNT_CLASS_1( PushScreenCommand, IScreenCommand )

  ZDATA
  Strong<NMainLoop::IScreenBase> pScreen;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&pScreen); return 0; }

private:
  virtual void Exec()
  {
    NMainLoop::EScreenLayer::Enum layer = pScreen->GetScreenLayer();
    TScreenList::iterator insertBefore = NMainLoop::GetScreens().end();
    for ( TScreenList::iterator it = NMainLoop::GetScreens().begin(); it != NMainLoop::GetScreens().end(); ++it )
    {
      if ( *it == pScreen )
        return;
      if( insertBefore == NMainLoop::GetScreens().end() )
        if( (*it)->GetScreenLayer() <= layer )
          insertBefore = it;
    }

    if( insertBefore != NMainLoop::GetScreens().end() )
      NMainLoop::GetScreens().insert( insertBefore, pScreen );
    else
      NMainLoop::GetScreens().push_back( pScreen );
  }
  virtual bool Prepare()
  {
    NI_PROFILE_FUNCTION

    if ( !IsValid( pScreen ) )
    {
      return false;
    }
    for ( TScreenList::iterator it = NMainLoop::GetScreens().begin(); it != NMainLoop::GetScreens().end(); ++it)
    {
      if ( *it == pScreen )
      {
        return false;
      }
    }

    {
      NI_PROFILE_BLOCK_MEM( "Init" )
      if ( !pScreen->Init( UI::GetUser() ) )
        return false;
      if( !NMainLoop::GetScreens().empty() )
        NMainLoop::GetScreens().front()->OnBeforeAddTopScreen( pScreen );
    }
    return true;
  }
public:
  PushScreenCommand() {}
  PushScreenCommand( NMainLoop::IScreenBase * _pScreen ) : pScreen( _pScreen )
  {
    //int i = 0;
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PushScreenCommand
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IScreenCommand *CreatePushScreenCommand( NMainLoop::IScreenBase *pScreenToPush )
{  
  return new PushScreenCommand( pScreenToPush );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PopScreenCommand
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PopScreenCommand: public IScreenCommand
{
  NI_DECLARE_REFCOUNT_CLASS_1( PopScreenCommand, IScreenCommand );
  ZDATA
    Weak<NMainLoop::IScreenBase> pScreen;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&pScreen); return 0; }
private:
  virtual void Exec()
  {
    if ( !IsValid( pScreen ) )
    {
      return;
    }
    for ( TScreenList::iterator it = NMainLoop::GetScreens().begin(); it != NMainLoop::GetScreens().end(); )
    {
      if ( *it != pScreen )
        ++it;
      else
      {
        it = NMainLoop::GetScreens().erase( it );
        break;
      }
    }
  }
  virtual bool Prepare()
  {
    if ( IsValid( pScreen ) )
    {
      for ( TScreenList::iterator it = NMainLoop::GetScreens().begin(); it != NMainLoop::GetScreens().end(); )
      {
        if ( *it != pScreen )
          ++it;
        else
        {
          return pScreen->OnBeforeClose();
        }
      }
    }
    return true;
  }
public:
  PopScreenCommand() {}
  PopScreenCommand( NMainLoop::IScreenBase * _pScreen ) : pScreen( _pScreen )
  {
  }
  PopScreenCommand( const string& _screenName )  
  {
    pScreen = FindScreen(_screenName);
    NI_ASSERT(pScreen, NStr::StrFmt("Screen of type: (%s) is not found in screens stack",_screenName));
  }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IScreenCommand *CreatePopScreenCommand( NMainLoop::IScreenBase *pScreenToPop )
{  
  return new PopScreenCommand( pScreenToPop );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IScreenCommand *CreatePopScreenCommand( const string& screenToPopName )
{
  return new PopScreenCommand( screenToPopName );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PopScreenCommand
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ClearStackCommand: public IScreenCommand
{
  NI_DECLARE_REFCOUNT_CLASS_1( ClearStackCommand, IScreenCommand );
  ZDATA
    Weak<NMainLoop::IScreenBase> pStopScreen;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&pStopScreen); return 0; }
private:
  virtual void Exec()
  {
    for ( TScreenList::iterator it = NMainLoop::GetScreens().begin(); it != NMainLoop::GetScreens().end(); )
    {
      if ( *it == pStopScreen )
        break;

      it = NMainLoop::GetScreens().erase( it );
    }
  }

  virtual bool Prepare()
  {
    for ( TScreenList::iterator it = NMainLoop::GetScreens().begin(); it != NMainLoop::GetScreens().end(); ++it )
    {
      if ( !(*it)->OnBeforeClose() )
      {
        pStopScreen = *it;
        break;
      }
    }

    return true;
  }
public:
  ClearStackCommand() {}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IScreenCommand *CreateClearStackCommand()
{
  return new ClearStackCommand();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ProcessScreenCmds()
{
  NI_PROFILE_FUNCTION

  for ( TScreenCommandsList::iterator it = GetScreenCmds().begin(); it != GetScreenCmds().end(); ++it )
  {
    (*it)->Exec();
  }

  GetScreenCmds().clear();
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AnalizeScreenCmds()
{
  NI_PROFILE_FUNCTION

  //Переключение стека команд
  g_bUseOddCommands = !g_bUseOddCommands;
  for ( TScreenCommandsList::iterator it = GetScreenCmds().begin(); it !=GetScreenCmds().end(); )
  {
    if ( (*it)->Prepare() )
      ++it;
    else
      it = GetScreenCmds().erase( it );
  }
  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PushCommand( IScreenCommand *pCommand )
{
  GetNextScreenCmds().push_back( pCommand );
}

} //namespace NScreenCommands
