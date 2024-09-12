#include <Windows.h>
#include <CommCtrl.h>
#include "shlobj.h"

#include "../Common/BrowserInterface.h"
#include "../Common/WebGameInterface.h"
#include "System/Basic.h"
#include "System/FilePath.h"
#include "System/Thread.h"
#include "System/ThreadHelpers.h"
#include "System/ZipFileSystem.h"

#include "HTTPDownloaderService.h"
#pragma warning(disable: 4512)

_interface IProgressBar
{
  virtual void SetProgress(double progress)=0;
};

class Bitmap
{
public:
  Bitmap(const char* path):
  HMemDC(0),
  HOldBmp(0)
  {
    SetPosition(0, 0);
    // create a memory DC
    HMemDC = CreateCompatibleDC(NULL);
    if (HMemDC)
    {
      // load a bitmap from file
      HBITMAP HBmp =
        static_cast<HBITMAP>(
        LoadImageA(0, path, IMAGE_BITMAP,
        0, 0, LR_LOADFROMFILE)
        );
      if (HBmp)
      {
        // extract dimensions of the bitmap
        GetObject(HBmp, sizeof(BITMAP), &bmp);

        // associate the bitmap with the memory DC
        HOldBmp = static_cast<HBITMAP>(
          SelectObject(HMemDC, HBmp)
          );
      }
    }
  }

  ~Bitmap()
  {
    DeleteObject(SelectObject(HMemDC, HOldBmp));
    DeleteDC(HMemDC);
  }
  int GetWidth() const { return bmp.bmWidth; }
  int GetHeight() const { return bmp.bmHeight; }

  void SetPosition(int x, int y)
  {
    RDest.left = x;
    RDest.top = y;
  }

  void Render(const HDC Hdc, float zoom_factor)
  {
    const int new_width = static_cast<int>(zoom_factor * GetWidth());
    const int new_height = static_cast<int>(zoom_factor * GetHeight());
    RDest.right = RDest.left + new_width;
    RDest.bottom = RDest.top + new_height;
    if (RDest.right - RDest.left > 0)
    {
      // use BitBlt when not zooming
      if (zoom_factor == 1.0)
      {
        BitBlt(Hdc, RDest.left, RDest.top,
          RDest.right - RDest.left,
          RDest.bottom - RDest.top,
          HMemDC, 0, 0,
          SRCCOPY);
      }
      else
      {
        if (zoom_factor < 1.0)
        {
          SetStretchBltMode(Hdc, COLORONCOLOR);
        }

        // render the zoomed image
        StretchBlt(Hdc, RDest.left, RDest.top,
          RDest.right - RDest.left,
          RDest.bottom - RDest.top,
          HMemDC, 0, 0,
          bmp.bmWidth, bmp.bmHeight,
          SRCCOPY);
      }
    }
  }
private:
  BITMAP bmp;
  HDC HMemDC;
  HBITMAP HOldBmp;
  RECT RDest;
};

HMODULE GetPluginModuleHandle(const void* address)
{
  HMODULE module = 0;
  BOOL result  = GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR)(void *)address, &module);
  return result?module:0;
}

class ProgressBar
{
  static const int progressBarPrecision = 1000;
public:
  ProgressBar(HWND parent):
  progress(0)
  {
    RECT rcClient;  // Client area of parent window 
    int cyVScroll;  // Height of scroll bar arrow 
    int cxVScroll;  
    GetClientRect(parent, &rcClient); 
    cyVScroll = GetSystemMetrics(SM_CYCURSOR)/3 + GetSystemMetrics(SM_CYEDGE); 
    cxVScroll = GetSystemMetrics(SM_CXVSCROLL); 

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, PROGRESS_CLASS,  (LPTSTR) NULL, WS_CHILD | WS_VISIBLE,
      rcClient.left + cxVScroll, (rcClient.bottom + rcClient.top) / 2 + 16 * cyVScroll / 2, rcClient.right - 2 * cxVScroll, 
      cyVScroll, 
      parent, 
      (HMENU)0, 
      GetPluginModuleHandle(&progressBarPrecision), NULL);
    SendMessage(hwnd, PBM_SETRANGE, 0,  MAKELPARAM(0, progressBarPrecision));
    SetProgress(0);
  }

  void Show(bool show)
  {
    SendMessage(hwnd, PBM_SETPOS, (WPARAM)int((progressBarPrecision*progress)),  0L);
    ShowWindow(hwnd, (show)?SW_SHOW:SW_HIDE);
  }

  void SetProgress(double value)
  {
    progress = value;
  }
