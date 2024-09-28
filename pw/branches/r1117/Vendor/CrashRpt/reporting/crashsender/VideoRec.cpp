/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// File: VideoRec.cpp
// Description: Video recording functionality.
// Authors: zexspectrum
// Date: Sep 2013

#include "stdafx.h"
#include "VideoRec.h"
#include "Utility.h"
#include "math.h"

static int ilog(unsigned _v){
  int ret;
  for(ret=0;_v;ret++)_v>>=1;
  return ret;
}

//-----------------------------------------------
// CVideoRecorder impl
//-----------------------------------------------

CVideoRecorder::CVideoRecorder()
{
	m_ScreenshotType = SCREENSHOT_TYPE_VIRTUAL_SCREEN;
	m_nVideoDuration = 60000;
	m_nVideoFrameInterval = 300;
	m_dwProcessId = 0;
	m_nFrameCount = 0;
	m_nFileId = 0;
	m_nFrameId = 0;
	m_nVideoQuality = 5;
	m_DesiredFrameSize.cx = 0;
	m_DesiredFrameSize.cy = 0;
	m_hbmpFrame = NULL;
	m_pFrameBits = NULL;
	m_pDIB = NULL;
	m_bInitialized = FALSE;
}

CVideoRecorder::~CVideoRecorder()
{
	Destroy();
}

BOOL CVideoRecorder::Init(LPCTSTR szSaveToDir, 
	SCREENSHOT_TYPE type,
	DWORD dwProcessId,
	int nVideoDuration,
	int nVideoFrameInterval,
	int nVideoQuality,
	SIZE* pDesiredFrameSize)
{
	// Validate input params
	if(nVideoDuration<=0 || nVideoFrameInterval<=0)
	{
		// Invalid arg
		return FALSE;
	}
	
	// Save params
	m_sSaveToDir = szSaveToDir;
	m_ScreenshotType = type;
	m_nVideoDuration = nVideoDuration;	
	m_nVideoFrameInterval = nVideoFrameInterval;
	m_nVideoQuality = nVideoQuality;
	m_dwProcessId = dwProcessId;

	// Save desired frame size
	if(pDesiredFrameSize)
		m_DesiredFrameSize = *pDesiredFrameSize;
	else
	{
		m_DesiredFrameSize.cx = 0; // auto
		m_DesiredFrameSize.cy = 0;
	}

	// Calculate max frame count
	m_nFrameCount = m_nVideoDuration/m_nVideoFrameInterval;
	m_nFileId = 0;
	m_nFrameId = 0;

	// Create folder where to save video frames
	CString sDirName = m_sSaveToDir + _T("\\~temp_video");
	if(!Utility::CreateFolder(sDirName))
	{
		// Error creating temp folder
		return FALSE;
	}

	// Done
	m_bInitialized = TRUE;
	return TRUE;
}

BOOL CVideoRecorder::IsInitialized()
{
	return m_bInitialized;
}

void CVideoRecorder::Destroy()
{
	// Remove temp files
	if(!m_sSaveToDir.IsEmpty())
	{
		CString sDirName = m_sSaveToDir + _T("\\~temp_video");
		Utility::RecycleFile(sDirName, TRUE);
	}

	m_bInitialized=FALSE;
}

BOOL CVideoRecorder::RecordVideoFrame()
{
	// The following method records a single video frame and returns.

	ScreenshotInfo ssi; // Screenshot params    

	CString sDirName = m_sSaveToDir + _T("\\~temp_video");

	// Take the screen shot and save it as raw BMP file.
	BOOL bTakeScreenshot = m_sc.TakeDesktopScreenshot(		
		sDirName, 
		ssi, m_ScreenshotType, m_dwProcessId, 
		SCREENSHOT_FORMAT_BMP, 0, FALSE, m_nFileId);
	if(bTakeScreenshot==FALSE)
	{
		// Failed to take screenshot
		return FALSE;
	}

	// Save video frame info
	SetVideoFrameInfo(m_nFrameId, ssi);

	// Increment file ID
	m_nFileId += (int)ssi.m_aMonitors.size();

	// Increment frame number
	m_nFrameId++;

	// Reuse files cyclically
	if(m_nFrameId>=m_nFrameCount)
	{
		m_nFileId = 0;
		m_nFrameId = 0;					
	}

	return TRUE;
}

