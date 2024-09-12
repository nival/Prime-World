#include "stdafx.h"

#include "../libdb/XmlSaver.h"
#include "UberShaderDesc.h"

#include "crc_math.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UberShaderPin::operator&( IXmlSaver &saver )
{
	saver.Add( "pinName", &pinName );
	saver.Add( "maxPinValue", &maxPinValue );
	saver.Add( "pinMultiplier", &pinMultiplier );

	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UberShaderDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "shaderName", &shaderName );
	saver.Add( "pins", &pins );

	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int UberShaderDesc::GetTotalCount( ) const
{
  // get total codes value
  if (pins.size() > 0)
    return pins.back().maxPinValue * pins.back().pinMultiplier;
  else
    return 1U;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UberShaderFileInfo::Reset( )
{
  unsigned int totalCnt = shader.GetTotalCount() * 2;
  needWrite = true;
  similar = 0;
  
  codes.resize(totalCnt);
  for (unsigned int i = 0; i < totalCnt; ++i)
  {
    codes[i].idx = -1;
    codes[i].CRC = 0;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UberShaderFileInfo::Read( int isV20 )
{
  /*unsigned int totalCnt = shader.GetTotalCount();
  FILE *fpFile;*/

  Reset();

  printf("Clean old code file. \n");
  return;
  
  /*string filename;
  if (isV20)
    filename = directory + shader.shaderName + ".codes2";
  else
    filename = directory + shader.shaderName + ".codes";

  fopen_s(&fpFile, filename.c_str(), "rb");
  if (0 == fpFile)
  {
    printf("No .codes file. Clean build. \n");
    return;
  }

  unsigned int cnt;
  unsigned int _similar;
  fread_s(&cnt,  4, 4, 1, fpFile);
  fread_s(&_similar, 4, 4, 1, fpFile);

  if (cnt != totalCnt)
  {
    fclose(fpFile);
    printf("Shader count inconsistent. Clean build. \n");
    return;
  }

  unsigned int size = fread_s(&codes[0], sizeof(CodeInfo) * totalCnt * 2, sizeof(CodeInfo), totalCnt * 2, fpFile);
  if (size != totalCnt * 2U)
  {
    fclose(fpFile);
    printf("Error codes-file reading. Clean build. \n");
    Reset();
    return;
  }

  needWrite = false;
  similar = _similar;
  printf("Codes-file reading OK. \n");
  fclose(fpFile);*/
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UberShaderFileInfo::Build( LPD3DXBUFFER *matrix )
{
  if (0 == matrix)
    return;

  unsigned int totalCnt = shader.GetTotalCount();

  if (!needWrite)
  {
    printf("Use build data - %.2f percents uniq codes\n", float(2 * totalCnt - similar) * 100.f / float(2 * totalCnt));
    return;
  }

  for (unsigned int idxWrite = 0; idxWrite < 2 * totalCnt; ++idxWrite)
  {
    if (0 == matrix[idxWrite])
      continue;

    char const *buf1 = (char const *)matrix[idxWrite]->GetBufferPointer();
    const int size1  = matrix[idxWrite]->GetBufferSize();

    unsigned int CRC_Write = CRC32(buf1, size1);
    codes[idxWrite].CRC = CRC_Write;

    for (unsigned int idxRead = 0; idxRead < idxWrite; ++idxRead)
    {
      if (0 == matrix[idxRead])
        continue;

      char const *buf2 = (char const *)matrix[idxRead]->GetBufferPointer();
      const int size2  = matrix[idxRead]->GetBufferSize();

      if (codes[idxRead].CRC == CRC_Write)
        if (size1 == size2)
          if (0 == memcmp(buf1, buf2, size1))
          {
            codes[idxWrite].idx = idxRead;
            //codes[idxWrite].CRC = CRC;

            similar ++;
            break;
          }
    }
  }
  
  printf("Build info-data done %.2f percents uniq codes\n", float(2 * totalCnt - similar) * 100.f / float(2 * totalCnt));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UberShaderFileInfo::Write( int isV20 )
{
  if (!needWrite)
    return;

  unsigned int totalCnt = shader.GetTotalCount();
  FILE *fpFile;

  string filename;
  string ext;

  if (isV20)
    ext = ".codes2";
  else
    ext = ".codes";

  filename = directory + shader.shaderName + ext;
  fopen_s(&fpFile, filename.c_str(), "wb");
  if (0 == fpFile)
  {
    printf("ERROR 001: Can't open %s file to write\nTry to write to current directory.\n", filename.c_str());
    
    filename = shader.shaderName + ext;
    fopen_s(&fpFile, filename.c_str(), "wb");
    if (0 == fpFile)
      printf("ERROR 002: Can't open %s file to write. Exit.\n", filename.c_str());
  }                                                          

  printf("Writing .codes file \n");
  fwrite(&totalCnt, 4, 1, fpFile);
  fwrite(&similar, 4, 1, fpFile);
  fwrite(&codes[0], sizeof(CodeInfo), totalCnt * 2, fpFile);

  fclose(fpFile);   
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LoadShadersCollection( const string& fileName, vector<UberShaderDesc>* pShaders )
{
	CObj<FileStream> pStream = new FileStream( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
	if ( !IsValid( pStream ) || !pStream->IsOk() )
		return false;

	CObj<IXmlSaver> pSaver = CreateXmlSaver( pStream, true );
	pSaver->Add( "shaders", pShaders );
	pSaver = 0;

	pStream = 0;
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
