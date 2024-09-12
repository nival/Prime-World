#pragma once

#include "Core/CommandSerializer.h"
#include "Core/Replay.h"

// HELPER-класс на коленке, для вытаскивания команд конкретного клиента по одной 
// (ага, избавьте нас от мучительной итерации по чанкам, сегментам, векторам команд и прочим ужосам Replay.cpp)
//
// тут весь механизм использования следующий:
// if( LoadReplay( filename, clientId )
// {
//   GetCurrentCommand // получаем текущую команду
//   do { ...smth... } while ( GetNextCommand ); // перебираем (по одной) следующие команды
// }
class ReplayCommandFeeder: public NonCopyable
{
public:
  ReplayCommandFeeder() : replay(0), startTime(0), clientId(0)
  {}

  bool LoadReplay( const char * replayFileName_, const int clientId_ );
  bool HasReplay() { return (replay != 0); }

  bool GetCurrentCommand( NCore::ReplaySegment::Commands::iterator & outCommand );
  bool GetNextCommand( NCore::ReplaySegment::Commands::iterator & outCommand );

  DWORD GetStartTime() { return startTime; }

  // относительное время ("от старта игровой сессии"), когда команда cmd должна быть исполнена
  DWORD GetCommandTimestamp( const NCore::ReplaySegment::Commands::iterator & cmd ) { return ((*cmd)->TimeSent() - startTime) / 1000.0; } // timeSent у нас в мсек

private:
  bool GetReplayStartTime();

  CObj<NCore::ReplayStorage> replay;
  NCore::ReplaySegment segment;
  NCore::ReplaySegment::Commands::iterator command;
  DWORD startTime;
  int clientId;
};
