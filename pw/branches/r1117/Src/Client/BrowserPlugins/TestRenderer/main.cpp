#include <Windows.h>
#include <d3dx9.h>
#include <process.h>

#include "header.h"
#include "../Common/BrowserInterface.h"

float r = 0.5f, h = 0.8f;
int const   n = 50;
int   xPos = 0, yPos = 0;
float rad = 4.0f, u = 1.5f, v = 1.5f; 
POINT MousePos;

LPDIRECT3D9             g_pD3D = NULL; 
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; 
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL; 


HRESULT InitD3D( HWND hWnd )
{
  WINDOWINFO info;
  info.cbSize = sizeof(info);
  GetWindowInfo(hWnd, &info);
  D3DPRESENT_PARAMETERS d3dpp;
  ZeroMemory( &d3dpp, sizeof( d3dpp ) );
  d3dpp.Windowed = TRUE;
  d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
  d3dpp.EnableAutoDepthStencil = TRUE;
  d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
  d3dpp.hDeviceWindow = hWnd;
  //d3dpp.BackBufferHeight = info.rcClient.bottom - info.rcClient.top;
  //d3dpp.BackBufferWidth  = info.rcClient.right - info.rcClient.left;

  if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING |/*D3DCREATE_SOFTWARE_VERTEXPROCESSING | */D3DCREATE_FPU_PRESERVE | D3DCREATE_MULTITHREADED, &d3dpp, &g_pd3dDevice ) ) )
  {
    return E_FAIL;
  }

  g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
  g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

  return S_OK;
}

HRESULT InitGeometry(float r, float h, int n)
{

    if(g_pVB == NULL)
    {
      if( FAILED( g_pd3dDevice->CreateVertexBuffer( n * sizeof( CUSTOMVERTEX ), D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, D3DFVF_CUSTOMVERTEX ,
        D3DPOOL_DEFAULT, &g_pVB, NULL ) ) )
      {
        return E_FAIL;
      }

    }

    CUSTOMVERTEX* pVertices;
    if( FAILED( g_pVB->Lock( 0, 0, ( void** )&pVertices, D3DLOCK_DISCARD ) ) )
        return E_FAIL;
    pVertices[0].position = D3DXVECTOR3( 0,  0,  0);
    pVertices[0].color    = (DWORD)0x0;
    for( DWORD i = 1; i < (DWORD)n; i++ )
    {                                        
      FLOAT theta = ( 2 * D3DX_PI * (i - 1) ) / ( n - 2 );
      pVertices[i].position = D3DXVECTOR3( r * cosf( theta ) ,  r * sinf( theta ),  h  );
   		pVertices[i].color    = (DWORD)0x000D32F41;
    }
    g_pVB->Unlock();

    return S_OK;
}


VOID Cleanup()
{
    if( g_pVB != NULL )
    {
      g_pVB->Release();
      g_pVB = NULL;
    }

    if( g_pd3dDevice != NULL )
    {
      g_pd3dDevice->Release();
      g_pd3dDevice = NULL;
    }

}



VOID SetupMatrices()
{
 
    D3DXVECTOR3 vEyePt( rad * sin(2*D3DX_PI * u)*cos (2*D3DX_PI*v), rad*sin(2*D3DX_PI * u)*sin (2*D3DX_PI*v)  ,rad*cos(2*D3DX_PI * u));
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, -0.01f );

    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}


VOID Render(int n)
{
  g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 255, 255, 220 ), 1.0f, 0 );

  if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
  {
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

    SetupMatrices();

    g_pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof( CUSTOMVERTEX ) );
    g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX);
    g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLEFAN, 0, n - 2 );

    g_pd3dDevice->EndScene();
  }

  g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
   
}


LRESULT MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
  GetCursorPos(&MousePos);

	switch( msg )
    {
		case WM_MOUSEMOVE:
		   xPos   = LOWORD(lParam);
		   yPos   = HIWORD(lParam);
		   u += 0.00005f*(xPos - MousePos.x);
		   v += 0.00005f*(yPos - MousePos.y);
		   break;
     }
     return DefWindowProc( hWnd, msg, wParam, lParam );
}


