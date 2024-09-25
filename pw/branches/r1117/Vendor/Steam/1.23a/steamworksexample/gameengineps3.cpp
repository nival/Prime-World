//========= Copyright © 1996-2008, Valve LLC, All rights reserved. ============
//
// Purpose: Main class for the game engine -- win32 implementation
//
// $NoKeywords: $
//=============================================================================

#include "stdafx.h"
#include "GameEnginePS3.h"
#include <map>
#include <cell/sysmodule.h>

// Allocate static member
std::map<void *, CGameEnginePS3* > CGameEnginePS3::m_MapEngineInstances;

// How big is the vertex buffer for batching lines in total?
#define LINE_BUFFER_TOTAL_SIZE 1000

// How big is the vertex buffer for batching points in total?
#define POINT_BUFFER_TOTAL_SIZE 1800

// How big is the vertex buffer for batching quads in total?
#define QUAD_BUFFER_TOTAL_SIZE 1000

// Only a single global console can be setup for output, track that here
CellDbgFontConsoleId g_DbgFontConsoleID = -1;

//-----------------------------------------------------------------------------
// Purpose: PS3 callback handler
//-----------------------------------------------------------------------------
static void PS3SysutilCallback( uint64_t status, uint64_t param, void* userdata )
{
	(void) param;

	CGameEnginePS3 *pGameEngine = CGameEnginePS3::FindEngineInstanceForPtr( userdata );

	switch( status ) 
	{
		case CELL_SYSUTIL_REQUEST_EXITGAME:
			pGameEngine->Shutdown();
			break;
		case CELL_SYSUTIL_DRAWING_BEGIN:
		case CELL_SYSUTIL_DRAWING_END:
			break;
		case CELL_SYSUTIL_SYSTEM_MENU_OPEN:
			OutputDebugString( "System menu opened!\n" );
			break;
		case CELL_SYSUTIL_SYSTEM_MENU_CLOSE:
			OutputDebugString( "System menu closed!\n" );
			break;
		default:
			OutputDebugString( "PS3SysutilCallback: Unknown status received\n" );
	}
}


//-----------------------------------------------------------------------------
// Purpose: Constructor for game engine instance
//-----------------------------------------------------------------------------
CGameEnginePS3::CGameEnginePS3()
{
	m_bEngineReadyForUse = false;
	m_bShuttingDown = false;
	m_nWindowWidth = 0;
	m_nWindowHeight = 0;
	m_ulPreviousGameTickCount = 0;
	m_ulGameTickCount = 0;
	m_hTextureWhite = 0;
	m_pPSGLContext = NULL;
	m_pPSGLDevice = NULL;
	m_DbgFontConsoleID = -1;
	m_nNextFontHandle = 1;
	m_nNextTextureHandle = 1;
	m_hLastTexture = 0;

	m_rgflPointsData = new GLfloat[ 3*POINT_BUFFER_TOTAL_SIZE ];
	m_rgflPointsColorData = new GLubyte[ 4*POINT_BUFFER_TOTAL_SIZE ];
	m_dwPointsToFlush = 0;

	m_rgflLinesData = new GLfloat[ 6*LINE_BUFFER_TOTAL_SIZE ];
	m_rgflLinesColorData = new GLubyte[ 8*LINE_BUFFER_TOTAL_SIZE ];
	m_dwLinesToFlush = 0;

	m_rgflQuadsData = new GLfloat [ 12*QUAD_BUFFER_TOTAL_SIZE ];
	m_rgflQuadsColorData = new GLubyte[ 16*QUAD_BUFFER_TOTAL_SIZE ];
	m_rgflQuadsTextureData = new GLfloat[ 8*QUAD_BUFFER_TOTAL_SIZE ];
	m_dwQuadsToFlush = 0;


	CGameEnginePS3::AddInstanceToPtrMap( this );

	// Setup timing data
	m_ulGameTickCount = cell::fios::FIOSAbstimeToMilliseconds( cell::fios::FIOSGetCurrentTime() );

	// Register sysutil exit callback
	int ret = cellSysutilRegisterCallback( 0, PS3SysutilCallback, this );
	if( ret != CELL_OK ) 
	{
		OutputDebugString( "!! Registering sysutil callback failed...\n" );
		return;
	}

	if( !BInitializePSGL() )
	{
		OutputDebugString( "!! Initializing PSGL failed\n" );
		return;
	}

	if( !BInitializeCellDbgFont() )
	{
		OutputDebugString( "!! Initializing CellDbgFont failed\n" );
		return;
	}


	// 7 is the magic maximum number of controllers
	if ( !BInitializeLibPad() )
	{
		OutputDebugString( "!! Initializing libpad failed\n" );
		return;
	}
	
	m_bEngineReadyForUse = true;
}


