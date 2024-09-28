#pragma once
// include the basic windows header files and the Direct3D header file
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <windowsx.h>
#include <stdio.h>


// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "user32.lib")


#if _MSC_VER // this is defined when compiling with Visual Studio
#define EXPORT_API __declspec(dllexport) // Visual Studio needs annotating exported functions with this
#else
#define EXPORT_API // XCode does not need annotating exported functions, so define is empty
#endif

// ------------------------------------------------------------------------
// Plugin itself


// Link following functions C-style (required for plugins)
extern "C"
{

	// global declarations
	LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
	LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
	void init_graphics(void);    // 3D declarations

	struct CUSTOMVERTEX {FLOAT X, Y, Z, RHW; DWORD COLOR;};
	#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
	LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;    // the pointer to the vertex buffer

  LPDIRECT3DTEXTURE9 pRenderTexture = NULL;
  LPDIRECT3DSURFACE9 pRenderSurface = NULL;

	// function prototypes
	void initD3D(HWND hWnd);    // sets up and initializes Direct3D
	void render_frame(void);    // renders a single frame
	void cleanD3D(void);    // closes Direct3D and releases memory

	// the WindowProc function prototype
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// this is the function that puts the 3D models into video RAM
	void init_graphics(void)
{
    // create the vertices using the CUSTOMVERTEX struct
    CUSTOMVERTEX vertices[] =
    {
        { 400.0f, 62.5f, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), },
        { 650.0f, 500.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), },
        { 150.0f, 500.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
    };

    // create a vertex buffer interface called v_buffer
    d3ddev->CreateVertexBuffer(3*sizeof(CUSTOMVERTEX),
                               0,
                               CUSTOMFVF,
                               D3DPOOL_MANAGED,
                               &v_buffer,
                               NULL);

    VOID* pVoid;    // a void pointer

    // lock v_buffer and load the vertices into it
    v_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, vertices, sizeof(vertices));
    v_buffer->Unlock();
}
	// this is the function used to render a single frame
	void EXPORT_API Render_frame(void)
	{
			// clear the window to a deep blue
			d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);

			d3ddev->BeginScene();    // begins the 3D scene

			// do 3D rendering on the back buffer here
			// select which vertex format we are using
        d3ddev->SetFVF(CUSTOMFVF);

        // select the vertex buffer to display
        d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

        // copy the vertex buffer to the back buffer
        d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

			d3ddev->EndScene();    // ends the 3D scene

			d3ddev->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
	}


	void EXPORT_API InitDevice()
	{
		//switch (ul_reason_for_call)
		//{
		//case DLL_PROCESS_ATTACH:
		//case DLL_THREAD_ATTACH:
		//case DLL_THREAD_DETACH:
		//case DLL_PROCESS_DETACH:
			//break;
		//}

		HWND hWnd = FindWindow(NULL,"UnityGame");

		// set up and initialize Direct3D
		initD3D(hWnd);

		// enter the main loop:
		MSG msg;

		
		for(int i = 0;i<300;++i){
			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
				}

				if(msg.message == WM_QUIT)
						break;

				Render_frame();
		}
	
		//while(TRUE)
		//{
		//		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		//		{
		//				TranslateMessage(&msg);
		//				DispatchMessage(&msg);
		//		}

		//		if(msg.message == WM_QUIT)
		//				break;

		//		Render_frame();
		//}

		//clean up DirectX and COM
		cleanD3D();

	}

  void MB( HRESULT res, char* badtext )
  {
    if ( res != D3D_OK )
    {
      MessageBox(0,badtext,"Bad",MB_OK);
    }
    else
    {
      MessageBox(0,"Good","Good",MB_OK);
    }
  }

  void EXPORT_API CreateDevice()
  {
    HWND hWnd = FindWindow(NULL,"UnityGame");
    initD3D(hWnd);
    HRESULT res = d3ddev->CreateTexture(1024,
      1024,
      1,
      D3DUSAGE_RENDERTARGET,
      D3DFMT_A8R8G8B8,
      D3DPOOL_DEFAULT,
      &pRenderTexture,
      NULL);
    MB(res, "CreateTexture");
    res = pRenderTexture->GetSurfaceLevel(0,&pRenderSurface);
    MB(res, "GetSurfaceLevel");
  }

  void EXPORT_API DrawTexture()
  {
    HRESULT res = d3ddev->SetRenderTarget(0,pRenderSurface);
    //clear texture
    res = d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
    res = d3ddev->BeginScene();    // begins the 3D scene
    res = d3ddev->SetFVF(CUSTOMFVF);
    res = d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
    res = d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
    res = d3ddev->EndScene();    // ends the 3D scene
  }

  EXPORT_API byte* GetTexture()
  {
    int headerSize = 128;
    LPD3DXBUFFER pBuffer = 0;
    HRESULT res = D3DXSaveSurfaceToFileInMemory( &pBuffer, D3DXIFF_DDS, pRenderSurface, 0, 0 );
    MB(res, "D3DXSaveSurfaceToFileInMemory");
    byte* ptr = (byte*)(pBuffer)->GetBufferPointer();
    unsigned int len = (pBuffer)->GetBufferSize();
    int realLength = len-headerSize;
    byte* realPtr = ptr+headerSize;
    byte* data = new byte[realLength];
    memcpy(data,realPtr,realLength);
    pBuffer->Release();  
    return data;
  }

  void EXPORT_API ReleaseDevice()
  {
    pRenderSurface->Release();
    pRenderSurface = NULL;
    cleanD3D();
  }

	// this function initializes and prepares Direct3D for use
	void initD3D(HWND hWnd)
	{
			d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

			D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

			ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
			d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
			d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
			d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D
			d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;

			// create a device class using this information and the info from the d3dpp stuct
			d3d->CreateDevice(D3DADAPTER_DEFAULT,
												D3DDEVTYPE_HAL,
												hWnd,
												D3DCREATE_SOFTWARE_VERTEXPROCESSING,
												&d3dpp,
												&d3ddev);

			init_graphics();    // call the function to initialize the triangle
	}


	// this is the function that cleans up Direct3D and COM
	// this is the function that cleans up Direct3D and COM
	void cleanD3D(void)
{
    v_buffer->Release();    // close and release the vertex buffer
    d3ddev->Release();    // close and release the 3D device
    d3d->Release();    // close and release Direct3D
}



} // end of export C block
