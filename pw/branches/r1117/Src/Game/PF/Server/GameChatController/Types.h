#pragma once

namespace gamechat
{
  typedef unsigned long long GameSessionId;
  const GameSessionId INVALID_GAME_SESSION_ID = (GameSessionId)-1;

  namespace channels
  {
    static const wchar_t * Session = L"Session";
    static const wchar_t * Team1 = L"Left";
    static const wchar_t * Team2 = L"Right";
    static const wchar_t * Team1_SmartChat = L"Left_SmartChat";
    static const wchar_t * Team2_SmartChat = L"Right_SmartChat";
  }
}