//-----------------------------------------------------------------------------
// Purpose: Shutdown the game engine
//-----------------------------------------------------------------------------
void CGameEnginePS3::Shutdown()
{
	// Flag that we are shutting down so the frame loop will stop running
	m_bShuttingDown = true;

	// Shutdown dbg font library
	if ( m_DbgFontConsoleID >= 0 )
	{
		cellDbgFontConsoleClose( m_DbgFontConsoleID );
		cellDbgFontExit();
	}

	// Should be safe to call even if we didn't actually init.
	cellPadEnd();

	// PS3 docs say it's best not to call this and allow the os/vshell to handle it instead to avoid brief noise
	// in the video display

	if ( m_rgflPointsData )
	{
		delete[] m_rgflPointsData;
		m_rgflPointsData = NULL;
	}

	if ( m_rgflPointsColorData )
	{
		delete[] m_rgflPointsColorData;
		m_rgflPointsColorData = NULL;
	}

	if ( m_rgflLinesData )
	{
		delete[] m_rgflLinesData;
		m_rgflLinesData = NULL;
	}

	if ( m_rgflLinesColorData )
	{
		delete[] m_rgflLinesColorData;
		m_rgflLinesColorData = NULL;
	}

	if ( m_rgflQuadsData )
	{
		delete[] m_rgflQuadsData;
		m_rgflQuadsData = NULL;
	}

	if ( m_rgflQuadsColorData )
	{
		delete[] m_rgflQuadsColorData;
		m_rgflQuadsColorData = NULL;
	}

	if ( m_rgflQuadsTextureData )
	{
		delete[] m_rgflQuadsTextureData;
		m_rgflQuadsTextureData = NULL;
	}

	m_dwLinesToFlush = 0;
	m_dwPointsToFlush = 0;
	m_dwQuadsToFlush = 0;

	/*

	// PS3 docs say it's best not to call this and allow the os/vshell to handle it instead to avoid brief noise
	// in the video display.  Should we not do this then?
	//
	// bugbug jmccaskey - don't do this?
	if ( m_pPSGLDevice )
	{
		psglMakeCurrent( NULL, m_pPSGLDevice );
		if ( m_pPSGLContext )
		{
			psglDestroyContext( m_pPSGLContext );
			m_pPSGLContext = NULL;
		}

		psglDestroyDevice( m_pPSGLDevice );
		m_pPSGLDevice = NULL;
	}

	psglExit();

	*/
}


//-----------------------------------------------------------------------------
// Purpose: Initialize libpad for controller input
//-----------------------------------------------------------------------------
bool CGameEnginePS3::BInitializeLibPad()
{
	int ret = cellPadInit( CELL_PAD_MAX_PORT_NUM );
	if ( ret != CELL_OK )
		return false;

	// We don't use pressure sensitivity or sixaxis
	for ( int i=0; i<CELL_PAD_MAX_PORT_NUM; ++i )
	{
		// May be we don't have all ports connected, but this setting will be set and persist anyway
		cellPadSetPortSetting( i, CELL_PAD_SETTING_PRESS_OFF | CELL_PAD_SETTING_SENSOR_OFF );
	}

	return true;
}


//-----------------------------------------------------------------------------
// Purpose: Initialize the PSGL rendering interfaces and default state
//-----------------------------------------------------------------------------
bool CGameEnginePS3::BInitializePSGL()
{
	// Clear any errors
	glGetError();

	// First, initialize PSGL
	// Note that since we initialized the SPUs ourselves earlier we should
	// make sure that PSGL doesn't try to do so as well.
	PSGLinitOptions initOpts = {
		enable: PSGL_INIT_MAX_SPUS | PSGL_INIT_INITIALIZE_SPUS | PSGL_INIT_HOST_MEMORY_SIZE,
		maxSPUs: 1,
		initializeSPUs: false,
						// We're not specifying values for these options, the code is only here
						// to alleviate compiler warnings.
		persistentMemorySize: 0,
		transientMemorySize: 0,
		errorConsole: 0,
		fifoSize: 0,	
		hostMemorySize: 128*1024*1024,  // 128 mbs for host memory 
	};

	psglInit( &initOpts );

	m_pPSGLDevice = psglCreateDeviceAuto( GL_ARGB_SCE, GL_DEPTH_COMPONENT24, GL_MULTISAMPLING_4X_SQUARE_ROTATED_SCE );
	if ( !m_pPSGLDevice )
	{
		OutputDebugString( "!! Failed to init the device \n" ); 
		return false;
	}

	GLuint width, height;
	psglGetDeviceDimensions( m_pPSGLDevice, &width, &height );
	m_nWindowHeight = height;
	m_nWindowWidth = width;

	// Now create a PSGL context
	m_pPSGLContext = psglCreateContext();
	if ( !m_pPSGLContext ) 
	{
		OutputDebugString( "Error creating PSGL context\n" );
		return false;
	}

	// Make this context current for the device we initialized
	psglMakeCurrent( m_pPSGLContext, m_pPSGLDevice );

	// Since we're using fixed function stuff (i.e. not using our own shader
	// yet), we need to load shaders.bin that contains the fixed function 
	// shaders.
	psglLoadShaderLibrary( SYS_APP_HOME"/shaders.bin" );

	// Reset the context
	psglResetCurrentContext();

	glViewport( 0, 0, width, height );
	glScissor( 0, 0, width, height );
	glClearDepthf(1.0f);
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glEnable( GL_VSYNC_SCE );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glDisable( GL_CULL_FACE );
	glDisable( GL_ALPHA_TEST );
	glDisable( GL_STENCIL_TEST );
	glDisable( GL_SCISSOR_TEST );
	glDisable( GL_LIGHTING );
	glDisable( GL_DEPTH_TEST );
	glDisable( GL_FOG );

	glDepthMask( GL_FALSE );

	// We always need these two
	glEnableClientState( GL_COLOR_ARRAY );
	glEnableClientState( GL_VERTEX_ARRAY );

	// This we'll enable as needed
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );

	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrthof( 0, width, height, 0, -1.0f, 1.0f );
	glTranslatef( 0, 0, 0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glTranslatef( 0, 0, 0 );

	glMatrixMode( GL_TEXTURE );
	glLoadIdentity();
	glTranslatef( 0, 0, 0 );

	glDepthRangef( 0.0f, 1.0f );

	// PSGL doesn't clear the screen on startup, so let's do that here.
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	psglSwap();

	return true;
}


