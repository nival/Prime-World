// This is the main DLL file.

#include "stdafx.h"
#include <tchar.h>

#include "CrashRptWraper.h"
#include <windows.h>
#include <stdio.h>
#include "CrashRpt.h"
#include "StackWalker.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <fstream>
#include "CrashHandler.h"

using namespace std;

typedef LPCWSTR(__stdcall * pGetManagedStack)();

static wchar_t* logFilesMaskG = NULL;

pGetManagedStack g_getManagedStack;
CString g_stackInfoFilePath = "stackinfo.txt";

void OpenConsole(){
	AllocConsole();

	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;

	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;
}

// Зададим Callback-функцию, которая будет вызвана при сбое
BOOL WINAPI CrashCallback(PEXCEPTION_POINTERS pExceptionPointers, __reserved LPVOID lpvState)
{  
	wchar_t computerName[128] = _T("");
	GetEnvironmentVariable( _T("COMPUTERNAME"), computerName, 128 );
	crAddProperty( _T("ComputerName"), computerName );

	// лог-файл и параметры конфигурации приложения  
	crAddFile2(_T("Data/output_log.txt"), NULL, _T("Log File"), CR_AF_MAKE_FILE_COPY);
	crAddFile2(logFilesMaskG, NULL, _T("Log File"), CR_AF_MAKE_FILE_COPY);
	// Добавим в отчет скриншот рабочего стола
	//crAddScreenshot(CR_AS_VIRTUAL_SCREEN);   

//	OpenConsole();
	LPCWSTR stackInfo = g_getManagedStack();
	wprintf(_T("\n%s\n"), _T("========== Managed Call Stack ==============")); 
	wprintf(_T("%s\n"), stackInfo);		

	CString folder = CCrashHandler::m_pProcessCrashHandler->m_sUnsentCrashReportsFolder +"\\"+CCrashHandler::m_pProcessCrashHandler->m_sCrashGUID;
	if (Utility::CreateFolder(folder)){

		wprintf(_T("StackOut file at : %s\n"), folder+"\\"+g_stackInfoFilePath);

		std::wofstream stackOut;
		stackOut.open(folder+"\\"+g_stackInfoFilePath);
		stackOut<<_T("========== Managed Call Stack ==============\n");
		stackOut<<stackInfo;
		stackOut.close();
		crAddFile2(folder+"\\"+g_stackInfoFilePath, NULL, _T("Exception File"), 0);

		

		/*wprintf(_T("\n%s\n"), _T("========== UnManaged Call Stack ==============")); 
		CastleStackWalker csw;
		csw.ShowCallstack(GetCurrentThread(),pExceptionInfo->pexcptrs->ContextRecord);*/
	}
	return TRUE;
}

extern "C" __declspec(dllexport) int __stdcall RegisterHandler(LPCWSTR version,LPWSTR logFilesMask,pGetManagedStack getStackMethod)
{
	logFilesMaskG = new wchar_t[wcslen(logFilesMask)+1];
	wcscpy(logFilesMaskG, logFilesMask);
	// Задаем параметры для CrashRpt
	CR_INSTALL_INFO info;  
	memset(&info, 0, sizeof(CR_INSTALL_INFO));  
	info.cb = sizeof(CR_INSTALL_INFO);    
	info.pszAppName = _T("Prime World Castle");  
	info.pszAppVersion = version;  
	info.pszEmailSubject = _T("Castle Crash Report");  
	info.pszEmailTo = _T("crashreport@playpw.com");    
	info.pszUrl = _T("http://b283.nivalnetwork.com/upload/");  
	info.pfnCrashCallback = CrashCallback;   
	info.uPriorities[CR_SMTP] = CR_NEGATIVE_PRIORITY;
	info.uPriorities[CR_SMAPI] = CR_NEGATIVE_PRIORITY;
	info.uPriorities[CR_HTTP] = 1;  
	info.dwFlags = 0; // Установить все доступные обработчики исключений  
	//info.dwFlags |= 	
	//CR_INST_SEH_EXCEPTION_HANDLER
	/* CR_INST_TERMINATE_HANDLER
	| CR_INST_UNEXPECTED_HANDLER
	| CR_INST_PURE_CALL_HANDLER
	| CR_INST_NEW_OPERATOR_ERROR_HANDLER
	| CR_INST_SECURITY_ERROR_HANDLER
	| CR_INST_INVALID_PARAMETER_HANDLER
	| CR_INST_SIGABRT_HANDLER
	| CR_INST_SIGFPE_HANDLER
	| CR_INST_SIGILL_HANDLER
	| CR_INST_SIGINT_HANDLER
	| CR_INST_SIGSEGV_HANDLER
	| CR_INST_SIGTERM_HANDLER
	| CR_INST_CRT_EXCEPTION_HANDLERS;*/
	//TODO URL для политики конфиденциальности
	// info.pszPrivacyPolicyURL = _T("http://nival.com");
	// Russian
	//info.pszLangFilePath = _T("lang_files/crashrpt_lang_RU.ini");
	info.pszDebugHelpDLL = NULL;
	info.uMiniDumpType = MiniDumpNormal;
	info.pszPrivacyPolicyURL = NULL; //TODO: Provide URL to Privacy Policy
	info.pszErrorReportSaveDir = NULL;
	info.pszRestartCmdLine = NULL;

	g_getManagedStack = getStackMethod;

	// Устанавливаем обработчики исключений  
	int nResult = crInstall(&info);

	if (nResult != 0)
	{    
		// Что-то пошло не так! Получим сообщение об ошибке.   
		wchar_t szErrorMsg[512];
		szErrorMsg[0] = 0;
		crGetLastErrorMsg(szErrorMsg, 512);    
		wprintf(_T("%s\n"), szErrorMsg);    
	} 

	return nResult;
}

extern "C" __declspec(dllexport) void __stdcall UnregisterHandler()
{
	crUninstall();
}

extern "C" __declspec(dllexport) void __stdcall EmulateCrash()
{
	wprintf(_T("%s\n"), _T("CRASH!!!")); 
	throw new std::exception();
}
