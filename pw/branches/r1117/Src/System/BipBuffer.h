#ifndef BIPBUFFER_H_
#define BIPBUFFER_H_

/*
Copyright (c) 2003 Simon Cooke, All Rights Reserved

Licensed royalty-free for commercial and non-commercial
use. All that I ask is that you send me an email
telling me that you're using my code. It'll make me
feel warm and fuzzy inside. simoncooke@earthlink.net

*/
#undef GetFreeSpace

class BipBuffer
{
private:
  BYTE* pBuffer;
  int ixa;
  int sza;
  int ixb;
  int szb;
  int buflen;
  int ixResrv;
  int szResrv;
public:
  BipBuffer() : pBuffer(NULL), ixa(0), sza(0), ixb(0), szb(0), buflen(0), ixResrv(0), szResrv(0)
  {
  }

  ~BipBuffer()
  {
    FreeBuffer();
  }


  // Allocate Buffer
  //
  // Allocates a buffer in virtual memory, to the nearest page size (rounded up)
  //
  // Parameters:
  //   int buffersize                size of buffer to allocate, in bytes (default: 4096)
  //
  // Returns:
  //   bool                        true if successful, false if buffer cannot be allocated

  bool AllocateBuffer( int buffersize )
  {
    if (buffersize <= 0) 
      return false;

    if (pBuffer != NULL) 
      FreeBuffer();

    pBuffer = new BYTE[buffersize];
    if (pBuffer == NULL) 
      return false;

    buflen = buffersize;
    return true;
  }

  bool ResizeBuffer( int buffersize )
  {
    int delta = buffersize - buflen;
    if ( delta <= 0 ) 
      return false;

    BYTE* newBuf = new BYTE[ buffersize ];

    if( szb == 0 )
    {
      //insert free space at the end
      memcpy( newBuf, pBuffer, sza );
    }
    else
    {
      //insert free space between B and A blocks
      memcpy( newBuf + ixb, pBuffer + ixb, szb );
      memcpy( newBuf + ixa + delta , pBuffer + ixa, sza );
      if ( ixResrv > ixa )
        ixResrv += delta;
      ixa += delta;
    }
    buflen += delta;

    delete[] pBuffer;
    pBuffer = newBuf;

    return true;
  }

  ///
  /// \brief Clears the buffer of any allocations.
  ///
  /// Clears the buffer of any allocations or reservations. Note; it
  /// does not wipe the buffer memory; it merely resets all pointers,
  /// returning the buffer to a completely empty state ready for new
  /// allocations.
  ///

  void Clear()
  {
    ixa = sza = ixb = szb = ixResrv = szResrv = 0;
  }

  // Free Buffer
  //
  // Frees a previously allocated buffer, resetting all internal pointers to 0.
  //
  // Parameters:
  //   none
  //
  // Returns:
  //   void

  void FreeBuffer()
  {
    ixa = sza = ixb = szb = buflen = 0;

    delete[] pBuffer;

    pBuffer = NULL;
  }

  // Reserve
  //
  // Reserves space in the buffer for a memory write operation
  //
  // Parameters:
  //   int size                amount of space to reserve
  //   OUT int& reserved        size of space actually reserved
  //
  // Returns:
  //   BYTE*                    pointer to the reserved block
  //
  // Notes:
  //   Will return NULL for the pointer if no space can be allocated.
  //   Can return any value from 1 to size in reserved.
  //   Will return NULL if a previous reservation has not been committed.

  BYTE* Reserve(int size, /*OUT*/ int& reserved)
  {
    // We always allocate on B if B exists; this means we have two blocks and our buffer is filling.
    if (szb)
    {
      int freespace = GetBFreeSpace();

      if (size < freespace) freespace = size;

      if (freespace == 0) return NULL;

      szResrv = freespace;
      reserved = freespace;
      ixResrv = ixb + szb;
      return pBuffer + ixResrv;
    }
    else
    {
      // Block b does not exist, so we can check if the space AFTER a is bigger than the space
      // before A, and allocate the bigger one.

      int freespace = GetSpaceAfterA();
      if (freespace >= ixa)
      {
        if (freespace == 0) return NULL;
        if (size < freespace) freespace = size;

        szResrv = freespace;
        reserved = freespace;
        ixResrv = ixa + sza;
        return pBuffer + ixResrv;
      }
      else
      {
        if (ixa == 0) return NULL;
        if (ixa < size) size = ixa;
        szResrv = size;
        reserved = size;
        ixResrv = 0;
        return pBuffer;
      }
    }
  }