//-----------------------------------------------------------------------------
// Purpose: Initialize the debug font library
//-----------------------------------------------------------------------------
bool CGameEnginePS3::BInitializeCellDbgFont()
{
	// initialize debug font library, then open 2 consoles
	CellDbgFontConfig cfg;
	cfg.bufSize      = 4096;
	cfg.screenWidth  = m_nWindowWidth;
	cfg.screenHeight = m_nWindowHeight;
	if ( cellDbgFontInit( &cfg) != CELL_OK )
	{
		OutputDebugString( "Failed initializing CellDbgFont\n" );
	}

	CellDbgFontConsoleConfig ccfg0;
	ccfg0.posLeft     = 0.18f;
	ccfg0.posTop      = 0.82f;
	ccfg0.cnsWidth    = 128;
	ccfg0.cnsHeight   = 8;
	ccfg0.scale       = 0.65f;
	ccfg0.color       = 0xff0080ff;  // ABGR -> orange
	g_DbgFontConsoleID = m_DbgFontConsoleID = cellDbgFontConsoleOpen( &ccfg0 );
	if ( g_DbgFontConsoleID < 0 )
	{
		OutputDebugString( "Failed creating CellDbgFontConsole\n" );
	}

	return true;
}

//-----------------------------------------------------------------------------
// Purpose: Updates current tick count for the game engine
//-----------------------------------------------------------------------------
void CGameEnginePS3::UpdateGameTickCount()
{
	m_ulPreviousGameTickCount = m_ulGameTickCount;
	m_ulGameTickCount = cell::fios::FIOSAbstimeToMilliseconds( cell::fios::FIOSGetCurrentTime() );
}


//-----------------------------------------------------------------------------
// Purpose: Tell the game engine to sleep for a bit if needed to limit frame rate.  You must keep
// calling this repeatedly until it returns false.  If it returns true it's slept a little, but more
// time may be needed.
//-----------------------------------------------------------------------------
bool CGameEnginePS3::BSleepForFrameRateLimit( uint32 ulMaxFrameRate )
{
	// Frame rate limiting
	float flDesiredFrameMilliseconds = 1000.0f/ulMaxFrameRate;

	uint64 ulGameTickCount = cell::fios::FIOSAbstimeToMilliseconds( cell::fios::FIOSGetCurrentTime() );

	float flMillisecondsElapsed = (float)(ulGameTickCount - m_ulGameTickCount);
	if ( flMillisecondsElapsed < flDesiredFrameMilliseconds )
	{
		// If enough time is left sleep, otherwise just keep spinning so we don't go over the limit...
		if ( flDesiredFrameMilliseconds - flMillisecondsElapsed > 3.0f )
		{
			sys_timer_usleep( 2000 );
		}
		else
		{
			// Just return right away so we busy loop, don't want to sleep too long and go over
		}

		return true;
	}
	else
	{
		return false;
	}
}


//-----------------------------------------------------------------------------
// Purpose: Set the background color to clear to
//-----------------------------------------------------------------------------
void CGameEnginePS3::SetBackgroundColor( short a, short r, short g, short b )
{
	glClearColor( (float)r/255.0f, (float)g/255.0f, (float)b/255.0f, (float)a/255.0f );
}

//-----------------------------------------------------------------------------
// Purpose: Start a new frame
//-----------------------------------------------------------------------------
bool CGameEnginePS3::StartFrame()
{
	// Pump PS3 system callbacks
	MessagePump();

	// We may now be shutting down, check and don't start a frame then
	if ( BShuttingDown() )
		return false;

	// Clear the screen for the new frame
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

	return true;
}