class BrowserInterface: public IBrowserInterface
{
public:
  BrowserInterface():hWnd(NULL), hThread(NULL),bWantExit(false), nStartCount(0) {}
  LRESULT CallWindowProc(HWND p1, UINT p2, WPARAM p3, LPARAM p4)
  {
    return MsgProc(p1, p2, p3, p4);
  }
  bool  Init(char const *)
  {
    return true;
  }
  bool  SetWindow(HWND hwnd)
  {
    if(1)//hWnd != hwnd)
    {
      StopInternal(false);

      if( g_pVB != NULL )
      {
        g_pVB->Release();   
        g_pVB = NULL;
      }
      if(g_pd3dDevice)
      {
        D3DPRESENT_PARAMETERS d3dpp;
        ZeroMemory( &d3dpp, sizeof( d3dpp ) );
        d3dpp.Windowed = TRUE;                
        d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
        d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
        d3dpp.EnableAutoDepthStencil = TRUE;
        d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
        d3dpp.hDeviceWindow = hwnd;
        if( FAILED( g_pd3dDevice->Reset(&d3dpp) ) )
        {
          return false;
        }
        g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
        g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

        StartInternal(hwnd, false);
      }
    }
    return true;
  }
  bool  Resize(HWND hwnd)
  {
    if(hwnd == NULL)
      return false;
    return SetWindow(hwnd);
  }
  bool  Start(HWND hwnd)
  {
    if(hwnd == NULL)
      return false;
    if(hWnd != hwnd)
    {
      if(hWnd != NULL)
      {
        StopInternal();
      }
      if(StartInternal(hwnd))
      {
        nStartCount++;
        return true;
      }
      else
      {
        return false;
      }
    }
    nStartCount++;

    return true;
  }
  bool  Stop()
  {
    nStartCount--;
    if(nStartCount > 0)
      return true;
    StopInternal();
    return true;
  }
  static unsigned __stdcall MainLoop( void *dummy)
  {
    BrowserInterface *pThis = (BrowserInterface *)dummy;
    while(!pThis->bWantExit) 
    {
      Render(n);
      Sleep(15);
      InitGeometry(r, h, n);
      Sleep(15);
    }
    _endthreadex( 0 );
    return 0;
  }

private:
  HWND hWnd;
  HANDLE hThread;
  bool bWantExit;
  int  nStartCount;

  bool StartInternal(HWND hwnd, bool need3dInit = true)
  {
    hWnd = hwnd;
    if(!need3dInit || SUCCEEDED( InitD3D( hwnd) ) )
    {
      if( SUCCEEDED( InitGeometry(r, h, n) ) )
      {
        UpdateWindow( hwnd );
        bWantExit = false;
        unsigned threadID;
        hThread = (HANDLE)_beginthreadex( NULL, 0, &MainLoop, this, 0, &threadID );
        return true;
      }
    }
    return false;
  }
  bool StopInternal(bool needCleanUp = true)
  {
    if(hWnd == NULL)
      return false;
    if(hThread == NULL)
      return false;
    bWantExit = true;
    //actually stop it
    WaitForSingleObject(hThread, INFINITE );
    hThread = NULL;
    if(needCleanUp)
    {
      Cleanup();
    }
    hWnd = NULL;
    return true;
  }

};

BrowserInterface *itf = NULL;

extern "C"{
__declspec(dllexport) IBrowserInterface * ITF_NAME();
};

IBrowserInterface *ITF_NAME()
{
  return itf;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason,LPVOID lpvReserved)
{
  if(DLL_PROCESS_ATTACH == fdwReason)
  {
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
      return E_FAIL;
    itf = new BrowserInterface();
  }
  if(DLL_PROCESS_DETACH == fdwReason)
  {
    delete itf;
    itf = NULL;

    if( g_pD3D != NULL )
    {
      g_pD3D->Release();
      g_pD3D = NULL ;
    }
  }
  //always TRUE
  return TRUE;
}



