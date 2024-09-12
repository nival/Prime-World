#include "stdafx.h"
#include "TutorialSplash.h"

#include "System/ImageDDS.h"
#include "System/FileSystem/FileStream.h"

namespace
{
  nstl::string s_tutorial_splash_image("UI/Styles/Tutorial/tutorial_splash.dds");
}

REGISTER_VAR("tutorial_splash_image", s_tutorial_splash_image, STORAGE_NONE);

namespace
{
#pragma pack(push, 1)

  struct _SRC_PIXEL
  {
    BYTE b;
    BYTE g;
    BYTE r;
    BYTE a;
  };

  struct _DST_PIXEL
  {
    BYTE b;
    BYTE g;
    BYTE r;
    BYTE a;
  };

#pragma pack(pop)

  LPCTSTR _splashWindowClassName = TEXT("SplashWindowClass");

  struct WindowDC : public NonCopyable
  {
    explicit WindowDC(const HWND _window = NULL)
      : window(_window)
      , dc(::GetDC(_window))
    {

    }

    ~WindowDC()
    {
      if (dc)
        ::ReleaseDC(window, dc);
    }

    operator HDC() const
    {
      return dc;
    }
  private:
    const HWND window;
    const HDC dc;
  };

  struct CompatibleDC : public NonCopyable
  {
    explicit CompatibleDC(const HDC _dc)
      : dc(::CreateCompatibleDC(_dc))
    {

    }

    ~CompatibleDC()
    {
      if (dc)
        ::DeleteDC(dc);
    }

    operator HDC() const
    {
      return dc;
    }
  private:
    CompatibleDC();

    const HDC dc;
  };

  class SplashJob : public BaseObjectMT, public threading::IThreadJob
  {
    NI_DECLARE_REFCOUNT_CLASS_2(SplashJob, BaseObjectMT, threading::IThreadJob);
  public:
    static StrongMT<SplashJob> Create()
    {
      const StrongMT<SplashJob> job(new SplashJob());

      return job;
    }

    virtual ~SplashJob()
    {
      Cleanup();
    }
  protected:
    SplashJob()
      : instance(::GetModuleHandle(NULL))
      , windowClassAtom(0)
      , splashWindow(NULL)
    {

    }

    virtual void Work(volatile bool& running)
    {
      DevTrace("TutorialSplash: start");

      if (Init())
      {
        DevTrace("TutorialSplash: loop");

        Loop(running);
      }

      DevTrace("TutorialSplash: end");
    }
  private:
    bool Init()
    {
      const bool initialized = DoInit();

      DoFinishInit();

      return initialized;
    }

    bool DoInit()
    {
      {
        WNDCLASSEX windowClass;

        Zero(windowClass);

        windowClass.cbSize = sizeof(windowClass);
        windowClass.hInstance = instance;
        windowClass.hCursor = ::LoadCursor(NULL, IDC_ARROW);
        windowClass.lpszClassName = _splashWindowClassName;
        windowClass.lpfnWndProc = ::DefWindowProc;

        windowClassAtom = ::RegisterClassEx(&windowClass);

        if (windowClassAtom == 0)
        {
          return false;
        }
      }

      {
        splashWindow = ::CreateWindowEx(WS_EX_LAYERED, _splashWindowClassName, NULL, WS_POPUP | WS_VISIBLE, 0, 0, 0, 0, NULL, NULL, instance, NULL);

        if (splashWindow == NULL)
        {
          return false;
        }
      }

      {
        if (!LoadImage())
        {
          return false;
        }

        if (!PrepareImage())
        {
          return false;
        }
      }

      {
        POINT ptZero;
        Zero(ptZero);

        HMONITOR hmonPrimary = ::MonitorFromPoint(ptZero, MONITOR_DEFAULTTOPRIMARY);

        MONITORINFO monitorInfo;
        Zero(monitorInfo);
        monitorInfo.cbSize = sizeof(monitorInfo);

        ::GetMonitorInfo(hmonPrimary, &monitorInfo);

        const RECT & monitorRect = monitorInfo.rcWork;

        SIZE size;

        size.cx = imageData.GetSizeX();
        size.cy = imageData.GetSizeY();

        POINT origin;

        origin.x = monitorRect.left + (monitorRect.right - monitorRect.left - size.cx) / 2;
        origin.y = monitorRect.top + (monitorRect.bottom - monitorRect.top - size.cy) / 2;

        const WindowDC desktopDC(HWND_DESKTOP);
        const CompatibleDC dc(desktopDC);

        HBITMAP bitmapOld = static_cast<HBITMAP>(::SelectObject(dc, bitmap));

        BLENDFUNCTION blendFunc;
        Zero(blendFunc);
        blendFunc.BlendOp = AC_SRC_OVER;
        blendFunc.SourceConstantAlpha = 255;
        blendFunc.AlphaFormat = AC_SRC_ALPHA;

        ::UpdateLayeredWindow(splashWindow, desktopDC, &origin, &size, dc, &ptZero, RGB(0, 0, 0), &blendFunc, ULW_ALPHA);
        ::SelectObject(dc, bitmapOld);
      }

      return true;
    }

