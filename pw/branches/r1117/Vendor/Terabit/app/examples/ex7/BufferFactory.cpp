#include "BufferFactory.h"

BufferFactory::BufferFactory(size_t chunk_size)
: Terabit::MessageBlockFactory ()
, mtx_           ()
, lock_          (mtx_)
, mb_allocator_  (sizeof(ACE_Message_Block))
, db_allocator_  (sizeof(ACE_Data_Block))
, buf_allocator_ (chunk_size)
{
}

BufferFactory::~BufferFactory(void)
{
}

ACE_Message_Block *
BufferFactory::alloc_msg (size_t length)
{
    ACE_Message_Block *mb = 0;

    ACE_NEW_MALLOC_RETURN (
        mb,
        static_cast<ACE_Message_Block *> (
            mb_allocator_.malloc (sizeof(ACE_Message_Block))),
        ACE_Message_Block  (length,                     // size
                            ACE_Message_Block::MB_DATA, // type
                            0,                          // cont
                            0,                          // data
		                    &buf_allocator_,            //
                            &lock_,                     // lock
                            ACE_DEFAULT_MESSAGE_BLOCK_PRIORITY,
		                    ACE_Time_Value::zero,
		                    ACE_Time_Value::max_time,
		                   	&db_allocator_,
                            &mb_allocator_),
        0);

    //ACE_Data_Block *db = 
    //    (ACE_Data_Block *) db_allocator_.malloc(sizeof(ACE_Data_Block));

    //if (db == 0)
    //    return 0;

    //new (db) 
    //    ACE_Data_Block (length,                      // size
    //                    ACE_Message_Block::MB_DATA,  // type
    //                    0,                           // data
    //                    &this->buf_allocator_,       // data allocator
    //                    &lock_,                      // lock
    //                    Terabit::MessageBlockFactory::EXTERNAL_MB_FLAG,
    //                                                 // flags
    //                    &this->db_allocator_);       // data block allocator

    //ACE_Message_Block *mb =
    //    (ACE_Message_Block*) mb_allocator_.malloc(sizeof(ACE_Message_Block));

    //new (mb)
    //    ACE_Message_Block (db,   // Data block
    //                       Terabit::MessageBlockFactory::EXTERNAL_MB_FLAG,
    //                                                 // flags
    //                       &this->mb_allocator_);

    mb->set_flags (Terabit::MessageBlockFactory::FLG_MB_SHARED);


    return mb;
}

void
BufferFactory::free_msg (ACE_Message_Block * mb)
{
    ACE_Message_Block::release(mb);
}
