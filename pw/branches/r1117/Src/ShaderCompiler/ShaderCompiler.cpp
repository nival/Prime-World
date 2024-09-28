#include "stdafx.h"
#include "UberShaderDesc.h"

#include "multythread/mtworkerlite.h"
#include "crc_math.h"
#include "parse.h"

#include <d3dx9shader.h>

//#define IS_MULTYTHREAD 1

namespace
{
  const int strsize = 32;

  const char macroV20[strsize] = "FORCE_SM20";
  const char macroV20_dummy[strsize] = "1";

  NFile::CFilePath s_directory;
  NFile::CFilePath s_outDirectory;

  LONG volatile shaderIndex;

  MTWorkerLite * s_mtWorker = 0;

  LPD3DXBUFFER *g_matrix;
}

class MyInclude : public ID3DXInclude
{
public:
  __declspec(nothrow) HRESULT __stdcall Open ( D3DXINCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID * ppData, UINT * pBytes) 
  { 
    int cnt = files.size();

    for( int i = 0; i < cnt; ++i )
    {
      FileData &cur = files[i];

      if (cur.name == pFileName)
      {
        *ppData = cur.pStream->GetBuffer();
        *pBytes = cur.pStream->GetSize();

        return D3D_OK; 
      }
    }

    // read file and add
    FileData newData;

    string fullPath = s_directory + pFileName;

    newData.name = pFileName;
    newData.pStream = new FileStream( fullPath, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
    if ( !IsValid( newData.pStream ) || !newData.pStream->IsOk() )
    {
      *ppData = 0;
      *pBytes = 0;

      return D3DERR_NOTFOUND;
    }

    *ppData = newData.pStream->GetBuffer();
    *pBytes = newData.pStream->GetSize();

    files.push_back(newData);

    return D3D_OK; 
  }
  __declspec(nothrow) HRESULT __stdcall Close( LPCVOID pData )
  { return D3D_OK; }
protected:
  struct FileData
  {
    CObj<FileStream> pStream;
    string           name;
  };
  vector<FileData> files;
};

MyInclude g_includeHandler;

bool CompileOneShader( DWORD &Flags, CObj<FileStream> pStream, D3DXMACRO* pDefines, MyInclude pInclude, LPCSTR const profile, LPCSTR const entryPoint, LPD3DXBUFFER* ppShader )
{
  HRESULT hr;
  LPD3DXBUFFER pErrorMsgs;

  hr = D3DXCompileShader( 
    pStream->GetBuffer(), 
    pStream->GetSize(), 
    pDefines, 
    &pInclude,
    entryPoint,
    profile,
    Flags, 
    ppShader, 
    &pErrorMsgs, 
    0
    );

  if (D3D_OK != hr)
  {
    char * err;
    err = (char *)pErrorMsgs->GetBufferPointer();

    printf("%s", err);

    return false;
  }

  return true;
}

#ifdef IS_MULTYTHREAD
class ShaderCompilerContext
{
public:
  MyInclude includeManager;

  //Define stuff
  CObj<FileStream> *pStream;
  UberShaderDesc *curShader;
  DWORD Flags;
  int   isV20;

