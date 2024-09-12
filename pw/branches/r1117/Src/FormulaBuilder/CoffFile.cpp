/*
* CoffFile.cpp
*
*  Created on: 19.01.2009
*      Author: earnol
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <memory.h>
#include <windows.h>
#include <assert.h>
#include "System/DefaultTypes.h"
#include "CoffFile.h"

bool CoffImage::Read(char const * fileName)
{
  struct __stat64 buf;
  int result;
  bool bRet = false;
  FILE *fFile = NULL;

  result = _stat64(fileName, &buf);

  NI_VERIFY(result == 0, "Problem getting information", return false;);
  fopen_s(&fFile, fileName, "rb");
  if(fFile != NULL)
  {
    bRet = Read(fFile, buf.st_size);
    fclose(fFile);
  }
  return bRet;
}

bool CoffImage::Read(FILE *f, unsigned int nSize)
{
  NI_VERIFY(f != NULL, "File not opened", return false;);

  image.resize(nSize);
  fread_s(&image[0], image.size(), sizeof(byte), image.size(), f);
  pHdr = (CoffHeader *)&image[0];
  NI_VERIFY(pHdr->machine == IMAGE_FILE_MACHINE_I386, "Not win32 OBJ file", return false;);

  NI_VERIFY(pHdr->nOptionalHeaderSize == 0 , "Optional header is not supported. Should be 0 for valid *.OBJ", return false;);

  NI_VERIFY(pHdr->nSectionsCount > 0 , "File does not contain any data. Empty OBJ file.", return false;);

  NI_VERIFY((pHdr->flags & (IMAGE_FILE_RELOCS_STRIPPED | IMAGE_FILE_EXECUTABLE_IMAGE | IMAGE_FILE_AGGRESIVE_WS_TRIM | IMAGE_FILE_BYTES_REVERSED_LO | IMAGE_FILE_DEBUG_STRIPPED | IMAGE_FILE_DLL)) == 0,
            "Ivalid image flags", return false;);

  NI_VERIFY((pHdr->flags & IMAGE_FILE_LARGE_ADDRESS_AWARE) == 0, "PAE images not supported", return false;);

  pSections = (CoffSection *)&image[sizeof(CoffHeader)];
  //validate section names
  int nI;
  for(nI = 0; nI < pHdr->nSectionsCount; nI++)
  {
    pSections[nI].szName[7]     = '\0'; //to be able to use standard procedures to work with strings
    if(pSections[nI].nSizeOfRawData > 0)
    {
      pSections[nI].pRawData      = shiftPointer(pSections[nI].pRawData    , pHdr);
    }
    if(pSections[nI].nNumberOfRelocations > 0)
    {
      pSections[nI].pRelocations  = shiftPointer(pSections[nI].pRelocations, pHdr);
    }
  }
  pSymbols  = (CoffSymbol  *)&image[pHdr->pSymbols    ];
  return true;
}


char const *GetName(CoffImage const *image, int nSymbolGlobalIdx)
{
  CoffImage::CoffSymbol &symb = image->pSymbols[nSymbolGlobalIdx];
  return GetName(*image, symb.szName);
}

char const *GetName(CoffImage const &image, const CoffName &a)
{
  const int *pA = (const int*)&a;
  if(pA[0] != 0)
  {
    const int N_TEMP_BUF = 10;
    char szBuf[N_TEMP_BUF];
    memset(szBuf, 0, N_TEMP_BUF );
    strncpy_s(szBuf, (const char*)&a, sizeof(a));
    return (const char*)&a;
  }
  int nOffs = image.pHdr->pSymbols + image.pHdr->nSymbols * 18;
  return (const char*)&image.image[ nOffs + pA[1] ];
}
