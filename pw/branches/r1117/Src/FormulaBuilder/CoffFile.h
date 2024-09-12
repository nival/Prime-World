#ifndef COFFFILE_H_
#define COFFFILE_H_

#include <typeinfo>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "../System/Asserts.h"
#include "../System/nlist.h"
#include "../System/nvector.h"
#include "../System/nstring.h"
using namespace nstl;
#include "../System/StrProc.h"
//#include "../System/Logger.h"
//#include "../System/SystemLog.h"
#include "System/Geom.h"
#include "../System/ScopedArray.h"


#pragma pack(push, 1)
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef char CoffName[8];
struct CoffImage
{
  typedef unsigned short word;
  typedef unsigned int dword;
  typedef unsigned char byte;

  struct CoffHeader
	{
		word  machine;
    word  nSectionsCount;
		dword timeStamp;
		dword pSymbols;
		dword nSymbols;
		word  nOptionalHeaderSize;
    word  flags;
	};
  struct CoffRelocation
  {
    dword dwOffset;
    dword nSymbol;
    word  type;
  };
	struct CoffSection
	{
		CoffName szName;
		dword nVirtualSize;
		dword nVirtualAddress;
		dword nSizeOfRawData;
		unsigned char  * pRawData; //pointer in 4 bytes here
		CoffRelocation * pRelocations;
		dword pLineNumbers;
		word  nNumberOfRelocations;
    word  nNumberOfLinenumbers;
		dword nFlags;
	};
	struct CoffSymbol
	{
		CoffName szName;
		int       nValue;
		word      nSection;
    word      nType;
		byte      nStorageClass;
    byte      nAuxSymbols;
	};
	struct CoffSectionDefinition
	{
		dword dwSize;
		word  nRelocs;
    word  nLineNumbers;
		dword dwChecksum;
		word  nNumber;
		byte  nSelection;
		byte  unused[3];
	};
	struct CoffWeakExternal
	{
		dword dwTagIndex;
		dword dwFlags;
		byte  unused[10];
	};

	CoffHeader  *pHdr;
	CoffSection *pSections;
	CoffSymbol  *pSymbols;
	vector<byte> image;


  bool Read(FILE *f, unsigned int nSize);
  bool Read(char const * fileName);
  //bool Link(LinkTable);
private:
  template<typename T1, typename T2> T1 *shiftPointer(T1 *p, T2 nShift)
  {
    return (T1 *)((byte *)p + (dword)nShift);
  }
};
#pragma pack(pop)
////////////////////////////////////////////////////////////////////////////////////////////////////
char const *GetName(CoffImage const *image, int nSymbolGlobalIdx);
char const *GetName(CoffImage const &image, const CoffName &a);

#endif /* COFFFILE_H_ */