  void DoJob()
  {
    string vsProfile, psProfile;
    int totalPinsCnt = curShader->pins.size();
    bool bOK;

    // build macros array
    int macroCnt = totalPinsCnt + isV20 + 1;
    D3DXMACRO* pDefines;
    pDefines = new D3DXMACRO[macroCnt];

    pDefines[macroCnt - 1].Definition = 0;
    pDefines[macroCnt - 1].Name = 0;

    if (1 == isV20)
    {
      vsProfile = "vs_2_0";
      psProfile = "ps_2_0";
      pDefines[macroCnt - 1 - 1].Name = macroV20;
      pDefines[macroCnt - 1 - 1].Definition = macroV20_dummy;
    }
    else
    {
      vsProfile = "vs_3_0";
      psProfile = "ps_3_0";
    }

    // get total codes value
    string *pinValues = 0;
    if (totalPinsCnt > 0)
      pinValues = new string[totalPinsCnt];

    int idx;

    int fullCount = curShader->GetTotalCount();
    do 
    {
      idx = InterlockedIncrement(&shaderIndex);
      if (idx >= fullCount)
        break;

      // build macro array
      int currentPinValue = idx;
      for ( int i = totalPinsCnt - 1; i > -1; --i )
      {
        UberShaderPin &curPin = curShader->pins[i];

        int temp = currentPinValue / curPin.pinMultiplier;
        char strTmp[strsize];

        sprintf_s(strTmp, strsize, "%d", temp);
        pinValues[i] = strTmp;

        pDefines[i].Name = curPin.pinName.c_str();
        pDefines[i].Definition = pinValues[i].c_str();

        currentPinValue = currentPinValue % curPin.pinMultiplier;
      }
                                              
      bOK = CompileOneShader(Flags, *pStream, pDefines, includeManager, vsProfile.c_str(), "MainPass_VSMain", &g_matrix[idx * 2]);
      bOK = CompileOneShader(Flags, *pStream, pDefines, includeManager, psProfile.c_str(), "MainPass_PSMain", &g_matrix[idx * 2 + 1]);
      
      printf("%d ", idx);
    } while(1);

    printf("done\n");

    // free mem
    if (totalPinsCnt > 0)
      delete[] pinValues;

    delete[] pDefines;
  }
};

static void ThreadJobFunc(void *p)
{
  static_cast<ShaderCompilerContext*>(p)->DoJob();
}
#endif // #ifdef IS_MULTYTHREAD

struct ShadersFileHeader
{
  unsigned int codesCount;
};

struct ShaderObjInfo
{
  unsigned int vsOffset;
  unsigned int psOffset;
};

LPD3DXBUFFER* BuildShaderMatrix( CObj<FileStream> pStream, UberShaderDesc &curShader, DWORD &Flags, int isV20, UberShaderFileInfo &info )
{
  string vsProfile, psProfile;
  int totalPinsCnt = curShader.pins.size();
  bool bOK = true;

  // build macros array
  int macroCnt = totalPinsCnt + isV20 + 1;
  D3DXMACRO* pDefines;
  pDefines = new D3DXMACRO[macroCnt];
                                                                                       
  pDefines[macroCnt - 1].Definition = 0;
  pDefines[macroCnt - 1].Name = 0;

  if (1 == isV20)
  {
    vsProfile = "vs_2_0";
    psProfile = "ps_2_0";
    pDefines[macroCnt - 1 - 1].Name = macroV20;
    pDefines[macroCnt - 1 - 1].Definition = macroV20_dummy;
  }
  else
  {
    vsProfile = "vs_3_0";
    psProfile = "ps_3_0";
  }

  // get total codes value
  int fullCount = curShader.GetTotalCount();

  LPD3DXBUFFER *matrix;
  matrix = new LPD3DXBUFFER[fullCount * 2];
  memset(matrix, 0, sizeof(LPD3DXBUFFER) * fullCount * 2);

  string* pinValues = 0;
  if (totalPinsCnt > 0)
    pinValues = new string[totalPinsCnt];

  /*
  float persPerTest = 1000.f / fullCount;
  float curDot = 0.f;
  */

  for (int idx = 0; idx < fullCount; ++idx)
  {
    // build macro array
    int currentPinValue = idx;
    for ( int i = totalPinsCnt - 1; i > -1; --i )
    {
      UberShaderPin &curPin = curShader.pins[i];

      int temp = currentPinValue / curPin.pinMultiplier;
      char strTmp[strsize];

      sprintf_s(strTmp, strsize, "%d", temp);
      pinValues[i] = strTmp;

      pDefines[i].Name = curPin.pinName.c_str();
      pDefines[i].Definition = pinValues[i].c_str();

      currentPinValue = currentPinValue % curPin.pinMultiplier;
    }

    // check existed code
    int vsCode = info.GetIdx(idx * 2);
    if (vsCode != -1)
    {
      matrix[idx * 2] = matrix[vsCode];
      matrix[vsCode]->AddRef();
    }
    else
      bOK = CompileOneShader(Flags, pStream, pDefines, g_includeHandler, vsProfile.c_str(), "MainPass_VSMain", &matrix[idx * 2]);

    int psCode = info.GetIdx(idx * 2 + 1);
    if (psCode != -1)
    {
      matrix[idx * 2 + 1] = matrix[psCode];
      matrix[psCode]->AddRef();
    }                                                  
    else
      bOK = CompileOneShader(Flags, pStream, pDefines, g_includeHandler, psProfile.c_str(), "MainPass_PSMain", &matrix[idx * 2 + 1]);
    
    printf("\r%d ", idx);

    if (!bOK)
    {
      printf("\n\nERROR while compiling shader!\n");
      delete[] matrix;
      matrix = NULL;
      break;
    }
  }

  printf("\n");

  // free mem
  if (totalPinsCnt > 0)
    delete[] pinValues;

  delete[] pDefines;

  return matrix;
}

LPD3DXBUFFER* BuildShaderMatrixMultyThread( UberShaderDesc &curShader, MTWorkerLite *mtworker )
{
  g_matrix = new LPD3DXBUFFER[curShader.GetTotalCount() * 2];

  mtworker->ExecuteJob();

  return g_matrix;
}

int WriteMatrix(LPD3DXBUFFER* matrix, UberShaderDesc &curShader, int isV20)
{
  int offset = 0;
  
  // get total codes value
  int fullCount = curShader.GetTotalCount();

  // output info
  ShadersFileHeader header;
  header.codesCount = fullCount;
  offset += sizeof(ShadersFileHeader);

  ShaderObjInfo *pInfo;
  pInfo = (ShaderObjInfo *)malloc(sizeof(ShaderObjInfo) * fullCount);
  offset += sizeof(ShaderObjInfo) * fullCount;

  for (int idx = 0; idx < 2 * fullCount; ++idx)
  {
    if (matrix[idx])
    {
      int idx2 = idx / 2;

      if (0 == (idx % 2))
        pInfo[idx2].vsOffset = offset;
      else
        pInfo[idx2].psOffset = offset;

      offset += matrix[idx]->GetBufferSize();
    }
  }

  // output to file
  string outFileName;
  string ext;

  if (1 == isV20)
    ext = ".shd2";
  else
    ext = ".shd";

  outFileName = s_outDirectory + curShader.shaderName + ext;

  FILE *fpFile;

  fopen_s(&fpFile, outFileName.c_str(), "wb");

  if (0 == fpFile)
  {
    printf("ERROR 001: Can't open %s file to write. Try to write to current directory.\n", outFileName.c_str());
    
    outFileName = curShader.shaderName + ext;
    fopen_s(&fpFile, outFileName.c_str(), "wb");
    if (0 == fpFile)
      printf("ERROR 002: Can't open %s file to write. Exit.\n", outFileName.c_str());
  }    

  fwrite(&header, sizeof(header), 1, fpFile);
  fwrite(pInfo, sizeof(ShaderObjInfo), fullCount, fpFile);

  int num = 0;
  for (int idx = 0; idx < 2 * fullCount; ++idx)
  {
    if (matrix[idx])
    {
      fwrite(matrix[idx]->GetBufferPointer(), matrix[idx]->GetBufferSize(), 1, fpFile);
      num++;
    }
  }
  
  free(pInfo);

  return num;
}
int main( int argc, char *argv[ ] )
{
#ifdef IS_MULTYTHREAD
  vector<ShaderCompilerContext> contexts;
  vector<void*> dataForMTWorker;

  int numCPUs = MTWorkerLite::GetCPUCount();

  contexts.resize(numCPUs);
  dataForMTWorker.resize(numCPUs);
  for (int i = 0; i < numCPUs; i++)
    dataForMTWorker[i] = &contexts[i];

  s_mtWorker = new MTWorkerLite(ThreadJobFunc, &(dataForMTWorker[0]), numCPUs, MTWorkerLite::AFFINITY_ORDERED);
#endif

  NHPTimer::STime curTime;

  bool bOK;
  string configName;
  string name;
  CommandLine params;

  if (argc < 2)
  {
    params.Print();
    return -100;
  }

  // parse command string
  params.Parse(argc, argv);

  const NFile::CFilePath fullFilePath = argv[1];

  s_directory = GetFilePath( fullFilePath );

  // set output directory
  if (params.GetOutDir())
    s_outDirectory = params.GetOutDir();
  else
    s_outDirectory = s_directory;

  configName = argv[1];

  vector<UberShaderDesc> shaders;
	bOK = LoadShadersCollection( configName, &shaders );
  if (!bOK)
  {
    printf("Can not load shader collection from %s\n", configName.c_str());
    return -100;
  }
  
  NHPTimer::GetTime( curTime );

  int cntShd = shaders.size();
  double rTime = 0.f;

  if (0 != params.GetShaderName())
  {
    printf("Single shader mode. Build only %s\n", params.GetShaderName());
  }

  for( int i = 0; i < cntShd; ++i )
  {
    string shaderName;
    UberShaderDesc &curShader = shaders[i];

//    printf("---- '%s' shader processing ...\n", curShader.shaderName.c_str());
    if (0 != params.GetShaderName())
    {
      if (strcmp(curShader.shaderName.c_str(), params.GetShaderName()))
      {
//        printf("Skip\n");
        continue;
      }
    }

    printf("---- '%s' shader processing ...\n", curShader.shaderName.c_str());
    UberShaderFileInfo info(curShader);
    info.SetDir(s_outDirectory);
    if (params.GetCleanState())
    {
      printf("Clean build \n");
      info.Reset();
    }
    else
      info.Read(params.GetVersion());

    shaderName = s_directory + curShader.shaderName + ".hlsl";
    // open file
    CObj<FileStream> pStream = new FileStream( shaderName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
    if ( !IsValid( pStream ) || !pStream->IsOk() )
    {
      printf("Can't open %s file. Skip\n", shaderName.c_str());
      continue;
    }

    DWORD Flags;
    Flags = D3DXSHADER_OPTIMIZATION_LEVEL3;

    LPD3DXBUFFER *matrix;

    // reset & build data
    shaderIndex = -1;
#ifdef IS_MULTYTHREAD
    for (int i = 0; i < numCPUs; i++)
    {
      contexts[i].curShader = &curShader;                 
      contexts[i].Flags = Flags;
      contexts[i].isV20 = params.GetVersion();
      contexts[i].pStream = &pStream;
    }                      
#endif
    // compile one shader matrix
#ifndef IS_MULTYTHREAD
    matrix = BuildShaderMatrix(pStream, curShader, Flags, params.GetVersion(), info);
#else
    matrix = BuildShaderMatrixMultyThread(curShader, s_mtWorker);
#endif
    if (matrix != NULL)
    {
      if (params.IsNoShare())
      {
        // write matrix to file
        printf("Writing matrix to file\n");
        WriteMatrix(matrix, curShader, params.GetVersion());

        // build info
        info.Build(matrix);
        info.Write(params.GetVersion());
      }
      else
      {
        void WriteSharedFileFormat(LPD3DXBUFFER const buffers[], UberShaderDesc const& shader, CommandLine const& params);
        WriteSharedFileFormat(matrix, curShader, params);
      }

      // release VS & PS
      for (unsigned int i = 0; i < curShader.GetTotalCount() * 2; ++i)
        if (0 != matrix[i])
          matrix[i]->Release();

      delete[] matrix;
    }

    rTime += NHPTimer::GetTimePassedAndUpdateTime( curTime );
    printf("---- '%s' shader done\n", curShader.shaderName.c_str());
    printf("Cur time %.2f\n", rTime);
    printf("\n", rTime);
  }

#ifdef IS_MULTYTHREAD
  delete s_mtWorker;
#endif

  rTime += NHPTimer::GetTimePassedAndUpdateTime( curTime );
  printf("Total time %.2f\n", rTime);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// keep file format compatible with the old reading code
void WriteSharedFileFormat(LPD3DXBUFFER const buffers[], UberShaderDesc const& shader, CommandLine const& params)
{
  NI_ASSERT(!params.IsNoShare(), "Should not use shared function in NoShare mode");

  //////////////////////////////////////////////////////////////////////////
  // Share compiled codes

  // hash for code sharing
  unsigned shaderCount = shader.GetTotalCount();
  unsigned bufferCount = 2 * shaderCount;
  nstl::vector<unsigned> byIndex(bufferCount);
  nstl::hash_map<unsigned, unsigned> byHash;

  // find equal buffers
  for (unsigned bufferIdx = 0; bufferIdx < bufferCount; ++bufferIdx)
  {
    LPD3DXBUFFER pBuffer = buffers[bufferIdx];
    NI_ASSERT(pBuffer, "Missing compiled data");
    NI_ASSERT(pBuffer->GetBufferPointer(), "Missing compiled data");
    NI_ASSERT(pBuffer->GetBufferSize() > 0, "Zero compiled data size");

    unsigned crc = CRC32((char*)pBuffer->GetBufferPointer(), pBuffer->GetBufferSize());
    nstl::hash_map<unsigned, unsigned>::iterator it = byHash.find(crc);
    if (it == byHash.end())
    {
      // the buffer is unique
      byHash[crc] = bufferIdx;
      byIndex[bufferIdx] = bufferIdx;
    }
    else
    {
      // the buffer looks similar, double check
      unsigned otherIdx = it->second;
      LPD3DXBUFFER pOther = buffers[otherIdx];
      if (pOther->GetBufferSize() == pBuffer->GetBufferSize() && memcmp(pOther->GetBufferPointer(), pBuffer->GetBufferPointer(), pBuffer->GetBufferSize()) == 0)
      {
        // the buffers are completely the same, save reference
        NI_ASSERT((bufferIdx & 1) == (otherIdx & 1), "Pixel shader is shared with vertex shader or vice versa");
        byIndex[bufferIdx] = otherIdx;
      }
      else
      {
        // no, they are different
        printf("NOTE: While sharing compiled codes found two with the same CRC but different content. It should not be a problem though.\n");
        byIndex[bufferIdx] = bufferIdx;
      }
    }
  }

  // sharing statistics
  unsigned totalSize = 0;
  unsigned actualSize = 0;
  NI_ASSERT(byIndex.size() == (int)bufferCount, "Some buffers miss reindex information");
  for (unsigned bufferIdx = 0; bufferIdx < bufferCount; ++bufferIdx)
  {
    totalSize += buffers[bufferIdx]->GetBufferSize();
    if (byIndex[bufferIdx] == bufferIdx)
      actualSize += buffers[bufferIdx]->GetBufferSize();
  }
  printf("Sharing: %.0f%% left (%.1fKb vs %.1fKb)\n",
    (float)actualSize * 100.0f / (float)totalSize, (float)actualSize / 1024.0f, (float)totalSize / 1024.0f);

  //////////////////////////////////////////////////////////////////////////
  // Prepare data to be written to file

  unsigned offset = 0;

  // file header
  ShadersFileHeader header = { shaderCount };
  offset += sizeof(ShadersFileHeader);

  // shader directory
  unsigned* offsets = new unsigned[bufferCount];
  memset(offsets, 0xFF, sizeof(unsigned) * bufferCount);
  offset += sizeof(unsigned) * bufferCount;

  // compute offsets
  unsigned dataOffset = offset;
  for (unsigned bufferIdx = 0; bufferIdx < bufferCount; ++bufferIdx)
  {
    unsigned otherIdx = byIndex[bufferIdx];
    if (otherIdx == bufferIdx)
    {
      // unique code, will be written
      offsets[bufferIdx] = offset;
      offset += buffers[bufferIdx]->GetBufferSize();
    }
    else
    {
      // shared code, make reference
      NI_ASSERT(offsets[otherIdx] != 0xFFFFFFFF, "Original code offset is not filled yet");
      NI_ASSERT(offsets[otherIdx] < offset, "Original code offset is impossible");
      offsets[bufferIdx] = offsets[otherIdx];
    }
  }
  unsigned fullSize = offset;
  NI_ASSERT(fullSize == sizeof(ShadersFileHeader) + sizeof(unsigned) * bufferCount + actualSize, "Real file size doesn't match with projected one");

  //////////////////////////////////////////////////////////////////////////
  // Write data to a file

  // open file
  string fileName = s_outDirectory + shader.shaderName + (params.GetVersion() == 1 ? ".shd2" : ".shd");
  FILE* fp = NULL;
  if (fopen_s(&fp, fileName.c_str(), "wb") != 0 || !fp)
  {
    printf("ERROR: Cannot open file for writing ('%s')\n", fileName.c_str());
    delete[] offsets;
    return;
  }

  // write header and shader directory
  fwrite(&header, sizeof(header), 1, fp);
  fwrite(offsets, sizeof(unsigned), bufferCount, fp);

  // note: i don't like this code duplication [3/1/2011 paul.smirnov]
  // write buffer contents
  offset = dataOffset;
  for (unsigned bufferIdx = 0; bufferIdx < bufferCount; ++bufferIdx)
  {
    unsigned otherIdx = byIndex[bufferIdx];
    if (otherIdx == bufferIdx)
    {
      // unique code, will be written
      NI_ASSERT(offsets[bufferIdx] == offset, "Offset mismatch when actually writing data");
      NI_ASSERT(ftell(fp) == (int)offset, "Offset mismatch when actually writing data");
      fwrite(buffers[bufferIdx]->GetBufferPointer(), buffers[bufferIdx]->GetBufferSize(), 1, fp);
      offset += buffers[bufferIdx]->GetBufferSize();
    }
    else
    {
      // shared code, make reference
      NI_ASSERT(offsets[otherIdx] != 0xFFFFFFFF, "Original code offset is not filled yet");
      NI_ASSERT(offsets[otherIdx] < offset, "Original code offset is impossible");
      NI_ASSERT(offsets[bufferIdx] == offsets[otherIdx], "Offset mismatch when skipping shared copy");
    }
  }
  NI_ASSERT(offset == fullSize, "Offset mismatch at the end of file");
  NI_ASSERT(ftell(fp) == (int)offset, "Offset mismatch at the end of file");

  delete[] offsets;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
