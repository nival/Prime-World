#pragma once
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <shlwapi.h>
#include <crtdbg.h>
#include <Strsafe.h>

extern "C"
{
	typedef void WINAPIV TStartPWPlugin( HWND hWnd, int width, int height, bool fullscreen );

	size_t StrLength( LPCTSTR str )
	{
		return StrCSpn( str, TEXT( "" ) );
	}

	void ErrorExit(LPTSTR lpszFunction) 
	{ 
		LPVOID lpMsgBuf;
		LPVOID lpDisplayBuf;
		DWORD dw = GetLastError(); 

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR) &lpMsgBuf,
			0, NULL );

		// Display the error message and exit the process

		lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
			(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
		StringCchPrintf((LPTSTR)lpDisplayBuf, 
			LocalSize(lpDisplayBuf) / sizeof(TCHAR),
			TEXT("%s failed with error %d: %s"), 
			lpszFunction, dw, lpMsgBuf); 
		MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

		LocalFree(lpMsgBuf);
		LocalFree(lpDisplayBuf);
	}

	bool LaunchGameDll( HWND hWnd, int width, int height, int fullscreen )
	{
		const size_t MAX_MOD_NAME = 1024;
		TCHAR szModuleName[MAX_MOD_NAME] = "";

		DWORD result = GetModuleFileName( GetModuleHandle( NULL ), szModuleName, MAX_MOD_NAME );
		if ( !result || ( result == MAX_MOD_NAME ) )
			return false;

		LPTSTR slash = StrRChr( szModuleName, NULL, TEXT( '\\' ) );
		if ( !slash )
			return false;

		slash[1] = 0;

		TCHAR szDirectory[MAX_PATH] = "";
		::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory);
		LPSTR dir = StrCat(szDirectory, TEXT("/../PvP/Bin"));
		SetCurrentDirectory(dir);
		::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory);
		LPSTR pszDllName = StrCat(szDirectory, TEXT("/PW_Client.dll"));

		HMODULE hDll = LoadLibraryEx( pszDllName, NULL, LOAD_WITH_ALTERED_SEARCH_PATH );
		if ( !hDll )
		{
			ErrorExit( TEXT("LoadLibraryEx") );
			return false;
		}

		TStartPWPlugin* proc = (TStartPWPlugin*)GetProcAddress( hDll, TEXT( "StartPWPlugin" ) );
		if ( !proc )
		{
			ErrorExit( TEXT("GetProcAddress") );
			return false;
		}

		//char temp[256];
		//sprintf(temp, "%dx%d, %d", width, height, fullscreen );
		//MessageBox(0,temp,"!",MB_OK);

		proc( hWnd, width, height, fullscreen ? true : false );

		FreeLibrary( hDll );
		return true;
	}

	void __declspec(dllexport) InitDevice( int width, int height, int fullscreen )
	{
		HWND hWnd = FindWindow( NULL, "lobby" );
		if ( !LaunchGameDll( hWnd, width, height, fullscreen ) )
		{
			MessageBox( 0, TEXT( "Could not launch main executable. Please re-install the application." ), TEXT( "Unpredictable Error" ), MB_OK | MB_ICONERROR );
		}
	}
}
