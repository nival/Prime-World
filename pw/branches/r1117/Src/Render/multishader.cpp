#include "stdafx.h"
#include "multishader.h"
#include "ImmediateRenderer.h"

#include "System/InlineProfiler.h"
#include "System/FileSystem/FileStream.h"
#include "System/FileSystem/FileSystem.h"
#include "shadercompiler.h"

NDebug::PerformanceDebugVar render_TranslationTime( "ShaderTransTime", "RenderOffline", 100, 100, false );
NDebug::DebugVar<int> render_TranslationCount( "ShaderTransCount", "RenderOffline" );

namespace Render
{
	namespace Materials
	{

		struct ShaderObjInfo
		{
			unsigned int vsOffset;
			unsigned int psOffset;
		};

		static ShaderPair defaultShaderPair;

		void MultiShader::InitializeDefaultShaderPair()
		{
      defaultShaderPair.pVertexShader = ImmRenderer::Get()->GetVShader("default_shader");
			defaultShaderPair.pPixelShader = ImmRenderer::Get()->GetPShader("default_shader");
		}

		void MultiShader::ReleaseDefaultShaderPair()
		{
			defaultShaderPair.pVertexShader = NULL;
			defaultShaderPair.pPixelShader  = NULL;
		}

		bool MultiShader::OpenFile(  )
		{
			char buf[256];
			sprintf_s( buf, "%s.shd%s", fileName.c_str(), GetRenderer()->GetCaps().bSupportSM30 ? "" : "2" );

			CObj<Stream> pShaderFileStream = RootFileSystem::OpenFile( buf, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
			NI_VERIFY( pShaderFileStream && pShaderFileStream->IsOk(), NStr::StrFmt( "Cannot open obj file: %s", buf), pairs.resize(1); return false; );

			unsigned char* pBegin = (unsigned char*)pShaderFileStream->GetBuffer();

			int shadersCount = *(unsigned int*)pBegin;
			NI_VERIFY(shadersCount, "fatal error: cant find uber shader objs!", pairs.resize(1); return false; );
			pairs.resize( shadersCount );

			int effectiveSize =  pShaderFileStream->GetSize()-4;
			pInfo = (ShaderObjInfo*)Aligned_MAlloc(effectiveSize, 16);
			memcpy(pInfo, pBegin+4, effectiveSize);
			
			/*for( int i = 0; i < shadersCount; ++i)
			{
					ASSERT(pInfo->vsOffset && pInfo->psOffset);
					pairs[i].pVertexShader = Render::GetRenderer()->CreateVertexShader( pBegin + pInfo->vsOffset );
					pairs[i].pPixelShader = Render::GetRenderer()->CreatePixelShader( pBegin + pInfo->psOffset );
					++pInfo;
			}*/

			return true;
		}

		ShaderPair& MultiShader::GetShaderPairByIndex(unsigned int index)
		{
			NI_VERIFY(pInfo, "pInfo is invalid!", return defaultShaderPair; );
			if ( !(0 <= index && (int)index < pairs.size()) )
				return defaultShaderPair;
			//NI_VERIFY((int)index < pairs.size() && index >= 0, NStr::StrFmt("out of pins! #%d", index), return defaultShaderPair; );
			if( !pairs[index].pVertexShader )
			{
        NI_ASSERT(Get(pairs[index].pPixelShader) == NULL, "Both shaders should be either missing or present at the same time");
				NDebug::PerformanceDebugVarGuard render_TranslationTimeGuard( render_TranslationTime, true );
        NI_PROFILE_BLOCK("create shaders");
				render_TranslationCount.AddValue( 1 );
				unsigned char* pBegin = (unsigned char*)pInfo - 4;
				pairs[index].pVertexShader = Render::GetRenderer()->CreateVertexShader( pBegin + pInfo[index].vsOffset );
				pairs[index].pPixelShader = Render::GetRenderer()->CreatePixelShader( pBegin + pInfo[index].psOffset );
			}
      else
      {
        NI_ASSERT(Get(pairs[index].pPixelShader) != NULL, "Both shaders should be either missing or present at the same time");
      }
			return pairs[index];
		}

		void MultiShader::Destroy()
		{
			const int shadersCount = pairs.size();
			for (int i = 0; i < shadersCount; ++i)
			{
				pairs[i].pVertexShader = 0;
				pairs[i].pPixelShader = 0;
			}
			Aligned_Free(pInfo);
		}

		MultiShader::~MultiShader()
		{
			Destroy();
		}

		MultiShader::MultiShader(const nstl::string& _fileName ) : pInfo(0), fileName(_fileName)
		{
			OpenFile( );
		}

		void MultiShader::ReloadShaders()
		{
			Destroy();
			OpenFile();
		}

		const nstl::string& MultiShader::GetShaderName() const
		{
			return fileName;
		}
	};
};