private:
  double progress;
  HWND hwnd;
};

struct FileDownloader
{
  void Stop()
  {
    event.Set();
    url.clear();
    localPath.clear();
  }

  void DownloadFile(char const *_url, wchar_t const *_localPath, bool _checkHead, threading::Event* _finishEvent=0)
  {
    NI_ASSERT(downloader.GetStatus() == HTTPDownloaderService::DL_NOTACTIVE, "Downloader should be inactive");
    url = _url;
    localPath = _localPath;
    checkHead = _checkHead;
    finishEvent = _finishEvent;
    event.Set();
  }

  unsigned GetContentSize() const {return downloader.GetContentSize();}
  unsigned GetRecievedSize() const {return downloader.GetRecievedSize(); }

  virtual uint Process(const bool& isRunning)
  {
    while (isRunning)
    {
      event.Wait();
      if (url.size() > 0)
      {
        if (checkHead)
        {
          downloader.DownloadFileIfNeeded(url.c_str(), localPath.c_str(), finishEvent);
        } else
        {
          downloader.DownloadFile(url.c_str(), localPath.c_str(), finishEvent);
        }
      }
    }
    return 0;
  }
private:
  nstl::string url;
  nstl::wstring localPath;
  bool checkHead;
  threading::Event event;
  threading::Event* finishEvent;
  HTTPDownloaderService downloader;
};

template <typename T>
struct VolatileType
{
  VolatileType(T _value):value(_value) {}

  void Set(T _value)
  {
    lock.Lock();
    value = _value;
    lock.Unlock();
  }
  const T Get() const 
  {
    threading::MutexLock locker(lock);
    return value;
  }
  T value;
private:
  threading::Mutex lock;
};

typedef VolatileType<HWND> WindowVType; 
struct Initializer
{
  Initializer(FileDownloader& _downloader, IProgressBar* _progressBar, WindowVType& _window):
  hGame(0), 
  gameItf(0), 
  downloader(_downloader),
  progressBar(_progressBar),
  window(_window)
  {

  }
  bool Start(HWND hwnd) { 
    if (gameItf)
    {
      return gameItf->Start(hwnd);
    }
    return true; 
  }

  bool Stop() { return gameItf?gameItf->Stop():false; }

  bool SetWindow(HWND hwnd) { return gameItf?gameItf->SetWindow(hwnd):true; }

  void Init(const char* _cmdLine)
  {
    cmdLine = _cmdLine;
  }

  void Release()
  {
    if(gameItf) 
    {
      gameItf->Release(); 
      gameItf = 0;
    }
    if (hGame)
    {
      FreeLibrary(hGame);
      hGame = 0;
    }
  }

  void ExtractAll(const nstl::string& zipName, const nstl::string& outputFolder)
  {
    ZipFileSystem fs(zipName.c_str());
    nstl::vector<nstl::string> files;
    fs.GetFiles(&files, ".", "*.*");
    for (int i=0;i<files.size();++i)
    {
      nstl::string _fileName = NFile::Combine(outputFolder, files[i], '/');
      CObj<Stream> f = fs.OpenFile(files[i], FILEACCESS_READ, FILEOPEN_OPEN_EXISTING);
      if (f && f->IsOk())
      {
        nstl::wstring fileName = NStr::ToUnicode(_fileName);
        NFile::CreateDirectory(fileName.c_str(), true);
        FileStream newFile(_fileName, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW);
        if (newFile.IsOk())
        {
          const int bufferSize = 100*1024;
          byte* buffer = new byte[bufferSize];
          while (true)
          {
            int readSize = f->Read(buffer, bufferSize);
            if (readSize > 0)
            {
              newFile.Write(buffer, readSize);
            } else
            {
              break;
            }
          }

          delete [] buffer;
        }
      }
    }
  }