void CVideoRecorder::SetVideoFrameInfo(int nFrameId, ScreenshotInfo& ssi)
{
	if((int)m_aVideoFrames.size()<=nFrameId)
	{
		// Add frame to the end of sequence
		m_aVideoFrames.push_back(ssi);
	}
	else
	{
		// Replace existing frame

		/*size_t j;
		for(j=0; j<m_aVideoFrames[nFrameId].m_aMonitors.size(); j++)
		{
		Utility::RecycleFile(m_aVideoFrames[nFrameId].m_aMonitors[j].m_sFileName, TRUE);
		}*/

		m_aVideoFrames[nFrameId]=ssi;
	}
}

BOOL CVideoRecorder::EncodeVideo()
{	
	// This method encodes all raw BMP files
	// into a single OGG file.

	FILE* fout = NULL;
	ogg_stream_state to; /* take physical pages, weld into a logical
						 stream of packets */
	ogg_page         og; /* one Ogg bitstream page.  Vorbis packets are inside */
	ogg_packet       op; /* one raw packet of data for decode */

	th_enc_ctx      *td = NULL;
	th_info          ti;
	th_comment       tc;
	int frame_avail = 0;
	th_ycbcr_buffer raw;	
	int frame_cnt = 0;
	int nFrameWidth = 0;
	int nFrameHeight = 0;
	int ret = 1;
	
	memset(&to, 0, sizeof(to));
	memset(&og, 0, sizeof(og));
	memset(&op, 0, sizeof(op));
	memset(&tc, 0, sizeof(tc));

	// Clear frame buffer
	memset(&raw, 0, sizeof(raw));

	/* Determine max screen size, it will define frame width and height */
	SIZE ScreenSize={0,0};
	size_t i;
	for(i=0; i<m_aVideoFrames.size(); i++)
	{
		ScreenshotInfo& ssi = m_aVideoFrames[i];
		if(ScreenSize.cx<ssi.m_rcVirtualScreen.right ||
			ScreenSize.cy<ssi.m_rcVirtualScreen.bottom)
		{
			ScreenSize.cx = ssi.m_rcVirtualScreen.right;
			ScreenSize.cy = ssi.m_rcVirtualScreen.bottom;
		}
	}
	
	// Check if desired frame size is not specified
	if(m_DesiredFrameSize.cx==0 && m_DesiredFrameSize.cy==0)
	{
		// Determine frame size automatically
		nFrameWidth = ScreenSize.cx;
		nFrameHeight = ScreenSize.cy;
	}
	else
	{
		// Use desired frame size, but we need to calculate
		// correct frame width/height based on aspect ratio of the screen.

		if(m_DesiredFrameSize.cx!=0)
			nFrameWidth=m_DesiredFrameSize.cx;
		if(m_DesiredFrameSize.cy!=0)
			nFrameHeight=m_DesiredFrameSize.cy;

		float ratio = (float)ScreenSize.cx/(float)ScreenSize.cy;
		if(m_DesiredFrameSize.cx==0)
		{
			nFrameWidth = (int)ceil(nFrameHeight*ratio-0.5f);
		}
		else if(m_DesiredFrameSize.cy!=0)
		{
			nFrameHeight = (int)ceil(nFrameWidth/ratio-0.5f);
		}
	}
	
	/* Theora encoder has a divisible-by-sixteen restriction for the encoded frame size */
    /* scale the picture size up to the nearest /16 and calculate offsets */
    nFrameWidth=nFrameWidth+15&~0xF;
    nFrameHeight=nFrameHeight+15&~0xF;
    
	/* Set up Ogg output stream */
    srand((unsigned int)time(NULL));
    ogg_stream_init(&to,rand());                                                              
		
	// Fill in a th_info structure with details on the format of the video you wish to encode.
	th_info_init(&ti);
    ti.frame_width=nFrameWidth;
    ti.frame_height=nFrameHeight;
    ti.pic_width=nFrameWidth;
    ti.pic_height=nFrameHeight;
    ti.pic_x=0;
    ti.pic_y=0;
    ti.fps_numerator=1000;
    ti.fps_denominator=m_nVideoFrameInterval;
    ti.aspect_numerator=0;
    ti.aspect_denominator=0;
    ti.colorspace=TH_CS_UNSPECIFIED;
    ti.target_bitrate=0; // VBR mode at specified video quality
    ti.quality=m_nVideoQuality; 
    ti.keyframe_granule_shift=6;
    ti.pixel_fmt=TH_PF_420;
   
	// Allocate a th_enc_ctx handle with th_encode_alloc().
    td=th_encode_alloc(&ti);
    th_info_clear(&ti);
	
	/*Allocate YV12 image */
	int nDataSize = (nFrameWidth*nFrameHeight*3)/2;
	unsigned char* pImageData = new unsigned char[nDataSize]; 
	raw[0].data = pImageData;
	raw[0].width = nFrameWidth;
	raw[0].height = nFrameHeight;
	raw[0].stride = nFrameWidth;
	raw[1].data = pImageData+nFrameWidth*nFrameHeight;
	raw[1].width = nFrameWidth/2;
	raw[1].height = nFrameHeight/2;
	raw[1].stride = nFrameWidth/2;
	raw[2].data = pImageData+nFrameWidth*nFrameHeight*5/4;
	raw[2].width = nFrameWidth/2;
	raw[2].height = nFrameHeight/2;
	raw[2].stride = nFrameWidth/2;
	
	/*Open output file */
	CString sFileName = m_sSaveToDir + _T("\\video.ogg");
	m_sOutFile = sFileName;
	_tfopen_s(&fout, sFileName, _T("wb"));
	if(fout==NULL)
		goto cleanup;

	/* write the bitstream header packets with proper page interleave */
    th_comment_init(&tc);
	// Repeatedly call th_encode_flushheader() to retrieve all the header packets.
    // first packet will get its own page automatically 
    if(th_encode_flushheader(td,&tc,&op)<=0)
	{
      // Internal Theora library error.
      goto cleanup;
    }

	/* Write OGG page */
	ogg_stream_packetin(&to,&op);
    if(ogg_stream_pageout(&to,&og)!=1)
	{
		goto cleanup;
	}
	fwrite(og.header,1,og.header_len,fout);
    fwrite(og.body,1,og.body_len,fout);

	/* create the remaining theora headers */
    for(;;)
	{
      ret=th_encode_flushheader(td,&tc,&op);
      if(ret<0)
	  {
        // Internal Theora library error
        goto cleanup;
      }
      else if(!ret)
		  break;
	  ogg_stream_packetin(&to,&op);
    }
		
	/* Write OGG page */
	for(;;)
	{
		int ret = ogg_stream_flush(&to,&og);
		if(ret==0)
			break;
		if(ret<0)
			goto cleanup;
		fwrite(og.header,1,og.header_len,fout);
		fwrite(og.body,1,og.body_len,fout);
	}
	
	/* Encode frames. */
	int nFrame = m_nFrameId; // Start with the oldest frame
	if(nFrame==(int)m_aVideoFrames.size())
		nFrame=0; // Start from the zeroth frame
	for( ; ; )
	{
		/* Compose frame */
		frame_avail = ComposeFrame(nFrame, &raw);

		// Encode frame
		if(th_encode_ycbcr_in(td, raw)) 
		{
			goto cleanup;
		}

		// Read packets
		while((ret = th_encode_packetout(td, !frame_avail, &op))!=0)
		{
			/* Write OGG page */
			ogg_stream_packetin(&to,&op);
			int ret = ogg_stream_pageout(&to,&og);
			if(ret<0)
				goto cleanup;
			if(ret!=0)
			{
				fwrite(og.header,1,og.header_len,fout);
				fwrite(og.body,1,og.body_len,fout);
			}
		}
	
		// Increment total encoded frame count
		if(frame_avail)
			frame_cnt++;
		else 
			break;

		// Increment frame index
		nFrame++;
		if(nFrame==(int)m_aVideoFrames.size())
			nFrame=0; // Start from the zeroth frame

		if(nFrame==m_nFrameId || frame_cnt>=(int)m_aVideoFrames.size())
			break; // All frames have been encoded
	}

	/* Write OGG page */
	for(;;)
	{
		int ret = ogg_stream_flush(&to,&og);
		if(ret==0)
			break;
		if(ret<0)
			goto cleanup;
		fwrite(og.header,1,og.header_len,fout);
		fwrite(og.body,1,og.body_len,fout);
	}
			
cleanup:

	/* Free codec resources */
	ogg_stream_clear(&to);
    th_comment_clear(&tc);
	th_encode_free(td);

	// Close file
	if(fout)
		fclose(fout);

	if(raw[0].data)
		delete [] raw[0].data;

	// Delete temp files.
	CString sDirName = m_sSaveToDir + _T("\\~temp_video");
	Utility::RecycleFile(sDirName, true);

	// Done
	return TRUE;
}