  // GetFreeSpace
  //
  // Queries how much space can be reserved.
  //
  // Returns:
  //   int                     amount of memory that an be reserved

  int GetFreeSpace() const
  {
    // We always allocate on B if B exists; this means we have two blocks and our buffer is filling.
    if (szb)
      return GetBFreeSpace();

    // Block b does not exist, so we can check if the space AFTER a is bigger than the space
    // before A, and allocate the bigger one.
    int freespace = GetSpaceAfterA();
    if (freespace >= ixa)
      return freespace; 
    else
      return ixa;
  }

  // Commit
  //
  // Commits space that has been written to in the buffer
  //
  // Parameters:
  //   int size                number of bytes to commit
  //
  // Notes:
  //   Committing a size > than the reserved size will cause an assert in a debug build;
  //   in a release build, the actual reserved size will be used.
  //   Committing a size < than the reserved size will commit that amount of data, and release
  //   the rest of the space.
  //   Committing a size of 0 will release the reservation.
  //

  void Commit(int size)
  {
    if (size == 0)
    {
      // decommit any reservation
      szResrv = ixResrv = 0;
      return;
    }

    // If we try to commit more space than we asked for, clip to the size we asked for.

    if (size > szResrv)
    {
      size = szResrv;
    }

    // If we have no blocks being used currently, we create one in A.

    if (sza == 0 && szb == 0)
    {
      ixa = ixResrv;
      sza = size;

      ixResrv = 0;
      szResrv = 0;
      return;
    }

    if (ixResrv == sza + ixa)
    {
      sza += size;
    }
    else
    {
      szb += size;
    }

    ixResrv = 0;
    szResrv = 0;
  }

  // GetContiguousBlock
  //
  // Gets a pointer to the first contiguous block in the buffer, and returns the size of that block.
  //
  // Parameters:
  //   OUT int & size            returns the size of the first contiguous block
  //
  // Returns:
  //   BYTE*                    pointer to the first contiguous block, or NULL if empty.

  BYTE* GetContiguousBlock(/*OUT*/ int& size) const
  {
    if (sza == 0)
    {
      size = 0;
      return NULL;
    }

    size = sza;
    return pBuffer + ixa;

  }

  // DecommitBlock
  //
  // Decommits space from the first contiguous block
  //
  // Parameters:
  //   int size                amount of memory to decommit
  //
  // Returns:
  //   nothing

  void DecommitBlock(int size)
  {
    if (size >= sza)
    {
      ixa = ixb;
      sza = szb;
      ixb = 0;
      szb = 0;
    }
    else
    {
      sza -= size;
      ixa += size;
    }
  }

  // GetCommittedSize
  //
  // Queries how much data (in total) has been committed in the buffer
  //
  // Parameters:
  //   none
  //
  // Returns:
  //   int                    total amount of committed data in the buffer

  int    GetCommittedSize() const
  {
    return sza + szb;
  }

  // GetReservationSize
  //
  // Queries how much space has been reserved in the buffer.
  //
  // Parameters:
  //   none
  //
  // Returns:
  //   int                    number of bytes that have been reserved
  //
  // Notes:
  //   A return value of 0 indicates that no space has been reserved

  int GetReservationSize() const
  {
    return szResrv;
  }

  // GetBufferSize
  //
  // Queries the maximum total size of the buffer
  //
  // Parameters:
  //   none
  //
  // Returns:
  //   int                    total size of buffer

  int GetBufferSize() const
  {
    return buflen;
  }

  // IsInitialized
  //
  // Queries whether or not the buffer has been allocated
  //
  // Parameters:
  //   none
  //
  // Returns:
  //   bool                    true if the buffer has been allocated

  bool IsInitialized() const
  {
    return pBuffer != NULL;
  }

private:
  int GetSpaceAfterA() const
  {
    return buflen - ixa - sza;
  }

  int GetBFreeSpace() const
  {
    return ixa - ixb - szb;
  }
};

#endif

