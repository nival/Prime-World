#include "stdafx.h"

#include "shadercompiler.h"
#include "DxResourcesControl.h"
#include "../System/InlineProfiler.h"

#define GETCURRENTTIME double currentShaderTime = ShaderCompileSeconds(); 

#define INCREMENTTIME(time) double deltaLoadTime = ShaderCompileSeconds() - currentShaderTime; time += deltaLoadTime; OutputDebugString(NStr::StrFmt( "shadercompiletime: \t %f\n", time ));

namespace Render
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static double shaderCompilerStartTime = 0;
static double secondsPerCPUCycle = 0;
static double shaderCompileTime = 0;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double ShaderCompileSeconds()
{
	LARGE_INTEGER Cycles;
	QueryPerformanceCounter(&Cycles);
	// Add big number to make bugs apparent where return value is being passed to FLOAT
	return Cycles.QuadPart * secondsPerCPUCycle;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitTiming()
{
	LARGE_INTEGER Frequency;
	//ASSERT( 
	QueryPerformanceFrequency(&Frequency);
	secondsPerCPUCycle= 1.0 / Frequency.QuadPart;
	shaderCompilerStartTime = ShaderCompileSeconds();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static struct SRegister_DummmyInit
{
	SRegister_DummmyInit() {InitTiming();} 

} __Dummy;


struct CompiledShaderInfo
{
  ID3DXBuffer* code;
  ID3DXBuffer* error_msg;

  CompiledShaderInfo():code(0), error_msg(0) {}
  CompiledShaderInfo(ID3DXBuffer* _code, ID3DXBuffer* _error_msg):code(_code), error_msg(_error_msg) {}

  void Clear()
  {
    code->Release();
    code = 0;
    if (error_msg) 
    {
      error_msg->Release();
      error_msg = 0;
    }
  }

  bool isOk() const { return code != 0; }
};

struct IncludeWrapper : ID3DXInclude
{

  IncludeWrapper(const char* name)
  {
    int n = strlen(name);
    while (n >= 0)
    {
      if (name[n] == '/' || name[n] == '\\')
      {
        break;
      }
      n --;
    }
    if (n > 0)
    {
      root = nstl::string(name, n+1);
    }
  }

  virtual HRESULT __stdcall Close(
    LPCVOID pData
    )
  {
    delete [] (char*)pData;
    return S_OK;
  }
  virtual HRESULT __stdcall Open(
    D3DXINCLUDE_TYPE IncludeType,
    LPCSTR pFileName,
    LPCVOID pParentData,
    LPCVOID * ppData,
    UINT * pBytes
    )
  { 
    nstl::string s = NFile::Combine(root, pFileName);
    CObj<Stream> pShaderFileStream = RootFileSystem::OpenFile( s.c_str(), FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
    if (pShaderFileStream)
    {
      int shaderSize = pShaderFileStream->GetSize();
      byte* shaderCode = new byte[shaderSize+1];
      pShaderFileStream->Read(shaderCode, shaderSize);
      shaderCode[shaderSize] = 0;
      *ppData = shaderCode;
      *pBytes = shaderSize;
      return S_OK;
    }
    return S_FALSE;
  }
  nstl::string root;

};

CompiledShaderInfo CompileShader( const char* filename, const nstl::vector<D3DXMACRO>& defines, const char* mainFuncName, const char* profileName)
{
  NI_PROFILE_FUNCTION

  ID3DXBuffer* code = 0;
  ID3DXBuffer* error_msg = 0;

  char* shaderCode=0;
  int shaderSize = 0;
  CObj<Stream> pShaderFileStream = RootFileSystem::OpenFile( filename, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
  if (pShaderFileStream)
  {
    shaderSize = pShaderFileStream->GetSize();
    shaderCode = new char[shaderSize+1];
    pShaderFileStream->Read(shaderCode, shaderSize);
    shaderCode[shaderSize] = 0;
    IncludeWrapper includer(filename);
    if (FAILED(D3DXCompileShader(shaderCode, shaderSize, &defines[0], &includer, mainFuncName, profileName, 
      0, &code, &error_msg, 0)))
    {
      char* error_ptr = (char*)error_msg->GetBufferPointer();
      OutputDebugStringA( error_ptr );
      delete [] shaderCode;
      return CompiledShaderInfo();
    }
  }
  delete [] shaderCode;
  return CompiledShaderInfo(code, error_msg);
}

struct ShaderDefines
{

  ShaderDefines(const ShaderDefinesTable& definesTable)
  {
    nstl::vector<nstl::string> names;
    nstl::vector<nstl::string> values;

    unsigned int definestable_size = definesTable.GetDefinesCount();
    for (unsigned int i = 0; i < definestable_size; i++)
    {
      const ShaderDefine& define = definesTable.GetShaderDefine(i);
      values.push_back( NStr::IntToStr( define.value ) );
      names.push_back( define.name );
    }

    for (unsigned int i = 0; i < definestable_size; i++)
    {
      D3DXMACRO def;
      def.Definition = values[i].c_str();
      def.Name = names[i].c_str();
      items.push_back(def);
    }
  }

  void AddDefine(const char* name, const char* definition=0)
  {
    D3DXMACRO def;
    def.Name = name;
    def.Definition = definition?definition:"";
    items.push_back(def);
  }

  void End()
  {
    D3DXMACRO end;
    ZeroMemory(&end, sizeof(end));
    items.push_back(end);
  }
  const nstl::vector<D3DXMACRO>& Items() const { return items; }

private:
  nstl::vector<D3DXMACRO> items;
};

DXPixelShaderRef CompilePixelShaderFromFile(const char* filename, const ShaderDefinesTable& definesTable)
{
  NI_PROFILE_FUNCTION

	//GETCURRENTTIME
	//systemLog( NLogg::LEVEL_MESSAGE ) << "deprecated online PS compiling: " << filename << endl;
  ShaderDefines defines(definesTable);
  defines.AddDefine("PS", "1");
	bool bSupportSM30 = GetRenderer()->GetCaps().bSupportSM30;
	if (!bSupportSM30)
	{
    defines.AddDefine("FORCE_SM20");
	}
  defines.End();

  CompiledShaderInfo info = CompileShader(filename, defines.Items(), "PS_main", bSupportSM30 ? "ps_3_0" : "ps_2_0");
  if (info.isOk())
  {
    IDirect3DPixelShader9* d3dshader = 0;
    HRESULT res = GetDevice()->CreatePixelShader(static_cast<DWORD*>(info.code->GetBufferPointer()), &d3dshader);
    NI_DX_THROW(res, "CreatePixelShader");

    info.Clear();

    //INCREMENTTIME(shaderCompileTime)
    return DXPixelShaderRef(d3dshader, false);
  }
  else
  {
		NI_ALWAYS_ASSERT("Compiling pixel shader error!");
		return DXPixelShaderRef(); // FIXME
	}
}
///

DXVertexShaderRef CompileVertexShaderFromFile(const char* filename, const ShaderDefinesTable& definesTable)
{
  NI_PROFILE_FUNCTION

	//GETCURRENTTIME
	//systemLog( NLogg::LEVEL_MESSAGE ) << "deprecated online VS compiling: " << filename << endl;
	////////////////////
  ShaderDefines defines(definesTable);
  defines.AddDefine("VS", "1");
	bool bSupportSM30 = GetRenderer()->GetCaps().bSupportSM30;
	if (!bSupportSM30)
	{
    defines.AddDefine("FORCE_SM20");
	}
	defines.End();

  CompiledShaderInfo info = CompileShader(filename, defines.Items(), "VS_main", bSupportSM30 ? "vs_3_0" : "vs_2_0");
  if (info.isOk())
  {
    IDirect3DVertexShader9* d3dshader = 0;

    // constant_table
    HRESULT res = GetDevice()->CreateVertexShader(static_cast<DWORD*>(info.code->GetBufferPointer()), &d3dshader);
    NI_DX_THROW(res, "CreateVertexShader");

    info.Clear();
    //INCREMENTTIME(shaderCompileTime)

    return DXVertexShaderRef(d3dshader, false);
  }
  else
  {
    NI_ALWAYS_ASSERT("Compiling vertex shader error!");
    return DXVertexShaderRef(); // FIXME
  }

}
}; // namespace Render
