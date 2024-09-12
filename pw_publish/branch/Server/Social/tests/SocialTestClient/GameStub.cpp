#include <stdio.h>
#include <process.h>
#include <io.h>
#include <direct.h>
#include <string>
#include <windows.h>

#define EXE "PW_Game.exe"

#define LAUNCH_GAME

#ifdef LAUNCH_GAME

int main(int argc, char* argv[])
{
  std::string путь = "..\\Src\\_Debug\\" EXE;
  //std::string путь = "..\\Src\\_Release\\" EXE;

  std::string аргументы;
  for ( int i = 0; i < argc; ++i ) {
    if ( !аргументы.empty() )
      аргументы += " ";
    аргументы += argv[i];
  }

  system( "echo %CD%" );

  printf( "Starting '%s' + '%s'\n", путь.c_str(), аргументы.c_str() );

  ShellExecute( NULL, "open", путь.c_str(), аргументы.c_str(), NULL, SW_SHOW );
  return 0;
}

#else //LAUNCH_GAME

void ToClipBoard( const std::string & text )
{
  if ( !OpenClipboard( NULL ) )
    return;

  if ( !EmptyClipboard() )
  {
    CloseClipboard();
    return;
  }

  HGLOBAL hCopy = GlobalAlloc( GMEM_MOVEABLE, ( text.size() + 1 ) * sizeof( TCHAR ) );
  if ( !hCopy )
  {
    CloseClipboard();
    return;
  }

  LPTSTR pCopy = (LPTSTR)GlobalLock( hCopy );
  memcpy( pCopy, text.c_str(), ( text.size() + 1 ) * sizeof( TCHAR ) );
  GlobalUnlock( hCopy ); 

  HANDLE hData = SetClipboardData( CF_TEXT, hCopy );
  if ( !hData )
  {
    GlobalFree( hCopy );
    CloseClipboard();
    return;
  }

  CloseClipboard();
}

//Show message box
int main( int argc, char* argv[] )
{
  std::string key, args;
  for ( int i = 0; i < argc; ++i )
  {
    args += argv[i];
    args += "\n";

    if ( key.empty() && !strcmp( argv[i], "-session_login" ) && i + 1 < argc )
    {
      key = argv[i + 1];
      break;
    }
  }

  char dir[512] = "", mod[512] = "";
  GetCurrentDirectory( 512, dir );
  GetModuleFileName( NULL, mod, 512 );

  if ( key.empty() )
  {
    char buf[1024];
    sprintf_s( buf, "Session key was not defined!\nCommand-line:\n%sCurrent dir and module:\n%s\n%s", args.c_str(), dir, mod );

    MessageBox( NULL, buf, "Error", MB_OK | MB_ICONERROR );
    return 0;
  }

  char buf[1024];
  sprintf_s( buf, "Your session key is:\n%s\nPress Yes to copy it into clipboard, press No to exit immediately\nCurrent dir and module:\n%s\n%s", key.c_str(), dir, mod );

  int result = MessageBox( NULL, buf, "Session Key", MB_ICONINFORMATION | MB_YESNO );
  if ( result == IDYES )
    ToClipBoard( key );
}

#endif //LAUNCH_GAME
