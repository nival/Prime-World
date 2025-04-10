/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

#pragma once
#include "stdafx.h"
#include "CritSec.h"
#include "theora/theoradec.h"

// Preview mode
enum PreviewMode
{
    PREVIEW_AUTO = -1,  // Auto
    PREVIEW_HEX  = 0,   // Hex
    PREVIEW_TEXT = 1,   // Text
    PREVIEW_IMAGE = 2,  // Image    
	PREVIEW_VIDEO = 3   // OGG Theora-encoded video
};

// Text encoding
enum TextEncoding
{
    ENC_AUTO = -1, // Auto
    ENC_ASCII = 0, // ASCII
    ENC_UTF8  = 1, // UTF-8
    ENC_UTF16_LE = 2, // UTF-16 little endian
    ENC_UTF16_BE = 3  // UTF-16 big endian
};

// Used to map file contents into memory
class CFileMemoryMapping
{
public:

    // Construction/destruction
    CFileMemoryMapping();  
    ~CFileMemoryMapping();  

    // Initializes the object
    BOOL Init(LPCTSTR szFileName);
    // Destroys the object
    BOOL Destroy();

    // Returns memory size
    ULONG64 GetSize();

    // Creates a view 
    LPBYTE CreateView(DWORD dwOffset, DWORD dwLength);

private:

    HANDLE m_hFile;		          // Handle to current file
    HANDLE m_hFileMapping;		  // Memory mapped object
    DWORD m_dwAllocGranularity; // System allocation granularity  	  
    ULONG64 m_uFileLength;		  // Size of the file.		
    CCritSec m_csLock;          // Synchronization object
    std::map<DWORD, LPBYTE> m_aViewStartPtrs; // Base of the view of the file.    
};

// Line info
struct LineInfo
{
    DWORD m_dwOffsetInFile; // Line offset in file
    DWORD m_cchLineLength;  // Line length in symbols
};

// Image class - encapsulates image reading functionality
class CImage
{
public:

    // Construction/destruction
    CImage();
    ~CImage();

    // Destroys the object
    void Destroy();

    // Returns TRUE if the file is a BMP image, otherwise returns FALSE
    static BOOL IsBitmap(FILE* f);
    // Returns TRUE if the file is a PNG image, otherwise returns FALSE
    static BOOL IsPNG(FILE* f);
    // Returns TRUE if the file is a JPEG image, otherwise returns FALSE
    static BOOL IsJPEG(FILE* f);
    // Returns TRUE if the file is an image file, otherwise returns FALSE
    static BOOL IsImageFile(CString sFileName);

    // Loads the image from file
    BOOL Load(CString sFileName);
    // Cancels loading
    void Cancel();
    // Returns TRUE if image is valid, otherwise returns FALSE
    BOOL IsValid();  
    // Draws the image on the device context
    void Draw(HDC hDC, LPRECT prcDraw);

private:

    BOOL LoadBitmapFromBMPFile(LPTSTR szFileName);
    BOOL LoadBitmapFromPNGFile(LPTSTR szFileName);
    BOOL LoadBitmapFromJPEGFile(LPTSTR szFileName);

    CCritSec m_csLock;      // Critical section
    HBITMAP m_hBitmap;      // Handle to the bitmap.  
    HPALETTE m_hPalette;    // Palette
    BOOL m_bLoadCancelled;  // Load cancel flag
};

class CVideo
{
public:

	// Construction/destruction.
	CVideo();
	virtual ~CVideo();

	// Detects if the file is a video file.
	static BOOL IsVideoFile(LPCTSTR szFileName);

	// Checks if the file is an OGG container file
	static BOOL IsOGG(FILE* f);

	// Loads video from file.
	BOOL Load(LPCTSTR szFileName);

	// Frees resources
	void Destroy();

	// Returns TRUE if video is valid, otherwise returns FALSE
    BOOL IsValid();

	// Sets position to zero-th frame.
	void Reset();

	// Decodes next video frame and returns pointer to bitmap.
	HBITMAP DecodeFrame(BOOL bFirstFrame, CSize& FrameSize, int& nDuration);

	void DrawFrame(HDC hDC, LPRECT prcDraw);

private:

	// Loads an OGG video
	BOOL LoadOggFile(LPCTSTR szFileName);

	BOOL ReadOGGPage();

	// Reads a page from OGG file
	BOOL ReadOGGPacket();

	// Creates a DIB bitmap
	BOOL CreateFrameDIB(DWORD dwWidth, DWORD dwHeight, int nBits);

	// Converts an YV12 image to RGB24 image.
	void YV12_To_RGB(unsigned char *pRGBData, int nFrameWidth, 
				int nFrameHeight, int nRGBStride, th_ycbcr_buffer raw );

	CCritSec m_csLock;      // Critical section
	CString m_sFileName;    // File currently loaded.
	FILE* m_pf;             // File handle.
	HBITMAP m_hbmpFrame;    // Video frame bitmap.
	LPVOID m_pFrameBits;    // Frame buffer.
	LPBITMAPINFO m_pDIB;    // Bitmap info.
	HDC m_hDC;              // Device context.
	HBITMAP m_hOldBitmap;   //	
	ogg_sync_state m_state;
	char* m_buf;
	ogg_page m_page;
	ogg_stream_state m_stream;
	ogg_packet m_packet;
	th_info m_info;
	th_comment m_comment;
	th_setup_info* m_psetup;
	th_dec_ctx* m_pctx;	
	ogg_int64_t m_pos;
	th_ycbcr_buffer m_raw;
	int m_nFrameWidth;
	int m_nFrameHeight;
	int m_nFrameInterval;
};