//-----------------------------------------------------------------------------
// Purpose: End the current frame
//-----------------------------------------------------------------------------
void CGameEnginePS3::EndFrame()
{
	if ( BShuttingDown() )
		return;

	if ( !m_pPSGLDevice )
		return;

	if ( !m_pPSGLContext )
		return;

	// Flush point buffer
	BFlushPointBuffer();

	// Flush line buffer
	BFlushLineBuffer();

	// Flush quad buffer
	BFlushQuadBuffer();

	// Flush dbg font data
	cellDbgFontDraw();

	// Swap buffers now that everything is flushed
	psglSwap();
}


//-----------------------------------------------------------------------------
// Purpose: Draw a line, the engine internally manages a vertex buffer for batching these
//-----------------------------------------------------------------------------
bool CGameEnginePS3::BDrawLine( float xPos0, float yPos0, DWORD dwColor0, float xPos1, float yPos1, DWORD dwColor1 )
{
	if ( !m_pPSGLContext || !m_pPSGLDevice || m_bShuttingDown )
		return false;


	// Check if we are out of room and need to flush the buffer
	if ( m_dwLinesToFlush == LINE_BUFFER_TOTAL_SIZE )	
	{
		BFlushLineBuffer();
	}

	DWORD dwOffset = m_dwLinesToFlush*6;
	m_rgflLinesData[dwOffset] = xPos0;
	m_rgflLinesData[dwOffset+1] = yPos0;
	m_rgflLinesData[dwOffset+2] = 1.0;
	m_rgflLinesData[dwOffset+3] = xPos1;
	m_rgflLinesData[dwOffset+4] = yPos1;
	m_rgflLinesData[dwOffset+5] = 1.0;

	dwOffset = m_dwLinesToFlush*8;
	m_rgflLinesColorData[dwOffset] = COLOR_RED( dwColor0 );
	m_rgflLinesColorData[dwOffset+1] = COLOR_GREEN( dwColor0 );
	m_rgflLinesColorData[dwOffset+2] = COLOR_BLUE( dwColor0 );
	m_rgflLinesColorData[dwOffset+3] = COLOR_ALPHA( dwColor0 );
	m_rgflLinesColorData[dwOffset+4] = COLOR_RED( dwColor1 );
	m_rgflLinesColorData[dwOffset+5] = COLOR_GREEN( dwColor1 );
	m_rgflLinesColorData[dwOffset+6] = COLOR_BLUE( dwColor1 );
	m_rgflLinesColorData[dwOffset+7] = COLOR_ALPHA( dwColor1 );

	++m_dwLinesToFlush;

	return true;
}


//-----------------------------------------------------------------------------
// Purpose: Flush batched lines to the screen
//-----------------------------------------------------------------------------
bool CGameEnginePS3::BFlushLineBuffer()
{
	if ( !m_pPSGLContext || !m_pPSGLDevice || !m_rgflLinesColorData || !m_rgflLinesData || m_bShuttingDown )
		return false;

	if ( m_dwLinesToFlush )
	{
		glColorPointer( 4, GL_UNSIGNED_BYTE, 0, m_rgflLinesColorData );
		glVertexPointer( 3, GL_FLOAT, 0, m_rgflLinesData );
		glDrawArrays( GL_LINES, 0, m_dwLinesToFlush*2 );

		m_dwLinesToFlush = 0;
	}

	return true;
}


//-----------------------------------------------------------------------------
// Purpose: Draw a point, the engine internally manages a vertex buffer for batching these
//-----------------------------------------------------------------------------
bool CGameEnginePS3::BDrawPoint( float xPos, float yPos, DWORD dwColor )
{
	
	if ( !m_pPSGLContext || !m_pPSGLDevice || m_bShuttingDown )
		return false;


	// Check if we are out of room and need to flush the buffer
	if ( m_dwPointsToFlush == POINT_BUFFER_TOTAL_SIZE )	
	{
		BFlushPointBuffer();
	}

	DWORD dwOffset = m_dwPointsToFlush*3;
	m_rgflPointsData[dwOffset] = xPos;
	m_rgflPointsData[dwOffset+1] = yPos;
	m_rgflPointsData[dwOffset+2] = 1.0;

	dwOffset = m_dwPointsToFlush*4;
	m_rgflPointsColorData[dwOffset] = COLOR_RED( dwColor );
	m_rgflPointsColorData[dwOffset+1] = COLOR_GREEN( dwColor );
	m_rgflPointsColorData[dwOffset+2] = COLOR_BLUE( dwColor );
	m_rgflPointsColorData[dwOffset+3] = COLOR_ALPHA( dwColor );

	++m_dwPointsToFlush;

	return true;
}


