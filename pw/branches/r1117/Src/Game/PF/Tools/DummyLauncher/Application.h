#pragma once

#include "Config.h"
#include "CommandLine.h"
#include "MainWindow.h"
#include "ConsoleWindow.h"
#include "UsersInfo.h"
#include "EnvironmentVars.h"

class Application : public CAtlModuleT<Application>
{
public:
	Application(HINSTANCE instance);
	~Application();

	void Run();

	const CommandLine& GetCommandLine() const { return m_commandLine; }
	EnvironmentVars& GetVars() { return m_environmentVars; }

	Config& GetConfig() { return m_config; }

	HINSTANCE GetHINSTANCE() { return m_instance; }

	MainWindow& GetMainWindow() { return m_mainWindow; }
  ConsoleWindow& GetConsole() { return m_console; }

	UsersInfo& GetUsersInfo() { return m_users; }

	class ErrorHandler
	{
	public:
		void Show(const wchar_t* fmt, ...);
		void Show(const std::wstring& message);
	private:
		ErrorHandler(int lineNum, const char* fileName) :
		   m_lineNum(lineNum), m_fileName(fileName) {}
		int m_lineNum;
		std::string m_fileName;
		friend class Application;
	};

	ErrorHandler& GetErrorHandler(const char* fileName, int lineNum);

  CMessageLoop* GetMainMessageLoop() { return &m_mainLoop; }

private:
	HINSTANCE m_instance;
	CommandLine m_commandLine;
	Config m_config;
	EnvironmentVars m_environmentVars;
  UsersInfo m_users;

  MainWindow m_mainWindow;
  ConsoleWindow m_console;

	void ShowErrorHandler(const ErrorHandler& handler, const wchar_t* errText);
	ErrorHandler m_errorHandler;

	friend class Application::ErrorHandler;

  CMessageLoop m_mainLoop;
};

extern Application* g_App;

//#define ShowError	g_App->SetCurErrInfo(__FILE__, __LINE__); g_App->ShowErrorMsg
#define ShowError g_App->GetErrorHandler(__FILE__, __LINE__).Show
#define Console g_App->GetConsole().AddText