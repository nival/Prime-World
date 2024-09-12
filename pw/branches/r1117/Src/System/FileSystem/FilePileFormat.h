#ifndef FILEPILEFORMAT_H_INCLUDED
#define FILEPILEFORMAT_H_INCLUDED

#include "../DefaultTypes.h"

namespace fileSystem
{

typedef ni_detail::Byte     Byte;
typedef ni_detail::UInt32   UInt32;


const static UInt32 FILEPILE_TAG = 0x656c6950;
const static UInt32 FILEPILE_VERSION = 0x00010002;

const static UInt32 FILEPILE_COMPRESSED = 0x0001;


#pragma pack(push, 1)

struct SFilePileTail
{
  UInt32    tag;
  UInt32    version;
  UInt32    filesNumber;
  UInt32    stringsOffset;
  UInt32    stringsLength;
  UInt32    fileIndexOffset;

  SFilePileTail() :
  tag( FILEPILE_TAG ), version( FILEPILE_VERSION ), filesNumber( 0 ), stringsOffset( 0 ), stringsLength( 0 ), fileIndexOffset( 0 ) {}
};



struct SFilePileEntry
{
  UInt32    size;
  UInt32    sourceSize; //uncompressed
  UInt32    offset;
  UInt32    flags; // FILEPILE_COMPRESSED
  UInt32    fileNameOffset;
  UInt32    crc;

  SFilePileEntry() : size( 0 ), offset( 0 ), flags( 0 ), fileNameOffset( 0 ), crc( 0 ) {}
};


} //namespace fileSystem

#pragma pack(pop)

#endif //FILEPILEFORMAT_H_INCLUDED
