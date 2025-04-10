/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

#ifndef __SCREENCAP_H__
#define __SCREENCAP_H__

#include "stdafx.h"

extern "C" {
#include "png.h"
}
#include "jpeglib.h"

// Window information
struct WindowInfo
{
    CString m_sTitle; // Window title
    CRect m_rcWnd;    // Window rect
    DWORD dwStyle;
    DWORD dwExStyle;
};

// Monitor info
struct MonitorInfo
{
    CString m_sDeviceID; // Device ID
    CRect m_rcMonitor;   // Monitor rectangle in screen coordinates
    CString m_sFileName; // Image file name corresponding to this monitor
};

// Desktop screen shot info
struct ScreenshotInfo
{
	// Constructor
    ScreenshotInfo()
    {
        m_bValid = FALSE;
    }

    BOOL m_bValid;           // If TRUE, this structure's fields are valid.
	time_t m_CreateTime;     // Time of screenshot capture.
    CRect m_rcVirtualScreen; // Coordinates of virtual screen rectangle.
    std::vector<MonitorInfo> m_aMonitors; // The list of monitors captured.
    std::vector<WindowInfo> m_aWindows; // The list of windows captured.	
};

// Screenshot type
enum SCREENSHOT_TYPE
{
	SCREENSHOT_TYPE_VIRTUAL_SCREEN      = 0, // Screenshot of entire desktop.
	SCREENSHOT_TYPE_MAIN_WINDOW         = 1, // Screenshot of given process' main window.
	SCREENSHOT_TYPE_ALL_PROCESS_WINDOWS = 2  // Screenshot of all process windows.
};

// What format to use when saving screenshots
enum SCREENSHOT_IMAGE_FORMAT
{
    SCREENSHOT_FORMAT_PNG = 0, // Use PNG format
    SCREENSHOT_FORMAT_JPG = 1, // Use JPG format
    SCREENSHOT_FORMAT_BMP = 2  // Use BMP format
};

// Desktop screenshot capture
class CScreenCapture
{
public:

    // Constructor.
    CScreenCapture();

	// Destructor.
    ~CScreenCapture();
	
	// Takes desktop screenshot and returns information about it.
	BOOL TakeDesktopScreenshot(	
			LPCTSTR szSaveToDir,
			ScreenshotInfo& ssi, 
			SCREENSHOT_TYPE type=SCREENSHOT_TYPE_VIRTUAL_SCREEN, 
			DWORD dwProcessId = 0, 
			SCREENSHOT_IMAGE_FORMAT fmt=SCREENSHOT_FORMAT_PNG,
			int nJpegQuality = 95,
			BOOL bGrayscale=FALSE,
			int nIdStartFrom=0);

private:

	// Returns current virtual screen rectangle
    void GetScreenRect(LPRECT rcScreen);

    // Returns an array of visible windows for the specified process or 
    // the main window of the process.
    BOOL FindWindows(DWORD dwProcessId, BOOL bAllProcessWindows, 
        std::vector<WindowInfo>* paWindows);

    // Captures the specified screen area and returns the list of image files
    BOOL CaptureScreenRect(
        std::vector<CRect> arcCapture, 
        CString sSaveDirName, 
        int nIdStartFrom, 
        SCREENSHOT_IMAGE_FORMAT fmt, 
        int nJpegQuality,
        BOOL bGrayscale,
        std::vector<MonitorInfo>& monitor_list);

	// Monitor enumeration callback.
	static BOOL CALLBACK EnumMonitorsProc(HMONITOR hMonitor, 
		HDC /*hdcMonitor*/, LPRECT lprcMonitor, LPARAM dwData);

	// Window enumeration callback.
	static BOOL CALLBACK EnumWndProc(HWND hWnd, LPARAM lParam);

    /* PNG management functions */

    // Initializes PNG file header
    BOOL PngInit(int nWidth, int nHeight, BOOL bGrayscale, CString sFileName);

    // Writes a scan line to the PNG file
    BOOL PngWriteRow(LPBYTE pRow, int nRowLen, BOOL bGrayscale);

    // Closes PNG file
    BOOL PngFinalize();

    /* JPEG management functions */

	// Initializes JPEG file header.
    BOOL JpegInit(int nWidth, int nHeight, BOOL bGrayscale, int nQuality, CString sFileName);

	// Writes a scan line to JPEG file.
    BOOL JpegWriteRow(LPBYTE pRow, int nRowLen, BOOL bGrayscale);

	// Closes PNG file.
    BOOL JpegFinalize();

	/* BMP management functions */

	// Initializes BMP file header
    BOOL BmpInit(int nWidth, int nHeight, BOOL bGrayscale, CString sFileName);

    // Writes a scan line to the BMP file
    BOOL BmpWriteRow(LPBYTE pRow, int nRowLen, BOOL bGrayscale);

    // Closes BMP file
    BOOL BmpFinalize();

	// The following structure stores window find data.
	struct FindWindowData
	{
		DWORD dwProcessId;                   // Process ID.
		BOOL bAllProcessWindows;             // If TRUE, finds all process windows, else only the main one
		std::vector<WindowInfo>* paWindows;  // Output array of window handles
	};

    /* Internal member variables. */

    CPoint m_ptCursorPos;                 // Current mouse cursor pos
    std::vector<CRect> m_arcCapture;      // Array of capture rectangles
    CURSORINFO m_CursorInfo;              // Cursor info  
    int m_nIdStartFrom;                   // An ID for the current screenshot image 
    CString m_sSaveDirName;               // Directory name to save screenshots to
    SCREENSHOT_IMAGE_FORMAT m_fmt;        // Image format
    int m_nJpegQuality;                   // Jpeg quality
    BOOL m_bGrayscale;                    // Create grayscale image or not
    FILE* m_fp;                           // Handle to the file
    png_structp m_png_ptr;                // libpng stuff
    png_infop m_info_ptr;                 // libpng stuff
    struct jpeg_compress_struct m_cinfo;  // libjpeg stuff
    struct jpeg_error_mgr m_jerr;         // libjpeg stuff
    std::vector<MonitorInfo> m_monitor_list; // The list of monitor devices   
};

#endif //__SCREENCAP_H__