    void Loop(volatile bool& running)
    {
      MSG message;

      while (true)
      {
        if (::PeekMessage(&message, splashWindow, 0, 0, PM_REMOVE))
        {
          ::TranslateMessage(&message);
          ::DispatchMessage(&message);
        }
        else
        {
          if (!running)
            break;

          ::Sleep(0);
        }
      }
    }

    void Cleanup()
    {
      if (bitmap != NULL)
      {
        ::DeleteObject(bitmap);

        bitmap = NULL;
      }

      if (splashWindow != NULL)
      {
        ::DestroyWindow(splashWindow);

        splashWindow = NULL;
      }

      if (windowClassAtom != 0)
      {
        ::UnregisterClass(_splashWindowClassName, instance);

        windowClassAtom = 0;
      }
    }

    void DoFinishInit()
    {
      if (bitmap != NULL)
      {
        ::DeleteObject(bitmap);

        bitmap = NULL;
      }

      imageData.Clear();
    }

    bool LoadImage()
    {
      nstl::string subpath("/Data/Localization/");
      subpath = NFile::Combine(subpath, (NStr::ToMBCS(NGlobal::GetVar("language").GetString())));
      subpath = NFile::Combine(subpath, s_tutorial_splash_image);
      const nstl::string path(NFile::Combine(NFile::GetBaseDir(), subpath));

      const CObj<Stream> stream(new FileStream(path, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING));

      if (!IsValid(stream) || !stream->IsOk())
      {
        ErrorTrace("Cannot open splash image file \"%s\"", path);
        return false;
      }

      if (!NImage::RecognizeFormatDDS(stream))
      {
        ErrorTrace("Invalid splash image \"%s\"", path);
        return false;
      }

      if (!NImage::LoadImageDDS(&imageData, stream))
      {
        ErrorTrace("Failed to load splash image \"%s\"", path);
        return false;
      }

      return true;
    }

    bool PrepareImage()
    {
      const WindowDC desktopDC(HWND_DESKTOP);

      BITMAPINFO bi;

      Zero(bi);

      bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
      bi.bmiHeader.biWidth = static_cast<LONG>(imageData.GetSizeX());
      bi.bmiHeader.biHeight = -static_cast<LONG>(imageData.GetSizeY());
      bi.bmiHeader.biPlanes = 1;
      bi.bmiHeader.biBitCount = 32;
      bi.bmiHeader.biCompression = BI_RGB;

      typedef LPCVOID const     src_bits_p;
      typedef LPVOID            dst_bits_p;
      typedef const _SRC_PIXEL* src_pixel_p;
      typedef _DST_PIXEL*       dst_pixel_p;

      src_bits_p src_bits = &imageData.GetUnsafe(0, 0);
      dst_bits_p dst_bits = NULL;

      bitmap = ::CreateDIBSection(desktopDC, &bi, DIB_RGB_COLORS, &dst_bits, NULL, 0U);

      if (bitmap == NULL)
      {
        ErrorTrace("Failed to create DIB");
        return false;
      }

      NI_VERIFY(!!dst_bits, "DIB was not initialized properly", return false);

      // premultiplied alpha требуется для корректной работы блендинга
      // TODO: использовать фактический формат пикселя исходной картинки
      {
        src_pixel_p src = reinterpret_cast<src_pixel_p>(src_bits);
        dst_pixel_p dst = reinterpret_cast<dst_pixel_p>(dst_bits);

        const int width = imageData.GetSizeX();
        const int height = imageData.GetSizeY();

        for (int j = 0; j < height; ++j)
        {
          for (int i = 0; i < width; ++i, ++src, ++dst)
          {
            (*dst).r = ((unsigned((*src).r) * unsigned((*src).a)) / 255U);
            (*dst).g = ((unsigned((*src).g) * unsigned((*src).a)) / 255U);
            (*dst).b = ((unsigned((*src).b) * unsigned((*src).a)) / 255U);
            (*dst).a = (*src).a;
          }
        }
      }

      return true;
    }

    const HINSTANCE instance;

    ATOM windowClassAtom;
    HWND splashWindow;

    HBITMAP bitmap;

    CArray2D<DWORD> imageData;
  };

  StrongMT<threading::JobThread> CreateSplashJobThread()
  {
    const StrongMT<SplashJob> job(SplashJob::Create());
    const StrongMT<threading::JobThread> thread(new threading::JobThread(job, "TutorialSplash"));

    return thread;
  }
}

NI_DEFINE_REFCOUNT(SplashJob);

namespace NGameX
{
  TutorialSplash::TutorialSplash()
    : thread(CreateSplashJobThread())
  {

  }

  TutorialSplash::~TutorialSplash()
  {
    if (thread)
    {
      thread->AsyncStop();
      thread->Wait();
    }
  }
}