  virtual uint Process(const bool& isRunning)
  {
    nstl::string _projectFolder;
    nstl::wstring dllFolder;
    nstl::string _dllFolder;
    nstl::string _dllName;
    if (strstr(cmdLine.c_str(), "http") == cmdLine.c_str() || strstr(cmdLine.c_str(), "https") == cmdLine.c_str())
    {
      nstl::string outputFileName = NFile::GetFileName(cmdLine);
      nstl::string outputExt = NFile::GetFileExt(outputFileName);
      nstl::string _outputPath;

      char szPath[MAX_PATH];
      SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA | CSIDL_FLAG_CREATE, NULL, 0, szPath);
      _projectFolder = NFile::Combine(szPath, "Nival\\PrimeWorld\\", '/');

      _dllFolder = NFile::Combine(_projectFolder, "Bin", '/');

      threading::Event finished;
      if (outputExt.find(".zip") != nstl::string::npos)
      {
        _outputPath = NFile::Combine(_projectFolder, outputFileName, '/');
      } else
      {
        _outputPath = NFile::Combine(_dllFolder, outputFileName, '/');
      }

      nstl::wstring outputPath = NStr::ToUnicode(_outputPath);
      downloader.DownloadFile(cmdLine.c_str(), outputPath.c_str(), true, &finished);

      while (!finished.Wait(50))
      {
        progressBar->SetProgress(double(downloader.GetRecievedSize())/double(downloader.GetContentSize()));
        //UpdateUI here
      }

      _dllName = NFile::Combine(_dllFolder, outputFileName, '/');
      if (outputExt.find(".zip") != nstl::string::npos)
      {
        ExtractAll(_outputPath, _projectFolder);
        _dllName = NFile::CutFileExt(_dllName, 0);
        _dllName += ".dll";
      } else
      {
        _dllName = NFile::Combine(_dllFolder, outputFileName, '/');
      }
    } else
    {
      _dllName = cmdLine;
      _projectFolder = "C:\\Nival\\PF_DInter\\";
      _dllFolder = NFile::Combine(_projectFolder, "Bin", '/');
    }
    // retrieve directory
    nstl::wstring projectFolder = NStr::ToUnicode(_projectFolder);
    dllFolder = NStr::ToUnicode(_dllFolder);
    dllName = NStr::ToUnicode(_dllName);
    bool result = false;

    // set directory to load dlls from
    SetDllDirectoryW(dllFolder.c_str());
    hGame = LoadLibraryW(dllName.c_str());
    if (hGame)
    {
      FARPROC p = GetProcAddress(hGame, ITF_WGI_NAME_S);
      if (p)
      {
        gameItf = ((IWebGameInterface * (*)(wchar_t const *))p)(projectFolder.c_str());
        if (gameItf)
        {
          result = gameItf->Init(cmdLine.c_str());
          if (result && window.Get())
          {
            result = gameItf->Start(window.Get());
          }
        }
      }
    }
    return result;
  }
  IWebGameInterface *gameItf;
private:
  nstl::wstring dllName;
  HMODULE hGame;
  FileDownloader& downloader;
  nstl::string cmdLine;
  IProgressBar* progressBar;
  WindowVType& window;
};

struct UIProgressBar : public IProgressBar
{
  UIProgressBar():
  progressBar(0),
  progress(0)
  {
  }
  ~UIProgressBar()
  {
    SetUI(0);
  }

  virtual void SetProgress(double _progress)
  {
    progress = _progress;
    if (progressBar)
    {
      progressBar->SetProgress(progress);
    }
  }

  void Show(bool show) { if (progressBar) progressBar->Show(show); }

  void SetUI(ProgressBar* _progressBar)
  {
    if (progressBar)
    {
      delete progressBar;
      progressBar = 0;
    }
    progressBar = _progressBar;
    if (progressBar)
    {
      progressBar->SetProgress(progress);
    }
  }
private:
  double progress;
  ProgressBar*            progressBar;
};

class BrowserInterface: public IBrowserInterface, public CObjectBase
{
  OBJECT_METHODS(0xE6C5B80, BrowserInterface);
  CObj<BrowserInterface>  objHolder;   
  Bitmap                  bitmap;
  bool                    isInitialized;
  bool                    isStarted;
public:
  static BrowserInterface *CreateInterface()
  {
    CObj<BrowserInterface> holder = new BrowserInterface();
    holder->objHolder = holder;
    return holder;
  }
  BrowserInterface():
    bitmap("NN.bmp"),
    window(0),
    downloadThread(downloader, false),
    isInitialized(false),
    isStarted(false),
    initializer(downloader, &progressBar, window),
    initializeThread(initializer, false)
  {
    downloadThread.Resume();
  }

  ~BrowserInterface()
  {
    downloadThread.Stop(false);
    downloader.Stop();
    downloadThread.Stop(true);

    RestartInterface(0);
    initializer.Stop();
  }