// This message is sent by file preview control when file loading is complete
#define WM_FPC_COMPLETE  (WM_APP+100)
#define WM_FPC_FRAMEAWAIL (WM_APP+101)

// File preview control
// A custom control derived from CStatic. Can preview files as hex, text and image
class CFilePreviewCtrl : public CWindowImpl<CFilePreviewCtrl, CStatic>
{
public:

    // Construction/destruction
    CFilePreviewCtrl();
    ~CFilePreviewCtrl();

    DECLARE_WND_SUPERCLASS(NULL, CWindow::GetWndClassName())

    BEGIN_MSG_MAP(CFilePreviewCtrl)  
        if (uMsg == WM_NCHITTEST || 
            uMsg == WM_NCLBUTTONDOWN || 
            uMsg == WM_NCLBUTTONDBLCLK ||
            uMsg == WM_NCMBUTTONDOWN ||
            uMsg == WM_NCXBUTTONDOWN)
        {
            // This is to enable scroll bar messages
            bHandled = TRUE;
            lResult = ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
            return TRUE;
        }

        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
            MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
            MESSAGE_HANDLER(WM_PAINT, OnPaint)
            MESSAGE_HANDLER(WM_SIZE, OnSize)
            MESSAGE_HANDLER(WM_HSCROLL, OnHScroll)
            MESSAGE_HANDLER(WM_VSCROLL, OnVScroll)
            MESSAGE_HANDLER(WM_TIMER, OnTimer)
            MESSAGE_HANDLER(WM_FPC_COMPLETE, OnComplete)			
            MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
            MESSAGE_HANDLER(WM_RBUTTONUP, OnRButtonUp)
            MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
    END_MSG_MAP()

    // Returns file name
    LPCTSTR GetFile();

    // Sets file for preview
    BOOL SetFile(LPCTSTR szFileName, PreviewMode mode=PREVIEW_AUTO, TextEncoding enc = ENC_AUTO);

    // Returns current preview mode
    PreviewMode GetPreviewMode();

    // Sets preview mode
    void SetPreviewMode(PreviewMode mode);

    // Returns text encoding
    TextEncoding GetTextEncoding();

    // Sets text encoding
    void SetTextEncoding(TextEncoding enc);

    // Sets the text that will be displayed as "No data to display" message
    void SetEmptyMessage(CString sText);

    // Sets the width of HEX preview
    BOOL SetBytesPerLine(int nBytesPerLine);

    // Returns the preview mode for the file
    PreviewMode DetectPreviewMode(LPCTSTR szFileName);

    // Detects what text encoding to use for the file
    TextEncoding DetectTextEncoding(LPCTSTR szFileName, int& nSignatureLen);

    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnHScroll(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnVScroll(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnComplete(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);	
    LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnRButtonUp(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnMouseWheel(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);

    void SetupScrollbars();
    CString FormatHexLine(LPBYTE pData, int nBytesInLine, ULONG64 uLineOffset);
    void DrawHexLine(HDC hdc, DWORD nLineNo);
    void DrawTextLine(HDC hdc, DWORD nLineNo);  
    void DoPaintEmpty(HDC hDC);
    void DoPaintText(HDC hDC);
    void DoPaintBitmap(HDC hDC);
	void DoPaintVideo(HDC hDC);
    void DoPaint(HDC hDC);

    // Used internally to performs some work assynchronously
    static DWORD WINAPI WorkerThread(LPVOID lpParam);  
    void DoInWorkerThread();

    // Parses text file assynchronously
    void ParseText();

    // Loads bitmap assynchronously
    void LoadBitmap();

	// Laods video assynchronously
	void LoadVideo();

    CString m_sFileName;         // File name.
    PreviewMode m_PreviewMode;   // File preview mode.
    TextEncoding m_TextEncoding; // Text encoding (if in text preview mode).
    int m_nEncSignatureLen;      // Length of the text encoding signature. 
    CCritSec m_csLock;           // Sync object.
    CFileMemoryMapping m_fm;     // File mapping object.  
    HFONT m_hFont;               // Font in use.  
    int m_xChar;                 // Size of character in x direction.
    int m_yChar;                 // Size of character in y direction.
    int m_nMaxColsPerPage;       // Maximum columns per page.
    int m_nMaxLinesPerPage;      // Maximum count of lines per one page.
    int m_nMaxDisplayWidth;      // Maximum display width
    ULONG64 m_uNumLines;         // Number of lines in the file.	
    int m_nBytesPerLine;         // Count of displayed bytes per line.
    int m_cchTabLength;          // Length of the tab, in characters
    CString m_sEmptyMsg;         // Text to display when file is empty
    int m_nHScrollPos;           // Horizontal scroll position.
    int m_nHScrollMax;           // Max horizontal scroll position.
    int m_nVScrollPos;           // Vertical scrolling position.
    int m_nVScrollMax;           // Maximum vertical scrolling position.  
    std::vector<DWORD> m_aTextLines; // The array of lines of text file.
    HANDLE m_hWorkerThread;      // Handle to the worker thread.
    BOOL m_bCancelled;           // Is worker thread cancelled?
    CImage m_bmp;                // Stores the bitmap.
	CVideo m_video;              // Stores the decoded video.
};