BOOL CVideoRecorder::ComposeFrame(int nFrameId, th_ycbcr_buffer *pImage)
{
	// This method composes several bitmaps into single frame image

	// Validate input
	if(nFrameId<0 || nFrameId>=(int)m_aVideoFrames.size())
		return FALSE;

	if(pImage==NULL)
		return FALSE;

	if(m_hbmpFrame==NULL)
	{
		// Calculate frame size

		CreateFrameDIB(pImage[0]->width, pImage[0]->height, 24);
	}

	// Walk through monitor bitmaps
	ScreenshotInfo& ssi = m_aVideoFrames[nFrameId];
	size_t i;
	for(i=0; i<ssi.m_aMonitors.size(); i++)
	{
		// Load image from BMP
		CString sFileName = ssi.m_aMonitors[i].m_sFileName;
		HBITMAP hBitmap = LoadBitmapFromBMPFile(sFileName);
		if(hBitmap)
		{
			// Create temp DC
			HDC hMemDC = CreateCompatibleDC(m_hDC);
			// Select loaded bitmap into DC
			HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

			float x_ratio = (float)pImage[0]->width/(float)ssi.m_rcVirtualScreen.Width();
			float y_ratio = (float)pImage[0]->height/(float)ssi.m_rcVirtualScreen.Height();
			int xDest = (int)ceil(ssi.m_aMonitors[i].m_rcMonitor.left*x_ratio-0.5);
			int yDest = (int)ceil(ssi.m_aMonitors[i].m_rcMonitor.top*y_ratio-0.5);
			int wDest = (int)ceil(ssi.m_aMonitors[i].m_rcMonitor.Width()*x_ratio-0.5);
			int hDest = (int)ceil(ssi.m_aMonitors[i].m_rcMonitor.Height()*y_ratio-0.5);

			// Copy bitmap to its destination rect
			int nOldMode = SetStretchBltMode(m_hDC, HALFTONE);
			StretchBlt(m_hDC, xDest, yDest, wDest, hDest, hMemDC, 0, 0, 
				ssi.m_aMonitors[i].m_rcMonitor.Width(), ssi.m_aMonitors[i].m_rcMonitor.Height(), SRCCOPY);
			SetStretchBltMode(m_hDC, nOldMode);

			// Select old bitmap into DC
			SelectObject(hMemDC, hOldBitmap);
			// Free DC
			DeleteDC(hMemDC);
			// Free loaded bitmap
			DeleteObject(hBitmap);
		}		
	}

	// Convert RGB to YV12
	RGB_To_YV12((unsigned char*)m_pFrameBits, 
		pImage[0]->width, pImage[0]->height, 
		pImage[0]->width*3+(pImage[0]->width*3)%4, 
		(*pImage)[0].data, (*pImage)[1].data, (*pImage)[2].data);

	return TRUE;
}