//-----------------------------------------------------------------------------
// Purpose: Flush batched points to the screen
//-----------------------------------------------------------------------------
bool CGameEnginePS3::BFlushPointBuffer()
{
	if ( !m_pPSGLContext || !m_pPSGLDevice || !m_rgflPointsColorData || !m_rgflPointsData || m_bShuttingDown )
		return false;

	if ( m_dwPointsToFlush )
	{
		glColorPointer( 4, GL_UNSIGNED_BYTE, 0, m_rgflPointsColorData );
		glVertexPointer( 3, GL_FLOAT, 0, m_rgflPointsData );
		glDrawArrays( GL_POINTS, 0, m_dwPointsToFlush );

		m_dwPointsToFlush = 0;
	}

	return true;
}


//-----------------------------------------------------------------------------
// Purpose: Draw a filled quad
//-----------------------------------------------------------------------------
bool CGameEnginePS3::BDrawFilledQuad( float xPos0, float yPos0, float xPos1, float yPos1, DWORD dwColor )
{
	if ( !m_hTextureWhite )
	{
		byte *pRGBAData = new byte[ 1 * 1 * 4 ];
		memset( pRGBAData, 255, 1*1*4 );
		m_hTextureWhite = HCreateTexture( pRGBAData, 1, 1 );
		delete[] pRGBAData;
	}

	return BDrawTexturedQuad( xPos0, yPos0, xPos1, yPos1, 0.0f, 0.0f, 1.0f, 1.0f, dwColor, m_hTextureWhite );
}


//-----------------------------------------------------------------------------
// Purpose: Draw a textured quad
//-----------------------------------------------------------------------------
bool CGameEnginePS3::BDrawTexturedQuad( float xPos0, float yPos0, float xPos1, float yPos1, float u0, float v0, float u1, float v1, DWORD dwColor, HGAMETEXTURE hTexture )
{
	if ( m_bShuttingDown || !m_pPSGLDevice || !m_pPSGLContext )
		return false;

	// Find the texture
	std::map<HGAMETEXTURE, TextureData_t>::iterator iter;
	iter = m_MapTextures.find( hTexture );
	if ( iter == m_MapTextures.end() )
	{
		OutputDebugString( "BDrawTexturedQuad called with invalid hTexture value\n" );
		return false;
	}

	// Check if we are out of room and need to flush the buffer, or if our texture is changing
	// then we also need to flush the buffer.
	if ( m_dwQuadsToFlush == QUAD_BUFFER_TOTAL_SIZE || m_hLastTexture != hTexture )	
	{
		BFlushQuadBuffer();
	}

	// Bind the new texture
	glBindTexture( GL_TEXTURE_2D, iter->second.m_uTextureID );

	DWORD dwOffset = m_dwQuadsToFlush*12;
	m_rgflQuadsData[dwOffset] = xPos0;
	m_rgflQuadsData[dwOffset+1] = yPos0;
	m_rgflQuadsData[dwOffset+2] = 1.0;
	m_rgflQuadsData[dwOffset+3] = xPos1;
	m_rgflQuadsData[dwOffset+4] = yPos0;
	m_rgflQuadsData[dwOffset+5] = 1.0;
	m_rgflQuadsData[dwOffset+6] = xPos1;
	m_rgflQuadsData[dwOffset+7] = yPos1;
	m_rgflQuadsData[dwOffset+8] = 1.0;
	m_rgflQuadsData[dwOffset+9] = xPos0;
	m_rgflQuadsData[dwOffset+10] = yPos1;
	m_rgflQuadsData[dwOffset+11] = 1.0;

	dwOffset = m_dwQuadsToFlush*16;
	m_rgflQuadsColorData[dwOffset] = COLOR_RED( dwColor );
	m_rgflQuadsColorData[dwOffset+1] = COLOR_GREEN( dwColor );
	m_rgflQuadsColorData[dwOffset+2] = COLOR_BLUE( dwColor );
	m_rgflQuadsColorData[dwOffset+3] = COLOR_ALPHA( dwColor );
	m_rgflQuadsColorData[dwOffset+4] = COLOR_RED( dwColor );
	m_rgflQuadsColorData[dwOffset+5] = COLOR_GREEN( dwColor );
	m_rgflQuadsColorData[dwOffset+6] = COLOR_BLUE( dwColor );
	m_rgflQuadsColorData[dwOffset+7] = COLOR_ALPHA( dwColor );
	m_rgflQuadsColorData[dwOffset+8] = COLOR_RED( dwColor );
	m_rgflQuadsColorData[dwOffset+9] = COLOR_GREEN( dwColor );
	m_rgflQuadsColorData[dwOffset+10] = COLOR_BLUE( dwColor );
	m_rgflQuadsColorData[dwOffset+11] = COLOR_ALPHA( dwColor );
	m_rgflQuadsColorData[dwOffset+12] = COLOR_RED( dwColor );
	m_rgflQuadsColorData[dwOffset+13] = COLOR_GREEN( dwColor );
	m_rgflQuadsColorData[dwOffset+14] = COLOR_BLUE( dwColor );
	m_rgflQuadsColorData[dwOffset+15] = COLOR_ALPHA( dwColor );

	dwOffset = m_dwQuadsToFlush*8;
	m_rgflQuadsTextureData[dwOffset] = u0;
	m_rgflQuadsTextureData[dwOffset+1] = v0;
	m_rgflQuadsTextureData[dwOffset+2] = u1;
	m_rgflQuadsTextureData[dwOffset+3] = v0;
	m_rgflQuadsTextureData[dwOffset+4] = u1;
	m_rgflQuadsTextureData[dwOffset+5] = v1;
	m_rgflQuadsTextureData[dwOffset+6] = u0;
	m_rgflQuadsTextureData[dwOffset+7] = v1;


	++m_dwQuadsToFlush;

	return true;
}


