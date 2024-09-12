#pragma once

#include "../System/systemStdAfx.h"
#include "../libdb/libdbStdAfx.h"
#include "specific.h"

#include "Vendor\DirectX\Include\DxErr.h"
#include "NullRenderSignal.h"

#define NI_DX_THROW( hr, user_text ) NI_ASSERT_TRACE( hr == D3D_OK, NStr::StrFmt("%s; Failed code: 0x%08X, error: %s description: %s", user_text, hr, DXGetErrorStringA(hr), DXGetErrorDescriptionA(hr)) );
#define NI_DX_WARN( hr, user_text ) do { if FAILED(hr) DebugTrace("%s; Failed code: 0x%08X, error: %s description: %s", user_text, hr, DXGetErrorStringA(hr), DXGetErrorDescriptionA(hr)); } while (0)
#define NI_DX_THROW_CRITICAL( hr, user_text ) do { if FAILED(hr) { \
  const char* msg = NStr::StrFmt("%s; Failed code: 0x%08X, error: %s description: %s", user_text, hr, DXGetErrorStringA(hr), DXGetErrorDescriptionA(hr)); \
  DebugTrace(msg); ShowErrorMessageAndTerminate(hr); \
} } while(0)