BOOL CVideoRecorder::CreateFrameDIB(DWORD dwWidth, DWORD dwHeight, int nBits)
{
	if (m_pDIB) 
		return FALSE;

	const DWORD dwcBihSize = sizeof(BITMAPINFOHEADER);

	// Calculate the memory required for the DIB
	DWORD dwSize = dwcBihSize +
		(2>>nBits) * sizeof(RGBQUAD) +
		((nBits * dwWidth) * dwHeight);

	m_pDIB = (LPBITMAPINFO)new BYTE[dwSize];
	if (!m_pDIB) 
		return FALSE;


	m_pDIB->bmiHeader.biSize = dwcBihSize;
	m_pDIB->bmiHeader.biWidth = dwWidth;
	m_pDIB->bmiHeader.biHeight = -(LONG)dwHeight;
	m_pDIB->bmiHeader.biBitCount = (WORD)nBits;
	m_pDIB->bmiHeader.biPlanes = 1;
	m_pDIB->bmiHeader.biCompression = BI_RGB;
	m_pDIB->bmiHeader.biXPelsPerMeter = 1000;
	m_pDIB->bmiHeader.biYPelsPerMeter = 1000;
	m_pDIB->bmiHeader.biClrUsed = 0;
	m_pDIB->bmiHeader.biClrImportant = 0;

	LPRGBQUAD lpColors =
		(LPRGBQUAD)(m_pDIB+m_pDIB->bmiHeader.biSize);
	int nColors=2>>m_pDIB->bmiHeader.biBitCount;
	for(int i=0;i<nColors;i++)
	{
		lpColors[i].rgbRed=0;
		lpColors[i].rgbBlue=0;
		lpColors[i].rgbGreen=0;
		lpColors[i].rgbReserved=0;
	}

	m_hDC = CreateCompatibleDC(GetDC(NULL));

	m_hbmpFrame = CreateDIBSection(m_hDC, m_pDIB, DIB_RGB_COLORS, &m_pFrameBits,
		NULL, 0);

	m_hOldBitmap = (HBITMAP)SelectObject(m_hDC, m_hbmpFrame);

	return TRUE;
}