//-----------------------------------------------------------------------------
// Purpose: Flush buffered quads
//-----------------------------------------------------------------------------
bool CGameEnginePS3::BFlushQuadBuffer()
{
	if ( !m_pPSGLContext || !m_pPSGLDevice || !m_rgflPointsColorData || !m_rgflPointsData || m_bShuttingDown )
		return false;

	if ( m_dwQuadsToFlush )
	{
		glEnable( GL_TEXTURE_2D );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );

		glColorPointer( 4, GL_UNSIGNED_BYTE, 0, m_rgflQuadsColorData );
		glVertexPointer( 3, GL_FLOAT, 0, m_rgflQuadsData );
		glTexCoordPointer( 2, GL_FLOAT, 0, m_rgflQuadsTextureData );
		glDrawArrays( GL_QUADS, 0, m_dwQuadsToFlush*4 );

		glDisable( GL_TEXTURE_2D );
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );

		m_dwQuadsToFlush = 0;
	}

	return true;
}


//-----------------------------------------------------------------------------
// Purpose: Creates a new texture 
//-----------------------------------------------------------------------------
HGAMETEXTURE CGameEnginePS3::HCreateTexture( byte *pRGBAData, uint32 uWidth, uint32 uHeight )
{
	if ( m_bShuttingDown || !m_pPSGLDevice || !m_pPSGLContext )
		return 0;

	TextureData_t TexData;
	TexData.m_uWidth = uWidth;
	TexData.m_uHeight = uHeight;
	TexData.m_uTextureID = 0;

	glEnable( GL_TEXTURE_2D );
	glGenTextures( 1, &TexData.m_uTextureID );
	glBindTexture( GL_TEXTURE_2D, TexData.m_uTextureID );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0 );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0 );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

	// build our texture mipmaps
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, uWidth, uHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void *)pRGBAData );
	glDisable( GL_TEXTURE_2D );

	int nHandle = m_nNextTextureHandle;
	++m_nNextTextureHandle;
	m_MapTextures[nHandle] = TexData;

	return nHandle;
}


//-----------------------------------------------------------------------------
// Purpose: Creates a new font
//-----------------------------------------------------------------------------
HGAMEFONT CGameEnginePS3::HCreateFont( int nHeight, int nFontWeight, bool bItalic, char * pchFont )
{
	HGAMEFONT hFont = m_nNextFontHandle;
	++m_nNextFontHandle;

	// weight + italic are not supported in our dbg font output on ps3.  Neither is specifying font.
	// We also have to compute a "scale" relative to screen size, so it may not match pc exactly. 

	// 1.0f for scale means 80 characters fit the screen width, 32 lines fit the height. 
	// We'll call that 1.0 scale font roughly equivalent to 28pt font height on pc/d3d.

	PS3DbgFont_t font;
	font.m_nScale = (float)nHeight/28.0f;
	m_MapGameFonts[ hFont ] = font;

	return hFont;
}