  virtual LRESULT CallWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
  {
    if (initializer.gameItf)
    {
      return initializer.gameItf->CallWindowProc(hWnd, msg, wParam, lParam);
    } else
    {
      switch (msg)
      {
        case WM_PAINT:
        {
          RECT rect;
          if (GetClientRect(hWnd, &rect))
          {
            int x = (rect.right-bitmap.GetWidth())/2;
            int y = (rect.bottom-bitmap.GetHeight())/2;
            bitmap.SetPosition(x, y);
          }
          PAINTSTRUCT ps;
          const HDC hdc = BeginPaint(hWnd, &ps);
          HBRUSH hbrGray  = (HBRUSH)GetStockObject(BLACK_BRUSH); 
          FillRect(hdc, &rect, hbrGray); 
          DeleteObject(hbrGray);

          bitmap.Render(hdc, 1.f);
          progressBar.Show(true);

          //::DrawTextA(Hdc, "Test", 4, &rect, DT_NOPREFIX|DT_END_ELLIPSIS|DT_SINGLELINE|DT_NOCLIP);

          EndPaint(hWnd, &ps);
          break;
        }
      }
      return DefWindowProc(hWnd, msg, wParam, lParam);
    }
  }

  virtual bool Init(char const* cmdLine)
  {
    if (cmdLine)
    {
      initializer.Init(cmdLine);
      initializeThread.Resume();
    }
    return true;
  }

  virtual bool Resize(HWND hwnd)
  {
    if (window.value != hwnd)
    {
      RestartInterface(hwnd);
    }
    return initializer.gameItf->Resize(hwnd);
  }

  virtual bool Start(HWND hwnd)
  {
    if (window.value != hwnd)
    {
      RestartInterface(hwnd);
    }
    return initializer.Start(hwnd);
  }

  virtual bool Stop()
  {
    return initializer.Stop();
  }

  virtual bool SetWindow(HWND hwnd)
  {
    if (window.value != hwnd)
    {
      RestartInterface(hwnd);
    }
    return initializer.gameItf->SetWindow(hwnd);
  }
  
  virtual void Release() 
  {
    initializer.Release();
    CObj<BrowserInterface> holder = objHolder;
    objHolder = 0;  //object deleted on holder destroy
  }
private:
  void RestartInterface(HWND hwnd)
  {
    progressBar.SetUI(0);
    if (hwnd)
    {
      ProgressBar* bar = new ProgressBar(hwnd);
      progressBar.SetUI(bar);
    }
    window.Set(hwnd);
  }
  UIProgressBar progressBar;
  WindowVType window;
  FileDownloader downloader;
  threading::ProcessingThread<FileDownloader> downloadThread;
  Initializer initializer;
  threading::ProcessingThread<Initializer> initializeThread;
};

extern "C"{
__declspec(dllexport) IBrowserInterface * ITF_NAME();
__declspec(dllexport) bool testInit(IBrowserInterface* api, char const *cmdLine) {  return api->Init(cmdLine); }
__declspec(dllexport) LRESULT testCallWindowProc(IBrowserInterface* api, HWND hwnd, UINT p0, WPARAM p1, LPARAM p2)  { return api->CallWindowProc(hwnd, p0, p1, p2); }
__declspec(dllexport) bool testStart(IBrowserInterface* api, HWND hwnd) { return api->Start(hwnd); }
__declspec(dllexport) bool testStop(IBrowserInterface* api) 
{ 
  bool result = api->Stop();
  return result; 
}          
__declspec(dllexport) bool testResize(IBrowserInterface* api, HWND hwnd) { return api->Resize(hwnd); }
__declspec(dllexport) bool testSetWindow(IBrowserInterface* api, HWND hwnd) { return api->SetWindow(hwnd); }
__declspec(dllexport) void testRelease(IBrowserInterface* api) { return api->Release(); }
};

IBrowserInterface *ITF_NAME()
{
  return BrowserInterface::CreateInterface();
}

void DeleteBrowserInterface(IBrowserInterface* api)
{
  delete api;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason,LPVOID lpvReserved)
{
  UNREFERENCED_PARAMETER(hinstDLL);
  UNREFERENCED_PARAMETER(lpvReserved);
  if(DLL_PROCESS_ATTACH == fdwReason)
  {
  }
  if(DLL_PROCESS_DETACH == fdwReason)
  {
  }
  return TRUE;
}