HBITMAP CVideoRecorder::LoadBitmapFromBMPFile(LPCTSTR szFileName)
{
	// This method loads a BMP file.

	// Use LoadImage() to get the image loaded into a DIBSection
	HBITMAP hBitmap = (HBITMAP)LoadImage( NULL, szFileName, IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );

	return hBitmap;
}

CString CVideoRecorder::GetOutFile()
{
	return m_sOutFile;
}

void CVideoRecorder::RGB_To_YV12( unsigned char *pRGBData, int nFrameWidth, 
	int nFrameHeight, int nRGBStride, unsigned char *pFullYPlane, 
	unsigned char *pDownsampledUPlane, 
	unsigned char *pDownsampledVPlane )
{
	// Convert RGB -> YV12. We do this in-place to avoid allocating any more memory.
	unsigned char *pYPlaneOut = (unsigned char*)pFullYPlane;
	int nYPlaneOut = 0;

	int x, y;
	for(y=0; y<nFrameHeight;y++)
	{
		for (x=0; x < nFrameWidth; x ++)
		{
			int nRGBOffs = y*nRGBStride+x*3;

			unsigned char B = pRGBData[nRGBOffs+0];
			unsigned char G = pRGBData[nRGBOffs+1];
			unsigned char R = pRGBData[nRGBOffs+2];

			float y = (float)( R*66 + G*129 + B*25 + 128 ) / 256 + 16;
			float u = (float)( R*-38 + G*-74 + B*112 + 128 ) / 256 + 128;
			float v = (float)( R*112 + G*-94 + B*-18 + 128 ) / 256 + 128;

			// NOTE: We're converting pRGBData to YUV in-place here as well as writing out YUV to pFullYPlane/pDownsampledUPlane/pDownsampledVPlane.
			pRGBData[nRGBOffs+0] = (unsigned char)y;
			pRGBData[nRGBOffs+1] = (unsigned char)u;
			pRGBData[nRGBOffs+2] = (unsigned char)v;

			// Write out the Y plane directly here rather than in another loop.
			pYPlaneOut[nYPlaneOut++] = pRGBData[nRGBOffs+0];
		}
	}

	// Downsample to U and V.
	int halfHeight = nFrameHeight/2;
	int halfWidth = nFrameWidth/2;
		
	for ( int yPixel=0; yPixel < halfHeight; yPixel++ )
	{
		int iBaseSrc = ( (yPixel*2) * nRGBStride );

		for ( int xPixel=0; xPixel < halfWidth; xPixel++ )
		{
			pDownsampledVPlane[yPixel * halfWidth + xPixel] = pRGBData[iBaseSrc + 2];
			pDownsampledUPlane[yPixel * halfWidth + xPixel] = pRGBData[iBaseSrc + 1];

			iBaseSrc += 6;
		}
	}
}