//-----------------------------------------------------------------------------
// Purpose: Draws text to the screen inside the given rectangular region, using the given font
//-----------------------------------------------------------------------------
bool CGameEnginePS3::BDrawString( HGAMEFONT hFont, RECT rect, DWORD dwColor, DWORD dwFormat, const char *pchText )
{
	if ( !hFont )
	{
		OutputDebugString( "Someone is calling BDrawString with a null font handle\n" );
		return false;
	}

	float fCharWidth = m_nWindowWidth/80.0f;
	float fCharHeight = m_nWindowHeight/32.0f;

	// Find the font object for the passed handle
	std::map<HGAMEFONT, PS3DbgFont_t>::iterator iter;
	iter = m_MapGameFonts.find( hFont );
	if ( iter == m_MapGameFonts.end() )
	{
		OutputDebugString( "Invalid font handle passed to BDrawString()\n" );
		return false;
	}

	fCharWidth *= iter->second.m_nScale;
	fCharHeight *= iter->second.m_nScale;

	// Compute width/height in chars/lines
	int nLinesInText = 1;
	int nCharsWideMax = 0;
	int nCharsLine = 0;
	for( int i=0; i < strlen(pchText); ++i )
	{
		if ( pchText[i] == '\n' )
		{
			++nLinesInText;
			nCharsWideMax = MAX( nCharsLine, nCharsWideMax );
			nCharsLine = 0;
		}
		else 
		{
			// We assume all non linebreak chars are printable, don't pass others!
			++nCharsLine;
		}
	}
	nCharsWideMax = MAX( nCharsLine, nCharsWideMax );

	// Assume top left positioning
	float x = (float)rect.left;
	float y = (float)rect.top;

	if ( TEXTPOS_CENTER & dwFormat )
	{
		float fTextWidth = nCharsWideMax * fCharWidth;
		x = (float)rect.left + ((float)( rect.right-rect.left) - fTextWidth)/2.0f;
	}
	else if ( TEXTPOS_RIGHT &dwFormat )
	{
		float fTextWidth = nCharsWideMax * fCharWidth;
		x = (float)rect.right - fTextWidth;
	}

	if ( TEXTPOS_VCENTER & dwFormat )
	{
		float fTextHeight = nLinesInText * fCharHeight;
		y = (float)rect.top + ((float)( rect.bottom-rect.top) - fTextHeight)/2.0f;
	}
	else if ( TEXTPOS_RIGHT &dwFormat )
	{
		float fTextHeight = nLinesInText * fCharHeight;
		y = (float)rect.bottom - fTextHeight;
	}

	// Convert x/y to 0.0->1.0 range vs screen size
	x = x/(float)m_nWindowWidth;
	y = y/(float)m_nWindowHeight;

	// we have the font, try to draw with it
	if( cellDbgFontPuts( x, y, iter->second.m_nScale, DWARGB_TO_DWABGR(dwColor), pchText ) < 0 )
	{
		OutputDebugString( "cellDbgFontPuts call failed\n" );
		return false;
	}

	return true;
}


//-----------------------------------------------------------------------------
// Purpose: Message pump for OS messages
//-----------------------------------------------------------------------------
void CGameEnginePS3::MessagePump()
{
	cellSysutilCheckCallback();

	// Running callbacks may have triggered shutdown, if not run input
	if ( !m_bShuttingDown )
	{
		CellPadInfo2 padInfo;
		int ret = cellPadGetInfo2( &padInfo );
		if ( ret == CELL_OK )
		{
			if ( padInfo.system_info & CELL_PAD_INFO_INTERCEPTED )
			{
				// System has taken control of controller info, we can't currently access it.
			}
			
			bool bControllerFound = false;
			m_iCurrentPadIndex = -1;
			for( int i=0; i < CELL_PAD_MAX_PORT_NUM; ++i )
			{
				if ( padInfo.port_status[i] & CELL_PAD_STATUS_ASSIGN_CHANGES )
				{
					if ( (padInfo.port_status[i] & CELL_PAD_STATUS_CONNECTED) == 0 )
					{
						char rgchBuffer[512];
						_snprintf( rgchBuffer, 512, "Gamepad %d removed\n", i );
						OutputDebugString( rgchBuffer );
					}
					else if ( (padInfo.port_status[i] & CELL_PAD_STATUS_CONNECTED) > 0 )
					{
						char rgchBuffer[512];
						_snprintf( rgchBuffer, 512, "Gamepad %d connected\n", i );
						OutputDebugString( rgchBuffer );
					}
				}

				if ( (padInfo.port_status[i] & CELL_PAD_STATUS_CONNECTED ) > 0 && padInfo.device_type[i] == CELL_PAD_DEV_TYPE_STANDARD )
				{
					bControllerFound = true;
					m_iCurrentPadIndex = i;
					break;
				}
			}

			if ( !bControllerFound )
			{
				// Definitely no appropriate controller plugged in, can't do input
				static DWORD dwLastSpewTime = 0;
				if ( GetGameTickCount() - dwLastSpewTime > 1000 || dwLastSpewTime == 0 || dwLastSpewTime > GetGameTickCount() )
				{
					dwLastSpewTime = GetGameTickCount();
					OutputDebugString( "No supported controllers are active, activate one.\n" );
				}

				// Clear all keys 
				m_SetKeysDown.clear();
			}
			else
			{
				// Get status of the first found controller now
				CellPadData padData;
				int ret = cellPadGetData( m_iCurrentPadIndex, &padData );

				// If we got data ok, and if the data is new (len != 0) then process it
				if ( ret == CELL_OK && padData.len )
				{
					if ( padData.button[CELL_PAD_BTN_OFFSET_DIGITAL2] & CELL_PAD_CTRL_R2 )
					{
						m_SetKeysDown.insert( 0x57 ); // W key, thrusters, mapped to R2 on PS3
					}
					else
					{
						m_SetKeysDown.erase( 0x57 );
					}

					if ( padData.button[CELL_PAD_BTN_OFFSET_DIGITAL2] & CELL_PAD_CTRL_L2 )
					{
						m_SetKeysDown.insert( 0x53 ); // S key, reverse thrusters, mapped to L2 on PS3
					}
					else
					{
						m_SetKeysDown.erase( 0x53 );
					}

					if ( padData.button[CELL_PAD_BTN_OFFSET_DIGITAL2] & CELL_PAD_CTRL_CROSS )
					{
						// Mapped to both enter in menus, and fire in game
						m_SetKeysDown.insert( VK_RETURN );
						m_SetKeysDown.insert( VK_SPACE );
					}
					else
					{
						m_SetKeysDown.erase( VK_RETURN );
						m_SetKeysDown.erase( VK_SPACE );
					}

					if ( padData.button[CELL_PAD_BTN_OFFSET_DIGITAL2] & CELL_PAD_CTRL_CIRCLE )
					{
						m_SetKeysDown.insert( VK_ESCAPE );
					}
					else
					{
						m_SetKeysDown.erase( VK_ESCAPE );
					}

					if ( padData.button[CELL_PAD_BTN_OFFSET_DIGITAL1] & CELL_PAD_CTRL_UP || padData.button[CELL_PAD_BTN_OFFSET_ANALOG_LEFT_Y] == 0x00 )
					{
						m_SetKeysDown.insert( VK_UP );
					}
					else
					{
						m_SetKeysDown.erase( VK_UP );
					}

					if ( padData.button[CELL_PAD_BTN_OFFSET_DIGITAL1] & CELL_PAD_CTRL_DOWN || padData.button[CELL_PAD_BTN_OFFSET_ANALOG_LEFT_Y] == 0xFF )
					{
						m_SetKeysDown.insert( VK_DOWN );
					}
					else
					{
						m_SetKeysDown.erase( VK_DOWN );
					}

					if ( padData.button[CELL_PAD_BTN_OFFSET_DIGITAL1] & CELL_PAD_CTRL_LEFT || padData.button[CELL_PAD_BTN_OFFSET_ANALOG_LEFT_X] == 0x00 )
					{
						m_SetKeysDown.insert( 0x41 ); // A Key, mapped to left on PS3
					}
					else
					{
						m_SetKeysDown.erase( 0x41 );
					}

					if ( padData.button[CELL_PAD_BTN_OFFSET_DIGITAL1] & CELL_PAD_CTRL_RIGHT || padData.button[CELL_PAD_BTN_OFFSET_ANALOG_LEFT_X] == 0xFF )
					{
						m_SetKeysDown.insert( 0x44 ); // D key, mapped to right on PS3
					}
					else
					{
						m_SetKeysDown.erase( 0x44 );
					}
				}
			}
		}
	}
}


