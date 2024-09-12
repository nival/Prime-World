#include "stdafx.h"
#include "Application.h"
#include "MainWindow.h"
#include "Convert.h"
#include "log.h"

Application* g_App = NULL;

Application::Application(HINSTANCE instance) 
	: m_instance(instance)
	, CAtlModuleT<Application>()
	, m_commandLine()
	, m_errorHandler(0, "")
{
	g_App = this;
	CoInitialize(NULL);
  setlocale(LC_ALL, "Russian");

  if(m_commandLine.HasConfigFile())
		m_config.Load(m_commandLine.GetConfigFile());
	else
		m_config.Load(L"dummyLauncher.cfg");
		
	g_Log->Init("Dummy Launcher", "dummyLauncher.log");

  m_users.LoadCache();
}

Application::~Application()
{
	CoUninitialize();
}

void Application::Run()
{
	CMessageLoop loop;

	m_mainWindow.Create(HWND_DESKTOP);
  m_console.Create(HWND_DESKTOP);

  loop.AddMessageFilter(&m_mainWindow);

  if(m_commandLine.HasServer())
    m_mainWindow.SetServer(m_commandLine.GetServer());

	if(!m_commandLine.HasUIDS())
  {
    m_console.ShowWindow(SW_SHOW);
		m_mainWindow.ShowWindow(SW_SHOW);
  }
	else
  {
		m_mainWindow.TryAutoLogin();
  }

	loop.Run();

  m_console.DestroyWindow();

	g_Log->Done();
}

Application::ErrorHandler& Application::GetErrorHandler(const char* fileName, int lineNum)
{
	m_errorHandler = ErrorHandler(lineNum, fileName);
	return m_errorHandler;
}

void Application::ErrorHandler::Show(const std::wstring& message)
{
	g_App->ShowErrorHandler(*this, message.c_str());
}

void Application::ErrorHandler::Show(const wchar_t* fmt, ...)
{
	wchar_t buffer[2048];
	va_list args;
	va_start(args, fmt);
	vswprintf_s(buffer, 2048, fmt, args);
	va_end(args);

	g_App->ShowErrorHandler(*this, buffer);
}

void Application::ShowErrorHandler(const Application::ErrorHandler& handler, const wchar_t* errText)
{
	g_Log->GetEntry(handler.m_lineNum, handler.m_fileName.c_str(), Log::LOG_ENTRY_ERROR).Put( Convert::ToUTF8(errText).c_str() );
	m_mainWindow.ShowErrorMessage(errText);
}

