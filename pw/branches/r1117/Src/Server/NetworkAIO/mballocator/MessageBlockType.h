#pragma once

namespace TransportLayer
{
  namespace TL = TransportLayer;

  namespace MBType
  {
    enum Enum
    {
      NOTYPE_BLOCK = 0,
      FIRST_BLOCK_TYPE = NOTYPE_BLOCK,
      READ_BLOCK = 1,
      WRITE_BLOCK = 2,
      LAST_BLOCK_TYPE = WRITE_BLOCK,
      NUMBER_OF_BLOCK_TYPE = LAST_BLOCK_TYPE + 1
    };
  }
}