//-----------------------------------------------------------------------------
// Purpose: Find out if a key is currently down
//-----------------------------------------------------------------------------
bool CGameEnginePS3::BIsKeyDown( DWORD dwVK )
{
	std::set<DWORD>::iterator iter;
	iter = m_SetKeysDown.find( dwVK );
	if ( iter != m_SetKeysDown.end() )
		return true;

	return false;
}

//-----------------------------------------------------------------------------
// Purpose: Get a down key value
//-----------------------------------------------------------------------------
bool CGameEnginePS3::BGetFirstKeyDown( DWORD *pdwVK )
{
	std::set<DWORD>::iterator iter;
	iter = m_SetKeysDown.begin();
	if ( iter != m_SetKeysDown.end() )
	{
		*pdwVK = *iter;
		m_SetKeysDown.erase( iter );
		return true;
	}
	else
	{
		return false;
	}
}


//-----------------------------------------------------------------------------
// Purpose: Find the engine instance tied to a given ptr
//-----------------------------------------------------------------------------
CGameEnginePS3 * CGameEnginePS3::FindEngineInstanceForPtr( void *ptr )
{
	std::map<void *, CGameEnginePS3 *>::iterator iter;
	iter = m_MapEngineInstances.find( ptr );
	if ( iter == m_MapEngineInstances.end() )
		return NULL;
	else
		return iter->second;
}


//-----------------------------------------------------------------------------
// Purpose: Add the engine instance tied to a given ptr to our static map
//-----------------------------------------------------------------------------
void CGameEnginePS3::AddInstanceToPtrMap( CGameEnginePS3 *pInstance )
{
	m_MapEngineInstances[(void*)pInstance] = pInstance;
}


//-----------------------------------------------------------------------------
// Purpose: Removes the instance associated with a given ptr from the map
//-----------------------------------------------------------------------------
void CGameEnginePS3::RemoveInstanceFromPtrMap( void *ptr )
{
	std::map<void *, CGameEnginePS3 *>::iterator iter;
	iter = m_MapEngineInstances.find( ptr );
	if ( iter != m_MapEngineInstances.end() )
		m_MapEngineInstances.erase( iter );
}

