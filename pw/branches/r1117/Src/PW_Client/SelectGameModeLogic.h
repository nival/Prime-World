#pragma once

#include "Client/ScreenUILogicBase.h"

namespace NGameX
{
  class SelectGameModeScreen;
}

namespace lobby
{
  struct SDevGameInfo;

  namespace EOperationResult { enum Enum; }
}


namespace UI
{
  class SelectGameModeLogic : public ClientScreenUILogicBase
  {
  private:
    NI_DECLARE_REFCOUNT_CLASS_1( SelectGameModeLogic, ClientScreenUILogicBase );
    DECLARE_LUA_TYPEINFO( SelectGameModeLogic );

    Weak<NGameX::SelectGameModeScreen> screen;
    string  joinMode;
   
  public:
    SelectGameModeLogic() {}
    void SetScreen( NGameX::SelectGameModeScreen * _screen ) { screen = _screen; }

    ///Lua///
    void SetDeveloperSex( int _sex );
    void CreateCustomGame( int playersNumber, const char * mapId );
    void JoinToGame( int sessionId );
    void RefreshList();
    void SetJoinMode( const string & mode );

    void AddMapEntry( int index, const char * id, const wchar_t * title, const wchar_t * description );
    void UpdateSessionInfo( const lobby::SDevGameInfo & info );
    void UpdateJoinResult( lobby::EOperationResult::Enum result );

    void SetStatus(wstring status);
  };
}